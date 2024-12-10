// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "tooltip.h"
#include "menu.h"
#include "mouse.h"
#include "blend.h"
#include "screen.h"


bool tooltip_control = false;
bool tooltip_fadeout = false;
bool tooltip_incontrol = false;
int tooltip_fadealpha=0;
int tooltip_alphavalue=200;
int tooltip_x=0,tooltip_y=0;
char *tooltip = "";
bool tooltip_visible = false;
bool tooltip_showing = false;
void settooltipalpha(int alphavalue);
void resettooltip(void);
void showtooltip(int x,int y,const char* text);
void showtooltip(const char* text);
void showtooltips(void);


void settooltipalpha(int alphavalue)
{
 tooltip_alphavalue = alphavalue;
}

void showtooltip(int x,int y,const char* text)
{
 int l=0,t=0,w=0,h=0;
 int alphav=tooltip_fadealpha;
 
     l = x;
     t = y;
     w = 16;
     h = 16;

   std::string tsline[1024];
   int tslinecnt=0;
   int tslinepos=0;
   char *tslinec = (char*)text;
     
     for (int i=0;i<strlen(text);i++)
     {
         if (tslinec[i] == '\n')
         {
           tslinecnt++;
           tsline[tslinecnt] = tslinec[i];
           tslinepos=0;
         }
         else
         {
           tsline[tslinecnt] = tsline[tslinecnt] + tslinec[i];
           tslinepos++;
         }
     }
     tslinecnt++;

     int hcnt = 0;
     int wcnt = 0;
     for (int i=0;i<tslinecnt;i++)
     {
         int tw = textwidth((char*)tsline[i].c_str());
         wcnt += tw*tw;
         hcnt += 16;
     }

   w = sqrt(wcnt)+8;
   h = hcnt+4;

   int shadowlength = 2;

   fillrect((l+1)+shadowlength,(t+1)+shadowlength,l+(w+shadowlength)-1,t+1+(h+shadowlength)-1,clBlack,alphav/4);
   glEnable(GL_SCISSOR_TEST);
   glScissor(l,height-(t+h),w,h+1);
   fillrect(l+1,t+1,l+w-1,t+h-1,clInfo,alphav);

   rectangle(l+1,t+1,l+w-1,t+h-1,clBlack,alphav);

   textattr(clInfoText,alphav,12,FW_NORMAL);
   std::string slinecurrent;
   std::string sline[1024];
   int slinelastnl=0;
   int slinetcnt=0;
   int slinenlcnt=0;
   int slinecnt=0;
   int slinepos=0;
   char *slinec = (char*)text;
   bool ww = false;
     
     for (int i=0;i<strlen(text);i++)
     {
         if (slinec[i] == '\n')
         {
           slinecnt++;
           sline[slinecnt] = slinec[i];
           slinepos=0;
         }
         else
         {
           sline[slinecnt] = sline[slinecnt] + slinec[i];
           slinepos++;
         }
     }
     slinecnt++;
     
     int slinehcnt = 0;
     int slinewcnt = 0;
     for (int i=0;i<slinecnt;i++)
     {
         textout(l+3,t+2+(i*14),(char*)sline[i].c_str());
         int tw = textwidth((char*)sline[i].c_str());
         slinewcnt += tw*tw;
         slinehcnt += 16;
     }
     w = sqrt(slinewcnt)+4;
     h = slinehcnt+4;
     int tooltipalphavalue = 0;
     if (tooltip_control)
     {
      tooltipalphavalue = tooltip_alphavalue;
      if (tooltipalphavalue <= 0) tooltipalphavalue = 0;
      if (tooltipalphavalue >= 255) tooltipalphavalue = 255;
      if (!tooltip_fadeout)
      {
        if (tooltip_fadealpha < tooltip_alphavalue) tooltip_fadealpha += (int)((float)sqrt(tooltipalphavalue)*1.5);
        if (tooltip_fadealpha >= tooltip_alphavalue) tooltip_fadealpha = tooltip_alphavalue;
      }
     }
     else tooltip_fadealpha = tooltip_alphavalue;
   glDisable(GL_SCISSOR_TEST);
   if (tooltip_control)
   {
    if (tooltip_fadeout)
    {
        if (tooltip_fadealpha > 0) 
        {
          tooltip_visible = true;
          if (tooltip_fadealpha > 0) tooltip_fadealpha -= (int)((float)sqrt(tooltipalphavalue)*1.5);
          if (tooltip_fadealpha <= 0) tooltip_fadealpha = 0;
        }
        if (tooltip_fadealpha<=0)
        {
          tooltip_fadealpha = 0;
          tooltip_showing = false;
          tooltip_visible = false;
        }
    }
    else tooltip_showing = true;
   }
   else tooltip_showing = true;
}

int oldtooltip_x=-1,oldtooltip_y=-1;

void resettooltip(void)
{
  tooltip_fadealpha = 0;
  tooltip_x = 0;
  tooltip_y = 0;
  oldtooltip_x = -1;
  oldtooltip_y = -1;
  tooltip_showing = false;
  tooltip_fadeout = false;
  tooltip_control = false;
  tooltip_incontrol = false;
}

void showtooltip(const char* text)
{
  //tooltip_visible = true;
  if ((oldtooltip_x != tooltip_x)&&(oldtooltip_y != tooltip_y))
  {
    tooltip_x = mousex+16;
    tooltip_y = mousey+16;
    if ((tooltip_x+textwidth((char*)text)+8)>=getscreenwidth()) tooltip_x -= (textwidth((char*)text)+8);
    if ((tooltip_y+12+16)>=getscreenheight()) tooltip_y -= (12+16);
  }
  else
  {
    //tooltip_x = mousex+16;
    //tooltip_y = mousey+16;
  }
  showtooltip(tooltip_x,tooltip_y,text);
  oldtooltip_x = tooltip_x;
  oldtooltip_y = tooltip_y;
}

void showtooltips(void)
{
    if (tooltip_visible)
    {
      showtooltip(tooltip);
      tooltip_visible = false;
    }
}


