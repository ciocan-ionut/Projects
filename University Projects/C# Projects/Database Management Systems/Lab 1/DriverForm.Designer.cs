namespace Formula_1_SGBD
{
    partial class DriverForm
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
            this.driverFormLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.nameTextBox = new System.Windows.Forms.MaskedTextBox();
            this.salaryUpDown = new System.Windows.Forms.NumericUpDown();
            this.contractLbl = new System.Windows.Forms.Label();
            this.nameLbl = new System.Windows.Forms.Label();
            this.salaryLbl = new System.Windows.Forms.Label();
            this.saveBtn = new System.Windows.Forms.Button();
            this.cancelBtn = new System.Windows.Forms.Button();
            this.contractExpDatePicker = new System.Windows.Forms.DateTimePicker();
            this.driverFormLayoutPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.salaryUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // driverFormLayoutPanel
            // 
            this.driverFormLayoutPanel.ColumnCount = 2;
            this.driverFormLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.driverFormLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.driverFormLayoutPanel.Controls.Add(this.nameTextBox, 1, 0);
            this.driverFormLayoutPanel.Controls.Add(this.salaryUpDown, 1, 1);
            this.driverFormLayoutPanel.Controls.Add(this.contractLbl, 0, 2);
            this.driverFormLayoutPanel.Controls.Add(this.nameLbl, 0, 0);
            this.driverFormLayoutPanel.Controls.Add(this.salaryLbl, 0, 1);
            this.driverFormLayoutPanel.Controls.Add(this.saveBtn, 1, 3);
            this.driverFormLayoutPanel.Controls.Add(this.cancelBtn, 0, 3);
            this.driverFormLayoutPanel.Controls.Add(this.contractExpDatePicker, 1, 2);
            this.driverFormLayoutPanel.Location = new System.Drawing.Point(12, 12);
            this.driverFormLayoutPanel.Name = "driverFormLayoutPanel";
            this.driverFormLayoutPanel.RowCount = 4;
            this.driverFormLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.driverFormLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.driverFormLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.driverFormLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.driverFormLayoutPanel.Size = new System.Drawing.Size(392, 127);
            this.driverFormLayoutPanel.TabIndex = 0;
            // 
            // nameTextBox
            // 
            this.nameTextBox.Location = new System.Drawing.Point(140, 3);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.Size = new System.Drawing.Size(147, 22);
            this.nameTextBox.TabIndex = 2;
            // 
            // salaryUpDown
            // 
            this.salaryUpDown.Increment = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.salaryUpDown.Location = new System.Drawing.Point(140, 31);
            this.salaryUpDown.Maximum = new decimal(new int[] {
            100000000,
            0,
            0,
            0});
            this.salaryUpDown.Name = "salaryUpDown";
            this.salaryUpDown.Size = new System.Drawing.Size(120, 22);
            this.salaryUpDown.TabIndex = 3;
            this.salaryUpDown.ThousandsSeparator = true;
            // 
            // contractLbl
            // 
            this.contractLbl.AutoSize = true;
            this.contractLbl.Location = new System.Drawing.Point(3, 56);
            this.contractLbl.Name = "contractLbl";
            this.contractLbl.Size = new System.Drawing.Size(131, 16);
            this.contractLbl.TabIndex = 4;
            this.contractLbl.Text = "Contract Expiry Date:";
            // 
            // nameLbl
            // 
            this.nameLbl.AutoSize = true;
            this.nameLbl.Location = new System.Drawing.Point(3, 0);
            this.nameLbl.Name = "nameLbl";
            this.nameLbl.Size = new System.Drawing.Size(47, 16);
            this.nameLbl.TabIndex = 0;
            this.nameLbl.Text = "Name:";
            // 
            // salaryLbl
            // 
            this.salaryLbl.AutoSize = true;
            this.salaryLbl.Location = new System.Drawing.Point(3, 28);
            this.salaryLbl.Name = "salaryLbl";
            this.salaryLbl.Size = new System.Drawing.Size(49, 16);
            this.salaryLbl.TabIndex = 1;
            this.salaryLbl.Text = "Salary:";
            // 
            // saveBtn
            // 
            this.saveBtn.Location = new System.Drawing.Point(140, 87);
            this.saveBtn.Name = "saveBtn";
            this.saveBtn.Size = new System.Drawing.Size(75, 29);
            this.saveBtn.TabIndex = 6;
            this.saveBtn.Text = "Salveaza";
            this.saveBtn.UseVisualStyleBackColor = true;
            this.saveBtn.Click += new System.EventHandler(this.saveBtn_Click);
            // 
            // cancelBtn
            // 
            this.cancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelBtn.Location = new System.Drawing.Point(3, 87);
            this.cancelBtn.Name = "cancelBtn";
            this.cancelBtn.Size = new System.Drawing.Size(75, 29);
            this.cancelBtn.TabIndex = 7;
            this.cancelBtn.Text = "Anuleaza";
            this.cancelBtn.UseVisualStyleBackColor = true;
            this.cancelBtn.Click += new System.EventHandler(this.cancelBtn_Click);
            // 
            // contractExpDatePicker
            // 
            this.contractExpDatePicker.Location = new System.Drawing.Point(140, 59);
            this.contractExpDatePicker.Name = "contractExpDatePicker";
            this.contractExpDatePicker.Size = new System.Drawing.Size(241, 22);
            this.contractExpDatePicker.TabIndex = 8;
            // 
            // DriverForm
            // 
            this.AcceptButton = this.saveBtn;
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelBtn;
            this.ClientSize = new System.Drawing.Size(420, 159);
            this.Controls.Add(this.driverFormLayoutPanel);
            this.Name = "DriverForm";
            this.Text = "DriverForm";
            this.Load += new System.EventHandler(this.DriverForm_Load);
            this.driverFormLayoutPanel.ResumeLayout(false);
            this.driverFormLayoutPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.salaryUpDown)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel driverFormLayoutPanel;
        private System.Windows.Forms.Label nameLbl;
        private System.Windows.Forms.Label salaryLbl;
        private System.Windows.Forms.MaskedTextBox nameTextBox;
        private System.Windows.Forms.NumericUpDown salaryUpDown;
        private System.Windows.Forms.Label contractLbl;
        private System.Windows.Forms.Button saveBtn;
        private System.Windows.Forms.Button cancelBtn;
        private System.Windows.Forms.DateTimePicker contractExpDatePicker;
    }
}