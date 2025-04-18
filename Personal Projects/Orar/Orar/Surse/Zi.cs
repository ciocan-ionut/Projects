using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;
using SQLite;
using System.Linq;

namespace Orar
{
    public class Zi
    {
        [PrimaryKey, AutoIncrement]
        public int Id { get; set; }
        public string Nume { get; set; }
        public string Activitate1 { get; set; }
        public string Activitate2 { get; set; }
        public string Activitate3 { get; set; }
        public string Activitate4 { get; set; }
        public string Activitate5 { get; set; }
        public string Activitate6 { get; set; }
    }
}