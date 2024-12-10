// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef PEN_H
#define PEN_H

#include "cimp.h"
#include "graphicobject.h" // inheriting class's header file

class TPen : public TGraphicObject
{
private:
public:		// User declarations
TPen();
~TPen();
int alpha;
TColor color;
TPenStyle style;
TPenMode mode;
int width;
};

#endif // PEN_H
