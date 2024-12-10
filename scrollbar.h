// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

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
#include "menu.h"
#include "control.h" // inheriting class's header file

extern bool sbarcontrolon;

class TScrollBar : public TControl
{
private:
public:		// User declarations
TScrollBar(TWindow *Window);
TNotifyEvent onchange;
void show();
void hide();
void rendercontrol();
bool twinkle;
int pagesize;
TScrollKind kind;
int min,max;
int position;
int smallchange,largechange;
bool fastchange;
bool showborder;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createscrollbar(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // SCROLLBAR_H
