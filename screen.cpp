// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "screen.h" // class's header file
#include "gfx.h"


int left=0,top=0,width=800,height=600;

void setscreenwidth(int w)
{
  width = w;
}
void setscreenheight(int h)
{
  height = h;
}

int getscreenwidth() { return width; };
int getscreenheight() { return height; };

BMP* xbk;

extern GLuint	texture[2];

// class constructor
TScreen::TScreen()
{
	// insert your code here
}

// class destructor
TScreen::~TScreen()
{
	// insert your code here
}

void drawbkimage(void)
{
  begindrawing();
  
  glPushMatrix();
  int tx=0,ty=0;
  tx=ty=(getscreenheight()/8);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glBegin( GL_QUADS );
  glColor4ub( 255, 255, 255, 255 );
    glTexCoord2f( 0, 0 );
    glVertex2i( 0, 0 );
    glTexCoord2f( tx, 0 );
    glVertex2i( width, 0 );
    glTexCoord2f( tx, ty );
    glVertex2i( width, height );
    glTexCoord2f( 0, ty );
    glVertex2i( 0, height );
  glEnd();
  
  glPopMatrix();
  enddrawing();

}
