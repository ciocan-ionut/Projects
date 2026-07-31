using model;
using System;
using System.Collections.Generic;
using System.Text;

namespace services
{
    public interface IService
    {
        void Login(string username, string password, IObserver client);
        void Logout(string username, IObserver client);

        public List<SwimmingTestDTO> GetAllSwimmingTestDTOs();
        public List<SwimmingTest> GetAllSwimmingTestsForParticipant(int participantId);
        public List<ParticipantDTO> GetAllParticipantDTOs(int swimmingTestId);

        public void AddParticipant(String name, int age, List<SwimmingTest> swimmingTests);
        public void UpdateParticipant(ParticipantDTO participantDTO, List<SwimmingTest> swimmingTests);
    }
}
