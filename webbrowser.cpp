// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "webbrowser.h" // class's header file
#include "fewebkit.h"

bool webbrowsercontrolon = false;

bool webbrowser_mousedown_on = false, webbrowser_mousemove_on = false, webbrowser_mouseup_on = false;
bool webbrowser_keydown_on = false, webbrowser_keypress_on = false, webbrowser_keyup_on = false;

extern void fegui_messagebox(int handlewindow,char* text,char *caption,int msgtype);

void renderwebbrowser(TControl *sender)
{
    TWebBrowser* webbrowser = dynamic_cast <TWebBrowser*>((TWebBrowser*)sender);
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    int wcaph = sender->window->height-sender->window->clientheight;
       
    if (sender->visible)
    {
       l0 = sender->window->left+sender->left;
       t0 = sender->window->top+wcaph+sender->top;
       w0 = sender->width;
       h0 = sender->height;
       l = l0;
       t = t0;
       w = w0;
       h = h0;

       if (w < 64)
       {
                webbrowser->hscroll->visible = false;
                webbrowser->vscroll->visible = false;
                return;
       }
       if (h < 64)
       {
                webbrowser->hscroll->visible = false;
                webbrowser->vscroll->visible = false;
                return;
       }

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


       webbrowser->hscroll->left = sender->left+2;
       webbrowser->hscroll->top = ((sender->top+h)-20)-6;
       webbrowser->hscroll->width = (w-20)-4;
       webbrowser->hscroll->height = 20;
       webbrowser->hscroll->visible = true;
     
       webbrowser->vscroll->left = ((sender->left+w)-20)-2;
       webbrowser->vscroll->top = sender->top-2;
       webbrowser->vscroll->width = 20;
       webbrowser->vscroll->height = (h-20)-3;
       webbrowser->vscroll->visible = true;

       webbrowser->hscroll->fastchange = true;
       webbrowser->hscroll->smallchange = 1;
       webbrowser->hscroll->max = 768;
     
       webbrowser->vscroll->fastchange = true;
       webbrowser->vscroll->smallchange = 1;
       webbrowser->vscroll->max = 768;

       if (mouseb)
       {
         if (sender->IsInControl(sender)&&((sender->IsInControl(webbrowser->hscroll))||(sender->IsInControl(webbrowser->vscroll)))) isinuse = 1;
         else isinuse = 0;
       }
       else isinuse = 0;

       if (sender->window->width<96) webbrowser->vscroll->visible = false, webbrowser->hscroll->visible = false;
       if (sender->window->height<64) webbrowser->vscroll->visible = false, webbrowser->hscroll->visible = false;
     
       if (sender->flat)
       {
         if (sender->IsInControl(sender) && (!IsInAnyMenu()))
         {
           webbrowser->hscroll->flat = false;
           webbrowser->vscroll->flat = false;
         } else
         {
           webbrowser->hscroll->flat = true;
           webbrowser->vscroll->flat = true;
         }
       }

       if (webbrowser->hscroll->visible && webbrowser->vscroll->visible)
       {
         w -= 24;
         h -= 25;
         l += 2;
         t -= 1;
       }

       if (mouseb)
       {
         if (sender->IsInControl(sender))
         {
           if (webbrowsercontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
           activewebbrowser = webbrowser->browser;
         } else
         {
           activewebbrowser = -1;
           webbrowsercontrolon = false;
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
       
       if (webbrowser->borderstyle==bsSingle)
       {
        drawcontroledge(l,t,w,h,14,a);
        fillrect(l,t+1,l+w-1,t+h-1,webbrowser->color,a);
        l+=2;
        t+=2;
        w-=5;
        h-=3;
        fillrect(l,t+1,l+w-1,t+h-1,webbrowser->color,a);
       }
       else
       {
        fillrect(l,t+1,l+w-1,t+h,webbrowser->color,a);
       }

       if (webbrowser->initialized==0)
       {
//        webbrowser->browser = fewebkit_createbrowser(webbrowser->width,webbrowser->height,(char*)webbrowser->url.c_str());
        webbrowser->browser = fewebkit_createbrowser(1024,1024,(char*)webbrowser->url.c_str());
        webbrowser->initialized = 1;
       }

       int hl = webbrowser->hscroll->position;
       int vt = webbrowser->vscroll->position;

       int mx = (mousex-(webbrowser->window->left+webbrowser->left))+hl;
       int my = ((mousey-(webbrowser->window->top+webbrowser->top))-16)+vt;

       if (webbrowser->initialized==1)
       {
         if (isinuse == 0)
         {

         if (webbrowser_mousedown_on)
         {
            fewebkit_mousedown(webbrowser->browser,mx,my);
         }

         if (webbrowser_mousemove_on)
         {
            fewebkit_mousemove(webbrowser->browser,mx,my);
         }

         if (webbrowser_mouseup_on)
         {
            fewebkit_mouseup(webbrowser->browser,mx,my);
         }
         /*
         if (activewindow == webbrowser->window->windowid)
         {
          if (webbrowser->focused) activewebbrowser = webbrowser->browser;
         }
         */

         }

        begindrawing();
        glPushMatrix();
        glColor4ub(255,255,255,a);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2i(l,t);
        glTexCoord2f(1,0); glVertex2i(l+w,t);
        glTexCoord2f(1,1); glVertex2i(l+w,t+h+1);
        glTexCoord2f(0,1); glVertex2i(l,t+h+1);
        glEnd();
        glPopMatrix();       
        enddrawing();

        int x=0; x = 1;
		int texon = glIsEnabled(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        begindrawing();

        glEnable(GL_SCISSOR_TEST);
        glScissor(l,height-(t+h+1),w,h+1);
        fewebkit_render(webbrowser->browser);
        int ow = w,oh = h;
        w = 1024;
        h = 1024;
        glColor4ub(255,255,255,a);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2i(l-hl,t-vt);
        glTexCoord2f(1,0); glVertex2i(l+w-hl,t-vt);
        glTexCoord2f(1,1); glVertex2i(l+w-hl,t+h-vt);
        glTexCoord2f(0,1); glVertex2i(l-hl,t+h-vt);
        glEnd();
        w = ow;
        h = oh;
        glDisable(GL_SCISSOR_TEST);

		enddrawing();
        if (texon) glEnable(GL_TEXTURE_2D);
        else glDisable(GL_TEXTURE_2D);
       }

       glDisable(GL_SCISSOR_TEST);
    }
    webbrowser_keydown_on = false;
    webbrowser_keyup_on = false;
    webbrowser_keypress_on = false;
    webbrowser_mousedown_on = false;
    webbrowser_mousemove_on = false;
    webbrowser_mouseup_on = false;
}

TWebBrowser::TWebBrowser(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="webbrowser";
          visible = false;
          left=0;
          top=0;
          width=256;
          height=256;
          parent = window;
          alphavalue = window->alphavalue;
          color = clBtnFace;
          caption="webbrowser";
          borderstyle = bsNone;
          initialized = 0;
          url = "";
          render = renderwebbrowser;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;    
          activewebbrowser = -1;
          hscroll = new TListScrollBar(window);
          hscroll->kind = sbHorizontal;
          hscroll->twinkle = false;
          hscroll->showborder = false;
          hscroll->width = width;
          hscroll->height = 20;
          hscroll->left = left+(width-4);
          hscroll->top = top;
          hscroll->visible = false;
          vscroll = new TListScrollBar(window);
          vscroll->kind = sbVertical;
          vscroll->twinkle = false;
          vscroll->showborder = false;
          vscroll->width = 20;
          vscroll->height = height;
          vscroll->left = left+(width-4);
          vscroll->top = top;
          vscroll->visible = false;
          webbrowserhandle = window->numwebbrowsers;
          window->webbrowsers[window->numwebbrowsers] = this;
          window->numwebbrowsers++;
          window->numcontrols++;
}

TWebBrowser::~TWebBrowser()
{
        activewebbrowser = -1;
        delete hscroll;
        delete vscroll;
         // if (window->webbrowsers[webbrowserhandle]) delete window->webbrowsers[webbrowserhandle];
}

void TWebBrowser::rendercontrol()
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
    if (clicked==true)
    {
      if (this->initialized) activewebbrowser = this->browser;
    }
  } else
  {
   focused = false;
   if (clicked==true) activewebbrowser = -1;
  }
//}
} else
{
 focused = false;
 if (clicked==true) activewebbrowser = -1;
}
if ((focused==true)&&(clicked==true)&&(webbrowsercontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) webbrowsercontrolon = false;
}
} else
{
 focused = false;
 if (clicked==true) activewebbrowser = -1;
}
}
}
if (visible==true) hscroll->rendercontrol();
if (visible==true) vscroll->rendercontrol();
instance = this;
window->webbrowsers[controlid] = this;
}
void TWebBrowser::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->webbrowsers[controlid] = this;
  }
}
void TWebBrowser::hide()
{
          activewebbrowser = -1;
          visible = false;
          window->webbrowsers[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif


#ifdef FEWEBKIT_LOADLIB


FEWEBKIT_CREATEBROWSER fewebkit_createbrowser;
FEWEBKIT_RENDER fewebkit_render;
FEWEBKIT_KEYUP fewebkit_keyup;
FEWEBKIT_KEYDOWN fewebkit_keydown;
FEWEBKIT_KEYPRESS fewebkit_keypress;
FEWEBKIT_MOUSEDOWN fewebkit_mousedown;
FEWEBKIT_MOUSEMOVE fewebkit_mousemove;
FEWEBKIT_MOUSEUP fewebkit_mouseup;

HINSTANCE fewebkithinst;

void fewebkit_init(void)
{
fewebkithinst = LoadLibrary("FEWEBKIT.DLL");
        if(!fewebkithinst){
            MessageBox(NULL,"This application has failed to start because FEWEBKIT.DLL was not found. Re-installing the application may fix this problem.","Unable To Locate Component",MB_OK|MB_ICONERROR);
            PostQuitMessage(0);
            exit(0);
            return;
        }

fewebkit_createbrowser = (FEWEBKIT_CREATEBROWSER)GetProcAddress(fewebkithinst, "_fewebkit_createbrowser");
fewebkit_render = (FEWEBKIT_RENDER)GetProcAddress(fewebkithinst, "_fewebkit_render");
fewebkit_keyup = (FEWEBKIT_KEYUP)GetProcAddress(fewebkithinst, "_fewebkit_keyup");
fewebkit_keydown = (FEWEBKIT_KEYDOWN)GetProcAddress(fewebkithinst, "_fewebkit_keydown");
fewebkit_keypress = (FEWEBKIT_KEYPRESS)GetProcAddress(fewebkithinst, "_fewebkit_keypress");
fewebkit_mousedown = (FEWEBKIT_MOUSEDOWN)GetProcAddress(fewebkithinst, "_fewebkit_mousedown");
fewebkit_mousemove = (FEWEBKIT_MOUSEMOVE)GetProcAddress(fewebkithinst, "_fewebkit_mousemove");
fewebkit_mouseup = (FEWEBKIT_MOUSEUP)GetProcAddress(fewebkithinst, "_fewebkit_mouseup");
}

void fewebkit_uninit(void)
{                    
 fewebkit_createbrowser = NULL;
 fewebkit_render = NULL;
 fewebkit_keyup = NULL;
 fewebkit_keydown = NULL;
 fewebkit_keypress = NULL;
 fewebkit_mousedown = NULL;
 fewebkit_mousemove = NULL;
 fewebkit_mouseup = NULL;
 FreeLibrary(fewebkithinst);
}

#else

void fewebkit_init(void)
{

}

void fewebkit_uninit(void)
{

}

#endif


int _fegui_windowexists(int winid);
int createwebbrowser(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int btnid = 0;
   btnid = windows[winid]->numwebbrowsers;
   TWebBrowser* webbrowser = new TWebBrowser(windows[winid]);
   webbrowser->alphavalue = 255;
   webbrowser->enabled = true;
   webbrowser->width=256;
   webbrowser->height=256;
   webbrowser->left=32;
   webbrowser->top=32;
   webbrowser->visible = false;   
   return btnid;
 }
 return 0;
}

void webkit_keydown(unsigned char key)
{
        if (activewebbrowser >= 0)
        {
               fewebkit_keypress(activewebbrowser,key);
               fewebkit_keydown(activewebbrowser,key);
        }
}

void webkit_keyup(unsigned char key)
{
        if (activewebbrowser >= 0)
        {
               fewebkit_keyup(activewebbrowser,key);
        }
}

int activewebbrowser = -1;

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

