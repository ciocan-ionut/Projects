using model;
using System;
using System.Collections.Generic;
using System.Text;

namespace persistence
{
    public interface ISwimmingTestRepository : IRepository<int, SwimmingTest>
    {
        List<SwimmingTest> FindSwimmingTestsByParticipantId(int participantId);
        List<SwimmingTestDTO> FindAllDTOs();
    }
}
