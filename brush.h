// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef BRUSH_H
#define BRUSH_H

#include "cimp.h"
#include "graphicobject.h" // inheriting class's header file

class TBrush : public TGraphicObject
{
private:
public:		// User declarations
TBrush();
~TBrush();
int alpha;
TColor color;
TBrushStyle style;
};


#endif // BRUSH_H
