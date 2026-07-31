using System;
using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;
using System.Linq;

namespace Lab_2
{
    public partial class Form1 : Form
    {
        private string connectionString = ConfigurationManager.ConnectionStrings["Formula1ConnectionString"].ConnectionString;

        public Form1()
        {
            InitializeComponent();

            dirtyReadBtn.Click += dirtyReadBtn_Click;
            nrrBtn.Click += nrrBtn_Click;
            phantomReadBtn.Click += phantomReadBtn_Click;
            lostUpdateBtn.Click += lostUpdateBtn_Click;
            deadlockBtn.Click += deadlockBtn_Click;
            batchTestBtn.Click += batchTestBtn_Click;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            driversTableAdapter.Fill(formula1DataSet.Drivers);
        }

        private void Log(string message)
        {
            if (sqlLog.InvokeRequired)
            {
                sqlLog.Invoke(new Action(() => Log(message)));
            }
            else
            {
                sqlLog.AppendText($"[{DateTime.Now:HH:mm:ss}] {message}{Environment.NewLine}");
                sqlLog.ScrollToCaret();
            }
        }

        private void RefreshGrid()
        {
            if (InvokeRequired)
            {
                Invoke(new Action(RefreshGrid));
                return;
            }
            driversTableAdapter.Fill(formula1DataSet.Drivers);
            Log("Table updated.");
        }

        private async void dirtyReadBtn_Click(object sender, EventArgs e)
        {
            sqlLog.Clear();
            Log("Dirty Read");

            await Task.Run(async () =>
            {
                using (var connA = new SqlConnection(connectionString))
                using (var connB = new SqlConnection(connectionString))
                {
                    await connA.OpenAsync();
                    await connB.OpenAsync();

                    // Tranzacția A
                    var txA = connA.BeginTransaction();
                    Log("Transaction A: BEGIN TRANSACTION");

                    var cmdA = new SqlCommand("UPDATE drivers SET salary = 10000 WHERE id = 1", connA, txA);
                    await cmdA.ExecuteNonQueryAsync();
                    Log("Transaction A: Salariu actualizat la 10000 (ne-comis)");

                    await Task.Delay(1000);

                    // Tranzacția B
                    var txB = connB.BeginTransaction(IsolationLevel.ReadUncommitted);
                    Log("Transaction B: BEGIN TRANSACTION (READ UNCOMMITTED)");

                    var cmdB = new SqlCommand("SELECT salary FROM drivers WHERE id = 1", connB, txB);
                    var val = await cmdB.ExecuteScalarAsync();
                    Log($"Transaction B: Valoarea citită este {val}");
                    txB.Commit();

                    txA.Rollback();
                    Log("Transaction A: Rollback efectuat!");
                }
            });

            await Task.Run(async () =>
            {
                using (var connA = new SqlConnection(connectionString)) using (var connB = new SqlConnection(connectionString))
                {
                    await connA.OpenAsync(); await connB.OpenAsync();
                    var txA = connA.BeginTransaction();
                    Log("Transaction A: BEGIN TRANSACTION");

                    await new SqlCommand("UPDATE drivers SET salary = 10000 WHERE id = 1", connA, txA).ExecuteNonQueryAsync();
                    Log("Transaction A: Salariu actualizat la 10000 (ne-comis)");

                    await Task.Delay(500);

                    var txB = connB.BeginTransaction(IsolationLevel.ReadCommitted);
                    Log("Transaction B: BEGIN TRANSACTION (Așteaptă după A)");

                    var cmdB = new SqlCommand("SELECT salary FROM drivers WHERE id = 1", connB, txB);

                    // Tx A face rollback după 1.5 secunde, deblocând Tx B
                    _ = Task.Run(async () => { 
                        await Task.Delay(1500); 
                        txA.Rollback(); 
                        Log("Transaction A: Rollback efectuat!"); 
                    });

                    var val = await cmdB.ExecuteScalarAsync();
                    Log($"Transaction B: Valoarea citită este {val}");
                    txB.Commit();
                }
            });
            RefreshGrid();
        }

        private async void nrrBtn_Click(object sender, EventArgs e)
        {
            sqlLog.Clear();
            Log("Non-Repeatable Read");

            await Task.Run(async () =>
            {
                using (var connA = new SqlConnection(connectionString))
                using (var connB = new SqlConnection(connectionString))
                {
                    await connA.OpenAsync();
                    await connB.OpenAsync();

                    // Tranzacția A citește
                    var txA = connA.BeginTransaction(IsolationLevel.ReadCommitted); 
                    Log("Transaction A: BEGIN TRANSACTION (READ COMMITTED)");

                    var cmdA1 = new SqlCommand("SELECT salary FROM drivers WHERE id = 1", connA, txA);
                    var val1 = await cmdA1.ExecuteScalarAsync();
                    Log($"Transaction A: Prima citire - {val1}");

                    // Tranzacția B actualizează
                    var txB = connB.BeginTransaction();
                    var cmdB = new SqlCommand("UPDATE drivers SET salary = 15000 WHERE id = 1", connB, txB);
                    await cmdB.ExecuteNonQueryAsync();
                    txB.Commit();
                    Log("Transaction B: Actualizat la 15000 și comis");

                    // Tranzacția A citește din nou
                    var cmdA2 = new SqlCommand("SELECT salary FROM drivers WHERE id = 1", connA, txA);
                    var val2 = await cmdA2.ExecuteScalarAsync();
                    Log($"Transaction A: A doua citire - {val2}");

                    txA.Commit();
                }
            });

            await Task.Run(async () =>
            {
                using (var connA = new SqlConnection(connectionString)) using (var connB = new SqlConnection(connectionString))
                {
                    await connA.OpenAsync(); await connB.OpenAsync();
                    var txA = connA.BeginTransaction(IsolationLevel.RepeatableRead);
                    Log("Transaction A: BEGIN TRANSACTION");

                    var val1 = await new SqlCommand("SELECT salary FROM drivers WHERE id = 1", connA, txA).ExecuteScalarAsync();
                    Log($"Transaction A: Prima citire - {val1}");

                    Log("Transaction B: BEGIN TRANSACTION (Blocat de A)");
                    var txB = connB.BeginTransaction();
                    var cmdB = new SqlCommand("UPDATE drivers SET salary = 12000 WHERE id = 1", connB, txB);

                    var updateTask = Task.Run(async () => { 
                        await cmdB.ExecuteNonQueryAsync(); 
                        txB.Commit(); 
                        Log("Transaction B: Actualizare finalizată (După ce A a terminat)."); 
                    });

                    await Task.Delay(1000);
                    var val2 = await new SqlCommand("SELECT salary FROM drivers WHERE id = 1", connA, txA).ExecuteScalarAsync();
                    Log($"Transaction A: A doua citire - {val2}");
                    txA.Commit();

                    await updateTask;
                }
            });
            RefreshGrid();
        }

        private async void phantomReadBtn_Click(object sender, EventArgs e)
        {
            sqlLog.Clear();
            Log("Phantom Read");

            string query = "SELECT COUNT(*) FROM drivers WHERE ContractExpDate = '2026-12-31'";

            await Task.Run(async () =>
            {
                using (var connA = new SqlConnection(connectionString))
                using (var connB = new SqlConnection(connectionString))
                {
                    await connA.OpenAsync();
                    await connB.OpenAsync();

                    var txA = connA.BeginTransaction(IsolationLevel.RepeatableRead);
                    Log("Transaction A: BEGIN TRANSACTION (REPEATABLE READ)");

                    var cmdA1 = new SqlCommand(query, connA, txA);
                    var count1 = await cmdA1.ExecuteScalarAsync();
                    Log($"Transaction A: Prima numărătoare - {count1}");

                    var txB = connB.BeginTransaction();
                    var cmdB = new SqlCommand("INSERT INTO drivers (name, salary, ContractExpDate) VALUES ('Sofer Nou', 4000, '2026-12-31')", connB, txB);
                    await cmdB.ExecuteNonQueryAsync();
                    txB.Commit();
                    Log("Transaction B: Șofer nou inserat");

                    var cmdA2 = new SqlCommand(query, connA, txA);
                    var count2 = await cmdA2.ExecuteScalarAsync();
                    Log($"Transaction A: A doua numărătoare - {count2}");

                    txA.Commit();
                }
            });

            using (var conn = new SqlConnection(connectionString)) {
                await conn.OpenAsync(); 
                await new SqlCommand("DELETE FROM drivers WHERE name = 'Sofer Nou'", conn).ExecuteNonQueryAsync(); 
            }

            await Task.Run(async () =>
            {
                using (var connA = new SqlConnection(connectionString)) using (var connB = new SqlConnection(connectionString))
                {
                    await connA.OpenAsync(); await connB.OpenAsync();
                    var txA = connA.BeginTransaction(IsolationLevel.Serializable);
                    Log("Transaction A: BEGIN TRANSACTION");

                    var count1 = await new SqlCommand(query, connA, txA).ExecuteScalarAsync();
                    Log($"Transaction A: Prima numărătoare - {count1}");

                    Log("Transaction B: BEGIN TRANSACTION (Blocat de A)");
                    var txB = connB.BeginTransaction();
                    var cmdB = new SqlCommand("INSERT INTO drivers (name, salary, ContractExpDate) VALUES ('Sofer Nou', 4000, '2026-12-31')", connB, txB);

                    var insertTask = Task.Run(async () => { 
                        await cmdB.ExecuteNonQueryAsync(); 
                        txB.Commit(); 
                        Log("Transaction B: Inserare finalizată cu succes (după ce A a terminat)."); });

                    await Task.Delay(1000);
                    var count2 = await new SqlCommand(query, connA, txA).ExecuteScalarAsync();
                    Log($"Transaction A: A doua numărătoare - {count2}");
                    txA.Commit();

                    await insertTask;
                }
            });

            using (var conn = new SqlConnection(connectionString))
            {
                await conn.OpenAsync();
                await new SqlCommand("DELETE FROM drivers WHERE name = 'Sofer Nou'", conn).ExecuteNonQueryAsync();
            }

            RefreshGrid();
        }

        private async void lostUpdateBtn_Click(object sender, EventArgs e)
        {
            sqlLog.Clear();
            Log("Lost Update");

            // Resetăm salariul la 5000 pentru test
            using (var conn = new SqlConnection(connectionString))
            {
                conn.Open();
                new SqlCommand("UPDATE drivers SET salary = 5000 WHERE id = 1", conn).ExecuteNonQuery();
            }

            await Task.Run(async () =>
            {
                using (var connA = new SqlConnection(connectionString))
                using (var connB = new SqlConnection(connectionString))
                {
                    await connA.OpenAsync();
                    await connB.OpenAsync();

                    var txA = connA.BeginTransaction();
                    var cmdA_Read = new SqlCommand("SELECT salary FROM drivers WHERE id = 1", connA, txA);
                    int salaryA = (int)await cmdA_Read.ExecuteScalarAsync();
                    Log($"Transaction A: Citește salariu = {salaryA}");

                    var txB = connB.BeginTransaction();
                    var cmdB_Read = new SqlCommand("SELECT salary FROM drivers WHERE id = 1", connB, txB);
                    int salaryB = (int)await cmdB_Read.ExecuteScalarAsync();
                    Log($"Transaction B: Citește salariu = {salaryB}");

                    int newSalaryB = salaryB + 500;
                    var cmdB_Update = new SqlCommand($"UPDATE drivers SET salary = {newSalaryB} WHERE id = 1", connB, txB);
                    await cmdB_Update.ExecuteNonQueryAsync();
                    txB.Commit();
                    Log($"Transaction B: Actualizat la {newSalaryB} și comis");

                    int newSalaryA = salaryA + 1000;
                    var cmdA_Update = new SqlCommand($"UPDATE drivers SET salary = {newSalaryA} WHERE id = 1", connA, txA);
                    await cmdA_Update.ExecuteNonQueryAsync();
                    txA.Commit();
                    Log($"Transaction A: Actualizat la {newSalaryA} și comis (A suprascris B!)");
                }
            });
            RefreshGrid();
        }

        private async void deadlockBtn_Click(object sender, EventArgs e)
        {
            sqlLog.Clear();
            Log("Deadlock");

            var taskA = Task.Run(async () =>
            {
                using (var connA = new SqlConnection(connectionString))
                {
                    await connA.OpenAsync();
                    var txA = connA.BeginTransaction();
                    try
                    {
                        new SqlCommand("UPDATE drivers SET salary = 6000 WHERE id = 1", connA, txA).ExecuteNonQuery();
                        Log("Transaction A: A blocat rândul 1");
                        await Task.Delay(2000);

                        Log("Transaction A: Încearcă să blocheze rândul 2...");
                        new SqlCommand("UPDATE drivers SET salary = 7000 WHERE id = 2", connA, txA).ExecuteNonQuery();
                        txA.Commit();
                    }
                    catch (SqlException ex)
                    {
                        if (ex.Number == 1205)
                            Log($"Transaction A: DEADLOCK DETECTAT! {ex.Message}");
                        txA.Rollback();
                    }
                }
            });

            var taskB = Task.Run(async () =>
            {
                using (var connB = new SqlConnection(connectionString))
                {
                    await connB.OpenAsync();
                    var txB = connB.BeginTransaction();
                    try
                    {
                        new SqlCommand("UPDATE drivers SET salary = 6000 WHERE id = 2", connB, txB).ExecuteNonQuery();
                        Log("Transaction B: A blocat rândul 2");
                        await Task.Delay(2000);

                        Log("Transaction B: Încearcă să blocheze rândul 1...");
                        new SqlCommand("UPDATE drivers SET salary = 7000 WHERE id = 1", connB, txB).ExecuteNonQuery();
                        txB.Commit();
                    }
                    catch (SqlException ex)
                    {
                        if (ex.Number == 1205)
                            Log($"Transaction B: DEADLOCK DETECTAT! {ex.Message}");
                        txB.Rollback();
                    }
                }
            });

            await Task.WhenAll(taskA, taskB);
            RefreshGrid();
        }

        private async void batchTestBtn_Click(object sender, EventArgs e)
        {
            batchTestBtn.Enabled = false;
            sqlLog.Clear();
            Log("Batch Test");

            long[] autoCommit = new long[3];
            long[] batchCommit = new long[3];
            long[] singleTx = new long[3];

            await Task.Run(async () =>
            {
                for (int run = 1; run <= 3; run++)
                {
                    Log($"\nRun {run}");

                    CleanupTestRecords();

                    // Abordarea 1: Auto-Commit
                    var sw = Stopwatch.StartNew();
                    using (var conn = new SqlConnection(connectionString))
                    {
                        await conn.OpenAsync();
                        for (int i = 0; i < 5000; i++)
                        {
                            using (var cmd = new SqlCommand("INSERT INTO drivers (name, salary, ContractExpDate) VALUES (@n, 3000, '2030-01-01')", conn))
                            {
                                cmd.Parameters.AddWithValue("@n", "TestAuto" + i);
                                cmd.ExecuteNonQuery(); // Auto-commit implicit
                            }
                        }
                    }
                    sw.Stop();
                    Log($"Abordarea 1 (Auto-commit): {sw.ElapsedMilliseconds} ms");
                    autoCommit[run - 1] = sw.ElapsedMilliseconds;

                    CleanupTestRecords();

                    // Abordarea 2: Commit la fiecare 100 de rânduri
                    sw.Restart();
                    using (var conn = new SqlConnection(connectionString))
                    {
                        await conn.OpenAsync();
                        var tx = conn.BeginTransaction();
                        for (int i = 0; i < 5000; i++)
                        {
                            using (var cmd = new SqlCommand("INSERT INTO drivers (name, salary, ContractExpDate) VALUES (@n, 3000, '2030-01-01')", conn, tx))
                            {
                                cmd.Parameters.AddWithValue("@n", "TestBatch" + i);
                                cmd.ExecuteNonQuery();
                            }
                            if ((i + 1) % 100 == 0)
                            {
                                tx.Commit();
                                tx = conn.BeginTransaction();
                            }
                        }
                        tx.Commit();
                    }
                    sw.Stop();
                    Log($"Abordarea 2 (Commit la 100): {sw.ElapsedMilliseconds} ms");
                    batchCommit[run - 1] = sw.ElapsedMilliseconds;

                    CleanupTestRecords();

                    // Abordarea 3: Tranzacție Unică (toate 5000)
                    sw.Restart();
                    using (var conn = new SqlConnection(connectionString))
                    {
                        await conn.OpenAsync();
                        var tx = conn.BeginTransaction();
                        for (int i = 0; i < 5000; i++)
                        {
                            using (var cmd = new SqlCommand("INSERT INTO drivers (name, salary, ContractExpDate) VALUES (@n, 3000, '2030-01-01')", conn, tx))
                            {
                                cmd.Parameters.AddWithValue("@n", "TestSingleTx" + i);
                                cmd.ExecuteNonQuery();
                            }
                        }
                        tx.Commit();
                    }
                    sw.Stop();
                    Log($"Abordarea 3 (Tranzacție Unică): {sw.ElapsedMilliseconds} ms");
                    singleTx[run - 1] = sw.ElapsedMilliseconds;
                    
                }
            });

            CleanupTestRecords();
            RefreshGrid();
            Log("\nTest Finalizat!");
            Log($"Timp mediu pentru Auto-commit: {autoCommit.Average()} ms");
            Log($"Timp mediu pentru Commit la 100: {batchCommit.Average()} ms");
            Log($"Timp mediu pentru Tranzactie Unică: {singleTx.Average()} ms");
            batchTestBtn.Enabled = true;
        }

        private void CleanupTestRecords()
        {
            using (var conn = new SqlConnection(connectionString))
            {
                conn.Open();
                new SqlCommand("DELETE FROM drivers WHERE name LIKE 'Test%'", conn).ExecuteNonQuery();
            }
        }
    }
}