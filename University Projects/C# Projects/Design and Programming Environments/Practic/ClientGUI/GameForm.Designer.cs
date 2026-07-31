namespace ClientGUI
{
    partial class GameForm
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
            waitLbl = new Label();
            categoryLbl = new Label();
            SuspendLayout();
            // 
            // waitLbl
            // 
            waitLbl.AutoSize = true;
            waitLbl.Location = new Point(157, 199);
            waitLbl.Name = "waitLbl";
            waitLbl.Size = new Size(38, 15);
            waitLbl.TabIndex = 0;
            waitLbl.Text = "label1";
            // 
            // categoryLbl
            // 
            categoryLbl.AutoSize = true;
            categoryLbl.Location = new Point(157, 9);
            categoryLbl.Name = "categoryLbl";
            categoryLbl.Size = new Size(38, 15);
            categoryLbl.TabIndex = 1;
            categoryLbl.Text = "label1";
            // 
            // GameForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(371, 450);
            Controls.Add(categoryLbl);
            Controls.Add(waitLbl);
            Name = "GameForm";
            Text = "GameForm";
            FormClosed += GameForm_FormClosed;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label waitLbl;
        private Label categoryLbl;
    }
}