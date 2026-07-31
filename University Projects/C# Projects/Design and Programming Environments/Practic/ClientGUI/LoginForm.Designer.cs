namespace ClientGUI
{
    partial class LoginForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            loginLbl = new Label();
            usernameLbl = new Label();
            usernameTxt = new TextBox();
            loginBtn = new Button();
            ageInput = new NumericUpDown();
            label1 = new Label();
            ((System.ComponentModel.ISupportInitialize)ageInput).BeginInit();
            SuspendLayout();
            // 
            // loginLbl
            // 
            loginLbl.AutoSize = true;
            loginLbl.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            loginLbl.Location = new Point(96, 7);
            loginLbl.Name = "loginLbl";
            loginLbl.Size = new Size(53, 21);
            loginLbl.TabIndex = 0;
            loginLbl.Text = "Login";
            // 
            // usernameLbl
            // 
            usernameLbl.AutoSize = true;
            usernameLbl.Location = new Point(10, 70);
            usernameLbl.Name = "usernameLbl";
            usernameLbl.Size = new Size(30, 15);
            usernameLbl.TabIndex = 1;
            usernameLbl.Text = "User";
            // 
            // usernameTxt
            // 
            usernameTxt.Location = new Point(49, 68);
            usernameTxt.Margin = new Padding(3, 2, 3, 2);
            usernameTxt.Name = "usernameTxt";
            usernameTxt.Size = new Size(200, 23);
            usernameTxt.TabIndex = 2;
            // 
            // loginBtn
            // 
            loginBtn.Location = new Point(165, 124);
            loginBtn.Margin = new Padding(3, 2, 3, 2);
            loginBtn.Name = "loginBtn";
            loginBtn.Size = new Size(82, 22);
            loginBtn.TabIndex = 3;
            loginBtn.Text = "Conectare";
            loginBtn.UseVisualStyleBackColor = true;
            loginBtn.Click += loginBtn_Click;
            // 
            // ageInput
            // 
            ageInput.Location = new Point(49, 96);
            ageInput.Name = "ageInput";
            ageInput.Size = new Size(198, 23);
            ageInput.TabIndex = 4;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(10, 98);
            label1.Name = "label1";
            label1.Size = new Size(28, 15);
            label1.TabIndex = 5;
            label1.Text = "Age";
            // 
            // LoginForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(259, 175);
            Controls.Add(label1);
            Controls.Add(ageInput);
            Controls.Add(loginBtn);
            Controls.Add(usernameTxt);
            Controls.Add(usernameLbl);
            Controls.Add(loginLbl);
            Margin = new Padding(3, 2, 3, 2);
            Name = "LoginForm";
            Text = "LoginForm";
            ((System.ComponentModel.ISupportInitialize)ageInput).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label loginLbl;
        private Label usernameLbl;
        private TextBox usernameTxt;
        private Button loginBtn;
        private NumericUpDown ageInput;
        private Label label1;
    }
}