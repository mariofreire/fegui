// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef TOOLTIP_H
#define TOOLTIP_H

#include "cimp.h"
#include "gfx.h"
#include "control.h"
#include "wincontrol.h"
#include "window.h"
#include "hint.h"

extern bool hintrect_reset;

extern bool tooltip_control;
extern bool tooltip_fadeout;
extern bool tooltip_incontrol;
extern int tooltip_fadealpha;
extern int tooltip_alphavalue;
extern int tooltip_x,tooltip_y;
extern char *tooltip;
extern bool tooltip_visible;
extern bool tooltip_showing;
void settooltipalpha(int alphavalue);
void resettooltip(void);
void showtooltip(int x,int y,const char* text);
void showtooltip(const char* text);
void showtooltips(void);


#endif // TOOLTIP_H
