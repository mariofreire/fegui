// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef EDIT_H
#define EDIT_H

#include "cimp.h"
#include "gfx.h"
#include "window.h"
#include "updown.h"
#include "mouse.h"
#include "keyboard.h"
#include "hint.h"
#include "menu.h"
#include "textbox.h"
#include "control.h" // inheriting class's header file

class TEdit : public TControl
{
private:
public:		// User declarations
TEdit(TWindow *Window);
TNotifyEvent onchange;
void show();
void hide();
void rendercontrol();
void editinput();
void clear();
void selectall();
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

extern TEdit* activeedit;

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createedit(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // EDIT_H
