using System;
using System.Collections.Generic;
using System.Runtime.ConstrainedExecution;
using System.Text;

namespace networking.protocol
{
    public interface Request
    {
    }

    [Serializable]
    public class AddParticipantRequest : Request
    {
        public String Name { get; }
        public int Age { get; }
        public List<model.SwimmingTest> SwimmingTests { get; }
        public AddParticipantRequest(String name, int age, List<model.SwimmingTest> swimmingTests)
        {
            Name = name;
            Age = age;
            SwimmingTests = swimmingTests;
        }
    }

    [Serializable]
    public class GetAllSwimmingTestsRequest : Request { }

    [Serializable]
    public class GetParticipantsRequest : Request
    {
        public int SwimmingTestId { get; }

        public GetParticipantsRequest(int swimmingTestId)
        {
            SwimmingTestId = swimmingTestId;
        }
    }

    [Serializable]
    public class GetSwimmingTestsForParticipantRequest : Request
    {
        public int ParticipantId { get; }

        public GetSwimmingTestsForParticipantRequest(int participantId)
        {
            ParticipantId = participantId;
        }
    }

    [Serializable]
    public class LoginRequest : Request
    {
        public string Username { get; }
        public string Password { get; }

        public LoginRequest(string username, string password)
        {
            Username = username;
            Password = password;
        }
    }

    [Serializable]
    public class LogoutRequest : Request
    {
        public string Username { get; }
        public LogoutRequest(string username)
        {
            Username = username;
        }
    }

    [Serializable]
    public class UpdateParticipantRequest : Request
    {
        public model.ParticipantDTO ParticipantDTO { get; }
        public List<model.SwimmingTest> SwimmingTests { get; }
        public UpdateParticipantRequest(model.ParticipantDTO participantDTO, List<model.SwimmingTest> swimmingTests)
        {
            ParticipantDTO = participantDTO;
            SwimmingTests = swimmingTests;
        }
    }
}
