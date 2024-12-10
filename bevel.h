// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef BEVEL_H
#define BEVEL_H

#include "cimp.h"
#include "gfx.h"
#include "wincontrol.h"
#include "screen.h"
#include "menu.h"
#include "listscrollbar.h"
#include "hint.h"
#include "window.h"
#include "control.h" // inheriting class's header file

class TBevel : public TControl
{
private:
public:		// User declarations
TBevel(TWindow *Window);
void show();
void hide();
void rendercontrol();
TBorderStyle borderstyle;
TBevelStyle bevelinner;
TBevelStyle bevelouter;
int bevelwidth;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createbevel(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // BEVEL_H
