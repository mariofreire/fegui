// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2013 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br
//---------------------------------------------------------------------------

#include <windows.h>
#include <gl/gl.h>
#include <dlltype.h>
#include "application.h"

#pragma hdrstop

#include "ext_unit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

extern HWND hWnd;

#ifdef _FEGUI
#define FEGUIFUNCTION DLLEXPORT
#else
#define FEGUIFUNCTION
#endif

FEGUIFUNCTION void fegui_sethwnd(void* hwnd)
{
hWnd = (HWND)hwnd;
}

FEGUIFUNCTION void fegui_appcreate()
{
appcreate();
}
FEGUIFUNCTION void fegui_appinit()
{
appinit();
}
FEGUIFUNCTION void fegui_appuninit()
{
appuninit();
}
FEGUIFUNCTION void fegui_apprun()
{
apprun();
}
FEGUIFUNCTION void fegui_appdestroy()
{
appdestroy();
}
FEGUIFUNCTION int fegui_getwindowcount(void)
{
return numwindows;
}
FEGUIFUNCTION int fegui_createwindow(void)
{
return createwindow();
}
FEGUIFUNCTION void fegui_deletewindow(int handlewindow)
{
return deletewindow(handlewindow);
}
FEGUIFUNCTION void fegui_setscreenwidth(int w)
{
setscreenwidth(w);
}
FEGUIFUNCTION void fegui_setscreenheight(int h)
{
setscreenheight(h);
}
FEGUIFUNCTION void fegui_setscreensize(int w,int h)
{
setscreenwidth(w);
setscreenheight(h);
}
FEGUIFUNCTION int fegui_getscreenwidth(void)
{
  return getscreenwidth();
}
FEGUIFUNCTION int fegui_getscreenheight(void)
{
  return getscreenheight();
}
FEGUIFUNCTION void fegui_setforegroundwindow(int handlewindow)
{
setforegroundwindow(handlewindow);
}
FEGUIFUNCTION int fegui_getforegroundwindow(void)
{
return getforegroundwindow();
}
FEGUIFUNCTION void fegui_setactivewindow(int handlewindow)
{
activewindow = handlewindow;
}
FEGUIFUNCTION int fegui_getactivewindow(void)
{
return activewindow;
}
FEGUIFUNCTION int fegui_findwindow(char* name)
{
  for (int i=0;i<numwindows;i++)
  {
      if (strcmp(windows[i]->name,name)==0) return i;
  }
  return -1;
}
FEGUIFUNCTION int fegui_windowexists(int handlewindow)
{
  for (int i=0;i<numwindows;i++)
  {
      if (windows[i]->windowid == handlewindow) return 1;
  }
  return 0;
}

#ifdef _FEGUI

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int handlewindow)
{
  for (int i=0;i<numwindows;i++)
  {
      if (windows[i]->windowid == handlewindow) return 1;
  }
  return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


#endif

unsigned int loadbitmaptexture(char* filename);
void fillrecttexture(unsigned int texture, int x0, int y0, int x1, int y1, COLORREF color, int alpha);


FEGUIFUNCTION void fegui_setwindowname(int handlewindow,char* name)
{
if (fegui_windowexists(handlewindow)) windows[handlewindow]->name = name;
}
FEGUIFUNCTION char* fegui_getwindowname(int handlewindow)
{
if (fegui_windowexists(handlewindow)) return windows[handlewindow]->name;
return NULL;
}
FEGUIFUNCTION void fegui_restorewindow(int handlewindow)
{
if (fegui_windowexists(handlewindow)) windows[handlewindow]->restore();
}
FEGUIFUNCTION void fegui_maximizewindow(int handlewindow)
{
if (fegui_windowexists(handlewindow)) windows[handlewindow]->maximize();
}
FEGUIFUNCTION void fegui_minimizewindow(int handlewindow)
{
if (fegui_windowexists(handlewindow)) windows[handlewindow]->minimize();
}
FEGUIFUNCTION void fegui_showwindow(int handlewindow)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->visible = true;
//windows[handlewindow]->show();
}
}
FEGUIFUNCTION void fegui_hidewindow(int handlewindow)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->visible = false;
//windows[handlewindow]->hide();
}
}
FEGUIFUNCTION int fegui_showmodalwindow(int handlewindow)
{
if (fegui_windowexists(handlewindow))
{
return windows[handlewindow]->showmodal();
}
return 0;
}
FEGUIFUNCTION void fegui_closewindow(int handlewindow)
{
if (fegui_windowexists(handlewindow))
{
fegui_deletewindow(handlewindow);
}
}
FEGUIFUNCTION void fegui_setwindowinstance(int handlewindow,int instance)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->instance = instance;
}
}
FEGUIFUNCTION int fegui_getwindowinstance(int handlewindow)
{
if (fegui_windowexists(handlewindow))
{
  return windows[handlewindow]->instance;
}
return -1;
}
FEGUIFUNCTION void fegui_setwindowthread(int handlewindow,int threadid)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->threadid = threadid;
}
}
FEGUIFUNCTION int fegui_getwindowthread(int handlewindow)
{
if (fegui_windowexists(handlewindow))
{
  return windows[handlewindow]->threadid;
}
return -1;
}
FEGUIFUNCTION void fegui_setwindowpid(int handlewindow,int pid)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->pid = pid;
}
}
FEGUIFUNCTION int fegui_getwindowpid(int handlewindow)
{
if (fegui_windowexists(handlewindow))
{
  return windows[handlewindow]->pid;
}
return -1;
}
FEGUIFUNCTION void fegui_windowfreeze(int handlewindow)
{
if (fegui_windowexists(handlewindow)) windows[handlewindow]->freeze();
}
FEGUIFUNCTION void fegui_setwindowcaption(int handlewindow,char* caption)
{
if (fegui_windowexists(handlewindow)) windows[handlewindow]->caption = caption;
}
FEGUIFUNCTION char* fegui_getwindowcaption(int handlewindow)
{
if (fegui_windowexists(handlewindow)) return windows[handlewindow]->caption;
return NULL;
}
FEGUIFUNCTION void fegui_setwindowcolor(int handlewindow,COLORREF color)
{
if (fegui_windowexists(handlewindow)) windows[handlewindow]->color = color;
}
FEGUIFUNCTION COLORREF fegui_getwindowcolor(int handlewindow)
{
if (fegui_windowexists(handlewindow)) return windows[handlewindow]->color;
return NULL;
}
FEGUIFUNCTION void fegui_setwindowalphavalue(int handlewindow,int alphavalue)
{
if (fegui_windowexists(handlewindow)) windows[handlewindow]->alphavalue = alphavalue;
}
FEGUIFUNCTION int fegui_getwindowalphavalue(int handlewindow)
{
if (fegui_windowexists(handlewindow)) return windows[handlewindow]->alphavalue;
return 0;
}
FEGUIFUNCTION void fegui_setwindowpos(int handlewindow,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->left = x;
windows[handlewindow]->top = y;
}
}
FEGUIFUNCTION void fegui_setwindowsize(int handlewindow,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->width = w;
windows[handlewindow]->height = h;
}
}
FEGUIFUNCTION void fegui_resizewindow(int handlewindow,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->width = w;
windows[handlewindow]->height = h;
}
}
FEGUIFUNCTION POINT fegui_getwindowpos(int handlewindow)
{
POINT p;
p.x=0;
p.y=0;
if (fegui_windowexists(handlewindow))
{
p.x = windows[handlewindow]->left;
p.y = windows[handlewindow]->top;
}
return p;
}
FEGUIFUNCTION POINT fegui_getwindowsize(int handlewindow)
{
POINT p;
p.x=0;
p.y=0;
if (fegui_windowexists(handlewindow))
{
p.x = windows[handlewindow]->width;
p.y = windows[handlewindow]->height;
}
return p;
}
FEGUIFUNCTION void fegui_setwindowstyle(int handlewindow,int style)
{
  switch(style)
  {
    case 0:
     windows[handlewindow]->borderstyle = bsNone;
    break;
    case 1:
     windows[handlewindow]->borderstyle = bsDialog;
    break;
    case 2:
     windows[handlewindow]->borderstyle = bsSingle;
    break;
    case 3:
     windows[handlewindow]->borderstyle = bsSizeable;
    break;
    case 4:
     windows[handlewindow]->borderstyle = bsToolWindow;
    break;
    case 5:
     windows[handlewindow]->borderstyle = bsSizeToolWin;
    break;
  };
}
FEGUIFUNCTION int fegui_getwindowstyle(int handlewindow)
{
int style = 0;
  switch(windows[handlewindow]->borderstyle)
  {
    case bsNone:
     style = 0;
    break;
    case bsDialog:
     style = 1;
    break;
    case bsSingle:
     style = 2;
    break;
    case bsSizeable:
     style = 3;
    break;
    case bsToolWindow:
     style = 4;
    break;
    case bsSizeToolWin:
     style = 5;
    break;
  };
  return style;
}
FEGUIFUNCTION void fegui_setwindowstate(int handlewindow,int state)
{
  switch(state)
  {
    case 0:
     windows[handlewindow]->windowstate = wsNormal;
    break;
    case 1:
     windows[handlewindow]->windowstate = wsMinimized;
    break;
    case 2:
     windows[handlewindow]->windowstate = wsMaximized;
    break;
  };
}
FEGUIFUNCTION int fegui_getwindowstate(int handlewindow)
{
int state = 0;
  switch(windows[handlewindow]->windowstate)
  {
    case wsNormal:
     state = 0;
    break;
    case wsMinimized:
     state = 1;
    break;
    case wsMaximized:
     state = 2;
    break;
  };
  return state;
}
FEGUIFUNCTION void fegui_setwindowmessageboxresult(int handlewindow,int result)
{
  windows[handlewindow]->messageboxresult = result;
}
FEGUIFUNCTION int fegui_getwindowmessageboxresult(int handlewindow)
{
  return windows[handlewindow]->messageboxresult;
}
FEGUIFUNCTION void fegui_setwindowid(int handlewindow,int id)
{
  windows[handlewindow]->id = id;
}
FEGUIFUNCTION int fegui_getwindowid(int handlewindow)
{
if (fegui_windowexists(handlewindow))
{
  return windows[handlewindow]->id;
}
return -1;
}

FEGUIFUNCTION void fegui_setmousedown_l(int x,int y)
{
 setmousedown_l(x,y);
}
FEGUIFUNCTION void fegui_setmousedown_m(int x,int y)
{
 setmousedown_m(x,y);
}
FEGUIFUNCTION void fegui_setmousedown_r(int x,int y)
{
 setmousedown_r(x,y);
}
FEGUIFUNCTION void fegui_setmousemove(int x,int y)
{
 setmousemove(x,y);
}
FEGUIFUNCTION void fegui_setmouseup(int x,int y)
{
 setmouseup(x,y);
}
FEGUIFUNCTION void fegui_setmousewheel(int key,int delta)
{
 setmousewheel(key,delta);
}
FEGUIFUNCTION void fegui_setmousepos(int x,int y)
{
 setmousepos(x,y);
}
FEGUIFUNCTION void fegui_getmousepos(int *x,int *y)
{
 getmousepos(x,y);
}
FEGUIFUNCTION void fegui_getmousestate(int *bs)
{
 getmousestate(bs);
}
FEGUIFUNCTION void fegui_getmousewheel(int *k,int *d)
{
 getmousewheel(k,d);
}
FEGUIFUNCTION int fegui_setmouseasync(int a)
{
 mousea = a;
 return mousea;
}
FEGUIFUNCTION int fegui_getmouseasync(void)
{
 return mousea;
}
FEGUIFUNCTION void fegui_setmousecursor(int cursor)
{
setmousecursor(cursor);
}
FEGUIFUNCTION int fegui_getmousecursor(void)
{
return getmousecursor();
}
FEGUIFUNCTION void fegui_setkeydown(unsigned char Key, int Shift)
{
setkeydown(Key,Shift);
}
FEGUIFUNCTION void fegui_setkeyup(unsigned char Key, int Shift)
{
setkeyup(Key,Shift);
}
FEGUIFUNCTION void fegui_setkeyshift(int Shift)
{
setkeyshift(Shift);
}
FEGUIFUNCTION int fegui_getkeychar()
{
return getkeychar();
}
FEGUIFUNCTION int fegui_getkeystate(unsigned char Key)
{
return getkeystate(Key);
}
FEGUIFUNCTION int fegui_getkeyshift()
{
return getkeyshift();
}

FEGUIFUNCTION int fegui_createbutton(int handlewindow)
{
 return createbutton(handlewindow);
}
FEGUIFUNCTION void fegui_setbuttonname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->buttons[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showbutton(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->buttons[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setbuttonpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->buttons[handlecontrol]->left = x;
windows[handlewindow]->buttons[handlecontrol]->top = y;
}
}
FEGUIFUNCTION int fegui_getbuttonwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->buttons[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_getbuttonheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->buttons[handlecontrol]->height;
}
return result;
}

FEGUIFUNCTION void fegui_resizebutton(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->buttons[handlecontrol]->width = w;
windows[handlewindow]->buttons[handlecontrol]->height = h;
}
}
FEGUIFUNCTION char* fegui_getbuttoncaption(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->buttons[handlecontrol]->caption;
}
return "";
}
FEGUIFUNCTION void fegui_setbuttoncaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->buttons[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setbuttonid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->buttons[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getbuttonid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
if (windows[handlewindow]) result = windows[handlewindow]->buttons[handlecontrol]->id;
}
return result;
}

fegui_TNotifyEvent fegui_button_onclick;

void button_onclick(TControl *sender)
{
if (fegui_button_onclick) fegui_button_onclick(sender->window->windowid,sender->controlid);
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FEGUIFUNCTION void fegui_setbuttononclick(int handlewindow,int handlecontrol,fegui_TNotifyEvent onclick)
{
 if (fegui_windowexists(handlewindow))
 {
  if (onclick)
  {
    fegui_button_onclick = onclick;
    windows[handlewindow]->buttons[handlecontrol]->onclick = button_onclick;
  }
 }
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)



FEGUIFUNCTION int fegui_createviewport(int handlewindow)
{
 return createviewport(handlewindow);
}
FEGUIFUNCTION void fegui_setviewportname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->viewports[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showviewport(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->viewports[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setviewportpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->viewports[handlecontrol]->left = x;
windows[handlewindow]->viewports[handlecontrol]->top = y;
}
}
FEGUIFUNCTION int fegui_getviewportwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->viewports[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_getviewportheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->viewports[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION int fegui_getviewportborderstyle(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->viewports[handlecontrol]->borderstyle;
}
return result;
}
FEGUIFUNCTION void fegui_setviewportborderstyle(int handlewindow,int handlecontrol,int borderstyle)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->viewports[handlecontrol]->borderstyle = borderstyle;
}
}
FEGUIFUNCTION void fegui_resizeviewport(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->viewports[handlecontrol]->width = w;
windows[handlewindow]->viewports[handlecontrol]->height = h;
}
}
FEGUIFUNCTION char* fegui_getviewportcaption(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->viewports[handlecontrol]->caption;
}
return "";
}
FEGUIFUNCTION void fegui_setviewportcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->viewports[handlecontrol]->caption = caption;
}
}

FEGUIFUNCTION void fegui_setviewportid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->viewports[handlecontrol]->id = id;
}
}

FEGUIFUNCTION int fegui_getviewportid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->viewports[handlecontrol]->id;
}
return result;
}

fegui_TRenderEvent fegui_viewport_onrender;

void viewport_onrender(TControl *sender)
{
if (fegui_viewport_onrender) fegui_viewport_onrender(sender->window->windowid,sender->controlid);
};

fegui_TNotifyEvent fegui_viewport_onclick;

void viewport_onclick(TControl *sender)
{
if (fegui_viewport_onclick) fegui_viewport_onclick(sender->window->windowid,sender->controlid);
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FEGUIFUNCTION void fegui_setviewportonclick(int handlewindow,int handlecontrol,fegui_TNotifyEvent onclick)
{
 if (fegui_windowexists(handlewindow))
 {
  if (onclick)
  {
    fegui_viewport_onclick = onclick;
    windows[handlewindow]->viewports[handlecontrol]->onclick = viewport_onclick;
  }
 }
}

FEGUIFUNCTION void fegui_setviewportonrender(int handlewindow,int handlecontrol,fegui_TRenderEvent onrender)
{
 if (fegui_windowexists(handlewindow))
 {
  if (onrender)
  {
    fegui_viewport_onrender = onrender;
    windows[handlewindow]->viewports[handlecontrol]->onrender = viewport_onrender;
  }
 }
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

FEGUIFUNCTION int fegui_createtransparentbox(int handlewindow)
{
 return createtransparentbox(handlewindow);
}
FEGUIFUNCTION void fegui_settransparentboxname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->transparentboxes[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showtransparentbox(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->transparentboxes[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_settransparentboxpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->transparentboxes[handlecontrol]->left = x;
windows[handlewindow]->transparentboxes[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizetransparentbox(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->transparentboxes[handlecontrol]->width = w;
windows[handlewindow]->transparentboxes[handlecontrol]->height = h;
}
}
FEGUIFUNCTION char* fegui_gettransparentboxcaption(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->transparentboxes[handlecontrol]->caption;
}
return "";
}
FEGUIFUNCTION void fegui_settransparentboxcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->transparentboxes[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_settransparentboxcolor(int handlewindow,int handlecontrol,COLORREF color)
{
if (fegui_windowexists(handlewindow))
{
	windows[handlewindow]->transparentboxes[handlecontrol]->color = color;
}
}
FEGUIFUNCTION void fegui_settransparentboxbackgroundalpha(int handlewindow,int handlecontrol,int backgroundalpha)
{
if (fegui_windowexists(handlewindow))
{
    windows[handlewindow]->transparentboxes[handlecontrol]->backgroundalpha = backgroundalpha;
}
}
FEGUIFUNCTION void fegui_settransparentboxalphavalue(int handlewindow,int handlecontrol,int alphavalue)
{
if (fegui_windowexists(handlewindow))
{
    windows[handlewindow]->transparentboxes[handlecontrol]->alphavalue = alphavalue;
}
}
FEGUIFUNCTION int fegui_gettransparentboxwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->transparentboxes[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_gettransparentboxheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->transparentboxes[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION int fegui_gettransparentboxborderstyle(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->transparentboxes[handlecontrol]->borderstyle;
}
return result;
}
FEGUIFUNCTION void fegui_settransparentboxborderstyle(int handlewindow,int handlecontrol,int borderstyle)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->transparentboxes[handlecontrol]->borderstyle = borderstyle;
}
}
FEGUIFUNCTION void fegui_settransparentboxid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->transparentboxes[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_gettransparentboxid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->transparentboxes[handlecontrol]->id;
}
return result;
}



fegui_TRenderEvent fegui_transparentbox_onrender;

void transparentbox_onrender(TControl *sender)
{
if (fegui_transparentbox_onrender) fegui_transparentbox_onrender(sender->window->windowid,sender->controlid);
};


#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FEGUIFUNCTION void fegui_settransparentboxonrender(int handlewindow,int handlecontrol,fegui_TRenderEvent onrender)
{
 if (fegui_windowexists(handlewindow))
 {
  if (onrender)
  {
    fegui_transparentbox_onrender = onrender;
    windows[handlewindow]->transparentboxes[handlecontrol]->onrender = transparentbox_onrender;
  }
 }
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)



FEGUIFUNCTION void fegui_messagebox(int handlewindow,char* text,char *caption,int msgtype)
{
 if (fegui_windowexists(handlewindow))
 {
  // TWindow* w = dynamic_cast <TWindow*>((TWindow*)windows[handlewindow]);
   messagebox(windows[0],text,caption,msgtype);
 }
}

FEGUIFUNCTION void fegui_setguipath(const char* path)
{
strcpy(guipath,path);
}

FEGUIFUNCTION char* fegui_getguipath(void)
{
return guipath;
}

FEGUIFUNCTION void fegui_begindrawing(void)
{
begindrawing();
}
FEGUIFUNCTION void fegui_enddrawing(void)
{
enddrawing();
}
FEGUIFUNCTION void fegui_setpixel(int x, int y, COLORREF color, int alpha)
{
setpixel(x, y, color, alpha);
}
FEGUIFUNCTION void fegui_drawcontroledge(int x,int y,int w,int h, int state, int alpha)
{
drawcontroledge(x,y,w,h,state,alpha);
}
FEGUIFUNCTION void fegui_drawcontroledgew(int x,int y,int w,int h, int state, int alpha)
{
drawcontroledgew(x,y,w,h,state,alpha);
}
FEGUIFUNCTION void fegui_subrecttess(int x0,int y0,int x1,int y1)
{
subrecttess(x0,y0,x1,y1);
}
FEGUIFUNCTION void fegui_fillrecttess(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
fillrecttess(x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION void fegui_fillrecttexture(unsigned int texture, int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
fillrecttexture(texture,x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION void fegui_fillrectpattern(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
fillrectpattern(x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION void fegui_fillrect(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
fillrect(x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION void fegui_rectangle(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
rectangle(x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION void fegui_rectangledashed(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
rectangledashed(x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION void fegui_rectangledotted(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
rectangledotted(x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION void fegui_drawline(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
drawline(x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION void fegui_drawcircle(int x0,int y0,int x1,int y1, COLORREF color, int alpha)
{
drawcircle(x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION void fegui_drawellipse(int x0,int y0,int x1,int y1, COLORREF color, int alpha)
{
drawellipse(x0,y0,x1,y1,color,alpha);
}
FEGUIFUNCTION int fegui_textwidth(char *text)
{
return textwidth(text);
}
FEGUIFUNCTION void fegui_textattr(COLORREF color,int alpha, int height, int weight)
{
textattr(color,alpha,height,weight);
}
FEGUIFUNCTION void fegui_textout(int x, int y, char *text)
{
textout(x,y,text);
}
FEGUIFUNCTION void fegui_drawgradient(int x0, int y0, int x1, int y1, COLORREF startcolor, COLORREF endcolor, int alpha,int direction)
{
drawgradient(x0,y0,x1,y1,startcolor,endcolor,alpha,direction);
}

FEGUIFUNCTION COLORREF fegui_clLightifDarkR(COLORREF c)
{
return clLightifDarkR(c);
}
FEGUIFUNCTION COLORREF fegui_clLightifDarkG(COLORREF c)
{
return clLightifDarkG(c);
}
FEGUIFUNCTION COLORREF fegui_clLightifDarkB(COLORREF c)
{
return clLightifDarkB(c);
}


FEGUIFUNCTION unsigned int fegui_loadbitmaptexture(char* filename)
{
 return loadbitmaptexture(filename);
}


extern char fatal_error_exceptionmessage[4096];

FEGUIFUNCTION void fegui_wmcrashmessage(const char* msg)
{
  strcpy(fatal_error_exceptionmessage,msg);
}


extern int fatal_error_exceptioncode;

FEGUIFUNCTION void fegui_wmcrash(unsigned long exceptioncode)
{
  if (!windowmanager_crash) fatal_error_exceptioncode = exceptioncode;
  windowmanager_crash = true;
}

FEGUIFUNCTION void fegui_drawimagedatamask(int x, int y,int w,int h,unsigned char*data,int alpha, COLORREF color, bool transparent, COLORREF transparentcolor)
{
  drawimagedatamask(x,y,w,h,data,alpha,color,transparent,transparentcolor);
}

FEGUIFUNCTION void fegui_consoletextcolor(COLORREF c)
{
  consoletextcolor(c);
}

FEGUIFUNCTION void fegui_consoletextfont(char *font)
{
  consoletextfont(font);
}

FEGUIFUNCTION void fegui_consoletextout(int x,int y,char *text)
{
  consoletextout(x,y,text);
}

FEGUIFUNCTION int fegui_consoletextwidth(char *text)
{
  return consoletextwidth(text);
}

FEGUIFUNCTION void fegui_consolecharout(int x,int y,unsigned char c)
{
  consolecharout(x,y,c);
}

FEGUIFUNCTION int fegui_consolecharwidth(void)
{
  return consolecharwidth();
}

FEGUIFUNCTION int fegui_createedit(int handlewindow)
{
 return createedit(handlewindow);
}
FEGUIFUNCTION void fegui_seteditname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->edits[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showedit(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->edits[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_seteditpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->edits[handlecontrol]->left = x;
windows[handlewindow]->edits[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizeedit(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->edits[handlecontrol]->width = w;
windows[handlewindow]->edits[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setedittext(int handlewindow,int handlecontrol,char* text)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->edits[handlecontrol]->text = text;
}
}
FEGUIFUNCTION char* fegui_getedittext(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->edits[handlecontrol]->text.c_str();
}
return "";
}
FEGUIFUNCTION void fegui_seteditid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->edits[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_geteditid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->edits[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createlabel(int handlewindow)
{
 return createlabel(handlewindow);
}
FEGUIFUNCTION void fegui_setlabelname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->labels[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showlabel(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->labels[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setlabelpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->labels[handlecontrol]->left = x;
windows[handlewindow]->labels[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizelabel(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->labels[handlecontrol]->width = w;
windows[handlewindow]->labels[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setlabelcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->labels[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION char* fegui_getlabelcaption(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->labels[handlecontrol]->caption;
}
return "";
}
FEGUIFUNCTION void fegui_setlabelid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->labels[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getlabelid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->labels[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createcheckbox(int handlewindow)
{
 return createcheckbox(handlewindow);
}
FEGUIFUNCTION void fegui_setcheckboxname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->checkboxes[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showcheckbox(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->checkboxes[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setcheckboxpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->checkboxes[handlecontrol]->left = x;
windows[handlewindow]->checkboxes[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizecheckbox(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->checkboxes[handlecontrol]->width = w;
windows[handlewindow]->checkboxes[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setcheckboxcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->checkboxes[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setcheckboxchecked(int handlewindow,int handlecontrol,int checked)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->checkboxes[handlecontrol]->checked = checked;
}
}
FEGUIFUNCTION int fegui_getcheckboxchecked(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->checkboxes[handlecontrol]->checked;
}
return result;
}
FEGUIFUNCTION void fegui_setcheckboxid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->checkboxes[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getcheckboxid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->checkboxes[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createradiobutton(int handlewindow)
{
 return createradiobutton(handlewindow);
}
FEGUIFUNCTION void fegui_setradiobuttonname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->radiobuttons[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showradiobutton(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->radiobuttons[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setradiobuttonpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->radiobuttons[handlecontrol]->left = x;
windows[handlewindow]->radiobuttons[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizeradiobutton(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->radiobuttons[handlecontrol]->width = w;
windows[handlewindow]->radiobuttons[handlecontrol]->height = h;
}
}
FEGUIFUNCTION char* fegui_getradiobuttoncaption(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->radiobuttons[handlecontrol]->caption;
}
return "";
}
FEGUIFUNCTION void fegui_setradiobuttoncaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->radiobuttons[handlecontrol]->caption = caption;
}
}


FEGUIFUNCTION void fegui_setradiobuttonchecked(int handlewindow,int handlecontrol,int checked)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->radiobuttons[handlecontrol]->checked = checked;
}
}
FEGUIFUNCTION int fegui_getradiobuttonchecked(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->radiobuttons[handlecontrol]->checked;
}
return result;
}

FEGUIFUNCTION void fegui_setradiobuttongroupindex(int handlewindow,int handlecontrol,int groupindex)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->radiobuttons[handlecontrol]->groupindex = groupindex;
}
}
FEGUIFUNCTION int fegui_getradiobuttongroupindex(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->radiobuttons[handlecontrol]->groupindex;
}
return result;
}

FEGUIFUNCTION void fegui_setradiobuttonid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->radiobuttons[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getradiobuttonid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->radiobuttons[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createlistbox(int handlewindow)
{
 return createlistbox(handlewindow);
}
FEGUIFUNCTION void fegui_setlistboxname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listboxes[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showlistbox(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listboxes[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setlistboxpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listboxes[handlecontrol]->left = x;
windows[handlewindow]->listboxes[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizelistbox(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listboxes[handlecontrol]->width = w;
windows[handlewindow]->listboxes[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setlistboxcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listboxes[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setlistboxid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listboxes[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getlistboxid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->listboxes[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION void fegui_addlistboxitem(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listboxes[handlecontrol]->additem(name);
}
}

FEGUIFUNCTION void fegui_setlistboxitemindex(int handlewindow,int handlecontrol,int index)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listboxes[handlecontrol]->itemindex = index;
}
}
FEGUIFUNCTION int fegui_getlistboxitemindex(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->listboxes[handlecontrol]->itemindex;
}
return result;
}

FEGUIFUNCTION void fegui_setlistboxitem(int handlewindow,int handlecontrol,int index,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listboxes[handlecontrol]->items[index] = name;
}
}
FEGUIFUNCTION char* fegui_getlistboxitem(int handlewindow,int handlecontrol, int index)
{
if (fegui_windowexists(handlewindow))
{
if (index < 0) return "";
if (index > windows[handlewindow]->listboxes[handlecontrol]->numitems) return "";
return (char*)windows[handlewindow]->listboxes[handlecontrol]->items[index].c_str();
}
return "";
}

FEGUIFUNCTION int fegui_createcombobox(int handlewindow)
{
 return createcombobox(handlewindow);
}
FEGUIFUNCTION void fegui_setcomboboxname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->comboboxes[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showcombobox(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->comboboxes[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setcomboboxpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->comboboxes[handlecontrol]->left = x;
windows[handlewindow]->comboboxes[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizecombobox(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->comboboxes[handlecontrol]->width = w;
windows[handlewindow]->comboboxes[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_addcomboboxitem(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->comboboxes[handlecontrol]->additem(name);
}
}

FEGUIFUNCTION void fegui_setcomboboxitemindex(int handlewindow,int handlecontrol,int index)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->comboboxes[handlecontrol]->itemindex = index;
}
}
FEGUIFUNCTION int fegui_getcomboboxitemindex(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->comboboxes[handlecontrol]->itemindex;
}
return result;
}

FEGUIFUNCTION void fegui_setcomboboxitem(int handlewindow,int handlecontrol,int index,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->comboboxes[handlecontrol]->items[index] = name;
}
}
FEGUIFUNCTION char* fegui_getcomboboxitem(int handlewindow,int handlecontrol, int index)
{
if (fegui_windowexists(handlewindow))
{
if (index < 0) return "";
if (index > windows[handlewindow]->comboboxes[handlecontrol]->numitems) return "";
return (char*)windows[handlewindow]->comboboxes[handlecontrol]->items[index].c_str();
}
return "";
}
FEGUIFUNCTION void fegui_setcomboboxtext(int handlewindow,int handlecontrol,char* text)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->comboboxes[handlecontrol]->text = text;
}
}
FEGUIFUNCTION void fegui_setcomboboxid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->comboboxes[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getcomboboxid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->comboboxes[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_creategroupbox(int handlewindow)
{
 return creategroupbox(handlewindow);
}
FEGUIFUNCTION void fegui_setgroupboxname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->groupboxes[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showgroupbox(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->groupboxes[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setgroupboxpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->groupboxes[handlecontrol]->left = x;
windows[handlewindow]->groupboxes[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizegroupbox(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->groupboxes[handlecontrol]->width = w;
windows[handlewindow]->groupboxes[handlecontrol]->height = h;
}
}
FEGUIFUNCTION char* fegui_getgroupboxcaption(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->groupboxes[handlecontrol]->caption;
}
return "";
}
FEGUIFUNCTION void fegui_setgroupboxcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->groupboxes[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setgroupboxid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->groupboxes[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getgroupboxid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->groupboxes[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createtextbox(int handlewindow)
{
 return createtextbox(handlewindow);
}
FEGUIFUNCTION void fegui_settextboxname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->textboxes[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showtextbox(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->textboxes[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_settextboxpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->textboxes[handlecontrol]->left = x;
windows[handlewindow]->textboxes[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizetextbox(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->textboxes[handlecontrol]->width = w;
windows[handlewindow]->textboxes[handlecontrol]->height = h;
}
}
FEGUIFUNCTION char* fegui_gettextboxtext(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->textboxes[handlecontrol]->text.c_str();
}
return "";
}
FEGUIFUNCTION void fegui_settextboxtext(int handlewindow,int handlecontrol,char* text)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->textboxes[handlecontrol]->text = text;
}
}
FEGUIFUNCTION void fegui_settextboxid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->textboxes[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_gettextboxid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->textboxes[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createscrollbar(int handlewindow)
{
 return createscrollbar(handlewindow);
}
FEGUIFUNCTION void fegui_setscrollbarname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->scrollbars[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showscrollbar(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->scrollbars[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setscrollbarpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->scrollbars[handlecontrol]->left = x;
windows[handlewindow]->scrollbars[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_setscrollbarvalue(int handlewindow,int handlecontrol,int value)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->scrollbars[handlecontrol]->position = value;
}
}
FEGUIFUNCTION void fegui_setscrollbarmin(int handlewindow,int handlecontrol,int min)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->scrollbars[handlecontrol]->position = min;
}
}
FEGUIFUNCTION void fegui_setscrollbarmax(int handlewindow,int handlecontrol,int max)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->scrollbars[handlecontrol]->position = max;
}
}
FEGUIFUNCTION int fegui_getscrollbarvalue(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->scrollbars[handlecontrol]->position;
}
return result;
}
FEGUIFUNCTION int fegui_getscrollbarmin(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->scrollbars[handlecontrol]->min;
}
return result;
}
FEGUIFUNCTION int fegui_getscrollbarmax(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->scrollbars[handlecontrol]->max;
}
return result;
}
FEGUIFUNCTION int fegui_getscrollbarwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->scrollbars[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_getscrollbarheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->scrollbars[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION void fegui_resizescrollbar(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->scrollbars[handlecontrol]->width = w;
windows[handlewindow]->scrollbars[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setscrollbarcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->scrollbars[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setscrollbarid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->scrollbars[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getscrollbarid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->scrollbars[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createpanel(int handlewindow)
{
 return createpanel(handlewindow);
}
FEGUIFUNCTION void fegui_setpanelname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showpanel(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setpanelpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->left = x;
windows[handlewindow]->panels[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizepanel(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->width = w;
windows[handlewindow]->panels[handlecontrol]->height = h;
}
}
FEGUIFUNCTION int fegui_getpanelwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->panels[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_getpanelheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->panels[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION int fegui_getpanelborderstyle(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->panels[handlecontrol]->borderstyle;
}
return result;
}
FEGUIFUNCTION int fegui_getpanelbevelinner(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->panels[handlecontrol]->bevelinner;
}
return result;
}
FEGUIFUNCTION int fegui_getpanelbevelouter(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->panels[handlecontrol]->bevelouter;
}
return result;
}
FEGUIFUNCTION int fegui_getpanelbevelwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->panels[handlecontrol]->bevelwidth;
}
return result;
}
FEGUIFUNCTION void fegui_setpanelborderstyle(int handlewindow,int handlecontrol,int borderstyle)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->borderstyle = borderstyle;
}
}
FEGUIFUNCTION void fegui_setpanelbevelinner(int handlewindow,int handlecontrol,int bevelinner)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->bevelinner = bevelinner;
}
}
FEGUIFUNCTION void fegui_setpanelbevelouter(int handlewindow,int handlecontrol,int bevelouter)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->bevelouter = bevelouter;
}
}
FEGUIFUNCTION void fegui_setpanelbevelwidth(int handlewindow,int handlecontrol,int bevelwidth)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->bevelwidth = bevelwidth;
}
}
FEGUIFUNCTION void fegui_setpanelcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setpanelid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->panels[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getpanelid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->panels[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createmainmenu(int handlewindow)
{
 return createmainmenu(handlewindow);
}
FEGUIFUNCTION void fegui_setmainmenuname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->mainmenues[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showmainmenu(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->mainmenues[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setmainmenupos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->mainmenues[handlecontrol]->left = x;
windows[handlewindow]->mainmenues[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizemainmenu(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->mainmenues[handlecontrol]->width = w;
windows[handlewindow]->mainmenues[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setmainmenucaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->mainmenues[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setmainmenuid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->mainmenues[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getmainmenuid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->mainmenues[handlecontrol]->id;
}
return result;
}
FEGUIFUNCTION int fegui_createmainmenuitem(int handlewindow,int handlecontrol,int id,char* caption)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
TMenu* m = windows[handlewindow]->mainmenues[handlecontrol]->additem(caption);
m->id = id;
result = m->id;
}
return result;
}
FEGUIFUNCTION int fegui_createmainmenusubitem(int handlewindow,int handlecontrol,int menuid,int id,char* caption)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
 int num_items = windows[handlewindow]->mainmenues[handlecontrol]->nummenuitems;
 int i=0;
 int m_id=0;
 for (i = 0; i < num_items; i++) {
  if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->id == menuid)
  {
	TMenuItem* m = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->additem(caption);
	m->id = id;
	m_id = m->id;
	result = m_id;
	return result;
  }
  else
  {
	int j=0;
	int num_subitems = 0;
	num_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->numitems;
	for (j = 0; j < num_subitems; j++) {
	   if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->id == menuid)
	   {
		 TMenuItem* sm0 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->additem(caption);
		 sm0->id = id;
		 m_id = sm0->id;
		 result = m_id;
		 return result;
	   }
	   else
	   {
			int k=0;
			int num_sub_subitems = 0;
			num_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->numitems;
			for (k = 0; k < num_sub_subitems; k++) {
			   if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->id == menuid)
			   {
				 TMenuItem* sm1 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->additem(caption);
				 sm1->id = id;
				 m_id = sm1->id;
				 result = m_id;
				 return result;
			   }
			   else
			   {
					int a=0;
					int num_sub_sub_subitems = 0;
					num_sub_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->numitems;
					for (a = 0; a < num_sub_sub_subitems; a++) {
					   if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->id == menuid)
					   {
						 TMenuItem* sm2 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->additem(caption);
						 sm2->id = id;
						 m_id = sm2->id;
						 result = m_id;
						 return result;
					   }
					   else
					   {
							int b=0;
							int num_sub_sub_sub_subitems = 0;
							num_sub_sub_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->numitems;
							for (b = 0; b < num_sub_sub_subitems; b++) {
								if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->id == menuid)
								{
								  TMenuItem* sm3 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->additem(caption);
								  sm3->id = id;
								  m_id = sm3->id;
								  result = m_id;
								  return result;
								}
								else
								{
										int c=0;
										int num_sub_sub_sub_sub_subitems = 0;
										num_sub_sub_sub_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->numitems;
										for (c = 0; c < num_sub_sub_sub_sub_subitems; c++) {
											if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->items[c]->id == menuid)
											{
											   TMenuItem* sm4 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->items[c]->additem(caption);
											   sm4->id = id;
											   m_id = sm4->id;
											   result = m_id;
											   return result;
											}
										}
								}
							}
					   }
					}
			   }
			}
	   }
	}
  }
 }
}
return result;
}

FEGUIFUNCTION int fegui_getmainmenuitemid(int handlewindow,int handlecontrol,int menuid)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
 int num_items = windows[handlewindow]->mainmenues[handlecontrol]->nummenuitems;
 int i=0;
 int m_id=0;
 for (i = 0; i < num_items; i++) {
  if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->id == menuid)
  {
	TMenu* m = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i];
	m_id = m->id;
	result = m_id;
	return result;
  }
  else
  {
	int j=0;
	int num_subitems = 0;
	num_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->numitems;
	for (j = 0; j < num_subitems; j++) {
	   if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->id == menuid)
	   {
		 TMenuItem* sm0 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j];
		 m_id = sm0->id;
		 result = m_id;
		 return result;
	   }
	   else
	   {
			int k=0;
			int num_sub_subitems = 0;
			num_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->numitems;
			for (k = 0; k < num_sub_subitems; k++) {
			   if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->id == menuid)
			   {
				 TMenuItem* sm1 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k];
				 m_id = sm1->id;
				 result = m_id;
				 return result;
			   }
			   else
			   {
					int a=0;
					int num_sub_sub_subitems = 0;
					num_sub_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->numitems;
					for (a = 0; a < num_sub_sub_subitems; a++) {
					   if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->id == menuid)
					   {
						 TMenuItem* sm2 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a];
						 m_id = sm2->id;
						 result = m_id;
						 return result;
					   }
					   else
					   {
							int b=0;
							int num_sub_sub_sub_subitems = 0;
							num_sub_sub_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->numitems;
							for (b = 0; b < num_sub_sub_subitems; b++) {
								if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->id == menuid)
								{
								  TMenuItem* sm3 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b];
								  m_id = sm3->id;
								  result = m_id;
								  return result;
								}
								else
								{
										int c=0;
										int num_sub_sub_sub_sub_subitems = 0;
										num_sub_sub_sub_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->numitems;
										for (c = 0; c < num_sub_sub_sub_sub_subitems; c++) {
											if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->items[c]->id == menuid)
											{
											   TMenuItem* sm4 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->items[c];
											   m_id = sm4->id;
											   result = m_id;
											   return result;
											}
										}
								}
							}
					   }
					}
			   }
			}
	   }
	}
  }
 }
}
return result;
}

FEGUIFUNCTION int fegui_createspeedbutton(int handlewindow)
{
 return createspeedbutton(handlewindow);
}
FEGUIFUNCTION void fegui_setspeedbuttonname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->speedbuttons[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showspeedbutton(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->speedbuttons[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setspeedbuttonpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->speedbuttons[handlecontrol]->left = x;
windows[handlewindow]->speedbuttons[handlecontrol]->top = y;
}
}
FEGUIFUNCTION int fegui_getspeedbuttonwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->speedbuttons[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_getspeedbuttonheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->speedbuttons[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION void fegui_resizespeedbutton(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->speedbuttons[handlecontrol]->width = w;
windows[handlewindow]->speedbuttons[handlecontrol]->height = h;
}
}
FEGUIFUNCTION char* fegui_getspeedbuttoncaption(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->speedbuttons[handlecontrol]->caption;
}
return "";
}
FEGUIFUNCTION void fegui_setspeedbuttoncaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->speedbuttons[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setspeedbuttonicon(int handlewindow,int handlecontrol,char* iconfilename)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->speedbuttons[handlecontrol]->loadicon(iconfilename);
}
}
FEGUIFUNCTION void fegui_setspeedbuttonid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->speedbuttons[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getspeedbuttonid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->speedbuttons[handlecontrol]->id;
}
return result;
}

fegui_TNotifyEvent fegui_speedbutton_onclick;

void speedbutton_onclick(TControl *sender)
{
if (fegui_speedbutton_onclick) fegui_speedbutton_onclick(sender->window->windowid,sender->controlid);
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FEGUIFUNCTION void fegui_setspeedbuttononclick(int handlewindow,int handlecontrol,fegui_TNotifyEvent onclick)
{
 if (fegui_windowexists(handlewindow))
 {
  if (onclick)
  {
    fegui_speedbutton_onclick = onclick;
    windows[handlewindow]->speedbuttons[handlecontrol]->onclick = speedbutton_onclick;
  }
 }
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


FEGUIFUNCTION int fegui_createbevel(int handlewindow)
{
 return createbevel(handlewindow);
}
FEGUIFUNCTION void fegui_setbevelname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showbevel(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setbevelpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->left = x;
windows[handlewindow]->bevels[handlecontrol]->top = y;
}
}
FEGUIFUNCTION int fegui_getbevelwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->bevels[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_getbevelheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->bevels[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION int fegui_getbevelborderstyle(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->bevels[handlecontrol]->borderstyle;
}
return result;
}
FEGUIFUNCTION int fegui_getbevelbevelinner(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->bevels[handlecontrol]->bevelinner;
}
return result;
}
FEGUIFUNCTION int fegui_getbevelbevelouter(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->bevels[handlecontrol]->bevelouter;
}
return result;
}
FEGUIFUNCTION int fegui_getbevelbevelwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->bevels[handlecontrol]->bevelwidth;
}
return result;
}
FEGUIFUNCTION void fegui_setbevelborderstyle(int handlewindow,int handlecontrol,int borderstyle)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->borderstyle = borderstyle;
}
}
FEGUIFUNCTION void fegui_setbevelbevelinner(int handlewindow,int handlecontrol,int bevelinner)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->bevelinner = bevelinner;
}
}
FEGUIFUNCTION void fegui_setbevelbevelouter(int handlewindow,int handlecontrol,int bevelouter)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->bevelouter = bevelouter;
}
}
FEGUIFUNCTION void fegui_setbevelbevelwidth(int handlewindow,int handlecontrol,int bevelwidth)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->bevelwidth = bevelwidth;
}
}

FEGUIFUNCTION void fegui_resizebevel(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->width = w;
windows[handlewindow]->bevels[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setbevelcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setbevelid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->bevels[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getbevelid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->bevels[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createimage(int handlewindow)
{
 return createimage(handlewindow);
}
FEGUIFUNCTION void fegui_setimagename(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->images[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showimage(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->images[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setimagefile(int handlewindow,int handlecontrol,char* imagefilename)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->images[handlecontrol]->picture->load(imagefilename);
}
}
FEGUIFUNCTION void fegui_setimagepos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->images[handlecontrol]->left = x;
windows[handlewindow]->images[handlecontrol]->top = y;
}
}
FEGUIFUNCTION int fegui_getimagewidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->images[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_getimageheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->images[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION void fegui_resizeimage(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->images[handlecontrol]->width = w;
windows[handlewindow]->images[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setimagecaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->images[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setimageid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->images[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getimageid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->images[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createglyphbutton(int handlewindow)
{
 return createglyphbutton(handlewindow);
}
FEGUIFUNCTION void fegui_setglyphbuttonname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->glyphbuttons[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showglyphbutton(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->glyphbuttons[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setglyphbuttonimagefile(int handlewindow,int handlecontrol,int buttonstate,char* imagefilename)
{
if (fegui_windowexists(handlewindow))
{
 switch(buttonstate)
 {
  case 0:
   windows[handlewindow]->glyphbuttons[handlecontrol]->btnNormal->load(imagefilename);
  break;
  case 1:
   windows[handlewindow]->glyphbuttons[handlecontrol]->btnDown->load(imagefilename);
  break;
  case 2:
   windows[handlewindow]->glyphbuttons[handlecontrol]->btnOver->load(imagefilename);
  break;
  case 3:
   windows[handlewindow]->glyphbuttons[handlecontrol]->btnUp->load(imagefilename);
  break;
  case 4:
   windows[handlewindow]->glyphbuttons[handlecontrol]->btnOut->load(imagefilename);
  break;
 }
}
}
FEGUIFUNCTION void fegui_setglyphbuttonpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->glyphbuttons[handlecontrol]->left = x;
windows[handlewindow]->glyphbuttons[handlecontrol]->top = y;
}
}
FEGUIFUNCTION int fegui_getglyphbuttonwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->glyphbuttons[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_getglyphbuttonheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->glyphbuttons[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION void fegui_resizeglyphbutton(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->glyphbuttons[handlecontrol]->width = w;
windows[handlewindow]->glyphbuttons[handlecontrol]->height = h;
}
}
FEGUIFUNCTION char* fegui_getglyphbuttoncaption(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->glyphbuttons[handlecontrol]->caption;
}
return "";
}
FEGUIFUNCTION void fegui_setglyphbuttoncaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->glyphbuttons[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setglyphbuttonid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->glyphbuttons[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getglyphbuttonid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->glyphbuttons[handlecontrol]->id;
}
return result;
}

fegui_TNotifyEvent fegui_glyphbutton_onclick;

void glyphbutton_onclick(TControl *sender)
{
if (fegui_glyphbutton_onclick) fegui_glyphbutton_onclick(sender->window->windowid,sender->controlid);
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FEGUIFUNCTION void fegui_setglyphbuttononclick(int handlewindow,int handlecontrol,fegui_TNotifyEvent onclick)
{
 if (fegui_windowexists(handlewindow))
 {
  if (onclick)
  {
    fegui_glyphbutton_onclick = onclick;
    windows[handlewindow]->glyphbuttons[handlecontrol]->onclick = glyphbutton_onclick;
  }
 }
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


FEGUIFUNCTION int fegui_createshape(int handlewindow)
{
 return createshape(handlewindow);
}
FEGUIFUNCTION void fegui_setshapename(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->shapes[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showshape(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->shapes[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setshapepos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->shapes[handlecontrol]->left = x;
windows[handlewindow]->shapes[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizeshape(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->shapes[handlecontrol]->width = w;
windows[handlewindow]->shapes[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setshapecaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->shapes[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setshapeid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->shapes[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getshapeid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->shapes[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createupdown(int handlewindow)
{
 return createupdown(handlewindow);
}
FEGUIFUNCTION void fegui_setupdownname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->updowns[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showupdown(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->updowns[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setupdownpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->updowns[handlecontrol]->left = x;
windows[handlewindow]->updowns[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizeupdown(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->updowns[handlecontrol]->width = w;
windows[handlewindow]->updowns[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setupdowncaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->updowns[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setupdownid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->updowns[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getupdownid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->updowns[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createdockbar(int handlewindow)
{
 return createdockbar(handlewindow);
}
FEGUIFUNCTION void fegui_setdockbarname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->dockbars[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showdockbar(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->dockbars[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setdockbarpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->dockbars[handlecontrol]->left = x;
windows[handlewindow]->dockbars[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizedockbar(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->dockbars[handlecontrol]->width = w;
windows[handlewindow]->dockbars[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setdockbarcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->dockbars[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setdockbarid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->dockbars[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getdockbarid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->dockbars[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createimagelist(int handlewindow)
{
 return createimagelist(handlewindow);
}
FEGUIFUNCTION void fegui_setimagelistname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->imagelists[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_resizeimagelist(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->imagelists[handlecontrol]->width = w;
windows[handlewindow]->imagelists[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setimagelistid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->imagelists[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getimagelistid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->imagelists[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createlistview(int handlewindow)
{
 return createlistview(handlewindow);
}
FEGUIFUNCTION void fegui_setlistviewname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listviews[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showlistview(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listviews[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setlistviewpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listviews[handlecontrol]->left = x;
windows[handlewindow]->listviews[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizelistview(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listviews[handlecontrol]->width = w;
windows[handlewindow]->listviews[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setlistviewcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listviews[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setlistviewid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->listviews[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getlistviewid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->listviews[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createtoolbar(int handlewindow)
{
 return createtoolbar(handlewindow);
}
FEGUIFUNCTION void fegui_settoolbarname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbars[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showtoolbar(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbars[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_settoolbarpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbars[handlecontrol]->left = x;
windows[handlewindow]->toolbars[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizetoolbar(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbars[handlecontrol]->width = w;
windows[handlewindow]->toolbars[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_settoolbarcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbars[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_settoolbarid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbars[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_gettoolbarid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->toolbars[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createtoolbutton(int handlewindow)
{
 return createtoolbutton(handlewindow);
}
FEGUIFUNCTION void fegui_settoolbuttonname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbuttons[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showtoolbutton(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbuttons[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_settoolbuttonpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbuttons[handlecontrol]->left = x;
windows[handlewindow]->toolbuttons[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizetoolbutton(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbuttons[handlecontrol]->width = w;
windows[handlewindow]->toolbuttons[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_settoolbuttoncaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbuttons[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_settoolbuttonid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->toolbuttons[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_gettoolbuttonid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->toolbuttons[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createprogressbar(int handlewindow)
{
 return createprogressbar(handlewindow);
}

FEGUIFUNCTION void fegui_setprogressbarname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->progressbars[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showprogressbar(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->progressbars[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setprogressbarpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->progressbars[handlecontrol]->left = x;
windows[handlewindow]->progressbars[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_setprogressbarvalue(int handlewindow,int handlecontrol,int value)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->progressbars[handlecontrol]->position = value;
}
}
FEGUIFUNCTION void fegui_setprogressbarmin(int handlewindow,int handlecontrol,int min)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->progressbars[handlecontrol]->position = min;
}
}
FEGUIFUNCTION void fegui_setprogressbarmax(int handlewindow,int handlecontrol,int max)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->progressbars[handlecontrol]->position = max;
}
}
FEGUIFUNCTION int fegui_getprogressbarvalue(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->progressbars[handlecontrol]->position;
}
return result;
}
FEGUIFUNCTION int fegui_getprogressbarmin(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->progressbars[handlecontrol]->min;
}
return result;
}
FEGUIFUNCTION int fegui_getprogressbarmax(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->progressbars[handlecontrol]->max;
}
return result;
}
FEGUIFUNCTION int fegui_getprogressbarwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->progressbars[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_getprogressbarheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->progressbars[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION void fegui_resizeprogressbar(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->progressbars[handlecontrol]->width = w;
windows[handlewindow]->progressbars[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setprogressbarcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->progressbars[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setprogressbarid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->progressbars[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getprogressbarid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->progressbars[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createtrackbar(int handlewindow)
{
 return createtrackbar(handlewindow);
}

FEGUIFUNCTION void fegui_settrackbarname(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->trackbars[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showtrackbar(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->trackbars[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_settrackbarpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->trackbars[handlecontrol]->left = x;
windows[handlewindow]->trackbars[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_settrackbarvalue(int handlewindow,int handlecontrol,int value)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->trackbars[handlecontrol]->position = value;
}
}
FEGUIFUNCTION void fegui_settrackbarmin(int handlewindow,int handlecontrol,int min)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->trackbars[handlecontrol]->position = min;
}
}
FEGUIFUNCTION void fegui_settrackbarmax(int handlewindow,int handlecontrol,int max)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->trackbars[handlecontrol]->position = max;
}
}
FEGUIFUNCTION int fegui_gettrackbarvalue(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->trackbars[handlecontrol]->position;
}
return result;
}
FEGUIFUNCTION int fegui_gettrackbarmin(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->trackbars[handlecontrol]->min;
}
return result;
}
FEGUIFUNCTION int fegui_gettrackbarmax(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->trackbars[handlecontrol]->max;
}
return result;
}
FEGUIFUNCTION int fegui_gettrackbarwidth(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->trackbars[handlecontrol]->width;
}
return result;
}
FEGUIFUNCTION int fegui_gettrackbarheight(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->trackbars[handlecontrol]->height;
}
return result;
}
FEGUIFUNCTION void fegui_resizetrackbar(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->trackbars[handlecontrol]->width = w;
windows[handlewindow]->trackbars[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_settrackbarcaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->trackbars[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_settrackbarid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->trackbars[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_gettrackbarid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->trackbars[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION int fegui_createvideoplayer(int handlewindow)
{
 return createvideoplayer(handlewindow);
}
FEGUIFUNCTION void fegui_setvideoplayername(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showvideoplayer(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setvideoplayerpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->left = x;
windows[handlewindow]->videoplayers[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizevideoplayer(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->width = w;
windows[handlewindow]->videoplayers[handlecontrol]->height = h;
}
}
FEGUIFUNCTION void fegui_setvideoplayercaption(int handlewindow,int handlecontrol,char* caption)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->caption = caption;
}
}
FEGUIFUNCTION void fegui_setvideoplayerid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getvideoplayerid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->id;
}
return result;
}
FEGUIFUNCTION void fegui_setvideoplayerfilename(int handlewindow,int handlecontrol,char* filename)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->filename = filename;
}
}
FEGUIFUNCTION void fegui_videoplayer_play(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->play();
}
}
FEGUIFUNCTION void fegui_videoplayer_stop(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->stop();
}
}
FEGUIFUNCTION void fegui_videoplayer_resume(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->resume();
}
}
FEGUIFUNCTION void fegui_videoplayer_open(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->open();
}
}
FEGUIFUNCTION void fegui_videoplayer_close(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->videoplayers[handlecontrol]->close();
}
}
FEGUIFUNCTION char* fegui_getvideoplayerfilename(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
return (char*)windows[handlewindow]->videoplayers[handlecontrol]->filename;
}
return "";
}
FEGUIFUNCTION int fegui_getvideoplayerisopened(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->isopenned;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayerisplaying(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->isplaying;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayerhasaudio(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->hasaudio;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayerhasvideo(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->hasvideo;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayerhasbink(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->hasbink;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayerstartframe(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->startframe;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayertotalframe(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->totalframe;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayerframerate(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->framerate;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayeraudiorate(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->audiorate;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayerposition(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->position;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayertextureid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->textureid;
}
return result;
}
FEGUIFUNCTION int fegui_getvideoplayervideonum(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->videoplayers[handlecontrol]->videonum;
}
return result;
}


FEGUIFUNCTION int fegui_createwebbrowser(int handlewindow)
{
 return createwebbrowser(handlewindow);
}
FEGUIFUNCTION void fegui_setwebbrowsername(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->webbrowsers[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_showwebbrowser(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->webbrowsers[handlecontrol]->visible = true;
}
}
FEGUIFUNCTION void fegui_setwebbrowserpos(int handlewindow,int handlecontrol,int x,int y)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->webbrowsers[handlecontrol]->left = x;
windows[handlewindow]->webbrowsers[handlecontrol]->top = y;
}
}
FEGUIFUNCTION void fegui_resizewebbrowser(int handlewindow,int handlecontrol,int w,int h)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->webbrowsers[handlecontrol]->width = w;
windows[handlewindow]->webbrowsers[handlecontrol]->height = h;
}
}
FEGUIFUNCTION char* fegui_getwebbrowserurl(int handlewindow,int handlecontrol)
{
if (fegui_windowexists(handlewindow))
{
  return (char*)windows[handlewindow]->webbrowsers[handlecontrol]->url.c_str();
}
return "";
}
FEGUIFUNCTION void fegui_setwebbrowserurl(int handlewindow,int handlecontrol,char* url)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->webbrowsers[handlecontrol]->url = url;
}
}
FEGUIFUNCTION void fegui_setwebbrowserid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->webbrowsers[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_getwebbrowserid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->webbrowsers[handlecontrol]->id;
}
return result;
}

FEGUIFUNCTION void fegui_webkit_keydown(unsigned char key)
{
   webkit_keydown(key);
}

FEGUIFUNCTION void fegui_webkit_keyup(unsigned char key)
{
   webkit_keyup(key);
}

FEGUIFUNCTION int fegui_createtimer(int handlewindow)
{
 return createtimer(handlewindow);
}
FEGUIFUNCTION void fegui_settimername(int handlewindow,int handlecontrol,char* name)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->timers[handlecontrol]->name = name;
}
}
FEGUIFUNCTION void fegui_settimerid(int handlewindow,int handlecontrol,int id)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->timers[handlecontrol]->id = id;
}
}
FEGUIFUNCTION int fegui_gettimerid(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->timers[handlecontrol]->id;
}
return result;
}
FEGUIFUNCTION void fegui_settimerinterval(int handlewindow,int handlecontrol,int interval)
{
if (fegui_windowexists(handlewindow))
{
windows[handlewindow]->timers[handlecontrol]->interval = interval;
}
}
FEGUIFUNCTION int fegui_gettimerinterval(int handlewindow,int handlecontrol)
{
int result = 0;
if (fegui_windowexists(handlewindow))
{
result = windows[handlewindow]->timers[handlecontrol]->interval;
}
return result;
}


fegui_TTimerEvent fegui_timer_ontimer;

void timer_ontimer(TComponent *sender)
{
if (fegui_timer_ontimer)
{
  TTimer* timer_sender = dynamic_cast <TTimer*>((TTimer*)sender);
  fegui_timer_ontimer(timer_sender->window->windowid,timer_sender->componentid);
}
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FEGUIFUNCTION void fegui_settimerontimer(int handlewindow,int handlecontrol,fegui_TTimerEvent ontimer)
{
 if (fegui_windowexists(handlewindow))
 {
  if (ontimer)
  {
    fegui_timer_ontimer = ontimer;
    windows[handlewindow]->timers[handlecontrol]->ontimer = timer_ontimer;
  }
 }
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)



fegui_TMenuEvent fegui_menuitem_onclick;

void menuitem_onclick(TControl *sender)
{
 if (fegui_menuitem_onclick)
 {
   TMenu* menu_sender = dynamic_cast <TMenu*>((TMenu*)sender);
   fegui_menuitem_onclick(sender->window->windowid,sender->controlid,menu_sender->id);
 }
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FEGUIFUNCTION void fegui_setmenuitemonclick(int handlewindow,int handlecontrol,int handlemenuitem,fegui_TMenuEvent onclick)
{
 if (fegui_windowexists(handlewindow))
 {
  if (onclick)
  {
   int i=0;
   for (i = 0; i < windows[handlewindow]->mainmenues[handlecontrol]->nummenuitems; i++) {
	if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->id == handlemenuitem) {
		fegui_menuitem_onclick = onclick;
		windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->onclick = menuitem_onclick;
	}
   }
  }
 }
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)



fegui_TMenuEvent fegui_menusubitem_onclick;

void menusubitem_onclick(TWinControl *sender)
{
 if (fegui_menusubitem_onclick)
 {
   int menu_id = submenuitemclickid;
   TMenu* menu_sender = dynamic_cast <TMenu*>((TMenu*)sender);
   fegui_menusubitem_onclick(sender->window->windowid,sender->controlid,menu_id);
   submenuitemclickid = -1;
 }
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FEGUIFUNCTION void fegui_setmenusubitemonclick(int handlewindow,int handlecontrol,int handlemenuitem,int handlemenusubitem,fegui_TMenuEvent onclick)
{
 if (fegui_windowexists(handlewindow))
 {
  if (onclick)
  {
   int i=0;
   for (i = 0; i < windows[handlewindow]->mainmenues[handlecontrol]->nummenuitems; i++) {
	if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->id == handlemenuitem) {
	int j=0;
	int num_subitems = 0;
	num_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->numitems;
	for (j = 0; j < num_subitems; j++) {
	   if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->id == handlemenusubitem)
	   {
		 TMenuItem* sm0 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j];
		 fegui_menusubitem_onclick = onclick;
		 sm0->onclick = menusubitem_onclick;
	   }
	   else
	   {
			int k=0;
			int num_sub_subitems = 0;
			num_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->numitems;
			for (k = 0; k < num_sub_subitems; k++) {
			   if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->id == handlemenusubitem)
			   {
				 TMenuItem* sm1 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k];
				 fegui_menusubitem_onclick = onclick;
				 sm1->onclick = menusubitem_onclick;
			   }
			   else
			   {
					int a=0;
					int num_sub_sub_subitems = 0;
					num_sub_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->numitems;
					for (a = 0; a < num_sub_sub_subitems; a++) {
					   if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->id == handlemenusubitem)
					   {
						 TMenuItem* sm2 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a];
						 fegui_menusubitem_onclick = onclick;
						 sm2->onclick = menusubitem_onclick;
					   }
					   else
					   {
							int b=0;
							int num_sub_sub_sub_subitems = 0;
							num_sub_sub_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->numitems;
							for (b = 0; b < num_sub_sub_subitems; b++) {
								if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->id == handlemenusubitem)
								{
								  TMenuItem* sm3 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b];
								  fegui_menusubitem_onclick = onclick;
								  sm3->onclick = menusubitem_onclick;
								}
								else
								{
										int c=0;
										int num_sub_sub_sub_sub_subitems = 0;
										num_sub_sub_sub_sub_subitems = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->numitems;
										for (c = 0; c < num_sub_sub_sub_sub_subitems; c++) {
											if (windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->items[c]->id == handlemenusubitem)
											{
											   TMenuItem* sm4 = windows[handlewindow]->mainmenues[handlecontrol]->menuitems[i]->menu->items[j]->items[k]->items[a]->items[b]->items[c];
											   fegui_menusubitem_onclick = onclick;
											   sm4->onclick = menusubitem_onclick;
											}
										}
								}
							}
					   }
					}
			   }
			}
	   }
	 }
	}
   }
  }
 }
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

