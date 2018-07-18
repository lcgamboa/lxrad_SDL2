/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2016  Luis Claudio Gamboa Lopes

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

/**
 * \file ctogglebutton.h
 * \author Luis Claudio Gamboa Lopes
 * \date 07-17-2016
 */

#ifndef CTOGGLEBUTTON
#define CTOGGLEBUTTON


#include"cbutton.h"
#include"cwindow.h"

/** \brief Toggle Button Control
 *
 * Toggle Button Control class
 */

class CToggleButton:public CButton
{
private:
  bool Check;
public:
   CToggleButton (void);
  //propriedades
  void Draw (void);
  void SetCheck (bool check);
  bool GetCheck (void);
  //Events
  void key_press (XEvent event);
  void button_press (XEvent event);
  void (CControl::*EvOnToggleButton) (CControl * control);
};

#endif
