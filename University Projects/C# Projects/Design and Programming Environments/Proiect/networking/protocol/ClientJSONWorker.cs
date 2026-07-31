using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using Newtonsoft.Json;

using services;

namespace networking.protocol
{
    public class ClientJSONWorker : IObserver
    {
        private readonly IService server;
        private readonly TcpClient connection;

        private readonly NetworkStream stream;
        private readonly StreamWriter writer;
        private readonly StreamReader reader;
        private volatile bool connected;

        private readonly JsonSerializerSettings jsonSettings;

        public ClientJSONWorker(IService server, TcpClient connection)
        {
            this.server = server;
            this.connection = connection;

            jsonSettings = new JsonSerializerSettings
            {
                TypeNameHandling = TypeNameHandling.All
            };

            try
            {
                stream = connection.GetStream();
                writer = new StreamWriter(stream) { AutoFlush = true };
                reader = new StreamReader(stream);
                connected = true;
            }
            catch (Exception e)
            {
                Console.WriteLine("Error initializing client worker: " + e.Message);
                Console.WriteLine(e.StackTrace);
            }
        }

        public virtual void run()
        {
            while (connected)
            {
                try
                {
                    string? requestJson = reader.ReadLine();
                    if (requestJson == null)
                    {
                        Console.WriteLine("Client disconnected");
                        connected = false;
                        break;
                    }
                    Request request = JsonConvert.DeserializeObject<Request>(requestJson, jsonSettings);
                    Response response = HandleRequest(request);
                    if (response != null)
                    {
                        SendResponse(response);
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("Error processing client request: " + e.Message);
                    Console.WriteLine(e.StackTrace);
                }
            }
            try
            {
                reader.Close();
                writer.Close();
                stream.Close();
                connection.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine("Error closing client connection: " + e.Message);
                Console.WriteLine(e.StackTrace);
            }
        }

        public void Update()
        {
            try
            {
                SendResponse(new TableUpdatedResponse());
            }
            catch (Exception e)
            {
                throw new AppException("Sending error " + e.Message);
            }
        }

        private Response HandleRequest(Request request)
        {
            if (request is LoginRequest logReq)
            {
                try
                {
                    lock (server)
                    {
                        server.Login(logReq.Username, logReq.Password, this);
                    }
                    return new OkResponse();
                }
                catch (AppException e)
                {
                    connected = false;
                    return new ErrorResponse(e.Message);
                }
            }

            if (request is LogoutRequest logOutReq)
            {
                try
                {
                    lock (server)
                    {
                        server.Logout(logOutReq.Username, this);
                    }
                    connected = false;
                    return new OkResponse();
                }
                catch (AppException e)
                {
                    return new ErrorResponse(e.Message);
                }
            }

            if (request is GetAllSwimmingTestsRequest)
            {
                try
                {
                    return new GetAllSwimmingTestsResponse(server.GetAllSwimmingTestDTOs());
                }
                catch (AppException e)
                {
                    return new ErrorResponse(e.Message);
                }
            }

            if (request is GetSwimmingTestsForParticipantRequest req1)
            {
                try
                {
                    return new GetSwimmingTestsForParticipantResponse(server.GetAllSwimmingTestsForParticipant(req1.ParticipantId));
                }
                catch (AppException e)
                {
                    return new ErrorResponse(e.Message);
                }
            }

            if (request is GetParticipantsRequest req2)
            {
                try
                {
                    return new GetParticipantsResponse(server.GetAllParticipantDTOs(req2.SwimmingTestId));
                }
                catch (AppException e)
                {
                    return new ErrorResponse(e.Message);
                }
            }

            if (request is AddParticipantRequest req3)
            {
                try
                {
                    lock (server)
                    {
                        server.AddParticipant(req3.Name, req3.Age, req3.SwimmingTests);
                    }
                    return new OkResponse();
                }
                catch (AppException e)
                {
                    return new ErrorResponse(e.Message);
                }
            }

            if (request is UpdateParticipantRequest req4)
            {
                try
                {
                    lock (server)
                    {
                        server.UpdateParticipant(req4.ParticipantDTO, req4.SwimmingTests);
                    }
                    return new OkResponse();
                }
                catch (AppException e)
                {
                    return new ErrorResponse(e.Message);
                }
            }

            return null;
        }

        private void SendResponse(Response response)
        {
            string jsonLine = JsonConvert.SerializeObject(response, jsonSettings);
            lock (writer)
            {
                writer.WriteLine(jsonLine);
            }
        }
    }
}
