/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  */
/*
 *  ======== GT_config_WinCE.c ========
 *  Description:
 *      WinCE configuration parameters for GT.  This file is separated from
 *      gt.c so that GT_assert() can reference the error function without
 *      forcing the linker to include all the code for GT_set(), GT_init(),
 *      etc. into a fully bound image.  Thus, GT_assert() can be retained in
 *      a program for which GT_?trace() has been compiled out.
 */

#include <xdc/std.h>

#include <ti/sdo/ce/osal/Global.h>

#include <stdarg.h>
#include <string.h>

#include <windows.h>
#include <dbgapi.h>

/*
 *  Compute maximum number of digits for integer octal representation
 *  this always longest since this is the smallest base!  For floating
 *  point add 5 (4 decimal places + '.') more.
 */
#define OUTMAX      ((32 + 2) / 3)

/* max line line length before forcing a newline */
#define MAXLINE 200

Void GTConfig_error(String msg, ...);
UInt32 GTConfig_gettimeofday(Void);
Void GTConfig_free(Ptr addr, Int size);
Ptr  GTConfig_malloc(Int size);
Void GTConfig_printf(String format, ...);
Int  GTConfig_threadId(Void);
Void GTConfig_tracePrintf(String format, ...);

static Void doPrint(Char *buf, String fmt, va_list va);
static Void doPutch(char ch);
static Char *formatNum(Char *ptr, UInt32 n, Int zpad, Int base);
//static Void printfCaller(String format, ...);
static Void putch(Char **bptr, Char ch);

static const Char digtohex[] = "0123456789abcdef";

static Bool   GTConfig_gettimeofdayInit = FALSE;
static UInt32 initTime   = 0;

static Void   cleanup(Void);


/* REMINDER: if you add an initialized static var, reinitialize it at cleanup */
static Bool curInit = FALSE;

/* this one is global -- a backdoor for TraceUtil */
FILE *GT_config_traceOutStream = NULL;

/* this is a FILE pointer we opened, if any -- we remember it for closing */
static FILE  *traceOutStreamOpenedHere = NULL;

static HANDLE mutex;



/*
 * ======== GTConfig_error ========
 *  purpose:
 *      Prints error onto the standard output.
 */
void GTConfig_error(String fmt, ...)
{
    Int arg1, arg2, arg3, arg4, arg5, arg6;

    va_list va;

    va_start(va, fmt);

    arg1 = va_arg(va, Int);
    arg2 = va_arg(va, Int);
    arg3 = va_arg(va, Int);
    arg4 = va_arg(va, Int);
    arg5 = va_arg(va, Int);
    arg6 = va_arg(va, Int);

    va_end(va);

//    printfCaller("ERROR: ");
//    printfCaller(fmt, arg1, arg2, arg3, arg4, arg5, arg6);
    GTConfig_printf("ERROR: ");
    GTConfig_printf(fmt, arg1, arg2, arg3, arg4, arg5, arg6);
}

/*
 *  ======== GTConfig_free ========
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Void GTConfig_free(Ptr addr, Int size)
{
    free(addr);
}

/*
 *  ======== GTConfig_gettimeofday ========
 *  return wallclock time in usec (starting from the from the first call to
 *  this function)
 */
UInt32 GTConfig_gettimeofday(Void)
{
    DWORD time;

    if (GTConfig_gettimeofdayInit == FALSE) {
        GTConfig_gettimeofdayInit = TRUE;
        initTime = GetTickCount();
    }

    time = GetTickCount();
    return ((2 * time - initTime) * 1000);
}

/*
 *  ======== GTConfig_init ========
 */
Int GTConfig_init(Void)
{
    String fileName;
    String fileFlags = "a"; /* assign here to keep compiler quiet */

    if (curInit != TRUE) {

        curInit = TRUE;

        Global_init();

        if ((fileName = Global_getenv("CE_TRACEFILE")) != NULL) {
            if ((fileFlags = Global_getenv("CE_TRACEFILEFLAGS")) == NULL) {
                fileFlags = "a";
            }
            GT_config_traceOutStream = fopen(fileName, fileFlags);
            if (GT_config_traceOutStream != NULL) {
                traceOutStreamOpenedHere = GT_config_traceOutStream;
            }
        }
        if (GT_config_traceOutStream == NULL) {
            GT_config_traceOutStream = stdout;
            if ((fileName != NULL) && (fileName[0] != '\0')) {
                printf("Warning: could not open file '%s' in mode '%s' "
                    "for writing trace.\n", fileName, fileFlags);
            }
        }

        /*
         *  TODO: (jeh) Should this be a named mutex? Does it need to protect
         *  accross processes?
         */
        /* initialize mutex */
                mutex = CreateMutex(NULL, FALSE, NULL);

        /* call Global_atexit() to schedule our cleanup. Global module
         * has not been initialized yet, but he knows we'll call him
         * here so he knows how to deal with this call.
         */
         Global_atexit((Fxn)cleanup);
    }
    return (1);
}

/*
 *  ======== GTConfig_malloc ========
 */
Ptr GTConfig_malloc(Int size)
{
    return malloc(size);
}

/*
 *  ======== GTConfig_printf ========
 */
Void GTConfig_printf(String format, ...)
{
    va_list va;

    va_start(va, format);
    doPrint(NULL, format, va);
    va_end(va);
}

/*
 *  ======== GTConfig_setOutTrace ========
 * [dm]TODO:M expose this func in an interface
 */
Void GT_config_setOutTrace(FILE *newOutTrace)
{
    GT_config_traceOutStream = newOutTrace;

}

/*
 *  ======== GTConfig_threadId ========
 */
Int GTConfig_threadId()
{
    DWORD   threadId;

    threadId = GetCurrentThreadId();
    return ((Int)threadId);
}

/*
 *  ======== GTConfig_threadLock ========
 */
Int GTConfig_threadLock(Void)
{
    WaitForSingleObject(mutex, INFINITE);
    return(1);
}


/*
 *  ======== GTConfig_threadUnlock ========
 */
Int GTConfig_threadUnlock(Void)
{
    ReleaseMutex(mutex);
    return (1);
}

/*
 *  ======== GTConfig_tracePrintf ========
 */
Void GTConfig_tracePrintf(String format, ...)
{
    va_list va;

    if (GT_config_traceOutStream == NULL) {
        GT_config_traceOutStream = stdout;
    }

    va_start(va, format);
    vfprintf(GT_config_traceOutStream, format, va);
    va_end(va);

    /* don't flush GT_config_traceOutStream because flush is *very* expensive;
     * we use line buffering instead (see init()).
     */
    /* fflush(GT_config_traceOutStream); */
}

/*
 *  ======== cleanup ========
 */
static Void cleanup()
{
    Int status;

    if (curInit != FALSE) {

        curInit = FALSE;

        if (traceOutStreamOpenedHere != NULL) {
            fclose(traceOutStreamOpenedHere);
        }

        status = CloseHandle(mutex);

        /* destroy fails try to unlock before freeing the object */
        if (status == 0) {
            do {
                status = ReleaseMutex(mutex);
            } while (status == 0);
            CloseHandle(mutex);
        }

        /* reinit static vars */
        GT_config_traceOutStream = NULL;
        traceOutStreamOpenedHere = NULL;
        GTConfig_gettimeofdayInit = FALSE;
        initTime                 = 0;
    }
}

/*
 *  ======== doPrint ========
 */
static Void doPrint(Char *buf, String fmt, va_list va)
{
    Int     base;
    Char    c;
    Char    *end;
    Int     length;
    Bool    lFlag;              /* length modifier flag */
    Char    outbuf[OUTMAX];
    Char    *ptr;
    Int     width;
    Int     zpad;               /* leading zero pad flag */

    if (fmt == (Char *)NULL) {
        return;
    }

    while ((c = *fmt++) != '\0') {
        if (c != '%') {
            putch(&buf, c);
        }
        else {
            c = *fmt++;
            /* check for leading 0 pad */
            if (c == '0') {
                zpad = 1;
                c = *fmt++;
            }
            else {
                zpad = 0;
            }

            /* allow optional field width specification */
            width = 0;
    
            /* note: dont use isdigit (very large for C30) */
            while (c >= '0' && c <= '9') {
                width = width * 10 + c - '0';
                c = *fmt++;
            }

            /* setup for leading zero padding */
            if (zpad) {
                zpad = width;
                width = 0;
            }

            /* check for presence of l flag (e.g., %ld) */
            if (c == 'l' || c == 'L') {
                lFlag = TRUE;
                c = *fmt++;
            }
            else {
                lFlag = FALSE;
            }

            ptr = outbuf;
            end = outbuf + OUTMAX;

            if (c == 'd' || c == 'i') {
                /* signed decimal */
                ptr = formatNum(end, lFlag ? (Int32)va_arg(va, long int) :
                        (Int32)va_arg(va, int), zpad, -10);
                length = end - ptr;
            }
            /* use comma operator to optimize code generation! */
            else if (((base = 10), (c == 'u')) ||   /* unsigned decimal */
                    ((base = 16), (c == 'x'))  ||   /* unsigned hex */
                    ((base = 8),  (c == 'o'))) {    /* unsigned octal */

                ptr = formatNum(end, lFlag ? (UInt32)va_arg(va, unsigned long):
                        (UInt32)va_arg(va, unsigned), zpad, base);
                length = end - ptr;
            }
            else if (c == 'c') {
                /* character */
                *ptr = (Char)va_arg(va, int);
                length = 1;
            }
            else if (c == 's') {
                /* string */
                ptr = va_arg(va, char *);

                /* substitute (null) for NULL pointer */
                if (ptr == (char *)NULL) {
                    ptr = "(null)";
                }
                length = strlen(ptr);
            }
            else {
                /* other character (like %) copy to output */
                *ptr = c;
                length = 1;
            }
        
            /* compute number of characters left in field */
            width -= length;
        
            /* pad with blanks on left */
            while (--width >= 0) {
                putch(&buf, ' ');
            }

            /* output number, character or string */
            while (length--) {
                putch(&buf, *ptr++);
            }
        } /* if */
    } /* while */
    
    if (buf) {
        *buf = '\0';
    }
}

/*
 *  ======== formatNum ========
 *  format unsigned long number in specified base returning returning
 *  pointer to converted output.  Note ptr points PAST end of buffer
 *  and is decremented as digits are converted from right to left!
 *
 *  Note: base is negative if n is signed else n unsigned!
 */
static Char *formatNum(Char *ptr, UInt32 n, Int zpad, Int base)
{
    Int i = 0;
    Char sign = 0;

    if (base < 0) {
        /* handle signed long case */
        base = -base;
        if ((Int32) n < 0) {
            n = -(Int32)n;
        
            /* account for sign '-': ok since zpad is signed */
            --zpad;
            sign = '-';
        }
    }

    /* compute digits in number from right to left */
    do {
        *(--ptr) = digtohex[(Int) (n % base)];
        n = n / base;
        ++i;
    } while (n);

    /* pad with leading 0s on left */
    while (i < zpad) {
        *(--ptr) = '0';
        ++i;
    }
    
    /* add sign indicator */
    if (sign) {
        *(--ptr) = sign;
    }
    return ptr;
}

/*
 *  ======== putch ========
 */
static Void putch(Char **bptr, Char c)
{
    if (*(bptr)) {
        (*(*(bptr))++ = (c));
    }
    else {
        doPutch(c);
    }
}

/*
 *  ======== doPutch ========
 */
static Void doPutch(char ch)
{
    static TCHAR buffer[MAXLINE + 3];
    static TCHAR *cp = buffer;
    
    if ((*cp++ = ch) == '\n') {
        *cp = '\r';
        *++cp = '\n';
        *++cp = '\0';
        cp = buffer;
        RETAILMSG(1, (buffer));
    }
    
    if (cp >= buffer + MAXLINE) {
        *cp++ = '\r';
        *cp++ = '\n';
        *cp = '\0';
        cp = buffer;
        RETAILMSG(1, (buffer));
    }
}
/*
 *  @(#) ti.sdo.ce.osal.wince; 1, 0, 0,82; 12-2-2010 21:25:04; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

