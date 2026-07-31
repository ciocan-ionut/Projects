using model;
using persistence;
using Serilog;
using services;
using System;
using System.Collections.Generic;
using System.Text;

namespace server
{
    public class Service : IService
    {
        private IOrganizerRepository organizerRepository;
        private ISwimmingTestRepository swimmingTestRepository;
        private IParticipantRepository participantRepository;

        private readonly IDictionary<string, IObserver> loggedClients;

        private static readonly ILogger _logger = Log.ForContext<Service>();

        public Service(IOrganizerRepository organizerRepo, ISwimmingTestRepository swimmingTestRepo, IParticipantRepository participantRepo)
        {
            organizerRepository = organizerRepo;
            swimmingTestRepository = swimmingTestRepo;
            participantRepository = participantRepo;

            loggedClients = new Dictionary<string, IObserver>();
        }

        public void Login(string username, string password, IObserver client)
        {
            Organizer org = organizerRepository.FindByUsernameAndPassword(username, password);
            if (org != null)
            {
                if (loggedClients.ContainsKey(username))
                {
                    throw new AppException("User already logged in");
                }
                loggedClients[username] = client;
            } else
            {
                throw new AppException("Authentification failed");
            }
        }

        public void Logout(string username, IObserver client)
        {
            bool opResult = loggedClients.Remove(username);
            if (!opResult)
            {
                throw new AppException("User not found");
            }
        }

        public List<SwimmingTestDTO> GetAllSwimmingTestDTOs()
        {
            return swimmingTestRepository.FindAllDTOs();
        }

        public List<SwimmingTest> GetAllSwimmingTestsForParticipant(int participantId)
        {
            return swimmingTestRepository.FindSwimmingTestsByParticipantId(participantId);
        }

        public List<ParticipantDTO> GetAllParticipantDTOs(int swimmingTestId)
        {
            return participantRepository.FindParticipantDTOsBySwimmingTestId(swimmingTestId);
        }

        public void AddParticipant(String name, int age, List<SwimmingTest> swimmingTests)
        {
            Participant participant = new Participant(0, name, age);
            participant.Tests = swimmingTests;
            participantRepository.Save(participant);
            notifyAllLoggedClients();
        }

        public void UpdateParticipant(ParticipantDTO participantDTO, List<SwimmingTest> swimmingTests)
        {
            Participant participant = new Participant(participantDTO.Id, participantDTO.Name, participantDTO.Age);
            participant.Tests = swimmingTests;
            participantRepository.Update(participant);
            notifyAllLoggedClients();
        }

        private void notifyAllLoggedClients()
        {
            _logger.Information("Notifying {Count} clients", loggedClients.Count);
            foreach (var client in loggedClients.Values)
            {
                Task.Run(client.Update);
            }
        }
    }
}
