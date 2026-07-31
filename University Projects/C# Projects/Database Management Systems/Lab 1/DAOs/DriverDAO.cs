using Formula_1_SGBD.Domain;
using System;
using System.Configuration;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Formula_1_SGBD.DAOs
{
    internal class DriverDAO
    {
        private readonly string _connectionURL;

        public DriverDAO()
        {
            _connectionURL = ConfigurationManager.ConnectionStrings["Formula1DB"].ConnectionString;
        }

        public void SaveDriver(Driver driver)
        {
            string query = "INSERT INTO Drivers (Name, Salary, ContractExpDate, TeamID) VALUES (@Name, @Salary, @ContractExpDate, @TeamID)";
            using (var connection = new SqlConnection(_connectionURL))
            {
                connection.Open();
                using (var cmd = new SqlCommand(query, connection))
                {
                    cmd.Parameters.AddWithValue("@Name", driver.Name);
                    cmd.Parameters.AddWithValue("@Salary", driver.Salary);
                    cmd.Parameters.AddWithValue("@ContractExpDate", driver.ContractExpDate);
                    cmd.Parameters.AddWithValue("@TeamID", driver.TeamID);
                    cmd.ExecuteNonQuery();
                }
            }
        }

        public void UpdateDriver(Driver driver)
        {
            string query = "UPDATE Drivers SET Name = @Name, Salary = @Salary, ContractExpDate = @ContractExpDate WHERE ID = @ID";
            using (var connection = new SqlConnection(_connectionURL))
            {
                connection.Open();
                using (var cmd = new SqlCommand(query, connection))
                {
                    cmd.Parameters.AddWithValue("@ID", driver.ID);
                    cmd.Parameters.AddWithValue("@Name", driver.Name);
                    cmd.Parameters.AddWithValue("@Salary", driver.Salary);
                    cmd.Parameters.AddWithValue("@ContractExpDate", driver.ContractExpDate);
                    cmd.ExecuteNonQuery();
                }
            }
        }

        public void DeleteDriver(int driverID)
        {
            string query = "DELETE FROM Drivers WHERE ID = @ID";
            using (var connection = new SqlConnection(_connectionURL))
            {
                connection.Open();
                using (var cmd = new SqlCommand(query, connection))
                {
                    cmd.Parameters.AddWithValue("@ID", driverID);
                    cmd.ExecuteNonQuery();
                }
            }
        }
    }
}
