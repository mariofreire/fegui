// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2013 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br
//---------------------------------------------------------------------------

#ifndef feguiH
#define feguiH
//---------------------------------------------------------------------------

#include <stdio.h>
#include <dlltype.h>

namespace fegui
{
class TObject
{
	public:
		// class constructor
		TObject();
		// class destructor
		~TObject();
};
};

typedef void (* TFEGUI_NotifyEvent)(int windowid,int sender);
typedef void (* TFEGUI_RenderEvent)(int windowid,int sender);
typedef void (* TFEGUI_TimerEvent)(int windowid, int sender);
typedef void (* TFEGUI_MenuEvent)(int windowid, int sender, int menuid);

#define FEGUI_STDCALL
#define FEGUI_CALLBACK FEGUI_STDCALL

typedef FILE* (FEGUI_CALLBACK *FEGUI_FILE_OPENCALLBACK) (const char* filename, const char* mode);
typedef int (FEGUI_CALLBACK *FEGUI_FILE_CLOSECALLBACK) (FILE* stream);
typedef long (FEGUI_CALLBACK *FEGUI_FILE_TELLCALLBACK) (FILE* stream);
typedef int (FEGUI_CALLBACK *FEGUI_FILE_SEEKCALLBACK) (FILE* stream, long offset, int whence);
typedef size_t (FEGUI_CALLBACK *FEGUI_FILE_READCALLBACK) (void* ptr, size_t size, size_t n, FILE* stream);
typedef size_t (FEGUI_CALLBACK *FEGUI_FILE_WRITECALLBACK) (const void* ptr, size_t size, size_t n, FILE* stream);


#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

void fegui_settransparentboxonrender(int handlewindow,int handlecontrol,TFEGUI_RenderEvent onrender);
void fegui_setviewportonrender(int handlewindow,int handlecontrol,TFEGUI_RenderEvent onrender);
void fegui_setviewportonclick(int handlewindow,int handlecontrol,TFEGUI_NotifyEvent onclick);
void fegui_setbuttononclick(int handlewindow,int handlecontrol,TFEGUI_NotifyEvent onclick);
void fegui_setspeedbuttononclick(int handlewindow,int handlecontrol,TFEGUI_NotifyEvent onclick);
void fegui_setglyphbuttononclick(int handlewindow,int handlecontrol,TFEGUI_NotifyEvent onclick);
void fegui_settimerontimer(int handlewindow,int handlecontrol,TFEGUI_TimerEvent ontimer);
void fegui_setmenuitemonclick(int handlewindow,int handlecontrol,int handlemenuitem,TFEGUI_MenuEvent onclick);
void fegui_setmenusubitemonclick(int handlewindow,int handlecontrol,int handlemenuitem,int handlemenusubitem,TFEGUI_MenuEvent onclick);
void fegui_setfilesystem(FEGUI_FILE_OPENCALLBACK fileopen,FEGUI_FILE_CLOSECALLBACK fileclose,FEGUI_FILE_READCALLBACK fileread,FEGUI_FILE_WRITECALLBACK filewrite,FEGUI_FILE_TELLCALLBACK filetell,FEGUI_FILE_SEEKCALLBACK fileseek);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)



#define FEGUI_MOUSECURSOR_XCURSOR               0x0000
#define FEGUI_MOUSECURSOR_ARROW                 0x0001
#define FEGUI_MOUSECURSOR_APPSTART              0x0002
#define FEGUI_MOUSECURSOR_IBEAM                 0x0003
#define FEGUI_MOUSECURSOR_CROSSHAIR             0x0004
#define FEGUI_MOUSECURSOR_POINTER               0x0005
#define FEGUI_MOUSECURSOR_HELP                  0x0006
#define FEGUI_MOUSECURSOR_WAIT                  0x0007
#define FEGUI_MOUSECURSOR_DRAG                  0x0008
#define FEGUI_MOUSECURSOR_MULTIDRAG             0x0009
#define FEGUI_MOUSECURSOR_HSPLIT                0x0010
#define FEGUI_MOUSECURSOR_VSPLIT                0x0011
#define FEGUI_MOUSECURSOR_MOVE                  0x0012
#define FEGUI_MOUSECURSOR_SIZEWZ                0x0013
#define FEGUI_MOUSECURSOR_SIZEXZ                0x0014
#define FEGUI_MOUSECURSOR_SIZEX                 0x0015
#define FEGUI_MOUSECURSOR_SIZEY                 0x0016
#define FEGUI_MOUSECURSOR_NO                    0x0017
#define FEGUI_MOUSECURSOR_NODROP                0x0018
#define FEGUI_MOUSECURSOR_UPARROW               0x0019
#define FEGUI_MOUSECURSOR_PENCIL                0x0020
#define FEGUI_MOUSECURSOR_ERASER                0x0021
#define FEGUI_MOUSECURSOR_FLOODFILL             0x0022
#define FEGUI_MOUSECURSOR_PICKERDROP            0x0023
#define FEGUI_MOUSECURSOR_STYLUSPEN             0x0024
#define FEGUI_MOUSECURSOR_OK                    0x0025
#define FEGUI_MOUSECURSOR_XCANCEL               0x0026
#define FEGUI_MOUSECURSOR_HANDMOVE              0x0027
#define FEGUI_MOUSECURSOR_DOWNARROW             0x0028
#define FEGUI_MOUSECURSOR_LEFTARROW             0x0029
#define FEGUI_MOUSECURSOR_RIGHTARROW            0x0030
#define FEGUI_MOUSECURSOR_WZARROW               0x0031
#define FEGUI_MOUSECURSOR_XZARROW               0x0032
#define FEGUI_MOUSECURSOR_YZARROW               0x0033
#define FEGUI_MOUSECURSOR_XYARROW               0x0034
#define FEGUI_MOUSECURSOR_SOUND                 0x0035
#define FEGUI_MOUSECURSOR_ARROWPLUS             0x0036
#define FEGUI_MOUSECURSOR_ARROWMINUS            0x0037
#define FEGUI_MOUSECURSOR_CAROUSELWAIT          0x0038
#define FEGUI_MOUSECURSOR_RADIALWAIT            0x0039
#define FEGUI_MOUSECURSOR_NONE                  0x0040


DLLIMPORT char* fegui_getbuttoncaption (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getcomboboxitem (int handlewindow,int handlecontrol, int index);
DLLIMPORT char* fegui_getedittext (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getglyphbuttoncaption (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getgroupboxcaption (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getguipath (void);
DLLIMPORT char* fegui_getlabelcaption (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getlistboxitem (int handlewindow,int handlecontrol, int index);
DLLIMPORT char* fegui_getradiobuttoncaption (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getspeedbuttoncaption (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_gettextboxtext (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_gettransparentboxcaption (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getvideoplayerfilename (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getviewportcaption (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getwebbrowserurl (int handlewindow,int handlecontrol);
DLLIMPORT char* fegui_getwindowcaption (int handlewindow);
DLLIMPORT char* fegui_getwindowname (int handlewindow);
DLLIMPORT COLORREF fegui_clLightifDarkB (COLORREF c);
DLLIMPORT COLORREF fegui_clLightifDarkG (COLORREF c);
DLLIMPORT COLORREF fegui_clLightifDarkR (COLORREF c);
DLLIMPORT COLORREF fegui_getwindowcolor (int handlewindow);
DLLIMPORT int fegui_consolecharwidth (void);
DLLIMPORT int fegui_consoletextwidth (char *text);
DLLIMPORT int fegui_createbevel (int handlewindow);
DLLIMPORT int fegui_createbutton (int handlewindow);
DLLIMPORT int fegui_createcheckbox (int handlewindow);
DLLIMPORT int fegui_createcombobox (int handlewindow);
DLLIMPORT int fegui_createdockbar (int handlewindow);
DLLIMPORT int fegui_createedit (int handlewindow);
DLLIMPORT int fegui_createglyphbutton (int handlewindow);
DLLIMPORT int fegui_creategroupbox (int handlewindow);
DLLIMPORT int fegui_createimage (int handlewindow);
DLLIMPORT int fegui_createimagelist (int handlewindow);
DLLIMPORT int fegui_createlabel (int handlewindow);
DLLIMPORT int fegui_createlistbox (int handlewindow);
DLLIMPORT int fegui_createlistview (int handlewindow);
DLLIMPORT int fegui_createmainmenu (int handlewindow);
DLLIMPORT int fegui_createmainmenuitem (int handlewindow,int handlecontrol,int id,char* caption);
DLLIMPORT int fegui_createmainmenusubitem (int handlewindow,int handlecontrol,int menuid,int id,char* caption);
DLLIMPORT int fegui_createpanel (int handlewindow);
DLLIMPORT int fegui_createprogressbar (int handlewindow);
DLLIMPORT int fegui_createradiobutton (int handlewindow);
DLLIMPORT int fegui_createscrollbar (int handlewindow);
DLLIMPORT int fegui_createshape (int handlewindow);
DLLIMPORT int fegui_createspeedbutton (int handlewindow);
DLLIMPORT int fegui_createtextbox (int handlewindow);
DLLIMPORT int fegui_createtimer (int handlewindow);
DLLIMPORT int fegui_createtoolbar (int handlewindow);
DLLIMPORT int fegui_createtoolbutton (int handlewindow);
DLLIMPORT int fegui_createtrackbar (int handlewindow);
DLLIMPORT int fegui_createtransparentbox (int handlewindow);
DLLIMPORT int fegui_createupdown (int handlewindow);
DLLIMPORT int fegui_createvideoplayer (int handlewindow);
DLLIMPORT int fegui_createviewport (int handlewindow);
DLLIMPORT int fegui_createwebbrowser (int handlewindow);
DLLIMPORT int fegui_createwindow (void);
DLLIMPORT int fegui_findwindow (char* name);
DLLIMPORT int fegui_getactivewindow (void);
DLLIMPORT int fegui_getbevelbevelinner (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getbevelbevelouter (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getbevelbevelwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getbevelborderstyle (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getbevelheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getbevelid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getbevelwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getbuttonheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getbuttonid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getbuttonwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getcheckboxchecked (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getcheckboxid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getcomboboxid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getcomboboxitemindex (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getdockbarid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_geteditid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getforegroundwindow (void);
DLLIMPORT int fegui_getglyphbuttonheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getglyphbuttonid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getglyphbuttonwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getgroupboxid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getimageheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getimageid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getimagelistid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getimagewidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getkeychar ();
DLLIMPORT int fegui_getkeyshift ();
DLLIMPORT int fegui_getkeystate (unsigned char Key);
DLLIMPORT int fegui_getlabelid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getlistboxid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getlistboxitemindex (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getlistviewid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getmainmenuid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getmainmenuitemid (int handlewindow,int handlecontrol,int menuid);
DLLIMPORT int fegui_getmouseasync (void);
DLLIMPORT int fegui_getmousecursor (void);
DLLIMPORT int fegui_getpanelbevelinner (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getpanelbevelouter (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getpanelbevelwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getpanelborderstyle (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getpanelheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getpanelid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getpanelwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getprogressbarheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getprogressbarid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getprogressbarmax (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getprogressbarmin (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getprogressbarvalue (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getprogressbarwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getradiobuttonchecked (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getradiobuttongroupindex (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getradiobuttonid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getscreenheight (void);
DLLIMPORT int fegui_getscreenwidth (void);
DLLIMPORT int fegui_getscrollbarheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getscrollbarid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getscrollbarmax (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getscrollbarmin (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getscrollbarvalue (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getscrollbarwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getshapeid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getspeedbuttonheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getspeedbuttonid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getspeedbuttonwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettextboxid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettimerid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettimerinterval (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettoolbarid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettoolbuttonid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettrackbarheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettrackbarid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettrackbarmax (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettrackbarmin (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettrackbarvalue (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettrackbarwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettransparentboxborderstyle (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettransparentboxheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettransparentboxid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_gettransparentboxwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getupdownid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayeraudiorate (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayerframerate (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayerhasaudio (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayerhasbink (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayerhasvideo (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayerid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayerisopened (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayerisplaying (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayerposition (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayerstartframe (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayertextureid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayertotalframe (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getvideoplayervideonum (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getviewportborderstyle (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getviewportheight (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getviewportid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getviewportwidth (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getwebbrowserid (int handlewindow,int handlecontrol);
DLLIMPORT int fegui_getwindowalphavalue (int handlewindow);
DLLIMPORT int fegui_getwindowcount (void);
DLLIMPORT int fegui_getwindowid (int handlewindow);
DLLIMPORT int fegui_getwindowinstance (int handlewindow);
DLLIMPORT int fegui_getwindowmessageboxresult (int handlewindow);
DLLIMPORT int fegui_getwindowpid (int handlewindow);
DLLIMPORT int fegui_getwindowstate (int handlewindow);
DLLIMPORT int fegui_getwindowstyle (int handlewindow);
DLLIMPORT int fegui_getwindowthread (int handlewindow);
DLLIMPORT int fegui_setmouseasync (int a);
DLLIMPORT int fegui_showmodalwindow (int handlewindow);
DLLIMPORT int fegui_textwidth (char *text);
DLLIMPORT int fegui_windowexists (int handlewindow);
DLLIMPORT POINT fegui_getwindowpos (int handlewindow);
DLLIMPORT POINT fegui_getwindowsize (int handlewindow);
DLLIMPORT unsigned int fegui_loadbitmaptexture (char* filename);
DLLIMPORT void fegui_addcomboboxitem (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_addlistboxitem (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_appcreate ();
DLLIMPORT void fegui_appdestroy ();
DLLIMPORT void fegui_appinit ();
DLLIMPORT void fegui_apprun ();
DLLIMPORT void fegui_appuninit ();
DLLIMPORT void fegui_begindrawing (void);
DLLIMPORT void fegui_closewindow (int handlewindow);
DLLIMPORT void fegui_consolecharout (int x,int y,unsigned char c);
DLLIMPORT void fegui_consoletextcolor (COLORREF c);
DLLIMPORT void fegui_consoletextfont (char *font);
DLLIMPORT void fegui_consoletextout (int x,int y,char *text);
DLLIMPORT void fegui_deletewindow (int handlewindow);
DLLIMPORT void fegui_drawcircle (int x0,int y0,int x1,int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_drawcontroledge (int x,int y,int w,int h, int state, int alpha);
DLLIMPORT void fegui_drawcontroledgew (int x,int y,int w,int h, int state, int alpha);
DLLIMPORT void fegui_drawellipse (int x0,int y0,int x1,int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_drawgradient (int x0, int y0, int x1, int y1, COLORREF startcolor, COLORREF endcolor, int alpha,int direction);
DLLIMPORT void fegui_drawimagedatamask (int x, int y,int w,int h,unsigned char*data,int alpha, COLORREF color, bool transparent, COLORREF transparentcolor);
DLLIMPORT void fegui_drawline (int x0, int y0, int x1, int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_enddrawing (void);
DLLIMPORT void fegui_fillrect (int x0, int y0, int x1, int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_fillrectpattern (int x0, int y0, int x1, int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_fillrecttess (int x0, int y0, int x1, int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_fillrecttexture (unsigned int texture, int x0, int y0, int x1, int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_getmousepos (int *x,int *y);
DLLIMPORT void fegui_getmousestate (int *bs);
DLLIMPORT void fegui_getmousewheel (int *k,int *d);
DLLIMPORT void fegui_hidewindow (int handlewindow);
DLLIMPORT void fegui_maximizewindow (int handlewindow);
DLLIMPORT void fegui_messagebox (int handlewindow,char* text,char *caption,int msgtype);
DLLIMPORT void fegui_minimizewindow (int handlewindow);
DLLIMPORT void fegui_rectangle (int x0, int y0, int x1, int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_rectangledashed (int x0, int y0, int x1, int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_rectangledotted (int x0, int y0, int x1, int y1, COLORREF color, int alpha);
DLLIMPORT void fegui_resizebevel (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizebutton (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizecheckbox (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizecombobox (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizedockbar (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizeedit (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizeglyphbutton (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizegroupbox (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizeimage (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizeimagelist (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizelabel (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizelistbox (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizelistview (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizemainmenu (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizepanel (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizeprogressbar (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizeradiobutton (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizescrollbar (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizeshape (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizespeedbutton (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizetextbox (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizetoolbar (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizetoolbutton (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizetrackbar (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizetransparentbox (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizeupdown (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizevideoplayer (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizeviewport (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizewebbrowser (int handlewindow,int handlecontrol,int w,int h);
DLLIMPORT void fegui_resizewindow (int handlewindow,int w,int h);
DLLIMPORT void fegui_restorewindow (int handlewindow);
DLLIMPORT void fegui_setactivewindow (int handlewindow);
DLLIMPORT void fegui_setbevelbevelinner (int handlewindow,int handlecontrol,int bevelinner);
DLLIMPORT void fegui_setbevelbevelouter (int handlewindow,int handlecontrol,int bevelouter);
DLLIMPORT void fegui_setbevelbevelwidth (int handlewindow,int handlecontrol,int bevelwidth);
DLLIMPORT void fegui_setbevelborderstyle (int handlewindow,int handlecontrol,int borderstyle);
DLLIMPORT void fegui_setbevelcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setbevelid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setbevelname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setbevelpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setbuttoncaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setbuttonid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setbuttonname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setbuttononclick (int handlewindow,int handlecontrol,TFEGUI_NotifyEvent onclick);
DLLIMPORT void fegui_setbuttonpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setcheckboxcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setcheckboxchecked (int handlewindow,int handlecontrol,int checked);
DLLIMPORT void fegui_setcheckboxid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setcheckboxname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setcheckboxpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setcomboboxid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setcomboboxitem (int handlewindow,int handlecontrol,int index,char* name);
DLLIMPORT void fegui_setcomboboxitemindex (int handlewindow,int handlecontrol,int index);
DLLIMPORT void fegui_setcomboboxname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setcomboboxpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setcomboboxtext (int handlewindow,int handlecontrol,char* text);
DLLIMPORT void fegui_setdockbarcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setdockbarid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setdockbarname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setdockbarpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_seteditid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_seteditname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_seteditpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setedittext (int handlewindow,int handlecontrol,char* text);
DLLIMPORT void fegui_setforegroundwindow (int handlewindow);
DLLIMPORT void fegui_setglyphbuttoncaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setglyphbuttonid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setglyphbuttonimagefile (int handlewindow,int handlecontrol,int buttonstate,char* imagefilename);
DLLIMPORT void fegui_setglyphbuttonname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setglyphbuttononclick (int handlewindow,int handlecontrol,TFEGUI_NotifyEvent onclick);
DLLIMPORT void fegui_setglyphbuttonpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setgroupboxcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setgroupboxid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setgroupboxname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setgroupboxpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setguipath (const char* path);
DLLIMPORT void fegui_sethwnd (void* hwnd);
DLLIMPORT void fegui_setimagecaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setimagefile (int handlewindow,int handlecontrol,char* imagefilename);
DLLIMPORT void fegui_setimageid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setimagelistid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setimagelistname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setimagename (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setimagepos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setkeydown (unsigned char Key, int Shift);
DLLIMPORT void fegui_setkeyshift (int Shift);
DLLIMPORT void fegui_setkeyup (unsigned char Key, int Shift);
DLLIMPORT void fegui_setlabelcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setlabelid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setlabelname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setlabelpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setlistboxcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setlistboxid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setlistboxitem (int handlewindow,int handlecontrol,int index,char* name);
DLLIMPORT void fegui_setlistboxitemindex (int handlewindow,int handlecontrol,int index);
DLLIMPORT void fegui_setlistboxname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setlistboxpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setlistviewcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setlistviewid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setlistviewname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setlistviewpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setmainmenucaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setmainmenuid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setmainmenuname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setmainmenupos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setmenuitemonclick (int handlewindow,int handlecontrol,int handlemenuitem,TFEGUI_MenuEvent onclick);
DLLIMPORT void fegui_setmenusubitemonclick (int handlewindow,int handlecontrol,int handlemenuitem,int handlemenusubitem,TFEGUI_MenuEvent onclick);
DLLIMPORT void fegui_setmousecursor (int cursor);
DLLIMPORT void fegui_setmousedown_l (int x,int y);
DLLIMPORT void fegui_setmousedown_m (int x,int y);
DLLIMPORT void fegui_setmousedown_r (int x,int y);
DLLIMPORT void fegui_setmousemove (int x,int y);
DLLIMPORT void fegui_setmousepos (int x,int y);
DLLIMPORT void fegui_setmouseup (int x,int y);
DLLIMPORT void fegui_setmousewheel (int key,int delta);
DLLIMPORT void fegui_setpanelbevelinner (int handlewindow,int handlecontrol,int bevelinner);
DLLIMPORT void fegui_setpanelbevelouter (int handlewindow,int handlecontrol,int bevelouter);
DLLIMPORT void fegui_setpanelbevelwidth (int handlewindow,int handlecontrol,int bevelwidth);
DLLIMPORT void fegui_setpanelborderstyle (int handlewindow,int handlecontrol,int borderstyle);
DLLIMPORT void fegui_setpanelcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setpanelid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setpanelname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setpanelpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setpixel (int x, int y, COLORREF color, int alpha);
DLLIMPORT void fegui_setprogressbarcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setprogressbarid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setprogressbarmax (int handlewindow,int handlecontrol,int max);
DLLIMPORT void fegui_setprogressbarmin (int handlewindow,int handlecontrol,int min);
DLLIMPORT void fegui_setprogressbarname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setprogressbarpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setprogressbarvalue (int handlewindow,int handlecontrol,int value);
DLLIMPORT void fegui_setradiobuttoncaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setradiobuttonchecked (int handlewindow,int handlecontrol,int checked);
DLLIMPORT void fegui_setradiobuttongroupindex (int handlewindow,int handlecontrol,int groupindex);
DLLIMPORT void fegui_setradiobuttonid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setradiobuttonname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setradiobuttonpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setscreenheight (int h);
DLLIMPORT void fegui_setscreensize (int w,int h);
DLLIMPORT void fegui_setscreenwidth (int w);
DLLIMPORT void fegui_setscrollbarcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setscrollbarid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setscrollbarmax (int handlewindow,int handlecontrol,int max);
DLLIMPORT void fegui_setscrollbarmin (int handlewindow,int handlecontrol,int min);
DLLIMPORT void fegui_setscrollbarname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setscrollbarpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setscrollbarvalue (int handlewindow,int handlecontrol,int value);
DLLIMPORT void fegui_setshapecaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setshapeid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setshapename (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setshapepos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setspeedbuttoncaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setspeedbuttonicon (int handlewindow,int handlecontrol,char* iconfilename);
DLLIMPORT void fegui_setspeedbuttonid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setspeedbuttonname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setspeedbuttononclick (int handlewindow,int handlecontrol,TFEGUI_NotifyEvent onclick);
DLLIMPORT void fegui_setspeedbuttonpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_settextboxid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_settextboxname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_settextboxpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_settextboxtext (int handlewindow,int handlecontrol,char* text);
DLLIMPORT void fegui_settimerid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_settimerinterval (int handlewindow,int handlecontrol,int interval);
DLLIMPORT void fegui_settimername (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_settimerontimer (int handlewindow,int handlecontrol,TFEGUI_TimerEvent ontimer);
DLLIMPORT void fegui_settoolbarcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_settoolbarid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_settoolbarname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_settoolbarpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_settoolbuttoncaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_settoolbuttonid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_settoolbuttonname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_settoolbuttonpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_settrackbarcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_settrackbarid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_settrackbarmax (int handlewindow,int handlecontrol,int max);
DLLIMPORT void fegui_settrackbarmin (int handlewindow,int handlecontrol,int min);
DLLIMPORT void fegui_settrackbarname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_settrackbarpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_settrackbarvalue (int handlewindow,int handlecontrol,int value);
DLLIMPORT void fegui_settransparentboxalphavalue (int handlewindow,int handlecontrol,int alphavalue);
DLLIMPORT void fegui_settransparentboxbackgroundalpha (int handlewindow,int handlecontrol,int backgroundalpha);
DLLIMPORT void fegui_settransparentboxborderstyle (int handlewindow,int handlecontrol,int borderstyle);
DLLIMPORT void fegui_settransparentboxcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_settransparentboxcolor (int handlewindow,int handlecontrol,COLORREF color);
DLLIMPORT void fegui_settransparentboxid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_settransparentboxname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_settransparentboxonrender (int handlewindow,int handlecontrol,TFEGUI_RenderEvent onrender);
DLLIMPORT void fegui_settransparentboxpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setupdowncaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setupdownid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setupdownname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setupdownpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setvideoplayercaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setvideoplayerfilename (int handlewindow,int handlecontrol,char* filename);
DLLIMPORT void fegui_setvideoplayerid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setvideoplayername (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setvideoplayerpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setviewportborderstyle (int handlewindow,int handlecontrol,int borderstyle);
DLLIMPORT void fegui_setviewportcaption (int handlewindow,int handlecontrol,char* caption);
DLLIMPORT void fegui_setviewportid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setviewportname (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setviewportonclick (int handlewindow,int handlecontrol,TFEGUI_NotifyEvent onclick);
DLLIMPORT void fegui_setviewportonrender (int handlewindow,int handlecontrol,TFEGUI_RenderEvent onrender);
DLLIMPORT void fegui_setviewportpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setwebbrowserid (int handlewindow,int handlecontrol,int id);
DLLIMPORT void fegui_setwebbrowsername (int handlewindow,int handlecontrol,char* name);
DLLIMPORT void fegui_setwebbrowserpos (int handlewindow,int handlecontrol,int x,int y);
DLLIMPORT void fegui_setwebbrowserurl (int handlewindow,int handlecontrol,char* url);
DLLIMPORT void fegui_setwindowalphavalue (int handlewindow,int alphavalue);
DLLIMPORT void fegui_setwindowcaption (int handlewindow,char* caption);
DLLIMPORT void fegui_setwindowcolor (int handlewindow,COLORREF color);
DLLIMPORT void fegui_setwindowid (int handlewindow,int id);
DLLIMPORT void fegui_setwindowinstance (int handlewindow,int instance);
DLLIMPORT void fegui_setwindowmessageboxresult (int handlewindow,int result);
DLLIMPORT void fegui_setwindowname (int handlewindow,char* name);
DLLIMPORT void fegui_setwindowpid (int handlewindow,int pid);
DLLIMPORT void fegui_setwindowpos (int handlewindow,int x,int y);
DLLIMPORT void fegui_setwindowsize (int handlewindow,int w,int h);
DLLIMPORT void fegui_setwindowstate (int handlewindow,int state);
DLLIMPORT void fegui_setwindowstyle (int handlewindow,int style);
DLLIMPORT void fegui_setwindowthread (int handlewindow,int threadid);
DLLIMPORT void fegui_showbevel (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showbutton (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showcheckbox (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showcombobox (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showdockbar (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showedit (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showglyphbutton (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showgroupbox (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showimage (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showlabel (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showlistbox (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showlistview (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showmainmenu (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showpanel (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showprogressbar (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showradiobutton (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showscrollbar (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showshape (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showspeedbutton (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showtextbox (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showtoolbar (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showtoolbutton (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showtrackbar (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showtransparentbox (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showupdown (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showvideoplayer (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showviewport (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showwebbrowser (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_showwindow (int handlewindow);
DLLIMPORT void fegui_subrecttess (int x0,int y0,int x1,int y1);
DLLIMPORT void fegui_textattr (COLORREF color,int alpha, int height, int weight);
DLLIMPORT void fegui_textout (int x, int y, char *text);
DLLIMPORT void fegui_videoplayer_close (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_videoplayer_open (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_videoplayer_play (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_videoplayer_resume (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_videoplayer_stop (int handlewindow,int handlecontrol);
DLLIMPORT void fegui_webkit_keydown (unsigned char key);
DLLIMPORT void fegui_webkit_keyup (unsigned char key);
DLLIMPORT void fegui_windowfreeze (int handlewindow);
DLLIMPORT void fegui_wmcrash (unsigned long exceptioncode);
DLLIMPORT void fegui_wmcrashmessage (const char* msg);

//---------------------------------------------------------------------------
#endif
