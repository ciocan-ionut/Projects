using Microsoft.Data.Sqlite;
using Serilog;
using System.Configuration;
using System;
using System.Collections.Generic;
using System.Data;
using System.Text;

namespace persistence
{
    public class DBUtils
    {
        private readonly string _connectionString;
        private IDbConnection _instance;
        private readonly ILogger _logger = Log.ForContext<DBUtils>();

        public DBUtils(string connectionString)
        {
            _connectionString = connectionString;
        }

        private IDbConnection CreateNewConnection()
        {
            _logger.Verbose("Entering CreateNewConnection");
            _logger.Information("Trying to connect to database...: {Url}", _connectionString);

            IDbConnection connection = null;
            try
            {
                connection = new SqliteConnection(_connectionString);
                connection.Open();
            }
            catch (Exception e)
            {
                _logger.Error(e, "Error getting connection");
                Console.WriteLine("Error getting connection " + e.Message);
            }
            return connection;
        }

        public IDbConnection GetConnection()
        {
            _logger.Verbose("Entering GetConnection");
            try
            {
                if (_instance == null || _instance.State == ConnectionState.Closed)
                {
                    _instance = CreateNewConnection();
                }
            }
            catch (Exception e)
            {
                _logger.Error(e, "Error DB");
                Console.WriteLine("Error DB " + e.Message);
            }

            _logger.Verbose("Exiting GetConnection");
            return _instance;
        }

        public void CloseConnection()
        {
            _logger.Verbose("Entering CloseConnection");
            if (_instance != null && _instance.State != ConnectionState.Closed)
            {
                try
                {
                    _instance.Close();
                    _logger.Information("Database connection closed successfully.");
                }
                catch (Exception e)
                {
                    _logger.Error(e, "Error closing database connection");
                    Console.WriteLine("Error closing connection " + e.Message);
                }
            }
        }
    }
}
