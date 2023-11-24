using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace zEntryptUI
{
    public partial class EncDecForm : TabPage
    {
        public EncDecForm(Form owner)
        {
            this.owner = owner;
            InitializeComponent();
        }

        protected void autoNameCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            outputFilenameText.ReadOnly = autoNameCheckbox.Checked;
        }

    }
}
