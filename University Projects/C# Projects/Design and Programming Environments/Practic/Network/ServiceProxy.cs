using log4net;
using Persistence;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Net.Http.Headers;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

namespace Network
{
    public class ServiceProxy : Service.IService
    {
        private readonly string _host;
        private readonly int _port;
        private Service.IObserver _client;
        private TcpClient _connection;
        private NetworkStream _stream;
        private StreamReader _reader;
        private StreamWriter _writer;
        private volatile bool _finished;

        private readonly BlockingCollection<Response> _responses = new BlockingCollection<Response>();

        public ServiceProxy(string host, int port)
        {
            _host = host;
            _port = port;
        }

        private void StartConnection()
        {
            if (_connection != null && _connection.Connected) return;

            _connection = new TcpClient(_host, _port);
            _stream = _connection.GetStream();
            _reader = new StreamReader(_stream);
            _writer = new StreamWriter(_stream) { AutoFlush = true };
            _finished = false;

            Thread listener = new Thread(Run) { IsBackground = true };
            listener.Start();
        }

        private void Run()
        {
            while (!_finished)
            {
                try
                {
                    var responseLine = _reader.ReadLine();
                    if (string.IsNullOrEmpty(responseLine)) continue;

                    var response = JsonSerializer.Deserialize<Response>(responseLine);
                    HandleUpdate(response);
                } catch (Exception e)
                {
                    Console.WriteLine("Conexiune inchisa");
                    break;
                }
            }
        }

        private void HandleUpdate(Response response)
        {
            switch (response.Type)
            {
                case ResponseType.InsufficientPlayers:
                    _client.InsufficientPlayers(response.Message);
                    break;
                case ResponseType.GameStarted:
                    _client.GameStarted(JsonSerializer.Deserialize<List<string>>(response.Payload));
                    break;
                case ResponseType.UpdateGameState:
                    _client.GameStateUpdated(response.Message);
                    break;
                case ResponseType.GameFinished:
                    _client.GameFinished(response.Payload);
                    break;
                default:
                    _responses.Add(response);
                    break;
            }
        }

        private Response SendAndReceive(Request request)
        {
            var requestLine = JsonSerializer.Serialize(request);
            _writer.WriteLine(requestLine);

            Response response = _responses.Take();
            if (response.Type == ResponseType.Error)
            {
                throw new Exception(response.Message);
            }
            return response;
        }

        public void Login(string username, int age, Service.IObserver client)
        {
            StartConnection();
            _client = client;
            SendAndReceive(new Request { Type = RequestType.Login, Username = username, Payload = age.ToString() });
        }

        public void Logout(string username, Service.IObserver client)
        {
            SendAndReceive(new Request { Type = RequestType.Logout, Username = username });
            _finished = true;
            _stream.Close();
            _connection.Close();
            _client = null;
        }

        public void PerformAction(string username, Domain.GameAction action)
        {
            var request = new Request
            {
                Type = RequestType.PerformAction,
                Username = username,
                Payload = JsonSerializer.Serialize(action)
            };
            SendAndReceive(request);
        }
    }
}
