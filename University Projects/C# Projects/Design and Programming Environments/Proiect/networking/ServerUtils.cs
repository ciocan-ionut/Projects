using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using Serilog;

namespace networking
{
    public abstract class AbstractServer
    {
        private TcpListener server;
        private String host;
        private int port;

        private readonly ILogger _logger = Log.ForContext<AbstractServer>();
        public AbstractServer(String host, int port)
        {
            this.host = host;
            this.port = port;
        }
        public void Start()
        {
            IPAddress adr = IPAddress.Parse(host);
            IPEndPoint ep = new IPEndPoint(adr, port);
            server = new TcpListener(ep);
            server.Start();
            while (true)
            {
                _logger.Debug("Waiting for clients ...");
                TcpClient client = server.AcceptTcpClient();
                _logger.Debug("Client connected ...");
                processRequest(client);
            }
        }

        public abstract void processRequest(TcpClient client);
    }


    public abstract class ConcurrentServer : AbstractServer
    {

        public ConcurrentServer(string host, int port) : base(host, port)
        { }

        public override void processRequest(TcpClient client)
        {
            Thread t = createWorker(client);
            t.Start();
        }

        protected abstract Thread createWorker(TcpClient client);
    }
}
