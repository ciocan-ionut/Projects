using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using services;

namespace client
{
    public partial class LoginPage : Form
    {
        private IService srv;

        public LoginPage(IService service)
        {
            InitializeComponent();
            srv = service;
        }

        private void loginBtn_Click(object sender, EventArgs e)
        {
            string username = usernameBox.Text;
            string password = passwordBox.Text;

            try
            {
                MainPage mainPage = new MainPage();
                srv.Login(username, password, mainPage);
                mainPage.SetService(srv, username);
                mainPage.Show();
                this.Hide();
                ClearFields();
            } catch (AppException ex)
            {
                MessageBox.Show(ex.Message, "Login Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ClearFields()
        {
            usernameBox.Clear();
            passwordBox.Clear();
        }
    }
}
