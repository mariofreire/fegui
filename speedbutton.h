// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef SPEEDBUTTON_H
#define SPEEDBUTTON_H

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
#include "component.h"
#include "control.h" // inheriting class's header file

extern bool speedbtncontrolon;

class TSpeedButton : public TControl
{
private:
public:		// User declarations
TSpeedButton(TWindow *Window);
~TSpeedButton();
void show();
void hide();
void rendercontrol();
void loadicon(char* filename);
bool toggle;
bool down;
int groupindex;
BMP* icon;
TColor iconbackground;
bool transparent;
int state;
int spacing;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createspeedbutton(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // SPEEDBUTTON_H
