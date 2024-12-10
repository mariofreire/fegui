// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef HINT_H
#define HINT_H

#include "cimp.h"
#include "gfx.h"
#include "control.h"
#include "wincontrol.h"
#include "screen.h"
#include "menu.h"
#include "window.h"

void hintrect(bool focus,char *text);
void hintcontrol(TControl *ctrl);
void hintwincontrol(TWinControl *wctrl);

#endif // HINT_H
