// Fast Engine Graphical User Interface (F.E.G.U.I)
// This feature is a part of FastEngine
// by Mario Freire
// Copyright (C) 2012 DSP Interactive. All rights reserved.
// Development Systems and Programs
// See more information in the website: https://www.dspinteractive.com.br

#ifndef MSGBOX_H
#define MSGBOX_H

#include "cimp.h"
#include "callback.h"
#include "gfx.h"
#include "window.h"
#include "button.h"
#include "label.h"
#include "image.h"


static const short mrNone = 0x0;
static const short mrOk = 0x1;
static const short mrCancel = 0x2;
static const short mrAbort = 0x3;
static const short mrRetry = 0x4;
static const short mrIgnore = 0x5;
static const short mrYes = 0x6;
static const short mrNo = 0x7;
static const short mrAll = 0x8;
static const short mrNoToAll = 0x9;
static const short mrYesToAll = 0xa;

void messagebox(TWindow* handle,char* text,char *caption,int msgtype);


#endif // MSGBOX_H
