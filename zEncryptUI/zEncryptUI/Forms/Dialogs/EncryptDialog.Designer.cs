using System.Resources;

namespace zEntryptUI.Forms.Dialogs
{
    partial class EncryptDialog
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
            SuspendLayout();
            Icon = new Icon("resources\\enc-icon.ico");
            encDecButton.Text = "Şifrele";
            encDecButton.Click += EncButton_Click;
            // 
            // EncryptDialog
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(456, 267);

            ResumeLayout(false);
            PerformLayout();
        }

        private void EncButton_Click(object sender, EventArgs e)
        {
            SaveOwnConfiguration("enc");
            advSettingsDialog.SaveOwnConfiguration();

            var configurator = Configurator.GetInstance();

            configurator.SaveConfig("resources\\config.in");

            var serviceHandler = ServiceHandler.GetInstance();
            serviceHandler.configPath = Path.GetFullPath("resources\\config.in");
            serviceHandler.StartEngine();

            File.Delete("resources\\config.in");
        }

        #endregion
    }
}