using model;
using services;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace client
{
    public partial class MainPage : Form, IObserver
    {
        private IService srv;
        private string loggedUser;

        BindingList<SwimmingTestDTO> swimmingTests = new BindingList<SwimmingTestDTO>();
        BindingList<ParticipantDTO> participants = new BindingList<ParticipantDTO>();

        public MainPage()
        {
            InitializeComponent();
            InitializeUI();
        }

        public void SetService(IService srv, string username)
        {
            this.srv = srv;
            loggedUser = username;
            LoadSwimmingTestTable();
            LoadSwimmingTestPane();
        }

        private void InitializeUI()
        {
            swimmingTestsTable.AutoGenerateColumns = false;
            swimmingTestsTable.DataSource = swimmingTests;
            swimmingTestsTable.SelectionChanged += SwimmingTestsTable_SelectionChanged;

            participantsTable.AutoGenerateColumns = false;
            participantsTable.DataSource = participants;
            participantsTable.SelectionChanged += ParticipantsTable_SelectionChanged;

            ageSpinner.Minimum = 0;
            ageSpinner.Maximum = 100;

            checkedTests.Format += (s, e) =>
            {
                var test = (SwimmingTestDTO)e.ListItem;
                e.Value = $"{test.Style} {test.Distance}";
            };
        }

        private void SwimmingTestsTable_SelectionChanged(object? sender, EventArgs e)
        {
            if (swimmingTestsTable.CurrentRow != null && swimmingTestsTable.CurrentRow.DataBoundItem is SwimmingTestDTO selectedTest)
            {
                LoadParticipantsTable(selectedTest.Id);
            }
        }

        private void ParticipantsTable_SelectionChanged(object? sender, EventArgs e)
        {
            if (participantsTable.CurrentRow != null && participantsTable.CurrentRow.DataBoundItem is ParticipantDTO selectedParticipant)
            {
                nameField.Text = selectedParticipant.Name;
                ageSpinner.Value = selectedParticipant.Age;

                nameField.Enabled = false;
                ageSpinner.Enabled = false;
                saveBtn.Enabled = false;

                CheckSwimmingTestsForParticipant(selectedParticipant.Id);
            }
        }

        private void LoadSwimmingTestTable()
        {
            try
            {
                List<SwimmingTestDTO> swimmingTestDTOs = srv.GetAllSwimmingTestDTOs();
                swimmingTests.Clear();
                foreach (var dto in swimmingTestDTOs)
                {
                    swimmingTests.Add(dto);
                } 
            } catch (AppException ex) { MessageBox.Show(ex.Message); }
        }

        private void LoadParticipantsTable(int swimmingTestId)
        {
            try
            {
                List<ParticipantDTO> participantDTOs = srv.GetAllParticipantDTOs(swimmingTestId);
                participants.Clear();
                foreach (var dto in participantDTOs)
                {
                    participants.Add(dto);
                }
            } catch (AppException ex) { MessageBox.Show(ex.Message); }
        }

        private void LoadSwimmingTestPane()
        {
            checkedTests.Items.Clear();
            foreach (var swimmingTest in swimmingTests)
            {
                checkedTests.Items.Add(swimmingTest);
            }
        }
        private void CheckSwimmingTestsForParticipant(int participantId)
        {
            try
            {
                List<SwimmingTest> participantTests = srv.GetAllSwimmingTestsForParticipant(participantId);

                for (int i = 0; i < checkedTests.Items.Count; i++)
                {
                    var swimmingTest = (SwimmingTestDTO)checkedTests.Items[i];
                    bool isSelected = participantTests.Any(st => st.Id == swimmingTest.Id);
                    checkedTests.SetItemChecked(i, isSelected);
                } 
            } catch (AppException ex) { MessageBox.Show(ex.Message); }
        }

        private void clearBtn_Click(object sender, EventArgs e)
        {
            participantsTable.ClearSelection();

            nameField.Clear();
            ageSpinner.Value = 0;

            nameField.Enabled = true;
            ageSpinner.Enabled = true;
            saveBtn.Enabled = true;

            CheckSwimmingTestsForParticipant(0);
        }

        private void editBtn_Click(object sender, EventArgs e)
        {
            if (participantsTable.CurrentRow != null && participantsTable.CurrentRow.DataBoundItem is ParticipantDTO selectedParticipant)
            {
                var selectedSwimmingTests = checkedTests.CheckedItems
                    .Cast<SwimmingTestDTO>()
                    .Select(dto => new SwimmingTest(dto.Id, dto.Distance, dto.Style))
                    .ToList();

                try
                {
                    srv.UpdateParticipant(selectedParticipant, selectedSwimmingTests);
                } catch (AppException ex) 
                { 
                    MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error); 
                }
            }
            else
            {
                MessageBox.Show("No participant selected!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void saveBtn_Click(object sender, EventArgs e)
        {
            string name = nameField.Text;
            int age = (int)ageSpinner.Value;

            var selectedSwimmingTests = checkedTests.CheckedItems
                .Cast<SwimmingTestDTO>()
                .Select(dto => new SwimmingTest(dto.Id, dto.Distance, dto.Style))
                .ToList();

            if (string.IsNullOrEmpty(name) || age < 11 || age > 100 || selectedSwimmingTests.Count == 0)
            {
                MessageBox.Show("Invalid input!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            try
            {
                srv.AddParticipant(name, age, selectedSwimmingTests);
                clearBtn_Click(null, null);
            } catch (AppException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void RefreshTables()
        {
            SwimmingTestDTO selectedSwimmingTest = null;
            if (swimmingTestsTable.CurrentRow != null)
            {
                selectedSwimmingTest = swimmingTestsTable.CurrentRow.DataBoundItem as SwimmingTestDTO;
            }

            LoadSwimmingTestTable();

            if (selectedSwimmingTest != null)
            {
                foreach (DataGridViewRow row in swimmingTestsTable.Rows)
                {
                    var test = (SwimmingTestDTO)row.DataBoundItem;
                    if (test.Id == selectedSwimmingTest.Id)
                    {
                        row.Selected = true;
                        swimmingTestsTable.CurrentCell = row.Cells[0];
                        LoadParticipantsTable(test.Id);
                        break;
                    }
                }
            }
            else
            {
                participants.Clear();
            }
        }

        private void logoutBtn_Click(object sender, EventArgs e)
        {
            try
            {
                srv.Logout(loggedUser, this);
                Application.ExitThread();
            } catch (AppException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void Update()
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new Action(Update));
                return;
            }
            RefreshTables();
        }

        private void MainPage_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                srv.Logout(loggedUser, this);
            }
            catch (AppException ex)
            {
                Console.WriteLine(ex.Message);
            }
            Application.ExitThread();
        }
    }
}
