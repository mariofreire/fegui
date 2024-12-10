// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "toolbutton.h" // class's header file


void rendertoolbutton(TControl *sender)
{
TToolButton* tbtn = dynamic_cast <TToolButton*>((TToolButton*)sender);
TToolBar* tbar;
bool isinwin = false;
int wcaph = sender->window->height-sender->window->clientheight;
if (windows[activewindow]!=sender->window)
{
 if (sender->window->IsInWindow(windows[activewindow]))
 {
   isinwin = false;
 } else isinwin = true;
} else isinwin = true;
/*
if (activewindow==sender->window->windowid) isinwin = true;
else isinwin = isinotherwindow(sender->window);
*/

int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);

if (sender->visible == true)
{
if (tbtn->parent) tbar = dynamic_cast <TToolBar*>((TToolBar*)tbtn->parent);
if (windowresize || (windowresizeside>0)) isinwin = false;
if (!tbtn->enabled) isinwin = false;
/*
sender->left = 32;
sender->top = 32;
sender->width = 32;
sender->height = 32;
sender->caption = " ";
sender->enabled = true;
*/

if (tbtn->parent)
{
  sender->width = tbar->buttonwidth;
  sender->height = tbar->buttonheight;
  int toolbtnleft=0;
  if (tbar->controlid == tbtn->parent->controlid) toolbtnleft = (tbtn->index*(tbar->buttonwidth+1));
  tbtn->left = tbar->left+toolbtnleft+tbar->ident+2;
  tbtn->top = tbar->top+2;
}

int l = sender->window->left+sender->left-1;
int t = sender->window->top+wcaph+sender->top-1;
int w = sender->width+1;
int h = sender->height+2;
glEnable(GL_SCISSOR_TEST);
glScissor(l,height-(t+h+1),w,h+1); 

if (IsInAnyMenu()) sender->focused = false;

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

//controlon = false;
if (sender->window->activecontrol==sender->controlid)
{
sender->clicked = false;
if (mouseb==1)
{
sender->clicked = false;
toolbtncontrolon = false;
if (sender->IsInControl(sender)==true)
{
if (isinwin)
{
  if (sender->flat)
  {
    if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,7,alphacontrol); // sender->alphavalue-alphacontrol);
    else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,1,alphacontrol); // sender->alphavalue-alphacontrol);
} else
{
  if (sender->flat)
  {
    if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
    else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
}
  sender->clicked = false;
  toolbtncontrolon = true;
} else
{
if (isinwin)
{
  if (sender->flat)
  {
     if (sender->IsInControl(sender)==true) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
     else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
  sender->clicked = false;
  toolbtncontrolon = false;
} else
{
  if (sender->flat)
  {
    if ((sender->IsInControl(sender)==true) && (isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
    else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
}
}
}
else
{
if (isinwin)
{
  if (sender->flat)
  {
     if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
     else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
if (sender->IsInControl(sender)==true)
{
  if (toolbtncontrolon==true) sender->clicked = true;
}
} else
{
  if (sender->flat)
  {
   if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
   else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
}
}
}
else
{
sender->clicked = false;
if (mouseb==1)
{
if (sender->IsInControl(sender)==true)
{
  sender->window->activecontrol = sender->controlid;
if (isinwin)
{
  if (sender->flat)
  {
     if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height+1,7,alphacontrol); // sender->alphavalue-alphacontrol);
     else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,1,alphacontrol); // sender->alphavalue-alphacontrol);
  //textattr(clBlack,alphacontrol,12,FW_NORMAL);
  //textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
} else
{
  if (sender->flat)
  {
   if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
   else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
}
} else 
{
  if (sender->flat)
  {
    if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
    else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
  if (tbtn->parent)
  {
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  if (tbar->images->images[tbtn->imageindex]) textout(sender->window->left+sender->left+((((sender->width+tbar->images->images[tbtn->imageindex]->canvas->width)-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
  else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
  } else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
}
}
else
{
  sender->clicked = false;
  if (sender->flat)
  {
    if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,6,alphacontrol); // sender->alphavalue-alphacontrol);
    else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,10,alphacontrol); // sender->alphavalue-alphacontrol);
  }
  else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,0,alphacontrol); // sender->alphavalue-alphacontrol);
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  if (tbtn->parent) 
  {
   if (tbar->images->images[tbtn->imageindex]) textout(sender->window->left+sender->left+((((sender->width+tbar->images->images[tbtn->imageindex]->canvas->width)-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
   else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
  } else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
}
}
int sblm = 0;
if (strlen(sender->caption)>0) sblm = tbtn->spacing;
if ((mouseb==1)&&(isinwin))
{
if (sender->IsInControl(sender)==false)
{
  if (tbtn->parent) 
  {
   textattr(clBlack,alphacontrol,12,FW_NORMAL);
   if (tbtn->imageindex >= 0) textout(sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width+sblm))-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
   else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
   if (tbtn->imageindex >= 0) 
   {
     drawimage32(sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width-sblm))-string_width(sender->caption))/2))-tbar->images->images[tbtn->imageindex]->canvas->width,sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2),tbar->images->images[tbtn->imageindex]->canvas->width,tbar->images->images[tbtn->imageindex]->canvas->height,tbar->images->images[tbtn->imageindex]->canvas->format,tbar->images->images[tbtn->imageindex]->canvas->pixels,tbtn->alphavalue,tbtn->transparent,tbar->images->images[tbtn->imageindex]->transparentcolor);
   }
  } else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
}
else
{
  if (tbtn->parent) 
  {
   textattr(clBlack,alphacontrol,12,FW_NORMAL);
   if (tbtn->imageindex >= 0) textout(sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width+sblm))-string_width(sender->caption))/2))+1,sender->window->top+wcaph+sender->top+((sender->height-12-3)/2)+1,sender->caption);
   else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2))+1,sender->window->top+wcaph+sender->top+((sender->height-12-3)/2)+1,sender->caption);
   if (tbtn->imageindex >= 0) 
   {
     drawimage32(sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width-sblm))-string_width(sender->caption))/2))-tbar->images->images[tbtn->imageindex]->canvas->width+1,sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2)+1,tbar->images->images[tbtn->imageindex]->canvas->width,tbar->images->images[tbtn->imageindex]->canvas->height,tbar->images->images[tbtn->imageindex]->canvas->format,tbar->images->images[tbtn->imageindex]->canvas->pixels,tbtn->alphavalue,tbtn->transparent,tbar->images->images[tbtn->imageindex]->transparentcolor);
   }
  } else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2))+1,sender->window->top+wcaph+sender->top+((sender->height-12-3)/2)+1,sender->caption);
}
}
else
{
  if (tbtn->enabled) textattr(clBlack,alphacontrol,12,FW_NORMAL);
  else textattr(clBtnHighlight,alphacontrol,12,FW_NORMAL);
  if ((tbtn->imageindex >= 0) && (tbtn->parent))
  {
  if (!tbtn->enabled)
  {
   if (tbtn->parent) 
   {
     textout(sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width+sblm))-string_width(sender->caption))/2))+1,sender->window->top+wcaph+sender->top+((sender->height-12-3)/2)+1,sender->caption);
     textattr(clBtnShadow,alphacontrol,12,FW_NORMAL);
     textout(sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width+sblm))-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
     // drawimagemask((sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width-sblm))-string_width(sender->caption))/2))-tbar->images->images[tbtn->imageindex]->canvas->width)+1,(sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2))+1,tbar->images->images[tbtn->imageindex],tbtn->alphavalue,clBtnHighlight,tbtn->transparent,tbar->images->images[tbtn->imageindex]->transparentcolor);
     // drawimagemask((sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width-sblm))-string_width(sender->caption))/2))-tbar->images->images[tbtn->imageindex]->canvas->width),sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2),tbar->images->images[tbtn->imageindex],tbtn->alphavalue,clBtnShadow,tbtn->transparent,tbar->images->images[tbtn->imageindex]->transparentcolor);
   }
  }
  else 
  {
   if (tbtn->parent) 
   {
    textout(sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width+sblm))-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
    drawimage32(sender->window->left+sender->left+((((sender->width+(tbar->images->images[tbtn->imageindex]->canvas->width-sblm))-string_width(sender->caption))/2))-tbar->images->images[tbtn->imageindex]->canvas->width,sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2),tbar->images->images[tbtn->imageindex]->canvas->width,tbar->images->images[tbtn->imageindex]->canvas->height,tbar->images->images[tbtn->imageindex]->canvas->format,tbar->images->images[tbtn->imageindex]->canvas->pixels,tbtn->alphavalue,tbtn->transparent,tbar->images->images[tbtn->imageindex]->transparentcolor);
   }
  }
  } else 
  {
    if (!tbtn->enabled)
    {
      textout((sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)))+1,(sender->window->top+wcaph+sender->top+((sender->height-12-3)/2))+1,sender->caption);
      textattr(clBtnShadow,alphacontrol,12,FW_NORMAL);
      textout((sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2))),(sender->window->top+wcaph+sender->top+((sender->height-12-3)/2)),sender->caption);
    } else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
  }
}

if (IsInAnyMenu()) sender->focused = false;

glDisable(GL_SCISSOR_TEST);
}
}






TToolButton::TToolButton(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="toolbutton";
          visible = false;
          enabled = true;
          left=0;
          top=0;
          width=20;
          height=20;
          spacing=4;
          index=0;
          imageindex = -1;
          transparent = true;
          alphavalue = window->alphavalue;
          caption="toolbutton";
          parent = window;
          render = rendertoolbutton;
          controlid = window->numcontrols;
          handleid = window->numtoolbuttons;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->toolbuttons[window->numtoolbuttons] = this;
          window->numtoolbuttons++;
          window->numcontrols++;
}

TToolButton::~TToolButton()
{
  //if (icon) freebmp(icon);
  //icon = NULL;
}


void TToolButton::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(toolbtncontrolon==true)&&(!(windowresize || (windowresizeside>0))))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) toolbtncontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->toolbuttons[handleid] = this;
}
void TToolButton::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->toolbuttons[handleid] = this;
  }
}
void TToolButton::hide()
{
          visible = false;
          window->toolbuttons[handleid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createtoolbutton(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int tbtnid = 0;
   tbtnid = windows[winid]->numtoolbuttons;
   TToolButton* toolbutton = new TToolButton(windows[winid]);
   toolbutton->alphavalue = 255;
   toolbutton->enabled = true;
   toolbutton->width=72;
   toolbutton->height=24;
   toolbutton->left=32;
   toolbutton->top=32;
   toolbutton->visible = false;
   return tbtnid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)



