// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

// #define TEST

#include "application.h" // class's header file


bool appinitialized = false;

char fatal_error_exceptionmessage[4096];
int fatal_error_exceptionmessagecnt=0;
std::string fatal_error_exceptionmessageline[32];
int fatal_error_exceptioncode=0;
int fatal_error_timestart_mday=0;
int fatal_error_timestart_mon=0;
int fatal_error_timestart_year=0;
int fatal_error_timestart_hour=0;
int fatal_error_timestart_min=0;
int fatal_error_timestart_sec=0;
time_t fatal_error_timestart_timevalue=0;
int shutdown_countdown=0;
bool fatal_error = false;

int msg_tr[256];

extern bool textarea;
extern bool updownspeedarea;

char guipath[256];


int getfatalerrormsgcount(void)
{
int i=0;
int n=0;
int l=0;
char* msg = fatal_error_exceptionmessage;
int len = strlen(msg);

  if (len > 0) n = 1;

  while ((*msg) && (l < len))
  {
    if (*msg == '\n') n++;
    l++;
    *msg++;
  }

  return n;
}


void setfatalerrormsglines(void)
{
int i=0;
int n=0;
int l=0;
char* msg = fatal_error_exceptionmessage;
int len = strlen(msg);

  while ((*msg) && (l < len))
  {
    if ((*msg != '\n')&&(*msg != '\r')&&(*msg != '\t')) fatal_error_exceptionmessageline[n] = fatal_error_exceptionmessageline[n] + *msg;
    if (*msg == '\n') n++;
    l++;
    *msg++;
  }
}



void systemmenumove(TWinControl *sender)
{
 if (windows[activewindow]->windowstate != wsMaximized)
 {
  // windows[activewindow]->left = 0;//mousex-1;
  // windows[activewindow]->top = 0;//mousey-1;
   windows[activewindow]->windowmove = true;
   winmove = true;
 }
}

void systemmenusize(TWinControl *sender)
{
 if ((windows[activewindow]->windowstate != wsMaximized)&&(!windows[activewindow]->freezing))
 {
  // windows[activewindow]->left = 0;//mousex-1;
  // windows[activewindow]->top = 0;//mousey-1;
  // windows[activewindow]->windowresize = true;
   mousex = windows[activewindow]->left+windows[activewindow]->width-4;
   mousey = windows[activewindow]->top+windows[activewindow]->height-4;
   windowresizeside = RESIZEWIN_SCALE;
  // windowresize = true;
   winresize = true;
 }
}

void systemmenurestore(TWinControl *sender)
{
 windows[activewindow]->restore();
 windows[activewindow]->windowstate = wsNormal; 
}

void systemmenumaximize(TWinControl *sender)
{
 windows[activewindow]->maximize();
 windows[activewindow]->windowstate = wsMaximized;
}

void systemmenuminimize(TWinControl *sender)
{
 windows[activewindow]->minimize();
 windows[activewindow]->windowstate = wsMinimized;
}

void systemmenuclose(TWinControl *sender)
{
// deletewindow(activewindow);
 windows[activewindow]->visible = false;
 if (activewindow > 0) activewindow--;
 if (activewindow <= 0) activewindow = 0;
}

void editmenudelete(TWinControl *sender)
{
if (activetextedit)
{
                activetextedit->focus = true;
                activetextedit->focused = true;
                activetextedit->window->activecontrol = activetextedit->controlid;
                activetextedit->clear();
}
if (activeedit)
{
                activeedit->focus = true;
                activeedit->focused = true;
                activeedit->window->activecontrol = activeedit->controlid;
                activeedit->clear();
}
}

void editmenuselectall(TWinControl *sender)
{
if (activetextedit) 
{
                activetextedit->focus = true;
                activetextedit->focused = true;
                activetextedit->window->activecontrol = activetextedit->controlid;
                activetextedit->selectall();
}
if (activeedit) 
{
                activeedit->focus = true;
                activeedit->focused = true;
                activeedit->window->activecontrol = activeedit->controlid;
                activeedit->selectall();
}
}



AUX_RGBImageRec *TextureImage[2];
GLuint	texture[2];

int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;									// Status Indicator

	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0]=LoadBMP("arrow.bmp"))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &texture[0]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}

		glGenTextures(1, &texture[1]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		int j=0,k=0;
		char *xbkdata = (char*)malloc(8*8*3);
		int c=0;
		for (int i=0;i<(8*8*3);i+=3)
		{
          if (xbackground[k]) c = 255;
          else c = 0;
          xbkdata[j * 3 + 0] = c;
          xbkdata[j * 3 + 1] = c;
          xbkdata[j * 3 + 2] = c;  
          j++;
          k++;
        }

		glTexImage2D(GL_TEXTURE_2D, 0, 3, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, xbkdata);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	return Status;										// Return The Status
}

void appcreate()
{
    int i=0;
    
    for (i=0;i<256;i++) keys[i] = false;
    for (i=0;i<256;i++) msg_tr[i] = 0;

    f_open = NULL;
    f_close = NULL;
    f_tell = NULL;
    f_seek = NULL;
    f_read = NULL;
    f_write = NULL;

    strcpy(guipath,"");

    strcpy(fatal_error_exceptionmessage,"");
    fatal_error_exceptionmessagecnt = 0;

    fastpnglib_init();
    fevsl_init();
    fewebkit_init();

    activewebbrowser = -1;
}

void appinit()
{
    int i=0;
    
    mousex = width / 2;
    mousey = height / 2;

    /*
    xbk = loadbmp("xbk.bmp");

    xcursor = loadbmp("xcursor.bmp");
    arrow = loadbmp("arrow.bmp");
    sizexcursor = loadbmp("sizex.bmp");
    sizeycursor = loadbmp("sizey.bmp");
    sizexzcursor = loadbmp("sizexz.bmp");
    sizewzcursor = loadbmp("sizewz.bmp");
    textcursor = loadbmp("textcursor.bmp");
    */

    /*
    char fn[256];
    for (int i=0;i<256;i++)
    {
         strcpy(fn,"font\\");
         strcat(fn,ltoa(i));
         strcat(fn,".bmp");
         fontbmp[i] = loadbmp(fn);
    }
    */
    
    loadbitmapfont(filenamefrompath(guipath,"textfont.bin"),&textfont, true);
    consoletextfont("");

    closebtn = loadbmp(filenamefrompath(guipath,"wm_clos.bmp"));
    maximizebtn = loadbmp(filenamefrompath(guipath,"wm_max.bmp"));
    minimizebtn = loadbmp(filenamefrompath(guipath,"wm_min.bmp"));
    restorebtn = loadbmp(filenamefrompath(guipath,"wm_res.bmp"));

    radiobtn = loadbmp(filenamefrompath(guipath,"radiob.bmp"));
    
    checkedicon = loadbmp(filenamefrompath(guipath,"checked.bmp"));
    radioicon = loadbmp(filenamefrompath(guipath,"radio.bmp"));
    leftarrowicon = loadbmp(filenamefrompath(guipath,"arrow_l.bmp"));
    rightarrowicon = loadbmp(filenamefrompath(guipath,"arrow_r.bmp"));
    uparrowicon = loadbmp(filenamefrompath(guipath,"arrow_u.bmp"));
    downarrowicon = loadbmp(filenamefrompath(guipath,"arrow_d.bmp"));
    uparrow4icon = loadbmp(filenamefrompath(guipath,"arrow4u.bmp"));
    downarrow4icon = loadbmp(filenamefrompath(guipath,"arrow4d.bmp"));
    uparrow8icon = loadbmp(filenamefrompath(guipath,"arrow8u.bmp"));
    downarrow8icon = loadbmp(filenamefrompath(guipath,"arrow8d.bmp"));
    leftarrow4icon = loadbmp(filenamefrompath(guipath,"arrow4l.bmp"));
    rightarrow4icon = loadbmp(filenamefrompath(guipath,"arrow4r.bmp"));
    leftarrow8icon = loadbmp(filenamefrompath(guipath,"arrow8l.bmp"));
    rightarrow8icon = loadbmp(filenamefrompath(guipath,"arrow8r.bmp"));

//    warning = loadpng(filenamefrompath(guipath,"warning.png"));
    
    glEnable(GL_TEXTURE_2D);
          
    // LoadGLTextures();
    
    ShowCursor(FALSE);


         systemmenu = new TMenu();
         systemmenu->alphavalue = 255;
         systemmenu->left = 0;
         systemmenu->top = 0;
         systemmenu->menu->additem("Restore")->onclick = systemmenurestore;//enabled = false;
         systemmenu->menu->additem("Move")->onclick = systemmenumove;
         systemmenu->menu->additem("Size")->onclick = systemmenusize;
         systemmenu->menu->additem("Minimize")->onclick = systemmenuminimize;//enabled = false;
         systemmenu->menu->additem("Maximize")->onclick = systemmenumaximize;//enabled = false;
         systemmenu->menu->additem("-");
         systemmenu->menu->additem("Close")->onclick = systemmenuclose;

         systemmenu->visible = false;

         editmenu = new TMenu();
         editmenu->alphavalue = 255;
         editmenu->left = 0;
         editmenu->top = 0;
         editmenu->menu->additem("Undo")->enabled = false;
         editmenu->menu->additem("-");
         editmenu->menu->additem("Cut")->enabled = false;
         editmenu->menu->additem("Copy")->enabled = false;
         editmenu->menu->additem("Paste")->enabled = false;
         editmenu->menu->additem("Delete")->onclick = editmenudelete;
         editmenu->menu->additem("-");
         editmenu->menu->additem("Select All")->onclick = editmenuselectall;

         systemmenu->visible = false;

         appinitialized = true;

}


void appuninit()
{

    appinitialized = false;

    glDisable(GL_TEXTURE_2D);
    /*
    freebmp(xbk);
    freebmp(xcursor);
    freebmp(arrow);
    freebmp(sizexcursor);
    freebmp(sizeycursor);
    freebmp(sizexzcursor);
    freebmp(sizewzcursor);
    freebmp(textcursor);
    */
    freebmp(closebtn);
    freebmp(maximizebtn);
    freebmp(minimizebtn);
    freebmp(restorebtn);
    freebmp(radiobtn);
    freebmp(checkedicon);
    freebmp(radioicon);
    freebmp(leftarrowicon);
    freebmp(rightarrowicon);
    freebmp(uparrowicon);
    freebmp(downarrowicon);
    freebmp(uparrow4icon);
    freebmp(downarrow4icon);
    freebmp(uparrow8icon);
    freebmp(downarrow8icon);
    freebmp(leftarrow4icon);
    freebmp(rightarrow4icon);
    freebmp(leftarrow8icon);
    freebmp(rightarrow8icon);
    freebitmapfont(&textfont);
    delete systemmenu;
    delete editmenu;
    for (int i=0;i<numwindows;i++)
    {
      if (windows[i])
      {
        for (int j=0;j<windows[i]->numwebbrowsers;j++)
        {
              if (windows[i]->webbrowsers[j]) delete windows[i]->webbrowsers[j];
        }
      }
    }
}


void appshow()
{
  int i;
if (windowmanager_crash) return;
if (activewindow<numwindows) 
{
  setforegroundwindow(activewindow);
  for (i=0;i<numwindows;i++)
//  for (i=numwindows-1;i>=0;i--)
  {
   //   if ((i != activewindow)&&(!windows[i]->focused))
      {
      windows[i]->show();
      windows[i]->showfreeze();
      }
  }
//  for (i=numwindows-1;i>=0;i--)
/*
  for (i=0;i<numwindows;i++)
  {
      if ((i != activewindow)&&(windows[i]->focused))
      {
      windows[i]->show();
      }
  }
  windows[activewindow]->show();    
*/
}
else
{
    if (numwindows>0) windowmanager_crash = true;
}
if (!windowmanager_crash)
{
  if (showmenu >= 0)
  {
    menues[showmenu]->show();
  }
  for (i=0;i<numwindows;i++)
  {
    if (msg_tr[i]>windows[i]->messageboxtimereset)
    {
      windows[i]->messageboxresult = mrNone;
      msg_tr[i] = 0;
    }
  msg_tr[i]++;
  }
}
}

void apprun()
{
  if (windowmanager > 1) windowmanager_crash = true;            
  if (windowmanager < 0) windowmanager_crash = true;
  glViewport(0, 0, width, height);    // Set the viewport for the OpenGL window
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
  gluPerspective(45.0, width/height, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth

  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View

            //glClearColor ((GetRValue(clBackground)/255.0), (GetGValue(clBackground)/255.0), (GetBValue(clBackground)/255.0), 0.0f);
            //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glLoadIdentity();                                       // Reset The View

  glShadeModel(GL_SMOOTH);                 // Enables Smooth Color Shading
  glClearDepth(1.0);                       // Depth Buffer Setup
//  glEnable(GL_DEPTH_TEST);                 // Enable Depth Buffer
//  glDepthFunc(GL_LEQUAL);		           // The Type Of Depth Test To Do
  // glEnable (GL_LINE_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   //Realy Nice perspective calculations
  //glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  // glLineWidth (1.0);
  glEnable(GL_TEXTURE_2D);
  setviewport(0,0,width,height);
//  drawtileimage(0,0,width,height,xbk,255,false,clBlack);
//  drawbkimage();
  glDisable(GL_TEXTURE_2D);
     
  appshow();
  if (numwindows>0)
  {
   int opengl_error=0;
   opengl_error=glGetError();
   if (opengl_error!=0) 
   {
     fatal_error_exceptioncode = opengl_error;
     messagebox(windows[activewindow],(char*)gluErrorString(opengl_error),"OpenGL Error",MB_OK|MB_ICONERROR);      
   }    
  }          
  setviewport(0,0,width,height);

if (!windowmanager_crash)
{
    showtooltips();
            
    bool warea=false;

    textarea=false;
    
    glPointSize(1.0);

    for (int i=0;i<nummenues;i++)
    {
     if (menues[i]->visible==true)
     {
      if (getarea(menues[i]->left,menues[i]->top,menues[i]->width,menues[i]->height)==true)
      {
       warea=true;
      }
      if (IsInAnyMenu()) warea=true;
     }
    }
    for (int i=0;i<numwindows;i++)
    {

     if (windows[i]->visible==false)
     {
       for (int j=0;j<windows[i]->numvideoplayers;j++)
       {
        if (windows[i]->videoplayers[j]->hasbink) fevsl_binksndonoff(windows[i]->videoplayers[j]->videonum,0);
       }
     }

     if (windows[i]->visible==true)
     {
      if (getarea(windows[i]->left,windows[i]->top,windows[i]->width,windows[i]->height)==true)
      {
       warea=true;
      }
      for (int j=0;j<windows[i]->numcomboboxes;j++)
      {
       if (windows[i]->comboboxes[j]->visible==true)
       {
         if (windows[i]->comboboxes[j]->IsInControl(windows[i]->comboboxes[j])==true)
         {
           if (windows[i]->comboboxes[j]->style==csDropDown)
           {
            int l=0,w=0,lw=0,cw=0;
            lw = windows[i]->left;
            l = windows[i]->comboboxes[j]->left;
            w = windows[i]->comboboxes[j]->width;
            cw = (lw+l+w)-24;
            if (mousex < (cw))
            {
             textarea = true;
             if (IsInAnyMenu()) textarea = false;
             if (activewindow!=i)
             {
               if (windows[i]->IsInWindow(windows[activewindow])) textarea=false;
             }
            } else textarea=false;
         } else textarea=false;        
        }
        if (windows[i]->comboboxes[j]->listbox->visible)
        {
            int wcaph = windows[i]->height-windows[i]->clientheight;
            if (getarea(windows[i]->left+windows[i]->comboboxes[j]->listbox->left,windows[i]->top+wcaph+windows[i]->comboboxes[j]->listbox->top,windows[i]->comboboxes[j]->listbox->width,windows[i]->comboboxes[j]->listbox->height)) warea = true;
        }
       }
      }
      for (int j=0;j<windows[i]->numedits;j++)
      {
       if (windows[i]->edits[j]->visible==true)
       {
         if (windows[i]->edits[j]->IsInControl(windows[i]->edits[j])==true)
         {
           textarea = true;
           if (IsInAnyMenu()) textarea = false;
           if (activewindow!=i)
           {
             if (windows[i]->IsInWindow(windows[activewindow])) textarea=false;
           }
         }
       }
      }
      for (int j=0;j<windows[i]->numtextboxes;j++)
      {
       if (windows[i]->textboxes[j]->visible==true)
       {
         if (windows[i]->textboxes[j]->IsInControl(windows[i]->textboxes[j])==true)
         {
           int wintopbarh = windows[i]->height-windows[i]->clientheight;
           if (getarea(windows[i]->left+windows[i]->textboxes[j]->left,windows[i]->top+wintopbarh+windows[i]->textboxes[j]->top,windows[i]->textboxes[j]->width-(20+(wintopbarh/2)),windows[i]->textboxes[j]->height-(20+(wintopbarh/2))))
           {
             textarea = true;
             if (IsInAnyMenu()) textarea = false;
           }
           if (activewindow!=i)
           {
             if (windows[i]->IsInWindow(windows[activewindow])) textarea=false;
           }
         }
       }
      }
      for (int j=0;j<windows[i]->numbuttons;j++)
      {
       if (windows[i]->buttons[j]->visible==true)
       {
         if (windows[i]->buttons[j]->IsInControl(windows[i]->buttons[j])==true)
         {
           if (activewindow!=i)
           {
             if (windows[i]->IsInWindow(windows[activewindow]))
             {
               windows[i]->buttons[j]->focus = false;
               windows[i]->buttons[j]->focused = false;
               windows[i]->buttons[j]->clicked = false;
               btncontrolon=false;
             }
           }
         }
       }
      }
      for (int j=0;j<windows[i]->numspeedbuttons;j++)
      {
       if (windows[i]->speedbuttons[j]->visible==true)
       {
         if (windows[i]->speedbuttons[j]->IsInControl(windows[i]->speedbuttons[j])==true)
         {
           if (activewindow!=i)
           {
             if (windows[i]->IsInWindow(windows[activewindow]))
             {
               windows[i]->speedbuttons[j]->focus = false;
               windows[i]->speedbuttons[j]->focused = false;
               windows[i]->speedbuttons[j]->clicked = false;
               speedbtncontrolon=false;
             }
           }
         }
       }
      }
      for (int j=0;j<windows[i]->numtoolbuttons;j++)
      {
       if (windows[i]->toolbuttons[j]->visible==true)
       {
         if (windows[i]->toolbuttons[j]->IsInControl(windows[i]->toolbuttons[j])==true)
         {
           if (activewindow!=i)
           {
             if (windows[i]->IsInWindow(windows[activewindow]))
             {
               windows[i]->toolbuttons[j]->focus = false;
               windows[i]->toolbuttons[j]->focused = false;
               windows[i]->toolbuttons[j]->clicked = false;
               toolbtncontrolon=false;
             }
           }
         }
       }
      }
      for (int j=0;j<windows[i]->numupdowns;j++)
      {
        if (windows[i]->updowns[j]->updown_speedarea)
        {
          updownspeedarea = true;
          if (updownspeedarea)
          {
            if (windows[i]->updowns[j]->orientation == udHorizontal)
            {
              updownspeedarea_horiz = true;
            }
          }
        }
      }
     }
    }
    if (updownspeedarea == true)
    {
       if (updownspeedarea_horiz) setmousecursor(FEGUI_MOUSECURSOR_SIZEX);
       else setmousecursor(FEGUI_MOUSECURSOR_SIZEY);
    }
    else
    if (textarea==true)
    {
       setmousecursor(FEGUI_MOUSECURSOR_IBEAM);
    }
    else if (windowresizeside>0)
    {
       if (windowresizeside == RESIZEWIN_SCALE) setmousecursor(FEGUI_MOUSECURSOR_SIZEWZ);
       else if (windowresizeside == RESIZEWIN_LT) setmousecursor(FEGUI_MOUSECURSOR_SIZEWZ);
       else if (windowresizeside == RESIZEWIN_LH) setmousecursor(FEGUI_MOUSECURSOR_SIZEXZ);
       else if (windowresizeside == RESIZEWIN_WT) setmousecursor(FEGUI_MOUSECURSOR_SIZEXZ);
       else if (windowresizeside == RESIZEWIN_LEFT) setmousecursor(FEGUI_MOUSECURSOR_SIZEX);
       else if (windowresizeside == RESIZEWIN_TOP) setmousecursor(FEGUI_MOUSECURSOR_SIZEY);
       else if (windowresizeside == RESIZEWIN_WIDTH) setmousecursor(FEGUI_MOUSECURSOR_SIZEX);
       else if (windowresizeside == RESIZEWIN_HEIGHT) setmousecursor(FEGUI_MOUSECURSOR_SIZEY);
    }
    else
    {
     if (warea==true)
     {
        setmousecursor(FEGUI_MOUSECURSOR_ARROW);
     } else setmousecursor(FEGUI_MOUSECURSOR_XCURSOR);
    }
    glPointSize(1.0);
    fatal_error_exceptioncode += glGetError();
}
else
{

#ifdef TEST
  RECT winr,winrect;
  char buf[256];
  int winw = 800;
  int winh = 600;
  GetWindowRect(hWnd,&winr);
  width = winw;
  height = winh;
  SetWindowPos(hWnd,HWND_TOP,winr.left,winr.top,width,height, SWP_SHOWWINDOW);
#endif

int exceptioncode=0,dd=0,mm=0,yy=0,hr=0,mn=0,sc=0;
if (!fatal_error)
{
  if (fatal_error_exceptioncode <= 0) fatal_error_exceptioncode += 0x001f3500+glGetError();
  fatal_error_exceptionmessagecnt = getfatalerrormsgcount();
  setfatalerrormsglines();
  struct tm *now = NULL;
  time_t time_value = 0;
  time_value = time(NULL);
  now = localtime(&time_value);
  fatal_error_timestart_mday = now->tm_mday;
  fatal_error_timestart_mon = now->tm_mon+1;
  fatal_error_timestart_year = abs(100-now->tm_year);
  fatal_error_timestart_hour = now->tm_hour;
  fatal_error_timestart_min = now->tm_min;
  fatal_error_timestart_sec = now->tm_sec;
  fatal_error_timestart_timevalue = time_value;
}

fatal_error = true;
fillrect(0,0,getscreenwidth(),getscreenheight(),clBlue,255);
consoletextfont("");
consoletextcolor(clWhite);
if (fatal_error)
{
  int msg_yoffset_end=fatal_error_exceptionmessagecnt*12;
  int msg_len=fatal_error_exceptionmessagecnt;
  exceptioncode = fatal_error_exceptioncode;
  struct tm *now = NULL;
  time_t time_value = 0;
  time_value = time(NULL);
  now = localtime(&time_value);
  dd = fatal_error_timestart_mday;
  mm = fatal_error_timestart_mon;
  yy = fatal_error_timestart_year;
  hr = fatal_error_timestart_hour;
  mn = fatal_error_timestart_min;
  sc = fatal_error_timestart_sec;
  int st = (time_value-fatal_error_timestart_timevalue);
  shutdown_countdown = 15-st;
  if (shutdown_countdown<=0) shutdown_countdown = 0;
char buf[256];
sprintf(buf,"Fatal error: Window Manager has encountered a problem and needs to shutdown.");
consoletextout(8,32,buf);
sprintf(buf,"We are sorry for the inconvenience.");
consoletextout(8,44,buf);
sprintf(buf,"");
consoletextout(8,56,buf);
sprintf(buf,"This problem may have occurred while charging invalid address or stack overflow.");
consoletextout(8,68,buf);
sprintf(buf,"You can make a diagnosis of your system to solve this exception.");
consoletextout(8,80,buf);
sprintf(buf,"The cause of this exception is somehow wrong to carry out some instructions.");
consoletextout(8,92,buf);
sprintf(buf,"The problem could be due to several factors:");
consoletextout(8,104,buf);
sprintf(buf,"Corrupted files can crash some resources, resulting in the execution exceptions.");
consoletextout(8,116,buf);
sprintf(buf,"The virtual hard drive being defragmented can not interfere with list of folders and file index.");
consoletextout(8,128,buf);
sprintf(buf,"Also the error occurs when you try to find some non-existent window");
consoletextout(8,140,buf);
sprintf(buf,"The incompatibility of video card can cause some problems when loading textures, meshes, etc.");
consoletextout(8,152,buf);
sprintf(buf,"In addition, delays the generation of frames per second (FPS), leaving few resources to run.");
consoletextout(8,164,buf);
sprintf(buf,"We recommend that your system has with compatible video card and enough memory to run this game.");
consoletextout(8,176,buf);
sprintf(buf,"See the website www.dspinteractive.com the minimum system requirements to solve this problem.");
consoletextout(8,188,buf);
sprintf(buf,"");
int j=0;
for (int i=0;i<msg_len;i++)
{
consoletextout(8,200+j,buf);
sprintf(buf,"%s",fatal_error_exceptionmessageline[i].c_str());
j += 12;
}
consoletextout(8,200+msg_yoffset_end,buf);
sprintf(buf,"Exception occurred at 0x%08x on %02d/%02d/%02d %02d:%02d:%02d.",exceptioncode,dd,mm,yy,hr,mn,sc);
consoletextout(8,212+msg_yoffset_end,buf);
sprintf(buf,"Press Esc to turn off the program immediately.");
consoletextout(8,224+msg_yoffset_end,buf);
sprintf(buf,"The program will shut down in %d seconds.",shutdown_countdown);
consoletextout(8,236+msg_yoffset_end,buf);
if (shutdown_countdown<=0) PostQuitMessage(0);
if (keys[VK_ESCAPE])  PostQuitMessage(0);
}
}
  glViewport(0, 0, width, height);    // Set the viewport for the OpenGL window
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
  gluPerspective(45.0, width/height, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth

  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View

}

void appdestroy()
{
    fastpnglib_uninit();
    fevsl_uninit();
    fewebkit_uninit();
}


void setguipath(const char* path)
{
strcpy(guipath,path);
}

char* getguipath(void)
{
return guipath;
}


