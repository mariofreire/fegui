// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef CMATH_H
#define CMATH_H

#include <math.h>

#define PI 3.1415926535897932384626433832795

#define sqr(x) (x*x)

int SearchForNextPower(int nNumber);
long SolveForX(long Y, long Z);
long SolveForY(long X, long Z);

float fatan2(float y,float x);
double Deg2Rad(double Angle);
double Rad2Deg(double Angle);
double getangle(double x, double y);
double finddist(double x, double y);

#endif // CMATH_H
