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

#ifndef CSTRING
#define CSTRING

#include"ccontrol.h"
#include"cwindow.h"

class CLabel:public CControl
{
protected:
  String Text;
  String VText;
  CAlign Align;
  uint TextPosition;
  uint TextPointer;
  uint TextMaxDisplay;
  int VX;
  int VY;
  uint VWidth;
  uint VHeight;
  void CalcVirtual (void);
  void SwapVirtual (void);
public:
    CLabel (void);
   ~CLabel (void);
  void Draw (void);
  void Update (void);
  void Erase (void);
  int Create (CControl * control);
  CStringList GetContext (void);
  void SetContext (CStringList context);
//propierties  
  void SetText (String text);
  String GetText (void);
  void SetAlign (CAlign align);
  CAlign GetAlign (void);
  uint GetTextWidth (void);
  uint GetTextHeight (void);
  uint GetTextDes (void);
  uint GetTextAsc (void);
  uint GetTextPosition (void);
  uint GetTextMaxDisplay (void);
  uint GetTextPointer (void);
  void SetTextPointer (uint pointer);
//  void button_press (SDL_Event event);
//  void button_release (SDL_Event event);
};

#endif
