// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "listbox.h" // class's header file

bool listboxcontrolon = false;
void renderlistbox(TControl *sender)
{
TListBox* listbox = dynamic_cast <TListBox*>((TListBox*)sender);
 bool onctrl = sender->IsInControl(sender);
 int bctl = 1;
 int wcaph = (sender->window->height-sender->window->clientheight);
// if (sender->window->borderstyle != bsNone) wcaph -= 3;

 bool isinwin = false;
  if (windows[activewindow]!=sender->window)
  {
   if (sender->window->IsInWindow(windows[activewindow]))
   {
     isinwin = false;
   } else isinwin = true;
  } else isinwin = true;
  
  int alphacontrol = blendto(sender->window->alphavalue,sender->alphavalue);
  
 if (!sender->visible) listbox->scroll->visible = false;
 if (!sender->window->visible) listbox->scroll->visible = false;
 if (sender->window->windowstate == wsMinimized) listbox->scroll->visible = false;
 
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
          
 if (sender->flat) bctl = 7;
 else bctl = 1;

 if (mouseb==1)
 {
  if (windows[activewindow]!=sender->window) sender->focused = false;
 }
 
 if (mouseb==0)
 {
  if (sender->IsInControl(sender)==true)
  {
      if ((listboxcontrolon == true)&&(sender->focus))
      {   
         if (onctrl && isinwin)
         {
           if (sender->onclick != NULL) 
           {
            sender->onclick(sender);
            sender->clicked = false;
            listboxcontrolon = false;
           }
           else
           {
            sender->clicked = false;
            listboxcontrolon = false;
           }
         }
      }
  } else
  {
 //   if (sender->IsInControl(sender)==false) listbox->checked = chk;
  }
 }
 if ((mouseb==1)&&(isinwin))
 {
  for (int i=0;i<sender->window->numcomboboxes;i++) sender->window->comboboxes[i]->focused = false;
  if (sender->IsInControl(sender)==true)
  {
      for (int i=0;i<sender->window->numlistboxes;i++) sender->window->listboxes[i]->focused = false;
      sender->clicked = true;     
      if (isinwin) sender->focused = true;
      if ((sender->flat==true)&&(isinwin)) bctl = 1;
  } else
  { 
    if (listboxcontrolon) sender->focused = false;
    sender->clicked = true;     
  }
 } else
 {
   sender->clicked = false;
   if ((sender->IsInControl(sender)==true)&&(isinwin)) bctl = 1;
 }

if (listbox->borderstyle == bsSingle) drawcontroledge(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,sender->width,sender->height,bctl,alphacontrol);

COLORREF bkcolor = clWhite;


 fillrect(((sender->window->left+sender->left)+1),((sender->window->top+wcaph+sender->top+2)+2),((sender->window->left+sender->left+sender->width)-2),((sender->window->top+wcaph+sender->top+2+sender->height)-2),bkcolor,alphacontrol);

//if (listbox->checked) drawimage(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,checkedicon,sender->alphavalue,true,clLime);
if (windows[activewindow]==sender->window)
{
if (sender->window->IsInWindow(windows[activewindow]))
if (mouseb==1) 
{
// if (sender->IsInControl(sender)==true) drawimagemask(sender->window->left+sender->left,sender->window->top+wcaph+sender->top+2,checkedicon,sender->alphavalue,clGray,true,clLime);
} else listbox->focus = false;
} else listbox->focus = false;

if (listbox->flat)
{
if (sender->IsInControl(sender) && (isinwin)) listbox->scroll->flat = false;
else listbox->scroll->flat = true;
} else listbox->scroll->flat = false;

listbox->scroll->kind = sbVertical;
listbox->scroll->showborder = false;
listbox->scroll->fastchange = true;
listbox->scroll->width = 20;
listbox->scroll->height = listbox->height-3;
listbox->scroll->left = (listbox->left+(listbox->width-4))-18;
listbox->scroll->top = listbox->top+3;
listbox->scroll->min = 0;
listbox->scroll->max = listbox->numitems;
listbox->scroll->smallchange = 1;

int itemx = sender->window->left+sender->left+4;
int itemy = sender->window->top+wcaph+sender->top+1;
int itemw = sender->width-4;
int itemh = listbox->itemheight;

listbox->scroll->visible = false;

int maxitems = 0;

for (int i=0;i<listbox->numitems;i++)
{
 itemx = sender->window->left+sender->left+4;
 itemw = sender->width-4;
 itemh = listbox->itemheight;
 if (itemy >= (sender->window->top+wcaph+sender->top+1+listbox->height-listbox->itemheight)-1)
 {
   if (listbox->window->windowstate != wsMinimized) listbox->scroll->visible = true;
 } else maxitems++;
 itemy += listbox->itemheight;
}

itemx = sender->window->left+sender->left+4;
itemy = sender->window->top+wcaph+sender->top+1;
itemw = sender->width-4;
itemh = listbox->itemheight;

if ((sender->focused) && (windows[activewindow]==sender->window))
{
  if (keys[VK_HOME])
  {
    if (listbox->itemindex>0)
    {
      listbox->itemindex = 0;
      listbox->scroll->position = listbox->itemindex;
    }
    keys[VK_HOME] = 0;
  }
  if (keys[VK_END])
  {
    if (listbox->itemindex<listbox->numitems-1)
    {
      listbox->itemindex = listbox->numitems-1;
      listbox->scroll->position = listbox->itemindex;
    }
    keys[VK_END] = 0;
  }
  if (keys[VK_PRIOR])
  {
    if (listbox->itemindex>0)
    {
      listbox->itemindex-=((maxitems));
      if (listbox->itemindex<0) listbox->itemindex = 0;
      listbox->scroll->position = listbox->itemindex;
    }
    keys[VK_PRIOR] = 0;
  }
  if (keys[VK_NEXT])
  {
    if (listbox->itemindex<listbox->numitems-1)
    {
      listbox->itemindex+=((maxitems));
      if (listbox->itemindex>listbox->numitems-1) listbox->itemindex = listbox->numitems-1;
      listbox->scroll->position = listbox->itemindex;
    }
    keys[VK_NEXT] = 0;
  }
  if (keys[VK_UP])
  {
    if (listbox->itemindex>0)
    {
      listbox->itemindex--;
      listbox->scroll->position = listbox->itemindex;
    }
    keys[VK_UP] = 0;
  }
  if (keys[VK_DOWN])
  {
    if (listbox->itemindex<listbox->numitems-1)
    {
      listbox->itemindex++;
      listbox->scroll->position = listbox->itemindex;
    }
    keys[VK_DOWN] = 0;
  }
}

int startindex = (listbox->scroll->position-maxitems);
if (startindex<0) startindex = 0;
if (startindex>=listbox->numitems) startindex = listbox->numitems-1;

for (int i=startindex;i<listbox->numitems;i++)
{
 itemx = sender->window->left+sender->left+4;
 itemw = sender->width-4;
 itemh = listbox->itemheight;

 if (listbox->scroll->visible)
 {
   // verticalscroll
   itemw = ((sender->width-4)-(listbox->scroll->width));
 }
 if (mouseb)
 {
   if (getarea(itemx-3,itemy+1,itemw-2,itemh-1) && (isinwin)) listbox->itemindex = i;
 }
 if (itemy >= (sender->window->top+wcaph+sender->top+1+listbox->height-listbox->itemheight)-1)
 {
   itemh-=2;
 }
 if (itemy < (sender->window->top+wcaph+sender->top+1+listbox->height-listbox->itemheight))
 {
  if (listbox->itemindex == i)
  {
   fillrect(itemx-3,itemy+3,itemx+itemw-2,itemy+itemh+2,clHighlight,alphacontrol);
   if (sender->focused) rectangledotted(itemx-2,itemy+3,itemx+itemw-2,itemy+itemh+1,clYellow,alphacontrol);
   textattr(clHighlightText,alphacontrol,12,FW_NORMAL);
  } else textattr(clBlack,alphacontrol,12,FW_NORMAL);
  textout(itemx,itemy+((listbox->itemheight-12)/2),(char*)listbox->items[i].c_str());
 }
 itemy += listbox->itemheight;
}

glDisable(GL_SCISSOR_TEST);
}

}

TListBox::TListBox(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="listbox";
          visible = false;
          left=0;
          top=0;
          width=121;
          height=97;
          alphavalue = window->alphavalue;
          color = clWindow;
          caption="listbox";
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
          render = renderlistbox;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->listboxes[window->numlistboxes] = this;
          window->numlistboxes++;
          window->numcontrols++;
}

TListBox::~TListBox()
{
  delete scroll;
}

void TListBox::additem(char* name)
{
     items[numitems] = name;
     numitems++;
}

void TListBox::rendercontrol()
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
  if (IsInControl(this)==true)
  {
    focused = true;  
    
  } //else focused = false;
//}
} //else focused = false;

if (mouseb==1)
{
  if (IsInControl(this)==true)
  {
    focus = true;  
  } else focus = false;
  if (focus==true)
  {
    clicked = true;
  }
}
if ((focus==true)&&(focused==true)&&(clicked==true)&&(listboxcontrolon==true))
{
if (IsInControl(this)==true)
{    
//  if (onclick != NULL) onclick(this);
  listboxcontrolon = false;
  clicked = false;
  listboxcontrolon = false;
}
} //else focused = false;
}
}
scroll->rendercontrol();
instance = this;
window->listboxes[controlid] = this;
}
void TListBox::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->listboxes[controlid] = this;
  }
}
void TListBox::hide()
{
          visible = false;
          window->listboxes[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createlistbox(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int lboxid = 0;
   lboxid = windows[winid]->numlistboxes;
   TListBox* listbox = new TListBox(windows[winid]);
   listbox->alphavalue = 255;
   listbox->enabled = true;
   listbox->width=72;
   listbox->height=24;
   listbox->left=32;
   listbox->top=32;
   listbox->visible = false;
   return lboxid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

