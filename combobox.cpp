// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "combobox.h" // class's header file

int comboboxeditxl=0;
int comboblinkcnt=0;
bool comboboxeditcontrolon = false;
bool comboboxeditfocused = false;
void rendercomboboxedit(TControl *sender)
{
     int l=0;
     int t=0;
     int w=0;
     int h=0;
     TComboBoxEdit* e = dynamic_cast <TComboBoxEdit*>((TComboBoxEdit*)sender);
     int len = strlen(e->text.c_str());
     int ebctl = 1;
     int wcaph = (sender->window->height-sender->window->clientheight);
     if ((sender->window->borderstyle != bsNone)&&(windowmanager == 1)) wcaph -= 3;
 
 bool isinwin = false;
 if (windows[activewindow]!=sender->window)
 {
  if (sender->window->IsInWindow(windows[activewindow]))
  {
    isinwin = false;
  } else isinwin = true;
 } else isinwin = true;
 
 int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);

if (sender->visible == true)
{
     l = sender->window->left+sender->left;
     t = sender->window->top+wcaph+sender->top+2;
     w = sender->width;
     h = sender->height;
     
     if (sender->flat) ebctl = 7;
     else ebctl = 1;
     
     if (sender->IsInControl(sender)) ebctl = 1;
     
     if (sender->flat)
     {
        if (!isinwin) ebctl = 7;
     }
     
     // drawcontroledge(l,t,w,h,ebctl,alphacontrol);
     // fillrect(l+1,t+1,l+w-2,t+h-2,clWhite,alphacontrol);
     textattr(clBlack,alphacontrol,12,FW_NORMAL);
     std::string s = "";
     
     if ((!sender->focus) && (sender->window->activecontrol != e->controlid) &&
     (sender->tabstop) && (sender->taborder == 0))
     {
       e->sel_start = 0;
       e->sel_index = e->sel_start;
       e->sel_length = e->text.length();
     }
     

     int k=0,j=1,l1=0;
     int b=0;
     float tw=0;
     int ll=0;
     int charwidth = textwidth("A");
     int halfcharwidth = charwidth/2;
     tw = textwidth((char*)s.c_str());

     k=0;
     s = e->text;
     while ((textwidth((char*)s.c_str()) >= w-(charwidth-2)) && (e->window->width))
     {
       if ((textwidth((char*)s.c_str()) >= w-(charwidth-2)))
       {
         s = s.substr(1,len);
         b++;
       }
       k++;
     }

     std::string seltextstr = e->text;
     seltextstr = seltextstr.substr(b,e->sel_start-b);
     
     int ssw=0;

     ssw = 0;
     ssw = textwidth((char*)seltextstr.c_str());

     tw = ssw;
     
     if (tw >= w-charwidth) tw = w-charwidth;
     if (tw <= 0) tw = 0;
     
     if (sender->focus)
     {
       if (mouseb==1)
       {
         char st[1024];
         strcpy(st,s.c_str());
         int ax = mousex-l;
         if (getarea(l,t,w,h))
         {
           int xx=0;
           int sti=0;
           while (sti <= s.size())
           {
             char stc[2];
             sprintf(stc,"%c",st[sti]);
             if ((mousex > ((l+4)+xx-8))&&(mousex < (l+xx+8)))
             {
               if (mousec == 0)
               {
                 if (sti >= e->sel_start)
                 {
                  // if (!comboboxeditxl) 
                   e->sel_length = sti-e->sel_start;
                  //else 
                   //if (sti >= e->sel_index) comboboxeditxl = 0;
                 }
                 else 
                 {
                   //if (sti < e->sel_index-1) comboboxeditxl=1;   
                   //if (comboboxeditxl)
                   //{
                    // e->sel_start = (e->sel_index);//sti+1;
                    // e->sel_length = abs(sti-e->sel_index)-1;//e->sel_index-e->sel_start;
                    // e->sel_start = (e->sel_index-e->sel_length);//sti+1;
                   //}
                 }
               }
               else
               {
                 e->sel_start = sti;
                 e->sel_index = e->sel_start;
                 e->sel_length = 0;
               }
             }
             xx += textwidth(stc);
             sti++;
           }  
           if ((mousex > l+xx)&&(mousex < l+w))
           {
             if (comboboxeditfocused)
             {
               e->sel_start = e->text.length();
               e->sel_index = e->sel_start;
             }
           }
         }
       }
     }
     if (mousec==0)
     {
       if (e->focus)
       {
         comboboxeditfocused = true;
       } //else comboboxeditfocused = false;
     }// else comboboxeditfocused = true;
     else
     {
       if (!e->IsInControl(e)){}// comboboxeditfocused = false;
       else comboboxeditfocused = true;
     }
     
     textout(l+4,t+3,(char*)s.c_str());
     
  if ((sender->focus) || ((sender->tabstop) && (sender->taborder == 0)))
  {
     if (comboblinkcnt > 128) comboblinkcnt = 0;

     std::string sellengthtext = e->text;
     std::string sellength_text = e->text;
     int slen = sellengthtext.length();
     int b1=0;
     int k1=0;
     while ((textwidth((char*)sellength_text.c_str()) >= w-(charwidth-2)) && (e->window->width))
     {
       if ((textwidth((char*)sellength_text.c_str()) >= w-(charwidth-2)))
       {
         sellength_text = sellength_text.substr(1,slen);
         b1++;
       }
       k1++;
     }
     sellengthtext = sellengthtext.substr(e->sel_start,e->sel_length);//(slen-(e->sel_start-e->sel_length)));
     
     int tlw = textwidth((char*)sellengthtext.c_str());
     int slw = ssw;
     if (tlw >= w-charwidth) tlw = w-charwidth;
     if (tlw <= 0) tlw = 0;
     if (slw >= w-charwidth) slw = w-charwidth;
     if (slw <= 0) slw = 0;
     //char buf[256];
     //sprintf(buf,"%i, %i, %i",e->sel_start,e->sel_length,e->sel_index);
     //textout(l+4+1,t-43,buf);
     if (e->sel_length>0)
     {
       int c=clBlack;
       int sll=0;
       int sllw = 0;
       int sllt = 0;
       int slltw = 0;
       
      // if (e->sel_start == e->sel_length) sll = ((l+4)+tlw);
      // else 
       sll = ((l+4)+slw);
       sllw = ((l+4)+slw+tlw);
       
//       fillrect(((l+4)+slw),t+3,((l+4)+slw+tlw),t+h-6,clHighlight,alphacontrol);
       if ((e->sel_index-e->sel_start)>0)
       {
         if (e->sel_start==0) sllt = 0;
         else sllt = 1;
         slltw = 0;
       } else
       {
          sllt = 0;
          slltw = 1;
       }
       
       if (tlw >= w-charwidth) tlw = w-charwidth;
       if (tlw <= 0) tlw = 0;
       if (slw >= w-charwidth) slw = w-charwidth;
       if (slw <= 0) slw = 0;
       if (sllw >= (l+(w+charwidth)))
       {
                 sll = l+4;
                 sllw = (l+w-5);
       }
       if (sllw <= 0) sllw = 0;

       if (e->sel_start != slen) fillrect(sll-sllt,t+3,sllw-slltw,t+h,clHighlight,alphacontrol);
  //     textout(l+4+1,t-23,(char*)sellengthtext.c_str());
       if (e->sel_length > 0)
       {
          c = clHighlightText;
       }

       //if (e->sel_length >= e->text.length())
     //  if (tlw>slw)  tw = slw+tlw+1;
     //  if (slw<tlw-slw)  tw = slw+tlw+1;
       if ((e->sel_index-e->sel_start)>0)
       {
         //  if (tlw>slw)  tw = slw+tlw+1;
         if (e->sel_start==0)  tw += 2;
       }
       else tw = slw+tlw+1;
       tw -= slltw;
     
       if (tw >= w-charwidth) tw = w-charwidth;
       if (tw <= 0) tlw = 0;
       if (tlw >= w-charwidth) tlw = w-charwidth;
       if (tlw <= 0) tlw = 0;
//       if (slw >= w-charwidth) slw = w-charwidth;
       if (slw >= ((w-charwidth)))
       {
                 slw = (0);
                 int sl = sellengthtext.length();
                 std::string sellengthtext1 = sellengthtext;
                 if (e->sel_start <= (w/charwidth))
                 {
                   b1--;
                 }
                 sellengthtext1 = sellengthtext1.substr(0,slen-b1);                   
                 if (textwidth((char*)sellengthtext1.c_str()) > (w-charwidth))
                 {
                 b1++;
                 sellengthtext1 = sellengthtext1.substr(0,slen-b1);                   
                 }
                 sellengthtext = sellengthtext1;
                 //sellengthtext1 = sellengthtext1.substr(0,slen);
                 //textout(((l+4)),t-23,(char*)sellengthtext1.c_str());
       }
       if (slw <= 0) slw = 0;
       if (sllw >= (l+(w+charwidth)))
       {
                 sll = l+4;
                 sllw = (l+w-5);
//                 sellengthtext = sellengthtext1;
//       sellengthtext = sellengthtext.substr(0,(sellengthtext.length())-1);
       }
       if (sllw <= 0) sllw = 0;

       e->seltext = sellengthtext;
       
       textattr(c,alphacontrol,12,FW_NORMAL);
       textout(((l+4)+slw),t+3,(char*)sellengthtext.c_str());
     } else e->seltext = "";
     
     if (comboblinkcnt & 32)
     {
       int lw = (tw);
       int c = clBlack;

       if (e->sel_length > 0)
       {
          c = clBlack;//clYellow;//clHighlightText;
          lw-=2;
       }
       else 
       {
           if (e->sel_start > 0)
           {
            lw-=4;
            l+=2;
           } else lw--;
       }
       
       textattr(c,alphacontrol,12,FW_NORMAL);
       textout((l+4)+(lw),t,"|");          
       textout((l+4)+(lw),t+1,"|");          
       textout((l+4)+(lw),t+2,"|");          
       textout((l+4)+(lw),t+3,"|");          
       textout((l+4)+(lw),t+4,"|");          
     }
     comboblinkcnt++;
  }
}
}

void TComboBoxEdit::comboboxeditinput()
{
  if (charcase == ecUpperCase) text = strupr((char*)text.c_str());
  if (charcase == ecLowerCase) text = strlwr((char*)text.c_str());
  if (focus)
  {  
    if (!readonly)
    {
     if (maxlength > 0)
     {
       if (text.length() >= maxlength) return;
     }
     for (int i=0;i<256;i++)
     {
         if (kbscan[i] > 0)
         {
           std::string s = text;
           char c[2];
           int k=0;
           if (keyshift) k = i;
           else
           {
             if ((i >=65) && (i <= 90)) k = tolower(i);
             else k = i;
           }
           if (charcase == ecUpperCase)
           {
             k = toupper(i);
             if ((i >= 224)&&(i <= 246)) k = k-32;
             if ((i >= 248)&&(i <= 254)) k = k-32;
           }
           if (charcase == ecLowerCase) 
           {
             k = tolower(i);
             if ((i >= 192)&&(i <= 214)) k = k+32;
             if ((i >= 216)&&(i <= 222)) k = k+32;
           }
           sprintf(c,"%c",k);
           
           if (i == VK_HOME)
           {
             if (keyshift)
             {
               sel_length = sel_start;
               sel_start = 0;
             }
             else
             {
               sel_start = 0;
               sel_length = 0;
               sel_index = sel_start;
             }
           }
           else
           if (i == VK_END)
           {
             if (keyshift)
             {
               sel_length = text.size();
             }
             else
             {
               sel_start = text.size();
               sel_length = 0;
               sel_index = sel_start;
             }
           }
           else
           if (i == VK_LEFT)
           {
             if (sel_start >= 0)
             {
               if (keyshift)
               {
                if (sel_start > 0)
                {
                 if ((sel_start >= (sel_index-sel_length)+1)&&(sel_length>0))
                 {
                   if (sel_start < (text.size())) 
                   {
                    if (sel_length > 0) sel_length--;
                   }
                   if (sel_length < 0) sel_length -= sel_length;
                 } else 
                 {
                   if (sel_length < (text.size())) sel_length++;
                   if (sel_start > 0) sel_start--;
                 }
                }
                else if (sel_index==0)
                {
                 if (sel_length > 0) sel_length--;
                }
               }
               else
               {
                 if (sel_length > 0) sel_start = sel_index+sel_length;
                 if (sel_start > 0) sel_start--;
                 sel_length = 0;
                 sel_index = sel_start;
               }
             }
           }
           else
           if (i == VK_RIGHT)
           {
             if (sel_start < text.length())
             {
               if (keyshift)
               {
                if (sel_length<text.size())
                {
                  if ((sel_index-sel_start) > 0)
                  {
                    if (sel_start<text.size()) sel_start++;
                    if (sel_length>0) sel_length--;
                  }
                  else 
                  {
                    if (sel_length < text.size()-sel_start) sel_length++;
                  }
                }
                else
                {
                  if ((sel_start<text.size())&&(sel_index>0)) sel_start++;
                }
               }
               else
               {
                 if (sel_length > 0) sel_start = sel_index+sel_length;
                 sel_start++;
                 sel_length = 0;
                 sel_index = sel_start;
               }
             }
           }
           else
           if(i == 8) //backspace
	       {
            if (sel_start > 0)
            {
	         if (s.size() > 0) 
             {
               std::string sbuf = s;
               s = sbuf.substr(0,sel_start-1) + sbuf.substr(sel_start, sbuf.size()-1);
               sel_start--;
             }
            }
           } else
           if(i == 190) //delete
	       {
	        if ((sel_start < s.size()) && (s.size() > 0))
            {
              std::string sbuf = s;
              s = sbuf.substr(0,sel_start) + sbuf.substr(sel_start+1, sbuf.size());
            }
           } else
           if (i == 16)
           {
           }
           else
            // if(i >= 32)
           {
             std::string sbuf = s;
             s = sbuf.substr(0,sel_start) + c + sbuf.substr(sel_start,sbuf.length());
             if (i != VK_SHIFT)
             {
              sel_start++;
              sel_length = 0;
              sel_index = sel_start;
             }
           }
           if (seltext.size()>0)
           {
             if ((i != VK_SHIFT)&&(i != VK_LEFT)&&(i != VK_RIGHT)&&(i != VK_HOME)&&(i != VK_END))
             {
                     std::string s1 = c;
                     int x = sel_start-1;
                     int y = sel_length;
                     if (x < 0)
                     {
                      x = 0;
                      y = 1;
                     }
                     x = text.find(seltext.c_str(),x,y);
                     text.replace(x,seltext.size(),s1);
             }
           }
           else text = s;
           kbscan[i] = 0;
         }
         if (sel_start < 0) sel_start = 0;
         if (sel_start > text.size()) sel_start = text.size();
     }
    }
  }
  if (charcase == ecUpperCase) text = strupr((char*)text.c_str());
  if (charcase == ecLowerCase) text = strlwr((char*)text.c_str());
}

TComboBoxEdit::TComboBoxEdit(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="comboboxedit";
          visible = false;
          left=0;
          top=0;
          width=128;
          height=32;
          alphavalue = window->alphavalue;
          color = clWindow;
          caption="comboboxedit";
          text="comboboxedit";
          render = rendercomboboxedit;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
}

void TComboBoxEdit::rendercontrol()
{
if ((visible==true)&&(window->visible==true))
{
if (visible)
{
  if (activewindow!=window->windowid) focus = false;
  comboboxeditinput();
  render(this);
  hintcontrol(this);
}

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

if (mouseb==1)
{
  if (IsInControl(this)==true)
  {
    focus = true;  
    
  } else focus = false;
}
if ((focused==true)&&(clicked==true)&&(comboboxeditcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  comboboxeditcontrolon = false;
}
} else focused = false;
}
}
instance = this;
}
void TComboBoxEdit::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
  }
}
void TComboBoxEdit::hide()
{
          visible = false;
}

bool combolistboxvisible = false;

bool comboboxctrlon = false;
bool combolistboxcontrolon = false;
bool showcomboscrolllistbox = false;
void rendercombolistbox(TControl *sender)
{
TComboListBox* combolistbox = dynamic_cast <TComboListBox*>((TComboListBox*)sender);
 bool onctrl = combolistbox->IsInComboBox(sender);
 int bctl = 1;
 int wcaph = sender->window->height-sender->window->clientheight;
 bool isinwin = false;
  if (windows[activewindow]!=sender->window)
  {
   if (sender->window->IsInWindow(windows[activewindow]))
   {
     isinwin = false;
   } else isinwin = true;
  } else isinwin = true;
  
 if (!sender->visible) combolistbox->scroll->visible = false;

 int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
  
 if (sender->visible)
 { 
// int l=sender->window->left;
// int t=sender->window->top+wcaph;
// int w=sender->window->width;
// int h=sender->window->height-wcaph;
// glEnable(GL_SCISSOR_TEST);
// glScissor(l,height-(t+h-2),w,h+1);
     int l = sender->window->left+sender->left;
     int t = sender->window->top+wcaph+sender->top;
     int w = sender->width;
     int h = sender->height;
     glEnable(GL_SCISSOR_TEST);
     glScissor(l,height-(t+h+1),w,h+1); 

 if (sender->flat) bctl = 7;
 else bctl = 1;
 
 if (comboboxctrlon==1) bctl = 1;
 
 if (mouseb==0)
 {
  if (combolistbox->IsInComboBox(sender)==true)
  {
      if ((combolistboxcontrolon == true)&&(sender->focus))
      {   
         if (onctrl && isinwin)
         {
           if (sender->onclick != NULL) 
           {
            sender->onclick(sender);
            sender->clicked = false;
            combolistboxcontrolon = false;
           }
           else
           {
            sender->clicked = false;
            combolistboxcontrolon = false;
           }
         }
      }
  } else
  {
 //   if (combolistbox->IsInComboBox(sender)==false) combolistbox->checked = chk;
  }
 }
 if ((mouseb==1)&&(isinwin))
 {
  if (combolistbox->IsInComboBox(sender)==true)
  {
      sender->clicked = true;     
      if (isinwin) sender->focused = true;
      if ((sender->flat==true)&&(isinwin)) bctl = 1;
  } else
  { 
    if (combolistboxcontrolon) sender->focused = false;
    sender->clicked = true;     
  }
 } else
 {
   sender->clicked = false;
   if ((combolistbox->IsInComboBox(sender)==true)&&(isinwin)) bctl = 1;
 }

if (combolistbox->borderstyle == bsSingle) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,sender->width,sender->height,bctl,alphacontrol);

COLORREF bkcolor = clWhite;


 fillrect(((sender->window->left+sender->left)+1),((sender->window->top+wcaph+sender->top+2)+1),((sender->window->left+sender->left+sender->width)-2),((sender->window->top+wcaph+sender->top+2+sender->height)-2),bkcolor,alphacontrol);

//if (combolistbox->checked) drawimage(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,checkedicon,sender->alphavalue,true,clLime);
if (windows[activewindow]==sender->window)
{
if (sender->window->IsInWindow(windows[activewindow]))
if (mouseb==1) 
{
// if (combolistbox->IsInComboBox(sender)==true) drawimagemask(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,checkedicon,sender->alphavalue,clGray,true,clLime);
} else combolistbox->focus = false;
} else combolistbox->focus = false;

if (combolistbox->flat)
{
if ((isinwin)&&(comboboxctrlon)) combolistbox->scroll->flat = false;
else combolistbox->scroll->flat = true;
} else combolistbox->scroll->flat = false;

combolistbox->scroll->kind = sbVertical;
combolistbox->scroll->showborder = false;
combolistbox->scroll->fastchange = true;
combolistbox->scroll->width = 20;
combolistbox->scroll->height = combolistbox->height-2;
combolistbox->scroll->left = (combolistbox->left+(combolistbox->width-4))-18;
combolistbox->scroll->top = combolistbox->top+2;
combolistbox->scroll->min = 0;
combolistbox->scroll->max = combolistbox->numitems;
combolistbox->scroll->smallchange = 1;

int itemx = sender->window->left+sender->left+4;
int itemy = sender->window->top+wcaph+sender->top+1;
int itemw = sender->width-4;
int itemh = combolistbox->itemheight;

combolistbox->scroll->visible = false;

int maxitems = 0;

for (int i=0;i<combolistbox->numitems;i++)
{
 itemx = sender->window->left+sender->left+4;
 itemw = sender->width-4;
 itemh = combolistbox->itemheight;
 if (itemy >= (sender->window->top+wcaph+sender->top+1+combolistbox->height-combolistbox->itemheight)-1)
 {
   if (sender->visible)
   {
      if(showcomboscrolllistbox) combolistbox->scroll->visible = true;
   }
   else combolistbox->scroll->visible = false;
 } else maxitems++;
 itemy += combolistbox->itemheight;
}

itemx = sender->window->left+sender->left+4;
itemy = sender->window->top+wcaph+sender->top+1;
itemw = sender->width-4;
itemh = combolistbox->itemheight;

if ((sender->focused) && (windows[activewindow]==sender->window))
{
  if (keys[VK_HOME])
  {
    if (combolistbox->itemindex>0)
    {
      combolistbox->itemindex = 0;
      combolistbox->scroll->position = combolistbox->itemindex;
    }
    keys[VK_HOME] = 0;
  }
  if (keys[VK_END])
  {
    if (combolistbox->itemindex<combolistbox->numitems-1)
    {
      combolistbox->itemindex = combolistbox->numitems-1;
      combolistbox->scroll->position = combolistbox->itemindex;
    }
    keys[VK_END] = 0;
  }
  if (keys[VK_PRIOR])
  {
    if (combolistbox->itemindex>0)
    {
      combolistbox->itemindex-=((maxitems));
      if (combolistbox->itemindex<0) combolistbox->itemindex = 0;
      combolistbox->scroll->position = combolistbox->itemindex;
    }
    keys[VK_PRIOR] = 0;
  }
  if (keys[VK_NEXT])
  {
    if (combolistbox->itemindex<combolistbox->numitems-1)
    {
      combolistbox->itemindex+=((maxitems));
      if (combolistbox->itemindex>combolistbox->numitems-1) combolistbox->itemindex = combolistbox->numitems-1;
      combolistbox->scroll->position = combolistbox->itemindex;
    }
    keys[VK_NEXT] = 0;
  }
  if (keys[VK_UP])
  {
    if (combolistbox->itemindex>0)
    {
      combolistbox->itemindex--;
      combolistbox->scroll->position = combolistbox->itemindex;
    }
    keys[VK_UP] = 0;
  }
  if (keys[VK_DOWN])
  {
    if (combolistbox->itemindex<combolistbox->numitems-1)
    {
      combolistbox->itemindex++;
      combolistbox->scroll->position = combolistbox->itemindex;
    }
    keys[VK_DOWN] = 0;
  }
}

int startindex = (combolistbox->scroll->position-maxitems);
if (startindex<0) startindex = 0;
if (startindex>=combolistbox->numitems) startindex = combolistbox->numitems-1;

for (int i=startindex;i<combolistbox->numitems;i++)
{
 itemx = sender->window->left+sender->left+4;
 itemw = sender->width-4;
 itemh = combolistbox->itemheight;

 if (combolistbox->scroll->visible)
 {
   // verticalscroll
   itemw = ((sender->width-4)-(combolistbox->scroll->width));
 }
 if (mouseb || combolistbox->autoselect)
 {
   if (getarea(itemx-3,itemy+1,itemw-2,itemh-1) && (isinwin)) combolistbox->itemindex = i;
 }
 if (itemy >= (sender->window->top+wcaph+sender->top+1+combolistbox->height-combolistbox->itemheight)-1)
 {
   itemh-=2;
 }
 if (itemy < (sender->window->top+wcaph+sender->top+1+combolistbox->height-combolistbox->itemheight))
 {
  if (combolistbox->itemindex == i)
  {
   fillrect(itemx-3,itemy+2,itemx+itemw-2,itemy+itemh+2,clHighlight,alphacontrol);
   if (sender->focused && combolistbox->showfocusframe) rectangledotted(itemx-2,itemy+2,itemx+itemw-3,itemy+itemh+1,clYellow,alphacontrol);
   textattr(clHighlightText,alphacontrol,12,FW_NORMAL);
  } else textattr(clBlack,alphacontrol,12,FW_NORMAL);
  textout(itemx,itemy+2,(char*)combolistbox->items[i].c_str());
 }
 itemy += combolistbox->itemheight;
}

glDisable(GL_SCISSOR_TEST);

}

}

TComboListBox::TComboListBox(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="combolistbox";
          visible = false;
          left=0;
          top=0;
          width=121;
          height=97;
          alphavalue = window->alphavalue;
          color = clWindow;
          caption="combolistbox";
          autoselect = false;
          itemheight = 16;
          itemindex = -1;
          numitems = 0;
          multiselect = false;
          scroll = new TListScrollBar(window);
          scroll->kind = sbVertical;
          scroll->twinkle = false;
          scroll->width = 20;
          scroll->height = height;
          scroll->left = left+(width-4);
          scroll->top = top;
          scroll->visible = false;
          borderstyle = bsSingle;
          showfocusframe = true;
          render = rendercombolistbox;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
}

TComboListBox::~TComboListBox()
{
  delete scroll;
}

bool TComboListBox::IsInComboBox(TControl* Control)
{
     int wt = Control->window->height-Control->window->clientheight;
     if ((Control->window->borderstyle != bsNone)&&(windowmanager == 1)) wt -= 3;
     if (((mousex>=(Control->window->left+Control->left))&&(mousey>=(Control->window->top+wt+Control->top)))&&(mousex<=(Control->window->left+Control->left+Control->width))&&(mousey<=(Control->window->top+Control->top+wt+Control->height)))
     {
       return true;
     }
     return false;
}

void TComboListBox::additem(char* name)
{
     items[numitems] = name;
     numitems++;
}

void TComboListBox::rendercontrol()
{
instance = this;
if ((visible==true)&&(window->visible==true))
{
if (visible) 
{
 render(this);
 hintcontrol(this);
}

if (activewindow==window->windowid)
{
if (window->activecontrol==controlid)
{
//if (mouseb==1)
//{
  if (IsInComboBox(this)==true)
  {
    focused = true;  
    
  } //else focused = false;
//}
} //else focused = false;

if (mouseb==1)
{
  if (IsInComboBox(this)==true)
  {
    focus = true;  
  } else focus = false;
  if (focus==true)
  {
    clicked = true;
  }
}
if ((focus==true)&&(focused==true)&&(clicked==true)&&(combolistboxcontrolon==true))
{
if (IsInComboBox(this)==true)
{    
//  if (onclick != NULL) onclick(this);
  combolistboxcontrolon = false;
  clicked = false;
  combolistboxcontrolon = false;
}
} //else focused = false;
}
}
scroll->rendercontrol();
}
void TComboListBox::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
  }
}
void TComboListBox::hide()
{
          visible = false;
}

bool combobox_focused = false;
bool showcombolistbox = false;
bool comboboxcontrolon = false;
void rendercombobox(TControl *sender)
{
TComboBox* combobox = dynamic_cast <TComboBox*>((TComboBox*)sender);
 bool onctrl = combobox->IsInComboBox(sender);
 int bctl = 1;
 int wcaph = sender->window->height-sender->window->clientheight;
 bool dropdownbtn = false;
 int dropdownbtnw = 20;

 bool isinwin = false;
  if (windows[activewindow]!=sender->window)
  {
   if (sender->window->IsInWindow(windows[activewindow]))
   {
     isinwin = false;
   } else isinwin = true;
  } else isinwin = true;
/*
   if (combobox->listbox->visible)
   {
    isinwin = true;
    combobox_focused = true;
    combobox->focus = true;
    combobox->focused = true;
    combobox->listbox->focus = true;
    combobox->listbox->focused = true;
   }
  */
 combolistboxvisible = sender->visible;
 
 int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
 
 if (sender->visible)
 { 
 if (windowresize || (windowresizeside>0)) isinwin = false;

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
     

  combobox->edit->text = combobox->text;
 
 if (sender->flat) bctl = 7;
 else bctl = 1;

 if (combobox->listbox->visible)
 {
      if (getarea(sender->window->left+combobox->listbox->left,sender->window->top+wcaph+combobox->listbox->top,combobox->listbox->width,combobox->listbox->height)) bctl = 1;
 }

 int dropdownbtnleft = (sender->window->left+sender->left+((sender->width-dropdownbtnw)-1));
 int dropdownbtntop = sender->window->top+wcaph+sender->top+4;
 int dropdownbtnwidth = (dropdownbtnw-((bctl == 12) ? 0 : 1));
 int dropdownbtnheight = (sender->height-5)-((bctl == 12) ? 1 : 0);
 
 if (combobox->style != csDropDown)
 {
   dropdownbtnleft = (sender->window->left+sender->left);
   dropdownbtnwidth = ((sender->width));//-((bctl == 12) ? 0 : 1));
 }
 
// if (mouseb)
// {
  if (getarea(dropdownbtnleft,dropdownbtntop,dropdownbtnwidth,dropdownbtnheight)) dropdownbtn = true;
  else dropdownbtn = false;
// } else dropdownbtn = false;

/*
if (dropdownbtn)
{
 for (int i=0;i<sender->window->numlistboxes;i++) sender->window->listboxes[i]->focused = false;
}
*/

for (int i=0;i<256;i++)
{
 if (combobox->style == csDropDown)
 {
  if ((i != VK_RETURN) && (keys[i]>0) && (!keys[VK_RETURN]) && (i != VK_RETURN))
  {
   if (combobox->numitems>0)
   {
    for (int j=0;j<combobox->numitems;j++)
    {
      if (combobox->items[j]==combobox->edit->text)
      {
        combobox->itemindex = j;
        combobox->listbox->itemindex = combobox->itemindex;
      }
    }
   }
  }
  else
  {
   if (keys[VK_RETURN] == 1)
   {
    if (showcombolistbox)
    {
      combobox->itemindex = combobox->listbox->itemindex;
      combobox->text = combobox->items[combobox->itemindex];
      showcombolistbox = false;
    }
   }
  }
 } 
 else
 {
  if (keys[VK_RETURN] == 1)
  {
    if (showcombolistbox)
    {
      combobox->itemindex = combobox->listbox->itemindex;
      combobox->text = combobox->items[combobox->itemindex];
      showcombolistbox = false;
    }
  }
 }
}
 if (windows[activewindow] != sender->window) combobox_focused = false;
 if (mouseb==1)
 {
   if ((comboboxcontrolon == true)&&(!sender->focused))
   {
     int dropdownitemleft = ((sender->window->left+sender->left)+1);
     int dropdownitemtop = ((sender->window->top+wcaph+sender->top+2)+1);
     int dropdownitemwidth = ((sender->window->left+sender->left+sender->width-dropdownbtnw)-2);
     int dropdownitemheight = ((sender->window->top+wcaph+sender->top+2+sender->height-1)-2);
     if (!getarea(dropdownitemleft,dropdownitemtop,dropdownitemwidth,dropdownitemheight)) combobox_focused = false;
   }
 }
 if (mouseb==0)
 {
  if (combobox->IsInComboBox(sender)==true)
  {
      if ((comboboxcontrolon == true)&&(sender->focus))
      {   
         if (onctrl && isinwin)
         {
           if (dropdownbtn)
           {
             showcombolistbox = !showcombolistbox;
             comboboxcontrolon = false;
           }
           if (sender->onclick != NULL) 
           {
            sender->onclick(sender);
            sender->clicked = false;
            comboboxcontrolon = false;
           }
           else
           {
            sender->clicked = false;
            comboboxcontrolon = false;
           }
         }
      }
  } else
  {
 //   if (combobox->IsInComboBox(sender)==false) combobox->checked = chk;
  }
 }
 if ((mouseb==1)&&(isinwin))
 {
  for (int i=0;i<sender->window->numlistboxes;i++) sender->window->listboxes[i]->focused = false;
  if (combobox->IsInComboBox(sender)==true)
  {
      for (int i=0;i<sender->window->numcomboboxes;i++) sender->window->comboboxes[i]->focused = false;
      sender->clicked = true;     
      if (isinwin)
      {
          sender->focused = true;
          combobox_focused = true;
      }
      if ((sender->flat==true)&&(isinwin)) bctl = 1;
  } else
  { 
    sender->focused = false;
    if (comboboxcontrolon) sender->focused = false;
    sender->clicked = true;     
  }
 } else
 {
   sender->clicked = false;
   if ((combobox->IsInComboBox(sender)==true)&&(isinwin)) bctl = 1;
 }
 if (bctl==1)
 {
    if (combobox->listbox->visible) comboboxctrlon = true;
    else comboboxctrlon = false;
 }
 else 
 {
  if (!combobox->listbox->IsInControl(combobox->listbox)) comboboxctrlon = false;
  else
  {
    if (combobox->listbox->visible) comboboxctrlon = true;
    else comboboxctrlon = false;
  }
 }
 
 if (combobox->listbox->IsInControl(combobox->listbox) && (combobox->listbox->visible)) bctl = 1;
 
 if ((mouseb==1)&&(!isinwin)) sender->focused = false;

if (combobox->borderstyle == bsSingle)
{
/*
 if (bctl==1) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,sender->width+1,sender->height-2,14,alphacontrol);
 else drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,sender->width,sender->height-1,bctl,alphacontrol);
*/
 drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,sender->width,sender->height-1,bctl,alphacontrol); 
}

COLORREF bkcolor = clWhite;
 
 int dropdownitemleft = ((sender->window->left+sender->left)+1);
 int dropdownitemtop = ((sender->window->top+wcaph+sender->top+2)+2);
 int dropdownitemwidth = ((sender->window->left+sender->left+sender->width-dropdownbtnw)-2);
 int dropdownitemheight = ((sender->window->top+wcaph+sender->top+2+sender->height-1)-2);
 
 fillrect(dropdownitemleft,dropdownitemtop,dropdownitemwidth,dropdownitemheight,bkcolor,alphacontrol);
 if (bctl == 1) bctl = 12;
 dropdownbtnleft = (sender->window->left+sender->left+((sender->width-dropdownbtnw)-1));
 dropdownbtntop = sender->window->top+wcaph+sender->top+4;
 dropdownbtnwidth = (dropdownbtnw-((bctl == 12) ? 0 : 1));
 dropdownbtnheight = (sender->height-5)-((bctl == 12) ? 1 : 0);

 if (combobox->style != csDropDown)
 {
   dropdownbtnleft = (sender->window->left+sender->left);
   dropdownbtnwidth = ((sender->width)-((bctl == 12) ? 0 : 1));
 }

 if (mouseb)
 {
  if (getarea(dropdownbtnleft,dropdownbtntop,dropdownbtnwidth,dropdownbtnheight)) dropdownbtn = true;
  else dropdownbtn = false;
 } else dropdownbtn = false;
  
 dropdownbtnleft = (sender->window->left+sender->left+((sender->width-dropdownbtnw)-1));
 dropdownbtntop = sender->window->top+wcaph+sender->top+4;
 dropdownbtnwidth = (dropdownbtnw-((bctl == 12) ? 0 : 1));
 dropdownbtnheight = (sender->height-6)-((bctl == 12) ? 1 : 0);

 drawcontroledge(dropdownbtnleft,dropdownbtntop,dropdownbtnwidth,dropdownbtnheight,((bctl-1)+dropdownbtn),alphacontrol);
 drawimage((dropdownbtnleft-1)+dropdownbtn,(dropdownbtntop-1)+dropdownbtn,downarrowicon,sender->alphavalue,true,clLime);

if (combobox->numitems > 0)
{
 combobox->listbox->borderstyle = bsNone;
 combobox->edit->left = combobox->left;
 combobox->edit->top = combobox->top+3;
 combobox->edit->width = ((combobox->width-dropdownbtnw)-2);
 combobox->edit->height = combobox->height-5;
 combobox->edit->visible = true;
 combobox->listbox->numitems = combobox->numitems;

 if (combobox->style != csSimple) combobox->listbox->showfocusframe = false;
 else combobox->listbox->showfocusframe = false;
 
if (combobox->style == csDropDown)  combobox->edit->visible = true;
else
{
 combobox->edit->visible = false;
 if (combobox->itemindex >= 0)
 {
  int itemfontcolor = clBlack;
 
  if (combobox_focused && (!showcombolistbox))
  {
    fillrect(dropdownitemleft+1,dropdownitemtop+1,dropdownitemwidth-1,dropdownitemheight-1,clHighlight,alphacontrol);
    rectangledotted(dropdownitemleft+2,dropdownitemtop+1,dropdownitemwidth-1,dropdownitemheight-2,clYellow,alphacontrol);
    itemfontcolor = clHighlightText;
  }
  
  textattr(itemfontcolor,alphacontrol,12,FW_NORMAL);
  textout(dropdownitemleft+4,dropdownitemtop+2,(char*)combobox->items[combobox->itemindex].c_str());
 }
} 

// combobox->listbox->focused = combobox->focused;
// combobox->focused = combobox->listbox->focused;
 for (int i=0;i<combobox->numitems;i++) combobox->listbox->items[i] = combobox->items[i];

if (mouseb)
{
 if (!sender->focused)
 {
   if (!combobox->listbox->IsInComboBox(combobox->listbox)) showcombolistbox = false;
 }
}
else
{
/*
   if (combobox->listbox->visible)
   {
       combobox->focus = combobox->listbox->focus;
       combobox->focused = combobox->listbox->focused;
   }
*/
}

if (combobox->numitems > 0)
{
 
 int dropdownlistleft = dropdownitemleft-1;
 int dropdownlisttop = (dropdownitemtop+24)-1;
 int dropdownlistwidth = (dropdownitemwidth+dropdownbtnw)+2;
 int dropdownlistheight = (combobox->itemheight*combobox->numitems)+2;
 
 if (getarea(dropdownlistleft,dropdownlisttop,dropdownlistwidth,dropdownlistheight))
 {
   if (combobox->listbox->visible)
   {
    isinwin = true;
    combobox_focused = true;
   }
 }

 if (combobox->dropdowncount > 0)
 {
 //  dropdownlistheight = (combobox->itemheight*combobox->dropdowncount);
   if (dropdownlistheight > ((combobox->itemheight*combobox->dropdowncount)+2)) dropdownlistheight = ((combobox->itemheight*combobox->dropdowncount)+2);
 }
 
 if (showcombolistbox)
 {
  // glEnable(GL_SCISSOR_TEST);
   glScissor(dropdownlistleft-1,height-((dropdownlisttop+(dropdownlistheight-1)-2)+h+1),dropdownlistwidth,(dropdownitemheight+dropdownlistheight-1)+1); 
   fillrect(dropdownlistleft,dropdownlisttop,dropdownlistwidth,dropdownitemheight+dropdownlistheight-1,bkcolor,alphacontrol);
   rectangle(dropdownlistleft,dropdownlisttop-2,dropdownlistwidth,dropdownitemheight+dropdownlistheight-1,clBlack,alphacontrol);
   combobox->listbox->left = combobox->left-1;
   combobox->listbox->top = (combobox->top+combobox->itemheight+8)-1;
   combobox->listbox->width = (dropdownlistwidth-(dropdownlistleft))+2;
   combobox->listbox->height = dropdownlistheight-1;
 }
 combobox->listbox->visible = showcombolistbox;
} else combobox->listbox->visible = false;

if (!combobox->listbox->visible) combobox->listbox->scroll->visible = false;

if (showcombolistbox)
{
 if (mouseb==1)
 {
  int dropdownlistscrollbtnw = dropdownbtnw;
  if (!combobox->listbox->scroll->visible) dropdownlistscrollbtnw = 0; 
  int dropdownlistleft = dropdownitemleft-1;
  int dropdownlisttop = (dropdownitemtop+24)-1;
  int dropdownlistwidth = (sender->width-dropdownlistscrollbtnw)-2;
  int dropdownlistheight = (combobox->itemheight*combobox->numitems)+2;

  if (getarea(dropdownlistleft,dropdownlisttop,dropdownlistwidth,dropdownlistheight))
  {
    combobox->itemindex = combobox->listbox->itemindex;
    combobox->edit->text = combobox->items[combobox->itemindex];
    combobox_focused = true;

    showcombolistbox = false;
  }
 }
 else
 {
   combobox->listbox->autoselect = true;
 }
}

}

//if (combobox->checked) drawimage(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,checkedicon,sender->alphavalue,true,clLime);
if (windows[activewindow]==sender->window)
{
if (sender->window->IsInWindow(windows[activewindow]))
if (mouseb==1) 
{
// if (combobox->IsInComboBox(sender)==true) drawimagemask(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,checkedicon,sender->alphavalue,clGray,true,clLime);
} else combobox->focus = false;
} else combobox->focus = false;

glDisable(GL_SCISSOR_TEST);
}

}

bool TComboBox::IsInComboBox(TControl* Control)
{
     
     /*
     int wt = Control->window->height-Control->window->clientheight;
     if ((Control->window->borderstyle != bsNone)&&(windowmanager == 1)) wt -= 3;
     if (((mousex>=(Control->window->left+Control->left))&&(mousey>=(Control->window->top+wt+Control->top)))&&(mousex<=(Control->window->left+Control->left+Control->width))&&(mousey<=(Control->window->top+Control->top+wt+Control->height)))
     {
       return true;
     }
     return false;
     */
     
     return IsInControl(Control);
}

TComboBox::TComboBox(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="combobox";
          visible = false;
          left=0;
          top=0;
          width=145;
          height=24;
          alphavalue = window->alphavalue;
          color = clWindow;
          caption="combobox";
          dropdowncount = 8;
          itemheight = 16;
          itemindex = -1;
          numitems = 0;
          maxlength = 0;
          borderstyle = bsSingle;
          
          int wcaph = window->height-window->clientheight;
     
          int dropdownbtnw = 20;
          int dropdownitemleft = ((window->left+left)+1);
          int dropdownitemtop = ((window->top+wcaph+top+2)+1);
          int dropdownitemwidth = ((width-dropdownbtnw)-2);
          int dropdownitemheight = ((height-1)-2);
          
          edit = new TComboBoxEdit(window);
          edit->left = left;
          edit->top = top+3;
          edit->width = ((width-dropdownbtnw)-2);
          edit->height = height-5;
          edit->visible = false;

          int dropdownbtnleft = (window->left+left+((width-dropdownbtnw)-1));
          int dropdownbtntop = window->top+wcaph+top+4;
          int dropdownbtnwidth = (dropdownbtnw);
          int dropdownbtnheight = (height-5);

          listbox = new TComboListBox(window);
          listbox->autoselect = false;
          listbox->borderstyle = bsNone;
          listbox->left = left+32;
          listbox->top = top+itemheight+4;
          listbox->width = width;
          listbox->height = itemheight*2;
          listbox->itemindex = 0;
          listbox->numitems = 0;
          listbox->visible = false;

          render = rendercombobox;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->comboboxes[window->numcomboboxes] = this;
          window->numcomboboxes++;
          window->numcontrols++;
}

TComboBox::~TComboBox()
{
  delete edit;
  delete listbox;
}

void TComboBox::additem(char* name)
{
     items[numitems] = name;
     numitems++;
}

void TComboBox::rendercontrol()
{
if ((visible==true)&&(window->visible==true))
{
if (visible)
{
  render(this);
  hintcontrol(this);
}

if (activewindow==window->windowid)
{
if (window->activecontrol==controlid)
{
//if (mouseb==1)
//{
  if (IsInComboBox(this)==true)
  {
    focused = true;  
    
  } //else focused = false;
//}
} //else focused = false;

if (mouseb==1)
{
  if (IsInComboBox(this)==true)
  {
    focus = true;  
  } else focus = false;
  if (focus==true)
  {
    clicked = true;
  }
}
if ((focus==true)&&(focused==true)&&(clicked==true)&&(comboboxcontrolon==true))
{
if (IsInComboBox(this)==true)
{    
//  if (onclick != NULL) onclick(this);
  comboboxcontrolon = false;
  clicked = false;
  comboboxcontrolon = false;
}
} //else focused = false;
}
}

edit->rendercontrol();
if (visible) text = edit->text;
listbox->rendercontrol();

if (numitems > dropdowncount)
{
  if (dropdowncount > 0) showcomboscrolllistbox = true;
  else showcomboscrolllistbox = false;
}
else 
{
  showcomboscrolllistbox = false;
}

instance = this;
window->comboboxes[controlid] = this;
}
void TComboBox::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->comboboxes[controlid] = this;
  }
}
void TComboBox::hide()
{
          visible = false;
          window->comboboxes[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createcombobox(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int cmbboxid = 0;
   cmbboxid = windows[winid]->numcomboboxes;
   TComboBox* combobox = new TComboBox(windows[winid]);
   combobox->alphavalue = 255;
   combobox->enabled = true;
   combobox->width=72;
   combobox->height=24;
   combobox->left=32;
   combobox->top=32;
   combobox->visible = false;
   return cmbboxid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

