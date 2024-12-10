//---------------------------------------------------------------------------
// Fast Engine Video Stream Loader
// by Mario Freire
// Version 1.0
// Copyright (C) 2012 DSP Interactive.
//---------------------------------------------------------------------------
#ifndef _FEVSL_H_
#define _FEVSL_H_

#include "dlltype.h"

#define FEVSL_STDCALL 
#define FEVSL_CALLBACK FEVSL_STDCALL

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

typedef void (FEVSL_CALLBACK *FEVSL_INITENGINE) ();
typedef void (FEVSL_CALLBACK *FEVSL_UNINITENGINE) ();
typedef int (FEVSL_CALLBACK *FEVSL_CREATEVIDEO) ();
typedef void (FEVSL_CALLBACK *FEVSL_OPEN) (int video, char* filename);
typedef void (FEVSL_CALLBACK *FEVSL_CLOSE) (int video);
typedef int (FEVSL_CALLBACK *FEVSL_GETWIDTH) (int video);
typedef int (FEVSL_CALLBACK *FEVSL_GETHEIGHT) (int video);
typedef int (FEVSL_CALLBACK *FEVSL_GETFRAMERATE) (int video);
typedef int (FEVSL_CALLBACK *FEVSL_GETAUDIORATE) (int video);
typedef char* (FEVSL_CALLBACK *FEVSL_GETIMAGE) (int video);
typedef void (FEVSL_CALLBACK *FEVSL_GETIMAGEDATA) (int video,const char* data);
typedef void (FEVSL_CALLBACK *FEVSL_LOADTEXTUREIMAGE) (int video);
typedef int (FEVSL_CALLBACK *FEVSL_HASBINK) (int video);
typedef void (FEVSL_CALLBACK *FEVSL_BINKSOUNDONOFF) (int video,int onoff);

FEVSL_INITENGINE fevsl_initengine;
FEVSL_UNINITENGINE fevsl_uninitengine;
FEVSL_CREATEVIDEO fevsl_createvideo;
FEVSL_OPEN fevsl_openvideo;
FEVSL_CLOSE fevsl_closevideo;
FEVSL_GETWIDTH fevsl_getwidth;
FEVSL_GETHEIGHT fevsl_getheight;
FEVSL_GETFRAMERATE fevsl_getframerate;
FEVSL_GETAUDIORATE fevsl_getaudiorate;
FEVSL_GETIMAGE fevsl_getimage;
FEVSL_GETIMAGEDATA fevsl_getimagedata;
FEVSL_LOADTEXTUREIMAGE fevsl_loadtextureimage;
FEVSL_HASBINK fevsl_hasbink;
FEVSL_BINKSOUNDONOFF fevsl_binksoundonoff;

HINSTANCE fevslhinst;


void fevsl_init(void)
{
fevslhinst = LoadLibrary("FEVSL.DLL");
        if(!fevslhinst){
            MessageBox(NULL,"This application has failed to start because FEVSL.DLL was not found. Re-installing the application may fix this problem.","Unable To Locate Component",MB_OK|MB_ICONERROR);
            PostQuitMessage(0);
            exit(0);
            return;
        }

fevsl_initengine = (FEVSL_INITENGINE)GetProcAddress(fevslhinst, "_fevsl_initengine");
fevsl_uninitengine = (FEVSL_UNINITENGINE)GetProcAddress(fevslhinst, "_fevsl_uninitengine");
fevsl_createvideo = (FEVSL_CREATEVIDEO)GetProcAddress(fevslhinst, "_fevsl_createvideo");
fevsl_createvideo = (FEVSL_CREATEVIDEO)GetProcAddress(fevslhinst, "_fevsl_createvideo");
fevsl_openvideo = (FEVSL_OPEN)GetProcAddress(fevslhinst, "_fevsl_openvideo");
fevsl_closevideo = (FEVSL_CLOSE)GetProcAddress(fevslhinst, "_fevsl_closevideo");
fevsl_getwidth = (FEVSL_GETWIDTH)GetProcAddress(fevslhinst, "_fevsl_getwidth");
fevsl_getheight = (FEVSL_GETHEIGHT)GetProcAddress(fevslhinst, "_fevsl_getheight");
fevsl_getframerate = (FEVSL_GETFRAMERATE)GetProcAddress(fevslhinst, "_fevsl_getframerate");
fevsl_getaudiorate = (FEVSL_GETAUDIORATE)GetProcAddress(fevslhinst, "_fevsl_getaudiorate");
fevsl_getimage = (FEVSL_GETIMAGE)GetProcAddress(fevslhinst, "_fevsl_getimage");
fevsl_getimagedata = (FEVSL_GETIMAGEDATA)GetProcAddress(fevslhinst, "_fevsl_getimagedata");
fevsl_loadtextureimage = (FEVSL_LOADTEXTUREIMAGE)GetProcAddress(fevslhinst, "_fevsl_loadtextureimage");
fevsl_hasbink = (FEVSL_HASBINK)GetProcAddress(fevslhinst, "_fevsl_hasbink");
fevsl_binksoundonoff = (FEVSL_BINKSOUNDONOFF)GetProcAddress(fevslhinst, "_fevsl_binksoundonoff");
fevsl_initengine();
}

void fevsl_uninit(void)
{
 fevsl_createvideo = NULL;
 fevsl_openvideo = NULL;
 fevsl_closevideo = NULL;
 fevsl_getwidth = NULL;
 fevsl_getheight = NULL;
 fevsl_getframerate = NULL;
 fevsl_getaudiorate = NULL;
 fevsl_getimage = NULL;
 fevsl_getimagedata = NULL;
 fevsl_loadtextureimage = NULL;
 fevsl_hasbink = NULL;
 fevsl_binksoundonoff = NULL;
 fevsl_uninitengine();
 fevsl_uninitengine = NULL;
 FreeLibrary(fevslhinst);
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // _FEVSL_H_
//---------------------------------------------------------------------------

