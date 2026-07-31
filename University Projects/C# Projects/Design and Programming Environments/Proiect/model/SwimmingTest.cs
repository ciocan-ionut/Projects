using System;
using System.Collections.Generic;
using System.Text;

namespace model
{
    public class SwimmingTest : Entity<int>
    {
        public int Distance { get; }
        public string Style { get; }
        private List<Participant> Participants { get; }

        public SwimmingTest(int id, int distance, string style) : base(id)
        {
            Distance = distance;
            Style = style;
            Participants = new List<Participant>();
        }

        public void AddParticipant(Participant participant)
        {
            Participants.Add(participant);
        }
    }
}
