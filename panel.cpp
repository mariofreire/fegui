// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "panel.h" // class's header file

bool panelcontrolon = false;
void renderpanel(TControl *sender)
{
    TPanel* panel = dynamic_cast <TPanel*>((TPanel*)sender);
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
           if (panelcontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           panelcontrolon = false;
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
       
       if (panel->borderstyle==bsSingle)
       {
        drawcontroledge(l,t,w,h,14,a);
        fillrect(l,t+1,l+w-1,t+h-1,panel->color,a);
        l+=2;
        t+=2;
        w-=5;
        h-=3;
        if (panel->bevelouter==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (panel->bevelouter==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (panel->bevelouter==bvSpace) drawcontroledge(l,t,w,h,6,a);
        fillrect(l,t+1,l+w-1,t+h-1,panel->color,a);
        if (panel->bevelouter!=bvNone)
        {
         l++;
         t++;
         w-=2;
         h-=2;
        } 
        if (panel->bevelinner==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (panel->bevelinner==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (panel->bevelinner==bvSpace) drawcontroledge(l,t,w,h,6,a);
        fillrect(l,t+1,l+w-1,t+h-1,panel->color,a);
       }
       else
       {
        if (panel->bevelouter==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (panel->bevelouter==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (panel->bevelouter==bvSpace) drawcontroledge(l,t,w,h,6,a);
        if (panel->bevelouter==bvLowered) fillrect(l,t+1,l+w-1,t+h-1,panel->color,a);
        else fillrect(l,t+1,l+w-1,t+h,panel->color,a);
        if (panel->bevelouter!=bvNone)
        {
         l++;
         t++;
         w-=2;
         h-=2;
        }
        if (panel->bevelinner==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (panel->bevelinner==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (panel->bevelinner==bvSpace) drawcontroledge(l,t,w,h,6,a);
        if (panel->bevelinner==bvLowered) fillrect(l,t+1,l+w-1,t+h-1,panel->color,a);
        else fillrect(l,t+1,l+w-1,t+h,panel->color,a);
       } 
       int cw = textwidth(sender->caption)+1;
       int ch = 16;
       textattr(clBlack,a,12,FW_NORMAL);
       textout(sender->window->left+sender->left+((sender->width-(cw))/2),sender->window->top+wcaph+sender->top+((sender->height-(ch))/2),sender->caption);
       glDisable(GL_SCISSOR_TEST);
    }
}

TPanel::TPanel(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="panel";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=128;
          parent = window;
          alphavalue = window->alphavalue;
          color = clBtnFace;
          caption="panel";
          borderstyle = bsNone;
          bevelinner = bvNone;
          bevelouter = bvRaised;
          render = renderpanel;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->panels[window->numpanels] = this;
          window->numpanels++;
          window->numcontrols++;
}

void TPanel::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(panelcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) panelcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->panels[controlid] = this;
}
void TPanel::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->panels[controlid] = this;
  }
}
void TPanel::hide()
{
          visible = false;
          window->panels[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createpanel(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int btnid = 0;
   btnid = windows[winid]->numpanels;
   TPanel* panel = new TPanel(windows[winid]);
   panel->alphavalue = 255;
   panel->enabled = true;
   panel->width=72;
   panel->height=24;
   panel->left=32;
   panel->top=32;
   panel->visible = false;
   return btnid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

