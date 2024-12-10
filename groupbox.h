// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef GROUPBOX_H
#define GROUPBOX_H


#include "control.h" // inheriting class's header file
#include "window.h"

class TGroupBox : public TControl
{
private:
public:		// User declarations
TGroupBox(TWindow *Window);
void show();
void hide();
void rendercontrol();
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int creategroupbox(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // GROUPBOX_H
