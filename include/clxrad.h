/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001  Luis Claudio Gamb�a Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#ifndef CLXRAD
#define CLXRAD


#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif

#define NO_STL


#ifndef NO_STL
//c++ headers
using namespace std;
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#endif

//c headers
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//X11 headers
#include<X11/Xlib.h>
#include<X11/Xatom.h>
#include<X11/Xutil.h>
#include<X11/keysym.h>

#include"lxutils.h"

#define Initialize int pmain(void); CApplication application; CApplication *Application=&application;\
	int main(int argc,char **argv){\
	application.Aargc=argc;application.Aargv=argv; pmain();}\
        int pmain(void)


#define AllEventMask KeyPressMask | KeyReleaseMask |KeymapStateMask | ButtonPressMask | ButtonReleaseMask |\
                     ButtonMotionMask| EnterWindowMask | LeaveWindowMask | ExposureMask | \
		     StructureNotifyMask | FocusChangeMask | PointerMotionMask

#define Parent 99999
#define EVMAX 100
#define DOUBLECLICKTIME 400

#define EVMOUSEMOVE              (void(CControl::*)(CControl*,uint,uint))
#define EVMOUSEBUTTONPRESS       (void(CControl::*)(CControl*,uint,uint,uint,uint))
#define EVMOUSEBUTTONRELEASE     (void(CControl::*)(CControl*,uint,uint,uint,uint))
#define EVMOUSEBUTTONCLICK       (void(CControl::*)(CControl*,uint,uint,uint,uint))
#define EVMOUSEBUTTONDOUBLECLICK (void(CControl::*)(CControl*,uint,uint,uint,uint))
#define EVKEYBOARDPRESS          (void(CControl::*)(CControl*,uint,uint,uint,uint))
#define EVKEYBOARDRELEASE        (void(CControl::*)(CControl*,uint,uint,uint,uint))
#define EVKEYBOARDKEY            (void(CControl::*)(CControl*,uint,uint,uint,uint))
#define EVPOINTERIN              (void(CControl::*)(CControl*))
#define EVPOINTEROUT             (void(CControl::*)(CControl*))
#define EVONDRAW                 (void(CControl::*)(CControl*))
#define EVCFOCUSIN              (void(CControl::*)(CControl*))
#define EVCFOCUSOUT             (void(CControl::*)(CControl*))
#define EVMENUACTIVE            (void(CControl::*)(CControl*))
#define EVONTIME                (void(CControl::*)(CControl*))
#define EVONTOGGLEBUTTON        (void(CControl::*)(CControl*))
#define EVTHREADRUN     	(void(CControl::*)(CControl*))
#define EVTHREADEND	        (void(CControl::*)(CControl*))
#define EVONCHANGESPINDOUBLE    (void(CControl::*)(CControl*))

typedef unsigned int uint;

#define  CAlign int
#define  ca_right  1
#define  ca_center 2
#define  ca_left 3

class CApplication;
extern CApplication *Application;

#endif
