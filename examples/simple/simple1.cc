/* ########################################################################

   XGRP -  GUI for X programing

   ########################################################################

   Copyright (c) : Luis Claudio Gambôa Lopes

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


#include"simple1.h"
#include"simple1_d.cc"

CWindow1 Window1;

//Implementation

void
CWindow1::button1_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
//Add
  string1.SetText("+");
  edit3.SetText(ftoa(atof(edit1.GetText())+atof((edit2.GetText()))));
};

void
CWindow1::button2_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
//Sub
  string1.SetText("-");
  edit3.SetText(ftoa(atof(edit1.GetText())-atof((edit2.GetText()))));
};

void
CWindow1::button3_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
//Mul
  string1.SetText("*");
  edit3.SetText(ftoa(atof(edit1.GetText())*atof((edit2.GetText()))));
};

void
CWindow1::button4_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
//Div
  string1.SetText("/");
  edit3.SetText(ftoa(atof(edit1.GetText())/atof((edit2.GetText()))));
};

void
CWindow1::button5_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  Window1.WDestroy();
};

void
CWindow1::_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
 Message("You clicked in the Window!");
};

void
CWindow1::menu1_About_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
   Message("LXRAD Simple Program by LCGambôa");
};

void
CWindow1::pmenu1_Exit_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  Window1.WDestroy();
};

