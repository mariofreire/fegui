// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef SHAPE_H
#define SHAPE_H

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
#include "mouse.h"
#include "tooltip.h"
#include "control.h" // inheriting class's header file


class TShape : public TControl
{
private:
public:		// User declarations
TShape(TWindow *Window);
~TShape();
void show();
void hide();
void rendercontrol();
TBrush *brush;
TPen *pen;
TShapeType shape;
bool transparent;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createshape(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


#endif // SHAPE_H
