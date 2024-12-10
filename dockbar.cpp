// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "dockbar.h" // class's header file


bool ExistsDockToolBar(TDockBar* dockbar)
{
       for (int i=0;i<dockbar->window->numtoolbars;i++)
       {
             TDockBar* dockctrl = dynamic_cast <TDockBar*>((TDockBar*)dockbar);
             if (dockctrl==dockbar->window->toolbars[i]->parent)
             {
               TToolBar* toolbar = dockbar->window->toolbars[i];
               if (toolbar)
               {
                 int docky = 0;
                 if (dockbar->height >= 32) docky = 4;
                 else docky = 2;
                 int bl = toolbar->window->left;
                 int bt = toolbar->window->top;
                 int lctrl = bl+(toolbar->left-12);
                 int tctrl = bt+(toolbar->top-docky);
                 int wctrl = toolbar->width+12;
                 int hctrl = toolbar->height+(docky*2);
                 
                 int tbl1 = mousex;
                 int tbt1 = mousey;

                 int tbl2 = bl+toolbar->left;
                 int tbt2 = bt+toolbar->top;
                 int tbr2 = bl+toolbar->left+toolbar->width;
                 int tbb2 = bt+toolbar->top+toolbar->height;

                 if ((tbl1 >= tbl2)&&(tbt1 >= tbt2)&&(tbl1 <= tbr2)&&(tbt1 <= tbb2))
                 {
                   return true;
                 }
               }
             }
       }
       return false;
}

bool ExistsDockMainMenu(TDockBar* dockbar)
{
       for (int i=0;i<dockbar->window->nummainmenues;i++)
       {
             TDockBar* dockctrl = dynamic_cast <TDockBar*>((TDockBar*)dockbar);
             if (dockctrl==dockbar->window->mainmenues[i]->parent)
             {
               TMainMenu* mainmenu = dockbar->window->mainmenues[i];
               if (mainmenu)
               {
                 int docky = 0;
                 if (dockbar->height >= 32) docky = 4;
                 else docky = 2;
                 int bl = mainmenu->window->left;
                 int bt = mainmenu->window->top;
                 int lctrl = bl+(mainmenu->left-12);
                 int tctrl = bt+(mainmenu->top-docky);
                 int wctrl = mainmenu->width+12;
                 int hctrl = mainmenu->height+(docky*2);
                 
                 int tbl1 = mousex;
                 int tbt1 = mousey;

                 int tbl2 = bl+mainmenu->left;
                 int tbt2 = bt+mainmenu->top;
                 int tbr2 = bl+mainmenu->left+mainmenu->width;
                 int tbb2 = bt+mainmenu->top+mainmenu->height;

                 if ((tbl1 >= tbl2)&&(tbt1 >= tbt2)&&(tbl1 <= tbr2)&&(tbt1 <= tbb2))
                 {
                   return true;
                 }
               }
             }
       }
       return false;
}

bool IsInDockToolBar(TDockBar* dockbar,TToolBar* tb)
{
       bool isincontrol = false;
       for (int i=0;i<dockbar->window->numtoolbars;i++)
       {
             TDockBar* dockctrl = dynamic_cast <TDockBar*>((TDockBar*)dockbar);
             if (dockctrl==dockbar->window->toolbars[i]->parent)
             {
               TToolBar* toolbar = dockbar->window->toolbars[i];
               if (toolbar)
               {
                 int docky = 0;
                 if (dockbar->height >= 32) docky = 4;
                 else docky = 2;
                 int bl = toolbar->window->left;
                 int bt = toolbar->window->top;
                 int lctrl = bl+(toolbar->left-12);
                 int tctrl = bt+(toolbar->top-docky);
                 int wctrl = toolbar->width+12;
                 int hctrl = toolbar->height+(docky*2);
                 if (((toolbar->left >= tb->left)&&(toolbar->top >= tb->top))&&((toolbar->width <= tb->width)&&(toolbar->height <= tb->height)))
                 {
                   int lctrl = bl+(toolbar->left-12);
                   int tctrl = bt+(toolbar->top-docky);
                   if (getarea(lctrl,tctrl,12,toolbar->height*4))
                   {
                   int lctrl = bl+(toolbar->left-12);
                   int tctrl = bt+(toolbar->top-docky);
                    if (!ExistsDockToolBar(dockbar)) 
                    {
                      int lctrl = bl+(toolbar->left-12);
                      int tctrl = bt+(toolbar->top-docky);
                      if (getarea(lctrl,tctrl,12,toolbar->height*2))
                      {
                        int lctrl = bl+(toolbar->left-12);
                        int tctrl = bt+(toolbar->top-docky);
                        if (getarea(lctrl,tctrl+toolbar->height,12,toolbar->height))
                        {
                          return true;
                        }
                        if (getarea(lctrl,tctrl,12,toolbar->height))
                        {
                          return true;
                        }
                      }
                    }
                   }
                  // else isincontrol = false;
                 }
               //  if (toolbar->IsInControl(toolbar)) isincontrol = true;
               //  if (getarea(lctrl,tctrl,12,toolbar->height*2)) isincontrol = true;
               }
             }
       }
       return isincontrol;
}

bool IsInDockMainMenu(TDockBar* dockbar,TMainMenu* mm)
{
       bool isincontrol = false;
       for (int i=0;i<dockbar->window->nummainmenues;i++)
       {
             TDockBar* dockctrl = dynamic_cast <TDockBar*>((TDockBar*)dockbar);
             if (dockctrl==dockbar->window->mainmenues[i]->parent)
             {
               TMainMenu* mainmenues = dockbar->window->mainmenues[i];
               if (mainmenues)
               {
                 int docky = 0;
                 if (dockbar->height >= 32) docky = 4;
                 else docky = 2;
                 int bl = mainmenues->window->left;
                 int bt = mainmenues->window->top;
                 int lctrl = bl+(mainmenues->left-12);
                 int tctrl = bt+(mainmenues->top-docky);
                 int wctrl = mainmenues->width+12;
                 int hctrl = mainmenues->height+(docky*2);
                 if (((mainmenues->left >= mm->left)&&(mainmenues->top >= mm->top))&&((mainmenues->width <= mm->width)&&(mainmenues->height <= mm->height)))
                 {
                   int lctrl = bl+(mainmenues->left-12);
                   int tctrl = bt+(mainmenues->top-docky);
                   if (getarea(lctrl,tctrl,12,mainmenues->height*4))
                   {
                   int lctrl = bl+(mainmenues->left-12);
                   int tctrl = bt+(mainmenues->top-docky);
                    if (!ExistsDockMainMenu(dockbar)) 
                    {
                      int lctrl = bl+(mainmenues->left-12);
                      int tctrl = bt+(mainmenues->top-docky);
                      if (getarea(lctrl,tctrl,12,mainmenues->height*2))
                      {
                        int lctrl = bl+(mainmenues->left-12);
                        int tctrl = bt+(mainmenues->top-docky);
                        if (getarea(lctrl,tctrl+mainmenues->height,12,mainmenues->height))
                        {
                          return true;
                        }
                        if (getarea(lctrl,tctrl,12,mainmenues->height))
                        {
                          return true;
                        }
                      }
                    }
                   }
                  // else isincontrol = false;
                 }
               //  if (mainmenues->IsInControl(mainmenues)) isincontrol = true;
               //  if (getarea(lctrl,tctrl,12,mainmenues->height*2)) isincontrol = true;
               }
             }
       }
       return isincontrol;
}

void AdjustDockToolBar(TDockBar* dockbar,TToolBar* tb)
{
       for (int i=0;i<dockbar->window->numtoolbars;i++)
       {
             TDockBar* dockctrl = dynamic_cast <TDockBar*>((TDockBar*)dockbar);
             if (dockctrl==dockbar->window->toolbars[i]->parent)
             {
               TToolBar* toolbar = dockbar->window->toolbars[i];
               if (toolbar)
               {
                 int docky = 0;
                 if (dockbar->height >= 32) docky = 4;
                 else docky = 2;
                 int bl = toolbar->window->left;
                 int bt = toolbar->window->top;
                 int lctrl = bl+(toolbar->left-12)+2;
                 int tctrl = bt+(toolbar->top-docky);
                 int wctrl = toolbar->width+12+2;
                 int hctrl = toolbar->height+(docky*2);
                 if (((tb->left >= toolbar->left)&&(tb->width <= toolbar->width))
                 && ((tb->top >= toolbar->top)&&(tb->height <= toolbar->height)))
                 {
               //    tb->left = toolbar->left+toolbar->width+12;
                 //  tb->top = toolbar->top+toolbar->height+(docky*2);
                //   if (tb->left >= tb->parent->left+tb->parent->width) tb->left = (tb->parent->left+tb->parent->width)-tb->width;
                //   if (tb->top >= tb->parent->top+tb->parent->height+(docky*2)) (tb->top = (tb->parent->top+tb->parent->height)-tb->height)+(docky*2);
                 }
                 
                 int tbl1 = tb->left;
                 int tbt1 = tb->top;
                 int tbr1 = tb->left+tb->width+12;
                 int tbb1 = tb->top+tb->height;

                 int tbl2 = toolbar->left+12;
                 int tbt2 = toolbar->top;
                 int tbr2 = toolbar->left+toolbar->width+12;
                 int tbb2 = toolbar->top+toolbar->height;

                 if ((tbl1 >= tbl2)&&(tbl1 <= tbr2))
                 {
              //     tb->left = toolbar->left+toolbar->width+12;
                 }

                 if ((tbl1 >= tbl2)&&(tbt1 >= tbt2)&&(tbl1 <= tbr2)&&(tbt1 <= tbb2))
                 {
                  tb->left = toolbar->left+toolbar->width+12+1;
                //  AdjustDockToolBar(dockbar,tb);
              //     tb->left = toolbar->left+toolbar->width;
                 }
                 
                 /*
                 if ((tb->left >= toolbar->left)&&(tb->width <= toolbar->width))
                 {
                   tb->left = toolbar->left+toolbar->width+12;
                 }
                 if ((tb->top >= toolbar->top)&&(tb->height <= toolbar->height))
                 {
                   tb->top = toolbar->top+toolbar->height+(docky*2);
                 }
*/

               //  if (toolbar->IsInControl(toolbar)) isincontrol = true;
               //  if (getarea(lctrl,tctrl,12,toolbar->height*2)) isincontrol = true;
               }
             }
       }
}


void AdjustDockMainMenu(TDockBar* dockbar,TMainMenu* mm)
{
       for (int i=0;i<dockbar->window->nummainmenues;i++)
       {
             TDockBar* dockctrl = dynamic_cast <TDockBar*>((TDockBar*)dockbar);
             if (dockctrl==dockbar->window->mainmenues[i]->parent)
             {
               TMainMenu* mainmenu = dockbar->window->mainmenues[i];
               if (mainmenu)
               {
                 int docky = 0;
                 if (dockbar->height >= 32) docky = 4;
                 else docky = 2;
                 int bl = mainmenu->window->left;
                 int bt = mainmenu->window->top;
                 int lctrl = bl+(mainmenu->left-12)+2;
                 int tctrl = bt+(mainmenu->top-docky);
                 int wctrl = mainmenu->width+12+2;
                 int hctrl = mainmenu->height+(docky*2);
                 if (((mm->left >= mainmenu->left)&&(mm->width <= mainmenu->width))
                 && ((mm->top >= mainmenu->top)&&(mm->height <= mainmenu->height)))
                 {
               //    mm->left = mainmenu->left+mainmenu->width+12;
                 //  mm->top = mainmenu->top+mainmenu->height+(docky*2);
                //   if (mm->left >= mm->parent->left+mm->parent->width) mm->left = (mm->parent->left+mm->parent->width)-mm->width;
                //   if (mm->top >= mm->parent->top+mm->parent->height+(docky*2)) (mm->top = (mm->parent->top+mm->parent->height)-mm->height)+(docky*2);
                 }
                 
                 int mml1 = mm->left;
                 int mmt1 = mm->top;
                 int mmr1 = mm->left+mm->width+12;
                 int mmb1 = mm->top+mm->height;

                 int mml2 = mainmenu->left+12;
                 int mmt2 = mainmenu->top;
                 int mmr2 = mainmenu->left+mainmenu->width+12;
                 int mmb2 = mainmenu->top+mainmenu->height;

                 if ((mml1 >= mml2)&&(mml1 <= mmr2))
                 {
              //     mm->left = mainmenu->left+mainmenu->width+12;
                 }

                 if ((mml1 >= mml2)&&(mmt1 >= mmt2)&&(mml1 <= mmr2)&&(mmt1 <= mmb2))
                 {
                  mm->left = mainmenu->left+mainmenu->width+12+1;
                //  AdjustDockMainMenu(dockbar,mm);
              //     mm->left = mainmenu->left+mainmenu->width;
                 }
                 
                 /*
                 if ((mm->left >= mainmenu->left)&&(mm->width <= mainmenu->width))
                 {
                   mm->left = mainmenu->left+mainmenu->width+12;
                 }
                 if ((mm->top >= mainmenu->top)&&(mm->height <= mainmenu->height))
                 {
                   mm->top = mainmenu->top+mainmenu->height+(docky*2);
                 }
*/

               //  if (mainmenu->IsInControl(mainmenu)) isincontrol = true;
               //  if (getarea(lctrl,tctrl,12,mainmenu->height*2)) isincontrol = true;
               }
             }
       }
}


bool dockbarcontrolon = false;
void renderdockbar(TControl *sender)
{
    TDockBar* dockbar = dynamic_cast <TDockBar*>((TDockBar*)sender);
    TToolBar* toolbar;
    TToolBar* oldtoolbar;
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    bool isinwin = false;
    int wcaph = sender->window->height-sender->window->clientheight;
    if (windows[activewindow]!=sender->window)
    {
      if (sender->window->IsInWindow(windows[activewindow]))
      {
        isinwin = false;
      } else isinwin = true;
    } else isinwin = true;
       
       if (sender->visible)
       {
/*
         for (int i=0;i<dockbar->window->numtoolbars;i++)
         {
             TDockBar* dockctrl = dynamic_cast <TDockBar*>((TDockBar*)dockbar);
             if (dockctrl==dockbar->window->toolbars[i]->parent)
             {
               toolbar = dockbar->window->toolbars[i];
             }
         }
*/       
       l0 = sender->window->left+sender->left;
       t0 = sender->window->top+wcaph+sender->top;
       w0 = sender->width;
       h0 = sender->height;
       l = l0;
       t = t0;
       w = w0;
       h = h0;
       
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
           if (dockbarcontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           dockbarcontrolon = false;
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
       
       if (dockbar->borderstyle==bsSingle)
       {
        drawcontroledge(l,t,w,h,14,a);
        fillrect(l,t+1,l+w-1,t+h-1,dockbar->color,a);
        l+=2;
        t+=2;
        w-=5;
        h-=3;
        if (dockbar->bevelouter==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (dockbar->bevelouter==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (dockbar->bevelouter==bvSpace) drawcontroledge(l,t,w,h,6,a);
        fillrect(l,t+1,l+w-1,t+h-1,dockbar->color,a);
        if (dockbar->bevelouter!=bvNone)
        {
         l++;
         t++;
         w-=2;
         h-=2;
        } 
        if (dockbar->bevelinner==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (dockbar->bevelinner==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (dockbar->bevelinner==bvSpace) drawcontroledge(l,t,w,h,6,a);
        fillrect(l,t+1,l+w-1,t+h-1,dockbar->color,a);
       }
       else
       {
        if (dockbar->bevelouter==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (dockbar->bevelouter==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (dockbar->bevelouter==bvSpace) drawcontroledge(l,t,w,h,6,a);
        if (dockbar->bevelouter==bvLowered) fillrect(l,t+1,l+w-1,t+h-1,dockbar->color,a);
        else fillrect(l,t+1,l+w-1,t+h,dockbar->color,a);
        if (dockbar->bevelouter!=bvNone)
        {
         l++;
         t++;
         w-=2;
         h-=2;
        }
        if (dockbar->bevelinner==bvLowered) drawcontroledge(l,t,w,h,7,a);
        else if (dockbar->bevelinner==bvRaised) drawcontroledge(l,t,w,h,6,a);
        else if (dockbar->bevelinner==bvSpace) drawcontroledge(l,t,w,h,6,a);
        if (dockbar->bevelinner==bvLowered) fillrect(l,t+1,l+w-1,t+h-1,dockbar->color,a);
        else fillrect(l,t+1,l+w-1,t+h,dockbar->color,a);
       }
       for (int i=0;i<dockbar->window->numtoolbars;i++)
       {
             TDockBar* dockctrl = dynamic_cast <TDockBar*>((TDockBar*)dockbar);
             if (dockctrl==dockbar->window->toolbars[i]->parent)
             {
               toolbar = dockbar->window->toolbars[i];
               if (toolbar)
               { 
                 int docky = 0;
                 if (dockbar->height >= 32) docky = 4;
                 else docky = 2;
                 if (!dockbar->applydocks)
                 {
                   toolbar->left = dockbar->left+12;
                   toolbar->top = dockbar->top+docky;
                   AdjustDockToolBar(dockbar,toolbar);
                   dockbar->applydocks = true;
                 }
                 int lctrl = bl+(toolbar->left-12);
                 int tctrl = bt+(toolbar->top-docky);
                 int wctrl = toolbar->width+12;
                 int hctrl = toolbar->height+(docky*2);
                 if ((mouseb == 1)&&(isinwin))
                 {
                  if (getarea(lctrl,tctrl+1,12,hctrl-1))
                  {
                   toolbar->dockmove = true;
                  } //else toolbar->dockmove = false;

                  if (getarea(lctrl,t+1,12,(dockbar->window->top+dockbar->window->height)-1))
                  {
                     for (int my=0; my < (dockbar->window->top+dockbar->window->height); my+=(toolbar->height+((docky*2)+1)))
                     {
                         lctrl = bl+(toolbar->left-12);
                         tctrl = bt+(toolbar->top-docky);
                         wctrl = toolbar->width+12;
                         hctrl = toolbar->height+(docky*2);
                         AdjustDockToolBar(dockbar,toolbar);
                       //  int my = mousey&8;///((toolbar->height+((docky*2)+1)));
//                         if ((((mousex>=lctrl)&&(mousey>=tctrl)&&(mousex<=lctrl+12)&&(mousey<=tctrl+toolbar->height))))
                         if (getarea(lctrl,bt+my+(toolbar->height),12,toolbar->height))
                         { 
                         if (getarea(lctrl,tctrl-toolbar->height,12,toolbar->height*2)) 
                          if (!ExistsDockToolBar(dockbar)) 
                          {
                          if (IsInDockToolBar(dockbar,toolbar))
                           {
                             toolbar->top = (dockbar->top+docky)+my;
                             if (toolbar->top < dockbar->top+docky) toolbar->top = dockbar->top+docky;
                             else AdjustDockToolBar(dockbar,toolbar);
                          //   if (ExistsDockToolBar(dockbar)) AdjustDockToolBar(dockbar,toolbar);//toolbar->dockmove = false;
                           //  if (IsInDockToolBar(dockbar,toolbar)) AdjustDockToolBar(dockbar,toolbar);
                             if (oldtoolbar)
                             {
                               if ((toolbar->left == oldtoolbar->left)&&(toolbar->top == oldtoolbar->top)) toolbar->top += toolbar->height+((docky*3)-1);
                             }
/*
                             char s[256];
                             strcpy(s,ltoa(dockbar->window->toolbars[0]->top));
                             strcat(s,", ");
                             strcat(s,ltoa(dockbar->window->toolbars[1]->top));
                             SetWindowText(hWnd,s);
*/
                           }
                          }
                         }
                     }
                  }
                  if (toolbar->dockmove)
                  {
                   int pushright = 0;
                   if ((mousex-oldmousex)>0) pushright = 1;
                   if (pushright)
                   {
                     if ((lctrl+wctrl)<(l+w)) 
                     {
                       if (toolbar->left >= (((dockbar->left+dockbar->width)-toolbar->width)))
                       {
                            toolbar->left = (((dockbar->left+dockbar->width)-toolbar->width));
                          //  if (ExistsDockToolBar(dockbar)) 
                            //AdjustDockToolBar(dockbar,toolbar);
                            lctrl = bl+(toolbar->left-12);
                            wctrl = toolbar->width+12;
                            toolbtncontrolon = false;
                            toolbarcontrolon = false;
                            toolbar->focus = false;
                            toolbar->focused = false;
                          //  if (!ExistsDockToolBar(dockbar)) mousex = (bl+toolbar->left)-6;
                       }
                       else 
                       {
                            if (!ExistsDockToolBar(dockbar)) toolbar->left = mousex-(bl-6);
                           // if (ExistsDockToolBar(dockbar)) 
                        //    if (ExistsDockToolBar(dockbar)) 
                            AdjustDockToolBar(dockbar,toolbar);
                            lctrl = bl+(toolbar->left-12);
                            wctrl = toolbar->width+12;
                         //   if (!ExistsDockToolBar(dockbar)) mousex = (bl+toolbar->left)-6;
                       }
                       if (toolbar->left >= (((dockbar->left+dockbar->width)-toolbar->width))) 
                       {
                            if (ExistsDockToolBar(dockbar)) AdjustDockToolBar(dockbar,toolbar);
                            toolbar->left = (((dockbar->left+dockbar->width)-toolbar->width));
                            //if (ExistsDockToolBar(dockbar)) 
                            lctrl = bl+(toolbar->left-12);
                            wctrl = toolbar->width+12;
                            toolbtncontrolon = false;
                            toolbarcontrolon = false;
                            toolbar->focus = false;
                            toolbar->focused = false;
                    //        if (!ExistsDockToolBar(dockbar)) mousex = (bl+toolbar->left)-6;
                       }
                     }
                     else 
                     {
                         // if (ExistsDockToolBar(dockbar))
                           AdjustDockToolBar(dockbar,toolbar);
                          toolbar->left = (((dockbar->left+dockbar->width)-toolbar->width));
                    //      if (ExistsDockToolBar(dockbar)) 
                          lctrl = bl+(toolbar->left-12);
                          wctrl = toolbar->width+12;
                   //       if (!ExistsDockToolBar(dockbar)) mousex = bl+toolbar->left-6;
                     }
                     
                   } else 
                   {
                     if ((lctrl)>=(bl+dockbar->left))
                     {
                       if (!ExistsDockToolBar(dockbar)) toolbar->left = mousex-(bl-6);
                    //   if (ExistsDockToolBar(dockbar)) 
                       //if (ExistsDockToolBar(dockbar)) 
                       AdjustDockToolBar(dockbar,toolbar);
                       if (toolbar->left <= dockbar->left+12) toolbar->left = dockbar->left+12;
                       if (toolbar->left >= (((dockbar->left+dockbar->width)-toolbar->width))) toolbar->left = (((dockbar->left+dockbar->width)-toolbar->width));
                       lctrl = bl+(toolbar->left-12);
                       wctrl = toolbar->width+12;
                     }
                     else
                     {
                         // if (ExistsDockToolBar(dockbar)) AdjustDockToolBar(dockbar,toolbar);
                          toolbar->left = dockbar->left+12;
                     }
                //     if (ExistsDockToolBar(dockbar))
//                      AdjustDockToolBar(dockbar,toolbar);
                     if (toolbar->left >= (((dockbar->left+dockbar->width)-toolbar->width))) toolbar->left = (((dockbar->left+dockbar->width)-toolbar->width));
                     lctrl = bl+(toolbar->left-12);
                     wctrl = toolbar->width+12;
                   }
                  }
                 } else toolbar->dockmove = false;
               //  if (ExistsDockToolBar(dockbar)) AdjustDockToolBar(dockbar,toolbar);
                 if (toolbar->left <= dockbar->left+12)
                 {
                   toolbar->left = dockbar->left+12;
                   if (toolbar->dockmove) 
                   {
                 //    if (!ExistsDockToolBar(dockbar)) mousex = (bl+toolbar->left)-6;
                   }
                 }
                 if (toolbar->left >= (((dockbar->left+dockbar->width)-toolbar->width))) toolbar->left = (((dockbar->left+dockbar->width)-toolbar->width));
                 lctrl = bl+(toolbar->left-12);
                 wctrl = toolbar->width+12;
                 drawcontroledge(lctrl,tctrl,wctrl,hctrl,6,a);
                 drawcontroledge(lctrl+4,tctrl+4,2,hctrl-8,6,a);
                 drawcontroledge(lctrl+7,tctrl+4,2,hctrl-8,6,a);
                 oldtoolbar = dockbar->window->toolbars[i];
               }
             }
       }
       glDisable(GL_SCISSOR_TEST);
    }
}

TDockBar::TDockBar(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="dockbar";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=128;
          parent = window;
          alphavalue = window->alphavalue;
          color = clBtnFace;
          applydocks = false;
          caption="dockbar";
          borderstyle = bsNone;
          bevelinner = bvNone;
          bevelouter = bvRaised;
          render = renderdockbar;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->dockbars[window->numdockbars] = this;
          window->numdockbars++;
          window->numcontrols++;
}

TDockBar::~TDockBar()
{
}

void TDockBar::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(dockbarcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) dockbarcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->dockbars[controlid] = this;
}
void TDockBar::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->dockbars[controlid] = this;
  }
}
void TDockBar::hide()
{
          visible = false;
          window->dockbars[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createdockbar(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int dbarid = 0;
   dbarid = windows[winid]->numdockbars;
   TDockBar* dockbar = new TDockBar(windows[winid]);
   dockbar->alphavalue = 255;
   dockbar->enabled = true;
   dockbar->width=72;
   dockbar->height=24;
   dockbar->left=32;
   dockbar->top=32;
   dockbar->visible = false;
   return dbarid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

