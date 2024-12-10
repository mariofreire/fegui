// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "timer.h" // class's header file


int TTimer::gettickcount()
{
if (timestarted == false) tickstart=GetTickCount();
timestarted = true;
tickcount=GetTickCount()-tickstart;
if (tickcount>interval) 
{
  tickstart=GetTickCount();
  tickcount=interval;
}
if (tickcount<0) tickcount = 0;
return tickcount;
}

TTimer::TTimer(TWindow *Window)
{
window = Window;
id=window->numcomponents+1000;
parent = Window;
tickcount = -1;
tickstart = 0;
timestarted = false;
interval = 1000;
enabled = true;
componentid = window->numcomponents;
window->timers[window->numtimers] = this;
window->numtimers++;
window->numcomponents++;
}

TTimer::~TTimer()
{
}

void TTimer::rendercomponent()
{
     if (enabled)
     {
       if (gettickcount()==interval)
       {
         if (ontimer) ontimer(this);
         tickstart=GetTickCount();
         tickcount=0;
       }
     } else timestarted = false;
     window->timers[componentid] = this;
}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createtimer(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int tmid = 0;
   tmid = windows[winid]->numtimers;
   TTimer* timer = new TTimer(windows[winid]);
   timer->interval = 1000;
   timer->enabled = true;
   return tmid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

