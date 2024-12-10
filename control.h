// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef CONTROL_H
#define CONTROL_H

#include "cimp.h"
#include "component.h" // inheriting class's header file

bool getarea(int left,int top,int width,int height);

bool getintersectedarea(int l0,int t0,int w0,int h0,int l1,int t1,int w1,int h1);

class TControl;

class TControl : public TComponent
{
	public:
		// class constructor
		TControl();
		// class destructor
		~TControl();
                int id;
		char *name;
		int left,top;
		int width,height;
		bool enabled;
		bool visible;
		bool flat;
		int alphavalue;
		char *caption;
		TColor color;
		bool focus;
		bool focused;
		bool clicked;
		char *hint;
		bool showhint;
		bool resethint;
		int taborder;
		bool tabstop;
		int tag;
		TWindow *window;
		TControl *parent;
		TRenderEvent render;
		TRenderEvent onrender;
		TNotifyEvent onclick;
		TKeyEvent onkeydown;
		TKeyEvent onkeyup;
		void show();
		bool IsInControl(TControl* Control);
		int controlid;
		int handleid;
		TControl* instance;
};

#endif // CONTROL_H
