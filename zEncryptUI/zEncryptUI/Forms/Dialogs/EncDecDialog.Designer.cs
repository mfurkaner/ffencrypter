using System.Resources;

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
            SuspendLayout();
            // 
            // seedList
            // 
            seedList.FormattingEnabled = true;
            seedList.Location = new Point(109, 115);
            seedList.Name = "seedList";
            seedList.Size = new Size(325, 23);
            seedList.TabIndex = 0;
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
            // 
            // advSettingsButton
            // 
            advSettingsButton.ImageAlign = ContentAlignment.MiddleRight;
            advSettingsButton.Location = new Point(160, 156);
            advSettingsButton.Name = "advSettingsButton";
            advSettingsButton.Size = new Size(130, 29);
            advSettingsButton.TabIndex = 11;
            advSettingsButton.Text = "Gelişmiş Ayarlar";
            advSettingsButton.TextAlign = ContentAlignment.MiddleLeft;
            advSettingsButton.UseVisualStyleBackColor = true;
            advSettingsButton.Click += AdvSettingsButton_Click;
            advSettingsButton.Image = Image.FromFile("resources\\adv-set-icon.png").GetThumbnailImage(20, 20, null, new IntPtr());
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
            seedListLable.Location = new Point(12, 118);
            seedListLable.Name = "seedListLable";
            seedListLable.Size = new Size(79, 15);
            seedListLable.TabIndex = 14;
            seedListLable.Text = "Tohum Listesi";
            // 
            // EncDecDialog
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(456, 267);
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

            }
        }


        protected void SaveOwnConfiguration(string command)
        {
            var configurator = Configurator.GetInstance();
            configurator.SetID(idBox.Text);
            configurator.SetPass(passBox.Text);
            configurator.SetCommand(command);

            List<string> seeds = new List<string>();
            foreach (var seed in seedList.Items)
            {
                seeds.Add(seed.ToString());
            }
            configurator.SetSeeds(seeds);
        }
        #endregion

        protected ComboBox seedList;
        protected int _selectedSeedIndex = -1;

        protected TextBox idBox;
        protected TextBox passBox;
        protected Label idLabel;
        protected Label passLabel;
        protected Button encDecButton;
        protected Button advSettingsButton;
        protected Button cancelEncButton;
        protected Label seedListLable;

        protected ToolTip toolTip;

        protected AdvSettingsDialog advSettingsDialog = new AdvSettingsDialog();
    }
}