// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "msgbox.h"


extern bool appinitialized;

extern char guipath[256];

void messageboxokclick(TControl* sender)
{
  sender->window->window->modalhalt = false;
  sender->window->visible = false;
  activewindow = sender->window->window->windowid;
  sender->window->window->messageboxresult = mrOk;
  sender->window->window->messageboxon = false;
  // deletewindow(sender->window->windowid);
}


void messageboxyesclick(TControl* sender)
{
  sender->window->window->modalhalt = false;
  sender->window->visible = false;
  activewindow = sender->window->window->windowid;
  sender->window->window->messageboxresult = mrYes;
  sender->window->window->messageboxon = false;
  // deletewindow(sender->window->windowid);
}


void messageboxnoclick(TControl* sender)
{
  sender->window->window->modalhalt = false;
  sender->window->visible = false;
  activewindow = sender->window->window->windowid;
  sender->window->window->messageboxresult = mrNo;
  sender->window->window->messageboxon = false;
  // deletewindow(sender->window->windowid);
}

void messageboxcancelclick(TControl* sender)
{
  sender->window->window->modalhalt = false;
  sender->window->visible = false;
  activewindow = sender->window->window->windowid;
  sender->window->window->messageboxresult = mrCancel;
  sender->window->window->messageboxon = false;
  // deletewindow(sender->window->windowid);
}

void messageboxallclick(TControl* sender)
{
  sender->window->window->modalhalt = false;
  sender->window->visible = false;
  activewindow = sender->window->window->windowid;
  sender->window->window->messageboxresult = mrAll;
  sender->window->window->messageboxon = false;
  // deletewindow(sender->window->windowid);
}

void messageboxignoreclick(TControl* sender)
{
  sender->window->window->modalhalt = false;
  sender->window->visible = false;
  activewindow = sender->window->window->windowid;
  sender->window->window->messageboxresult = mrIgnore;
  sender->window->window->messageboxon = false;
  // deletewindow(sender->window->windowid);
}

void messageboxabortclick(TControl* sender)
{
  sender->window->window->modalhalt = false;
  sender->window->visible = false;
  activewindow = sender->window->window->windowid;
  sender->window->window->messageboxresult = mrAbort;
  sender->window->window->messageboxon = false;
  // deletewindow(sender->window->windowid);
}

void messageboxretryclick(TControl* sender)
{
  sender->window->window->modalhalt = false;
  sender->window->visible = false;
  activewindow = sender->window->window->windowid;
  sender->window->window->messageboxresult = mrRetry;
  sender->window->window->messageboxon = false;
  // deletewindow(sender->window->windowid);
}


void messagebox(TWindow* handle,char* text,char *caption,int msgtype)
{
if (!handle) return;
if (strlen(text)>1024) return;
if (handle->messageboxon) return;
handle->messageboxresult = mrNone;
TWindow* msgwin = new TWindow();

int l=0;
int t=0;
int w=0;
int h=0;
int msgicon_on = 0;
switch (msgtype & MB_ICONMASK)
{
case MB_ICONWARNING:
case MB_ICONERROR:
case MB_ICONINFORMATION:
case MB_ICONQUESTION:
{
msgicon_on = 1;
break;
};
};

if (msgicon_on) w = textwidth(text)+96;
else w = textwidth(text)+32;
if (msgicon_on) h = 116;
else h = 90;
int cx=0;
int i=0,len=0;
int n=0;
len = strlen(text);
msgwin->window = handle;
handle->modalhalt = true;
char stext[768][768];
for (i=0;i<len;i++)
{
  if (text[i]=='\n')
  {
    n++;
    cx=0;
  }
  else 
  {
    stext[n][cx]=text[i];
    cx++;
  }
}

int minw=0,maxw=0;
for (i=0;i<=n;i++)
{
 int tw = textwidth(stext[i]);
 if (minw == 0) minw =  99999999;
 if (maxw == 0) maxw = -99999999;
 if (tw < minw ) minw = tw;
 if (tw > maxw ) maxw = tw;
}

if ((n==0)&&(msgicon_on)) maxw = textwidth(text)+48;

//SetWindowText(hWnd,stext[3]);

if ((n>0)&&(msgicon_on))
{
         h += (n-1)*13;
         
         if (n>1)
         {
           w = textwidth(text)/n;
           if (w<textwidth(text)/1.5)
           {
             w = (maxw);//w += 32;
             w += 80;
           }
           else w += 80;
         }
         else
         {
           w = maxw;
           w += 80;
         }
} else
{
       w = maxw+32;
       h += (n)*13;
}

if (w<96) w = 96;

msgwin->left = ((getscreenwidth()-w)/2);
msgwin->top = ((getscreenheight()-h)/2);
msgwin->width = w;
msgwin->height = h;
msgwin->borderstyle = bsDialog;
msgwin->caption = caption;
msgwin->visible = false;

l = msgwin->left;
t = msgwin->top;
w = msgwin->width;
h = msgwin->height;

switch (msgtype & MB_TYPEMASK)
{
case MB_OK:
{
TButton *okbtn = new TButton(msgwin);
okbtn->width = 64;
okbtn->height = 21;
okbtn->left = ((w-okbtn->width)/2);
okbtn->top = ((h-okbtn->height)-38);
okbtn->caption = "OK";
okbtn->onclick = messageboxokclick;
okbtn->visible = true;
break;
};
case MB_YESNO:
{
TButton *yesbtn = new TButton(msgwin);
yesbtn->width = 64;
yesbtn->height = 21;
yesbtn->left = ((w-(yesbtn->width+75))/2);
yesbtn->top = ((h-yesbtn->height)-38);
yesbtn->caption = "Yes";
yesbtn->onclick = messageboxyesclick;
yesbtn->visible = true;

TButton *nobtn = new TButton(msgwin);
nobtn->width = 64;
nobtn->height = 21;
nobtn->left = ((w-(nobtn->width-75))/2);
nobtn->top = ((h-nobtn->height)-38);
nobtn->caption = "No";
nobtn->onclick = messageboxnoclick;
nobtn->visible = true;
break;
};
case MB_YESNOCANCEL:
{
TButton *yesbtn = new TButton(msgwin);
yesbtn->width = 64;
yesbtn->height = 21;
yesbtn->left = ((w-(yesbtn->width+150))/2);
yesbtn->top = ((h-yesbtn->height)-38);
yesbtn->caption = "Yes";
yesbtn->onclick = messageboxyesclick;
yesbtn->visible = true;

TButton *nobtn = new TButton(msgwin);
nobtn->width = 64;
nobtn->height = 21;
nobtn->left = ((w-(nobtn->width))/2);
nobtn->top = ((h-nobtn->height)-38);
nobtn->caption = "No";
nobtn->onclick = messageboxnoclick;
nobtn->visible = true;

TButton *cancelbtn = new TButton(msgwin);
cancelbtn->width = 64;
cancelbtn->height = 21;
cancelbtn->left = ((w-(cancelbtn->width-150))/2);
cancelbtn->top = ((h-cancelbtn->height)-38);
cancelbtn->caption = "Cancel";
cancelbtn->onclick = messageboxcancelclick;
cancelbtn->visible = true;

break;
};
case MB_OKCANCEL:
{
TButton *okbtn = new TButton(msgwin);
okbtn->width = 64;
okbtn->height = 21;
okbtn->left = ((w-(okbtn->width+75))/2);
okbtn->top = ((h-okbtn->height)-38);
okbtn->caption = "OK";
okbtn->onclick = messageboxokclick;
okbtn->visible = true;

TButton *cancelbtn = new TButton(msgwin);
cancelbtn->width = 64;
cancelbtn->height = 21;
cancelbtn->left = ((w-(cancelbtn->width-75))/2);
cancelbtn->top = ((h-cancelbtn->height)-38);
cancelbtn->caption = "Cancel";
cancelbtn->onclick = messageboxcancelclick;
cancelbtn->visible = true;
break;
};
case MB_ABORTRETRYIGNORE:
{
TButton *abortbtn = new TButton(msgwin);
abortbtn->width = 64;
abortbtn->height = 21;
abortbtn->left = ((w-(abortbtn->width+150))/2);
abortbtn->top = ((h-abortbtn->height)-38);
abortbtn->caption = "Abort";
abortbtn->onclick = messageboxabortclick;
abortbtn->visible = true;

TButton *retrybtn = new TButton(msgwin);
retrybtn->width = 64;
retrybtn->height = 21;
retrybtn->left = ((w-(retrybtn->width))/2);
retrybtn->top = ((h-retrybtn->height)-38);
retrybtn->caption = "Retry";
retrybtn->onclick = messageboxretryclick;
retrybtn->visible = true;

TButton *ignorebtn = new TButton(msgwin);
ignorebtn->width = 64;
ignorebtn->height = 21;
ignorebtn->left = ((w-(ignorebtn->width-150))/2);
ignorebtn->top = ((h-ignorebtn->height)-38);
ignorebtn->caption = "Ignore";
ignorebtn->onclick = messageboxignoreclick;
ignorebtn->visible = true;

break;
};
};

TLabel* textlabel = new TLabel(msgwin);
textlabel->width = textwidth(text);
textlabel->height = 64;
textlabel->left = 64;
if (msgicon_on) textlabel->top = 16;
else textlabel->top = 8;
textlabel->caption = text;
textlabel->visible = true;

if (msgicon_on)
{
TImage* msgimg = new TImage(msgwin);
msgimg->left = 16;
msgimg->top = 4;
msgimg->width = 36;
msgimg->height = 36;
msgimg->picture->textured = true;
msgimg->picture->transparentcolor = clBlue;
msgimg->picture->transparent = true;
msgimg->visible = false;
switch (msgtype & MB_ICONMASK)
{
case MB_ICONWARNING:
{
 msgimg->picture->load(filenamefrompath(guipath,"mfx_w.bmp"));
 break;
};
case MB_ICONERROR:
{
 msgimg->picture->load(filenamefrompath(guipath,"mfx_e.bmp"));
 break;
};
case MB_ICONINFORMATION:
{
 msgimg->picture->load(filenamefrompath(guipath,"mfx_i.bmp"));
 break;
};
case MB_ICONQUESTION:
{
 msgimg->picture->load(filenamefrompath(guipath,"mfx_q.bmp"));
 break;
};
};
msgimg->center = true;
msgimg->visible = true;
} else
{
       if (n>0) textlabel->left = ((w-maxw)/2);
       else textlabel->left = ((w-textlabel->width)/2);
}
msgwin->visible = true;
activewindow = msgwin->windowid;
handle->messageboxon = true;
return;
}

void fegui_messagebox(char* text,char *caption,int msgtype)
{
  if (numwindows > 0)
  {
   if (appinitialized) messagebox(windows[0],text,caption,msgtype);
  }
}


