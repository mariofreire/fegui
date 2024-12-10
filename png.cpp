// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "png.h" // class's header file


#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FASTPNGLIB_SETFILESYSTEM fastpnglib_setfilesystem;
FASTPNGLIB_LOADPNGDATA loadpngdata;
FASTPNGLIB_LOADPNG loadpng;
FASTPNGLIB_CLOSE freepng;

HINSTANCE fastpnglibhinst;

void fastpnglib_init(void)
{
FASTPNGLIB_INIT fpnginit;

fastpnglibhinst = LoadLibrary("FASTPNGLIB.DLL");
        if(!fastpnglibhinst){
            MessageBox(NULL,"This application has failed to start because FASTPNGLIB.DLL was not found. Re-installing the application may fix this problem.","Unable To Locate Component",MB_OK|MB_ICONERROR);
            PostQuitMessage(0);
            exit(0);
            return;
        }
 
fpnginit = (FASTPNGLIB_INIT)GetProcAddress(fastpnglibhinst, "_fastpnglib_init");
fastpnglib_setfilesystem = (FASTPNGLIB_SETFILESYSTEM)GetProcAddress(fastpnglibhinst, "_fastpnglib_setfilesystem");
loadpngdata = (FASTPNGLIB_LOADPNGDATA)GetProcAddress(fastpnglibhinst, "_loadpngdata");
loadpng = (FASTPNGLIB_LOADPNG)GetProcAddress(fastpnglibhinst, "_loadpng");
freepng = (FASTPNGLIB_CLOSE)GetProcAddress(fastpnglibhinst, "_closepng");
fpnginit();
fpnginit = NULL;
}

void fastpnglib_uninit(void)
{
 fastpnglib_setfilesystem = NULL;
 loadpngdata = NULL;
 loadpng = NULL;
 freepng = NULL;
 FreeLibrary(fastpnglibhinst);
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


// class constructor
TPNGObject::TPNGObject()
{
	// insert your code here
}

// class destructor
TPNGObject::~TPNGObject()
{
	// insert your code here
}
