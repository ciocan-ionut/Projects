using Formula_1_SGBD.DAOs;
using Formula_1_SGBD.Database;
using Formula_1_SGBD.Domain;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Serialization;
using System.Data.Entity;

namespace Formula_1_SGBD
{
    public partial class DashboardForm : Form
    {
        private int selectedTeamID = -1;
        private Driver selectedDriver = null;

        public DashboardForm()
        {
            InitializeComponent();
        }

        private void Dashboard_Load(object sender, EventArgs e)
        {
            LoadTeams();
        }

        private void LoadTeams()
        {
            using (var context = new MyContext())
            {
                dataGridViewTeams.DataSource = context.Teams
                    .Select(t => new { t.ID, t.Name, t.Budget, t.Location })
                    .ToList();
            }
        }

        private void RefreshDrivers()
        {
            if (selectedTeamID != -1)
            {
                using (var context = new MyContext())
                {
                    var drivers = context.Drivers
                        .Select(d => new { d.ID, d.Name, d.Salary, d.ContractExpDate, d.TeamID })
                        .Where(d => d.TeamID == selectedTeamID)
                        .ToList();
                    dataGridViewDrivers.DataSource = drivers;
                }
            }
        }

        private void dataGridViewTeams_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                selectedTeamID = (int)dataGridViewTeams.Rows[e.RowIndex].Cells["ID"].Value;
                RefreshDrivers();
            }
        }

        private void addBtn_Click(object sender, EventArgs e)
        {
            if (selectedTeamID == -1)
            {
                MessageBox.Show("Please select a team first.");
                return;
            }

            DriverForm driverForm = new DriverForm(selectedTeamID, null);
            driverForm.ShowDialog();
            RefreshDrivers();
        }

        private void dataGridViewDrivers_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                int selectedDriverID = (int)dataGridViewDrivers.Rows[e.RowIndex].Cells["ID"].Value;
                string name = dataGridViewDrivers.Rows[e.RowIndex].Cells["Name"].Value.ToString();
                int salary = (int)dataGridViewDrivers.Rows[e.RowIndex].Cells["Salary"].Value;
                DateTime contractExpDate = (DateTime)dataGridViewDrivers.Rows[e.RowIndex].Cells["ContractExpDate"].Value;
                selectedDriver = new Driver(selectedDriverID, name, salary, contractExpDate, selectedTeamID);
            }
        }

        private void editBtn_Click(object sender, EventArgs e)
        {
            if (selectedDriver == null)
            {
                MessageBox.Show("Please select a driver first.");
                return;
            }

            DriverForm driverForm = new DriverForm(selectedTeamID, selectedDriver);
            driverForm.ShowDialog();
            RefreshDrivers();
        }

        private void deleteBtn_Click(object sender, EventArgs e)
        {
            if (selectedDriver == null)
            {
                MessageBox.Show("Please select a driver first.");
                return;
            }

            DialogResult result = MessageBox.Show("Are you sure you want to delete this driver?", "Confirm Deletion", MessageBoxButtons.YesNo);
            if (result == DialogResult.Yes)
            {
                DriverORM driverDAO = new DriverORM();
                try
                {
                    driverDAO.DeleteDriver(selectedDriver.ID);
                    RefreshDrivers();
                }
                catch (SqlException ex)
                {
                    MessageBox.Show("An error occurred while trying to delete the driver: " + ex.Message);
                }
            }
        }

        private void runTestBtn_Click(object sender, EventArgs e)
        {
            RunPerformanceTest();
            RunLeakTest();
            RunLoadingDemonstration();
            MessageBox.Show("Tests completed. Check the console for results.");
        }

        private void RunPerformanceTest()
        {
            int iterations = 100;
            // No pool
            string connStringNoPool = "Data Source=LAPTOP-IONUT\\SQLEXPRESS01;Initial Catalog=Formula1;Integrated Security=True;TrustServerCertificate=True;Pooling=false;";

            // With pool
            string connStringPool = "Data Source=LAPTOP-IONUT\\SQLEXPRESS01;Initial Catalog=Formula1;Integrated Security=True;TrustServerCertificate=True;Pooling=true;Max Pool Size=10;Min Pool Size=5;";

            Stopwatch swNoPool = Stopwatch.StartNew();
            for (int i = 0; i < iterations; i++)
            {
                using (SqlConnection conn = new SqlConnection(connStringNoPool))
                {
                    conn.Open();
                }
            }
            swNoPool.Stop();

            Stopwatch swPool = Stopwatch.StartNew();
            for (int i = 0; i < iterations; i++)
            {
                using (SqlConnection conn = new SqlConnection(connStringPool))
                {
                    conn.Open();
                }
            }
            swPool.Stop();

            double totalNoPoolMs = swNoPool.Elapsed.TotalMilliseconds;
            double avgNoPoolMs = totalNoPoolMs / iterations;

            double totalPoolMs = swPool.Elapsed.TotalMilliseconds;
            double avgPoolMs = totalPoolMs / iterations;

            Debug.WriteLine("\n=== SARCINA A: REZULTATE TEST DE PERFORMANTA ===");
            Debug.WriteLine($"FARA POOLING: Timp total = {totalNoPoolMs:F2} ms | Timp mediu/conexiune = {avgNoPoolMs:F4} ms");
            Debug.WriteLine($"CU POOLING:   Timp total = {totalPoolMs:F2} ms | Timp mediu/conexiune = {avgPoolMs:F4} ms");
            Debug.WriteLine($"CONCLUZIE:    Cu Connection Pooling aplicatia este de aproximativ {(totalNoPoolMs / totalPoolMs):F2} ori mai rapida la gestionarea conexiunilor.");
            Debug.WriteLine("==================================================================\n");
        }

        private void RunLeakTest()
        {
            Debug.WriteLine("=== SARCINA B: TEST SCURGERE CONEXIUNI ===");
            string connStringPool = "Data Source=LAPTOP-IONUT\\SQLEXPRESS01;Initial Catalog=Formula1;Integrated Security=True;TrustServerCertificate=True;Pooling=true;Max Pool Size=10;";
            List<SqlConnection> leakedConnections = new List<SqlConnection>();

            try
            {
                for (int i = 1; i <= 15; i++)
                {
                    SqlConnection conn = new SqlConnection(connStringPool);
                    conn.Open();

                    leakedConnections.Add(conn);
                    Debug.WriteLine($"Conexiunea {i} deschisa cu succes.");
                }
            }
            catch (InvalidOperationException ex)
            {
                Debug.WriteLine($"\nPool-ul de conexiuni a fost epuizat.");
                Debug.WriteLine($"Mesaj eroare: {ex.Message}");
            }
            finally
            {
                foreach (var conn in leakedConnections)
                {
                    if (conn.State == System.Data.ConnectionState.Open)
                    {
                        conn.Close();
                    }
                }
                Debug.WriteLine("Conexiunile au fost inchise fortat.");
            }
            Debug.WriteLine("==========================================\n");
        }

        private void RunLoadingDemonstration()
        {
            Debug.WriteLine("=== DEMONSTRARE LAZY LOADING ===");
            using (var context = new MyContext())
            {
                var teamLazy = context.Teams.FirstOrDefault();
                Debug.WriteLine($"Echipa incarcata: {teamLazy?.Name}");

                Debug.WriteLine("[Accesam proprietatea 'Drivers'...");
                int driverCount = teamLazy?.Drivers.Count ?? 0;

                Debug.WriteLine($"Soferi gasiti: {driverCount}");
            }

            Debug.WriteLine("=== DEMONSTRARE EAGER LOADING ===");

            using (var context = new MyContext())
            {
                var teamEager = context.Teams.Include(t => t.Drivers).FirstOrDefault();
                Debug.WriteLine($"Echipa incarcata: {teamEager?.Name}");

                Debug.WriteLine("Accesam proprietatea 'Drivers'...");
                int driverCount = teamEager?.Drivers.Count ?? 0;

                Debug.WriteLine($"Soferi gasiti: {driverCount}");
            }
        }
    }
}
