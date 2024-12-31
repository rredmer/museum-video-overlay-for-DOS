//---------------------------------------------------------------------------
//
//  Module.....: VSET.C
//
//  Description: Procedure to genlock live NTSC video source using New Media
//               Graphics Super VideoWindows board revision 1.4a.
//
//  Author.....: Ronald D. Redmer
//
//  Parameters.: x, y, width, height - dimensions of live video window.
//
//  Notes......: This program assumes the video is currently in 640x480
//               graphics mode (i.e. TO480 was run prior to execution).
//
//  Compiler...: This module was compiled and linked with the following tools:
//                 Microsoft (R) Optimizing C/C++ Compiler  Version 8.00c
//                 Microsoft (R) Segmented Executable Linker  Version 5.60
//
//               The compile and link batch script should be:
//
//                 SET INCLUDE=J:\DEVTOOLS\MSC800\INCLUDE
//                 SET LIB=J:\DEVTOOLS\MSC800\LIB
//                 CL /c /W4 /AL /Zi /Od /Gs vset.c
//                 LINK /CO /STACK:8192 vset.obj,,,lvide lsvw;
//
//  History....:
//               DATE     ENG VERS DESCRIPTION
//               ------------------------------------------------------------
//               03/30/94 RDR 1.00 Designed & Programmed using VSHOW as ref.
//                                 Tested first release @ 2:50pm
//
//---------------------------------------------------------------------------

#define SOURCE "Source1"	// Name of video source saved in video
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys\types.h>
#include <sys\timeb.h>
#include "avdos.h"

//---- Funtion Prototypes ---------------------------------------------------
void CIL_CALLBACK myerr(int , AVfixString, int, AVfixString);
void main(int argcnt, char **args);

/*---------------------------------------------------------------------------
**
**  Function...: main
**					
**  Description: Initialize the SVW board and create live video window.
**
*/
void main(int argcnt, char **args)
{
int result=0;					// Generic function result
VIDEO vid;						// SVW video input struct
Winport wp;						// SVW window struct
Winport nwp;					// SVW window struct

//---- Validate parameters --------------------------------------------------
if (argcnt < 5)
	{
	printf("%c", (char) 7);
	printf("\n\nUSAGE:\n\n");
	printf("   VSET <left> <top> <right> <bottom>\n\n\n");
	printf("   The most common parameters are:\n\n");
	printf("    VSET 155 10 640 400\n\n");
	exit(0);
	}

//---- Setup SVW Video Source -----------------------------------------------
AVinstallErrHandler(myerr);
if (AVinit("video.ini")) 
	{
	fprintf(stderr, "Unable to initialize video system.\n");
	exit(1);
	}
vid = AVcreate(SOURCE);
if (!vid) 
	{
	fprintf(stderr, "Unable to open %s.\n", SOURCE);
	AVend();
	exit(1);
	}

//---- Set window size to passed parameters ---------------------------------
wp.x      = (short) atoi( *(args+1) );
wp.y      = (short) atoi( *(args+2) );
wp.width  = (short) atoi( *(args+3) );
wp.height = (short) atoi( *(args+4) );

//---- Configure live video window and exit ---------------------------------
AVconfigure(vid, &wp, &nwp, 0);
result = AVcolorKey(vid, KEY_COLOR, 0);
AVenable(vid);
result = AVfreeze(vid, 0);
exit(0);
}
/*---------------------------------------------------------------------------
**
**  Function...: myerr
**					
**  Description: User defined error handler for low-level SVW functions.
**
*/
void CIL_CALLBACK myerr(int lev, AVfixString routine, int AVerrno, AVfixString reason)
{
if (lev == INFO) printf("** AV Information: ");
if (lev == FATAL) printf("** Fatal AV Error: ");
if (lev == WARN) printf("** AV Warning: ");
printf("%s.\n    %s\n", AVerrorString(AVerrno), reason);
if (lev == FATAL)               // Unrecoverable error
	exit(EXIT_FAILURE);
}

