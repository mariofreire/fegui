// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "imagelist.h" // class's header file


void renderimagelist(TComponent* sender)
{
TImageList* imagelist = dynamic_cast <TImageList*>((TImageList*)sender);
imagelist->window->imagelists[sender->componentid] = imagelist;
}

TImageList::TImageList(TWindow *Window)
{
window = Window;
id=window->numcomponents+1000;
name="imagelist";
width=16;
height=16;
enabled = true;
alphavalue = window->alphavalue;
parent = Window;
numimages = 0;
for (int i=0;i<numimages;i++)
{
images[i] = new TPicture();
images[i]->canvas->width = 16;
images[i]->canvas->height = 16;
if (images[i]->canvas->pixels) delete images[i]->canvas->pixels;
images[i]->canvas->pixels = new unsigned char [16*16*images[i]->canvas->format];
}
componentid = window->numcomponents;
render = renderimagelist;
window->imagelists[window->numimagelists] = this;
window->numimagelists++;
window->numcomponents++;
}

TImageList::~TImageList()
{
for (int i=0;i<numimages;i++) delete images[i];
}

void TImageList::rendercomponent()
{
window->imagelists[componentid] = this;
}


void TImageList::addimage(TPicture* image)
{
  images[numimages] = new TPicture();
  images[numimages] = image;
  numimages++;
}

void TImageList::addimage(char* filename)
{
  TPicture* image = new TPicture();
  image->load(filename);
  addimage(image);
}

TPicture* TImageList::createimage()
{
  TPicture* image = new TPicture();
  image->canvas->pixels = new unsigned char [width*height*3]; 
  images[numimages] = image;
  numimages++;
  return image;
}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createimagelist(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int imglstid = 0;
   imglstid = windows[winid]->numimagelists;
   TImageList* imagelist = new TImageList(windows[winid]);
   imagelist->alphavalue = 255;
   imagelist->enabled = true;
   imagelist->width=16;
   imagelist->height=16;
   return imglstid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

