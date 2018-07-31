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

#ifndef COWINDOW
#define COWINDOW

#include"cwindow.h"

class COWindow:public CWindow
{
protected:
public:
    COWindow (void);
   ~COWindow (void);
  void Draw (void);
  void WCreate (CWindow* window = NULL);
  void WDestroy (void);
  void Destroy (void);

  void Show (void);
  void ShowExclusive (void);
  void Hide (void);
  void HideExclusive (void);
/*
  void Update (void);
  void Update (SDL_Rect Reg);
*/
//propiedades
};


#endif
