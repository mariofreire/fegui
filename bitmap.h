// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef BITMAP_H
#define BITMAP_H

#include "cimp.h"
#include "filesystem.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h"
#include "canvas.h"
#include "graphicobject.h"


int		savebmp(char* filename, BMP* bmp);
BMP*		loadbmp(char* filename);
void		freebmp(BMP* bmp);
unsigned int loadbitmaptexture(char* filename);
AUX_RGBImageRec *LoadBMP(char *Filename);				// Loads A Bitmap Image


class TBitmap : public TGraphicObject
{
	public:
		// class constructor
		TBitmap();
		// class destructor
		~TBitmap();
};


#endif // BITMAP_H
