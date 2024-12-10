// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"
#include "screen.h"
#include "mouse.h"
#include "hint.h"
#include "menu.h"
#include "gfx.h"
#include "msgbox.h"
#include "viewport.h"
#include "console.h"
#include "filesystem.h"
#include "image.h"
#include "button.h"
#include "speedbutton.h"
#include "glyphbutton.h"
#include "toolbutton.h"
#include "radiobutton.h"
#include "edit.h"
#include "listscrollbar.h"
#include "textbox.h"
#include "tooltip.h"
#include "keyboard.h"
#include "icons.h"
#include "cursors.h"
#include "bitmap.h"
#include "png.h"
#include "font.h"
#include "filesystem.h"
#include "canvas.h"
#include "groupbox.h"
#include "label.h"
#include "msgbox.h"
#include "imagelist.h"
#include "shape.h"
#include "updown.h"
#include "blend.h"
#include "picture.h"
#include "checkbox.h"
#include "combobox.h"
#include "listbox.h"
#include "panel.h"
#include "bevel.h"
#include "scrollbar.h"
#include "progressbar.h"
#include "timer.h"
#include "transparentbox.h"
#include "trackbar.h"
#include "dockbar.h"
#include "listview.h"
#include "toolbar.h"
#include "mainmenu.h"
#include "videoplayer.h"
#include "webbrowser.h"

void appcreate();
void appinit();
void appuninit();
void apprun();
void appdestroy();

extern bool appinitialized;

extern char guipath[256];


#endif // APPLICATION_H
