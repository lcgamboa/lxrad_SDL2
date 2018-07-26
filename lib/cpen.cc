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
#include"../include/capplication.h"

// CPen________________________________________________________________

void
CPen::Create (CControl * control)
{
    Owner=control;
};

void
CPen::SetColor (SDL_Color color)
{
  Color = color;
  if((Owner)&&(Owner->GetWin()))
    SDL_SetRenderDrawColor(Owner->GetWin()->GetRenderer(),color.r,color.g,color.b,0xFF);
};

void
CPen::SetBGColor (SDL_Color color)
{
  BGColor = color;
 // if((Owner)&&(Owner->GetWin()))
 //   SDL_SetRenderDrawColor(Owner->GetWin()->GetRenderer(),color.r,color.g,color.b,0xFF);
};

SDL_Color CPen::GetColor ()
{
  return Color;
};

SDL_Color CPen::GetBGColor ()
{
  return BGColor;
};


void
CPen::SetWidth (unsigned long width)
{
//  XSetLineAttributes(Disp, *Agc, width, LineSolid, CapNotLast,JoinMiter);
};

void
CPen::SetPen (int function)
{
//  XSetFunction (Disp, *Agc, function);
};

