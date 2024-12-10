// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef COMPONENT_H
#define COMPONENT_H

#include "cimp.h"
#include "object.h" // inheriting class's header file

class TComponent : public TObject
{
	public:
		// class constructor
		TComponent();
		// class destructor
		~TComponent();
                int id;
		char *name;
		int tag;
		int componentid;
};

#endif // COMPONENT_H
