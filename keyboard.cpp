// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#include "keyboard.h"

bool keys[256];
bool kbscan[256];
int keyshift=0;


unsigned char lastkey = 0;
unsigned char lastshift = 0;

extern bool webbrowser_keydown_on, webbrowser_keypress_on, webbrowser_keyup_on;  

#pragma pack(push, 1)

#ifdef __cplusplus
extern "C" {
#endif

void webkit_keydown(unsigned char key);
void webkit_keyup(unsigned char key);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)


void setkeydown(unsigned char Key, int Shift)
{
unsigned char key = 0;
int shift = 0;
int shift2 = 0;

if (Shift) shift = 1;
else shift = 0;

if (Key == VK_RETURN)
{
 keys[VK_RETURN] = 1;
 kbscan[VK_RETURN] = 1;
}


if (Key != 222)
{
if (!Shift)
{
 key = tolower((char)Key);
} else
if (Shift)
{
  key = toupper((char)Key);
}
}

/*
if (Key == 16)
{
if (Key != VK_SHIFT)
{
 key = toupper((char)Key);
}
}
*/
if (Key == 46) key = 190;
if (Key == 188) key = ',';
if (Key == 190) key = '.';
if (Key == 186) key = 'ç';
if (Key == 191)
{
 if (shift) key = ':';
 else key = ';';
}
if (Key == 221) key = '[';
if (Key == 220) key = ']';
if (Key == 219) key = '´';
if (Key == 187) key = '=';
if (Key == 189) key = '-';
if (Key == 109) key = '-';
if (Key == 107) key = '+';
if (Key == 194) key = '.';
if (Key == 111) key = '/';
if (Key == 106) key = '*';
if (Key == 226) key = '\\';

if ((Key == 49) && (shift)) key = '!';
if ((Key == 50) && (shift)) key = '@';
if ((Key == 51) && (shift)) key = '#';
if ((Key == 52) && (shift)) key = '$';
if ((Key == 53) && (shift)) key = '%';
if ((Key == 54) && (shift)) key = '¨';
if ((Key == 55) && (shift)) key = '&';
if ((Key == 56) && (shift)) key = '*';
if ((Key == 57) && (shift)) key = '(';
if ((Key == 48) && (shift)) key = ')';

if (Key == 192)
{
 if (shift) key = '"';
 else key = 96;
}
if (Key == 110) key = ',';
if (Key == 222)
{
 if (shift) shift2 = 1;
 else shift2 = 0;
 if (lastkey == 222)
 {
  if (shift) key = '^';
  else key = '~';
 }
// else key = ' ';
}
if (Key == 193) key = '/';
if (Key == 219) key = '´';
if (Key == 32)
{
  if (lastkey == 222)
  {
  if (shift2 || shift) key = '^';
  else key = '~';
  }
}

if (lastshift && !shift)
{
if (lastkey == 222)
{
 if (Key == 65)
 {
   key = 'â';
   lastshift = 0;
 } else if (Key == 79)
 {
   key = 'ô';
   lastshift = 0;
 } else lastshift = 0;
} else  lastshift = 0;

}
else
{

if (Key == 65)
{
  if (lastkey == 222)
  {
   if (shift) key = 'Ã';
   else key = 'ã';
  }
}
if (Key == 79)
{
  if (lastkey == 222)
  {
   if (shift) key = 'Õ';
   else key = 'õ';
  }
}

}


if (Key == 186)
{
   if (shift) key = 'Ç';
   else key = 'ç';
}

keys[key] = 1;
kbscan[key] = 1;
if (Key != VK_SHIFT) lastkey = Key;
else
{
 if (!shift2) lastshift = 1;
}
webkit_keydown(key);
webbrowser_keydown_on = true;
}

void setkeyup(unsigned char Key, int Shift)
{
webbrowser_keyup_on = true;
char key = (char)Key;
if (Key == 16) key = toupper((char)Key);
if (Key == 188) key = ',';
if (Key == 190) key = '.';
if (Key == 186) key = 'ç';
if (Key == 191)
{
 if (Shift) key = ':';
 else key = ';';
}
if (Key == 221) key = '[';
if (Key == 220) key = ']';
if (Key == 219) key = '´';
if (Key == 187) key = '=';
if (Key == 189) key = '-';
if (Key == 109) key = '-';
if (Key == 107) key = '+';
if (Key == 194) key = '.';
if (Key == 111) key = '/';
if (Key == 106) key = '*';
if (Key == 192) key = 96;
if (Key == 110) key = ',';
if (Key == 222) key = '~';
if (Key == 193) key = '/';
if (Key == 219) key = '´';
keys[key] = 0;
keys[Key] = 0;
kbscan[key] = 0;
kbscan[Key] = 0;               
webkit_keyup(key);
webbrowser_keyup_on = true;
}

void setkeyshift(int Shift)
{
keyshift = Shift;
}

int getkeychar()
{
for (int i=0;i<256;i++)
{
if (keyshift)
{
  if (i != VK_SHIFT) return i;
}
if (keys[i]) return i;
}
}

int getkeystate(unsigned char Key)
{
  return keys[Key];
}

int getkeyshift()
{
  return keyshift;
}

