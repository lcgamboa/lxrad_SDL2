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

#ifndef CTOOLBUTTON
#define CTOOLBUTTON

#include"cbutton.h"
#include"cdraw.h"

class CToolButton:public CButton
{
private:
public:
  CDraw * Xpm;
  CToolButton (void);
   ~CToolButton (void);
  void Draw (void);
  int  Create (CControl * control);
  CStringList GetContext (void);
  void SetContext (CStringList context);
  //propiedades
  void SetPixmapFileName (String filename);
  void SetImgFileName(String filename);
  String GetPixmapFileName (void);
  void SetWidth (uint width);
  void SetHeight (uint height);

};

#endif
