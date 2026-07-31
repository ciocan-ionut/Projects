namespace client
{
    partial class MainPage
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
            swimmingTestsTable = new DataGridView();
            Distance = new DataGridViewTextBoxColumn();
            Style = new DataGridViewTextBoxColumn();
            ParticipantsCount = new DataGridViewTextBoxColumn();
            participantsTable = new DataGridView();
            NameColumn = new DataGridViewTextBoxColumn();
            Age = new DataGridViewTextBoxColumn();
            SwimmingTestsCount = new DataGridViewTextBoxColumn();
            tableLayoutPanel1 = new TableLayoutPanel();
            nameField = new TextBox();
            label1 = new Label();
            ageSpinner = new NumericUpDown();
            label2 = new Label();
            checkedTests = new CheckedListBox();
            clearBtn = new Button();
            editBtn = new Button();
            saveBtn = new Button();
            logoutBtn = new Button();
            ((System.ComponentModel.ISupportInitialize)swimmingTestsTable).BeginInit();
            ((System.ComponentModel.ISupportInitialize)participantsTable).BeginInit();
            tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)ageSpinner).BeginInit();
            SuspendLayout();
            // 
            // swimmingTestsTable
            // 
            swimmingTestsTable.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            swimmingTestsTable.Columns.AddRange(new DataGridViewColumn[] { Distance, Style, ParticipantsCount });
            swimmingTestsTable.Location = new Point(12, 12);
            swimmingTestsTable.Name = "swimmingTestsTable";
            swimmingTestsTable.RowHeadersWidth = 51;
            swimmingTestsTable.Size = new Size(358, 580);
            swimmingTestsTable.TabIndex = 0;
            // 
            // Distance
            // 
            Distance.DataPropertyName = "Distance";
            Distance.HeaderText = "Distanta";
            Distance.MinimumWidth = 6;
            Distance.Name = "Distance";
            Distance.Width = 125;
            // 
            // Style
            // 
            Style.DataPropertyName = "Style";
            Style.HeaderText = "Stil";
            Style.MinimumWidth = 6;
            Style.Name = "Style";
            Style.Width = 80;
            // 
            // ParticipantsCount
            // 
            ParticipantsCount.DataPropertyName = "ParticipantCount";
            ParticipantsCount.HeaderText = "Participanti";
            ParticipantsCount.MinimumWidth = 6;
            ParticipantsCount.Name = "ParticipantsCount";
            ParticipantsCount.Width = 125;
            // 
            // participantsTable
            // 
            participantsTable.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            participantsTable.Columns.AddRange(new DataGridViewColumn[] { NameColumn, Age, SwimmingTestsCount });
            participantsTable.Location = new Point(518, 12);
            participantsTable.Name = "participantsTable";
            participantsTable.RowHeadersWidth = 51;
            participantsTable.Size = new Size(333, 298);
            participantsTable.TabIndex = 1;
            // 
            // NameColumn
            // 
            NameColumn.DataPropertyName = "Name";
            NameColumn.HeaderText = "Nume";
            NameColumn.MinimumWidth = 6;
            NameColumn.Name = "NameColumn";
            NameColumn.Width = 125;
            // 
            // Age
            // 
            Age.DataPropertyName = "Age";
            Age.HeaderText = "Varsta";
            Age.MinimumWidth = 6;
            Age.Name = "Age";
            Age.Width = 80;
            // 
            // SwimmingTestsCount
            // 
            SwimmingTestsCount.DataPropertyName = "SwimmingTestCount";
            SwimmingTestsCount.HeaderText = "Probe";
            SwimmingTestsCount.MinimumWidth = 6;
            SwimmingTestsCount.Name = "SwimmingTestsCount";
            SwimmingTestsCount.Width = 125;
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 2;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 22F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 78F));
            tableLayoutPanel1.Controls.Add(nameField, 1, 0);
            tableLayoutPanel1.Controls.Add(label1, 0, 0);
            tableLayoutPanel1.Controls.Add(ageSpinner, 1, 1);
            tableLayoutPanel1.Controls.Add(label2, 0, 1);
            tableLayoutPanel1.Location = new Point(537, 316);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 2;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel1.Size = new Size(300, 68);
            tableLayoutPanel1.TabIndex = 3;
            // 
            // nameField
            // 
            nameField.Location = new Point(69, 3);
            nameField.Name = "nameField";
            nameField.Size = new Size(228, 27);
            nameField.TabIndex = 0;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(3, 0);
            label1.Name = "label1";
            label1.Size = new Size(49, 20);
            label1.TabIndex = 1;
            label1.Text = "Nume";
            // 
            // ageSpinner
            // 
            ageSpinner.Location = new Point(69, 37);
            ageSpinner.Name = "ageSpinner";
            ageSpinner.Size = new Size(228, 27);
            ageSpinner.TabIndex = 2;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(3, 34);
            label2.Name = "label2";
            label2.Size = new Size(49, 20);
            label2.TabIndex = 3;
            label2.Text = "Varsta";
            // 
            // checkedTests
            // 
            checkedTests.FormattingEnabled = true;
            checkedTests.Location = new Point(540, 390);
            checkedTests.Name = "checkedTests";
            checkedTests.Size = new Size(297, 202);
            checkedTests.TabIndex = 4;
            // 
            // clearBtn
            // 
            clearBtn.Location = new Point(399, 12);
            clearBtn.Name = "clearBtn";
            clearBtn.Size = new Size(94, 29);
            clearBtn.TabIndex = 5;
            clearBtn.Text = "Clear";
            clearBtn.UseVisualStyleBackColor = true;
            clearBtn.Click += clearBtn_Click;
            // 
            // editBtn
            // 
            editBtn.Location = new Point(399, 47);
            editBtn.Name = "editBtn";
            editBtn.Size = new Size(94, 29);
            editBtn.TabIndex = 6;
            editBtn.Text = "Edit";
            editBtn.UseVisualStyleBackColor = true;
            editBtn.Click += editBtn_Click;
            // 
            // saveBtn
            // 
            saveBtn.Location = new Point(399, 82);
            saveBtn.Name = "saveBtn";
            saveBtn.Size = new Size(94, 29);
            saveBtn.TabIndex = 7;
            saveBtn.Text = "Save";
            saveBtn.UseVisualStyleBackColor = true;
            saveBtn.Click += saveBtn_Click;
            // 
            // logoutBtn
            // 
            logoutBtn.Location = new Point(399, 117);
            logoutBtn.Name = "logoutBtn";
            logoutBtn.Size = new Size(94, 29);
            logoutBtn.TabIndex = 8;
            logoutBtn.Text = "Logout";
            logoutBtn.UseVisualStyleBackColor = true;
            logoutBtn.Click += logoutBtn_Click;
            // 
            // MainPage
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(863, 604);
            Controls.Add(logoutBtn);
            Controls.Add(saveBtn);
            Controls.Add(editBtn);
            Controls.Add(clearBtn);
            Controls.Add(checkedTests);
            Controls.Add(tableLayoutPanel1);
            Controls.Add(participantsTable);
            Controls.Add(swimmingTestsTable);
            Name = "MainPage";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Dashboard";
            FormClosing += MainPage_FormClosing;
            ((System.ComponentModel.ISupportInitialize)swimmingTestsTable).EndInit();
            ((System.ComponentModel.ISupportInitialize)participantsTable).EndInit();
            tableLayoutPanel1.ResumeLayout(false);
            tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)ageSpinner).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private DataGridView swimmingTestsTable;
        private DataGridView participantsTable;
        private TableLayoutPanel tableLayoutPanel1;
        private TextBox nameField;
        private Label label1;
        private NumericUpDown ageSpinner;
        private Label label2;
        private CheckedListBox checkedTests;
        private Button clearBtn;
        private Button editBtn;
        private Button saveBtn;
        private Button logoutBtn;
        private DataGridViewTextBoxColumn Distance;
        private DataGridViewTextBoxColumn Style;
        private DataGridViewTextBoxColumn ParticipantsCount;
        private DataGridViewTextBoxColumn NameColumn;
        private DataGridViewTextBoxColumn Age;
        private DataGridViewTextBoxColumn SwimmingTestsCount;
    }
}