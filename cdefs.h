// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef CDEFS_H
#define CDEFS_H



/**************************
 * Includes
 *
 **************************/

#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <windef.h>
#include <math.h>
#include <set>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <gl/glaux.h>
#include <time.h>

#ifndef IN_BOUNDS
#define IN_BOUNDS( x, lo, hi ) ( (x) >= (lo) && (x) <= (hi) )
#endif

#ifndef MAX
#define MAX(a,b)  ((a)>(b) ? (a) : (b))
#define MIN(a,b)  ((a)<(b) ? (a) : (b))
#endif


#define PI 3.1415926535897932384626433832795

/*
#ifndef max
#define max(a,b)  ((a)>(b) ? (a) : (b))
#define min(a,b)  ((a)<(b) ? (a) : (b))
#endif
*/

#define imageoffset(_x,_y,_width,_height) (((_width*(_height-_y))-(_width-_x)))

#define XBACKGROUND_LEN 64

#define RESIZEWIN_NONE        0
#define RESIZEWIN_LEFT        1
#define RESIZEWIN_TOP         2
#define RESIZEWIN_WIDTH       3
#define RESIZEWIN_HEIGHT      4
#define RESIZEWIN_LT          5
#define RESIZEWIN_WT          6
#define RESIZEWIN_LH          7
#define RESIZEWIN_WH          8
#define RESIZEWIN_SCALE       RESIZEWIN_WH
#define RESIZEWIN_SIZE        RESIZEWIN_WH
#define RESIZEWIN_SIZEXY      RESIZEWIN_WH
#define RESIZEWIN_RESIZE      RESIZEWIN_WH

#define EDITTEXT_BOXINNERMARGINX   3
#define EDITTEXT_HEIGHT            20
#define EDITTEXT_WIDTH            130
#define EDITTEXT_MIN_INT_WIDTH   35
#define EDITTEXT_MIN_TEXT_WIDTH   50

#define NEAREST		1
#define BILNEAR		2

#define clBlack                                      0x0
#define clMaroon                                     0x80
#define clGreen                                      0x8000
#define clOlive                                      0x8080
#define clNavy                                       0x800000
#define clPurple                                     0x800080
#define clTeal                                       0x808000
#define clGray                                       0x808080
#define clSilver                                     0xc0c0c0
#define clRed                                        0xff
#define clLime                                       0xff00
#define clYellow                                     0xffff
#define clBlue                                       0xff0000
#define clFuchsia                                    0xff00ff
#define clAqua                                       0xffff00
#define clLtGray                                     0xc0c0c0
#define clDkGray                                     0x808080
#define clWhite                                      0xffffff
#define clMoneyGreen                                 0xc0dcc0
#define clSkyBlue                                    0xf0caa6
#define clCream                                      0xf0fbff
#define clMedGray                                    0xa4a0a0
#define clDarkGray                                   0x606060
#define clDarkBlue                                   0x6a240a

#define clBackground RGB(0,0,0)

#define clBtnFace RGB(0,192,255)
//#define clBtnFace RGB(224,224,224)

#define clBtnHighlight RGB(clLightifDarkR(clBtnFace),clLightifDarkG(clBtnFace),clLightifDarkB(clBtnFace))
#define clBtnShadow  RGB(GetRValue(clBtnFace)/1.5,GetGValue(clBtnFace)/1.5,GetBValue(clBtnFace)/1.5)
#define cl3DDkShadow  RGB(64,64,64)
#define clActiveCaptionIn RGB(0,0,0)
#define clActiveCaptionOut RGB(255,0,0)
#define clInactiveCaptionIn RGB(16,16,16)
#define clInactiveCaptionOut RGB(164,164,164)
#define clHighlight RGB(0,96,192)
#define clHighlightText RGB(255,255,255)
#define clInfo RGB(255,255,128)
#define clInfoText RGB(0,0,0)
#define clWindow RGB(255,255,255)
#define clWindowText RGB(0,0,0)

#define IMAGE_RGB8    1
#define IMAGE_RGB     3
#define IMAGE_RGB32   3
#define IMAGE_RGBA    4

#define sqr(x) (x*x)

#define FEGUI_STDCALL 
#define FEGUI_CALLBACK FEGUI_STDCALL

#endif // CDEFS_H
