// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef LABEL_H
#define LABEL_H

#include "cimp.h"
#include "gfx.h"
#include "window.h"
#include "control.h" // inheriting class's header file

class TLabel : public TControl
{
private:
public:		// User declarations
TLabel(TWindow *Window);
void show();
void hide();
void rendercontrol();
bool autosize;
TAlignment alignment;
TTextLayout layout;
bool transparent;
bool wordwrap;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createlabel(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // LABEL_H
