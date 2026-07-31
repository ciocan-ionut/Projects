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
    public partial class LoginForm : Form
    {
        private readonly IService _serv;

        public LoginForm(IService serv)
        {
            InitializeComponent();
            _serv = serv;
        }

        private void loginBtn_Click(object sender, EventArgs e)
        {
            string username = usernameTxt.Text.Trim();
            int age = (int)ageInput.Value;
            if (string.IsNullOrEmpty(username))
            {
                MessageBox.Show("Introdu un utilizator", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            try
            {
                GameForm gameForm = new GameForm(_serv, username);
                _serv.Login(username, age, gameForm);

                this.Hide();
                gameForm.Show();
            } catch (Exception ex)
            {
                MessageBox.Show("Eroare la conectare: " + ex.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
