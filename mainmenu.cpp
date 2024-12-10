// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "mainmenu.h" // class's header file


int oldmi = -1;        
int menuitemclick = 0;

bool menuitemdownclick = false;
int menuitemdownindex = -1;

bool mainmenucontrolon = false;
void rendermainmenu(TControl *sender)
{
    TMainMenu* mainmenu = dynamic_cast <TMainMenu*>((TMainMenu*)sender);
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
       
       if (mainmenu->parent)
       {
         for (int i=0;i<sender->window->numtoolbars;i++)
         {
           TToolBar* tbctrl = dynamic_cast <TToolBar*>((TToolBar*)mainmenu->parent);
           if (tbctrl==tbctrl->window->toolbars[i])
           {
             mainmenu->bevelouter = bvNone;
             mainmenu->bevelinner = bvNone;
             mainmenu->left = tbctrl->left;
             mainmenu->top = tbctrl->top;
             mainmenu->width = tbctrl->width;
             mainmenu->height = tbctrl->height;
             mainmenu->visible = tbctrl->visible;
           }
         }
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

       if (mouseb)
       {
         if (sender->IsInControl(sender))
         {
           if (mainmenucontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           mainmenucontrolon = false;
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
       
       if (mainmenu->borderstyle==bsSingle)
       {
        drawcontroledge(l,t,w,h,14,a);
        fillrect(l,t+1,l+w-1,t+h-1,mainmenu->color,a);
        l+=2;
        t+=2;
        w-=5;
        h-=3;
        if (mainmenu->bevelouter==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (mainmenu->bevelouter==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (mainmenu->bevelouter==bvSpace) drawcontroledge(l,t,w,h,6,a);
        fillrect(l,t+1,l+w-1,t+h-1,mainmenu->color,a);
        if (mainmenu->bevelouter!=bvNone)
        {
         l++;
         t++;
         w-=2;
         h-=2;
        } 
        if (mainmenu->bevelinner==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (mainmenu->bevelinner==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (mainmenu->bevelinner==bvSpace) drawcontroledge(l,t,w,h,6,a);
        fillrect(l,t+1,l+w-1,t+h-1,mainmenu->color,a);
       }
       else
       {
        if (mainmenu->bevelouter==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (mainmenu->bevelouter==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (mainmenu->bevelouter==bvSpace) drawcontroledge(l,t,w,h,6,a);
        if (mainmenu->bevelouter==bvLowered) fillrect(l,t+1,l+w-1,t+h-1,mainmenu->color,a);
        else fillrect(l,t+1,l+w-1,t+h,mainmenu->color,a);
        if (mainmenu->bevelouter!=bvNone)
        {
         l++;
         t++;
         w-=2;
         h-=2;
        }
        if (mainmenu->bevelinner==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (mainmenu->bevelinner==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (mainmenu->bevelinner==bvSpace) drawcontroledge(l,t,w,h,6,a);
        if (mainmenu->bevelinner==bvLowered) fillrect(l,t+1,l+w-1,t+h-1,mainmenu->color,a);
        else fillrect(l,t+1,l+w-1,t+h,mainmenu->color,a);
        
        int cw = 0;
        int ch = 16;
        
        int xx = l+2+1;
        int yy = t+2;
        
        int bvis = 0;
        int hidden = 0;
        
        for (int i=0;i<mainmenu->nummenuitems;i++)
        {
          if (mainmenu->menuitems[i]->visible) bvis = 1;
        }
        for (int i=0;i<mainmenu->nummenuitems;i++)
        {
          if (mouseb==0)
          {
            if (mainmenu->menuitems[i]->menu->menuitemhighlight && mainmenu->menuitems[i]->menu->menuitemctl)
            {
              mainmenu->menuitems[i]->left = xx+cw;
              mainmenu->menuitems[i]->top = yy+ch+4;
              if (getarea(xx+cw,yy,textwidth(mainmenu->menuitems[i]->caption)+6,ch+2)) 
              {
                if (!mainmenu->menuitems[i]->menu->menuitemdown)
                {
                   for (int k=0;k<mainmenu->nummenuitems;k++) mainmenu->menuitems[k]->visible = false;
                   show_menu(mainmenu->menuitems[i]);
                }
                if (mainmenu->menuitems[i]->clicked) 
                {
                  mainmenu->menuitems[i]->menu->menuitemdown = !mainmenu->menuitems[i]->menu->menuitemdown;
                }
              } else 
              {
                mainmenu->menuitems[i]->menu->menuitemdown = false;
              }
            }
            mainmenu->menuitems[i]->clicked = false;
          }
          if (getarea(xx+cw,yy,textwidth(mainmenu->menuitems[i]->caption)+6,ch+2)) mainmenu->menuitems[i]->menu->menuitemhighlight = true;
          else mainmenu->menuitems[i]->menu->menuitemhighlight = false;
          int bctl = 6;
          if (mainmenu->menuitems[i]->menu->menuitemhighlight || mainmenu->menuitems[i]->visible) 
          {
            if ((mouseb==1)||(bvis==1)) 
            {
              mainmenu->menuitems[i]->menu->menuitemctl = true;
              if (mouseb==1) mainmenu->menuitems[i]->clicked = true;
            }
            else mainmenu->menuitems[i]->menu->menuitemctl = false;
            if (mainmenu->menuitems[i]->visible) mainmenu->menuitems[i]->menu->menuitemctl = true;
            bctl = 6+mainmenu->menuitems[i]->menu->menuitemctl;
            if (getarea(xx+cw,yy,textwidth(mainmenu->menuitems[i]->caption)+6,ch+2)||(mainmenu->menuitems[i]->visible)) drawcontroledge(xx+cw,yy,textwidth(mainmenu->menuitems[i]->caption)+6,ch+2,bctl,a);
          }
          else mainmenu->menuitems[i]->menu->menuitemctl = false;
          textattr(clBlack,a,12,FW_NORMAL);
          textout(xx+cw+(textwidth(mainmenu->menuitems[i]->caption)/8)+mainmenu->menuitems[i]->menu->menuitemctl,t+((h-ch)/2)+mainmenu->menuitems[i]->menu->menuitemctl,mainmenu->menuitems[i]->caption);
          cw += textwidth(mainmenu->menuitems[i]->caption)+7;
        }

        
       }
       
       glDisable(GL_SCISSOR_TEST);
    }
}

TMainMenu::TMainMenu(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="mainmenu";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=128;
          parent = window;
          alphavalue = window->alphavalue;
          color = clBtnFace;
          caption="mainmenu";
          borderstyle = bsNone;
          bevelinner = bvNone;
          bevelouter = bvRaised;
          nummenuitems = 0;
          render = rendermainmenu;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->mainmenues[window->nummainmenues] = this;
          window->nummainmenues++;
          window->numcontrols++;
}

TMainMenu::~TMainMenu()
{
  for (int i=0;i<nummenuitems;i++) delete menuitems[i];
  nummenuitems = 0;
}

void TMainMenu::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(mainmenucontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) mainmenucontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->mainmenues[controlid] = this;
}
void TMainMenu::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->mainmenues[controlid] = this;
  }
}
void TMainMenu::hide()
{
          visible = false;
          window->mainmenues[controlid] = this;

}

TMenu* TMainMenu::additem()
{
 menuitems[nummenuitems] = new TMenu();
 menuitems[nummenuitems]->alphavalue = 255;
 menuitems[nummenuitems]->left = 0;
 menuitems[nummenuitems]->top = 0;
 menuitems[nummenuitems]->caption = "";
 menuitems[nummenuitems]->visible = false;
 nummenuitems++;
 return menuitems[nummenuitems-1];
}


TMenu* TMainMenu::additem(char* caption)
{
 TMenu* m = additem();
 m->caption = caption;
 return m;
}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createmainmenu(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int mnmenuid = 0;
   mnmenuid = windows[winid]->nummainmenues;
   TMainMenu* mainmenu = new TMainMenu(windows[winid]);
   mainmenu->alphavalue = 255;
   mainmenu->enabled = true;
   mainmenu->width=72;
   mainmenu->height=24;
   mainmenu->left=32;
   mainmenu->top=32;
   mainmenu->visible = false;
   return mnmenuid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

