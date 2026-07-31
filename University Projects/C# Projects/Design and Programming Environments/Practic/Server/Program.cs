using log4net;
using Microsoft.Extensions.Configuration;
using Network;
using Persistence;
using System.Net.Sockets;

namespace Server
{
    class Program
    {
        private readonly static string _defaultConnectionString = "Data Source=app.db";
        private readonly static int _defaultPort = 55555;

        private static readonly ILog _logger = LogManager.GetLogger("Server");

        static void Main(string[] args)
        {
            log4net.Config.XmlConfigurator.Configure(new FileInfo("log4net.config"));
            _logger.Info("Start server...");

            var config = Build();
            var connectionString = config.GetConnectionString("DefaultConnection") ?? _defaultConnectionString;
            var dbContext = new Persistence.AppDbContext(connectionString);
            var userRepo = new Persistence.UserRepository(dbContext);
            var categoryRepo = new Persistence.CategoryRepository(dbContext);

            var players = config.GetSection("ServerConfig")["Players"];
            var playersPerGame = int.Parse(players);

            Service.IService service = new Service.Service(userRepo, categoryRepo, playersPerGame);

            int port = int.TryParse(config.GetSection("ServerConfig")["Port"], out int p) ? p : _defaultPort;
            TcpListener listener = new TcpListener(System.Net.IPAddress.Any, port);
            listener.Start();
            _logger.Info($"Server-ul asculta pe portul {port}...");

            try
            {
                while (true)
                {
                    TcpClient client = listener.AcceptTcpClient();
                    _logger.Info("Client nou conectat");

                    ClientWorker worker = new ClientWorker(service, client);
                    Thread thread = new Thread(worker.Run);
                    thread.Start();
                }
            } catch (Exception ex)
            {
                _logger.Error("Eroare server: " + ex.Message);
            }
            finally
            {
                listener.Stop();
            }
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