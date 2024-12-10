// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "speedbutton.h" // class's header file


bool speedbtncontrolon = false;
void renderspeedbutton(TControl *sender)
{
TSpeedButton* sbtn = dynamic_cast <TSpeedButton*>((TSpeedButton*)sender);
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
if (windowresize || (windowresizeside>0)) isinwin = false;
if (!sbtn->enabled) isinwin = false;

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

//controlon = false;
if (sender->window->activecontrol==sender->controlid)
{
sender->clicked = false;
if (mouseb==1)
{
sender->clicked = false;
speedbtncontrolon = false;
if (sender->IsInControl(sender)==true)
{
if (isinwin)
{
  if (sender->flat)
  {
    if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height+1,7,alphacontrol); // sender->alphavalue-alphacontrol);
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
  speedbtncontrolon = true;
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
  speedbtncontrolon = false;
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
  if (speedbtncontrolon==true) sender->clicked = true;
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
     if ((sender->IsInControl(sender)==true)&&(isinwin)) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top,sender->width,sender->height,7,alphacontrol); // sender->alphavalue-alphacontrol);
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
  //textattr(clBlack,alphacontrol,12,FW_NORMAL);
  //if (sbtn->icon) textout(sender->window->left+sender->left+((((sender->width+sbtn->icon->width)-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
  //else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
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
  //textattr(clBlack,alphacontrol,12,FW_NORMAL);
  //if (sbtn->icon) textout(sender->window->left+sender->left+((((sender->width+sbtn->icon->width)-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
  //else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
}
}
int sblm = 0;
if (strlen(sender->caption)>0) sblm = sbtn->spacing;
if ((mouseb==1)&&(isinwin))
{
if (sender->IsInControl(sender)==false)
{
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  if (sbtn->icon) textout(sender->window->left+sender->left+((((sender->width+(sbtn->icon->width+sblm))-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
  else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
  if (sbtn->icon) 
  {
    drawimage(sender->window->left+sender->left+((((sender->width+(sbtn->icon->width-sblm))-string_width(sender->caption))/2))-sbtn->icon->width,sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2),sbtn->icon,sbtn->alphavalue,sbtn->transparent,sbtn->iconbackground);
  }
}
else
{
  textattr(clBlack,alphacontrol,12,FW_NORMAL);
  if (sbtn->icon) textout(sender->window->left+sender->left+((((sender->width+(sbtn->icon->width+sblm))-string_width(sender->caption))/2))+1,sender->window->top+wcaph+sender->top+((sender->height-12-3)/2)+1,sender->caption);
  else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2))+1,sender->window->top+wcaph+sender->top+((sender->height-12-3)/2)+1,sender->caption);
  if (sbtn->icon) 
  {
    drawimage(sender->window->left+sender->left+((((sender->width+(sbtn->icon->width-sblm))-string_width(sender->caption))/2))-sbtn->icon->width+1,sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2)+1,sbtn->icon,sbtn->alphavalue,sbtn->transparent,sbtn->iconbackground);
  }
}
}
else
{
  if (sbtn->enabled) textattr(clBlack,alphacontrol,12,FW_NORMAL);
  else textattr(clBtnHighlight,alphacontrol,12,FW_NORMAL);
  if (sbtn->icon) 
  {
  if (!sbtn->enabled)
  {
    textout(sender->window->left+sender->left+((((sender->width+(sbtn->icon->width+sblm))-string_width(sender->caption))/2))+1,sender->window->top+wcaph+sender->top+((sender->height-12-3)/2)+1,sender->caption);
    textattr(clBtnShadow,alphacontrol,12,FW_NORMAL);
    textout(sender->window->left+sender->left+((((sender->width+(sbtn->icon->width+sblm))-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
    drawimagemask((sender->window->left+sender->left+((((sender->width+(sbtn->icon->width-sblm))-string_width(sender->caption))/2))-sbtn->icon->width)+1,(sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2))+1,sbtn->icon,sbtn->alphavalue,clBtnHighlight,sbtn->transparent,sbtn->iconbackground);
    drawimagemask((sender->window->left+sender->left+((((sender->width+(sbtn->icon->width-sblm))-string_width(sender->caption))/2))-sbtn->icon->width),sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2),sbtn->icon,sbtn->alphavalue,clBtnShadow,sbtn->transparent,sbtn->iconbackground);
  }
  else 
  {
    textout(sender->window->left+sender->left+((((sender->width+(sbtn->icon->width+sblm))-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
    drawimage(sender->window->left+sender->left+((((sender->width+(sbtn->icon->width-sblm))-string_width(sender->caption))/2))-sbtn->icon->width,sender->window->top+wcaph+sender->top+(((sender->height)-12-3)/2),sbtn->icon,sbtn->alphavalue,sbtn->transparent,sbtn->iconbackground);
  }
  } else 
  {
    if (!sbtn->enabled)
    {
      textout((sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)))+1,(sender->window->top+wcaph+sender->top+((sender->height-12-3)/2))+1,sender->caption);
      textattr(clBtnShadow,alphacontrol,12,FW_NORMAL);
      textout((sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2))),(sender->window->top+wcaph+sender->top+((sender->height-12-3)/2)),sender->caption);
    } else textout(sender->window->left+sender->left+(((sender->width-string_width(sender->caption))/2)),sender->window->top+wcaph+sender->top+((sender->height-12-3)/2),sender->caption);
  }
}

glDisable(GL_SCISSOR_TEST);
}
}


TSpeedButton::TSpeedButton(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="speedbutton";
          visible = false;
          enabled = true;
          left=0;
          top=0;
          width=64;
          height=128;
          spacing=4;
          iconbackground = clBlue;
          transparent = true;
          alphavalue = window->alphavalue;
          caption="speedbutton";
          icon = NULL;
          render = renderspeedbutton;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          window->speedbuttons[window->numspeedbuttons] = this;
          window->numspeedbuttons++;
          window->numcontrols++;
}

TSpeedButton::~TSpeedButton()
{
  if (icon) freebmp(icon);
  icon = NULL;
}

void TSpeedButton::loadicon(char *filename)
{
  icon = loadbmp(filename);
}

void TSpeedButton::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(speedbtncontrolon==true)&&(!(windowresize || (windowresizeside>0))))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) speedbtncontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->speedbuttons[controlid] = this;
}
void TSpeedButton::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->speedbuttons[controlid] = this;
  }
}
void TSpeedButton::hide()
{
          visible = false;
          window->speedbuttons[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createspeedbutton(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int sbtnid = 0;
   sbtnid = windows[winid]->numspeedbuttons;
   TSpeedButton* speedbutton = new TSpeedButton(windows[winid]);
   speedbutton->alphavalue = 255;
   speedbutton->enabled = true;
   speedbutton->width=72;
   speedbutton->height=24;
   speedbutton->left=32;
   speedbutton->top=32;
   speedbutton->visible = false;
   return sbtnid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)



