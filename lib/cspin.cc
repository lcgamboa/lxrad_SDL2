/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2020  Luis Claudio Gamboa Lopes

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

#include"../include/cspin.h"


// CSpin_____________________________________________________________

CSpin::CSpin (void)
{
  Value=50;				
  Min=0;
  Max=100;
  Inc=1;
  EvOnChangeSpin=NULL;
  
  SetClass ("CSpin");
  edit1.SetText ("");
  edit1.SetFont (FontName);
  edit1.SetReadOnly (false);
  edit1.SetFOwner (this);
  edit1.EvKeyboardPress = EVKEYBOARDPRESS & CSpin::EditKeyPress;

  tbutton1.SetFOwner (this);
  tbutton1.EvMouseButtonPress = EVMOUSEBUTTONPRESS & CSpin::TButtonPress1;
  
  tbutton2.SetFOwner (this);
  tbutton2.EvMouseButtonPress = EVMOUSEBUTTONPRESS & CSpin::TButtonPress2;

  SetX (10);
  SetY (10);
  SetHeight (20);
  SetWidth (80);
  CreateChild (&edit1);
  CreateChild (&tbutton1);
  CreateChild (&tbutton2);
}

CSpin::~CSpin (void)
{
}

int
CSpin::Create (CControl * control)
{
  return CControl::Create (control);
}

void
CSpin::SetWidth (unsigned width)
{
  edit1.SetX (0);
  edit1.SetWidth (width - GetHeight () - 1);
  tbutton1.SetX (width - GetHeight ());
  tbutton1.SetWidth (GetHeight ());
  tbutton2.SetX (width - GetHeight ());
  tbutton2.SetWidth (GetHeight ());

  CControl::SetWidth (width);
};

void
CSpin::SetHeight (unsigned height)
{
  edit1.SetY (0);
  edit1.SetHeight (height);
  tbutton1.SetY (0);
  tbutton1.SetHeight (height/2);
  tbutton2.SetY (height/2);
  tbutton2.SetHeight (height/2);
  CControl::SetHeight (height);
};

void
CSpin::Draw ()
{
  if ((!Visible)||(Paint == NULL))
    return;
  
  SDL_Point points[3];
  points[0].x= 3;
  points[0].y= tbutton1.GetHeight ()-6;;
  points[1].x= tbutton1.GetWidth () -6;
  points[1].y=points[0].y;
  points[2].x=((tbutton1.GetWidth ()-3)/2.0) ;
  points[2].y=3;
  
  tbutton1.Xpm->Canvas.Init();
  tbutton1.Xpm->Canvas.SetFgColor(Color);
  tbutton1.Xpm->Canvas.Rectangle (1,0,0,tbutton1.GetWidth (),tbutton1.GetHeight ());
  tbutton1.Xpm->Canvas.SetColor(0,0,0);
  tbutton1.Xpm->Canvas.Polygon (1,points,3);
  tbutton1.Xpm->Canvas.End ();
  
  points[0].x= 3;
  points[0].y= 3;
  points[1].x= tbutton2.GetWidth () -6;
  points[1].y=3;
  points[2].x=((tbutton2.GetWidth ()-3)/2.0) ;
  points[2].y=tbutton2.GetHeight ()-6;
  
  tbutton2.Xpm->Canvas.Init();
  tbutton2.Xpm->Canvas.SetFgColor(Color);
  tbutton2.Xpm->Canvas.Rectangle (1,0,0,tbutton2.GetWidth (),tbutton2.GetHeight ());
  tbutton2.Xpm->Canvas.SetColor(0,0,0);
  tbutton2.Xpm->Canvas.Polygon (1,points,3);
  tbutton2.Xpm->Canvas.End ();
  
  Paint->InitDraw (this);
  Paint->Pen.SetColor (Color);
  Paint->Rectangle ( 0, 0, Width, Height);
  CControl::Draw ();
};

lxStringList 
CSpin::GetContext (void)
{
  //FIXME	
  lxStringList sl;
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  return sl;
}

void 
CSpin::SetContext (lxStringList context)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}
  
void 
CSpin::SetValue(int v)
{	
  Value=v;
  edit1.SetText(lxString().Printf("%i",Value));  
}

int 
CSpin::GetValue (void)
{
  return Value;	
}

void 
CSpin::SetMin(int v)
{
  Min=v;	
}

int 
CSpin::GetMin (void)
{
 return Min;	
}

void 
CSpin::SetMax(int v)
{
  Max=v;	
}

int 
CSpin::GetMax (void)
{
  return Max;	
}

void 
CSpin::SetInc(int v)
{
  Inc=v;	
}

int 
CSpin::GetInc (void)
{
  return Inc;	
}

void
CSpin::EditKeyPress (CControl * control, const uint key, const uint hk, uint mask)
{
  Update ();
};

void
CSpin::TButtonPress1 (CControl * control, uint button, uint x, uint y, uint state)
{
  Value+=Inc;
  if(Value > Max)Value=Max;
  SetValue(Value);
};

void
CSpin::TButtonPress2 (CControl * control, uint button, uint x, uint y, uint state)
{
  Value-=Inc;
  if(Value < Min)Value=Min;
  SetValue(Value);
};
