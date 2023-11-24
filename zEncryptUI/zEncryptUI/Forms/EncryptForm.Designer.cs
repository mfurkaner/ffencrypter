using zEntryptUI.Forms.Dialogs;

namespace zEntryptUI
{
    partial class EncryptForm
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
            encryptDialog = new EncryptDialog(owner);
            SuspendLayout();
            // 
            // encDecButton
            // 
            encDecButton.Text = "Şifrele";
            encDecButton.Click += EncButton_Click;
            encDecButton.Image = Image.FromFile("resources\\enc-icon.png").GetThumbnailImage(20, 20, null, new IntPtr());

            inputFilenameText.TextChanged += inputFilenameText_TextChanged;
            // 
            // EncryptForm
            // 
            ClientSize = new Size(500, 300);

            Name = "Encrypt";
            Text = "Şifreleme";

            ResumeLayout(false);
            PerformLayout();
        }

        private void EncButton_Click(object sender, EventArgs e)
        {
            SaveOwnConfiguration();
            encryptDialog.ShowDialog(this);
        }

        private void inputFilenameText_TextChanged(object sender, EventArgs e)
        {
            if (inputFilenameText.Text.StartsWith("...\\"))
            {
                actual_input_path = actual_input_path.Substring(0, actual_input_path.LastIndexOf('\\'))
                    + inputFilenameText.Text.Substring(inputFilenameText.Text.IndexOf('\\'));
            }

            if (!File.Exists(actual_input_path))
            {
                inputFilenameText.BackColor = Color.PaleVioletRed;
            }
            else
            {
                inputFilenameText.BackColor = Color.WhiteSmoke;
            }

            if (autoNameCheckbox.Checked)
            {
                var input = inputFilenameText.Text;
                var actual_input = actual_input_path;

                var dotIndex = input.LastIndexOf('.');
                var dotIndexAct = actual_input.LastIndexOf('.');
                if (dotIndex == -1)
                    outputFilenameText.Text = input + "_enc";
                else
                    outputFilenameText.Text = input.Substring(0, dotIndex) + "_enc" + input.Substring(dotIndex);

                if (dotIndexAct == -1)
                    actual_output_path = actual_input + "_enc";
                else
                    actual_output_path = actual_input.Substring(0, dotIndexAct) + "_enc" + actual_input.Substring(dotIndexAct);
            }
        }

        #endregion

        private EncryptDialog encryptDialog;
    }
}