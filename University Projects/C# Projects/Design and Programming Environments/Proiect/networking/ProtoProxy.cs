using Grpc.Core;
using Grpc.Net.Client;
using Networking.Grpc;
using services;
using System;
using System.Collections.Generic;
using System.Text;

namespace networking
{
    public class ProtoProxy : IService
    {
        private readonly ProtoService.ProtoServiceClient _client;
        private IObserver _clientObserver;
        private CancellationTokenSource _cancellationTokenSource;

        public ProtoProxy(string host, int port)
        {
            var channel = GrpcChannel.ForAddress($"http://{host}:{port}");
            _client = new ProtoService.ProtoServiceClient(channel);
        }

        public void Login(string username, string password, IObserver client)
        {
            try
            {
                _client.Login(new LoginRequest { Username = username, Password = password });

                _clientObserver = client;

                _cancellationTokenSource = new CancellationTokenSource();
                _ = ListenForUpdatesAsync(_cancellationTokenSource.Token);
            }
            catch (RpcException e)
            {
                throw new AppException(e.Status.Detail);
            }
        }

        public void Logout(string username, IObserver client)
        {
            try
            {
                _client.Logout(new LogoutRequest { Username = username });

                _cancellationTokenSource?.Cancel();
                _clientObserver = null;
            }
            catch (RpcException e)
            {
                throw new AppException(e.Status.Detail);
            }
        }

        private async Task ListenForUpdatesAsync(CancellationToken token)
        {
            try
            {
                using var call = _client.SubscribeToUpdates(new EmptyRequest(), cancellationToken: token);

                while (await call.ResponseStream.MoveNext(token))
                {
                    var update = call.ResponseStream.Current;
                    if (update.Message == "TableUpdated")
                    {
                        _clientObserver?.Update();
                    }
                }
            }
            catch (RpcException)
            {
                Console.WriteLine("Conexiunea cu serverul pentru notificări a fost pierdută.");
            }
            catch (OperationCanceledException)
            {
                
            }
        }

        public List<model.SwimmingTestDTO> GetAllSwimmingTestDTOs()
        {
            try
            {
                var response = _client.GetAllSwimmingTests(new EmptyRequest());

                return response.Tests.Select(t => new model.SwimmingTestDTO(
                    t.Id,
                    t.Distance,
                    t.Style,
                    t.ParticipantCount
                )).ToList();
            }
            catch (RpcException e)
            {
                throw new AppException(e.Status.Detail);
            }
        }

        public List<model.SwimmingTest> GetAllSwimmingTestsForParticipant(int participantId)
        {
            try
            {
                var response = _client.GetSwimmingTestsForParticipant(new ParticipantIdRequest { ParticipantId = participantId });
                return response.Tests.Select(t => new model.SwimmingTest(t.Id, t.Distance, t.Style)).ToList();
            }
            catch (RpcException e)
            {
                throw new AppException(e.Status.Detail);
            }
        }

        public List<model.ParticipantDTO> GetAllParticipantDTOs(int swimmingTestId)
        {
            try
            {
                var response = _client.GetParticipants(new SwimmingTestIdRequest { SwimmingTestId = swimmingTestId });
                return response.Participants.Select(p => new model.ParticipantDTO(p.Id, p.Name, p.Age, p.SwimmingTestCount)).ToList();
            }
            catch (RpcException e)
            {
                throw new AppException(e.Status.Detail);
            }
        }

        public void AddParticipant(string name, int age, List<model.SwimmingTest> swimmingTests)
        {
            try
            {
                var request = new AddParticipantRequest
                {
                    Name = name,
                    Age = age
                };

                request.Tests.AddRange(swimmingTests.Select(t => new Networking.Grpc.SwimmingTest
                {
                    Id = t.Id,
                    Style = t.Style,
                    Distance = t.Distance
                }));

                _client.AddParticipant(request);
            }
            catch (RpcException e)
            {
                throw new AppException(e.Status.Detail);
            }
        }

        public void UpdateParticipant(model.ParticipantDTO participantDTO, List<model.SwimmingTest> swimmingTests)
        {
            try
            {
                var request = new UpdateParticipantRequest
                {
                    Participant = new Networking.Grpc.ParticipantDTO
                    {
                        Id = participantDTO.Id,
                        Name = participantDTO.Name,
                        Age = participantDTO.Age
                    }
                };

                request.Tests.AddRange(swimmingTests.Select(t => new Networking.Grpc.SwimmingTest
                {
                    Id = t.Id,
                    Style = t.Style,
                    Distance = t.Distance
                }));

                _client.UpdateParticipant(request);
            }
            catch (RpcException e)
            {
                throw new AppException(e.Status.Detail);
            }
        }
    }
}