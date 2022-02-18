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


#include"../include/cmessage.h"
#include"../include/capplication.h"

// CMessage__________________________________________________________


CMessage::CMessage (void)
{
  SetClass ("CMessage");
  SetX (320);
  SetY (240);
  SetWidth (285);
  SetHeight (115);
  SetName ("Message");
  SetVisible(false);
  #ifdef _ONEWIN
  OverWin=true;
  #endif
  //button1
  button1.SetText ("OK");
  button1.SetX (110);
  button1.SetY (70);
  button1.SetFOwner (this);
  button1.EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CMessage::ButtonRelease1;
  CreateChild (&button1);
  //string1
  string1.SetText ("OK");
  string1.SetX (0);
  string1.SetY (0);
  string1.SetWidth (285);
  string1.SetHeight (75);
  CreateChild (&string1);
}


void
CMessage::ButtonRelease1 (CControl * control, uint button, uint x, uint y,
			  uint state)
{
  HideExclusive ();
}

CMessage wmessage;
 
void
Message (lxString str)
{
  wmessage.string1.SetText (str);

#ifdef _ONEWIN  
  wmessage.SetX((Application->GetARootWindow()->GetWidth ()- wmessage.GetWidth())/2);
  wmessage.SetY((Application->GetARootWindow()->GetHeight ()- wmessage.GetHeight())/2);
#else
  wmessage.SetX(((Application->GetARootWindow()->GetWidth ()- wmessage.GetWidth())/2)+Application->GetARootWindow()->GetX ());
  wmessage.SetY(((Application->GetARootWindow()->GetHeight ()- wmessage.GetHeight())/2)+Application->GetARootWindow()->GetY ());
#endif  
  if(!wmessage.GetWWindow ())
    wmessage.WCreate ();
  wmessage.Draw ();
  wmessage.ShowExclusive ();
  //wmessage.SetCanDestroy (true);
}

void
Message_sz (lxString str, int Width, int Height)
{
  wmessage.string1.SetText (str);
  
  wmessage.SetWidth (Width);
  wmessage.SetHeight (Height);
  wmessage.button1.SetX ((Width- wmessage.button1.GetWidth())/2);
  wmessage.button1.SetY (Height-75);
  wmessage.string1.SetWidth (Width-5);
  wmessage.string1.SetHeight (Height-95);

#ifdef _ONEWIN  
  wmessage.SetX((Application->GetARootWindow()->GetWidth ()- wmessage.GetWidth())/2);
  wmessage.SetY((Application->GetARootWindow()->GetHeight ()- wmessage.GetHeight())/2);
#else
  wmessage.SetX(((Application->GetARootWindow()->GetWidth ()- wmessage.GetWidth())/2)+Application->GetARootWindow()->GetX ());
  wmessage.SetY(((Application->GetARootWindow()->GetHeight ()- wmessage.GetHeight())/2)+Application->GetARootWindow()->GetY ());
#endif  
  if(!wmessage.GetWWindow ())
    wmessage.WCreate ();
  wmessage.Draw ();
  wmessage.ShowExclusive ();
  //wmessage.SetCanDestroy (true);
}
