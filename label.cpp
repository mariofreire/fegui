// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "label.h" // class's header file
#include "font.h"
#include "blend.h"
#include "screen.h"
#include "tooltip.h"
#include "mouse.h"


bool labelcontrolon = false;
void renderlabel(TControl *sender)
{
 TLabel* label = dynamic_cast <TLabel*>((TLabel*)sender);
 bool onctrl = sender->IsInControl(sender);
 int bctl = 1;
 int l=0,t=0,w=0,h=0;
 bool isinwin = false;
 int wcaph = (sender->window->height-sender->window->clientheight);
 if ((sender->window->borderstyle != bsNone)&&(windowmanager == 1)) wcaph -= 3;

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
     
     l = sender->window->left+sender->left;
     t = sender->window->top+wcaph+sender->top;
     w = sender->width;
     h = sender->height;
   glEnable(GL_SCISSOR_TEST);
   glScissor(l,height-(t+h),w,h+1);

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


   if (!label->transparent)
   {
     l = sender->window->left+sender->left;
     t = sender->window->top+wcaph+sender->top;
     w = sender->width;
     h = sender->height;
     fillrect(l+1,t+1,l+w-1,t+h-1,clBtnFace,alphacontrol);
   }

   //rectangle(l+1,t+1,l+w-1,t+h-1,clBlue,alphacontrol);

   textattr(clBlack,alphacontrol,12,FW_NORMAL);
   std::string slinecurrent;
   std::string sline[1024];
   int slinelastnl=0;
   int slinetcnt=0;
   int slinenlcnt=0;
   int slinecnt=0;
   int slinepos=0;
   char *slinec = (char*)sender->caption;
   bool ww = false;
     
     for (int i=0;i<strlen(sender->caption);i++)
     {
         if (label->wordwrap)
         {
           int charsperline = (int)(1.65*sender->width / 14);
           if ((textwidth((char*)sline[slinecnt].c_str()) >= sender->width-charsperline*4)&&(slinec[i-1] == ' ')) ww = true;
           else ww = false;
         }
         if ((slinec[i] == '\n')||(ww))
         {
           slinecnt++;
           sline[slinecnt] = slinec[i];
           slinepos=0;
         }
         else
         {
           sline[slinecnt] = sline[slinecnt] + slinec[i];
           slinepos++;
         }
     }
     slinecnt++;
     
     int slinehcnt = 0;
     int slinewcnt = 0;
     for (int i=0;i<slinecnt;i++)
     {
         textout(sender->window->left+sender->left+1,sender->window->top+wcaph+sender->top+1+(i*14),(char*)sline[i].c_str());
         int tw = textwidth((char*)sline[i].c_str());
         if (label->autosize) 
         {
           slinewcnt += tw*tw;
           slinehcnt += 16;
         }
     }
     if (label->autosize)
     {
       sender->width = sqrt(slinewcnt)+1;
       sender->height = slinehcnt+4;
     }
   glDisable(GL_SCISSOR_TEST);
 }
}

TLabel::TLabel(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="label";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=128;
          alphavalue = window->alphavalue;
          caption="label";
          transparent = true;
          wordwrap = false;
          autosize = true;
          render = renderlabel;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->labels[window->numlabels] = this;
          window->numlabels++;
          window->numcontrols++;
}

void TLabel::rendercontrol()
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
    
  } else focused = false;
//}
} else focused = false;

if (mouseb==1)
{
  if (IsInControl(this)==true)
  {
    focus = true;  
    
  } else focus = false;
}
if ((focused==true)&&(clicked==true)&&(labelcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  labelcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->labels[controlid] = this;
}
void TLabel::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->labels[controlid] = this;
  }
}
void TLabel::hide()
{
          visible = false;
          window->labels[controlid] = this;

}


#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createlabel(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int lblid = 0;
   lblid = windows[winid]->numlabels;
   TLabel* label = new TLabel(windows[winid]);
   label->alphavalue = 255;
   label->enabled = true;
   label->width=72;
   label->height=24;
   label->left=32;
   label->top=32;
   label->visible = false;
   return lblid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


