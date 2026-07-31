using System;
using System.Collections.Generic;
using System.Text;

namespace Network
{
    public class Request
    {
        public RequestType Type { get; set; }
        public string Username { get; set; }
        public string Payload { get; set; }
    }
}
