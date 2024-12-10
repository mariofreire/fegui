// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "groupbox.h" // class's header file
#include "cimp.h"
#include "gfx.h"
#include "blend.h"
#include "screen.h"
#include "mouse.h"
#include "msgbox.h"


bool groupboxcontrolon = false;
void rendergroupbox(TControl *sender)
{
    TGroupBox* groupbox = dynamic_cast <TGroupBox*>((TGroupBox*)sender);
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    int wcaph = (sender->window->height-sender->window->clientheight);
    if ((sender->window->borderstyle != bsNone)&&(windowmanager == 1)) wcaph -= 3;

    int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);

    if (sender->visible)
    {
       // if (windowresize || (windowresizeside>0)) isinwin = false;
       l0 = sender->window->left+sender->left;
       t0 = sender->window->top+wcaph+sender->top;
       w0 = sender->width;
       h0 = sender->height;
       l = l0;
       t = t0;
       w = w0;
       h = h0;

       int l1 = sender->window->left+sender->left-1;
       int t1 = sender->window->top+wcaph+sender->top-1;
       int w1 = sender->width+1;
       int h1 = sender->height+2;
       glEnable(GL_SCISSOR_TEST);
       glScissor(l1,height-(t1+h1+1),w1,h1+1); 

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
           if (groupboxcontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           groupboxcontrolon = false;
           sender->clicked = false;
           sender->focus = false;
           sender->focused = false;
         }
       }
       else
       {
           sender->clicked = false;
       }

       int cw = textwidth(sender->caption)+1;
       int ch = 16;
       
       t += ch;
       h -= ch;

       drawcontroledge(l,t,w,h,7,alphacontrol);
       drawcontroledge(l+1,t+1,w-2,h-3,6,alphacontrol);
       
       l += textwidth("A");
       t -= ch/2;
       
       fillrect(l-1,t,l+cw,t+ch,clBtnFace,alphacontrol);

       textattr(clBlack,alphacontrol,12,FW_NORMAL);
       textout(l,t,sender->caption);
       glDisable(GL_SCISSOR_TEST);
    }
}

TGroupBox::TGroupBox(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="groupbox";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=128;
          alphavalue = window->alphavalue;
          caption="groupbox";
          render = rendergroupbox;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->groupboxes[window->numgroupboxes] = this;
          window->numgroupboxes++;
          window->numcontrols++;
}

void TGroupBox::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(groupboxcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) groupboxcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->groupboxes[controlid] = this;
}
void TGroupBox::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->groupboxes[controlid] = this;
  }
}
void TGroupBox::hide()
{
          visible = false;
          window->groupboxes[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int creategroupbox(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int grpboxid = 0;
   grpboxid = windows[winid]->numgroupboxes;
   TGroupBox* groupbox = new TGroupBox(windows[winid]);
   groupbox->alphavalue = 255;
   groupbox->enabled = true;
   groupbox->width=72;
   groupbox->height=24;
   groupbox->left=32;
   groupbox->top=32;
   groupbox->visible = false;
   return grpboxid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

