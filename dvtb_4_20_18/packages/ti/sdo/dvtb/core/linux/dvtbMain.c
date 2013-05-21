/*
 * dvtbMain.c
 *
 * Parser and application main implementation
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include "dvtbMain.h"
#include "dvtbEngine.h"
#include "dvtbParam.h"
#include "dvtbSetParam.h"
#include "dvtbThread.h"
#include "dvtbDispatcher.h"
#include "dvtbApisDispatcher.h"
#include "dvtbAppInit.h"
#include "dvtbAppExit.h"
#include "dvtbUtils.h"

#define USE_EDITLINE

#ifdef USE_EDITLINE
#include "readline.h"
#endif

#include <ti/sdo/ce/trace/gt.h>

char PRINT_BUFF[MAX_LINE_SIZE];
FILE *perfFp = NULL;

/* Print a welcome screen */
void
dvtb_printWelcomeMessage()
{
	SYS_PRINTF("\r\n-----------------------------------------------------------------------------\r\n");
	SYS_PRINTF("\r\n===================***********************************=======================\r\n");
	SYS_PRINTF("\r\n\t\t    Digital Video Test Bench ( DVTB )\r\n");
	SYS_PRINTF("\r\n===================**********************************========================\r\n");
	SYS_PRINTF("\r\n-----------------------------------------------------------------------------\r\n");
}

/* Check whether an exit command has come */
DvevmStBool
dvtb_quit(char *buff)
{
	if (NULL == buff)
		return DVEVM_ST_FALSE;
	else if (0 == strcmp("z", buff))
		return DVEVM_ST_TRUE;
	else if (0 == strcmp("exit", buff))
		return DVEVM_ST_TRUE;
	else
		return DVEVM_ST_FALSE;
}

/* Reports status back to the user */
void
dvtb_reportStatus(DvevmStRetCode rc, char *str)
{
	char *buff;

	if (DVEVM_ST_SUCCESS == rc)
		buff = "PASS";
	else if (DVEVM_ST_PNDG == rc)
		buff = "PNDG";
	else
		buff = "FAIL";

	SYS_PRINTF("%s: %s\n", buff, str);
}

/* Reads from a file until end of line */
int
dvtb_readFile(FILE *fp, char *line)
{
	int nBytes = 0;
	char *buff = NULL;

	ASSERT(fp);
	ASSERT(line);

	buff = fgets(line, MAX_LINE_SIZE, fp);
	if (NULL == buff)
		nBytes = DVEVM_ST_FAIL;
	else
	{
		nBytes = strlen(buff) - 1;
		buff[nBytes] = 0;
	}

	if (nBytes > 0)
		SYS_PRINTF("%s\n ", line);

	SYS_DEBUG("Read line : %s, %d\n", line, nBytes);
	return nBytes;
}

/* Reads from host interface until a new line */

int
dvtb_readLine(char *line)
{
	int i = DVEVM_ST_FAIL;
	char *buff = NULL;

	if (NULL == line)
	{
		SYS_ERROR("Cannot read to a NULL pointer\n");
		return i;
	}

	memset(line, 0, MAX_LINE_SIZE);

#ifndef USE_EDITLINE
	DVTB_ST_PROMPT();

	for(i=0; i<MAX_LINE_SIZE; i++)
	{
		char outchar[2];
		line[i] = fgetc(stdin);

		if( line[i] == '\n'|| line[i] == '\r')
		{
			SYS_PRINTF("\n\r");
			DVEVM_ST_FLUSH();
			break;
		}

		outchar[1] = '\0';
		outchar[0] = line[i];

		if (BS_CHAR == line[i])
		{
			SYS_PRINTF((char *)outchar);
			SYS_PRINTF(SPACE_CHAR);
			if (i >= 1)
			{ /* If cmd lines chars >=1, get rid of the char */
				i -= 2;
				SYS_PRINTF((char *)outchar);
				DVEVM_ST_FLUSH();
			} /* backspace at first cmd line char, just ignore */
			else
			i--;
			continue;
		}

		/* If this is not an ESC char, nor the previous one, print out char */
		if (outchar[0] != 0x1b && line[i-1] != 0x1b)
		{
			SYS_PRINTF(outchar);
			DVEVM_ST_FLUSH();
		}
	}

	line[i] = 0;
#else

	buff = readline((const char *) DVTB_PROMPT);
	if (NULL != buff && 0 != buff[0])
	{
		i = strlen(buff);
		strncpy(line, buff, i);
		add_history(line);
		free(buff);
	} else
		i = 0;
#endif

	return i;
}

/* Parse the input line into tokens */
int
dvtb_tokenize(char *buff, char **tokens, int maxTokens)
{
	int numTokens = 0;

	while ((*buff != CHAR_ZERO) && (numTokens < maxTokens))
	{
		while ((*buff == ' ') || (*buff == '\t') || (*buff == '\n'))
			*buff++ = CHAR_ZERO;

		if (CHAR_ZERO == *buff)
			break;

		*tokens++ = buff;
		numTokens++;

		while ((*buff != CHAR_ZERO) && (*buff != ' ') && (*buff != '\t') && (*buff != '\n'))
			buff++;
	}

	*tokens = NULL;
	return numTokens;
}

void
dvtb_waitForThreads()
{
	int i = 0;

	for (i = 0; i < MAX_THREADS; i++)
	{
		if (TH[i].inUse)
			pthread_join(TH[i].thrId, NULL);
	}
}

int
main(int argc, char *argv[])
{
	int nBytes = 0, numTokens = 0;
	char buff[MAX_LINE_SIZE], *parsedTokens[MAX_TOKENS], *script = NULL;

	FILE *fp = NULL;
	DvevmStRetCode rc = DVEVM_ST_FAIL;
	DvevmStBool useScript = DVEVM_ST_FALSE;

	if (argc >= 3)
	{
		if (0 == strcmp(argv[1], "-s"))
		{
			script = argv[2];
			useScript = DVEVM_ST_TRUE;
		}
	}

	if (useScript)
	{
		if(DVEVM_ST_FAIL == dvtb_fileOpen(&fp, script, "r"))
		{
			SYS_PERROR("Unable to open script file %s\n",script);
			return DVEVM_ST_FAIL;
		}
	}

	if (DVEVM_ST_FAIL == dvtb_fileOpen(&perfFp ,PERF_LOGFILE, "w"))	
	{
		SYS_PERROR("Unable to open performance log file\n");
		return DVEVM_ST_FAIL;
	}

	dvtb_apisInit( );

	dvtb_initThr( );

	if (!useScript)
		dvtb_printWelcomeMessage( );

	DVEVM_ST_FLUSH( );
	rc = dvtb_initApp( );
	ASSERT(rc != DVEVM_ST_FAIL);

	while (DVEVM_ST_TRUE)
	{
		SYS_PRINTF("\n");
		memset(buff, 0, MAX_LINE_SIZE);
		if (useScript)
			nBytes = dvtb_readFile(fp, buff);
		else
			nBytes = dvtb_readLine(buff);

		if (DVEVM_ST_FAIL == nBytes)
			break;

		if ('#' == buff[0] || 0 == nBytes || 0 == buff[0])
			continue;

		numTokens = dvtb_tokenize(buff, parsedTokens, MAX_TOKENS);
		if (0 == numTokens)
			continue;

		if (dvtb_quit(parsedTokens[0]))
		{
			SYS_PRINTF("Exiting .......\n");
			break;
		}
		
		rc = dvtb_execute(numTokens, parsedTokens);
		dvtb_reportStatus(rc, parsedTokens[0]);
	}

	dvtb_waitForThreads( );
	fclose(perfFp);

	rc = dvtb_unInitApp( );
	ASSERT(rc != DVEVM_ST_FAIL);

	return 0;
}
