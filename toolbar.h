// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "cimp.h"
#include "gfx.h"
#include "wincontrol.h"
#include "screen.h"
#include "menu.h"
#include "listscrollbar.h"
#include "hint.h"
#include "imagelist.h"
#include "keyboard.h"
#include "window.h"
#include "control.h" // inheriting class's header file

extern bool toolbarcontrolon;
extern bool toolbtncontrolon;

class TToolBar : public TControl
{
private:
public:		// User declarations
TToolBar(TWindow *Window);
void show();
void hide();
void rendercontrol();
TBorderStyle borderstyle;
TBevelStyle bevelinner;
TBevelStyle bevelouter;
int bevelwidth;
int borderwidth;
TColor color;
int buttonwidth;
int buttonheight;
TImageList* images;
int ident;
bool dockmove;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createtoolbar(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // TOOLBAR_H
