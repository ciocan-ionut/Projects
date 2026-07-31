using System;
using System.Collections.Generic;
using System.Text;

namespace model
{
    public class ParticipantDTO
    {
        public int Id { get; }
        public string Name { get; }
        public int Age { get; }
        public int SwimmingTestCount { get; }

        public ParticipantDTO(int id, string name, int age, int swimmingTestCount)
        {
            Id = id;
            Name = name;
            Age = age;
            SwimmingTestCount = swimmingTestCount;
        }
    }
}
