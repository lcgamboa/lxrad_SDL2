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


#include"../include/cbutton.h"

// CButton___________________________________________________________

CButton::CButton (void)
{
  Text = new CLabel;
  Text->SetText ("Button");
  Text->SetFont (FontName);
  Text->SetX (0);
  Text->SetY (0);
  SetX (10);
  SetY (10);
  SetWidth (60);
  SetHeight (20);
  Press = false;
  SetClass ("CButton");
  CreateChild (Text);
};

CButton::~CButton (void)
{
};

void
CButton::Create (CControl * control)
{
  CControl::Create (control);
  PressColor = ColorByName ("gray");
};

void
CButton::Draw (void)
{
  SDL_Color TColor;
	
  if((!Visible)||(Paint == NULL))return;
  
  Paint->InitDraw (this);

  if (Press && PointerOn)
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

CStringList CButton::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine (xml_out (lxT("Text"), lxT("String"), GetText ()));

  return Context;
};

void
CButton::SetContext (CStringList context)
{	
  Eraser ();
  String name, type, value;
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      xml_in (Context.GetLine (i), name, type, value);
      if (name.compare (lxT("Text")) == 0)
	SetText (value);
    };
  Draw ();
};

//propiedades

void
CButton::SetPress (bool press)
{
  Press = press;
  Draw ();
};

bool
CButton::GetPress (void)
{
  return Press;
};

void
CButton::SetText (String t)
{
  Text->SetText (t);
  Draw ();
};

String CButton::GetText (void)
{
  return Text->GetText ();
};

void
CButton::SetWidth (uint width)
{
  Text->SetWidth (width);
  CControl::SetWidth (width);
};

void
CButton::SetHeight (uint height)
{
  Text->SetHeight (height);
  CControl::SetHeight (height);
};

//eventos

void
CButton::key_press (SDL_Event event)
{
  
  if (event.key.keysym.sym == SDLK_RETURN)
    {
      Press = true;
      Draw ();
      CControl::button_press (event);
    }
  else
    CControl::key_press (event);
};

void
CButton::key_release (SDL_Event event)
{

  if (event.key.keysym.sym == SDLK_RETURN)
    {
      Press = false;
      Draw ();
      CControl::button_release (event);
    }
  else
    CControl::key_release (event);
};

void
CButton::button_press (SDL_Event event)
{
  if (event.button.button == 1)
    {
      Press = true;
      Draw ();
      CControl::button_press (event);
    };
};

void
CButton::button_release (SDL_Event event)
{
  if (event.button.button == 1)
    {
      Press = false;
      Draw ();
      CControl::button_release (event);
    };
};

void
CButton::pointer_in (void)
{
  CControl::pointer_in ();
};

void
CButton::pointer_out (void)
{
  CControl::pointer_out ();
  if (Press)
    {
      Draw ();
      Press = false;
    };
};

void
CButton::SetAlign (CAlign align)
{
  Text->SetAlign (align);
};

CAlign CButton::GetAlign (void)
{
  return Text->GetAlign ();
};

void
CButton::focus_in (void)
{
  Draw ();
  CControl::focus_out ();
};

void
CButton::focus_out (void)
{
  Draw ();
  CControl::focus_out ();
};
