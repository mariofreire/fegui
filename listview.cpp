// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "listview.h" // class's header file




TListItem::TListItem()
{
caption = "";
imageindex = 0;
stateindex = -1;
numsubitems = 0;
for (int i=0;i<256;i++) subitems[i] = "";
}

TListItem::TListItem(char* caption)
{
this->caption = "";
this->imageindex = 0;
this->stateindex = -1;
this->numsubitems = 0;
for (int i=0;i<256;i++) this->subitems[i] = "";
}

TListItem::~TListItem()
{
}


TListItems::TListItems()
{
numitems = 0;
itemindex = -1;
}

TListItems::~TListItems()
{
}

TListItem* TListItems::additem()
{
items[numitems] = new TListItem();
TListItem* item = items[numitems];
numitems++;
return item;
}

TListItem* TListItems::additem(char* caption)
{
items[numitems] = new TListItem();
items[numitems]->caption = caption;
TListItem* item = items[numitems];
numitems++;
return item;
}

void TListItems::additem(TListItem* item)
{
items[numitems] = item;
numitems++;
}





TListColumn::TListColumn()
{
enabled = true;
text = "";
width = 64;
}

TListColumn::~TListColumn()
{
}


TListColumns::TListColumns()
{
numitems = 0;
}

TListColumns::~TListColumns()
{
}

void TListColumns::additem(char* text)
{
items[numitems] = new TListColumn();
items[numitems]->text = text;
numitems++;
}

void TListColumns::additem(TListColumn* item)
{
items[numitems] = item;
numitems++;
}


bool listviewcontrolon = false;
void renderlistview(TControl *sender)
{
    TListView* listview = dynamic_cast <TListView*>((TListView*)sender);
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
           if (listviewcontrolon) sender->clicked = true;
           sender->window->activecontrol = sender->controlid;
         } else 
         {
           listviewcontrolon = false;
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
       
       int bctl = 1;
       if (!listview->IsInControl(listview)) bctl = 7;

       drawcontroledge(l,t,w,h,bctl,a);
       fillrect(l+1,t+2,l+w-2,t+h-2,listview->color,a);
       
       int x = l+8;
       int y = t+8;
       for (int i=0;i<listview->items->numitems;i++)
       {       
         int xw = textwidth(listview->items->items[i]->caption)+8;
         int hasicon = 0;
         if (listview->viewstyle == vsIcon)
         {
           if (listview->largeimages != NULL)
           {
             hasicon = 1;
           }
         }
         else
         {
           if (listview->smallimages != NULL)
           {
             hasicon = 1;
           }
         }
         
         if (x >= ((l+w)-8))
         {
           y += 32+16;
           x = l+8;
         }
/*
         if (y >= ((t+h)-8))
         {
           x = l+8;
           y = t+8;
         }
*/
         int ix = 0;
         int iy = 0;
         
         int imgidx = listview->items->items[i]->imageindex;
         
         if (hasicon && (imgidx >= 0))
         {
           if (listview->viewstyle == vsIcon) iy += listview->largeimages->images[imgidx]->canvas->height;
           else ix += listview->smallimages->images[imgidx]->canvas->width;
         }
         
         int cx = (x+ix)-2;
         int cy = y+iy+8;
         int cw = x+xw-6;
         int ch = y+iy+24;
         int iw = 0;
         int ih = 0;
         
         if (hasicon && (imgidx >= 0))
         {
           if (listview->viewstyle == vsIcon)
           {
             iw = listview->largeimages->images[imgidx]->canvas->width;
             ih = listview->largeimages->images[imgidx]->canvas->height;
           }
           else 
           {
             iw = listview->smallimages->images[imgidx]->canvas->width;
             ih = listview->smallimages->images[imgidx]->canvas->height;
           }
         }
         
         if (mouseb==1)
         {
           if (!getarea(cx,(cy-ih)-8,xw-6,20+ih)) listview->items->itemindex = -1;
         }
         x += textwidth(listview->items->items[i]->caption)+8;
       }
       x = l+8+(listview->largeimages->images[0]->canvas->width/2);
       for (int i=0;i<listview->items->numitems;i++)
       {       
         int xw = textwidth(listview->items->items[i]->caption)+8;
         int hasicon = 0;
         if (listview->viewstyle == vsIcon)
         {
           if (listview->largeimages != NULL)
           {
             hasicon = 1;
           }
         }
         else
         {
           if (listview->smallimages != NULL)
           {
             hasicon = 1;
           }
         }
         
         if (x >= ((l+w)-8))
         {
           y += 32+16;
           x = l+8;
         }
/*
         if (y >= ((t+h)-8))
         {
           x = l+8;
           y = t+8;
         }
*/
         int ix = 0;
         int iy = 0;
         
         int imgidx = listview->items->items[i]->imageindex;
         
         if (hasicon && (imgidx >= 0))
         {
           if (listview->viewstyle == vsIcon) iy += listview->largeimages->images[imgidx]->canvas->height;
           else ix += listview->smallimages->images[imgidx]->canvas->width;
         }
         
         int cx = (x+ix)-2;
         int cy = y+iy+8;
         int cw = x+xw-6;
         int ch = y+iy+24;
         int sel = 0;
         int iw = 0;
         int ih = 0;

         int xxw = textwidth(listview->items->items[i]->caption);
         int xiw = listview->largeimages->images[imgidx]->canvas->width;
         if (xxw > xiw) xxw -= xiw-2;
         else xxw += xiw;

         if (hasicon && (imgidx >= 0))
         {
           if (listview->viewstyle == vsIcon)
           {
             iw = listview->largeimages->images[imgidx]->canvas->width;
             ih = listview->largeimages->images[imgidx]->canvas->height;
             drawimage32(cx+((xxw)/2),(cy-iy)-8,iw,ih,GL_RGB,listview->largeimages->images[imgidx]->canvas->pixels,a,listview->largeimages->images[imgidx]->transparent,listview->largeimages->images[imgidx]->transparentcolor);
             if (sel) drawimagemask32(cx+((xxw)/2),(cy-iy)-8,iw,ih,GL_RGB,listview->largeimages->images[imgidx]->canvas->pixels,(a/2),clHighlight,listview->largeimages->images[imgidx]->transparent,listview->largeimages->images[imgidx]->transparentcolor);
           }
           else 
           {
             iw = listview->smallimages->images[imgidx]->canvas->width;
             ih = listview->smallimages->images[imgidx]->canvas->height;
             drawimage32(cx-ix,cy,iw,ih,GL_RGB,listview->smallimages->images[imgidx]->canvas->pixels,a,listview->smallimages->images[imgidx]->transparent,listview->smallimages->images[imgidx]->transparentcolor);
           }
         }
         
         if (mouseb==1)
         {
           if (getarea(cx,(cy-ih)-8,xw-6,20+ih)) listview->items->itemindex = i;
         }
         
         if (i == listview->items->itemindex) sel = 1;

         if (hasicon && (imgidx >= 0))
         {
           if (listview->viewstyle == vsIcon)
           {
             int iw = listview->largeimages->images[imgidx]->canvas->width;
             int ih = listview->largeimages->images[imgidx]->canvas->height;
             drawimage32(cx+((xxw)/2),(cy-iy)-8,iw,ih,GL_RGB,listview->largeimages->images[imgidx]->canvas->pixels,a,listview->largeimages->images[imgidx]->transparent,listview->largeimages->images[imgidx]->transparentcolor);
             if (sel) drawimagemask32(cx+((xxw)/2),(cy-iy)-8,iw,ih,GL_RGB,listview->largeimages->images[imgidx]->canvas->pixels,(a/2),clHighlight,listview->largeimages->images[imgidx]->transparent,listview->largeimages->images[imgidx]->transparentcolor);
           }
           else 
           {
             int iw = listview->smallimages->images[imgidx]->canvas->width;
             int ih = listview->smallimages->images[imgidx]->canvas->height;
             drawimage32(cx-ix,cy,iw,ih,GL_RGB,listview->smallimages->images[imgidx]->canvas->pixels,a,listview->smallimages->images[imgidx]->transparent,listview->smallimages->images[imgidx]->transparentcolor);
           }
         }

         COLORREF itemtextcolor = clBlack;
         if (sel)
         {
           itemtextcolor = clHighlightText;
           fillrect(cx,cy,cw,ch,clHighlight,a);
           rectangledotted(cx+1,cy,cw,ch-1,clYellow,a);
         }
         textattr(itemtextcolor,a,12,FW_NORMAL);
         textout(x+ix,y+iy+8,listview->items->items[i]->caption);
         x += textwidth(listview->items->items[i]->caption)+(listview->largeimages->images[imgidx]->canvas->width/2);
       }

       glDisable(GL_SCISSOR_TEST);
    }
}

TListView::TListView(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="listview";
          visible = false;
          left=0;
          top=0;
          width=64;
          height=128;
          parent = window;
          alphavalue = window->alphavalue;
          color = clWindow;
          caption="listview";
          autoarrange = false;
          columnclick = true;
          gridlines = false;
          hideselection = true;
          hottrack = false;
          multiselect = false;
          readonly = false;
          rowselect = false;
          showcolumnheaders = true;
          showworkareas = true;
          wraptext = false;
          hovertime = -1;
          sorttype = stBoth;
          viewstyle = vsIcon;
          smallimages = NULL;
          largeimages = NULL;
          stateimages = NULL;
          items = new TListItems();
          render = renderlistview;
          handleid = window->numlistviews;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->listviews[window->numlistviews] = this;
          window->numlistviews++;
          window->numcontrols++;
}

TListView::~TListView()
{
  delete items;
}


void TListView::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(listviewcontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) listviewcontrolon = false;
}
} else focused = false;
}
}
instance = this;
window->listviews[handleid] = this;
}
void TListView::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->listviews[handleid] = this;
  }
}
void TListView::hide()
{
          visible = false;
          window->listviews[handleid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createlistview(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int lstvwid = 0;
   lstvwid = windows[winid]->numlistviews;
   TListView* listview = new TListView(windows[winid]);
   listview->alphavalue = 255;
   listview->enabled = true;
   listview->width=72;
   listview->height=24;
   listview->left=32;
   listview->top=32;
   listview->visible = false;
   return lstvwid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

