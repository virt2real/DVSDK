#!/usr/local/bin/perl5.8.0 -w
###############################################################################################
# Copyright 2004, All Rights Reserved, Texas Instruments Incorporated
#
# genAIS.pl
#
# Generates AIS command sctream for bootloading TMS320C672xx.
#
# 2005-04-01 v1.00
# - Created
# 2005-10-10 v1.01.00
# - Re-introduced using AIS BOOT TABLE commands for PLL/SDRAM/ASYNC RAM configuration
# - Fixed bug that required cfg.c file to be included
# 2005-10-25 v1.01.01
# - Fixed bug with odd byte sized sections that caused bad array reference to
#   section data when calculating CRC
# - Fixed async ram configuration problem when using boot table commands.
# 2005-Oct-27 v1.01.02
# - Fixed potential problem with creating default output file name (if none is specified
#   on command line) that specifically looks for .out extension. Changed this to use
#   generic fileparse utility to find basename of file.
# 2005-Nov-03 v1.01.03
# - Added error checking to detect sections that may overload internal ram that
#   on-chip bootloader uses for stack/data. Primarily, this affects SPI/I2C boot modes
# 2005-Nov-10 v1.01.04
# - Fixed internal ram overload detect warning
# - Fixed section type checking to stop load of COPY sections and make sure we get
#   sections created by linker "fill".
# - Added test for I2C/SPI master mode to give warning when AIS file exceeeds 64KB
# 2005-Nov-15 v1.02.00
# - Added -eepromsz and -slaveaddrs options to support booting application from
#   multiple EEPROMS for I2C Master mode. Added CreateMultiEeprom function that
#   divides the ASI stream among the EEPROMS and creates separate AIS file for
#   each device in the chain.
# 2005-Nov-16 V1.03.00
# - Modified multi-eeprom boot to use small self-modifying code to set slave
#   address and reset internal addres counter for multi-eeprom boot.
# 2005-Nov-21 v1.03.01
# - Added Warning and abort for condition where number of address pins defined
#   was not enough to configure addressing for next page
# 2006-Apr-13 V1.03.02
# - Removed debug comments from SecondaryBoot
# 2006-Apr-17 V1.30.03
# - Fixed paging for GPIO pins hen specifying FLASH pgsize option
# 2006-May-1 V1.30.04
# - Added warning to use -cfg for pin definition and fixed jump to TIBootSetup, even
#   though symbol may have been undefined.
# 2006-June-14 V1.30.05
# - Fixed problem with error checking for number of GPIO pins required to load
#   for secondary boot.
# 2007-Jan-26 V1.03.06
# - Fixed problem with parsing COFF file in identifying loadable sections
#   we now also check for value of raw data pointer to make sure that section
#   does have raw data/information in the file
# 2007-April-25 V1.03.07
# - Fixed problem with -crc 0 option. The option value as read from args, was being
#   ignored and default value of 1 for this option was always used.
# 2008-Oct-16 V1.04.00
# - Changed BOOT_TABLE (SET) command usage to reflect the PG1.2 ROM silicon
#   Note that this introuces compatibility issue with PG1.3 silicon.
#
###############################################################################################
use strict qw(subs refs);
use warnings qw(all);
use FindBin;
use FindBin;
use lib "$FindBin::Bin/../lib";
use CoffFile;
use AISFile;
use File::Basename;

my ($CFG);
my ($VERSION) = "1.03.07";
my ($dotOutFile) = "";
my ($aisOutFile) = "";
my ($useTISecondaryBoot) = 0;
my ($oType) = "ASM";
my ($cfgFile) = "";
my ($cf);
my ($entryPoint);
my ($pkgType);
my ($bootmode);
my ($pinTable) = {};
my ($sdramCfg) = {};
my ($pllCfg) = {};
my ($asyncRamcCfg) = {};
my ($pllConfigured) = 0;
my ($sdramConfigured) = 0;
my ($asyncRamConfigured) = 0;
my ($useAddressLatch) = 0;
my ($pageSize) = 1 << 13;
my ($addressShift) = 13;
my ($pincount) = 0;
my ($pinMask) = 0;
my ($debug) = 0;

#----------------------------------------------------------------------------------------------
# helpText - Displayed when user uses the -h or -hh command line options
#----------------------------------------------------------------------------------------------
my $helpText = qq{
  genAis v$VERSION:  AIS Generation Tool
    -i          => Input COFF (.out) File (REQUIRED)
    
    -o          => AIS Ouput File
                   Default ===> inputFileName.asm
                   
    -cfg        => Configuration file containing initialization for EMIF, GPIO
                   pins, PLL, or other startup conditions for boot. Using this
                   option currently requires use of TI Secondary Boot. CFG file
                   must conform to output of genBootCfg utlity.
                   
    -cfgtype    => type of configuration to use "ais" or "c"
                   if == ais, then AIS SET command will be used to effect
                   the configuration.
                   if == c, then too lassumes that cfg.c file was compiled/linked
                   with application code and will search for .TIBOOT section for
                   configuration.               
                   
    -otype      => Output file type , one of ascii, asm, bin
                   Default ===> asm
                   
    -pkg        => Package Type , One of bga, tqfp
                   Default ===> asm
                   
    -bootmode   => spimaster  => C672x is SPI Master
                   spislave   => C672x is SPI Slave
                   i2cmaster  => C672x is I2C Master
                   i2cslave   => C672x is I2C Slave
                   hpi        => HPI boot - Raw AIS stream produced
                   tisecboot  => Using TISecondary Boot Loader with Parallel Flash
                   raw       => Boot From FLASH on PADK or to generate RAW AIS stream
                   Default ===> tisecboot
                   
    -pf            => 8 , or 16 bit, relevant only when using TI Secondary Boot
                   Default ===> 8
                   
    -crc        => 0, 1, 2
                   0 ===> No CRC Generated/Enabled
                   1 ===> CRC Enabled and Generated for Each Section Load/Fill
                   2 ===> CRC Enabled, Single CRC Generated For Entire Load
                   
    -pgsize     => FLASH page size

    -eepromsz   => EEPROM size in Kbytes, required parameter for muli-eeprom boot  
                     
    -slaveaddr  => Give quoted, comma separae list of slave addresses for
                   boot requiring multiple I2C EEPROM devices i.e. -slaves \"0x23,0x24,0x25\".
                   Please mote that slave address is only specified whe more than one
                   I2C EEPROM is required for boot sequence. The first I2C EEPROM
                   MUST always use slave address 0x50. The -slaves option is used to specify
                   the slave address for any subsequent devices.
                   
    -debug      => Invokes genAIS in debug mode which produces additional information in
                   output file to allow tracking of data/addresses in flash
  Example(s)...
    genAis -i myApplication.out -o myAIStable.asm -pkg BGA -pf 8 -boomode tisecboot -cfg myApplication.cfg
    
    genAis -i myApplication.out -o myApplication.ais -otype ASCII -bootmode spimaster
};

#--------------------------------------------------------------------------------------------
# Peripheral Register Address Constant
#--------------------------------------------------------------------------------------------
my ($TIBOOT_EMIF_REGS_BASE_ADDR) = (0xF0000000);
my ($TIBOOT_EMIF_AWCCR)          = ($TIBOOT_EMIF_REGS_BASE_ADDR + 0x4);
my ($TIBOOT_EMIF_SDCR)           = ($TIBOOT_EMIF_REGS_BASE_ADDR + 0x8);
my ($TIBOOT_EMIF_SDRCR)          = ($TIBOOT_EMIF_REGS_BASE_ADDR + 0xC);
my ($TIBOOT_EMIF_A1CR)           = ($TIBOOT_EMIF_REGS_BASE_ADDR + 0x10);
my ($TIBOOT_EMIF_SDTIMR)         = ($TIBOOT_EMIF_REGS_BASE_ADDR + 0x20);
my ($TIBOOT_EMIF_SDSRETR)        = ($TIBOOT_EMIF_REGS_BASE_ADDR + 0x3C);

my ($TIBOOT_PLL_REG_BASE_ADDR)   = (0x41000000);
my ($TIBOOT_PLL_PLLCSR)          = ($TIBOOT_PLL_REG_BASE_ADDR + 0x100);
my ($TIBOOT_PLL_PLLM)            = ($TIBOOT_PLL_REG_BASE_ADDR + 0x110);
my ($TIBOOT_PLL_PLLDIV0)         = ($TIBOOT_PLL_REG_BASE_ADDR + 0x114);
my ($TIBOOT_PLL_PLLDIV1)         = ($TIBOOT_PLL_REG_BASE_ADDR + 0x118);
my ($TIBOOT_PLL_PLLDIV2)         = ($TIBOOT_PLL_REG_BASE_ADDR + 0x11C);
my ($TIBOOT_PLL_PLLDIV3)         = ($TIBOOT_PLL_REG_BASE_ADDR + 0x120);
my ($TIBOOT_PLL_PLLCMD)          = ($TIBOOT_PLL_REG_BASE_ADDR + 0x138);
my ($TIBOOT_PLL_PLLSTAT)         = ($TIBOOT_PLL_REG_BASE_ADDR + 0x13C);
my ($TIBOOT_PLL_PLLALNCTL)       = ($TIBOOT_PLL_REG_BASE_ADDR + 0x140);

my ($TIBOOT_CFGBRIDGE_REGISTER)  = (0x40000024);

my ($TIBOOT_PLLENABLE)           = (0x01);
my ($TIBOOT_PLLDISABLE)          = (0x00);
my ($TIBOOT_PLLPWRDN)            = (0x02);
my ($TIBOOT_PLLPWRUP)            = (0x00);
my ($TIBOOT_PLLOSCPWRDN)         = (0x04);
my ($TIBOOT_PLLOSCPWRUP)         = (0x00);
my ($TIBOOT_PLLRESET)            = (0x08);
my ($TIBOOT_PLLRESETRELEASE)     = (0x00);
my ($TIBOOT_PLLSTABLE)           = (0x40);
my ($TIBOOT_PLLUNSTABLE)         = (0x00);
my ($TIBOOT_PLLLOCKED)           = (0x20);
my ($TIBOOT_PLLNOTLOCKED)        = (0x00);


my ($TIBOOT_PLLGOCLR)            = (0x0000);
my ($TIBOOT_PLLGOSET)            = (0x0001);

my ($TIBOOT_PLLGODONE)           = (0x0000);
my ($TIBOOT_PLLGOWAIT)           = (0x0001);

my ($TIBOOT_PLLALN1)             = (0x0001);
my ($TIBOOT_PLLALN2)             = (0x0002);
my ($TIBOOT_PLLALN3)             = (0x0004);

my ($TIBOOT_DIVENABLED)          = (0x8000);

#my ($TIBOOT_I2C1_ICSAR)         = (0xA02A001C); # (NOTE: INCORRECT FOR c672x SERIES!)
my ($TIBOOT_I2C1_ICSAR)          = (0x4A00001C); # (fixed 4/26/08 by MSA)

my ($TIBOOT_BOOTLOADER_ADDRESS_COUNTER) = 	(0x10000738);
my ($TIBOOT_BOOTLOADER_SPI_READ_CMD)    =   (0x3); 
my ($TIBOOT_SETSLAVE_LOAD_ADDR)         = (0x10000D00);
my ($TIBOOT_SLAVEADDR_SHIFT)            = 0x7;
my ($TIBOOT_SLAVEADDR_MASK)             = 0xFFF << $TIBOOT_SLAVEADDR_SHIFT;
my ($TIBOOT_SETSLAVE_CODE_SIZE)         = 48;

my (@TIBOOT_SetSlaveAddr) = ( 
        0x02800E2A,        #    MVK.S2   0x001C, B5
        0x0200002A,        #    MVK.S2   slaveAddr, B4
#       0x02D0156A,        #    MKVH.S2  0xA02A0000, B5 (NOTE: INCORRECT FOR c672x SERIES!)
        0x02A5006A,        #    MKVH.S2  0x4A000000, B5 (fixed 4/26/08 by MSA)
        0x021402F6,        #    STW.D2T2 B4, *+B5[0]
        0x00002000,        #    NOP      2
        0x020000FB,        #    ZERO.L2  B4
        0x01839C28,        # || MVK.S1   0x0738, A3
        0x0201806B,        #    MVKH.S2  0x3000000, B4
        0x01880068,        #    MVKH.S1  0x10000000, A3
        0x020C0276,        #    STW.D1T2 B4, *+A3[0]
        0x000C0362,        #    B.S2     B3
        0x00008000         #    NOP 5
    );
    
    
my (%BOOT_TABLE_TYPE) = (
     byte => 0,
     short => 1,
     long => 2,
     field => 3,
     bits  => 4
);


#----------------------------------------------------------------------------------------------
# AIS Commands - HASH Table of AIS Commands
#----------------------------------------------------------------------------------------------

my (%AISCOMMAND) = (
    aisMagic          => 0x41504954,
    spiI2cMasterMagic => 0x41504954,
    i2cSlaveXmtStart  => 0x00000058,    
    spiSlaveXmtStart  => 0x00005853,
    spiI2cXmitSync    => 0x58535900,
    spiI2cPingDevice  => 0x5853590B,
	sectionLoad       => 0x58535901,
	requestCRC        => 0x58535902,
	enableCRC         => 0x58535903,
	disableCRC        => 0x58535904,
	jump              => 0x58535905,
	jumpAndClose      => 0x58535906,
	bootTable         => 0x58535907,
	startOver         => 0x58535908,
	reserved          => 0x58535909,
	sectionFill       => 0x5853590A,
	ping              => 0x5853590B,
	deviceCfgCommand  => 0x585359F0,	
	pageSwapCommand   => 0x585359F1,
	latchAddress      => 0x585359F2
);

#----------------------------------------------------------------------------------------------
# COFF Section Types
#----------------------------------------------------------------------------------------------

my (%SECTYPE) = (
    STYP_REG	  => 0x00000000,
    STYP_DSECT	  => 0x00000001,
    STYP_NOLOAD	  => 0x00000002,
    STYP_GROUP	  => 0x00000004,
    STYP_PAD	  => 0x00000008,
    STYP_COPY	  => 0x00000010,
    STYP_TEXT	  => 0x00000020,
    STYP_DATA	  => 0x00000040,
    STYP_BSS	  => 0x00000080,
    STYP_CLINK	  => 0x00004000,
    STYP_LOADABLE => 0x00000060
);

#----------------------------------------------------------------------------------------------
# CALL Main Application
#----------------------------------------------------------------------------------------------

main();
exit(0);

#----------------------------------------------------------------------------------------------
# Main Application
#----------------------------------------------------------------------------------------------
sub main {
	my ($args);
	$args = parseArguments (\@ARGV,
	   -i     => "",
	   -o     => "",
	   -cfg   => "",
	   -otype => "asm",
	   -pkg   => "bga",
	   -crc   => 1,
	   -sec   => 0,
	   -pf    => 8,
	   -cfgtype => 'c',
	   -bootmode => 'tisecboot',
	   -pgsize => 'default',
	   -ping   => 10,
	   -eepromsz => '',
	 );
	 
	$numSlaves = 0;
	$dotOutFile = $args->{"-i"};
	$aisOutFile = $args->{"-o"};
	$cfgFile = $args->{"-cfg"};
    $genCrc  = ($args->{"-crc"});
	$oType = uc($args->{"-otype"});	
	$pkgType = uc($args->{"-pkg"});
	$bootmode = lc($args->{"-bootmode"});
	$cfgType = uc($args->{"-cfgtype"});
	$pfSize  = ($args->{"-pf"});
	$debug   = ($args->{"-debug"}) ? 1 : 0; 
	$ping    = ($args->{"-ping"}) ? ($args->{'-ping'}) : 10;
		
	$pageSize = 1 << 12 if ($pkgType eq 'TQFP');
	$pageSize = oct($args->{"-pgsize"}) if ($args->{"-pgsize"} ne 'default');
	$pageSize = ($pageSize << 2)if ($args->{"-pgsize"} eq 'default') ;	
	$eepromSize = ($args->{"-eepromsz"}) ? ($args->{"-eepromsz"}) : 64;
	$eepromSize = $eepromSize * 1024;
	@slaveAddr = split (/,/, ($args->{"-slaveaddrs"})) if ($args->{"-slaveaddrs"});
	$numSlaves = @slaveAddr;
	
	
	for($i = 0 ; $i < $numSlaves ; ++$i) {
		$slaveAddr[$i] = oct($slaveAddr[$i]);
	}
	
	
	$addressShift = 12 if ($pkgType eq 'TQFP');
	$addressShift += 2 if ($pfSize eq 16);
	
	$useTISecondaryBoot = 1 if ($bootmode eq 'tisecboot');
	
	if (($bootmode eq 'tisecboot') && ($genCrc eq 2)) {
		printf (STDERR "Error - global CRC (- crc 2) Not Supported for this mode\n");
		printf (STDERR "      Using -crc 1\n");
		$genCrc = '1';
	}
	 
	if ($dotOutFile eq "") {
		printf (STDERR "Error - no input file specified\n");
		doHelp($helpText);
    }
    
	if (-e $dotOutFile) {
	   $cf = CoffFile->new($dotOutFile);
    } else {
	   printf (STDERR "Specified input file, $dotOutFile, does not exist\n");
	   exit(1);
    }
    
    if ($cfgFile ne "") {
        open($CFG,"<$cfgFile") || die "Couldn't open '$cfgFile' for reading";
     }
 
     $aisExtension = ($oType eq "ASM")? "asm" : "ais";
     
     if ($aisOutFile eq "") {
	     $aisOutFile = $dotOutFile;
	     ($aisOutFile, $tmpPath) = fileparse($dotOutFile, ('\.\S*'));
	     $aisOutFile = $tmpPath."/".$aisOutFile.".".$aisExtension;
     }
 
    CreateCFGTable($CFG,$args) if ($cfgFile ne "");
    CreateSecondaryBootAISStream() if ($useTISecondaryBoot);
    CreateRawFlashAisStream() if ($bootmode eq 'raw');
    CreateMultiEeprom() if (($bootmode eq 'i2cmaster') && ($numSlaves != 0));
    CreateAISStream() if ((!$useTISecondaryBoot) && ($bootmode ne 'raw') && ($numSlaves == 0));
    
    printf "\tAIS File Generation Complete\n";
    close($CFG) if ($cfgFile ne "");
    CoffFile->delete($cf);
}

#--------------------------------------------------------------------------------------------
sub CreateCFGTable {
	my ($CFG) = shift(@_);
	my ($args) = @_;
	my ($lineCnt);
	my ($address);
	my ($dataType);
	my ($val);
	my ($doze);
	my ($pinEnableReg);
	my ($pinEnableMask);
	my ($pinEnableMaskMode);
	my ($pinDirectionReg);
	my ($pinDirectionMask);
	my ($pinDirectionMaskMode);
	my ($pinSetReg);
	my ($pinSetMask);
	my ($pinSetMaskMode);
	my ($pinClearReg);
	my ($pinClearMask);
	my ($pinClearMaskMode);
	my ($pinDisableReg);
	my ($pinDisableMask);
	my ($pinDisableMaskMode);
	my ($pinGlobalSetupFlag);
	my ($i);
	my ($tlArgs);
	my ($linesPerEntry) = 9;
	my ($iline) = "";
	my ($j);
	my ($numSets) = 0;

	

    $lineCnt = 0;
        
	while ($iline = <$CFG>) {
	    # skip line if it begins with a comment
	    next if ($iline =~ m/^\s*\#/);
	    
	    # skip if blank line
	    $tmpLine = $iline;
	    $tmpLine =~ s/[\n\r\f]//g;
	    
	    next if ($tmpLine eq '');
	    
	    # Check for end of data marker
	    last if ($iline =~ m/^\s*<END>/);
	    # Remove trailing comment
	    $iline =~ s/\#.*//;
	    
	    # get test case name and options, skip line if it doesn't contain one	    
	    next if ($iline !~ m/^(\s*\-\s*\w*)*/);
	    $tlOptions = $iline;
	    # Merge options from tl file into args hash
	    $tlArgs = parseOptionsString($tlOptions,%$args);
	    %$args = (%$args, %$tlArgs);
    }
    
    # Check For All Imported Data, If Found set the value from Imported File
    # Otherwise set value to default
 
    $pincount = ($tlArgs->{-pincount}) ? oct($tlArgs->{-pincount}) : 0;
    $useAddressLatch = ($tlArgs->{-useAddressLatch}) ? oct($tlArgs->{-useAddressLatch}) : 0;
    $asyncRamConfigured = $tlArgs->{-asyncRamCfg} ? oct($tlArgs->{-asyncRamCfg}) : 0;
    $sdramConfigured = $tlArgs->{-sdramCfg} ? oct($tlArgs->{-sdramCfg}) : 0;
    $pllConfigured   = $tlArgs->{-pllCfg} ? oct($tlArgs->{-pllCfg}) : 0;
    
    if ($pllConfigured) {
	    $pllCfg{osc} = $tlArgs->{-pllcfgosc} ? $tlArgs->{-pllcfgosc} : 25.0;                        
	    $pllCfg{pllm} = $tlArgs->{-pllcfgpllm} ? oct($tlArgs->{-pllcfgpllm}) : 0;
	    $pllCfg{div0} = $tlArgs->{-pllcfgdiv0} ? oct($tlArgs->{-pllcfgdiv0}) : 0; 
	    $pllCfg{div1} = $tlArgs->{-pllcfgdiv1} ? oct($tlArgs->{-pllcfgdiv1}) : 0; 
	    $pllCfg{div2} = $tlArgs->{-pllcfgdiv2} ? oct($tlArgs->{-pllcfgdiv2}) : 0; 
	    $pllCfg{div3} = $tlArgs->{-pllcfgdiv3} ? oct($tlArgs->{-pllcfgdiv3}) : 0; 	    	    
    }
    
    if ($asyncRamConfigured) {
	    $asyncRamCfg{a1cr} = $tlArgs->{-asyncRamA1CR} ? oct($tlArgs->{-asyncRamA1CR}) : 0;
	    $asyncRamCfg{awccr} = $tlArgs->{-asyncRamAWCCR} ? oct($tlArgs->{-asyncRamAWCCR}) : 0;
    } 
    
    if ($sdramConfigured) {
	    $sdramCfg{sdcr} = $tlArgs->{-sdramSDCR} ? oct($tlArgs->{-sdramSDCR}) : 0;
	    $sdramCfg{sdrcr} = $tlArgs->{-sdramSDRCR} ? oct($tlArgs->{-sdramSDRCR}) : 0;
	    $sdramCfg{sdtimr} = $tlArgs->{-sdramSDTIMR} ? oct($tlArgs->{-sdramSDTIMR}) : 0;
	    $sdramCfg{sdsretr} = $tlArgs->{-sdramSDSRETR} ? oct($tlArgs->{-sdramSDSRETR}) : 0;
	    
    }
		     
    for($i=0;$i<$pincount;$i++) {
	    $pinEnableReg = '-pinEnableReg'.$i;
	    $pinEnableMask = '-pinEnableMask'.$i;
	    $pinEnableMaskMode = '-pinEnableMaskMode'.$i;
	    $pinDirectionReg = '-pinDirectionReg'.$i;
	    $pinDirectionMask ='-pinDirectionMask'.$i;
	    $pinDirectionMaskMode = '-pinDirectionMaskMode'.$i;
	    $pinSetReg = '-pinSetReg'.$i;
	    $pinSetMask = '-pinSetMask'.$i;
	    $pinSetMaskMode = '-pinSetMode'.$i;
	    $pinClearReg = '-pinClearReg'.$i;
	    $pinClearMask = '-pinClearMask'.$i;
	    $pinClearMaskMode = '-pinClearMode'.$i;
	    $pinDisableReg = '-pinDisableReg'.$i;
	    $pinDisableMask = '-pinDisableMask'.$i;
	    $pinDisableMaskMode = '-pinDisableMode'.$i;
	    $pinGlobalSetupFlag = '-pinGlobalSetupFlag'.$i;
	    
	    
	    $pinTable[$i]{'pinEnableRegister'} = ($tlArgs->{$pinEnableReg}) ? oct($tlArgs->{$pinEnableReg}) : 0;
 	    $pinTable[$i]{'pinEnableMask'} = ($tlArgs->{$pinEnableMask}) ? oct($tlArgs->{$pinEnableMask}) : 0;
	    $pinTable[$i]{'pinEnableMaskMode'} = ($tlArgs->{$pinEnableMaskMode}) ? oct($tlArgs->{$pinEnableMaskMode}) : 0;

	    $pinTable[$i]{'pinDirectionRegister'} = ($tlArgs->{$pinDirectionReg}) ? oct($tlArgs->{$pinDirectionReg}) : 0;
 	    $pinTable[$i]{'pinDirectionMask'} = ($tlArgs->{$pinDirectionMask}) ? oct($tlArgs->{$pinDirectionMask}) : 0;
	    $pinTable[$i]{'pinDirectionMaskMode'} = ($tlArgs->{$pinDirectionMaskMode}) ? oct($tlArgs->{$pinDirectionMaskMode}) : 0;

	    $pinTable[$i]{'pinSetRegister'} = ($tlArgs->{$pinSetReg}) ? oct($tlArgs->{$pinSetReg}) : 0;
 	    $pinTable[$i]{'pinSetMask'} = ($tlArgs->{$pinSetMask}) ? oct($tlArgs->{$pinSetMask}) : 0;
	    $pinTable[$i]{'pinSetMaskMode'} = ($tlArgs->{$pinSetMaskMode}) ? oct($tlArgs->{$pinSetMaskMode}) : 0;

	    $pinTable[$i]{'pinClearRegister'} = ($tlArgs->{$pinClearReg}) ? oct($tlArgs->{$pinClearReg}) : 0;
 	    $pinTable[$i]{'pinClearMask'} = ($tlArgs->{$pinClearMask}) ? oct($tlArgs->{$pinClearMask}) : 0;
	    $pinTable[$i]{'pinClearMaskMode'} = ($tlArgs->{$pinClearMaskMode}) ? oct($tlArgs->{$pinClearMaskMode}) : 0;

	    $pinTable[$i]{'pinDisableRegister'} = ($tlArgs->{$pinDisableReg}) ? oct($tlArgs->{$pinDisableReg}) : 0;
 	    $pinTable[$i]{'pinDisableMask'} = ($tlArgs->{$pinDisableMask}) ? oct($tlArgs->{$pinDisableMask}) : 0;
	    $pinTable[$i]{'pinDisableMaskMode'} = ($tlArgs->{$pinDisableMaskMode}) ? oct($tlArgs->{$pinDisableMaskMode}) : 0;	
	    $pinTable[$i]{'pinGlobalSetupFlag'} = ($tlArgs->{$pinGlobalSetupFlag}) ? oct($tlArgs->{$pinGlobalSetupFlag}) : 0;	        
	
	    if ($pinTable[$i]{'pinGlobalSetupFlag'} ne 0) {
		    $numSets = $pinTable[$i]{'pinGlobalSetupFlag'};
		    for($j = 0; $j < $numSets; ++$j) {
			    $pinRegAddr = '-pinRegAddr'.$i.'_'.$j;
			    $pinRegVal = '-pinRegVal'.$i.'_'.$j;
			    $pinRegSetMode = '-pinRegSetMode'.$i.'_'.$j;
	            $pinTable[$i]{'pinGlobalSetup'}[$j]{'regAddr'}    = ($tlArgs->{$pinRegAddr})    ? oct($tlArgs->{$pinRegAddr}) : 0;	        
	            $pinTable[$i]{'pinGlobalSetup'}[$j]{'regVal'}     = ($tlArgs->{$pinRegVal})     ? oct($tlArgs->{$pinRegVal}) : 0;	        
	            $pinTable[$i]{'pinGlobalSetup'}[$j]{'regSetMode'} = ($tlArgs->{$pinRegSetMode}) ? oct($tlArgs->{$pinRegSetMode}) : 0;	        
		    }
	    }
			    
			                
   }  
   
    $pkgType = ($tlArgs->{'-pkg'}) ? ($tlArgs->{'-pkg'}) : $pkgType;
    
   return;
}

#--------------------------------------------------------------------------------------------
sub CreateAISStream {
    my ($numSections);
	my ($runAddr);
	my ($secName);
	my ($secSize);
	my ($entryPoint);
	my ($count);
	my ($sizeOfRequestCrc) = 4 * 3;
	my ($sizeOfSectionLoad) = 4 * 3;
	my ($seek) = 0;
	my ($crcVal) = 0;
	my ($byteCount) = 0;
	my ($fh);
	my ($writeFn);
	my ($i);
	my ($TIBoot) = 0;
	my ($TIBootSetupAddr) = '';
	my ($TIBootSecSize) = 0;
	my ($TIBootSetupSym) = {};
	my ($secDataPtr) = 0;
	
	$numSections = $cf->{"header"}{"numSectionHeaders"};
    $entryPoint = $cf->{"header"}{"optEntryPoint"};
    $TIBootSetupAddr = '';
    
    $AIS = AISFile->new($aisOutFile, $oType, ">", $debug);
    $fh = $AIS->{'fh'};
    $writeFn = $AIS->{'write'};

    
	&$writeFn($AIS,$AISCOMMAND{"aisMagic"},\$byteCount);
        
    if (($bootmode eq 'i2cslave')) {
	 &$writeFn($AIS,$AISCOMMAND{"i2cSlaveXmtStart"},\$byteCount);
    }

    if (($bootmode eq 'spislave')) {
	 &$writeFn($AIS,$AISCOMMAND{"spiSlaveXmtStart"},\$byteCount);
    }            
    
     if (($bootmode eq 'i2cslave') || ($bootmode eq 'spislave')) {
	   &$writeFn($AIS,$AISCOMMAND{"spiI2cPingDevice"},\$byteCount);
	   &$writeFn($AIS,$ping,\$byteCount);
	   for($i = 1; $i <= $ping; ++$i) {
	     &$writeFn($AIS,$i,\$byteCount);
       }
    }   
    
    if ($cfgType eq 'AIS') {
       if (($pllConfigured == 1) || ($asyncRamConfigured == 1) || ($sdramConfigured == 1)) {
	       genBootTableCommands($AIS, $byteCount);
       }
    }    
        
    if ($genCrc eq 1) {
	    &$writeFn($AIS,$AISCOMMAND{enableCRC},\$byteCount);
    }
       
    for ($secNum = 0; $secNum < $numSections; ++$secNum) {
	   $secName = $cf->{"sections"}[$secNum]{"name"};
       if ($secName eq '.TIBoot') {
	       $TIBoot = $secNum;
           $TIBootSecSize = $cf->{"sections"}[$TIBoot]{"byteSize"};
	       $TIBootSetupSym = $cf->symFind("_TIBootSetup");
	       if (defined($TIBootSetupSym)) {
	           $TIBootSetupAddr = $TIBootSetupSym->{"value"};
		       
	       } else {
		       $TIBootSetupAddr = 0;
           }
       }
    }
    
    if (($TIBoot) && ($TIBootSecSize != 0)) {
	   $secName = $cf->{"sections"}[$TIBoot]{"name"};
	   $runAddr = $cf->{"sections"}[$TIBoot]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$TIBoot]{"wordSize"}) * 4;
       $secData = $cf->secRead($TIBoot);
       $secSize += 3;
       $secSize ^= 3;
       
       if ($oType eq 'ASM') {
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
          printf $fh ";;;   Loading .TIBoot Section\n";
          printf $fh ";;;   Current FLASH Address: 0x%08X\n",$byteCount;
          printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"; 
       }  
       
       &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$byteCount);
	   &$writeFn($AIS,$runAddr,\$byteCount);
	   &$writeFn($AIS,$secSize,\$byteCount);
	                      
       for ($count = 0; $count < (int ($secSize/4)); ++$count) {
	      &$writeFn($AIS,$secData->[$count],\$byteCount);
       }
       $seek = int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc); 

       $crcVal = 0 if ($genCrc eq 1);
	   $crcVal = calcCrcWord($runAddr,$crcVal);
	   $crcVal = calcCrcWord($secSize,$crcVal);	   
	   $crcVal = calcCrcSection($secData,$secSize,$crcVal,0);
				
	   if ($genCrc eq 1) {
	       if ($oType eq "ASM") {
	           printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	           printf $fh ";;; Requesting CRC\n";
	           printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
	           printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	           printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	       }
		            
	       &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$byteCount);
	       &$writeFn($AIS,$crcVal,\$byteCount);
	       &$writeFn($AIS,0-($seek),\$byteCount);
	  }
	  
	  if ($TIBootSetupAddr ne 0) {
	      if ($oType eq 'ASM') {
	          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	          printf $fh ";;;   Placing Jump Command\n";
	          printf $fh ";;;   Current FLASH Address: 0x%08X\n", $byteCount;
	          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	      } 
	      
		   &$writeFn($AIS,$AISCOMMAND{jump},\$byteCount);
		   &$writeFn($AIS,$TIBootSetupAddr,\$byteCount);
	  }
    }
      
    for ($secNum = 0; $secNum < $numSections; ++$secNum) {
	   $secName = $cf->{"sections"}[$secNum]{"name"};

	   $runAddr = $cf->{"sections"}[$secNum]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$secNum]{"wordSize"}) * 4;
       $secDataPtr = $cf->{"sections"}[$secNum]{"dataPtr"};
       
       $secSize += 3;
       $secSize ^= 3;
       
       $flags = $cf->{"sections"}[$secNum]{"flags"};
       $sType = $flags & 0xFF;
             
      if ((($secSize != 0)&&($secDataPtr != 0)) && ($secName ne '.TIBoot') && ($secName ne '.TIBootStrap')){
         if ((($sType & $SECTYPE{"STYP_NOLOAD"})== 0) 
             && (($sType & $SECTYPE{"STYP_DSECT"}) == 0)
             && (($sType & $SECTYPE{"STYP_BSS"}) == 0)
             && (($sType & $SECTYPE{"STYP_COPY"}) == 0)
             && ((($sType & $SECTYPE{"STYP_LOADABLE"}) ||
                 (($sType == $SECTYPE{"STYP_REG"}) && ($secSize != 0))))){

	             
	           
	         if ($runAddr == 0) {
		         printf STDERR "RUNADDR == 0, for section :%s:\n",$secName;
		         printf STDERR " section flags == 0x%08x",$flags;
	         }
	             	             
             if ($oType eq "ASM") {
	            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	            printf $fh ";;; Loading %s:\n",$secName;
	            printf $fh ";;;   Run/CopyTo Address: 0x%08X\n",$runAddr;
	            printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
             }
	         
             &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$byteCount);
	         &$writeFn($AIS,$runAddr,\$byteCount);
	         &$writeFn($AIS,$secSize,\$byteCount);
	          
             if (   (($runAddr <= 0x10000400) && (($runAddr + $secSize) >= 0x10000400))
                 || (($runAddr >= 0x10000400) && (($runAddr) < 0x10001000))
                 ){
	             printf STDERR "!!!!WARNING, Section, \"%s\" ,falls in restricted memory range\n",
	             $secName;
	             printf STDERR "\tSection start address = 0x%08X, secSize = 0x%08X\n",
	             $runAddr, $secSize;
	             printf STDERR "\tMemory space (0x10000400-0x10000FFF)is reserved at boot-up for use by\n";
	             printf STDERR "\tthe on-chip bootloader\n";
	             printf STDERR "!!!Aborting AIS translation\n";
	             
	             printf $fh "!!!!WARNING, Section, \"%s\" ,falls in restricted memory range\n",
	             $secName;
	             printf $fh "\tSection start address = 0x%08X, secSize = 0x%08X\n",
	             $runAddr, $secSize;
	             printf $fh "\tMemory space (0x10000400-0x10000FFF)is reserved at boot-up for use by\n";
	             printf $fh "\tthe on-chip bootloader\n";
	             printf $fh "!!!Aborting AIS translation\n";	             
	             exit(1);
             }
             
             $secData = $cf->secRead($secNum);
           
             for ($count = 0; $count < int($secSize/4); ++$count) {
		        &$writeFn($AIS,$secData->[$count],\$byteCount);
            }
            
            if ($genCrc ne 0) {
                $seek = int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc); 

                $crcVal = 0 if ($genCrc eq 1);
	            $crcVal = calcCrcWord($runAddr,$crcVal);
	            $crcVal = calcCrcWord($secSize,$crcVal);
				$crcVal = calcCrcSection($secData,$secSize,$crcVal,0);
				
	            if ($genCrc eq 1) {
		            if ($oType eq "ASM") {
		               printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		               printf $fh ";;; Requesting CRC\n";
		               printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
		               printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
		               printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		            }
		            
		            &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$byteCount);
		            &$writeFn($AIS,$crcVal,\$byteCount);
		            &$writeFn($AIS,0-($seek),\$byteCount);
	            }
	        }
            
            $seek += int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc);         
         }
       }
    }
    
    if ($genCrc eq 2) {
	   if ($oType eq "ASM") {
	      printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	      printf $fh ";;; Requesting CRC\n";
	      printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
	      printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	      printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";

	   }
	   &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$byteCount);
	   &$writeFn($AIS,$crcVal,\$byteCount);	
	   &$writeFn($AIS,0-($seek),\$byteCount);   
	      
    }
    
    if ($oType eq "ASM") {
	       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	       printf $fh ";;; All sections should be loaded,  branch to entry ;\n";
 	       printf $fh ";;; point for application code.                     ;\n";
 	       printf $fh ";;;    !!!!Entry Point Address: 0x%08X              ;\n",$entryPoint;
	       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";

    }
     
	&$writeFn($AIS,$AISCOMMAND{"jumpAndClose"},\$byteCount);
	&$writeFn($AIS,$entryPoint,\$byteCount);
	
    if ((($bootmode eq 'i2cmaster') || ($bootmode eq 'spimaster')) &&
        ($byteCount >= 65536)) {
	        printf STDERR "!!! WARNING, AIS File size exceeds SPI/I2C Master Boot limit of 64KBytes";
	        printf STDERR "\tAIS file generation aborting";
	        printf STDERR "\tC672xx SPI/I2C Master boot may fail with this data stream";
	        
	        printf $fh "!!! WARNING, AIS File size exceeds SPI/I2C Master Boot limit of 64KBytes\n";
	        printf $fh "\tAIS file generation aborting\n";
	        printf $fh "\tC672xx SPI/I2C Master boot may fail with this data stream\n";
	        exit(1);
    }
    	
    $AIS->DESTROY();
    
	return;

}



#--------------------------------------------------------------------------------------------
sub genBootTableCommands {
	my($AIS) = shift(@_);
	my($byteCount) = shift(@_);
	
	my($wait_for_setup) = 0x100;
	my($wait_for_lock) = 0xC00;
	my($writeFn) = $AIS->{'write'};
	
	# Perform PLL Configuration First if Required
	if ($pllConfigured) {
		
		# NOTE: Steps 1, 2, and 3 are not necessary when the device is coming
        # out of reset, since by default PLLEN = 0 and PLLRST = 1. They are
        # shown here, however, for completeness. 
 
        # Make sure SDRAM is in Self-Refresh mode before setting PLL //
        # By setting SR bit in EMIF SDCR register to 1               //
        #   *(unsigned char *)TIBOOT_EMIF_SDCR = 0x8;
        
        &$writeFn($AIS,$AISCOMMAND{bootTable},\$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{byte},\$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_SDCR,\$byteCount);
        &$writeFn($AIS,0x00000008,\$byteCount);
        &$writeFn($AIS,0x00000004,\$byteCount);
        
       # 1. In PLLCSR, write PLLEN = 0 (bypass mode) //
       #*(volatile unsigned int *)TIBOOT_PLL_PLLCSR = TIBOOT_PLLDISABLE;
       #2. Wait 4 cycles of the slowest of PLLOUT or reference// clock source (CLKIN or OSCIN)

       &$writeFn($AIS,$AISCOMMAND{bootTable},\$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long},\$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLCSR,\$byteCount);
       &$writeFn($AIS,$TIBOOT_PLLDISABLE,\$byteCount);
       &$writeFn($AIS,0x00000004,\$byteCount);  

       #3. In PLLCSR, write PLLRST = 1 (PLL is reset) 
       # *(volatile unsigned int *)TIBOOT_PLL_PLLCSR = TIBOOT_PLLDISABLE | TIBOOT_PLLRESET;

       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLCSR, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLLDISABLE | $TIBOOT_PLLRESET, \$byteCount);
       &$writeFn($AIS,0x00000000,\$byteCount);
       
       #4. If necessary, program PLLDIV0 and PLLM 
       #   DIV0 - Before PLL(set to/1)               
       #    *(volatile unsigned int *)TIBOOT_PLL_PLLDIV0 = TIBOOT_DIVENABLED | 0x00000000;
       #    *(volatile unsigned int *)TIBOOT_PLL_PLLM = 0x00000018;
       
       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);       
       &$writeFn($AIS,$TIBOOT_PLL_PLLDIV0, \$byteCount);
       &$writeFn($AIS,$TIBOOT_DIVENABLED | $pllCfg{div0}, \$byteCount);
       &$writeFn($AIS,0x00000000, \$byteCount);      

       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLM, \$byteCount);
       &$writeFn($AIS,$pllCfg{pllm}, \$byteCount);
       &$writeFn($AIS,0x00000000, \$byteCount);  
                            
       #5. If necessary, program PLLDIV1-n. Note that you must apply the GO operation to
       #   change these dividers to new ratios. 
       #   DIV1 - After PLL- SYSCLK1 DSP Core
       #   DIV2 - After PLL- SYSCLK2 PERIPHS (Always twice DIV3)
       #   DIV3 - After PLL- SYSCLK3 EMIF CLOCK
         
       
       #*(volatile unsigned int *)TIBOOT_PLL_PLLDIV1 = TIBOOT_DIVENABLED | 0x00000001;
       # // 8 cycle wait
   
       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLDIV1, \$byteCount);
       &$writeFn($AIS,$TIBOOT_DIVENABLED | $pllCfg{div1}, \$byteCount);
       &$writeFn($AIS,0x00000008, \$byteCount);  
       
       #*(volatile unsigned int *)TIBOOT_PLL_PLLDIV2 = TIBOOT_DIVENABLED | 0x00000003;
	   #// 8 cycle wait
	   
       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLDIV2, \$byteCount);
       &$writeFn($AIS,$TIBOOT_DIVENABLED | $pllCfg{div2}, \$byteCount);
       &$writeFn($AIS,0x00000008, \$byteCount);  
        
       #*(volatile unsigned int *)TIBOOT_PLL_PLLDIV3 = TIBOOT_DIVENABLED | 0x00000005;
       
       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLDIV3, \$byteCount);
       &$writeFn($AIS,$TIBOOT_DIVENABLED | $pllCfg{div3}, \$byteCount);
       &$writeFn($AIS,0x00000008, \$byteCount);  
         
       
       #6. Enable PLL Align control.
       # *(volatile unsigned int *)TIBOOT_PLL_PLLALNCTL = TIBOOT_PLLALN1 | TIBOOT_PLLALN2 | TIBOOT_PLLALN3;

       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLALNCTL, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLLALN1 | $TIBOOT_PLLALN2 | $TIBOOT_PLLALN3, \$byteCount);
       &$writeFn($AIS,0x00000000, \$byteCount);         
       
       #   *(volatile unsigned int *)TIBOOT_PLL_PLLCMD = TIBOOT_PLLGOSET;
	   #6. Wait for PLL to properly reset
       #   Reset wait time is 125 ns
       #   for(i=0;i<3072;i++)
       #   {
       #   }
       
       $wait_for_setup = int($pllCfg{osc} * 0.125) + 5;       
       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLCMD, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLLGOSET, \$byteCount);
       &$writeFn($AIS,$wait_for_setup, \$byteCount);   
             
       #while (*(volatile unsigned int *)TIBOOT_PLL_PLLSTAT == TIBOOT_PLLGOWAIT){
       #*(volatile unsigned int *)TIBOOT_PLL_PLLCMD = TIBOOT_PLLGOCLR;
       #}
       
       $wait_for_lock = int($pllCfg{osc} * 187.5) + 100;
       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLCMD, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLLGOCLR, \$byteCount);
       &$writeFn($AIS,$wait_for_lock, \$byteCount);        
       

       #7. In PLLCSR, write PLLRST = 0 to bring PLL out of reset
       #   *(volatile unsigned int *)TIBOOT_PLL_PLLCSR = TIBOOT_PLLDISABLE | TIBOOT_PLLRESETRELEASE;
       #8. Wait for PLL to lock 
       #   // Lock time after changing D0, PLLM, or input clock is 187.5 us
       #   // assuming 24.576 MHz input
       #   for(i=0;i<4608;i++)
       #   {
       #   }
       
       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLCSR, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLLDISABLE | $TIBOOT_PLLRESETRELEASE, \$byteCount);
       &$writeFn($AIS,$wait_for_lock, \$byteCount);       
       


      #9. In PLLCSR, write PLLEN = 1 to enable PLL mode 
      #     *(volatile unsigned int *)TIBOOT_PLL_PLLCSR = TIBOOT_PLLENABLE | TIBOOT_PLLRESETRELEASE;
      #     for(i=0;i<4608;i++)
      #     {
      #     }
      
       &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
       &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLL_PLLCSR, \$byteCount);
       &$writeFn($AIS,$TIBOOT_PLLENABLE | $TIBOOT_PLLRESETRELEASE, \$byteCount);
       &$writeFn($AIS,$wait_for_lock, \$byteCount);       
             
      

       #10. Wait for Lock bit to become 1 
       #      while ( ((*(volatile unsigned int *)TIBOOT_PLL_PLLCSR) & TIBOOT_PLLLOCKED) == 0 )
       #      {
       #      }
       # Normally we would do this step. AIS does not support such an operation so
       # We are assuming enough time has passed for PLL lock to have occurred
       # // ---- done PLL Programation ---- 

       # take CFG bridge out of reset
       #    *(volatile unsigned int *)TIBOOT_CFGBRIDGE_REGISTER |= 1;
       #    asm("	nop 9");
       #   *(volatile unsigned int *)TIBOOT_CFGBRIDGE_REGISTER &= 0xFFFFFFFE;
       # Anytime PLL is reset, we need to reset CFGBRIDGE before write to any
       # other peripheral registers
       
        &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{bits}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_CFGBRIDGE_REGISTER, \$byteCount);
        &$writeFn($AIS,0x00000001, \$byteCount);
        &$writeFn($AIS,0x00000009, \$byteCount);         
    
        &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{bits}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_CFGBRIDGE_REGISTER, \$byteCount);
        &$writeFn($AIS,0x00000000, \$byteCount);
        &$writeFn($AIS,0x00000009, \$byteCount);     

       # Make sure SDRAM exits Self-Refesh Mode
       # By setting SR bit in EMIF SDCR register to 0
       #   *(volatile unsigned char *)TIBOOT_EMIF_SDCR = 0x0;
       
        &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{byte}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_SDCR, \$byteCount);
        &$writeFn($AIS,0x00000000, \$byteCount);
        &$writeFn($AIS,0x00000004, \$byteCount);
	}
	
	if ($sdramConfigured) {
		
	   #/* 1. Set SR bit to 1 */
	   #      *(volatile unsigned char *)TIBOOT_EMIF_SDCR = TIBOOT_EMIF_SDCR_SR;
	   
        &$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{byte}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_SDCR, \$byteCount);
        &$writeFn($AIS,0x00000008, \$byteCount);
        &$writeFn($AIS,0x00000004, \$byteCount);

       #// Assume PLL has already been configured for proper EM_CLK cycles
       #// 2. Set SDRAM Timing Register
       #      *(volatile unsigned int *)TIBOOT_EMIF_SDTIMR = 0x8121C110;
       
		&$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
    &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_SDTIMR, \$byteCount);
        &$writeFn($AIS,$sdramCfg{sdtimr}, \$byteCount);
        &$writeFn($AIS,0x00000000, \$byteCount);
           
       #// 3. Set SDRAM Self-Refresh Exit Timing Register
       #   *(volatile unsigned int *)TIBOOT_EMIF_SDSRETR = 0x00000001;
       
		&$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_SDSRETR, \$byteCount);
        &$writeFn($AIS,$sdramCfg{sdsretr}, \$byteCount);
        &$writeFn($AIS,0x00000000, \$byteCount);      
      
       #// 4.  Set SDRAM Refresh Control Register
       #   *(volatile unsigned int *)TIBOOT_EMIF_SDRCR = 0x00000190;
       
		&$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_SDRCR, \$byteCount);
        &$writeFn($AIS,$sdramCfg{sdrcr}, \$byteCount);
        &$writeFn($AIS,0x00000000, \$byteCount);  
           
       #// 5. Set SDRAM Control Register
       #   *(volatile unsigned int *)TIBOOT_EMIF_SDCR = 0x00000620;
       
		&$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_SDCR, \$byteCount);
        &$writeFn($AIS,$sdramCfg{sdcr}, \$byteCount);
        &$writeFn($AIS,0x00000000, \$byteCount);  
                  
       #// 6. Clear SR bit
       #   *(volatile unsigned char *)TIBOOT_EMIF_SDCR = 0x00;
       
 		&$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{byte}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_SDCR, \$byteCount);
        &$writeFn($AIS,0x00000000, \$byteCount);
        &$writeFn($AIS,0x00000400, \$byteCount);             
    }
    
    if ($asyncRamConfigured) {
	    
		&$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_AWCCR, \$byteCount);
        &$writeFn($AIS,$asyncRamCfg{awccr}, \$byteCount);
        &$writeFn($AIS,0x00000000, \$byteCount); 
        
		&$writeFn($AIS,$AISCOMMAND{bootTable}, \$byteCount);
        &$writeFn($AIS,$BOOT_TABLE_TYPE{long}, \$byteCount);
        &$writeFn($AIS,$TIBOOT_EMIF_A1CR, \$byteCount);
        &$writeFn($AIS,$asyncRamCfg{a1cr}, \$byteCount);
        &$writeFn($AIS,0x00000000, \$byteCount);
    }        	           
}


	
#--------------------------------------------------------------------------------------------
sub CreateSecondaryBootAISStream {
    my ($numSections);
	my ($runAddr);
	my ($secName);
	my ($secSize);
	my ($entryPoint);
	my ($count) = 0;
	my ($i,$j,$k);
	my ($pins);
	my ($numPartitions) = 0;
	my ($currPage) = 0;
	my ($pinCfgSize) = 0;
	my ($pinRegSetSize) = 12;
	my ($pinCfgElemSize) = ($useAddressLatch == 0) ? 36 : 48;
	my ($pinCfgCmdSize) = 8;
	my ($pinCfgForNextPage) = 0;
	my ($SecLoadCmdSize) = 12;
	my ($sizeOfRequestCrc) = ($genCrc eq 1) ? 4 * 3 : 0;
	my ($sizeOfSectionLoad) = (4 * 3);	
	my ($TIBootStrap) = 0;
	my ($TIBoot) = 0;
	my ($byteCount) = 0;
	my ($flashAddr) = 0x90000000;
	my ($secDataPtr) = 0;
	my ($fh);
	my ($writeFn);
	my ($numSets);
	my ($TIBootSecSize) = 0;
    my ($TIBootSetupSym) = {};
	my ($TIBootSetupAddr) = 0;
	my ($numPins) = 0;
	my ($cfgSize) = $sizeOfSectionLoad + $sizeOfRequestCrc;
		
	$numSections = $cf->{"header"}{"numSectionHeaders"};
    $entryPoint = $cf->{"header"}{"optEntryPoint"};

 
    $AIS = AISFile->new($aisOutFile, $oType, '>', $debug);
    $fh = $AIS->{'fh'};
    $writeFn = $AIS->{'write'};
    
    $pinMask = setPinMask($pincount);
    
    if ($oType eq 'ASM') {
       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
       printf $fh ";;;   Creating Boot Mode Word for On-chip Bootloader\n";
       printf $fh ";;;   Current FLASH Address: 0x%08X\n", $flashAddr;
       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"; 
       printf $fh ";;; PFSIZE = %d\n",$pfSize;
    }

    
    &$writeFn($AIS,(($pfSize == 8) ? 0x00000000:0x00000001),\$flashAddr);
               
    $byteCount += 4;
       
    	
    for ($secNum = 0; $secNum < $numSections; ++$secNum) {
	   $secName = $cf->{"sections"}[$secNum]{"name"};
       if ($secName eq '.TIBootStrap'){
	       $TIBootStrap = $secNum;
       }
       if ($secName eq '.TIBoot') {
	       $TIBoot = $secNum;
	       $TIBootSecSize = $cf->{"sections"}[$TIBoot]{"byteSize"};
       }
    }
    
    if ($TIBootStrap) {
	   $secName = $cf->{"sections"}[$TIBootStrap]{"name"};
	   $runAddr = $cf->{"sections"}[$TIBootStrap]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$TIBootStrap]{"wordSize"}) * 4;
       $secData = $cf->secRead($TIBootStrap);
       $secSize += 3;
       $secSize ^= 3; 
            
       if ($oType eq 'ASM') {
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
          printf $fh ";;;   Loading .TIBootStrap Section\n";
          printf $fh ";;;   Current FLASH Address: 0x%08X\n",$flashAddr;
          printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";  
       }  
             		          
       for ($count = 0; $count < ($secSize/4); ++$count) {	      
	      &$writeFn($AIS,$secData->[$count],\$flashAddr);
       }

       if ($secSize < 2048) {
	       while($count < ((int(2048/4))-1)) {
	          &$writeFn($AIS,0x00000000,\$flashAddr);
            ++$count;
          }
          $byteCount = 2048;			       	    
       }
    }
        
    if (($TIBoot)&& ($TIBootSecSize !=0)) {
	   $secName = $cf->{"sections"}[$TIBoot]{"name"};
	   $runAddr = $cf->{"sections"}[$TIBoot]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$TIBoot]{"wordSize"}) * 4;
       $secData = $cf->secRead($TIBoot);
       $secSize += 3;
       $secSize ^= 3;
       
       $TIBootSetupSym = $cf->symFind("_TIBootSetup");	   
	   if (defined($TIBootSetupSym)) {
	           $TIBootSetupAddr = $TIBootSetupSym->{"value"};      
	    } else {
		       $TIBootSetupAddr = 0;
        }	   
       
       if ($oType eq 'ASM') {
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
          printf $fh ";;;   Loading .TIBoot Section\n";
          printf $fh ";;;   Current FLASH Address: 0x%08X\n",$flashAddr;
          printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"; 
       }  
                    
       for ($count = 0; $count < (int ($secSize/4)); ++$count) {
	      &$writeFn($AIS,$secData->[$count],\$flashAddr);
       }
       
       if ($oType eq 'ASM') {
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
          printf $fh ";;;   Placing Device Config Command\n";
          printf $fh ";;;   Current FLASH Address: 0x%08X\n", $flashAddr;
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
       }
        
       if ($TIBootSetupAddr ne 0) {
	      if ($oType eq 'ASM') {
	          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	          printf $fh ";;;   Placing Jump Command\n";
	          printf $fh ";;;   Current FLASH Address: 0x%08X\n", $flashAddr;
	          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	      } 
	      
		   &$writeFn($AIS,$AISCOMMAND{jump},\$flashAddr);
		   &$writeFn($AIS,$TIBootSetupAddr,\$flashAddr);
	  }
   
    }
    
    if ($genCrc eq 1) {
	    &$writeFn($AIS,$AISCOMMAND{enableCRC},\$flashAddr);
    }
    
    
    $byteCount = ($flashAddr - 0x90000000);
    
    $currPage = int($byteCount/$pageSize);
	for ($secNum = 0; $secNum < $numSections; ++$secNum) {
	   $secName = $cf->{"sections"}[$secNum]{"name"};

	   $runAddr = $cf->{"sections"}[$secNum]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$secNum]{"wordSize"}) * 4;
       $secDataPtr = $cf->{"sections"}[$secNum]{"dataPtr"};
       $secSize += 3;
       $secSize ^= 3;


       $flags = $cf->{"sections"}[$secNum]{"flags"};
       $sType = $flags & 0xFF;
       
       if ((($secSize != 0)&& ($secDataPtr != 0))&& ($secName ne '.TIBoot') && ($secName ne '.TIBootStrap')){
        if ((($sType & $SECTYPE{"STYP_NOLOAD"})== 0) 
             && (($sType & $SECTYPE{"STYP_DSECT"}) == 0)
             && (($sType & $SECTYPE{"STYP_BSS"}) == 0)
             && (($sType & $SECTYPE{"STYP_COPY"}) == 0)
             && ((($sType & $SECTYPE{"STYP_LOADABLE"}) ||
                 (($sType == $SECTYPE{"STYP_REG"}) && ($secSize != 0))))){

	          if ($oType eq 'ASM') {
	             printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
                 printf $fh ";;;   Loading Section: %s\n",$secName;
                 printf $fh ";;;   Current FLASH Address: 0x%08X\n", $flashAddr;
                 printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
                 printf $fh ";;;   Section Type: 0x%08X\n",$sType;
                 printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";   
             }
             
             if (   (($runAddr <= 0x10000400) && (($runAddr + $secSize) >= 0x10000400))
                 || (($runAddr >= 0x10000400) && (($runAddr) < 0x10001000))
                 ){
	             printf STDERR "!!!!WARNING, Section, \"%s\" ,falls in restricted memory range\n",
	             $secName;
	             printf STDERR "\tSection start address = 0x%08X, secSize = 0x%08X\n",
	             $runAddr, $secSize;
	             printf STDERR "\tMemory space (0x10000400-0x10000FFF)is reserved at boot-up for use by\n";
	             printf STDERR "\tthe on-chip bootloader\n";
	             printf STDERR "!!!Aborting AIS translation\n";
	             
	             printf $fh "!!!!WARNING, Section, \"%s\" ,falls in restricted memory range\n",
	             $secName;
	             printf $fh "\tSection start address = 0x%08X, secSize = 0x%08X\n",
	             $runAddr, $secSize;
	             printf $fh "\tMemory space (0x10000400-0x10000FFF)is reserved at boot-up for use by\n";
	             printf $fh "\tthe on-chip bootloader\n";
	             printf $fh "!!!Aborting AIS translation\n";	             
	             exit(1);
             }
                    	           
	         $byteCount += ($secSize + $cfgSize);
	         if ($useAddressLatch == 0) {
		          $pinCfgForNextPage = $pinCfgCmdSize;
		          $numPins = numPinsReq($currPage+1,$pinMask,$pincount);
		          if (($pincount == 0) && ($cfgFile eq "")) {
			          printf STDERR "WARNING, Configuration File is required to enable\n";
			          printf STDERR "      page swap via GPIO pins, please use -cfg   \n";
			          printf STDERR "      option to define configuration file\n";
			          exit(1);
		          }
		          if (($numPins > $pincount)) {
			          printf STDERR "!!!!WARNING, Not enough address pins defined to configure addressing\n";
			          printf STDERR "    for next page, %d are defined, %d are required\n",$pincount, $numPins;
			          printf STDERR "AIS Generation aborting\n";
			          exit(1);
		          }
		          for($j = 0; $j < int($numPins); ++$j) {
			          $pinCfgForNextPage +=  ($pinCfgElemSize + int((($pinTable[$j]{'pinGlobalSetupFlag'}) * $pinRegSetSize)));
		          }
             } else {
	               $pinCfgForNextPage = ($pinCfgElemSize + int((($pinTable[0]{'pinGlobalSetupFlag'})*$pinCfgElemSize)) + $pinCfgCmdSize);
             }	            
                           
	         $pinCfgForNextPage = $pinCfgForNextPage + 1 if ($pinCfgForNextPage & 1);
	         
             $page = int(($byteCount + $pinCfgForNextPage) / $pageSize);
             
              if ($oType eq 'ASM') {
	             printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
                 printf $fh ";;;   PAGE %d, Current Page %d \n",$page, $currPage;
                 printf $fh ";;;   Byte Count : 0x%08X\n", $byteCount;
                 printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
                 printf $fh ";;;   Pin Cfg Size in bytes: 0x%08X\n",$pinCfgForNextPage;
                 printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";  
             }
              
              
             $count = 0;
                         
             if ($page ne $currPage) {
	            $byteCount -= $secSize;
	            $byteCount = $byteCount + 1 if ($byteCount & 1);
	            
	            $remainder = $pageSize - ($byteCount % $pageSize);
	            $i = $page;
	            while($i > $currPage) {
		            if ($useAddressLatch == 0) {
		               $pinCfgSize = $pinCfgCmdSize;
		               for($j = 0; $j < numPinsReq($i,$pinMask,$pincount); ++$j) {
			               $pinCfgSize +=  ($pinCfgElemSize + int((($pinTable[$j]{'pinGlobalSetupFlag'}) * $pinRegSetSize)));
		               }			            
                    } else {
	                   $pinCfgSize = ($pinCfgElemSize + $pinCfgCmdSize);
                    }	                   
	                 --$i;
                }
                
                
                $pinCfgSize = $pinCfgSize + 1 if ($pinCfgSize & 1);

                if ($oType eq 'ASM') {              
                  printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
                  printf $fh ";;;   PAGE %d, Current Page %d \n",$page, $currPage;
                  printf $fh ";;;   Byte Count : 0x%08X\n", $byteCount;
                  printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
                  printf $fh ";;;   Total Pin Cfg Size Needed: 0x%08X\n",$pinCfgSize;
                  printf $fh ";;;   Pin Cfg Size For Next Page: 0x%08X\n",$pinCfgForNextPage; 
                  printf $fh ";;;   Remainder on this page: 0x%08X\n",$remainder;             
                  printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
               }  
              
	           if ( $pinCfgForNextPage > $remainder) {
		           $secNum -= 2;
		           printf "Not enough memory on current page for pin config, Retrying\n";
		           exit();
	           }
	           	           	            
	           $numPartitions = int($secSize/$pageSize);
	           $numPartitions = (($pinCfgSize + int ($SecLoadCmdSize * $numPartitions) + int ($sizeOfRequestCrc * $numPartitions)) > ($pageSize - ($secSize % $pageSize))) ? $numPartitions + 1: $numPartitions;
		        
	           $secData = $cf->secRead($secNum);
		       $count = 0;
		       
		       
	           for($i = 0; $i <= $numPartitions; $i++) {


		          
		           $currSecSize = (int($remainder - $pinCfgForNextPage));
		           $currSecSize = $currSecSize + 1 if ($currSecSize & 1);
		                               
		           if ($oType eq "ASM") {
			          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
			          printf $fh ";;; Loading %s:\n",$secName;
			          printf $fh ";;;   Run/CopyTo Address: 0x%08X\n",$runAddr;
			          printf $fh ";;;   Number bytes to copy: 0x%08X\n",$currSecSize;
			          printf $fh ";;;   Pin Cfg for next page: 0x%08X\n",$pinCfgForNextPage;
			          printf $fh ";;;   Remainder: 0x%08X\n",$remainder;
			          printf $fh ";;;   Current Flash Addr: 0x%08X\n",$flashAddr;
			          printf $fh ";;;   Partition Number : %d\n",$i;
			          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		           }
			       
		           &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$flashAddr);
			       &$writeFn($AIS,$runAddr,\$flashAddr);
			       &$writeFn($AIS,$currSecSize,\$flashAddr);
			       
#			       $runAddr += $currSecSize;
		           

		             ######################################################################
		             # Write Data For Current Section Partition                           #
		             ######################################################################
		            
			         $secDataPtr = $count;
                     for ($j = 0; $j < (int($currSecSize/4)); ++$j, ++$count) {
		                 &$writeFn($AIS,$secData->[$count],\$flashAddr);
                     }
                  
                     ######################################################################
                     # Calculate CRC if CRC is Enabled                                    #
                     ######################################################################
                     if ($genCrc ne  0) {
                         $seek = int ($currSecSize + $sizeOfSectionLoad + $sizeOfRequestCrc); 
                         $crcVal = 0 if ($genCrc eq 1);
                         
	                     $crcVal = calcCrcWord($runAddr,$crcVal);
	                     $crcVal = calcCrcWord($currSecSize,$crcVal); 
	                     $crcVal = calcCrcSection($secData,$currSecSize,$crcVal,$secDataPtr);

	                     if ($oType eq "ASM") {
	                         printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                         printf $fh ";;; Requesting CRC\n";
	                         printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
	                         printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	                         printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                     }
	            
	                     ###################################################################
	                     # Send CRC Request Only if Section by Section CRC is Requested    #
	                     ###################################################################         
	                     if ($genCrc eq 1) {
	                         &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$flashAddr);
	                         &$writeFn($AIS,$crcVal,\$flashAddr);
	                         &$writeFn($AIS,0-($seek),\$flashAddr);
                         }
	            
                    }
            
                    $seek += int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc);      
                    $runAddr += $currSecSize; 
                     
                     ######################################################################
                     # Place Pin Configuration for Next Page As Last Data on Current Page #
                     ######################################################################
                     
                     
                     $pins = numPinsReq($currPage+1, $pinMask, $pincount);
                     if ($pins > $pincount) {
                            printf STDERR "!!!! WARNING, Not enough address pins defined to configure addressing\n";
			                printf STDERR "     for next page, %d are defined, %d are required\n", $pincount, $currPage+1;
			                printf STDERR "AIS Geneneration aborting\n";
			                exit(1);
                     }
                     
                     if ($oType eq "ASM") {
			            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
			            printf $fh ";;; Loading Pin Configuration for Page\n",$currPage+1;
			            printf $fh ";;;   Current Address: 0x%08X\n",$flashAddr;
			            printf $fh ";;;   Number of Pins to Configure %d\n",$pins;
			            printf $fh ";;;   Pin used as Latch : %s\n",($useAddressLatch == 1) ? "YES" : "NO";
			            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		             }
		              
		             if ($useAddressLatch == 0) {
			             $numSets = 0;
			             for($j = 0; $j < $pins; ++$j) {
			                 $numSets += int(3 + $pinTable[$j]{'pinGlobalSetupFlag'});
		                 }
			                     
				         &$writeFn($AIS,$AISCOMMAND{"pageSwapCommand"},\$flashAddr);
				         &$writeFn($AIS, $numSets,\$flashAddr);
			             		              
	                      for($j=0;$j<$pins;++$j) {
		                      if ($pinTable[$j]{'pinGlobalSetupFlag'}) {
			                      for($k = 0; $k < $pinTable[$j]{'pinGlobalSetupFlag'}; ++$k) {
					                 &$writeFn($AIS,$pinTable[$j]{'pinGlobalSetup'}[$k]{'regAddr'},\$flashAddr);
					                 &$writeFn($AIS,$pinTable[$j]{'pinGlobalSetup'}[$k]{'regVal'},\$flashAddr);
					                 &$writeFn($AIS,$pinTable[$j]{'pinGlobalSetup'}[$k]{'regSetMode'},\$flashAddr);
				                  }
				              }
				                            
					          &$writeFn($AIS,$pinTable[$j]{'pinEnableRegister'},\$flashAddr);
					          &$writeFn($AIS,$pinTable[$j]{'pinEnableMask'},\$flashAddr);
					          &$writeFn($AIS,$pinTable[$j]{'pinEnableMaskMode'},\$flashAddr);
		
					          &$writeFn($AIS,$pinTable[$j]{'pinDirectionRegister'},\$flashAddr);
					          &$writeFn($AIS,$pinTable[$j]{'pinDirectionMask'},\$flashAddr);
					          &$writeFn($AIS,$pinTable[$j]{'pinDirectionMaskMode'},\$flashAddr);
					            
					          if (((1 << $j) & ($currPage+1)) != 0){
					             &$writeFn($AIS,$pinTable[$j]{'pinSetRegister'},\$flashAddr);
					             &$writeFn($AIS,$pinTable[$j]{'pinSetMask'},\$flashAddr);
					             &$writeFn($AIS,$pinTable[$j]{'pinSetMaskMode'},\$flashAddr);
					               
				              }else {
					             &$writeFn($AIS,$pinTable[$j]{'pinClearRegister'},\$flashAddr);
					             &$writeFn($AIS,$pinTable[$j]{'pinClearMask'},\$flashAddr);
					             &$writeFn($AIS,$pinTable[$j]{'pinClearMaskMode'},\$flashAddr);
				              } 
		                  }
	                 } else {
		                 
		                 
				         &$writeFn($AIS,$AISCOMMAND{"latchAddress"},\$flashAddr);
				         
				         for($k = 0; $k < $pinTable[0]{'pinGlobalSetupFlag'}; ++$k) {
					        &$writeFn($AIS,$pinTable[0]{'pinGlobalSetup'}[$k]{'regAddr'},\$flashAddr);
					        &$writeFn($AIS,$pinTable[0]{'pinGlobalSetup'}[$k]{'regVal'},\$flashAddr);
					        &$writeFn($AIS,$pinTable[0]{'pinGlobalSetup'}[$k]{'regSetMode'},\$flashAddr);
				         }
				          
				         &$writeFn($AIS,$pinTable[0]{'pinEnableRegister'},\$flashAddr);
				         &$writeFn($AIS,$pinTable[0]{'pinEnableMask'},\$flashAddr);
				         &$writeFn($AIS,$pinTable[0]{'pinEnableMaskMode'},\$flashAddr);
	
				         &$writeFn($AIS,$pinTable[0]{'pinDirectionRegister'},\$flashAddr);
				         &$writeFn($AIS,$pinTable[0]{'pinDirectionMask'},\$flashAddr);
				         &$writeFn($AIS,$pinTable[0]{'pinDirectionMaskMode'},\$flashAddr);
				            
				         &$writeFn($AIS,$pinTable[0]{'pinSetRegister'},\$flashAddr);
				         &$writeFn($AIS,$pinTable[0]{'pinSetMask'},\$flashAddr);
				         &$writeFn($AIS,$pinTable[0]{'pinSetMaskMode'},\$flashAddr);
				             
				         &$writeFn($AIS,$pinTable[0]{'pinClearRegister'},\$flashAddr);
				         &$writeFn($AIS,$pinTable[0]{'pinClearMask'},\$flashAddr);
				         &$writeFn($AIS,$pinTable[0]{'pinClearMaskMode'},\$flashAddr);
				         
				         &$writeFn($AIS,(int(($currPage+1)*4)) + 0x90000000,\$flashAddr);
	                 } 
	                 ++$currPage;	                 
	                 $byteCount += $remainder; 
                     $secSize -= $currSecSize;
	                 $secSize = $secSize + 1 if ($secSize & 1);
	                 
                     $byteCount += ($secSize + $SecLoadCmdSize + $sizeOfRequestCrc);

	                 if ($useAddressLatch == 0) {
		                $pinCfgForNextPage = $pinCfgCmdSize;
		                if ((numPinsReq($currPage + 1, $pinMask, $pincount)) > $pincount) {
			                printf STDERR "!!!! WARNING, Not enough address pins defined to configure addressing\n";
			                printf STDERR "     for next page, %d defined, %d required\n", $pincount, $currPage + 1;
			                printf STDERR "AIS Geneneration aborting\n";
			                exit(1);
		                }
		                for($j = 0; $j < numPinsReq($currPage + 1, $pinMask, $pincount); ++$j) {
			               $pinCfgForNextPage +=  ($pinCfgElemSize + int((($pinTable[$j]{'pinGlobalSetupFlag'}) * $pinRegSetSize)));
		                }
                     } else {
	                    $pinCfgForNextPage = ($pinCfgElemSize + int((($pinTable[0]{'pinGlobalSetupFlag'})*$pinCfgElemSize)) + $pinCfgCmdSize);
                     }
                     	                                          
                     $page = int(($byteCount + $pinCfgForNextPage) / $pageSize);

                     if ($page != $currPage) {
#	                     $byteCount -= ($secSize)+ $SecLoadCmdSize + $sizeOfRequestCrc);
	                     $byteCount -= ($secSize);
	                     $byteCount = $byteCount + 1 if ($byteCount & 1);
	                     $remainder = $pageSize - ($byteCount % $pageSize);	                                       
                     
                     } else {
	                     $currSecSize = $secSize;

                	                     	                     
			             if ($oType eq "ASM") {
				            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
				            printf $fh ";;; Loading %s:\n",$secName;
				            printf $fh ";;;   Run/CopyTo Address: 0x%08X\n",$runAddr;
				            printf $fh ";;;   Number bytes to copy: 0x%08X\n",$currSecSize;
				            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
			             }
			             
				         &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$flashAddr);
				         &$writeFn($AIS,$runAddr,\$flashAddr);
				         &$writeFn($AIS,$currSecSize,\$flashAddr);

			             ######################################################################
			             # Write Data For Current Section Partition                           #
			             ######################################################################
			             
			             $secDataPtr = $count;
			             
	                     for ($j = 0; $j < (int($currSecSize/4)); ++$count,++$j) {
			                 &$writeFn($AIS,$secData->[$count],\$flashAddr);
	                     }
	                     
			             ######################################################################
		                 # Calculate CRC if CRC is Enabled                                    #
		                 ######################################################################
		                 if ($genCrc ne  0) {
		                     $seek = int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc); 
		                     $crcVal = 0 if ($genCrc eq 1);
		                     
			                 $crcVal = calcCrcWord($runAddr,$crcVal);
			                 $crcVal = calcCrcWord($currSecSize,$crcVal);
						     $crcVal = calcCrcSection($secData,$currSecSize,$crcVal, $secDataPtr);
						     
			                 if ($oType eq "ASM") {
			                     printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
			                     printf $fh ";;; Requesting CRC\n";
			                     printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
			                     printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
			                     printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
			                 }
			            
			                 ###################################################################
			                 # Send CRC Request Only if Section by Section CRC is Requested    #
			                 ###################################################################   
			                 if ($genCrc eq 1) {
			                     &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$flashAddr);
			                     &$writeFn($AIS,$crcVal,\$flashAddr);
			                     &$writeFn($AIS,0-($seek),\$flashAddr);
		                     }
			            }
	                     last;   # No more partitions to process	                     
                    } 	                     
                 }	### End no of partitions
             } else {
	             
	             if ($oType eq "ASM") {
		            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		            printf $fh ";;; Loading %s:\n",$secName;
		            printf $fh ";;;   Run/CopyTo Address: 0x%08X\n",$runAddr;
		            printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
		            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	             }
	             
		         &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$flashAddr);
		         &$writeFn($AIS,$runAddr,\$flashAddr);
		         &$writeFn($AIS,$secSize,\$flashAddr);
	             
		         $secData = $cf->secRead($secNum);
	             for ($count = 0; $count < (int($secSize/4)); ++$count) {
			        &$writeFn($AIS,$secData->[$count],\$flashAddr);
	             }
	             
	             
                 ######################################################################
                 # Calculate CRC if CRC is Enabled                                    #
                 ######################################################################
                 if ($genCrc ne  0) {
                     $seek = int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc); 
                     $crcVal = 0 if ($genCrc eq 1);
                     
	                 $crcVal = calcCrcWord($runAddr,$crcVal);
	                 $crcVal = calcCrcWord($secSize,$crcVal);
				     $crcVal = calcCrcSection($secData,$secSize,$crcVal,0);
	                         				     
	                 if ($oType eq "ASM") {
	                     printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                     printf $fh ";;; Requesting CRC\n";
	                     printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
	                     printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	                     printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                 }
	            
	                 ###################################################################
	                 # Send CRC Request Only if Section by Section CRC is Requested    #
	                 ###################################################################   
	                 if ($genCrc eq 1) {
	                     &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$flashAddr);
	                     &$writeFn($AIS,$crcVal,\$flashAddr);
	                     &$writeFn($AIS,0-($seek),\$flashAddr);
                     }
	            }
            
                $seek += int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc); 	             
	             
	             
            }
         }
      }
      
      
    }
    if ($oType eq "ASM") {
	       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	       printf $fh ";;; All sections should be loaded,  branch to entry ;\n";
 	       printf $fh ";;; point for application code.                     ;\n";
 	       printf $fh ";;;    !!!!Entry Point Address: 0x%08X              ;\n",$entryPoint;
	       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
    } 
	
    &$writeFn($AIS,$AISCOMMAND{"jumpAndClose"},\$flashAddr);
	&$writeFn($AIS,$entryPoint,\$flashAddr);
    	
	return;
}


#--------------------------------------------------------------------------------------------
sub CreateMultiEeprom {
    my ($numSections);
	my ($runAddr);
	my ($secName);
	my ($secSize);
	my ($entryPoint);
	my ($count) = 0;
	my ($i,$j,$k);
	my ($SecLoadCmdSize) = 12;
	my ($sizeOfRequestCrc) = ($genCrc eq 1) ? 4 * 3 : 0;
	my ($TIBootStrap) = 0;
	my ($TIBoot) = 0;
	my ($byteCount) = 0;
	my ($flashAddr) = 0x00000000;
	my ($secDataPtr) = 0;
	my ($fh);
	my ($writeFn);
	my ($numSets);
	my ($TIBootSecSize) = 0;
    my ($TIBootSetupSym) = {};
	my ($TIBootSetupAddr) = 0;
	my ($slaveOutf) = $aisOutFile."50";
	my ($nextEeprom) = 0;
	my ($JumpCmdSize) = 8;
	my ($setSlaveAddrSize) = $TIBOOT_SETSLAVE_CODE_SIZE + $SecLoadCmdSize +  $JumpCmdSize +(($genCrc ne 0)? 8:0) ;
		
	$numSections = $cf->{"header"}{"numSectionHeaders"};
    $entryPoint = $cf->{"header"}{"optEntryPoint"};
    $SecLoadCmdSize += $sizeOfRequestCrc;

    

    $AIS = AISFile->new($slaveOutf, $oType, '>', $debug);
    $fh = $AIS->{'fh'};
    $writeFn = $AIS->{'write'};
 
	&$writeFn($AIS,$AISCOMMAND{"aisMagic"},\$flashAddr);
    	
    if ($cfgType eq 'AIS') {
       if (($pllConfigured == 1) || ($asyncRamConfigured == 1) || ($sdramConfigured == 1)) {
	       genBootTableCommands($AIS, $flashAddr);
       }
    }    
        
    if ($genCrc eq 1) {
	    &$writeFn($AIS,$AISCOMMAND{enableCRC},\$flashAddr);
    }
       
    for ($secNum = 0; $secNum < $numSections; ++$secNum) {
	   $secName = $cf->{"sections"}[$secNum]{"name"};
       if ($secName eq '.TIBoot') {
	       $TIBoot = $secNum;
           $TIBootSecSize = $cf->{"sections"}[$TIBoot]{"byteSize"};
	       $TIBootSetupSym = $cf->symFind("_TIBootSetup");
	       if (defined($TIBootSetupSym)) {
	           $TIBootSetupAddr = $TIBootSetupSym->{"value"};
		       
	       } else {
		       $TIBootSetupAddr = 0;
           }
       }
    }
    
    if (($TIBoot) && ($TIBootSecSize != 0)) {
	   $secName = $cf->{"sections"}[$TIBoot]{"name"};
	   $runAddr = $cf->{"sections"}[$TIBoot]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$TIBoot]{"wordSize"}) * 4;
       $secData = $cf->secRead($TIBoot);
       $secSize += 3;
       $secSize ^= 3;
              
       if ($oType eq 'ASM') {
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
          printf $fh ";;;   Loading .TIBoot Section\n";
          printf $fh ";;;   Current FLASH Address: 0x%08X\n",$flashAddr;
          printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"; 
       }  
       
       &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$flashAddr);
	   &$writeFn($AIS,$runAddr,\$flashAddr);
	   &$writeFn($AIS,$secSize,\$flashAddr);
	                      
       for ($count = 0; $count < (int ($secSize/4)); ++$count) {
	      &$writeFn($AIS,$secData->[$count],\$flashAddr);
       }
       $seek = int ($secSize + $SecLoadCmdSize); 

       $crcVal = 0 if ($genCrc eq 1);
	   $crcVal = calcCrcWord($runAddr,$crcVal);
	   $crcVal = calcCrcWord($secSize,$crcVal);	   
	   $crcVal = calcCrcSection($secData,$secSize,$crcVal,0);
				
	   if ($genCrc eq 1) {
	       if ($oType eq "ASM") {
	           printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	           printf $fh ";;; Requesting CRC\n";
	           printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
	           printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	           printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	       }
		            
	       &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$flashAddr);
	       &$writeFn($AIS,$crcVal,\$flashAddr);
	       &$writeFn($AIS,0-($seek),\$flashAddr);
	  }
	  
	  if ($TIBootSetupAddr ne 0) {
	      if ($oType eq 'ASM') {
	          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	          printf $fh ";;;   Placing Jump Command\n";
	          printf $fh ";;;   Current FLASH Address: 0x%08X\n", $flashAddr;
	          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	      } 
	      
		   &$writeFn($AIS,$AISCOMMAND{jump},\$flashAddr);
		   &$writeFn($AIS,$TIBootSetupAddr,\$flashAddr);
	  }
    }
      
    if ($genCrc eq 1) {
	    &$writeFn($AIS,$AISCOMMAND{enableCRC},\$flashAddr);
    }
    
           
	for ($secNum = 0; $secNum < $numSections; ++$secNum) {
	   $secName = $cf->{"sections"}[$secNum]{"name"};

	   $runAddr = $cf->{"sections"}[$secNum]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$secNum]{"wordSize"}) * 4;
       $secDataPtr = $cf->{"sections"}[$secNum]{"dataPtr"};
       $secSize += 3;
       $secSize ^= 3;


       $flags = $cf->{"sections"}[$secNum]{"flags"};
       $sType = $flags & 0xFF;
       
       if ((($secSize != 0) && ($secDataPtr != 0)) && ($secName ne '.TIBoot') && ($secName ne '.TIBootStrap')){
        if ((($sType & $SECTYPE{"STYP_NOLOAD"})== 0) 
             && (($sType & $SECTYPE{"STYP_DSECT"}) == 0)
             && (($sType & $SECTYPE{"STYP_BSS"}) == 0)
             && (($sType & $SECTYPE{"STYP_COPY"}) == 0)
             && ((($sType & $SECTYPE{"STYP_LOADABLE"}) ||
                 (($sType == $SECTYPE{"STYP_REG"}) && ($secSize != 0))))){

	          if ($oType eq 'ASM') {
	             printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
                 printf $fh ";;;   Loading Section: %s\n",$secName;
                 printf $fh ";;;   Current FLASH Address: 0x%08X\n", $flashAddr;
                 printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
                 printf $fh ";;;   Section Type: 0x%08X\n",$sType;
                 printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";   
             }
 
                                	          
             $count = 0;
                         
             if (($flashAddr + $secSize + $SecLoadCmdSize) > $eepromSize){
	                 

	           $secData = $cf->secRead($secNum);
		       $count = 0;
		       		       
		       while ($secSize > 0) {
			       			      
			        if (($flashAddr + $secSize + $SecLoadCmdSize + $setSlaveAddrSize) > $eepromSize) {
				        
				        $remainder = $eepromSize - ($flashAddr + $SecLoadCmdSize + $setSlaveAddrSize);
				        $remainder = ($remainder + 1) if ($remainder & 1);
				        $currSecSize = $remainder;
				        
                    } else {
				        $currSecSize = $secSize;
			        }				        
				        
		           &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$flashAddr);
			       &$writeFn($AIS,$runAddr,\$flashAddr);
			       &$writeFn($AIS,$currSecSize,\$flashAddr);
			       		           

		             ######################################################################
		             # Write Data For Current Section Partition                           #
		             ######################################################################
		            
			         $secDataPtr = $count;
                     for ($j = 0; $j < (int($currSecSize/4)); ++$j, ++$count) {
		                 &$writeFn($AIS,$secData->[$count],\$flashAddr);
                     }
                  
                     ######################################################################
                     # Calculate CRC if CRC is Enabled                                    #
                     ######################################################################
                     if ($genCrc ne  0) {
                         $seek = int ($currSecSize + $SecLoadCmdSize); 
                         $crcVal = 0 if ($genCrc eq 1);
                         
	                     $crcVal = calcCrcWord($runAddr,$crcVal);
	                     $crcVal = calcCrcWord($currSecSize,$crcVal); 
	                     $crcVal = calcCrcSection($secData,$currSecSize,$crcVal,$secDataPtr);

	                     if ($oType eq "ASM") {
	                         printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                         printf $fh ";;; Requesting CRC\n";
	                         printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
	                         printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	                         printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                     }
	            
	                     ###################################################################
	                     # Send CRC Request Only if Section by Section CRC is Requested    #
	                     ###################################################################         
	                     if ($genCrc eq 1) {
	                         &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$flashAddr);
	                         &$writeFn($AIS,$crcVal,\$flashAddr);
	                         &$writeFn($AIS,0-($seek),\$flashAddr);
                         }
	            
                    }
            
                    $seek += int ($secSize + $SecLoadCmdSize);      
                    
                    
                    $runAddr += $currSecSize; 
                    $secSize -= $currSecSize;
                                     
                    if ($secSize > 0) {	
			            my ($tmp) = ($slaveAddr[$nextEeprom] << $TIBOOT_SLAVEADDR_SHIFT) & $TIBOOT_SLAVEADDR_MASK;
	                    
	                    &$writeFn($AIS,$AISCOMMAND{"disableCRC"},\$flashAddr) if ($genCrc ne 0);
		                &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SETSLAVE_LOAD_ADDR,\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SETSLAVE_CODE_SIZE,\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[0],\$flashAddr);         
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[1] | $tmp,\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[2],\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[3],\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[4],\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[5],\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[6],\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[7],\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[8],\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[9],\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[10],\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SetSlaveAddr[11],\$flashAddr);
		
	                    &$writeFn($AIS,$AISCOMMAND{"enableCRC"},\$flashAddr) if ($genCrc ne 0);
			            	    
	                    &$writeFn($AIS,$AISCOMMAND{"jump"},\$flashAddr);
			            &$writeFn($AIS,$TIBOOT_SETSLAVE_LOAD_ADDR,\$flashAddr);         
	                  
	                    close(AIS);
	                   
	                    $slaveOutf = sprintf("%s%2X", $aisOutFile, $slaveAddr[$nextEeprom]);
	                    $AIS = AISFile->new($slaveOutf, $oType, '>', $debug);
	                    $fh = $AIS->{'fh'};
	                    $writeFn = $AIS->{'write'};
	                    $flashAddr = 0;	
	                    ++$nextEeprom;    
                    }             
                }  
                      			        
             } else {
	             
	             if ($oType eq "ASM") {
		            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		            printf $fh ";;; Loading %s:\n",$secName;
		            printf $fh ";;;   Run/CopyTo Address: 0x%08X\n",$runAddr;
		            printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
		            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	             }
	             
		         &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$flashAddr);
		         &$writeFn($AIS,$runAddr,\$flashAddr);
		         &$writeFn($AIS,$secSize,\$flashAddr);
	             
		         $secData = $cf->secRead($secNum);
	             for ($count = 0; $count < (int($secSize/4)); ++$count) {
			        &$writeFn($AIS,$secData->[$count],\$flashAddr);
	             }
	             
	             
                 ######################################################################
                 # Calculate CRC if CRC is Enabled                                    #
                 ######################################################################
                 if ($genCrc ne  0) {
                     $seek = int ($secSize + $SecLoadCmdSize); 
                     $crcVal = 0 if ($genCrc eq 1);
                     
	                 $crcVal = calcCrcWord($runAddr,$crcVal);
	                 $crcVal = calcCrcWord($secSize,$crcVal);
				     $crcVal = calcCrcSection($secData,$secSize,$crcVal,0);
	                         				     
	                 if ($oType eq "ASM") {
	                     printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                     printf $fh ";;; Requesting CRC\n";
	                     printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
	                     printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	                     printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                 }
	            
	                 ###################################################################
	                 # Send CRC Request Only if Section by Section CRC is Requested    #
	                 ###################################################################   
	                 if ($genCrc eq 1) {
	                     &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$flashAddr);
	                     &$writeFn($AIS,$crcVal,\$flashAddr);
	                     &$writeFn($AIS,0-($seek),\$flashAddr);
                     }
	            }
            
                $seek += int ($secSize + $SecLoadCmdSize); 	             
	             
	             
            }
         }
      }
      
      
    }
    if ($oType eq "ASM") {
	       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	       printf $fh ";;; All sections should be loaded,  branch to entry ;\n";
 	       printf $fh ";;; point for application code.                     ;\n";
 	       printf $fh ";;;    !!!!Entry Point Address: 0x%08X              ;\n",$entryPoint;
	       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
    } 
	
    &$writeFn($AIS,$AISCOMMAND{"jumpAndClose"},\$flashAddr);
	&$writeFn($AIS,$entryPoint,\$flashAddr);
	
	while( ($flashAddr < int ($eepromSize - $setSlaveAddrSize))) 
	{
	    &$writeFn($AIS,$AISCOMMAND{"disableCRC"},\$flashAddr);
    }
		
    if ($flashAddr + $setSlaveAddrSize < $eepromSize) {
	    my ($tmp) = (0x50 << $TIBOOT_SLAVEADDR_SHIFT) & $TIBOOT_SLAVEADDR_MASK;
	    
	    &$writeFn($AIS,$AISCOMMAND{"disableCRC"},\$flashAddr) if ($genCrc ne 0);
	    &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SETSLAVE_LOAD_ADDR,\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SETSLAVE_CODE_SIZE,\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[0],\$flashAddr);         
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[1] | $tmp,\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[2],\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[3],\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[4],\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[5],\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[6],\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[7],\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[8],\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[9],\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[10],\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SetSlaveAddr[11],\$flashAddr);
	
	    &$writeFn($AIS,$AISCOMMAND{"enableCRC"},\$flashAddr) if ($genCrc ne 0);
	    	    
	    &$writeFn($AIS,$AISCOMMAND{"jump"},\$flashAddr);
	    &$writeFn($AIS,$TIBOOT_SETSLAVE_LOAD_ADDR,\$flashAddr); 
    }  
    
    close(AIS);	
                        	
	return;
}



#--------------------------------------------------------------------------------------------
sub CreateRawFlashAisStream {
    my ($numSections);
	my ($runAddr);
	my ($secName);
	my ($secSize);
	my ($entryPoint);
	my ($count) = 0;
	my ($i,$j,$k);
	my ($pins);
	my ($currPage) = 0;
	my ($pinCfgSize) = 0;
	my ($pinRegSetSize) = 12;
	my ($pinCfgCmdSize) = 8;
	my ($SecLoadCmdSize) = 12;
	my ($sizeOfRequestCrc) = ($genCrc eq 1) ? 4 * 3 : 0;
	my ($sizeOfSectionLoad) = 4 * 3;	
	my ($TIBootStrap) = 0;
	my ($TIBoot) = 0;
	my ($byteCount) = 0;
	my ($flashAddr) = 0x90000000;
	my ($secDataPtr) = 0;
	my ($fh);
	my ($writeFn);
	my ($numSets);
    my ($TIBootSetupSym) = {};
	my ($TIBootSetupAddr) = 0;
	my ($TIBootSecSize) = 0;
		
	$numSections = $cf->{"header"}{"numSectionHeaders"};
    $entryPoint = $cf->{"header"}{"optEntryPoint"};

    $AIS = AISFile->new($aisOutFile, $oType, '>', $debug);
    $fh = $AIS->{'fh'};
    $writeFn = $AIS->{'write'};
    
    if ($oType eq 'ASM') {
       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
       printf $fh ";;;   Creating Boot Mode Word for On-chip Bootloader\n";
       printf $fh ";;;   Current FLASH Address: 0x%08X\n", $flashAddr;
       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"; 
       printf $fh ";;; PFSIZE = %d\n",$pfSize;
    }
           
    ## FLASH Size is 16 bit on RAW
    &$writeFn($AIS, ($pfSize == 8)? 0x00000000 : 0x00000001,\$flashAddr);  
           
    $byteCount += 4;
       
    	
    for ($secNum = 0; $secNum < $numSections; ++$secNum) {
	   $secName = $cf->{"sections"}[$secNum]{"name"};
       if ($secName eq '.TIBootStrap'){
	       $TIBootStrap = $secNum;
       }
       if ($secName eq '.TIBoot') {
	       $TIBoot = $secNum;
	       $TIBoot = $secNum;
           $TIBootSecSize = $cf->{"sections"}[$TIBoot]{"byteSize"};
	       $TIBootSetupSym = $cf->symFind("_TIBootSetup");
	       $TIBootSetupAddr = $TIBootSetupSym->{"value"};
	       printf "TIBootSetupAddr :0x%08X:\n",$TIBootSetupAddr;       }
    }
    
    if ($TIBootStrap) {
	   $secName = $cf->{"sections"}[$TIBootStrap]{"name"};
	   $runAddr = $cf->{"sections"}[$TIBootStrap]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$TIBootStrap]{"wordSize"}) * 4;
       $secData = $cf->secRead($TIBootStrap);
       $secSize += 3;
       $secSize ^= 3; 
            
       if ($oType eq 'ASM') {
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
          printf $fh ";;;   Loading .TIBootStrap Section\n";
          printf $fh ";;;   Current FLASH Address: 0x%08X\n",$flashAddr;
          printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";  
       }  
             		          
       for ($count = 0; $count < ($secSize/4); ++$count) {	      
	      &$writeFn($AIS,$secData->[$count],\$flashAddr);
       }

       if ($secSize < 2048) {
	       while($count < ((int(2048/4))-1)) {
	          &$writeFn($AIS,0x00000000,\$flashAddr);
            ++$count;
          }
          $byteCount = 2048;			       	    
       }
    }
        
    if (($TIBoot) && ($TIBootSecSize != 0)) {
	   $secName = $cf->{"sections"}[$TIBoot]{"name"};
	   $runAddr = $cf->{"sections"}[$TIBoot]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$TIBoot]{"wordSize"}) * 4;
       $secData = $cf->secRead($TIBoot);
       $secSize += 3;
       $secSize ^= 3;
      

	   printf "TIBootSetupAddr 0x%08X\n",$TIBootSetupAddr;
	    
       if ($oType eq 'ASM') {
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
          printf $fh ";;;   Loading .TIBoot Section\n";
          printf $fh ";;;   Current FLASH Address: 0x%08X\n",$flashAddr;
          printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"; 
       }  
                    
       for ($count = 0; $count < (int ($secSize/4)); ++$count) {
	      &$writeFn($AIS,$secData->[$count],\$flashAddr);
       }
       
       if ($oType eq 'ASM') {
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
          printf $fh ";;;   Placing Device Config Command\n";
          printf $fh ";;;   Current FLASH Address: 0x%08X\n", $flashAddr;
          printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
       }
        
	   &$writeFn($AIS,$AISCOMMAND{jump},\$flashAddr);
 	   &$writeFn($AIS,$TIBootSetupAddr,\$flashAddr);           
    }
       
    if ($genCrc eq 1) {
	    &$writeFn($AIS,$AISCOMMAND{enableCRC},\$flashAddr);
    }
    

    
    $byteCount = ($flashAddr - 0x90000000);
    
    $currPage = int($byteCount/$pageSize);
	for ($secNum = 0; $secNum < $numSections; ++$secNum) {
	   $secName = $cf->{"sections"}[$secNum]{"name"};

	   $runAddr = $cf->{"sections"}[$secNum]{"phyAddr"};
       $secSize = ($cf->{"sections"}[$secNum]{"wordSize"}) * 4;
       $secDataPtr = $cf->{"sections"}[$secNum]{"dataPtr"};
       $secSize += 3;
       $secSize ^= 3;


       $flags = $cf->{"sections"}[$secNum]{"flags"};
       $sType = $flags & 0xFF;
       
       if ((($secSize != 0) && ($secDataPtr != 0)) && ($secName ne '.TIBoot') && ($secName ne '.TIBootStrap')){
        if ((($sType & $SECTYPE{"STYP_NOLOAD"})== 0) 
             && (($sType & $SECTYPE{"STYP_DSECT"}) == 0)
             && (($sType & $SECTYPE{"STYP_BSS"}) == 0)
             && (($sType & $SECTYPE{"STYP_COPY"}) == 0)
             && ((($sType & $SECTYPE{"STYP_LOADABLE"}) ||
                 (($sType == $SECTYPE{"STYP_REG"}) && ($secSize != 0))))){
                 
	          if ($oType eq 'ASM') {
	             printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
                 printf $fh ";;;   Loading Section: %s\n",$secName;
                 printf $fh ";;;   Current FLASH Address: 0x%08X\n", $flashAddr;
                 printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
                 printf $fh ";;;   Section Type: 0x%08X\n",$sType;
                 printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";   
             }
                    	           
	         $byteCount += ($secSize + $SecLoadCmdSize + $sizeOfRequestCrc);
             
              if ($oType eq 'ASM') {
	             printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
                 printf $fh ";;;   PAGE %d, Current Page %d \n",$page, $currPage;
                 printf $fh ";;;   Byte Count : 0x%08X\n", $byteCount;
                 printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
                 printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";  
             }
              
              
             $count = 0;      
                     

	             
	             if ($oType eq "ASM") {
		            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		            printf $fh ";;; Loading %s:\n",$secName;
		            printf $fh ";;;   Run/CopyTo Address: 0x%08X\n",$runAddr;
		            printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
		            printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	             }
	             
		         &$writeFn($AIS,$AISCOMMAND{"sectionLoad"},\$flashAddr);
		         &$writeFn($AIS,$runAddr,\$flashAddr);
		         &$writeFn($AIS,$secSize,\$flashAddr);
	             
		         $secData = $cf->secRead($secNum);
	             for ($count = 0; $count < (int($secSize/4)); ++$count) {
			        &$writeFn($AIS,$secData->[$count],\$flashAddr);
	             }
	             
	             
                 ######################################################################
                 # Calculate CRC if CRC is Enabled                                    #
                 ######################################################################
                 if ($genCrc ne  0) {
                     $seek = int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc); 
                     $crcVal = 0 if ($genCrc eq 1);
                     
                     
	                 $crcVal = calcCrcWord($runAddr,$crcVal);
	                 $crcVal = calcCrcWord($secSize,$crcVal);
				     $crcVal = calcCrcSection($secData,$secSize,$crcVal,0);
				     				                     	                 
	                 if ($oType eq "ASM") {
	                     printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                     printf $fh ";;; Requesting CRC\n";
	                     printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
	                     printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	                     printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	                 }
	            
	                 ###################################################################
	                 # Send CRC Request Only if Section by Section CRC is Requested    #
	                 ###################################################################   
	                 if ($genCrc eq 1) {
	                     &$writeFn($AIS,$AISCOMMAND{"requestCRC"},\$flashAddr);
	                     &$writeFn($AIS,$crcVal,\$flashAddr);
	                     &$writeFn($AIS,0-($seek),\$flashAddr);
                     }
	            }
            
                $seek += int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc); 	             
	             
	             
            }
         }
      }
      
    if ($oType eq "ASM") {
	       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	       printf $fh ";;; All sections should be loaded,  branch to entry ;\n";
 	       printf $fh ";;; point for application code.                     ;\n";
 	       printf $fh ";;;    !!!!Entry Point Address: 0x%08X              ;\n",$entryPoint;
	       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
    } 
	
    &$writeFn($AIS,$AISCOMMAND{"jumpAndClose"},\$flashAddr);
	&$writeFn($AIS,$entryPoint,\$flashAddr);
    	
	return;
}

#--------------------------------------------------------------------------------------------
sub writeASM {
	
	my($OUT) = shift(@_);
	my($data) = shift(@_);
	my($addrPtr) = shift(@_);
	my($addr);
	
	$addr = $$addrPtr;
	
	if ($debug eq 1) {
       printf $OUT "\t.word 0x%08X\t\t;Flash Address 0x%08X\n",$data,$addr;
    } else {
       printf $OUT "\t.word 0x%08X\n",$data;
    }	   
    $addr += 4;
    $$addrPtr = $addr;
    
    return;
}

#--------------------------------------------------------------------------------------------
sub writeASCII {
	
	my($OUT) = shift(@_);
	my($data) = shift(@_);
	my($addrPtr) = shift(@_);
	my($addr);
	
	$addr = $$addrPtr;
	
	printf "writeASCII, DEBUG = %d\n",$debug;
	exit();
	
	if ($debug eq 1) {
       printf $OUT "\t0x%08X\t\t;Flash Address 0x%08x\n",$data,$addr;
    } else {
       printf $OUT "\t0x%08X\n",$data;
    }	   
    
    $addr += 4;
    $$addrPtr = $addr;
    
    return;
}

#--------------------------------------------------------------------------------------------
sub writeBIN {
	
	my($OUT) = shift(@_);
	my($data) = shift(@_);
	my($addrPtr) = shift(@_);
	
    syswrite($OUT, $data, 4);
    $$addrPtr += 4;
    
    return;
}


#--------------------------------------------------------------------------------------------
sub setPinMask {
	
	my($cnt) = shift(@_);
	my($i);
	my($mask) = 0;
	
	for($i=0; $i < $cnt;++$i) {
		$mask = ($mask << 1) + 1;
	}
		
    
    return $mask;
}


#--------------------------------------------------------------------------------------------
sub numPinsReq{
	
	my($page) = shift(@_);
	my($mask)  = shift(@_);
	my($cnt) = shift(@_);
	my($i)= 0;
	my($tmp) = 0;
	
	do {
	   $tmp = (1 << $i);
	   $i++;
    } until (($tmp > $page) | ($i > $cnt));
		    
    return $i-1;
}

#--------------------------------------------------------------------------------------------
sub calcCrcSection {
	my($secData) = shift(@_);
	my($section_size) = shift(@_);
	my($crc) = shift(@_);
	my($dataNdx) = shift(@_);
	my($n);
	my($residue_value) = 0;
	my($msb_bit) = 0;
	my($bits) = 0;
	my($nwords);
	my($temp);
	my($crc_poly) = 0x04C11DB7; # CRC - 32
	

	for( $n = 0; $n < ($section_size>>2); $n++ )
	{
		$bits = 32;
		while( --$bits >= 0 )
		{
			$msb_bit = $crc & 0x80000000;
			$crc = ($crc << 1) ^ ((($secData->[$n + $dataNdx]) >> $bits) & 1 );
			if ( $msb_bit ){
       		  $crc = ($crc ^ $crc_poly);
   		    }
		}
	}
			
	if (($section_size & 3) == 1) {
	   $residue_value = (($secData->[$n + $dataNdx]) && 0xFF);
	   $bits = 8;	   
    }
    if (($section_size & 3) == 2) {
	    $residue_value = (($secData->[$n + $dataNdx]) && 0xFFFF);
	    $bits = 16;	    
    }
    if (($section_size & 3) == 3) {
	    $residue_value = (($secData->[$n + $dataNdx]) && 0xFFFFFF);
	    $bits = 24;
    }
	
	if($section_size & 3)
	{

		while( --$bits >= 0 )
		{
			$msb_bit = $crc & 0x80000000;
			$crc = ($crc << 1) ^ (($residue_value >> $bits) & 1 );
			if ( $msb_bit ) {
			   $crc = ($crc ^ $crc_poly);
			}
		}
	}	  	

	return  $crc;
}


#--------------------------------------------------------------------------------------------
sub calcCrcWord {
	my($dataWord) = shift(@_);
	my($crc) = shift(@_);
	my($msb_bit) = 0;
	my($bits) = 0;
	my($crc_poly) = 0x04C11DB7; # CRC - 32
	


	$bits = 32;
	while( --$bits >= 0 )
	{
		$msb_bit = $crc & 0x80000000;
		$crc = ($crc << 1) ^ (($dataWord >> $bits) & 1 );
		if ( $msb_bit ){
    		  $crc = $crc ^ $crc_poly;
 	    }
	}
		

	return  $crc;
}


#--------------------------------------------------------------------------------------------
sub parseArguments {

  my ($argv)           = shift(@_);
  my ($inputDefaults)  = {@_};
  my ($status)         = 0;
  my ($args)           = {};
  my ($argStr)         = "";
  my ($rcStr)          = "";
  my ($strArgs);
  my ($key);
  my ($arg);

  # Baseline defaults for librray specific arguments
  my ($defaults) = {
	   -i     => "",
	   -o     => "",
	   -cfg   => "",
	   -otype => "asm",
	   -pkg   => "bga",
	   -crc   => 1,
	   -sec   => 0,
	   -pf    => 8,
	   -bootmode => 'spislave',
  };

  # Assign base defaults to args
  foreach $key (keys %$defaults) {
    $args->{$key} = $defaults->{$key};
  }

  # Assign input defaults to args
  foreach $key (keys %$inputDefaults) {
    $args->{$key} = $inputDefaults->{$key};
  }

  # Need to double quote all entries in @argv that have white-space
  foreach $arg (@$argv) {
    if ($arg =~ m/\s+/) {
      $arg = "\"$arg\"";
    }
  }

  # Combine command line arguments into a string
  $argStr = join(' ',@$argv);

  # Assign the argument string to the return hash
  $args->{_argument_str_} = $argStr;

  # Parse the argument string into a hash
  $strArgs = parseCommandString($argStr);

  # Assign the string arguments to the arguments hash
  foreach $key (keys %$strArgs) {
    $args->{$key} = $strArgs->{$key};
  }

  # Set help level
  $args->{-h} = 2 if ($args->{-hh});

  # This is used by the setupLog() subroutine to get original command line arguments
  $args->{_original_args_} = $args;

  return $args;
}

#------------------------------------------------------------------------------
#  The following files are a set of utilities used to parse option strings, etc.
#------------------------------------------------------------------------------
sub parseOptionsString {

  my ($inputStr)  = shift(@_);
  my ($inputArgs) = {@_};
  my ($args);
  my ($arg);
  my ($strArgs);

  %$args = %$inputArgs;
  
  $strArgs = parseCommandString($inputStr);
  
  %$args = (%$args, %$strArgs);

  return $args;
}


#------------------------------------------------------------------------------
sub parseCommandString {

  my ($inputStr) = shift(@_);
  my ($args);
  my ($state);
  my (@chars);
  my ($ch);
  my (@tokens);
  my ($token);
  my ($string);
  my ($switch);
  my (@nonSwitches);

  #*******************************************************
  # Tokenizing state machine, turn string into array of
  # strings and tokens.
  #*******************************************************

  # Initialize state information
  @chars  = split(//,$inputStr);
  $ch     = shift(@chars);
  $state  = 'base';
  $token  = "";
  $string = "";
  @tokens = ();

  # Enter the state machine
  while (1) {

    #=== base state =======================================
    if ($state eq 'base') {

      if (! defined $ch) {
        $state = 'done';
        next;
      }
      elsif ($ch eq '#') {
        $state = 'done';
        next;
      }
      elsif ($ch =~ m/\s/) {
        $ch = shift(@chars);
        next;
      }
      elsif ($ch eq '"') {
        $ch = shift(@chars);
        $state = 'string';
        next;
      }
      else {
        $token = $ch;
        $ch = shift(@chars);
        $state = 'token';
        next;
      }
    }

    #=== token state ======================================
    elsif ($state eq 'token') {

      if (! defined $ch) {
        push(@tokens,$token);
        $token = "";
        $state = 'base';
        next;
      }
      if ($ch eq '#') {
        push(@tokens,$token);
        $token = "";
        $state = 'base';
        next;
      }
      elsif ($ch =~ m/\s/) {
        push(@tokens,$token);
        $token = "";
        $state = 'base';
        next;
      }
      else {
        $token .= $ch;
        $ch = shift(@chars);
        next;
      }
    }

    #=== string state =====================================
    elsif ($state eq 'string') {

      if (! defined $ch) {
        push(@tokens, $token);
        $token = "";
        $state = 'base';
        next;
      }
      elsif ($ch eq '"') {
        push(@tokens, $token);
        $token = "";
        $ch = shift(@chars);
        $state = 'base';
        next;
      }
      else {
        $token .= $ch;
        $ch = shift(@chars);
        next;
      }
    }

    #=== done state =======================================
    elsif ($state eq 'done') {
      last;
    }

  }


  #*******************************************************
  # Switch parsing state machine, turn tokens and strings
  # into switch hash values.
  #*******************************************************

  # Initialize state information
  $args = {};
  @nonSwitches = ();
  $token = shift(@tokens);
  $state = 'base';
  $switch = "";

  # Enter the state machine
  while (1) {

    #=== base state =======================================
    if ($state eq 'base') {

      if (! defined $token) {
        $state = 'done';
        next;
      }

      elsif ($token =~ m/^-/) {
        $switch = $token;
        $token = shift(@tokens);
        $state = 'switch';
        next;
      }

      else {
        push(@nonSwitches,$token);
        $token = shift(@tokens);
        next;
      }
    }

    #=== switch state =====================================
    elsif ($state eq 'switch') {

      if (! defined $token) {
        $args->{$switch} = '1';
        $switch = "";
        $state = 'done';
        next;
      }

      elsif ($token =~ m/^-/) {
        $args->{$switch} = '1';
        $switch = "";
        $state = 'base';
        next;
      }

      else {
        $args->{$switch} = $token;
        $token = shift(@tokens);
        $state = 'base';
        next;
      }
    }

    #=== done state =======================================
    elsif ($state eq 'done') {
      last;
    }
  }

  #*******************************************************
  # Done with state machine parsing
  #*******************************************************

  return $args;
}

#--------------------------------------------------------------------------------------------
sub doHelp {

  my ($helpText)  = shift(@_);


    print $helpText;


  exit();
}   
#----------------------------------------------------------------------------------------------

__END__
###############################################################################################
# End of File
###############################################################################################
  