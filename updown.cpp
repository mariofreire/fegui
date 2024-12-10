// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "updown.h" // class's header file



bool updownbtnctrlon = false;
bool updownbtn_btndown = false;
int updown_btncnt = 0;
int updownbtncnt = 0;
bool updowncontrolon = false;
bool updownspeedarea = false;
bool updownspeedarea_horiz = false;

void renderupdown(TControl *sender)
{
    TUpDown* updown = dynamic_cast <TUpDown*>((TUpDown*)sender);
    int l0=0,t0=0,w0=0,h0=0;
    int l=0,t=0,w=0,h=0;
    int wcaph = sender->window->height-sender->window->clientheight;
    
    if (sender->visible == false) 
    {
      updown->updownctrlsetvalueonshow = true;
      updownspeedarea = false;
    }
       
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
           if (updowncontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           updowncontrolon = false;
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
       
       
       if (updown->orientation == udVertical)
       {
       
       int bctl = 0;
       int btnborder = 0;
       
       bool incontrol = getarea(l,t,w,h+2);
       if (!updown->window->IsInWindow(updown->window)) incontrol = false;
       
       if (sender->flat && (!incontrol)) bctl = 6;
       
       if (updown->updown_speedarea)
       {
         bctl = 0;
         incontrol = true;
       }
       if (updown->associate)
       {
        for (int edcnt=0;edcnt<updown->window->numedits;edcnt++)
        {
         TEdit* updedit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
         if (updown->window->edits[edcnt] == updedit)
         {
           if (updedit->IsInControl(updedit))
           {
             bctl = 0;
             incontrol = true;
           }
         }
        }
       }
       
       if (bctl == 6) btnborder = 1;
       else btnborder = 0;
       
       int halfborder = h/2;
       
       int upbtnl = l;
       int upbtnt = t;
       int upbtnw = w;
       int upbtnh = halfborder;      
       bool upbtnd = false;
       if ((mouseb==1)&&getarea(upbtnl,upbtnt,upbtnw,upbtnh)) upbtnd = true;

       int dnbtnl = l;
       int dnbtnt = t+halfborder+2;
       int dnbtnw = w;
       int dnbtnh = halfborder;
       if (sender->flat && (!incontrol)) dnbtnt = t+halfborder+1;
       bool dnbtnd = false;
       if ((mouseb==1)&&getarea(dnbtnl,dnbtnt,dnbtnw,dnbtnh)) dnbtnd = true;
       
       if (updownspeedarea)
       {
         upbtnd = false;
         dnbtnd = false;
         updown->upbtn_down = false;
         updown->dnbtn_down = false;
       }
       
       drawcontroledge(upbtnl,upbtnt-(upbtnd+btnborder),upbtnw,upbtnh+(upbtnd*2)+btnborder,bctl+upbtnd,a);
       drawcontroledge(dnbtnl,dnbtnt-dnbtnd,dnbtnw,(dnbtnh+dnbtnd*2)+btnborder,bctl+dnbtnd,a);
       
       /*
       drawline(l-1,t+(h/2),l+w-1,t+(h/2),clBtnShadow,a);
       drawline(l-1,t+(h/2)+1,l+w-1,t+(h/2)+1,clBtnHighlight,a);
       */
       
       int btnimgsz = 4;
       
       if (h < 24) btnimgsz = 4;
       else if ((h >= 24)&&(h < 32)) btnimgsz = 8;
       else if (h >= 32) btnimgsz = 16;
       
       if (mouseb == 1)
       {
         if (getarea(l,t+(h/2),w,1)) updown->updownbtnspeed = true;
       }
       if (mouseb == 0)
       {
         updownspeedarea = false;
         if (getarea(l,t+(h/2),w,1)) updown->updown_speedarea = true;
         else updown->updown_speedarea = false;
         updown->updownbtnspeed = false;
         updown->updownlastpos = updown->position;
       }
       
       if (updown->updownbtnspeed)
       {
         updownspeedarea = true;
         updown->position = updown->updownlastpos-((mousey-(t+(h/2))));
         if (updown->position <= updown->min) updown->position = updown->min;
         if (updown->position >= updown->max) updown->position = updown->max;
         if (updown->associate)
         {
            TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
            edit->text = ltoa(updown->position);
         }         
       }
       
       if (updown->position <= updown->min) updown->position = updown->min;
       if (updown->position >= updown->max) updown->position = updown->max;
       if (updown->associate)
       {
            TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
            if (updown->updownctrlsetvalueonshow) edit->text = ltoa(updown->position);
            updown->position = atol(edit->text.c_str());
       }
       // up/down commands
       if (incontrol)
       {
         if (updownbtnctrlon)
         {
            if (mouseb == 0)
            {
              if (updown_btncnt == 0) updownbtn_btndown = true;
            }
            updownbtnctrlon = false;
         }
         
         if (mouseb == 0) updown_btncnt = 0;
         if ((mouseb == 0))
         {
         if (updown->upbtn_down)
         {
            updownbtncnt = 0;
            if (updown->position < updown->max) updown->position += updown->increment;
            if (updown->position >= updown->max) updown->position = updown->max;
            if (updown->associate)
            {
             TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
             edit->text = ltoa(updown->position);
            }
            updown->upbtn_down = false;
         }
         if (updown->dnbtn_down)
         {
           updownbtncnt = 0;
           if (updown->position > updown->min) updown->position -= updown->increment;
           if (updown->position <= updown->min) updown->position = updown->min;
           if (updown->associate)
           {
            TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
            edit->text = ltoa(updown->position);
           }
           updown->dnbtn_down = false;
         }
         updownbtn_btndown = false;
         }
         
         /*
         else if ((mouseb==1) && !updownbtn_btndown)
         {
         updownbtn_btndown = false;
         if ((mouseb==1) && updown->upbtn_down)
         {
           if (updownbtncnt >= 2) updownbtncnt = 0;
           if ((updownbtncnt == 1))
           {
            if (updown->position < updown->max) updown->position += updown->increment;
            if (updown->position >= updown->max) updown->position = updown->max;
            if (updown->associate)
            {
             TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
             edit->text = ltoa(updown->position);
            }
           }
           updownbtncnt++;
           updown->upbtn_down = false;
         }
         if ((mouseb==1) && updown->dnbtn_down)
         {
           if (updownbtncnt >= 2) updownbtncnt = 0;
           if ((updownbtncnt == 1))
           {
            if (updown->position > updown->min) updown->position -= updown->increment;
            if (updown->position <= updown->min) updown->position = updown->min;
            if (updown->associate)
            {
             TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
             edit->text = ltoa(updown->position);
            }
           }
           updownbtncnt++;
           updown->dnbtn_down = false;
         }
         }
         */
         
         updownbtn_btndown = false;
       }

       switch (btnimgsz)
       {
       case 4:
       {
        drawimage(upbtnl+((upbtnw-btnimgsz)/2)+upbtnd,upbtnt+((upbtnh-btnimgsz)/2)+upbtnd,uparrow4icon,a,true,clLime);
        drawimage(dnbtnl+((dnbtnw-btnimgsz)/2)+dnbtnd,(t+halfborder+2)+((dnbtnh-btnimgsz)/2)+dnbtnd,downarrow4icon,a,true,clLime);
        break;
       }
       case 8:
       {
        drawimage(upbtnl+((upbtnw-btnimgsz)/2)+upbtnd,upbtnt+((upbtnh-btnimgsz)/2)+upbtnd,uparrow8icon,a,true,clLime);
        drawimage(dnbtnl+((dnbtnw-btnimgsz)/2)+dnbtnd,(t+halfborder+2)+((dnbtnh-btnimgsz)/2)+dnbtnd,downarrow8icon,a,true,clLime);
        break;
       }
       case 16:
       {
        drawimage(upbtnl+((upbtnw-(btnimgsz+4))/2)+upbtnd,upbtnt+((upbtnh-(btnimgsz+4))/2)+upbtnd,uparrowicon,a,true,clLime);
        drawimage(dnbtnl+((dnbtnw-(btnimgsz+4))/2)+dnbtnd,(t+halfborder+2)+((dnbtnh-(btnimgsz+4))/2)+dnbtnd,downarrowicon,a,true,clLime);
        break;
       }
       };
       if (incontrol)
       {
         if (upbtnd) 
         {
           updown->upbtn_down = true;
           updownbtnctrlon = true;
         }
         if (dnbtnd) 
         {
           updown->dnbtn_down = true;
           updownbtnctrlon = true;
         }         
         if (mouseb == 1) updown_btncnt++;
         else updown_btncnt = 0;
       }
       
       }
       else
       if (updown->orientation == udHorizontal)
       {
       
       int bctl = 0;
       int btnborder = 0;
       
       bool incontrol = getarea(l,t,w,h+2);
       if (!updown->window->IsInWindow(updown->window)) incontrol = false;
       
       if (sender->flat && (!incontrol)) bctl = 6;
       
       if (updown->updown_speedarea)
       {
         bctl = 0;
         incontrol = true;
       }
       if (updown->associate)
       {
        for (int edcnt=0;edcnt<updown->window->numedits;edcnt++)
        {
         TEdit* updedit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
         if (updown->window->edits[edcnt] == updedit)
         {
           if (updedit->IsInControl(updedit))
           {
             bctl = 0;
             incontrol = true;
           }
         }
        }
       }
       
       if (bctl == 6) btnborder = 1;
       else btnborder = 0;
       
       int halfborder = w/2;
       
       int upbtnl = l;
       int upbtnt = t;
       int upbtnw = halfborder;
       int upbtnh = h;      
       bool upbtnd = false;
       if ((mouseb==1)&&getarea(upbtnl,upbtnt,upbtnw,upbtnh)) upbtnd = true;

       int dnbtnl = l+halfborder+1;
       int dnbtnt = t;
       int dnbtnw = halfborder;
       int dnbtnh = h;
       if (sender->flat && (!incontrol)) dnbtnl = l+halfborder+1;
       bool dnbtnd = false;
       if ((mouseb==1)&&getarea(dnbtnl,dnbtnt,dnbtnw,dnbtnh)) dnbtnd = true;
       
       if (updownspeedarea)
       {
         upbtnd = false;
         dnbtnd = false;
         updown->upbtn_down = false;
         updown->dnbtn_down = false;
       }
       
       drawcontroledge(upbtnl,upbtnt-(upbtnd+btnborder),upbtnw,upbtnh+(upbtnd*2)+btnborder,bctl+upbtnd,a);
       drawcontroledge(dnbtnl,(dnbtnt-dnbtnd)-btnborder,dnbtnw,(dnbtnh+dnbtnd*2)+btnborder,bctl+dnbtnd,a);
       
       int btnimgsz = 4;
       
       if (w < 24) btnimgsz = 4;
       else if ((w >= 24)&&(w < 32)) btnimgsz = 8;
       else if (w >= 32) btnimgsz = 16;
       
       if (mouseb == 1)
       {
         if (getarea(l+(w/2),t,1,h)) updown->updownbtnspeed = true;
       }
       if (mouseb == 0)
       {
         updownspeedarea = false;
         updownspeedarea_horiz = false;
         if (getarea(l+(w/2),t,1,h)) updown->updown_speedarea = true;
         else updown->updown_speedarea = false;
         updown->updownbtnspeed = false;
         updown->updownlastpos = updown->position;
       }
       
       if (updown->updownbtnspeed)
       {
         updownspeedarea = true;
         updownspeedarea_horiz = true;
         updown->position = updown->updownlastpos-((mousey-(t+(h/2))));
         if (updown->position <= updown->min) updown->position = updown->min;
         if (updown->position >= updown->max) updown->position = updown->max;
         if (updown->associate)
         {
            TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
            edit->text = ltoa(updown->position);
         }         
       }
       
       if (updown->position <= updown->min) updown->position = updown->min;
       if (updown->position >= updown->max) updown->position = updown->max;
       if (updown->associate)
       {
            TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
            if (updown->updownctrlsetvalueonshow) edit->text = ltoa(updown->position);
            updown->position = atol(edit->text.c_str());
       }
       // up/down commands
       if (incontrol)
       {
         if (updownbtnctrlon)
         {
            if (mouseb == 0)
            {
              if (updown_btncnt == 0) updownbtn_btndown = true;
            }
            updownbtnctrlon = false;
         }
         
         if (mouseb == 0) updown_btncnt = 0;
         if ((mouseb == 0))
         {
         if (updown->upbtn_down)
         {
            updownbtncnt = 0;
            if (updown->position < updown->max) updown->position += updown->increment;
            if (updown->position >= updown->max) updown->position = updown->max;
            if (updown->associate)
            {
             TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
             edit->text = ltoa(updown->position);
            }
            updown->upbtn_down = false;
         }
         if (updown->dnbtn_down)
         {
           updownbtncnt = 0;
           if (updown->position > updown->min) updown->position -= updown->increment;
           if (updown->position <= updown->min) updown->position = updown->min;
           if (updown->associate)
           {
            TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
            edit->text = ltoa(updown->position);
           }
           updown->dnbtn_down = false;
         }
         updownbtn_btndown = false;
         }
         
         /*
         else if ((mouseb==1) && !updownbtn_btndown)
         {
         updownbtn_btndown = false;
         if ((mouseb==1) && updown->upbtn_down)
         {
           if (updownbtncnt >= 2) updownbtncnt = 0;
           if ((updownbtncnt == 1))
           {
            if (updown->position < updown->max) updown->position += updown->increment;
            if (updown->position >= updown->max) updown->position = updown->max;
            if (updown->associate)
            {
             TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
             edit->text = ltoa(updown->position);
            }
           }
           updownbtncnt++;
           updown->upbtn_down = false;
         }
         if ((mouseb==1) && updown->dnbtn_down)
         {
           if (updownbtncnt >= 2) updownbtncnt = 0;
           if ((updownbtncnt == 1))
           {
            if (updown->position > updown->min) updown->position -= updown->increment;
            if (updown->position <= updown->min) updown->position = updown->min;
            if (updown->associate)
            {
             TEdit* edit = dynamic_cast <TEdit*>((TEdit*)updown->associate);
             edit->text = ltoa(updown->position);
            }
           }
           updownbtncnt++;
           updown->dnbtn_down = false;
         }
         }
         */
         
         updownbtn_btndown = false;
       }

       switch (btnimgsz)
       {
       case 4:
       {
        drawimage(upbtnl+((upbtnw-btnimgsz)/2)+upbtnd,upbtnt+((upbtnh-btnimgsz)/2)+upbtnd,leftarrow4icon,a,true,clLime);
        drawimage(((l+halfborder))+((dnbtnw-btnimgsz)/2)+dnbtnd,upbtnt+((dnbtnh-btnimgsz)/2)+dnbtnd,rightarrow4icon,a,true,clLime);
        break;
       }
       case 8:
       {
        drawimage(upbtnl+((upbtnw-btnimgsz)/2)+upbtnd,upbtnt+((upbtnh-btnimgsz)/2)+upbtnd,leftarrow8icon,a,true,clLime);
        drawimage(((l+halfborder))+((dnbtnw-btnimgsz)/2)+dnbtnd,upbtnt+((dnbtnh-btnimgsz)/2)+dnbtnd,rightarrow8icon,a,true,clLime);
        break;
       }
       case 16:
       {
        drawimage(upbtnl+((upbtnw-(btnimgsz+4))/2)+upbtnd,upbtnt+((upbtnh-(btnimgsz+4))/2)+upbtnd,leftarrowicon,a,true,clLime);
        drawimage(((l+halfborder))+((dnbtnw-(btnimgsz+4))/2)+dnbtnd,upbtnt+((dnbtnh-(btnimgsz+4))/2)+dnbtnd,rightarrowicon,a,true,clLime);
        break;
       }
       };
       if (incontrol)
       {
         if (upbtnd) 
         {
           updown->upbtn_down = true;
           updownbtnctrlon = true;
         }
         if (dnbtnd) 
         {
           updown->dnbtn_down = true;
           updownbtnctrlon = true;
         }         
         if (mouseb == 1) updown_btncnt++;
         else updown_btncnt = 0;
       }
       
       }
              
       updown->updownctrlsetvalueonshow = false;
       glDisable(GL_SCISSOR_TEST);
    }
}

TUpDown::TUpDown(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="updown";
          visible = false;
          left=0;
          top=0;
          width=16;
          height=24;
          parent = window;
          alphavalue = window->alphavalue;
          color = clBtnFace;
          caption="updown";
          upbtn_down = false;
          dnbtn_down = false;
          arrowkeys = true;
          associate = NULL;
          increment = 1;
          min = 0;
          max = 0;
          orientation = udVertical;
          position = 0;
          updownctrlsetvalueonshow = true;
          updownbtnspeed = false;
          updown_speedarea = false;
          updownlastpos = 0;
          thousands = true;
          wrap = false;
          render = renderupdown;
          controlid = window->numcontrols;
          handleid - window->numupdowns;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->updowns[window->numupdowns] = this;
          window->numupdowns++;
          window->numcontrols++;
}

void TUpDown::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(updowncontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) updowncontrolon = false;
}
} else focused = false;
}
}
instance = this;
// window->updowns[handleid] = this;
}
void TUpDown::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->updowns[handleid] = this;
  }
}
void TUpDown::hide()
{
          visible = false;
          window->updowns[handleid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createupdown(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int updnid = 0;
   updnid = windows[winid]->numupdowns;
   TUpDown* updown = new TUpDown(windows[winid]);
   updown->alphavalue = 255;
   updown->enabled = true;
   updown->width=72;
   updown->height=24;
   updown->left=32;
   updown->top=32;
   updown->visible = false;
   return updnid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


