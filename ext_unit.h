// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2013 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br
//---------------------------------------------------------------------------

#ifndef ext_unitH
#define ext_unitH

namespace fegui
{
class TObject
{
	public:
		// class constructor
		TObject();
		// class destructor
		~TObject();
};
};

typedef void (FEGUI_CALLBACK * fegui_TNotifyEvent)(int windowid, int sender);
typedef void (FEGUI_CALLBACK * fegui_TRenderEvent)(int windowid, int sender);
typedef void (FEGUI_CALLBACK * fegui_TTimerEvent)(int windowid, int sender);
typedef void (FEGUI_CALLBACK * fegui_TMenuEvent)(int windowid, int sender, int menuid);
//---------------------------------------------------------------------------
#endif
