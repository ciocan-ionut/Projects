using model;
using Serilog;
using System;
using System.Collections.Generic;
using System.Text;

namespace persistence
{
    public class SwimmingTestsDBRepository : ISwimmingTestRepository
    {
        private readonly DBUtils _dbUtils;
        private readonly ILogger _logger = Log.ForContext<SwimmingTestsDBRepository>();

        public SwimmingTestsDBRepository(DBUtils dbUtils)
        {
            _logger.Information("Initializing SwimmingTestsDBRepository");
            _dbUtils = dbUtils;
        }

        public List<SwimmingTest> FindSwimmingTestsByParticipantId(int participantId)
        {
            _logger.Information("Finding swimming tests for participant with ID: {ParticipantId}", participantId);
            var swimmingTests = new List<SwimmingTest>();

            var con = _dbUtils.GetConnection();
            string query = @"SELECT S.* FROM SwimmingTests S 
                             JOIN Registrations R ON S.id = R.swimmingtest_id 
                             WHERE R.participant_id = @PartId";

            try
            {
                using var stmt = con.CreateCommand();
                stmt.CommandText = query;

                var param = stmt.CreateParameter();
                param.ParameterName = "@PartId";
                param.Value = participantId;
                stmt.Parameters.Add(param);

                using var result = stmt.ExecuteReader();
                while (result.Read())
                {
                    var test = new SwimmingTest(
                        Convert.ToInt32(result["id"]),
                        Convert.ToInt32(result["distance"]),
                        result["style"].ToString()
                    );
                    swimmingTests.Add(test);
                }
            }
            catch (Exception e)
            {
                _logger.Error(e, "Error finding tests by participant");
            }
            return swimmingTests;
        }

        public List<SwimmingTestDTO> FindAllDTOs()
        {
            _logger.Information("Finding all swimming test DTOs");
            var dtos = new List<SwimmingTestDTO>();
            var con = _dbUtils.GetConnection();
            string query = @"SELECT S.id, S.distance, S.style, COUNT(R.participant_id) AS participant_count
                             FROM SwimmingTests S
                             LEFT JOIN Registrations R ON S.id = R.swimmingtest_id
                             GROUP BY S.id";
            try
            {
                using var stmt = con.CreateCommand();
                stmt.CommandText = query;
                using var result = stmt.ExecuteReader();
                while (result.Read())
                {
                    var dto = new SwimmingTestDTO(
                        Convert.ToInt32(result["id"]),
                        Convert.ToInt32(result["distance"]),
                        Convert.ToString(result["style"]),
                        Convert.ToInt32(result["participant_count"])
                    );
                    dtos.Add(dto);
                }
            }
            catch (Exception e)
            {
                _logger.Error(e, "Error finding all DTOs");
            }
            return dtos;

        }

        public List<SwimmingTest> FindAll() => throw new NotImplementedException();

        public void Save(SwimmingTest entity) => throw new NotImplementedException();
        public void Delete(int id) => throw new NotImplementedException();
        public void Update(SwimmingTest entity) => throw new NotImplementedException();
        public SwimmingTest FindById(int id) => throw new NotImplementedException();
    }
}
