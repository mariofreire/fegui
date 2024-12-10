// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef MOUSE_H
#define MOUSE_H

extern int mousea, mouseb,mousec,mousex,mousey,mousekeys,mousedelta;
extern int oldmousex, oldmousey;

extern int mc;

void setmousedown_l(int x,int y);
void setmousedown_m(int x,int y);
void setmousedown_r(int x,int y);
void setmousemove(int x,int y);
void setmouseup(int x,int y);
void setmousewheel(int key,int delta);
void setmousepos(int x,int y);
void getmousepos(int *x,int *y);
void getmousestate(int *bs);
void getmousewheel(int *k,int *d);

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

extern int currentcursor;

void setmousecursor(int cursor);
int getmousecursor(void);


class TMouse
{
	public:
		// class constructor
		TMouse();
		// class destructor
		~TMouse();
		int X,Y;
		int Button;
		int ShiftState;
};

#endif // MOUSE_H
