using System;
using System.Collections.Generic;
using System.Text;

namespace Service
{
    public interface IService
    {
        void Login(string username, int age, IObserver client);
        void Logout(string username, IObserver client);

        void PerformAction(string username, Domain.GameAction action);
    }
}
