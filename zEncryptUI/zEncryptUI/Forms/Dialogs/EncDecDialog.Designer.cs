using System.Resources;
using System.Windows.Forms;

namespace zEntryptUI.Forms.Dialogs
{
    partial class EncDecDialog
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
            components = new System.ComponentModel.Container();
            seedList = new ComboBox();
            idBox = new TextBox();
            passBox = new TextBox();
            idLabel = new Label();
            passLabel = new Label();
            encDecButton = new Button();
            advSettingsButton = new Button();
            cancelEncButton = new Button();
            seedListLable = new Label();
            toolTip = new ToolTip(components);
            manualSeeds = new CheckBox();
            selectSeedfileButton = new Button();
            seedfilePath = new Label();
            SuspendLayout();
            // 
            // seedList
            // 
            seedList.FormattingEnabled = true;
            seedList.Location = new Point(177, 145);
            seedList.Name = "seedList";
            seedList.Size = new Size(251, 23);
            seedList.TabIndex = 0;
            seedList.Visible = false;
            seedList.SelectedIndexChanged += SeedList_SelectedIndexChanged;
            seedList.KeyUp += SeedList_KeyUp;
            seedList.MouseHover += SeedList_MouseHover;
            // 
            // idBox
            // 
            idBox.Location = new Point(211, 24);
            idBox.MaxLength = 20;
            idBox.Name = "idBox";
            idBox.Size = new Size(193, 23);
            idBox.TabIndex = 5;
            idBox.TextChanged += idBox_TextChanged;
            // 
            // passBox
            // 
            passBox.Location = new Point(211, 72);
            passBox.MaxLength = 20;
            passBox.Name = "passBox";
            passBox.PasswordChar = '*';
            passBox.Size = new Size(193, 23);
            passBox.TabIndex = 6;
            passBox.MouseHover += PassBox_MouseHover;
            passBox.TextChanged += passBox_TextChanged;
            // 
            // idLabel
            // 
            idLabel.AutoSize = true;
            idLabel.Location = new Point(41, 27);
            idLabel.Name = "idLabel";
            idLabel.Size = new Size(73, 15);
            idLabel.TabIndex = 7;
            idLabel.Text = "Kullanici Adı";
            // 
            // passLabel
            // 
            passLabel.AutoSize = true;
            passLabel.Location = new Point(41, 72);
            passLabel.Name = "passLabel";
            passLabel.Size = new Size(30, 15);
            passLabel.TabIndex = 8;
            passLabel.Text = "Şifre";
            // 
            // encDecButton
            // 
            encDecButton.Location = new Point(61, 217);
            encDecButton.Name = "encDecButton";
            encDecButton.Size = new Size(112, 32);
            encDecButton.TabIndex = 10;
            encDecButton.UseVisualStyleBackColor = true;
            encDecButton.Enabled = false;
            // 
            // advSettingsButton
            // 
            advSettingsButton.ImageAlign = ContentAlignment.MiddleRight;
            advSettingsButton.Location = new Point(177, 182);
            advSettingsButton.Name = "advSettingsButton";
            advSettingsButton.Size = new Size(99, 29);
            advSettingsButton.TabIndex = 11;
            advSettingsButton.Text = "Gelişmiş Ayarlar";
            advSettingsButton.TextAlign = ContentAlignment.MiddleLeft;
            advSettingsButton.UseVisualStyleBackColor = true;
            advSettingsButton.Click += AdvSettingsButton_Click;
            // 
            // cancelEncButton
            // 
            cancelEncButton.Location = new Point(277, 217);
            cancelEncButton.Name = "cancelEncButton";
            cancelEncButton.Size = new Size(112, 32);
            cancelEncButton.TabIndex = 12;
            cancelEncButton.Text = "İptal";
            cancelEncButton.UseVisualStyleBackColor = true;
            cancelEncButton.Click += CancelEncButton_Click;
            // 
            // seedListLable
            // 
            seedListLable.AutoSize = true;
            seedListLable.Location = new Point(51, 151);
            seedListLable.Name = "seedListLable";
            seedListLable.Size = new Size(67, 15);
            seedListLable.TabIndex = 14;
            seedListLable.Text = "Seed Listesi";
            seedListLable.Visible = false;
            // 
            // manualSeeds
            // 
            manualSeeds.Location = new Point(162, 115);
            manualSeeds.Name = "manualSeeds";
            manualSeeds.Size = new Size(157, 24);
            manualSeeds.TabIndex = 0;
            manualSeeds.Text = "Manuel seed seçimi";
            manualSeeds.Click += ManualSeed_Click;
            // 
            // selectSeedfileButton
            // 
            selectSeedfileButton.ImageAlign = ContentAlignment.MiddleRight;
            selectSeedfileButton.Location = new Point(41, 145);
            selectSeedfileButton.Name = "selectSeedfileButton";
            selectSeedfileButton.Size = new Size(102, 26);
            selectSeedfileButton.TabIndex = 11;
            selectSeedfileButton.Text = "Seed dosyası";
            selectSeedfileButton.TextAlign = ContentAlignment.MiddleLeft;
            selectSeedfileButton.UseVisualStyleBackColor = true;
            selectSeedfileButton.Click += selectSeedfile_Click;
            selectSeedfileButton.Image = Image.FromFile("resources\\open-file-icon.jpg").GetThumbnailImage(20, 20, null, new IntPtr());
            selectSeedfileButton.TextAlign = ContentAlignment.MiddleLeft;
            // 
            // seedfilePath
            // 
            seedfilePath.AutoSize = false;
            seedfilePath.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point);
            seedfilePath.Location = new Point(162, 143);
            seedfilePath.Name = "seedfilePath";
            seedfilePath.Size = new Size(280, 15);
            seedfilePath.TabIndex = 7;
            seedfilePath.Text = "Seed dosyası seçilmedi!";
            seedfilePath.Click += seedfilePath_Click;
            seedfilePath.Width = 280; // Set the desired width
            seedfilePath.Height = 30;               // Set the desired height
            seedfilePath.TextAlign = ContentAlignment.MiddleLeft; // Align text to the top-left
            // 
            // EncDecDialog
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(456, 267);
            Controls.Add(manualSeeds);
            Controls.Add(selectSeedfileButton);
            Controls.Add(seedfilePath);
            Controls.Add(seedListLable);
            Controls.Add(cancelEncButton);
            Controls.Add(advSettingsButton);
            Controls.Add(encDecButton);
            Controls.Add(passLabel);
            Controls.Add(idLabel);
            Controls.Add(passBox);
            Controls.Add(idBox);
            Controls.Add(seedList);
            Name = "EncDecDialog";
            Text = "Encrypt Dialog";
            ResumeLayout(false);
            PerformLayout();
        }

        private void shouldEncDecBeEnabled()
        {
            bool encDecEnabled = passBox.Text.Length > 0 && idBox.Text.Length > 0;

            if (manualSeeds.Checked)
            {
                encDecEnabled = encDecEnabled && seedList.Items.Count > 0;
            }
            else
            {
                encDecEnabled = encDecEnabled && canUseSeedfile;
            }

            encDecButton.Enabled = encDecEnabled;
        }

        private void passBox_TextChanged(object sender, EventArgs e)
        {
            shouldEncDecBeEnabled();
        }

        private void idBox_TextChanged(object sender, EventArgs e)
        {
            shouldEncDecBeEnabled();
        }

        private void selectSeedfile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();

            // Set dialog properties
            openFileDialog.Filter = "Seedfiles (*.sf)|*.sf|All Files (*.*)|*.*"; // Filter to .sf files
            openFileDialog.Title = "Select an Seedfile";

            if (Directory.Exists("seedfiles") == false)
                Directory.CreateDirectory("seedfiles");

            openFileDialog.InitialDirectory = Path.GetFullPath("seedfiles/");

            // Show the dialog and check if a file was selected
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                // Get the selected file path
                string selectedFilePath = openFileDialog.FileName;

                seedfilePath.Text = selectedFilePath;
                canUseSeedfile = false;
                seedfilePath.ForeColor = Color.DarkRed;
                shouldEncDecBeEnabled();

                var conf = Configurator.GetInstance();

                conf.SaveConfig("dummyfile.in");
                conf.ResetConfig();

                conf.SetCommand("readsf");
                conf.SetID(idBox.Text);
                conf.SetPass(passBox.Text);
                conf.SetInFilepath(seedfilePath.Text);

                conf.SaveConfig("resources\\config.in");

                conf.ReadFromFile("dummyfile.in");
                File.Delete("dummyfile.in");

                var shand = ServiceHandler.GetInstance();

                var res = shand.StartEngine("resources\\config.in");
                File.Delete("resources\\config.in");

                var lines = res.Split('\n');

                foreach (var line in lines)
                {
                    if (line.Contains("Total seeds : "))
                    {
                        var sline = line.Remove(0, line.IndexOf(':') + 1);
                        if (int.Parse(sline) > 0)
                        {
                            canUseSeedfile = true;
                            seedfilePath.ForeColor = Color.DarkGreen;
                            shouldEncDecBeEnabled();
                            break;
                        }
                    }
                }
            }




        }

        private void ManualSeed_Click(object sender, EventArgs e)
        {
            seedList.Visible = manualSeeds.Checked;
            seedListLable.Visible = manualSeeds.Checked;

            selectSeedfileButton.Visible = manualSeeds.Checked == false;
            seedfilePath.Visible = manualSeeds.Checked == false;
            shouldEncDecBeEnabled();
        }

        private void AdvSettingsButton_Click(object sender, EventArgs e)
        {
            advSettingsDialog.ShowDialog(this);
        }

        private void CancelEncButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void SeedList_MouseHover(object sender, EventArgs e)
        {
            string seeds = string.Empty;

            for (int i = 0; i < seedList.Items.Count; i++)
            {
                seeds += (i + 1) + ") " + seedList.Items[i] + (i + 1 < seedList.Items.Count ? "\n" : "");
            }

            toolTip.SetToolTip(seedList, seeds);
        }

        private void PassBox_MouseHover(object sender, EventArgs e)
        {
            toolTip.SetToolTip(passBox, passBox.Text);
        }

        private void SeedList_SelectedIndexChanged(object sender, EventArgs e)
        {
            _selectedSeedIndex = seedList.SelectedIndex;
        }

        private void SeedList_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (seedList.Text != string.Empty && seedList.Text.Trim() != string.Empty)
                {
                    seedList.BackColor = Color.White;
                    var text = seedList.Text;

                    if (_selectedSeedIndex == -1)
                    {
                        seedList.Items.Add(text);
                        seedList.Text = "";
                    }
                    else
                    {
                        seedList.Items[_selectedSeedIndex] = text;
                        seedList.Text = "";
                        _selectedSeedIndex = -1;
                    }
                }
                else if (_selectedSeedIndex != -1)
                {
                    seedList.Items.RemoveAt(_selectedSeedIndex);
                }
                else
                {
                    seedList.BackColor = Color.PaleVioletRed;
                }
                shouldEncDecBeEnabled();
            }
        }


        protected void SaveOwnConfiguration(string command)
        {
            var configurator = Configurator.GetInstance();
            configurator.SetID(idBox.Text);
            configurator.SetPass(passBox.Text);
            configurator.SetCommand(command);

            if (manualSeeds.Checked)
            {
                List<string> seeds = new List<string>();
                foreach (var seed in seedList.Items)
                {
                    seeds.Add(seed.ToString());
                }

                configurator.SetSeeds(seeds);
            }
            else
            {
                configurator.SetSeedfile(seedfilePath.Text);
            }


        }
        #endregion



        protected TextBox idBox;
        protected TextBox passBox;
        protected Label idLabel;
        protected Label passLabel;
        protected Button encDecButton;
        protected Button advSettingsButton;
        protected Button cancelEncButton;

        protected CheckBox manualSeeds;

        protected Button selectSeedfileButton;
        protected bool canUseSeedfile = false;
        protected Label seedfilePath;

        protected ComboBox seedList;
        protected int _selectedSeedIndex = -1;

        protected Label seedListLable;

        protected ToolTip toolTip;

        protected AdvSettingsDialog advSettingsDialog = new AdvSettingsDialog();
    }
}