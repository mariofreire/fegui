// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "cimp.h"
#include "brush.h"
#include "pen.h"
#include "graphicobject.h"
#include "canvas.h"
#include "bitmap.h"
#include "png.h"
#include "picture.h"
#include "window.h"
#include "screen.h"
#include "gfx.h"
#include "icons.h"
#include "mouse.h"
#include "hint.h"
#include "control.h" // inheriting class's header file

#define FEVSL_STDCALL _stdcall
#define FEVSL_CALLBACK FEVSL_STDCALL

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif



void fevsl_init(void);
void fevsl_uninit(void);
void fevsl_binksndonoff(int video,int onoff);



#ifdef __cplusplus
}
#endif

#pragma pack(pop)


class TVideoPlayer : public TControl
{
private:
public:		// User declarations
TVideoPlayer(TWindow *Window);
~TVideoPlayer();
void show();
void hide();
void rendercontrol();
char* filename;
bool isopenned;
bool isplaying;
bool hasaudio;
bool hasvideo;
bool hasbink;
int startframe;
int totalframe;
int framerate;
int audiorate;
int position;
void play();
void stop();
void resume();
void pause();
void open();
void close();
void getstream();
char* image;
GLuint textureid;
int videonum;
TColor color;
};

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int createvideoplayer(int winid);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // VIDEOPLAYER_H
