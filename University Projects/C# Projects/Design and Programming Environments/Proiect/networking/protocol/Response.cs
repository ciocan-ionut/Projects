using System;
using System.Collections.Generic;
using System.Text;

namespace networking.protocol
{
    public interface Response
    {
    }

    [Serializable]
    public class OkResponse : Response 
    { 
    }

    [Serializable]
    public class ErrorResponse : Response
    {
        public string Message { get; }
        public ErrorResponse(string message)
        {
            Message = message;
        }
    }

    [Serializable]
    public class GetAllSwimmingTestsResponse : Response
    {
        public List<model.SwimmingTestDTO> SwimmingTests { get; }
        public GetAllSwimmingTestsResponse(List<model.SwimmingTestDTO> swimmingTests)
        {
            SwimmingTests = swimmingTests;
        }
    }

    [Serializable]
    public class GetParticipantsResponse : Response
    {
        public List<model.ParticipantDTO> Participants { get; }
        public GetParticipantsResponse(List<model.ParticipantDTO> participants)
        {
            Participants = participants;
        }
    }

    [Serializable]
    public class GetSwimmingTestsForParticipantResponse : Response
    {
        public List<model.SwimmingTest> SwimmingTests { get; }
        public GetSwimmingTestsForParticipantResponse(List<model.SwimmingTest> swimmingTests)
        {
            SwimmingTests = swimmingTests;
        }
    }

    public interface UpdateResponse : Response
    {
    }

    [Serializable]
    public class TableUpdatedResponse : UpdateResponse
    {
    }
}
