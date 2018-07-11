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

#include"../include/clabel.h"

/*
Pixmap 
XCreateFontMask (
		Display *display, 
		Drawable d, 
		unsigned long int pixel, 
		Pixmap p, 
		int width, 
		int height)
{
  register int x, c, b;
  register unsigned char *ptr;
  int y;
  unsigned char *data;
  int bytes_per_line;
  XImage* image;
  Pixmap pixmap;
	  
  image = XGetImage (display, p, 0, 0, width, height, AllPlanes, XYPixmap);

  bytes_per_line = (width + 7) / 8;

  data = (unsigned char *) malloc ( bytes_per_line * height );
  if (!data)
    return 0;
  
  ptr = data;
  c = 0;
  b = 1;
  for (y = 0; y < height; y++)
    {
      for (x = 0; x < width;)
	{
	  if (XGetPixel (image, x, y)!=pixel)
	    c |= b;
	  b <<= 1;
	  if (!(++x & 7))
	    {
	      *(ptr++) = c;
	      c = 0;
	      b = 1;
	    }

	}
      if (x & 7)
	{
	  *(ptr++) = c;
	  c = 0;
	  b = 1;
	}
    }
  XDestroyImage (image);
  pixmap=XCreateBitmapFromData (display, d, (const char *) data, width, height);
  XFree(data);
  return pixmap;
}
*/


// CLabel _________________________________________________________________

CLabel::CLabel (void)
{
  CanExecuteEvent = false;
  CanFocus = false;
  X = 0;
  Y = 0;
  Width = 60;
  Height = 20;
  Text = "Label";
  VText = "";
  TextPosition = 0;
  TextPointer = 0;
  TextMaxDisplay = 0;
  Align = ca_center;
  SetClass ("CLabel");
};


CLabel::~CLabel (void)
{
};

void
CLabel::Draw (void)
{
  if((!Visible)||(Paint == NULL))return;
  CalcVirtual ();
  SwapVirtual ();
  
  Paint->InitDraw (this);
   
  Paint->Pen.SetColor (Owner->GetColor ());
  //Paint->Pen.SetColor (ColorByName("yellow"));
  Paint->Rectangle ( 0, 0, Width, Height);
  /*
  Paint->Pen.SetColor (Color);
  Paint->Text (this, 0, Height - GetTextDes (), VText);
  */
  
  Paint->Pen.SetColor (Color);
  Paint->Pen.SetBGColor (Owner->GetColor ());
  Paint->ImgText ( 0, Height - GetTextDes (), VText);
  SwapVirtual ();
/*
  Pixmap mask=XCreateFontMask (Win->GetADisplay (), Win->GetWWindow (), ColorByName("yellow").pixel,CPixmap,50,50);

  XGCValues gcvalues;
  gcvalues.clip_x_origin = VX;
  gcvalues.clip_y_origin = VY;
  gcvalues.clip_mask = mask;
  XChangeGC (Win->GetADisplay (), Paint->Agc,
	     GCClipXOrigin | GCClipYOrigin | GCClipMask, &gcvalues);
*/
  CControl::Draw ();
/*  
  XSetClipMask (Win->GetADisplay (),Paint->Agc, None);
  XFreePixmap(Win->GetADisplay (),mask);
*/
};

void
CLabel::Update (void)
{
  if (Visible)
    {
      CalcVirtual ();
      SwapVirtual ();
      CControl::Update ();
      SwapVirtual ();
    };
};

void
CLabel::Eraser (void)
{
  CControl::Eraser ();
/*
  if ((Win == NULL)||(Win->GetPixmap() == 0))
    return;
   
//   SwapVirtual ();
   XPoint p = GetRealXY();
   Paint->Pen.SetColor (GetOwner()->GetColor());
   Paint->Rectangle (Win, p.x, p.y, Width, Height);
//   SwapVirtual ();
   CControl::Draw();
*/
};

void
CLabel::CalcVirtual (void)
{
  if (Win == NULL)
    return;

  uint TextWidth, TextWidth2;
  int xo = 0;
  bool mux=false;

  VText = Text.substr (TextPointer, Text.size ());
  TextWidth2 = XTextWidth (CFont, VText.c_str (), VText.size ());
  
  //align
  switch (Align)
    {
    case ca_right:
      while (TextWidth2 >= Width)
	{
	  VText = strndel (VText, 1);
	  TextWidth2 = XTextWidth (CFont, VText.c_str (), VText.size ());
	};
      xo = Width - TextWidth2 - 5;
      break;
    case ca_center:
      while (TextWidth2 >= Width)
	{
	  if(mux)
	  {
	  VText = strndel (VText, VText.size ());
	  mux=false;
	  }
	  else
	  {
	  VText = strndel (VText,1);
	  mux=true;
	  };
	  TextWidth2 = XTextWidth (CFont, VText.c_str (), VText.size ());
	};
      xo = (((Width - TextWidth2)) / 2);
      break;
    case ca_left:
      while (TextWidth2 >= Width)
	{
	  VText = strndel (VText, VText.size ());
	  TextWidth2 = XTextWidth (CFont, VText.c_str (), VText.size ());
	};
      xo = 5 ;
      break;
    default:
      eprint("Invalid Aligment\n");
      exit (0);
    };
  
  TextMaxDisplay = VText.size ();
  
  TextWidth = GetTextWidth ();
  
  TextPosition = XTextWidth (CFont, Text.c_str (), TextPointer)-xo+1;

  VX = X + xo;
  
  VY = Y + ((Height - GetTextHeight ()) / 2);

  VWidth = TextWidth2;

  VHeight = GetTextHeight ();
};

void
CLabel::SwapVirtual (void)
{
  int x, y;
  uint w, h;

  x = X;
  y = Y;
  w = Width;
  h = Height;

  X = VX;
  Y = VY;
  Width = VWidth;
  Height = VHeight;

  VX = x;
  VY = y;
  VWidth = w;
  VHeight = h;
};


void
CLabel::Create (CControl * control)
{
  if (!ColorSet)
    SetColor ("black");
  CControl::Create (control);
};



CStringList CLabel::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine ("Text=" + GetText () + ";String");
  return Context;
};

void
CLabel::SetContext (CStringList context)
{
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      String line = Context.GetLine (i);
      String arg;
      eqparse (line, arg);
      if (line.compare ("Text") == 0)
	SetText (arg);
    };
};

//propierties
void
CLabel::SetText (String text)
{
  Eraser ();
  Text = text;
  Draw ();
};

String CLabel::GetText (void)
{
  return Text;
};

void
CLabel::SetAlign (CAlign align)
{
  Align = align;
  Draw ();
};

CAlign CLabel::GetAlign (void)
{
  return Align;
};

uint
CLabel::GetTextWidth (void)
{
  return XTextWidth (CFont, Text.c_str (), Text.size ());
};

uint
CLabel::GetTextAsc (void)
{
  return CFont->max_bounds.ascent;
};

uint
CLabel::GetTextDes (void)
{
  return CFont->max_bounds.descent;
};

uint
CLabel::GetTextHeight (void)
{
  return GetTextAsc () + GetTextDes ();
};

uint
CLabel::GetTextMaxDisplay (void)
{
  return TextMaxDisplay;
}

//events
/*
void
CLabel::button_press (XEvent event)
{
  if ((FOwner) && (MouseButtonPress))
    (FOwner->*MouseButtonPress) (this, event.xbutton.button, event.xbutton.x,
				 event.xbutton.y, event.xbutton.state);
//  if ((!(CanExecuteEvent))&&(Owner != NULL))
//    Owner->button_press (event);
};

void
CLabel::button_release (XEvent event)
{
  if ((FOwner) && (MouseButtonRelease))
    (FOwner->*MouseButtonRelease) (this, event.xbutton.button,
				   event.xbutton.x, event.xbutton.y,
				   event.xbutton.state);
//  if (!((CanExecuteEvent))&&(Owner!=NULL))
//    Owner->button_release (event);
};
*/

uint
CLabel::GetTextPosition (void)
{
  return TextPosition;
};

uint
CLabel::GetTextPointer (void)
{
  return TextPointer;
};

void
CLabel::SetTextPointer (uint pointer)
{
  if (pointer <= Text.size ())
    TextPointer = pointer;
};
