using Domain;

namespace Service
{
    // Daca vreau sa adaug mai multe tipuri de notificari, trebe sa schimb si in ResponseType, ServiceProxy, ClientWorker si GameForm
    public interface IObserver
    {
        void InsufficientPlayers(string message);
        void GameStarted(List<string> categories);
        void GameStateUpdated(string message);
        void GameFinished(string finalStandings);
    }
}
