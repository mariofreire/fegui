// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef GFX_H
#define GFX_H

#include "cimp.h"
#include "viewport.h"
#include "screen.h"
#include "callback.h"
#include "bitmap.h"
#include "png.h"
#include "font.h"

void begindrawing(void);
void enddrawing(void);
void setpixel(int x, int y, COLORREF color, int alpha);
void drawcontroledge(int x,int y,int w,int h, int state, int alpha);
void drawcontroledgew(int x,int y,int w,int h, int state, int alpha);
void subrecttess(int x0,int y0,int x1,int y1);
void fillrecttexture(unsigned int texture, int x0, int y0, int x1, int y1, COLORREF color, int alpha);
void fillrecttess(int x0, int y0, int x1, int y1, COLORREF color, int alpha);
void fillrectpattern(int x0, int y0, int x1, int y1, COLORREF color, int alpha);
void fillrect(int x0, int y0, int x1, int y1, COLORREF color, int alpha);
void rectangle(int x0, int y0, int x1, int y1, COLORREF color, int alpha);
void rectangledashed(int x0, int y0, int x1, int y1, COLORREF color, int alpha);
void rectangledotted(int x0, int y0, int x1, int y1, COLORREF color, int alpha);
void drawline(int x0, int y0, int x1, int y1, COLORREF color, int alpha);
void drawcircle(int x0,int y0,int x1,int y1, COLORREF color, int alpha);
void drawellipse(int x0,int y0,int x1,int y1, COLORREF color, int alpha);
int textwidth(char *text);
void textattr(COLORREF color,int alpha, int height, int weight);
void textout(int x, int y, char *text);
void drawgradient(int x0, int y0, int x1, int y1, COLORREF startcolor, COLORREF endcolor, int alpha,int direction);


COLORREF clLightifDarkR(COLORREF c);
COLORREF clLightifDarkG(COLORREF c);
COLORREF clLightifDarkB(COLORREF c);


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


extern int tessrect_x0;
extern int tessrect_y0;
extern int tessrect_x1;
extern int tessrect_y1;
extern TColor tessrect_color;
extern int tessrect_alpha;

extern int subrect_x0;
extern int subrect_y0;
extern int subrect_x1;
extern int subrect_y1;

int string_width( char *text );
void drawimagemask(int x, int y,BMP* imagefile,int alpha, COLORREF color, bool transparent, COLORREF transparentcolor);
void drawimage(int x, int y,BMP* imagefile,int alpha, bool transparent, COLORREF transparentcolor);
void drawtileimage(int x, int y, int width, int height, BMP* imagefile,int alpha, bool transparent, COLORREF transparentcolor);
void drawsysbtnimage(int x, int y,BMP* imagefile,int alpha,COLORREF highlightcolor,COLORREF shadowcolor,bool transparent, COLORREF transparentcolor, bool enabled);
void drawradioimage(int x, int y,BMP* imagefile,int alpha,COLORREF color,COLORREF highlightcolor,COLORREF shadowcolor,COLORREF lightshadowcolor,COLORREF darkshadowcolor, bool transparent, COLORREF transparentcolor);
void drawflatradioimage(int x, int y,BMP* imagefile,int alpha,COLORREF color,COLORREF highlightcolor,COLORREF shadowcolor,COLORREF lightshadowcolor,COLORREF darkshadowcolor, bool transparent, COLORREF transparentcolor);
void drawcursorimage(int x, int y,BMP* cursorfile,int alpha);
void drawcursorimagemask(int x, int y,BMP* cursorfile,COLORREF color,int alpha);
void drawcursor(int x, int y,BMP* cursorfile);
void drawimagepng(int x, int y,PNG* imagefile,int alpha, bool transparent, COLORREF transparentcolor);


#endif // GFX_H
