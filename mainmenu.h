// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef MAINMENU_H
#define MAINMENU_H

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
#include "menu.h"
#include "hint.h"
#include "toolbar.h"
#include "dockbar.h"
#include "control.h" // inheriting class's header file

class TMainMenu : public TControl
{
private:
public:
TMainMenu(TWindow *Window);
~TMainMenu();
void show();
void hide();
void rendercontrol();
TBorderStyle borderstyle;
TBevelStyle bevelinner;
TBevelStyle bevelouter;
int bevelwidth;
TColor color;
TMenu* menuitems[256];
int nummenuitems;
TMenu* additem();
TMenu* additem(char* caption);
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createmainmenu(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // MAINMENU_H
