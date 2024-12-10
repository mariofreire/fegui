// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "filesystem.h"
#include "png.h"
#include "dlltype.h"


#ifdef _FEGUI
#define FEGUIFUNCTION DLLEXPORT
#else
#define FEGUIFUNCTION
#endif

//#ifndef _FEGUI

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

//#endif


FEGUI_FILE_OPENCALLBACK f_open;
FEGUI_FILE_CLOSECALLBACK f_close;
FEGUI_FILE_READCALLBACK f_read;
FEGUI_FILE_WRITECALLBACK f_write;
FEGUI_FILE_TELLCALLBACK f_tell;
FEGUI_FILE_SEEKCALLBACK f_seek;

FEGUIFUNCTION void fegui_setfilesystem(FEGUI_FILE_OPENCALLBACK fileopen,FEGUI_FILE_CLOSECALLBACK fileclose,FEGUI_FILE_READCALLBACK fileread,FEGUI_FILE_WRITECALLBACK filewrite,FEGUI_FILE_TELLCALLBACK filetell,FEGUI_FILE_SEEKCALLBACK fileseek)
{
f_open = fileopen;
f_close = fileclose;
f_read = fileread;
f_write = filewrite;
f_tell = filetell;
f_seek = fileseek;
fastpnglib_setfilesystem(f_open,f_close,f_read,f_write,f_tell,f_seek);
}

#ifndef _FEGUI

DLLEXPORT void _fegui_setfilesystem(FEGUI_FILE_OPENCALLBACK fileopen,FEGUI_FILE_CLOSECALLBACK fileclose,FEGUI_FILE_READCALLBACK fileread,FEGUI_FILE_WRITECALLBACK filewrite,FEGUI_FILE_TELLCALLBACK filetell,FEGUI_FILE_SEEKCALLBACK fileseek)
{
f_open = fileopen;
f_close = fileclose;
f_read = fileread;
f_write = filewrite;
f_tell = filetell;
f_seek = fileseek;
fastpnglib_setfilesystem(f_open,f_close,f_read,f_write,f_tell,f_seek);
}

#endif


//#ifndef _FEGUI

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

//#endif


