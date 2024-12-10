// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h"
#include "canvas.h"
#include "bitmap.h"
#include "png.h"
#include "picture.h"
#include "window.h"
#include "screen.h"
#include "gfx.h"
#include "icons.h"
#include "mouse.h"  
#include "keyboard.h"
#include "hint.h"
#include "fewebkit.h"     
#include "listscrollbar.h"
#include "control.h" // inheriting class's header file


extern bool webbrowsercontrolon;

extern bool webbrowser_mousedown_on, webbrowser_mousemove_on, webbrowser_mouseup_on;
extern bool webbrowser_keydown_on, webbrowser_keypress_on, webbrowser_keyup_on;

class TWebBrowser : public TControl
{
private:
int webbrowserhandle;
public:		// User declarations
TWebBrowser(TWindow *Window);
~TWebBrowser();
void show();
void hide();
void rendercontrol();
TBorderStyle borderstyle;
TListScrollBar* hscroll;
TListScrollBar* vscroll;
TColor color;
std::string url;
int initialized;
int browser;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createwebbrowser(int winid);

void webkit_keydown(unsigned char key);
void webkit_keyup(unsigned char key);     

extern int activewebbrowser;

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // WEBBROWSER_H
