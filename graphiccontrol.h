// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef GRAPHICCONTROL_H
#define GRAPHICCONTROL_H

#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h" // inheriting class's header file
#include "canvas.h" // inheriting class's header file
#include "control.h" // inheriting class's header file

class TGraphicControl : public TControl
{
private:
public:		// User declarations
TGraphicControl(TWindow *Window);
~TGraphicControl();
void show();
void hide();
void rendercontrol();
};

#endif // GRAPHICCONTROL_H
