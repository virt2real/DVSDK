namespace OMAP_L138_AIS_GUI
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.labelBootType = new System.Windows.Forms.Label();
            this.labelBootMode = new System.Windows.Forms.Label();
            this.labelClockSource = new System.Windows.Forms.Label();
            this.comboBoxBootType = new System.Windows.Forms.ComboBox();
            this.comboBoxBootMode = new System.Windows.Forms.ComboBox();
            this.comboBoxClockSource = new System.Windows.Forms.ComboBox();
            this.textBoxClockSpeed = new System.Windows.Forms.TextBox();
            this.labelInputClockMHz = new System.Windows.Forms.Label();
            this.checkBoxPLL0 = new System.Windows.Forms.CheckBox();
            this.checkBoxDDR2 = new System.Windows.Forms.CheckBox();
            this.checkBoxSDRAM = new System.Windows.Forms.CheckBox();
            this.checkBoxCRC = new System.Windows.Forms.CheckBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.restoreDefaultsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveConfigToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadConfigToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tabControlConfig = new System.Windows.Forms.TabControl();
            this.tabPageGeneral = new System.Windows.Forms.TabPage();
            this.checkBoxLPSC = new System.Windows.Forms.CheckBox();
            this.checkBoxPinmux = new System.Windows.Forms.CheckBox();
            this.checkBoxPLL1 = new System.Windows.Forms.CheckBox();
            this.textBoxSpecifyEntrypoint = new System.Windows.Forms.TextBox();
            this.checkBoxSpecifyEntrypoint = new System.Windows.Forms.CheckBox();
            this.tabPageFlash = new System.Windows.Forms.TabPage();
            this.textBoxFlashTiming = new System.Windows.Forms.TextBox();
            this.labelFlashTiming = new System.Windows.Forms.Label();
            this.labelFlashWidth = new System.Windows.Forms.Label();
            this.comboBoxFlashWidth = new System.Windows.Forms.ComboBox();
            this.tabPagePeripheral = new System.Windows.Forms.TabPage();
            this.checkBoxPeriphSeqRead = new System.Windows.Forms.CheckBox();
            this.textBoxPeriphClockActual = new System.Windows.Forms.TextBox();
            this.labelPeriphClockHz = new System.Windows.Forms.Label();
            this.labelPeriphClock = new System.Windows.Forms.Label();
            this.textBoxPeriphClockIdeal = new System.Windows.Forms.TextBox();
            this.labelPeriphModuleClockMHz = new System.Windows.Forms.Label();
            this.labelPeriphModuleClock = new System.Windows.Forms.Label();
            this.textBoxPeriphModuleClock = new System.Windows.Forms.TextBox();
            this.tabPagePLL0 = new System.Windows.Forms.TabPage();
            this.labelPLL0emacMHz = new System.Windows.Forms.Label();
            this.labelPLL0sdramMHz = new System.Windows.Forms.Label();
            this.labelPLL0cpuMHz = new System.Windows.Forms.Label();
            this.labelPLL0emac = new System.Windows.Forms.Label();
            this.textBoxPLL0emac = new System.Windows.Forms.TextBox();
            this.labelPLL0sdram = new System.Windows.Forms.Label();
            this.textBoxPLL0sdram = new System.Windows.Forms.TextBox();
            this.labelPLL0cpu = new System.Windows.Forms.Label();
            this.textBoxPLL0cpu = new System.Windows.Forms.TextBox();
            this.labelPLL0div7 = new System.Windows.Forms.Label();
            this.textBoxPLL0div7 = new System.Windows.Forms.TextBox();
            this.labelPLL0div3 = new System.Windows.Forms.Label();
            this.textBoxPLL0div3 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxPLL0div1 = new System.Windows.Forms.TextBox();
            this.labelPLL0postDiv = new System.Windows.Forms.Label();
            this.textBoxPLL0postDiv = new System.Windows.Forms.TextBox();
            this.labelPLL0preDiv = new System.Windows.Forms.Label();
            this.textBoxPLL0preDiv = new System.Windows.Forms.TextBox();
            this.labelPLL0mult = new System.Windows.Forms.Label();
            this.textBoxPLL0mult = new System.Windows.Forms.TextBox();
            this.tabPageSDRAM = new System.Windows.Forms.TabPage();
            this.labelSDRAMsdrcr = new System.Windows.Forms.Label();
            this.textBoxSDRAMsdrcr = new System.Windows.Forms.TextBox();
            this.labelSDRAMsdrsrpdexit = new System.Windows.Forms.Label();
            this.textBoxSDRAMsdrsrpdexit = new System.Windows.Forms.TextBox();
            this.labelSDRAMsdtmr = new System.Windows.Forms.Label();
            this.textBoxSDRAMsdtmr = new System.Windows.Forms.TextBox();
            this.labelSDRAMsdbcr = new System.Windows.Forms.Label();
            this.textBoxSDRAMsdbcr = new System.Windows.Forms.TextBox();
            this.checkBoxSDRAMdiv = new System.Windows.Forms.CheckBox();
            this.labelSDRAMclockMHz = new System.Windows.Forms.Label();
            this.labelSDRAMclock = new System.Windows.Forms.Label();
            this.textBoxSDRAMclock = new System.Windows.Forms.TextBox();
            this.tabPagePLL1 = new System.Windows.Forms.TabPage();
            this.labelPLL1ddr2MHz = new System.Windows.Forms.Label();
            this.labelPLL1ddr2 = new System.Windows.Forms.Label();
            this.textBoxPLL1ddr2 = new System.Windows.Forms.TextBox();
            this.labelPLL1div3 = new System.Windows.Forms.Label();
            this.textBoxPLL1div3 = new System.Windows.Forms.TextBox();
            this.labelPLL1div2 = new System.Windows.Forms.Label();
            this.textBoxPLL1div2 = new System.Windows.Forms.TextBox();
            this.labelPLL1div1 = new System.Windows.Forms.Label();
            this.textBoxPLL1div1 = new System.Windows.Forms.TextBox();
            this.labelPLL1postDiv = new System.Windows.Forms.Label();
            this.textBoxPLL1postDiv = new System.Windows.Forms.TextBox();
            this.labelPLL1mult = new System.Windows.Forms.Label();
            this.textBoxPLL1mult = new System.Windows.Forms.TextBox();
            this.tabPageDDR2 = new System.Windows.Forms.TabPage();
            this.labelDDR2phy = new System.Windows.Forms.Label();
            this.textBoxDDR2phy = new System.Windows.Forms.TextBox();
            this.labelDDR2sdrcr = new System.Windows.Forms.Label();
            this.textBoxDDR2sdrcr = new System.Windows.Forms.TextBox();
            this.labelDDR2sdtimr2 = new System.Windows.Forms.Label();
            this.textBoxDDR2sdtimr2 = new System.Windows.Forms.TextBox();
            this.labelDDR2sdtimr = new System.Windows.Forms.Label();
            this.textBoxDDR2sdtimr = new System.Windows.Forms.TextBox();
            this.labelDDR2sdcr = new System.Windows.Forms.Label();
            this.textBoxDDR2sdcr = new System.Windows.Forms.TextBox();
            this.checkBoxDDR2directClock = new System.Windows.Forms.CheckBox();
            this.labelDDR2clockMHz = new System.Windows.Forms.Label();
            this.labelDDR2clock = new System.Windows.Forms.Label();
            this.textBoxDDR2clock = new System.Windows.Forms.TextBox();
            this.tabPageLPSC = new System.Windows.Forms.TabPage();
            this.labelLpsc1 = new System.Windows.Forms.Label();
            this.labelLpsc0 = new System.Windows.Forms.Label();
            this.textBoxLps1SyncRst = new System.Windows.Forms.TextBox();
            this.textBoxLps1Disable = new System.Windows.Forms.TextBox();
            this.textBoxLps1Enable = new System.Windows.Forms.TextBox();
            this.textBoxLps0SyncRst = new System.Windows.Forms.TextBox();
            this.textBoxLps0Disable = new System.Windows.Forms.TextBox();
            this.textBoxLps0Enable = new System.Windows.Forms.TextBox();
            this.labelLpsc0SyncRst = new System.Windows.Forms.Label();
            this.labelLpsc0Disable = new System.Windows.Forms.Label();
            this.labelLpsc0enable = new System.Windows.Forms.Label();
            this.tabPagePinmux = new System.Windows.Forms.TabPage();
            this.textBoxPinmuxVal19 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg20 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux19 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal18 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg19 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux18 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal17 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg18 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux17 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal16 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg17 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux16 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal15 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg16 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux15 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal14 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg15 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux14 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal13 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg14 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux13 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal12 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg13 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux12 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal11 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg12 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux11 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal10 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg11 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux10 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal9 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg10 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux9 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal8 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg9 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux8 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal7 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg8 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux7 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal6 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg7 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux6 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal5 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg6 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux5 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal4 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg5 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux4 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal3 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg4 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux3 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal2 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg3 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux2 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal1 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg2 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux1 = new System.Windows.Forms.NumericUpDown();
            this.textBoxPinmuxVal0 = new System.Windows.Forms.TextBox();
            this.labelPinmuxReg1 = new System.Windows.Forms.Label();
            this.numericUpDownPinmux0 = new System.Windows.Forms.NumericUpDown();
            this.labelAppFile = new System.Windows.Forms.Label();
            this.buttonBrowseFile = new System.Windows.Forms.Button();
            this.textBoxAppFiles = new System.Windows.Forms.TextBox();
            this.buttonAddFile = new System.Windows.Forms.Button();
            this.textBoxAISfile = new System.Windows.Forms.TextBox();
            this.labelAISfile = new System.Windows.Forms.Label();
            this.buttonAISbrowseFile = new System.Windows.Forms.Button();
            this.buttonGenerateAIS = new System.Windows.Forms.Button();
            this.labelMessage = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.tabControlConfig.SuspendLayout();
            this.tabPageGeneral.SuspendLayout();
            this.tabPageFlash.SuspendLayout();
            this.tabPagePeripheral.SuspendLayout();
            this.tabPagePLL0.SuspendLayout();
            this.tabPageSDRAM.SuspendLayout();
            this.tabPagePLL1.SuspendLayout();
            this.tabPageDDR2.SuspendLayout();
            this.tabPageLPSC.SuspendLayout();
            this.tabPagePinmux.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux19)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux18)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux17)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux16)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux15)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux14)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux13)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux12)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux11)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux10)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux9)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux8)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux7)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux6)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux0)).BeginInit();
            this.SuspendLayout();
            // 
            // labelBootType
            // 
            this.labelBootType.AutoSize = true;
            this.labelBootType.Location = new System.Drawing.Point(100, 12);
            this.labelBootType.Name = "labelBootType";
            this.labelBootType.Size = new System.Drawing.Size(71, 13);
            this.labelBootType.TabIndex = 0;
            this.labelBootType.Text = "Device Type:";
            // 
            // labelBootMode
            // 
            this.labelBootMode.AutoSize = true;
            this.labelBootMode.Location = new System.Drawing.Point(100, 39);
            this.labelBootMode.Name = "labelBootMode";
            this.labelBootMode.Size = new System.Drawing.Size(62, 13);
            this.labelBootMode.TabIndex = 1;
            this.labelBootMode.Text = "Boot Mode:";
            // 
            // labelClockSource
            // 
            this.labelClockSource.AutoSize = true;
            this.labelClockSource.Location = new System.Drawing.Point(100, 66);
            this.labelClockSource.Name = "labelClockSource";
            this.labelClockSource.Size = new System.Drawing.Size(74, 13);
            this.labelClockSource.TabIndex = 2;
            this.labelClockSource.Text = "Clock Source:";
            // 
            // comboBoxBootType
            // 
            this.comboBoxBootType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxBootType.FormattingEnabled = true;
            this.comboBoxBootType.Items.AddRange(new object[] {
            "ARM",
            "DSP"});
            this.comboBoxBootType.Location = new System.Drawing.Point(179, 9);
            this.comboBoxBootType.Name = "comboBoxBootType";
            this.comboBoxBootType.Size = new System.Drawing.Size(100, 21);
            this.comboBoxBootType.TabIndex = 3;
            this.comboBoxBootType.SelectedIndexChanged += new System.EventHandler(this.comboBoxBootType_SelectedIndexChanged);
            // 
            // comboBoxBootMode
            // 
            this.comboBoxBootMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxBootMode.FormattingEnabled = true;
            this.comboBoxBootMode.Items.AddRange(new object[] {
            "NOR Flash",
            "NAND Flash",
            "SPI0 Flash",
            "SPI1 Flash",
            "I2C0 EEPROM",
            "I2C1 EEPROM",
            "SPI0 EEPROM",
            "SPI1 EEPROM",
            "I2C0 Slave",
            "I2C1 Slave",
            "SPI0 Slave",
            "SPI1 Slave",
            "UART0",
            "UART1",
            "UART2"});
            this.comboBoxBootMode.Location = new System.Drawing.Point(180, 36);
            this.comboBoxBootMode.MaxDropDownItems = 16;
            this.comboBoxBootMode.Name = "comboBoxBootMode";
            this.comboBoxBootMode.Size = new System.Drawing.Size(100, 21);
            this.comboBoxBootMode.TabIndex = 4;
            this.comboBoxBootMode.SelectedIndexChanged += new System.EventHandler(this.comboBoxBootMode_SelectedIndexChanged);
            // 
            // comboBoxClockSource
            // 
            this.comboBoxClockSource.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxClockSource.FormattingEnabled = true;
            this.comboBoxClockSource.Items.AddRange(new object[] {
            "Crystal",
            "Oscillator"});
            this.comboBoxClockSource.Location = new System.Drawing.Point(180, 63);
            this.comboBoxClockSource.Name = "comboBoxClockSource";
            this.comboBoxClockSource.Size = new System.Drawing.Size(100, 21);
            this.comboBoxClockSource.TabIndex = 5;
            this.comboBoxClockSource.SelectedIndexChanged += new System.EventHandler(this.comboBoxClockSource_SelectedIndexChanged);
            // 
            // textBoxClockSpeed
            // 
            this.textBoxClockSpeed.Location = new System.Drawing.Point(286, 63);
            this.textBoxClockSpeed.MaxLength = 6;
            this.textBoxClockSpeed.Name = "textBoxClockSpeed";
            this.textBoxClockSpeed.Size = new System.Drawing.Size(40, 20);
            this.textBoxClockSpeed.TabIndex = 6;
            this.textBoxClockSpeed.Text = "24.00";
            this.textBoxClockSpeed.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxClockSpeed.TextChanged += new System.EventHandler(this.textBoxClockSpeed_TextChanged);
            // 
            // labelInputClockMHz
            // 
            this.labelInputClockMHz.AutoSize = true;
            this.labelInputClockMHz.Location = new System.Drawing.Point(346, 66);
            this.labelInputClockMHz.Name = "labelInputClockMHz";
            this.labelInputClockMHz.Size = new System.Drawing.Size(29, 13);
            this.labelInputClockMHz.TabIndex = 7;
            this.labelInputClockMHz.Text = "MHz";
            // 
            // checkBoxPLL0
            // 
            this.checkBoxPLL0.AutoSize = true;
            this.checkBoxPLL0.Location = new System.Drawing.Point(103, 90);
            this.checkBoxPLL0.Name = "checkBoxPLL0";
            this.checkBoxPLL0.Size = new System.Drawing.Size(99, 17);
            this.checkBoxPLL0.TabIndex = 8;
            this.checkBoxPLL0.Text = "Configure PLL0";
            this.checkBoxPLL0.UseVisualStyleBackColor = true;
            this.checkBoxPLL0.CheckedChanged += new System.EventHandler(this.checkBoxPLL0_CheckedChanged);
            // 
            // checkBoxDDR2
            // 
            this.checkBoxDDR2.AutoSize = true;
            this.checkBoxDDR2.Location = new System.Drawing.Point(223, 112);
            this.checkBoxDDR2.Name = "checkBoxDDR2";
            this.checkBoxDDR2.Size = new System.Drawing.Size(104, 17);
            this.checkBoxDDR2.TabIndex = 9;
            this.checkBoxDDR2.Text = "Configure DDR2";
            this.checkBoxDDR2.UseVisualStyleBackColor = true;
            this.checkBoxDDR2.CheckedChanged += new System.EventHandler(this.checkBoxDDR2_CheckedChanged);
            // 
            // checkBoxSDRAM
            // 
            this.checkBoxSDRAM.AutoSize = true;
            this.checkBoxSDRAM.Location = new System.Drawing.Point(103, 113);
            this.checkBoxSDRAM.Name = "checkBoxSDRAM";
            this.checkBoxSDRAM.Size = new System.Drawing.Size(113, 17);
            this.checkBoxSDRAM.TabIndex = 10;
            this.checkBoxSDRAM.Text = "Configure SDRAM";
            this.checkBoxSDRAM.UseVisualStyleBackColor = true;
            this.checkBoxSDRAM.CheckedChanged += new System.EventHandler(this.checkBoxSDRAM_CheckedChanged);
            // 
            // checkBoxCRC
            // 
            this.checkBoxCRC.AutoSize = true;
            this.checkBoxCRC.Location = new System.Drawing.Point(103, 159);
            this.checkBoxCRC.Name = "checkBoxCRC";
            this.checkBoxCRC.Size = new System.Drawing.Size(84, 17);
            this.checkBoxCRC.TabIndex = 11;
            this.checkBoxCRC.Text = "Enable CRC";
            this.checkBoxCRC.UseVisualStyleBackColor = true;
            this.checkBoxCRC.CheckedChanged += new System.EventHandler(this.checkBoxCRC_CheckedChanged);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(506, 24);
            this.menuStrip1.TabIndex = 13;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.restoreDefaultsToolStripMenuItem,
            this.saveConfigToolStripMenuItem,
            this.loadConfigToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // restoreDefaultsToolStripMenuItem
            // 
            this.restoreDefaultsToolStripMenuItem.Name = "restoreDefaultsToolStripMenuItem";
            this.restoreDefaultsToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.restoreDefaultsToolStripMenuItem.Text = "Restore Defaults";
            this.restoreDefaultsToolStripMenuItem.Click += new System.EventHandler(this.restoreDefaultsToolStripMenuItem_Click);
            // 
            // saveConfigToolStripMenuItem
            // 
            this.saveConfigToolStripMenuItem.Name = "saveConfigToolStripMenuItem";
            this.saveConfigToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.saveConfigToolStripMenuItem.Text = "Save Configuration";
            this.saveConfigToolStripMenuItem.Click += new System.EventHandler(this.saveConfigToolStripMenuItem_Click);
            // 
            // loadConfigToolStripMenuItem
            // 
            this.loadConfigToolStripMenuItem.Name = "loadConfigToolStripMenuItem";
            this.loadConfigToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.loadConfigToolStripMenuItem.Text = "Load Configuration";
            this.loadConfigToolStripMenuItem.Click += new System.EventHandler(this.loadConfigToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // tabControlConfig
            // 
            this.tabControlConfig.Controls.Add(this.tabPageGeneral);
            this.tabControlConfig.Controls.Add(this.tabPageFlash);
            this.tabControlConfig.Controls.Add(this.tabPagePeripheral);
            this.tabControlConfig.Controls.Add(this.tabPagePLL0);
            this.tabControlConfig.Controls.Add(this.tabPageSDRAM);
            this.tabControlConfig.Controls.Add(this.tabPagePLL1);
            this.tabControlConfig.Controls.Add(this.tabPageDDR2);
            this.tabControlConfig.Controls.Add(this.tabPageLPSC);
            this.tabControlConfig.Controls.Add(this.tabPagePinmux);
            this.tabControlConfig.Location = new System.Drawing.Point(12, 27);
            this.tabControlConfig.Name = "tabControlConfig";
            this.tabControlConfig.SelectedIndex = 0;
            this.tabControlConfig.Size = new System.Drawing.Size(482, 235);
            this.tabControlConfig.TabIndex = 14;
            // 
            // tabPageGeneral
            // 
            this.tabPageGeneral.Controls.Add(this.checkBoxLPSC);
            this.tabPageGeneral.Controls.Add(this.checkBoxPinmux);
            this.tabPageGeneral.Controls.Add(this.checkBoxPLL1);
            this.tabPageGeneral.Controls.Add(this.comboBoxBootMode);
            this.tabPageGeneral.Controls.Add(this.labelBootType);
            this.tabPageGeneral.Controls.Add(this.checkBoxCRC);
            this.tabPageGeneral.Controls.Add(this.labelBootMode);
            this.tabPageGeneral.Controls.Add(this.textBoxSpecifyEntrypoint);
            this.tabPageGeneral.Controls.Add(this.checkBoxSDRAM);
            this.tabPageGeneral.Controls.Add(this.checkBoxSpecifyEntrypoint);
            this.tabPageGeneral.Controls.Add(this.labelClockSource);
            this.tabPageGeneral.Controls.Add(this.checkBoxDDR2);
            this.tabPageGeneral.Controls.Add(this.comboBoxBootType);
            this.tabPageGeneral.Controls.Add(this.checkBoxPLL0);
            this.tabPageGeneral.Controls.Add(this.comboBoxClockSource);
            this.tabPageGeneral.Controls.Add(this.labelInputClockMHz);
            this.tabPageGeneral.Controls.Add(this.textBoxClockSpeed);
            this.tabPageGeneral.Location = new System.Drawing.Point(4, 22);
            this.tabPageGeneral.Name = "tabPageGeneral";
            this.tabPageGeneral.Size = new System.Drawing.Size(474, 209);
            this.tabPageGeneral.TabIndex = 5;
            this.tabPageGeneral.Text = "General";
            this.tabPageGeneral.UseVisualStyleBackColor = true;
            // 
            // checkBoxLPSC
            // 
            this.checkBoxLPSC.AutoSize = true;
            this.checkBoxLPSC.Location = new System.Drawing.Point(103, 136);
            this.checkBoxLPSC.Name = "checkBoxLPSC";
            this.checkBoxLPSC.Size = new System.Drawing.Size(95, 17);
            this.checkBoxLPSC.TabIndex = 22;
            this.checkBoxLPSC.Text = "Configure PSC";
            this.checkBoxLPSC.UseVisualStyleBackColor = true;
            this.checkBoxLPSC.CheckedChanged += new System.EventHandler(this.checkBoxLPSC_CheckedChanged);
            // 
            // checkBoxPinmux
            // 
            this.checkBoxPinmux.AutoSize = true;
            this.checkBoxPinmux.Location = new System.Drawing.Point(223, 135);
            this.checkBoxPinmux.Name = "checkBoxPinmux";
            this.checkBoxPinmux.Size = new System.Drawing.Size(108, 17);
            this.checkBoxPinmux.TabIndex = 21;
            this.checkBoxPinmux.Text = "Configure Pinmux";
            this.checkBoxPinmux.UseVisualStyleBackColor = true;
            this.checkBoxPinmux.CheckedChanged += new System.EventHandler(this.checkBoxPinmux_CheckedChanged);
            // 
            // checkBoxPLL1
            // 
            this.checkBoxPLL1.AutoSize = true;
            this.checkBoxPLL1.Location = new System.Drawing.Point(223, 89);
            this.checkBoxPLL1.Name = "checkBoxPLL1";
            this.checkBoxPLL1.Size = new System.Drawing.Size(99, 17);
            this.checkBoxPLL1.TabIndex = 13;
            this.checkBoxPLL1.Text = "Configure PLL1";
            this.checkBoxPLL1.UseVisualStyleBackColor = true;
            this.checkBoxPLL1.CheckedChanged += new System.EventHandler(this.checkBoxPLL1_CheckedChanged);
            // 
            // textBoxSpecifyEntrypoint
            // 
            this.textBoxSpecifyEntrypoint.Enabled = false;
            this.textBoxSpecifyEntrypoint.Location = new System.Drawing.Point(223, 179);
            this.textBoxSpecifyEntrypoint.MaxLength = 10;
            this.textBoxSpecifyEntrypoint.Name = "textBoxSpecifyEntrypoint";
            this.textBoxSpecifyEntrypoint.Size = new System.Drawing.Size(80, 20);
            this.textBoxSpecifyEntrypoint.TabIndex = 20;
            this.textBoxSpecifyEntrypoint.Text = "0x00000000";
            this.textBoxSpecifyEntrypoint.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxSpecifyEntrypoint.TextChanged += new System.EventHandler(this.textBoxSpecifyEntrypoint_TextChanged);
            // 
            // checkBoxSpecifyEntrypoint
            // 
            this.checkBoxSpecifyEntrypoint.AutoSize = true;
            this.checkBoxSpecifyEntrypoint.Location = new System.Drawing.Point(103, 182);
            this.checkBoxSpecifyEntrypoint.Name = "checkBoxSpecifyEntrypoint";
            this.checkBoxSpecifyEntrypoint.Size = new System.Drawing.Size(114, 17);
            this.checkBoxSpecifyEntrypoint.TabIndex = 19;
            this.checkBoxSpecifyEntrypoint.Text = "Specify Entrypoint:";
            this.checkBoxSpecifyEntrypoint.UseVisualStyleBackColor = true;
            this.checkBoxSpecifyEntrypoint.CheckedChanged += new System.EventHandler(this.checkBoxSpecifyEntrypoint_CheckedChanged);
            // 
            // tabPageFlash
            // 
            this.tabPageFlash.Controls.Add(this.textBoxFlashTiming);
            this.tabPageFlash.Controls.Add(this.labelFlashTiming);
            this.tabPageFlash.Controls.Add(this.labelFlashWidth);
            this.tabPageFlash.Controls.Add(this.comboBoxFlashWidth);
            this.tabPageFlash.Location = new System.Drawing.Point(4, 22);
            this.tabPageFlash.Name = "tabPageFlash";
            this.tabPageFlash.Size = new System.Drawing.Size(474, 209);
            this.tabPageFlash.TabIndex = 8;
            this.tabPageFlash.Text = "Flash";
            this.tabPageFlash.UseVisualStyleBackColor = true;
            // 
            // textBoxFlashTiming
            // 
            this.textBoxFlashTiming.Location = new System.Drawing.Point(232, 108);
            this.textBoxFlashTiming.MaxLength = 10;
            this.textBoxFlashTiming.Name = "textBoxFlashTiming";
            this.textBoxFlashTiming.Size = new System.Drawing.Size(80, 20);
            this.textBoxFlashTiming.TabIndex = 27;
            this.textBoxFlashTiming.Text = "0x00000000";
            this.textBoxFlashTiming.TextChanged += new System.EventHandler(this.textBoxFlashTiming_TextChanged);
            // 
            // labelFlashTiming
            // 
            this.labelFlashTiming.AutoSize = true;
            this.labelFlashTiming.Location = new System.Drawing.Point(162, 111);
            this.labelFlashTiming.Name = "labelFlashTiming";
            this.labelFlashTiming.Size = new System.Drawing.Size(61, 13);
            this.labelFlashTiming.TabIndex = 25;
            this.labelFlashTiming.Text = "CS3 Setup:";
            // 
            // labelFlashWidth
            // 
            this.labelFlashWidth.AutoSize = true;
            this.labelFlashWidth.Location = new System.Drawing.Point(162, 84);
            this.labelFlashWidth.Name = "labelFlashWidth";
            this.labelFlashWidth.Size = new System.Drawing.Size(64, 13);
            this.labelFlashWidth.TabIndex = 4;
            this.labelFlashWidth.Text = "Data Width:";
            // 
            // comboBoxFlashWidth
            // 
            this.comboBoxFlashWidth.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxFlashWidth.FormattingEnabled = true;
            this.comboBoxFlashWidth.Items.AddRange(new object[] {
            "8-bit",
            "16-bit"});
            this.comboBoxFlashWidth.Location = new System.Drawing.Point(232, 81);
            this.comboBoxFlashWidth.Name = "comboBoxFlashWidth";
            this.comboBoxFlashWidth.Size = new System.Drawing.Size(80, 21);
            this.comboBoxFlashWidth.TabIndex = 5;
            this.comboBoxFlashWidth.SelectedIndexChanged += new System.EventHandler(this.comboBoxFlashWidth_SelectedIndexChanged);
            // 
            // tabPagePeripheral
            // 
            this.tabPagePeripheral.Controls.Add(this.checkBoxPeriphSeqRead);
            this.tabPagePeripheral.Controls.Add(this.textBoxPeriphClockActual);
            this.tabPagePeripheral.Controls.Add(this.labelPeriphClockHz);
            this.tabPagePeripheral.Controls.Add(this.labelPeriphClock);
            this.tabPagePeripheral.Controls.Add(this.textBoxPeriphClockIdeal);
            this.tabPagePeripheral.Controls.Add(this.labelPeriphModuleClockMHz);
            this.tabPagePeripheral.Controls.Add(this.labelPeriphModuleClock);
            this.tabPagePeripheral.Controls.Add(this.textBoxPeriphModuleClock);
            this.tabPagePeripheral.Location = new System.Drawing.Point(4, 22);
            this.tabPagePeripheral.Name = "tabPagePeripheral";
            this.tabPagePeripheral.Padding = new System.Windows.Forms.Padding(3);
            this.tabPagePeripheral.Size = new System.Drawing.Size(474, 209);
            this.tabPagePeripheral.TabIndex = 0;
            this.tabPagePeripheral.Text = "Peripheral";
            this.tabPagePeripheral.UseVisualStyleBackColor = true;
            // 
            // checkBoxPeriphSeqRead
            // 
            this.checkBoxPeriphSeqRead.AutoSize = true;
            this.checkBoxPeriphSeqRead.Location = new System.Drawing.Point(189, 122);
            this.checkBoxPeriphSeqRead.Name = "checkBoxPeriphSeqRead";
            this.checkBoxPeriphSeqRead.Size = new System.Drawing.Size(141, 17);
            this.checkBoxPeriphSeqRead.TabIndex = 26;
            this.checkBoxPeriphSeqRead.Text = "Enable Sequential Read";
            this.checkBoxPeriphSeqRead.UseVisualStyleBackColor = true;
            this.checkBoxPeriphSeqRead.CheckedChanged += new System.EventHandler(this.checkBoxPeriphSeqRead_CheckedChanged);
            // 
            // textBoxPeriphClockActual
            // 
            this.textBoxPeriphClockActual.Location = new System.Drawing.Point(269, 96);
            this.textBoxPeriphClockActual.Name = "textBoxPeriphClockActual";
            this.textBoxPeriphClockActual.ReadOnly = true;
            this.textBoxPeriphClockActual.Size = new System.Drawing.Size(60, 20);
            this.textBoxPeriphClockActual.TabIndex = 25;
            this.textBoxPeriphClockActual.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // labelPeriphClockHz
            // 
            this.labelPeriphClockHz.AutoSize = true;
            this.labelPeriphClockHz.Location = new System.Drawing.Point(335, 99);
            this.labelPeriphClockHz.Name = "labelPeriphClockHz";
            this.labelPeriphClockHz.Size = new System.Drawing.Size(31, 13);
            this.labelPeriphClockHz.TabIndex = 24;
            this.labelPeriphClockHz.Text = "baud";
            // 
            // labelPeriphClock
            // 
            this.labelPeriphClock.AutoSize = true;
            this.labelPeriphClock.Location = new System.Drawing.Point(108, 99);
            this.labelPeriphClock.Name = "labelPeriphClock";
            this.labelPeriphClock.Size = new System.Drawing.Size(76, 13);
            this.labelPeriphClock.TabIndex = 23;
            this.labelPeriphClock.Text = "[Periph] Clock:";
            // 
            // textBoxPeriphClockIdeal
            // 
            this.textBoxPeriphClockIdeal.Location = new System.Drawing.Point(189, 96);
            this.textBoxPeriphClockIdeal.Name = "textBoxPeriphClockIdeal";
            this.textBoxPeriphClockIdeal.Size = new System.Drawing.Size(60, 20);
            this.textBoxPeriphClockIdeal.TabIndex = 22;
            this.textBoxPeriphClockIdeal.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPeriphClockIdeal.TextChanged += new System.EventHandler(this.textBoxPeriphClockIdeal_TextChanged);
            // 
            // labelPeriphModuleClockMHz
            // 
            this.labelPeriphModuleClockMHz.AutoSize = true;
            this.labelPeriphModuleClockMHz.Location = new System.Drawing.Point(269, 73);
            this.labelPeriphModuleClockMHz.Name = "labelPeriphModuleClockMHz";
            this.labelPeriphModuleClockMHz.Size = new System.Drawing.Size(29, 13);
            this.labelPeriphModuleClockMHz.TabIndex = 21;
            this.labelPeriphModuleClockMHz.Text = "MHz";
            // 
            // labelPeriphModuleClock
            // 
            this.labelPeriphModuleClock.AutoSize = true;
            this.labelPeriphModuleClock.Location = new System.Drawing.Point(108, 73);
            this.labelPeriphModuleClock.Name = "labelPeriphModuleClock";
            this.labelPeriphModuleClock.Size = new System.Drawing.Size(75, 13);
            this.labelPeriphModuleClock.TabIndex = 20;
            this.labelPeriphModuleClock.Text = "Module Clock:";
            // 
            // textBoxPeriphModuleClock
            // 
            this.textBoxPeriphModuleClock.Location = new System.Drawing.Point(189, 70);
            this.textBoxPeriphModuleClock.Name = "textBoxPeriphModuleClock";
            this.textBoxPeriphModuleClock.ReadOnly = true;
            this.textBoxPeriphModuleClock.Size = new System.Drawing.Size(60, 20);
            this.textBoxPeriphModuleClock.TabIndex = 19;
            this.textBoxPeriphModuleClock.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // tabPagePLL0
            // 
            this.tabPagePLL0.Controls.Add(this.labelPLL0emacMHz);
            this.tabPagePLL0.Controls.Add(this.labelPLL0sdramMHz);
            this.tabPagePLL0.Controls.Add(this.labelPLL0cpuMHz);
            this.tabPagePLL0.Controls.Add(this.labelPLL0emac);
            this.tabPagePLL0.Controls.Add(this.textBoxPLL0emac);
            this.tabPagePLL0.Controls.Add(this.labelPLL0sdram);
            this.tabPagePLL0.Controls.Add(this.textBoxPLL0sdram);
            this.tabPagePLL0.Controls.Add(this.labelPLL0cpu);
            this.tabPagePLL0.Controls.Add(this.textBoxPLL0cpu);
            this.tabPagePLL0.Controls.Add(this.labelPLL0div7);
            this.tabPagePLL0.Controls.Add(this.textBoxPLL0div7);
            this.tabPagePLL0.Controls.Add(this.labelPLL0div3);
            this.tabPagePLL0.Controls.Add(this.textBoxPLL0div3);
            this.tabPagePLL0.Controls.Add(this.label1);
            this.tabPagePLL0.Controls.Add(this.textBoxPLL0div1);
            this.tabPagePLL0.Controls.Add(this.labelPLL0postDiv);
            this.tabPagePLL0.Controls.Add(this.textBoxPLL0postDiv);
            this.tabPagePLL0.Controls.Add(this.labelPLL0preDiv);
            this.tabPagePLL0.Controls.Add(this.textBoxPLL0preDiv);
            this.tabPagePLL0.Controls.Add(this.labelPLL0mult);
            this.tabPagePLL0.Controls.Add(this.textBoxPLL0mult);
            this.tabPagePLL0.Location = new System.Drawing.Point(4, 22);
            this.tabPagePLL0.Name = "tabPagePLL0";
            this.tabPagePLL0.Padding = new System.Windows.Forms.Padding(3);
            this.tabPagePLL0.Size = new System.Drawing.Size(474, 209);
            this.tabPagePLL0.TabIndex = 1;
            this.tabPagePLL0.Text = "PLL0";
            this.tabPagePLL0.UseVisualStyleBackColor = true;
            // 
            // labelPLL0emacMHz
            // 
            this.labelPLL0emacMHz.AutoSize = true;
            this.labelPLL0emacMHz.Location = new System.Drawing.Point(362, 162);
            this.labelPLL0emacMHz.Name = "labelPLL0emacMHz";
            this.labelPLL0emacMHz.Size = new System.Drawing.Size(29, 13);
            this.labelPLL0emacMHz.TabIndex = 20;
            this.labelPLL0emacMHz.Text = "MHz";
            // 
            // labelPLL0sdramMHz
            // 
            this.labelPLL0sdramMHz.AutoSize = true;
            this.labelPLL0sdramMHz.Location = new System.Drawing.Point(362, 136);
            this.labelPLL0sdramMHz.Name = "labelPLL0sdramMHz";
            this.labelPLL0sdramMHz.Size = new System.Drawing.Size(29, 13);
            this.labelPLL0sdramMHz.TabIndex = 19;
            this.labelPLL0sdramMHz.Text = "MHz";
            // 
            // labelPLL0cpuMHz
            // 
            this.labelPLL0cpuMHz.AutoSize = true;
            this.labelPLL0cpuMHz.Location = new System.Drawing.Point(362, 110);
            this.labelPLL0cpuMHz.Name = "labelPLL0cpuMHz";
            this.labelPLL0cpuMHz.Size = new System.Drawing.Size(29, 13);
            this.labelPLL0cpuMHz.TabIndex = 18;
            this.labelPLL0cpuMHz.Text = "MHz";
            // 
            // labelPLL0emac
            // 
            this.labelPLL0emac.AutoSize = true;
            this.labelPLL0emac.Location = new System.Drawing.Point(247, 162);
            this.labelPLL0emac.Name = "labelPLL0emac";
            this.labelPLL0emac.Size = new System.Drawing.Size(40, 13);
            this.labelPLL0emac.TabIndex = 17;
            this.labelPLL0emac.Text = "EMAC:";
            // 
            // textBoxPLL0emac
            // 
            this.textBoxPLL0emac.Location = new System.Drawing.Point(302, 159);
            this.textBoxPLL0emac.Name = "textBoxPLL0emac";
            this.textBoxPLL0emac.ReadOnly = true;
            this.textBoxPLL0emac.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL0emac.TabIndex = 16;
            this.textBoxPLL0emac.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // labelPLL0sdram
            // 
            this.labelPLL0sdram.AutoSize = true;
            this.labelPLL0sdram.Location = new System.Drawing.Point(247, 136);
            this.labelPLL0sdram.Name = "labelPLL0sdram";
            this.labelPLL0sdram.Size = new System.Drawing.Size(49, 13);
            this.labelPLL0sdram.TabIndex = 15;
            this.labelPLL0sdram.Text = "SDRAM:";
            // 
            // textBoxPLL0sdram
            // 
            this.textBoxPLL0sdram.Location = new System.Drawing.Point(302, 133);
            this.textBoxPLL0sdram.Name = "textBoxPLL0sdram";
            this.textBoxPLL0sdram.ReadOnly = true;
            this.textBoxPLL0sdram.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL0sdram.TabIndex = 14;
            this.textBoxPLL0sdram.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // labelPLL0cpu
            // 
            this.labelPLL0cpu.AutoSize = true;
            this.labelPLL0cpu.Location = new System.Drawing.Point(247, 110);
            this.labelPLL0cpu.Name = "labelPLL0cpu";
            this.labelPLL0cpu.Size = new System.Drawing.Size(32, 13);
            this.labelPLL0cpu.TabIndex = 13;
            this.labelPLL0cpu.Text = "CPU:";
            // 
            // textBoxPLL0cpu
            // 
            this.textBoxPLL0cpu.Location = new System.Drawing.Point(302, 107);
            this.textBoxPLL0cpu.Name = "textBoxPLL0cpu";
            this.textBoxPLL0cpu.ReadOnly = true;
            this.textBoxPLL0cpu.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL0cpu.TabIndex = 12;
            this.textBoxPLL0cpu.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // labelPLL0div7
            // 
            this.labelPLL0div7.AutoSize = true;
            this.labelPLL0div7.Location = new System.Drawing.Point(84, 162);
            this.labelPLL0div7.Name = "labelPLL0div7";
            this.labelPLL0div7.Size = new System.Drawing.Size(34, 13);
            this.labelPLL0div7.TabIndex = 11;
            this.labelPLL0div7.Text = "DIV7:";
            // 
            // textBoxPLL0div7
            // 
            this.textBoxPLL0div7.Location = new System.Drawing.Point(156, 159);
            this.textBoxPLL0div7.Name = "textBoxPLL0div7";
            this.textBoxPLL0div7.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL0div7.TabIndex = 10;
            this.textBoxPLL0div7.Text = "6";
            this.textBoxPLL0div7.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL0div7.TextChanged += new System.EventHandler(this.textBoxPLL0div7_TextChanged);
            // 
            // labelPLL0div3
            // 
            this.labelPLL0div3.AutoSize = true;
            this.labelPLL0div3.Location = new System.Drawing.Point(84, 136);
            this.labelPLL0div3.Name = "labelPLL0div3";
            this.labelPLL0div3.Size = new System.Drawing.Size(34, 13);
            this.labelPLL0div3.TabIndex = 9;
            this.labelPLL0div3.Text = "DIV3:";
            // 
            // textBoxPLL0div3
            // 
            this.textBoxPLL0div3.Location = new System.Drawing.Point(156, 133);
            this.textBoxPLL0div3.Name = "textBoxPLL0div3";
            this.textBoxPLL0div3.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL0div3.TabIndex = 8;
            this.textBoxPLL0div3.Text = "3";
            this.textBoxPLL0div3.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL0div3.TextChanged += new System.EventHandler(this.textBoxPLL0div3_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(84, 110);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "DIV1:";
            // 
            // textBoxPLL0div1
            // 
            this.textBoxPLL0div1.Location = new System.Drawing.Point(156, 107);
            this.textBoxPLL0div1.Name = "textBoxPLL0div1";
            this.textBoxPLL0div1.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL0div1.TabIndex = 6;
            this.textBoxPLL0div1.Text = "1";
            this.textBoxPLL0div1.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL0div1.TextChanged += new System.EventHandler(this.textBoxPLL0div1_TextChanged);
            // 
            // labelPLL0postDiv
            // 
            this.labelPLL0postDiv.AutoSize = true;
            this.labelPLL0postDiv.Location = new System.Drawing.Point(84, 84);
            this.labelPLL0postDiv.Name = "labelPLL0postDiv";
            this.labelPLL0postDiv.Size = new System.Drawing.Size(66, 13);
            this.labelPLL0postDiv.TabIndex = 5;
            this.labelPLL0postDiv.Text = "Post-Divisor:";
            // 
            // textBoxPLL0postDiv
            // 
            this.textBoxPLL0postDiv.Location = new System.Drawing.Point(156, 81);
            this.textBoxPLL0postDiv.Name = "textBoxPLL0postDiv";
            this.textBoxPLL0postDiv.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL0postDiv.TabIndex = 4;
            this.textBoxPLL0postDiv.Text = "2";
            this.textBoxPLL0postDiv.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL0postDiv.TextChanged += new System.EventHandler(this.textBoxPLL0postDiv_TextChanged);
            // 
            // labelPLL0preDiv
            // 
            this.labelPLL0preDiv.AutoSize = true;
            this.labelPLL0preDiv.Location = new System.Drawing.Point(84, 32);
            this.labelPLL0preDiv.Name = "labelPLL0preDiv";
            this.labelPLL0preDiv.Size = new System.Drawing.Size(61, 13);
            this.labelPLL0preDiv.TabIndex = 3;
            this.labelPLL0preDiv.Text = "Pre-Divisor:";
            // 
            // textBoxPLL0preDiv
            // 
            this.textBoxPLL0preDiv.Location = new System.Drawing.Point(156, 29);
            this.textBoxPLL0preDiv.Name = "textBoxPLL0preDiv";
            this.textBoxPLL0preDiv.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL0preDiv.TabIndex = 2;
            this.textBoxPLL0preDiv.Text = "1";
            this.textBoxPLL0preDiv.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL0preDiv.TextChanged += new System.EventHandler(this.textBoxPLL0preDiv_TextChanged);
            // 
            // labelPLL0mult
            // 
            this.labelPLL0mult.AutoSize = true;
            this.labelPLL0mult.Location = new System.Drawing.Point(84, 58);
            this.labelPLL0mult.Name = "labelPLL0mult";
            this.labelPLL0mult.Size = new System.Drawing.Size(51, 13);
            this.labelPLL0mult.TabIndex = 1;
            this.labelPLL0mult.Text = "Multiplier:";
            // 
            // textBoxPLL0mult
            // 
            this.textBoxPLL0mult.Location = new System.Drawing.Point(156, 55);
            this.textBoxPLL0mult.Name = "textBoxPLL0mult";
            this.textBoxPLL0mult.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL0mult.TabIndex = 0;
            this.textBoxPLL0mult.Text = "20";
            this.textBoxPLL0mult.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL0mult.TextChanged += new System.EventHandler(this.textBoxPLL0mult_TextChanged);
            // 
            // tabPageSDRAM
            // 
            this.tabPageSDRAM.Controls.Add(this.labelSDRAMsdrcr);
            this.tabPageSDRAM.Controls.Add(this.textBoxSDRAMsdrcr);
            this.tabPageSDRAM.Controls.Add(this.labelSDRAMsdrsrpdexit);
            this.tabPageSDRAM.Controls.Add(this.textBoxSDRAMsdrsrpdexit);
            this.tabPageSDRAM.Controls.Add(this.labelSDRAMsdtmr);
            this.tabPageSDRAM.Controls.Add(this.textBoxSDRAMsdtmr);
            this.tabPageSDRAM.Controls.Add(this.labelSDRAMsdbcr);
            this.tabPageSDRAM.Controls.Add(this.textBoxSDRAMsdbcr);
            this.tabPageSDRAM.Controls.Add(this.checkBoxSDRAMdiv);
            this.tabPageSDRAM.Controls.Add(this.labelSDRAMclockMHz);
            this.tabPageSDRAM.Controls.Add(this.labelSDRAMclock);
            this.tabPageSDRAM.Controls.Add(this.textBoxSDRAMclock);
            this.tabPageSDRAM.Location = new System.Drawing.Point(4, 22);
            this.tabPageSDRAM.Name = "tabPageSDRAM";
            this.tabPageSDRAM.Size = new System.Drawing.Size(474, 209);
            this.tabPageSDRAM.TabIndex = 4;
            this.tabPageSDRAM.Text = "SDRAM";
            this.tabPageSDRAM.UseVisualStyleBackColor = true;
            // 
            // labelSDRAMsdrcr
            // 
            this.labelSDRAMsdrcr.AutoSize = true;
            this.labelSDRAMsdrcr.Location = new System.Drawing.Point(145, 161);
            this.labelSDRAMsdrcr.Name = "labelSDRAMsdrcr";
            this.labelSDRAMsdrcr.Size = new System.Drawing.Size(48, 13);
            this.labelSDRAMsdrcr.TabIndex = 33;
            this.labelSDRAMsdrcr.Text = "SDRCR:";
            // 
            // textBoxSDRAMsdrcr
            // 
            this.textBoxSDRAMsdrcr.Location = new System.Drawing.Point(230, 158);
            this.textBoxSDRAMsdrcr.MaxLength = 10;
            this.textBoxSDRAMsdrcr.Name = "textBoxSDRAMsdrcr";
            this.textBoxSDRAMsdrcr.Size = new System.Drawing.Size(80, 20);
            this.textBoxSDRAMsdrcr.TabIndex = 32;
            this.textBoxSDRAMsdrcr.Text = "0x00000000";
            this.textBoxSDRAMsdrcr.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxSDRAMsdrcr.TextChanged += new System.EventHandler(this.textBoxSDRAMsdrcr_TextChanged);
            // 
            // labelSDRAMsdrsrpdexit
            // 
            this.labelSDRAMsdrsrpdexit.AutoSize = true;
            this.labelSDRAMsdrsrpdexit.Location = new System.Drawing.Point(145, 135);
            this.labelSDRAMsdrsrpdexit.Name = "labelSDRAMsdrsrpdexit";
            this.labelSDRAMsdrsrpdexit.Size = new System.Drawing.Size(62, 13);
            this.labelSDRAMsdrsrpdexit.TabIndex = 31;
            this.labelSDRAMsdrsrpdexit.Text = "SDSRETR:";
            // 
            // textBoxSDRAMsdrsrpdexit
            // 
            this.textBoxSDRAMsdrsrpdexit.Location = new System.Drawing.Point(230, 132);
            this.textBoxSDRAMsdrsrpdexit.MaxLength = 10;
            this.textBoxSDRAMsdrsrpdexit.Name = "textBoxSDRAMsdrsrpdexit";
            this.textBoxSDRAMsdrsrpdexit.Size = new System.Drawing.Size(80, 20);
            this.textBoxSDRAMsdrsrpdexit.TabIndex = 30;
            this.textBoxSDRAMsdrsrpdexit.Text = "0x00000000";
            this.textBoxSDRAMsdrsrpdexit.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxSDRAMsdrsrpdexit.TextChanged += new System.EventHandler(this.textBoxSDRAMsdrsrpdexit_TextChanged);
            // 
            // labelSDRAMsdtmr
            // 
            this.labelSDRAMsdtmr.AutoSize = true;
            this.labelSDRAMsdtmr.Location = new System.Drawing.Point(145, 109);
            this.labelSDRAMsdtmr.Name = "labelSDRAMsdtmr";
            this.labelSDRAMsdtmr.Size = new System.Drawing.Size(49, 13);
            this.labelSDRAMsdtmr.TabIndex = 29;
            this.labelSDRAMsdtmr.Text = "SDTMR:";
            // 
            // textBoxSDRAMsdtmr
            // 
            this.textBoxSDRAMsdtmr.Location = new System.Drawing.Point(230, 106);
            this.textBoxSDRAMsdtmr.MaxLength = 10;
            this.textBoxSDRAMsdtmr.Name = "textBoxSDRAMsdtmr";
            this.textBoxSDRAMsdtmr.Size = new System.Drawing.Size(80, 20);
            this.textBoxSDRAMsdtmr.TabIndex = 28;
            this.textBoxSDRAMsdtmr.Text = "0x00000000";
            this.textBoxSDRAMsdtmr.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxSDRAMsdtmr.TextChanged += new System.EventHandler(this.textBoxSDRAMsdtmr_TextChanged);
            // 
            // labelSDRAMsdbcr
            // 
            this.labelSDRAMsdbcr.AutoSize = true;
            this.labelSDRAMsdbcr.Location = new System.Drawing.Point(145, 83);
            this.labelSDRAMsdbcr.Name = "labelSDRAMsdbcr";
            this.labelSDRAMsdbcr.Size = new System.Drawing.Size(40, 13);
            this.labelSDRAMsdbcr.TabIndex = 27;
            this.labelSDRAMsdbcr.Text = "SDCR:";
            // 
            // textBoxSDRAMsdbcr
            // 
            this.textBoxSDRAMsdbcr.Location = new System.Drawing.Point(230, 80);
            this.textBoxSDRAMsdbcr.MaxLength = 10;
            this.textBoxSDRAMsdbcr.Name = "textBoxSDRAMsdbcr";
            this.textBoxSDRAMsdbcr.Size = new System.Drawing.Size(80, 20);
            this.textBoxSDRAMsdbcr.TabIndex = 26;
            this.textBoxSDRAMsdbcr.Text = "0x00000000";
            this.textBoxSDRAMsdbcr.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxSDRAMsdbcr.TextChanged += new System.EventHandler(this.textBoxSDRAMsdbcr_TextChanged);
            // 
            // checkBoxSDRAMdiv
            // 
            this.checkBoxSDRAMdiv.AutoSize = true;
            this.checkBoxSDRAMdiv.Location = new System.Drawing.Point(148, 31);
            this.checkBoxSDRAMdiv.Name = "checkBoxSDRAMdiv";
            this.checkBoxSDRAMdiv.Size = new System.Drawing.Size(182, 17);
            this.checkBoxSDRAMdiv.TabIndex = 25;
            this.checkBoxSDRAMdiv.Text = "Use 4.5 divisor for SDRAM clock";
            this.checkBoxSDRAMdiv.UseVisualStyleBackColor = true;
            this.checkBoxSDRAMdiv.CheckedChanged += new System.EventHandler(this.checkBoxSDRAMdiv_CheckedChanged);
            // 
            // labelSDRAMclockMHz
            // 
            this.labelSDRAMclockMHz.AutoSize = true;
            this.labelSDRAMclockMHz.Location = new System.Drawing.Point(290, 57);
            this.labelSDRAMclockMHz.Name = "labelSDRAMclockMHz";
            this.labelSDRAMclockMHz.Size = new System.Drawing.Size(29, 13);
            this.labelSDRAMclockMHz.TabIndex = 24;
            this.labelSDRAMclockMHz.Text = "MHz";
            // 
            // labelSDRAMclock
            // 
            this.labelSDRAMclock.AutoSize = true;
            this.labelSDRAMclock.Location = new System.Drawing.Point(145, 57);
            this.labelSDRAMclock.Name = "labelSDRAMclock";
            this.labelSDRAMclock.Size = new System.Drawing.Size(79, 13);
            this.labelSDRAMclock.TabIndex = 23;
            this.labelSDRAMclock.Text = "SDRAM Clock:";
            // 
            // textBoxSDRAMclock
            // 
            this.textBoxSDRAMclock.Location = new System.Drawing.Point(230, 54);
            this.textBoxSDRAMclock.Name = "textBoxSDRAMclock";
            this.textBoxSDRAMclock.ReadOnly = true;
            this.textBoxSDRAMclock.Size = new System.Drawing.Size(40, 20);
            this.textBoxSDRAMclock.TabIndex = 22;
            this.textBoxSDRAMclock.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // tabPagePLL1
            // 
            this.tabPagePLL1.Controls.Add(this.labelPLL1ddr2MHz);
            this.tabPagePLL1.Controls.Add(this.labelPLL1ddr2);
            this.tabPagePLL1.Controls.Add(this.textBoxPLL1ddr2);
            this.tabPagePLL1.Controls.Add(this.labelPLL1div3);
            this.tabPagePLL1.Controls.Add(this.textBoxPLL1div3);
            this.tabPagePLL1.Controls.Add(this.labelPLL1div2);
            this.tabPagePLL1.Controls.Add(this.textBoxPLL1div2);
            this.tabPagePLL1.Controls.Add(this.labelPLL1div1);
            this.tabPagePLL1.Controls.Add(this.textBoxPLL1div1);
            this.tabPagePLL1.Controls.Add(this.labelPLL1postDiv);
            this.tabPagePLL1.Controls.Add(this.textBoxPLL1postDiv);
            this.tabPagePLL1.Controls.Add(this.labelPLL1mult);
            this.tabPagePLL1.Controls.Add(this.textBoxPLL1mult);
            this.tabPagePLL1.Location = new System.Drawing.Point(4, 22);
            this.tabPagePLL1.Name = "tabPagePLL1";
            this.tabPagePLL1.Size = new System.Drawing.Size(474, 209);
            this.tabPagePLL1.TabIndex = 2;
            this.tabPagePLL1.Text = "PLL1";
            this.tabPagePLL1.UseVisualStyleBackColor = true;
            // 
            // labelPLL1ddr2MHz
            // 
            this.labelPLL1ddr2MHz.AutoSize = true;
            this.labelPLL1ddr2MHz.Location = new System.Drawing.Point(362, 97);
            this.labelPLL1ddr2MHz.Name = "labelPLL1ddr2MHz";
            this.labelPLL1ddr2MHz.Size = new System.Drawing.Size(29, 13);
            this.labelPLL1ddr2MHz.TabIndex = 26;
            this.labelPLL1ddr2MHz.Text = "MHz";
            // 
            // labelPLL1ddr2
            // 
            this.labelPLL1ddr2.AutoSize = true;
            this.labelPLL1ddr2.Location = new System.Drawing.Point(247, 97);
            this.labelPLL1ddr2.Name = "labelPLL1ddr2";
            this.labelPLL1ddr2.Size = new System.Drawing.Size(40, 13);
            this.labelPLL1ddr2.TabIndex = 25;
            this.labelPLL1ddr2.Text = "DDR2:";
            // 
            // textBoxPLL1ddr2
            // 
            this.textBoxPLL1ddr2.Location = new System.Drawing.Point(302, 94);
            this.textBoxPLL1ddr2.Name = "textBoxPLL1ddr2";
            this.textBoxPLL1ddr2.ReadOnly = true;
            this.textBoxPLL1ddr2.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL1ddr2.TabIndex = 24;
            this.textBoxPLL1ddr2.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // labelPLL1div3
            // 
            this.labelPLL1div3.AutoSize = true;
            this.labelPLL1div3.Location = new System.Drawing.Point(84, 149);
            this.labelPLL1div3.Name = "labelPLL1div3";
            this.labelPLL1div3.Size = new System.Drawing.Size(34, 13);
            this.labelPLL1div3.TabIndex = 23;
            this.labelPLL1div3.Text = "DIV3:";
            // 
            // textBoxPLL1div3
            // 
            this.textBoxPLL1div3.Location = new System.Drawing.Point(156, 146);
            this.textBoxPLL1div3.Name = "textBoxPLL1div3";
            this.textBoxPLL1div3.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL1div3.TabIndex = 22;
            this.textBoxPLL1div3.Text = "3";
            this.textBoxPLL1div3.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL1div3.TextChanged += new System.EventHandler(this.textBoxPLL1div3_TextChanged);
            // 
            // labelPLL1div2
            // 
            this.labelPLL1div2.AutoSize = true;
            this.labelPLL1div2.Location = new System.Drawing.Point(84, 123);
            this.labelPLL1div2.Name = "labelPLL1div2";
            this.labelPLL1div2.Size = new System.Drawing.Size(34, 13);
            this.labelPLL1div2.TabIndex = 21;
            this.labelPLL1div2.Text = "DIV2:";
            // 
            // textBoxPLL1div2
            // 
            this.textBoxPLL1div2.Location = new System.Drawing.Point(156, 120);
            this.textBoxPLL1div2.Name = "textBoxPLL1div2";
            this.textBoxPLL1div2.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL1div2.TabIndex = 20;
            this.textBoxPLL1div2.Text = "2";
            this.textBoxPLL1div2.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL1div2.TextChanged += new System.EventHandler(this.textBoxPLL1div2_TextChanged);
            // 
            // labelPLL1div1
            // 
            this.labelPLL1div1.AutoSize = true;
            this.labelPLL1div1.Location = new System.Drawing.Point(84, 97);
            this.labelPLL1div1.Name = "labelPLL1div1";
            this.labelPLL1div1.Size = new System.Drawing.Size(34, 13);
            this.labelPLL1div1.TabIndex = 19;
            this.labelPLL1div1.Text = "DIV1:";
            // 
            // textBoxPLL1div1
            // 
            this.textBoxPLL1div1.Location = new System.Drawing.Point(156, 94);
            this.textBoxPLL1div1.Name = "textBoxPLL1div1";
            this.textBoxPLL1div1.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL1div1.TabIndex = 18;
            this.textBoxPLL1div1.Text = "1";
            this.textBoxPLL1div1.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL1div1.TextChanged += new System.EventHandler(this.textBoxPLL1div1_TextChanged);
            // 
            // labelPLL1postDiv
            // 
            this.labelPLL1postDiv.AutoSize = true;
            this.labelPLL1postDiv.Location = new System.Drawing.Point(84, 71);
            this.labelPLL1postDiv.Name = "labelPLL1postDiv";
            this.labelPLL1postDiv.Size = new System.Drawing.Size(66, 13);
            this.labelPLL1postDiv.TabIndex = 17;
            this.labelPLL1postDiv.Text = "Post-Divisor:";
            // 
            // textBoxPLL1postDiv
            // 
            this.textBoxPLL1postDiv.Location = new System.Drawing.Point(156, 68);
            this.textBoxPLL1postDiv.Name = "textBoxPLL1postDiv";
            this.textBoxPLL1postDiv.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL1postDiv.TabIndex = 16;
            this.textBoxPLL1postDiv.Text = "2";
            this.textBoxPLL1postDiv.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL1postDiv.TextChanged += new System.EventHandler(this.textBoxPLL1postDiv_TextChanged);
            // 
            // labelPLL1mult
            // 
            this.labelPLL1mult.AutoSize = true;
            this.labelPLL1mult.Location = new System.Drawing.Point(84, 45);
            this.labelPLL1mult.Name = "labelPLL1mult";
            this.labelPLL1mult.Size = new System.Drawing.Size(51, 13);
            this.labelPLL1mult.TabIndex = 13;
            this.labelPLL1mult.Text = "Multiplier:";
            // 
            // textBoxPLL1mult
            // 
            this.textBoxPLL1mult.Location = new System.Drawing.Point(156, 42);
            this.textBoxPLL1mult.Name = "textBoxPLL1mult";
            this.textBoxPLL1mult.Size = new System.Drawing.Size(40, 20);
            this.textBoxPLL1mult.TabIndex = 12;
            this.textBoxPLL1mult.Text = "20";
            this.textBoxPLL1mult.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPLL1mult.TextChanged += new System.EventHandler(this.textBoxPLL1mult_TextChanged);
            // 
            // tabPageDDR2
            // 
            this.tabPageDDR2.Controls.Add(this.labelDDR2phy);
            this.tabPageDDR2.Controls.Add(this.textBoxDDR2phy);
            this.tabPageDDR2.Controls.Add(this.labelDDR2sdrcr);
            this.tabPageDDR2.Controls.Add(this.textBoxDDR2sdrcr);
            this.tabPageDDR2.Controls.Add(this.labelDDR2sdtimr2);
            this.tabPageDDR2.Controls.Add(this.textBoxDDR2sdtimr2);
            this.tabPageDDR2.Controls.Add(this.labelDDR2sdtimr);
            this.tabPageDDR2.Controls.Add(this.textBoxDDR2sdtimr);
            this.tabPageDDR2.Controls.Add(this.labelDDR2sdcr);
            this.tabPageDDR2.Controls.Add(this.textBoxDDR2sdcr);
            this.tabPageDDR2.Controls.Add(this.checkBoxDDR2directClock);
            this.tabPageDDR2.Controls.Add(this.labelDDR2clockMHz);
            this.tabPageDDR2.Controls.Add(this.labelDDR2clock);
            this.tabPageDDR2.Controls.Add(this.textBoxDDR2clock);
            this.tabPageDDR2.Location = new System.Drawing.Point(4, 22);
            this.tabPageDDR2.Name = "tabPageDDR2";
            this.tabPageDDR2.Size = new System.Drawing.Size(474, 209);
            this.tabPageDDR2.TabIndex = 3;
            this.tabPageDDR2.Text = "DDR2";
            this.tabPageDDR2.UseVisualStyleBackColor = true;
            // 
            // labelDDR2phy
            // 
            this.labelDDR2phy.AutoSize = true;
            this.labelDDR2phy.Location = new System.Drawing.Point(155, 70);
            this.labelDDR2phy.Name = "labelDDR2phy";
            this.labelDDR2phy.Size = new System.Drawing.Size(61, 13);
            this.labelDDR2phy.TabIndex = 47;
            this.labelDDR2phy.Text = "DRPYC1R:";
            // 
            // textBoxDDR2phy
            // 
            this.textBoxDDR2phy.Location = new System.Drawing.Point(231, 67);
            this.textBoxDDR2phy.MaxLength = 10;
            this.textBoxDDR2phy.Name = "textBoxDDR2phy";
            this.textBoxDDR2phy.Size = new System.Drawing.Size(80, 20);
            this.textBoxDDR2phy.TabIndex = 46;
            this.textBoxDDR2phy.Text = "0x00000000";
            this.textBoxDDR2phy.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxDDR2phy.TextChanged += new System.EventHandler(this.textBoxDDR2phy_TextChanged);
            // 
            // labelDDR2sdrcr
            // 
            this.labelDDR2sdrcr.AutoSize = true;
            this.labelDDR2sdrcr.Location = new System.Drawing.Point(155, 174);
            this.labelDDR2sdrcr.Name = "labelDDR2sdrcr";
            this.labelDDR2sdrcr.Size = new System.Drawing.Size(48, 13);
            this.labelDDR2sdrcr.TabIndex = 45;
            this.labelDDR2sdrcr.Text = "SDRCR:";
            // 
            // textBoxDDR2sdrcr
            // 
            this.textBoxDDR2sdrcr.Location = new System.Drawing.Point(231, 171);
            this.textBoxDDR2sdrcr.MaxLength = 10;
            this.textBoxDDR2sdrcr.Name = "textBoxDDR2sdrcr";
            this.textBoxDDR2sdrcr.Size = new System.Drawing.Size(80, 20);
            this.textBoxDDR2sdrcr.TabIndex = 44;
            this.textBoxDDR2sdrcr.Text = "0x00000000";
            this.textBoxDDR2sdrcr.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxDDR2sdrcr.TextChanged += new System.EventHandler(this.textBoxDDR2sdrcr_TextChanged);
            // 
            // labelDDR2sdtimr2
            // 
            this.labelDDR2sdtimr2.AutoSize = true;
            this.labelDDR2sdtimr2.Location = new System.Drawing.Point(155, 148);
            this.labelDDR2sdtimr2.Name = "labelDDR2sdtimr2";
            this.labelDDR2sdtimr2.Size = new System.Drawing.Size(58, 13);
            this.labelDDR2sdtimr2.TabIndex = 43;
            this.labelDDR2sdtimr2.Text = "SDTIMR2:";
            // 
            // textBoxDDR2sdtimr2
            // 
            this.textBoxDDR2sdtimr2.Location = new System.Drawing.Point(231, 145);
            this.textBoxDDR2sdtimr2.MaxLength = 10;
            this.textBoxDDR2sdtimr2.Name = "textBoxDDR2sdtimr2";
            this.textBoxDDR2sdtimr2.Size = new System.Drawing.Size(80, 20);
            this.textBoxDDR2sdtimr2.TabIndex = 42;
            this.textBoxDDR2sdtimr2.Text = "0x00000000";
            this.textBoxDDR2sdtimr2.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxDDR2sdtimr2.TextChanged += new System.EventHandler(this.textBoxDDR2sdtimr2_TextChanged);
            // 
            // labelDDR2sdtimr
            // 
            this.labelDDR2sdtimr.AutoSize = true;
            this.labelDDR2sdtimr.Location = new System.Drawing.Point(155, 122);
            this.labelDDR2sdtimr.Name = "labelDDR2sdtimr";
            this.labelDDR2sdtimr.Size = new System.Drawing.Size(58, 13);
            this.labelDDR2sdtimr.TabIndex = 41;
            this.labelDDR2sdtimr.Text = "SDTIMR1:";
            // 
            // textBoxDDR2sdtimr
            // 
            this.textBoxDDR2sdtimr.Location = new System.Drawing.Point(231, 119);
            this.textBoxDDR2sdtimr.MaxLength = 10;
            this.textBoxDDR2sdtimr.Name = "textBoxDDR2sdtimr";
            this.textBoxDDR2sdtimr.Size = new System.Drawing.Size(80, 20);
            this.textBoxDDR2sdtimr.TabIndex = 40;
            this.textBoxDDR2sdtimr.Text = "0x00000000";
            this.textBoxDDR2sdtimr.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxDDR2sdtimr.TextChanged += new System.EventHandler(this.textBoxDDR2sdtimr_TextChanged);
            // 
            // labelDDR2sdcr
            // 
            this.labelDDR2sdcr.AutoSize = true;
            this.labelDDR2sdcr.Location = new System.Drawing.Point(155, 96);
            this.labelDDR2sdcr.Name = "labelDDR2sdcr";
            this.labelDDR2sdcr.Size = new System.Drawing.Size(40, 13);
            this.labelDDR2sdcr.TabIndex = 39;
            this.labelDDR2sdcr.Text = "SDCR:";
            // 
            // textBoxDDR2sdcr
            // 
            this.textBoxDDR2sdcr.Location = new System.Drawing.Point(231, 93);
            this.textBoxDDR2sdcr.MaxLength = 10;
            this.textBoxDDR2sdcr.Name = "textBoxDDR2sdcr";
            this.textBoxDDR2sdcr.Size = new System.Drawing.Size(80, 20);
            this.textBoxDDR2sdcr.TabIndex = 38;
            this.textBoxDDR2sdcr.Text = "0x00000000";
            this.textBoxDDR2sdcr.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxDDR2sdcr.TextChanged += new System.EventHandler(this.textBoxDDR2sdcr_TextChanged);
            // 
            // checkBoxDDR2directClock
            // 
            this.checkBoxDDR2directClock.AutoSize = true;
            this.checkBoxDDR2directClock.Location = new System.Drawing.Point(158, 18);
            this.checkBoxDDR2directClock.Name = "checkBoxDDR2directClock";
            this.checkBoxDDR2directClock.Size = new System.Drawing.Size(154, 17);
            this.checkBoxDDR2directClock.TabIndex = 37;
            this.checkBoxDDR2directClock.Text = "Use direct clock from PLL1";
            this.checkBoxDDR2directClock.UseVisualStyleBackColor = true;
            this.checkBoxDDR2directClock.CheckedChanged += new System.EventHandler(this.checkBoxDDR2directClock_CheckedChanged);
            // 
            // labelDDR2clockMHz
            // 
            this.labelDDR2clockMHz.AutoSize = true;
            this.labelDDR2clockMHz.Location = new System.Drawing.Point(291, 44);
            this.labelDDR2clockMHz.Name = "labelDDR2clockMHz";
            this.labelDDR2clockMHz.Size = new System.Drawing.Size(29, 13);
            this.labelDDR2clockMHz.TabIndex = 36;
            this.labelDDR2clockMHz.Text = "MHz";
            // 
            // labelDDR2clock
            // 
            this.labelDDR2clock.AutoSize = true;
            this.labelDDR2clock.Location = new System.Drawing.Point(155, 44);
            this.labelDDR2clock.Name = "labelDDR2clock";
            this.labelDDR2clock.Size = new System.Drawing.Size(70, 13);
            this.labelDDR2clock.TabIndex = 35;
            this.labelDDR2clock.Text = "DDR2 Clock:";
            // 
            // textBoxDDR2clock
            // 
            this.textBoxDDR2clock.Location = new System.Drawing.Point(231, 41);
            this.textBoxDDR2clock.Name = "textBoxDDR2clock";
            this.textBoxDDR2clock.ReadOnly = true;
            this.textBoxDDR2clock.Size = new System.Drawing.Size(40, 20);
            this.textBoxDDR2clock.TabIndex = 34;
            this.textBoxDDR2clock.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // tabPageLPSC
            // 
            this.tabPageLPSC.Controls.Add(this.labelLpsc1);
            this.tabPageLPSC.Controls.Add(this.labelLpsc0);
            this.tabPageLPSC.Controls.Add(this.textBoxLps1SyncRst);
            this.tabPageLPSC.Controls.Add(this.textBoxLps1Disable);
            this.tabPageLPSC.Controls.Add(this.textBoxLps1Enable);
            this.tabPageLPSC.Controls.Add(this.textBoxLps0SyncRst);
            this.tabPageLPSC.Controls.Add(this.textBoxLps0Disable);
            this.tabPageLPSC.Controls.Add(this.textBoxLps0Enable);
            this.tabPageLPSC.Controls.Add(this.labelLpsc0SyncRst);
            this.tabPageLPSC.Controls.Add(this.labelLpsc0Disable);
            this.tabPageLPSC.Controls.Add(this.labelLpsc0enable);
            this.tabPageLPSC.Location = new System.Drawing.Point(4, 22);
            this.tabPageLPSC.Name = "tabPageLPSC";
            this.tabPageLPSC.Size = new System.Drawing.Size(474, 209);
            this.tabPageLPSC.TabIndex = 6;
            this.tabPageLPSC.Text = "PSC";
            this.tabPageLPSC.UseVisualStyleBackColor = true;
            // 
            // labelLpsc1
            // 
            this.labelLpsc1.AutoSize = true;
            this.labelLpsc1.Location = new System.Drawing.Point(289, 60);
            this.labelLpsc1.Name = "labelLpsc1";
            this.labelLpsc1.Size = new System.Drawing.Size(34, 13);
            this.labelLpsc1.TabIndex = 16;
            this.labelLpsc1.Text = "PSC1";
            // 
            // labelLpsc0
            // 
            this.labelLpsc0.AutoSize = true;
            this.labelLpsc0.Location = new System.Drawing.Point(163, 60);
            this.labelLpsc0.Name = "labelLpsc0";
            this.labelLpsc0.Size = new System.Drawing.Size(34, 13);
            this.labelLpsc0.TabIndex = 15;
            this.labelLpsc0.Text = "PSC0";
            // 
            // textBoxLps1SyncRst
            // 
            this.textBoxLps1SyncRst.Location = new System.Drawing.Point(292, 128);
            this.textBoxLps1SyncRst.Name = "textBoxLps1SyncRst";
            this.textBoxLps1SyncRst.Size = new System.Drawing.Size(106, 20);
            this.textBoxLps1SyncRst.TabIndex = 14;
            this.textBoxLps1SyncRst.TextChanged += new System.EventHandler(this.textBoxLps1SyncRst_TextChanged);
            // 
            // textBoxLps1Disable
            // 
            this.textBoxLps1Disable.Location = new System.Drawing.Point(292, 102);
            this.textBoxLps1Disable.Name = "textBoxLps1Disable";
            this.textBoxLps1Disable.Size = new System.Drawing.Size(106, 20);
            this.textBoxLps1Disable.TabIndex = 13;
            this.textBoxLps1Disable.TextChanged += new System.EventHandler(this.textBoxLps1Disable_TextChanged);
            // 
            // textBoxLps1Enable
            // 
            this.textBoxLps1Enable.Location = new System.Drawing.Point(292, 76);
            this.textBoxLps1Enable.Name = "textBoxLps1Enable";
            this.textBoxLps1Enable.Size = new System.Drawing.Size(106, 20);
            this.textBoxLps1Enable.TabIndex = 12;
            this.textBoxLps1Enable.TextChanged += new System.EventHandler(this.textBoxLps1Enable_TextChanged);
            // 
            // textBoxLps0SyncRst
            // 
            this.textBoxLps0SyncRst.Location = new System.Drawing.Point(166, 128);
            this.textBoxLps0SyncRst.Name = "textBoxLps0SyncRst";
            this.textBoxLps0SyncRst.Size = new System.Drawing.Size(106, 20);
            this.textBoxLps0SyncRst.TabIndex = 11;
            this.textBoxLps0SyncRst.TextChanged += new System.EventHandler(this.textBoxLps0SyncRst_TextChanged);
            // 
            // textBoxLps0Disable
            // 
            this.textBoxLps0Disable.Location = new System.Drawing.Point(166, 102);
            this.textBoxLps0Disable.Name = "textBoxLps0Disable";
            this.textBoxLps0Disable.Size = new System.Drawing.Size(106, 20);
            this.textBoxLps0Disable.TabIndex = 10;
            this.textBoxLps0Disable.TextChanged += new System.EventHandler(this.textBoxLps0Disable_TextChanged);
            // 
            // textBoxLps0Enable
            // 
            this.textBoxLps0Enable.Location = new System.Drawing.Point(166, 76);
            this.textBoxLps0Enable.Name = "textBoxLps0Enable";
            this.textBoxLps0Enable.Size = new System.Drawing.Size(106, 20);
            this.textBoxLps0Enable.TabIndex = 9;
            this.textBoxLps0Enable.TextChanged += new System.EventHandler(this.textBoxLps0Enable_TextChanged);
            // 
            // labelLpsc0SyncRst
            // 
            this.labelLpsc0SyncRst.AutoSize = true;
            this.labelLpsc0SyncRst.Location = new System.Drawing.Point(77, 131);
            this.labelLpsc0SyncRst.Name = "labelLpsc0SyncRst";
            this.labelLpsc0SyncRst.Size = new System.Drawing.Size(83, 13);
            this.labelLpsc0SyncRst.TabIndex = 8;
            this.labelLpsc0SyncRst.Text = "Sync Rst LPSC:";
            // 
            // labelLpsc0Disable
            // 
            this.labelLpsc0Disable.AutoSize = true;
            this.labelLpsc0Disable.Location = new System.Drawing.Point(77, 105);
            this.labelLpsc0Disable.Name = "labelLpsc0Disable";
            this.labelLpsc0Disable.Size = new System.Drawing.Size(75, 13);
            this.labelLpsc0Disable.TabIndex = 7;
            this.labelLpsc0Disable.Text = "Disable LPSC:";
            // 
            // labelLpsc0enable
            // 
            this.labelLpsc0enable.AutoSize = true;
            this.labelLpsc0enable.Location = new System.Drawing.Point(77, 79);
            this.labelLpsc0enable.Name = "labelLpsc0enable";
            this.labelLpsc0enable.Size = new System.Drawing.Size(73, 13);
            this.labelLpsc0enable.TabIndex = 6;
            this.labelLpsc0enable.Text = "Enable LPSC:";
            // 
            // tabPagePinmux
            // 
            this.tabPagePinmux.AutoScroll = true;
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal19);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg20);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux19);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal18);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg19);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux18);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal17);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg18);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux17);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal16);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg17);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux16);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal15);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg16);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux15);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal14);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg15);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux14);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal13);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg14);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux13);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal12);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg13);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux12);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal11);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg12);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux11);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal10);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg11);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux10);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal9);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg10);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux9);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal8);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg9);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux8);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal7);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg8);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux7);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal6);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg7);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux6);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal5);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg6);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux5);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal4);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg5);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux4);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal3);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg4);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux3);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal2);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg3);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux2);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal1);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg2);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux1);
            this.tabPagePinmux.Controls.Add(this.textBoxPinmuxVal0);
            this.tabPagePinmux.Controls.Add(this.labelPinmuxReg1);
            this.tabPagePinmux.Controls.Add(this.numericUpDownPinmux0);
            this.tabPagePinmux.Location = new System.Drawing.Point(4, 22);
            this.tabPagePinmux.Name = "tabPagePinmux";
            this.tabPagePinmux.Size = new System.Drawing.Size(474, 209);
            this.tabPagePinmux.TabIndex = 7;
            this.tabPagePinmux.Text = "Pinmux";
            this.tabPagePinmux.UseVisualStyleBackColor = true;
            // 
            // textBoxPinmuxVal19
            // 
            this.textBoxPinmuxVal19.Enabled = false;
            this.textBoxPinmuxVal19.Location = new System.Drawing.Point(271, 497);
            this.textBoxPinmuxVal19.MaxLength = 10;
            this.textBoxPinmuxVal19.Name = "textBoxPinmuxVal19";
            this.textBoxPinmuxVal19.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal19.TabIndex = 104;
            this.textBoxPinmuxVal19.Text = "0x00000000";
            this.textBoxPinmuxVal19.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal19.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg20
            // 
            this.labelPinmuxReg20.AutoSize = true;
            this.labelPinmuxReg20.Location = new System.Drawing.Point(106, 499);
            this.labelPinmuxReg20.Name = "labelPinmuxReg20";
            this.labelPinmuxReg20.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg20.TabIndex = 103;
            this.labelPinmuxReg20.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux19
            // 
            this.numericUpDownPinmux19.Location = new System.Drawing.Point(225, 497);
            this.numericUpDownPinmux19.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux19.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux19.Name = "numericUpDownPinmux19";
            this.numericUpDownPinmux19.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux19.TabIndex = 102;
            this.numericUpDownPinmux19.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux19.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux19.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal18
            // 
            this.textBoxPinmuxVal18.Enabled = false;
            this.textBoxPinmuxVal18.Location = new System.Drawing.Point(271, 471);
            this.textBoxPinmuxVal18.MaxLength = 10;
            this.textBoxPinmuxVal18.Name = "textBoxPinmuxVal18";
            this.textBoxPinmuxVal18.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal18.TabIndex = 101;
            this.textBoxPinmuxVal18.Text = "0x00000000";
            this.textBoxPinmuxVal18.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal18.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg19
            // 
            this.labelPinmuxReg19.AutoSize = true;
            this.labelPinmuxReg19.Location = new System.Drawing.Point(106, 473);
            this.labelPinmuxReg19.Name = "labelPinmuxReg19";
            this.labelPinmuxReg19.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg19.TabIndex = 100;
            this.labelPinmuxReg19.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux18
            // 
            this.numericUpDownPinmux18.Location = new System.Drawing.Point(225, 471);
            this.numericUpDownPinmux18.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux18.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux18.Name = "numericUpDownPinmux18";
            this.numericUpDownPinmux18.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux18.TabIndex = 99;
            this.numericUpDownPinmux18.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux18.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux18.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal17
            // 
            this.textBoxPinmuxVal17.Enabled = false;
            this.textBoxPinmuxVal17.Location = new System.Drawing.Point(271, 445);
            this.textBoxPinmuxVal17.MaxLength = 10;
            this.textBoxPinmuxVal17.Name = "textBoxPinmuxVal17";
            this.textBoxPinmuxVal17.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal17.TabIndex = 98;
            this.textBoxPinmuxVal17.Text = "0x00000000";
            this.textBoxPinmuxVal17.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal17.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg18
            // 
            this.labelPinmuxReg18.AutoSize = true;
            this.labelPinmuxReg18.Location = new System.Drawing.Point(106, 447);
            this.labelPinmuxReg18.Name = "labelPinmuxReg18";
            this.labelPinmuxReg18.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg18.TabIndex = 97;
            this.labelPinmuxReg18.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux17
            // 
            this.numericUpDownPinmux17.Location = new System.Drawing.Point(225, 445);
            this.numericUpDownPinmux17.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux17.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux17.Name = "numericUpDownPinmux17";
            this.numericUpDownPinmux17.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux17.TabIndex = 96;
            this.numericUpDownPinmux17.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux17.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux17.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal16
            // 
            this.textBoxPinmuxVal16.Enabled = false;
            this.textBoxPinmuxVal16.Location = new System.Drawing.Point(271, 419);
            this.textBoxPinmuxVal16.MaxLength = 10;
            this.textBoxPinmuxVal16.Name = "textBoxPinmuxVal16";
            this.textBoxPinmuxVal16.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal16.TabIndex = 95;
            this.textBoxPinmuxVal16.Text = "0x00000000";
            this.textBoxPinmuxVal16.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal16.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg17
            // 
            this.labelPinmuxReg17.AutoSize = true;
            this.labelPinmuxReg17.Location = new System.Drawing.Point(106, 421);
            this.labelPinmuxReg17.Name = "labelPinmuxReg17";
            this.labelPinmuxReg17.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg17.TabIndex = 94;
            this.labelPinmuxReg17.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux16
            // 
            this.numericUpDownPinmux16.Location = new System.Drawing.Point(225, 419);
            this.numericUpDownPinmux16.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux16.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux16.Name = "numericUpDownPinmux16";
            this.numericUpDownPinmux16.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux16.TabIndex = 93;
            this.numericUpDownPinmux16.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux16.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux16.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal15
            // 
            this.textBoxPinmuxVal15.Enabled = false;
            this.textBoxPinmuxVal15.Location = new System.Drawing.Point(271, 393);
            this.textBoxPinmuxVal15.MaxLength = 10;
            this.textBoxPinmuxVal15.Name = "textBoxPinmuxVal15";
            this.textBoxPinmuxVal15.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal15.TabIndex = 92;
            this.textBoxPinmuxVal15.Text = "0x00000000";
            this.textBoxPinmuxVal15.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal15.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg16
            // 
            this.labelPinmuxReg16.AutoSize = true;
            this.labelPinmuxReg16.Location = new System.Drawing.Point(106, 395);
            this.labelPinmuxReg16.Name = "labelPinmuxReg16";
            this.labelPinmuxReg16.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg16.TabIndex = 91;
            this.labelPinmuxReg16.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux15
            // 
            this.numericUpDownPinmux15.Location = new System.Drawing.Point(225, 393);
            this.numericUpDownPinmux15.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux15.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux15.Name = "numericUpDownPinmux15";
            this.numericUpDownPinmux15.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux15.TabIndex = 90;
            this.numericUpDownPinmux15.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux15.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux15.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal14
            // 
            this.textBoxPinmuxVal14.Enabled = false;
            this.textBoxPinmuxVal14.Location = new System.Drawing.Point(271, 367);
            this.textBoxPinmuxVal14.MaxLength = 10;
            this.textBoxPinmuxVal14.Name = "textBoxPinmuxVal14";
            this.textBoxPinmuxVal14.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal14.TabIndex = 89;
            this.textBoxPinmuxVal14.Text = "0x00000000";
            this.textBoxPinmuxVal14.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal14.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg15
            // 
            this.labelPinmuxReg15.AutoSize = true;
            this.labelPinmuxReg15.Location = new System.Drawing.Point(106, 369);
            this.labelPinmuxReg15.Name = "labelPinmuxReg15";
            this.labelPinmuxReg15.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg15.TabIndex = 88;
            this.labelPinmuxReg15.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux14
            // 
            this.numericUpDownPinmux14.Location = new System.Drawing.Point(225, 367);
            this.numericUpDownPinmux14.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux14.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux14.Name = "numericUpDownPinmux14";
            this.numericUpDownPinmux14.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux14.TabIndex = 87;
            this.numericUpDownPinmux14.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux14.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux14.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal13
            // 
            this.textBoxPinmuxVal13.Enabled = false;
            this.textBoxPinmuxVal13.Location = new System.Drawing.Point(271, 341);
            this.textBoxPinmuxVal13.MaxLength = 10;
            this.textBoxPinmuxVal13.Name = "textBoxPinmuxVal13";
            this.textBoxPinmuxVal13.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal13.TabIndex = 86;
            this.textBoxPinmuxVal13.Text = "0x00000000";
            this.textBoxPinmuxVal13.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal13.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg14
            // 
            this.labelPinmuxReg14.AutoSize = true;
            this.labelPinmuxReg14.Location = new System.Drawing.Point(106, 343);
            this.labelPinmuxReg14.Name = "labelPinmuxReg14";
            this.labelPinmuxReg14.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg14.TabIndex = 85;
            this.labelPinmuxReg14.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux13
            // 
            this.numericUpDownPinmux13.Location = new System.Drawing.Point(225, 341);
            this.numericUpDownPinmux13.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux13.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux13.Name = "numericUpDownPinmux13";
            this.numericUpDownPinmux13.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux13.TabIndex = 84;
            this.numericUpDownPinmux13.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux13.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux13.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal12
            // 
            this.textBoxPinmuxVal12.Enabled = false;
            this.textBoxPinmuxVal12.Location = new System.Drawing.Point(271, 315);
            this.textBoxPinmuxVal12.MaxLength = 10;
            this.textBoxPinmuxVal12.Name = "textBoxPinmuxVal12";
            this.textBoxPinmuxVal12.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal12.TabIndex = 83;
            this.textBoxPinmuxVal12.Text = "0x00000000";
            this.textBoxPinmuxVal12.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal12.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg13
            // 
            this.labelPinmuxReg13.AutoSize = true;
            this.labelPinmuxReg13.Location = new System.Drawing.Point(106, 317);
            this.labelPinmuxReg13.Name = "labelPinmuxReg13";
            this.labelPinmuxReg13.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg13.TabIndex = 82;
            this.labelPinmuxReg13.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux12
            // 
            this.numericUpDownPinmux12.Location = new System.Drawing.Point(225, 315);
            this.numericUpDownPinmux12.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux12.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux12.Name = "numericUpDownPinmux12";
            this.numericUpDownPinmux12.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux12.TabIndex = 81;
            this.numericUpDownPinmux12.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux12.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux12.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal11
            // 
            this.textBoxPinmuxVal11.Enabled = false;
            this.textBoxPinmuxVal11.Location = new System.Drawing.Point(271, 289);
            this.textBoxPinmuxVal11.MaxLength = 10;
            this.textBoxPinmuxVal11.Name = "textBoxPinmuxVal11";
            this.textBoxPinmuxVal11.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal11.TabIndex = 80;
            this.textBoxPinmuxVal11.Text = "0x00000000";
            this.textBoxPinmuxVal11.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal11.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg12
            // 
            this.labelPinmuxReg12.AutoSize = true;
            this.labelPinmuxReg12.Location = new System.Drawing.Point(106, 291);
            this.labelPinmuxReg12.Name = "labelPinmuxReg12";
            this.labelPinmuxReg12.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg12.TabIndex = 79;
            this.labelPinmuxReg12.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux11
            // 
            this.numericUpDownPinmux11.Location = new System.Drawing.Point(225, 289);
            this.numericUpDownPinmux11.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux11.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux11.Name = "numericUpDownPinmux11";
            this.numericUpDownPinmux11.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux11.TabIndex = 78;
            this.numericUpDownPinmux11.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux11.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux11.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal10
            // 
            this.textBoxPinmuxVal10.Enabled = false;
            this.textBoxPinmuxVal10.Location = new System.Drawing.Point(271, 263);
            this.textBoxPinmuxVal10.MaxLength = 10;
            this.textBoxPinmuxVal10.Name = "textBoxPinmuxVal10";
            this.textBoxPinmuxVal10.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal10.TabIndex = 77;
            this.textBoxPinmuxVal10.Text = "0x00000000";
            this.textBoxPinmuxVal10.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal10.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg11
            // 
            this.labelPinmuxReg11.AutoSize = true;
            this.labelPinmuxReg11.Location = new System.Drawing.Point(106, 265);
            this.labelPinmuxReg11.Name = "labelPinmuxReg11";
            this.labelPinmuxReg11.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg11.TabIndex = 76;
            this.labelPinmuxReg11.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux10
            // 
            this.numericUpDownPinmux10.Location = new System.Drawing.Point(225, 263);
            this.numericUpDownPinmux10.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux10.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux10.Name = "numericUpDownPinmux10";
            this.numericUpDownPinmux10.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux10.TabIndex = 75;
            this.numericUpDownPinmux10.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux10.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux10.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal9
            // 
            this.textBoxPinmuxVal9.Enabled = false;
            this.textBoxPinmuxVal9.Location = new System.Drawing.Point(271, 237);
            this.textBoxPinmuxVal9.MaxLength = 10;
            this.textBoxPinmuxVal9.Name = "textBoxPinmuxVal9";
            this.textBoxPinmuxVal9.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal9.TabIndex = 74;
            this.textBoxPinmuxVal9.Text = "0x00000000";
            this.textBoxPinmuxVal9.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal9.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg10
            // 
            this.labelPinmuxReg10.AutoSize = true;
            this.labelPinmuxReg10.Location = new System.Drawing.Point(106, 239);
            this.labelPinmuxReg10.Name = "labelPinmuxReg10";
            this.labelPinmuxReg10.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg10.TabIndex = 73;
            this.labelPinmuxReg10.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux9
            // 
            this.numericUpDownPinmux9.Location = new System.Drawing.Point(225, 237);
            this.numericUpDownPinmux9.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux9.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux9.Name = "numericUpDownPinmux9";
            this.numericUpDownPinmux9.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux9.TabIndex = 72;
            this.numericUpDownPinmux9.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux9.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux9.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal8
            // 
            this.textBoxPinmuxVal8.Enabled = false;
            this.textBoxPinmuxVal8.Location = new System.Drawing.Point(271, 211);
            this.textBoxPinmuxVal8.MaxLength = 10;
            this.textBoxPinmuxVal8.Name = "textBoxPinmuxVal8";
            this.textBoxPinmuxVal8.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal8.TabIndex = 71;
            this.textBoxPinmuxVal8.Text = "0x00000000";
            this.textBoxPinmuxVal8.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal8.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg9
            // 
            this.labelPinmuxReg9.AutoSize = true;
            this.labelPinmuxReg9.Location = new System.Drawing.Point(106, 213);
            this.labelPinmuxReg9.Name = "labelPinmuxReg9";
            this.labelPinmuxReg9.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg9.TabIndex = 70;
            this.labelPinmuxReg9.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux8
            // 
            this.numericUpDownPinmux8.Location = new System.Drawing.Point(225, 211);
            this.numericUpDownPinmux8.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux8.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux8.Name = "numericUpDownPinmux8";
            this.numericUpDownPinmux8.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux8.TabIndex = 69;
            this.numericUpDownPinmux8.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux8.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux8.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal7
            // 
            this.textBoxPinmuxVal7.Enabled = false;
            this.textBoxPinmuxVal7.Location = new System.Drawing.Point(271, 185);
            this.textBoxPinmuxVal7.MaxLength = 10;
            this.textBoxPinmuxVal7.Name = "textBoxPinmuxVal7";
            this.textBoxPinmuxVal7.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal7.TabIndex = 68;
            this.textBoxPinmuxVal7.Text = "0x00000000";
            this.textBoxPinmuxVal7.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal7.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg8
            // 
            this.labelPinmuxReg8.AutoSize = true;
            this.labelPinmuxReg8.Location = new System.Drawing.Point(106, 187);
            this.labelPinmuxReg8.Name = "labelPinmuxReg8";
            this.labelPinmuxReg8.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg8.TabIndex = 67;
            this.labelPinmuxReg8.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux7
            // 
            this.numericUpDownPinmux7.Location = new System.Drawing.Point(225, 185);
            this.numericUpDownPinmux7.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux7.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux7.Name = "numericUpDownPinmux7";
            this.numericUpDownPinmux7.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux7.TabIndex = 66;
            this.numericUpDownPinmux7.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux7.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux7.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal6
            // 
            this.textBoxPinmuxVal6.Enabled = false;
            this.textBoxPinmuxVal6.Location = new System.Drawing.Point(271, 159);
            this.textBoxPinmuxVal6.MaxLength = 10;
            this.textBoxPinmuxVal6.Name = "textBoxPinmuxVal6";
            this.textBoxPinmuxVal6.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal6.TabIndex = 65;
            this.textBoxPinmuxVal6.Text = "0x00000000";
            this.textBoxPinmuxVal6.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal6.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg7
            // 
            this.labelPinmuxReg7.AutoSize = true;
            this.labelPinmuxReg7.Location = new System.Drawing.Point(106, 161);
            this.labelPinmuxReg7.Name = "labelPinmuxReg7";
            this.labelPinmuxReg7.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg7.TabIndex = 64;
            this.labelPinmuxReg7.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux6
            // 
            this.numericUpDownPinmux6.Location = new System.Drawing.Point(225, 159);
            this.numericUpDownPinmux6.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux6.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux6.Name = "numericUpDownPinmux6";
            this.numericUpDownPinmux6.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux6.TabIndex = 63;
            this.numericUpDownPinmux6.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux6.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux6.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal5
            // 
            this.textBoxPinmuxVal5.Enabled = false;
            this.textBoxPinmuxVal5.Location = new System.Drawing.Point(271, 133);
            this.textBoxPinmuxVal5.MaxLength = 10;
            this.textBoxPinmuxVal5.Name = "textBoxPinmuxVal5";
            this.textBoxPinmuxVal5.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal5.TabIndex = 62;
            this.textBoxPinmuxVal5.Text = "0x00000000";
            this.textBoxPinmuxVal5.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal5.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg6
            // 
            this.labelPinmuxReg6.AutoSize = true;
            this.labelPinmuxReg6.Location = new System.Drawing.Point(106, 135);
            this.labelPinmuxReg6.Name = "labelPinmuxReg6";
            this.labelPinmuxReg6.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg6.TabIndex = 61;
            this.labelPinmuxReg6.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux5
            // 
            this.numericUpDownPinmux5.Location = new System.Drawing.Point(225, 133);
            this.numericUpDownPinmux5.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux5.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux5.Name = "numericUpDownPinmux5";
            this.numericUpDownPinmux5.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux5.TabIndex = 60;
            this.numericUpDownPinmux5.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux5.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux5.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal4
            // 
            this.textBoxPinmuxVal4.Enabled = false;
            this.textBoxPinmuxVal4.Location = new System.Drawing.Point(271, 107);
            this.textBoxPinmuxVal4.MaxLength = 10;
            this.textBoxPinmuxVal4.Name = "textBoxPinmuxVal4";
            this.textBoxPinmuxVal4.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal4.TabIndex = 59;
            this.textBoxPinmuxVal4.Text = "0x00000000";
            this.textBoxPinmuxVal4.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal4.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg5
            // 
            this.labelPinmuxReg5.AutoSize = true;
            this.labelPinmuxReg5.Location = new System.Drawing.Point(106, 109);
            this.labelPinmuxReg5.Name = "labelPinmuxReg5";
            this.labelPinmuxReg5.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg5.TabIndex = 58;
            this.labelPinmuxReg5.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux4
            // 
            this.numericUpDownPinmux4.Location = new System.Drawing.Point(225, 107);
            this.numericUpDownPinmux4.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux4.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux4.Name = "numericUpDownPinmux4";
            this.numericUpDownPinmux4.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux4.TabIndex = 57;
            this.numericUpDownPinmux4.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux4.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux4.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal3
            // 
            this.textBoxPinmuxVal3.Enabled = false;
            this.textBoxPinmuxVal3.Location = new System.Drawing.Point(271, 81);
            this.textBoxPinmuxVal3.MaxLength = 10;
            this.textBoxPinmuxVal3.Name = "textBoxPinmuxVal3";
            this.textBoxPinmuxVal3.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal3.TabIndex = 56;
            this.textBoxPinmuxVal3.Text = "0x00000000";
            this.textBoxPinmuxVal3.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal3.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg4
            // 
            this.labelPinmuxReg4.AutoSize = true;
            this.labelPinmuxReg4.Location = new System.Drawing.Point(106, 83);
            this.labelPinmuxReg4.Name = "labelPinmuxReg4";
            this.labelPinmuxReg4.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg4.TabIndex = 55;
            this.labelPinmuxReg4.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux3
            // 
            this.numericUpDownPinmux3.Location = new System.Drawing.Point(225, 81);
            this.numericUpDownPinmux3.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux3.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux3.Name = "numericUpDownPinmux3";
            this.numericUpDownPinmux3.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux3.TabIndex = 54;
            this.numericUpDownPinmux3.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux3.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux3.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal2
            // 
            this.textBoxPinmuxVal2.Enabled = false;
            this.textBoxPinmuxVal2.Location = new System.Drawing.Point(271, 55);
            this.textBoxPinmuxVal2.MaxLength = 10;
            this.textBoxPinmuxVal2.Name = "textBoxPinmuxVal2";
            this.textBoxPinmuxVal2.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal2.TabIndex = 53;
            this.textBoxPinmuxVal2.Text = "0x00000000";
            this.textBoxPinmuxVal2.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal2.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg3
            // 
            this.labelPinmuxReg3.AutoSize = true;
            this.labelPinmuxReg3.Location = new System.Drawing.Point(106, 57);
            this.labelPinmuxReg3.Name = "labelPinmuxReg3";
            this.labelPinmuxReg3.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg3.TabIndex = 52;
            this.labelPinmuxReg3.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux2
            // 
            this.numericUpDownPinmux2.Location = new System.Drawing.Point(225, 55);
            this.numericUpDownPinmux2.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux2.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux2.Name = "numericUpDownPinmux2";
            this.numericUpDownPinmux2.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux2.TabIndex = 51;
            this.numericUpDownPinmux2.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux2.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux2.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal1
            // 
            this.textBoxPinmuxVal1.Enabled = false;
            this.textBoxPinmuxVal1.Location = new System.Drawing.Point(271, 29);
            this.textBoxPinmuxVal1.MaxLength = 10;
            this.textBoxPinmuxVal1.Name = "textBoxPinmuxVal1";
            this.textBoxPinmuxVal1.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal1.TabIndex = 50;
            this.textBoxPinmuxVal1.Text = "0x00000000";
            this.textBoxPinmuxVal1.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal1.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg2
            // 
            this.labelPinmuxReg2.AutoSize = true;
            this.labelPinmuxReg2.Location = new System.Drawing.Point(106, 31);
            this.labelPinmuxReg2.Name = "labelPinmuxReg2";
            this.labelPinmuxReg2.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg2.TabIndex = 49;
            this.labelPinmuxReg2.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux1
            // 
            this.numericUpDownPinmux1.Location = new System.Drawing.Point(225, 29);
            this.numericUpDownPinmux1.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux1.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux1.Name = "numericUpDownPinmux1";
            this.numericUpDownPinmux1.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux1.TabIndex = 48;
            this.numericUpDownPinmux1.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux1.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux1.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // textBoxPinmuxVal0
            // 
            this.textBoxPinmuxVal0.Enabled = false;
            this.textBoxPinmuxVal0.Location = new System.Drawing.Point(271, 3);
            this.textBoxPinmuxVal0.MaxLength = 10;
            this.textBoxPinmuxVal0.Name = "textBoxPinmuxVal0";
            this.textBoxPinmuxVal0.Size = new System.Drawing.Size(80, 20);
            this.textBoxPinmuxVal0.TabIndex = 47;
            this.textBoxPinmuxVal0.Text = "0x00000000";
            this.textBoxPinmuxVal0.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textBoxPinmuxVal0.TextChanged += new System.EventHandler(this.textBoxPinmuxVal_TextChanged);
            // 
            // labelPinmuxReg1
            // 
            this.labelPinmuxReg1.AutoSize = true;
            this.labelPinmuxReg1.Location = new System.Drawing.Point(106, 5);
            this.labelPinmuxReg1.Name = "labelPinmuxReg1";
            this.labelPinmuxReg1.Size = new System.Drawing.Size(113, 13);
            this.labelPinmuxReg1.TabIndex = 6;
            this.labelPinmuxReg1.Text = "Pinmux Register (0-19)";
            // 
            // numericUpDownPinmux0
            // 
            this.numericUpDownPinmux0.Location = new System.Drawing.Point(225, 3);
            this.numericUpDownPinmux0.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numericUpDownPinmux0.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux0.Name = "numericUpDownPinmux0";
            this.numericUpDownPinmux0.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownPinmux0.TabIndex = 5;
            this.numericUpDownPinmux0.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownPinmux0.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownPinmux0.ValueChanged += new System.EventHandler(this.numericUpDownPinmux_ValueChanged);
            // 
            // labelAppFile
            // 
            this.labelAppFile.AutoSize = true;
            this.labelAppFile.Location = new System.Drawing.Point(12, 272);
            this.labelAppFile.Name = "labelAppFile";
            this.labelAppFile.Size = new System.Drawing.Size(112, 13);
            this.labelAppFile.TabIndex = 15;
            this.labelAppFile.Text = "[Core] Application File:";
            // 
            // buttonBrowseFile
            // 
            this.buttonBrowseFile.Location = new System.Drawing.Point(439, 268);
            this.buttonBrowseFile.Name = "buttonBrowseFile";
            this.buttonBrowseFile.Size = new System.Drawing.Size(25, 20);
            this.buttonBrowseFile.TabIndex = 16;
            this.buttonBrowseFile.Text = "...";
            this.buttonBrowseFile.UseVisualStyleBackColor = true;
            this.buttonBrowseFile.Click += new System.EventHandler(this.buttonBrowseFile_Click);
            // 
            // textBoxAppFiles
            // 
            this.textBoxAppFiles.Location = new System.Drawing.Point(132, 269);
            this.textBoxAppFiles.Name = "textBoxAppFiles";
            this.textBoxAppFiles.Size = new System.Drawing.Size(288, 20);
            this.textBoxAppFiles.TabIndex = 17;
            this.textBoxAppFiles.Text = "C:\\dsp_app.out";
            this.textBoxAppFiles.TextChanged += new System.EventHandler(this.textBoxAppFiles_TextChanged);
            // 
            // buttonAddFile
            // 
            this.buttonAddFile.Location = new System.Drawing.Point(470, 268);
            this.buttonAddFile.Name = "buttonAddFile";
            this.buttonAddFile.Size = new System.Drawing.Size(25, 20);
            this.buttonAddFile.TabIndex = 18;
            this.buttonAddFile.Text = "+";
            this.buttonAddFile.UseVisualStyleBackColor = true;
            this.buttonAddFile.Click += new System.EventHandler(this.buttonBrowseFile_Click);
            // 
            // textBoxAISfile
            // 
            this.textBoxAISfile.Location = new System.Drawing.Point(132, 295);
            this.textBoxAISfile.Name = "textBoxAISfile";
            this.textBoxAISfile.Size = new System.Drawing.Size(288, 20);
            this.textBoxAISfile.TabIndex = 21;
            this.textBoxAISfile.Text = "C:\\oh_my.h";
            this.textBoxAISfile.TextChanged += new System.EventHandler(this.textBoxAISfile_TextChanged);
            // 
            // labelAISfile
            // 
            this.labelAISfile.AutoSize = true;
            this.labelAISfile.Location = new System.Drawing.Point(13, 298);
            this.labelAISfile.Name = "labelAISfile";
            this.labelAISfile.Size = new System.Drawing.Size(81, 13);
            this.labelAISfile.TabIndex = 22;
            this.labelAISfile.Text = "AIS Output File:";
            // 
            // buttonAISbrowseFile
            // 
            this.buttonAISbrowseFile.Location = new System.Drawing.Point(439, 295);
            this.buttonAISbrowseFile.Name = "buttonAISbrowseFile";
            this.buttonAISbrowseFile.Size = new System.Drawing.Size(25, 20);
            this.buttonAISbrowseFile.TabIndex = 23;
            this.buttonAISbrowseFile.Text = "...";
            this.buttonAISbrowseFile.UseVisualStyleBackColor = true;
            this.buttonAISbrowseFile.Click += new System.EventHandler(this.buttonAISbrowseFile_Click);
            // 
            // buttonGenerateAIS
            // 
            this.buttonGenerateAIS.Location = new System.Drawing.Point(375, 321);
            this.buttonGenerateAIS.Name = "buttonGenerateAIS";
            this.buttonGenerateAIS.Size = new System.Drawing.Size(120, 24);
            this.buttonGenerateAIS.TabIndex = 24;
            this.buttonGenerateAIS.Text = "Generate AIS";
            this.buttonGenerateAIS.UseVisualStyleBackColor = true;
            this.buttonGenerateAIS.Click += new System.EventHandler(this.buttonGenerateAIS_Click);
            // 
            // labelMessage
            // 
            this.labelMessage.AutoSize = true;
            this.labelMessage.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelMessage.Location = new System.Drawing.Point(13, 327);
            this.labelMessage.Name = "labelMessage";
            this.labelMessage.Size = new System.Drawing.Size(51, 13);
            this.labelMessage.TabIndex = 25;
            this.labelMessage.Text = "[Ready]";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(506, 356);
            this.Controls.Add(this.labelMessage);
            this.Controls.Add(this.buttonGenerateAIS);
            this.Controls.Add(this.buttonAISbrowseFile);
            this.Controls.Add(this.labelAISfile);
            this.Controls.Add(this.textBoxAISfile);
            this.Controls.Add(this.buttonAddFile);
            this.Controls.Add(this.textBoxAppFiles);
            this.Controls.Add(this.buttonBrowseFile);
            this.Controls.Add(this.labelAppFile);
            this.Controls.Add(this.tabControlConfig);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximumSize = new System.Drawing.Size(514, 390);
            this.MinimumSize = new System.Drawing.Size(514, 390);
            this.Name = "MainForm";
            this.Text = "AISgen for D800K002";
            this.Load += new System.EventHandler(this.FormLoad);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tabControlConfig.ResumeLayout(false);
            this.tabPageGeneral.ResumeLayout(false);
            this.tabPageGeneral.PerformLayout();
            this.tabPageFlash.ResumeLayout(false);
            this.tabPageFlash.PerformLayout();
            this.tabPagePeripheral.ResumeLayout(false);
            this.tabPagePeripheral.PerformLayout();
            this.tabPagePLL0.ResumeLayout(false);
            this.tabPagePLL0.PerformLayout();
            this.tabPageSDRAM.ResumeLayout(false);
            this.tabPageSDRAM.PerformLayout();
            this.tabPagePLL1.ResumeLayout(false);
            this.tabPagePLL1.PerformLayout();
            this.tabPageDDR2.ResumeLayout(false);
            this.tabPageDDR2.PerformLayout();
            this.tabPageLPSC.ResumeLayout(false);
            this.tabPageLPSC.PerformLayout();
            this.tabPagePinmux.ResumeLayout(false);
            this.tabPagePinmux.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux19)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux18)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux17)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux16)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux15)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux14)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux13)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux12)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux11)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux10)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux9)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux8)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux7)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux6)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPinmux0)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelBootType;
        private System.Windows.Forms.Label labelBootMode;
        private System.Windows.Forms.Label labelClockSource;
        private System.Windows.Forms.ComboBox comboBoxBootType;
        private System.Windows.Forms.ComboBox comboBoxBootMode;
        private System.Windows.Forms.ComboBox comboBoxClockSource;
        private System.Windows.Forms.Label labelInputClockMHz;
        private System.Windows.Forms.CheckBox checkBoxPLL0;
        private System.Windows.Forms.CheckBox checkBoxDDR2;
        private System.Windows.Forms.CheckBox checkBoxSDRAM;
        private System.Windows.Forms.CheckBox checkBoxCRC;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveConfigToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadConfigToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.TabControl tabControlConfig;
        private System.Windows.Forms.TabPage tabPagePeripheral;
        private System.Windows.Forms.TabPage tabPagePLL0;
        private System.Windows.Forms.TabPage tabPagePLL1;
        private System.Windows.Forms.TabPage tabPageDDR2;
        private System.Windows.Forms.TabPage tabPageSDRAM;
        private System.Windows.Forms.Label labelPLL0postDiv;
        private System.Windows.Forms.Label labelPLL0preDiv;
        private System.Windows.Forms.Label labelPLL0mult;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelPLL0div7;
        private System.Windows.Forms.Label labelPLL0div3;
        private System.Windows.Forms.TabPage tabPageGeneral;
        private System.Windows.Forms.CheckBox checkBoxPLL1;
        private System.Windows.Forms.Label labelPLL1div3;
        private System.Windows.Forms.Label labelPLL1div2;
        private System.Windows.Forms.Label labelPLL1div1;
        private System.Windows.Forms.Label labelPLL1postDiv;
        private System.Windows.Forms.Label labelPLL1mult;
        private System.Windows.Forms.Label labelPLL0emac;
        private System.Windows.Forms.Label labelPLL0sdram;
        private System.Windows.Forms.Label labelPLL0cpu;
        private System.Windows.Forms.Label labelPLL0emacMHz;
        private System.Windows.Forms.Label labelPLL0sdramMHz;
        private System.Windows.Forms.Label labelPLL0cpuMHz;
        private System.Windows.Forms.Label labelPLL1ddr2MHz;
        private System.Windows.Forms.Label labelPLL1ddr2;
        private System.Windows.Forms.Label labelPeriphClockHz;
        private System.Windows.Forms.Label labelPeriphClock;
        private System.Windows.Forms.Label labelPeriphModuleClockMHz;
        private System.Windows.Forms.Label labelPeriphModuleClock;
        private System.Windows.Forms.TextBox textBoxPeriphClockActual;
        private System.Windows.Forms.Label labelSDRAMsdbcr;
        private System.Windows.Forms.CheckBox checkBoxSDRAMdiv;
        private System.Windows.Forms.Label labelSDRAMclockMHz;
        private System.Windows.Forms.Label labelSDRAMclock;
        private System.Windows.Forms.Label labelSDRAMsdrcr;
        private System.Windows.Forms.Label labelSDRAMsdrsrpdexit;
        private System.Windows.Forms.Label labelSDRAMsdtmr;
        private System.Windows.Forms.Label labelDDR2sdrcr;
        private System.Windows.Forms.Label labelDDR2sdtimr2;
        private System.Windows.Forms.Label labelDDR2sdtimr;
        private System.Windows.Forms.Label labelDDR2sdcr;
        private System.Windows.Forms.CheckBox checkBoxDDR2directClock;
        private System.Windows.Forms.Label labelDDR2clockMHz;
        private System.Windows.Forms.Label labelDDR2clock;
        private System.Windows.Forms.Label labelDDR2phy;
        private System.Windows.Forms.Label labelAppFile;
        private System.Windows.Forms.Button buttonBrowseFile;
        private System.Windows.Forms.Button buttonAddFile;
        private System.Windows.Forms.CheckBox checkBoxSpecifyEntrypoint;
        private System.Windows.Forms.Label labelAISfile;
        private System.Windows.Forms.Button buttonAISbrowseFile;
        private System.Windows.Forms.Button buttonGenerateAIS;
        private System.Windows.Forms.Label labelMessage;
        private System.Windows.Forms.CheckBox checkBoxPeriphSeqRead;
        public System.Windows.Forms.TextBox textBoxClockSpeed;
        public System.Windows.Forms.TextBox textBoxPLL0mult;
        public System.Windows.Forms.TextBox textBoxPLL0postDiv;
        public System.Windows.Forms.TextBox textBoxPLL0preDiv;
        public System.Windows.Forms.TextBox textBoxPLL0div1;
        public System.Windows.Forms.TextBox textBoxPLL0div7;
        public System.Windows.Forms.TextBox textBoxPLL0div3;
        public System.Windows.Forms.TextBox textBoxPLL1div3;
        public System.Windows.Forms.TextBox textBoxPLL1div2;
        public System.Windows.Forms.TextBox textBoxPLL1div1;
        public System.Windows.Forms.TextBox textBoxPLL1postDiv;
        public System.Windows.Forms.TextBox textBoxPLL1mult;
        public System.Windows.Forms.TextBox textBoxPLL0emac;
        public System.Windows.Forms.TextBox textBoxPLL0sdram;
        public System.Windows.Forms.TextBox textBoxPLL0cpu;
        public System.Windows.Forms.TextBox textBoxPLL1ddr2;
        public System.Windows.Forms.TextBox textBoxPeriphClockIdeal;
        public System.Windows.Forms.TextBox textBoxPeriphModuleClock;
        public System.Windows.Forms.TextBox textBoxSDRAMsdbcr;
        public System.Windows.Forms.TextBox textBoxSDRAMclock;
        public System.Windows.Forms.TextBox textBoxSDRAMsdrcr;
        public System.Windows.Forms.TextBox textBoxSDRAMsdrsrpdexit;
        public System.Windows.Forms.TextBox textBoxSDRAMsdtmr;
        public System.Windows.Forms.TextBox textBoxDDR2sdrcr;
        public System.Windows.Forms.TextBox textBoxDDR2sdtimr2;
        public System.Windows.Forms.TextBox textBoxDDR2sdtimr;
        public System.Windows.Forms.TextBox textBoxDDR2sdcr;
        public System.Windows.Forms.TextBox textBoxDDR2clock;
        public System.Windows.Forms.TextBox textBoxDDR2phy;
        public System.Windows.Forms.TextBox textBoxAppFiles;
        public System.Windows.Forms.TextBox textBoxSpecifyEntrypoint;
        public System.Windows.Forms.TextBox textBoxAISfile;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.CheckBox checkBoxLPSC;
        private System.Windows.Forms.CheckBox checkBoxPinmux;
        private System.Windows.Forms.TabPage tabPageLPSC;
        private System.Windows.Forms.TabPage tabPagePinmux;
        private System.Windows.Forms.Label labelLpsc0SyncRst;
        private System.Windows.Forms.Label labelLpsc0Disable;
        private System.Windows.Forms.Label labelLpsc0enable;
        private System.Windows.Forms.Label labelLpsc1;
        private System.Windows.Forms.Label labelLpsc0;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux0;
        public System.Windows.Forms.TextBox textBoxPinmuxVal3;
        private System.Windows.Forms.Label labelPinmuxReg4;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux3;
        public System.Windows.Forms.TextBox textBoxPinmuxVal2;
        private System.Windows.Forms.Label labelPinmuxReg3;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux2;
        public System.Windows.Forms.TextBox textBoxPinmuxVal1;
        private System.Windows.Forms.Label labelPinmuxReg2;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux1;
        public System.Windows.Forms.TextBox textBoxPinmuxVal0;
        private System.Windows.Forms.Label labelPinmuxReg1;
        public System.Windows.Forms.TextBox textBoxPinmuxVal4;
        private System.Windows.Forms.Label labelPinmuxReg5;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux4;
        public System.Windows.Forms.TextBox textBoxPinmuxVal19;
        private System.Windows.Forms.Label labelPinmuxReg20;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux19;
        public System.Windows.Forms.TextBox textBoxPinmuxVal18;
        private System.Windows.Forms.Label labelPinmuxReg19;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux18;
        public System.Windows.Forms.TextBox textBoxPinmuxVal17;
        private System.Windows.Forms.Label labelPinmuxReg18;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux17;
        public System.Windows.Forms.TextBox textBoxPinmuxVal16;
        private System.Windows.Forms.Label labelPinmuxReg17;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux16;
        public System.Windows.Forms.TextBox textBoxPinmuxVal15;
        private System.Windows.Forms.Label labelPinmuxReg16;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux15;
        public System.Windows.Forms.TextBox textBoxPinmuxVal14;
        private System.Windows.Forms.Label labelPinmuxReg15;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux14;
        public System.Windows.Forms.TextBox textBoxPinmuxVal13;
        private System.Windows.Forms.Label labelPinmuxReg14;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux13;
        public System.Windows.Forms.TextBox textBoxPinmuxVal12;
        private System.Windows.Forms.Label labelPinmuxReg13;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux12;
        public System.Windows.Forms.TextBox textBoxPinmuxVal11;
        private System.Windows.Forms.Label labelPinmuxReg12;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux11;
        public System.Windows.Forms.TextBox textBoxPinmuxVal10;
        private System.Windows.Forms.Label labelPinmuxReg11;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux10;
        public System.Windows.Forms.TextBox textBoxPinmuxVal9;
        private System.Windows.Forms.Label labelPinmuxReg10;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux9;
        public System.Windows.Forms.TextBox textBoxPinmuxVal8;
        private System.Windows.Forms.Label labelPinmuxReg9;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux8;
        public System.Windows.Forms.TextBox textBoxPinmuxVal7;
        private System.Windows.Forms.Label labelPinmuxReg8;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux7;
        public System.Windows.Forms.TextBox textBoxPinmuxVal6;
        private System.Windows.Forms.Label labelPinmuxReg7;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux6;
        public System.Windows.Forms.TextBox textBoxPinmuxVal5;
        private System.Windows.Forms.Label labelPinmuxReg6;
        private System.Windows.Forms.NumericUpDown numericUpDownPinmux5;
        public System.Windows.Forms.TextBox textBoxLps1SyncRst;
        public System.Windows.Forms.TextBox textBoxLps1Disable;
        public System.Windows.Forms.TextBox textBoxLps1Enable;
        public System.Windows.Forms.TextBox textBoxLps0SyncRst;
        public System.Windows.Forms.TextBox textBoxLps0Disable;
        public System.Windows.Forms.TextBox textBoxLps0Enable;
        private System.Windows.Forms.ToolStripMenuItem restoreDefaultsToolStripMenuItem;
        private System.Windows.Forms.TabPage tabPageFlash;
        public System.Windows.Forms.TextBox textBoxFlashTiming;
        private System.Windows.Forms.Label labelFlashTiming;
        private System.Windows.Forms.Label labelFlashWidth;
        private System.Windows.Forms.ComboBox comboBoxFlashWidth;
    }
}

