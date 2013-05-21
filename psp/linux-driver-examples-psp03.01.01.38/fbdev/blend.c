/*
 * Filename: blend.c
 * 
 * Function: Blending of RGB window with video window.
 *
 * This sample application demonstrates the blending of the OSD0 window with 
 * the video window by FBDEV drivers by directly writing into the OSD1 framebuffer.
 * The blend value entered by the user is used to set the OSD1 bit that controls the
 * blending factor of OSD window with video window. OSD1 has to be in attribute mode 
 * for this to work.
 * The blend factor will be set across the area entire area covered by OSD1.
*/
/* Header files */
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* True of false enumeration */
#define TRUE            1
#define FALSE           0

// Do not Initialise these anymore. They should be updated only if the device exists.
char *OSD1_DEVICE = NULL;

void printdev()
{
  if (OSD1_DEVICE == NULL){
                           printf("No OSD1 device\n");
                          }
                          else{
                               printf("OSD1 Device string is %s \n",OSD1_DEVICE);
                               }
}

void printVarInfo(struct fb_var_screeninfo *varInfo, char *device)
{

 printf("Var Info for %s\n",device);
 printf("xres:%d\n",varInfo->xres);
 printf("yres:%d\n",varInfo->yres);
 printf("xres_virtual:%d\n",varInfo->xres_virtual);
 printf("yres_virtual:%d\n",varInfo->yres_virtual);
 printf("xoffset:%d\n",varInfo->xoffset);
 printf("yoffset:%d\n",varInfo->yoffset);
 printf("bits per pixel:%d\n",varInfo->bits_per_pixel);
 printf("grayscale:%d\n",varInfo->grayscale);
 printf("nonstd:%d\n",varInfo->nonstd);
 printf("activate:%d\n",varInfo->activate);
 printf("height in mm:%d\n", varInfo->height);
 printf("width in mm:%d\n", varInfo->width);

} 

int main(int argc,char *argv[])
{

  FILE * fp;
  int c = 0;
  char d1[5];
  char d2[50];
  struct fb_var_screeninfo osdVarInfo;
  struct fb_fix_screeninfo osdFixInfo;
  char *osd1buff = NULL;
  int color = 0;
  int blend = 0;
  int memsize; 

  int fd = 0; //Handle for device file descriptors
 
  fp = fopen("/proc/fb","r");

  if (fp == NULL){
                  printf(" Unable to open /proc/fb for reading\n");
                 }  

  while( fscanf(fp,"%s",d1) != EOF)
  {
   fscanf(fp,"%s",d2);

    if (strcmp(d2,"dm_osd1_fb") == 0){
      OSD1_DEVICE = malloc(10);
      strcpy(OSD1_DEVICE,"/dev/fb");
      strcat(OSD1_DEVICE,d1);
      break;
      }
      // There need not be an else to this as OSD1 is alwaus initialized.
  }

  //printdev();
  fd = open(OSD1_DEVICE,O_RDWR);

  if (fd < 0){
   printf("Unable to open OSD1\n");
   return -1;
   }

  //printf("Opened OSD1 successfully\n");

 if (ioctl(fd,FBIOGET_VSCREENINFO,&osdVarInfo) < 0){
         printf("FBIOGET_VSCREENINFO Failed\n");
         return -1;
         }

 // Check if OSD1 is in Attribute mode.

  if (osdVarInfo.nonstd != 1){
       printf("OSD1 is not in attribute mode\n");
       return -1;
       }

 printVarInfo(&osdVarInfo,"OSD1");  

 if (ioctl(fd,FBIOGET_FSCREENINFO,&osdFixInfo) < 0){
         printf("FBIOGET_FSCREENINFO Failed\n");
         return -1;
         }


 // mmap osd1

 if (argc == 1){
               printf("Please enter blend factor from 0 to 15\n");
               printf("\t\t blend [0-15]\n");
               return -1;
               }

 if (argc > 2){
              printf("Too many arguments\n");
              printf("\t\t blend [0-15]\n");
              return -1;
              }

 color = atoi(argv[1]);
 
 if ((color < 0) || (color > 15)){
                              printf("Please enter blend factor from 0 to 15\n");
               printf("\t\t blend [0-15]\n");
               return -1;
               }


 blend = (((int) color & 0xf) << 4) | ((int) color);

 //width_bytes = (width * osdVarInfo.bits_per_pixel)/8;
  
   memsize = ((osdFixInfo.line_length*osdVarInfo.yres));

  osd1buff = (char *) mmap(NULL,memsize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

  if (osd1buff == MAP_FAILED){
                             printf("mmap failed\n");
                             return -1;
                             }  

                                memset(osd1buff,blend,memsize);
              
 //munmap

 munmap(osd1buff,memsize);
 
  return 0;
}
