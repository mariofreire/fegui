// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef CANVAS_H
#define CANVAS_H

#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "blend.h"
#include "graphicobject.h" // inheriting class's header file


class TCanvas : public TGraphicObject
{
private:
public:		// User declarations
TCanvas();
~TCanvas();
int format;
int depth;
int width;
int height;
TBrush *brush;
TPen *pen;
unsigned char *pixels;
TColor getpixel(int x,int y);
void setpixel(int x,int y,TColor c);
void drawline(int x0,int y0,int x1,int y1,TColor c);
void fillrect(int x0,int y0,int x1,int y1,TColor c);
void rectangle(int x0,int y0,int x1,int y1,TColor c);
};

#endif // CANVAS_H
