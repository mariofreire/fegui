// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "console.h" // class's header file

int cblinkcnt=0;

void drawimagedatamask(int x, int y,int w,int h,unsigned char*data,int alpha, COLORREF color, bool transparent, COLORREF transparentcolor)
{
int cx,cy,index=0,c,r,g,b;

{
  for(cy=0;cy<h;cy++)
  {
  for(cx=0;cx<w;cx++)
  {
    r = data[index + 2];
    g = data[index + 1];
    b = data[index + 0];
    c = RGB(r,g,b);
    if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(h-cy),color,alpha);
    index += 3;
  }
  }
}
//  enddrawing();

}


COLORREF c_textcolor=clBlack;
char c_textfont[256];

void consoletextcolor(COLORREF c)
{
  c_textcolor = c;
}

void consoletextfont(char *font)
{
  if (strcmp(font,"GLUT_BITMAP_8_BY_13")==0)
  {
    strcpy(c_textfont,"GLUT_BITMAP_8_BY_13");
  }
  else strcpy(c_textfont,font);
}

void consoletextout_fontdefault(int x,int y,char *text)
{
  int xx = x;
  for (int i=0;i<strlen(text);i++)
  {
    if (textfont.tex)
    {
      int texenabled = glIsEnabled(GL_TEXTURE_2D);
      glEnable(GL_TEXTURE_2D);
      begindrawing();
      glPushMatrix();
      glBindTexture(GL_TEXTURE_2D, textfont.chars[(unsigned char)text[i]].textureid);
      glColor4ub( GetRValue(c_textcolor), GetGValue(c_textcolor), GetBValue(c_textcolor), 255 );
      glBegin(GL_QUADS);
      glTexCoord2i(0,0); glVertex2i(xx,             y+textfont.dh);
      glTexCoord2i(1,0); glVertex2i(xx+textfont.dw, y+textfont.dh);
      glTexCoord2i(1,1); glVertex2i(xx+textfont.dw, y            );
      glTexCoord2i(0,1); glVertex2i(xx,             y            );
      glEnd();
      glPopMatrix();
      enddrawing();
      if (texenabled) glEnable(GL_TEXTURE_2D);
      else glDisable(GL_TEXTURE_2D);
    }
    else drawimagedatamask(xx,y,textfont.dw,textfont.dh,textfont.chars[(unsigned char)text[i]].data,255,c_textcolor,true,clWhite);
    xx += textfont.fw;
  }
}

void consoletextout_fontglut(int x,int y,unsigned char *text)
{
  int xx = x;
  int yy = y+11;
  for (int i=0;i<strlen(text);i++)
  {
      int texenabled = glIsEnabled(GL_TEXTURE_2D);
      glDisable(GL_TEXTURE_2D);
      begindrawing();
      glPushMatrix();
      glColor4ub( GetRValue(c_textcolor), GetGValue(c_textcolor), GetBValue(c_textcolor), 255 );
      glRasterPos2i(xx,yy);
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13,(int)text[i]);
      glPopMatrix();
      enddrawing();
      if (texenabled) glEnable(GL_TEXTURE_2D);
      else glDisable(GL_TEXTURE_2D);
      xx += glutBitmapWidth(GLUT_BITMAP_8_BY_13,(int)text[i]);
  }
}

void consoletextout(int x,int y,char *text)
{
   if (strcmp(c_textfont,"GLUT_BITMAP_8_BY_13")==0)
   {
      consoletextout_fontglut(x,y,text);
   }
   else
   {
      consoletextout_fontdefault(x,y,text);
   }
}

int consoletextwidth(char *text)
{
  int xx = 0;
  for (int i=0;i<strlen(text);i++)
  {
    xx += textfont.fw;
  }
  return xx;
}

void consolecharout(int x,int y,unsigned char c)
{
  int xx = x;
    if (textfont.tex)
    {
      int texenabled = glIsEnabled(GL_TEXTURE_2D);
      glEnable(GL_TEXTURE_2D);
      begindrawing();
      glPushMatrix();
      glBindTexture(GL_TEXTURE_2D, textfont.chars[(unsigned char)c].textureid);
      glColor4ub( GetRValue(c_textcolor), GetGValue(c_textcolor), GetBValue(c_textcolor), 255 );
      glBegin(GL_QUADS);
      glTexCoord2i(0,0); glVertex2i(xx,             y+textfont.dh);
      glTexCoord2i(1,0); glVertex2i(xx+textfont.dw, y+textfont.dh);
      glTexCoord2i(1,1); glVertex2i(xx+textfont.dw, y            );
      glTexCoord2i(0,1); glVertex2i(xx,             y            );
      glEnd();
      glPopMatrix();
      enddrawing();
      if (texenabled) glEnable(GL_TEXTURE_2D);
      else glDisable(GL_TEXTURE_2D);
    }
    else drawimagedatamask(xx,y,textfont.dw,textfont.dh,textfont.chars[(unsigned char)c].data,255,c_textcolor,true,clWhite);
}
int consolecharwidth(void)
{
  return textfont.fw;
}


