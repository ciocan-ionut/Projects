using Service;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ClientGUI
{
    public partial class GameForm : Form, IObserver
    {
        private readonly IService _serv;
        private readonly string _username;
        public GameForm(IService serv, string username)
        {
            InitializeComponent();

            _serv = serv;
            _username = username;

            waitLbl.Visible = false;
            categoryLbl.Visible = false;
        }

        private void GameForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                _serv.Logout(_username, this);
            }
            catch { /* ignore */ }
            finally
            {
                Application.Exit();
            }
        }

        public void InsufficientPlayers(string message)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new Action<string>(InsufficientPlayers), message);
                return;
            }

            waitLbl.Visible = true;
            waitLbl.Text = message;
        }

        public void GameStarted(List<string> categories)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new Action<List<string>>(GameStarted), categories);
                return;
            }
            
            waitLbl.Visible = false;
            categoryLbl.Visible = true;
            categoryLbl.Text = "Categorii: " + string.Join(", ", categories);
        }

        public void GameStateUpdated(string message)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new Action<string>(GameStateUpdated), message);
                return;
            }

            // action
        }

        public void GameFinished(string finalStandings)
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new Action<string>(GameFinished), finalStandings);
                return;
            }

            // action
        }
    }
}
