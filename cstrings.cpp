// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "cstrings.h"
#include "cimp.h"


int fstrlen(const char* s)
{
  int len = 0;
  while (*s != NULL)
  {
    len++;
    *s++;
  }
  return len;
}


char* fextractfileext(const char* filename)
{
  char* ext = (char*)malloc(fstrlen(filename)+1);
  int len=0;
  while (*filename != NULL)
  {
    if ((*filename == '.')||(len > 0))
    {
      ext[len] = *filename;
      len++;
    }
    *filename++;
  }
  ext[len] = 0;
  return ext;
}

char* filenamefrompath(const char* path,const char* filename)
{
  char* fnpath = (char*)malloc(fstrlen(path)+fstrlen(filename)+1);
  int len=0;
  while (*path != NULL)
  {
    fnpath[len] = *path;
    len++;
    *path++;
  }
  while (*filename != NULL)
  {
    fnpath[len] = *filename;
    len++;
    *filename++;
  }
  fnpath[len] = 0;
  return fnpath;
}


char *ltoa(long value)
{
     std::string a="";
     char buf[256];
     strcpy(buf,"");
     sprintf(buf,"%i",value);
     //a = buf;
     //char *b = (char*)a.c_str();
     return buf;
}
