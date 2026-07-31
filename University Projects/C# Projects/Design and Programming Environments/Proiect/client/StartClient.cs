using services;
using networking;

namespace client
{
    internal static class StartClient
    {
        private static readonly int PORT = 55555;
        private static readonly string HOST = "127.0.0.1";

        [STAThread]
        static void Main()
        {
            // IService service = new networking.protocol.ServicesJSONProxy(HOST, PORT);
            IService service = new ProtoProxy(HOST, PORT);

            ApplicationConfiguration.Initialize();
            Application.Run(new LoginPage(service));
        }
    }
}