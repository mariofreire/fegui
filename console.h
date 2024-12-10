// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef CONSOLE_H
#define CONSOLE_H

#include "cimp.h"
#include "gfx.h"
#include "window.h"
#include "control.h"

extern COLORREF c_textcolor;
extern int cblinkcnt;

void drawimagedatamask(int x, int y,int w,int h,unsigned char*data,int alpha, COLORREF color, bool transparent, COLORREF transparentcolor);
void consoletextcolor(COLORREF c);
void consoletextfont(char *font);
void consoletextout(int x,int y,char *text);
int consoletextwidth(char *text);
void consolecharout(int x,int y,unsigned char c);
int consolecharwidth(void);

#endif // CONSOLE_H
