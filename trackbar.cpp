// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "trackbar.h" // class's header file

bool trackbarcontrolon = false;
void rendertrackbar(TControl *sender)
{
    TTrackBar* trackbar = dynamic_cast <TTrackBar*>((TTrackBar*)sender);
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
       
       if (trackbar->orientation == trHorizontal)
       {

       if (mouseb)
       {
         if (sender->IsInControl(sender))
         {
           if (trackbarcontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           trackbarcontrolon = false;
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
       
       if (sender->window->activecontrol==sender->controlid)
       {
         rectangledotted(l-2,t,l+w+2,t+h-1,cl3DDkShadow,a);
       }
       t++;
       
       int tbd=0;
       int tbbd=0;
       int bctl = 0;
       if (sender->flat) bctl = 6;
       if (sender->IsInControl(trackbar)) bctl = 0;
       int lslide=l+2;
       int tslide=t+3;
       int wslide=w-4;
       int hslide=h-((trackbar->thumblength/2)-1);
       int inctrl = 0;
       if ((sender->flat) && sender->IsInControl(trackbar)) inctrl = 1;
       
       // drawcontroledge(l,t,w,h,bctl+1,a);
       drawcontroledge(lslide,tslide,wslide,hslide,bctl+1,a);
       fillrect(lslide+1,tslide+2,lslide+2+wslide-4,tslide+2+hslide-(((trackbar->thumblength/2)/2)-1),clWhite,a);
       int lsbtn = lslide;
       int tsbtn = tslide-1;
       int wsbtn = (trackbar->thumblength/2)-2;
       int hsbtn = trackbar->thumblength-2;
       int lx = lslide;
       //lx += trackbar->position*trackbar->frequency;
     
       int tbminmax = trackbar->max-trackbar->min;
     
       int sm = 0;
       if (tbminmax>200) sm = 2;
       if ((tbminmax>100)&&(tbminmax<200)) sm = 1;
       if (tbminmax<50) sm = 1;
       if (tbminmax==1) sm = 0;
     
       int smax = SolveForY(sender->width-((wsbtn+4)-sm),tbminmax);
       lx += SolveForX(trackbar->position,smax);
       
       if (tbminmax>100)
       {
        if (lx > ((sender->window->left+sender->left+sender->width)-00)-1) lx = ((sender->window->left+sender->left+sender->width)-00)+1;
       }
       if (lx > ((sender->window->left+sender->left+sender->width)-00)) l = ((sender->window->left+sender->left+sender->width)-00)+1;
       if (lx < ((sender->window->left+sender->left+00)+1)) l = (sender->window->left+sender->left+00)+1;
       if (lx < 0) lx = 0;
       
       if (trackbar->IsInControl(trackbar))
       {

       if (mouseb)
       {
        if (((mousex > l) && (mousex < (sender->window->left+sender->left+sender->width)))&&((mousey > t)&&(mousey < (t+h))))
        {
          tbd = 1;
          tbbd = 1;
        } else tbd = 0;        
       } else
       {
          tbd = 0;
          tbbd = 0;
       }
       if (tbbd)
       {
         trackbar->position = SolveForX(SolveForY(((mousex-l)+1),sender->width-((wsbtn+4)/2)),trackbar->max);
         if (trackbar->position <= trackbar->min) trackbar->position = trackbar->min;
         if (trackbar->position >= trackbar->max) trackbar->position = trackbar->max;
         if (trackbar->onchange) trackbar->onchange(trackbar);
       }
       
       }

       drawcontroledge(lx,tsbtn-(1-inctrl),wsbtn,hsbtn+(1-inctrl),bctl,a);
       
       }
       else
       if (trackbar->orientation == trVertical)
       {

       if (mouseb)
       {
         if (sender->IsInControl(sender))
         {
           if (trackbarcontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           trackbarcontrolon = false;
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
       
       if (sender->window->activecontrol==sender->controlid)
       {
         rectangledotted(l-1,t,l+w-2,t+h+4,cl3DDkShadow,a);
       }
       t++;
       
       int tbd=0;
       int tbbd=0;
       int bctl = 0;
       if (sender->flat) bctl = 6;
       if (sender->IsInControl(trackbar)) bctl = 0;
       int lslide=l+2;
       int tslide=t+3;
       int wslide=w-((trackbar->thumblength/2)-1);
       int hslide=h-4;
       int inctrl = 0;
       if ((sender->flat) && sender->IsInControl(trackbar)) inctrl = 1;
       
       // drawcontroledge(l,t,w,h,bctl+1,a);
       drawcontroledge(lslide+2,tslide,wslide-2,hslide,bctl+1,a);
       fillrect(lslide+3,tslide+2,lslide+2+wslide-(((trackbar->thumblength/2)/2)-1),tslide+2+hslide-4,clWhite,a);
       int lsbtn = lslide;
       int tsbtn = tslide-1;
       int wsbtn = trackbar->thumblength-1;
       int hsbtn = (trackbar->thumblength/2)-2;
       int ty = tslide;
       //ty += trackbar->position*trackbar->frequency;
     
       int tbminmax = trackbar->max-trackbar->min;
     
       int sm = 0;
       if (tbminmax>200) sm = 2;
       if ((tbminmax>100)&&(tbminmax<200)) sm = 1;
       if (tbminmax<50) sm = 1;
       if (tbminmax==1) sm = 0;
     
       int smax = SolveForY(sender->height-((hsbtn+4)-sm),tbminmax);
       ty += SolveForX(trackbar->position,smax);
     
       if (tbminmax>100)
       {
        if (ty > (((sender->window->top+sender->top+sender->height)+wcaph)-00)-1) ty = (((sender->window->top+sender->top+sender->height)+wcaph)-00)+1;
       }
       if (ty > (((sender->window->top+sender->top+sender->height)+wcaph)-00)) ty = (((sender->window->top+sender->top+sender->height)+wcaph)-00)+1;
       if (ty <= (((sender->window->top+sender->top+wcaph)+00)+1)) ty = (((sender->window->top+sender->top+wcaph)+00)+1);
       if (ty < 0) ty = 0;

       if (trackbar->IsInControl(trackbar))
       {

       if (mouseb)
       {
        // if (((mousex > l) && (mousex < (sender->window->left+sender->left+sender->width)))&&((mousey > t)&&(mousey < (t+h))))
        if (((mousex > l)&&(mousex < (l+w)))&&((mousey > t) && (mousey < ((sender->window->top+sender->top+sender->height+wcaph)))))
        {
          tbd = 1;
          tbbd = 1;
        } else tbd = 0;        
       } else
       {
          tbd = 0;
          tbbd = 0;
       }
       if (tbbd)
       {
         trackbar->position = SolveForX(SolveForY(((mousey-t)+1),sender->height-((hsbtn+4)/2)),trackbar->max);
         if (trackbar->position <= trackbar->min) trackbar->position = trackbar->min;
         if (trackbar->position >= trackbar->max) trackbar->position = trackbar->max;
         if (trackbar->onchange) trackbar->onchange(trackbar);
       }
       
       }

       drawcontroledge(lsbtn,ty+inctrl,wsbtn,hsbtn-inctrl,bctl,a);
       
       }

       glDisable(GL_SCISSOR_TEST);
    }
}

TTrackBar::TTrackBar(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="trackbar";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=128;
          parent = window;
          alphavalue = window->alphavalue;
          color = clBtnFace;
          caption="trackbar";
          linesize = 1;
          frequency = 1;
          pagesize = 2;
          position = 0;
          max = 10;
          min = 0;
          orientation = trHorizontal;
          selstart = 0;
          selend = 0;
          slidervisible = true;
          thumblength = 20;
          render = rendertrackbar;
          handleid = window->numtrackbars;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          enabled = true;
          visible = false;
          instance = this;
          window->trackbars[window->numtrackbars] = this;
          window->numtrackbars++;
          window->numcontrols++;
}

void TTrackBar::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(trackbarcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) trackbarcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->trackbars[handleid] = this;
}
void TTrackBar::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->trackbars[handleid] = this;
  }
}
void TTrackBar::hide()
{
          visible = false;
          window->trackbars[handleid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createtrackbar(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int trkbarid = 0;
   trkbarid = windows[winid]->numtrackbars;
   TTrackBar* trackbar = new TTrackBar(windows[winid]);
   trackbar->alphavalue = 255;
   trackbar->enabled = true;
   trackbar->width=72;
   trackbar->height=24;
   trackbar->left=32;
   trackbar->top=32;
   trackbar->visible = false;
   return trkbarid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

