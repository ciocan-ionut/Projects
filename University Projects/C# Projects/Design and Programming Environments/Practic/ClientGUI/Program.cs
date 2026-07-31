using System;
using System.IO;
using Microsoft.Extensions.Configuration;
using Network;
using Service;

namespace ClientGUI
{
    internal static class Program
    {
        private readonly static string _defaultHost = "localhost";
        private readonly static int _defaultPort = 55555;

        [STAThread]
        static void Main()
        {
            ApplicationConfiguration.Initialize();

            var config = Build();

            string host = config.GetSection("ServerConfig")["Host"] ?? _defaultHost;
            int port = int.TryParse(config.GetSection("ServerConfig")["Port"], out int p) ? p : _defaultPort;

            IService serv = new ServiceProxy(host, port);
            Application.Run(new LoginForm(serv));
        }

        static IConfigurationRoot Build()
        {
            var builder = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory())
                .AddJsonFile("appsettings.json", optional: false, reloadOnChange: true);

            return builder.Build();
        }
    }
}