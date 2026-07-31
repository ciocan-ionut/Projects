namespace Formula_1_SGBD
{
    partial class DashboardForm
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
            this.dataGridViewTeams = new System.Windows.Forms.DataGridView();
            this.dataGridViewDrivers = new System.Windows.Forms.DataGridView();
            this.addBtn = new System.Windows.Forms.Button();
            this.editBtn = new System.Windows.Forms.Button();
            this.deleteBtn = new System.Windows.Forms.Button();
            this.runTestBtn = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTeams)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewDrivers)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewTeams
            // 
            this.dataGridViewTeams.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewTeams.Location = new System.Drawing.Point(12, 12);
            this.dataGridViewTeams.Name = "dataGridViewTeams";
            this.dataGridViewTeams.RowHeadersWidth = 51;
            this.dataGridViewTeams.RowTemplate.Height = 24;
            this.dataGridViewTeams.Size = new System.Drawing.Size(553, 267);
            this.dataGridViewTeams.TabIndex = 0;
            this.dataGridViewTeams.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewTeams_CellClick);
            // 
            // dataGridViewDrivers
            // 
            this.dataGridViewDrivers.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewDrivers.Location = new System.Drawing.Point(613, 12);
            this.dataGridViewDrivers.Name = "dataGridViewDrivers";
            this.dataGridViewDrivers.RowHeadersWidth = 51;
            this.dataGridViewDrivers.RowTemplate.Height = 24;
            this.dataGridViewDrivers.Size = new System.Drawing.Size(553, 267);
            this.dataGridViewDrivers.TabIndex = 1;
            this.dataGridViewDrivers.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewDrivers_CellClick);
            // 
            // addBtn
            // 
            this.addBtn.Location = new System.Drawing.Point(613, 294);
            this.addBtn.Name = "addBtn";
            this.addBtn.Size = new System.Drawing.Size(75, 27);
            this.addBtn.TabIndex = 2;
            this.addBtn.Text = "Adauga";
            this.addBtn.UseVisualStyleBackColor = true;
            this.addBtn.Click += new System.EventHandler(this.addBtn_Click);
            // 
            // editBtn
            // 
            this.editBtn.Location = new System.Drawing.Point(694, 294);
            this.editBtn.Name = "editBtn";
            this.editBtn.Size = new System.Drawing.Size(75, 27);
            this.editBtn.TabIndex = 3;
            this.editBtn.Text = "Editeaza";
            this.editBtn.UseVisualStyleBackColor = true;
            this.editBtn.Click += new System.EventHandler(this.editBtn_Click);
            // 
            // deleteBtn
            // 
            this.deleteBtn.Location = new System.Drawing.Point(775, 294);
            this.deleteBtn.Name = "deleteBtn";
            this.deleteBtn.Size = new System.Drawing.Size(75, 27);
            this.deleteBtn.TabIndex = 4;
            this.deleteBtn.Text = "Sterge";
            this.deleteBtn.UseVisualStyleBackColor = true;
            this.deleteBtn.Click += new System.EventHandler(this.deleteBtn_Click);
            // 
            // runTestBtn
            // 
            this.runTestBtn.Location = new System.Drawing.Point(1091, 294);
            this.runTestBtn.Name = "runTestBtn";
            this.runTestBtn.Size = new System.Drawing.Size(75, 27);
            this.runTestBtn.TabIndex = 5;
            this.runTestBtn.Text = "Testeaza";
            this.runTestBtn.UseVisualStyleBackColor = true;
            this.runTestBtn.Click += new System.EventHandler(this.runTestBtn_Click);
            // 
            // DashboardForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(1186, 493);
            this.Controls.Add(this.runTestBtn);
            this.Controls.Add(this.deleteBtn);
            this.Controls.Add(this.editBtn);
            this.Controls.Add(this.addBtn);
            this.Controls.Add(this.dataGridViewDrivers);
            this.Controls.Add(this.dataGridViewTeams);
            this.Name = "DashboardForm";
            this.Text = "SGBD";
            this.Load += new System.EventHandler(this.Dashboard_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTeams)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewDrivers)).EndInit();
            this.ResumeLayout(false);

        }

        private void EditBtn_Click(object sender, System.EventArgs e)
        {
            throw new System.NotImplementedException();
        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewTeams;
        private System.Windows.Forms.DataGridView dataGridViewDrivers;
        private System.Windows.Forms.Button addBtn;
        private System.Windows.Forms.Button editBtn;
        private System.Windows.Forms.Button deleteBtn;
        private System.Windows.Forms.Button runTestBtn;
    }
}

