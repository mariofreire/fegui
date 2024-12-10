// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h"
#include "canvas.h"
#include "bitmap.h"
#include "png.h"
#include "picture.h"
#include "window.h"
#include "screen.h"
#include "gfx.h"
#include "icons.h"
#include "mouse.h"
#include "hint.h"
#include "scrollbar.h"
#include "control.h" // inheriting class's header file

class TProgressBar : public TControl
{
private:
public:		// User declarations
TProgressBar(TWindow *Window);
TNotifyEvent onchange;
void show();
void hide();
void rendercontrol();
bool twinkle;
bool smooth;
TProgressBarOrientation orientation;
int min,max;
int position;
int step;
int blocksize;
int blockspace;
bool showborder;
int backgroundalpha;
TColor gaugecolor;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createprogressbar(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // PROGRESSBAR_H
