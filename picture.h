// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef PICTURE_H
#define PICTURE_H

#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h"
#include "canvas.h"
#include "graphicobject.h"
#include "bitmap.h"
#include "png.h"


class TPicture : public TGraphicObject
{
private:
public:		// User declarations
TPicture();
~TPicture();
TCanvas* canvas;
GLuint textureid;
bool textured;
bool transparent;
TColor transparentcolor;
void load(char *filename);
void save(char* filename);
};


#endif // PICTURE_H
