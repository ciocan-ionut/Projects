using System;
using System.Collections.Generic;
using System.Text;

namespace Network
{
    public enum ResponseType
    {
        Ok,
        Error,
        InsufficientPlayers,
        GameStarted,
        UpdateGameState,
        GameFinished
    }
}
