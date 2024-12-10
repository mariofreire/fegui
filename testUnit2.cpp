// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br
//---------------------------------------------------------------------------

#include <vcl.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#pragma hdrstop

#include "testUnit2.h"
#include "fegui.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
int mousea=0,mouseb=0;
bool keys[256];
//---------------------------------------------------------------------------
HDC hDC;
HGLRC hRC;

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


void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}



#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

FILE* FEGUI_CALLBACK feguiopen (const char* filename, const char* mode)
{
  return fopen(filename,mode);
}
int FEGUI_CALLBACK feguiclose (FILE* stream)
{
  return fclose(stream);
}
 long FEGUI_CALLBACK feguitell (FILE* stream)
{
  return ftell(stream);
}
int FEGUI_CALLBACK feguiseek (FILE* stream, long offset, int whence)
{
  return fseek(stream,offset,whence);
}
size_t FEGUI_CALLBACK feguiread (void* ptr, size_t size, size_t n, FILE* stream)
{
  return fread(ptr,size,n,stream);
}
size_t FEGUI_CALLBACK feguiwrite (const void* ptr, size_t size, size_t n, FILE* stream)
{
  return fwrite(ptr,size,n,stream);
}


#ifdef __cplusplus
}
#endif

#pragma pack(pop)





typedef struct bmp
{
 BITMAPFILEHEADER	head;
 BITMAPINFO		info;
 void*			data;
 int			width;
 int			height;
 int			size;
 unsigned char*		bgr;
}BMP;



int savebmp(char* filename, BMP* bmp)
{
 int	infosize;
 FILE*  file = NULL;
 if(!(file = feguiopen(filename, "wb"))) return 1;
 feguiwrite(&(bmp->head), sizeof(BITMAPFILEHEADER), 1, file);
 infosize = (bmp->head).bfOffBits - sizeof(BITMAPFILEHEADER);
 feguiwrite(&(bmp->info), 1, infosize, file);
 feguiwrite((unsigned char *)(bmp->data), 1, bmp->size, file);
 feguiclose(file);
 return 0;
}

BMP* loadbmp(char* filename)
{
 FILE*	file		= NULL;
 BMP*	bmp		= NULL;
 long	infosize;
 long	bitsize;
 if(!(file = feguiopen(filename, "rb"))) return NULL;
 bmp = (BMP *)malloc(sizeof(BMP));
 feguiread(&(bmp->head), sizeof(BITMAPFILEHEADER), 1, file);
 if((bmp->head).bfType!= 'MB') { feguiclose(file); free(bmp); return NULL; }
 infosize = (bmp->head).bfOffBits - sizeof(BITMAPFILEHEADER);
 feguiread(&(bmp->info), 1, infosize, file);
 if((bitsize = (bmp->info).bmiHeader.biSizeImage)==0)
  bitsize = ((bmp->info).bmiHeader.biWidth*((bmp->info).bmiHeader.biBitCount+7)/8) * abs((bmp->info).bmiHeader.biHeight);
 (bmp->data) = (void *)malloc(sizeof(char)*bitsize); 
 feguiread((unsigned char *)(bmp->data), 1, bitsize, file);
 feguiclose(file);
 bmp->size	= bitsize;
 bmp->width	= (bmp->info).bmiHeader.biWidth;
 bmp->height = (bmp->info).bmiHeader.biHeight;
 bmp->bgr = (unsigned char*)bmp->data;
 return bmp;
}

void freebmp(BMP* bmp)
{
 if(!bmp) return;
 if(bmp->data) free(bmp->data);
 free(bmp);
}





unsigned int window[256];
int numwindows=0;
int viewport1=NULL;
int consolebox=NULL;
int webbrowser=NULL;

bool window2created = false;

int rotating = 1;
float theta = 0.0f;




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
      fegui_messagebox(0,"Zero length vector","Error",MB_OK|MB_ICONERROR);
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

void specialkeys(int key)
{
     if (fegui_getactivewindow() == fegui_findwindow("window1"))
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
    if (mesh)	//  以四边形模式进行绘制
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-1.f, 0.f, -1.f);
		glTexCoord2f(0, 1); glVertex3f(-1.f, 0.f,  1.f);
		glTexCoord2f(1, 1); glVertex3f( 1.f, 0.f,  1.f);
		glTexCoord2f(1, 0); glVertex3f( 1.f, 0.f, -1.f);
		glEnd();
    } 
	else		//  以多个三角形面片的形式进行绘制
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
    specialkeys(keydown);
    if (rotating) animate();
}

void printext(int x,int y,char* text)
{
    fegui_textattr(clBlack,255,13,FW_BOLD);
    fegui_textout(x+1,y+1,text);
    fegui_textattr(clWhite,255,13,FW_BOLD);
    fegui_textout(x,y,text);
}

void printextcolor(int x,int y,int color,char* text)
{
    fegui_textattr(clBlack,255,13,FW_BOLD);
    fegui_textout(x+1,y+1,text);
    fegui_textattr(color,255,13,FW_BOLD);
    fegui_textout(x,y,text);
}

int dica=1;
int indicador=1;
int seta_y=0;
int seta_volta=0;
int seta_cor=clRed;

GLuint watertexture;

void viewportrender(int windowid,int sender)
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
    if (indicador)
    {
    if (dica==1)
    {
     printext(305,180,"Clique nas ondas");
     if (seta_volta==0)
     {
       seta_y++;
       if (seta_y>=32) seta_volta=1;
     }
     else
     {
       if (seta_y<=0) seta_volta=0;
       seta_y--;
     }
     if (seta_y <= 0) seta_y = 0;
     if (seta_y > 32) seta_y = 32;
     fegui_drawline(335,200+seta_y,335,210+seta_y,seta_cor,255);
     fegui_drawline(335,200+seta_y,365,220+seta_y,seta_cor,255);
     fegui_drawline(365,220+seta_y,395,200+seta_y,seta_cor,255);
     fegui_drawline(335,203+seta_y,365,223+seta_y,seta_cor,255);
     fegui_drawline(365,223+seta_y,395,203+seta_y,seta_cor,255);
     fegui_drawline(335,205+seta_y,365,225+seta_y,seta_cor,255);
     fegui_drawline(365,225+seta_y,395,205+seta_y,seta_cor,255);
     fegui_drawline(335,208+seta_y,365,228+seta_y,seta_cor,255);
     fegui_drawline(365,228+seta_y,395,208+seta_y,seta_cor,255);
     fegui_drawline(335,210+seta_y,365,230+seta_y,seta_cor,255);
     fegui_drawline(365,230+seta_y,395,210+seta_y,seta_cor,255);
     fegui_drawline(395,200+seta_y,395,210+seta_y,seta_cor,255);
    }
    else if (dica==2)
    {
     printextcolor(200,180,clLime,"Pressione a tecla  \"  para restaurar a janela atual.");
    }
    }

}

int showmsg1=1;
int msgcnt=0;
int startfreeze=0;
int freezecount=0;

void viewport1Render(int windowid,int sender)
{
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);

            if (msgcnt>32)
            {
             if (showmsg1)
             {
              fegui_messagebox(fegui_findwindow("window1"),"Clique nas ondas e pressione a tecla  \"  para restaurar a janela atual.","Aviso",MB_ICONWARNING|MB_OK);
              //fegui_setactivewindow(fegui_findwindow("window1"));
              showmsg1=0;
              msgcnt = 1000;
             }
            }
            if (msgcnt<=256) msgcnt++;
            /*
            if (fegui_getwindowmessageboxresult(fegui_findwindow("window1")))
            {
              fegui_setactivewindow(fegui_findwindow("window1"));
              fegui_setwindowmessageboxresult(fegui_findwindow("window1"),mrNone);
            }
            if (fegui_getwindowmessageboxresult(fegui_findwindow("window2")))
            {
              fegui_setactivewindow(fegui_findwindow("window1"));
              fegui_setwindowmessageboxresult(fegui_findwindow("window2"),mrNone);
            }
            */
            if (strcmp(fegui_getwindowname(fegui_getforegroundwindow()),"window1")==0)
            {
              if (keys[VK_OEM_3])
              {
                dica=0;
                int win = fegui_findwindow("window1");
                if (fegui_getwindowstate(win)) fegui_restorewindow(win);
                else fegui_maximizewindow(win);
                keys[VK_OEM_3] = false;
              }
              if (keys[VK_F7])
              {
                startfreeze=1;
                fegui_windowfreeze(fegui_findwindow("window1"));
                keys[VK_F7] = false;
              }
              if (keys[VK_SPACE])
              {
                rotating = 1-rotating;
                keys[VK_SPACE] = false;
              }
              if (!rotating)
              {
                if (keys[VK_ADD])
                {
                  theta += 2.0f;
                  keys[VK_ADD] = false;
                }
                if (keys[VK_SUBTRACT])
                {
                  theta -= 2.0f;
                  keys[VK_SUBTRACT] = false;
                }
              }
            }
            viewportrender(0,sender);
            /*
            glPushMatrix ();
            glRotatef (theta, 0.0f, 0.0f, 1.0f);
            glBegin (GL_TRIANGLES);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (0.0f, 1.0f);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (0.87f, -0.5f);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (-0.87f, -0.5f);
            glEnd ();
            glPopMatrix ();
            */
            if (rotating) theta += 1.0f;
}

void viewport1Click(int windowid,int sender)
{
  if (dica==1) dica=2;
}

void idle_render(void)
{
POINT wsize1 = fegui_getwindowsize(fegui_findwindow("window1"));
int w1=wsize1.x;
int h1=wsize1.y;
if (startfreeze)
{
  if (freezecount >= 384)
  {
    int win=fegui_findwindow("window1");
    if (fegui_getwindowstate(win)==2) fegui_restorewindow(win);
    startfreeze=0;
  }
  else
  {
    freezecount++;
  }
}
int st1=fegui_getwindowstate(fegui_findwindow("window1"));
if (st1 == 2)
{
  fegui_setwindowstyle(fegui_findwindow("window1"),0);
}
else fegui_setwindowstyle(fegui_findwindow("window1"),3);
int s1=fegui_getwindowstyle(fegui_findwindow("window1"));
if (s1)
{
 fegui_setviewportpos(fegui_findwindow("window1"),viewport1,3,-3);
 fegui_resizeviewport(fegui_findwindow("window1"),viewport1,w1-9,h1-29);
}
else
{
  fegui_setviewportpos(fegui_findwindow("window1"),viewport1,0,0);
  fegui_resizeviewport(fegui_findwindow("window1"),viewport1,w1,h1);
}
POINT wsize2 = fegui_getwindowsize(fegui_findwindow("window2"));
int w2=wsize2.x;
int h2=wsize2.y;
fegui_resizetransparentbox(fegui_findwindow("window2"),consolebox,w2-9,h2-29);
POINT wsize3 = fegui_getwindowsize(fegui_findwindow("window3"));
int w3=wsize3.x;
int h3=wsize3.y;
fegui_resizewebbrowser(fegui_findwindow("window3"),webbrowser,w3-20,h3-43);
}


void drawcursorimage(int x, int y,BMP* cursorfile,int alpha)
{
int cx,cy,index=0,c,r,g,b;

  for(cy=0;cy<cursorfile->height;cy++)
  {
  for(cx=0;cx<cursorfile->width;cx++)
  {
    r = cursorfile->bgr[index + 2];
    g = cursorfile->bgr[index + 1];
    b = cursorfile->bgr[index + 0];
    c = RGB(r,g,b);
    if (c!=clBlue) fegui_setpixel(x+cx,y+(cursorfile->height-cy),c,alpha);
    index += 3;
  }
  }
  
//  enddrawing();

}

void drawcursorimagemask(int x, int y,BMP* cursorfile,COLORREF color,int alpha)
{
int cx,cy,index=0,c,r,g,b;

  for(cy=0;cy<cursorfile->height;cy++)
  {
  for(cx=0;cx<cursorfile->width;cx++)
  {
    r = cursorfile->bgr[index + 2];
    g = cursorfile->bgr[index + 1];
    b = cursorfile->bgr[index + 0];
    c = RGB(r,g,b);
    if (c!=clBlue) fegui_setpixel(x+cx,y+(cursorfile->height-cy),color,alpha);
    index += 3;
  }
  }
  
//  enddrawing();

}


void drawcursor(int x, int y,BMP* cursorfile)
{
  int cx,cy;
  COLORREF color;
  int alpha;

  glPointSize(1.0);
  
  cx = x+2;
  cy = y+2;

  color = RGB(0,0,0);

  alpha = 72;
  drawcursorimagemask(cx,cy,cursorfile,color,alpha);
  cx = x;
  cy = y;


  color = RGB(255,255,255);

  alpha = 255;
  
  drawcursorimage(cx,cy,cursorfile,alpha);
  
//  enddrawing();

}



BMP* xcursor;
BMP* arrow;
BMP* sizexcursor;
BMP* sizeycursor;
BMP* sizexzcursor;
BMP* sizewzcursor;
BMP* textcursor;

char* filenamefrompath(const char* path,const char* filename)
{
  char* fnpath = (char*)malloc(strlen(path)+strlen(filename)+1);
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

char guipath[256];


GLuint	texture[65536];
int showbkimg=0;


#define XBACKGROUND_LEN 64

 static unsigned char xbackground[]=
 {
  0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,
  0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00,
  0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
  0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,
  0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00
  };

void loadxbk(void)
{
        int tex_on = glIsEnabled(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &texture[0]);					// Create The Texture

        // Typical Texture Generation Using Data From The Bitmap
        glBindTexture(GL_TEXTURE_2D, texture[0]);

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

        if (!tex_on) glDisable(GL_TEXTURE_2D);
}

void drawbkimage(void)
{
  int width = fegui_getscreenwidth();
  int height = fegui_getscreenheight();
  glPushMatrix();
//  fegui_begindrawing();

  int tex_on = glIsEnabled(GL_TEXTURE_2D);
  int tx=0,ty=0;
  tx=ty=(height/8);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glBegin( GL_QUADS );
  glColor4ub( 255, 255, 255, 255 );
    glTexCoord2f( 0, 0 );
    glVertex2i( 0, 0 );
    glTexCoord2f( tx, 0 );
    glVertex2i( width, 0 );
    glTexCoord2f( tx, ty );
    glVertex2i( width, height );
    glTexCoord2f( 0, ty );
    glVertex2i( 0, height );
  glEnd();
  
//  fegui_enddrawing();
  glPopMatrix();

  if (!tex_on) glDisable(GL_TEXTURE_2D);

}


GLuint	bktexture[65536];
BMP* background;

void loadbkimage(void)
{
        background = loadbmp(filenamefrompath(guipath,"background.bmp"));
        int tex_on = glIsEnabled(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &bktexture[0]);					// Create The Texture

        // Typical Texture Generation Using Data From The Bitmap
        glBindTexture(GL_TEXTURE_2D, bktexture[0]);
        int w=background->width;
        int h=background->height;
        unsigned char* data = (unsigned char*)malloc(w*h*4);
        int j=0;
        for(int i=0;i<(w*h*3);i+=3)
        {
          data[j+3] = 255;
          data[j+2] = background->bgr[i];
          data[j+1] = background->bgr[i+1];
          data[j] = background->bgr[i+2];
          j += 4;
        }

        //int nw = SearchForNextPower(background->width);
        //int nh = SearchForNextPower(background->height);
   	//BYTE *scaled;
	//scaled = (BYTE*)malloc(nw * nh * 4);
	//gluScaleImage(GL_RGBA, background->width, background->height, GL_UNSIGNED_BYTE, data, nw, nh, GL_UNSIGNED_BYTE, scaled);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        if (!tex_on) glDisable(GL_TEXTURE_2D);
        //free(scaled);
        free(data);
}

void drawbksubimage(void)
{
  int width = fegui_getscreenwidth();
  int height = fegui_getscreenheight();
  glPushMatrix();
//  fegui_begindrawing();

  int tex_on = glIsEnabled(GL_TEXTURE_2D);
  int tx=0,ty=0;
  tx=ty=(1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, bktexture[0]);
  glBegin( GL_QUADS );
  glColor4ub( 255, 255, 255, 255 );
    glTexCoord2f( 0, 0 );
    glVertex2i( 0, 0 );
    glTexCoord2f( tx, 0 );
    glVertex2i( width, 0 );
    glTexCoord2f( tx, ty );
    glVertex2i( width, height );
    glTexCoord2f( 0, ty );
    glVertex2i( 0, height );
  glEnd();

//  fegui_enddrawing();
  glPopMatrix();

  if (!tex_on) glDisable(GL_TEXTURE_2D);

}



int LoadWaterTexture()
{
    BMP* water1;

    glEnable(GL_TEXTURE_2D);

    water1 = loadbmp(filenamefrompath(guipath,"water1.bmp"));
    
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

void initengine(void)
{
    loadxbk();
    strcpy(guipath,fegui_getguipath());
    xcursor = loadbmp(filenamefrompath(guipath,"xcursor.bmp"));
    arrow = loadbmp(filenamefrompath(guipath,"arrow.bmp"));
    sizexcursor = loadbmp(filenamefrompath(guipath,"sizex.bmp"));
    sizeycursor = loadbmp(filenamefrompath(guipath,"sizey.bmp"));
    sizexzcursor = loadbmp(filenamefrompath(guipath,"sizexz.bmp"));
    sizewzcursor = loadbmp(filenamefrompath(guipath,"sizewz.bmp"));
    textcursor = loadbmp(filenamefrompath(guipath,"textcursor.bmp"));
}
void uninitengine(void)
{
    freebmp(xcursor);
    freebmp(arrow);
    freebmp(sizexcursor);
    freebmp(sizeycursor);
    freebmp(sizexzcursor);
    freebmp(sizewzcursor);
    freebmp(textcursor);
}



void __fastcall TForm1::FormCreate(TObject *Sender)
{
  EnableOpenGL (Handle, &hDC, &hRC);
  fegui_sethwnd(Handle);
  fegui_appcreate();
  fegui_setguipath("img/");
  fegui_setscreensize(ClientWidth,ClientHeight);
  fegui_setfilesystem(feguiopen,feguiclose,feguiread,feguiwrite,feguitell,feguiseek);
  initengine();
  fegui_appinit();

  LoadWaterTexture();
  loadbkimage();

  window[numwindows] = fegui_createwindow();
  fegui_setwindowname(window[numwindows],"window1");
  fegui_setwindowcaption(window[numwindows],"Primeira janela");
  fegui_setwindowpos(window[numwindows],300,20);
  fegui_resizewindow(window[numwindows],320,240);
  fegui_setwindowstyle(window[numwindows],3);
  fegui_maximizewindow(window[numwindows]);
  fegui_setwindowmessageboxresult(window[numwindows],mrNone);

  viewport1 = fegui_createviewport(window[numwindows]);
  fegui_setviewportname(window[numwindows],viewport1,"viewport1");
  fegui_setviewportcaption(window[numwindows],viewport1,"");
  fegui_setviewportpos(window[numwindows],viewport1,3,-3);
  fegui_resizeviewport(window[numwindows],viewport1,311,211);
  fegui_showviewport(window[numwindows],viewport1);
  fegui_setviewportonrender(window[numwindows],viewport1,viewport1Render);
  fegui_setviewportonclick(window[numwindows],viewport1,viewport1Click);

  fegui_showwindow(window[numwindows]);
  fegui_setactivewindow(window[numwindows]);
  fegui_setmouseup(ClientWidth/2,ClientHeight/2);
  numwindows++;


  window[numwindows] = fegui_createwindow();
  fegui_setwindowname(window[numwindows],"window2");
  fegui_setwindowcaption(window[numwindows],"Segunda janela");
  fegui_setwindowpos(window[numwindows],20,20);
  fegui_resizewindow(window[numwindows],265,445);

  consolebox = fegui_createtransparentbox(window[numwindows]);
  fegui_settransparentboxname(window[numwindows],consolebox,"consolebox");
  fegui_settransparentboxcaption(window[numwindows],consolebox,"");
  fegui_settransparentboxpos(window[numwindows],consolebox,3,-3);
  fegui_resizetransparentbox(window[numwindows],consolebox,256,416);
  fegui_settransparentboxcaption(window[numwindows],consolebox,"/data/maps]");
  fegui_settransparentboxcolor(window[numwindows],consolebox,clBlack);
  fegui_settransparentboxbackgroundalpha(window[numwindows],consolebox,192);
  fegui_settransparentboxalphavalue(window[numwindows],consolebox,255);
  fegui_showtransparentbox(window[numwindows],consolebox);

  fegui_showwindow(window[numwindows]);
  fegui_setactivewindow(window[numwindows]);
  fegui_setmouseup(ClientWidth/2,ClientHeight/2);
  numwindows++;

  window[numwindows] = fegui_createwindow();
  fegui_setwindowname(window[numwindows],"window3");
  fegui_setwindowcaption(window[numwindows],"Nova janela");
  fegui_setwindowpos(window[numwindows],300,275);
  fegui_resizewindow(window[numwindows],320,190);
  fegui_showwindow(window[numwindows]);
  webbrowser = fegui_createwebbrowser(window[numwindows]);
  fegui_setwebbrowserid(window[numwindows],webbrowser,300);
  fegui_setwebbrowsername(window[numwindows],webbrowser,"webbrowser1");
  fegui_setwebbrowserpos(window[numwindows],webbrowser,8,8);
  fegui_resizewebbrowser(window[numwindows],webbrowser,300,152);
  fegui_setwebbrowserurl(window[numwindows],webbrowser,"http://www.google.com.br/");
  fegui_showwebbrowser(window[numwindows],webbrowser);
  numwindows++;

  fegui_setactivewindow(fegui_findwindow("window1"));

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  fegui_deletewindow(window[numwindows]);
  fegui_appuninit();
  uninitengine();
  fegui_appdestroy();
  DisableOpenGL (Handle, hDC, hRC);
}
int render_on=0;
int startcnt=0;
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
            fegui_setscreensize(ClientWidth,ClientHeight);
            glClearColor ((GetRValue(clBackground)/255.0), (GetGValue(clBackground)/255.0), (GetBValue(clBackground)/255.0), 0.0f);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            drawbkimage();
            drawbksubimage();
            idle_render();
            fegui_apprun();
            fegui_setmouseasync(0);
            BMP* cursor=NULL;
            int mousex=0,mousey=0;
            fegui_getmousepos(&mousex,&mousey);
            switch(fegui_getmousecursor())
            {
              case FEGUI_MOUSECURSOR_XCURSOR:
                cursor = xcursor;
              break;
              case FEGUI_MOUSECURSOR_ARROW:
                cursor = arrow;
              break;
              case FEGUI_MOUSECURSOR_IBEAM:
                cursor = textcursor;
              break;
              case FEGUI_MOUSECURSOR_SIZEWZ:
                mousex -= 8;
                mousey -= 8;
                cursor = sizewzcursor;
              break;
              case FEGUI_MOUSECURSOR_SIZEXZ:
                mousex -= 8;
                mousey -= 8;
                cursor = sizexzcursor;
              break;
              case FEGUI_MOUSECURSOR_SIZEX:
                mousex -= 8;
                mousey -= 8;
                cursor = sizexcursor;
              break;
              case FEGUI_MOUSECURSOR_SIZEY:
                mousex -= 8;
                mousey -= 8;
                cursor = sizeycursor;
              break;
            };
            if (cursor) drawcursor(mousex,mousey,cursor);
            if (render_on)
            {

            }
            else
            {
              fegui_fillrect(0,0,Width,Height,0,255);
              drawbkimage();
              drawcursor(mousex,mousey,xcursor);
              if (startcnt > 64)
              {
                render_on = 1;
                startcnt = 0;
              }
              else
              {
                startcnt++;
              }
            }
            SwapBuffers (hDC);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
fegui_setmouseasync(0);
if (Button == mbLeft) fegui_setmousedown_l(X,Y);
else if (Button == mbMiddle) fegui_setmousedown_m(X,Y);
else if (Button == mbRight) fegui_setmousedown_r(X,Y);
else fegui_setmousedown_l(X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
mousea = fegui_getmouseasync();
if (!mousea) fegui_setmousemove(X,Y);
else fegui_setmousepos(X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if (mouseb) fegui_setmouseasync(1);
fegui_setmouseup(X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{
fegui_setmousewheel(0,WheelDelta);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
         if (Shift.Contains(ssShift)) fegui_setkeyshift(true);
         fegui_setkeydown(Key,fegui_getkeyshift());
         keys[Key] = true;
         if (Key == 'K') Designer->PaintGrid();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
         if (Shift.Contains(ssShift)) fegui_setkeyshift(false);
         fegui_setkeyup(Key,fegui_getkeyshift());
         keys[Key] = false;
}
//---------------------------------------------------------------------------

AnsiString EMessage="";
void __fastcall TForm1::ApplicationEvents1Exception(TObject *Sender,
      Exception *E)
{
  if (E->Message.Length()>0) EMessage = WrapText(E->Message,64);
  fegui_messagebox(0,EMessage.c_str(),"Error",MB_ICONERROR|MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
exit(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
exit(0);
}
//---------------------------------------------------------------------------

