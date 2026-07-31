using model;
using Serilog;
using System;
using System.Collections.Generic;
using System.Text;

namespace persistence
{
    public class OrganizersDBRepository : IOrganizerRepository
    {
        private readonly DBUtils _dbUtils;
        private readonly ILogger _logger = Log.ForContext<OrganizersDBRepository>();

        public OrganizersDBRepository(DBUtils dbUtils)
        {
            _logger.Information("Initializing OrganizersDBRepository");
            _dbUtils = dbUtils;
        }

        public Organizer FindByUsernameAndPassword(string username, string password)
        {
            _logger.Information("Validating username and password for user: {Username}", username);

            var con = _dbUtils.GetConnection();
            string query = "SELECT id FROM Organizers WHERE username = @User AND password = @Pass";

            try
            {
                using var stmt = con.CreateCommand();
                stmt.CommandText = query;

                var pUser = stmt.CreateParameter();
                pUser.ParameterName = "@User";
                pUser.Value = username;
                stmt.Parameters.Add(pUser);

                var pPass = stmt.CreateParameter();
                pPass.ParameterName = "@Pass";
                pPass.Value = password;
                stmt.Parameters.Add(pPass);

                using var result = stmt.ExecuteReader();
                if (result.Read())
                {
                    int id = result.GetInt32(0);
                    _logger.Information("Credentials valid for user: {Username} with ID: {Id}", username, id);
                    return new Organizer(id, username, password);
                } else
                {
                    _logger.Warning("Invalid credentials for user: {Username}", username);
                    return null;
                }
            }
            catch (Exception e)
            {
                _logger.Error(e, "Database error validating credentials");
                Console.WriteLine("Error DB " + e.Message);
                return null;
            }
        }

        public void Save(Organizer entity) => throw new NotImplementedException();
        public void Delete(int id) => throw new NotImplementedException();
        public void Update(Organizer entity) => throw new NotImplementedException();
        public Organizer FindById(int id) => throw new NotImplementedException();
        public List<Organizer> FindAll() => throw new NotImplementedException();
    }
}
