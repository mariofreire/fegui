// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef WINDOW_H
#define WINDOW_H

#include "cimp.h"
#include "wincontrol.h" // inheriting class's header file


extern bool windowmanager_crash;
extern int windowmanager;

extern int windowmove;
extern int windowresize;

extern bool winmove;
extern bool winresize;

extern int activewindow;
extern int numwindows;

extern int windowresizeside;
extern int windowtopbarheightdefault;

extern int isinuse;

extern COLORREF textcolor;

bool WindowExists(TWindow* Window);

void setforegroundwindow(int num);
int getforegroundwindow(void);
int createwindow(void);
void deletewindow(int num);

class TWindow : public TWinControl
{
private:	// User declarations
bool start_freeze;
int temp_left,temp_top;
int temp_width,temp_height;
bool temp_minimized;
bool temp_winanim;
bool temp_winfreeze;
bool temp_startfreeze;
TColor temp_freezecolor;
int temp_freezetime;
int temp_freezewidth,temp_freezeheight;
unsigned char* temp_freeze;
unsigned char* temp_freezebuf;
void rendercontrols();
public:		// User declarations
TWindow();
void show();
void restore();
void minimize();
void maximize();
void freeze();
void showfreeze();
int showmodal();
int instance;
int threadid;
int pid;
TBorderIcon bordericon;
TBorderStyle borderstyle;
TFormStyle formstyle;
TWindowState windowstate;
TColor color;
int numcomponents;
int numcontrols;
int numbuttons;
TButton *buttons[1024];
int numspeedbuttons;
TSpeedButton *speedbuttons[1024];
int numtoolbuttons;
TToolButton *toolbuttons[1024];
int numlabels;
TLabel *labels[1024];
int numedits;
TEdit *edits[1024];
int numtextboxes;
TTextBox *textboxes[1024];
int numlistboxes;
TListBox *listboxes[1024];
int numcomboboxes;
TComboBox *comboboxes[1024];
int numcheckboxes;
TCheckBox *checkboxes[1024];
int numradiobuttons;
TRadioButton *radiobuttons[1024];
int numscrollbars;
TScrollBar *scrollbars[1024];
int numprogressbars;
TProgressBar *progressbars[1024];
int numpanels;
TPanel *panels[1024];
int numbevels;
TBevel *bevels[1024];
int numgroupboxes;
TGroupBox *groupboxes[1024];
int numtransparentboxes;
TTransparentBox *transparentboxes[1024];
int numshapes;
TShape *shapes[1024];
int numimages;
TImage *images[1024];
int numglyphbuttons;
TGlyphButton *glyphbuttons[1024];
int numtimers;
TTimer *timers[1024];
int numviewports;
TViewport *viewports[1024];
int numimagelists;
TImageList* imagelists[1024];
int numtoolbars;
TToolBar *toolbars[1024];
int numdockbars;
TDockBar *dockbars[1024];
int nummainmenues;
TMainMenu *mainmenues[1024];
int numtrackbars;
TTrackBar* trackbars[1024];
int numupdowns;
TUpDown* updowns[1024];
int numvideoplayers;
TVideoPlayer* videoplayers[1024];
int numlistviews;
TListView* listviews[1024];
int numwebbrowsers;
TWebBrowser* webbrowsers[1024];
};

extern TWindow *windows[1024];

#endif // WINDOW_H
