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

/**
 * \file cspind.h
 * \author Luis Claudio Gamboa Lopes
 * \date 07-10-2016
 */

#ifndef CSPIND
#define CSPIND

#include"ccontrol.h"
#include"cwindow.h"
#include"cedit.h"
#include"ctoolbutton.h"

/** \brief SPIND Control.
 *
 * Generic Spind Control Class.
 */

class CSpind:public CControl
{
protected:
  CEdit edit1;
  CToolButton tbutton1;
  CToolButton tbutton2;
  double Value;				
  double Min;
  double Max;
  double Inc;
  int Digits;
  int CEvent (int event);
public:
    CSpind (void);
   ~CSpind (void);
  void Draw (void);
  void SetWidth(unsigned width);
  void SetHeight(unsigned height );
  int Create (CControl * control);
  CStringList GetContext (void);
  void SetContext (CStringList context);
  //void Event (wxEvent & event);
  //propiedades
  void SetValue(double v);
  double GetValue (void);
  void SetMin(double v);
  double GetMin (void);
  void SetMax(double v);
  double GetMax (void);
  void SetInc(double v);
  double GetInc (void);
  void SetDigits(int v);
  int GetDigits(void);
  //eventos
  void EditKeyPress (CControl * control, const uint key, const uint hk, uint mask);
  void TButtonPress1 (CControl * control, const uint button, const uint x, const uint y, const uint state);
  void TButtonPress2 (CControl * control, const uint button, const uint x, const uint y, const uint state);
  void (CControl::*EvOnChangeSpinDouble) (CControl * control);
};

#endif
