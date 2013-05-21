/*
 * saBootApp.c
 * Application to boot DM6467 PCI Target. Runs on host and uses character
 * device interface provided by DM6467 PCI boot driver to boot DM6467 target.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*******************************************************************************
 *	LOCAL INCLUDES
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>		/**< For mmap support */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/ioctl.h>

#define u32	u_int32_t
#include <dm646x_pci_targetdrv.h>

/*******************************************************************************
 *	LOCAL STRUCTURE DEFINITIONS
 */

/*******************************************************************************
 *	LOCAL DEFINES
 */

/*******************************************************************************
 *	FILE GLOBALS
 */
static int dev_desc = -1;
static char * mapped_buffer = NULL;

/*******************************************************************************
 *	FUNCTION DEFINITIONS
 */
static int remapped_copy(char * file_name);
static int map_file(char * file_name, unsigned int bar_number
    , unsigned int barOffset);
static int console_control(void);
static unsigned int get_hex_number(char * input_string);
static int kbhit(void);

/*******************************************************************************
 *	FUNCTION DEFINITIONS
 */
/**
 *	Application function to demonstrate file transfer
 */
int main(int argc, char * argv[])
{
    int result = 0;
    struct DM646x_Remap_Bar_Args remap_bar_args;
    char dev_name[128] = "/dev/";

    /**
     *	1.  Ensure there is a single argument
     */
    if(4 != argc)
    {
        printf("Program requires file name to be passed to it\n");
        printf("for eg: [linux-prompt]# "
            "./saBootApp.o ublDaVinci.bin u-boot.bin "
            "bootScript.img\n");
        return -1;
    }
    
    /**
     *	2.  Open device file for writing data
     */
    strcat(dev_name, DM646X_PCI_MODFILE);
    dev_desc = open(dev_name, O_RDWR);
    if(-1 == dev_desc)
    {
        printf("Device \"%s\" could not opened\n", dev_name);
        return -1;
    }

    /**
     *	3.  Map the UBL onto the DaVinciHD Card and
     *      then run it
     */
    result = map_file(argv[1], 0, 0x20);
    if(0 != result)
    {
        printf("Mapping of UBL to IRAM failed\n");
        close(dev_desc);
        return result;
    }

    /**
     *	4.  Transfer control to the UBL and
     *      then run it
     */
    result = ioctl(dev_desc, DM646X_PCI_RUN_TCM_IMG);
    if(0 != result) 
    {
        printf("Failed to run the UBL\n");
        close(dev_desc);
        return -1;
    }

    /**
     *	5.  Map the Boot script file into the DDR2-A
     */
    result = map_file(argv[3], 4, 0x80000);
    if(0 != result)
    {
        printf("Mapping of Boot-script to DDR2-A failed\n");
        close(dev_desc);
        return result;
    }

    /**
     *	8.	Remap BAR-4 to 0x81000000 to copy U-Boot
     */
    remap_bar_args.bar_number = 4;
    remap_bar_args.new_window = 0x81000000;
    result = ioctl(dev_desc, DM646X_PCI_REMAP_BAR, &remap_bar_args);
    if(0 != result)
    {
        printf("Error: Bar remapping to 0x81000000 failed\n");
        close(dev_desc);
        return -1;
    }
    
    /**
     *	9.	Map the u-boot.bin onto the DaVinciHD Card
     */
    result = map_file(argv[2], 4, 0x80000);
    if(0 != result)
    {
        printf("Mapping of uBoot to DDR2 failed\n");
        close(dev_desc);
        return result;
    }

    /**
     *	10.	Remap BAR-4 back  to 0x82000000 for other operations 
     */
    remap_bar_args.bar_number = 4;
    remap_bar_args.new_window = 0x82000000;
    result = ioctl(dev_desc, DM646X_PCI_REMAP_BAR, &remap_bar_args);
    if(0 != result)
    {
        printf("Error: Bar remapping back to 0x82000000 failed\n");
        close(dev_desc);
        return -1;
    }
 
    /**
     *  11.  Write the boot location for U-boot and run it
     */
    result = ioctl(dev_desc, DM646X_PCI_BOOT_IMAGE, 0x81080000);
    if(0 != result) 
    {
        printf("Could not write boot address\n");
        close(dev_desc);
        return result;
    }

    /**
     *  12.  Run PCI console for runtime controls
     */
    result = console_control();
    if(0 != result)
    {
        printf("Console returned with error\n");
    }
    printf("Interrupt generation console closed safely\n");

    close(dev_desc);
    return result;
}

/*******************************************************************************
 *  Function to use mmap and remap IOCTL to copy files beyond BAR limits 
 */
static int remapped_copy(char * file_name)
{
    int result = -1;
    FILE * file_desc = NULL;
    unsigned int file_length = 0;
    struct DM646x_Remap_Bar_Args remap_bar_args;
    unsigned int bar_number = 5, bar_size = 0x800000;

    /**
     *   1.  Map BAR-4 namely, DDR2_A (0x82000000) with a size of 8MB here
     */
    mapped_buffer = (char *)mmap (NULL, bar_size, (PROT_READ|PROT_WRITE)
        , MAP_SHARED, dev_desc, (off_t) bar_number*getpagesize());
    if (MAP_FAILED == (void *) mapped_buffer)
    {
        printf("Error: Cannot mmap = %d bytes buffer\n"
            , bar_size);
        return -1;
    }
    printf("Bar-%d mapped to 0x%08x\n", (int)bar_number
        , (int)mapped_buffer);
    fflush(stdout);

    /**
     *   2.  Open the file to be read
     */
    file_desc = fopen(file_name, "rb");
    if(!file_desc)
    {
        printf("Specified file \"%s\" not found\n", file_name);
        munmap(mapped_buffer, bar_size);
        return -1;
    }
    printf("%s file opened\n", file_name);
    fflush(stdout);

    /**
     *	3.  Query size of the file to be sent
     */
    fseek(file_desc, 0, SEEK_END);
    file_length = ftell(file_desc);
    fseek(file_desc, 0, SEEK_SET);
    printf("Size of %s file = %d\n", file_name
        , (int)file_length);
    fflush(stdout);

    /**
     *  4.  Read the file straight into the mapped buffer
     */
    result = fread((mapped_buffer + (bar_size - 0x100000)), 1
        , 0x100000, file_desc);
    if(result < 0x100000)
    {
        printf("Could only read %d bytes from the file \"%s\""
            , result, file_name);
        fclose(file_desc);
        munmap(mapped_buffer, bar_size);
        return -1;
    }
    printf("%d bytes read from file %s\n", 0x100000, file_name);
    fflush(stdout);

    /**
     *  5.  Remap the BAR-5 to the next 8MB of DDR2 memory
     */
    remap_bar_args.bar_number = bar_number;
    remap_bar_args.new_window = 0x83000000;
    result = ioctl(dev_desc, DM646X_PCI_REMAP_BAR, &remap_bar_args);
    if(0 != result)
    {
        printf("Bar remapping failed\n");
        fclose(file_desc);
        munmap(mapped_buffer, bar_size);
        return -1;
    }
    printf("Bar-%d remapped to 0x%08x\n", (int)bar_number
        , (int)remap_bar_args.new_window);
    fflush(stdout);

    /**
     *  6.  Copy the remaining file in the start of new window
     */
    result = fread((mapped_buffer), 1
        , (file_length - 0x100000), file_desc);
    if(result < (file_length - 0x100000))
    {
        printf("Could only read %d bytes from the file \"%s\""
            , result, file_name);
        fclose(file_desc);
        munmap(mapped_buffer, bar_size);
        return -1;
    }
	printf("%d bytes read from file %s\n"
        , (file_length - 0x100000), file_name);
    fflush(stdout);

    /**
     *  7.  Cleanup the system
     */
    remap_bar_args.bar_number = bar_number;
    remap_bar_args.new_window = 0x82800000;
    result = ioctl(dev_desc, DM646X_PCI_REMAP_BAR, &remap_bar_args);
    if(0 != result)
    {
        printf("Bar remapping failed\n");
        fclose(file_desc);
        munmap(mapped_buffer, bar_size);
        return -1;
    }
    printf("Bar-%d remapped to 0x%08x\n", (int)bar_number
        , (int)remap_bar_args.new_window);
    fflush(stdout);

    fclose(file_desc);
    munmap(mapped_buffer, bar_size);
    return 0;
}

/*******************************************************************************
 *  Function to use mmap to copy files
 */
static int map_file(char * file_name, unsigned int bar_number
    , unsigned int barOffset)
{
    int result = -1;
    FILE * file_desc = NULL;
    unsigned int file_length = 0;
    unsigned int bar_size = 0;
   
    /**
     *   1.  Set the size of BAR intrinsically
     */
    switch(bar_number)
    {
        // TCM IRAM memory      = 32KB
        case 0: 
            bar_size = 32 * 1024;
            break;
        // EMIF Registers       = 32KB
        case 1: 
            bar_size = 32 * 1024;
            break;
        // Chip MMR registers   = 4MB
        case 2: 
            bar_size = 0x400000;
            break;
        // L2 RAM               = 128KB
        case 3: 
            bar_size = 128 * 1024;
            break;
        // DDR-2 A-Window       = 8MB
        case 4:
            bar_size = 0x800000;
            break;
        // DDR-2 B-Window       = 8MB
        case 5: 
            bar_size = 0x800000;
            break;
        default:
            break;
    }
    
    /**
     *   2.  Map BAR-4 namely, DDR2_A (0x82000000) with a size of 8MB here
     */
    mapped_buffer = (char *)mmap (NULL, bar_size, (PROT_READ|PROT_WRITE)
        , MAP_SHARED, dev_desc, (off_t) bar_number*getpagesize());
    if(MAP_FAILED == (void *) mapped_buffer)
    {
        printf("Error: Cannot mmap = %d bytes buffer\n"
            , bar_size);
        return -1;
    }

    /**
     *   3.  Open the file to be read
     */
    file_desc = fopen(file_name, "rb");
    if(!file_desc)
    {
        printf("Specified file \"%s\" not found\n", file_name);
        munmap(mapped_buffer, bar_size);
        return -1;
    }
    printf("%s file opened\n", file_name);
    fflush(stdout);

    /**
     *	4.  Query size of the file to be sent
     */
    fseek(file_desc, 0, SEEK_END);
    file_length = ftell(file_desc);
    fseek(file_desc, 0, SEEK_SET);
    printf("Size of %s file = %d\n", file_name
        , (int)file_length);
    fflush(stdout);

    /**
     *  5.  Read the file straight into the mapped buffer
     */
    result = fread((mapped_buffer + barOffset), 1
        , file_length, file_desc);
    if(result < file_length)
    {
        printf("Could only read %d bytes from the file \"%s\""
            , result, file_name);
        fclose(file_desc);
        munmap(mapped_buffer, bar_size);
        return -1;
    }
    printf("%d bytes read from file %s\n", file_length, file_name);
    fflush(stdout);

    /**
     *  6.  Cleanup the system
     */
    fclose(file_desc);
    munmap(mapped_buffer, bar_size);
    return 0;
}

/*******************************************************************************
 *  Function to generate interrupts to the DM6467
 */
#define CMD_LEN         (128)
static int console_control(void)
{
    char cmd[CMD_LEN];
    int result = -1;
    memset(cmd, '\0', CMD_LEN);
    printf("\nType \"help\" or \"?\" for available commands");
    printf("\nPCIConsole:\\> ");
    gets(cmd);
    while((0 != strcmp("exit", cmd))&& (0 != strcmp("quit", cmd)))
    {
        if(0 == strcmp("int",cmd))
        {
            result = ioctl(dev_desc, DM646X_PCI_GEN_INTRPT);
            if(0 != result)
            {
                printf("Failed to generate interrupt\n");
                return result;
            }
            printf("Sent software interrupt to DM6467\n");
        }
        else if((0 == strcmp("help", cmd)) 
            || (0 == strcmp("?", cmd)))
        {
            printf("\"int\"    \t-Send an interrupt to DM6467 device\n");
            printf("\"exit/quit\"\t-Exit PCI console\n");
            printf("\"help\"   \t-Prints the help menu\n");
        }
        else
        {
            system(cmd);
        }

        printf("\nPCIConsole:\\> ");
        gets(cmd);
    }
    return 0;
}

/*******************************************************************************
 *  Function to convert a hex number in string format to actual value
 */
static unsigned int get_hex_number(char * input_string)
{
    unsigned char temp_string [11] = "0x";
    unsigned int value = 0;
    
    /*
     * The input is always considered as hex
     */
    if ( input_string [ 0 ] == '0' \
        && ( input_string [ 1 ] == 'x' ||  input_string [ 1 ] == 'X' ) )
    {
        strcpy ((char *)&temp_string[2]
            , (const char *)&input_string[2]);
    }
    else
    {
        /* Skip 0x already entered */
        strcat ((char *)&temp_string[2]
            , (const char *)input_string );
    }
    input_string[10] = '\0';
    
    value = strtoul ( (const char *)temp_string
        , NULL, 16 /* Radix - Hex */ );
    
    return      value;
}

/******************************************************************************
 *  Function to check for keyboard inputs
 */
static int kbhit(void)
{
    struct timeval tv;
    fd_set read_fd;

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);

    if(-1 == select(1, &read_fd, NULL, NULL, &tv))
        return 0;

    if(FD_ISSET(0, &read_fd))
        return 1;

    return 0;
}
