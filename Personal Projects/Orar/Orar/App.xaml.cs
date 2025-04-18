using System;
using System.IO;
using System.Threading;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace Orar
{
    public partial class App : Application
    {
        static Database database;
        public static Database Database
        {
            get
            {
                if (database == null)
                    database = new Database(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "OrarDatabase.db3"));
                return database;
            }
        }
        public App()
        {
            InitializeComponent();
            MainPage = new AppShell();
        }
        protected override async void OnStart()
        {
            await Database.InitializeDatabase();
            MainPage = new AppShell();
        }

        protected override void OnSleep()
        {
        }

        protected override void OnResume()
        {
        }
    }
}
