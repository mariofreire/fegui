// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include <windows.h>
#include "dlltype.h"
#include "application.h"


#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

DLLEXPORT void _fegui_appcreate()
{
appcreate();
}
DLLEXPORT void _fegui_appinit()
{
appinit();
}
DLLEXPORT void _fegui_appuninit()
{
appuninit();
}
DLLEXPORT void _fegui_apprun()
{
apprun();
}
DLLEXPORT void _fegui_appdestroy()
{
appdestroy();
}
DLLEXPORT int _fegui_createwindow(void)
{
return createwindow();
}
DLLEXPORT void _fegui_deletewindow(int winid)
{
return deletewindow(winid);
}
DLLEXPORT void _fegui_setscreenwidth(int w)
{
setscreenwidth(w);
}
DLLEXPORT void _fegui_setscreenheight(int h)
{
setscreenheight(h);
}
DLLEXPORT void _fegui_setscreensize(int w,int h)
{
setscreenwidth(w);
setscreenheight(h);
}
DLLEXPORT void _fegui_setforegroundwindow(int winid)
{
setforegroundwindow(winid);
}
DLLEXPORT int _fegui_getforegroundwindow(void)
{
return getforegroundwindow();
}
DLLEXPORT void _fegui_setactivewindow(int winid)
{
activewindow = winid;
}
DLLEXPORT int _fegui_getactivewindow(void)
{
return activewindow;
}
DLLEXPORT int _fegui_findwindow(char* name)
{
  for (int i=0;i<numwindows;i++)
  {
      if (strcmp(windows[i]->name,name)==0) return i;
  }
  return -1;
}
DLLEXPORT int _fegui_windowexists(int winid)
{
  for (int i=0;i<numwindows;i++)
  {
      if (windows[i]->windowid == winid) return 1;
  }
  return 0;
}
DLLEXPORT void _fegui_setwindowname(int winid,char* name)
{
if (_fegui_windowexists(winid)) windows[winid]->name = name;
}
DLLEXPORT char* _fegui_getwindowname(int winid)
{
if (_fegui_windowexists(winid)) return windows[winid]->name;
return NULL;
}
DLLEXPORT void _fegui_restorewindow(int winid)
{
if (_fegui_windowexists(winid)) windows[winid]->restore();
}
DLLEXPORT void _fegui_maximizewindow(int winid)
{
if (_fegui_windowexists(winid)) windows[winid]->maximize();
}
DLLEXPORT void _fegui_minimizewindow(int winid)
{
if (_fegui_windowexists(winid)) windows[winid]->minimize();
}
DLLEXPORT void _fegui_showwindow(int winid)
{
if (_fegui_windowexists(winid))
{
windows[winid]->visible = true;
//windows[winid]->show();
}
}
DLLEXPORT int _fegui_showmodalwindow(int winid)
{
if (_fegui_windowexists(winid))
{
return windows[winid]->showmodal();
}
return 0;
}
DLLEXPORT void _fegui_windowfreeze(int winid)
{
if (_fegui_windowexists(winid)) windows[winid]->freeze();
}
DLLEXPORT void _fegui_setwindowcaption(int winid,char* caption)
{
if (_fegui_windowexists(winid)) windows[winid]->caption = caption;
}
DLLEXPORT void _fegui_setwindowpos(int winid,int x,int y)
{
if (_fegui_windowexists(winid)) 
{
windows[winid]->left = x;
windows[winid]->top = y;
}
}
DLLEXPORT void _fegui_setwindowsize(int winid,int w,int h)
{
if (_fegui_windowexists(winid)) 
{
windows[winid]->width = w;
windows[winid]->height = h;
}
}
DLLEXPORT void _fegui_resizewindow(int winid,int w,int h)
{
if (_fegui_windowexists(winid)) 
{
windows[winid]->width = w;
windows[winid]->height = h;
}
}

DLLEXPORT void _fegui_setmousedown_l(int x,int y)
{
 setmousedown_l(x,y);
}
DLLEXPORT void _fegui_setmousedown_m(int x,int y)
{
 setmousedown_m(x,y);
}
DLLEXPORT void _fegui_setmousedown_r(int x,int y)
{
 setmousedown_r(x,y);
}
DLLEXPORT void _fegui_setmousemove(int x,int y)
{
 setmousemove(x,y);
}
DLLEXPORT void _fegui_setmouseup(int x,int y)
{
 setmouseup(x,y);
}
DLLEXPORT void _fegui_setmousewheel(int key,int delta)
{
 setmousewheel(key,delta);
}
DLLEXPORT void _fegui_setmousepos(int x,int y)
{
 setmousepos(x,y);
}
DLLEXPORT void _fegui_getmousepos(int *x,int *y)
{
 getmousepos(x,y);
}
DLLEXPORT void _fegui_getmousestate(int *bs)
{
 getmousestate(bs);
}
DLLEXPORT void _fegui_getmousewheel(int *k,int *d)
{
 getmousewheel(k,d);
}
DLLEXPORT int _fegui_setmouseasync(int a)
{
 mousea = a;
}
DLLEXPORT int _fegui_getmouseasync(void)
{
 return mousea;
}
DLLEXPORT int _fegui_createbutton(int winid)
{
 return createbutton(winid);
}
DLLEXPORT void _fegui_setbuttonname(int winid,int btnid,char* name)
{
if (_fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->caption = name;
}
}
DLLEXPORT void _fegui_showbutton(int winid,int btnid)
{
if (_fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->visible = true;
}
}
DLLEXPORT void _fegui_setbuttonpos(int winid,int btnid,int x,int y)
{
if (_fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->left = x;
windows[winid]->buttons[btnid]->top = y;
}
}
DLLEXPORT void _fegui_resizebutton(int winid,int btnid,int w,int h)
{
if (_fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->width = w;
windows[winid]->buttons[btnid]->height = h;
}
}
DLLEXPORT void _fegui_setbuttoncaption(int winid,int btnid,char* caption)
{
if (_fegui_windowexists(winid))
{
windows[winid]->buttons[btnid]->caption = caption;
}
}
DLLEXPORT int _fegui_createviewport(int winid)
{
 return createviewport(winid);
}
DLLEXPORT void _fegui_setviewportname(int winid,int btnid,char* name)
{
if (_fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->caption = name;
}
}
DLLEXPORT void _fegui_showviewport(int winid,int btnid)
{
if (_fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->visible = true;
}
}
DLLEXPORT void _fegui_setviewportpos(int winid,int btnid,int x,int y)
{
if (_fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->left = x;
windows[winid]->viewports[btnid]->top = y;
}
}
DLLEXPORT void _fegui_resizeviewport(int winid,int btnid,int w,int h)
{
if (_fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->width = w;
windows[winid]->viewports[btnid]->height = h;
}
}
DLLEXPORT void _fegui_setviewportcaption(int winid,int btnid,char* caption)
{
if (_fegui_windowexists(winid))
{
windows[winid]->viewports[btnid]->caption = caption;
}
}

DLLEXPORT void _fegui_setviewportonrender(int winid,int viewportid,TFEGUI_RenderEvent onrender)
{
 if (_fegui_windowexists(winid))
 {
  if (onrender)
  {
    windows[winid]->viewports[viewportid]->onrender = onrender;
  }
 }
}

DLLEXPORT int _fegui_createtransparentbox(int winid)
{
 return createtransparentbox(winid);
}
DLLEXPORT void _fegui_settransparentboxname(int winid,int btnid,char* name)
{
if (_fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->caption = name;
}
}
DLLEXPORT void _fegui_showtransparentbox(int winid,int btnid)
{
if (_fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->visible = true;
}
}
DLLEXPORT void _fegui_settransparentboxpos(int winid,int btnid,int x,int y)
{
if (_fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->left = x;
windows[winid]->transparentboxes[btnid]->top = y;
}
}
DLLEXPORT void _fegui_resizetransparentbox(int winid,int btnid,int w,int h)
{
if (_fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->width = w;
windows[winid]->transparentboxes[btnid]->height = h;
}
}
DLLEXPORT void _fegui_settransparentboxcaption(int winid,int btnid,char* caption)
{
if (_fegui_windowexists(winid))
{
windows[winid]->transparentboxes[btnid]->caption = caption;
}
}


/*
typedef struct
{
TButton* instance;
TFEGUI_NotifyEvent onclick;
} btnclickevent_t;

btnclickevent_t btnclickevent[256][256];
int hwndbtnwin=0;
 
void btnonclick(TControl* sender)
{
    TButton* btn = dynamic_cast <TButton*>((TButton*)sender);
    TWindow* wnd = dynamic_cast <TWindow*>((TWindow*)btn->window);
   // if (btn->tag != wnd->windowid) btn->tag = wnd->windowid;
    int hwnd=hwndbtnwin;
    
  //  hwnd = btn->tag;
    btnclickevent[hwnd][btn->controlid].onclick(btn->handleid);
}

DLLEXPORT void _fegui_setbuttononclick(int winid,int btnid,TFEGUI_NotifyEvent onclick)
{
 if (_fegui_windowexists(winid))
 {
  if (onclick)
  {
    hwndbtnwin = windows[winid]->windowid;
    windows[winid]->buttons[btnid]->window->windowid = winid;
    btnclickevent[winid][btnid].onclick = onclick;
    windows[winid]->buttons[btnid]->onclick = btnonclick;
  }
 }
}
*/

DLLEXPORT void _fegui_setbuttononclick(int winid,int btnid,TFEGUI_NotifyEvent onclick)
{
 if (_fegui_windowexists(winid))
 {
  if (onclick)
  {
    windows[winid]->buttons[btnid]->onclick = onclick;
  }
 }
}

DLLEXPORT void _fegui_messagebox(int hwnd,char* text,char *caption,int msgtype)
{
 if (_fegui_windowexists(hwnd))
 {
  // TWindow* w = dynamic_cast <TWindow*>((TWindow*)windows[hwnd]);
   messagebox(windows[0],text,caption,msgtype);
 }
}



#ifdef __cplusplus
}
#endif

#pragma pack(pop)


BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}
