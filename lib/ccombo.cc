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

#include"../include/ccombo.h"
#include"../include/capplication.h"


// CCombo_____________________________________________________________

CCombo::CCombo (void)
{
 SetClass ("CCombo");
 edit1.SetText ("");
 edit1.SetFont (FontName);
 edit1.SetReadOnly (true);
 edit1.SetFOwner (this);
 edit1.EvKeyboardPress = EVKEYBOARDPRESS & CCombo::EditKeyPress;

 tbutton1.SetFOwner (this);
 tbutton1.EvMouseButtonPress = EVMOUSEBUTTONPRESS & CCombo::TButtonPress;

 dlist1.SetX (10);
 dlist1.SetY (10);

 dlist1.combo = this;

 SetX (10);
 SetY (10);
 SetHeight (20);
 SetWidth (80);
 CreateChild (&edit1);
 CreateChild (&tbutton1);
 //CreateChild (&dlist1);
 EvOnComboChange = NULL;
};

CCombo::~CCombo (void)
{
 dlist1.WDestroy ();
};

int
CCombo::Create (CControl * control)
{
 return CControl::Create (control);
}

void
CCombo::SetWidth (unsigned width)
{
 if (Width == width) return;
 edit1.SetX (0);
 edit1.SetWidth (width - GetHeight () - 1);
 tbutton1.SetX (width - GetHeight ());
 tbutton1.SetWidth (GetHeight ());

 edit1.SetY (0);
 edit1.SetHeight (Height);
 tbutton1.SetY (0);
 tbutton1.SetHeight (Height);

 dlist1.SetWidth (width);
 
 CControl::SetWidth (width);
};

void
CCombo::SetHeight (unsigned height)
{
 if (Height == height)return;
 edit1.SetY (0);
 edit1.SetHeight (height);
 tbutton1.SetY (0);
 tbutton1.SetHeight (height);

 edit1.SetX (0);
 edit1.SetWidth (Width - height - 1);
 tbutton1.SetX (Width - height);
 tbutton1.SetWidth (height);

 CControl::SetHeight (height);
};


void
CCombo::Draw ()
{
 if ((!Visible) || (Paint == NULL))
  return;
 
 SDL_Point points[3];
 points[0].x = 6;
 points[0].y = 6;
 points[1].x = tbutton1.GetWidth () - 12;
 points[1].y = 6;
 points[2].x = ((tbutton1.GetWidth () - 6) / 2.0);
 points[2].y = tbutton1.GetHeight () - 12;

 tbutton1.Xpm->Canvas.Init ();
 tbutton1.Xpm->Canvas.SetColor (Color);
 tbutton1.Xpm->Canvas.Rectangle (1, 0, 0, tbutton1.GetWidth (), tbutton1.GetHeight ());
 tbutton1.Xpm->Canvas.SetColor (0, 0, 0);
 tbutton1.Xpm->Canvas.Polygon (1, points, 3);
 tbutton1.Xpm->Canvas.End ();
  
 Paint->InitDraw (this);
 Paint->Pen.SetColor (Color);
 Paint->Rectangle (0, 0, Width, Height);
 CControl::Draw ();
}

void
CCombo::AddItem (lxString text)
{
 dlist1.list1.AddItem (text);
};

void
CCombo::LoadItemsFromFile (lxString fname)
{
 dlist1.list1.LoadItemsFromFile (fname);
};

void
CCombo::SaveItemsToFile (lxString fname)
{
 dlist1.list1.SaveItemsToFile (fname);
};

lxString
CCombo::GetItem (int item)
{
 return dlist1.list1.GetItem (item);
};

void
CCombo::SetSelectedItem (lxString item)
{
 dlist1.list1.SetSelectedItem (item);
 edit1.SetText (dlist1.list1.GetSelectedItem ());
 Update ();
};

lxString
CCombo::GetSelectedItem (void)
{
 return dlist1.list1.GetSelectedItem ();
};

int
CCombo::GetItemsCount (void)
{
 return dlist1.list1.GetItemsCount ();
};

void
CCombo::DeleteItem (int item)
{
 dlist1.list1.DeleteItem (item);
};

void
CCombo::DeleteItems (void)
{
 dlist1.list1.DeleteItems ();
};

lxStringList
CCombo::GetContext (void)
{
 CControl::GetContext ();
 Context.AddLine (xml_out (lxT ("Items"), lxT ("lxStringList"), GetItems ()));
 Context.AddLine (xml_out (lxT ("Text"), lxT ("lxString"), GetText ()));
 Context.AddLine (xml_out (lxT ("ReadOnly"), lxT ("bool"), itoa (GetReadOnly ())));
 Context.AddLine (xml_out (lxT ("EvOnComboChange"), lxT ("Event"), btoa (GetEv ())));
 return Context;
}

void
CCombo::SetContext (lxStringList context)
{
 lxString name, type, value;
 Erase ();

 CControl::SetContext (context);
 for (uint i = 0; i < context.GetLinesCount (); i++)
  {
   xml_in (Context.GetLine (i), name, type, value);
   if (name.compare (lxT ("Text")) == 0)
    SetText (value);
   if (name.compare (lxT ("Items")) == 0)
    SetItems (value);
   if (name.compare (lxT ("ReadOnly")) == 0)
    SetReadOnly (atoi (value));
   if (name.compare (lxT ("EvOnComboChange")) == 0)
    SetEv (atob (value));
  };
 Draw ();
}

void
CCombo::SetText (lxString text)
{
 edit1.SetText (text);
};

lxString
CCombo::GetText (void)
{
 return edit1.GetText ();
};

void
CCombo::SetItems (lxString litens)
{
 dlist1.SetItems (litens);
};

lxString
CCombo::GetItems (void)
{
 return dlist1.GetItems ();
};


//events

void
CCombo::EditKeyPress (CControl * control, const uint key, const uint hk, uint mask)
{
 Update ();
};

void
CCombo::TButtonPress (CControl * control, uint button, uint x, uint y,
                      uint state)
{
 int wx, wy;
 //Window child;

 Update ();

 dlist1.SetX (0);
 dlist1.SetY (0);
 /*
   if (!dlist1.GetWWindow ())
     {
       //Application.ACreateWindow (&dlist1,Win);
       Application->ACreateWindow (&dlist1);
     };
  */

 //  XTranslateCoordinates (Win->GetADisplay (), Win->GetWWindow (),
 //			 dlist1.GetWWindow (), GetX (), GetY (), &wx, &wy,
 //			 &child);
#ifdef _ONEWIN    
 wx = Win->GetX () + X;
 if(Win->HasMenu)
   wy = Win->GetY () + Y + Height + 17;
 else 
   wy = Win->GetY () + Y + Height -8;
#else
 wx = Win->GetX () + X;
 wy = Win->GetY () + Y + Height;
#endif  
 dlist1.SetX (wx);
 dlist1.SetY (wy + GetHeight () + 1);
 if (!dlist1.GetWWindow ())
  dlist1.WCreate (Win);

 //dlist1.list1.Draw ();
 dlist1.ShowExclusive ();

};

void
CCombo::combo_change (void)
{
 if ((FOwner) && (EvOnComboChange))
  (FOwner->*EvOnComboChange) (this);
};

void
CCombo::SetReadOnly (bool r)
{
 edit1.SetReadOnly (r);
}

bool
CCombo::GetReadOnly (void)
{
 return edit1.GetReadOnly ();
};
