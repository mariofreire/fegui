// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>
#include "application.h"


float theta = 0.0f;

int rotating=1;

WNDCLASS wc;
HWND hWnd;
HDC hDC;
HGLRC hRC;        
MSG msg;



TWindow *Window1;
TWindow *Window2;
TWindow *Window3;
TWindow *Window4;
TWindow *Window5;
TWindow *Window6;
TWindow *Window7;
TWindow *Window8;
TWindow *Window9;
TWindow *Window10;
TWindow *Window11;
TWindow *Window12;
TWindow *Window13;
TWindow *Window14;
TWindow *Window15;


LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);



void editmenudelete(TWinControl *sender);
void editmenuselectall(TWinControl *sender);

void scrollbar2change(TControl *sender)
{
     TScrollBar* scrollbar = dynamic_cast <TScrollBar*>((TScrollBar*)sender);
     TProgressBar* progressbar = dynamic_cast <TProgressBar*>((TProgressBar*)sender->window->progressbars[1]);
     progressbar->position = scrollbar->position;
     //Window1->color = RGB(0,0,scrollbar->position*2);
}

void scrollbar1change(TControl *sender)
{
     TScrollBar* scrollbar = dynamic_cast <TScrollBar*>((TScrollBar*)sender);
     TProgressBar* progressbar = dynamic_cast <TProgressBar*>((TProgressBar*)sender->window->progressbars[0]);
     progressbar->position = scrollbar->position;
  //   Window1->caption = ltoa(scrollbar->position);
}

void progressbar1change(TControl *sender)
{
     TProgressBar* progressbar = dynamic_cast <TProgressBar*>((TProgressBar*)sender);
  //   Window1->caption = ltoa(progressbar->position);
}

void progressbar2change(TControl *sender)
{
     TProgressBar* progressbar = dynamic_cast <TProgressBar*>((TProgressBar*)sender);
  //   Window1->caption = ltoa(progressbar->position);
}


void transparentbox1click(TControl *sender)
{

}

void checkbox1click(TControl *sender)
{

}

void checkbox2click(TControl *sender)
{
    TCheckBox* cb = dynamic_cast <TCheckBox*>((TCheckBox*)sender);
    bool fullscreen = cb->checked;
/*
    if (fullscreen)         // Attempt fullscreen mode?
	{
		DEVMODE dmScreenSettings;                                       // Device mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	        // Makes sure memory's cleared
		dmScreenSettings.dmSize         = sizeof(dmScreenSettings);     // Size of the devmode structure
		dmScreenSettings.dmPelsWidth	= width;                          // Selected screen width
		dmScreenSettings.dmPelsHeight	= height;                          // Selected screen height
		dmScreenSettings.dmBitsPerPel	= 32;	                        // Selected bits per pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
    		return;
		}
	}
*/
}

void radiobutton1click(TControl *sender)
{

}

void radiobutton2click(TControl *sender)
{

}

void radiobutton3click(TControl *sender)
{

}

void radiobutton4click(TControl *sender)
{

}

void changewindowsizeclick(TControl *sender)
{
  RECT r,rect;
  char buf[256];
  int w = 0;
  int h = 0;
  GetWindowRect(hWnd,&r);
  strcpy(buf,sender->caption);
  sscanf(buf,"%d x %d",&w,&h);
  width = w;
  height = h;
//  SetWindowText(hWnd,ltoa(w));
  SetWindowPos(hWnd,HWND_TOP,r.left,r.top,width,height, SWP_SHOWWINDOW);
            
  glViewport(0, 0, width, height);    // Set the viewport for the OpenGL window
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
  gluPerspective(45.0, width/height, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth

  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View

  glClearColor ((GetRValue(clBackground)/255.0), (GetGValue(clBackground)/255.0), (GetBValue(clBackground)/255.0), 0.0f);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glLoadIdentity();                                       // Reset The View

  glShadeModel(GL_SMOOTH);                 // Enables Smooth Color Shading
  glClearDepth(1.0);                       // Depth Buffer Setup
//  glEnable(GL_DEPTH_TEST);                 // Enable Depth Buffer
//  glDepthFunc(GL_LEQUAL);		           // The Type Of Depth Test To Do
  // glEnable (GL_LINE_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   //Realy Nice perspective calculations
  //glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  // glLineWidth (1.0);
  setviewport(0,0,width,height);
}

void edit1click(TControl *sender)
{
     
}

void edit2click(TControl *sender)
{

}

void edit1change(TControl *sender)
{
     TEdit* edit = dynamic_cast <TEdit*>((TEdit*)sender);
     Window1->caption = (char*)edit->text.c_str();
}

void edit2change(TControl *sender)
{
//     TEdit* edit = dynamic_cast <TEdit*>((TEdit*)sender);
//     Window1->hint = (char*)edit->text.c_str();
//     Window1->showhint = true;
//     Window1->caption = (char*)edit->text.c_str();
}

void listbox1click(TControl *sender)
{
     TListBox* listbox = dynamic_cast <TListBox*>((TListBox*)sender);
     if (listbox->itemindex>=0) sender->window->labels[1]->caption = (char*)listbox->items[listbox->itemindex].c_str();
//     listbox->additem("Item Novo");
}

void combobox1click(TControl *sender)
{
}

void speedbutton1click(TControl *sender)
{
  rotating = 1;
}

void speedbutton2click(TControl *sender)
{
  rotating = 0;
}


void button1click(TControl *sender)
{
  Window1->visible = false;
}

void button2click(TControl *sender)
{
  Window1->caption = "Nova janela";
  messagebox(Window1,"OpenGL GUI Sample - This feature is a part of FastEngine\nFast Engine Graphical User Interface\nAuthor: Mario Freire\nVersion: 0.01alpha\nCopyright © 2012 DSP Interactive. All rights reserved.\nDevelopment Systems and Programs\nSee more information in the website: https://www.dspinteractive.com.br   ","Mensagem",MB_OK|MB_ICONWARNING);

//  TButton *btn = dynamic_cast <TButton*>((TButton*)(sender));
//  btn->caption = "aa";
//  btn->visible = false;
//  btn->hide();
}

void button3click(TControl *sender)
{
  if (Window2->alphavalue>0) Window2->alphavalue-=4;
  if (Window2->alphavalue<=0) Window2->alphavalue = 0;
}

void button4click(TControl *sender)
{
  if (Window2->alphavalue<255) Window2->alphavalue+=4;
  if (Window2->alphavalue>=255)  Window2->alphavalue = 255;
}
int testenumero=0;
void panel1click(TControl *sender)
{
     char buf[256];
     sprintf(buf,"%i",testenumero);
     sender->caption = (char*)malloc(256);
     strcpy(sender->caption,buf);
     testenumero++;
}

void panel2click(TControl *sender)
{
}




#define expf(x) ((float)exp((x)))
#define sinf(x) ((float)sin((x)))
#define M_PI 3.14159265


static int rgb;
static int translate = 1;
static int mesh = 0;
static float ttrans[2];
static float transx, transy, rotx, roty;
static float amplitude = 0.08;
static float freq = 5.0f;
static float phase = .00003;
//static int ox = -1, oy = -1;
static int mot;
#define PAN	1
#define ROT	2

void ffunc(void) { freq *= 2.f; }
void Ffunc(void) { freq /= 2.f; }
void mfunc(void) { mesh ^= 1; }





void normalize(float v[3])
{
   GLfloat d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
   if (d == 0.0) {
      if (Window3) messagebox(Window3,"Zero length vector","Error",MB_OK|MB_ICONERROR);
      return;
   }
   v[0] /= d;
   v[1] /= d;
   v[2] /= d;
}

void normcrossprod(float v1[3], float v2[3], float out[3])
{
   out[0] = v1[1]*v2[2] - v1[2]*v2[1];
   out[1] = v1[2]*v2[0] - v1[0]*v2[2];
   out[2] = v1[0]*v2[1] - v1[1]*v2[0];
   normalize(out);
}

void drawtriangle(float *v1, float *v2, float *v3)
{
   glBegin(GL_TRIANGLES);
      glTexCoord2f(0, 0); 
      glNormal3fv(v1);
      glVertex3fv(v1);
      glTexCoord2f(1, 0); 
      glNormal3fv(v2);
      glVertex3fv(v2);
      glTexCoord2f(1, 1); 
      glNormal3fv(v3);
      glVertex3fv(v3);
   glEnd();
}



void subdivide(float *v1, float *v2, float *v3)
{
   GLfloat v12[3], v23[3], v31[3];
   GLint i;

   for (i = 0; i < 3; i++) {
      v12[i] = (v1[i]+v2[i])/2.0;
      v23[i] = (v2[i]+v3[i])/2.0;
      v31[i] = (v3[i]+v1[i])/2.0;
   }
   normalize(v12);
   normalize(v23);
   normalize(v31);
   drawtriangle(v1, v12, v31);
   drawtriangle(v2, v23, v12);
   drawtriangle(v3, v31, v23);
   drawtriangle(v12, v23, v31);
}

GLuint gTriangleNum=0;
float* g_pTriangles;

void buildTriangles(GLuint gTriangleStripNum,float g_pTriangleStrips[][3])
{
    gTriangleNum = gTriangleStripNum - 3 + 1;
    
    if (g_pTriangles) delete g_pTriangles;

    g_pTriangles = new float[gTriangleNum * 3];

    for (int i=0; i<gTriangleNum; i++)
    {
        if ((i%2)==0)
        {
            g_pTriangles[i*3+0]    = g_pTriangleStrips[i][0];
            g_pTriangles[i*3+1]    = g_pTriangleStrips[i][1];
            g_pTriangles[i*3+2]    = g_pTriangleStrips[i][2];
        }
        else
        {
            g_pTriangles[i*3+0]    = g_pTriangleStrips[i][2];
            g_pTriangles[i*3+1]    = g_pTriangleStrips[i][1];
            g_pTriangles[i*3+2]    = g_pTriangleStrips[i][0];
        }
    }

    return;
}

void wire(void) 
{
    static int w;
    if (w ^= 1) 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } 
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void light(void) 
{
    static int l;
    if (l ^= 1)
		glEnable(GL_LIGHTING);
    else
		glDisable(GL_LIGHTING);
}

void upkey(void) { amplitude += .01; }
void downkey(void) { amplitude -= .01; }
void leftkey(void) { phase -= .00001; }
void rightkey(void) { phase += .00001; }

void specialkeys(int key, int x, int y) 
{
     if (activewindow == Window3->windowid)
     {
        switch(key) 
        {
                case VK_UP:       upkey();    break;
                case VK_DOWN:     downkey();  break;
                case VK_LEFT:     leftkey();  break;
                case VK_RIGHT:    rightkey(); break;
        }
     }
}

void animate(void) 
{
    ttrans[0] += .005f;
    if (ttrans[0] == 1.0f) 
                ttrans[0] = 0.0f;
    ttrans[1] -= .0025f;
    if (ttrans[1] <= 0.0f) 
                ttrans[1] = 1.0f;
}

static float off;

void draw_mesh(void) 
{
//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    if (mesh)	//  ÒÔËÄ±ßÐÎÄ£Ê½½øÐÐ»æÖÆ
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-1.f, 0.f, -1.f);
		glTexCoord2f(0, 1); glVertex3f(-1.f, 0.f,  1.f);
		glTexCoord2f(1, 1); glVertex3f( 1.f, 0.f,  1.f);
		glTexCoord2f(1, 0); glVertex3f( 1.f, 0.f, -1.f);
		glEnd();
    } 
	else		//  ÒÔ¶à¸öÈý½ÇÐÎÃæÆ¬µÄÐÎÊ½½øÐÐ»æÖÆ
	{
		#define MESH 32
		float x0=0,y0=0,z0=0,s0=0,t0=0;
		int i, j, k;
//		static float off;
		float d = 1.f/MESH;
		for(i = 0; i < MESH; i++) 
		{
			glBegin(GL_TRIANGLE_STRIP);
			for(j = 0; j < MESH; j++) 
			{
				float s = (float)j*d;
				float t = (float)i*d;
				float x = -1.0 + 2.f*s;
				float z = -1.0 + 2.f*t;
				float y = amplitude*sinf(freq*2.f*M_PI*t+off);
				glTexCoord2f(s, t); glVertex3f(x, y, z);
				
				s += d; t += d;
				x = -1.0 + 2.f*s;
				z = -1.0 + 2.f*t;
				y = amplitude*sinf(freq*2.f*M_PI*t+off);
				glTexCoord2f(s, t); glVertex3f(x, y, z);
                
				x0=x;
				y0=y;
				z0=z;
				s0=s;
				t0=t;
				off += phase;
			}
			glEnd();
		}
		
    }
//    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

}

void displaywave(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(transx, transy, 0.f);
    glRotatef(rotx, 0., 1., 0.);
    glRotatef(roty, 1., 0., 0.);
    glScalef(10,1,10);
    if (!rgb)
		glColor3f(.31, .41, .97);
    else
		glColor3f(1.f,1.f,1.f);
    glTranslatef(0.f,-1.f,0.f);
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glTranslatef(ttrans[0], ttrans[1], 0.);
    glScalef(10.f, 10.f,1.f);
    draw_mesh();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    int keydown = 0;
    for (int i=0;i<256;i++)
    {
        if (keys[i]) keydown = i;
    }
    specialkeys(keydown,mousex,mousey);
    if (rotating) animate();
}


GLuint watertexture;

int LoadWaterTexture()
{
    BMP* water1;
    
    glEnable(GL_TEXTURE_2D);

    water1 = loadbmp("water1.bmp");
    
	if (water1)
	{
		glGenTextures(1, &watertexture);

		glBindTexture(GL_TEXTURE_2D, watertexture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, water1->width, water1->height, 0, GL_RGB, GL_UNSIGNED_BYTE, water1->bgr);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}

	if (water1)	
	{
		freebmp(water1);
	}

}

void viewport1render(TControl *sender)
{
    GLfloat black_color[4] = {0.00f,0.00f,0.00f,1.00f};//{ 1., 1., 1., 0., };
    GLfloat cloud_color[4] = {0.25, 1.0, 1.0, 1.0};//{ 1., 1., 1., 0., };
    GLfloat fog_color[4], fog_density = 0.05, density, far_cull;

    glPushMatrix();
     /* set up depth-buffering */
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.,1.,.1,far_cull = 10.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.,0.,-5.5);

    density = 1.- expf(-5.5 * fog_density * fog_density *
                              far_cull * far_cull);

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
    density = MAX(MIN(density, 1.), 0.);

    fog_color[0] = .45 + density *.05;
    fog_color[1] = 0.35 + density *.45;
    fog_color[2] = 0.95 + density *.05;
//    fog_color[0] = .23 + density *.57;
//    fog_color[1] = .35 + density *.45;
//    fog_color[2] = .78 + density *.22;

    glClearColor(fog_color[0], fog_color[1], fog_color[2], 1.f);

    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, fog_density);
    glFogfv(GL_FOG_COLOR, fog_color);
    if (fog_density > 0)
        glEnable(GL_FOG);
       /* future matrix manipulations should affect the modelview matrix */
    glMatrixMode(GL_MODELVIEW);
    
    int texon = glIsEnabled(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    /* draw scene */
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, watertexture);
    displaywave();    
    glPopMatrix();

    if (texon) glEnable(GL_TEXTURE_2D);
    else glDisable(GL_TEXTURE_2D);

     /* disable depth-buffering */
    glDisable(GL_DEPTH_TEST);
    /* turn off default lighting */
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glPopMatrix();
    if (rotating) theta+=2.0f;
     
}

void viewport2render(TControl *sender)
{
     
            glPushMatrix ();
            glRotatef(theta, 0.0f, 0.0f, 1.0f);
            glTranslatef(0,-1,0);
            glBegin (GL_QUADS);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (-0.25f, -0.25f);
            glColor3f (1.0f, 1.0f, 0.0f);   glVertex2f (0.25f, -0.25f);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (0.25f, 0.25f);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (-0.25f, 0.25f);
            glEnd ();
            glPopMatrix ();
            // if (rotating) theta+=2.0f;
     
    glPushMatrix();
     /* set up depth-buffering */
    glEnable(GL_DEPTH_TEST);

    /* turn on default lighting */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    /* define the projection transformation */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40,1,4,20);

    /* define the viewing transformation */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);

       /* future matrix manipulations should affect the modelview matrix */
    glMatrixMode(GL_MODELVIEW);

    /* draw scene */
    glPushMatrix();
    float m[4] = {0,1,0,1};           // green
    float mw[4] = {0,0.5,0,1};        // dark green
    
    // glRotatef(theta, 0.0f, 1.0f, 0.0f); // rotate camera

    // house
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m);
    glutSolidCube(2);                 // solid building
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mw);
    glutWireCube(2);                 // wireframe building

    glTranslatef(0,1,0);
    glPushMatrix();                   // roof
    glRotatef(-90,1,0,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m);
    glutSolidCone(1.5,1,16,8);
    glPopMatrix();

    glTranslatef(.75,.5,-.75);         
    glPushMatrix();                   // chimney
    glScalef(1,3,1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m);
    glutSolidCube(.25);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mw);
    glutWireCube(.25);
    glPopMatrix();
    glPopMatrix();

    glRotatef(theta, 0.0f, 1.0f, 0.0f); // rotate car
    glTranslatef(0,-.65,2);

    // car
    glPushMatrix();
    glPushMatrix();                   // body
    glScalef(2,.5,1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m);
    glutSolidCube(.5);
    glPopMatrix();
    glTranslatef(0,0,.25);
    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glTranslatef(.8,0,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glPopMatrix();
    glTranslatef(0,0,-.5);
    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glTranslatef(.8,0,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
     /* disable depth-buffering */
    glDisable(GL_DEPTH_TEST);
    /* turn off default lighting */
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glPopMatrix();
    if (rotating) theta+=2.0f;
}

void menuitem1click(TWinControl *sender)
{
 if (WindowExists(Window6))
 {
  Window6->visible = true;
 }
}

void menuitem2click(TWinControl *sender)
{
 if (WindowExists(Window1))
 {
  Window1->visible = false;
 }
}

void menusubitem4click(TWinControl *sender)
{
 if (WindowExists(Window12))
 {
  Window12->visible = true;
  setforegroundwindow(Window12->windowid);
 }
}

void menuitem4click(TWinControl *sender)
{
  menues[2]->menu->items[5]->checked = !menues[2]->menu->items[5]->checked;
}

void menuitem2item1click(TWinControl *sender)
{
 if (WindowExists(Window13))
 {
  Window13->visible = true;
  setforegroundwindow(Window13->windowid);
 }
}



void window7showclick(TWinControl *sender)
{
 if (WindowExists(Window7))
 {
  Window7->visible = true;
  activewindow = Window7->windowid;
 }
}

void window8showclick(TControl *sender)
{
 if (WindowExists(Window8))
 {
  Window8->progressbars[0]->position = 0;
  Window8->visible = true;
  activewindow = Window8->windowid;
 }
}

void window14showclick(TControl *sender)
{
 if (WindowExists(Window14))
 {
  Window14->visible = true;
  activewindow = Window14->windowid;
  Window14->videoplayers[0]->play();
 }
}

void window15showclick(TControl *sender)
{
 if (WindowExists(Window15))
 {
  Window15->visible = true;
  activewindow = Window15->windowid;
 }
}

void glyphbutton1click(TControl *sender)
{
 if (WindowExists(Window8))
 {
  Window8->progressbars[0]->position = 0;
  Window8->visible = true;
  activewindow = Window8->windowid;
 }
}

void glyphbutton2click(TControl *sender)
{
 if (WindowExists(Window11))
 {
  Window11->visible = true;
  activewindow = Window11->windowid;
 }
}

void timer1timer(TComponent *sender)
{
 TTimer* timer = dynamic_cast <TTimer*>((TTimer*)sender);
 timer->window->progressbars[0]->position++;
 if (timer->window->progressbars[0]->position>=timer->window->progressbars[0]->max) timer->window->progressbars[0]->position=timer->window->progressbars[0]->max;
}




FEGUI_CALLBACK FILE* feguiopen (const char* filename, const char* mode)
{
  return fopen(filename,mode);
}
FEGUI_CALLBACK int feguiclose (FILE* stream)
{
  return fclose(stream);
}
FEGUI_CALLBACK long feguitell (FILE* stream)
{
  return ftell(stream);
}
FEGUI_CALLBACK int feguiseek (FILE* stream, long offset, int whence)
{
  return fseek(stream,offset,whence);
}
FEGUI_CALLBACK size_t feguiread (void* ptr, size_t size, size_t n, FILE* stream)
{
  return fread(ptr,size,n,stream);
}
FEGUI_CALLBACK size_t feguiwrite (const void* ptr, size_t size, size_t n, FILE* stream)
{
  return fwrite(ptr,size,n,stream);
}




/**************************
 * WinMain
 *
 **************************/


int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    BOOL bQuit = FALSE;
    float theta = 0.0f;
    int i=0;
    char wintext[256];
    TSpeedButton *speedbutton1;
    TSpeedButton *speedbutton2;
    TLabel *label1;
    TLabel *label2;
    TLabel *label3;
    TLabel *label4;
    TLabel *label5;
    TEdit *edit1;
    TEdit *edit2;
    TTextBox *textbox1;
    TCheckBox *checkbox1;
    TCheckBox *checkbox2;
    TRadioButton *radiobutton1;
    TRadioButton *radiobutton2;
    TRadioButton *radiobutton3;
    TRadioButton *radiobutton4;
    TRadioButton *radiobutton5;
    TRadioButton *radiobutton6;
    TRadioButton *radiobutton7;
    TScrollBar *scrollbar1;
    TScrollBar *scrollbar2;
    TProgressBar *progressbar1;
    TProgressBar *progressbar2;
    TProgressBar *progressbar3;
    TButton *button1;
    TButton *button2;
    TButton *button3;
    TButton *button4;
    TButton *button5;
    TButton *button6;
    TButton *button7;
    TGroupBox *groupbox1;
    TGroupBox *groupbox2;
    TGroupBox *groupbox3;
    TPanel *panel1;
    TPanel *panel2;
    TPanel* panel3;
    TPanel* panel4;
    TBevel* bevel1;
    TTransparentBox *transparentbox1;
    TListBox *listbox1;
    TComboBox *combobox1;
    TShape* shape1;
    TImage* image1;
    TImage* image2;
    TImage* image3;
    TGlyphButton* glyphbutton1;
    TGlyphButton* glyphbutton2;
    TTimer* timer1;
    TViewport *viewport1;
    TImageList* imagelist1;
    TImageList* imagelist2;
    TImageList* imagelist3;
    TToolBar* toolbar1;
    TToolBar* toolbar2;
    TToolBar* toolbar3;
    TDockBar* dockbar1;
    TToolButton* toolbutton1;
    TToolButton* toolbutton2;
    TToolButton* toolbutton3;
    TToolButton* toolbutton4;
    TToolButton* toolbutton5;
    TToolButton* toolbutton6;
    TToolButton* toolbutton7;
    TMainMenu* mainmenu1;
    TTrackBar* trackbar1;
    TTrackBar* trackbar2;
    TTrackBar* trackbar3;
    TTrackBar* trackbar4;
    TUpDown* updown1;
    TUpDown* updown2;
    TUpDown* updown3;
    TUpDown* updown4;
    TEdit* edit3;
    TVideoPlayer* videoplayer1;
    TListView* listview1;
    

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL GUI Sample by Mario Freire", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      left+64, top+64, width, height+25,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);      
    
    appcreate();
    
    fegui_setfilesystem(feguiopen,feguiclose,feguiread,feguiwrite,feguitell,feguiseek);    
    
    appinit();
    
    Window1 = new TWindow();
    Window1->borderstyle = bsSingle;
    Window1->caption="Window 1";
    Window1->left = 200;
    Window1->top = 32;    
    Window1->width = 320;
    Window1->height = 260;
    Window1->alphavalue = 255;
    Window1->visible = true;
    
    Window2 = new TWindow();
    Window2->borderstyle = bsDialog;
    Window2->caption="Window 2";
    Window2->left = 32;
    Window2->top = 164;    
    Window2->width = 150;
    Window2->height = 200;
    Window2->alphavalue = 255;
    Window2->subtessleft = 0;
    Window2->subtesstop = 0;
    Window2->subtesswidth = 0;
    Window2->subtessheight = 0;
    Window2->color = clBtnFace;
    Window2->visible = true;
    
    Window3 = new TWindow();
    Window3->borderstyle = bsSizeable;
    Window3->caption="Window 3";
    Window3->left = 300;
    Window3->top = 315;    
    Window3->width = 320;
    Window3->height = 240;
    Window3->alphavalue = 255;
    Window3->visible = true;
    
    Window4 = new TWindow();
    Window4->borderstyle = bsDialog;
    Window4->caption="Window 4";
    Window4->left = 24;
    Window4->top = 384;    
    Window4->width = 256;
    Window4->height = 128;
    Window4->alphavalue = 255;
    Window4->visible = true;
    
    Window5 = new TWindow();
    Window5->borderstyle = bsSingle;
    Window5->caption="Window 5";
    Window5->left = 530;
    Window5->top = 48;    
    Window5->width = 256;
    Window5->height = 256;
    Window5->alphavalue = 255;
    Window5->visible = true;
    
    Window6 = new TWindow();
    Window6->borderstyle = bsSizeable;
    Window6->caption="Window 6";
    Window6->left = 530;
    Window6->top = 320;    
    Window6->width = 256;
    Window6->height = 256;
    Window6->alphavalue = 255;
    Window6->visible = false;

    Window7 = new TWindow();
    Window7->borderstyle = bsSizeable;
    Window7->caption="Window 7";
    Window7->left = 300;
    Window7->top = 315;    
    Window7->width = 320;
    Window7->height = 260;
    Window7->alphavalue = 255;
    Window7->visible = false;

    Window8 = new TWindow();
    Window8->borderstyle = bsSizeable;
    Window8->caption="Window 8";
    Window8->left = 20;
    Window8->top = 45;    
    Window8->width = 600;
    Window8->height = 320;
    Window8->alphavalue = 255;
    Window8->visible = false;

    Window9 = new TWindow();
    Window9->borderstyle = bsSingle;
    Window9->caption="Window 9";
    Window9->left = 64;
    Window9->top = 48;    
    Window9->width = 512;
    Window9->height = 256;
    Window9->alphavalue = 255;
    Window9->visible = true;

    Window10 = new TWindow();
    Window10->borderstyle = bsDialog;
    Window10->caption="Dump Report Debug - There was one exception in the program and will be closed";
    Window10->left = 32;
    Window10->top = 32;    
    Window10->width = 732;
    Window10->height = 532;
    Window10->alphavalue = 255;
    Window10->visible = false;
    
    Window11 = new TWindow();
    Window11->borderstyle = bsDialog;
    Window11->caption="Opções";
    Window11->left = 164;
    Window11->top = 164;    
    Window11->width = 135;
    Window11->height = 153;
    Window11->alphavalue = 255;
    Window11->subtessleft = 0;
    Window11->subtesstop = 0;
    Window11->subtesswidth = 0;
    Window11->subtessheight = 0;
    Window11->color = clBtnFace;
    Window11->visible = false;
    
    Window12 = new TWindow();
    Window12->borderstyle = bsDialog;
    Window12->caption="Window 12";
    Window12->left = 164;
    Window12->top = 164;    
    Window12->width = 200;
    Window12->height = 153;
    Window12->alphavalue = 255;
    Window12->subtessleft = 0;
    Window12->subtesstop = 0;
    Window12->subtesswidth = 0;
    Window12->subtessheight = 0;
    Window12->color = clBtnFace;
    Window12->visible = false;
    
    Window13 = new TWindow();
    Window13->borderstyle = bsSingle;
    Window13->caption="Window 13";
    Window13->left = 216;
    Window13->top = 48;    
    Window13->width = 320;
    Window13->height = 260;
    Window13->alphavalue = 255;
    Window13->visible = false;
    
    Window14 = new TWindow();
    Window14->borderstyle = bsSingle;
    Window14->caption="Window 14";
    Window14->left = 132;
    Window14->top = 64;    
    Window14->width = 600;
    Window14->height = 480;
    Window14->alphavalue = 255;
    Window14->visible = false;
    
    Window15 = new TWindow();
    Window15->borderstyle = bsSingle;
    Window15->caption="Window 15";
    Window15->left = 64;
    Window15->top = 64;    
    Window15->width = 400;
    Window15->height = 320;
    Window15->alphavalue = 255;
    Window15->visible = false;
    
    speedbutton1 = new TSpeedButton(Window1);
    speedbutton2 = new TSpeedButton(Window1); 

    label1 = new TLabel(Window2); 
    label2 = new TLabel(Window2); 
    label3 = new TLabel(Window5); 
    label4 = new TLabel(Window5); 
    label5 = new TLabel(Window1); 

    edit1 = new TEdit(Window1); 
    edit2 = new TEdit(Window1); 
    edit3 = new TEdit(Window13); 

    textbox1 = new TTextBox(Window6); 

    checkbox1 = new TCheckBox(Window1); 
    checkbox2 = new TCheckBox(Window11); 

    radiobutton1 = new TRadioButton(Window4); 
    radiobutton2 = new TRadioButton(Window4); 
    radiobutton3 = new TRadioButton(Window4); 
    radiobutton4 = new TRadioButton(Window4); 
    radiobutton5 = new TRadioButton(Window11); 
    radiobutton6 = new TRadioButton(Window11); 
    radiobutton7 = new TRadioButton(Window11); 

    progressbar1 = new TProgressBar(Window1); 
    progressbar2 = new TProgressBar(Window1); 
    progressbar3 = new TProgressBar(Window8); 

    scrollbar1 = new TScrollBar(Window1); 
    scrollbar2 = new TScrollBar(Window1); 

    button1 = new TButton(Window1);
    button2 = new TButton(Window1); 

    button3 = new TButton(Window2);
    button4 = new TButton(Window2); 

    groupbox1 = new TGroupBox(Window4);
    groupbox2 = new TGroupBox(Window4); 
    groupbox3 = new TGroupBox(Window11); 

    panel1 = new TPanel(Window1);
    panel2 = new TPanel(Window1); 
    panel3 = new TPanel(Window7); 
    panel4 = new TPanel(Window7); 
    bevel1 = new TBevel(Window10); 
    button5 = new TButton(Window7); 

    transparentbox1 = new TTransparentBox(Window9);

    listbox1 = new TListBox(Window5);

    combobox1 = new TComboBox(Window5);

    shape1 = new TShape(Window7);

    image1 = new TImage(Window7);
    image2 = new TImage(Window8);
    image3 = new TImage(Window10);
    
    glyphbutton1 = new TGlyphButton(Window7);
    glyphbutton2 = new TGlyphButton(Window7);

    timer1 = new TTimer(Window8);
    
    viewport1 = new TViewport(Window3);

    imagelist1 = new TImageList(Window12);
    imagelist2 = new TImageList(Window15);
    imagelist3 = new TImageList(Window15);
    
    toolbar1 = new TToolBar(Window12);
    toolbar2 = new TToolBar(Window12);
    toolbar3 = new TToolBar(Window12);

    dockbar1 = new TDockBar(Window12);
    
    toolbutton1 = new TToolButton(Window12);
    toolbutton2 = new TToolButton(Window12);
    toolbutton3 = new TToolButton(Window12);
    toolbutton4 = new TToolButton(Window12);
    toolbutton5 = new TToolButton(Window12);
    toolbutton6 = new TToolButton(Window12);
    toolbutton7 = new TToolButton(Window12);
    
    mainmenu1 = new TMainMenu(Window12);
    
    updown1 = new TUpDown(Window13);
    updown2 = new TUpDown(Window13);
    updown3 = new TUpDown(Window13);
    updown4 = new TUpDown(Window13);
    
    trackbar1 = new TTrackBar(Window13);
    trackbar2 = new TTrackBar(Window13);
    trackbar3 = new TTrackBar(Window13);
    trackbar4 = new TTrackBar(Window13);

    button6 = new TButton(Window13); 
    button7 = new TButton(Window13); 
    
    videoplayer1 = new TVideoPlayer(Window14);
    videoplayer1->filename = //"01f.bik";
    //"dsplogo.bik";
    //"video.bik";  //
    //"mms://aovivo.tvpontanegra.com.br/tvpnaovivo";
    "1.avi";

    listview1 = new TListView(Window15);

    imagelist1->addimage("run.bmp");
    imagelist1->images[0]->transparentcolor = clBlue;
    imagelist1->images[0]->transparent = true;
    imagelist1->addimage("pause.bmp");
    imagelist1->images[1]->transparentcolor = clBlue;
    imagelist1->images[1]->transparent = true;
    imagelist1->addimage("form.bmp");
    imagelist1->images[2]->transparentcolor = clBlue;
    imagelist1->images[2]->transparent = true;
    imagelist1->addimage("close.bmp");
    imagelist1->images[3]->transparentcolor = clLime;
    imagelist1->images[3]->transparent = true;
    imagelist1->addimage("package.bmp");
    imagelist1->images[4]->transparentcolor = clLime;
    imagelist1->images[4]->transparent = true;
    imagelist1->addimage("formlist.bmp");
    imagelist1->images[5]->transparentcolor = clLime;
    imagelist1->images[5]->transparent = true;
    imagelist1->addimage("formtemp.bmp");
    imagelist1->images[6]->transparentcolor = clLime;
    imagelist1->images[6]->transparent = true;

    imagelist2->addimage("warning.bmp");
    imagelist2->images[0]->transparentcolor = clBlue;
    imagelist2->images[0]->transparent = true;
    imagelist2->addimage("error.bmp");
    imagelist2->images[1]->transparentcolor = clBlue;
    imagelist2->images[1]->transparent = true;
    imagelist2->addimage("information.bmp");
    imagelist2->images[2]->transparentcolor = clBlue;
    imagelist2->images[2]->transparent = true;

    imagelist3->addimage("package.bmp");
    imagelist3->images[0]->transparentcolor = clLime;
    imagelist3->images[0]->transparent = true;
    imagelist3->addimage("form.bmp");
    imagelist3->images[1]->transparentcolor = clBlue;
    imagelist3->images[1]->transparent = true;
    imagelist3->addimage("formlist.bmp");
    imagelist3->images[2]->transparentcolor = clLime;
    imagelist3->images[2]->transparent = true;

    dockbar1->caption="";
    dockbar1->left = 8;
    dockbar1->top = 32;
    dockbar1->width = 190;
    dockbar1->height = 28;
    dockbar1->bevelinner = bvNone;
    dockbar1->bevelouter = bvNone;
    dockbar1->enabled = true;
    dockbar1->visible = true;

    toolbar1->images = NULL;
    toolbar1->caption="";
    toolbar1->left = 8;
    toolbar1->top = 32;
    toolbar1->width = 90;
    toolbar1->height = 24;
    toolbar1->bevelinner = bvNone;
    toolbar1->bevelouter = bvNone;
    toolbar1->enabled = true;
    toolbar1->parent = dockbar1;
    toolbar1->visible = true;

    toolbar2->images = imagelist1;
    toolbar2->caption="";
    toolbar2->left = 8;
    toolbar2->top = 92;
    toolbar2->width = 90;
    toolbar2->height = 24;
    toolbar2->bevelinner = bvNone;
    toolbar2->bevelouter = bvNone;
    toolbar2->enabled = true;
    toolbar2->parent = dockbar1;
    toolbar2->visible = true;

    toolbar3->images = imagelist1;
    toolbar3->caption="";
    toolbar3->left = 8;
    toolbar3->top = 63;
    toolbar3->width = 68;
    toolbar3->height = 24;
    toolbar3->bevelinner = bvNone;
    toolbar3->bevelouter = bvNone;
    toolbar3->enabled = true;
    toolbar3->parent = dockbar1;
    toolbar3->visible = true;

    toolbutton1->caption = "";
    toolbutton1->hint = "Executar";
    toolbutton1->index = 0;
    toolbutton1->imageindex = 0;
    toolbutton1->showhint = true;
    toolbutton1->enabled = true;
    toolbutton1->parent = toolbar2;
    toolbutton1->visible = true;
    
    toolbutton2->caption = "";
    toolbutton2->hint = "Pausar";
    toolbutton2->index = 1;
    toolbutton2->imageindex = 1;
    toolbutton2->showhint = true;
    toolbutton2->enabled = true;
    toolbutton2->parent = toolbar2;
    toolbutton2->visible = true;
    
    toolbutton3->caption = "";
    toolbutton3->hint = "Criar formulário";
    toolbutton3->index = 2;
    toolbutton3->imageindex = 2;
    toolbutton3->showhint = true;
    toolbutton3->enabled = true;
    toolbutton3->parent = toolbar2;
    toolbutton3->visible = true;
    
    toolbutton4->caption = "";
    toolbutton4->hint = "Fechar";
    toolbutton4->index = 3;
    toolbutton4->imageindex = 3;
    toolbutton4->showhint = true;
    toolbutton4->enabled = true;
    toolbutton4->parent = toolbar2;
    toolbutton4->visible = true;
    
    toolbutton5->caption = "";
    toolbutton5->hint = "Pacotes";
    toolbutton5->index = 0;
    toolbutton5->imageindex = 4;
    toolbutton5->showhint = true;
    toolbutton5->enabled = true;
    toolbutton5->parent = toolbar3;
    toolbutton5->visible = true;
    
    toolbutton6->caption = "";
    toolbutton6->hint = "Lista de formulários";
    toolbutton6->index = 1;
    toolbutton6->imageindex = 5;
    toolbutton6->showhint = true;
    toolbutton6->enabled = true;
    toolbutton6->parent = toolbar3;
    toolbutton6->visible = true;
    
    toolbutton7->caption = "";
    toolbutton7->hint = "Template de formulário";
    toolbutton7->index = 2;
    toolbutton7->imageindex = 6;
    toolbutton7->showhint = true;
    toolbutton7->enabled = true;
    toolbutton7->parent = toolbar3;
    toolbutton7->visible = true;

    speedbutton1->left = 32;
    speedbutton1->top = 90;
    speedbutton1->width = 80;
    speedbutton1->height = 22;
    speedbutton1->caption = "Executar";
    speedbutton1->hint = "Execute a animação OpenGL.";
    speedbutton1->showhint = true;
    speedbutton1->onclick = speedbutton1click;
    speedbutton1->flat = true;
    speedbutton1->loadicon("run.bmp");
    speedbutton1->enabled = true;
    speedbutton1->visible = true;
    

    speedbutton2->left = 200;
    speedbutton2->top = 90;
    speedbutton2->width = 72;
    speedbutton2->height = 22;
    speedbutton2->caption = "Parar";
    speedbutton2->hint = "Pare a animação OpenGL.";
    speedbutton2->showhint = true;
    speedbutton2->onclick = speedbutton2click;
    speedbutton2->flat =true;
    speedbutton2->loadicon("pause.bmp");
    speedbutton2->visible = true;

    label1->left = 32;
    label1->top = 32;
    label1->width = 64;
    label1->height = 25;
    label1->caption = "Label1";
    label1->visible = true;

    label2->left = 32;
    label2->top = 148;
    label2->width = 96;
    label2->height = 25;
    label2->caption = "Label2";
    label2->visible = true;

    label3->left = 32;
    label3->top = 32;
    label3->width = 98;
    label3->height = 25;
    label3->caption = "Item selecionado: ";
    label3->visible = true;

    label4->left = 132;
    label4->top = 32;
    label4->width = 96;
    label4->height = 25;
    label4->caption = "(nenhum)";
    label4->visible = true;

    label5->left = 32;
    label5->top = 125;
    label5->width = 65;
    label5->height = 20;
    label5->caption = "Novo rótulo sem definição.";
    label5->wordwrap = true;
    label5->autosize = true;
    label5->visible = true;

    edit1->left = 32;
    edit1->top = 164;
    edit1->width = 128;
    edit1->height = 25;
    edit1->text = "Edit1";
    edit1->hint = "Escreva seu texto aqui.";
    edit1->showhint = true;
//    edit1->maxlength = 0;
//    edit1->readonly = true;
    edit1->onclick = edit1click;
    edit1->onchange = edit1change;
    edit1->visible = true;

    edit2->left = 32;
    edit2->top = 196;
    edit2->width = 128;
    edit2->height = 25;
    edit2->text = "Edit2";
    edit2->onclick = edit2click;
    edit2->onchange = edit2change;
    edit2->visible = true;

    edit3->left = 16;
    edit3->top = 166;
    edit3->width = 64;
    edit3->height = 24;
    edit3->text = "0";
    edit3->visible = true;

    textbox1->left = 16;
    textbox1->top = 16;
    textbox1->width = 232;
    textbox1->height = 200;  
    textbox1->text = "Maresia Surf International \ntermina no domingo e na terça-feira\ncomeça outro WQS 6 estrelas\n";
    textbox1->maxlength = 0;
    textbox1->readonly = false;
    textbox1->visible = true;
    
    textbox1->align = alClient;
    Window6->width = 248;
    Window6->height = 150;

    checkbox1->left = 200;
    checkbox1->top = 132;
    checkbox1->width = 85;
    checkbox1->height = 20;
    checkbox1->caption = "checkbox1";
    checkbox1->onclick = checkbox1click;
    checkbox1->visible = true;

    checkbox2->left = 8;
    checkbox2->top = 8;
    checkbox2->width = 85;
    checkbox2->height = 20;
    checkbox2->caption = "Tela inteira";
    checkbox2->onclick = checkbox2click;
    checkbox2->visible = true;

    radiobutton1->left = 20;
    radiobutton1->top = 32;
    radiobutton1->width = 96;
    radiobutton1->height = 20;
    radiobutton1->groupindex = 0;
    radiobutton1->checked = true;
    radiobutton1->caption = "radiobutton1";
    radiobutton1->onclick = radiobutton1click;
    radiobutton1->visible = true;

    radiobutton2->left = 20;
    radiobutton2->top = 64;
    radiobutton2->width = 96;
    radiobutton2->height = 20;
    radiobutton2->groupindex = 0;
    radiobutton2->caption = "radiobutton2";
    radiobutton2->onclick = radiobutton2click;
    radiobutton2->visible = true;

    radiobutton3->left = 140;
    radiobutton3->top = 32;
    radiobutton3->width = 96;
    radiobutton3->height = 20;
    radiobutton3->groupindex = 1;
    radiobutton3->caption = "radiobutton3";
    radiobutton3->onclick = radiobutton3click;
    radiobutton3->visible = true;

    radiobutton4->left = 140;
    radiobutton4->top = 64;
    radiobutton4->width = 96;
    radiobutton4->height = 20;
    radiobutton4->groupindex = 1;
    radiobutton4->checked = true;
    radiobutton4->caption = "radiobutton4";
    radiobutton4->onclick = radiobutton4click;
    radiobutton4->visible = true;

    radiobutton5->left = 16;
    radiobutton5->top = 52;
    radiobutton5->width = 96;
    radiobutton5->height = 20;
    radiobutton5->groupindex = 0;
    radiobutton5->checked = false;
    radiobutton5->caption = "640 x 480";
    radiobutton5->onclick = changewindowsizeclick;
    radiobutton5->visible = true;

    radiobutton6->left = 16;
    radiobutton6->top = 72;
    radiobutton6->width = 96;
    radiobutton6->height = 20;
    radiobutton6->groupindex = 0;
    radiobutton6->checked = true;
    radiobutton6->caption = "800 x 600";
    radiobutton6->onclick = changewindowsizeclick;
    radiobutton6->visible = true;

    radiobutton7->left = 16;
    radiobutton7->top = 92;
    radiobutton7->width = 96;
    radiobutton7->height = 20;
    radiobutton7->groupindex = 0;
    radiobutton7->checked = false;
    radiobutton7->caption = "1024 x 768";
    radiobutton7->onclick = changewindowsizeclick;
    radiobutton7->visible = true;

    scrollbar1->left = 164;
    scrollbar1->top = 164;
    scrollbar1->width = 121;
    scrollbar1->height = 20;
    scrollbar1->kind = sbHorizontal;
    scrollbar1->onchange = scrollbar1change;
    scrollbar1->visible = true;

    scrollbar2->left = 128;
    scrollbar2->top = 16;
    scrollbar2->width = 20;
    scrollbar2->height = 121;
    scrollbar2->kind = sbVertical;
    scrollbar2->onchange = scrollbar2change;
    scrollbar2->visible = true;

    progressbar1->left = 164;
    progressbar1->top = 194;
    progressbar1->width = 122;
    progressbar1->height = 20;
    progressbar1->min = 0;
    progressbar1->max = 100;
    progressbar1->step = 10;
    progressbar1->blockspace = 2;
    progressbar1->blocksize = 10;
    progressbar1->smooth = false;
    progressbar1->orientation = pbHorizontal;
    progressbar1->onchange = progressbar1change;
    progressbar1->visible = true;

    progressbar2->left = 164;
    progressbar2->top = 16;
    progressbar2->width = 20;
    progressbar2->height = 123;
    progressbar2->min = 0;
    progressbar2->max = 100;
    progressbar2->blockspace = 2;
    progressbar2->blocksize = 10;
    progressbar2->step = 10;
    progressbar2->smooth = false;
    progressbar2->orientation = pbVertical;
    progressbar2->onchange = progressbar2change;
    progressbar2->visible = true;

    progressbar3->left = 164;
    progressbar3->top = 194;
    progressbar3->width = 122;
    progressbar3->height = 20;
    progressbar3->min = 0;
    progressbar3->max = 100;
    progressbar3->step = 10;
    progressbar3->blockspace = 2;
    progressbar3->blocksize = 10;
    progressbar3->smooth = false;
    progressbar3->orientation = pbHorizontal;
    progressbar3->onchange = progressbar1change;
    progressbar3->visible = true;

    button1->left = 32;
    button1->top = 16;
    button1->width = 72;
    button1->height = 23;
    button1->caption = "Fechar";
    button1->onclick = button1click;
    button1->visible = true;

    button2->left = 200;
    button2->top = 16;
    button2->width = 72;
    button2->height = 22;
    button2->caption = "Mensagem";
    button2->onclick = button2click;
    button2->visible = true;

    button3->left = 20;
    button3->top = 80;
    button3->width = 72;
    button3->height = 23;
    button3->caption = "Alpha--";
    button3->onclick = button3click;
    button3->visible = true;

    button4->left = 20;
    button4->top = 110;
    button4->width = 72;
    button4->height = 23;
    button4->caption = "Alpha++";
    button4->onclick = button4click;
    button4->visible = true;

    button5->left = 150;
    button5->top = 8;
    button5->width = 72;
    button5->height = 28;
    button5->caption = "Window 8";
    button5->onclick = window8showclick;
    button5->alphavalue = 255;
    button5->visible = true;

    button6->left = 32;
    button6->top = 92;
    button6->width = 72;
    button6->height = 28;
    button6->caption = "Window 14";
    button6->onclick = window14showclick;
    button6->alphavalue = 255;
    button6->visible = true;

    button7->left = 32;
    button7->top = 24;
    button7->width = 72;
    button7->height = 28;
    button7->caption = "Window 15";
    button7->onclick = window15showclick;
    button7->alphavalue = 255;
    button7->visible = true;

    listview1->left = 32;
    listview1->top = 24;
    listview1->width = 320;
    listview1->height = 240;
    listview1->alphavalue = 255;
    listview1->visible = true;
    listview1->largeimages = imagelist2;
    listview1->smallimages = imagelist3;
    TListItem* listview1item1 = listview1->items->additem();
    listview1item1->caption = "Item 1";
    listview1item1->imageindex = 0;
    TListItem* listview1item2 = listview1->items->additem();
    listview1item2->caption = "Item 2";
    listview1item2->imageindex = 1;
    TListItem* listview1item3 = listview1->items->additem();
    listview1item3->caption = "Item 3";
    listview1item3->imageindex = 2;

    panel1->left = 32;
    panel1->top = 48;
    panel1->width = 72;
    panel1->height = 32;
    panel1->caption = "Panel1";
    panel1->onclick = panel1click;
    panel1->visible = true;

    panel2->left = 200;
    panel2->top = 48;
    panel2->width = 72;
    panel2->height = 32;
    panel2->caption = "Panel2";
    panel2->onclick = panel2click;
    panel2->bevelouter = bvLowered;
    panel2->color = clBtnFace;
    panel2->visible = true;

    panel3->left = 32;
    panel3->top = 128;
    panel3->width = 128;
    panel3->height = 96;
    panel3->caption = "Panel";
    panel3->color = clRed;
    panel3->bevelouter = bvLowered;
    panel3->visible = true;

    panel4->left = 18;
    panel4->top = 118;
    panel4->width = 64;
    panel4->height = 64;
    panel4->caption = "Panel";
    panel4->color = clLime;
    panel4->alphavalue = 128;
//    panel4->parent = Window7;
//    panel4->window = Window7;
    panel4->visible = true;

    bevel1->left = 13;
    bevel1->top = 9;
    bevel1->width = 323;
    bevel1->height = 484;
    bevel1->caption = "";
    bevel1->bevelouter = bvNone;
    bevel1->borderstyle = bsSingle;
    bevel1->visible = true;

    groupbox1->left = 16;
    groupbox1->top = 4;
    groupbox1->width = 108;
    groupbox1->height = 90;
    groupbox1->caption = "groupbox1";
    groupbox1->visible = true;

    groupbox2->left = 134;
    groupbox2->top = 4;
    groupbox2->width = 108;
    groupbox2->height = 90;
    groupbox2->caption = "groupbox2";
    groupbox2->visible = true;

    groupbox3->left = 8;
    groupbox3->top = 28;
    groupbox3->width = 116;
    groupbox3->height = 94;
    groupbox3->caption = "Modos de vídeo";
    groupbox3->visible = true;

    transparentbox1->left = 8;
    transparentbox1->top = 2;
    transparentbox1->width = 492;
    transparentbox1->height = 216;
    transparentbox1->borderstyle = bsSingle;
    transparentbox1->color = clBlack;
    transparentbox1->backgroundalpha = 192;
    transparentbox1->caption = "/data/maps]";
    transparentbox1->onclick = transparentbox1click;
    transparentbox1->alphavalue = 255;
    transparentbox1->visible = true;

    listbox1->left = 32;
    listbox1->top = 52;
    listbox1->width = 160;
    listbox1->height = 97;
    listbox1->caption = "listbox1";
    listbox1->onclick = listbox1click;
    listbox1->visible = true;
    listbox1->additem("Item 1");
    listbox1->additem("Item 2");
    listbox1->additem("Item 3");
    listbox1->additem("Item 4");
    listbox1->additem("Item 5");
    listbox1->additem("Item 6");
    listbox1->additem("Item 7");
    listbox1->additem("Item 8");
    listbox1->additem("Item 9");
    listbox1->additem("Item 10");
    listbox1->additem("Item 11");
    listbox1->additem("Item 12");
    listbox1->additem("Item 13");
    listbox1->additem("Item 14");
    listbox1->additem("Item 15");
    listbox1->additem("Item 16");
    listbox1->additem("Item 17");
    listbox1->additem("Item 18");
    listbox1->additem("Item 19");
    listbox1->additem("Item 20");
    listbox1->additem("Item 21");
    listbox1->additem("Item 22");
    listbox1->additem("Item 23");
    listbox1->additem("Item 24");
    listbox1->additem("Item 25");
    listbox1->additem("Item 26");
    listbox1->additem("Item 27");
    listbox1->additem("Item 28");
    listbox1->additem("Item 29");
    listbox1->additem("Item 30");

    combobox1->left = 32;
    combobox1->top = 172;
    combobox1->width = 160;
    combobox1->height = 24;
    combobox1->text = "combobox1";
    combobox1->onclick = combobox1click;
    combobox1->visible = true;
    combobox1->additem("Item 1");
    combobox1->additem("Item 2");
    combobox1->additem("Item 3");
    combobox1->additem("Item 4");
    combobox1->additem("Item 5");
    combobox1->additem("Item 6");
    combobox1->additem("Item 7");
    combobox1->additem("Item 8");
    combobox1->additem("Item 9");
    combobox1->additem("Item 10");
    combobox1->dropdowncount = 4;
    combobox1->style = csDropDownList;
    combobox1->itemindex = 0;

    shape1->left = 16;
    shape1->top = 4;
    shape1->width = 108;
    shape1->height = 90;
    shape1->shape = stRectangle;
    shape1->visible = true;

    image1->left = 175;
    image1->top = 96;
    image1->width = 48;
    image1->height = 48;
    image1->visible = true;
    image1->center = true;
    image1->picture->textured = true;
    image1->picture->transparentcolor = clBlue;
    image1->picture->transparent = true;
    image1->picture->load("bk_0.png");

    image2->left = 15;
    image2->top = 4;
    image2->width = 512;
    image2->height = 256;
    image2->alphavalue = 255;
    image2->visible = true;
    image2->center = true;
    image2->picture->textured = true;
    image2->picture->transparentcolor = clBlack;
    image2->picture->transparent = false;
    image2->picture->load("paisagem.bmp");

    image3->left = 15;
    image3->top = 10;
    image3->width = 320;
    image3->height = 480;
    image3->alphavalue = 255;
    image3->visible = true;
    image3->center = true;
    image3->picture->textured = true;
    image3->picture->transparentcolor = clBlack;
    image3->picture->transparent = false;
    image3->picture->load("reportbkleft.bmp");

    glyphbutton1->left = 160;
    glyphbutton1->top = 96;
    glyphbutton1->width = 128;
    glyphbutton1->height = 32;
    glyphbutton1->visible = true;
    glyphbutton1->center = true;
    glyphbutton1->fadestep = 24;
    glyphbutton1->btnNormal->textured = true;
    glyphbutton1->btnNormal->transparentcolor = clBlue;
    glyphbutton1->btnNormal->transparent = true;
    glyphbutton1->btnNormal->load("novojogo_bn.png");
    glyphbutton1->btnDown->textured = true;
    glyphbutton1->btnDown->transparentcolor = clBlue;
    glyphbutton1->btnDown->transparent = true;
    glyphbutton1->btnDown->load("novojogo_bd.png");
    glyphbutton1->btnOver->textured = true;
    glyphbutton1->btnOver->transparentcolor = clBlue;
    glyphbutton1->btnOver->transparent = true;
    glyphbutton1->btnOver->load("novojogo_bo.png");
    glyphbutton1->btnUp->textured = true;
    glyphbutton1->btnUp->transparentcolor = clBlue;
    glyphbutton1->btnUp->transparent = true;
    glyphbutton1->btnUp->load("novojogo_bn.png");
    glyphbutton1->btnOut = glyphbutton1->btnNormal;
    glyphbutton1->onclick = glyphbutton1click;

    glyphbutton2->left = 160;
    glyphbutton2->top = 128;
    glyphbutton2->width = 128;
    glyphbutton2->height = 32;
    glyphbutton2->visible = true;
    glyphbutton2->center = true;
    glyphbutton2->fadestep = 24;
    glyphbutton2->btnNormal->textured = true;
    glyphbutton2->btnNormal->transparentcolor = clBlue;
    glyphbutton2->btnNormal->transparent = true;
    glyphbutton2->btnNormal->load("opcoes_bn.png");
    glyphbutton2->btnDown->textured = true;
    glyphbutton2->btnDown->transparentcolor = clBlue;
    glyphbutton2->btnDown->transparent = true;
    glyphbutton2->btnDown->load("opcoes_bd.png");
    glyphbutton2->btnOver->textured = true;
    glyphbutton2->btnOver->transparentcolor = clBlue;
    glyphbutton2->btnOver->transparent = true;
    glyphbutton2->btnOver->load("opcoes_bo.png");
    glyphbutton2->btnUp->textured = true;
    glyphbutton2->btnUp->transparentcolor = clBlue;
    glyphbutton2->btnUp->transparent = true;
    glyphbutton2->btnUp->load("opcoes_bn.png");
    glyphbutton2->btnOut = glyphbutton2->btnNormal;
    glyphbutton2->onclick = glyphbutton2click;
    
    progressbar3->left = image2->left+((image2->width-progressbar3->width)/2);
    progressbar3->color = clWhite;
    progressbar3->backgroundalpha = 80;
    progressbar3->smooth = true;
    progressbar3->position = 0;
    progressbar3->gaugecolor = RGB(232,96,0);
    progressbar3->alphavalue = 255;
    
    timer1->interval = 1;
    timer1->ontimer = timer1timer;
    
    viewport1->left = 8;
    viewport1->top = 4;
    viewport1->width = 320-20;
    viewport1->height = 240-41;
    viewport1->align = alClient;
    viewport1->color = clBlack;
    viewport1->alphavalue = 255;
    viewport1->backgroundalpha = 255;
    viewport1->onrender = viewport1render;
    viewport1->visible = true;



    TMenu* menu = new TMenu();
    menu->alphavalue = 255;
    menu->left = 128;
    menu->menu->additem("Adicionar");
    menu->menu->additem("Remover");
    menu->menu->items[0]->onclick = menuitem1click;
    menu->menu->items[1]->onclick = menuitem2click;
    menu->menu->additem("-");
    menu->menu->additem("Item novo")->additem("Sub-item novo 1");
    menu->menu->items[3]->additem("Sub-item novo 2")->onclick = menuitem1click;
    menu->menu->items[3]->additem("Sub-item novo 3")->additem("1")->additem("2")->onclick = menuitem2item1click;
    menu->menu->items[3]->additem("Sub-item novo 4")->onclick = menusubitem4click;;
    menu->menu->items[3]->additem("Sub-item novo 5")->onclick = menuitem2click;;
    menu->menu->additem("Item desabilitado")->enabled = false;
    menu->menu->additem("Marcar item")->onclick = menuitem4click;
    menu->menu->additem("Mostrar nova janela")->onclick = window7showclick;

    mainmenu1->caption = "";
    mainmenu1->enabled = true;
    mainmenu1->left = 8;
    mainmenu1->top = 2;
    mainmenu1->width = 160;
    mainmenu1->height = 24;
    mainmenu1->parent = toolbar1;
    mainmenu1->visible = true;
    
    TMenu* filemenu1 = mainmenu1->additem("File");
    TMenu* editmenu1 = mainmenu1->additem("Edit");
   
    filemenu1->menu->additem("New")->onclick = menuitem1click;
    filemenu1->menu->additem("Open")->onclick = menuitem2click;
    filemenu1->menu->additem("Save");
    filemenu1->menu->additem("-");
    filemenu1->menu->additem("Exit");
    editmenu1->menu->additem("Undo");
    editmenu1->menu->additem("-");
    editmenu1->menu->additem("Cut");
    editmenu1->menu->additem("Copy");
    editmenu1->menu->additem("Paste");
    editmenu1->menu->additem("Select All")->onclick = editmenuselectall;
    editmenu1->menu->additem("Delete")->onclick = editmenudelete;

    trackbar1->left = 16;
    trackbar1->top = 64;
    trackbar1->width = 128;
    trackbar1->height = 24;    
    trackbar1->min = 0;
    trackbar1->max = 10;
    trackbar1->position = 0;
    trackbar1->parent = Window13;
    trackbar1->visible = true;

    trackbar2->left = 16;
    trackbar2->top = 128;
    trackbar2->width = 128;
    trackbar2->height = 24;    
    trackbar2->min = 0;
    trackbar2->max = 25;
    trackbar2->position = 0;
    trackbar2->parent = Window13;
    trackbar2->visible = true;

    trackbar3->left = 208;
    trackbar3->top = 64;
    trackbar3->width = 25;
    trackbar3->height = 150;    
    trackbar3->min = 0;
    trackbar3->max = 10;
    trackbar3->orientation = trVertical;
    trackbar3->position = 0;
    trackbar3->parent = Window13;
    trackbar3->visible = true;

    trackbar4->left = 264;
    trackbar4->top = 64;
    trackbar4->width = 25;
    trackbar4->height = 150;    
    trackbar4->min = 0;
    trackbar4->max = 25;
    trackbar4->orientation = trVertical;
    trackbar4->position = 0;
    trackbar4->parent = Window13;
    trackbar4->visible = true;

    updown1->left = 80;
    updown1->top = 164;
    updown1->width = 16;
    updown1->height = 21;    
    updown1->min = 0;
    updown1->max = 10;
    updown1->position = 0;
    updown1->increment = 1;
    updown1->parent = Window13;
    updown1->associate = edit3;
    updown1->visible = true;

    updown2->left = 16;
    updown2->top = 196;
    updown2->width = 16;
    updown2->height = 24;    
    updown2->min = 0;
    updown2->max = 25;
    updown2->position = 0;
    updown2->parent = Window13;
    updown2->visible = true;

    updown3->left = 80;
    updown3->top = 196;
    updown3->width = 21;
    updown3->height = 16;    
    updown3->min = 0;
    updown3->max = 10;
    updown3->position = 0;
    updown3->increment = 1;
    updown3->orientation = udHorizontal;
    updown3->parent = Window13;
    updown3->visible = true;

    updown4->left = 128;
    updown4->top = 196;
    updown4->width = 24;
    updown4->height = 16;    
    updown4->min = 0;
    updown4->max = 25;
    updown4->position = 0;
    updown4->orientation = udHorizontal;
    updown4->parent = Window13;
    updown4->visible = true;

    videoplayer1->left = 32;
    videoplayer1->top = 32;
    videoplayer1->width = 320;
    videoplayer1->height = 240;    
    videoplayer1->color = clBlack;
    videoplayer1->position = 0;
    videoplayer1->parent = Window13;
    videoplayer1->visible = true;

    LoadWaterTexture();
        
    activewindow = windows[0]->windowid;


    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

/*
  
     for (int i=0;i<256;i++)
     {
         if (keys[i])
         {
           int len = strlen(edit1->text);
           edit1->text = "AaaaAaBBzzZZAAAA";
         
           char c[2];
           char *s = (char*)malloc(len+1);
           char buf[256];
           sprintf(c,"%c",(char)keys[i]);
           strcpy(s,edit1->text);
           strcat(s,c);
           edit1->text = s;// + keys[i];
        //   free(s);
        
         }
     }
*/     
/*
     for (int i=0;i<256;i++)
     {
         if (kbscan[i] > 0)
         {
           int len = strlen(edit1->text);
           
           std::string s = "";
           for (int j=0;j<len;j++) s = s + edit1->text[j];
           char c[2];
           sprintf(c,"%c",i);
           s = s + c;
           char t[256];
           strcpy(t,(char*)s.c_str());
           
           edit1->text = t;
           kbscan[i] = 0;
        
         }
     }
*/


  apprun();  
  
  


// drawimagepng(32,32,warning,255,false,clBlack);
//  subrecttess(50,50,100,100);
//  fillrecttess(20,20,200,200,clLime,255);
// drawcircle(Window1->left,Window1->top,Window1->left+64,Window1->top+64,clLime,255);            
// drawradioimage(64,64,radiobtn,255,0x00F8F8F5,0x00F8F8F8,0x0099A8AC,0x00E2EFF1,0x00646F71, true, clLime);
// drawflatradioimage(64,64,radiobtn,255,0x00F8F8F5,0x00F8F8F8,0x0099A8AC,0x00E2EFF1,0x00646F71, true, clLime);
       
//  edit1->editinput();
            if (keys[VK_F5])
            {
                           deletewindow(numwindows-1);
                           keys[VK_F5] = 0;
            }
            if (keys[VK_F6])
            {
                           setforegroundwindow(activewindow);
                           keys[VK_F6] = 0;
            }
            if (keys[VK_F7])
            {
                           if (WindowExists(Window3)) Window3->freeze();
                           keys[VK_F7] = 0;
            }            
            if (keys[VK_F8])
            {
                           if (WindowExists(Window3)&&WindowExists(Window10)) 
                           {
                             Window10->window = Window3;
                             Window3->visible = false;
                             Window10->showmodal();
                             activewindow = Window10->windowid;
                           }
                           keys[VK_F8] = 0;
            }            
            if (keys[VK_ESCAPE])  PostQuitMessage(0);
            if (keys[VK_F4]) 
            {
                           show_menu(menu);
                           keys[VK_F4] = 0;
            }
            if (keys[VK_F9]) 
            {
                           windowmanager_crash = true;
                           keys[VK_F4] = 0;
            }
            /*
            if (keys[VK_F1]) 
            {
              resettooltip();
              keys[VK_F1] = 0;
            }
            showtooltip("Nova legenda.\nNovo título usando tooltip.");
            */

            SwapBuffers (hDC);
            
            Sleep (1);
            theta += 1.0;
        }
    }
//    freepng(warning);
    
    //for (int i=0;i<256;i++) freebmp(fontbmp[i]);
    
    delete panel1;
    delete panel2;
    delete panel3;
    delete panel4;
    delete bevel1;
    delete groupbox1;
    delete groupbox2;
    delete groupbox3;
    delete transparentbox1;
    delete shape1;
    delete image1;
    delete image2;
    delete image3;
    delete imagelist1;
    delete imagelist2;
    delete imagelist3;
    delete toolbar1;
    delete toolbar2;
    delete toolbar3;
    delete toolbutton1;
    delete toolbutton2;
    delete toolbutton3;
    delete toolbutton4;
    delete toolbutton5;
    delete toolbutton6;
    delete toolbutton7;
    delete dockbar1;
    delete glyphbutton1;
    delete glyphbutton2;
    delete timer1;
    delete viewport1;
    delete combobox1;
    delete listbox1;
    delete listview1;
    delete button1;
    delete button2;
    delete button3;
    delete button4;
    delete button5;
    delete button6;
    delete button7;
    delete label1;
    delete label2;
    delete label3;
    delete label4;
    delete label5;
    delete edit1;
    delete edit2;
    delete edit3;
    delete textbox1;
    delete checkbox1;
    delete checkbox2;
    delete radiobutton1;
    delete radiobutton2;
    delete radiobutton3;
    delete radiobutton4;
    delete radiobutton5;
    delete radiobutton6;
    delete radiobutton7;
    delete scrollbar1;
    delete scrollbar2;
    delete progressbar1;
    delete progressbar2;
    delete progressbar3;
    delete mainmenu1;
    delete trackbar1;
    delete trackbar2;
    delete trackbar3;
    delete trackbar4;
    delete updown1;
    delete updown2;
    delete updown3;
    delete updown4;
    delete videoplayer1;
    delete Window1;
    delete Window2;
    delete Window3;
    delete Window4;
    delete Window5;
    delete Window6;
    delete Window7;
    delete Window8;
    delete Window9;
    delete Window10;
    delete Window11;
    delete Window12;
    delete Window13;
    delete Window14;
    delete Window15;

    appuninit();
    appdestroy();

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);
    
    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;
    case WM_DESTROY:
        return 0;
    case WM_LBUTTONDOWN:
         setmousedown_l(LOWORD(lParam),HIWORD(lParam));
         return 0;
    case WM_MBUTTONDOWN:
         setmousedown_m(LOWORD(lParam),HIWORD(lParam));
         return 0;
    case WM_RBUTTONDOWN:
         setmousedown_r(LOWORD(lParam),HIWORD(lParam));
         return 0;
    case WM_MOUSEMOVE:
         setmousemove(LOWORD(lParam),HIWORD(lParam));
         return 0;
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
         setmouseup(LOWORD(lParam),HIWORD(lParam));
         return 0;
    case WM_MOUSEWHEEL:
         setmousewheel(LOWORD(wParam),(short) HIWORD(wParam));
         return 0;
    case WM_KEYDOWN:
       //  keys[wParam] = true;
       //  kbscan[wParam] = true;
         if (wParam == VK_SHIFT) setkeyshift(true);
         setkeydown(wParam,keyshift);
         return 0;
    case WM_KEYUP:
        // keys[wParam] = false;
        // kbscan[wParam] = false;
         if (wParam == VK_SHIFT) setkeyshift(false);
         setkeyup(wParam,keyshift);
         return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
