using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace OMAP_L138_AIS_GUI
{
    public partial class AboutForm : Form
    {
        private int x, y;

        public AboutForm(int hx, int hy)
        {
            InitializeComponent();

            x = hx;
            y = hy;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void AboutForm_Load(object sender, EventArgs e)
        {
            this.SetDesktopLocation(x, y);

            labelVersion.Text = String.Format("Version {0}.{1}", Consts.majorRev, Consts.minorRev);
        }
    }
}