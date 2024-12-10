// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef MENU_H
#define MENU_H

#include "screen.h"
#include "viewport.h"
#include "hint.h"
#include "icons.h"
#include "wincontrol.h" // inheriting class's header file


extern int showmenu;
extern int nummenues;

void show_menu(TMenu* menu);

bool IsInAnyMenu(void);


extern int submenuleft[256],submenutop[256],submenuwidth[256],submenuheight[256];
extern int submenues;
extern int showsubmenu;

void pushmenuitemindex();
void popmenuitemindex();

bool submenuitemclick(TMenuItem* item);

extern int submenuitemclickid;

class TMenuItem
{
private:	// User declarations
//void rendercontrols();
public:		// User declarations
TMenuItem();
~TMenuItem();
char *name;
TWinRenderEvent onclick;
TWinRenderEvent onpopup;
TWinRenderEvent onupdate;
TWinRenderEvent onshow;
TMenuItem* additem(char* caption);
void additem(TMenuItem* item);
char* caption;
bool checked;
int groupindex;
int state;
bool enabled;
int imageindex;
int numitems;
TMenuItem* items[256];
int itemindex;
int tag;
bool showing;
bool menuitemhighlight;
bool menuitemdown;
int menuitemshow;
int menuitemctl;
int mindex;
int id;
};

class TMenuItems : public TMenuItem
{
private:	// User declarations
//void rendercontrols();
public:		// User declarations
TMenuItems();
~TMenuItems();
};

class TMenu : public TWinControl
{
private:	// User declarations
void rendercontrols();
public:		// User declarations
TMenu();
~TMenu();
void show();
void click();
bool IsInMenu(TWinControl* Window);
//TImageList* images;
TMenuItems* menu;
};

extern TMenu *menues[256];

extern TMenu* systemmenu;
extern TMenu* editmenu;

#endif // MENU_H
