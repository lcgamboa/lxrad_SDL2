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

#include"../include/medit.h"
#include"../include/cedit.h"
#include"../include/cwindow.h"


//Manipulating Text---------------------------------------------------------------
SDL_Keysym
MEdit (CEdit * control, SDL_Event event)
{
  //buffers 
  uint cursorpos;
  SDL_Keysym key=event.key.keysym;


  if (key.sym == SDLK_RIGHT)
    {
      if (control->GetCursorPos () < control->GetText ().size ())
	control->SetCursorPos (control->GetCursorPos () + 1);
      return key;
    };
  if (key.sym == SDLK_LEFT)
    {
      if (control->GetCursorPos () > 0)
	control->SetCursorPos (control->GetCursorPos () - 1);
      return key;
    };

      switch (key.sym)
	{
	case SDLK_RETURN:
	  return key;
	  break;
	case SDLK_CAPSLOCK:
	  return key;
	  break;
	case SDLK_LSHIFT:
	  return key;
	  break;
	case SDLK_RSHIFT:
	  return key;
	  break;
	case SDLK_DOWN:
	  return key;
	  break;
	case SDLK_UP:
	  return key;
	  break;
	case SDLK_BACKSPACE:
	  if (control->GetText ().size () > 0)
	    {
	      uint cursorpos;
	      cursorpos = control->GetCursorPos ();
	      lxString nstr = strndel (control->GetText ().c_str (), cursorpos);
	      control->SetText (nstr);
	      if (cursorpos > 0)
		control->SetCursorPos (cursorpos - 1);
	      else
		control->SetCursorPos (cursorpos);
	    };
	  return key;
	  break;
	case SDLK_DELETE:
	  if (control->GetText ().size () > 0)
	    {
	      cursorpos = control->GetCursorPos ();
	      lxString nstr =
		strndel (control->GetText ().c_str (), cursorpos + 1);
	      control->SetText (nstr);
	      control->SetCursorPos (cursorpos);
	    };
	  return key;
	  break;
	default:
	     if (control->GetText ().size () ==
		  (uint) (control->GetMaxLenght ()))
		return key;
	      cursorpos = control->GetCursorPos ();
	      lxString nstr = strnadd (control->GetText (), SDL_GetKeyName(key.sym)[0], cursorpos);
	      control->SetText (nstr);
	      control->SetCursorPos (cursorpos + 1);
	      control->CControl::key_press (event);
	      return key;
	  break;
	};
  return key;
};
