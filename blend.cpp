// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "blend.h"


COLORREF blendcolorto(COLORREF s,COLORREF d,int a)
{
  COLORREF c=0;
  BYTE sr=0,sg=0,sb=0;
  BYTE dr=0,dg=0,db=0;
  BYTE r=0,g=0,b=0;
  BYTE alpha=0;
  alpha = 255-a;
  c = s;
  sb = GetRValue(c);
  sg = GetGValue(c);
  sr = GetBValue(c);
  dr = GetRValue(d);
  dg = GetGValue(d);
  db = GetBValue(d);
  dr = sr*(alpha/255.0)+dr*(1.0-(alpha/255.0));
  dg = sg*(alpha/255.0)+dg*(1.0-(alpha/255.0));
  db = sb*(alpha/255.0)+db*(1.0-(alpha/255.0));
  r = db;
  g = dg;
  b = dr;
  c = RGB(r,g,b);
  return c;   
}

int blendto(int s,int d)
{
       int a = d;
       
       a = (int)(s * (float)(d/255.0) + (float)(1.0 - (a/255.0)));
       
       if (a<=0) a = 0;
       if (a>=255) a = 255;
       
       return a;      
}
