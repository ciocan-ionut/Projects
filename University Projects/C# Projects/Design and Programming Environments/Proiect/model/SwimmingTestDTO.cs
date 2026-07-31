using System;
using System.Collections.Generic;
using System.Text;

namespace model
{
    public class SwimmingTestDTO
    {
        public int Id { get; }
        public int Distance { get; }
        public string Style { get; }
        public int ParticipantCount { get; }

        public SwimmingTestDTO(int id, int distance, string style, int participantCount)
        {
            Id = id;
            Distance = distance;
            Style = style;
            ParticipantCount = participantCount;
        }
    }
}
