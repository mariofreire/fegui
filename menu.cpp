// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "menu.h" // class's header file
#include "mouse.h" // class's header file

TMenu *menues[256];

TMenu* systemmenu;
TMenu* editmenu;

int showmenu=-1;
int nummenues=0;

void show_menu(TMenu* menu);

int submenuleft[256],submenutop[256],submenuwidth[256],submenuheight[256];
int submenues=0;
int showsubmenu=-1;

void pushmenuitemindex();
void popmenuitemindex();

bool submenuitemclick(TMenuItem* item);

int submenuitemclickid = -1;

bool IsInAnyMenu(void)
{
     if (showmenu >= 0)
     {
		bool inmenu = menues[showmenu]->IsInMenu(menues[showmenu]);
        return inmenu;
     }
     if (showsubmenu >= 0)
     {
       if (getarea(submenuleft[showsubmenu],submenutop[showsubmenu],submenuwidth[showsubmenu],submenuheight[showsubmenu]))
       {
         return true;
       }
     }
     return false;
}

TMenuItem* TMenuItem::additem(char* caption)
{
items[numitems] = new TMenuItem();
int ni = numitems+1;
char newname[256];
sprintf(newname,"menuitem%i",ni);
items[numitems]->name = newname;
items[numitems]->caption = caption;
items[numitems]->id = -1;
numitems++;
return items[numitems-1];
}

void TMenuItem::additem(TMenuItem* item)
{
items[numitems] = item;
numitems++;
}

TMenuItem::TMenuItem()
{
name = "menuitem";
caption = "";
enabled = true;
itemindex = -1;
numitems = 0;
checked = false;
menuitemhighlight = false;
menuitemdown = false;
menuitemshow = -1;
menuitemctl = 0;
mindex = -1;
showing = false;
onclick = NULL;
onpopup = NULL;
onupdate = NULL;
onshow = NULL;
}

TMenuItem::~TMenuItem()
{
itemindex = -1;
numitems = 0;
enabled = false;
onclick = NULL;
onpopup = NULL;
onupdate = NULL;
onshow = NULL;
}

TMenuItems::TMenuItems()
{
name = "menuitems";
caption = "";
itemindex = -1;
numitems = 0;
id = -1;
onclick = NULL;
onpopup = NULL;
onupdate = NULL;
onshow = NULL;
}

TMenuItems::~TMenuItems()
{
itemindex = -1;
numitems = 0;
onclick = NULL;
onpopup = NULL;
onupdate = NULL;
onshow = NULL;
}

bool TMenu::IsInMenu(TWinControl* Window)
{
 if (showsubmenu >= 0)
 {
     int l = submenuleft[showsubmenu];
     int t = submenutop[showsubmenu];
     int w = submenuwidth[showsubmenu];
     int h = submenuheight[showsubmenu];
     if (((mousex>=(l))&&(mousey>=(t)))&&(mousex<=(l+w))&&(mousey<=(t+h)))
     {
       return true;
     }     
 }
 if (((mousex>=(Window->left))&&(mousey>=(Window->top)))&&(mousex<=(Window->left+Window->width))&&(mousey<=(Window->top+Window->height)))
 {    
   return true;
 }
 return false;
}

bool submenuitemclick(TMenuItem* item)
{
     if (item)
     {
      if (item->itemindex >= 0)
      {
       if (item->items[item->itemindex]->numitems > 0) 
       {
         if (item->items[item->itemindex]->itemindex >= 0) return submenuitemclick(item->items[item->itemindex]);
       }
	   if (item->items[item->itemindex]->onclick && item->items[item->itemindex]->enabled)
	   {
		submenuitemclickid = item->items[item->itemindex]->id;
		item->items[item->itemindex]->onclick(menues[showmenu]);
	   }
      }
     }
     return false;
}

bool menuclick = false;
void TMenu::rendercontrols()
{
setviewport(0,0,getscreenwidth(),getscreenheight());
menues[windowid] = this;
glPushMatrix();
if (visible)
{
 TWinControl::render(this);    
 hintwincontrol(this);
}
glPopMatrix();

if (visible)
{
 if (mouseb==0 && menuclick)
 {
  if (menu)
  {
  if (menu->itemindex >= 0)
  {
   if (IsInMenu(this))
   {
     if (menu)
     {
      if (menu->itemindex >= 0)
      {
	   if (menu->items[menu->itemindex]->onclick && menu->items[menu->itemindex]->enabled)
	   {
		   submenuitemclickid = menu->items[menu->itemindex]->id;
		   menu->items[menu->itemindex]->onclick(this);
	   }
      }
      submenuitemclick(menu->items[menu->itemindex]);
     }
   }
  if (menu->items[menu->itemindex]->enabled)
  {
    visible = false;
    menuclick = false;
    showmenu = -1;
  }
  }
  }
 }
 else if ((mouseb==1)&&(!(IsInMenu(this))))
 {
   visible = false;
   menuclick = false;
   showmenu = -1;
 }
}

}

void TMenu::click()
{
menuclick = true;
//mouseb = 0;
setviewport(0,0,getscreenwidth(),getscreenheight());
menues[windowid] = this;
glPushMatrix();
//if (visible)
{
 //TWinControl::render(this);    
 hintwincontrol(this);
}
glPopMatrix();
 if (mouseb==1 && menuclick)
 {
//  if (menu)
  {
  if (menu->itemindex >= 0)
  {
   if (IsInMenu(this))
   {
  //   if (menu)
     {
      if (menu->itemindex >= 0)
      {
	   if (menu->items[menu->itemindex]->onclick && menu->items[menu->itemindex]->enabled)
	   {
		 submenuitemclickid = menu->items[menu->itemindex]->id;
		 menu->items[menu->itemindex]->onclick(this);
	   }
      }
      submenuitemclick(menu->items[menu->itemindex]);
     }
   }
  if (menu->items[menu->itemindex]->enabled)
  {
//    visible = false;
    menuclick = false;
//    showmenu = -1;
  }
  }
  }
}
}

void TMenu::show()
{
 begindrawing();
 rendercontrols();
 enddrawing();
}

void show_menu(TMenu* menu)
{
  menu->visible = true;
  showmenu = menu->windowid;
}

bool mindexon = false;

void pushmenuitemindex()
{
  mindexon = true;
}

void popmenuitemindex()
{
  mindexon = false;
}

void rendermenuitem(TMenuItem* m,int alpha)
{
 int ebctl = 0;
 int l = submenuleft[submenues];
 int t = submenutop[submenues];
 int w = submenuwidth[submenues];
 int h = submenuheight[submenues];
 int nh = 0;
 int lastlen = 0;
 m->mindex = -1;
 showsubmenu = -1;
 {
 glEnable(GL_SCISSOR_TEST);
 glScissor(l-2,height-((t-2)+(h+2)+1),w+2,h+2+1); 
 bool vs = false;
 {
 if (m->numitems > 0)
 {
  {
   int nw = 0;
   if (m->numitems >= 0) lastlen = strlen(m->items[0]->caption);
   for (int i=0;i<m->numitems;i++)
   {
     //if (lastlen <= strlen(m->items[i]->caption)) submenuwidth = textwidth(m->items[i]->caption)+16+20;
     if (strlen(m->items[i]->caption)<4)
     {
      if (m->items[i]->numitems>=0) nw += 32*32;
     }
     nw += textwidth(m->items[i]->caption)*textwidth(m->items[i]->caption);
     nh += 16;
     lastlen = strlen(m->items[i]->caption);
     if (i >= m->numitems-1) vs = true;
   }
   submenuheight[submenues] = nh+8;
//   if (m->numitems == 1) submenuheight = 24;
//   if (m->numitems > 2) submenuheight -= 20;
   submenuwidth[submenues] = sqrt(nw)+32;
   if (m->numitems == 1)
   {
     submenuwidth[submenues] = textwidth(m->items[0]->caption)+32;
     submenuheight[submenues] = 24;
     if (m->items[0]->numitems>0) submenuwidth[submenues] = textwidth(m->items[0]->caption)+16+32;
   }
  }
  if (vs)
  {
  COLORREF colordisabled = clBtnShadow;
//  drawcontroledge(l,t,w,h-1,ebctl,alpha);
  drawcontroledgew(l,t-1,w,h,ebctl,alpha);
  if (submenues >= 0)
  {
   for (int xsmi=0;xsmi<=submenues;xsmi++)
   {
    int l = submenuleft[xsmi];
    int t = submenutop[xsmi];
    int w = submenuwidth[xsmi];
    int h = submenuheight[xsmi];
    if (getarea(l,t,w,h)) showsubmenu = xsmi;
   }
  }

  int ih = 0;
  {
   int ni=m->numitems;
   for (int i=0;i<ni;i++)
   {
      if (getarea(l+2,t+1+(i*16),w-4,15)) m->itemindex = i;
      else if (getarea(l+2,t+1,w-4,(15))) m->itemindex = 0;
  //    else m->itemindex = -1;
     glEnable(GL_SCISSOR_TEST);
     glScissor(w-1,h+2+1,l-2,height-((t-2)+(h+2)+1)); 
//     if (m->items[i]->caption.length()>0)
     {
     int ii=-1;
     if (m->itemindex>=0)
     {
       ii = m->itemindex;
       if (ii >= ni) ii = -1;
     }
 //    m->itemindex = ii;
      
      if ((ii>=0)&&(strcmp(m->items[ii]->caption,"-")!=0))
      {
       int ith = t+4+(ii*16)+16;
       if (ii == ni-1) ith++;
       COLORREF itemcolor = clHighlight;
       fillrect(l+1,t+1+(ii*16),l+2+w-5,ith,itemcolor,alpha);
      }
      COLORREF itemtextcolor = clBlack;
     // if (i == ii) itemtextcolor = clHighlightText;
      if (!m->items[i]->enabled) itemtextcolor = colordisabled;
      textattr(itemtextcolor,alpha,12,FW_NORMAL);
      if (ii == 0)
      {
       if (getarea(l+2,t+1,w-4,(16)))
       {
        COLORREF itemtextcolor = clBlack;
        if ((m->itemindex == 0)&&(strcmp(m->items[0]->caption,"-")!=0)) itemtextcolor = clHighlightText;
        if (!m->items[0]->enabled) itemtextcolor = colordisabled;
        textattr(itemtextcolor,alpha,12,FW_NORMAL);
        textout(l+4+20,t+3,m->items[0]->caption);
       }
      }

      itemtextcolor = clBlack;
      if ((i == ii)&&(strcmp(m->items[ii]->caption,"-")!=0)) itemtextcolor = clHighlightText;
      if (!m->items[i]->enabled) itemtextcolor = colordisabled;
      textattr(itemtextcolor,alpha,12,FW_NORMAL);
      if (strcmp(m->items[i]->caption,"-")==0)
      {
        drawline(l+2,t+3+ih+9,l+w-4,t+3+ih+9,clBtnHighlight,alpha);
        drawline(l+2,t+3+ih+8,l+w-4,t+3+ih+8,clBtnShadow,alpha);
      }
     }
     ih += 16;   
   }

   if (m->itemindex>=0)
   {
      if (m->items[m->itemindex]->numitems>0) submenues++;
   }
   
   m->mindex = -1;

   ih=0;
   for (int i=0;i<ni;i++)
   {
      if (getarea(l+2,t+1+(i*16),w-4,15)) 
      {
           m->itemindex = i;
           if (getarea(submenuleft[submenues],submenutop[submenues],submenuwidth[submenues],submenuheight[submenues]))
           {
             if (mindexon)
             {
               if (strcmp(m->items[i]->caption,"-")!=0) m->mindex = i;
               else m->mindex = -1;
             }
             else m->mindex = -1;
           } else m->mindex = -1;
      }
      else if (getarea(l+2,t+1,w-4,(15))) 
      {
           m->itemindex = 0;
           if (getarea(submenuleft[submenues],submenutop[submenues],submenuwidth[submenues],submenuheight[submenues]))
           {
             if (mindexon)
             {
               if (strcmp(m->items[i]->caption,"-")!=0) m->mindex = 0;
               else m->mindex = -1;
             }
             else m->mindex = -1;
           } else m->mindex = -1;
      }
  //    else m->itemindex = -1;

     glEnable(GL_SCISSOR_TEST);
     glScissor(w-1,h+2+1,l-2,height-((t-2)+(h+2)+1)); 
//     if (m->items[i]->caption.length()>0)
     {
     int ii=-1;
     if (m->itemindex>=0)
     {
       ii = m->itemindex;
       if (ii >= ni) ii = -1;
     }
 //    m->itemindex = ii;
      
      if ((ii>=0)&&(strcmp(m->items[ii]->caption,"-")!=0))
      {
       int ith = t+4+(ii*16)+16;
       if (ii == ni-1) ith++;
       COLORREF itemcolor = clHighlight;
    //   fillrect(l+1,t+1+(ii*16),l+2+w-5,ith,itemcolor,alpha);
      }
      COLORREF itemtextcolor = clBlack;
     // if (i == ii) itemtextcolor = clHighlightText;
      if (!m->items[i]->enabled) itemtextcolor = colordisabled;
      textattr(itemtextcolor,alpha,12,FW_NORMAL);
      if (ii == 0)
      {
       if (getarea(l+2,t+1,w-4,(16)))
       {
        COLORREF itemtextcolor = clBlack;
        if ((m->itemindex == 0)&&(strcmp(m->items[0]->caption,"-")!=0)) itemtextcolor = clHighlightText;
        if (!m->items[0]->enabled) itemtextcolor = colordisabled;
        textattr(itemtextcolor,alpha,12,FW_NORMAL);
        textout(l+4+20,t+3,m->items[0]->caption);
       }
      }

      itemtextcolor = clBlack;
      if ((i == ii)&&(strcmp(m->items[ii]->caption,"-")!=0)) itemtextcolor = clHighlightText;
      if (!m->items[i]->enabled) itemtextcolor = colordisabled;
      textattr(itemtextcolor,alpha,12,FW_NORMAL);
      if (strcmp(m->items[i]->caption,"-")==0)
      {
      }
      else 
      {
        if ((!m->items[i]->enabled)&&(i!=ii))
        {
          itemtextcolor = clBtnHighlight;
          textattr(itemtextcolor,alpha,12,FW_NORMAL);
          textout(l+4+20+1,t+3+ih+1,m->items[i]->caption);
          itemtextcolor = colordisabled;
          textattr(itemtextcolor,alpha,12,FW_NORMAL);
          textout(l+4+20,t+3+ih,m->items[i]->caption);
        }
        else
        {
             if (m->items[i]->enabled)
             {
               if (m->items[i]->numitems>0) drawimagemask(l+w-24,t+1+ih,rightarrowicon,alpha,itemtextcolor,true,clLime);
               if (m->items[i]->checked) drawimagemask(l+6,t+4+ih,checkedicon,alpha,itemtextcolor,true,clLime);
             }
             textout(l+4+20,t+3+ih,m->items[i]->caption);
        }
      }
     }
     ih += 16;   
   }
   for (int i=0;i<ni;i++)
   {
      if (getarea(l+2,t+1+(i*16),w-4,15)) m->itemindex = i;
      else if (getarea(l+2,t+1,w-4,(15))) m->itemindex = 0;
   }
   if (!IsInAnyMenu()) 
   {
    if (m->itemindex>=0)
    {
     if (!(m->items[m->itemindex]->numitems>0))
     {
       m->itemindex = -1;
//       m->mindex = -1;
     }
     else
     {
       if (m->items[m->itemindex]->itemindex<0) 
       {
         if (getarea(l-w+2,t+1,w-4,h))
         {
           m->itemindex = -1;     
//           m->mindex = -1;
         }
       }
     }
    }
   }
  }
 }
 }
//if (m->visible)
{
 if (m->itemindex>=0)
 {
   if (m->items[m->itemindex]->numitems>0)
   {
     submenuleft[submenues] = (l+w-6)+1;
     submenutop[submenues] = t+(m->itemindex*16);
     rendermenuitem(m->items[m->itemindex],alpha);
   }
 }
 if (mouseb==1)
 {
  // if (m->IsInMenu(m))
//   {
     if (m->itemindex>=0)
     {
       if (m->items[m->itemindex]->enabled)  menuclick = true;
     }
//   }
 }
}
}
glDisable(GL_SCISSOR_TEST);
}
}

void rendermenu(TWinControl* sender)
{
 TMenu* m = dynamic_cast <TMenu*>((TMenu*)sender);
 int ebctl = 0;
 int l = m->left;
 int t = m->top;
 int w = m->width;
 int h = m->height;
 int nh = 0;
 int lastlen = 0;
 if (m->visible)
 {
 glEnable(GL_SCISSOR_TEST);
 glScissor(l-2,height-((t-2)+(h+2)+1),w+2,h+2+1); 
 bool vs = false;
 if (m->menu)
 {
 if (m->menu->numitems > 0)
 {
  if (m->menu)
  {
   int nw = 0;
   if (m->menu->numitems >= 0) lastlen = strlen(m->menu->items[0]->caption);
   for (int i=0;i<m->menu->numitems;i++)
   {
     //if (lastlen <= strlen(m->menu->items[i]->caption)) sender->width = textwidth(m->menu->items[i]->caption)+16+20;
     nw += textwidth(m->menu->items[i]->caption)*textwidth(m->menu->items[i]->caption);
     nh += 16;
     lastlen = strlen(m->menu->items[i]->caption);
     if (i >= m->menu->numitems-1) vs = true;
   }
   sender->height = nh+8;
//   if (m->menu->numitems == 1) sender->height = 24;
//   if (m->menu->numitems > 2) sender->height -= 20;
   sender->width = sqrt(nw)+32;
   if (m->menu->numitems == 1)
   {
     sender->width = textwidth(m->menu->items[0]->caption)+32;
     sender->height = 24;
   }
  }
  if (vs)
  {
  COLORREF colordisabled = clBtnShadow;
//  drawcontroledgew(l,t+1,w,h-1,ebctl,sender->alphavalue);
  drawcontroledgew(l,t-1,w,h,ebctl,sender->alphavalue);

  int ih = 0;
  int niii=0;
  int iii=-1;
  if (m->menu)
  {
   int ni=m->menu->numitems;
 //  if ((m->menu->itemindex>=0)&&(ni>0))
   {
//    if (m->menu->items[m->menu->itemindex]->numitems>0)
    {
     int i=0;
     int niii0=0;
     while((i<ni)&&(niii0==0))
     {
        if (getarea(l+2,t+1+(i*16),w-4,15))
        {
       //   m->menu->itemindex = i;
          niii0=1;
        }
        else if (getarea(l+2,t+1,w-4,(15))) 
        {
       //   m->menu->itemindex = 0;
          niii0=1;
        }
        i++;
     }
    }
   }
   for (int i=0;i<ni;i++)
   {
   
     glEnable(GL_SCISSOR_TEST);
     glScissor(l-2,height-((t-2)+(h+2)+1),w-1,h+2+1); 
//     if (m->menu->items[i]->caption.length()>0)
     {
     int ii=-1;
     if (m->menu->itemindex>=0)
     {
       ii = m->menu->itemindex;
       if (ii >= ni) ii = -1;
     }

 //    m->menu->itemindex = ii;
      
      if ((ii>=0)&&(strcmp(m->menu->items[ii]->caption,"-")!=0))
      {
       int ith = t+4+(ii*16)+16;
       if (ii == ni-1) ith++;
       COLORREF itemcolor = clHighlight;
       fillrect(l+1,t+1+(ii*16),l+2+w-5,ith,itemcolor,sender->alphavalue);
      }
      COLORREF itemtextcolor = clBlack;
     // if (i == ii) itemtextcolor = clHighlightText;
      if (!m->menu->items[i]->enabled) itemtextcolor = colordisabled;
      textattr(itemtextcolor,sender->alphavalue,12,FW_NORMAL);
      if (ii == 0)
      {
       if (getarea(l+2,t+1,w-4,(16)))
       {
        COLORREF itemtextcolor = clBlack;
        if ((m->menu->itemindex == 0)&&(strcmp(m->menu->items[0]->caption,"-")!=0)) itemtextcolor = clHighlightText;
        if (!m->menu->items[0]->enabled) itemtextcolor = colordisabled;
        textattr(itemtextcolor,sender->alphavalue,12,FW_NORMAL);
        textout(l+4+20,t+3,m->menu->items[0]->caption);
       }
      }

      itemtextcolor = clBlack;
      if ((i == ii)&&(strcmp(m->menu->items[ii]->caption,"-")!=0)) itemtextcolor = clHighlightText;
      if (!m->menu->items[i]->enabled) itemtextcolor = colordisabled;
      textattr(itemtextcolor,sender->alphavalue,12,FW_NORMAL);
      if (strcmp(m->menu->items[i]->caption,"-")==0)
      {
        drawline(l+2,t+3+ih+9,l+w-4,t+3+ih+9,clBtnHighlight,m->alphavalue);
        drawline(l+2,t+3+ih+8,l+w-4,t+3+ih+8,clBtnShadow,m->alphavalue);
      }
     }
     ih += 16;   
   }
   submenues=-1;

   if (m->menu->itemindex>=0)
   {
      if (m->menu->items[m->menu->itemindex]->numitems>0) submenues++;
   }

   ih=0;
   for (int i=0;i<ni;i++)
   {
  //   int iii=0;
     
  //   iii = m->menu->itemindex;
   //  if (iii<=0) iii = 0;
   
     if (m->menu->itemindex>=0)
     {
    //  if (m->menu->items[m->menu->itemindex]->numitems>0) goto skipindex;
     }

      if (getarea(l+2,t+1+(i*16),w-4,15)) m->menu->itemindex = i;
      else if (getarea(l+2,t+1,w-4,(15))) m->menu->itemindex = 0;
    //  else m->menu->itemindex = -1;
      
   //  skipindex:
    // if (iii>=0) m->menu->itemindex = iii;
  //   if (m->menu->itemindex>=0) SetWindowText(hWnd,(m->menu->items[m->menu->itemindex]->caption));
     //else niii = 0;
     glEnable(GL_SCISSOR_TEST);
     glScissor(l-2,height-((t-2)+(h+2)+1),w-1,h+2+1); 
//     if (m->menu->items[i]->caption.length()>0)
     {
     int ii=-1;
     if (m->menu->itemindex>=0)
     {
       ii = m->menu->itemindex;
       if (ii >= ni) ii = -1;
     }

 //    m->menu->itemindex = ii;
      
      if ((ii>=0)&&(strcmp(m->menu->items[ii]->caption,"-")!=0))
      {
       int ith = t+4+(ii*16)+16;
       if (ii == ni-1) ith++;
       COLORREF itemcolor = clHighlight;
    //   fillrect(l+1,t+1+(ii*16),l+2+w-5,ith,itemcolor,sender->alphavalue);
      }
      COLORREF itemtextcolor = clBlack;
     // if (i == ii) itemtextcolor = clHighlightText;
      if (!m->menu->items[i]->enabled) itemtextcolor = colordisabled;
      textattr(itemtextcolor,sender->alphavalue,12,FW_NORMAL);
      if (ii == 0)
      {
       if (getarea(l+2,t+1,w-4,(16)))
       {
        COLORREF itemtextcolor = clBlack;
        if ((m->menu->itemindex == 0)&&(strcmp(m->menu->items[0]->caption,"-")!=0)) itemtextcolor = clHighlightText;
        if (!m->menu->items[0]->enabled) itemtextcolor = colordisabled;
        textattr(itemtextcolor,sender->alphavalue,12,FW_NORMAL);
        textout(l+4+20,t+3,m->menu->items[0]->caption);
       }
      }

      itemtextcolor = clBlack;
      if ((i == ii)&&(strcmp(m->menu->items[ii]->caption,"-")!=0)) itemtextcolor = clHighlightText;
      if (!m->menu->items[i]->enabled) itemtextcolor = colordisabled;
      textattr(itemtextcolor,sender->alphavalue,12,FW_NORMAL);
      if (strcmp(m->menu->items[i]->caption,"-")==0)
      {
      }
      else 
      {
        if ((!m->menu->items[i]->enabled)&&(i!=ii))
        {
          itemtextcolor = clBtnHighlight;
          textattr(itemtextcolor,sender->alphavalue,12,FW_NORMAL);
          textout(l+4+20+1,t+3+ih+1,m->menu->items[i]->caption);
          itemtextcolor = colordisabled;
          textattr(itemtextcolor,sender->alphavalue,12,FW_NORMAL);
          textout(l+4+20,t+3+ih,m->menu->items[i]->caption);
        }
        else
        {
             if (m->menu->items[i]->enabled)
             {
               if (m->menu->items[i]->numitems>0) drawimagemask(l+w-24,t+1+ih,rightarrowicon,sender->alphavalue,itemtextcolor,true,clLime);
               if (m->menu->items[i]->checked) drawimagemask(l+6,t+4+ih,checkedicon,sender->alphavalue,itemtextcolor,true,clLime);
             }
             textout(l+4+20,t+3+ih,m->menu->items[i]->caption);
        }
      }
     }
     ih += 16;   
   }
   for (int i=0;i<ni;i++)
   {
      if (getarea(l+2,t+1+(i*16),w-4,15)) m->menu->itemindex = i;
      else if (getarea(l+2,t+1,w-4,(15))) m->menu->itemindex = 0;
   }
   if (!IsInAnyMenu()) 
   {
    if (m->menu->itemindex>=0)
    {
     if (!(m->menu->items[m->menu->itemindex]->numitems>0)) m->menu->itemindex = -1;
     else
     {
       if (m->menu->items[m->menu->itemindex]->itemindex<0) 
       {
         if (getarea(l-w+2,t+1,w-4,h)) m->menu->itemindex = -1;     
       }
     }
    }
   }
  }
 }
 }
if (m->visible)
{
 if (m->menu->itemindex>=0)
 {
   if (m->menu->items[m->menu->itemindex]->numitems>0)
   {
     submenuleft[submenues] = (l+w-6)+1;
     submenutop[submenues] = t+(m->menu->itemindex*16);
     rendermenuitem(m->menu->items[m->menu->itemindex],sender->alphavalue);
   }
 }
 if (mouseb==1)
 {
  // if (m->IsInMenu(m))
//   {
     if (m->menu->itemindex>=0)
     {
       if (m->menu->items[m->menu->itemindex]->enabled)  menuclick = true;
     }
//   }
 }
}
}
glDisable(GL_SCISSOR_TEST);
}
}



TMenu::TMenu()
{
 left = 32;
 top = 64;
 width = 64;
 height = 24;
 alphavalue = 255;
 menu = new TMenuItems();
 showmenu = nummenues;
 windowid = nummenues;
 render = rendermenu;
 showing = false;
 visible = false;
 menues[nummenues] = this;
 nummenues++;
}

TMenu::~TMenu()
{
delete menu;
}
