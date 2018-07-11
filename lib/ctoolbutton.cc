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


#include"../include/ctoolbutton.h"


// CToolButton___________________________________________________________

CToolButton::CToolButton (void)
{
  Xpm = new CDraw;
  Xpm->SetBorder (0);
  Xpm->SetCanExecuteEvent (false);
  Xpm->SetTransparent (true);
  Xpm->SetX (2);
  Xpm->SetY (2);
  SetX (10);
  SetY (10);
  SetWidth (26);
  SetHeight (26);
  Press = false;
  SetClass ("CToolButton");
  CanFocus=false;
  DestroyChilds ();
  CreateChild (Xpm);
};

CToolButton::~CToolButton (void)
{
};

void
CToolButton::Create (CControl * control)
{
  CButton::Create (control);
  Xpm->SetColor (GetColor ());
};

void
CToolButton::Draw (void)
{
  if ((!Visible)||(Paint == NULL))return;
  Paint->InitDraw (this);
  if (Press && PointerOn)
    {
      Paint->Pen.SetColor (PressColor);
      Paint->Rectangle ( 0, 0, Width, Height);
      Xpm->SetColor (PressColor);
      Paint->LowerFrame ( 0, 0, Width, Height, Border);
    }
  else
    {
      Paint->Pen.SetColor (Color);
      Paint->Rectangle ( 0, 0, Width, Height);
      Xpm->SetColor (Color);
      Paint->RaiserFrame ( 0, 0, Width, Height, Border);
    };
  CControl::Draw ();
};

CStringList CToolButton::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine ("PixmapFileName=" + GetPixmapFileName () + ";File");
  return Context;
};

void
CToolButton::SetContext (CStringList context)
{
  Eraser ();
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      String line = Context.GetLine (i);
      String arg;
      eqparse (line, arg);
      if (line.compare ("PixmapFileName") == 0)
      {
	if(arg.size() >  0)
	  SetPixmapFileName (arg);
	else
	  SetPixmapFileName ("");
      }
    };
  Draw ();
};

//propiedades

void
CToolButton::SetPixmapData (char **data)
{
  Xpm->SetPixmapData (data);
  Draw ();
};

void
CToolButton::SetPixmapFileName (String filename)
{
  Xpm->SetPixmapFileName (filename);
  Draw ();
};

String
CToolButton::GetPixmapFileName (void)
{
  return Xpm->GetPixmapFileName ();
};

void
CToolButton::SetWidth (uint width)
{
  CControl::SetWidth (width);
  Xpm->SetWidth (width - 4);
};

void
CToolButton::SetHeight (uint height)
{
  CControl::SetHeight (height);
  Xpm->SetHeight (height - 4);
};
