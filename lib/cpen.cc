/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2018  Luis Claudio Gamboa Lopes

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

#include"../include/cpen.h"
#include"../include/cpen.h"
#include"../include/cpaint.h"
#include"../include/cwindow.h"

// CPen________________________________________________________________

void
CPen::Create (CControl * control, GC * gc)
{
  if(control)
    Win = control->GetWin ();
  else
   Win=NULL;
  Agc = gc;
};

void
CPen::SetColor (XColor color)
{
  Color = color;
  XSetForeground (Win->GetADisplay (), *Agc, color.pixel);
};

void
CPen::SetBGColor (XColor color)
{
  Color = color;
  XSetBackground (Win->GetADisplay (), *Agc, color.pixel);
};

XColor CPen::GetColor ()
{
  return Color;
};

void
CPen::SetWidth (unsigned long width)
{
  XSetLineAttributes(Win->GetADisplay(), *Agc, width, LineSolid, CapNotLast,JoinMiter);
};

void
CPen::SetPen (int function)
{
  XSetFunction (Win->GetADisplay (), *Agc, function);
};

