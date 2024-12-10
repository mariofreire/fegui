// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "listscrollbar.h" // class's header file


bool lbsbarcontrolon = false;

int lbtwinklecnt=0;

int lblbdd=0,lbrbdi=0;
int lbsbbd = 0;

void renderlistscrollbar(TControl* sender)
{
     TListScrollBar *sbar = dynamic_cast <TListScrollBar*>((TListScrollBar*)sender);
     int l=0,t=0,w=0,h=0;
     int lbd=0,rbd=0;
     int flblbdd=0,flbrbdi=0;
     int state=0;
     int sbbctl=11;
     int sbcon=0;
     int wcaph = (sender->window->height-sender->window->clientheight);
//     if (sender->window->borderstyle != bsNone) wcaph -= 3;
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
     
     l = sender->window->left+sender->left;
     t = sender->window->top+wcaph+sender->top;
     w = sender->width;
     h = sender->height;
     glEnable(GL_SCISSOR_TEST);
     glScissor(l,height-(t+h+1),w,h+1);
     

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
        if (lbtwinklecnt >= 100) lbtwinklecnt = 0;
      } else lbtwinklecnt = 0;
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
     fillrect(l,t,l+w-1,t+h+2,clWhite,alphacontrol);
     fillrectpattern(l,t,l+w-1,t+h+2,clBtnFace,alphacontrol);
     w = 20;
     
     if (getarea(l,t,w,h)&&(!lbsbbd)&&(mouseb)&&(isinwin)&&(!sender->window->modalhalt)) lbd = 1;
     else lbd = 0;
     if (lbd) state = 1;
     else state = 0;
     
     drawcontroledge(l,t,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl+state,alphacontrol);
     drawimage(l-(1-lbd),((t+((sender->height-20)/2))-(1-lbd))+1,leftarrowicon,sender->alphavalue,true,clLime);
     l += (sender->width-w);
     if (getarea(l,t,w,h)&&(!lbsbbd)&&(mouseb)&&(isinwin)&&(!sender->window->modalhalt)) rbd = 1;
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
        if (lbtwinklecnt >= 50) fillrectpattern((l+1)-(sender->flat-sbcon),(t)-(sender->flat-sbcon),(l+w-3)+(sender->flat-sbcon),(t+h-1)+(sender->flat-sbcon),cl3DDkShadow,alphacontrol);
      }
      if (sbar->twinkle) lbtwinklecnt++;
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
     
     if (getarea(l,t,w,h)&&(!lbsbbd)&&(mouseb)&&(isinwin)&&(!sender->window->modalhalt)) lbd = 1;
     else lbd = 0;
     if (lbd) state = 1;
     else state = 0;

     drawcontroledge(l,t,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl+state,alphacontrol);
     drawimage(((l+((sender->width-20)/2))-(1-lbd)),(t-(1-lbd))+1,uparrowicon,sender->alphavalue,true,clLime);
     t += (sender->height-h)-2;
     if (getarea(l,t,w,h)&&(!lbsbbd)&&(mouseb)&&(isinwin)&&(!sender->window->modalhalt)) rbd = 1;
     else rbd = 0;
     if (rbd) state = 1;
     else state = 0;
     drawcontroledge(l,t-1,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl+state,alphacontrol);
     drawimage((l+((sender->width-20)/2))-(1-rbd),t-(1-rbd),downarrowicon,sender->alphavalue,true,clLime);
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
     if (t > (((sender->window->top+sender->top+sender->height)+wcaph)-40)) t = (((sender->window->top+sender->top+sender->height)+wcaph)-40);
     if (t <= (((sender->window->top+sender->top+wcaph)+20)+1)) t = (((sender->window->top+sender->top+wcaph)+20)+1);
     if (t < 0) t = 0;
     
     drawcontroledge(l,t,w-(sender->flat-sbcon),h+(sender->flat-sbcon),sbbctl,alphacontrol);

     if ((activewindow==sender->window->windowid)&&(sender->focus)&&(!(windowresize)))
     {
      if ((sbar->twinkle) && ((sender->window->activecontrol==-1)||(sender->focus)))
      {
        if (lbtwinklecnt >= 50) fillrectpattern((l+1)-(sender->flat-sbcon),(t)-(sender->flat-sbcon),(l+w-3)+(sender->flat-sbcon),(t+h-1)+(sender->flat-sbcon),cl3DDkShadow,alphacontrol);
      }
      if (sbar->twinkle) lbtwinklecnt++;
     }
     }

     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
     if (!sbar->fastchange)
     {
      if (lbd)
      {
        if (lblbdd > 10) lblbdd = 0;
        flblbdd = (lblbdd == (10-4));
      } else lblbdd = 0;
      if (rbd)
      {
        if (lbrbdi > 10) lbrbdi = 0;
        flbrbdi = (lbrbdi == (10-4));
      } else lbrbdi = 0;
     } else
     {
      if (lbd)
      {
       lblbdd = 1;
       flblbdd = 1;
      }
      else
      {
       lblbdd = 0;
       flblbdd = 1;
      }
      if (rbd)
      {
       lbrbdi = 1;
       flbrbdi = 1;
      }
      else
      {
       lbrbdi = 0;
       flbrbdi = 1;
      }
     }
     }
     
     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
     if (lbd && (lblbdd==flblbdd))
     {
      if (sbar->position>sbar->min)
      {
        sbar->position -= sbar->smallchange;
        lblbdd=0;
      }
     }
     }
     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
     if (rbd && (lbrbdi==flbrbdi))
     {
      if (sbar->position<sbar->max)
      {
        sbar->position += sbar->smallchange;
        lbrbdi=0;
      }
     }
     }
     
     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
     if (!sbar->fastchange)
     {
       if (lbd)
       {
         lblbdd++;
       }     
       if (rbd)
       {
         lbrbdi++;
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
          lbsbbd = 1;
        } else sbd = 0;        
       } else
       {
          sbd = 0;
          lbsbbd = 0;
       }
       
       if (lbsbbd)
       {
         sbar->position = SolveForX(SolveForY(((mousex-l)+1),sender->width-60)-10,sbar->max);
         if (sbar->position <= sbar->min) sbar->position = sbar->min;
         if (sbar->position >= sbar->max) sbar->position = sbar->max;
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
          lbsbbd = 1;
        } else sbd = 0;        
       } else
       {
          sbd = 0;
          lbsbbd = 0;
       }
       
       if (lbsbbd)
       {
         sbar->position = SolveForX(SolveForY(((mousey-t)+1),sender->height-60)-10,sbar->max);
         if (sbar->position <= sbar->min) sbar->position = sbar->min;
         if (sbar->position >= sbar->max) sbar->position = sbar->max;
       }
       
     }
     }
     }
     
     glDisable(GL_SCISSOR_TEST);
 }    
     

}

TListScrollBar::TListScrollBar(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="listboxscrollbar";
          visible = false;
          left=0;
          top=0;
          width=121;
          height=20;
          alphavalue = window->alphavalue;
          caption="listboxscrollbar";
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
          render = renderlistscrollbar;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
}

bool TListScrollBar::IsInListScrollBar(TControl* Control)
{
     

     int wt = Control->window->height-Control->window->clientheight;
     if ((Control->window->borderstyle != bsNone)&&(windowmanager == 1)) wt -= 3;
     if (((mousex>=(Control->window->left+Control->left))&&(mousey>=(Control->window->top+wt+Control->top)))&&(mousex<=(Control->window->left+Control->left+Control->width))&&(mousey<=(Control->window->top+Control->top+wt+Control->height)))
     {
       return true;
     }
     return false;
     
     
    // return IsInControl(Control);
}

void TListScrollBar::rendercontrol()
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
  if (IsInListScrollBar(this)==true)
  {
    focused = true;  
    
  } else focused = false;
//}
} else focused = false;

if (mouseb==1)
{
  if (IsInListScrollBar(this)==true)
  {
    focus = true;  
    
  } else focus = false;
}
if ((focused==true)&&(clicked==true)&&(lbsbarcontrolon==true))
{
if (IsInListScrollBar(this)==true)
{
  if (onclick != NULL) onclick(this);
  lbsbarcontrolon = false;
}
} else focused = false;
}
}
instance = this;
}
void TListScrollBar::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
  }
}
void TListScrollBar::hide()
{
          visible = false;

}

