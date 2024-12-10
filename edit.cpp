// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "edit.h" // class's header file

TEdit* activeedit;
int xl=0;
int blinkcnt=0;
bool editcontrolon = false;
bool editfocused = false;
bool textarea = false;


void renderedit(TControl *sender)
{
     int l=0;
     int t=0;
     int w=0;
     int h=0;
     TEdit* e = dynamic_cast <TEdit*>((TEdit*)sender);
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

if (sender->visible == true)
{
     if (windowresize || (windowresizeside>0)) isinwin = false;
     
     int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
     int l = sender->window->left+sender->left-1;
     int t = sender->window->top+wcaph+sender->top-1;
     int w = sender->width+1;
     int h = sender->height+2;
     glEnable(GL_SCISSOR_TEST);
     glScissor(l,height-(t+h+1),w,h+1); 
     l = sender->window->left+sender->left;
     t = sender->window->top+wcaph+sender->top;
     w = sender->width;
     h = sender->height;

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
     
     if (sender->flat) ebctl = 7;
     else ebctl = 1;
     
     if (sender->IsInControl(sender)) ebctl = 1;
     
     if (sender->flat)
     {
        if (!isinwin) ebctl = 7;
     }
     for (int updcnt=0;updcnt<e->window->numupdowns;updcnt++)
     {
        if (e->window->updowns[updcnt]->associate)
        {
         TEdit* updedit = dynamic_cast <TEdit*>((TEdit*)e->window->updowns[updcnt]->associate);
         if (e == updedit)
         {
           TUpDown* updc = dynamic_cast <TUpDown*>((TUpDown*)e->window->updowns[updcnt]);
           int updcl = sender->window->left+updc->left;
           int updct = sender->window->top+wcaph+updc->top;
           int updcw = updc->width;
           int updch = updc->height+5;
           if (getarea(updcl,updct,updcw,updch))
           {
             if (updc->window->IsInWindow(updc->window)) ebctl = 1;
           }
         }
        }
     }

     drawcontroledge(l,t,w,h,ebctl,alphacontrol);
     fillrect(l+1,t+2,l+w-2,t+h-2,clWhite,alphacontrol);
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
             if ((mousex > (l+xx-8))&&(mousex < (l+xx+8)))
             {
               if (mousec == 0)
               {
                 if (sti >= e->sel_start)
                 {
                  // if (!xl) 
                   e->sel_length = sti-e->sel_start;
                  //else 
                   //if (sti >= e->sel_index) xl = 0;
                 }
                 else 
                 {
                   //if (sti < e->sel_index-1) xl=1;   
                   //if (xl)
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
             if (editfocused)
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
         editfocused = true;
       } //else editfocused = false;
     }// else editfocused = true;
     else
     {
       if (!e->IsInControl(e)){}// editfocused = false;
       else editfocused = true;
     }
     
     if (e->text.length()>0) textout(l+4,t+3,(char*)s.c_str());
     
  if ((sender->focus) || ((sender->tabstop) && (sender->taborder == 0)))
  {
     if (blinkcnt > 128) blinkcnt = 0;

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

       if (e->sel_start != slen) fillrect(sll-sllt,t+3,sllw-slltw,t+h-6,clHighlight,alphacontrol);
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
     
     if (blinkcnt & 32)
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
     blinkcnt++;
     
     if (sender->IsInControl(sender))
     {
       if (mouseb==3)
       {
         activetextedit = NULL;
         activeedit = e;
         editmenu->alphavalue = sender->alphavalue;
         editmenu->left = mousex;
         editmenu->top = mousey;
         show_menu(editmenu);
       }
     }
  }
  glDisable(GL_SCISSOR_TEST);
}
}

void TEdit::editinput()
{
  if (charcase == ecUpperCase) text = strupr((char*)text.c_str());
  if (charcase == ecLowerCase) text = strlwr((char*)text.c_str());
  if (focus)
  {  
    std::string oldtext = text;
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
           if (oldtext != text)
           {
             if (onchange) onchange(this);
           }
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


TEdit::TEdit(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="edit";
          visible = false;
          left=0;
          top=0;
          width=128;
          height=32;
          alphavalue = window->alphavalue;
          color = clWindow;
          caption="edit";
          text="edit";
          seltext="";
          sel_index = 0;
          sel_start = 0;
          sel_length = 0;
          charcase = ecNormal;
          maxlength = 0;
          readonly = false;
          render = renderedit;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->edits[window->numedits] = this;
          window->numedits++;
          window->numcontrols++;
          activeedit = this;
          parent = Window;
}


void TEdit::clear()
{
std::string s = "";
sel_index = 0;
sel_start = 0;
sel_length = 0;
text = s;
seltext = s;
if (onchange) onchange(this);
}

void TEdit::selectall()
{
  sel_start = 0;
  sel_index = 0;
  sel_length = text.length();
  seltext = text;
}

void TEdit::rendercontrol()
{
if ((visible==true)&&(window->visible==true))
{
if (visible)
{
  if (activewindow!=window->windowid) focus = false;
  editinput();
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
if ((focused==true)&&(clicked==true)&&(editcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  editcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->edits[controlid] = dynamic_cast <TEdit*>((TEdit*)this);//this;
}
void TEdit::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->edits[controlid] = this;
  }
}
void TEdit::hide()
{
          visible = false;
          window->edits[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createedit(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int edtid = 0;
   edtid = windows[winid]->numedits;
   TEdit* edit = new TEdit(windows[winid]);
   edit->alphavalue = 255;
   edit->enabled = true;
   edit->width=72;
   edit->height=24;
   edit->left=32;
   edit->top=32;
   edit->visible = false;
   return edtid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

