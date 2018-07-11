/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001  Luis Claudio Gambôa Lopes

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

#include"../include/clist.h"

// CList_____________________________________________________________

CList::CList (void)
{
  Scroll = new CScroll;
  Scroll->SetPosition (0);
  Scroll->SetRange (1);
  Scroll->SetFOwner (this);
  Scroll->EvMouseButtonPress = EVMOUSEBUTTONPRESS & CList::ScrollOnButtonPress;
  Scroll->EvOnChangePosition = EVONCHANGEPOSITION & CList::ScrollOnChangePosition;
  Itens = NULL;
  ItensCount = -1;
  ItensList.Clear ();
  SetX (10);
  SetY (10);
  SetWidth (160);
  SetHeight (130);
  SetClass ("CList");
  SelectedItem = 0;
  CreateChild (Scroll);
  OnChangeItem = NULL;
  ShowSelection = true;
};


CList::~CList (void)
{
  if (Itens)
    {
      delete[]Itens;
      Itens = NULL;
    };
  ItensCount = -1;
};

void
CList::Create (CControl * control)
{
  if (!ColorSet)
    SetColor ("white");
  CControl::Create (control);
};

void
CList::Draw ()
{
  if ((!Visible)||(Paint == NULL))
    return;
  int lcount = ItensList.GetLinesCount ();
  int ssize = Scroll->GetWidth ();

  Paint->InitDraw (this);
  Paint->Pen.SetColor (Color);
  Paint->Rectangle ( 0, 0, Width - ssize, Height);
  Paint->LowerFrame ( 0, 0, Width - ssize, Height);


  if(GChanges)
  {
  DeleteItens (false);
  if ((ItensCount == -1) && (Height > 20) && (lcount > 0))
    {
      GChanges=false;	  
      AddStringItem (ItensList.GetLine (0));
      int h = Itens[0]->GetTextHeight ();
      int y = 0;
      Itens[0]->SetVisible (false, false);
      Itens[0]->SetY (y);
      Itens[0]->SetVisible (true, false);
      for (int c = 1; (h * c + h) < (int) Height; c++)
	{
	  AddStringItem ("");
	  int y = h * c;
	  Itens[c]->SetVisible (false, false);
	  Itens[c]->SetY (y);
	  Itens[c]->SetVisible (true, false);
	};
      
      Scroll->SetVisible (false, false);
      Scroll->SetX (Width - Scroll->GetWidth ());
      Scroll->SetHeight (Height);
      Scroll->SetVisible (true, false);
    };
  };
      
  Scroll->SetVisible (false, false);
  Scroll->SetRange (lcount - ItensCount);
  Scroll->SetVisible (true, false);
  
  for (int c = 0; c <= ItensCount; c++)
    {
      Itens[c]->SetVisible (false, false);
      if(c < lcount)
        Itens[c]->SetText (ItensList.GetLine (c + Scroll->GetPosition ()));
      else
        Itens[c]->SetText ("");
      Itens[c]->SetVisible (true, false);
    };

  CControl::Draw ();

  if (ShowSelection)
    {
      if ((SelectedItem - Scroll->GetPosition () >= 0) &&
	  (SelectedItem - Scroll->GetPosition () <= ItensCount))
	{
	  SetColor ("dark blue");
	  XColor color =
	    Itens[SelectedItem - Scroll->GetPosition ()]->GetColor ();
	  Itens[SelectedItem - Scroll->GetPosition ()]->SetColor ("white");
	  Itens[SelectedItem - Scroll->GetPosition ()]->Draw ();
	  SetColor ("white");
	  Itens[SelectedItem - Scroll->GetPosition ()]->SetColor (color);
	};
      Update ();
    };
};

void
CList::Update ()
{
  CControl::Update ();
};

CStringList
CList::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine ("Itens=" + GetItens () + ";StringList");
  Context.AddLine ("OnChangeItem=" + btoa (GetEv ()) + ";event");
  return Context;
};

void
CList::SetContext (CStringList context)
{
  Eraser ();
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      String line = Context.GetLine (i);
      String arg;
      eqparse (line, arg);
      if (line.compare ("Itens") == 0)
	  SetItens (arg);
      if (line.compare ("OnChangeItem") == 0)
	SetEv (atob (arg));
    };
  Draw ();
};


//propriedades

void
CList::SetItens (String litens)
{
  int f = 0;
  ItensList.Clear ();
  while (f + 1 <= (int) litens.size ())
    {
      f = litens.find (",");
      ItensList.AddLine (litens.substr (0, f));
      litens = litens.substr (f + 1, litens.size ());
    };
  Draw ();
};

String
CList::GetItens (void)
{
  String list = "";
  for (uint c = 0; c < ItensList.GetLinesCount (); c++)
    {
      list += ItensList.GetLine (c) + ",";
    };
  return list;
};

void
CList::AddStringItem (String text)
{
  CLabel *item = new CLabel;
  item->SetText (text);
  item->SetAlign (ca_left);
  item->SetCanExecuteEvent (true);
  item->SetX (5);
  item->SetY (5);
  item->SetTag (ItensCount + 1);
  item->SetWidth (Width - Scroll->GetWidth () - 10);
  item->SetVisible (false, false);
  item->SetFOwner (this);
  item->EvMouseButtonPress = EVMOUSEBUTTONPRESS & CList::ItemButtonPress;
  CreateChild (item);
  ItensCount++;
  CLabel **AItens = new CLabel *[ItensCount + 1];
  for (int c = 0; c < ItensCount; c++)
    AItens[c] = Itens[c];
  AItens[ItensCount] = item;
  if (Itens)
    delete[]Itens;
  Itens = AItens;
};

void
CList::AddItem (String text)
{
  ItensList.AddLine (text);
  Draw ();
};

String CList::GetItem (int item)
{
  if (item <= (int) ItensList.GetLinesCount ())
    return ItensList.GetLine (item);
  else
    return '\0';
};

void
CList::SetItem (int item,String sitem)
{
  if (item <= (int) ItensList.GetLinesCount ())
    ItensList.SetLine (sitem,item);
};

void
CList::SetSelectedItemN (int item)
{
  SelectedItem = item;
  if (ItensCount != -1)
    {
      Draw ();
    };
  change_item ();
};

void
CList::SetSelectedItem (String item)
{

  for (uint c = 0; c < ItensList.GetLinesCount (); c++)
    {
      if (ItensList.GetLine (c).compare (item) == 0)
	{
	  SelectedItem = c;
	  if (ItensCount != -1)
	    {
	      Draw ();
	    };
	  change_item ();

	  break;
	};
    };
};

int
CList::GetSelectedItemN (void)
{
  if (((uint) (SelectedItem) < ItensList.GetLinesCount ()))
    {
      return SelectedItem;
    }
  else
    {
      return -1;
    };
};

String CList::GetSelectedItem (void)
{
  if (((uint) (SelectedItem) < ItensList.GetLinesCount ()))
    {
      return ItensList.GetLine (SelectedItem);
    }
  else
    {
      return "";
    };
};

int
CList::GetItensCount (void)
{
  return ItensList.GetLinesCount ();
};

void
CList::DeleteItem (int item)
{
  if (item >= 0)
    {
      ItensList.DelLine (item);
      Scroll->SetVisible (false, false);
      Scroll->SetPosition (0);
      Scroll->SetVisible (true, false);
      Draw ();
    };
};

void
CList::DeleteItens (bool clean)
{
  GChanges=true;	
  if (Itens != NULL)
    {
      for (int c = 0; c <= ItensCount; c++)
	{
	  Itens[c]->SetVisible (false, false);
	  DestroyChild (Itens[c]);
	  Itens[c] = NULL;
	};
      delete[]Itens;
      Itens = NULL;
      ItensCount = -1;
    };
  if (clean)
    {
      Scroll->SetPosition (0);
      ItensList.Clear ();
      SelectedItem = -1;
      Draw ();
    };
};

void
CList::SetX (int x)
{
  Scroll->SetX (Width - Scroll->GetWidth ());
  CControl::SetX (x);
};

void
CList::SetY (int y)
{
  Scroll->SetY (0);
  CControl::SetY (y);
};

void
CList::SetWidth (uint width)
{
  if (ItensCount >= 0)
    {
      for (int c = 0; c < ItensCount; c++)
	Itens[c]->SetWidth (width - Scroll->GetWidth () - 10);
    };
  Scroll->SetX (width - Scroll->GetWidth ());
  CControl::SetWidth (width);
};

void
CList::SetHeight (uint height)
{
  Scroll->SetHeight (height);
  CControl::SetHeight (height);
};

void
CList::LoadItensFromFile (String fname)
{
  DeleteItens ();
  ItensList.LoadFromFile (fname);
  Draw();
};

void
CList::SaveItensToFile (String fname)
{
  ItensList.SaveToFile (fname);
};

void
CList::SetShowSelection (bool show)
{
  ShowSelection = show;
  Draw ();
};

bool CList::GetShowSelection (void)
{
  return ShowSelection;
};

//eventos

void
CList::ScrollOnButtonPress (CControl * control, uint button, uint x, uint y,
			    uint state)
{
  Update ();
};

void
CList::ScrollOnChangePosition (CScroll * scroll, bool status)
{
  Draw ();
};

void
CList::ItemButtonPress (CControl * control, uint button, uint x, uint y,
			uint state)
{
  if (ShowSelection)
    {
      XColor color;
      if ((SelectedItem - Scroll->GetPosition () >= 0) &&
	  (SelectedItem - Scroll->GetPosition () <= ItensCount))
	{
	  SetColor ("white");
	  Itens[SelectedItem - Scroll->GetPosition ()]->Draw ();
	};
      SetColor ("dark blue");
      color = control->GetColor ();
      control->SetColor ("white");
      control->Draw ();
      SetColor ("white");
      control->SetColor (color);
    }
  SelectedItem = control->GetTag () + Scroll->GetPosition ();
  Update ();
  change_item ();
};

void
CList::change_item (void)
{
  if ((FOwner) && (OnChangeItem))
    (FOwner->*OnChangeItem) (this);
};

void
CList::button_press (XEvent event)
{
  CControl::button_press (event);
};

void
CList::key_press (XEvent event)
{
  CControl::key_press (event);
};

void
CList::focus_in (void)
{
  CControl::focus_in ();
};

void
CList::focus_out (void)
{
  CControl::focus_out ();
};
