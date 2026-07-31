using Domain;
using Persistence;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Text;

namespace Service
{
    public class Service : IService
    {
        private readonly Persistence.IUserRepository _userRepository;
        private readonly ICategoryRepository _categoryRepository;

        private readonly int _playersPerGame;
        private List<Category> _categories;

        private readonly ConcurrentDictionary<string, IObserver> _loggedClients;

        public Service(Persistence.IUserRepository userRepository, ICategoryRepository categoryRepository, int players)
        {
            _userRepository = userRepository;
            _categoryRepository = categoryRepository;

            _playersPerGame = players;
            _categories = new List<Category>();

            _loggedClients = new ConcurrentDictionary<string, IObserver>();
        }

        public void Login(string username, int age, IObserver client)
        {
            var user = _userRepository.FindByAlias(username);
            if (user == null)
                throw new Exception("Invalid username");
            if (user.Age != age)
                throw new Exception("Invalid age");
            if (!_loggedClients.TryAdd(username, client))
                throw new Exception("User already logged in");

            if (_loggedClients.Count < _playersPerGame)
                client.InsufficientPlayers("Asteptam jucatori...");

            if (_loggedClients.Count == _playersPerGame)
            {
                var game = new Game { Players = _playersPerGame, IsFinished = false, StartTime = DateTime.Now };

                var categories = _categoryRepository.FindRandom(_playersPerGame + 1);
                _categories.Clear();
                _categories.AddRange(categories);
                var categoryNames = _categories.ConvertAll(c => c.Name);
                NotifyStartToClients(categoryNames);
            }
        }

        public void Logout(string username, IObserver client)
        {
            if (!_loggedClients.TryRemove(username, out _))
                throw new Exception("User not logged in");
        }

        public void PerformAction(string username, Domain.GameAction action)
        {
            if (!_loggedClients.ContainsKey(username))
                throw new Exception("User not logged in");

            // Implementare

            NotifyAllClients("");
        }

        private void NotifyStartToClients(List<string> categories)
        {
            foreach (var clientEntry in _loggedClients)
            {
                var client = clientEntry.Value;
                Task.Run(() =>
                {
                    try
                    {
                        client.GameStarted(categories);
                    }
                    catch (Exception)
                    {
                        _loggedClients.TryRemove(clientEntry.Key, out _);
                    }
                });
            }
        }

        private void NotifyAllClients(string message)
        {
            foreach (var clientEntry in _loggedClients)
            {
                var client = clientEntry.Value;
                Task.Run(() =>
                {
                    try
                    {
                        client.GameStateUpdated(message);
                    }
                    catch (Exception)
                    {
                        _loggedClients.TryRemove(clientEntry.Key, out _);
                    }
                });
            }
        }
    }
}
