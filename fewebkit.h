//---------------------------------------------------------------------------
// Fast Engine Video Stream Loader
// by Mario Freire
// Version 1.0
// Copyright (C) 2014 DSP Interactive.
//---------------------------------------------------------------------------
#ifndef _FEWEBKIT_H_
#define _FEWEBKIT_H_

#include "dlltype.h"

#define FEWEBKIT_STDCALL _stdcall
#define FEWEBKIT_CALLBACK FEWEBKIT_STDCALL

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif


#ifdef FEWEBKIT_LOADLIB

typedef int (FEWEBKIT_CALLBACK *FEWEBKIT_CREATEBROWSER) (int width,int height,char* url);
typedef void (FEWEBKIT_CALLBACK *FEWEBKIT_RENDER) (int browser);
typedef void (FEWEBKIT_CALLBACK *FEWEBKIT_KEYUP) (int browser, unsigned char key);
typedef void (FEWEBKIT_CALLBACK *FEWEBKIT_KEYDOWN) (int browser, unsigned char key);
typedef void (FEWEBKIT_CALLBACK *FEWEBKIT_KEYPRESS) (int browser, unsigned char key);
typedef void (FEWEBKIT_CALLBACK *FEWEBKIT_MOUSEDOWN) (int browser, int x, int y);
typedef void (FEWEBKIT_CALLBACK *FEWEBKIT_MOUSEMOVE) (int browser, int x, int y);
typedef void (FEWEBKIT_CALLBACK *FEWEBKIT_MOUSEUP) (int browser, int x, int y);

void fewebkit_init(void);
void fewebkit_uninit(void);

extern FEWEBKIT_CREATEBROWSER fewebkit_createbrowser;
extern FEWEBKIT_RENDER fewebkit_render;
extern FEWEBKIT_KEYUP fewebkit_keyup;
extern FEWEBKIT_KEYDOWN fewebkit_keydown;
extern FEWEBKIT_KEYPRESS fewebkit_keypress;
extern FEWEBKIT_MOUSEDOWN fewebkit_mousedown;
extern FEWEBKIT_MOUSEMOVE fewebkit_mousemove;
extern FEWEBKIT_MOUSEUP fewebkit_mouseup;

extern HINSTANCE fewebkithinst;

#else

void fewebkit_init(void);
void fewebkit_uninit(void);

DLLIMPORT int fewebkit_createbrowser(int width,int height,char* url);
DLLIMPORT void fewebkit_render(int browser);
DLLIMPORT void fewebkit_keydown(int browser, unsigned char key);
DLLIMPORT void fewebkit_keyup(int browser, unsigned char key);
DLLIMPORT void fewebkit_keypress(int browser, unsigned char key);
DLLIMPORT void fewebkit_mousedown(int browser, int x, int y);
DLLIMPORT void fewebkit_mousemove(int browser, int x, int y);
DLLIMPORT void fewebkit_mouseup(int browser, int x, int y);

#endif


#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // _FEWEBKIT_H_
//---------------------------------------------------------------------------

