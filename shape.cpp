// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "shape.h" // class's header file


bool shapecontrolon = false;
void rendershape(TControl *sender)
{
    TShape* shape = dynamic_cast <TShape*>((TShape*)sender);
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    int wcaph = sender->window->height-sender->window->clientheight;
       
    if (sender->visible)
    {
       int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
       l0 = sender->window->left+sender->left;
       t0 = sender->window->top+wcaph+sender->top;
       w0 = sender->width;
       h0 = sender->height;
       l = l0;
       t = t0;
       w = w0;
       h = h0;
       glEnable(GL_SCISSOR_TEST);
       glScissor(l-1,height-(t+h+1),w+1,h+1);

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
       
       if (mouseb)
       {
         if (sender->IsInControl(sender))
         {
           if (shapecontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           shapecontrolon = false;
           sender->clicked = false;
           sender->focus = false;
           sender->focused = false;
         }
       }
       else
       {
           sender->clicked = false;
       }
       
       switch(shape->shape)
       {
         case stRectangle:
         {
            fillrect(l,t+1,l+w-1,t+h-1,shape->brush->color,alphacontrol);
            rectangle(l,t+1,l+w-1,t+h-1,shape->pen->color,alphacontrol);
            break;
         };
         case stEllipse:
         {
            drawellipse(l,t+1,l+(w/2)-1,t+(h/2),shape->brush->color,alphacontrol);
            drawcircle(l,t+1,l+(w/2)-1,t+(h/2),shape->pen->color,alphacontrol);
            break;
         };
       };

       //int cw = textwidth(sender->caption)+1;
       //int ch = 16;
       //textattr(clBlack,alphacontrol,12,FW_NORMAL);
       //textout(sender->window->left+sender->left+((sender->width-(cw))/2),sender->window->top+wcaph+sender->top+((sender->height-(ch))/2),sender->caption);
       glDisable(GL_SCISSOR_TEST);
    }
}

void TShape::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(shapecontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) shapecontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->shapes[controlid] = this;
}
void TShape::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->shapes[controlid] = this;
  }
}
void TShape::hide()
{
          visible = false;
          window->shapes[controlid] = this;

}

TShape::TShape(TWindow *Window)
{
brush = new TBrush();
pen = new TPen();
shape = stRectangle;
window = Window;
id=window->numcontrols+100;
name="shape";
visible = false;
left=0;
top=0;
width=64;
height=64;
alphavalue = window->alphavalue;
render = rendershape;
controlid = window->numcontrols;
onclick = NULL;
onkeydown = NULL;
onkeyup = NULL;
visible = false;
instance = this;
window->shapes[window->numshapes] = this;
window->numshapes++;
window->numcontrols++;
}

TShape::~TShape()
{
delete brush;
delete pen;
}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createshape(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int shpid = 0;
   shpid = windows[winid]->numshapes;
   TShape* shape = new TShape(windows[winid]);
   shape->alphavalue = 255;
   shape->enabled = true;
   shape->width=72;
   shape->height=24;
   shape->left=32;
   shape->top=32;
   shape->visible = false;
   return shpid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

