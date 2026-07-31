using persistence;
using Serilog;
using server;
using services;
using networking;
using System.Configuration;
using System.Net.Sockets;
using System.Reflection;

class StartServer
{
    private static int PORT = 55555;
    private static string HOST = "127.0.0.1";

    private static readonly ILogger _logger = Log.ForContext<StartServer>();
    private static readonly string defaultLogTemplate = "{Timestamp:yyyy-MM-dd HH:mm:ss} [{Level:u4}] {SourceContext} - {Message:lj}{NewLine}{Exception}";
    private static readonly string defaultLogFilePath = "C:\\Proiect MPP\\SharedProjectLog.log";

    static void Main(string[] args)
    {
        string logTemplate = ConfigurationManager.AppSettings["LogTemplate"] ?? defaultLogTemplate;
        string logFilePath = ConfigurationManager.AppSettings["LogFilePath"] ?? defaultLogFilePath;

        Log.Logger = new LoggerConfiguration()
            .MinimumLevel.Verbose()
            .Enrich.FromLogContext()
            .WriteTo.Console(outputTemplate: logTemplate)
            .WriteTo.File(logFilePath,
                outputTemplate: logTemplate,
                rollingInterval: RollingInterval.Infinite,
                shared: true)
            .CreateLogger();

        string? connectionString = ConfigurationManager.ConnectionStrings["projectDB"]?.ConnectionString;
        if (string.IsNullOrEmpty(connectionString))
        {
            _logger.Error("Connection string 'projectDB' not found in configuration.");
            return;
        }
        var dbUtils = new DBUtils(connectionString);


        IOrganizerRepository organizerRepository = new OrganizersDBRepository(dbUtils);
        IParticipantRepository participantRepository = new ParticipantsDBRepository(dbUtils);
        ISwimmingTestRepository swimmingTestRepository = new SwimmingTestsDBRepository(dbUtils);

        IService service = new Service(organizerRepository, swimmingTestRepository, participantRepository);

        try
        {
            SerialChatServer server = new SerialChatServer(HOST, PORT, service);
            server.Start();
        } finally
        {
            dbUtils.CloseConnection();
        }
    }
}
public class SerialChatServer : ConcurrentServer
{
    private IService server;
    private networking.protocol.ClientJSONWorker worker;
    public SerialChatServer(string host, int port, IService server) : base(host, port)
    {
        this.server = server;
        Console.WriteLine("SerialChatServer...");
    }
    protected override Thread createWorker(TcpClient client)
    {
        worker = new networking.protocol.ClientJSONWorker(server, client);
        return new Thread(new ThreadStart(worker.run));
    }
}
