// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "canvas.h" // class's header file

// class constructor
TCanvas::TCanvas()
{
format = IMAGE_RGB;
depth = 96;
width = 1;
height = 1;
brush = new TBrush();
pen = new TPen();
pixels = new unsigned char [width*height*format];
}

// class destructor
TCanvas::~TCanvas()
{
delete brush;
delete pen;
delete pixels;
}
