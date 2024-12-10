// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "checkbox.h" // class's header file

bool cbcontrolon = false;
void rendercheckbox(TControl *sender)
{
TCheckBox* cb = dynamic_cast <TCheckBox*>((TCheckBox*)sender);
 bool onctrl = sender->IsInControl(sender);
 int bctl = 1;
 int wcaph = (sender->window->height-sender->window->clientheight);
 if ((sender->window->borderstyle != bsNone)&&(windowmanager == 1)) wcaph += 1;

 bool isinwin = false;
  if (windows[activewindow]!=sender->window)
  {
   if (sender->window->IsInWindow(windows[activewindow]))
   {
     isinwin = false;
   } else isinwin = true;
  } else isinwin = true;
  
 int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
  
 if (sender->visible)
 { 
 if (windowresize || (windowresizeside>0)) isinwin = false;

 int l = sender->window->left+sender->left-1;
 int t = sender->window->top+wcaph+sender->top-1;
 int w = sender->width+1;
 int h = sender->height+2;
 glEnable(GL_SCISSOR_TEST);
 glScissor(l,height-(t+h+1),w,h+1); 

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
 
 if (sender->flat) bctl = 7;
 else bctl = 1;
 
 if (mouseb==0)
 {
  bool chk = cb->checked;
  if ((sender->IsInControl(sender)==true)&&(!(windowresize || (windowresizeside>0))))
  {
    //  for (int i=0;i<sender->window->numcheckboxes;i++) sender->window->checkboxes[i]->focused = false;
      if ((cbcontrolon == true)&&(sender->focus)&&(!(windowresize || (windowresizeside>0))))
      {
       //  sender->clicked = true;     
       //  sender->focused = true;
         if (onctrl) cb->checked = !cb->checked;
      }
  } else
  {
    if ((sender->IsInControl(sender)==false)&&(!(windowresize || (windowresizeside>0)))) cb->checked = chk;
  //  sender->clicked = true;     
  //  sender->focused = false;
  }
 }
 if (mouseb==1)
 {
  if ((sender->IsInControl(sender)==true)&&(!(windowresize || (windowresizeside>0))))
  {
      for (int i=0;i<sender->window->numcheckboxes;i++) sender->window->checkboxes[i]->focused = false;
      sender->clicked = true;     
      if (isinwin) sender->focused = true;
      if ((sender->flat==true)&&(isinwin)) bctl = 1;
  } else
  { 
    if (cbcontrolon) sender->focused = false;
    sender->clicked = true;     
  }
 } else
 {
   sender->clicked = false;
   if ((sender->IsInControl(sender)==true)&&(isinwin)) bctl = 1;
 }

drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,16,16,bctl,alphacontrol);

COLORREF bkcolor = clWhite;

/*
// Default Windows CheckBox Style
if (mouseb==1) 
{
 if (sender->IsInControl(sender)==true) bkcolor = clBtnFace;
 else bkcolor = clWhite;
}
*/

 fillrect(((sender->window->left+sender->left)+1),((sender->window->top+wcaph+sender->top+2)+2),((sender->window->left+sender->left+16)-2),((sender->window->top+wcaph+sender->top+2+16)-2),bkcolor,alphacontrol);

if (cb->checked) drawimage(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,checkedicon,sender->alphavalue,true,clLime);
if (windows[activewindow]==sender->window)
{
if (sender->window->IsInWindow(windows[activewindow]))
if (mouseb==1) 
{
 if ((sender->IsInControl(sender)==true)&&(!(windowresize))) drawimagemask(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,checkedicon,sender->alphavalue,clGray,true,clLime);
} else cb->focus = false;
} else cb->focus = false;

textattr(clBlack,alphacontrol,12,FW_NORMAL);
textout(sender->window->left+sender->left+24,sender->window->top+wcaph+sender->top+1,sender->caption);

if (sender->focused) rectangledotted(sender->window->left+sender->left+24,sender->window->top+wcaph+sender->top+1,sender->window->left+sender->left+24+(textwidth(sender->caption)),sender->window->top+wcaph+sender->top+1+16,clBlack,alphacontrol);
glDisable(GL_SCISSOR_TEST);
//cbcontrolon = false;
//sender->clicked = false;
}

}

TCheckBox::TCheckBox(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="checkbox";
          visible = false;
          left=0;
          top=0;
          width=128;
          height=32;
          alphavalue = window->alphavalue;
          caption="checkbox";
          checked = false;
          focused = false;
          render = rendercheckbox;
          controlid = window->numcontrols;
          handleid = window->numcheckboxes;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->checkboxes[window->numcheckboxes] = this;
          window->numcheckboxes++;
          window->numcontrols++;
}

void TCheckBox::rendercontrol()
{
if ((visible==true)&&(window->visible==true))
{
if (visible)
{
  render(this);
  hintcontrol(this);
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
    
  } //else focused = false;
//}
} //else focused = false;

if (mouseb==1)
{
  if (IsInControl(this)==true)
  {
    focus = true;  
  } else focus = false;
  if (focus==true)
  {
    clicked = true;
  }
}
if ((focus==true)&&(focused==true)&&(clicked==true)&&(cbcontrolon==true))
{
if (IsInControl(this)==true)
{    
  if (onclick != NULL) onclick(this);
  cbcontrolon = false;
  clicked = false;
  cbcontrolon = false;
}
} //else focused = false;
}
}
instance = this;
window->checkboxes[handleid] = this;
}
void TCheckBox::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->checkboxes[handleid] = this;
  }
}
void TCheckBox::hide()
{
          visible = false;
          window->checkboxes[handleid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createcheckbox(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int chkboxid = 0;
   chkboxid = windows[winid]->numcheckboxes;
   TCheckBox* checkbox = new TCheckBox(windows[winid]);
   checkbox->alphavalue = 255;
   checkbox->enabled = true;
   checkbox->width=72;
   checkbox->height=24;
   checkbox->left=32;
   checkbox->top=32;
   checkbox->visible = false;
   return chkboxid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

