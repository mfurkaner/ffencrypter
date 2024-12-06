namespace zEntryptUI
{
    partial class EncDecForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            findButton = new Button();
            encDecButton = new Button();
            autoNameCheckbox = new CheckBox();
            inputFilenameText = new TextBox();
            outputFilenameText = new TextBox();
            toolTip = new ToolTip(components);
            SuspendLayout();
            // 
            // findButton
            // 
            findButton.ImageAlign = ContentAlignment.MiddleRight;
            findButton.Name = "findButton";
            findButton.Size = new Size(85, 25);
            findButton.TabIndex = 0;
            findButton.Text = "Dosya Seç";
            findButton.TextAlign = ContentAlignment.MiddleLeft;
            findButton.UseVisualStyleBackColor = true;
            findButton.Click += FindButton_Click;
            findButton.Location = new Point(50, 50);
            findButton.Image = Image.FromFile("resources\\open-file-icon.jpg").GetThumbnailImage(20, 20, null, new IntPtr());
            // 
            // encDecButton
            // 
            encDecButton.ImageAlign = ContentAlignment.MiddleRight;
            encDecButton.Name = "encDecButton";
            encDecButton.Size = new Size(85, 25);
            encDecButton.TabIndex = 0;
            encDecButton.TextAlign = ContentAlignment.MiddleLeft;
            encDecButton.UseVisualStyleBackColor = true;
            encDecButton.Location = new Point(50, 120);
            // 
            // autoNameCheckbox
            // 
            autoNameCheckbox.AutoSize = true;
            autoNameCheckbox.Checked = true;
            autoNameCheckbox.CheckState = CheckState.Checked;
            autoNameCheckbox.Name = "autoNameCheckbox";
            autoNameCheckbox.Size = new Size(131, 19);
            autoNameCheckbox.TabIndex = 3;
            autoNameCheckbox.Text = "Otomatik isimlendir";
            autoNameCheckbox.UseVisualStyleBackColor = true;
            autoNameCheckbox.CheckedChanged += autoNameCheckbox_CheckedChanged;
            autoNameCheckbox.Location = new Point(150, 90);
            // 
            // inputFilenameText
            // 
            inputFilenameText.Location = new Point(150, 50);
            inputFilenameText.Name = "inputFilenameText";
            inputFilenameText.Size = new Size(388, 23);
            inputFilenameText.TabIndex = 4;
            inputFilenameText.MouseMove += inputFilenameText_MouseMove;
            // 
            // outputFilenameText
            // 
            outputFilenameText.Location = new Point(150, 120);
            outputFilenameText.Name = "outputFilenameText";
            outputFilenameText.ReadOnly = true;
            outputFilenameText.Size = new Size(388, 23);
            outputFilenameText.TabIndex = 5;
            outputFilenameText.MouseMove += OutputFilenameText_MouseMove;
            // 
            // EncDecForm
            // 
            Controls.Add(outputFilenameText);
            Controls.Add(inputFilenameText);
            Controls.Add(autoNameCheckbox);
            Controls.Add(findButton);
            Controls.Add(encDecButton);
            Size = new Size(500, 300);
            Enter += onEnterForm;
            ResumeLayout(false);
            PerformLayout();
        }

        private void onEnterForm(object sender, EventArgs e)
        {
            if (owner != null)
            {
                // Define the desired client size of the current form
                ClientSize = new Size(600, 250);

                // Resize the owner form to accommodate the current form, including borders
                owner.Size = new Size(600, 280);

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

        protected void inputFilenameText_MouseMove(object sender, MouseEventArgs e)
        {
            toolTip.SetToolTip(inputFilenameText, actual_input_path);
        }

        protected void OutputFilenameText_MouseMove(object sender, MouseEventArgs e)
        {
            toolTip.SetToolTip(outputFilenameText, actual_output_path);
        }

        protected void FindButton_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = "c:\\";
                openFileDialog.Filter = "All files (*.*)|*.*";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    //Get the path of specified file
                    actual_input_path = openFileDialog.FileName;
                    inputFilenameText.Text = GetRelativePath(actual_input_path);
                }
            }
        }

        protected void SaveOwnConfiguration()
        {
            var configurator = Configurator.GetInstance();
            configurator.SetInFilepath(actual_input_path);
            configurator.SetOutFilepath(actual_output_path);
        }

        protected string GetRelativePath(string path)
        {
            string relativePath = Path.GetFileName(path);
            return "...\\" + relativePath;
        }

        #endregion

        protected Button findButton;
        protected Button encDecButton;
        protected Button advSettingsButton;
        protected CheckBox autoNameCheckbox;
        protected TextBox inputFilenameText;
        protected TextBox outputFilenameText;

        protected ToolTip toolTip;

        protected string actual_input_path;
        protected string actual_output_path;

        protected Form owner;
    }
}