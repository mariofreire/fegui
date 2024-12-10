// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef FONT_H
#define FONT_H

#include "cimp.h"
#include "filesystem.h"

//extern BMP* fontbmp[256];
extern bitmapfont_t textfont;

int loadbitmapfont(char *filename, bitmapfont_t *f,bool textured);
void freebitmapfont(bitmapfont_t *f);

void *get_font( void );

extern GLuint	base;				// Base Display List For The Font Set
extern COLORREF fontcolor;
extern int fontalpha;
extern int fontheight,fontweight;

GLvoid BuildFont(int height, int weight);								// Build Our Bitmap Font
GLvoid KillFont(GLvoid);									// Delete The Font List


#endif // FONT_H
