// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

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
#include "control.h" // inheriting class's header file

class TToolButton : public TControl
{
private:
public:		// User declarations
TToolButton(TWindow *Window);
~TToolButton();
void show();
void hide();
void rendercontrol();
int imageindex;
bool toggle;
bool down;
int index;
int groupindex;
bool transparent;
int state;
int spacing;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createtoolbutton(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // TOOLBUTTON_H
