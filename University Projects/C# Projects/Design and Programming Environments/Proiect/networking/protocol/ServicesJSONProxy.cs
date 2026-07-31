using model;
using Newtonsoft.Json;
using services;
using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;

namespace networking.protocol
{
    public class ServicesJSONProxy : IService
    {
        private readonly string host;
        private readonly int port;
        private IObserver client;

        private TcpClient connection;
        private NetworkStream stream;
        private StreamReader reader;
        private StreamWriter writer;

        private readonly JsonSerializerSettings jsonSettings;

        private Queue<Response> responses;
        private volatile bool finished;
        private EventWaitHandle _waitHandle;

        public ServicesJSONProxy(string host, int port)
        {
            this.host = host;
            this.port = port;
            responses = new Queue<Response>();

            jsonSettings = new JsonSerializerSettings
            {
                TypeNameHandling = TypeNameHandling.All
            };
        }

        public virtual void Login(string username, string password, IObserver client)
        {
            InitializeConnection();
            SendRequest(new LoginRequest(username, password));
            Response response = ReadResponse();

            if (response is OkResponse)
            {
                this.client = client;
                return;
            }
            if (response is ErrorResponse err)
            {
                CloseConnection();
                throw new AppException(err.Message);
            }
        }

        public virtual void Logout(string username, IObserver client)
        {
            SendRequest(new LogoutRequest(username));
            Response response = ReadResponse();
            CloseConnection();

            if (response is ErrorResponse err)
            {
                throw new AppException(err.Message);
            }
        }

        public virtual List<SwimmingTestDTO> GetAllSwimmingTestDTOs()
        {
            SendRequest(new GetAllSwimmingTestsRequest());
            Response response = ReadResponse();

            if (response is ErrorResponse err)
            {
                throw new AppException(err.Message);
            }

            return ((GetAllSwimmingTestsResponse)response).SwimmingTests;
        }

        public virtual List<SwimmingTest> GetAllSwimmingTestsForParticipant(int participantId)
        {
            SendRequest(new GetSwimmingTestsForParticipantRequest(participantId));
            Response response = ReadResponse();

            if (response is ErrorResponse err)
            {
                throw new AppException(err.Message);
            }

            return ((GetSwimmingTestsForParticipantResponse)response).SwimmingTests;
        }

        public virtual List<ParticipantDTO> GetAllParticipantDTOs(int swimmingTestId)
        {
            SendRequest(new GetParticipantsRequest(swimmingTestId));
            Response response = ReadResponse();

            if (response is ErrorResponse err)
            {
                throw new AppException(err.Message);
            }

            return ((GetParticipantsResponse)response).Participants;
        }

        public virtual void AddParticipant(string name, int age, List<SwimmingTest> swimmingTests)
        {
            SendRequest(new AddParticipantRequest(name, age, swimmingTests));
            Response response = ReadResponse();

            if (response is ErrorResponse err)
            {
                throw new AppException(err.Message);
            }
        }

        public virtual void UpdateParticipant(ParticipantDTO participantDTO, List<SwimmingTest> swimmingTests)
        {
            SendRequest(new UpdateParticipantRequest(participantDTO, swimmingTests));
            Response response = ReadResponse();

            if (response is ErrorResponse err)
            {
                throw new AppException(err.Message);
            }
        }

        private void CloseConnection()
        {
            finished = true;
            try
            {
                reader?.Close();
                writer?.Close();
                stream?.Close();
                connection?.Close();
                _waitHandle?.Close();
                client = null;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }

        private void SendRequest(Request request)
        {
            try
            {
                string jsonLine = JsonConvert.SerializeObject(request, jsonSettings);

                lock (writer)
                {
                    writer.WriteLine(jsonLine);
                }
            }
            catch (Exception e)
            {
                throw new AppException("Error sending object: " + e.Message);
            }
        }

        private Response ReadResponse()
        {
            Response response = null;
            try
            {
                _waitHandle.WaitOne();

                lock (responses)
                {
                    response = responses.Dequeue();
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
            return response;
        }

        private void InitializeConnection()
        {
            try
            {
                connection = new TcpClient(host, port);
                stream = connection.GetStream();
                writer = new StreamWriter(stream) { AutoFlush = true };
                reader = new StreamReader(stream);

                finished = false;
                _waitHandle = new AutoResetEvent(false);
                StartReader();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }

        private void StartReader()
        {
            Thread tw = new Thread(run);
            tw.Start();
        }

        private void HandleUpdate(UpdateResponse update)
        {
            if (update is TableUpdatedResponse)
            {
                try
                {
                    client.Update();
                }
                catch (AppException e)
                {
                    Console.WriteLine(e.StackTrace);
                }
            }
        }

        public virtual void run()
        {
            while (!finished)
            {
                try
                {
                    string jsonLine = reader.ReadLine();
                    if (jsonLine == null)
                    {
                        finished = true;
                        break;
                    }
 
                    Response response = JsonConvert.DeserializeObject<Response>(jsonLine, jsonSettings);

                    if (response is UpdateResponse)
                    {
                        HandleUpdate((UpdateResponse)response);
                    }
                    else
                    {
                        lock (responses)
                        {
                            responses.Enqueue(response);
                        }
                        _waitHandle.Set();
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("Reading error " + e.Message);
                }
            }
        }
    }
}
