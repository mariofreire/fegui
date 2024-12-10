// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "gfx.h"
#include "console.h"


int tessrect_x0 = 0;
int tessrect_y0 = 0;
int tessrect_x1 = 0;
int tessrect_y1 = 0;
TColor tessrect_color = 0;
int tessrect_alpha = 0;


int subrect_x0 = 0;
int subrect_y0 = 0;
int subrect_x1 = 0;
int subrect_y1 = 0;


void drawimagemask(int x, int y,BMP* imagefile,int alpha, COLORREF color, bool transparent, COLORREF transparentcolor)
{
int cx,cy,index=0,c,r,g,b;

  for(cy=0;cy<imagefile->height;cy++)
  {
  for(cx=0;cx<imagefile->width;cx++)
  {
    r = imagefile->bgr[index + 2];
    g = imagefile->bgr[index + 1];
    b = imagefile->bgr[index + 0];
    c = RGB(r,g,b);
    if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(imagefile->height-cy),color,alpha);
    index += 3;
  }
  }
  
//  enddrawing();

}

void drawimage(int x, int y,BMP* imagefile,int alpha, bool transparent, COLORREF transparentcolor)
{
int cx,cy,index=0,c,r,g,b;

  for(cy=0;cy<imagefile->height;cy++)
  {
  for(cx=0;cx<imagefile->width;cx++)
  {
    r = imagefile->bgr[index + 2];
    g = imagefile->bgr[index + 1];
    b = imagefile->bgr[index + 0];
    c = RGB(r,g,b);
    if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(imagefile->height-cy),c,alpha);
    index += 3;
  }
  }
  
//  enddrawing();

}

void drawtileimage(int x, int y, int width, int height, BMP* imagefile,int alpha, bool transparent, COLORREF transparentcolor)
{
int cx,cy,xx=0,yy=0,index=0,c,r,g,b;

  for(yy=0;yy<height;yy+=imagefile->height)
  {
  for(xx=0;xx<width;xx+=imagefile->width)
  {
    index = 0;
    for(cy=0;cy<imagefile->height;cy++)
    {
    for(cx=0;cx<imagefile->width;cx++)
    {
      r = imagefile->bgr[index + 2];
      g = imagefile->bgr[index + 1];
      b = imagefile->bgr[index + 0];
      c = RGB(r,g,b);
      if ((transparent) && (c!=transparentcolor)) setpixel(xx+(x+cx),yy+(y+(imagefile->height-cy)),c,alpha);
      else setpixel(xx+(x+cx),yy+(y+(imagefile->height-cy)),c,alpha);
      index += 3;
    }
   }
  }
  }
  
//  enddrawing();

}

void drawsysbtnimage(int x, int y,BMP* imagefile,int alpha,COLORREF highlightcolor,COLORREF shadowcolor,bool transparent, COLORREF transparentcolor, bool enabled)
{
int cx,cy,index=0,c,r,g,b;

  for(cy=0;cy<imagefile->height;cy++)
  {
  for(cx=0;cx<imagefile->width;cx++)
  {
   r = imagefile->bgr[index + 2];
   g = imagefile->bgr[index + 1];
   b = imagefile->bgr[index + 0];
   c = RGB(r,g,b);
   if (enabled)
   {
    int factor=32;
    //if (c == highlightcolor) c = clBtnHighlight;
    //if (c == shadowcolor) c = clBtnShadow;
    int rhl=0,ghl=0,bhl=0;
    rhl = GetRValue(clBtnHighlight);
    ghl = GetGValue(clBtnHighlight);
    bhl = GetBValue(clBtnHighlight);
    rhl += factor/2;
    ghl += factor/2;
    bhl += factor/2;
    if (rhl>=255) rhl = 255;
    if (ghl>=255) ghl = 255;
    if (bhl>=255) bhl = 255;
    if (c == highlightcolor) c = RGB(rhl,ghl,bhl);
    rhl = GetRValue(clBtnShadow);
    ghl = GetGValue(clBtnShadow);
    bhl = GetBValue(clBtnShadow);
    rhl -= factor*2;
    ghl -= factor*2;
    bhl -= factor*2;
    if (rhl<=0) rhl = 0;
    if (ghl<=0) ghl = 0;
    if (bhl<=0) bhl = 0;
    if (c == shadowcolor) c = RGB(rhl,ghl,bhl);
   }
   else
   {
    if (c == highlightcolor) c = clBtnShadow;
    if (c == shadowcolor) c = clBtnHighlight;
   }
   if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(imagefile->height-cy),c,alpha);
   index += 3;
  }
  }
  
//  enddrawing();

}

void drawradioimage(int x, int y,BMP* imagefile,int alpha,COLORREF color,COLORREF highlightcolor,COLORREF shadowcolor,COLORREF lightshadowcolor,COLORREF darkshadowcolor, bool transparent, COLORREF transparentcolor)
{
int cx,cy,index=0,c,r,g,b;

  for(cy=0;cy<imagefile->height;cy++)
  {
  for(cx=0;cx<imagefile->width;cx++)
  {
    r = imagefile->bgr[index + 2];
    g = imagefile->bgr[index + 1];
    b = imagefile->bgr[index + 0];
    c = RGB(r,g,b);
    if (c == color) c = clWhite;
    if (c == highlightcolor) c = clBtnHighlight;
    if (c == shadowcolor) c = clBtnShadow;
    if (c == lightshadowcolor) c = clBtnFace;
    if (c == darkshadowcolor) c = cl3DDkShadow;
    if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(imagefile->height-cy),c,alpha);
    index += 3;
  }
  }
  
//  enddrawing();

}

void drawflatradioimage(int x, int y,BMP* imagefile,int alpha,COLORREF color,COLORREF highlightcolor,COLORREF shadowcolor,COLORREF lightshadowcolor,COLORREF darkshadowcolor, bool transparent, COLORREF transparentcolor)
{
int cx,cy,index=0,c,r,g,b;

  for(cy=0;cy<imagefile->height;cy++)
  {
  for(cx=0;cx<imagefile->width;cx++)
  {
    r = imagefile->bgr[index + 2];
    g = imagefile->bgr[index + 1];
    b = imagefile->bgr[index + 0];
    c = RGB(r,g,b);
    if (c == color) c = clWhite;
    if (c == highlightcolor) c = clBtnHighlight;
    if (c == shadowcolor) c = clBtnShadow;
    if (c == lightshadowcolor) c = transparentcolor;
    if (c == darkshadowcolor) c = transparentcolor;
    if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(imagefile->height-cy),c,alpha);
    index += 3;
  }
  }
  
//  enddrawing();

}

void drawcursorimage(int x, int y,BMP* cursorfile,int alpha)
{
int cx,cy,index=0,c,r,g,b;

  for(cy=0;cy<cursorfile->height;cy++)
  {
  for(cx=0;cx<cursorfile->width;cx++)
  {
    r = cursorfile->bgr[index + 2];
    g = cursorfile->bgr[index + 1];
    b = cursorfile->bgr[index + 0];
    c = RGB(r,g,b);
    if (c!=clBlue) setpixel(x+cx,y+(cursorfile->height-cy),c,alpha);
    index += 3;
  }
  }
  
//  enddrawing();

}

void drawcursorimagemask(int x, int y,BMP* cursorfile,COLORREF color,int alpha)
{
int cx,cy,index=0,c,r,g,b;

  for(cy=0;cy<cursorfile->height;cy++)
  {
  for(cx=0;cx<cursorfile->width;cx++)
  {
    r = cursorfile->bgr[index + 2];
    g = cursorfile->bgr[index + 1];
    b = cursorfile->bgr[index + 0];
    c = RGB(r,g,b);
    if (c!=clBlue) setpixel(x+cx,y+(cursorfile->height-cy),color,alpha);
    index += 3;
  }
  }
  
//  enddrawing();

}


void drawcursor(int x, int y,BMP* cursorfile)
{
  int cx,cy;
  COLORREF color;
  int alpha;
  
  glPointSize(1.0);
  
  cx = x+2;
  cy = y+2;

  color = RGB(0,0,0);
  
  alpha = 72;
  drawcursorimagemask(cx,cy,cursorfile,color,alpha);
  cx = x;
  cy = y;


  color = RGB(255,255,255);

  alpha = 255;
  
  drawcursorimage(cx,cy,cursorfile,alpha); 
  
//  enddrawing();

}


void drawimagepng(int x, int y,PNG* imagefile,int alpha, bool transparent, COLORREF transparentcolor)
{
int cx,cy,index=0,c,r,g,b,a;

  for(cy=0;cy<imagefile->height;cy++)
  {
  for(cx=0;cx<imagefile->width;cx++)
  {
    r = imagefile->pixels[index + 0];
    g = imagefile->pixels[index + 1];
    b = imagefile->pixels[index + 2];
    a = imagefile->pixels[index + 3];
    c = RGB(r,g,b);
    if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+cy,c,blendto(a,alpha));
    else setpixel(x+cx,y+cy,c,blendto(a,alpha));
    index += 4;
  }
  }
  
//  enddrawing();

}



void drawgradient(int x0, int y0, int x1, int y1, COLORREF startcolor, COLORREF endcolor, int alpha,int direction)
{
  begindrawing();
  glPushMatrix();

if (direction==0)
{
  glBegin( GL_QUADS );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x0, y0 );
  glColor4ub( GetRValue(endcolor), GetGValue(endcolor), GetBValue(endcolor), alpha );
    glVertex2i( x1, y0 );
  glColor4ub( GetRValue(endcolor), GetGValue(endcolor), GetBValue(endcolor), alpha );
    glVertex2i( x1, y1 );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x0, y1 );
  glEnd();
}
else if (direction==1)
{
  glBegin( GL_QUADS );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x0, y0 );
    glVertex2i( x1, y0 );
  glColor4ub( GetRValue(endcolor), GetGValue(endcolor), GetBValue(endcolor), alpha );
    glVertex2i( x1, y1 );
    glVertex2i( x0, y1 );
  glEnd();
}
else if (direction==2)
{
  glBegin( GL_QUADS );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x0, y0 );
  glColor4ub( GetRValue(endcolor), GetGValue(endcolor), GetBValue(endcolor), alpha );
    glVertex2i( x1, y0 );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x1, y1 );
    glVertex2i( x0, y1 );
  glEnd();
}
else if (direction==3)
{
  glBegin( GL_QUADS );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x0, y0 );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x1, y0 );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x1, y1 );
  glColor4ub( GetRValue(endcolor), GetGValue(endcolor), GetBValue(endcolor), alpha );
    glVertex2i( x0, y1 );
  glEnd();
}
else if (direction==4)
{
  glBegin( GL_QUADS );
  glColor4ub( GetRValue(endcolor), GetGValue(endcolor), GetBValue(endcolor), alpha );
    glVertex2i( x0, y0 );
  glColor4ub( GetRValue(endcolor), GetGValue(endcolor), GetBValue(endcolor), alpha );
    glVertex2i( x1, y0 );
    glVertex2i( x1, y1 );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x0, y1 );
  glEnd();
}
else if (direction==5)
{
  glBegin( GL_QUADS );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x0, y0 );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x1, y0 );
  glColor4ub( GetRValue(startcolor), GetGValue(startcolor), GetBValue(startcolor), alpha );
    glVertex2i( x1, y1 );
  glColor4ub( GetRValue(endcolor), GetGValue(endcolor), GetBValue(endcolor), alpha );
    glVertex2i( x0, y1 );
  glEnd();
}
  glPopMatrix();
  enddrawing();

}

void fillrecttexture(unsigned int texture, int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
  begindrawing();

  glPushMatrix();

  glBindTexture(GL_TEXTURE_2D,texture);

  glBegin( GL_QUADS );
  glColor4ub( GetRValue(color), GetGValue(color), GetBValue(color), alpha );
    glTexCoord2f(0.0f,1.0f); glVertex2i( x0, y0 );
    glTexCoord2f(1.0f,1.0f); glVertex2i( x1, y0 );
    glTexCoord2f(1.0f,0.0f); glVertex2i( x1, y1 );
    glTexCoord2f(0.0f,0.0f); glVertex2i( x0, y1 );
  glEnd();
  
  glPopMatrix();
  enddrawing();

}

void fillrectpattern(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
  bool patternon = true;
  begindrawing();
  
  glPushMatrix();

  glBegin( GL_POINTS );
  glColor4ub( GetRValue(color), GetGValue(color), GetBValue(color), alpha );
  for (int x=x0;x<=x1-1;x++)
  {
   for (int y=y0+1;y<=y1;y++)
   {
     if (((x&1)&&(y&1))) glVertex2i( x,y );
     if ((((x&1)==0)&&((y&1)==0))) glVertex2i( x,y );
   }
  }
  glEnd();
  
  glPopMatrix();
  enddrawing();

}

void fillrect(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
  begindrawing();
  
  glPushMatrix();

  glBegin( GL_QUADS );
  glColor4ub( GetRValue(color), GetGValue(color), GetBValue(color), alpha );
    glVertex2i( x0, y0 );
    glVertex2i( x1, y0 );
    glVertex2i( x1, y1 );
    glVertex2i( x0, y1 );
  glEnd();
  
  glPopMatrix();
  enddrawing();

}

void rectangledashed(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
  begindrawing();
  
  glPushMatrix();
  
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, (short) 0x9999);

  drawline(x0-1,y0,x1,y0,color,alpha);
  drawline(x0-1,y0,x0,y1,color,alpha);
  drawline(x0,y1,x1,y1,color,alpha);
  drawline(x1,y0,x1,y1,color,alpha);
  
  glLineStipple(1, 0);
  glDisable(GL_LINE_STIPPLE);

  glPopMatrix();
  
  enddrawing();

}

void rectangledotted(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
  begindrawing();
  
  glPushMatrix();
  
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, (short) 0xaaaa);

  drawline(x0-1,y0,x1,y0,color,alpha);
  drawline(x0-1,y0,x0,y1,color,alpha);
  drawline(x0,y1,x1,y1,color,alpha);
  drawline(x1,y0,x1,y1,color,alpha);
  
  glLineStipple(1, 0);
  glDisable(GL_LINE_STIPPLE);

  glPopMatrix();
  
  enddrawing();

}

void rectangle(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
  begindrawing();
  
  glPushMatrix();

  drawline(x0,y0,x1,y0,color,alpha);
  drawline(x0,y0,x0,y1+1,color,alpha);
  drawline(x0,y1,x1,y1,color,alpha);
  drawline(x1,y0,x1,y1,color,alpha);
  
  glPopMatrix();
  
  enddrawing();

}

void drawline(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
  begindrawing();
  
  glPushMatrix();

  glBegin( GL_LINES );
  glColor4ub( GetRValue(color), GetGValue(color), GetBValue(color), alpha );
    glVertex2i( x0, y0 );
    glVertex2i( x1, y1 );
  glEnd();
  
  glPopMatrix();
  
  enddrawing();

}



void drawcircle(int x0,int y0,int x1,int y1, COLORREF color, int alpha)
{
float pts = 100; 
float a=0,z=0,x=x1-x0,y=y1-y0;
int i=0;
for (i = 0; i < pts; i++) {    
   a = 2*PI*(i-1)/pts; 
   z = 2*PI*(i-0)/pts; 
   drawline(x0-(x*sin(a))+x, y0-(y*cos(a))+y,x0-(x*sin(z))+x, y0-(y*cos(z))+(y), color, alpha); 
} 
}


void drawellipse(int x0,int y0,int x1,int y1, COLORREF color, int alpha)
{
float pts = 100; 
float a=0,z=0,x=x1-x0,y=y1-y0;
int i=0;

begindrawing();

glPushMatrix();
glBegin(GL_POLYGON);
glColor4ub(GetRValue(color), GetGValue(color), GetBValue(color), alpha);
for (i = 0; i < pts; i++) {    
   a = 2*PI*(i-1)/pts; 
   z = 2*PI*(i-0)/pts; 
   glVertex2f(x0-(x*sin(a))+x, y0-(y*cos(a))+y); 
   glVertex2f(x0-(x*sin(z))+x, y0-(y*cos(z))+(y)); 
} 

glEnd();
glPopMatrix();

enddrawing();

}




void drawcontroledge_intel(int x,int y,int w,int h, int state, int alpha)
{
int sx=0,sy=0,sw=0,sh=0;
//begindrawing();
if (state==0)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==1)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w-1,y,cl3DDkShadow,alpha);
drawline(x,y-1,x,y+h-1,cl3DDkShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,clBtnShadow,alpha);
drawline(x+1,y,x+1,y+h-2,clBtnShadow,alpha);

drawline(x-1,y+h,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w-1,y-1,x+w,y+h,clBtnHighlight,alpha);

} else if (state==2)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y+1,x+w-1,y+1,clBtnHighlight,alpha);
drawline(x+1,y-1,x+1,y+h-1,clBtnHighlight,alpha);

drawline(x+1,y+h-2,x+w-1,y+h-2,clBtnShadow,alpha);
drawline(x+w-2,y+1,x+w-2,y+h-1,clBtnShadow,alpha);

drawline(x-1,y+h-1,x+w-1,y+h-1,cl3DDkShadow,alpha);
drawline(x+w-2,y-1,x+w-1,y+h-1,cl3DDkShadow,alpha);

rectangle(x,y,x+w,y+h,clBlack,alpha);

} else if (state==3)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);
rectangle(x,y,x+w,y+h,clBlack,alpha);
rectangle(x+1,y+1,x+w-1,y+h-1,clBtnShadow,alpha);
} else if (state==4)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,cl3DDkShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h,x+w,y+h,clBtnShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,clBtnShadow,alpha);
} else if (state==5)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w-1,y,clBtnShadow,alpha);
drawline(x,y-1,x,y+h-1,clBtnShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,cl3DDkShadow,alpha);
drawline(x+1,y,x+1,y+h-2,cl3DDkShadow,alpha);

drawline(x-1,y+h,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w-1,y-1,x+w,y+h,clBtnHighlight,alpha);

} else if (state==6)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h,x+w,y+h,clBtnShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,clBtnShadow,alpha);
} else if (state==7)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x,y+1,x+w,y,clBtnShadow,alpha);
drawline(x,y,x,y+h,clBtnShadow,alpha);

drawline(x,y+h,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w-1,y,x+w,y+h,clBtnHighlight,alpha);

} else if (state==8)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);

} else if (state==9)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w-1,y,cl3DDkShadow,alpha);
drawline(x,y-1,x,y+h-1,cl3DDkShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,clBtnShadow,alpha);
drawline(x+1,y,x+1,y+h-2,clBtnShadow,alpha);

drawline(x-1,y+h,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w-1,y-1,x+w,y+h,clBtnHighlight,alpha);

} else if (state==10)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);
} else if (state==11)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
drawcontroledgew(sx+1,sy+1,sw-1,sh-1,0,alpha);
}else if (state==12)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
fillrect(sx,sy,sx+sw,sy+sh-1,clBtnFace,alpha);
rectangle(sx,sy,sx+sw,sy+sh,clBtnShadow,alpha);
} else if (state==13)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
drawcontroledgew(sx+1,sy+1,sw-1,sh-1,0,alpha);
} else if (state==14)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
drawcontroledgew(sx+1,sy+1,sw-1,sh-1,1,alpha);
}
//enddrawing();
}

void drawcontroledgew_intel(int x,int y,int w,int h, int state, int alpha)
{
//begindrawing();
if (state==0)
{
fillrect(x-2,y-2,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h-2,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-2,y-1,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-2,y+h-1,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-2,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==1)
{
fillrect(x-2,y-2,x+w,y+h,clBtnFace,alpha);

drawline(x-2,y-1,x+w-1,y-1,clBtnShadow,alpha);
drawline(x-1,y-2,x-1,y+h-1,clBtnShadow,alpha);

drawline(x-1,y,x+w,y,cl3DDkShadow,alpha);
drawline(x,y-1,x,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h-2,x+w,y+h-1,clBtnFace,alpha);
drawline(x+w-2,y-1,x+w-1,y+h,clBtnFace,alpha);

drawline(x-2,y+h-1,x+w,y+h,clBtnHighlight,alpha);
drawline(x+w-1,y-2,x+w,y+h,clBtnHighlight,alpha);
}
//enddrawing();
}





void drawcontroledge_nvidia(int x,int y,int w,int h, int state, int alpha)
{
int sx=0,sy=0,sw=0,sh=0;
// begindrawing();

if (state==0)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y-1,x+w,y-1,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==1)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w-1,y,cl3DDkShadow,alpha);
drawline(x,y,x,y+h-1,cl3DDkShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,clBtnShadow,alpha);
drawline(x+1,y+1,x+1,y+h-2,clBtnShadow,alpha);

drawline(x-1,y+h,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w-1,y,x+w,y+h,clBtnHighlight,alpha);

} else if (state==2)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y+1,x+w-1,y+1,clBtnHighlight,alpha);
drawline(x+1,y-1,x+1,y+h-1,clBtnHighlight,alpha);

drawline(x+1,y+h-2,x+w-1,y+h-2,clBtnShadow,alpha);
drawline(x+w-2,y+1,x+w-2,y+h-1,clBtnShadow,alpha);

drawline(x-1,y+h-1,x+w-1,y+h-1,cl3DDkShadow,alpha);
drawline(x+w-2,y-1,x+w-1,y+h-1,cl3DDkShadow,alpha);

rectangle(x,y,x+w,y+h,clBlack,alpha);

} else if (state==3)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);
rectangle(x,y,x+w,y+h,clBlack,alpha);
rectangle(x+1,y+1,x+w-1,y+h-1,clBtnShadow,alpha);
} else if (state==4)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,cl3DDkShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h,x+w,y+h,clBtnShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,clBtnShadow,alpha);
} else if (state==5)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w-1,y,clBtnShadow,alpha);
drawline(x,y-1,x,y+h-1,clBtnShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,cl3DDkShadow,alpha);
drawline(x+1,y,x+1,y+h-2,cl3DDkShadow,alpha);

drawline(x-1,y+h,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w-1,y-1,x+w,y+h,clBtnHighlight,alpha);

} else if (state==6)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h,x+w,y+h,clBtnShadow,alpha);
drawline(x+w-1,y,x+w,y+h,clBtnShadow,alpha);
} else if (state==7)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnShadow,alpha);
drawline(x,y,x,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h-1,clBtnHighlight,alpha);
drawline(x+w,y,x+w,y+h-1,clBtnHighlight,alpha);

} else if (state==8)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y+1,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y,x+w,y+h,cl3DDkShadow,alpha);

} else if (state==9)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w-1,y,cl3DDkShadow,alpha);
drawline(x,y,x,y+h-1,cl3DDkShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,clBtnShadow,alpha);
drawline(x+1,y+1,x+1,y+h-2,clBtnShadow,alpha);

drawline(x-1,y+h,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w-1,y,x+w,y+h,clBtnHighlight,alpha);

} else if (state==10)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);
} else if (state==11)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
drawcontroledgew(sx+1,sy+1,sw-1,sh-1,0,alpha);
}else if (state==12)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
fillrect(sx,sy,sx+sw,sy+sh,clBtnFace,alpha);
rectangle(sx,sy,sx+sw,sy+sh,clBtnShadow,alpha);
} else if (state==13)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
drawcontroledgew(sx+1,sy+1,sw-1,sh-1,0,alpha);
} else if (state==14)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
drawcontroledgew(sx+1,sy+1,sw-1,sh-1,1,alpha);
} else if (state==15)
{

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h,x+w,y+h,clBtnShadow,alpha);
drawline(x+w-1,y,x+w,y+h,clBtnShadow,alpha);
} else if (state==16)
{

drawline(x-1,y,x+w,y,clBtnShadow,alpha);
drawline(x,y,x,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h-1,clBtnHighlight,alpha);
drawline(x+w,y,x+w,y+h-1,clBtnHighlight,alpha);

}
else if (state==17)
{

drawline(x-1,y-1,x+w,y-1,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==18)
{

drawline(x-1,y,x+w-1,y,cl3DDkShadow,alpha);
drawline(x,y,x,y+h-1,cl3DDkShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,clBtnShadow,alpha);
drawline(x+1,y+1,x+1,y+h-2,clBtnShadow,alpha);

drawline(x-1,y+h,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w-1,y,x+w,y+h,clBtnHighlight,alpha);

}
// enddrawing();
}

void drawcontroledgew_nvidia(int x,int y,int w,int h, int state, int alpha)
{
//begindrawing();
if (state==0)
{
fillrect(x-2,y-1,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y+1,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-2,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-2,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==1)
{
fillrect(x-2,y-2,x+w,y+h,clBtnFace,alpha);

drawline(x-2,y-1,x+w-1,y-1,clBtnShadow,alpha);
drawline(x-1,y-2,x-1,y+h-1,clBtnShadow,alpha);

drawline(x-1,y-1,x+w,y-1,cl3DDkShadow,alpha);
drawline(x,y-1,x,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h-2,x+w,y+h-1,clBtnFace,alpha);
drawline(x+w-2,y-1,x+w-1,y+h,clBtnFace,alpha);

drawline(x-2,y+h-1,x+w,y+h,clBtnHighlight,alpha);
drawline(x+w-1,y-2,x+w,y+h,clBtnHighlight,alpha);
} else if (state==2)
{
fillrecttess(x-2,y-1,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y+1,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-2,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-2,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==3)
{
fillrecttess(x-2,y-2,x+w,y+h,clBtnFace,alpha);

drawline(x-2,y-1,x+w-1,y-1,clBtnShadow,alpha);
drawline(x-1,y-2,x-1,y+h-1,clBtnShadow,alpha);

drawline(x-1,y-1,x+w,y-1,cl3DDkShadow,alpha);
drawline(x,y-1,x,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h-2,x+w,y+h-1,clBtnFace,alpha);
drawline(x+w-2,y-1,x+w-1,y+h,clBtnFace,alpha);

drawline(x-2,y+h-1,x+w,y+h,clBtnHighlight,alpha);
drawline(x+w-1,y-2,x+w,y+h,clBtnHighlight,alpha);
} else if (state==4)
{
// fillrect(x-2,y-1,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y+1,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-2,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-2,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==5)
{
// fillrect(x-2,y-2,x+w,y+h,clBtnFace,alpha);

drawline(x-2,y-1,x+w-1,y-1,clBtnShadow,alpha);
drawline(x-1,y-2,x-1,y+h-1,clBtnShadow,alpha);

drawline(x-1,y-1,x+w,y-1,cl3DDkShadow,alpha);
drawline(x,y-1,x,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h-2,x+w,y+h-1,clBtnFace,alpha);
drawline(x+w-2,y-1,x+w-1,y+h,clBtnFace,alpha);

drawline(x-2,y+h-1,x+w,y+h,clBtnHighlight,alpha);
drawline(x+w-1,y-2,x+w,y+h,clBtnHighlight,alpha);
}
//enddrawing();
}





void drawcontroledge(int x,int y,int w,int h, int state, int alpha)
{
int sx=0,sy=0,sw=0,sh=0;
// begindrawing();

if (state==0)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y-1,x+w,y-1,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==1)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w-1,y,cl3DDkShadow,alpha);
drawline(x,y,x,y+h-1,cl3DDkShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,clBtnShadow,alpha);
drawline(x+1,y+1,x+1,y+h-2,clBtnShadow,alpha);

drawline(x-1,y+h-1,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w,y,x+w,y+h,clBtnHighlight,alpha);

} else if (state==2)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y+1,x+w-1,y+1,clBtnHighlight,alpha);
drawline(x+1,y-1,x+1,y+h-1,clBtnHighlight,alpha);

drawline(x+1,y+h-2,x+w-1,y+h-2,clBtnShadow,alpha);
drawline(x+w-2,y+1,x+w-2,y+h-1,clBtnShadow,alpha);

drawline(x-1,y+h-1,x+w-1,y+h-1,cl3DDkShadow,alpha);
drawline(x+w-2,y-1,x+w-1,y+h-1,cl3DDkShadow,alpha);

rectangle(x,y,x+w,y+h,clBlack,alpha);

} else if (state==3)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);
rectangle(x,y,x+w,y+h,clBlack,alpha);
rectangle(x+1,y+1,x+w-1,y+h-1,clBtnShadow,alpha);
} else if (state==4)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,cl3DDkShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h,x+w,y+h,clBtnShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,clBtnShadow,alpha);
} else if (state==5)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w-1,y,clBtnShadow,alpha);
drawline(x,y-1,x,y+h-1,clBtnShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,cl3DDkShadow,alpha);
drawline(x+1,y,x+1,y+h-2,cl3DDkShadow,alpha);

drawline(x-1,y+h,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w-1,y-1,x+w,y+h,clBtnHighlight,alpha);

} else if (state==6)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h,x+w,y+h,clBtnShadow,alpha);
drawline(x+w,y,x+w,y+h,clBtnShadow,alpha);
} else if (state==7)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnShadow,alpha);
drawline(x,y,x,y+h,clBtnShadow,alpha);

drawline(x-1,y+h-1,x+w,y+h-1,clBtnHighlight,alpha);
drawline(x+w,y,x+w,y+h,clBtnHighlight,alpha);

} else if (state==8)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y+1,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w,y,x+w,y+h,cl3DDkShadow,alpha);

} else if (state==9)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w-1,y,cl3DDkShadow,alpha);
drawline(x,y,x,y+h-1,cl3DDkShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,clBtnShadow,alpha);
drawline(x+1,y+1,x+1,y+h-2,clBtnShadow,alpha);

drawline(x-1,y+h-1,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w,y,x+w,y+h,clBtnHighlight,alpha);

} else if (state==10)
{
fillrect(x,y,x+w,y+h,clBtnFace,alpha);
} else if (state==11)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
drawcontroledgew(sx+1,sy+1,sw-1,sh-1,0,alpha);
}else if (state==12)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
fillrect(sx,sy,sx+sw,sy+sh,clBtnFace,alpha);
rectangle(sx,sy,sx+sw,sy+sh,clBtnShadow,alpha);
} else if (state==13)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
drawcontroledgew(sx+1,sy+1,sw-1,sh-1,0,alpha);
} else if (state==14)
{
sx = x;
sy = y;
sw = w-1;
sh = h+1;
drawcontroledgew(sx+1,sy+1,sw-1,sh-1,1,alpha);
} else if (state==15)
{

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h,x+w,y+h,clBtnShadow,alpha);
drawline(x+w-1,y,x+w,y+h,clBtnShadow,alpha);
} else if (state==16)
{

drawline(x-1,y,x+w,y,clBtnShadow,alpha);
drawline(x,y,x,y+h,clBtnShadow,alpha);

drawline(x-1,y+h-1,x+w,y+h-1,clBtnHighlight,alpha);
drawline(x+w,y,x+w,y+h-1,clBtnHighlight,alpha);

}
else if (state==17)
{

drawline(x-1,y-1,x+w,y-1,clBtnHighlight,alpha);
drawline(x,y-1,x,y+h,clBtnHighlight,alpha);

drawline(x,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-1,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==18)
{

drawline(x-1,y,x+w-1,y,cl3DDkShadow,alpha);
drawline(x,y,x,y+h-1,cl3DDkShadow,alpha);

drawline(x+1,y+1,x+w-2,y+1,clBtnShadow,alpha);
drawline(x+1,y+1,x+1,y+h-2,clBtnShadow,alpha);

drawline(x-1,y+h-1,x+w-1,y+h-1,clBtnHighlight,alpha);
drawline(x+w,y,x+w,y+h,clBtnHighlight,alpha);

}
// enddrawing();
}

void drawcontroledgew(int x,int y,int w,int h, int state, int alpha)
{
//begindrawing();
if (state==0)
{
fillrect(x-2,y-1,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y+1,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-2,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==1)
{
fillrect(x-2,y-2,x+w,y+h,clBtnFace,alpha);

drawline(x-2,y-1,x+w-1,y-1,clBtnShadow,alpha);
drawline(x-1,y-2,x-1,y+h-1,clBtnShadow,alpha);

drawline(x-1,y-1,x+w,y-1,cl3DDkShadow,alpha);
drawline(x,y-1,x,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h-2,x+w,y+h-1,clBtnFace,alpha);
drawline(x+w-2,y-1,x+w-1,y+h,clBtnFace,alpha);

drawline(x-2,y+h-1,x+w,y+h,clBtnHighlight,alpha);
drawline(x+w-1,y-2,x+w,y+h,clBtnHighlight,alpha);
} else if (state==2)
{
fillrecttess(x-2,y-1,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y+1,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-1,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-2,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==3)
{
fillrecttess(x-2,y-2,x+w,y+h,clBtnFace,alpha);

drawline(x-2,y-1,x+w-1,y-1,clBtnShadow,alpha);
drawline(x-1,y-2,x-1,y+h-1,clBtnShadow,alpha);

drawline(x-1,y-1,x+w,y-1,cl3DDkShadow,alpha);
drawline(x,y-1,x,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h-2,x+w,y+h-1,clBtnFace,alpha);
drawline(x+w-2,y-1,x+w-1,y+h,clBtnFace,alpha);

drawline(x-2,y+h-1,x+w,y+h,clBtnHighlight,alpha);
drawline(x+w-1,y-2,x+w,y+h,clBtnHighlight,alpha);
} else if (state==4)
{
// fillrect(x-2,y-1,x+w,y+h,clBtnFace,alpha);

drawline(x-1,y,x+w,y,clBtnHighlight,alpha);
drawline(x,y+1,x,y+h,clBtnHighlight,alpha);

drawline(x-1,y+h-1,x+w,y+h-1,clBtnShadow,alpha);
drawline(x+w-2,y,x+w-1,y+h,clBtnShadow,alpha);

drawline(x-2,y+h,x+w,y+h,cl3DDkShadow,alpha);
drawline(x+w-1,y-1,x+w,y+h,cl3DDkShadow,alpha);
} else if (state==5)
{
// fillrect(x-2,y-2,x+w,y+h,clBtnFace,alpha);

drawline(x-2,y-1,x+w-1,y-1,clBtnShadow,alpha);
drawline(x-1,y-2,x-1,y+h-1,clBtnShadow,alpha);

drawline(x-1,y-1,x+w,y-1,cl3DDkShadow,alpha);
drawline(x,y-1,x,y+h,cl3DDkShadow,alpha);

drawline(x-1,y+h-2,x+w,y+h-1,clBtnFace,alpha);
drawline(x+w-2,y-1,x+w-1,y+h,clBtnFace,alpha);

drawline(x-2,y+h-1,x+w,y+h,clBtnHighlight,alpha);
drawline(x+w-1,y-2,x+w,y+h,clBtnHighlight,alpha);
}
//enddrawing();
}


COLORREF clLightifDarkR(COLORREF c)
{
if (GetRValue(c)<64) return (GetRValue(c)+128); else
return (GetRValue(c)|(GetRValue(c)/2));
}

COLORREF clLightifDarkG(COLORREF c)
{
if (GetGValue(c)<64) return (GetGValue(c)+128); else
return (GetGValue(c)|(GetGValue(c)/2));
}

COLORREF clLightifDarkB(COLORREF c)
{
if (GetBValue(c)<64) return (GetBValue(c)+128); else
return (GetBValue(c)|(GetBValue(c)/2));
}



void begindrawing(void)
{
  int lv,tv;
  int rv,bv;
  RECT boundsrect;
  
  lv = viewportleft;
  tv = viewporttop;
  rv = viewportright;
  bv = viewportbottom;
  
  /*
  rv -= lv;
  bv -= tv;
  
  
  /*
  boundsrect.left    = lv;
  boundsrect.top     = tv;
  boundsrect.right   = (rv-lv);
  boundsrect.bottom  = (bv-tv);
  */
  /*
  lv  = viewportleft;//+2;
  tv  = (getscreenheight()-viewporttop);//+4;
  rv  = viewportright;//-6;
  bv  = viewportbottom;//-28;
  tv -= bv;//+28;
  */
  
  /*
  lv = 0;
  tv = 0;
  rv = getscreenwidth();
  bv = getscreenheight();
  */

//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glViewport(lv,tv,rv,bv);
/*
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D( 0.0, rv, bv, 0.0 );
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
*/
	glPushAttrib(GL_TRANSFORM_BIT);
	GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
//	glPushMatrix();
	glLoadIdentity();
    gluOrtho2D( 0.0f, viewport[2], viewport[3], 0.0f );
//	gluOrtho2D(viewport[0],viewport[2],viewport[1],viewport[3]);
	glPopAttrib();
//	glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT  | GL_ENABLE_BIT | GL_TRANSFORM_BIT);	
	glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	float modelview_matrix[16];	
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

//	glPushMatrix();
 	glLoadIdentity();
    glMultMatrixf(modelview_matrix);


  //glDrawBuffer( GL_FRONT );
//  glEnable(GL_CULL_FACE);
//  glPolygonMode( GL_FRONT,GL_FILL );
}

void enddrawing(void)
{
  glViewport(0,0,width,height);
  /*
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  */
//  glPopMatrix();
  glPushAttrib(GL_TRANSFORM_BIT);
  glMatrixMode(GL_PROJECTION);
//  glPopMatrix();
  glPopAttrib();
}

void setpixel(int x, int y, COLORREF color, int alpha)
{
  begindrawing();
  glPushMatrix();
  glBegin( GL_POINTS );
  glColor4ub( GetRValue(color), GetGValue(color), GetBValue(color), alpha );
  glVertex2i( x, y );
  glEnd();
  glPopMatrix();
  enddrawing();
}


void subrecttess(int x0,int y0,int x1,int y1)
{
  subrect_x0 = x0;
  subrect_y0 = y0;
  subrect_x1 = x1;
  subrect_y1 = y1;
}

void fillrecttess(int x0, int y0, int x1, int y1, COLORREF color, int alpha)
{
  GLUtesselator *t;
  
  GLdouble rect[4][3];
  GLdouble subrect[4][3];
  
  tessrect_x0 = x0;
  tessrect_y0 = y0;
  tessrect_x1 = x1;
  tessrect_y1 = y1;
  
  tessrect_color = color;
  tessrect_alpha = alpha;

  rect[0][0] = tessrect_x0;
  rect[0][1] = tessrect_y0;
  rect[0][2] = 0;
  rect[1][0] = tessrect_x1;
  rect[1][1] = tessrect_y0;
  rect[1][2] = 0;
  rect[2][0] = tessrect_x1;
  rect[2][1] = tessrect_y1;
  rect[2][2] = 0;
  rect[3][0] = tessrect_x0;
  rect[3][1] = tessrect_y1;
  rect[3][2] = 0;
  
  subrect[0][0] = subrect_x0;
  subrect[0][1] = subrect_y0;
  subrect[0][2] = 0;
  subrect[1][0] = subrect_x1;
  subrect[1][1] = subrect_y0;
  subrect[1][2] = 0;
  subrect[2][0] = subrect_x1;
  subrect[2][1] = subrect_y1;
  subrect[2][2] = 0;
  subrect[3][0] = subrect_x0;
  subrect[3][1] = subrect_y1;
  subrect[3][2] = 0;
  
  glPushMatrix();  
  {
  
  t = gluNewTess();
  glColor4ub( GetRValue(color), GetGValue(color), GetBValue(color), alpha );
  
  gluTessCallback(t, GLU_TESS_VERTEX, (void (__stdcall*)(void))vertexCallback);
  gluTessCallback(t, GLU_TESS_BEGIN, (void (__stdcall*)(void))beginCallback);
  gluTessCallback(t, GLU_TESS_END, (void (__stdcall*)(void))endCallback);
  gluTessCallback(t, GLU_TESS_ERROR, (void (__stdcall*)(void))errorCallback);
  gluTessCallback(t, GLU_TESS_COMBINE, (void (__stdcall*)(void))combineCallback);
//  gluTessProperty(t, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_POSITIVE);
  gluTessBeginPolygon(t, NULL);
     gluTessBeginContour(t);
       for (int i=0;i<4;i++) gluTessVertex(t, (double*)&rect[i], (double*)&rect[i]);
     gluTessEndContour(t);
     gluTessBeginContour(t);
       for (int i=0;i<4;i++) gluTessVertex(t, (double*)&subrect[i], (double*)&subrect[i]);
     gluTessEndContour(t);
  gluTessEndPolygon(t);
  gluDeleteTess(t);
  
  }
  glPopMatrix();

}



int _glutBitmapWidthString( void *font, char *s )
{
  char *p = s;
  int  width = 0;

  while( *p != '\0' )  {
    width += glutBitmapWidth( font, (unsigned char)*p );
    p++;
  }

  return width;
}

void _glutBitmapString( void *font, char *s )
{
  char *p = s;

  while( *p != '\0' )  {
    glutBitmapCharacter( font, (unsigned char)*p );
    p++;
  }
}

void draw_string( char *text )
{
  _glutBitmapString( get_font(), text );
}

void draw_char( char c )
{
  glutBitmapCharacter( get_font(), c );
}

int string_width( char *text )
{
  return _glutBitmapWidthString( get_font(), text );
}

int char_width( char c )
{
  return glutBitmapWidth( get_font(), c );
}

/*
GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
    BuildFont(12,FW_NORMAL);  
    char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
    KillFont();

}
*/

int textwidth(char *text)
{
    if (text == "\r") return 0;
    if (text == "\t") return 0;
    if (text == "\n") return 0;
    if (text == NULL) return 0;
    if (strlen(text)==0) return 0;
    return _glutBitmapWidthString( get_font(),text); //glutBitmapLength(GLUT_BITMAP_HELVETICA_18,(const unsigned char *)text);
}

void textattr(COLORREF color, int alpha, int height, int weight)
{
fontcolor = color;
fontalpha = alpha;
fontheight = height;
fontweight = weight;
}

void textout(int x, int y, char *text)
{
  if (text == "\r") return;
  if (text == "\t") return;
  if (text == "\n") return;
  if (text == NULL) return;
  if (strlen(text)==0) return;
  if (fontweight == FW_BOLD) setviewport(x,getscreenheight()-(y+12),textwidth(text),12);
  else setviewport(x,getscreenheight()-(y+12),textwidth(text),12);
  begindrawing();
  
  glPushMatrix();

//   glColor4ub(255,255,255,255);
   glColor4ub(GetRValue(fontcolor),GetGValue(fontcolor),GetBValue(fontcolor),fontalpha);
   
if (fontweight == FW_BOLD)
{
    glPopMatrix();
    enddrawing();
    setviewport(0,0,getscreenwidth(),getscreenheight());

    consoletextcolor(fontcolor);
    consoletextout(x,y+3,text);

    begindrawing();
    glPushMatrix();
/*
    glRasterPos2i(0, 12);
    //glRasterPos2i(x, y+12);
    BuildFont(fontheight,fontweight);  
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
    KillFont();
 */
}
else
{
//  int w=0,h=0;
//  font->getTextSizeI(text,w,h);
//  font->render(text, x, y+h);
	
	int i,n;
  
	n = strlen(text);
    
    glRasterPos2i(0, 12);

	//glRasterPos2d(x,y+(glutBitmapLength(get_font(),(const unsigned char *)"A")*1.25));
/*	for (i=0;i<n;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,(int)text[i]);
    }
    */
    _glutBitmapString(get_font(),text);
	
}
  glPopMatrix();
  
  enddrawing();
  setviewport(0,0,getscreenwidth(),getscreenheight());
}

void wraptextout(int x, int y, char *text)
{
  if (text == "\r") return;
  if (text == "\t") return;
  if (text == "\n") return;
  if (text == NULL) return;
  if (strlen(text)==0) return;
  if (fontweight == FW_BOLD) setviewport(x,getscreenheight()-(y+12),textwidth(text),12);
  else setviewport(x,getscreenheight()-(y+12),textwidth(text),12);
  begindrawing();
  
  glPushMatrix();

//   glColor4ub(255,255,255,255);
   glColor4ub(GetRValue(fontcolor),GetGValue(fontcolor),GetBValue(fontcolor),fontalpha);
   
if (fontweight == FW_BOLD)
{
    glPopMatrix();
    enddrawing();
    setviewport(0,0,getscreenwidth(),getscreenheight());

    consoletextcolor(fontcolor);
    consoletextout(x,y+3,text);

    begindrawing();
    glPushMatrix();
/*
    glRasterPos2i(0, 12);
    //glRasterPos2i(x, y+12);
    BuildFont(fontheight,fontweight);  
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
    KillFont();
*/
}
else
{
//  int w=0,h=0;
//  font->getTextSizeI(text,w,h);
//  font->render(text, x, y+h);
	
	int i,n;
  
	n = strlen(text);
    
    glRasterPos2i(0, 12);

	//glRasterPos2d(x,y+(glutBitmapLength(get_font(),(const unsigned char *)"A")*1.25));
	for (i=0;i<n;i++)
	{
		glutBitmapCharacter(get_font(),(int)text[i]);
    }
    
    // _glutBitmapString(get_font(),text);
	
}
  glPopMatrix();
  
  enddrawing();
  setviewport(0,0,getscreenwidth(),getscreenheight());
}


