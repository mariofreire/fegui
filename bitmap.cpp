// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "bitmap.h" // class's header file

// class constructor
TBitmap::TBitmap()
{
	// insert your code here
}

// class destructor
TBitmap::~TBitmap()
{
	// insert your code here
}



int savebmp(char* filename, BMP* bmp)
{
 int	infosize;
 FILE*  file = NULL;
 if(!(file = f_open(filename, "wb"))) return 1;
 f_write(&(bmp->head), sizeof(BITMAPFILEHEADER), 1, file);
 infosize = (bmp->head).bfOffBits - sizeof(BITMAPFILEHEADER);
 f_write(&(bmp->info), 1, infosize, file);
 f_write((unsigned char *)(bmp->data), 1, bmp->size, file);
 f_close(file);
 return 0;
}

BMP* loadbmp(char* filename)
{
 FILE*	file		= NULL;
 BMP*	bmp		= NULL;
 long	infosize;
 long	bitsize;
 if(!(file = f_open(filename, "rb"))) return NULL;
 bmp = (BMP *)malloc(sizeof(BMP));
 f_read(&(bmp->head), sizeof(BITMAPFILEHEADER), 1, file);
 if((bmp->head).bfType!= 'MB') { f_close(file); free(bmp); return NULL; }
 infosize = (bmp->head).bfOffBits - sizeof(BITMAPFILEHEADER);
 f_read(&(bmp->info), 1, infosize, file);
 if((bitsize = (bmp->info).bmiHeader.biSizeImage)==0)
  bitsize = ((bmp->info).bmiHeader.biWidth*((bmp->info).bmiHeader.biBitCount+7)/8) * abs((bmp->info).bmiHeader.biHeight);
 (bmp->data) = (void *)malloc(sizeof(char)*bitsize); 
 f_read((unsigned char *)(bmp->data), 1, bitsize, file);
 f_close(file);
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

int loadimage(int width,int height,char *image, GLuint *tex) {

if (image==NULL) return -1;
 
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


glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, image);
return 0;
 
}

unsigned int loadbitmaptexture(char* filename)
{
  FILE* fp;
  BMP* bmp;
  unsigned int newtexture = 0;
  fp = f_open(filename,"rb");
  if (!fp) return 0;
  f_close(fp);
  bmp = loadbmp(filename);
  for (int i=0;i<bmp->width*bmp->height*3;i+=3)
  {
    unsigned char tmp = bmp->bgr[i+2];
    bmp->bgr[i+2] = bmp->bgr[i+0];
    bmp->bgr[i+0] = tmp;
  }
  loadimage(bmp->width,bmp->height,bmp->bgr,&newtexture);
  freebmp(bmp);
  return newtexture;
}




AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=f_open(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		f_close(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}


