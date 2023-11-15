
//
//    This file is part of Dire Wolf, an amateur radio packet TNC.
//
//    Copyright (C) 2011, 2012, 2013, 2014, 2019  John Langner, WB2OSZ
//    Copyright (C) 2023 Henrik Andersson <henrik.4e@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//


/*-------------------------------------------------------------------
 *
 * Name:        textcolor.c
 *
 * Purpose:     Originally this would only set color of text
 *	 	and we used printf everywhere.
 *		Now we also have a printf replacement that can
 *		be used to redirect all output to the desired place.
 *		This opens the door to using ncurses, a GUI, or
 *		running as a daemon.
 *
 * Description:	For Linux and Cygwin use the ANSI escape sequences.
 *		In earlier versions of Windows, the cmd window and ANSI.SYS
 *		could interpret this but it doesn't seem to be available
 *		anymore so we use a different interface.
 *
 * Reference:
 *		http://en.wikipedia.org/wiki/ANSI_escape_code
 *
 *
 */

#include "direwolf.h"		// Should be first.  includes windows.h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "textcolor.h"

#define MAX_THEMES 1
static const char *_theme[MAX_THEMES][6] = {
    // Standard Terminal ANSI colors
    { "\e[0m", "\e[31m", "\e[32m", "\e[35m", "\e[35m", "\e[90m" },
};

/*
 * g_enable_color:
 *	 0 = disable text colors.
 *	 1 = Standard Terminal ANSI colors
 */
static int g_enable_color = 1;
static int g_theme = 0;

void text_color_init (int enable_color)
{
    g_enable_color = enable_color != 0 ? 1 : 0;

    if (g_enable_color == 0) {
        return;
    }

    g_theme = enable_color - 1;       

#if __WIN32__
    /*
     * Setup VT100 processing for windows console to enable ANSI colors and other codes
     */
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == NULL) {
        fprintf(stderr, "WARNING - Failed to get console handle for enable of ANSI\n");
        return;
    }
    
    SetConsoleMode(h, ENABLE_PROCESSED_OUTPUT|ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}


void text_color_set ( enum dw_color_e c )
{
	if (g_enable_color == 0) {
	  return;
	}

    printf("%s", _theme[g_theme][c]);
}


/*-------------------------------------------------------------------
 *
 * Name:        dw_printf 
 *
 * Purpose:     printf replacement that allows us to send all text
 *	            output to stdout or other desired destination.
 *
 * Inputs:	fmt	- C language format.
 *		...	- Additional arguments, just like printf.
 *
 *
 * Returns:	Number of characters in result.
 *
 *
 *--------------------------------------------------------------------*/

// TODO: replace all printf, look for stderr, perror
// TODO:   $ grep printf *.c | grep -v dw_printf | grep -v fprintf | gawk '{ print $1 }' |  sort -u

int dw_printf (const char *fmt, ...) 
{
    int ret;
    va_list argptr;
    va_start(argptr, fmt);
    ret = vfprintf(stdout, fmt, argptr);
    va_end(argptr);
    return ret;
}



#if TESTC
main () 
{
	printf ("Initial condition\n");
	text_color_init (1);
	printf ("After text_color_init\n");
	text_color_set(DW_COLOR_INFO); 		printf ("Info\n");
	text_color_set(DW_COLOR_ERROR); 	printf ("Error\n");
	text_color_set(DW_COLOR_REC); 		printf ("Rec\n");
	text_color_set(DW_COLOR_DECODED); 	printf ("Decoded\n");
	text_color_set(DW_COLOR_XMIT); 		printf ("Xmit\n");
	text_color_set(DW_COLOR_DEBUG); 	printf ("Debug\n");
}
#endif
	
/* end textcolor.c */
