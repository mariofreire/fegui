// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef IMAGE_H
#define IMAGE_H


#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h"
#include "canvas.h"
#include "graphicobject.h"
#include "bitmap.h"
#include "png.h"
#include "picture.h"
#include "window.h"
#include "screen.h"
#include "gfx.h"
#include "mouse.h"
#include "tooltip.h"
#include "control.h" // inheriting class's header file


void drawimage32(int x, int y,int width,int height,int format,unsigned char *data,int alpha, bool transparent, COLORREF transparentcolor);
void drawimagemask32(int x, int y,int width,int height,int format,unsigned char *data,int alpha, COLORREF color, bool transparent, COLORREF transparentcolor);


class TImage : public TControl
{
private:
public:		// User declarations
TImage(TWindow *Window);
~TImage();
void show();
void hide();
void rendercontrol();
bool autosize;
bool center;
bool doublebuffer;
bool generate;
TPicture* picture;
bool proportional;
bool stretch;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createimage(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // IMAGE_H
