using Formula_1_SGBD.DAOs;
using Formula_1_SGBD.Domain;
using System;
using System.Configuration;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Formula_1_SGBD
{
    public partial class DriverForm : Form
    {
        private int teamID;
        private Driver initialData;
        private DriverORM driverDAO;
        public DriverForm(int teamID, Driver initialData)
        {
            InitializeComponent();
            this.teamID = teamID;
            this.initialData = initialData;
            driverDAO = new DriverORM();
        }

        private void DriverForm_Load(object sender, EventArgs e)
        {
            if (initialData != null)
            {
                nameTextBox.Text = initialData.Name;
                salaryUpDown.Value = initialData.Salary;
                contractExpDatePicker.Value = initialData.ContractExpDate;
            }
        }

        private void saveBtn_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(nameTextBox.Text) || salaryUpDown.Value == 0 || contractExpDatePicker.Value <= DateTime.Now)
            {
                MessageBox.Show("Please fill in all fields with valid values.");
                return;
            }

            int id = initialData != null ? initialData.ID : 0;
            string name = nameTextBox.Text;
            int salary = (int)salaryUpDown.Value;
            DateTime contractExpDate = contractExpDatePicker.Value;
            Driver driver = new Driver(id, name, salary, contractExpDate, teamID);
            try
            {
                if (initialData != null)
                    driverDAO.UpdateDriver(driver);
                else
                    driverDAO.SaveDriver(driver);
                this.Close();
            } catch (SqlException ex)
            {
                MessageBox.Show("An error occurred while saving the driver: " + ex.Message);
            }
        }

        private void cancelBtn_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
