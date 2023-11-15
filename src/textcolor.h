
/*-------------------------------------------------------------------
 *
 * Name:        textcolor.h
 *
 * Purpose:     Set color of text.
 *
 *--------------------------------------------------------------------*/


#ifndef TEXTCOLOR_H
#define TEXTCOLOR_H 1
#include <stdarg.h>
enum dw_color_e {
    DW_COLOR_INFO = 0, 	/* foreground */
    DW_COLOR_ERROR,	 	/* red */
    DW_COLOR_REC,		/* green */
    DW_COLOR_DECODED,	/* blue */
    DW_COLOR_XMIT,		/* magenta */
    DW_COLOR_DEBUG		/* dark_white */
};

typedef enum dw_color_e dw_color_t;

	
void text_color_init (int enable_color);
void text_color_set (dw_color_t c);
void text_color_term (void);


/* Degree symbol. */

#if __WIN32__

//#define CH_DEGREE "\xc2\xb0"	/* UTF-8. */

#define CH_DEGREE " "


#else

/* Maybe we could change this based on LANG environment variable. */

//#define CH_DEGREE "\xc2\xb0"	/* UTF-8. */

#define CH_DEGREE " "

#endif



int dw_printf(const char *fmt, ...);
int dw_fprintf(FILE *stream, const char *fmt, ...);

#endif
