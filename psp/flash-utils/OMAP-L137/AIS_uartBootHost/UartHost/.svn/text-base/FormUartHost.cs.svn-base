// FormUartHost.cs ------------------------------------------------------------------------------
//
// Implements GUI wrapper to run UART boot using AIS_Parser class (in AIS_Util namespace).
//
// Written by Joe Coombs, 2009-02-20
//
// Copyright (C) 2008 Texas Instruments Incorporated
// All Rights Reserved
// ------------------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Threading;
using AIS_Util;

namespace UartHost
{
    delegate void CloseDelegate();

    public partial class FormUartHost : Form
    {
        private SerialPort myUART;
        private Thread bootThread;
        private byte[] ais;

        public FormUartHost()
        {
            InitializeComponent();
        }

        public void UTIL_log(String text)
        {
            // print text as new line in log text box (append newline)
            richTextBoxLog.AppendText(text + "\n");
            // scroll box to end
            richTextBoxLog.ScrollToCaret();
            // force redraw
            richTextBoxLog.Refresh();
        }

        // invoke version; can be called safely from another thread
        public void UTIL_log_INVOKE(String text)
        {
            LogFxnDelegate temp_delegate = new LogFxnDelegate(UTIL_log);
            this.Invoke(temp_delegate, new object[] { text });
        }

        public void UTIL_clr_log()
        {
            // reset log box contents
            richTextBoxLog.Clear();
        }

        private int UTIL_uartRead(byte[] rcvBuf, int index, int rcvSize, int timeout)
        {
            int bytesRead = 0;

            myUART.ReadTimeout = timeout;
            try
            {
                // note: this is necessary because the SerialPort.Read method likes to return
                // after reading only one byte, regardless of the specified count
                while (bytesRead < rcvSize)
                    bytesRead += myUART.Read(rcvBuf, index + bytesRead, rcvSize - bytesRead);
            }
            catch (Exception ex)
            {
                // log using invoke since this will be called by other thread
                UTIL_log_INVOKE("(Serial Port): Read error! (" + ex.Message + ")");
                return -1;
            }

            return 0;
        }

        private int UTIL_uartWrite(byte[] xmtBuf, int index, int xmtSize, int timeout)
        {
            myUART.WriteTimeout = timeout;
            try
            {
                myUART.Write(xmtBuf, index, xmtSize);
            }
            catch (Exception ex)
            {
                // log using invoke since this will be called by other thread
                UTIL_log_INVOKE("(Serial Port): Write error! (" + ex.Message + ")");
                return -1;
            }

            return 0;
        }

        private void UTIL_boot()
        {
            // create and run AIS parser
            AIS_Parser parser = new AIS_Parser(AIS_Parser.AIS_UART, this.UTIL_log_INVOKE, this.UTIL_uartRead, this.UTIL_uartWrite);
            parser.waitBOOTME = checkBoxWaitForBootme.Checked;

            try
            {
                parser.boot(ais);

                // reset form when done (use invoke)
                UTIL_close_boot_INVOKE();
            }
            catch (Exception ex)
            {
                UTIL_log_INVOKE("(System): Unhandled exception (" + ex.Message + ")");
            }
        }

        private void UTIL_close_boot()
        {
            // close serial port
            try
            {
                myUART.Close();

                UTIL_log("(Serial Port): Closing " + textBoxPort.Text + ".");

                // toggle on buttons
                buttonStart.Enabled = true;
                buttonStop.Enabled = false;
            }
            catch (Exception ex)
            {
                UTIL_log("(System): Unhandled exception (" + ex.Message + ")");
            }
        }

        // invoke version; can be called safely from another thread
        private void UTIL_close_boot_INVOKE()
        {
            CloseDelegate temp_delegate = new CloseDelegate(UTIL_close_boot);
            this.Invoke(temp_delegate, new object[] { });
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            // clear log
            UTIL_clr_log();

            // dump contents of specified AIS file
            try
            {
                ais = File.ReadAllBytes(textBoxFileName.Text);
                UTIL_log(String.Format("(File IO): Read {0} bytes from file ", ais.Length) + textBoxFileName.Text + ".");
            }
            catch (Exception ex)
            {
                UTIL_log("(File IO): Error reading file \"" + textBoxFileName.Text + "\". (" + ex.Message + ")");
                return;
            }
            
            // open serial port
            try
            {
                UTIL_log("(Serial Port): Opening " + textBoxPort.Text + " at " + textBoxBaud.Text + " baud...");
                myUART = new SerialPort(textBoxPort.Text, Convert.ToInt32(textBoxBaud.Text), Parity.None, 8, StopBits.One); 
                myUART.Open();
            }
            catch (Exception ex)
            {
                UTIL_log("(Serial Port): Error opening " + textBoxPort.Text + "! (" + ex.Message + ")");
                return;
            }

            // toggle buttons before processing
            buttonStart.Enabled = false;
            buttonStop.Enabled = true;

            // parse AIS in new thread
            bootThread = new Thread(UTIL_boot);
            bootThread.Start();
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            // make sure boot is running
            if (bootThread.IsAlive == false)
                return;

            // abort boot
            bootThread.Suspend();
            // Note: Thread.Abort does not play nicely with SerialPort operations.
            //       Thread.Suspend is deprecated and messy (we never dispose the thread),
            //       but it'll have to do.
            UTIL_log("(System): Boot aborted by user.");
            UTIL_close_boot();
        }

        private void buttonFileBrowse_Click(object sender, EventArgs e)
        {
            // open file browser
            OpenFileDialog aisOpenSel = new OpenFileDialog();

            aisOpenSel.Filter = "AIS binary files|*.bin;*.ais|All files|*.*";
            aisOpenSel.Title = "Open AIS File";
            try
            {
                if (aisOpenSel.ShowDialog() == DialogResult.OK)
                    textBoxFileName.Text = aisOpenSel.FileName;
            }
            catch (Exception ex)
            {
                UTIL_log("(System): Error retrieving file name (" + ex.Message + ")");
                textBoxFileName.Clear();
            }
        }
    }
}