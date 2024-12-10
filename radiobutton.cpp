// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "radiobutton.h" // class's header file

bool rbcontrolon = false;
void renderradiobutton(TControl *sender)
{
TRadioButton* rb = dynamic_cast <TRadioButton*>((TRadioButton*)sender);
 bool onctrl = sender->IsInControl(sender);
 int bctl = 1;
 int wcaph = sender->window->height-sender->window->clientheight;

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
  bool chk = rb->checked;
  if (sender->IsInControl(sender)==true)
  {
    //  for (int i=0;i<sender->window->numradiobuttons;i++) sender->window->radiobuttons[i]->focused = false;
       if ((rbcontrolon == true)&&(sender->focus))
       {
        //  sender->clicked = true;     
        //  sender->focused = true;
          if ((onctrl) && (!rb->checked) && (rb->groupindex==sender->window->radiobuttons[sender->handleid]->groupindex))
          {
             for (int i=0;i<sender->window->numradiobuttons;i++)
             {
               if ((sender->handleid != i) && (rb->groupindex==sender->window->radiobuttons[i]->groupindex))
               {
                 if (sender->window->radiobuttons[i]->checked) sender->window->radiobuttons[i]->checked = false;
               }
             }
             rb->checked = !rb->checked;
          }
       }
  } else
  {
    if (sender->IsInControl(sender)==false) rb->checked = chk;
  //  sender->clicked = true;     
  //  sender->focused = false;
  }
 }
 if (mouseb==1)
 {
  if (sender->IsInControl(sender)==true)
  {
      for (int i=0;i<sender->window->numradiobuttons;i++) sender->window->radiobuttons[i]->focused = false;
      sender->clicked = true;     
      if (isinwin) sender->focused = true;
      if ((sender->flat==true)&&(isinwin)) bctl = 1;
  } else
  { 
    if (rbcontrolon) sender->focused = false;
    sender->clicked = true;     
  }
 } else
 {
   sender->clicked = false;
   if ((sender->IsInControl(sender)==true)&&(isinwin)) bctl = 1;
 }

//drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,16,16,bctl,alphacontrol);
 if (bctl == 1) drawradioimage(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,radiobtn,sender->alphavalue,0x00F8F8F5,0x00F8F8F8,0x0099A8AC,0x00E2EFF1,0x00646F71, true, clLime);
 else drawflatradioimage(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,radiobtn,sender->alphavalue,0x00F8F8F5,0x00F8F8F8,0x0099A8AC,0x00E2EFF1,0x00646F71, true, clLime);

COLORREF bkcolor = clWhite;

if (rb->checked) drawimage(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,radioicon,sender->alphavalue,true,clLime);
if (windows[activewindow]==sender->window)
{
if (sender->window->IsInWindow(windows[activewindow]))
if (mouseb==1) 
{
 if (sender->IsInControl(sender)==true) drawimagemask(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,radioicon,sender->alphavalue,clSilver,true,clLime);
} else rb->focus = false;
} else rb->focus = false;

textattr(clBlack,alphacontrol,12,FW_NORMAL);
textout(sender->window->left+sender->left+24,sender->window->top+wcaph+sender->top+1,sender->caption);

if (windows[activewindow]==sender->window)
{
if (sender->focused) rectangledotted(sender->window->left+sender->left+24,sender->window->top+wcaph+sender->top+1,sender->window->left+sender->left+24+(textwidth(sender->caption)),sender->window->top+wcaph+sender->top+1+16,clBlack,alphacontrol);
}

//rbcontrolon = false;
//sender->clicked = false;
glDisable(GL_SCISSOR_TEST);
}

}

TRadioButton::TRadioButton(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="radiobutton";
          visible = false;
          left=0;
          top=0;
          width=128;
          height=32;
          alphavalue = window->alphavalue;
          caption="radiobutton";
          checked = false;
          groupindex = 0;
          focused = false;
          render = renderradiobutton;
          controlid = window->numcontrols;
          handleid = window->numradiobuttons;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->radiobuttons[window->numradiobuttons] = this;
          window->numradiobuttons++;
          window->numcontrols++;
}

void TRadioButton::rendercontrol()
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
if ((focus==true)&&(focused==true)&&(clicked==true)&&(rbcontrolon==true))
{
if (IsInControl(this)==true)
{    
  if (onclick != NULL) onclick(this);
  rbcontrolon = false;
  clicked = false;
  rbcontrolon = false;
}
} //else focused = false;
}
}
instance = this;
window->radiobuttons[handleid] = this;
}
void TRadioButton::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->radiobuttons[handleid] = this;
  }
}
void TRadioButton::hide()
{
          visible = false;
          window->radiobuttons[handleid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createradiobutton(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int rbtnid = 0;
   rbtnid = windows[winid]->numradiobuttons;
   TRadioButton* radiobutton = new TRadioButton(windows[winid]);
   radiobutton->alphavalue = 255;
   radiobutton->enabled = true;
   radiobutton->width=72;
   radiobutton->height=24;
   radiobutton->left=32;
   radiobutton->top=32;
   radiobutton->visible = false;
   return rbtnid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

