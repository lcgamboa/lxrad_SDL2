/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001  Luis Claudio Gambôa Lopes

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

#ifndef CUTILS
#define CUTILS

#include"clxrad.h"
#include"mstring.h"

struct TXColor
{
  String name;
  XColor color;
  XColor displaycolor;
};

void mprint(String message);

void eprint(String error);

XColor ColorByRGB (unsigned short r, unsigned short g, unsigned short b);

XColor ColorByName (String name);

int XXLookupString (XIC ic, XKeyPressedEvent * event, char *buffer_return,
		    int bytes_buffer, KeySym * keysym_return,
		    Status * status_return);

#endif
