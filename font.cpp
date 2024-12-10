// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "font.h"
#include "screen.h"


//BMP* fontbmp[256];
bitmapfont_t textfont;


int loadbitmapfont(char *filename, bitmapfont_t *f,bool textured)
{
FILE* fp = f_open(filename,"rb");
if (!fp) return 0;
f_read(&f->ptr[0],4,1,fp);
if (!((f->ptr[0]=='B')&&(f->ptr[1]=='F')&&(f->ptr[2]=='N')&&(f->ptr[3]=='T'))) return 0;
f_read(&f->fmt,4,1,fp);
if (f->fmt != 0x60F0) return 0;
f_read(&f->ver,4,1,fp);
if (f->ver != 1) return 0;
f_read(&f->fw,4,1,fp);
f_read(&f->fh,4,1,fp);
f_read(&f->dw,4,1,fp);
f_read(&f->dh,4,1,fp);
f_read(&f->numchars,4,1,fp);
for (int i=0;i<f->numchars;i++)
{
  f->chars[i].data = (unsigned char*)malloc(f->dw*f->dh*3);
  f_read(&f->chars[i].data[0],(f->dw*f->dh*3),1,fp);
}
f_close(fp);
f->tex = textured;
if (f->tex)
{

for (int i=0;i<f->numchars;i++)
{
    int texenabled = glIsEnabled(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &f->chars[i].textureid);
	glBindTexture(GL_TEXTURE_2D, f->chars[i].textureid);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w = f->dw;
    int h = f->dh;

    int nw = SearchForNextPower(w);
    int nh = SearchForNextPower(h);

  
    char* img = (char*)malloc(w*h*4);
    int r=0,g=0,b=0,a=0;
    int cx=0;
    COLORREF c=0;
    for(cx=0;cx<w*h;cx++)
    {
      r = f->chars[i].data[cx*3+0];
      g = f->chars[i].data[cx*3+1];
      b = f->chars[i].data[cx*3+2];
      a = 255;
      c = RGB(r,g,b);
      if (c == clWhite)
      {
        img[cx*4+0] = 0;
        img[cx*4+1] = 0;
        img[cx*4+2] = 0;
        img[cx*4+3] = 0;
      }
      else if (c == clBlack)
      {
        img[cx*4+0] = 255;
        img[cx*4+1] = 255;
        img[cx*4+2] = 255;
        img[cx*4+3] = 255;
      } else
      {
        img[cx*4+0] = 0;
        img[cx*4+1] = 0;
        img[cx*4+2] = 0;
        img[cx*4+3] = 0;
      }
    }

   	BYTE *scaled;
	scaled = (BYTE*)malloc(nw * nh * 4);
	gluScaleImage(GL_RGBA, w, h, GL_UNSIGNED_BYTE, img, nw, nh, GL_UNSIGNED_BYTE, scaled);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, nw, nh, 0, GL_RGBA, GL_UNSIGNED_BYTE, scaled);
	free(scaled);
	free(img);
    if (texenabled) glEnable(GL_TEXTURE_2D);
    else glDisable(GL_TEXTURE_2D);
}


}
return 1;
}

void freebitmapfont(bitmapfont_t *f)
{
f->ptr[0]=0;
f->ptr[1]=0;
f->ptr[2]=0;
f->ptr[3]=0;
f->fmt=0;
f->ver=0;
f->fw=0;
f->fh=0;
f->dw=0;
f->dh=0;
for (int i=0;i<f->numchars;i++) free(f->chars[i].data);
f->numchars=0;
}


GLuint	base;				// Base Display List For The Font Set
COLORREF fontcolor;
int fontalpha=255;
int fontheight=8,fontweight=FW_NORMAL;

/*
GLvoid BuildFont(int height, int weight)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(224);								// Storage For 224 Characters

	font = CreateFont(	-height,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						weight,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Lucida Console");//Microsoft Sans Serif");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 224, base);				// Builds 224 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

GLvoid KillFont(GLvoid)									// Delete The Font List
{
	glDeleteLists(base, 224);							// Delete All 224 Characters
}
*/

void *get_font( void )
{
  return GLUT_BITMAP_HELVETICA_12;
}
