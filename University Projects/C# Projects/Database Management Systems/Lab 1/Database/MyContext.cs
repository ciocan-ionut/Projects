using Formula_1_SGBD.Domain;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.Entity;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Formula_1_SGBD.Database
{
    public class MyContext : DbContext
    {
        public DbSet<Team> Teams { get; set; }
        public DbSet<Driver> Drivers { get; set; }

        public MyContext() : base(ConfigurationManager.ConnectionStrings["Formula1DB"].ConnectionString) 
        {
            this.Configuration.ProxyCreationEnabled = true;
            this.Configuration.LazyLoadingEnabled = true;
            this.Database.Log = mesaj => Debug.Write(mesaj);
        }
    }
}
