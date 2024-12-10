// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "textbox.h" // class's header file

TTextBox* activetextedit;
int textbox_xl=0;
int textboxblinkcnt=0;
bool textboxcontrolon = false;
bool textboxfocused = false;

void rendertextbox(TControl *sender)
{
     int l=0;
     int t=0;
     int w=0;
     int h=0;
     TTextBox* e = dynamic_cast <TTextBox*>((TTextBox*)sender);
     int len = strlen(e->text.c_str());
     int ebctl = 1;
     int wcaph = (sender->window->height-sender->window->clientheight);
     if ((sender->window->borderstyle != bsNone)&&(windowmanager == 1)) wcaph -= 3;
     if ((sender->window->borderstyle != bsNone)&&(windowmanager == 0)) wcaph -= 3;
     int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
 
 bool isinwin = false;
 if (windows[activewindow]!=sender->window)
 {
  if (sender->window->IsInWindow(windows[activewindow]))
  {
    isinwin = false;
  } else isinwin = true;
 } else isinwin = true;
 if (IsInAnyMenu()) isinwin = false;
 
if (sender->visible == true)
{
     if (windowresize || (windowresizeside>0)) isinwin = false;
     
     int l = sender->window->left+sender->left-1;
     int t = sender->window->top+wcaph+sender->top-1;
     int w = sender->width+1;
     int h = sender->height+2;
     if (windowmanager == 0) h -= windowtopbarheightdefault;
     glEnable(GL_SCISSOR_TEST);
     glScissor(l,height-(t+h+1),w,h+1); 
     
     int bl=sender->window->left;
     int bt=sender->window->top+wcaph;
     int bw=sender->window->width;
     int bh=sender->window->height-wcaph;
     if (windowmanager == 0) bh -= windowtopbarheightdefault;

     glEnable(GL_SCISSOR_TEST);
     if (!windowmanager) glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
     else
     {
     if (wcaph>0) glScissor(bl+1,height-(bt+bh-5),bw-6,bh+1);
     else glScissor(bl,height-(bt+bh-2),bw-2,bh+1);
     }

     l = sender->window->left+sender->left;
     t = sender->window->top+wcaph+sender->top;
     w = sender->width;
     h = sender->height;
     if (windowmanager == 0) h -= windowtopbarheightdefault;
     
     e->hscroll->left = sender->left+1;
     e->hscroll->top = ((sender->top+h)-20)-6;
     e->hscroll->width = (w-20)-3;
     e->hscroll->height = 20;
     e->hscroll->visible = true;
     
     e->vscroll->left = ((sender->left+w)-20)-2;
     e->vscroll->top = sender->top-2;
     e->vscroll->width = 20;
     e->vscroll->height = (h-20)-3;
     e->vscroll->visible = true;
     std::string e_text = "";
     if (e->text.length()<=0) e->text = 32;
     e_text = e->text;
     
     if (mouseb)
     {
     if (sender->IsInControl(sender)&&((sender->IsInControl(e->hscroll))||(sender->IsInControl(e->vscroll)))) isinuse = 1;
     else isinuse = 0;
     }
     else isinuse = 0;
     
     if (sender->window->width<96) e->vscroll->visible = false, e->hscroll->visible = false;
     if (sender->window->height<64) e->vscroll->visible = false, e->hscroll->visible = false;
     
  //   if (sender->window->width<96) return;
     if (sender->window->height<64) return;

     if (sender->flat) ebctl = 7;
     else ebctl = 1;
     
     if (sender->IsInControl(sender)) ebctl = 1;
     
     if (sender->flat)
     {
        if ((!isinwin)||(IsInAnyMenu())) ebctl = 7;
     }
     
     if (sender->flat)
     {
       if (sender->IsInControl(sender) && (!IsInAnyMenu()))
       {
         e->hscroll->flat = false;
         e->vscroll->flat = false;
       } else
       {
         e->hscroll->flat = true;
         e->vscroll->flat = true;
       }
     }
     
     drawcontroledge(l,t,w,h,ebctl,alphacontrol);
     if (e->hscroll->visible && e->vscroll->visible)
     {
       w -= 20;
       h -= 20;
     }
     fillrect(l+1,t+2,l+w-2,t+h-2,clWhite,alphacontrol);
     textattr(clBlack,alphacontrol,12,FW_NORMAL);
     std::string s = "";
     
     if ((!sender->focus) && (sender->window->activecontrol != e->controlid) &&
     (sender->tabstop) && (sender->taborder == 0))
     {
       e->sel_start = 0;
       e->sel_length = 0;
     //  e->sel_index = e->sel_start;
     //  e->sel_length = e_text.length();
     }
     

     int k=0,j=1,l1=0;
     int b=0;
     float tw=0;
     int ll=0;
     int charwidth = textwidth("A");
     int halfcharwidth = charwidth/2;
     tw = textwidth((char*)s.c_str());

     k=0;
     
     std::string sline[1024];
     int slinelastnl=0;
     int slinetcnt=0;
     int slinenlcnt=0;
     int slinecnt=0;
     int slinepos=0;
     char *slinec = (char*)e_text.c_str();
     for (int i=0;i<e_text.length();i++)
     {
         if (slinec[i] == '\n')
         {
           slinenlcnt++;
           slinelastnl = i;
         }
     }

     for (int i=0;i<e_text.length();i++)
     {
         if (slinec[i] == '\n')
         {
           slinecnt++;
           sline[slinecnt] = slinec[i];
           slinepos = i;
         }
         else
         {
           sline[slinecnt] = sline[slinecnt] + slinec[i];
           slinepos = i;
           b = slinelastnl;
         }
//       int stnl = e_text.substr(slinepos,i).find_first_not_of( '\n' );
/*       if ((slinepos<e_text.length())&&(slinecnt<e_text.length()))
       {
         slinetcnt++;
         if ((slinec[i] == '\n')&&(slinecnt < slinenlcnt-1))
         {
           sline[slinecnt] = e_text.substr(slinepos,i);
           slinecnt++;
           slinepos = i;
         } else if (slinecnt==slinenlcnt-1)
         {
           sline[slinecnt] = e_text.substr(slinepos,i-(e_text.length()-(slinelastnl-4)));
           slinecnt++;
           slinepos = i;
         }
          else if (slinecnt==slinenlcnt)
         {
           sline[slinecnt] = e_text.substr(slinelastnl,i);
           slinecnt++;
           slinepos = i;
           b = slinelastnl;
         }
       }  
       */
     }
     slinecnt++;
     
     int slinemax = 0;
     int slinelen = 0;
     
     int slineyoff=0;
     for (int sli=0;sli<slinecnt;sli++)
     {
     s = sline[sli];//e_text;
  //   b=0;
     /*
     while ((textwidth((char*)s.c_str()) >= w-(charwidth-2)) && (e->window->width))
     {
       if ((textwidth((char*)s.c_str()) >= w-(charwidth-2)))
       {
         s = s.substr(e->hscroll->position/charwidth,(len-b));
         b++;
       }
       k++;
     }
     */
     
     slinelen = textwidth((char*)s.c_str());//s.length();
     
     if (slinemax == 0) slinemax = -999999;
     if (slinelen > slinemax) slinemax = slinelen;
     
     e->hscroll->fastchange = true;
     e->hscroll->smallchange = 1;
     e->hscroll->max = slinemax-24;//e_text.length();
     
     e->vscroll->fastchange = true;
     e->vscroll->smallchange = 1;
     e->vscroll->max = abs(slinecnt-((e->height/14)-2));

     std::string seltextstr = e_text;
     seltextstr = seltextstr.substr(b,e->sel_start-b);
     
     int ssw=0;

     ssw = 0;
     ssw = textwidth((char*)seltextstr.c_str());

     tw = ssw;
     
//     if (tw >= w-charwidth) tw = w-charwidth;
//     if (tw <= 0) tw = 0;
     /*
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
                  // if (!textbox_xl) 
                   e->sel_length = sti-e->sel_start;
                  //else 
                   //if (sti >= e->sel_index) textbox_xl = 0;
                 }
                 else 
                 {
                   //if (sti < e->sel_index-1) textbox_xl=1;   
                   //if (textbox_xl)
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
             if (textboxfocused)
             {
               e->sel_start = e_text.length();
               e->sel_index = e->sel_start;
             }
           }
         }
       }
     }
     */
     if (mousec==0)
     {
       if (e->focus)
       {
         textboxfocused = true;
       } //else textboxfocused = false;
     }// else textboxfocused = true;
     else
     {
       if (!e->IsInControl(e)){}// textboxfocused = false;
       else textboxfocused = true;
     }
     
     glEnable(GL_SCISSOR_TEST);
     glScissor(l+2,height-(t+h+2),w-5,h+1);
     if ((s.length()>0)&&(s[0]==0x0a)) s = s.substr(1,s.length());
     textout((l+4)-(e->hscroll->position),t+3+(slineyoff)-(e->vscroll->position*14),(char*)s.c_str());
     
  if ((sender->focus) || ((sender->tabstop) && (sender->taborder == 0)))
  {
     if (textboxblinkcnt > 128) textboxblinkcnt = 0;

     std::string sellengthtext = e_text;
     std::string sellength_text = e_text;
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

  //bkhere   //  if (e->sel_start != slen) fillrect(sll-sllt,t+3,sllw-slltw,t+h-6,clHighlight,alphacontrol);
  //     textout(l+4+1,t-23,(char*)sellengthtext.c_str());
       if (e->sel_length > 0)
       {
          c = clHighlightText;
       }

       //if (e->sel_length >= e_text.length())
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
       
     //  textattr(c,alphacontrol,12,FW_NORMAL); //textattr
     //  textout(((l+4)+slw),t+3,(char*)sellengthtext.c_str()); //texthere
     } else e->seltext = "";
     
  }
  slineyoff+=14;
 }
 
       int c = clBlack;
       int lw = 0;
       int lh = 0;
       int sly = 0;
       int sl = 0;
       int cl = 0;
       e->sel_start = e->caretx;
       lh = e->carety;
       if (lh > 0)
       {
         int thl=0;
         for (int k=0;k<lh;k++) thl += sline[k].length();
         thl += e->caretx+1;
         e->sel_start = thl;
       }
       e->rowlength = sline[lh].length();
       if (e->caretx >= e->rowlength) e->caretx = e->rowlength-1;
       e->count = slinecnt;
       if (e->carety>0) cl = 1;
       else cl = 0;
       std::string slinew = sline[lh].substr(cl,e->caretx);
       sl = e->sel_length;
       if (e->carety>0) cl = e->caretx+1;
       else cl = e->caretx;
       std::string slinex = "";
       if (cl < 0)
       {
         cl = 0;
         e->caretx = 0;
       }
       if (sline[lh].length()>0) slinex = sline[lh].substr(cl,sl);
       e->seltext = slinex;
       lw = textwidth((char*)slinew.c_str());
       lw -= (e->hscroll->position);
       sly = lh*14;
       sly -= (e->vscroll->position*14);
       
       fillrect((l+4)+(lw),t+3+sly,(l+4)+(lw+textwidth((char*)e->seltext.c_str())),t+3+sly+14,clHighlight,255);
       
       textattr(clHighlightText,alphacontrol,12,FW_NORMAL);
       textout((l+4)+(lw),t+3+sly,(char*)e->seltext.c_str()); 

       if (e->carety>0) cl = 1;
       else cl = 0;
       slinew = sline[lh].substr(cl,e->caretx+e->sel_length);
       lw = textwidth((char*)slinew.c_str());
       lw -= (e->hscroll->position);

     if (((sender->focus)&&(activewindow==sender->window->windowid))&&(textboxblinkcnt & 32))
     {
       textattr(c,alphacontrol,12,FW_NORMAL);
       textout((l+3)+(lw),t+sly,"|");   
       textout((l+3)+(lw),t+sly+1,"|");          
       textout((l+3)+(lw),t+sly+2,"|");          
     }

/*
     if (textboxblinkcnt & 32)
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
       int sly = 0;
       
       sly = slineyoff-14;
       
       lw -= (e->hscroll->position);
       
       textattr(c,alphacontrol,12,FW_NORMAL);
       textout((l+4)+(lw),t+sly,"|");          
       textout((l+4)+(lw),t+sly+1,"|");          
       textout((l+4)+(lw),t+sly+2,"|");          
       textout((l+4)+(lw),t+sly+3,"|");          
       textout((l+4)+(lw),t+sly+4,"|");          
     }
*/
     textboxblinkcnt++;
     glDisable(GL_SCISSOR_TEST);
     
     if (sender->IsInControl(sender))
     {
       if (mouseb==3)
       {
         activeedit = NULL;
         activetextedit = e;
         editmenu->alphavalue = sender->alphavalue;
         editmenu->left = mousex;
         editmenu->top = mousey;
         show_menu(editmenu);
       }
     }
}
}

void TTextBox::textinput()
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
           // if (s.length()<=0) s = 32;
           // if (s[0]==10) return;
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
               sel_length = caretx;
               sel_start = 0;
               caretx = 0;
             }
             else
             {
               caretx = 0;
               sel_start = 0;
               sel_length = 0;
               sel_index = sel_start;
               hscroll->position = sel_start;
             }
           }
           else
           if (i == VK_END)
           {
             if (keyshift)
             {
               sel_length = rowlength-1;
             }
             else
             {
               sel_start = rowlength-1;
               caretx = sel_start;
               sel_length = 0;
               sel_index = sel_start;
             }
           }
           else
           if (i == VK_UP)
           {
             rowlength = 0;
             sel_start = caretx;
             sel_length = 0;
             if (carety > 0) carety--;
           }
           else
           if (i == VK_DOWN)
           {
             rowlength = 0;
             sel_start = caretx;
             sel_length = 0;
             if (carety < count-1) carety++;
           }
           else
           if (i == VK_LEFT)
           {
           /*
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
             */
             if (keyshift) { if (sel_length>0) sel_length--; }
             else
             {
               if (caretx > 0) caretx--;
               sel_start = caretx;
               sel_length = 0;
             }
           }
           else
           if (i == VK_RIGHT)
           {
           /*
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
             } */
             if (keyshift) { if (sel_length < rowlength) sel_length++; }
             else
             {
               if (caretx < rowlength-1) caretx++;
               sel_start = caretx;
               sel_length = 0;
             }
           }
           else
           if(i == 8) //backspace
	       {
            if (sel_start > 0)
            {
	         if ((s.size() > 0) && (rowlength>0))
             {
               std::string sbuf = s;
               s = sbuf.substr(0,sel_start-1) + sbuf.substr(sel_start, sbuf.size()-1);
               sel_start--;
               if (caretx > 0) caretx--;
               else
               {
                   carety--;
                   caretx=sbuf.substr(0,sel_start-1).length();
               }
             } else { if (carety>0) carety--; sel_start = 0; };
            } else { if (carety>0) carety--; sel_start = 0; };
           } else
           if(i == 190) //delete
	       {
	        if ((sel_start < s.size()) && (s.size() > 0))
            {
              std::string sbuf = s;
              s = sbuf.substr(0,sel_start) + sbuf.substr(sel_start+1, sbuf.size());
            }
           } else
           if (i == 13)
           {
             std::string sbuf = s;
             s = sbuf.substr(0,sel_start) + '\n' + sbuf.substr(sel_start,sbuf.length());
             if (i != VK_SHIFT)
             {
              sel_start++;
              caretx=0;
              carety++;
              sel_length = 0;
              sel_index = sel_start;
             }
           }
           else
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
              caretx++;
              sel_length = 0;
              sel_index = sel_start;
             }
           }
           if (seltext.size()>0)
           {
             if ((i != VK_SHIFT)&&(i != VK_LEFT)&&(i != VK_RIGHT)&&(i != VK_UP)&&(i != VK_DOWN)&&(i != VK_HOME)&&(i != VK_END)&&(i != VK_RETURN))
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






TTextBox::TTextBox(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="textbox";
          visible = false;
          left=0;
          top=0;
          width=128;
          height=32;
          alphavalue = window->alphavalue;
          color = clWindow;
          caption="textbox";
          text="textbox";
          seltext="";
          sel_index = 0;
          sel_start = 0;
          sel_length = 0;
          charcase = ecNormal;
          maxlength = 0;
          caretx = 0;
          carety = 0;
          rowlength = 0;
          count = 0;
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
          align = alNone;
          render = rendertextbox;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          readonly = false;
          window->textboxes[window->numtextboxes] = this;
          window->numtextboxes++;
          window->numcontrols++;
          activetextedit = this;
          parent = Window;
}

TTextBox::~TTextBox()
{
  delete hscroll;
  delete vscroll;
}


void TTextBox::rendercontrol()
{
if (align==alClient)
{
  left = 3;
  top = 3;
  width = window->clientwidth-7;
  height = window->clientheight-5;   
}
if ((visible==true)&&(window->visible==true))
{
if (visible)
{
  if (activewindow!=window->windowid) focus = false;
  textinput();
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
if ((focused==true)&&(clicked==true)&&(textboxcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  textboxcontrolon = false;
}
} else focused = false;
}
}
if (visible==true) hscroll->rendercontrol();
if (visible==true) vscroll->rendercontrol();
instance = this;
window->textboxes[controlid] = dynamic_cast <TTextBox*>((TTextBox*)this);//this;
}
void TTextBox::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->textboxes[controlid] = this;
  }
}
void TTextBox::hide()
{
          visible = false;
          window->textboxes[controlid] = this;

}


void TTextBox::clear()
{
std::string s = "";
caretx = 0;
carety = 0;
sel_index = 0;
sel_start = 0;
sel_length = 0;
text = s;
seltext = s;
// if (onchange) onchange(this);
}

void TTextBox::selectall()
{
  caretx = 0;
  carety = 0;
  sel_index = 0;
  sel_start = 0;
  sel_length = text.length();
}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createtextbox(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int txtboxid = 0;
   txtboxid = windows[winid]->numtextboxes;
   TTextBox* textbox = new TTextBox(windows[winid]);
   textbox->alphavalue = 255;
   textbox->enabled = true;
   textbox->width=72;
   textbox->height=24;
   textbox->left=32;
   textbox->top=32;
   textbox->visible = false;
   return txtboxid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

