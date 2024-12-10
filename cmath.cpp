// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "cmath.h"



int SearchForNextPower(int nNumber)
{
	int power;
	for(power = 2; power < 1024; power *= 2)
	{
		if(power >= nNumber)
		{
			return power;
		}
	}
	return 0;
}

long SolveForX(long Y, long Z)
{
  return floor( Z * (Y * 0.01) );
}

long SolveForY(long X, long Z)
{
  if (Z==0)
    return 0;
  else
    return floor( (X * 100.0) / Z );
}

#define sqr(x) (x*x)

double finddist(double x, double y);


float fatan2(float y,float x)
{
 if (x==0) return (2*atan(y/(finddist(x,y)+x)));
 return atan2(y,x); //(2*atan(y/(finddist(x,y)+x)));
}
// 2*ARCTAN(y/(SQRT(x^2+y^2)+x))

double Deg2Rad(double Angle)
{
 return Angle*PI/180;
}

double Rad2Deg(double Angle)
{
 return 180*Angle/PI;
}

double getangle(double x, double y)
{
 return Rad2Deg(fatan2(x,y));
}

double finddist(double x, double y)
{
 return sqrt(sqr(x)+sqr(y));
}
