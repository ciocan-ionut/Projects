using model;
using Serilog;
using System;
using System.Collections.Generic;
using System.Text;

namespace persistence
{
    public class ParticipantsDBRepository : IParticipantRepository
    {
        private readonly DBUtils _dbUtils;
        private readonly ILogger _logger = Log.ForContext<ParticipantsDBRepository>();

        public ParticipantsDBRepository(DBUtils dbUtils)
        {
            _logger.Information("Initializing ParticipantsDBRepository");
            _dbUtils = dbUtils;
        }

        public List<ParticipantDTO> FindParticipantDTOsBySwimmingTestId(int swimmingTestId)
        {
            _logger.Information("Finding participant DTOs for swimming test ID: {SwimmingTestId}", swimmingTestId);
            var dtos = new List<ParticipantDTO>();

            string query = @"SELECT P.*, COUNT(R2.swimmingtest_id) AS test_count 
                             FROM Participants P 
                             INNER JOIN Registrations R1 ON P.id = R1.participant_id 
                             INNER JOIN Registrations R2 ON P.id = R2.participant_id 
                             WHERE R1.swimmingtest_id = @TestId 
                             GROUP BY P.id, P.name, P.age";

            var con = _dbUtils.GetConnection();
            try
            {
                using var stmt = con.CreateCommand();
                stmt.CommandText = query;

                var param = stmt.CreateParameter();
                param.ParameterName = "@TestId";
                param.Value = swimmingTestId;
                stmt.Parameters.Add(param);

                using var result = stmt.ExecuteReader();
                while (result.Read())
                {
                    int id = Convert.ToInt32(result["id"]);
                    string name = result["name"].ToString();
                    int age = Convert.ToInt32(result["age"]);
                    int count = Convert.ToInt32(result["test_count"]);

                    dtos.Add(new ParticipantDTO(id, name, age, count));
                }
            }
            catch (Exception e)
            {
                _logger.Error(e, "Error finding participant DTOs");
            }

            return dtos;
        }

        public void Save(Participant entity)
        {
            _logger.Information("Saving new participant: {ParticipantName}", entity.Name);

            var con = _dbUtils.GetConnection();
            using var transaction = con.BeginTransaction();

            try
            {
                using var insertParticipantCmd = con.CreateCommand();
                insertParticipantCmd.Transaction = transaction;
                insertParticipantCmd.CommandText = "INSERT INTO Participants (name, age) VALUES (@Name, @Age); SELECT last_insert_rowid();";

                var pName = insertParticipantCmd.CreateParameter();
                pName.ParameterName = "@Name";
                pName.Value = entity.Name;
                insertParticipantCmd.Parameters.Add(pName);

                var pAge = insertParticipantCmd.CreateParameter();
                pAge.ParameterName = "@Age";
                pAge.Value = entity.Age;
                insertParticipantCmd.Parameters.Add(pAge);

                entity.Id = Convert.ToInt32(insertParticipantCmd.ExecuteScalar());

                using var insertEnrollmentCmd = con.CreateCommand();
                insertEnrollmentCmd.Transaction = transaction;
                insertEnrollmentCmd.CommandText = "INSERT INTO Registrations (participant_id, swimmingtest_id) VALUES (@PartId, @TestId)";

                var pPartId = insertEnrollmentCmd.CreateParameter();
                pPartId.ParameterName = "@PartId";
                insertEnrollmentCmd.Parameters.Add(pPartId);

                var pTestId = insertEnrollmentCmd.CreateParameter();
                pTestId.ParameterName = "@TestId";
                insertEnrollmentCmd.Parameters.Add(pTestId);

                foreach (var test in entity.Tests)
                {
                    pPartId.Value = entity.Id;
                    pTestId.Value = test.Id;
                    insertEnrollmentCmd.ExecuteNonQuery();
                }

                transaction.Commit();
            }
            catch (Exception e)
            {
                _logger.Error(e, "Error inserting participant or enrollments");
                transaction.Rollback();
            }
        }

        public void Update(Participant entity)
        {
            _logger.Information("Updating enrollments for participant ID: {ParticipantId}", entity.Id);

            var con = _dbUtils.GetConnection();
            using var transaction = con.BeginTransaction();

            try
            {
                using var deleteCmd = con.CreateCommand();
                deleteCmd.Transaction = transaction;
                deleteCmd.CommandText = "DELETE FROM Registrations WHERE participant_id = @PartId";

                var pDelPartId = deleteCmd.CreateParameter();
                pDelPartId.ParameterName = "@PartId";
                pDelPartId.Value = entity.Id;
                deleteCmd.Parameters.Add(pDelPartId);

                deleteCmd.ExecuteNonQuery();

                using var insertCmd = con.CreateCommand();
                insertCmd.Transaction = transaction;
                insertCmd.CommandText = "INSERT INTO Registrations (participant_id, swimmingtest_id) VALUES (@PartId, @TestId)";

                var pPartId = insertCmd.CreateParameter();
                pPartId.ParameterName = "@PartId";
                insertCmd.Parameters.Add(pPartId);

                var pTestId = insertCmd.CreateParameter();
                pTestId.ParameterName = "@TestId";
                insertCmd.Parameters.Add(pTestId);

                foreach (var test in entity.Tests)
                {
                    pPartId.Value = entity.Id;
                    pTestId.Value = test.Id;
                    insertCmd.ExecuteNonQuery();
                }

                transaction.Commit();
            }
            catch (Exception e)
            {
                _logger.Error(e, "Error updating enrollments");
                transaction.Rollback();
            }
        }

        public void Delete(int id) => throw new NotImplementedException();
        public Participant FindById(int id) => throw new NotImplementedException();
        public List<Participant> FindAll() => throw new NotImplementedException();
    }
}
