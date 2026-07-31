using Domain;
using log4net;
using Microsoft.Extensions.DependencyInjection;
using Persistence;
using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

namespace Network
{
    public class ClientWorker : Service.IObserver
    {
        private readonly Service.IService _service;
        private readonly TcpClient _connection;
        private readonly NetworkStream _stream;
        private readonly StreamReader _reader;
        private readonly StreamWriter _writer;
        private volatile bool _connected;

        private static readonly ILog _logger = LogManager.GetLogger(typeof(ClientWorker));

        public ClientWorker(Service.IService service, TcpClient connection)
        {
            _service = service;
            _connection = connection;
            _stream = connection.GetStream();
            _reader = new StreamReader(_stream);
            _writer = new StreamWriter(_stream) { AutoFlush = true };
        }

        public void Run()
        {
            _connected = true;
            while (_connected)
            {
                try
                {
                    var requestLine = _reader.ReadLine();
                    if (string.IsNullOrEmpty(requestLine)) break;

                    var request = JsonSerializer.Deserialize<Request>(requestLine);
                    _logger.Info($"Request primit: {request.Type} de la {request.Username}");
                    var response = HandleRequest(request);

                    if (response != null)
                        SendResponse(response);
                } catch (Exception e)
                {
                    _logger.Error(e);
                    break;
                }
            }
            try 
            { 
                _connection.Close(); 
                _logger.Info("Client deconectat");
            } catch { /* ignore */ }
        }

        private Response HandleRequest(Request request)
        {
            Response response = new Response { Type = ResponseType.Ok };
            try
            {
                switch (request.Type)
                {
                    case RequestType.Login:
                        _service.Login(request.Username, int.Parse(request.Payload), this);
                        break;
                    case RequestType.Logout:
                        _service.Logout(request.Username, this);
                        _connected = false;
                        break;
                    case RequestType.PerformAction:
                        var action = JsonSerializer.Deserialize<GameAction>(request.Payload);
                        _service.PerformAction(request.Username, action);
                        break;
                }
            } catch (Exception e)
            {
                return new Response { Type = ResponseType.Error, Message = e.Message };
            }
            return response;
        }

        private void SendResponse(Response response)
        {
            var responseLine = JsonSerializer.Serialize(response);
            lock (_writer)
            {
                _writer.WriteLine(responseLine);
            }
        }

        public void InsufficientPlayers(string message)
        {
            SendResponse(new Response { Type = ResponseType.InsufficientPlayers, Message = message });
        }

        public void GameStarted(List<string> categories)
        {
            var payload = JsonSerializer.Serialize(categories);
            SendResponse(new Response { Type = ResponseType.GameStarted, Payload = payload });
        }

        public void GameStateUpdated(string message)
        {
            SendResponse(new Response { Type = ResponseType.UpdateGameState, Message = message });
        }

        public void GameFinished(string finalStandings)
        {
            SendResponse(new Response { Type = ResponseType.GameFinished, Payload = finalStandings });
        }
    }
}
