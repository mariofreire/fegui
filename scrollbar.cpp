// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "scrollbar.h" // class's header file


bool sbarcontrolon = false;

int twinklecnt=0;

int lbdd=0,rbdi=0;
int sbbd = 0;

void renderscrollbar(TControl* sender)
{
     TScrollBar *sbar = dynamic_cast <TScrollBar*>((TScrollBar*)sender);
     int l=0,t=0,w=0,h=0;
     int lbd=0,rbd=0;
     int flbdd=0,frbdi=0;
     int state=0;
     int wcaph=sender->window->height-sender->window->clientheight;//21;
     int sbbctl=11;
     int sbcon=0;
 
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
 
 int l = sender->window->left+sender->left-2;
 int t = sender->window->top+wcaph+sender->top-2;
 int w = sender->width+3;
 int h = sender->height+3;
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
 
     l = sender->window->left+sender->left;
     t = sender->window->top+wcaph+sender->top;
     w = sender->width;
     h = sender->height;
     
     if (sender->flat)
     {
        sbbctl = 6;
     }
     else sbbctl = 11;
     
     if (sender->flat)
     {
      if (getarea(l,t,w,h)&&(!sender->window->modalhalt))
      {
       sbbctl = 11;
       sbcon = 1;
      } else
      {
       sbcon = 0;
      }
     }
     else
     {
       sbbctl = 11;
       sbcon = 0;
     }
     
     if (sender->flat)
     {
      if (!isinwin)
      {
        sbbctl = 6;
        sbcon = 0;
      }
     }

     if (mouseb)
     {
       if (getarea(l,t,w,h)&&(!sender->window->modalhalt))
       {
         sender->window->activecontrol = sender->controlid;
       } else
       {
         sender->focus = false;
       }
     }
     
     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
      if (sbar->twinkle)
      {
        if (twinklecnt >= 100) twinklecnt = 0;
      } else twinklecnt = 0;
     }
     
     if (sbar->kind == sbHorizontal)
     {
     if (sbar->showborder)
     {
      rectangle(l+1,t+1,l+w+1,t+h+1,clBtnHighlight,alphacontrol);
      rectangle(l,t,l+w,t+h,clBtnShadow,alphacontrol);
     }
     l++;
     t++;
     h-=2;
     fillrect(l,t,l+w-1,t+h+1,clWhite,alphacontrol);
     fillrectpattern(l,t,l+w-1,t+h+1,clBtnFace,alphacontrol);
     w = 20;
     
     if (getarea(l,t,w,h)&&(!sbbd)&&(mouseb)&&(isinwin)&&(!sender->window->modalhalt)) lbd = 1;
     else lbd = 0;
     if (lbd) state = 1;
     else state = 0;
     
     drawcontroledge(l,t,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl+state,alphacontrol);
     drawimage(l-(1-lbd),((t+((sender->height-20)/2))-(1-lbd))+1,leftarrowicon,sender->alphavalue,true,clLime);
     l += (sender->width-w);
     if (getarea(l,t,w,h)&&(!sbbd)&&(mouseb)&&(isinwin)&&(!sender->window->modalhalt)) rbd = 1;
     else rbd = 0;
     if (rbd) state = 1;
     else state = 0;
     

     drawcontroledge(l,t,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl+state,alphacontrol);
     drawimage(l-(1-rbd),((t+((sender->height-20)/2))-(1-rbd))+1,rightarrowicon,sender->alphavalue,true,clLime);
     l = (sender->window->left+sender->left+w+1);
     
     int sbminmax = sbar->max-sbar->min;
     
     int sm = 0;
     if (sbminmax>200) sm = 2;
     if ((sbminmax>100)&&(sbminmax<200)) sm = 1;
     if (sbminmax<50) sm = 1;
     if (sbminmax==1) sm = 0;
     
     int smax = SolveForY(sender->width-(60-sm),sbminmax);
     l += SolveForX(sbar->position,smax);
     if (sbminmax>100)
     {
      if (l > ((sender->window->left+sender->left+sender->width)-40)-1) l = ((sender->window->left+sender->left+sender->width)-40)+1;
     }
     if (l > ((sender->window->left+sender->left+sender->width)-40)) l = ((sender->window->left+sender->left+sender->width)-40)+1;
     if (l < ((sender->window->left+sender->left+20)+1)) l = (sender->window->left+sender->left+20)+1;
     if (l < 0) l = 0;

     drawcontroledge(l,t,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl,alphacontrol);

     if ((activewindow==sender->window->windowid)&&(sender->focus)&&(!(windowresize)))
     {
      if ((sbar->twinkle) && ((sender->window->activecontrol==-1)||(sender->focus)))
      {
        if (twinklecnt >= 50) fillrectpattern((l+1)-(sender->flat-sbcon),(t+2)-(sender->flat-sbcon),(l+w-3)+(sender->flat-sbcon),(t+h)+(sender->flat-sbcon),cl3DDkShadow,alphacontrol);
      }
      if (sbar->twinkle) twinklecnt++;
     }
     
     
     
     
     }
     else if (sbar->kind == sbVertical)
     {
          
          
          
          
     if (sbar->showborder)
     {
      rectangle(l+1,t+1,l+w+1,t+h+1,clBtnHighlight,alphacontrol);
      rectangle(l,t,l+w,t+h,clBtnShadow,alphacontrol);
     }
     l++;
     t++;
     h-=2;
     fillrect(l-1,t,l+w-1,t+h+1,clWhite,alphacontrol);
     fillrectpattern(l-1,t,l+w-1,t+h+1,clBtnFace,alphacontrol);
     h = 20;
     h-=2;
     
     if (getarea(l,t,w,h)&&(!sbbd)&&(mouseb)&&(isinwin)&&(!sender->window->modalhalt)) lbd = 1;
     else lbd = 0;
     if (lbd) state = 1;
     else state = 0;

     drawcontroledge(l,t,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl+state,alphacontrol);
     drawimage((l+((sender->width-20)/2))-(1-lbd),(t-(1-lbd))+1,uparrowicon,sender->alphavalue,true,clLime);
     t += (sender->height-h)-2;
     if (getarea(l,t,w,h)&&(!sbbd)&&(mouseb)&&(isinwin)&&(!sender->window->modalhalt)) rbd = 1;
     else rbd = 0;
     if (rbd) state = 1;
     else state = 0;
     drawcontroledge(l,t,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl+state,alphacontrol);
     drawimage((l+((sender->width-20)/2))-(1-rbd),(t-(1-rbd))+1,downarrowicon,sender->alphavalue,true,clLime);
     t = (((sender->window->top+sender->top+h)+wcaph)+1);
     
     int sbminmax = sbar->max-sbar->min;
     
     int sm = 0;
     if (sbminmax>200) sm = 2;
     if ((sbminmax>100)&&(sbminmax<200)) sm = 1;
     if (sbminmax<50) sm = 1;
     if (sbminmax==1) sm = 0;
     
     int smax = SolveForY((sender->height+2)-(60-sm),sbminmax);
     t += SolveForX(sbar->position,smax);
     
     if (sbminmax>100)
     {
      if (t > (((sender->window->top+sender->top+sender->height)+wcaph)-40)-1) t = (((sender->window->top+sender->top+sender->height)+wcaph)-40)+1;
     }
     if (t > (((sender->window->top+sender->top+sender->height)+wcaph)-40)) t = (((sender->window->top+sender->top+sender->height)+wcaph)-40)+1;
     if (t <= (((sender->window->top+sender->top+wcaph)+20)+1)) t = (((sender->window->top+sender->top+wcaph)+20)+1);
     if (t < 0) t = 0;
     
     
     drawcontroledge(l,t,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl,alphacontrol);

     if ((activewindow==sender->window->windowid)&&(sender->focus)&&(!(windowresize)))
     {
      if ((sbar->twinkle) && ((sender->window->activecontrol==-1)||(sender->focus)))
      {
        if (twinklecnt >= 50) fillrectpattern((l+1)-(sender->flat-sbcon),(t+2)-(sender->flat-sbcon),(l+w-3)+(sender->flat-sbcon),(t+h)+(sender->flat-sbcon),cl3DDkShadow,alphacontrol);
      }
      if (sbar->twinkle) twinklecnt++;
     }
     }

     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
     if (!sbar->fastchange)
     {
      if (lbd)
      {
        if (lbdd > 10) lbdd = 0;
        flbdd = (lbdd == (10-4));
      } else lbdd = 0;
      if (rbd)
      {
        if (rbdi > 10) rbdi = 0;
        frbdi = (rbdi == (10-4));
      } else rbdi = 0;
     } else
     {
      if (lbd)
      {
       lbdd = 1;
       flbdd = 1;
      }
      else
      {
       lbdd = 0;
       flbdd = 1;
      }
      if (rbd)
      {
       rbdi = 1;
       frbdi = 1;
      }
      else
      {
       rbdi = 0;
       frbdi = 1;
      }
     }
     }
     
     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
     if (lbd && (lbdd==flbdd))
     {
      if (sbar->position>sbar->min)
      {
        sbar->position -= sbar->smallchange;
        if (sbar->onchange) sbar->onchange(sbar);
        lbdd=0;
      }
     }
     }
     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
     if (rbd && (rbdi==frbdi))
     {
      if (sbar->position<sbar->max)
      {
        sbar->position += sbar->smallchange;
        if (sbar->onchange) sbar->onchange(sbar);
        rbdi=0;
      }
     }
     }
     
     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
     if (!sbar->fastchange)
     {
       if (lbd)
       {
         lbdd++;
       }     
       if (rbd)
       {
         rbdi++;
       }
     }
     }
     
     if (isinwin)
     {
     
     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
     if (sbar->kind == sbHorizontal)
     {
       int sbd = 0;
       l = sender->window->left+sender->left;
       t = sender->window->top+wcaph+sender->top;
       w = sender->width;
       h = sender->height;
       
       l += 20;
       w = 20;
       
       if (mouseb)
       {
        if (((mousex > l) && (mousex < (sender->window->left+sender->left+sender->width-20)))&&((mousey > t)&&(mousey < (t+h))))
        {
          sbd = 1;
          sbbd = 1;
        } else sbd = 0;        
       } else
       {
          sbd = 0;
          sbbd = 0;
       }
       
       if (sbbd)
       {
         sbar->position = SolveForX(SolveForY(((mousex-l)+1),sender->width-60)-10,sbar->max);
         if (sbar->position <= sbar->min) sbar->position = sbar->min;
         if (sbar->position >= sbar->max) sbar->position = sbar->max;
         if (sbar->onchange) sbar->onchange(sbar);
       }
       
     }


     if (sbar->kind == sbVertical)
     {
       int sbd = 0;
       l = sender->window->left+sender->left;
       t = sender->window->top+wcaph+sender->top;
       w = sender->width;
       h = sender->height;
       
       t += 20;
       h = 20;
       
       if (mouseb)
       {
        if (((mousex > l)&&(mousex < (l+w)))&&((mousey > t) && (mousey < ((sender->window->top+sender->top+sender->height+wcaph)-20))))
        {
          sbd = 1;
          sbbd = 1;
        } else sbd = 0;        
       } else
       {
          sbd = 0;
          sbbd = 0;
       }
       
       if (sbbd)
       {
         sbar->position = SolveForX(SolveForY(((mousey-t)+1),sender->height-60)-10,sbar->max);
         if (sbar->position <= sbar->min) sbar->position = sbar->min;
         if (sbar->position >= sbar->max) sbar->position = sbar->max;
         if (sbar->onchange) sbar->onchange(sbar);
       }
       
     }
     }
     }
     
 glDisable(GL_SCISSOR_TEST);
 }    
     

}

TScrollBar::TScrollBar(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="scrollbar";
          visible = false;
          left=0;
          top=0;
          width=121;
          height=20;
          alphavalue = window->alphavalue;
          caption="scrollbar";
          pagesize = 0;
          twinkle = true;
          kind = sbHorizontal;
          min = 0;
          max = 100;
          position = 0;          
          smallchange = 1;
          largechange = 1;
          fastchange = false;
          showborder = true;
          render = renderscrollbar;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->scrollbars[window->numscrollbars] = this;
          window->numscrollbars++;
          window->numcontrols++;
}

void TScrollBar::rendercontrol()
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
if ((focused==true)&&(clicked==true)&&(sbarcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  sbarcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->scrollbars[controlid] = this;
}
void TScrollBar::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->scrollbars[controlid] = this;
  }
}
void TScrollBar::hide()
{
          visible = false;
          window->scrollbars[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createscrollbar(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int scrlbarid = 0;
   scrlbarid = windows[winid]->numscrollbars;
   TScrollBar* scrollbar = new TScrollBar(windows[winid]);
   scrollbar->alphavalue = 255;
   scrollbar->enabled = true;
   scrollbar->width=72;
   scrollbar->height=24;
   scrollbar->left=32;
   scrollbar->top=32;
   scrollbar->visible = false;
   return scrlbarid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

