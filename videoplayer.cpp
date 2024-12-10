// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "videoplayer.h" // class's header file
#include "fevsl.h"



#define GL_BGR 0x80E0

bool fevsl_reloadtexture_on = false;
void fevsl_reloadtexture()
{
fevsl_reloadtexture_on = true;
}

void fevsl_binksndonoff(int video,int onoff)
{
 fevsl_binksoundonoff(video,onoff);
}

int fevsl_loadimage(int bgr,int width,int height,char *image, GLuint *tex) {
if (width < 1) return -1;
if (height < 1) return -1;
if (image==NULL) return -1;

if ((*tex == 0)||(fevsl_reloadtexture_on))
{
glGenTextures(1, tex);

glBindTexture( GL_TEXTURE_2D, *tex ); //bind the texture to it's array

      /*
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
       */
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

if (bgr) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_BGR, GL_UNSIGNED_BYTE, image);
else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, image);

if (fevsl_reloadtexture_on) fevsl_reloadtexture_on = false;
}
else
{
  glBindTexture( GL_TEXTURE_2D, *tex ); //bind the texture to it's array
  if (bgr) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_BGR, GL_UNSIGNED_BYTE, image);
  else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  //if (bgr) glTexSubImage2D(GL_TEXTURE_2D, 0,0,0, width, height, GL_BGR, GL_UNSIGNED_BYTE, image); // can't resize texture
  //else glTexSubImage2D(GL_TEXTURE_2D, 0,0,0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image); // can't resize texture
}

return 0;
}

bool videoplayercontrolon = false;
void rendervideoplayer(TControl *sender)
{
    TVideoPlayer* videoplayer = dynamic_cast <TVideoPlayer*>((TVideoPlayer*)sender);
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
           if (videoplayercontrolon) sender->clicked = true;
		   sender->window->activecontrol = sender->controlid;
         } else 
         {
           videoplayercontrolon = false;
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
       fillrect(l,t+1,l+w,t+h,videoplayer->color,a);
       
       videoplayer->getstream();
       
       if (videoplayer->image)
       {
        int x=0; x = 1;
		int texon = glIsEnabled(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        begindrawing();
//        fevsl_loadtextureimage(videoplayer->videonum);
        if (videoplayer->hasbink) fevsl_loadimage(0,videoplayer->width,videoplayer->height,videoplayer->image,&videoplayer->textureid);
        else fevsl_loadimage(1,videoplayer->width,videoplayer->height,videoplayer->image,&videoplayer->textureid);
        
        glColor4ub(255,255,255,a);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2i(l,t);
        glTexCoord2f(1,0); glVertex2i(l+w,t);
        glTexCoord2f(1,1); glVertex2i(l+w,t+h);
        glTexCoord2f(0,1); glVertex2i(l,t+h);
        glEnd();
		enddrawing();
        if (texon) glEnable(GL_TEXTURE_2D);
        else glDisable(GL_TEXTURE_2D);
       // if (videoplayer->image) free(videoplayer->image);
       }
       
       glDisable(GL_SCISSOR_TEST);
    }
    else
    {
      if (videoplayer->hasbink) fevsl_binksoundonoff(videoplayer->videonum,0);
    }
}

TVideoPlayer::TVideoPlayer(TWindow *Window)
{
          window = Window;
          id=window->numcontrols+100;
          name="videoplayer";
          visible = false;
          left=0;
          top=0;
		  width=64;
          height=128;
          parent = window;
          alphavalue = window->alphavalue;
          color = clBtnFace;
          caption="videoplayer";
          isopenned = false;
          isplaying = false;
          hasaudio = false;
          hasvideo = false;
          hasbink = false;
          framerate = 0;
          audiorate = 0;
          startframe = 0;
		  totalframe = 0;
          position = 0;
          textureid = 0;
          filename = NULL;
          image = NULL;
          videonum = fevsl_createvideo();
          render = rendervideoplayer;
          controlid = window->numcontrols;
          onclick = NULL;
          onkeydown = NULL;
          onkeyup = NULL;
          visible = false;
          instance = this;
          window->videoplayers[window->numvideoplayers] = this;
          window->numvideoplayers++;
          window->numcontrols++;
}

TVideoPlayer::~TVideoPlayer()
{
  fevsl_closevideo(videonum);
  if (image) free(image);
}

void TVideoPlayer::getstream()
{
  width = fevsl_getwidth(videonum);
  height = fevsl_getheight(videonum);
  framerate = fevsl_getframerate(videonum);
  audiorate = fevsl_getaudiorate(videonum);
  hasbink = fevsl_hasbink(videonum);
//  image = (char*)malloc(width*height*3);
//  memset(image,255,width*height*3);
  image = fevsl_getimage(videonum);
//  fevsl_getimagedata(videonum,image);
}

void TVideoPlayer::play()
{
  fevsl_openvideo(videonum,filename);
}

void TVideoPlayer::stop()
{
  fevsl_closevideo(videonum);
}

void TVideoPlayer::resume()
{
}

void TVideoPlayer::open()
{
  fevsl_openvideo(videonum,filename);
}

void TVideoPlayer::close()
{
  fevsl_closevideo(videonum);
}

void TVideoPlayer::rendercontrol()
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

if ((focused==true)&&(clicked==true)&&(videoplayercontrolon==true))
{
if (IsInControl(this)==true)
{
  if (onclick != NULL) onclick(this);
  clicked = false;
  if (!mouseb) videoplayercontrolon = false;
}
} else focused = false;
}
}
else
{
      if (hasbink) fevsl_binksoundonoff(videonum,0);
}
instance = this;
window->videoplayers[controlid] = this;
}
void TVideoPlayer::show()
{
  if ( window->showing==true) 
  {
       visible = true;
       if (visible) rendercontrol();
       window->videoplayers[controlid] = this;
  }
}
void TVideoPlayer::hide()
{
          visible = false;
		  window->videoplayers[controlid] = this;

}

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

int _fegui_windowexists(int winid);
int createvideoplayer(int winid)
{
 if (_fegui_windowexists(winid))
 {
   int vidplayid = 0;
   vidplayid = windows[winid]->numvideoplayers;
   TVideoPlayer* videoplayer = new TVideoPlayer(windows[winid]);
   videoplayer->alphavalue = 255;
   videoplayer->enabled = true;
   videoplayer->width=72;
   videoplayer->height=24;
   videoplayer->left=32;
   videoplayer->top=32;
   videoplayer->visible = false;
   return vidplayid;
 }
 return 0;
}

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


