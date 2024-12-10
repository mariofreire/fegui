// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "cimp.h"
#include "gfx.h"
#include "window.h"
#include "menu.h"
#include "edit.h"
#include "listscrollbar.h"
#include "control.h" // inheriting class's header file

class TTextBox : public TControl
{
private:
public:		// User declarations
TTextBox(TWindow *Window);
~TTextBox();
void show();
void hide();
void rendercontrol();
void textinput();
void clear();
void selectall();
TAlign align;
TListScrollBar* hscroll;
TListScrollBar* vscroll;
TEditCharCase charcase;
bool readonly;
int caretx,carety;
int rowlength;
int count;
int maxlength;
std::string seltext;
int sel_start,sel_length;
int sel_index;
int substring_start;
int substring_end;  
std::string text;
int text_x_offset;
bool wordwrap;
};

extern TTextBox* activetextedit;

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createtextbox(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // TEXTBOX_H
