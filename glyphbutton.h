// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef GLYPHBUTTON_H
#define GLYPHBUTTON_H

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
#include "bitmap.h"
#include "picture.h"
#include "image.h"
#include "mouse.h"
#include "tooltip.h"
#include "control.h" // inheriting class's header file


class TGlyphButton : public TControl
{
private:
public:		// User declarations
TGlyphButton(TWindow *Window);
~TGlyphButton();
void show();
void hide();
void rendercontrol();
bool autosize;
bool center;
bool doublebuffer;
bool generate;
bool fadebutton;
int fadestep;
int fadecount;
TPicture* btnNormal;
TPicture* btnDown;
TPicture* btnOver;
TPicture* btnUp;
TPicture* btnOut;
bool proportional;
bool stretch;
bool glyphbuttoncontrolon;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createglyphbutton(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


#endif // GLYPHBUTTON_H
