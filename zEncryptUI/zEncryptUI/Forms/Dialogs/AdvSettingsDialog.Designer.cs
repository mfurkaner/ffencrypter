namespace zEntryptUI
{
    partial class AdvSettingsDialog
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
            binary = new CheckBox();
            mangle = new CheckBox();
            depth = new NumericUpDown();
            depthLabel = new Label();
            okButton = new Button();
            resetButton = new Button();
            ((System.ComponentModel.ISupportInitialize)depth).BeginInit();
            SuspendLayout();

            Icon = new Icon("resources\\adv-set-icon.ico");
            // 
            // binary
            // 
            binary.AutoSize = true;
            binary.Checked = true;
            binary.CheckState = CheckState.Checked;
            binary.Location = new Point(66, 36);
            binary.Name = "binary";
            binary.Size = new Size(134, 19);
            binary.TabIndex = 0;
            binary.Text = "Bit seviyesi şifreleme";
            binary.UseVisualStyleBackColor = true;
            // 
            // mangle
            // 
            mangle.AutoSize = true;
            mangle.Checked = true;
            mangle.CheckState = CheckState.Checked;
            mangle.Location = new Point(66, 76);
            mangle.Name = "mangle";
            mangle.Size = new Size(110, 19);
            mangle.TabIndex = 1;
            mangle.Text = "Parça karıştırma";
            mangle.UseVisualStyleBackColor = true;
            mangle.CheckedChanged += Mangle_CheckedChanged;
            // 
            // depth
            // 
            depth.Font = new Font("Segoe UI", 10F, FontStyle.Regular, GraphicsUnit.Point);
            depth.Location = new Point(161, 118);
            depth.Name = "depth";
            depth.Size = new Size(39, 25);
            depth.TabIndex = 2;
            depth.Value = new decimal(new int[] { 10, 0, 0, 0 });
            depth.ValueChanged += depth_ValueChanged;
            // 
            // depthLabel
            // 
            depthLabel.AutoSize = true;
            depthLabel.Location = new Point(39, 122);
            depthLabel.Name = "depthLabel";
            depthLabel.Size = new Size(106, 15);
            depthLabel.TabIndex = 3;
            depthLabel.Text = "Karıştırma derinliği";
            // 
            // okButton
            // 
            okButton.Location = new Point(39, 161);
            okButton.Name = "okButton";
            okButton.Size = new Size(58, 35);
            okButton.TabIndex = 4;
            okButton.Text = "OK";
            okButton.UseVisualStyleBackColor = true;
            okButton.Click += OkButton_Click;
            // 
            // resetButton
            // 
            resetButton.Location = new Point(161, 161);
            resetButton.Name = "resetButton";
            resetButton.Size = new Size(64, 35);
            resetButton.TabIndex = 5;
            resetButton.Text = "Reset";
            resetButton.UseVisualStyleBackColor = true;
            resetButton.Click += ResetButton_Click;
            // 
            // AdvSettingsDialog
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(258, 218);
            Controls.Add(resetButton);
            Controls.Add(okButton);
            Controls.Add(depthLabel);
            Controls.Add(depth);
            Controls.Add(mangle);
            Controls.Add(binary);
            Name = "AdvSettingsDialog";
            Text = "AdvSettingsDialog";
            ((System.ComponentModel.ISupportInitialize)depth).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        private void ResetButton_Click(object sender, EventArgs e)
        {
            mangle.Checked = true;
            binary.Checked = true;
            depth.Value = 10;
        }

        private void OkButton_Click(object sender, EventArgs e)
        {
            SaveOwnConfiguration();
            this.Close();
        }

        public void SaveOwnConfiguration()
        {
            var configurator = Configurator.GetInstance();
            configurator.SetMangle(mangle.Checked);
            configurator.SetBinary(binary.Checked);
            configurator.SetMangleDepth((mangle.Checked ? (int)depth.Value : 0));
        }

        private void Mangle_CheckedChanged(object sender, EventArgs e)
        {
            depth.Enabled = mangle.Checked;
            depthLabel.Enabled = mangle.Checked;
        }

        #endregion

        private CheckBox binary;
        private CheckBox mangle;
        private NumericUpDown depth;
        private Label depthLabel;
        private Button okButton;
        private Button resetButton;
    }
}