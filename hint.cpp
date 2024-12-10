// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "hint.h"
#include "tooltip.h"

bool hintrect_reset = false;
void hintrect(bool focus,char *text);
void hintcontrol(TControl *ctrl);
void hintwincontrol(TWinControl *wctrl);

void hintrect(bool focus,char *text)
{
    bool f = focus;  // getarea(x,y,w,h);
    if (IsInAnyMenu()) return;
    //hintrect_reset = true;
    if (f)
    {
      if (tooltip_control)
      {
        tooltip_fadeout = false;
        tooltip_incontrol = true;
      }
      if (hintrect_reset)
      {
        resettooltip();
        hintrect_reset = false;
      }
      tooltip = text;
      tooltip_visible = true;
      tooltip_control = true;
    } else 
    {
      if (hintrect_reset)
      {
       if (!tooltip_visible)
       {
        tooltip_control = false;
        tooltip_incontrol = false;
       }
      }
      if (hintrect_reset)
      {
       if (!tooltip_control)
       {
        if (tooltip_fadealpha > 0) 
        {
          tooltip_control = true;
          tooltip_fadeout = true;
          tooltip_visible = true;
        }
        if (tooltip_fadealpha<=0)
        {
          tooltip_visible = false;
          tooltip_showing = false;
          tooltip_fadeout = false;
          tooltip_control = false;
          tooltip_fadealpha = 0;
        }
       } 
      } else hintrect_reset = true;
      // tooltip_control = false;
      // tooltip_incontrol = false;
    }
}

void hintcontrol(TControl *ctrl)
{
  if (ctrl->showhint)
  {
    bool f = ctrl->IsInControl(ctrl);
    if (!ctrl->window->IsInWindow(ctrl->window)) f = false;
    
    if (IsInAnyMenu()) return;
    
    //resethint = true;
    if (f)
    {
      if (tooltip_control)
      {
        tooltip_fadeout = false;
        tooltip_incontrol = true;
      }
      if (ctrl->resethint)
      {
        resettooltip();
        ctrl->resethint = false;
      }
      tooltip = ctrl->hint;
      tooltip_visible = true;
      tooltip_control = true;
    } else 
    {
      if (ctrl->resethint)
      {
       if (!tooltip_visible)
       {
        tooltip_control = false;
        tooltip_incontrol = false;
       }
      }
      if (ctrl->resethint)
      {
       if (!tooltip_control)
       {
        if (tooltip_fadealpha > 0) 
        {
          tooltip_control = true;
          tooltip_fadeout = true;
          tooltip_visible = true;
        }
        if (tooltip_fadealpha<=0)
        {
          tooltip_visible = false;
          tooltip_showing = false;
          tooltip_fadeout = false;
          tooltip_control = false;
          tooltip_fadealpha = 0;
        }
       } 
      } else ctrl->resethint = true;
      // tooltip_control = false;
      // tooltip_incontrol = false;
    }
  }
  else
  {
    if (ctrl->window->IsInWindow(ctrl->window))
    {
      if (ctrl->IsInControl(ctrl))
      {
        if (tooltip_fadealpha > 0) 
        {
          tooltip_control = true;
          tooltip_fadeout = true;
          tooltip_visible = true;
        }
        if (tooltip_fadealpha<=0)
        {
          tooltip_visible = false;
          tooltip_showing = false;
          tooltip_fadeout = false;
          tooltip_control = false;
          tooltip_fadealpha = 0;
        }
      }
    }
  }
}

void hintwincontrol(TWinControl *wctrl)
{
  if (wctrl->showhint)
  {
    bool f = wctrl->IsInWindow(wctrl);
    if (IsInAnyMenu()) return;
    //resethint = true;
    if (f)
    {
      if (tooltip_control)
      {
        tooltip_fadeout = false;
        tooltip_incontrol = true;
      }
      if (wctrl->resethint)
      {
        resettooltip();
        wctrl->resethint = false;
      }
      tooltip = wctrl->hint;
      tooltip_visible = true;
      tooltip_control = true;
    } else 
    {
      if (wctrl->resethint)
      {
       if (!tooltip_visible)
       {
        tooltip_control = false;
        tooltip_incontrol = false;
       }
      }
      if (wctrl->resethint)
      {
       if (!tooltip_control)
       {
        if (tooltip_fadealpha > 0) 
        {
          tooltip_control = true;
          tooltip_fadeout = true;
          tooltip_visible = true;
        }
        if (tooltip_fadealpha<=0)
        {
          tooltip_visible = false;
          tooltip_showing = false;
          tooltip_fadeout = false;
          tooltip_control = false;
          tooltip_fadealpha = 0;
        }
       } 
      } else wctrl->resethint = true;
      // tooltip_control = false;
      // tooltip_incontrol = false;
    }
  }
}


