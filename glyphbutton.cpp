// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "glyphbutton.h" // class's header file



void renderglyphbuttonimage(TControl *sender,TPicture* btnImage,int alphacontrol)
{
    TGlyphButton* glyphbutton = dynamic_cast <TGlyphButton*>((TGlyphButton*)sender);
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    int wcaph = sender->window->height-sender->window->clientheight;
       
    if ((sender->visible)&&(btnImage)&&(btnImage->canvas))
    {
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

       // fillrect(l,t+1,l+w-1,t+h-1,btnImage->canvas->brush->color,alphacontrol);
       // rectangle(l,t+1,l+w-1,t+h-1,btnImage->canvas->pen->color,alphacontrol);
       
       if (glyphbutton->center)
       {
         l += ((w-btnImage->canvas->width)/2)-1;
         t += ((h-btnImage->canvas->height)/2);
       }
       
       if (btnImage->textured)
       {
         int tx = l;
         int ty = t+1;
         int tw = btnImage->canvas->width;
         int th = btnImage->canvas->height;
         int texenabled = glIsEnabled(GL_TEXTURE_2D);
         glEnable(GL_TEXTURE_2D);
         begindrawing();
         glPushMatrix();
         glBindTexture(GL_TEXTURE_2D, btnImage->textureid);
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
         if (btnImage->canvas->format == IMAGE_RGB) drawimage32(l,t+1,btnImage->canvas->width,btnImage->canvas->height,btnImage->canvas->format,btnImage->canvas->pixels,alphacontrol,btnImage->transparent,btnImage->transparentcolor);
         else if (btnImage->canvas->format == IMAGE_RGBA) drawimage32(l,t+1,btnImage->canvas->width,btnImage->canvas->height,btnImage->canvas->format,btnImage->canvas->pixels,alphacontrol,btnImage->transparent,btnImage->transparentcolor);
       }

       //int cw = textwidth(sender->caption)+1;
       //int ch = 16;
       //textattr(clBlack,alphacontrol,12,FW_NORMAL);
       //textout(sender->window->left+sender->left+((sender->width-(cw))/2),sender->window->top+wcaph+sender->top+((sender->height-(ch))/2),sender->caption);
       glDisable(GL_SCISSOR_TEST);
    }
}

bool glyphfadebtndown=false;
bool glyphfadebtnup=false;

void renderglyphbutton(TControl *sender)
{
    TGlyphButton* glyphbutton = dynamic_cast <TGlyphButton*>((TGlyphButton*)sender);
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    int wcaph = sender->window->height-sender->window->clientheight;
       
    if (sender->visible)
    {
       int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
       int fadestep = glyphbutton->fadestep;
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
       
       if (mouseb)
       {
           if (sender->IsInControl(sender)) glyphbutton->glyphbuttoncontrolon = true;
           else glyphbutton->glyphbuttoncontrolon = false;
           sender->clicked = false;
       }
       else
       {
         if (sender->IsInControl(sender))
         {
           if (glyphbutton->glyphbuttoncontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           glyphbutton->glyphbuttoncontrolon = false;
           sender->clicked = false;
           sender->focus = false;
           sender->focused = false;
         }
       }

       if (glyphbutton->IsInControl(glyphbutton)) 
       {
        if (mouseb)
        {
          if (glyphbutton->fadebutton) 
          {
            if (glyphbutton->fadecount >= alphacontrol)
            {
              if (glyphfadebtndown == false) glyphbutton->fadecount = 0;
              glyphfadebtndown = true;
            }
            renderglyphbuttonimage(sender,glyphbutton->btnOver,alphacontrol-glyphbutton->fadecount);
            renderglyphbuttonimage(sender,glyphbutton->btnDown,glyphbutton->fadecount);
            if (glyphbutton->fadecount < alphacontrol) glyphbutton->fadecount += fadestep;
            if (glyphbutton->fadecount >= alphacontrol) glyphbutton->fadecount = alphacontrol;
          }
          else renderglyphbuttonimage(sender,glyphbutton->btnDown,alphacontrol);
        }
        else 
        {
          if (glyphbutton->fadebutton) 
          {
            if (glyphfadebtndown)
            {
              renderglyphbuttonimage(sender,glyphbutton->btnOver,alphacontrol-glyphbutton->fadecount);
              renderglyphbuttonimage(sender,glyphbutton->btnDown,glyphbutton->fadecount);
              if (glyphbutton->fadecount <= 0)
              {
                glyphfadebtnup = true;
                glyphfadebtndown = false;
              }
              if (glyphbutton->fadecount > 0) glyphbutton->fadecount -= fadestep;
              if (glyphbutton->fadecount <= 0) glyphbutton->fadecount = 0;
            }
            else
            {
              if (glyphfadebtnup)
              {
                glyphbutton->fadecount = alphacontrol;
                glyphfadebtnup = false;
              }
              renderglyphbuttonimage(sender,glyphbutton->btnNormal,alphacontrol-glyphbutton->fadecount);
              renderglyphbuttonimage(sender,glyphbutton->btnOver,glyphbutton->fadecount);
              if (glyphbutton->fadecount < alphacontrol) glyphbutton->fadecount += fadestep;
              if (glyphbutton->fadecount >= alphacontrol) glyphbutton->fadecount = alphacontrol;
            }
          }
          else 
          {
               renderglyphbuttonimage(sender,glyphbutton->btnOver,alphacontrol);
               glyphbutton->fadecount = 0;
               glyphfadebtndown = false;            
          }
        }
       }
       else 
       {
         if (glyphbutton->fadebutton)
         {
           renderglyphbuttonimage(sender,glyphbutton->btnOver,glyphbutton->fadecount);
           renderglyphbuttonimage(sender,glyphbutton->btnNormal,alphacontrol-glyphbutton->fadecount);
           if (glyphbutton->fadecount > 0) glyphbutton->fadecount -= fadestep;
           if (glyphbutton->fadecount <= 0) glyphbutton->fadecount = 0;
         }
         else 
         {
              renderglyphbuttonimage(sender,glyphbutton->btnNormal,alphacontrol);
              glyphbutton->fadecount = 0;
              glyphfadebtndown = false;            
         }
       }

       glDisable(GL_SCISSOR_TEST);
    }
}

void TGlyphButton::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(glyphbuttoncontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) glyphbuttoncontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->glyphbuttons[controlid] = this;
}
void TGlyphButton::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->glyphbuttons[controlid] = this;
  }
}
void TGlyphButton::hide()
{
          visible = false;
          window->glyphbuttons[controlid] = this;

}

TGlyphButton::TGlyphButton(TWindow *Window)
{
btnNormal = new TPicture();
btnDown = new TPicture();
btnOver = new TPicture();
btnUp = new TPicture();
btnOut = new TPicture();
window = Window;
id=window->numcontrols+100;
name="shape";
visible = false;
left=0;
top=0;
width=64;
height=64;
alphavalue = window->alphavalue;
fadecount = 0;
fadestep = 32;
fadebutton = true;
btnNormal->canvas->width = width;
btnNormal->canvas->height = height;
if (btnNormal->canvas->pixels) delete btnNormal->canvas->pixels;
btnNormal->canvas->pixels = new unsigned char [width*height*btnNormal->canvas->format];
btnDown->canvas->width = width;
btnDown->canvas->height = height;
if (btnDown->canvas->pixels) delete btnDown->canvas->pixels;
btnDown->canvas->pixels = new unsigned char [width*height*btnDown->canvas->format];
btnOver->canvas->width = width;
btnOver->canvas->height = height;
if (btnOver->canvas->pixels) delete btnOver->canvas->pixels;
btnOver->canvas->pixels = new unsigned char [width*height*btnOver->canvas->format];
btnUp->canvas->width = width;
btnUp->canvas->height = height;
if (btnUp->canvas->pixels) delete btnUp->canvas->pixels;
btnUp->canvas->pixels = new unsigned char [width*height*btnUp->canvas->format];
btnOut->canvas->width = width;
btnOut->canvas->height = height;
if (btnOut->canvas->pixels) delete btnOut->canvas->pixels;
btnOut->canvas->pixels = new unsigned char [width*height*btnOut->canvas->format];
glyphbuttoncontrolon = false;
render = renderglyphbutton;
controlid = window->numcontrols;
onclick = NULL;
onkeydown = NULL;
onkeyup = NULL;
visible = false;
instance = this;
window->glyphbuttons[window->numglyphbuttons] = this;
window->numglyphbuttons++;
window->numcontrols++;
}

TGlyphButton::~TGlyphButton()
{
delete btnNormal;
delete btnDown;
delete btnOver;
delete btnUp;
delete btnOut;
}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createglyphbutton(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int glybtnid = 0;
   glybtnid = windows[winid]->numglyphbuttons;
   TGlyphButton* glyphbutton = new TGlyphButton(windows[winid]);
   glyphbutton->alphavalue = 255;
   glyphbutton->enabled = true;
   glyphbutton->width=72;
   glyphbutton->height=24;
   glyphbutton->left=32;
   glyphbutton->top=32;
   glyphbutton->visible = false;
   return glybtnid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


