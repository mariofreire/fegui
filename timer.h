// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef TIMER_H
#define TIMER_H

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
#include "hint.h"
#include "toolbar.h"
#include "image.h"
#include "control.h"
#include "component.h" // inheriting class's header file

class TTimer : public TComponent
{
private:
int tickcount;
int tickstart;
bool timestarted;
public:		// User declarations
TTimer(TWindow *Window);
~TTimer();
bool enabled;
int interval;
int gettickcount();
void rendercomponent();
TTimerEvent ontimer;
TWindow* window;
TControl* parent;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createtimer(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // TIMER_H
