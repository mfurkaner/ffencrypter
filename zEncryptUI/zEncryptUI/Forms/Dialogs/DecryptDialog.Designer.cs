using System.Resources;

namespace zEntryptUI.Forms.Dialogs
{
    partial class DecryptDialog
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
            Icon = new Icon("resources\\dec-icon.ico");
            encDecButton.Text = "    Çöz";
            encDecButton.Image = Image.FromFile("resources\\dec-icon.png").GetThumbnailImage(20, 20, null, new IntPtr());
            encDecButton.ImageAlign = ContentAlignment.MiddleRight;
            encDecButton.TextAlign = ContentAlignment.MiddleLeft;
            encDecButton.Click += DecButton_Click;
            // 
            // EncryptDialog
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(456, 267);

            Name = "DecDialog";
            Text = "Decrypt Dialog";

            ResumeLayout(false);
            PerformLayout();
        }

        private void DecButton_Click(object sender, EventArgs e)
        {
            SaveOwnConfiguration("dec");
            advSettingsDialog.SaveOwnConfiguration();

            var configurator = Configurator.GetInstance();

            configurator.SaveConfig("resources\\config.in");

            var serviceHandler = ServiceHandler.GetInstance();
            serviceHandler.configPath = Path.GetFullPath("resources\\config.in");
            var res = serviceHandler.StartEngine();

            File.Delete("resources\\config.in");

            var res_lines = res.Split('\n');
            bool succ = false;
            foreach (var line in res_lines)
            {
                if (line.Contains("is decrypted and written to"))
                {
                    succ = true;
                    break;
                }
            }

            if (succ)
                MessageBox.Show("Çözme işlemi başarıyla tamamlandı.", "Çözme Başarılı", MessageBoxButtons.OK, MessageBoxIcon.Information);
            else
                MessageBox.Show("Çözme işlemi sırasında bir hata ile karşılaşıldı.", "Çözme Başarısız", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        #endregion
    }
}