/************************************************************************
 *									*
 * Copyright (C) 1990 New Media Graphics Corp.				*
 *									*
 * Module:	avsys.h							*
 * Description:	Local definitions for the AVSYS layer			*
 *									*
 *		      M S - D O S   E D I T I O N			*
 *									*
 ***********************************************************************/

#ifndef AVSYS_LH
#define AVSYS_LH

/* $Id: avsys.h 8.4 92/11/23 11:25:36 jim_b Exp $ */


/*
 * Define the strings for graphics mode configuration
 */
#define INI_GRAPHICS_MODE   "Mode"
#define INI_WALIGN_LEFT     "Wleft"
#define INI_WALIGN_TOP      "Wtop"
#define INI_VALIGN_LEFT     "Vleft"
#define INI_VALIGN_RIGHT    "Vright"
#define INI_VALIGN_TOP      "Vtop"
#define INI_VSTART          "Vstart"
#define INI_SHIFT           "Shift"
#define INI_GDELAY          "Gdelay"
#define INI_RED		    "Red"
#define INI_GREEN	    "Green"
#define INI_BLUE	    "Blue"

typedef void _huge *AVbitmapPtr;
typedef int AVfile;
typedef int  *AVfilePtr;

/*
 * Use this to declare error handlers.  For example:
 * void CIL_CALLBACK myerr(...)
 */
#define CIL_CALLBACK _cdecl

/*
 * Macros for finding out useful things about a video window
 * These should never be used as lvalues.  The macros can be
 * left out and function substituted instead by defining
 * IGNORE_GET_MACROS in your source code.
 */

#ifndef IGNORE_GET_MACROS

#define AVgetX1(v)	((v)->vp.x1)
#define AVgetY1(v)	((v)->vp.y1)
#define AVgetX3(v)	((v)->vp.x3)
#define AVgetY3(v)	((v)->vp.y3)
#define AVgetVidport(v)	((v)->vp)
#define	AVgetVidFrm	((v)->vfrm)

#define AVgetWidth(v)	((v)->wp.width)
#define AVgetHeight(v)	((v)->wp.height)
#define AVgetX(v)	((v)->wp.x)
#define AVgetY(v)	((v)->wp.y)
#define AVgetWinport(v)	((v)->wp)
#define AVgetWinFrm(v)	((v)->wfrm)

#define AVgetFitMode(v)	((v)->fit_mode)
#define AVisFrozen(v)	((v)->frozen)
#define AVisEnabled(v)	((v)->enabled)
#define AVgetVolume(v)	((v)->volume)
#define AVgetBalance(v)	((v)->balance)
#define AVgetBass(v)	((v)->bass)
#define AVgetTreble(v)	((v)->treble)
#define	AVisMuted(v)	((v)->audiomute)
#define AVisMapped(v)	((v)->unitbind != (UnitBindingParamsPtr)NULL)
#define	AVcanControl(v)	((v)->srcbind != (SourceBindingParamsPtr)NULL)
#define AVgetVideoSignal(v) ((v)->sigtype)

#endif	/* IGNORE_GET_MACROS */


#endif	/* AVSYS_LH */
/************************************************************************
 *									*
 * Copyright (C) 1991 New Media Graphics Corp.				*
 *									*
 * Module:	av.h							*
 * Description:	Include file for AV Common Interface Library (CIL)	*
 *									*
 ************************************************************************/

/* $Id: av.h 8.23 92/12/15 11:18:05 ben_t Exp $ */

#ifndef AV_H
#define AV_H


/*
 * Maximum length of a source name
 */
#define SRCNAME_LEN 16

/*
 * These definitions allow a data hiding/inheritance scheme
 * These are placeholders only and should never be declared in user programs.
 */
typedef struct gendevstr  * DeviceControlParamsPtr;
typedef struct genwinstr  * UnitBindingParamsPtr;
typedef struct gensrcstr  * SourceBindingParamsPtr;
typedef struct genosstr  * OSBLK;

typedef short AVgcoord;		/* A position or dimension in graphic */
				/* pixel coordinates */
typedef short AVvcoord;		/* A position or dimension in video */
				/* pixel coordinates */

/*
 * This structure defines what a vidport looks like.  It
 * is used by AVdefineVidport.
 */
struct vp_str {
	AVvcoord x1;
	AVvcoord y1;
	AVvcoord x3;
	AVvcoord y3;
	};
typedef struct vp_str Vidport;
typedef struct vp_str  *VidportPtr;

struct wp_str {
	AVgcoord x;
	AVgcoord y;
	AVgcoord width;
	AVgcoord height;
	};
typedef struct wp_str Winport;
typedef struct wp_str  *WinportPtr;

struct disp_str {
	unsigned short bright;
	unsigned short sat;
	unsigned short contrast;
	unsigned short hue;
	unsigned short sharp;
	unsigned short flags;		/* Black and white flag */
	};
typedef struct disp_str DisplayAttr;
typedef struct disp_str  *DisplayAttrPtr;

typedef char const  * AVfixString;	/* Constant string */
typedef char  * AVvarString;		/* String will be changed string */

typedef void (CIL_CALLBACK *ErrorHandler)(int level, AVfixString func, int av_errno, AVfixString reason);

/*
 * vwbuf is a generic structure designed to hold information
 * that would apply for any hardware box.  UnitBindingParamsPtr gets linked
 * into it from a level down and contains device dependent
 * information about this video window.
 *
 * Do NOT try to directly reference vwbuf_str.  Use the get functions.
 *   **  It WILL change!! **
 */

struct vwbuf_str {
	/* Hardware info */
	unsigned short unit_id;		/* Index of video unit */
	unsigned short con_id;		/* Index of connection */
	unsigned short src_id;		/* Index of source */
	unsigned short video_inp;	/* Current video inp */
	unsigned short audio_inp;	/* Current audio inp */
	
	/* Input */
	Vidport vp;		/* Vidport in use */
	Vidport vfrm;		/* Frame for vidport */
	/* Output */
	Winport wp;		/* Winport in use */
	Winport wfrm;		/* Winport requested */
	short fit_mode;		/* How video is fitted to windows */
	char frozen;		/* flag if this window is a still */
	char enabled;		/* If MMO is on (different from still)*/
	char faded;		/* flag if window video is faded */
	char sigtype;
	/* Audio */
	short volume;		/* 0 to 100 percent */
	short treble;		/* 0 to 100 */
	short bass;		/* 0 to 100 */
	short balance;		/* -100 to 100 */
	char audiofaded;	/* If the audio is faded */
	char audiomute;		/* TRUE If mute is turned on */
	DisplayAttr disp;	/* AVsetDisplay stuff */
	/* Video handle interface block */
	/* Points to information about this specific video handle */
	UnitBindingParamsPtr unitbind;		/* Inheritance link for device dependent */
				/* window information.  This is NULL if */
				/* we are not mapped to hardware */
	SourceBindingParamsPtr srcbind;		/* Inheritance link for device dependent */
				/* source information.  This is NULL if */
				/* we are not mapped to hardware */
	short key_mode;		/* Current color keying mode KEY_ below */
	short key_value;	/*   Parameter for color key mode */
	};
typedef struct vwbuf_str  * VIDEO;

/*
 * Describe a unit configuration
 */
struct uconf_str {
	short unit_type;	/* Type of video unit, from UNIT_ below */
	short total_vins;	/* Video inputs */
	short total_ains;	/* Audio inputs */
	short window_mode;	/* Reserved */
	short locks;		/* Number of open handles */
	short key_mode;		/* Current color keying mode KEY_ below */
	short key_value;	/*   Parameter for color key mode */
	unsigned char active;
	};
typedef struct uconf_str UnitConfig;
typedef struct uconf_str  * UnitConfigPtr;

/*
 * Describe a source configuration
 */
struct sconf_str {
	char srctype;		/* See SRC_* below */
	char sigtype;		/* See SIG_* below */
	unsigned char active;	/* TRUE or FALSE */
	};
typedef struct sconf_str SrcConfig;
typedef struct sconf_str  * SrcConfigPtr;

/*
 * Describe a connection.  Both of these are numbered 1..n.
 * These are logical numbers, not physical, so the private bus
 * would simply be considered some ordinally numbered input.
 */
struct cconf_str {
	unsigned short video_input;
	unsigned short audio_input;
	};
typedef struct cconf_str ConConfig;
typedef struct cconf_str  * ConConfigPtr;


/*
 * Macros will never be used under Windows because it is possible that
 * the video structure will change within the DLL, but the calling
 * application would not know about it.  Backwards compatibility.
 */
#ifdef IGNORE_GET_MACROS
AVvcoord  _cdecl AVgetX1(VIDEO vid);
AVvcoord  _cdecl AVgetY1(VIDEO vid);
AVvcoord  _cdecl AVgetX3(VIDEO vid);
AVvcoord  _cdecl AVgetY3(VIDEO vid);
Vidport  _cdecl AVgetVidport(VIDEO vid);
Vidport  _cdecl AVgetVidFrame(VIDEO vid);
Vidport  _cdecl AVgetMaxVidport(VIDEO vid);
AVgcoord  _cdecl AVgetWidth(VIDEO vid);
AVgcoord  _cdecl AVgetHeight(VIDEO vid);
AVgcoord  _cdecl AVgetX(VIDEO vid);
AVgcoord  _cdecl AVgetY(VIDEO vid);
Winport  _cdecl AVgetWinport(VIDEO vid);
Winport  _cdecl AVgetWinFrame(VIDEO vid);
int  _cdecl AVgetFitMode(VIDEO vid);
int  _cdecl AVisFrozen(VIDEO vid);
int  _cdecl AVisEnabled(VIDEO vid);
int  _cdecl AVgetVolume(VIDEO vid);
int  _cdecl AVgetBalance(VIDEO vid);
int  _cdecl AVgetBass(VIDEO vid);
int  _cdecl AVgetTreble(VIDEO vid);
int  _cdecl AVisMuted(VIDEO vid);
int  _cdecl AVisMapped(VIDEO vid);
int  _cdecl AVcanControl(VIDEO vid);
int  _cdecl AVgetVideoSignal(VIDEO vid);
#endif	/* IGNORE_GET_MACROS */

/*
 * Values used by AVerrhnd and passed 
 * to the user installed error handler
 */
#define FATAL	1
#define WARN	2
#define INFO	3

/* Misc defines */
#define	AV_UNDEF	-30000	/* use big value to allow for Windows neg. coord. */
#define AV_FILLIN	-2

/* Error returns from video module */
#define AV_OK		0	/* Everything hunky dory */
#define	AV_FAIL		1
#define	AV_NOMEM	2	/* No memory left */
#define	AV_SYSERR	3	/* The system returned an error */
#define	AV_INTERNAL	4	/* Internal error */
#define	AV_NULLVID	5	/* Null video handle passed */
#define	AV_ILLARG	6	/* Illegal argument */
#define	AV_RANGE	7	/* Argument out of range */
#define AV_TIMEOUT	8	/* Timeout - no response from hardware*/
#define	AV_OVERRUN	9	/* Data overrun */

#define	AV_NOTFOUND	10	/* Entry not in configuration file */
#define	AV_NOCONFIG	11	/* No configuration file */
#define	AV_NOUNITS	12	/* No Super VideoWindows found */
#define AV_BADCONFIG	13	/* Bad entry in configuration file */
#define AV_DUPNAME	14	/* Attempt to add a duplicate name */
#define	AV_BADINPUT	15	/* Illegal connection description */
#define	AV_SPLIT	16	/* Can't split audio/video across units */
#define	AV_SIGNAL	17	/* Unknown signal description */
#define AV_NOCONTROL	18	/* No control line available for device */
#define AV_INUSE	19	/* Device is active */
#define	AV_NOTSUPT	20	/* Feature not supported */
#define	AV_NOTACTIVE	21	/* Device requested is not active */
#define	AV_NOCONNECT	22	/* Device not connected */

#define	AV_BADLOC	23	/* Attempt to move to bad location */
#define	AV_BADSIZE	24	/* Attempt to create window with bad size */
#define AV_BADFIT	25	/* Window won't fit on screen */
#define AV_WMODE	26	/* Can't in this windowing mode */
#define AV_ALMOST	27	/* The winport values were adjusted */

#define	AV_NOTREADY	28	/* Device not ready */
#define	AV_DEVICE	29	/* Wrong device type for operation */

#define AV_BADFORMAT	30      /* Format not allowed for this operation */
#define AV_BADFILENAME	31      /* Filename was not allowed */
#define AV_BADREGION	32      /* Error in framegrabbing region */

#define AV_NOTCOMPLETE  33      /* Used in framegrabbing.
                                   Operation went fine but is NOT
				   finished yet. It should be called 
				   again */

#define AV_NOFBACCESS	34	/* Cannot access framebuffer (Not receiving vertical sync) */
#define	AV_BADIOADDR	35	/* Bad SVW I/O address */
#define	AV_BADMEMADDR	36	/* Bad framebuffer address */


/* Masks for AVconfigure */
#define	AV_QUERY	1

/* Return values from AVgrabToBand and AVputFromBitmap */
#define XFR_CMPLT	0xa0
#define XFR_NCMPLT	0xa1
#define XFR_START	0xa2

/*
 * Useful Audio constants
 * These constants are documented to be these ranges and will not change.
 */
#define	AV_MINVOL	0
#define	AV_MAXVOL	100
#define	AV_MINBAL	-100
#define	AV_MAXBAL	100
#define	AV_MINBASS	0
#define	AV_MAXBASS	100
#define	AV_MINTREBLE	0
#define	AV_MAXTREBLE	100

#define	AV_VOLUME	1
#define	AV_VOLUME_UP	2
#define	AV_VOLUME_DOWN	3
#define	AV_VOLUME_MUTE	4
#define	AV_BALANCE	5
#define	AV_BALANCE_LEFT	6
#define	AV_BALANCE_RIGHT	7
#define	AV_BASS		8
#define	AV_BASS_MORE	9
#define	AV_BASS_LESS	10
#define	AV_TREBLE	11
#define	AV_TREBLE_MORE	12
#define	AV_TREBLE_LESS	13
#define AUDIO_USRDEF	0x1000		/* Load user defined default */

/* Flags for DisplayAttr.flags */
#define DISP_FLAG_BNW		0x0001
#define DISP_FLAG_MOTION_FILTER	0x0002	// Motion Filter
#define DISP_FLAG_X_ZOOM	0x0004	// These two values do not mean,
					// "Is the video currently zoomed?"
#define DISP_FLAG_Y_ZOOM	0x0008	//   They really mean, "Can we use
					//   zoom to satisfy a request?"
#define DISP_FLAG_RECORDING	0x0010	// If system is in record mode (SMC)
					//   Set by AVstandbyDigitalRecord

/* Parameters for AVsetDisplay and AVgetDisplay */
#define	DISP_HUE	1
#define	DISP_SATURATION	2
#define	DISP_BRIGHTNESS	3
#define	DISP_CONTRAST	4
#define	DISP_SHARPNESS	5
#define DISP_MOTION_FILTER	6
#define	DISP_BNW	7
#define	DISP_RED	8		/* Internal use only */
#define	DISP_GREEN	9		/* Internal use only */
#define	DISP_BLUE	10		/* Internal use only */
#define DISP_ALLOW_X_ZOOM	11
#define DISP_ALLOW_Y_ZOOM	12
#define DISP_USRDEF	0x1000		/* Load user defined default */
#define DISP_SYSDEF	0x2000		/* Load system defined default */

#define	DISP_MIN_HUE	0
#define	DISP_MAX_HUE	100
#define	DISP_MIN_SAT	0
#define	DISP_MAX_SAT	100
#define	DISP_MIN_BRIGHT	0
#define	DISP_MAX_BRIGHT	100
#define	DISP_MIN_CONT	0
#define	DISP_MAX_CONT	100
#define	DISP_MIN_SHARP	0
#define	DISP_MAX_SHARP	100

/* Types of sources */
#define	SRC_UNKNOWN	'U'
#define	SRC_LASERDISC	'L'
#define	SRC_TUNER	'T'		/* TV Tuner */
#define	SRC_VCR		'V'
#define	SRC_CAMERA	'C'
#define SRC_TUNER_PLUS	'I'             /* Jr + Tuner (inboard) */
#define SRC_MOTION_COMPRESS 'O'         /* Super Motion Compression */

/* Types of video units */
#define UNIT_HIRES	'H'	/* Workstation product	*/
#define UNIT_SVW	'S'	/* Super VideoWindows	*/
#define UNIT_SVW_SL	'J'	/* Super VideoWindows SL */
#define UNIT_SVW_TV	'P'	/* TV VideoWindows (on one card) */
#define UNIT_SVW_CM	'C'	/* Super VideoWindows w/Compression */
#define UNIT_SVW_MCA	'M'	/* Super VideoWindows Microchannel */

/* Video source types */
#define SIG_NONE	0
#define SIG_AUTO	'a'		/* Automatically detect */
#define SIG_NTSC	'n'
#define SIG_PAL		'p'
#define SIG_RGB		'r'		/* Not supported by SVW */
#define SIG_SVHS_NTSC 	'v'		
#define SIG_SVHS_PAL 	'l'		
#define SIG_DIGITAL	'd'		/* Private Bus */

/* Fade flag */
#define	FADE_IN		1
#define	FADE_OUT	0

/* Fade masks -- Not supported in this release */
#define FADE_VIDEO	1
#define FADE_AUDIO	2
#define FADE_SCREEN	4		

/* Various modes for AVfitMode */
#define FIT_STRETCH	0x10	/* 16 decimal */
#define	FIT_COMPRESS	0x20	/* 32 decimal */
#define	FIT_CROP	0x40	/* 64 decimal - not supported */
#define	FIT_CENTER	0x21	/* 33 decimal */
#define	FIT_GRAB	0x11	/* 17 decimal */
#define FIT_ONETOONE	0x12	/* 18 decimal */

/* Color key modes */
#define	KEY_NONE	0	/* Keying off.  Always show video */
#define	KEY_COLOR	1	/* Single color */
#define	KEY_MASK	2	/* Set of colors-not implemented yet */
#define	KEY_LOGICAL_PALETTE	3
#define	KEY_PHYSICAL_PALETTE	KEY_COLOR
#define	KEY_NEVER	4	/* Do not key on any color.
				   This enable you to have a window
				   active in the framebuffer without
				   actually showing it on the screen.
				 */
				   

/* Op codes for AVcvtRGBtoKeyColor */
/*
 * BGR888 or COLORREF are intended to accept a Windows COLORREF structure
 */
#define	CVT_BGR888		1
#define	CVT_COLORREF		1
/*
 * BGR666 is intended to accept the Microsoft C6 constants such
 * as _RED and _GREEN that appear in graph.h.
 */
#define	CVT_BGR666		2

/*
 * Flags for AVgetDevices.  The active and inactive modifiers
 * are mutually exclusive.  Asking for both of them gives you nothing.
 */
#define	GET_SOURCES	0x01
#define	GET_UNITS	0x02
#define	GET_ALL		(GET_SOURCES | GET_UNITS)
#define	GET_ONLYINACTIVE	0x10
#define	GET_ONLYACTIVE	0x20
#define	AVgetSources(index,buf,n) AVgetDevices(GET_SOURCES|GET_ONLYACTIVE,index,buf,n)

/*
 * Various definitions for how to parse video.ini
 * These are case insensitive
 */
#define INI_VIDEO_CONNECTION "VideoOut"
#define INI_AUDIO_CONNECTION "AudioOut"
#define	INI_ACTIVE_SOURCE "Active"
#define	INI_CONTROL_LINE "Control"
#define	INI_CONTROL_SETTINGS "CtrlCfg"
#define INI_SIGNAL_TYPE "Signal"
#define INI_SOURCES "Sources"
#define	INI_DRIVER_NAME "DLL"		/* For Microsoft Windows 3.0 */
#define INI_UNITS "VideoUnits"
#define INI_IOADDR "IOaddr"		/* For SVW, Tuner, SMC */
#define	INI_MEMADDR "MemAddr"		/* For SVW */
#define	INI_PASSTHRU "PassThru"		/* For SVW */
#define	INI_INTERRUPT	"Interrupt"		/* For SVW */
#define INI_SYNC	"AlignSync"
#define INI_CONTRAST    "Contrast"
#define INI_HUE         "Hue"
#define INI_SAT         "Saturation"
#define INI_BRIGHT      "Brightness"
#define INI_SHARP       "Sharpness"
#define INI_VOLUME  "Volume"
#define INI_BASS    "Bass"
#define INI_TREBLE  "Treble"
#define INI_BALANCE "Balance"
#define INI_SOURCE_DEFAULT "DefaultSource"
#define INI_SOURCE_NONE    ""

#define DEV_LASERDISC "Laserdisc"
#define DEV_VCR "VCR"
#define DEV_TUNER "Tuner"
#define DEV_TUNER_PLUS "TunerPlus"
#define DEV_CAMERA "Camera"
#define DEV_UNKNOWN "Unknown"
#define DEV_SVW "SVW"
#define DEV_HIRES "Hires"
#define DEV_MOTION_COMPRESS "MotionCompress"

/*
 * Laserdisc stuff
 */
#define	PLAY_FORWARD	0
#define	PLAY_REVERSE	1

#define	AUDIO_NONE	0
#define	AUDIO_LEFT	1
#define	AUDIO_RIGHT	2
#define	AUDIO_BOTH	3

#define MODE_NONE	0
#define MODE_STOP	1
#define MODE_PLAY	2
#define MODE_PAUSE	3
#define MODE_RECORD	4

#define PLAYER_AUDIO		1
#define	PLAYER_DIRECTION	2
#define	PLAYER_SPEED		3
#define	PLAYER_FRAME		4	// Get only
#define	PLAYER_DISPLAY		5	// Laserdiscs only
#define	PLAYER_MODE		6	// SMC only
#define	PLAYER_PERCENT_SPEED	7	// SMC only
#define	PLAYER_INDEX		8	// SMC only.  Set only.
#define	PLAYER_LENFRAMES	9	// SMC only

/*
 * Frame Grabbing Stuff
 */
typedef struct rect_str {
        short left;
        short top;
        short right;
        short bottom;
        } AVrect;
typedef AVrect  * AVrectPtr;

/* A pointer to actual pixel data */
typedef char _huge *AVpixelPtr;

/*************************************************************************
 *
 * Data structures describing an image currently being framegrabbed
 *
 ************************************************************************/
/* FGB format flags */
#define AV_BITMAP   1
#define AV_FILE     0
#define AV_PUT      2
#define AV_GRAB     0
#define AV_BOTTOMUP 4
#define AV_TOPDOWN  0

typedef struct imageinfo  * AVimageInfoPtr;

typedef int ( _cdecl *AVfgbFunc)(AVimageInfoPtr imageInfoPtr);
typedef int ( _cdecl *AVconvertFunc)(AVimageInfoPtr imageInfoPtr, AVpixelPtr srcPtr, AVpixelPtr destPtr);
typedef int ( _cdecl *AVrowSize)(int width);

typedef struct imageaccess
    {
    /* The developer has to give pointers to callback functions for 
       operations to be performed during a framegrab operation on there 
       format.  These functions will be called at the appropriate time 
       from the CIL framegrabbing functions with the arguments defined.  
       There might be some default access functions provided by the CIL. */


    /* Called when starting to framegrab an image.  The function  should 
       check the flags field to see whether to prepare to do  a read or write 
       to a file or bitmap.  The developer can open  any needed files, lock 
       any bitmaps, read/write any headers, and allocate any needed memory in 
       the formatData field. It can also set flags in the ImageInfo. */
    AVfgbFunc Start;  


    /* Called when finished framegrabbing an image.  The function  should 
       close any files, unlock any bitmaps, and free any memory  that was 
       allocated. */
    AVfgbFunc End;


    /* Function that outputs the actual picture data.  This function  will 
       be called when the externalBand buffer is filled with  data.  This 
       function should write the external band to a file or a bitmap as 
       appropriate. */
    AVfgbFunc Write;


    /* Function for reading in actual picture data.  This function  will 
       be called when the externalBand buffer is empty and needs  the next 
       band of data from a file or a bitmap. It should put the new data into 
       the externalBand. */
    AVfgbFunc Read;
    } AVimageAccess;
typedef AVimageAccess  *AVimageAccessPtr;


typedef struct formatinfo
    {
    /* This user should fill this in with the format that they want used 
       for the framegrab operation. */
    int formatID;	// FGB format to use.


    /* These fields will be filled in by the CIL so that the correct 
       format functions will be called by the CIL. */
    struct fgbformat  *formatInfo;	/* Holds info about specified format. */
    AVimageAccessPtr accessPtr;	/* Pointer to File or Bitmap access functions
                                   to use. */
    } AVformatInfo;

// This is a copy of the MMO structure SVWRECT2.
// If that structure changes, this should change also.
typedef struct internalrect
    {
    AVrect rect;
    AVrect reserved;
    int reserved2;
    } AVinternalRect;

typedef struct imagedescriptor
    {
    VIDEO vid;	/* handle to video image. */

    /* These fields describe the aspect ratio of the image in the 
       framebuffer. The aspectWidth/aspectHeight is the aspect ratio of 
       the image.  It is 720/480 for SVW and it is normally 640/480 for 
       VGA graphics if the image is to be corrected.*/
    int aspectWidth;
    int aspectHeight;


    AVrect graphicsRect; /* Clipping rectangle in graphics coordinates. */

    AVrect externalRect; /* Rectangle describing the size of the 
                               file/bitmap. */
    AVrect videoRect;    /* Rectangle in framebuffer to get/put pixels 
                               to/from.  (0, 0) is the top left of the 
                               visible video area.  Negative coordinates 
                               will be allowed when extended vidports are 
                               implemented. */
    AVinternalRect internalRect; /* Clipping rectangle in graphics coordinates. 
                              This structure will be updated as each band
			      is grabbed/put */

    } AVimageDescriptor;

typedef struct externaldescriptor
    {
    AVfile file;                // Pointer to an open file if needed
    AVbitmapPtr bitmap;         // Pointer to a bitmap if needed
    char  *fileName;	// Pointer to filename if needed. 
    unsigned long pixelsOffset;	/* Byte offset from the beginning of the 
                                   file/bitmap to where the pixel data 
                                   starts. */
    } AVexternalDescriptor;

typedef struct band
    {
    int startRow;   /* Starting row of the image in the buffer. */
    int width;      // Width of the image in the buffer.
    int height;     // Height of the image in the buffer
    int rowsize;    // Size in bytes of 1 row of pixels.
    long bufferSize;// Size of the actual buffer.
    long dataSize;  /* The number of bytes of data actually in the buffer.  
                       If this is negative, then ((width * rowsize) * height)
                        should be used. */
    AVpixelPtr buffer;  // Buffer holding actual pixels.
    int  continuation;  // Continuation value for the framebuffer.
    } AVband;
typedef AVband  * AVbandPtr;

typedef struct imagebuffer
    {
    AVband nativeBand;      /* Buffer of pixels in native format. */
    AVband externalBand;    /* Buffer of pixels when in the format 
                               specified by formatID. */
    } AVimageBuffer;
	
typedef struct imageinfo
    {
    AVformatInfo format;	    /* Information about the format to use 
                                       for the framegrabbing operation. */
    long flags;                     /* Holds framegrabbing options:
                                        TopDown/BottomUp image format, 
                                        File/Bitmap,
                                        Grab/Put, 			
                                        Aspect Ratio Correction?
                                    */
    short putOp;                    /* Bit operations on Put command:
                                        Default - Copy Bits
                                        Future Options: And, Or, Xor Bits 
                                    */
    AVimageDescriptor image;        // Description of image to grab/put 
    AVexternalDescriptor external;  /* Info on the source/destination of the 
                                        image. */
    AVimageBuffer buffers;	    /* Buffers to hold bands of the image 
                                       being grabbed/put. */
    void  *formatData;     	    /* Additional data needed by a specific 
                                       format in order to do any needed 
                                       conversions. */
    } AVimageInfo;

/*************************************************************************
 *
 * Data structures describing a FGB format installed in the CIL
 *
 ************************************************************************/

/* Native Format IDs */
#define AV_SVW      1

/* Supported features of a framegrab format */
#define AV_GRABBITMAP_SUPT 1
#define AV_PUTBITMAP_SUPT  2
#define AV_GRABFILE_SUPT   4
#define AV_PUTFILE_SUPT    8
#define AV_PRESCAN_SUPT    16
#define AV_APPLGLOBAL       32

typedef struct formatdescriptor
    {
    /* The developer should enter a descriptive name about the format and
       the preferred extension for the format.  They should also set all
       the flags that apply for the format. */
    char formatName[30];	/* Text string describing format. */
    char fileExtension[4];	// Filename  extension + NULL.
    int flags; /* Describes which options are supported by this format:
		* Grab to bitmaps support?
		* Put from bitmaps support?
		* Grab to files support?
		* Put from files support?
		* Prescan image needed?
		* Application Global Format?
	        */
    } AVformatDescriptor;


typedef struct formatconversion
    {
    /* This field specifies which native format these conversion routines
       support. Right now we only have SVW's YUV format.  In the future
       we may have products with a different native format. */
    int nativeFormat;	/* This should specify AV_SVW. */


    /* Function for converting pixels from SVW native format. This function
       can convert any number of pixels at a time as  long as there are still
       pixels to be converted in the native band and room to store the
       converted pixels in the external band. This function should convert 1
       row of pixels or less at a time in order to be used with AVgrabPixels(). */
    AVconvertFunc ConvertFromNative;

    /* Function for converting pixels to SVW native format. This function
       can convert any number of pixels at a time as long as there are still
       pixels to be converted in the external band and room to store the
       converted pixels in the native band.  This function should convert 1
       row of pixels or less at a time in order to be used with
       AVputPixels(). */
    AVconvertFunc ConvertToNative;

    /* This function has the responsibility for grabbing all the pixels, 
       converting them and writing them out.  The CIL will provide 
       AVgrabPixels() to be used as the default function.  The AVgrabBand() 
       and the format's ConvertFromNative() and Write() functions should be 
       called by this function. */
    AVfgbFunc GrabPixels;

    /* This function has the responsibility for reading in all the pixels, 
       converting them and putting them to the framebuffer.  The CIL will 
       provide AVputPixels() to be used as the default function.  The 
       AVputBand() and the format's ConvertToNative() and Read() functions 
       should be called by this function. */
    AVfgbFunc PutPixels;


    /* When grabbing an image, if this function is not NULL then it will 
       be called for all the pixels in the image as a first pass.  This 
       function can analyze the image before the image is converted.  For 
       example this program can do a histogram on the colors in the image 
       and create an optimized color palette for the image. */
    AVfgbFunc PrescanPixels;


    /* This function will return the number of bytes needed to hold a row 
       of pixels given the width in pixels.  This is needed by CIL functions 
       such as AVcreateBands(), AVgrabPixels(), and AVputPixels(). */
    AVrowSize RowSize;
    } AVformatConversion;


typedef struct fgbformat
    {
    /* This is set by the CIL when the format is installed.  This value is
       used to identify this format in other CIL calls. */
    int formatID;


    /* These fields are filled out with information about the format to be
       added.  They must be filled out before the format is installed into
       the CIL using the AVinstallFGBformat() function. */
    AVformatDescriptor description;
    AVformatConversion convert;
    AVimageAccess fileAccess;
    AVimageAccess bitmapAccess;
    } AVfgbFormat;

typedef AVfgbFormat  * AVfgbFormatPtr;
typedef AVfgbFormat  *  * AVfgbFormatPtr2;

/*************************************************************************
 *
 * Data structures describing pixels
 *
 ************************************************************************/
/*
 * Format of the SVW native pixel format
 */
#define Y_MASK  0x00FE
#define CR_MASK 0X3000
#define CB_MASK 0XC000
typedef unsigned int AVsvwPixel;
typedef AVsvwPixel _huge *AVsvwPixelPtr;

/* 4 pixels needed to hold complete info */
typedef AVsvwPixel AV4svwPixels[4];
typedef AV4svwPixels _huge *AV4svwPixelsPtr;


/* Define an RGB color triple */
typedef struct rgbTriple {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    } AVrgbPixel;
typedef AVrgbPixel _huge *AVrgbPixelPtr;

/* 4 pixels are converted at a time */
typedef AVrgbPixel AV4rgbPixels[4];
typedef AV4rgbPixels _huge *AV4rgbPixelsPtr;

/*************************************************************************
 *
 * Data structures describing SVW native file format
 *
 ************************************************************************/
#define MakeID(a,b,c,d)  ( (long)(a)		\
			 | (long)(b)<<8 	\
			 | (long)(c)<<16	\
			 | (long)(d)<<24 )
#define FILE_SVW_TYPE  MakeID('S', 'V', 'W', ' ')
#define FILE_REVISION  1

typedef struct nativefile {
        long fileheader;
        int format;
        int revision;
        int width;
        int height;
        int reserved1;
        int reserved2;
        int reserved3;
        int reserved4;
        } AVnativeFile;
typedef AVnativeFile _huge * AVnativeFilePtr;

/*************************************************************************
 *
 * Format IDs 
 *
 ************************************************************************/

/* Band Formats */
#define BAND_SVW_NATIVE     1
#define BAND_WINDOWS24      2
#define BAND_TARGA16        4
#define BAND_TARGA24        5
#define BAND_TARGA32        6
#define BAND_PCXGRAY        7
#define BAND_PCX256         8
#define BAND_WINDOWS8       9
#define BAND_WINDOWS8GRAY   10
#define BAND_JPEG           11
#define BAND_OS2_24      12		// OS/2 only
#define BAND_OS2_8       13		// OS/2 only
#define BAND_OS2_8GRAY   14		// OS/2 only

/* Bitmap Formats */
#define BITMAP_SVW_NATIVE   BAND_SVW_NATIVE
#define BITMAP_WINDOWS24    BAND_WINDOWS24
#define BITMAP_WINDOWS8     BAND_WINDOWS8	/* Grab Only */
#define BITMAP_WINDOWS8GRAY BAND_WINDOWS8GRAY	/* Grab Only */
#define BITMAP_OS2_24       BAND_OS2_24
#define BITMAP_OS2_8        BAND_OS2_8		/* Grab Only */
#define BITMAP_OS2_8GRAY    BAND_OS2_8GRAY	/* Grab Only */

/*
 * Supported File Formats
 * 
 * Windows formats are not available under DOS.
 * 8 bit formats can only be used for "grab" operations (write),
 *   not for "put" operations (read).
 * OS/2 formats only work under OS/2
 */
#define FILE_SVW_NATIVE     BAND_SVW_NATIVE  /* read/write         */
#define FILE_WINDOWS24      BAND_WINDOWS24   /* read/write         */
#define FILE_TARGA16        BAND_TARGA16     /* read/write         */
#define FILE_TARGA24        BAND_TARGA24     /* read/write         */
#define FILE_TARGA32        BAND_TARGA32     /* read/write         */
#define FILE_PCXGRAY        BAND_PCXGRAY     /* write only         */
#define FILE_PCX256         BAND_PCX256      /* write only         */
#define FILE_WINDOWS8       BAND_WINDOWS8    /* write only         */
#define FILE_WINDOWS8GRAY   BAND_WINDOWS8GRAY/* write only         */
#define FILE_JPEG           BAND_JPEG        /* read/write         */
#define FILE_OS2_24	    BAND_OS2_24	     /* read/write         */
#define FILE_OS2_8	    BAND_OS2_8	     /* write only         */
#define FILE_OS2_8GRAY	    BAND_OS2_8GRAY   /* write only         */


/* Standards for the AVtuner call */
#define USA_BCST 0
#define USA_CATV 1
#define JAPAN	 3
#define W_EUROPE 4

#endif	/* AV_H */
int  _cdecl AVdefineAudio(VIDEO vid, int volume, int balance, int bass, int treble);
int  _cdecl AVsetAudio(VIDEO vid, int parm, int value);
AVfixString  _cdecl AVerrorString(int n);
int  _cdecl AVgetVidConnection(VIDEO vid, ConConfigPtr cc);
int  _cdecl AVgetVidUnit(VIDEO vid, AVvarString buf, int n);
int  _cdecl AVgetVidSource(VIDEO vid, AVvarString buf, int n);
int  _cdecl AVgetDisplay(VIDEO vid, int parm);
int  _cdecl AVgetAudio(VIDEO vid, int parm);
int  _cdecl AVcvtBGRtoKeyColor (int op, long value);
int  _cdecl AVcvtRGBtoKeyColor (int r, int g, int b);
long  _cdecl AVgetPlayerStatus(VIDEO vid, int parm);
int  _cdecl AVpausePlayer(VIDEO vid);
int  _cdecl AVplayPlayer(VIDEO vid, long end_frame);
int  _cdecl AVseekPlayer(VIDEO vid, long frame);
int  _cdecl AVsetPlayer(VIDEO vid, int parm, int value);
int  _cdecl AVstepPlayer(VIDEO vid, long incr);
int  _cdecl AVstopPlayer(VIDEO vid);
int  _cdecl AVloadPlayer(VIDEO vid, AVfixString clip);
int  _cdecl AVunloadPlayer(VIDEO vid);
int  _cdecl AVtuner(VIDEO vid, int channel, int fine, int standard);
int  _cdecl AVcolorKey(VIDEO vid, int mode, int value);
int  _cdecl AVfitMode(VIDEO vid, int mode);
VIDEO  _cdecl AVcreate(AVfixString source);
void  _cdecl AVdestroy(VIDEO vid);
int  _cdecl AVmap(VIDEO vid);
int  _cdecl AVunmap(VIDEO vid);
int  _cdecl AVenable(VIDEO vid);
int  _cdecl AVdisable(VIDEO vid);
int  _cdecl AVvideoInput(VIDEO vid, int vin);
int  _cdecl AVsetVideoSignal(VIDEO vid, int sigtype);
int  _cdecl AVaudioInput(VIDEO vid, int ain);
int  _cdecl AVfreeze(VIDEO vid, int flag);
int  _cdecl AVdefineVidport(VIDEO vid, VidportPtr vp);
int  _cdecl AVconfigure(VIDEO vid, WinportPtr frame, WinportPtr ret_wp, int mask);
int  _cdecl AVmove(VIDEO vid, AVgcoord x, AVgcoord y);
int  _cdecl AVsize(VIDEO vid, AVgcoord width, AVgcoord height);
VIDEO  _cdecl AVvideoWindow(AVfixString src_name, AVgcoord x, AVgcoord y, AVgcoord width, AVgcoord height);
int  _cdecl AVgetKeyMode(VIDEO vid);
int  _cdecl AVgetKeyValue(VIDEO vid);
int  _cdecl AVdevice(VIDEO vid, AVfixString device);
int  _cdecl AVsetDisplay(VIDEO vid, int parm, int value);
int  _cdecl AVxlatGrToVid(VIDEO vid, AVrectPtr GraphicsRect, AVrectPtr VideoRect);
int  _cdecl AVfade (VIDEO vid, int how, int mask, unsigned duration);
int  _cdecl AVisFaded(VIDEO vid, int mask);
int  _cdecl AVgrabToFile (VIDEO vid, AVfixString filename, int format, AVrectPtr graphicsRect);
int  _cdecl AVputFromFile (VIDEO vid, AVfixString filename, int format, AVrectPtr graphicsRect);
int  _cdecl AVgrabToBitmap (VIDEO vid, int format, AVrectPtr graphicsRect, AVbitmapPtr  *bitmap);
int  _cdecl AVputFromBitmap (VIDEO vid, int format, AVbitmapPtr bitmap, AVrectPtr graphicsRect);
int  _cdecl AVclear (VIDEO vid, AVrectPtr graphicsRect);
int  _cdecl AVgrabImage (AVimageInfoPtr imageInfoPtr);
int  _cdecl AVputImage (AVimageInfoPtr imageInfoPtr);
int  _cdecl AVprescanImage (AVimageInfoPtr infoPtr);
int  _cdecl AVinstallFGBformat (AVfgbFormatPtr formatPtr);
int  _cdecl AVlistFGBformats (int arraySize, int  *array, int  *num);
int  _cdecl AVgrabPixelsFixed (AVimageInfoPtr infoPtr);
int  _cdecl AVputPixelsFixed (AVimageInfoPtr infoPtr);
int  _cdecl AVclearInfo (AVimageInfoPtr infoPtr);
int  _cdecl AVgetFormatInfo (AVimageInfoPtr infoPtr);
int  _cdecl AVupdateImageSize (AVimageInfoPtr infoPtr);
int  _cdecl AVcreateBands (AVimageInfoPtr infoPtr);
int  _cdecl AVfreeBands (AVimageInfoPtr infoPtr);
int  _cdecl AVrectWidth (AVrectPtr rectPtr);
int  _cdecl AVrectHeight (AVrectPtr rectPtr);
int  _cdecl AVwriteBand (AVimageInfoPtr infoPtr);
int  _cdecl AVreadBand (AVimageInfoPtr infoPtr);
int  _cdecl AVcreateFileBand (AVimageInfoPtr infoPtr);
int  _cdecl AVcreateBitmapBand (AVimageInfoPtr infoPtr);
int  _cdecl AVendFile (AVimageInfoPtr infoPtr);
int  _cdecl AVgrabToBand(AVimageInfoPtr infoPtr);
int  _cdecl AVputFromBand(AVimageInfoPtr infoPtr);
int  _cdecl AVnativeRowSize(int width, int nativeFormat);
int  _cdecl AVconvertRGBtoSVWpixels(AV4rgbPixelsPtr rgb, AV4svwPixelsPtr svw);
int  _cdecl AVconvertSVWtoRGBpixels(AV4svwPixelsPtr svw4, AV4rgbPixelsPtr rgb4);
int  _cdecl AVconvertRGBtoSVW(AVimageInfoPtr infoPtr, AVpixelPtr srcPtr, AVpixelPtr destPtr);
int  _cdecl AVconvertSVWtoRGB(AVimageInfoPtr infoPtr, AVpixelPtr srcPtr, AVpixelPtr destPtr);
int  _cdecl AVsvwRowSize(int width);
int  _cdecl AVdoNothing(AVimageInfoPtr infoPtr);
int  _cdecl AVcreateNativeBand(AVimageInfoPtr infoPtr);
int  _cdecl AVgetDevices(int crit, int  *cnt, AVvarString buf, int n);
int  _cdecl AVinit(AVfixString fnam);
void  _cdecl AVend(void);
ErrorHandler  _cdecl AVinstallErrHandler (ErrorHandler func);
int  _cdecl AVsetConnection(AVfixString srcnam,AVfixString unitnam,ConConfigPtr cc);
int  _cdecl AVgetConnection(AVfixString srcnam,AVfixString unitnam,ConConfigPtr cc);
int  _cdecl AVgetSrcsByUnit(AVfixString unitnam,int  *cnt,AVvarString buf,int n);
int  _cdecl AVgetUnitsBySrc(AVfixString srcnam,int  *cnt,AVvarString buf,int n);
int  _cdecl AVdelDevice(AVfixString srcnam);
int  _cdecl AVaddDevice(AVfixString src_name,SrcConfigPtr uconfig);
int  _cdecl AVgetUnitConfig(AVfixString src_name,UnitConfigPtr uconfig);
int  _cdecl AVgetSourceConfig(AVfixString src_name, SrcConfigPtr sconfig);
int  _cdecl AVsetSourceConfig(AVfixString src_name, SrcConfigPtr sconfig);
int  _cdecl AVremoveFGBformat (int formatID);
int  _cdecl AVgetFGBformat (int formatID, AVfgbFormatPtr2 formatPtr);
int  _cdecl AVwrite (AVfile fh, AVpixelPtr data, long size);
int  _cdecl AVread (AVfile fh, AVpixelPtr data, long size);
void huge * _cdecl AVfgbmalloc (long nbytes);
void  _cdecl AVfgbfree (void _huge *ptr);
int  _cdecl AVopen (AVfixString fileName, AVfixString type, AVfilePtr fh);
int  _cdecl AVclose (AVfile file);
int  _cdecl AVseek (AVfile file, long position, int origin);
int  _cdecl AVendBitmap (AVimageInfoPtr infoPtr);
