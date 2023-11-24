namespace zEntryptUI.Forms
{
    partial class MainForm
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
            encryptForm = new EncryptForm(this);
            decryptForm = new DecryptForm(this);
            Icon = new Icon("resources\\app-icon.ico");
            SuspendLayout();
            this.components = new System.ComponentModel.Container();
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Text = "zEncrypter GUI";

            tabControl.Controls.AddRange(new Control[] {encryptForm, decryptForm});
            tabControl.Location = new Point(0, 0);
            tabControl.Size = new Size(600, 250);

            ClientSize = new Size(600, 250);
            Controls.Add(tabControl);

            Location = new Point(300, 300);

            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private EncryptForm encryptForm;
        private DecryptForm decryptForm;
        private TabControl tabControl = new TabControl();
    }
}