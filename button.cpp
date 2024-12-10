// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "button.h" // class's header file
#include "blend.h"
#include "tooltip.h"
#include "gfx.h"
#include "font.h"
#include "screen.h"
#include "mouse.h"

int string_width( char *text );


bool bcontrolon = false;
bool btncontrolon = false;
int btnfocus = -1;
void renderbutton(TControl *sender)
{
char sbuf[256];
int l=0,t=0;
int w=0,h=0;
int wintopbarh = sender->window->height-sender->window->clientheight;
int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
//if (!windowmanager) wintopbarh = 0;
/*
l = 0;
t = 0;
w = 800;
h = 600;

if (sender->top > ((sender->window->height-sender->height)-wintopbarh))
{
t = (((sender->window->height)+(sender->height*2+wintopbarh))-(sender->window->top-25));
h = 600-t;
}
if (sender->top < 0)
{
 t = 0;
 h = 0;
}
if (sender->height < 0)
{
 t = 0;
 h = 0;
}
*/
//setviewport(l,t,w,h);

 l=sender->window->left;
 t=sender->window->top+wintopbarh;
 w=sender->window->width;
 h=sender->window->height-wintopbarh;

int cw = textwidth(sender->caption)+1;//strlen(sender->caption)*4;
bool isinwin = false;

if (windows[activewindow]!=sender->window)
{
 if (sender->window->IsInWindow(windows[activewindow]))
 {
   isinwin = false;
 } else isinwin = true;
} else isinwin = true;
//bool isinwin = true;//false;
/*
if (activewindow==sender->window->windowid) isinwin = true;
else isinwin = isinotherwindow(sender->window);
*/

if (sender->visible == true)
{
if (windowresize || (windowresizeside>0)) isinwin = false;
if (!sender->enabled) isinwin = false;

int bl = sender->window->left+sender->left-1;
int bt = sender->window->top+wintopbarh+sender->top-1;
int bw = sender->width+1;
int bh = sender->height+2;
glEnable(GL_SCISSOR_TEST);
glScissor(bl,height-(bt+bh+1),bw,bh+1); 

glEnable(GL_SCISSOR_TEST);
if (!windowmanager) glScissor(l,height-(t+h-2),w-2,h+1);
else
{
if (wintopbarh>0) glScissor(l+1,height-(t+h-5),w-6,h+1);
else glScissor(l,height-(t+h-2),w-2,h+1);
}

if (mouseb==0) sender->clicked = false;
// controlon = false;
if (sender->window->activecontrol==sender->controlid)
{
sender->clicked = false;
if (mouseb==1)
{
sender->clicked = false;
btncontrolon = false;
if (sender->IsInControl(sender)==true)
{
for (int i=0;i<sender->window->numbuttons;i++) sender->window->buttons[i]->focused = false;
sender->window->buttons[sender->handleid]->focused = true;
sender->focused = true;
if (isinwin)
{
  if (sender->focus==true)
  {
  if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,9,alphacontrol); // sender->alphavalue-alphacontrol);
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,3,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else
  {
  if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,7,alphacontrol); // sender->alphavalue-alphacontrol);
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,1,alphacontrol); // sender->alphavalue-alphacontrol);
  }
} else
{
  if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
}
  sender->clicked = false;
  btncontrolon = true;
} else
{
if (isinwin)
{
  if (sender->flat)
  {
    if (sender->IsInControl(sender)==true) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,8,alphacontrol);
    else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,6,alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,2,alphacontrol); // sender->alphavalue-alphacontrol);
  sender->clicked = false;
  btncontrolon = false;
} else
{
  if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
}
}
}
else
{
if (isinwin)
{
  if (sender->focus==true)
  {
   if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,8,alphacontrol); // sender->alphavalue-alphacontrol);
   else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,2,alphacontrol); // sender->alphavalue-alphacontrol);
  } else
  {
   if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
   else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
  } 
if ((sender->IsInControl(sender)==true)&&(isinwin))
{
  if ((btncontrolon==true)&&(!sender->clicked)&&(bcontrolon==true))
  {
    sender->clicked = true;
    bcontrolon = false;
  }
  else sender->clicked = false;
}
} else
{
  sender->clicked = false;
  if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
}
}
}
else
{
sender->clicked = false;
if (mouseb==1)
{
if ((sender->IsInControl(sender)==true)&&(isinwin))
{
  sender->window->activecontrol = sender->controlid;
if (isinwin)
{
  if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,7,alphacontrol); // sender->alphavalue-alphacontrol);
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,1,alphacontrol); // sender->alphavalue-alphacontrol);
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2))+1,sender->window->top+wintopbarh+sender->top+((sender->height-12-3)/2)+1,sender->caption);
} else
{
  if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
}
} else 
{
  if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wintopbarh+sender->top+((sender->height-12-3)/2),sender->caption);
}
}
else
{
  sender->clicked = false;
  if (sender->flat) drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  if (sender->enabled) textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wintopbarh+sender->top+((sender->height-12-3)/2),sender->caption);
}
}
if ((mouseb==1)&&(isinwin))
{
if ((sender->IsInControl(sender)==false))
{
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wintopbarh+sender->top+((sender->height-12-3)/2),sender->caption);
}
else
{
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2))+1,sender->window->top+wintopbarh+sender->top+((sender->height-12-3)/2)+1,sender->caption);
}
}
else
{
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  if (sender->enabled) textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wintopbarh+sender->top+((sender->height-12-3)/2),sender->caption);
  else
  {
    textattr(clBtnHighlight,alphacontrol,12,FW_NORMAL);
    textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2))+1,sender->window->top+wintopbarh+sender->top+((sender->height-12-3)/2)+1,sender->caption);
    textattr(clBtnShadow,alphacontrol,12,FW_NORMAL);
    textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wintopbarh+sender->top+((sender->height-12-3)/2),sender->caption);
  }
}
if (mouseb==0)
{
if (btnfocus == sender->controlid)
{
   int ldot = sender->window->left+sender->left+((sender->width-string_width(sender->caption))/2);
   int tdot = sender->window->top+wintopbarh+sender->top+((sender->height-14)/2);
   int wdot = string_width(sender->caption);
   int hdot = 14;                                //cl3DDkShadow
   if (sender->enabled) rectangledotted(ldot,tdot,ldot+wdot,tdot+hdot,clBtnShadow,alphacontrol); // sender->alphavalue-alphacontrol);
}
}

if (isinwin)
{
 if (sender->flat)
 {
   if (sender->IsInControl(sender)==true)
   {
     sender->focus = true;
     sender->focused = true;
     sender->window->activecontrol = sender->controlid;
   } else
   {
     sender->focus = false;
     sender->focused = false;
   }
 }
}
glDisable(GL_SCISSOR_TEST);
}
//drawcontroledge(sender->window->left+sender->left,sender->window->top+wintopbarh+sender->top+110,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
//setviewport(0,0,getscreenwidth(),getscreenheight());
}


TButton::TButton(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="button";
          visible = false;
          enabled = true;
          left=0;
          top=0;
          width=64;
          height=128;
          alphavalue = window->alphavalue;
          caption="button";
          render = renderbutton;
          controlid = window->numcontrols;
          handleid = window->numbuttons;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->buttons[window->numbuttons] = this;
          window->numbuttons++;
          window->numcontrols++;
}

void TButton::rendercontrol()
{
if ((visible==true)&&(window->visible==true))
{
if (visible)
{
  render(this);
  hintcontrol(this);
}

if (activewindow != window->windowid)
{
if (mouseb==1) btnfocus = -1;
}

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

if (mouseb==1)
{
  if (IsInControl(this)==true)
  {
    focus = true;  
    if (activewindow==window->windowid) btnfocus = controlid;
    else btnfocus = -1;
  } else
  {
    btnfocus = -1;
    focus = false;
  }
}
if ((focused==true)&&(clicked==true)&&(btncontrolon==true)&&(!(windowresize || (windowresizeside>0))))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL)
  {
    btnfocus = controlid;
    onclick(this);
  }
  btncontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->buttons[handleid] = this;
}
void TButton::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->buttons[handleid] = this;
  }
}
void TButton::hide()
{
          visible = false;
          window->buttons[handleid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createbutton(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int btnid = 0;
   btnid = windows[winid]->numbuttons;
   TButton* button = new TButton(windows[winid]);
   button->alphavalue = 255;
   button->enabled = true;
   button->width=72;
   button->height=24;
   button->left=32;
   button->top=32;
   button->visible = false;
   return btnid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

