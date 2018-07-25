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


#include"../include/ctogglebutton.h"

// CToggleButton___________________________________________________________

CToggleButton::CToggleButton (void)
{
  EvOnToggleButton=NULL;
  SetClass ("CToggleButton");
  Check=false;
};

void
CToggleButton::Draw (void)
{
  SDL_Color TColor;
	
  if((!Visible)||(Paint == NULL))return;
  
  Paint->InitDraw (this);

  if (Check)
    {
      Paint->Pen.SetColor (PressColor);
      Paint->Rectangle ( 0, 0, Width, Height);
      Paint->LowerFrame ( 0, 0, Width, Height, Border);
      TColor=GetColor();
      SetColor(PressColor);
      CControl::Draw ();		
      SetColor(TColor);
    }
  else
    {
      Paint->Pen.SetColor (Color);
      Paint->Rectangle ( 0, 0, Width, Height);
      Paint->RaiserFrame ( 0, 0, Width, Height, Border);
      CControl::Draw ();		
    };
};

//propriedades

void
CToggleButton::SetCheck (bool check)
{
  Check = check;
  Draw ();
};

bool
CToggleButton::GetCheck (void)
{
  return Check;
};

//eventos

void
CToggleButton::key_press (SDL_Event event)
{

  if (event.key.keysym.sym == SDLK_RETURN)
    {
      Check = !Check;
      Draw ();
      CControl::button_press (event);
      if ((FOwner) && (EvOnToggleButton))
         (FOwner->*EvOnToggleButton) (this);
    }
  else
    CControl::key_press (event);
};

void
CToggleButton::button_press (SDL_Event event)
{
  if (event.button.button == 1)
    {
      Check = !Check;
      Draw ();
      CControl::button_press (event);
      if ((FOwner) && (EvOnToggleButton))
         (FOwner->*EvOnToggleButton) (this);
    };
};


