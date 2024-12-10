// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h"
#include "canvas.h"
#include "bitmap.h"
#include "png.h"
#include "picture.h"
#include "window.h"
#include "screen.h"
#include "gfx.h"
#include "icons.h"
#include "mouse.h"
#include "hint.h"
#include "control.h" // inheriting class's header file

extern int viewportleft,viewporttop,viewportright,viewportbottom;
void setviewport(int left,int top,int right,int bottom);

extern bool viewportcontrolon;

class TViewport : public TControl
{
private:
public:		// User declarations
TViewport(TWindow *Window);
void show();
void hide();
void rendercontrol();
TAlign align;
TBorderStyle borderstyle;
TColor color;
int backgroundalpha;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createviewport(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


#endif // VIEWPORT_H
