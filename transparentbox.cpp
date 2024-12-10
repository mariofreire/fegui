// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "transparentbox.h" // class's header file
#include "console.h"


bool transparentboxcontrolon = false;
void rendertransparentbox(TControl *sender)
{
    TTransparentBox* transparentbox = dynamic_cast <TTransparentBox*>((TTransparentBox*)sender);
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    int wcaph = sender->window->height-sender->window->clientheight;
       
    if (sender->visible)
    {
       l0 = sender->window->left+sender->left;
       t0 = sender->window->top+wcaph+sender->top;
       w0 = sender->width;
       h0 = sender->height;
       l = l0;
       t = t0;
       w = w0;
       h = h0;

       if (transparentbox->window->windowstate == wsMinimized)
       {
         transparentbox->window->subtessleft=0;
         transparentbox->window->subtesstop=0;
         transparentbox->window->subtesswidth=0;
         transparentbox->window->subtessheight=0;
         return;
       }
       
       int bl=sender->window->left;
       int bt=sender->window->top+wcaph;
       int bw=sender->window->width;
       int bh=sender->window->height-wcaph;
       int scissorw = w;
       if ((l+w)>=(bl+bw)-5) scissorw = (bw-sender->left)-5;
       int scissorh = h;
       if ((t+h)>=(bt+bh)-5) scissorh = (bh-sender->top)-5;
       
       if (scissorw>bw-5) scissorw = bw-5;
       if (scissorh>bh-5) scissorh = bh-5;

       if (sender->parent != sender->window)
       {
        int lp = sender->window->left+sender->parent->left;
        int tp = sender->window->top+wcaph+sender->parent->top;
        int wp = sender->parent->width;
        int hp = sender->parent->height-1;
        int scissorw = wp;
        if ((lp+wp)>=(bl+bw)-13) scissorw = (bw-sender->left)-13;
        int scissorh = hp;
        if ((tp+hp)>=(bt+bh)-11) scissorh = (bh-sender->top)-11;
        glEnable(GL_SCISSOR_TEST);
        glScissor(lp-1,height-(tp+scissorh+1),scissorw+1,scissorh+1);
       }
       else
       {
        // glEnable(GL_SCISSOR_TEST);
        // glScissor(l-1,height-(t+scissorh+1),scissorw+1,scissorh+1);
        glEnable(GL_SCISSOR_TEST);
        if (!windowmanager) glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
        else
        {
          if (wcaph>0) glScissor(bl+1,height-(bt+bh-5),bw-6,bh+1);
          else glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
        }
       }

       glEnable(GL_SCISSOR_TEST);
       if (!windowmanager) glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
       else
       {
         if (wcaph>0) glScissor(bl+1,height-(bt+bh-5),bw-6,bh+1);
         else glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
       }

       int bctl = 18;
       
       if (sender->flat)
       {
         if (sender->IsInControl(sender)) bctl = 18;
         else bctl = 16;
       }

       if (mouseb)
       {
         if (sender->IsInControl(sender))
         {
           if (transparentboxcontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           transparentboxcontrolon = false;
           sender->clicked = false;
           sender->focus = false;
           sender->focused = false;
         }
       }
       else
       {
           sender->clicked = false;
       }
       
       int a = blendto(sender->window->alphavalue,sender->alphavalue);
       
       if (transparentbox->borderstyle==bsSingle)
       {
        drawcontroledge(l,t+3,w,h,bctl,a);
        transparentbox->window->subtessleft=sender->left+1;
        transparentbox->window->subtesstop=sender->top+6;
        transparentbox->window->subtesswidth=sender->width-3;
        transparentbox->window->subtessheight=sender->height-4;
        fillrect(l+1,t+5,l+w-2,t+h+1,transparentbox->color,blendto(a,transparentbox->backgroundalpha));
       }
       else
       {
        transparentbox->window->subtessleft=sender->left+1;
        transparentbox->window->subtesstop=sender->top+6;
        transparentbox->window->subtesswidth=sender->width-3;
        transparentbox->window->subtessheight=sender->height-4;
        fillrect(l+1,t+5,l+w-2,t+h+1,transparentbox->color,blendto(a,transparentbox->backgroundalpha));
       }
       
       int cw = textwidth(sender->caption)+1;
       int ch = 16;
       consoletextcolor(RGB(224,224,224));
       if (cblinkcnt > 64) cblinkcnt = 0;
       consoletextfont("GLUT_BITMAP_8_BY_13");
       consoletextout(sender->window->left+sender->left+6,sender->window->top+wcaph+sender->top+(sender->height-12)-3,sender->caption);
       consoletextcolor(clWhite);
       char* cblinkstr = "_";
       if (cblinkcnt & 16) consoletextout((sender->window->left+sender->left+6)+(consoletextwidth(sender->caption)),sender->window->top+wcaph+sender->top+(sender->height-12)-3,cblinkstr);
       cblinkcnt++;
       consoletextfont("");

       //textattr(clWhite,a,12,FW_NORMAL);
       //textout(sender->window->left+sender->left+((sender->width-(cw))/2),sender->window->top+wcaph+sender->top+((sender->height-(ch))/2),sender->caption);


if (transparentbox->window->windowstate != wsMinimized)
{
 begindrawing();

  int l=0,t=0,w=0,h=0,bw=0,bh=0,lw=0,rw=0;
  glPushMatrix ();
//  glViewport(this->left,(-this->top+this->height-32),this->width,this->height);
 // glTranslated(this->left,this->top,0);
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
 // gluPerspective(45.0, width/height, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth

  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View
  
  bw = sender->width;//this->width-this->clientwidth;
  bh = sender->height;//this->height-this->clientheight;
  if (windowmanager == 0) bh -= windowtopbarheightdefault;

  if ((transparentbox->borderstyle == bsNone)&&(windowmanager == 1)) lw = 6;
  else lw = 2;

            glPushMatrix ();
            glPopMatrix ();

  if ((transparentbox->borderstyle == bsNone)&&(windowmanager == 1)) lw = 6;
  else lw = 2;

  if ((transparentbox->borderstyle == bsNone)&&(windowmanager == 1)) rw = 12;
  else rw = 8;

       l0 = sender->window->left+sender->left;
       t0 = sender->window->top+wcaph+sender->top-((wcaph/2)+4);
       if (windowmanager == 0) t0 += 14;
       w0 = sender->width-2;
       h0 = sender->height-wcaph;
       if (windowmanager == 0) h0 -= windowtopbarheightdefault+14;
       l = l0+2;
       t = (getscreenheight()-t0)+2;
       w = w0-3;
       h = h0+((wcaph/2)+6);
       t-=h+wcaph;
       l-=1;
       t-=1;
       h+=2;
       w+=2;

  glPushMatrix ();
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
  //gluPerspective(45.0, (float)w/(float)h, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth
  glViewport(l,t,w,h);
//  gluOrtho2D( 0.0,w,h,0.0 );

  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View
            glScissor(l,t,w,h);
            glPushMatrix ();
            if (transparentbox->window->windowstate != wsMinimized)
            {
              if (transparentbox->visible && transparentbox->enabled)
              {
                if (transparentbox->onrender) transparentbox->onrender(transparentbox);
              }
            }
            glPopMatrix ();

            glPopMatrix ();
            glPopMatrix ();
}


       glDisable(GL_SCISSOR_TEST);
    }
}

TTransparentBox::TTransparentBox(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="transparentbox";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=128;
          backgroundalpha=255;
          parent = window;
          alphavalue = window->alphavalue;
          color = clBtnFace;
          caption="transparentbox";
          borderstyle = bsSingle;
          render = rendertransparentbox;
          controlid = window->numcontrols;
          onrender = NULL;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->transparentboxes[window->numtransparentboxes] = this;
          window->numtransparentboxes++;
          window->numcontrols++;
}

void TTransparentBox::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(transparentboxcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) transparentboxcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->transparentboxes[controlid] = this;
}
void TTransparentBox::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->transparentboxes[controlid] = this;
  }
}
void TTransparentBox::hide()
{
          visible = false;
          window->transparentboxes[controlid] = this;

}


#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createtransparentbox(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int transparentboxid = 0;
   transparentboxid = windows[winid]->numtransparentboxes;
   TTransparentBox* transparentbox = new TTransparentBox(windows[winid]);
   transparentbox->alphavalue = 255;
   transparentbox->backgroundalpha = 192;
   transparentbox->enabled = true;
   transparentbox->width=128;
   transparentbox->height=128;
   transparentbox->left=32;
   transparentbox->top=32;
   transparentbox->visible = false;
   return transparentboxid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)
