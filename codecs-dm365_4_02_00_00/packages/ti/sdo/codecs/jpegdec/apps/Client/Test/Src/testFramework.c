#include "tistdtypes.h"
#include "testFramework.h"

#ifndef MULTI_INSTANCE_TEST

FILE *fConfigFile, *ftestFile, *fjpegFile, *fparamsFile;
FILE *fdumpFile;
static Uint16 countConfigSet;
static sTokenMapping *sTokenMap;
static TestType *testType; 


Int32 initTestFramework(Int8 *fname, TestType *testtype, sTokenMapping *sTokenmap){
    
    sTokenMap = sTokenmap;
    testType= testtype;

 /* Open Test Config File                                                    */
  fConfigFile = fopen(fname,"r");

  if (!fConfigFile)
  {
      printf("Couldn't open parameter file %s",fname);
      return XDM_EFAIL;
  }

  countConfigSet = 1; /* Reset countConfigSet value to 1 */
  return XDM_EOK;
}


Int32 nextTestSet(){

  Int8 line[STRING_SIZE], inFile[STRING_SIZE], jpegFile[STRING_SIZE], testFile[STRING_SIZE],
       paramsFile[STRING_SIZE], dumpFile[STRING_SIZE], testCompliance;


  /* Read the Config File until it reaches the end of file                    */
  if (feof(fConfigFile)){
   printf("End of config file reached\n");
   fclose(fConfigFile);
   return 1;
   }
  else
  { 
    /* Read Compliance Checking parameter */
    if(fgets(line,254,fConfigFile))
    {
      sscanf(line,"%d",testType);
    }
    else
    {
     return XDM_EFAIL;
    }

	if(fgets(line,254,fConfigFile))
    {
      sscanf(line,"%s",paramsFile);
    }
    else
    {
      return XDM_EFAIL;
    }

	if(fgets(line,254,fConfigFile))
    {
      sscanf(line,"%s",jpegFile);
    }
    else
    {
      return XDM_EFAIL;
    }

	if(*testType==TEST_FILECOMP){
	    /* Read Output/Reference file name */
	    if(fgets(line,254,fConfigFile))
	    {
	      sscanf(line,"%s",testFile);
	    }
	    else
	    {
	      return XDM_EFAIL;
	    }

	}

	if(*testType==TEST_FILEDUMP){
	    /* Read Output/Reference file name */
	    if(fgets(line,254,fConfigFile))
	    {
	      sscanf(line,"%s",dumpFile);
	    }
	    else
	    {
	      return XDM_EFAIL;
	    }

		}


    printf("\n*******************************************");
    printf("\nRead Configuration Set %d",countConfigSet);
    printf("\n*******************************************");
	  countConfigSet++;

    /* Open Parameters file */
    fparamsFile = fopen (paramsFile, "rb");
    if (!fparamsFile)
    {
      printf("\nCouldn't open Parameters file...   %s\n ",paramsFile);
      printf("Exiting for this configuration...\n");
	  return XDM_EFAIL;
    }
	  
    if(readparamfile(fparamsFile, sTokenMap) < 0 )
    {
      printf("\nSyntax Error in %s\n ",paramsFile);
      printf("Exiting for this configuration...\n");
	  return XDM_EFAIL;
    }
    
    /* Close Parameters File */
    fclose(fparamsFile);
    
    fjpegFile = fopen (jpegFile, "rb");
	if( !fjpegFile){
      	printf("\nCouldn't open Jpeg File... %s",jpegFile);
	    printf("\n Exiting for this configuration..." );
		return XDM_EFAIL;
    	}
	else
		printf("\nOpened file %s\n",jpegFile); 

    switch (*testType){

	case TEST_FILECOMP:
      printf("\nRunning in file comparison");
	   ftestFile = fopen (testFile, "rb");
	   if( !ftestFile){
      	printf("Couldn't open Test File... %s",testFile);
	    printf("\n Exiting for this configuration..." );
		return XDM_EFAIL;
    	}
      break;

	case TEST_FILEDUMP:
      fdumpFile = fopen (dumpFile, "wb");
	  if (!fdumpFile) {
		printf("\nCouldn't open dump File... %s",dumpFile);
	    printf("\nExiting for this configuration..." );
		return XDM_EFAIL;
	  }

      break;

	}

    
 	return XDM_EOK;
	}
}

Uint32 testReadJpegfile(char *output, Uint32 len){

	Uint32 bufferSize;
	if(output == NULL) {
		printf("Invalid Buffer pointer.\n");
		return FALSE;
	}

	fseek (fjpegFile, 0, SEEK_END);
	bufferSize = ftell (fjpegFile);
	printf("\nFileSize = %d, ", bufferSize);
	
	if(bufferSize <= len) {
		printf("Reading file ...");
		fflush(stdout);
		fseek (fjpegFile, 0, SEEK_SET);
	if(output != NULL)
	{
		fread(output, 1, bufferSize, fjpegFile);
		printf("done\n");
	}
	} else {
		printf("Input buffer is smaller than the total file size.. exiting\n"); 
	}
	fclose(fjpegFile);
	return bufferSize;
}

#endif //#ifndef MULTI_INSTANCE_TEST

