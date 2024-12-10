// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "toolbar.h" // class's header file

bool toolbarcontrolon = false;
bool toolbtncontrolon = false;



void rendertoolbar(TControl *sender)
{
    TToolBar* toolbar = dynamic_cast <TToolBar*>((TToolBar*)sender);
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
       
       if (IsInAnyMenu()) sender->focused = false;
       
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

       if (mouseb)
       {
         if (sender->IsInControl(sender))
         {
           if (toolbarcontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           toolbarcontrolon = false;
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
       
       if (toolbar->borderstyle==bsSingle)
       {
        drawcontroledge(l,t,w,h,14,a);
        fillrect(l,t+1,l+w-1,t+h-1,toolbar->color,a);
        l+=2;
        t+=2;
        w-=5;
        h-=3;
        if (toolbar->bevelouter==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (toolbar->bevelouter==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (toolbar->bevelouter==bvSpace) drawcontroledge(l,t,w,h,6,a);
        fillrect(l,t+1,l+w-1,t+h-1,toolbar->color,a);
        if (toolbar->bevelouter!=bvNone)
        {
         l++;
         t++;
         w-=2;
         h-=2;
        } 
        if (toolbar->bevelinner==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (toolbar->bevelinner==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (toolbar->bevelinner==bvSpace) drawcontroledge(l,t,w,h,6,a);
        fillrect(l,t+1,l+w-1,t+h-1,toolbar->color,a);
       }
       else
       {
        if (toolbar->bevelouter==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (toolbar->bevelouter==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (toolbar->bevelouter==bvSpace) drawcontroledge(l,t,w,h,6,a);
        if (toolbar->bevelouter==bvLowered) fillrect(l,t+1,l+w-1,t+h-1,toolbar->color,a);
        else fillrect(l,t+1,l+w-1,t+h,toolbar->color,a);
        if (toolbar->bevelouter!=bvNone)
        {
         l++;
         t++;
         w-=2;
         h-=2;
        }
        if (toolbar->bevelinner==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (toolbar->bevelinner==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (toolbar->bevelinner==bvSpace) drawcontroledge(l,t,w,h,6,a);
        if (toolbar->bevelinner==bvLowered) fillrect(l,t+1,l+w-1,t+h-1,toolbar->color,a);
        else fillrect(l,t+1,l+w-1,t+h,toolbar->color,a);
       } 
       int cw = textwidth(sender->caption)+1;
       int ch = 16;
       textattr(clBlack,a,12,FW_NORMAL);
       textout(sender->window->left+sender->left+((sender->width-(cw))/2),sender->window->top+wcaph+sender->top+((sender->height-(ch))/2),sender->caption);
       glDisable(GL_SCISSOR_TEST);
    }
}

TToolBar::TToolBar(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="toolbar";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=128;
          parent = window;
          alphavalue = window->alphavalue;
          color = clBtnFace;
          caption="toolbar";
          borderstyle = bsNone;
          bevelinner = bvNone;
          bevelouter = bvRaised;
          buttonwidth = 20;
          buttonheight = 20;
          ident = 0;
          dockmove = false;
          images = NULL;
          render = rendertoolbar;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->toolbars[window->numtoolbars] = this;
          window->numtoolbars++;
          window->numcontrols++;
}

void TToolBar::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(toolbarcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) toolbarcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->toolbars[controlid] = this;
}
void TToolBar::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->toolbars[controlid] = this;
  }
}
void TToolBar::hide()
{
          visible = false;
          window->toolbars[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createtoolbar(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int tbarid = 0;
   tbarid = windows[winid]->numtoolbars;
   TToolBar* toolbar = new TToolBar(windows[winid]);
   toolbar->alphavalue = 255;
   toolbar->enabled = true;
   toolbar->width=72;
   toolbar->height=24;
   toolbar->left=32;
   toolbar->top=32;
   toolbar->visible = false;
   return tbarid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

