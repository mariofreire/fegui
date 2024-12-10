// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "cimp.h"

extern bool keys[256];
extern bool kbscan[256];
extern int keyshift;

extern unsigned char lastkey;
extern unsigned char lastshift;

void setkeydown(unsigned char Key, int Shift);
void setkeyup(unsigned char Key, int Shift);
void setkeyshift(int Shift);

int getkeychar();
int getkeystate(unsigned char Key);
int getkeyshift();

#endif // KEYBOARD_H
