namespace Lab_2
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.formula1DataSet = new Lab_2.Formula1DataSet();
            this.driversBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.driversTableAdapter = new Lab_2.Formula1DataSetTableAdapters.DriversTableAdapter();
            this.iDDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.nameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.salaryDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.contractExpDateDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.teamIDDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.carIDDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.sqlLog = new System.Windows.Forms.RichTextBox();
            this.dirtyReadBtn = new System.Windows.Forms.Button();
            this.nrrBtn = new System.Windows.Forms.Button();
            this.phantomReadBtn = new System.Windows.Forms.Button();
            this.lostUpdateBtn = new System.Windows.Forms.Button();
            this.deadlockBtn = new System.Windows.Forms.Button();
            this.batchTestBtn = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.formula1DataSet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.driversBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.AutoGenerateColumns = false;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.iDDataGridViewTextBoxColumn,
            this.nameDataGridViewTextBoxColumn,
            this.salaryDataGridViewTextBoxColumn,
            this.contractExpDateDataGridViewTextBoxColumn,
            this.teamIDDataGridViewTextBoxColumn,
            this.carIDDataGridViewTextBoxColumn});
            this.dataGridView1.DataSource = this.driversBindingSource;
            this.dataGridView1.Location = new System.Drawing.Point(13, 13);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 51;
            this.dataGridView1.RowTemplate.Height = 24;
            this.dataGridView1.Size = new System.Drawing.Size(554, 259);
            this.dataGridView1.TabIndex = 0;
            // 
            // formula1DataSet
            // 
            this.formula1DataSet.DataSetName = "Formula1DataSet";
            this.formula1DataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // driversBindingSource
            // 
            this.driversBindingSource.DataMember = "Drivers";
            this.driversBindingSource.DataSource = this.formula1DataSet;
            // 
            // driversTableAdapter
            // 
            this.driversTableAdapter.ClearBeforeFill = true;
            // 
            // iDDataGridViewTextBoxColumn
            // 
            this.iDDataGridViewTextBoxColumn.DataPropertyName = "ID";
            this.iDDataGridViewTextBoxColumn.HeaderText = "ID";
            this.iDDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.iDDataGridViewTextBoxColumn.Name = "iDDataGridViewTextBoxColumn";
            this.iDDataGridViewTextBoxColumn.ReadOnly = true;
            this.iDDataGridViewTextBoxColumn.Width = 125;
            // 
            // nameDataGridViewTextBoxColumn
            // 
            this.nameDataGridViewTextBoxColumn.DataPropertyName = "Name";
            this.nameDataGridViewTextBoxColumn.HeaderText = "Name";
            this.nameDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.nameDataGridViewTextBoxColumn.Name = "nameDataGridViewTextBoxColumn";
            this.nameDataGridViewTextBoxColumn.Width = 125;
            // 
            // salaryDataGridViewTextBoxColumn
            // 
            this.salaryDataGridViewTextBoxColumn.DataPropertyName = "Salary";
            this.salaryDataGridViewTextBoxColumn.HeaderText = "Salary";
            this.salaryDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.salaryDataGridViewTextBoxColumn.Name = "salaryDataGridViewTextBoxColumn";
            this.salaryDataGridViewTextBoxColumn.Width = 125;
            // 
            // contractExpDateDataGridViewTextBoxColumn
            // 
            this.contractExpDateDataGridViewTextBoxColumn.DataPropertyName = "ContractExpDate";
            this.contractExpDateDataGridViewTextBoxColumn.HeaderText = "ContractExpDate";
            this.contractExpDateDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.contractExpDateDataGridViewTextBoxColumn.Name = "contractExpDateDataGridViewTextBoxColumn";
            this.contractExpDateDataGridViewTextBoxColumn.Width = 125;
            // 
            // teamIDDataGridViewTextBoxColumn
            // 
            this.teamIDDataGridViewTextBoxColumn.DataPropertyName = "TeamID";
            this.teamIDDataGridViewTextBoxColumn.HeaderText = "TeamID";
            this.teamIDDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.teamIDDataGridViewTextBoxColumn.Name = "teamIDDataGridViewTextBoxColumn";
            this.teamIDDataGridViewTextBoxColumn.Visible = false;
            this.teamIDDataGridViewTextBoxColumn.Width = 125;
            // 
            // carIDDataGridViewTextBoxColumn
            // 
            this.carIDDataGridViewTextBoxColumn.DataPropertyName = "CarID";
            this.carIDDataGridViewTextBoxColumn.HeaderText = "CarID";
            this.carIDDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.carIDDataGridViewTextBoxColumn.Name = "carIDDataGridViewTextBoxColumn";
            this.carIDDataGridViewTextBoxColumn.Visible = false;
            this.carIDDataGridViewTextBoxColumn.Width = 125;
            // 
            // sqlLog
            // 
            this.sqlLog.Location = new System.Drawing.Point(574, 13);
            this.sqlLog.Name = "sqlLog";
            this.sqlLog.Size = new System.Drawing.Size(265, 259);
            this.sqlLog.TabIndex = 1;
            this.sqlLog.Text = "";
            // 
            // dirtyReadBtn
            // 
            this.dirtyReadBtn.AutoSize = true;
            this.dirtyReadBtn.Location = new System.Drawing.Point(13, 279);
            this.dirtyReadBtn.Name = "dirtyReadBtn";
            this.dirtyReadBtn.Size = new System.Drawing.Size(81, 26);
            this.dirtyReadBtn.TabIndex = 2;
            this.dirtyReadBtn.Text = "Dirty Read";
            this.dirtyReadBtn.UseVisualStyleBackColor = true;
            // 
            // nrrBtn
            // 
            this.nrrBtn.AutoSize = true;
            this.nrrBtn.Location = new System.Drawing.Point(100, 279);
            this.nrrBtn.Name = "nrrBtn";
            this.nrrBtn.Size = new System.Drawing.Size(155, 26);
            this.nrrBtn.TabIndex = 3;
            this.nrrBtn.Text = "Non-Repeatable Read";
            this.nrrBtn.UseVisualStyleBackColor = true;
            // 
            // phantomReadBtn
            // 
            this.phantomReadBtn.AutoSize = true;
            this.phantomReadBtn.Location = new System.Drawing.Point(261, 279);
            this.phantomReadBtn.Name = "phantomReadBtn";
            this.phantomReadBtn.Size = new System.Drawing.Size(107, 26);
            this.phantomReadBtn.TabIndex = 4;
            this.phantomReadBtn.Text = "Phantom Read";
            this.phantomReadBtn.UseVisualStyleBackColor = true;
            // 
            // lostUpdateBtn
            // 
            this.lostUpdateBtn.AutoSize = true;
            this.lostUpdateBtn.Location = new System.Drawing.Point(374, 279);
            this.lostUpdateBtn.Name = "lostUpdateBtn";
            this.lostUpdateBtn.Size = new System.Drawing.Size(90, 26);
            this.lostUpdateBtn.TabIndex = 5;
            this.lostUpdateBtn.Text = "Lost Update";
            this.lostUpdateBtn.UseVisualStyleBackColor = true;
            // 
            // deadlockBtn
            // 
            this.deadlockBtn.AutoSize = true;
            this.deadlockBtn.Location = new System.Drawing.Point(470, 279);
            this.deadlockBtn.Name = "deadlockBtn";
            this.deadlockBtn.Size = new System.Drawing.Size(76, 26);
            this.deadlockBtn.TabIndex = 6;
            this.deadlockBtn.Text = "Deadlock";
            this.deadlockBtn.UseVisualStyleBackColor = true;
            // 
            // batchTestBtn
            // 
            this.batchTestBtn.AutoSize = true;
            this.batchTestBtn.Location = new System.Drawing.Point(552, 279);
            this.batchTestBtn.Name = "batchTestBtn";
            this.batchTestBtn.Size = new System.Drawing.Size(81, 26);
            this.batchTestBtn.TabIndex = 7;
            this.batchTestBtn.Text = "Batch Test";
            this.batchTestBtn.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(851, 450);
            this.Controls.Add(this.batchTestBtn);
            this.Controls.Add(this.deadlockBtn);
            this.Controls.Add(this.lostUpdateBtn);
            this.Controls.Add(this.phantomReadBtn);
            this.Controls.Add(this.nrrBtn);
            this.Controls.Add(this.dirtyReadBtn);
            this.Controls.Add(this.sqlLog);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.formula1DataSet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.driversBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private Formula1DataSet formula1DataSet;
        private System.Windows.Forms.BindingSource driversBindingSource;
        private Formula1DataSetTableAdapters.DriversTableAdapter driversTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn iDDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn nameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn salaryDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn contractExpDateDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn teamIDDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn carIDDataGridViewTextBoxColumn;
        private System.Windows.Forms.RichTextBox sqlLog;
        private System.Windows.Forms.Button dirtyReadBtn;
        private System.Windows.Forms.Button nrrBtn;
        private System.Windows.Forms.Button phantomReadBtn;
        private System.Windows.Forms.Button lostUpdateBtn;
        private System.Windows.Forms.Button deadlockBtn;
        private System.Windows.Forms.Button batchTestBtn;
    }
}

