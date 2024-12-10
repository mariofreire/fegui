// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "wincontrol.h" // class's header file
#include "tooltip.h"
#include "menu.h"
#include "screen.h"
#include "control.h"
#include "menu.h"
#include "window.h"
#include "msgbox.h"


TWinControl::TWinControl()
{
          name="wincontrol";
          visible = false;
          left=0;
          top=0;
          width=128;
          height=128;
          subtessleft=0;
          subtesstop=0;
          subtesswidth=0;
          subtessheight=0;
          modalresult=mrNone;
          messageboxresult=0;
          messageboxtimereset=2;
          modalhalt = false;
          messageboxon = false;
          clicked = false;
          hint = "";
          showhint = false;
          resethint = false;
          color = clBtnFace;
}

TWinControl::~TWinControl()
{
}

void TWinControl::show()
{
          visible = true;
                 
          if (visible==true) render(this);        
}

void TWinControl::hide()
{
          visible = false;
}

bool TWinControl::IsInControl(TControl* Control)
{
     bool iscontrol = false;
     int wt = Control->window->height-Control->window->clientheight;
     if ((Control->window->borderstyle != bsNone)&&(windowmanager == 1)) wt -= 3;

     if (Control->window->freezing) return false;

     if (IsInAnyMenu()) return false;
     
     if (((mousex>=(Control->window->left+Control->left))&&(mousey>=(Control->window->top+(wt)+Control->top)))&&(mousex<=(Control->window->left+Control->left+Control->width))&&(mousey<=(Control->window->top+wt+Control->height)))
     {       
       iscontrol = true;
     }
     if (modalhalt) iscontrol = false;
     if (Control->window->modalhalt) iscontrol = false;
     return iscontrol;
}

bool TWinControl::IsInWindow(TWinControl* Window)
{
     bool iswindow = false;

     int l0=0, t0=0, w0=0, h0=0, l1=0, t1=0, w1=0, h1=0, l2=0, t2=0, w2=0, h2=0;

     if (IsInAnyMenu()) return false;

     for (int i=numwindows-1;i>=0;i--)
     {
      if (windows[i]->visible && Window->visible)
      {
        if (((((mousex>=(windows[i]->left))&&(mousey>=(windows[i]->top)))&&(mousex<=(windows[i]->left+windows[i]->width))&&(mousey<=(windows[i]->top+windows[i]->height)))))
        {
          l0 = windows[i]->left;
          t0 = windows[i]->top;
          w0 = windows[i]->width;
          h0 = windows[i]->height;
        }
      
        l2 = (l0-l1);
        t2 = (t0-t1);
        w2 = (w0-w1);
        h2 = (h0-h1);   
        
        if (windows[i]->visible && Window->visible)
        {
           if ((((mousex>=(l2))&&(mousey>=(t2)))&&(mousex<=(l2+w2))&&(mousey<=(t2+h2))))
           {
              if (i == Window->windowid) 
              {
                    if (Window->modalhalt) return false;
                    return true;
              }
           }
        }
        if (((((mousex>=(windows[i]->left))&&(mousey>=(windows[i]->top)))&&(mousex<=(windows[i]->left+windows[i]->width))&&(mousey<=(windows[i]->top+windows[i]->height)))))
        {
          l1 = windows[i]->left;
          t1 = windows[i]->top;
          w1 = windows[i]->width;
          h1 = windows[i]->height;        
        }
      }
     }
   
     if (Window->modalhalt) iswindow = false;

     return iswindow;
}
