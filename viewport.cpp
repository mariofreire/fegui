// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "viewport.h" // class's header file

int viewportleft=0,viewporttop=0,viewportright=0,viewportbottom=0;

void setviewport(int left,int top,int right,int bottom)
{
  viewportleft   = left;
  viewporttop    = top;
  viewportright  = right;
  viewportbottom = bottom;
}

bool viewportcontrolon = false;
void renderviewport(TControl *sender)
{
    TViewport* viewport = dynamic_cast <TViewport*>((TViewport*)sender);
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    int wcaph = sender->window->height-sender->window->clientheight;
       
    if (sender->visible)
    {
       l0 = sender->window->left+sender->left;
       t0 = sender->window->top+wcaph+sender->top;
       w0 = sender->width;
       h0 = sender->height;
       if (windowmanager == 0)
       {
        t0 += 3;
        h0 -= windowtopbarheightdefault;
        h0 -= 1;
       }
       l = l0;
       t = t0;
       w = w0;
       h = h0;
       
       if (viewport->window->windowstate == wsMinimized) return;
       
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
       
       int bctl = 18;
       
       if (sender->flat)
       {
         if (sender->IsInControl(sender)) bctl = 18;
         else bctl = 16;
       }

       if (mouseb)
       {
         if (sender->IsInControl(sender))
         {
           if (viewportcontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           viewportcontrolon = false;
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
       
       if (viewport->borderstyle==bsSingle)
       {
        drawcontroledge(l,t+3,w,h,bctl,a);
        if (viewport->backgroundalpha<255)
        {
          viewport->window->subtessleft=sender->left+1;
          viewport->window->subtesstop=sender->top+6;
          viewport->window->subtesswidth=sender->width-3;
          viewport->window->subtessheight=sender->height-4;
        }
        fillrect(l+1,t+5,l+w-2,t+h+1,viewport->color,blendto(a,viewport->backgroundalpha));
       }
       else
       {
        if (viewport->backgroundalpha<255)
        {
          viewport->window->subtessleft=sender->left+1;
          viewport->window->subtesstop=sender->top+6;
          viewport->window->subtesswidth=sender->width-3;
          viewport->window->subtessheight=sender->height-4;
        }
        fillrect(l+1,t+5,l+w-2,t+h+1,viewport->color,blendto(a,viewport->backgroundalpha));
       }

if (viewport->window->windowstate != wsMinimized)
{
 begindrawing();
  
  int l=0,t=0,w=0,h=0,bw=0,bh=0,lw=0,rw=0;
  glPushMatrix ();
//  glViewport(this->left,(-this->top+this->height-32),this->width,this->height);
 // glTranslated(this->left,this->top,0);
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
 // gluPerspective(45.0, width/height, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth

  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View
  
  bw = sender->width;//this->width-this->clientwidth;
  bh = sender->height;//this->height-this->clientheight;
  if (windowmanager == 0) bh -= windowtopbarheightdefault;

  if ((viewport->borderstyle == bsNone)&&(windowmanager == 1)) lw = 6;
  else lw = 2;

            glPushMatrix ();
            glPopMatrix ();

  if ((viewport->borderstyle == bsNone)&&(windowmanager == 1)) lw = 6;
  else lw = 2;

  if ((viewport->borderstyle == bsNone)&&(windowmanager == 1)) rw = 12;
  else rw = 8;

       l0 = sender->window->left+sender->left;
       t0 = sender->window->top+wcaph+sender->top-((wcaph/2)+4);
       if (windowmanager == 0) t0 += 14;
       w0 = sender->width-2;
       h0 = sender->height-wcaph;
       if (windowmanager == 0) h0 -= windowtopbarheightdefault+14;
       l = l0+2;
       t = (getscreenheight()-t0)+2;
       w = w0-3;
       h = h0+((wcaph/2)+6);
       t-=h+wcaph;
       l-=1;
       t-=1;
       h+=2;
       w+=2;

  glPushMatrix ();
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
  //gluPerspective(45.0, (float)w/(float)h, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth
  glViewport(l,t,w,h);
//  gluOrtho2D( 0.0,w,h,0.0 );

  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
//            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glScissor(l,t,w,h);
            glPushMatrix ();
            if (viewport->window->windowstate != wsMinimized)
            {
              if (viewport->visible && viewport->enabled)
              {
                if (viewport->onrender) viewport->onrender(viewport);
              }
            }
            glPopMatrix ();

            glPopMatrix ();
            glPopMatrix ();

 enddrawing();
}
else
{
 viewport->window->subtessleft=0;
 viewport->window->subtesstop=0;
 viewport->window->subtesswidth=0;
 viewport->window->subtessheight=0;
}

       glDisable(GL_SCISSOR_TEST);
    }
}

TViewport::TViewport(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="viewport";
          visible = false;
          enabled = true;
          left=0;
          top=0;
          width=64;
          height=128;
          parent = window;
          align = alNone;
          alphavalue = window->alphavalue;
          backgroundalpha = 255;
          color = clBtnFace;
          caption="viewport";
          borderstyle = bsSingle;
          render = renderviewport;
          controlid = window->numcontrols;
          handleid = window->numviewports;
          onrender = NULL;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->viewports[window->numviewports] = this;
          window->numviewports++;
          window->numcontrols++;
}

void TViewport::rendercontrol()
{
if (align==alClient)
{
  left = 3;
  top = -3;
  width = window->clientwidth-7;
  height = window->clientheight-5;   
}
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

if ((focused==true)&&(clicked==true)&&(viewportcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) viewportcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->viewports[controlid] = this;
}
void TViewport::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->viewports[controlid] = this;
  }
}
void TViewport::hide()
{
          visible = false;
          window->viewports[controlid] = this;

}



#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif
extern TWindow* window_i[256];
int _fegui_windowexists(int winid);
int createviewport(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int viewportid = 0;
   viewportid = windows[winid]->numviewports;
   TViewport* viewport = new TViewport(window_i[winid]);
   viewport->alphavalue = 255;
   viewport->enabled = true;
   viewport->width=128;
   viewport->height=128;
   viewport->left=32;
   viewport->top=32;
   viewport->visible = false;
   return viewportid;
 
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

