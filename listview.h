// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef LISTVIEW_H
#define LISTVIEW_H

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
#include "hint.h"
#include "image.h"
#include "imagelist.h"
#include "control.h" // inheriting class's header file

class TListItem;

class TListItem : public TObject
{
protected:
private:
public:		// User declarations
TListItem(char* caption);
TListItem();
~TListItem();
char* caption;
int imageindex;
int stateindex;
std::string subitems[256];
int numsubitems;
};

class TListItems : public TObject
{
protected:
private:
public:		// User declarations
TListItems();
~TListItems();
TListItem* additem();
TListItem* additem(char *caption);
void additem(TListItem* item);
TListItem* items[1024];
int numitems;
int itemindex;
};

class TListColumn : public TObject
{
protected:
private:
public:		// User declarations
TListColumn();
~TListColumn();
bool enabled;
int width;
char* text;
};

class TListColumns : public TObject
{
protected:
private:
public:		// User declarations
TListColumns();
~TListColumns();
void additem(char *text);
void additem(TListColumn* item);
TListColumn* items[1024];
int numitems;
};

class TListView : public TControl
{
private:
public:		// User declarations
TListView(TWindow *Window);
~TListView();
void show();
void hide();
void rendercontrol();
TBorderStyle borderstyle;
bool columnclick;
TListColumns* columns;
TColor color;
bool gridlines;
bool hideselection;
bool hottrack;
TListHotTrackStyle hottrackstyle;
int hovertime;
TIconArrangement iconarrangement;
bool autoarrange;
bool wraptext;
TListItems* items;
TImageList* largeimages;
bool multiselect;
bool readonly;
bool rowselect;
bool showcolumnheaders;
bool showworkareas;
TImageList* smallimages;
TSortType sorttype;
TImageList* stateimages;
TViewStyle viewstyle;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createlistview(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // LISTVIEW_H
