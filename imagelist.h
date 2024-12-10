// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef IMAGELIST_H
#define IMAGELIST_H

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
#include "control.h"
#include "component.h" // inheriting class's header file


class TImageList : public TComponent
{
private:
public:		// User declarations
TImageList(TWindow *Window);
~TImageList();
int alphavalue;
int width;
int height;
bool enabled;
int numimages;
TPicture* images[1024];
void addimage(TPicture* image);
void addimage(char* filename);
TPicture* createimage();
void rendercomponent();
TWindow* window;
TControl *parent;
TRenderComponentEvent render;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createimagelist(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // IMAGELIST_H
