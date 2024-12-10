// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br
//---------------------------------------------------------------------------

#include <windows.h>
#include <gl/gl.h>
#include "application.h"

#pragma hdrstop

#include "exam1.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TWindow *Window1;
TWindow *Window2;
TWindow *Window3;
TWindow *Window4;
TWindow *Window5;
TWindow *Window6;
TWindow *Window7;
TWindow *Window8;
TWindow *Window9;
TWindow *Window10;
TWindow *Window11;
TWindow *Window12;
TWindow *Window13;
TWindow *Window14;
TWindow *Window15;




void fegui_appcreate()
{
appcreate();
}
void fegui_appinit()
{
appinit();
}
void fegui_appuninit()
{
appuninit();
}
void fegui_apprun()
{
apprun();
}
void fegui_appdestroy()
{
appdestroy();
}
int fegui_createwindow(void)
{
return createwindow();
}
void fegui_deletewindow(int winid)
{
return deletewindow(winid);
}
void fegui_setscreenwidth(int w)
{
setscreenwidth(w);
}
void fegui_setscreenheight(int h)
{
setscreenheight(h);
}
void fegui_setscreensize(int w,int h)
{
setscreenwidth(w);
setscreenheight(h);
}
void fegui_setforegroundwindow(int winid)
{
setforegroundwindow(winid);
}
int fegui_getforegroundwindow(void)
{
return getforegroundwindow();
}
void fegui_setactivewindow(int winid)
{
activewindow = winid;
}
int fegui_getactivewindow(void)
{
return activewindow;
}
int fegui_findwindow(char* name)
{
  for (int i=0;i<numwindows;i++)
  {
      if (strcmp(windows[i]->name,name)==0) return i;
  }
  return -1;
}
int fegui_windowexists(int winid)
{
  for (int i=0;i<numwindows;i++)
  {
      if (windows[i]->windowid == winid) return 1;
  }
  return 0;
}
void fegui_setwindowname(int winid,char* name)
{
if (fegui_windowexists(winid)) windows[winid]->name = name;
}
char* fegui_getwindowname(int winid)
{
if (fegui_windowexists(winid)) return windows[winid]->name;
return NULL;
}
void fegui_restorewindow(int winid)
{
if (fegui_windowexists(winid)) windows[winid]->restore();
}
void fegui_maximizewindow(int winid)
{
if (fegui_windowexists(winid)) windows[winid]->maximize();
}
void fegui_minimizewindow(int winid)
{
if (fegui_windowexists(winid)) windows[winid]->minimize();
}
void fegui_showwindow(int winid)
{
if (fegui_windowexists(winid))
{
windows[winid]->visible = true;
//windows[winid]->show();
}
}
int fegui_showmodalwindow(int winid)
{
if (fegui_windowexists(winid))
{
return windows[winid]->showmodal();
}
return 0;
}
void fegui_windowfreeze(int winid)
{
if (fegui_windowexists(winid)) windows[winid]->freeze();
}
void fegui_setwindowcaption(int winid,char* caption)
{
if (fegui_windowexists(winid)) windows[winid]->caption = caption;
}
void fegui_setwindowpos(int winid,int x,int y)
{
if (fegui_windowexists(winid)) 
{
windows[winid]->left = x;
windows[winid]->top = y;
}
}
void fegui_setwindowsize(int winid,int w,int h)
{
if (fegui_windowexists(winid))
{
windows[winid]->width = w;
windows[winid]->height = h;
}
}
void fegui_resizewindow(int winid,int w,int h)
{
if (fegui_windowexists(winid)) 
{
windows[winid]->width = w;
windows[winid]->height = h;
}
}

void fegui_setmousedown_l(int x,int y)
{
 setmousedown_l(x,y);
}
void fegui_setmousedown_m(int x,int y)
{
 setmousedown_m(x,y);
}
void fegui_setmousedown_r(int x,int y)
{
 setmousedown_r(x,y);
}
void fegui_setmousemove(int x,int y)
{
 setmousemove(x,y);
}
void fegui_setmouseup(int x,int y)
{
 setmouseup(x,y);
}
void fegui_setmousewheel(int key,int delta)
{
 setmousewheel(key,delta);
}
void fegui_setmousepos(int x,int y)
{
 setmousepos(x,y);
}
void fegui_getmousepos(int *x,int *y)
{
 getmousepos(x,y);
}
void fegui_getmousestate(int *bs)
{
 getmousestate(bs);
}
void fegui_getmousewheel(int *k,int *d)
{
 getmousewheel(k,d);
}
int fegui_setmouseasync(int a)
{
 mousea = a;
}
int fegui_getmouseasync(void)
{
 return mousea;
}
int fegui_createbutton(int winid)
{
 return createbutton(winid);
}
void fegui_setbuttonname(int winid,int btnid,char* name)
{
if (fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->caption = name;
}
}
void fegui_showbutton(int winid,int btnid)
{
if (fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->visible = true;
}
}
void fegui_setbuttonpos(int winid,int btnid,int x,int y)
{
if (fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->left = x;
windows[winid]->buttons[btnid]->top = y;
}
}
void fegui_resizebutton(int winid,int btnid,int w,int h)
{
if (fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->width = w;
windows[winid]->buttons[btnid]->height = h;
}
}
void fegui_setbuttoncaption(int winid,int btnid,char* caption)
{
if (fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->caption = caption;
}
}
int fegui_createviewport(int winid)
{
 return createviewport(winid);
}
void fegui_setviewportname(int winid,int btnid,char* name)
{
if (fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->caption = name;
}
}
void fegui_showviewport(int winid,int btnid)
{
if (fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->visible = true;
}
}
void fegui_setviewportpos(int winid,int btnid,int x,int y)
{
if (fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->left = x;
windows[winid]->viewports[btnid]->top = y;
}
}
void fegui_resizeviewport(int winid,int btnid,int w,int h)
{
if (fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->width = w;
windows[winid]->viewports[btnid]->height = h;
}
}
void fegui_setviewportcaption(int winid,int btnid,char* caption)
{
if (fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->caption = caption;
}
}

void fegui_setviewportonrender(int winid,int viewportid,TFEGUI_RenderEvent onrender)
{
 if (fegui_windowexists(winid))
 {
  if (onrender)
  {
    windows[winid]->viewports[viewportid]->onrender = onrender;
  }
 }
}

int fegui_createtransparentbox(int winid)
{
 return createtransparentbox(winid);
}
void fegui_settransparentboxname(int winid,int btnid,char* name)
{
if (fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->caption = name;
}
}
void fegui_showtransparentbox(int winid,int btnid)
{
if (fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->visible = true;
}
}
void fegui_settransparentboxpos(int winid,int btnid,int x,int y)
{
if (fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->left = x;
windows[winid]->transparentboxes[btnid]->top = y;
}
}
void fegui_resizetransparentbox(int winid,int btnid,int w,int h)
{
if (fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->width = w;
windows[winid]->transparentboxes[btnid]->height = h;
}
}
void fegui_settransparentboxcaption(int winid,int btnid,char* caption)
{
if (fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->caption = caption;
}
}



void __fastcall initengine()
{
    Window1 = new TWindow();
    Window1->borderstyle = bsSingle;
    Window1->caption="Window 1";
    Window1->left = 200;
    Window1->top = 32;
    Window1->width = 320;
    Window1->height = 260;
    Window1->alphavalue = 255;
    Window1->visible = true;
}

void __fastcall uninitengine()
{
    delete Window1;
}
