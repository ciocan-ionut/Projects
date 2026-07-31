using System;
using System.Collections.Generic;
using System.Text;

namespace model
{
    public class Participant : Entity<int>
    {
        public string Name { get; }
        public int Age { get; }
        public List<SwimmingTest> Tests { get; set; }
        public Participant(int id, string name, int age) : base(id)
        {
            Name = name;
            Age = age;
            Tests = new List<SwimmingTest>();
        }

        public void AddTest(SwimmingTest test)
        {
            Tests.Add(test);
        }
    }
}
