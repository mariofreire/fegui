// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "image.h" // class's header file



void drawimage32(int x, int y,int width,int height,int format,unsigned char *data,int alpha, bool transparent, COLORREF transparentcolor)
{
int cx,cy,index=0,c,r,g,b,a;
/*
  for(cy=0;cy<height;cy++)
  {
  for(cx=0;cx<width;cx++)
  {
    if (format == IMAGE_RGBA) a = data[index + 3];
    r = data[index + 2];
    g = data[index + 1];
    b = data[index + 0];
    c = RGB(r,g,b);
    if (format == IMAGE_RGBA)
    {
      if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(height-cy),c,a);
      else if (!transparent) setpixel(x+cx,y+(height-cy),c,a);
    } else
    {
      if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(height-cy),c,alpha);
      else if (!transparent) setpixel(x+cx,y+(height-cy),c,alpha);
    }
    index += format;
  }
  }*/
  
  char* img = (char*)malloc(width*height*4);

  for(cx=0;cx<width*height;cx++)
  {
    if (format == IMAGE_RGBA)
    {
      img[cx*4+0] = data[cx*4+0];
      img[cx*4+1] = data[cx*4+1];
      img[cx*4+2] = data[cx*4+2];
      img[cx*4+3] = data[cx*4+3];
      r = data[cx*4+0];
      g = data[cx*4+1];
      b = data[cx*4+2];
      a = data[cx*4+3];
    }
    else
    {
      img[cx*4+0] = data[cx*3+0];
      img[cx*4+1] = data[cx*3+1];
      img[cx*4+2] = data[cx*3+2];
      img[cx*4+3] = 255;
      r = data[cx*3+0];
      g = data[cx*3+1];
      b = data[cx*3+2];
      a = 255;
    }
    c = RGB(r,g,b);
    if (format == IMAGE_RGBA)
    {
      if ((transparent) && (c!=transparentcolor))
      {
        img[cx*4+0] = r;
        img[cx*4+1] = g;
        img[cx*4+2] = b;
        img[cx*4+3] = a;
      }
      else if (!transparent)
      {
        img[cx*4+0] = r;
        img[cx*4+1] = g;
        img[cx*4+2] = b;
        img[cx*4+3] = a;
      }
      else img[cx*4+3] = 0;
    } else
    {
      if ((transparent) && (c!=transparentcolor)) 
      {
        img[cx*4+0] = r;
        img[cx*4+1] = g;
        img[cx*4+2] = b;
        img[cx*4+3] = alpha;
      }
      else if (!transparent)
      {
        img[cx*4+0] = r;
        img[cx*4+1] = g;
        img[cx*4+2] = b;
        img[cx*4+3] = alpha;
      }
      else img[cx*4+3] = 0;
    }

  }
  setviewport(x,getscreenheight()-(y+height),width,height);
  begindrawing();
  glRasterPos2i(0, height);
  glDrawPixels(width,height,GL_RGBA,GL_UNSIGNED_BYTE,img);
  enddrawing();
  setviewport(0,0,getscreenwidth(),getscreenheight());
  free(img);

}

void drawimagemask32(int x, int y,int width,int height,int format,unsigned char *data,int alpha, COLORREF color, bool transparent, COLORREF transparentcolor)
{
int cx,cy,index=0,c,r,g,b,a;
/*
  for(cy=0;cy<height;cy++)
  {
  for(cx=0;cx<width;cx++)
  {
    if (format == IMAGE_RGBA) a = data[index + 3];
    r = data[index + 2];
    g = data[index + 1];
    b = data[index + 0];
    c = RGB(r,g,b);
    if (format == IMAGE_RGBA)
    {
      if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(height-cy),c,a);
      else if (!transparent) setpixel(x+cx,y+(height-cy),c,a);
    } else
    {
      if ((transparent) && (c!=transparentcolor)) setpixel(x+cx,y+(height-cy),c,alpha);
      else if (!transparent) setpixel(x+cx,y+(height-cy),c,alpha);
    }
    index += format;
  }
  }*/
  
  char* img = (char*)malloc(width*height*4);

  for(cx=0;cx<width*height;cx++)
  {
    if (format == IMAGE_RGBA)
    {
      img[cx*4+0] = data[cx*4+0];
      img[cx*4+1] = data[cx*4+1];
      img[cx*4+2] = data[cx*4+2];
      img[cx*4+3] = data[cx*4+3];
      r = data[cx*4+0];
      g = data[cx*4+1];
      b = data[cx*4+2];
      a = data[cx*4+3];
    }
    else
    {
      img[cx*4+0] = data[cx*3+0];
      img[cx*4+1] = data[cx*3+1];
      img[cx*4+2] = data[cx*3+2];
      img[cx*4+3] = 255;
      r = data[cx*3+0];
      g = data[cx*3+1];
      b = data[cx*3+2];
      a = 255;
    }
    c = RGB(r,g,b);
    if (format == IMAGE_RGBA)
    {
      if ((transparent) && (c!=transparentcolor))
      {
        img[cx*4+0] = GetRValue(color);
        img[cx*4+1] = GetGValue(color);
        img[cx*4+2] = GetBValue(color);
        img[cx*4+3] = a;
      }
      else if (!transparent)
      {
        img[cx*4+0] = GetRValue(color);
        img[cx*4+1] = GetGValue(color);
        img[cx*4+2] = GetBValue(color);
        img[cx*4+3] = a;
      }
      else img[cx*4+3] = 0;
    } else
    {
      if ((transparent) && (c!=transparentcolor)) 
      {
        img[cx*4+0] = GetRValue(color);
        img[cx*4+1] = GetGValue(color);
        img[cx*4+2] = GetBValue(color);
        img[cx*4+3] = alpha;
      }
      else if (!transparent)
      {
        img[cx*4+0] = GetRValue(color);
        img[cx*4+1] = GetGValue(color);
        img[cx*4+2] = GetBValue(color);
        img[cx*4+3] = alpha;
      }
      else img[cx*4+3] = 0;
    }
  }
  setviewport(x,getscreenheight()-(y+height),width,height);
  begindrawing();
  glRasterPos2i(0, height);
  glDrawPixels(width,height,GL_RGBA,GL_UNSIGNED_BYTE,img);
  enddrawing();
  setviewport(0,0,getscreenwidth(),getscreenheight());
  free(img);

}



bool imagecontrolon = false;
void renderimage(TControl *sender)
{
    TImage* image = dynamic_cast <TImage*>((TImage*)sender);
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    int wcaph = sender->window->height-sender->window->clientheight;
       
    if ((sender->visible)&&(image->picture)&&(image->picture->canvas))
    {
       int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
       l0 = sender->window->left+sender->left;
       t0 = sender->window->top+wcaph+sender->top;
       w0 = sender->width;
       h0 = sender->height;
       l = l0;
       t = t0;
       w = w0;
       h = h0;
       glEnable(GL_SCISSOR_TEST);
       glScissor(l-1,height-(t+h+1),w+1,h+1);

       int bl=sender->window->left;
       int bt=sender->window->top+wcaph;
       int bw=sender->window->width;
       int bh=sender->window->height-wcaph;

       glEnable(GL_SCISSOR_TEST);
       if (!windowmanager) glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
       else
       {
         if (wcaph>0) glScissor(bl+1,height-(bt+bh-5),bw-6,bh+1);
         else glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
       }
       
       if (mouseb)
       {
         if (sender->IsInControl(sender))
         {
           if (imagecontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           imagecontrolon = false;
           sender->clicked = false;
           sender->focus = false;
           sender->focused = false;
         }
       }
       else
       {
           sender->clicked = false;
       }

       // fillrect(l,t+1,l+w-1,t+h-1,image->picture->canvas->brush->color,alphacontrol);
       // rectangle(l,t+1,l+w-1,t+h-1,image->picture->canvas->pen->color,alphacontrol);
       
       if (image->center)
       {
         l += ((w-image->picture->canvas->width)/2)-1;
         t += ((h-image->picture->canvas->height)/2);
       }
       
       if (image->picture->textured)
       {
         int tx = l;
         int ty = t+1;
         int tw = image->picture->canvas->width;
         int th = image->picture->canvas->height;
         int texenabled = glIsEnabled(GL_TEXTURE_2D);
         glEnable(GL_TEXTURE_2D);
         begindrawing();
         glPushMatrix();
         glBindTexture(GL_TEXTURE_2D, image->picture->textureid);
         glColor4ub( 255, 255, 255, alphacontrol );
         glBegin(GL_QUADS);
          glTexCoord2i(0,0); glVertex2i(tx,             ty+th         );
          glTexCoord2i(1,0); glVertex2i(tx+tw,          ty+th         );
          glTexCoord2i(1,1); glVertex2i(tx+tw,          ty            );
          glTexCoord2i(0,1); glVertex2i(tx,             ty            );
         glEnd();
         glPopMatrix();
         enddrawing();
         if (texenabled) glEnable(GL_TEXTURE_2D);
         else glDisable(GL_TEXTURE_2D);
       }
       else
       {
         if (image->picture->canvas->format == IMAGE_RGB) drawimage32(l,t+1,image->picture->canvas->width,image->picture->canvas->height,image->picture->canvas->format,image->picture->canvas->pixels,alphacontrol,image->picture->transparent,image->picture->transparentcolor);
         else if (image->picture->canvas->format == IMAGE_RGBA) drawimage32(l,t+1,image->picture->canvas->width,image->picture->canvas->height,image->picture->canvas->format,image->picture->canvas->pixels,alphacontrol,image->picture->transparent,image->picture->transparentcolor);
       }

       //int cw = textwidth(sender->caption)+1;
       //int ch = 16;
       //textattr(clBlack,alphacontrol,12,FW_NORMAL);
       //textout(sender->window->left+sender->left+((sender->width-(cw))/2),sender->window->top+wcaph+sender->top+((sender->height-(ch))/2),sender->caption);
       glDisable(GL_SCISSOR_TEST);
    }
}

void TImage::rendercontrol()
{
if ((visible==true)&&(window->visible==true))
{
render(this);
hintcontrol(this);

if (activewindow==window->windowid)
{
if (window->activecontrol==controlid)
{
//if (mouseb==1)
//{
  if (IsInControl(this)==true)
  {
    focused = true;  
    
  } else focused = false;
//}
} else focused = false;

if ((focused==true)&&(clicked==true)&&(imagecontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) imagecontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->images[controlid] = this;
}
void TImage::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->images[controlid] = this;
  }
}
void TImage::hide()
{
          visible = false;
          window->images[controlid] = this;

}

TImage::TImage(TWindow *Window)
{
picture = new TPicture();
window = Window;
id=window->numcontrols+100;
name="image";
visible = false;
left=0;
top=0;
width=64;
height=64;
alphavalue = window->alphavalue;
picture->canvas->width = width;
picture->canvas->height = height;
if (picture->canvas->pixels) delete picture->canvas->pixels;
picture->canvas->pixels = new unsigned char [width*height*picture->canvas->format];
render = renderimage;
controlid = window->numcontrols;
onclick = NULL;
onkeydown = NULL;
onkeyup = NULL;
visible = false;
instance = this;
window->images[window->numimages] = this;
window->numimages++;
window->numcontrols++;
}

TImage::~TImage()
{
delete picture;
}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createimage(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int imgid = 0;
   imgid = windows[winid]->numimages;
   TImage* image = new TImage(windows[winid]);
   image->alphavalue = 255;
   image->enabled = true;
   image->width=72;
   image->height=24;
   image->left=32;
   image->top=32;
   image->visible = false;
   return imgid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

