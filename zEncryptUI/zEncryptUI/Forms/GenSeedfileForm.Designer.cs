using System.Windows.Forms;
using zEntryptUI;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Window;

namespace zEncryptUI.Forms
{
    partial class GenSeedfileForm
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
            idTextbox = new TextBox();
            pwTextbox = new TextBox();
            idLabel = new Label();
            pwLabel = new Label();
            seedsListbox = new ListBox();
            saveButton = new Button();
            seedLabel = new Label();
            seedTextbox = new TextBox();
            addSeedButton = new Button();
            seedListLabel = new Label();
            editSeedButton = new Button();
            deleteSeedButton = new Button();
            SuspendLayout();
            // 
            // idTextbox
            // 
            idTextbox.Location = new Point(100, 67);
            idTextbox.Name = "idTextbox";
            idTextbox.Size = new Size(176, 23);
            idTextbox.TabIndex = 0;
            idTextbox.TextChanged += idTextbox_TextChanged;
            // 
            // pwTextbox
            // 
            pwTextbox.Location = new Point(100, 114);
            pwTextbox.Name = "pwTextbox";
            pwTextbox.Size = new Size(176, 23);
            pwTextbox.TabIndex = 1;
            pwTextbox.PasswordChar = '*';
            pwTextbox.TextChanged += pwTextbox_TextChanged;
            // 
            // idLabel
            // 
            idLabel.AutoSize = true;
            idLabel.Location = new Point(28, 70);
            idLabel.Name = "idLabel";
            idLabel.Size = new Size(18, 15);
            idLabel.TabIndex = 2;
            idLabel.Text = "ID";
            idLabel.Click += label1_Click;
            // 
            // pwLabel
            // 
            pwLabel.AutoSize = true;
            pwLabel.Location = new Point(28, 122);
            pwLabel.Name = "pwLabel";
            pwLabel.Size = new Size(57, 15);
            pwLabel.TabIndex = 3;
            pwLabel.Text = "Password";
            // 
            // seedsListbox
            // 
            seedsListbox.FormattingEnabled = true;
            seedsListbox.ItemHeight = 15;
            seedsListbox.Location = new Point(326, 67);
            seedsListbox.Name = "seedsListbox";
            seedsListbox.Size = new Size(203, 229);
            seedsListbox.TabIndex = 6;
            seedsListbox.SelectedIndexChanged += seedsListbox_SelectedIndexChanged;
            seedsBindingSource.DataSource = seeds;
            seedsListbox.DataSource = seedsBindingSource;
            seedsBindingSource.ListChanged += seeds_changed;
            // 
            // saveButton
            // 
            saveButton.Location = new Point(250, 313);
            saveButton.Name = "saveButton";
            saveButton.Size = new Size(80, 35);
            saveButton.TabIndex = 5;
            saveButton.Text = "  Save";
            saveButton.Font = new Font(saveButton.Font.FontFamily, saveButton.Font.Size, FontStyle.Bold); saveButton.UseVisualStyleBackColor = true;
            saveButton.Click += saveButton_Click;
            saveButton.Enabled = false;
            saveButton.Image = Image.FromFile("resources\\open-file-icon.jpg").GetThumbnailImage(20, 20, null, new IntPtr());
            saveButton.TextAlign = ContentAlignment.MiddleLeft;
            saveButton.ImageAlign = ContentAlignment.MiddleRight;
            // 
            // seedLabel
            // 
            seedLabel.AutoSize = true;
            seedLabel.Location = new Point(28, 204);
            seedLabel.Name = "seedLabel";
            seedLabel.Size = new Size(32, 15);
            seedLabel.TabIndex = 7;
            seedLabel.Text = "Seed";
            // 
            // seedTextbox
            // 
            seedTextbox.Location = new Point(100, 196);
            seedTextbox.Name = "seedTextbox";
            seedTextbox.Size = new Size(176, 23);
            seedTextbox.TabIndex = 4;
            seedTextbox.KeyUp += seedTextbox_KeyUp;
            // 
            // seedListLabel
            // 
            seedListLabel.AutoSize = true;
            seedListLabel.Location = new Point(409, 40);
            seedListLabel.Name = "seedListLabel";
            seedListLabel.Size = new Size(37, 15);
            seedListLabel.TabIndex = 9;
            seedListLabel.Text = "Seeds";
            // 
            // addSeedButton
            // 
            addSeedButton.Location = new Point(81, 238);
            addSeedButton.Name = "addSeedButton";
            addSeedButton.Size = new Size(66, 25);
            addSeedButton.TabIndex = 8;
            addSeedButton.Text = "Add Seed";
            addSeedButton.UseVisualStyleBackColor = true;
            addSeedButton.Click += addSeedButton_Click;
            // 
            // editSeedButton
            // 
            editSeedButton.Location = new Point(155, 238);
            editSeedButton.Name = "editSeedButton";
            editSeedButton.Size = new Size(66, 25);
            editSeedButton.TabIndex = 10;
            editSeedButton.Text = "Edit Seed";
            editSeedButton.UseVisualStyleBackColor = true;
            editSeedButton.Click += editSeedButton_Click;
            editSeedButton.Enabled = false;
            // 
            // deleteSeedButton
            // 
            deleteSeedButton.Location = new Point(229 , 238);
            deleteSeedButton.Name = "deleteSeedButton";
            deleteSeedButton.Size = new Size(66, 25);
            deleteSeedButton.TabIndex = 10;
            deleteSeedButton.Text = "Del Seed";
            deleteSeedButton.UseVisualStyleBackColor = true;
            deleteSeedButton.Click += deleteSeedButton_Click;
            deleteSeedButton.Enabled = false;
    
            // 
            // GenSeedfileForm
            // 
            ClientSize = new Size(1000, 1000);
            Controls.Add(editSeedButton);
            Controls.Add(seedListLabel);
            Controls.Add(addSeedButton);
            Controls.Add(deleteSeedButton);
            Controls.Add(seedLabel);
            Controls.Add(seedTextbox);
            Controls.Add(saveButton);
            Controls.Add(seedsListbox);
            Controls.Add(pwLabel);
            Controls.Add(idLabel);
            Controls.Add(pwTextbox);
            Controls.Add(idTextbox);
            Name = "GenSeedfileForm";
            Text = "Generate Seedfile";
            Enter += onEnterForm;
            ResumeLayout(false);
            PerformLayout();
        }

        private void seedTextbox_KeyUp(object sender, KeyEventArgs e)
        {
            if ( e.KeyCode == Keys.Enter)
            {
                addSeedButton_Click(sender, e);
            }
        }

        private void seeds_changed(object sender, System.ComponentModel.ListChangedEventArgs e)
        {
            saveButton.Enabled = pwTextbox.Text.Length > 0 && idTextbox.Text.Length > 0 && seeds.Count > 0;
        }

        private void pwTextbox_TextChanged(object sender, EventArgs e)
        {
            saveButton.Enabled = pwTextbox.Text.Length > 0 && idTextbox.Text.Length > 0 && seeds.Count > 0;
        }

        private void idTextbox_TextChanged(object sender, EventArgs e)
        {
            saveButton.Enabled = pwTextbox.Text.Length > 0 && idTextbox.Text.Length > 0 && seeds.Count > 0;
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            using (SaveFileDialog saveFileDialog = new SaveFileDialog())
            {
                // Set initial properties for the SaveFileDialog
                saveFileDialog.Title = "Save Seedfile";
                saveFileDialog.Filter = "Seed Files (*.sf)|*.sf|All Files (*.*)|*.*"; // Allow text or all files
                saveFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments); // Default to user's Documents folder
                saveFileDialog.FileName = "zEncyptSeedfile.sf"; // Suggest a default filename

                // Show the dialog and get the result
                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                {
                    string selectedFilePath = saveFileDialog.FileName;

                    var conf = Configurator.GetInstance();

                    conf.SaveConfig("dummyfile.in");
                    conf.ResetConfig();

                    conf.SetCommand("gensf");
                    conf.SetID(idTextbox.Text);
                    conf.SetPass(pwTextbox.Text);
                    conf.SetOutFilepath(selectedFilePath);
                    
                    conf.SetSeeds(seeds);


                    conf.SaveConfig("resources\\config.in");

                    conf.ReadFromFile("dummyfile.in");
                    File.Delete("dummyfile.in");

                    var shand = ServiceHandler.GetInstance();

                    var res = shand.StartEngine("resources\\config.in");
                    File.Delete("resources\\config.in");
                }
            }
        }

        private void onEnterForm(object sender, EventArgs e)
        {
            if (owner != null)
            {
                // Define the desired client size of the current form
                ClientSize = new Size(592, 400);

                // Resize the owner form to accommodate the current form, including borders
                owner.Size = new Size(
                    ClientSize.Width + (owner.Size.Width - owner.ClientSize.Width),
                    ClientSize.Height + (owner.Size.Height - owner.ClientSize.Height)
                );

                // Optional: Adjust the size of the TabControl inside the form if necessary
                foreach (Control control in owner.Controls)
                {
                    if (control is TabControl tabControl)
                    {
                        tabControl.Dock = DockStyle.Fill; // Ensures it fills the form
                    }
                }

                PerformLayout();
                owner.PerformLayout();
            }
        }


        private void seedsListbox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (seedsListbox.SelectedIndex >= 0 && seedsListbox.SelectedIndex < seeds.Count)
            {
                seedTextbox.Text = seeds[seedsListbox.SelectedIndex];
                editSeedButton.Enabled = seeds.Count > 0;
                deleteSeedButton.Enabled = seeds.Count > 0;
            }
            else
            {
                editSeedButton.Enabled = false;
                deleteSeedButton.Enabled = false;
            }
                
        }

        private void addSeedButton_Click(object sender, EventArgs e)
        {
            seeds.Add(seedTextbox.Text);
            seedsBindingSource.ResetBindings(false); // Notify the BindingSource to refresh

            seedTextbox.Text = "";
        }

        private void editSeedButton_Click(object sender, EventArgs e)
        {
            if (seedsListbox.SelectedIndex < seeds.Count)
            {
                seeds[seedsListbox.SelectedIndex] = seedTextbox.Text;
                seedsBindingSource.ResetBindings(false); // Notify the BindingSource to refresh

                seedTextbox.Text = "";
            }
        }


        private void deleteSeedButton_Click(object sender, EventArgs e)
        {
            if (seedsListbox.SelectedIndex < seeds.Count)
            {
                seeds.RemoveAt(seedsListbox.SelectedIndex);
                seedsBindingSource.ResetBindings(false); // Notify the BindingSource to refresh
            }
        }


        #endregion

        private TextBox idTextbox;
        private TextBox pwTextbox;
        private Label idLabel;
        private Label pwLabel;
        private ListBox seedsListbox;
        private Button saveButton;
        private Label seedLabel;
        private TextBox seedTextbox;
        private Button addSeedButton;
        private Label seedListLabel;
        private Button editSeedButton;
        private Button deleteSeedButton;


        private List<string> seeds = new List<string>();
        private BindingSource seedsBindingSource = new BindingSource();

        protected Form owner;
    }
}