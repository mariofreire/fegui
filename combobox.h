// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "cimp.h"
#include "gfx.h"
#include "wincontrol.h"
#include "screen.h"
#include "menu.h"
#include "listscrollbar.h"
#include "keyboard.h"
#include "hint.h"
#include "window.h"
#include "checkbox.h"
#include "listbox.h"
#include "control.h" // inheriting class's header file

extern int comboboxeditxl;
extern int comboblinkcnt;
extern bool comboboxeditcontrolon;
extern bool comboboxeditfocused;
extern bool combobox_focused;
extern bool showcombolistbox;
extern bool comboboxcontrolon;

class TComboListBox : public TControl
{
private:
public:		// User declarations
TComboListBox(TWindow *Window);
~TComboListBox();
void show();
void hide();
void rendercontrol();
void additem(char* name);
bool IsInComboBox(TControl* Control);
bool autoselect;
TBorderStyle borderstyle;
TListScrollBar* scroll;
int itemheight;
int itemindex;
int numitems;
std::string items[4096];
bool multiselect;
bool showfocusframe;
};

class TComboBoxEdit : public TControl
{
private:
public:		// User declarations
TComboBoxEdit(TWindow *Window);
void show();
void hide();
void rendercontrol();
void comboboxeditinput();
TEditCharCase charcase;
bool readonly;
int maxlength;
std::string seltext;
int sel_start,sel_length;
int sel_index;
int substring_start;
int substring_end;  
std::string text;
int text_x_offset;
};

class TComboBox : public TControl
{
private:
public:		// User declarations
TComboBox(TWindow *Window);
~TComboBox();
void show();
void hide();
void rendercontrol();
void additem(char* name);
bool IsInComboBox(TControl* Control);
TBorderStyle borderstyle;
TComboBoxEdit* edit;
TComboListBox* listbox;
int dropdowncount;
int itemheight;
int itemindex;
int numitems;
std::string items[4096];
int maxlength;
std::string text;
TComboBoxStyle style;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createcombobox(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // COMBOBOX_H
