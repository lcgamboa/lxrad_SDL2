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

#ifndef CLIST
#define CLIST

#include"ccontrol.h"
#include"clabel.h"
#include"cscroll.h"
#include"cwindow.h"

#define ONCHANGEITEM   (void(CControl::*)(CList*))

class CList:public CControl
{
protected:
  CScroll * Scroll;
  CLabel **Itens;
  int ItensCount;
  CStringList ItensList;
  int SelectedItem;
  bool ShowSelection;
  void change_item (void);
  void AddStringItem (String text);
public:
    CList (void);
   ~CList (void);
  void Draw (void);
  void Update (void);
  void Create (CControl * control);
  CStringList GetContext (void);
  void SetContext (CStringList context);
  //propiedades
  void SetItens (String litens);
  String GetItens (void);
  void AddItem (String text);
  void LoadItensFromFile (String fname);
  void SaveItensToFile (String fname);
  String GetItem (int item);
  void SetItem(int item,String sitem);
  void SetSelectedItemN (int item);
  void SetSelectedItem (String item);
  int GetSelectedItemN (void);
  String GetSelectedItem (void);
  int GetItensCount (void);
  void DeleteItem (int item);
  void DeleteItens (bool clean=true);
  void SetX (int x);
  void SetY (int y);
  void SetWidth (uint width);
  void SetHeight (uint height);
  void SetShowSelection (bool show);
  bool GetShowSelection (void);
  //eventos
  void ScrollOnChangePosition (CScroll * scroll, bool status);
  void ScrollOnButtonPress (CControl * control, uint button, uint x, uint y,
			    uint state);
  void ItemButtonPress (CControl * control, uint button, uint x, uint y,
			uint state);
  void button_press (XEvent event);
  void key_press (XEvent event);
  void focus_in (void);
  void focus_out (void);
  
  void (CControl::*OnChangeItem) (CList * list);
};

#endif
