// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "mouse.h" // class's header file
#include "application.h"

int mousea=0, mouseb=0,mousec=0,mousex=0,mousey=0,mousekeys=0,mousedelta=0;
int oldmousex=0, oldmousey=0;

int currentcursor = FEGUI_MOUSECURSOR_XCURSOR;

int mc = 0;

extern bool webbrowser_mousedown_on, webbrowser_mousemove_on, webbrowser_mouseup_on;

// class constructor
TMouse::TMouse()
{
	// insert your code here
}

// class destructor
TMouse::~TMouse()
{
	// insert your code here
}

void setmousedown_l(int x,int y)
{
         mc = true;
         mousea = 0;
         mousec = 1;
         mouseb = 1;        // key flags 
         mousex = x;  // horizontal position of cursor 
         mousey = y;  // vertical position of cursor     
         webbrowser_mousedown_on = true;
}
void setmousedown_m(int x,int y)
{
         mc = true;
         mousea = 0;
         mousec = 16;
         mouseb = 2;        // key flags 
         mousex = x;  // horizontal position of cursor 
         mousey = y;  // vertical position of cursor 
}
void setmousedown_r(int x,int y)
{
         mc = true;
         mousea = 0;
         mousec = 2;
         mouseb = 3;        // key flags 
         mousex = x;  // horizontal position of cursor 
         mousey = y;  // vertical position of cursor 
}
void setmousemove(int x,int y)
{
         mc = false;
         mousea = 0;
         mousec = 0;
         //mouseb = wParam;        // key flags 
         oldmousex = mousex;
         oldmousey = mousey;
         mousex = x;  // horizontal position of cursor 
         mousey = y;  // vertical position of cursor     
         webbrowser_mousemove_on = true;
}
void setmousepos(int x,int y)
{
         mousex = x;  // horizontal position of cursor 
         mousey = y;  // vertical position of cursor 
}
void setmouseup(int x,int y)
{
         mc = false;
         mousea = 1;
         mouseb = 0;
         mousec = 0;
         mousex = x;  // horizontal position of cursor 
         mousey = y;  // vertical position of cursor 
         comboboxcontrolon = true;
         listboxcontrolon = true;
         cbcontrolon = true;
         rbcontrolon = true;
         bcontrolon = true;
         panelcontrolon = true;
         viewportcontrolon = true;
         webbrowsercontrolon = true;
         webbrowser_mouseup_on = true;
}
void setmousewheel(int key,int delta)
{
         mousekeys = key;    // key flags
         mousedelta = (short) delta;    // wheel rotation
}

void getmousepos(int *x,int *y)
{
*x = mousex;
*y = mousey;
}
void getmousestate(int *bs)
{
*bs = mouseb;
}
void getmousewheel(int *k,int *d)
{
*k = mousekeys;
*d = mousedelta;
}

void setmousecursor(int cursor)
{
  currentcursor = cursor;
}

int getmousecursor(void)
{
  return currentcursor;
}

