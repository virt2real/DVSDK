/*****************************************************************************/
/*                                                                           */
/*                            COMMON SPEECH CODEC                            */
/*                  ITTIAM SYSTEMS PVT LTD, BANGALORE                        */
/*                           COPYRIGHT(C) 2006                               */
/*                                                                           */
/*  This program  is  proprietary to  Ittiam  Systems  Private  Limited  and */
/*  is protected under Indian  Copyright Law as an unpublished work. Its use */
/*  and  disclosure  is  limited by  the terms  and  conditions of a license */
/*  agreement. It may not be copied or otherwise  reproduced or disclosed to */
/*  persons outside the licensee's organization except in accordance with the*/
/*  terms  and  conditions   of  such  an  agreement.  All  copies  and      */
/*  reproductions shall be the property of Ittiam Systems Private Limited and*/
/*  must bear this notice in its entirety.                                   */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/*  File Name         : test_utility.h                                       */
/*                                                                           */
/*  Description       : This header contains functions shared by             */
/*                      the speech encoder algorithms.                       */
/*  Version           : 0.3                                                  */
/*                                                                           */
/*  List of Functions : None                                                 */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         10 01 2005   Ittiam          Draft                                */
/*                                                                           */
/*****************************************************************************/


#ifndef _TEST_UTILILTY_
#define _TEST_UTILILTY_

/*****************************************************************************/
/* Enums                                                                     */
/*****************************************************************************/
typedef enum COMMAND
{
	INSTANTIATE = 1,
	START,
	STOP,
	CLOSE,
	FLUSH
}COMMAND;

typedef enum TESTING_MODES
{	
	NO_TEST = 0,
	INTERRUPT_TEST,
	PROFILE_TEST,
	STACK_TEST
}TESTING_MODES;
/*****************************************************************************/
/* Constant Macros                                                           */
/*****************************************************************************/
#define OPEN INSTANTIATE

/*****************************************************************************/
/* Union                                                                     */
/*****************************************************************************/

typedef union info_t
{
    char *file_string;
    int  count;
}info_t;

/*****************************************************************************/
/*  Function Declarations                                                    */
/*****************************************************************************/
void interrupt_algorithm(COMMAND cmd);
void profile_algorithm(COMMAND cmd);
void cache_algorithm(COMMAND cmd);
void stack_contamination(void);
int stack_usage(void);
void algo_testing(int test, int command);

#endif /* _TEST_UTILILTY_ */
