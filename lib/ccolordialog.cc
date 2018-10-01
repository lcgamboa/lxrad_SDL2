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

#include"../include/ccolordialog.h"

CColorDialog::CColorDialog (void)
{
 EvOnClose = NULL;
 SetClass ("CColorDialog");
 SetX (310);
 SetY (240);
 SetWidth (320);
 SetHeight (243);
 SetName ("CColorDialog");
#ifdef _ONEWIN
 OverWin = true;
#endif
 //scroll1
 scroll1.SetFOwner (this);
 scroll1.SetClass (lxT ("CScroll"));
 scroll1.SetName (lxT ("scroll1"));
 scroll1.SetTag (0);
 scroll1.SetX (88);
 scroll1.SetY (40);
 scroll1.SetWidth (130);
 scroll1.SetHeight (20);
 scroll1.SetHint (lxT (""));
 scroll1.SetEnable (1);
 scroll1.SetVisible (1);
 scroll1.SetColor (lxT ("#000001"));
 scroll1.SetPopupMenu (NULL);
 scroll1.SetRange (256);
 scroll1.SetPosition (100);
 scroll1.SetType (4);
 scroll1.EvOnChangePosition = EVONCHANGEPOSITION & CColorDialog::scroll_EvOnChangePosition;
 CreateChild (&scroll1);
 //scroll2
 scroll2.SetFOwner (this);
 scroll2.SetClass (lxT ("CScroll"));
 scroll2.SetName (lxT ("scroll2"));
 scroll2.SetTag (0);
 scroll2.SetX (88);
 scroll2.SetY (72);
 scroll2.SetWidth (130);
 scroll2.SetHeight (20);
 scroll2.SetHint (lxT (""));
 scroll2.SetEnable (1);
 scroll2.SetVisible (1);
 scroll2.SetColor (lxT ("#000001"));
 scroll2.SetPopupMenu (NULL);
 scroll2.SetRange (256);
 scroll2.SetPosition (100);
 scroll2.SetType (4);
 scroll2.EvOnChangePosition = EVONCHANGEPOSITION & CColorDialog::scroll_EvOnChangePosition;
 CreateChild (&scroll2);
 //scroll3
 scroll3.SetFOwner (this);
 scroll3.SetClass (lxT ("CScroll"));
 scroll3.SetName (lxT ("scroll3"));
 scroll3.SetTag (0);
 scroll3.SetX (89);
 scroll3.SetY (104);
 scroll3.SetWidth (130);
 scroll3.SetHeight (20);
 scroll3.SetHint (lxT (""));
 scroll3.SetEnable (1);
 scroll3.SetVisible (1);
 scroll3.SetColor (lxT ("#000001"));
 scroll3.SetPopupMenu (NULL);
 scroll3.SetRange (256);
 scroll3.SetPosition (100);
 scroll3.SetType (4);
 scroll3.EvOnChangePosition = EVONCHANGEPOSITION & CColorDialog::scroll_EvOnChangePosition;
 CreateChild (&scroll3);
 //label1
 label1.SetFOwner (this);
 label1.SetClass (lxT ("CLabel"));
 label1.SetName (lxT ("label1"));
 label1.SetTag (0);
 label1.SetX (22);
 label1.SetY (39);
 label1.SetWidth (60);
 label1.SetHeight (20);
 label1.SetHint (lxT (""));
 label1.SetEnable (1);
 label1.SetVisible (1);
 label1.SetColor (lxT ("#000001"));
 label1.SetPopupMenu (NULL);
 label1.SetText (lxT ("Red"));
 label1.SetAlign (1);
 CreateChild (&label1);
 //label2
 label2.SetFOwner (this);
 label2.SetClass (lxT ("CLabel"));
 label2.SetName (lxT ("label2"));
 label2.SetTag (0);
 label2.SetX (22);
 label2.SetY (69);
 label2.SetWidth (60);
 label2.SetHeight (20);
 label2.SetHint (lxT (""));
 label2.SetEnable (1);
 label2.SetVisible (1);
 label2.SetColor (lxT ("#000001"));
 label2.SetPopupMenu (NULL);
 label2.SetText (lxT ("Green"));
 label2.SetAlign (1);
 CreateChild (&label2);
 //label3
 label3.SetFOwner (this);
 label3.SetClass (lxT ("CLabel"));
 label3.SetName (lxT ("label3"));
 label3.SetTag (0);
 label3.SetX (22);
 label3.SetY (101);
 label3.SetWidth (60);
 label3.SetHeight (20);
 label3.SetHint (lxT (""));
 label3.SetEnable (1);
 label3.SetVisible (1);
 label3.SetColor (lxT ("#000001"));
 label3.SetPopupMenu (NULL);
 label3.SetText (lxT ("Blue"));
 label3.SetAlign (1);
 CreateChild (&label3);
 //button1
 button1.SetFOwner (this);
 button1.SetClass (lxT ("CButton"));
 button1.SetName (lxT ("button1"));
 button1.SetTag (1);
 button1.SetX (81);
 button1.SetY (149);
 button1.SetWidth (65);
 button1.SetHeight (28);
 button1.SetHint (lxT (""));
 button1.SetEnable (1);
 button1.SetVisible (1);
 button1.SetColor (lxT ("#000001"));
 button1.SetPopupMenu (NULL);
 button1.EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CColorDialog::button_EvMouseButtonRelease;
 button1.SetText (lxT ("Ok"));
 CreateChild (&button1);
 //button2
 button2.SetFOwner (this);
 button2.SetClass (lxT ("CButton"));
 button2.SetName (lxT ("button2"));
 button2.SetTag (0);
 button2.SetX (175);
 button2.SetY (150);
 button2.SetWidth (65);
 button2.SetHeight (28);
 button2.SetHint (lxT (""));
 button2.SetEnable (1);
 button2.SetVisible (1);
 button2.SetColor (lxT ("#000001"));
 button2.SetPopupMenu (NULL);
 button2.EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CColorDialog::button_EvMouseButtonRelease;
 button2.SetText (lxT ("Cancel"));
 CreateChild (&button2);
 //edit1
 edit1.SetFOwner (this);
 edit1.SetClass (lxT ("CEdit"));
 edit1.SetName (lxT ("edit1"));
 edit1.SetTag (0);
 edit1.SetX (225);
 edit1.SetY (35);
 edit1.SetWidth (80);
 edit1.SetHeight (26);
 edit1.SetHint (lxT (""));
 edit1.SetEnable (1);
 edit1.SetVisible (1);
 edit1.SetColor (lxT ("#000001"));
 edit1.SetPopupMenu (NULL);
 edit1.EvOnFocusOut = EVONFOCUSOUT & CColorDialog::edit_EvOnFocusOut;
 edit1.SetText (lxT (""));
 edit1.SetReadOnly (1);
 CreateChild (&edit1);
 //edit2
 edit2.SetFOwner (this);
 edit2.SetClass (lxT ("CEdit"));
 edit2.SetName (lxT ("edit2"));
 edit2.SetTag (0);
 edit2.SetX (225);
 edit2.SetY (66);
 edit2.SetWidth (80);
 edit2.SetHeight (26);
 edit2.SetHint (lxT (""));
 edit2.SetEnable (1);
 edit2.SetVisible (1);
 edit2.SetColor (lxT ("#000001"));
 edit2.SetPopupMenu (NULL);
 edit2.EvOnFocusOut = EVONFOCUSOUT & CColorDialog::edit_EvOnFocusOut;
 edit2.SetText (lxT (""));
 edit2.SetReadOnly (1);
 CreateChild (&edit2);
 //edit3
 edit3.SetFOwner (this);
 edit3.SetClass (lxT ("CEdit"));
 edit3.SetName (lxT ("edit3"));
 edit3.SetTag (0);
 edit3.SetX (225);
 edit3.SetY (98);
 edit3.SetWidth (80);
 edit3.SetHeight (26);
 edit3.SetHint (lxT (""));
 edit3.SetEnable (1);
 edit3.SetVisible (1);
 edit3.SetColor (lxT ("#000001"));
 edit3.SetPopupMenu (NULL);
 edit3.EvOnFocusOut = EVONFOCUSOUT & CColorDialog::edit_EvOnFocusOut;
 edit3.SetText (lxT (""));
 edit3.SetReadOnly (1);
 CreateChild (&edit3);
}

CColorDialog::~CColorDialog (void) { }

void
CColorDialog::Create (CControl * control)
{
 CWindow::Create (control);
}

void
CColorDialog::Run (void)
{
 SetTitle (GetName ());
 if (!WWindow)
  WCreate (Win);
 CControl::SetColor (Color);
 
 scroll1.SetPosition (Color.GetR ());
 scroll2.SetPosition (Color.GetG ());
 scroll3.SetPosition (Color.GetB ());
  
 edit1.SetText (itoa(Color.GetR ()));
 edit2.SetText (itoa(Color.GetG ()));
 edit3.SetText (itoa(Color.GetB ()));
 
 ShowExclusive ();
 
}

String
CColorDialog::GetColorName (void)
{
 return Color.GetAsString();
}

void
CColorDialog::SetColorName (String cname)
{
 Color = ColorByName(cname);
}

lxColor
CColorDialog::GetColor (void)
{
 return Color;
}

void
CColorDialog::SetColor (lxColor c)
{
 Color = c;
}

void
CColorDialog::SetColor (uint r, uint g, uint b)
{
 Color = ColorByRGB (r, g, b);
}

CStringList
CColorDialog::GetContext (void)
{
 CControl::GetContext ();
 return Context;
}

void
CColorDialog::SetContext (CStringList context)
{
 Eraser ();
 CControl::SetContext (context);
 /*
 for (uint i = 0; i < context.GetLinesCount (); i++)
   {
     String line = Context.GetLine (i);
     String arg;
     eqparse (line, arg);
   };
  */
 Draw ();
}

void
CColorDialog::scroll_EvOnChangePosition (CControl * control) 
{ 
 
 lxColor color = ColorByRGB(scroll1.GetPosition (),scroll2.GetPosition (),scroll3.GetPosition ());
 CControl::SetColor(color);
 
 edit1.SetText (itoa(color.GetR ()));
 edit2.SetText (itoa(color.GetG ()));
 edit3.SetText (itoa(color.GetB ()));
}

void
CColorDialog::edit_EvOnFocusOut (CControl * control) 
{ 
}

void
CColorDialog::button_EvMouseButtonRelease (CControl * control, const uint button, const uint x, const uint y, const uint state)
{
 int Result = control->GetTag ();

 HideExclusive ();
 if (Result)
  {
   Color= CControl::GetColor ();
  }
 WDestroy ();
 Owner->Draw ();
 if ((FOwner) && (EvOnClose))
  (FOwner->*EvOnClose) (Result);
};
