// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "picture.h" // class's header file


void TPicture::load(char *filename)
{
  BMP* bmp;
  PNG* png;
  
  int format = 0;
  
  if (strcmp(strupr(fextractfileext(filename)),".BMP")==0) format = 1;
  else if (strcmp(strupr(fextractfileext(filename)),".PNG")==0) format = 2;
  else
  {
      format = 0;
      return;
  }

  if (format == 1) bmp = loadbmp(filename);
  else if (format == 2) png = loadpng(filename);
  
  if (canvas->pixels) delete canvas->pixels;
  if (format == 1) canvas->format = IMAGE_RGB;
  else if (format == 2) canvas->format = IMAGE_RGBA;
  if (format == 1)
  {
    canvas->width = bmp->width;
    canvas->height = bmp->height;
  } else if (format == 2)
  {
    canvas->width = png->width;
    canvas->height = png->height;
  }
  canvas->pixels = new unsigned char [canvas->width * canvas->height * canvas->format];

  int x,y,c,r,g,b,a,index=0;
  for(y=0;y<canvas->height;y++)
  {
  for(x=0;x<canvas->width;x++)
  {
    if (format == 1)
    {
      r = bmp->bgr[index + 2];
      g = bmp->bgr[index + 1];
      b = bmp->bgr[index + 0];
    } else
    if (format == 2)
    {
      r = png->pixels[(imageoffset(x,y,canvas->width,canvas->height)*canvas->format) + 0];
      g = png->pixels[(imageoffset(x,y,canvas->width,canvas->height)*canvas->format) + 1];
      b = png->pixels[(imageoffset(x,y,canvas->width,canvas->height)*canvas->format) + 2];
      if (canvas->format == IMAGE_RGBA) a = png->pixels[(imageoffset(x,y,canvas->width,canvas->height)*canvas->format) + 3];
      else a = 255;
    }
    c = RGB(r,g,b);
    canvas->pixels[index + 0] = r;
    canvas->pixels[index + 1] = g;
    canvas->pixels[index + 2] = b;
    if (format == 2) canvas->pixels[index + 3] = a;
    index += canvas->format;
  }
  }
  
  if (format == 1) freebmp(bmp);
  else if (format == 2) freepng(png);

  if (textured)
  {
    int texenabled = glIsEnabled(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_2D, textureid);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w = canvas->width;
    int h = canvas->height;

    int nw = SearchForNextPower(w);
    int nh = SearchForNextPower(h);

  
    char* img = (char*)malloc(w*h*4);
    int r=0,g=0,b=0,a=0;
    int cx=0;
    COLORREF c=0;
    for(cx=0;cx<w*h;cx++)
    {
      r = canvas->pixels[cx*canvas->format+0];
      g = canvas->pixels[cx*canvas->format+1];
      b = canvas->pixels[cx*canvas->format+2];
      if (canvas->format==IMAGE_RGBA) a = canvas->pixels[cx*canvas->format+3];
      else a = 255;
      c = RGB(r,g,b);
      if (transparent)
      {
        if (c == transparentcolor)
        {
          img[cx*4+0] = 0;
          img[cx*4+1] = 0;
          img[cx*4+2] = 0;
          img[cx*4+3] = 0;
        }
        else
        {
          img[cx*4+0] = r;
          img[cx*4+1] = g;
          img[cx*4+2] = b;
          img[cx*4+3] = a;
        }
      }
      else
      {
        img[cx*4+0] = r;
        img[cx*4+1] = g;
        img[cx*4+2] = b;
        img[cx*4+3] = a;
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

TPicture::TPicture()
{
canvas = new TCanvas();
transparentcolor = clBlack;
transparent = false;
textured = false;
textureid = 0;
}

TPicture::~TPicture()
{
delete canvas;
}


