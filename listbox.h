// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef LISTBOX_H
#define LISTBOX_H

#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h"
#include "canvas.h"
#include "graphicobject.h"
#include "bitmap.h"
#include "png.h"
#include "picture.h"
#include "window.h"
#include "screen.h"
#include "gfx.h"
#include "icons.h"
#include "mouse.h"
#include "hint.h"
#include "listscrollbar.h"
#include "menu.h"
#include "scrollbar.h"
#include "combobox.h"
#include "keyboard.h"
#include "control.h" // inheriting class's header file

extern bool listboxcontrolon;

class TListBox : public TControl
{
private:
public:		// User declarations
TListBox(TWindow *Window);
~TListBox();
void show();
void hide();
void rendercontrol();
void additem(char* name);
TBorderStyle borderstyle;
TListScrollBar* scroll;
int itemheight;
int itemindex;
int numitems;
std::string items[4096];
bool multiselect;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createlistbox(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // LISTBOX_H
