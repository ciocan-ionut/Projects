using System;
using System.Collections.Generic;
using System.Text;

namespace Network
{
    public class Response
    {
        public ResponseType Type { get; set; }
        public string Message { get; set; }
        public string Payload { get; set; }
    }
}
