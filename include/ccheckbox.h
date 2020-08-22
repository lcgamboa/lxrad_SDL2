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

#ifndef CCHECKBOX
#define CCHECKBOX


#include"ccontrol.h"
#include"clabel.h"
#include"cwindow.h"
#include"cbox.h"

class CCheckBox:public CControl
{
private:
  CLabel * Text;
  CCbox *CBox;
public:
    CCheckBox (void);
   ~CCheckBox (void);
  int Create (CControl * control);
  lxStringList GetContext (void);
  void SetContext (lxStringList context);
  void Draw (void);
  //propiedades
  void SetCheck (bool check);
  bool GetCheck (void);
  void SetText (lxString t);
  lxString GetText (void);
  void SetWidth (uint width);
  void SetHeight (uint height);
  void SetAlign (CAlign align);
  CAlign GetAlign (void);
  //events
  void key_press (SDL_Event event);
  void button_press (SDL_Event event);
  void (CControl::*EvOnCheckBox) (CControl * control);
};

#endif
