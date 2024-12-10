// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "progressbar.h" // class's header file

void fillrectprogressblock(int x0, int y0, int x1, int y1, int bw, int bh, int x, int y, int w, int h, TProgressBarOrientation o, COLORREF c, int a)
{
  if (o == pbHorizontal)
  {
     int lbw = bw;
     int rect_l=0,rect_t=0,rect_r=0,rect_b=0;
     if (lbw<1) lbw = 1;
     if (lbw>12) lbw = 12;
     rect_l = x0+x1;
     rect_t = y0;
     rect_r = x0+x1+lbw;
     rect_b = y0+y1+bh;
     if (rect_l<=x) rect_l = x;
     if (rect_t<=y) rect_t = y;
     if (rect_r>=((x+w)-3)) rect_r = ((x+w)-3);
     if (rect_b>=(y+h)) rect_b = y+h;
     fillrect(rect_l, rect_t, rect_r, rect_b, c, a);
  }
  else if (o == pbVertical) 
  {
     int lbh = bh;
     int rect_l=0,rect_t=0,rect_r=0,rect_b=0;
     if (lbh<1) lbh = 1;
     if (lbh>12) lbh = 12;
     rect_l=x0;
     rect_t=y0+y1;
     rect_r=x0+x1+bw;
     rect_b=y0+y1-lbh;
     int lh = lbh;
     if (lh<=4) lh = 6;
     else lh = 3;
     if (lbh<4) lh = 8;
     if (lbh==8) lh = 0;
     if (lbh==2) lh = 12;
     if (rect_t<=y-(lh/2)) 
     {
      if (rect_b<=y) rect_b = y-6;//((rect_b-rect_t)+1);
      if ((lbh>1)&&(lbh<4))
      {
       if ((rect_t-rect_b)>0) fillrect(rect_l, rect_t, rect_r, rect_b, c, a);
       return;
      }
      else
      if (lbh==1) 
      {
       if ((rect_t-rect_b)>0)
       {
         rect_b++;
         fillrect(rect_l, rect_t, rect_r, rect_b, c, a);
       }
       return;
      }
      else
      if (lbh==8) 
      {
       if ((rect_t-rect_b)>0) fillrect(rect_l, rect_t, rect_r, rect_b, c, a);
       return;
      }
      else
      fillrect(rect_l, rect_t, rect_r, rect_b, c, a);
     } else
     fillrect(rect_l, rect_t, rect_r, rect_b, c, a);
  }
}

void fillrectprogresshoriz(int x0, int y0, int x1, int y1, int l0, int t0, int w0, int h0, int blocksize, int step, int space, COLORREF color, int alpha)
{
//fillrect(x0, y0, x1, y1, color, alpha);

int i=0;
int x=0;
int s=0;
int l=0;
int cnt=0;
if (space>0) s = (space-1);
if (space>0) l = (space);
if (space>1) s = 1;
if (space>1) l = 2;
x = x1-x0;
cnt = x/(blocksize);
for (i=0;i<=cnt-s;i+=step) fillrectprogressblock(x0+(i*(blocksize/2)), y0, (i*((blocksize+l)/2)), y1-y0, (blocksize-1), 0, l0, t0, w0, h0, pbHorizontal, color, alpha);
}

void fillrectprogressvert(int x0, int y0, int x1, int y1, int l0, int t0, int w0, int h0, int blocksize, int step, int space, COLORREF color, int alpha)
{
//fillrect(x0, y0, x1, y1, color, alpha);

int i=0;
int y=0;
int s=0;
int l=0;
int cnt=0;
if (space>0) s = (space-1);
if (space>0) l = (space);
if (space>1) s = 1;
if (space>1) l = 2;
y = (y1-y0);
cnt = y/(blocksize);
for (i=0;i<=cnt-s;i+=step) fillrectprogressblock(x0, y0+h0-(i*(blocksize/2)), x1-x0, -(i*((blocksize+l)/2)), 0, (blocksize-1), l0, t0, w0, h0, pbVertical, color, alpha);
}

void fillrectprogress(int x0, int y0, int x1, int y1, int x, int y, int w, int h, TProgressBarOrientation orientation, int blocksize, int step, int space, COLORREF color, int alpha)
{
  if (orientation == pbHorizontal) fillrectprogresshoriz(x0, y0, x1, y1, x, y, w, h, blocksize, step, space, color, alpha);
  else if (orientation == pbVertical) fillrectprogressvert(x0, y0, x1, y1, x, y, w, h, blocksize, step, space, color, alpha);
}


bool progressbarcontrolon = false;

int progressbartwinklecnt=0;

int plbdd=0,prbdi=0;
int pbbd = 0;

void renderprogressbar(TControl* sender)
{
     TProgressBar *progressbar = dynamic_cast <TProgressBar*>((TProgressBar*)sender);
     int l=0,t=0,w=0,h=0;
     int lbd=0,rbd=0;
     int fplbdd=0,fprbdi=0;
     int state=0;
     int wcaph=sender->window->height-sender->window->clientheight;//21;
     int pbbctl=11;
     int pbcon=0;
 
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
     l = sender->window->left+sender->left;
     t = sender->window->top+wcaph+sender->top;
     w = sender->width;
     h = sender->height;
     
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
          
     
     if (sender->flat)
     {
        pbbctl = 6;
     }
     else pbbctl = 0;
     
     if (sender->flat)
     {
      if (getarea(l,t,w,h))
      {
       pbbctl = 0;
       pbcon = 1;
      } else
      {
       pbcon = 0;
      }
     }
     else
     {
       pbbctl = 0;
       pbcon = 0;
     }
     
     if (sender->flat)
     {
      if (!isinwin)
      {
        pbbctl = 6;
        pbcon = 0;
      }
     }
     
     pbbctl = 15;

     if (mouseb)
     {
       if (getarea(l,t,w,h))
       {
         sender->window->activecontrol = sender->controlid;
       } else
       {
         sender->focus = false;
       }
     }
     
     if ((activewindow==sender->window->windowid)&&(sender->focus))
     {
      if (progressbar->twinkle)
      {
        if (progressbartwinklecnt >= 100) progressbartwinklecnt = 0;
      } else progressbartwinklecnt = 0;
     }
     
     if (progressbar->orientation == pbHorizontal)
     {
       
       if (progressbar->showborder)  drawcontroledge(l,t,w,h,pbbctl+1,alphacontrol);       
       fillrect(l,t+1,l+w-1,t+h-1,progressbar->color,blendto(alphacontrol,progressbar->backgroundalpha));  
     
       int pw = 3;
     
       int pbminmax = progressbar->max-progressbar->min;
     
       int pm = 0;
       if (pbminmax>200) pm = 2;
       if ((pbminmax>100)&&(pbminmax<200)) pm = 1;
       if (pbminmax<50) pm = 1;
       if (pbminmax==1) pm = 0;

       int pmax = SolveForY(sender->width-(pm),(int)((float)pbminmax/(float)((float)progressbar->step/10)));
       pw += SolveForX((int)((float)progressbar->position/(float)((float)progressbar->step/10)),pmax);     
       if (pw >= w) pw = w;

       if (progressbar->smooth) fillrect(l+1,t+2,l+pw-2,t+h-2,progressbar->gaugecolor,alphacontrol);     
       else
       {
         if (progressbar->position > 0) fillrectprogress(l+1,t+2,l+(pw)-2,t+h-2,l+1,t+2,w,h,pbHorizontal,progressbar->blocksize,1,progressbar->blockspace,progressbar->gaugecolor,alphacontrol);
       }
     }
     else if (progressbar->orientation == pbVertical)
     {
          
       if (progressbar->showborder)  drawcontroledge(l,t,w,h,pbbctl+1,alphacontrol);    
       fillrect(l,t+1,l+w-1,t+h-1,progressbar->color,blendto(alphacontrol,progressbar->backgroundalpha));  
         
/*
     t = (((sender->window->top+sender->top+h)+wcaph)+1);
     
     int pbminmax = progressbar->max-progressbar->min;
     
     int pm = 0;
     if (pbminmax>200) pm = 2;
     if ((pbminmax>100)&&(pbminmax<200)) pm = 1;
     if (pbminmax<50) pm = 1;
     if (pbminmax==1) pm = 0;
     
     int pmax = SolveForY((sender->height+2)-(60-pm),pbminmax);
     t += SolveForX(progressbar->position,pmax);
     
     if (pbminmax>100)
     {
      if (t > (((sender->window->top+sender->top+sender->height)+wcaph)-40)-1) t = (((sender->window->top+sender->top+sender->height)+wcaph)-40)+1;
     }
     if (t > (((sender->window->top+sender->top+sender->height)+wcaph)-40)) t = (((sender->window->top+sender->top+sender->height)+wcaph)-40)+1;
     if (t <= (((sender->window->top+sender->top+wcaph)+20)+1)) t = (((sender->window->top+sender->top+wcaph)+20)+1);
     if (t < 0) t = 0;
     */
     
       int ph = 4;
     
       int pbminmax = progressbar->max-progressbar->min;
     
       int pm = 0;
       if (pbminmax>200) pm = 2;
       if ((pbminmax>100)&&(pbminmax<200)) pm = 1;
       if (pbminmax<50) pm = 1;
       if (pbminmax==1) pm = 0;
     
       int pmax = SolveForY((sender->height+2)-(pm),(int)((float)pbminmax/(float)((float)progressbar->step/10)));
       ph += SolveForX((int)((float)progressbar->position/(float)((float)progressbar->step/10)),pmax);
     
       if (ph >= h) ph = h;

       if (progressbar->smooth) fillrect(l+1,t+h-2,l+w-2,t+(h-(ph-4))-2,progressbar->gaugecolor,alphacontrol);     
       else 
       {
         if (progressbar->position > 0) fillrectprogress(l+1,t+1,l+w-2,t+ph-3,l+1,t+8,w,h-3,pbVertical,progressbar->blocksize,1,progressbar->blockspace,progressbar->gaugecolor,alphacontrol);
       }
     
     }
     
     
 }    
     

}



TProgressBar::TProgressBar(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="progressbar";
          visible = false;
          left=0;
          top=0;
          width=121;
          height=20;
          alphavalue = window->alphavalue;
          backgroundalpha = alphavalue;
          color = window->color;
          gaugecolor = clHighlight;
          caption="progressbar";
          step = 10;
          blocksize = 10;
          blockspace = 2;
          twinkle = false;
          smooth = false;
          orientation = pbHorizontal;
          min = 0;
          max = 100;
          position = 0;          
          showborder = true;
          render = renderprogressbar;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->progressbars[window->numprogressbars] = this;
          window->numprogressbars++;
          window->numcontrols++;
}

void TProgressBar::rendercontrol()
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
window->progressbars[controlid] = this;
}
void TProgressBar::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->progressbars[controlid] = this;
  }
}
void TProgressBar::hide()
{
          visible = false;
          window->progressbars[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createprogressbar(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int pbarid = 0;
   pbarid = windows[winid]->numprogressbars;
   TProgressBar* progressbar = new TProgressBar(windows[winid]);
   progressbar->alphavalue = 255;
   progressbar->enabled = true;
   progressbar->width=72;
   progressbar->height=24;
   progressbar->left=32;
   progressbar->top=32;
   progressbar->visible = false;
   return pbarid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

