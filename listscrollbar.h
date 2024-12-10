// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef LISTSCROLLBAR_H
#define LISTSCROLLBAR_H

#include "cimp.h"
#include "gfx.h"
#include "window.h"
#include "mouse.h"
#include "hint.h"
#include "icons.h"
#include "control.h" // inheriting class's header file

class TListScrollBar : public TControl
{
private:
public:		// User declarations
TListScrollBar(TWindow *Window);
void show();
void hide();
void rendercontrol();
bool IsInListScrollBar(TControl* Control);
bool twinkle;
int pagesize;
TScrollKind kind;
int min,max;
int position;
int smallchange,largechange;
bool fastchange;
bool showborder;
};

#endif // LISTSCROLLBAR_H
