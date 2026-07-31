using model;
using System;
using System.Collections.Generic;
using System.Text;

namespace persistence
{
    public interface IParticipantRepository : IRepository<int, Participant>
    {
        List<ParticipantDTO> FindParticipantDTOsBySwimmingTestId(int swimmingTestId);
    }
}
