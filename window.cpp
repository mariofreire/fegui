// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "window.h" // class's header file
#include "screen.h"
#include "mouse.h"
#include "hint.h"
#include "menu.h"
#include "gfx.h"
#include "viewport.h"
#include "image.h"
#include "button.h"
#include "speedbutton.h"
#include "glyphbutton.h"
#include "toolbutton.h"
#include "radiobutton.h"
#include "edit.h"
#include "listscrollbar.h"
#include "textbox.h"
#include "tooltip.h"
#include "keyboard.h"
#include "icons.h"
#include "bitmap.h"
#include "png.h"
#include "font.h"
#include "filesystem.h"
#include "canvas.h"
#include "groupbox.h"
#include "label.h"
#include "msgbox.h"
#include "imagelist.h"
#include "shape.h"
#include "updown.h"
#include "blend.h"
#include "picture.h"
#include "checkbox.h"
#include "combobox.h"
#include "listbox.h"
#include "panel.h"
#include "bevel.h"
#include "scrollbar.h"
#include "progressbar.h"
#include "timer.h"
#include "transparentbox.h"
#include "trackbar.h"
#include "dockbar.h"
#include "listview.h"
#include "toolbar.h"
#include "mainmenu.h"
#include "videoplayer.h"
#include "webbrowser.h"


bool windowmanager_crash = false;
int windowmanager = 1;

int windowmove = 0;
int windowresize = 0;

int activewindow=0;
int numwindows = 0;

bool WindowExists(TWindow* Window);

TWindow *windows[1024];

int windowresizeside = RESIZEWIN_NONE;

int isinuse=0;

COLORREF textcolor = RGB(255,255,255);

bool isinotherwindow(TWindow* win)
{
   bool isinwin = false;
   for (int i=0;i<numwindows;i++)
   {
 //  for (int j=numwindows-1;j>0;j--)
   {
       int l0=0, t0=0, w0=0, h0=0, l1=0, t1=0, w1=0, h1=0, l2=0, t2=0, w2=0, h2=0;
       
       l0 = win->left;
       t0 = win->top;
       w0 = win->width;
       h0 = win->height;
       
       l1 = windows[i]->left;
       t1 = windows[i]->top;
       w1 = windows[i]->width;
       h1 = windows[i]->height;
/*       
       l2 = windows[j]->left;
       t2 = windows[j]->top;
       w2 = windows[j]->width;
       h2 = windows[j]->height;
*/         
       isinwin = getintersectedarea(l0,t0,w0,h0,l1,t1,w1,h1);
/*
      // if (!isinwin)
       {
        // if (!windows[j]->focused) isinwin = getintersectedarea(l0,t0,w0,h0,l1,t1,w1,h1);
       //  else isinwin = getintersectedarea(l0,t0,w0,h0,l2,t2,w2,h2);
       }
    //   else isinwin = getintersectedarea(l0,t0,w0,h0,l1,t1,w1,h1);
*/
   }
   }
   return !isinwin;
}


bool pressclosebtn=false, closepressed = false;
bool pressmaximizebtn=false, maximizepressed = false;
bool pressminimizebtn=false, minimizepressed = false;

int ox = 0;
int oy = 0;
int ol = 0;
int ot = 0;
int windowtopbar = 1;
int windowtopbarheight = 22;
int windowtopbarheightdefault = 0;
bool winmove = false;
bool winresize = false;

void renderwindow(TWinControl* sender)
{
TWindow* win = dynamic_cast <TWindow*>((TWindow*)sender);
//  setviewport(sender->left,sender->top,sender->width,sender->height);
  int winwidth = sender->width-2;
  int winheight = sender->height-2;
  
  if ((win->borderstyle == bsNone)&&(windowmanager == 1)) windowtopbar = 0;
  else windowtopbar = 1;
  
  if (windowmanager == 0) windowtopbar = 0;
  
  if (windowmanager == 0) 
  {
    if (windowtopbarheight != 0) windowtopbarheightdefault = windowtopbarheight;
    windowtopbarheight = 0;
  }
  
  if (windowtopbar) sender->clientwidth = winwidth;
  else sender->clientwidth = sender->width;

  if (windowtopbar) sender->clientheight = winheight-windowtopbarheight;
  else sender->clientheight = winheight+1;
  
  if (windowmanager == 0) sender->clientheight = winheight-windowtopbarheight+1;
  
bool isinwin = false;

if (windows[activewindow]!=sender->window)
{
 if (sender->window->IsInWindow(windows[activewindow]))
 {
   isinwin = false;
 } else isinwin = false;
} else isinwin = true;
  
   if (mouseb)
   {
     if (getarea(sender->left,sender->top+1,winwidth,19)==false) isinwin = false;
     if (getarea(sender->left,sender->top+1,winwidth,19)==true)
     {
      if (isinwin)
      {
        if ((activewindow != sender->windowid)&&(!((windowresize) || (windowresizeside>0)))) activewindow = sender->windowid;
      }
     }
   }
   
   if (activewindow==win->windowid)
   {
     if (win->borderstyle == bsSizeable)
     {
       systemmenu->menu->items[0]->enabled = false;
       systemmenu->menu->items[1]->enabled = true;
       if (!win->freezing) systemmenu->menu->items[2]->enabled = true;
       else systemmenu->menu->items[2]->enabled = false;
       systemmenu->menu->items[3]->enabled = true;
       systemmenu->menu->items[4]->enabled = true;
       if (win->windowstate == wsMaximized)
       {
         systemmenu->menu->items[0]->enabled = true;
         systemmenu->menu->items[1]->enabled = false;
         systemmenu->menu->items[2]->enabled = false;
         systemmenu->menu->items[3]->enabled = true;
         systemmenu->menu->items[4]->enabled = false;
       }
       else
       if (win->windowstate == wsMinimized)
       {
         systemmenu->menu->items[0]->enabled = true;
         systemmenu->menu->items[1]->enabled = false;
         systemmenu->menu->items[2]->enabled = false;
         systemmenu->menu->items[3]->enabled = false;
         systemmenu->menu->items[4]->enabled = true;
       }
     }
     else 
     {
       systemmenu->menu->items[0]->enabled = false;
       systemmenu->menu->items[1]->enabled = true;
       systemmenu->menu->items[2]->enabled = false;
       systemmenu->menu->items[3]->enabled = false;
       systemmenu->menu->items[4]->enabled = false;
     }
   }
   
   int lw0=win->left;
   int tw0=win->top;
   int ww0=win->clientwidth;
   int wh0=win->clientheight+windowtopbarheight+1;
     
   if ((getarea(lw0-128,tw0-128,ww0+256,wh0+256))&&(!isinuse))
   {
    if ((win->borderstyle == bsSizeable)&&(win->windowstate != wsMaximized))
    {
     int lw=win->left;
     int tw=win->top;
     int ww=win->clientwidth;
     int wh=win->clientheight+windowtopbarheight+1;
     if (((!windowmove)&&(!sender->windowmove)) && (!win->freezing))
     {
      if (getarea(lw+ww-4,tw+wh-4,4,4)) windowresizeside = RESIZEWIN_SCALE;
      else
      {
       if (getarea(lw-4,tw-4,4,4)) windowresizeside = RESIZEWIN_LT;
       else if (getarea(lw+ww-4,tw-4,4,4)) windowresizeside = RESIZEWIN_WT;
       else if (getarea(lw-4,tw+wh-4,4,4)) windowresizeside = RESIZEWIN_LH;
       else if (getarea(lw-4,tw-4,4,wh+4)) windowresizeside = RESIZEWIN_LEFT;
       else if (getarea(lw-4,tw-4,ww+4,4)) windowresizeside = RESIZEWIN_TOP;
       else if (getarea(lw+ww-4,tw-4,4,wh+4)) windowresizeside = RESIZEWIN_WIDTH;
       else if (getarea(lw-4,tw+wh-4,ww+4,4)) windowresizeside = RESIZEWIN_HEIGHT;
       else windowresizeside = RESIZEWIN_NONE;
      }
     } else windowresizeside = RESIZEWIN_NONE;
     
     if (windowresizeside>0) winresize = true;
     
     if (windowmanager == 0)
     {
       windowresizeside = RESIZEWIN_NONE;
       winresize = false;
     }
     
     if((!isinuse) && (!win->freezing))
    // if (getarea((lw+ww)-128,(tw+wh)-128,256,256))
     {
       int wrsz = RESIZEWIN_NONE;
       if ((!windowmove)&&(!sender->windowmove))
       {
         if (getarea((lw)-32,(tw)-32,64,64)) wrsz = RESIZEWIN_LT;
         else if (getarea((lw+ww)-32,(tw)-32,64,64)) wrsz = RESIZEWIN_WT;
         else if (getarea((lw)-32,(tw+wh)-32,64,64)) wrsz = RESIZEWIN_LH;
         else if (getarea((lw+ww)-32,(tw+wh)-32,64,64)) wrsz = RESIZEWIN_SCALE;
         else if (getarea((lw)-32,(tw)-32,64,wh+64)) wrsz = RESIZEWIN_LEFT;
         else if (getarea((lw)-32,(tw)-32,ww+64,64)) wrsz = RESIZEWIN_TOP;
         else if (getarea((lw+ww)-32,(tw)-32,64,wh+64)) wrsz = RESIZEWIN_WIDTH;
         else if (getarea((lw)-32,(tw+wh)-32,ww+64,64)) wrsz = RESIZEWIN_HEIGHT;
         else wrsz = RESIZEWIN_NONE;
       } else wrsz = RESIZEWIN_NONE;
       
       if ((wrsz) && (!win->freezing))
       {
          if (activewindow==sender->windowid)
          {
           if (mouseb)
           {
             if (winresize)
             {
               switch (wrsz)
               {
                 case RESIZEWIN_LT:
                 {
                   windowresizeside = RESIZEWIN_LT;
                   break;
                 }
                 case RESIZEWIN_WT:
                 {
                   windowresizeside = RESIZEWIN_WT;
                   break;
                 }
                 case RESIZEWIN_LH:
                 {
                   windowresizeside = RESIZEWIN_LH;
                   break;
                 }
                 case RESIZEWIN_LEFT:
                 {
                   windowresizeside = RESIZEWIN_LEFT;
                   break;
                 }
                 case RESIZEWIN_TOP:
                 {
                   windowresizeside = RESIZEWIN_TOP;
                   break;
                 }
                 case RESIZEWIN_WIDTH:
                 {
                   windowresizeside = RESIZEWIN_WIDTH;
                   break;
                 }
                 case RESIZEWIN_HEIGHT:
                 {
                   windowresizeside = RESIZEWIN_HEIGHT;
                   break;
                 }
                 case RESIZEWIN_SCALE:
                 {
                   windowresizeside = RESIZEWIN_SCALE;
                   break;
                 }
               };
               windowresize = 1;
             }
           } else
           {
             if (winresize) winresize = false;
             else windowresize = false;
           }
          // else windowresize = 0;
          }// else windowresize = 0;
       }
       else
       {
        if(!isinuse)
        {
          switch(windowresizeside)
          {
            case RESIZEWIN_LT:
            {
             if (!getarea(lw-24,tw-24,48,48)) windowresize = 0;
             break;
            }
            case RESIZEWIN_WT:
            {
             if (!getarea(lw+ww-24,tw-24,48,48)) windowresize = 0;
             break;
            }
            case RESIZEWIN_LH:
            {
             if (!getarea(lw-24,tw+wh-24,48,48)) windowresize = 0;
             break;
            }
            case RESIZEWIN_LEFT:
            {
             if (!getarea(lw-24,tw-24,48,wh+48)) windowresize = 0;
             break;
            }
            case RESIZEWIN_TOP:
            {
             if (!getarea(lw-24,tw-24,ww+48,48)) windowresize = 0;
             break;
            }
            case RESIZEWIN_WIDTH:
            {
             if (!getarea(lw+ww-24,tw-24,48,wh+48)) windowresize = 0;
             break;
            }
            case RESIZEWIN_HEIGHT:
            {
             if (!getarea(lw-24,tw+wh-24,ww+48,48)) windowresize = 0;
             break;
            }
            case RESIZEWIN_SCALE:
            {
             if (!getarea(lw+ww-24,tw+wh-24,48,48)) windowresize = 0;
             break;
            }
          };
        }
       }
     }
     
    }
    else 
    {
     if(!isinuse)
     {     
        int lw=win->left;
        int tw=win->top;
        int ww=win->clientwidth;
        int wh=win->clientheight+windowtopbarheight+1;
        switch(windowresizeside)
        {
          case RESIZEWIN_LT:
          {
           if (!getarea(lw-24,tw-24,48,48)) windowresize = 0;
           break;
          }
          case RESIZEWIN_WT:
          {
           if (!getarea(lw+ww-24,tw-24,48,48)) windowresize = 0;
           break;
          }
          case RESIZEWIN_LH:
          {
           if (!getarea(lw-24,tw+wh-24,48,48)) windowresize = 0;
           break;
          }
          case RESIZEWIN_LEFT:
          {
           if (!getarea(lw-24,tw-24,48,wh+48)) windowresize = 0;
           break;
          }
          case RESIZEWIN_TOP:
          {
           if (!getarea(lw-24,tw-24,ww+48,48)) windowresize = 0;
           break;
          }
          case RESIZEWIN_WIDTH:
          {
           if (!getarea(lw+ww-24,tw-24,48,wh+48)) windowresize = 0;
           break;
          }
          case RESIZEWIN_HEIGHT:
          {
           if (!getarea(lw-24,tw+wh-24,ww+48,48)) windowresize = 0;
           break;
          }
          case RESIZEWIN_SCALE:
          {
           if (!getarea(lw+ww-24,tw+wh-24,48,48)) windowresize = 0;
           break;
          }
        };
        windowresizeside = RESIZEWIN_NONE;
      }
    }
   } 
  
   if ((activewindow==sender->windowid)&&(!isinuse))
   {
       if ((windowresize)&&(!windowmove)&&(!sender->windowmove)&&(!isinuse))
       {
         int lw=win->left;
         int tw=win->top;
         int ww=win->clientwidth;
         int wh=win->clientheight+windowtopbarheight+1;

         switch(windowresizeside)
         {
             case RESIZEWIN_LT:
             {
              if ( (((((lw+ww)-(mousex))+8)>64)) && (((((tw+wh)-(mousey))+8)>(25+2))) )
              {
                int oldpos = win->left;
                int oldsiz = win->width;
                win->left = ((mousex))+2;
                int newsiz = ((oldpos+oldsiz)-win->left);
                win->width = newsiz;
                oldpos = win->top;
                oldsiz = win->height;
                //if (win->height>25+2) 
                win->top = ((mousey))+2;
                newsiz = ((oldpos+oldsiz)-win->top);
                win->height = newsiz;
              }
              break;
             };
             case RESIZEWIN_WT:
             {
              if ( (((((mousex)-lw)+8)>64)) ) 
              {
                int oldpos = win->left;
                int oldsiz = win->width;
                int newsiz = ((oldpos+oldsiz)-win->left);
                win->width = ((mousex)-lw)+8;
                oldpos = win->top;
                oldsiz = win->height;
                if (win->height>25+2) win->top = ((mousey))+2;
                newsiz = ((oldpos+oldsiz)-win->top);
                win->height = newsiz;
              }
              break;
             };
             case RESIZEWIN_LH:
             {
              int oldpos = win->left;
              int oldsiz = win->width;
              win->left = ((mousex))+2;
              int newsiz = ((oldpos+oldsiz)-win->left);
              win->width = newsiz;
              oldpos = win->top;
              oldsiz = win->height;
              newsiz = ((oldpos+oldsiz)-win->top);
              win->height = ((mousey)-tw)+8;
              break;
             };
             case RESIZEWIN_LEFT:
             {
              int oldpos = win->left;
              int oldsiz = win->width;
              win->left = ((mousex))+2;
              int newsiz = ((oldpos+oldsiz)-win->left);
              win->width = newsiz;
              break;
             };
             case RESIZEWIN_TOP:
             {
              int oldpos = win->top;
              int oldsiz = win->height;
              win->top = ((mousey))+2;
              int newsiz = ((oldpos+oldsiz)-win->top);
              win->height = newsiz;
              break;
             };
         }

         if ( (((((mousex)-lw)+8)>64)) && (((((mousey)-tw)+8)>(25+2))) )
         {
           switch(windowresizeside)
           {
             case RESIZEWIN_WIDTH:
             {
              win->width = ((mousex)-lw)+6;
              break;
             };
             case RESIZEWIN_HEIGHT:
             {
              win->height = ((mousey)-tw)+5;
              break;
             };
             case RESIZEWIN_SCALE:
             {
              win->width = ((mousex)-lw)+8;
              win->height = ((mousey)-tw)+8;
              break;
             };
           };
         }
       }
   }

  int nbtns = 3;
  if (win->borderstyle == bsDialog) nbtns = 1;

  int wbtns = 20*nbtns;

  if (win->width <= 64) win->width = 64;
  if (win->height <= 25+2) win->height = 25+2;

  setviewport(0,0,getscreenwidth(),getscreenheight());

/*  
  if (win->windowstate == wsMinimized)
  {
     win->height = 28;
  }
*/
  
  glPushMatrix();
  if (activewindow==sender->windowid)
  {
   if (windowmove)
   {
//     mousex = sender->left+1;
//     mousey = sender->top+1;
  //   sender->left = mousex;
   //  sender->top = mousey;
 //    mc = 1;
   }
   if (win->windowstate != wsMaximized)
   {
      if (winmove) windowmove = true;
   }
  if (mouseb)
   {
   if (getarea(sender->left+1,sender->top+1,winwidth-(wbtns+8),19)==true)
     {
       if (mc)
       {
        ol = sender->left;
        ox = mousex;
        ot = sender->top;
        oy = mousey;
        mc = false;
       }
       if ((mouseb==1) && (win->windowstate != wsMaximized))
       {
        sender->windowmove = true;
       }
       else if (mouseb==3)
       {
         systemmenu->alphavalue = sender->alphavalue;
         systemmenu->left = ox;
         systemmenu->top = oy;
         if ((systemmenu->left+systemmenu->width) >= getscreenwidth()-4) systemmenu->left -= systemmenu->width;
         if ((systemmenu->top+systemmenu->height) >= getscreenheight()-4) systemmenu->top -= systemmenu->height;
         show_menu(systemmenu);
//         systemmenu->menu->items[0]->onclick = menuitem1click;
//         systemmenu->menu->items[1]->onclick = menuitem2click;
       }
       pressclosebtn = false;
       closepressed = false;
       pressmaximizebtn = false;
       maximizepressed = false;
       pressminimizebtn = false;
       minimizepressed = false;
     }
   } else 
   {
          if (!windowmove) sender->windowmove = false;
   }
   if (sender->windowmove && (!mc) && (!((windowresize)||(windowresizeside>0))))
   {    
       sender->left = mousex-(winwidth-(winwidth-ox+ol));
       sender->top = mousey-(19-(19-oy+ot));
       pressclosebtn = false;
       closepressed = false;
       pressmaximizebtn = false;
       maximizepressed = false;
       pressminimizebtn = false;
       minimizepressed = false;
   }
  }
  else if (pressclosebtn==true) closepressed = true;
  else if (pressmaximizebtn==true) maximizepressed = true;
  else if (pressminimizebtn==true) minimizepressed = true;

   if (mouseb)
   {
        if (winmove)
        {
          windowmove = false;
          winmove = false;
        }
   }
   if (windowtopbar==1)
   {
   int stl=0;
   int stt=0;
   int stw=0;
   int sth=0;
   stl = sender->left+win->subtessleft;
   stt = sender->top+win->subtesstop+windowtopbarheight+1;
   stw = sender->left+win->subtessleft+win->subtesswidth;
   sth = sender->top+win->subtesstop+win->subtessheight+windowtopbarheight+1;   
   if (stl < sender->left) stl = sender->left;
   if (stt < sender->top+windowtopbarheight+1) stt = sender->top+windowtopbarheight+1;
   if (stw > sender->left+sender->width-4) stw = sender->left+sender->width-4;
   if (sth > sender->top+sender->height-5) sth = sender->top+sender->height-5;
   subrecttess(stl,stt,stw,sth);
   drawcontroledgew(sender->left,sender->top,winwidth,winheight,2,sender->alphavalue);
   fillrecttess(sender->left,sender->top+1,sender->left+winwidth-2,sender->top+winheight-1,win->color,sender->alphavalue);
   if (activewindow==sender->windowid)
   {
    drawcontroledge(sender->left+3,sender->top+3,winwidth-(wbtns+9),19,1,sender->alphavalue);
    drawgradient(sender->left+4,sender->top+5,sender->left+winwidth-(wbtns+8),sender->top+1+19,clActiveCaptionIn,clActiveCaptionOut,sender->alphavalue,0);

    int bl=sender->left+1;
    int bt=sender->top+1;
    int bw=sender->width-(wbtns+8);
    int bh=24+2;

    glEnable(GL_SCISSOR_TEST);
    if (!windowmanager) glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
    else
    {
       if (windowtopbarheight>0) glScissor(bl+1,height-(bt+bh-5),bw-6,bh+1);
       else glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
    }

    textattr(textcolor,sender->alphavalue,12,FW_BOLD);
    textout(sender->left+8,sender->top+4,sender->caption);
   // fillrect(sender->left+(winwidth-24),sender->top+1,sender->left+winwidth-2,sender->top+4+19,clBtnFace,sender->alphavalue);
    glDisable(GL_SCISSOR_TEST);
   } else
   {
   /*
   drawgradient(sender->left+2,sender->top+2,sender->left+winwidth-4,sender->top+2+18,clDarkGray,clSilver,sender->alphavalue,0);
   textattr(clSilver,sender->alphavalue,12,FW_BOLD);
   textout(sender->left+4,sender->top+3,sender->caption);
   */
    drawcontroledge(sender->left+3,sender->top+3,winwidth-(wbtns+9),19,1,sender->alphavalue);
    drawgradient(sender->left+4,sender->top+5,sender->left+winwidth-(wbtns+8),sender->top+1+19,clInactiveCaptionIn,clInactiveCaptionOut,sender->alphavalue,0);
    textattr(clSilver,sender->alphavalue,12,FW_BOLD);
    textout(sender->left+8,sender->top+4,sender->caption);
   // fillrect(sender->left+(winwidth-24),sender->top+1,sender->left+winwidth-2,sender->top+4+19,clBtnFace,sender->alphavalue);
   }
   

   bool closeenabled = true;
   bool maxenabled = true;
   bool minenabled = true;

   if ((win->borderstyle == bsSingle)||(win->borderstyle == bsDialog)) maxenabled = false;
   if (win->borderstyle == bsDialog) minenabled = false;

   if (win->borderstyle == bsSingle)
   {
    if (minenabled) 
    {
     if (win->windowstate == wsNormal)
     {
       systemmenu->menu->items[0]->enabled = false;
       systemmenu->menu->items[3]->enabled = true;
     }
     else if (win->windowstate == wsMinimized)
     {
       systemmenu->menu->items[0]->enabled = true;
       systemmenu->menu->items[3]->enabled = false;
     }
     if (win->windowstate == wsMaximized) win->windowstate = wsNormal;
    }
   }
   
   if (nbtns >= 1)
   {

   if (getarea(sender->left+winwidth-21,sender->top+5,15,15)==true)
   {
     drawcontroledge(sender->left+winwidth-21,sender->top+5,15,14,6,sender->alphavalue);
   }

   drawsysbtnimage(sender->left+winwidth-19,sender->top+6,closebtn,sender->alphavalue,clAqua,clNavy,true,clLime,true);
   closepressed = false;
   if (mouseb)
   {
   if (getarea(sender->left+winwidth-21,sender->top+5,15,15)==true)
   {
     drawcontroledge(sender->left+winwidth-21,sender->top+5,15,15,7,sender->alphavalue);
     drawsysbtnimage(sender->left+winwidth-18,sender->top+7,closebtn,sender->alphavalue,clAqua,clNavy,true,clLime,true);
     pressclosebtn = true;
     closepressed = false;
     if ((isinwin)&&(!((windowresize) || (windowresizeside>0)))) activewindow = sender->windowid;
   }
  } else if (pressclosebtn==true) closepressed = true;
  
  }



   if (nbtns >= 2)
   {

   if ((getarea(sender->left+winwidth-41,sender->top+5,15,15)==true) && (maxenabled==true))
   {
     if ((win->windowstate == wsMinimized)&&(win->borderstyle != bsSizeable))
     {
     }
     else
     {
       drawcontroledge(sender->left+winwidth-41,sender->top+5,15,14,6,sender->alphavalue);
     }
   }
   if (win->windowstate == wsNormal) drawsysbtnimage(sender->left+winwidth-39,sender->top+6,maximizebtn,sender->alphavalue,clAqua,clNavy,true,clLime,maxenabled);
   else if (win->windowstate == wsMaximized) drawsysbtnimage(sender->left+winwidth-39,sender->top+6,restorebtn,sender->alphavalue,clAqua,clNavy,true,clLime,maxenabled);
   else 
   {
     if (win->borderstyle == bsSizeable) drawsysbtnimage(sender->left+winwidth-39,sender->top+6,maximizebtn,sender->alphavalue,clAqua,clNavy,true,clLime,maxenabled);
     else drawsysbtnimage(sender->left+winwidth-39,sender->top+6,maximizebtn,sender->alphavalue,clAqua,clNavy,true,clLime,false);
   }
   maximizepressed = false;
   if (mouseb && maxenabled)
   {
   if ((win->windowstate == wsMinimized)&&(win->borderstyle != bsSizeable))
   {
   }
   else
   {
    if (getarea(sender->left+winwidth-41,sender->top+5,15,15)==true)
    {
     drawcontroledge(sender->left+winwidth-41,sender->top+5,15,15,7,sender->alphavalue);
     if (win->windowstate == wsNormal) drawsysbtnimage(sender->left+winwidth-38,sender->top+7,maximizebtn,sender->alphavalue,clAqua,clNavy,true,clLime,maxenabled);
     else if (win->windowstate == wsMaximized) drawsysbtnimage(sender->left+winwidth-38,sender->top+7,restorebtn,sender->alphavalue,clAqua,clNavy,true,clLime,maxenabled);
     else 
     {
       if (win->borderstyle == bsSizeable) drawsysbtnimage(sender->left+winwidth-38,sender->top+7,maximizebtn,sender->alphavalue,clAqua,clNavy,true,clLime,maxenabled);
       else drawsysbtnimage(sender->left+winwidth-38,sender->top+7,maximizebtn,sender->alphavalue,clAqua,clNavy,true,clLime,false);
     }
     pressmaximizebtn = true;
     maximizepressed = false;
     if ((isinwin)&&(!((windowresize) || (windowresizeside>0)))) activewindow = sender->windowid;
    }
   }
  } else if (pressmaximizebtn==true) maximizepressed = true;
  
  }

  
   if (nbtns >= 3)
   {

   if (getarea(sender->left+winwidth-61,sender->top+5,15,15)==true)
   {
     drawcontroledge(sender->left+winwidth-61,sender->top+5,15,14,6,sender->alphavalue);
   }
   if (win->windowstate == wsMinimized) drawsysbtnimage(sender->left+winwidth-59,sender->top+6,restorebtn,sender->alphavalue,clAqua,clNavy,true,clLime,true);
   else drawsysbtnimage(sender->left+winwidth-59,sender->top+6,minimizebtn,sender->alphavalue,clAqua,clNavy,true,clLime,true);
   minimizepressed = false;
   if (mouseb)
   {
   if (getarea(sender->left+winwidth-61,sender->top+5,15,15)==true)
   {
     drawcontroledge(sender->left+winwidth-61,sender->top+5,15,15,7,sender->alphavalue);
     if (win->windowstate == wsMinimized) drawsysbtnimage(sender->left+winwidth-58,sender->top+7,restorebtn,sender->alphavalue,clAqua,clNavy,true,clLime,true);
     else drawsysbtnimage(sender->left+winwidth-58,sender->top+7,minimizebtn,sender->alphavalue,clAqua,clNavy,true,clLime,true);
     pressminimizebtn = true;
     minimizepressed = false;
     if ((isinwin)&&(!((windowresize) || (windowresizeside>0)))) activewindow = sender->windowid;
   }
  } else if (pressminimizebtn==true) minimizepressed = true;
  
  }

   
   if (sender->visible)
   {
     int xhint = sender->left+winwidth;
     int yhint = sender->top;
     if ((sender->left+winwidth) >= getscreenwidth()) xhint = (sender->left+winwidth);
     
     bool maxbtnon = false;
     
     if ((win->windowstate == wsMinimized)&&(win->borderstyle != bsSizeable)) maxbtnon = true;

     if ((getarea(xhint-21,sender->top+5,15,15)==true)&&(closeenabled==true))
     {
       if (!mouseb) hintrect(getarea(xhint-21,sender->top+5,15,15),systemmenu->menu->items[6]->caption);
     }
     else 
     if ((getarea(xhint-41,sender->top+5,15,15)==true)&&(maxenabled==true)&&(!maxbtnon))
     {
       if (!mouseb) 
       {
         if (win->windowstate == wsMaximized) hintrect(getarea(xhint-41,sender->top+5,15,15),systemmenu->menu->items[0]->caption);
         else hintrect(getarea(xhint-41,sender->top+5,15,15),systemmenu->menu->items[4]->caption);
       }
     }
     else 
     if ((getarea(xhint-61,sender->top+5,15,15)==true)&&(minenabled==true))
     {
       if (!mouseb) 
       {
         if (win->windowstate == wsMinimized) hintrect(getarea(xhint-61,sender->top+5,15,15),systemmenu->menu->items[0]->caption);
         else hintrect(getarea(xhint-61,sender->top+5,15,15),systemmenu->menu->items[3]->caption);
       }
     }
     else 
     {
       if (sender->visible)
       {
         if (sender->IsInWindow(sender)) hintrect(false,"");
       }
     }
   }

  }
  else 
  {
       subrecttess(sender->left+win->subtessleft,sender->top+win->subtesstop,sender->left+win->subtessleft+win->subtesswidth,sender->top+win->subtesstop+win->subtessheight);
       fillrecttess(sender->left,sender->top,sender->left+winwidth+2,(sender->top+winheight-windowtopbarheightdefault)+2,win->color,sender->alphavalue);
  }
  glPopMatrix();
  sender->showing = true; 
  setviewport(0,0,getscreenwidth(),getscreenheight());
}

void setforegroundwindow(int num)
{
  TWindow* win=NULL;
  if (num < 0) return;
  if (num > numwindows) return;
  if (numwindows <= 0) return;
  if ((num == activewindow)&&(activewindow>0)) 
  {
   if (activewindow>=numwindows) 
   {
     activewindow=numwindows-2;
     if (activewindow<=0) activewindow = 0;
   }
   else
   {
     activewindow--;
   }
  }
  win = windows[num];
  for (int i=num;i<numwindows-1;i++)
  {
       int wid = windows[i+1]->windowid-1;
       windows[i] = windows[i+1];
       windows[i+1]->windowid = wid;
  }
  windows[numwindows-1] = win;
  windows[numwindows-1]->windowid = numwindows-1;
  activewindow = numwindows-1;
}

int getforegroundwindow(void)
{
    return activewindow;
}
TWindow* window_i[256];
int createwindow(void)
{
  if (numwindows >= 255) return 255;
  int numwindow = numwindows;
  window_i[numwindow] = new TWindow();
  windows[numwindow]->alphavalue = 255;
  windows[numwindow]->borderstyle = bsSizeable;
  windows[numwindow]->enabled = true;
  windows[numwindow]->width=256;
  windows[numwindow]->height=256;
  windows[numwindow]->windowstate = wsNormal;
  windows[numwindow]->messageboxresult = mrNone;
  windows[numwindow]->modalresult = 0;
  windows[numwindow]->visible = false;
  if (numwindow <= 0) activewindow = windows[numwindow]->windowid;
  return numwindow;  
}

void deletewindow(int num)
{
  TWindow* win=NULL;
  if (num < 0) return;
  if (num > numwindows) return;
  if (numwindows <= 0) return;
  if ((num == activewindow)&&(activewindow>0)) 
  {
   if (activewindow>=numwindows) 
   {
     activewindow=numwindows-2;
     if (activewindow<=0) activewindow = 0;
   }
   else
   {
     activewindow--;
   }
  }
  delete windows[num];
  for (int i=num;i<numwindows-1;i++)
  {
       int wid = windows[i+1]->windowid-1;
       windows[i] = windows[i+1];
       windows[i+1]->windowid = wid;
  }
  windows[numwindows-1]=win;
  numwindows--;
  activewebbrowser = -1;
}


void TWindow::rendercontrols()
{
int numw = 0;
int i=0,j=0;
int knw=1;
setviewport(0,0,getscreenwidth(),getscreenheight());
//setviewport(this->left,this->top,this->width,this->height);
windows[windowid] = this;
glPushMatrix();
if (visible)
{
         
 if (activewindow == windowid)
 {
  if ((borderstyle != bsDialog)&&(borderstyle != bsNone))
  {
   if (getarea(left+width-41,top+5,15,13)==true)
   {
        if ((mousea == 1)&&(!temp_winanim))
        {
          if (windowstate == wsNormal)
          {
            if (borderstyle == bsSizeable)
            {
              maximize();
              windowstate = wsMaximized;
            }
          }
          else if (windowstate == wsMinimized)
          {
            if (borderstyle != bsSizeable)
            {
              windowstate = wsMinimized;
            }
            else
            {
              maximize();
              windowstate = wsMaximized;
            }
          }
          else if (windowstate == wsMaximized)
          {
            restore();
            windowstate = wsNormal;
          }
        }
   }
         
   if (getarea(left+width-61,top+5,15,13)==true)
   {
        if (mousea == 1)
        {
          if (windowstate == wsMinimized)
          {
               restore();
               windowstate = wsNormal;
          }
          else 
          {
               minimize();
               windowstate = wsMinimized;
          }
        }
   }
  } 
 }

// mousea = 0;




  if (temp_winanim)
  {
   if (activewindow == windowid)
   {
     if (windowstate == wsNormal)
     {
       int sizvel = 24;
       int scrw = getscreenwidth();
       int scrh = getscreenheight();
       
       int x = temp_left;
       int y = temp_top;
       int w = temp_width;
       int h = temp_height;
       float a = getangle(x,y);
       float a2 = getangle(w,h);
       
       if (temp_minimized)
       {
        // left = temp_left;
        // top = temp_top;
        // width = temp_width;
        // height = temp_height;

       for (int i=0;i<sizvel;i++)
       {
         if ((left < x)&&(top < y)&&(width > w)&&(height > h)) 
         {
           left+=sin(a*PI/180)*(3);
           top+=cos(a*PI/180)*(4);
           width-=sin(a2*PI/180)*(3);
           height-=cos(a2*PI/180)*(4);
         }
          else
         {
           left = x;
           top = y;
           width = w;
           height = h;
         }
         
         if (left >= x) left = x;
         if (top >= y) top = y;
         if (width <= w) width = w;
         if (height <= h) height = h;
         
       }
         temp_winanim = false;
         temp_minimized = false;
       }
       else
       {

       for (int i=0;i<sizvel;i++)
       {
         if ((left < x)&&(top < y)&&(width > w)&&(height > h)) 
         {
           left+=sin(a*PI/180)*(3);
           top+=cos(a*PI/180)*(4);
           width-=sin(a2*PI/180)*(3);
           height-=cos(a2*PI/180)*(4);
         }
         else
         {
           left = x;
           top = y;
           width = w;
           height = h;
         }
         if (left >= x) left = x;
         if (top >= y) top = y;
         if (width <= w) width = w;
         if (height <= h) height = h;
       }
       
       }
       
       if (left >= x) left = x;
       if (top >= y) top = y;
       if (width <= w) width = w;
       if (height <= h) height = h;
       temp_minimized = false;
       if ((left >= x)&&(top >= y)&&(width <= w)&&(height <= h)) temp_winanim = false;
     }
     if (windowstate == wsMinimized)
     {
//       top = getscreenheight()-28;     
       int sizvel = 24;
       int scrw = getscreenwidth();
       int scrh = getscreenheight();
       
       int x = temp_left;
       int y = getscreenheight()-28;     
       int w = temp_width;
       int h = 28;
       float a = getangle(x,y);
       float a2 = getangle(w,h);
       for (int i=0;i<sizvel;i++)
       {
        // if ((left < x)&&(top < y)&&(width > w)&&(height > h)) 
         {
           left+=sin(a*PI/180)*(3);
           top+=cos(a*PI/180)*(4);
           width-=sin(a2*PI/180)*(3);
           height-=cos(a2*PI/180)*(4);
         }
         /*else
         {
           left = x;
           top = y;
           width = w;
           height = h;
         }*/
         if (left >= x) left = x;
         if (top >= y) top = y;
         if (width <= w) width = w;
         if (height <= h) height = h;
       }
       
       if (left >= x) left = x;
       if (top >= y) top = y;
       if (width <= w) width = w;
       if (height <= h) height = h;
       temp_minimized = true;
       if ((left >= x)&&(top >= y)&&(width <= w)&&(height <= h)) temp_winanim = false;
     }
     if (windowstate == wsMaximized)
     {
       int sizvel = 24;
       int scrw = getscreenwidth();
       int scrh = getscreenheight();
       
       float a = getangle(1,1);
       float a2 = getangle(scrw,scrh);
       int x = temp_left;
       int y = temp_top;
       int w = temp_width;
       int h = temp_height;

       if (temp_minimized)
       {
      /*
        left = 0;
        top = 0;
        width = getscreenwidth();
        height = getscreenheight();
        SetWindowText(hWnd,"minimized");
        temp_winanim = false;
      */
       }
   //    else
       {

       for (int i=0;i<sizvel;i++)
       {
        if ((left > 0)&&(top > 0)&&(width < scrw)&&(height < scrh)) 
        {
         left-=sin(a*PI/180)*(1);
         top-=cos(a*PI/180)*(1);
         width+=sin(a2*PI/180)*(3);
         height+=cos(a2*PI/180)*(4);
        }
        else
        {
         left = 0;
         top = 0;
         width = scrw;
         height = scrh+4;
        }
        if (left <= 0) left = 0;
        if (top <= 0) top = 0;
        #ifdef TEST
        if (width >= scrw) width = scrw;//scrw4
        #else
        if (width >= scrw) width = scrw+4;//scrw4
        #endif
        if (height >= scrh) height = scrh+4;
       }
       /*
       left--;
       top--;
       width++;
       height++;
       */
       
       if (left <= 0) left = 0;
       if (top <= 0) top = 0;
       #ifdef TEST
       if (width >= scrw) width = scrw;//scrw4
       #else
       if (width >= scrw) width = scrw+4;//scrw4
       #endif
       if (height >= scrh) height = scrh+4;
       temp_minimized = false;
       if ((left <= 0)&&(top <= 0)&&(width >= scrw)&&(height >= scrh)) temp_winanim = false;
       }
       temp_minimized = false;
     }
   }
   }
   else
   {
       if (windowstate == wsMinimized) height = 28;
   }
   

   
   TWinControl::render(this);    
   hintwincontrol(this);
  
  
  if (windows[activewindow]->borderstyle != bsNone)
  {
     if (getarea(windows[activewindow]->left+windows[activewindow]->width-21,windows[activewindow]->top+5,15,13)==true)
     {
        if (mousea == 1)
        {
          //deletewindow(activewindow);
          windows[activewindow]->visible = false;
          if (activewindow > 0) activewindow--;
          if (activewindow <= 0) activewindow = 0;
        }
     }
  }
//  if (mouseb==0) mousea = 0;
  
  if (mouseb==MK_LBUTTON)
  {

  if (activewindow!=windowid)
  {
  if (IsInWindow(windows[windowid])==true)
  {

 // if (activewindow!=windowid)
 // if (IsInWindow(windows[numw])==false)
  if (mousec == MK_LBUTTON)
  for(j=0;j<numwindows;j++)
  {
  for(i=0;i<numwindows;i++)
  {
   
   bool intersected = true;
   bool i2 = false;
   bool i3 = true;
   
   if (i != activewindow) numw = i;
 
   intersected = getintersectedarea(windows[activewindow]->left,windows[activewindow]->top,windows[activewindow]->width,windows[activewindow]->height, windows[numw]->left,windows[numw]->top,windows[numw]->width,windows[numw]->height);
   if (windows[j]->focused == false) i2 = true;
   else i2 = false;
   if (i2) i3 = getintersectedarea(windows[numw]->left,windows[numw]->top,windows[numw]->width,windows[numw]->height,windows[j]->left,windows[j]->top,windows[j]->width,windows[j]->height);
   else i3 = true;
   if ((intersected==false)&&(!IsInAnyMenu()))
   {
     if ((IsInWindow(windows[numw])==true))
     {
       if (!i3)
       {
        windows[windowid]->focused = true;
        activewindow = windowid;
       }
       else 
       {
        windows[numw]->focused = true;
        activewindow = numw;
       }
     }
     else windows[numw]->focused = false;
   }
   else windows[numw]->focused = false;
  }
  }
  }
  }
  }
 showing = true;

int wintopbarh = height-clientheight;

   
   if (((temp_winfreeze && freezing)) && (temp_startfreeze == false))
   {
     if (temp_freeze && temp_freezebuf)
     {
       int winw = this->width-8;
       int winhs = (this->height-5)-wintopbarh;
       int winh = (this->height-5)+wintopbarh;
       setviewport(this->left+2,getscreenheight()-(this->top+winh),winw,winh);
       begindrawing();
       glRasterPos2i(0, (this->height-5));
       float fw = 0;
       float fh = 0;
       for (int i=0;i<winw;i++) fw += 1.0f/((float)temp_freezewidth);
       for (int i=0;i<winhs;i++) fh += 1.0f/((float)temp_freezeheight);
       glPixelZoom(fw,fh);
       glDrawPixels(temp_freezewidth,temp_freezeheight,GL_RGBA,GL_UNSIGNED_BYTE,temp_freeze);
       if (temp_freezetime >= 255) temp_freezetime = 255;
       for (int i=0;i<temp_freezewidth*temp_freezeheight;i++)
       {
         temp_freezebuf[i*4+3] = temp_freezetime;
       }
       glDrawPixels(temp_freezewidth,temp_freezeheight,GL_RGBA,GL_UNSIGNED_BYTE,temp_freezebuf);
       // this->color = blendcolorto(this->color,temp_freezecolor,temp_freezetime);   // freeze window color
       enddrawing();
       setviewport(0,0,getscreenwidth(),getscreenheight());
       glDisable(GL_SCISSOR_TEST);
       glPopMatrix();
       // this->modalhalt = true; // freeze window controls
       if (temp_freezetime < 255) temp_freezetime++;
       return;
     }
   }
   
if (visible == true)
{
int l=0,t=0,w=0,h=0;
l=left;
t=top+wintopbarh;
w=width;
h=height-wintopbarh;
glEnable(GL_SCISSOR_TEST);

if (!windowmanager) glScissor(l,height-(t+h-2),w-2,h+1);
else
{
if (wintopbarh>0) glScissor(l+1,height-(t+h-5),w-4,h+1);
else glScissor(l,height-(t+h-2),w-2,h+1);
}
}

 for (int i=0;i<numimages;i++) 
 {
     if (images[i]->visible) images[i]->rendercontrol();
 }

 for (int i=0;i<numshapes;i++) 
 {
     if (shapes[i]->visible) shapes[i]->rendercontrol();
 }

 for (int i=0;i<numglyphbuttons;i++) 
 {
     if (glyphbuttons[i]->visible) glyphbuttons[i]->rendercontrol();
 }

 for (int i=0;i<numcomboboxes;i++) 
 {
     if (comboboxes[i]->visible) comboboxes[i]->rendercontrol();
 }

 for (int i=0;i<numlistboxes;i++) 
 {
     if (listboxes[i]->visible) listboxes[i]->rendercontrol();
 }

 for (int i=0;i<numgroupboxes;i++) 
 {
     if (groupboxes[i]->visible) groupboxes[i]->rendercontrol();
 }
 
 for (int i=0;i<numpanels;i++) 
 {
     if (panels[i]->visible) panels[i]->rendercontrol();
 }
 
 for (int i=0;i<numbevels;i++) 
 {
     if (bevels[i]->visible) bevels[i]->rendercontrol();
 }

 for (int i=0;i<numbuttons;i++) 
 {
     if (buttons[i]->visible) buttons[i]->rendercontrol();
 }
 
 for (int i=0;i<numspeedbuttons;i++) 
 {
     if (speedbuttons[i]->visible) speedbuttons[i]->rendercontrol();
 }
 
 for (int i=0;i<numlabels;i++) 
 {
     if (labels[i]->visible) labels[i]->rendercontrol();
 }
 
 for (int i=0;i<numedits;i++) 
 {
     if (edits[i]->visible) edits[i]->rendercontrol();
 }
 
 for (int i=0;i<numtextboxes;i++) 
 {
     if (textboxes[i]->visible) textboxes[i]->rendercontrol();
 }
 
 for (int i=0;i<numcheckboxes;i++) 
 {
     if (checkboxes[i]->visible) checkboxes[i]->rendercontrol();
 }
 
 for (int i=0;i<numradiobuttons;i++) 
 {
     if (radiobuttons[i]->visible) radiobuttons[i]->rendercontrol();
 }
 
 for (int i=0;i<numscrollbars;i++) 
 {
     if (scrollbars[i]->visible) scrollbars[i]->rendercontrol();
 }
 
 for (int i=0;i<numprogressbars;i++) 
 {
     if (progressbars[i]->visible) progressbars[i]->rendercontrol();
 }
 
 for (int i=0;i<numtransparentboxes;i++) 
 {
     if (transparentboxes[i]->visible) transparentboxes[i]->rendercontrol();
 }
 
 for (int i=0;i<numviewports;i++) 
 {
     if (viewports[i]->visible) viewports[i]->rendercontrol();
 }
 
 for (int i=0;i<numtimers;i++) 
 {
     if (timers[i]->enabled) timers[i]->rendercomponent();
 }
 
 for (int i=0;i<numimagelists;i++) 
 {
     if (imagelists[i]->enabled) imagelists[i]->rendercomponent();
 }
 
 for (int i=0;i<numtrackbars;i++) 
 {
     if (trackbars[i]->visible) trackbars[i]->rendercontrol();
 }
 
 for (int i=0;i<numupdowns;i++) 
 {
     if (updowns[i]->visible) updowns[i]->rendercontrol();
 }
 
 for (int i=0;i<numvideoplayers;i++) 
 {
     if (videoplayers[i]->visible) videoplayers[i]->rendercontrol();
     else
     {
      if (videoplayers[i]->hasbink) fevsl_binksndonoff(videoplayers[i]->videonum,0);
     }
 }
  
 for (int i=0;i<numlistviews;i++) 
 {
     if (listviews[i]->visible) listviews[i]->rendercontrol();
 }
  
 for (int i=0;i<numwebbrowsers;i++)
 {
     if (webbrowsers[i]->visible) webbrowsers[i]->rendercontrol();
 }

 for (int i=0;i<numdockbars;i++) 
 {
     if (dockbars[i]->enabled) dockbars[i]->rendercontrol();
 }
 
 for (int i=0;i<numtoolbars;i++) 
 {
     if (toolbars[i]->enabled) toolbars[i]->rendercontrol();
 }
 
 for (int i=0;i<numtoolbuttons;i++) 
 {
     if (toolbuttons[i]->enabled) toolbuttons[i]->rendercontrol();
 }

 for (int i=0;i<nummainmenues;i++) 
 {
     if (mainmenues[i]->enabled) mainmenues[i]->rendercontrol();
 }


glDisable(GL_SCISSOR_TEST);
int l=left;
int t=top;
int w=width;
int h=height;

        //    drawcontroledge(l+20,t+64,64,24,5,255);
        //    fillrect(l+22,t+66,l+82,t+86,clWhite,255);

}
  glPopMatrix();

  setviewport(0,0,getscreenwidth(),getscreenheight());

}

// int rotating=1;

void TWindow::show()
{
 begindrawing();
 rendercontrols();
 enddrawing();
}

int TWindow::showmodal()
{
  if (!window->modalhalt) visible = true;
  window->modalhalt = true;
  return modalresult;
}

bool WindowExists(TWindow* Window)
{
  for (int i=0;i<numwindows;i++)
  {
      if (windows[i] == Window) return true;
  }
  return false;
}

TWindow::TWindow()
{
         // TOnRender renderc = dynamic_cast<TOnRender>(rendercontrol);
          name="window";
          id=numwindows+2000;
          visible = false;
          left=100;
          top=100;
          width=256;
          height=256;
          alphavalue=255;
          color = clBtnFace;
          borderstyle = bsSizeable;
          caption="window";
          color = clBtnFace;
          numbuttons = 0;
          numdockbars = 0;
          numspeedbuttons = 0;
          numtoolbuttons = 0;
          numgroupboxes = 0;
          numcheckboxes = 0;
          numradiobuttons = 0;
          nummainmenues = 0;
          numlabels = 0;
          numimages = 0;
          numcontrols = 0;
          numcomponents = 0;
          activecontrol = -1;
          activewindow = numwindows;
          windowid = numwindows;
          render = renderwindow;
          showing = false;
          visible = false;
          start_freeze = false;
          temp_winanim = false;
          temp_left = 0;
          temp_top = 0;
          temp_width = 0;
          temp_height = 0;
          temp_minimized = false;
          temp_winfreeze = false;
          temp_startfreeze = false;
          temp_freezecolor = clBtnFace;
          temp_freezetime = 0;
          temp_freezewidth = 0;
          temp_freezeheight = 0;
          temp_freeze = NULL;
          temp_freezebuf = NULL;
          freezing = false;
          windows[windowid] = this;
          numwindows++;
}

void TWindow::restore()
{
  if ((windowstate == wsMaximized)||(windowstate == wsMinimized))
  {
  /*
    left = temp_left;
    top = temp_top;
    width = temp_width;
    height = temp_height;
  */
  }
    temp_winanim = true;
  
  windowstate = wsNormal;
}

void TWindow::minimize()
{
  if ((windowstate != wsMaximized)&&(windowstate != wsMinimized))
  {
    temp_left = left;
    temp_top = top;
    temp_width = width;
    temp_height = height;
  }
  temp_minimized = true;
  temp_winanim = true;
  
  windowstate = wsMinimized;
}

void TWindow::maximize()
{
  if ((windowstate != wsMaximized)&&(windowstate != wsMinimized))
  {  
    temp_left = left;
    temp_top = top;
    temp_width = width;
    temp_height = height;  
  }
  temp_winanim = true;
  windowstate = wsMaximized;
}

void TWindow::freeze()
{
  start_freeze = true;
}

void TWindow::showfreeze()
{
if (start_freeze)
{
  temp_startfreeze = true;
  temp_winfreeze = true;
  freezing = true;
  
if (visible)
{  
  if (freezing)
  {
    if (temp_startfreeze)
    {
       int wintopbarh = this->height-this->clientheight;
       int winw = this->width-8;
       int winh = (this->height+4)-wintopbarh;
       temp_freezewidth = winw;
       temp_freezeheight = winh-9;
       temp_freeze = (unsigned char*)malloc(temp_freezewidth*temp_freezeheight*4);
       temp_freezebuf = (unsigned char*)malloc(temp_freezewidth*temp_freezeheight*4);
       glReadPixels(this->left+2,getscreenheight()-(this->top+(this->height-5)),temp_freezewidth,temp_freezeheight,GL_RGBA,GL_UNSIGNED_BYTE,temp_freeze);
       glReadPixels(this->left+2,getscreenheight()-(this->top+(this->height-5)),temp_freezewidth,temp_freezeheight,GL_RGBA,GL_UNSIGNED_BYTE,temp_freezebuf);

       if (temp_startfreeze)
       {
         int r=0,g=0,b=0;
         r = GetRValue(this->color);
         g = GetGValue(this->color);
         b = GetBValue(this->color);
         if (r <= 0) r = 0;
         if (g <= 0) g = 0;
         if (b <= 0) b = 0;
         if (r >= 255) r = 255;
         if (g >= 255) g = 255;
         if (b >= 255) b = 255;
         r = g = b = (r + g + b) / 3;
         temp_freezecolor = RGB(r,g,b);
       }

       for (int i=0;i<temp_freezewidth*temp_freezeheight;i++)
       {
         int r=0,g=0,b=0;
         r = temp_freeze[i*4+0];
         g = temp_freeze[i*4+1];
         b = temp_freeze[i*4+2];
         if (r <= 0) r = 0;
         if (g <= 0) g = 0;
         if (b <= 0) b = 0;
         if (r >= 255) r = 255;
         if (g >= 255) g = 255;
         if (b >= 255) b = 255;
         r = g = b = (r + g + b) / 3;
         temp_freezebuf[i*4+0] = r;
         temp_freezebuf[i*4+1] = g;
         temp_freezebuf[i*4+2] = b;
         temp_freezebuf[i*4+3] = 0;
       }
       temp_startfreeze = false;
    }
  }
  else
  {
    if (temp_freeze) free(temp_freeze);
    if (temp_freezebuf) free(temp_freezebuf);
    temp_freezetime = 0;
  }
}
start_freeze = false;
}
}

