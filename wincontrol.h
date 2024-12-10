// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef WINCONTROL_H
#define WINCONTROL_H

#include "cimp.h"
#include "control.h" // inheriting class's header file


class TWinControl : public TControl
{
	public:
		// class constructor
		TWinControl();
		// class destructor
		~TWinControl();
		char *name;
		int clientwidth;
		int clientheight;
		int left,top;
		int width,height;
		bool visible;
		int alphavalue;
		char *caption;
		TColor color;
		bool windowmove;
		bool modalhalt;
		bool messageboxon;
		bool freezing;
		bool focused;
		bool clicked;
		char *hint;
		bool showhint;
		bool resethint;
		bool showing;
		int modalresult;
		int messageboxresult;
		int messageboxtimereset;
		int subtessleft,subtesstop;
		int subtesswidth,subtessheight;
		TWindow *window;
		TNotifyEvent onclick;
		TKeyEvent onkeydown;
		TKeyEvent onkeyup;
		TWinRenderEvent render;
		void show();
		void hide();
		bool IsInControl(TControl* Control);
		bool IsInWindow(TWinControl* Window);
		int windowid;
		int controlid;
		int activecontrol;
};

#endif // WINCONTROL_H
