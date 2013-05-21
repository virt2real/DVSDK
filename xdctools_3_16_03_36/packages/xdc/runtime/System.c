/* --COPYRIGHT--,ESD
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * --/COPYRIGHT--*/
/*
 *  ======== System.c ========
 */

#include <xdc/runtime/Startup.h>

#include <xdc/runtime/Gate.h>

#include "package/internal/System.xdc.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* 
 * the maximum length of a string representing a 32-bit number in base 8 
 * plus 5 to accomodate the decimal point and 4 digits after the decimal 
 * point 
 */
#define OUTMAX      ((32 + 2) / 3) + 5

static const Char digtohex[] = "0123456789abcdef";

/*
 *  ======== System_Module_startup ========
 */
Int System_Module_startup(Int stat)
{
    atexit(System_rtsExit);
    return (Startup_DONE);
}

/*
 *  ======== System_abort ========
 */
Void System_abort(String str)
{
    Gate_enterSystem();

    System_SupportProxy_abort(str);

    abort();
}

/*
 *  ======== System_atexit ========
 */
Bool System_atexit(System_AtexitHandler handler)
{
    IArg key;
    Bool status = TRUE;
    
    key = Gate_enterSystem();

    if (module->numAtexitHandlers < System_maxAtexitHandlers) {
        module->atexitHandlers[module->numAtexitHandlers] = handler;
        module->numAtexitHandlers++;
    }
    else {
        status = FALSE;
    }

    Gate_leaveSystem(key);
    
    return (status);
}

/*
 *  ======== System_exit ========
 */
Void System_exit(Int stat)
{
    module->exitStatus = stat;

    exit(stat);
}

/* 
 * rtsExit__I is an internal entry point called by target/platform boot code.
 * Boot code is not brought into a partial-link assembly. So without this pragma,
 * whole program optimizers would otherwise optimize-out these functions.
 */
#ifdef __ti__
#pragma FUNC_EXT_CALLED(xdc_runtime_System_rtsExit__I);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
xdc_Void xdc_runtime_System_rtsExit__I(void) __attribute__ ((externally_visible));
#endif
#endif

/*
 *  ======== System_rtsExit ========
 */
Void System_rtsExit()
{
    Int i;

    Gate_enterSystem();

    for (i = module->numAtexitHandlers; i > 0; i--) {
        (module->atexitHandlers[i - 1])(module->exitStatus);
    }
    System_SupportProxy_exit(module->exitStatus);
}

/*
 *  ======== System_flush ========
 */
Void System_flush()
{
    System_SupportProxy_flush();
}


/*
 *  ======== System_putch ========
 */
Void System_putch(Char ch)
{
    if (System_SupportProxy_ready()) {
        System_SupportProxy_putch(ch);
    }
}

/*
 *  ======== System_aprintf_va ========
 */
Int System_aprintf_va(String fmt, VaList va)
{
    return (System_avprintf(fmt, va));
}

/*
 *  ======== System_avprintf ========
 */
Int System_avprintf(String fmt, VaList va)
{
    return (System_SupportProxy_ready() ? System_doPrint(NULL, fmt, va, TRUE) : -1);
}

/*
 *  ======== System_asprintf_va ========
 */
Int System_asprintf_va(Char buf[], String fmt, VaList va)
{
    return (System_avsprintf(buf, fmt, va));
}

/*
 *  ======== System_avsprintf ========
 */
Int System_avsprintf(Char buf[], String fmt, VaList va)
{
    return (System_doPrint(buf, fmt, va, TRUE));
}

/*
 *  ======== System_printf_va ========
 */
Int System_printf_va(String fmt, VaList va)
{
    return (System_vprintf(fmt, va));
}

/*
 *  ======== System_vprintf ========
 */
Int System_vprintf(String fmt, VaList va)
{
    return (System_SupportProxy_ready()
        ? System_doPrint(NULL, fmt, va, FALSE) : -1);
}

/*
 *  ======== System_sprintf_va ========
 */
Int System_sprintf_va(Char buf[], String fmt, VaList va)
{
    return (System_vsprintf(buf, fmt, va));
}

/*
 *  ======== System_vsprintf ========
 */
Int System_vsprintf(Char buf[], String fmt, VaList va)
{
    return (System_doPrint(buf, fmt, va, FALSE));
}

/*
 *  ======== System_doPrint ========
 *  Internal function
 *
 *  If buf == NULL, characters are sent to System_SupportProxy_putch();
 *  otherwise, they are written into buf. The return value contains the number
 *  of characters printed.
 */
Int System_doPrint(Char *buf, String fmt, VaList va, Bool aFlag)
{
    /* temp vars */
    Int     base;
    Char    c;
    Int     res;
    Char    outbuf[OUTMAX];
   
    /* vars passed to System_extendFxn. Also keep track in while loop */
    struct System_ParseData parse;

    parse.aFlag = aFlag;

    res = 0;

    if (fmt == (Char *)NULL) {
        return (res);
    }

    while ((c = *fmt++) != '\0') {
        if (c != '%') {
            System_putchar(&buf, c);
            res++;
        }
        else {
            c = *fmt++;
            /* check for - flag (pad on right) */
            if (c == '-') {
                parse.lJust = TRUE;
                c = *fmt++;
            }
            else {
                parse.lJust = FALSE;
            }
            /* check for leading 0 pad */
            if (c == '0') {
                parse.zpad = 1;
                c = *fmt++;
            }
            else {
                parse.zpad = 0;
            }

            /* allow optional field width/precision specification */
            parse.width = 0;
            parse.precis = -1;

            /* note: dont use isdigit (very large for C30) */
            if (c == '*') {
                parse.width = parse.aFlag
                    ? (int)va_arg(va, IArg) : (int)va_arg(va, int);
                c = *fmt++;
                if (parse.width < 0) {
                    parse.lJust = TRUE;
                    parse.width = -parse.width;
                }
            }
            else {
                while (c >= '0' && c <= '9') {
                    parse.width = parse.width * 10 + c - '0';
                    c = *fmt++;
                }
            }

            /* allow optional field precision specification */
            if (c == '.') {
                parse.precis = 0;
                c = *fmt++;
                if (c == '*') {
                    parse.precis = parse.aFlag ? (int)va_arg(va, IArg) :
                                     (int)va_arg(va, int);
                    if (parse.precis < 0) {
                        parse.precis = 0;
                    }
                    
                    c = *fmt++;
                }
                else {
                    while (c >= '0' && c <= '9') {
                        parse.precis = parse.precis * 10 + c - '0';
                        c = *fmt++;
                    }
                }
            }

            /* setup for leading zero padding */
            if (parse.zpad) {
                parse.zpad = parse.width;
            }

            if (parse.precis > parse.zpad) {
                parse.zpad = parse.precis;
            }

            /* check for presence of l flag (e.g., %ld) */
            if (c == 'l' || c == 'L') {
                parse.lFlag = TRUE;
                c = *fmt++;
            }
            else {
                parse.lFlag = FALSE;
            }

            parse.ptr = outbuf;
            parse.end = outbuf + OUTMAX;
            parse.len = 0;

            if (c == 'd' || c == 'i') {
                /* signed decimal */
                Int32 val =
                    parse.aFlag ? (Int32)va_arg(va, IArg) :
                    parse.lFlag ? (Int32)va_arg(va, long int) :
                    (Int32)va_arg(va, int);
                parse.ptr = System_formatNum(parse.end, val, parse.zpad, -10);
                parse.len = parse.end - parse.ptr;
            }
            /* use comma operator to optimize code generation! */
            else if (((base = 10), (c == 'u')) ||       /* unsigned decimal */
                     ((base = 16), (c == 'x')) ||       /* unsigned hex */
                     ((base = 8),  (c == 'o'))) {       /* unsigned octal */

                UInt32 val =
                    parse.aFlag ? (UInt32)va_arg(va, IArg) :
                    parse.lFlag ? (UInt32)va_arg(va, unsigned long) :
                    (UInt32)va_arg(va, unsigned);
                parse.ptr = System_formatNum(parse.end, val, parse.zpad, base);
                parse.len = parse.end - parse.ptr;
            }
            else if ((base = 16), (c == 'p')) {
                parse.zpad = 8;                       /* for 32 bit pointer */
                parse.ptr = System_formatNum(
                    parse.end,
                    parse.aFlag
                        ? (UInt32)va_arg(va, IArg) : (UInt32)(UArg)va_arg(va, Ptr),
                    parse.zpad, base);
                *(--parse.ptr) = '@';
                parse.len = parse.end - parse.ptr;
            }
            else if (c == 'c') {
                /* character */
                *parse.ptr = parse.aFlag
                    ? (Char)va_arg(va, IArg) : (Char)va_arg(va, int);
                parse.len = 1;
            }
            else if (c == 's') {
                /* string */
                parse.ptr = parse.aFlag ? (String)iargToPtr(va_arg(va, IArg)) :
                              (String)va_arg(va, void *);

                /* substitute (null) for NULL pointer */
                if (parse.ptr == (char *)NULL) {
                    parse.ptr = "(null)";
                }
                parse.len = strlen(parse.ptr);
                if (parse.precis != -1 && parse.precis < parse.len) {
                    parse.len = parse.precis;
                }
            }
            else {
	        fmt--;
	        res += System_extendFxn(&buf, &fmt, &va, &parse); 
            }

            /* compute number of characters left in field */
            parse.width -= parse.len;

            if (!parse.lJust) {
                /* pad with blanks on left */
                while (--parse.width >= 0) {
                    System_putchar(&buf, ' ');
                    res++;
                }
            }

            /* output number, character or string */
            while (parse.len--) {
                System_putchar(&buf, *parse.ptr++);
                res++;
            }
            /* pad with blanks on right */
            if (parse.lJust) {
                while (--parse.width >= 0) {
                    System_putchar(&buf, ' ');
                    res++;
                }
            }
        } /* if */
    } /* while */

    if (buf) {
        *buf = '\0';
    }

    return (res);
}

/*
 *  ======== System_formatNum ========
 *  Internal function
 *
 *  Format unsigned long number in specified base, returning pointer to
 *  converted output.
 *
 *  Note: ptr points PAST end of the buffer, and is decremented as digits
 *  are converted from right to left!
 *
 *  Note: base is negative if n is signed else n unsigned!
 *
 */
Char *System_formatNum(Char *ptr, UInt32 un, Int zpad, Int base)
{
    Int i = 0;
    Char sign = 0;

    UInt32 n;
    n = un;

    if (base < 0) {
        /* handle signed long case */
        base = -base;
        if ((Int32)n < 0) {
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
    return (ptr);
}

/*
 *  ======== System_putchar ========
 *  Internal function
 *
 *  Write character ch to the buffer and, if the buffer pointer is
 *  non-NULL, update the buffer pointer.
 */
Void System_putchar(Char **bufp, Char c)
{
    /*
     *  If the buffer is non-NULL, use it, otherwise call the
     *  proxy's putch function (if it is ready).
     */
    if (*(bufp)) {
        (*(*(bufp))++ = (c));
        return;
    }

    if (System_SupportProxy_ready()) {
        System_SupportProxy_putch(c);
    }
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

