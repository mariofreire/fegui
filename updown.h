// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef UPDOWN_H
#define UPDOWN_H


#include "cimp.h"
#include "gfx.h"
#include "wincontrol.h"
#include "window.h"
#include "mouse.h"
#include "keyboard.h"
#include "screen.h"
#include "hint.h"
#include "edit.h"
#include "textbox.h"
#include "control.h" // inheriting class's header file


extern bool updownbtnctrlon;
extern bool updownbtn_btndown;
extern int updown_btncnt;
extern int updownbtncnt;
extern bool updowncontrolon;
extern bool updownspeedarea;
extern bool updownspeedarea_horiz;

class TUpDown : public TControl
{
private:
public:		// User declarations
TUpDown(TWindow *Window);
void show();
void hide();
void rendercontrol();
bool updown_speedarea;
bool updownctrlsetvalueonshow;
bool updownbtnspeed;
int updownlastpos;
bool upbtn_down,dnbtn_down;
bool arrowkeys;
TControl* associate;
int increment;
int max;
int min;
TUDOrientation orientation;
int position;
bool thousands;
bool wrap;
TColor color;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createupdown(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // UPDOWN_H
