namespace client
{
    partial class LoginPage
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
            tableLayoutPanel2 = new TableLayoutPanel();
            label2 = new Label();
            label1 = new Label();
            passwordBox = new TextBox();
            usernameBox = new TextBox();
            loginBtn = new Button();
            label3 = new Label();
            tableLayoutPanel2.SuspendLayout();
            SuspendLayout();
            // 
            // tableLayoutPanel2
            // 
            tableLayoutPanel2.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
            tableLayoutPanel2.ColumnCount = 2;
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 32.4F));
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 67.6F));
            tableLayoutPanel2.Controls.Add(label2, 0, 1);
            tableLayoutPanel2.Controls.Add(label1, 0, 0);
            tableLayoutPanel2.Controls.Add(passwordBox, 1, 1);
            tableLayoutPanel2.Controls.Add(usernameBox, 1, 0);
            tableLayoutPanel2.Controls.Add(loginBtn, 1, 2);
            tableLayoutPanel2.Location = new Point(48, 118);
            tableLayoutPanel2.Name = "tableLayoutPanel2";
            tableLayoutPanel2.RowCount = 3;
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Absolute, 40F));
            tableLayoutPanel2.Size = new Size(250, 139);
            tableLayoutPanel2.TabIndex = 0;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(3, 49);
            label2.Name = "label2";
            label2.Size = new Size(70, 20);
            label2.TabIndex = 4;
            label2.Text = "Password";
            label2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(3, 0);
            label1.Name = "label1";
            label1.Size = new Size(75, 20);
            label1.TabIndex = 0;
            label1.Text = "Username";
            // 
            // passwordBox
            // 
            passwordBox.Location = new Point(84, 52);
            passwordBox.Name = "passwordBox";
            passwordBox.PasswordChar = '*';
            passwordBox.Size = new Size(163, 27);
            passwordBox.TabIndex = 2;
            passwordBox.UseSystemPasswordChar = true;
            // 
            // usernameBox
            // 
            usernameBox.Location = new Point(84, 3);
            usernameBox.Name = "usernameBox";
            usernameBox.Size = new Size(163, 27);
            usernameBox.TabIndex = 1;
            // 
            // loginBtn
            // 
            loginBtn.Location = new Point(84, 101);
            loginBtn.Name = "loginBtn";
            loginBtn.Size = new Size(94, 29);
            loginBtn.TabIndex = 3;
            loginBtn.Text = "Login";
            loginBtn.UseVisualStyleBackColor = true;
            loginBtn.Click += loginBtn_Click;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 18F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label3.Location = new Point(132, 9);
            label3.Name = "label3";
            label3.Size = new Size(97, 41);
            label3.TabIndex = 1;
            label3.Text = "Login";
            // 
            // LoginPage
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(353, 450);
            Controls.Add(label3);
            Controls.Add(tableLayoutPanel2);
            Name = "LoginPage";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "LoginPage";
            tableLayoutPanel2.ResumeLayout(false);
            tableLayoutPanel2.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TableLayoutPanel tableLayoutPanel2;
        private Label label1;
        private TextBox passwordBox;
        private TextBox usernameBox;
        private Label label2;
        private Label label3;
        private Button loginBtn;
    }
}