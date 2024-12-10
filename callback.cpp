// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "callback.h"
#include "gfx.h"
#include "window.h"
#include "msgbox.h"

void CALLBACK combineCallback(GLdouble coords[3], 
                     GLdouble *vertex_data[4],
                     GLfloat weight[4], GLdouble **dataOut )
{
   GLdouble *vertex;
   int i;

   vertex = (GLdouble *) malloc(3 * sizeof(GLdouble));

   vertex[0] = coords[0];
   vertex[1] = coords[1];
   vertex[2] = coords[2];

   *dataOut = vertex;
}

void CALLBACK beginCallback(GLenum which)
{
   begindrawing();
   glBegin(which);
}

void CALLBACK errorCallback(GLenum errorCode)
{
   const GLubyte *estring;
   estring = gluErrorString(errorCode);
   fillrect(tessrect_x0,tessrect_y0,tessrect_x1,tessrect_y1,tessrect_color,tessrect_alpha);
   if (numwindows<=0) return;
   windows[0]->messageboxtimereset = 256;
   if (windows[0]->messageboxresult==mrOk) 
   {
     return;
   }
   messagebox(windows[0],(char*)estring,"Tessellation Error",MB_OK|MB_ICONERROR);
}

void CALLBACK endCallback(void)
{
   glEnd();
   enddrawing();
}

void CALLBACK vertexCallback(GLvoid *vertex)
{
   const GLdouble *pointer;

   pointer = (GLdouble *) vertex;
   glVertex2i((int)pointer[0],(int)pointer[1]);
}

