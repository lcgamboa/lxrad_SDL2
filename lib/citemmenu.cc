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


#include"../include/citemmenu.h"
#include"../include/cpmenu.h"
#include"../include/cmenu.h"
#include"../include/capplication.h"


//CItemMenu------------------------------------------------------

CItemMenu::CItemMenu (void)
{
 SetCanExecuteEvent (true);
 SetClass ("CItemMenu");
 SubMenu = NULL;
 EvMenuActive = NULL;
 CanVisible = false;
}

void
CItemMenu::Draw (void)
{
 if ((!Visible) || (Paint == NULL)) return;

 Width = GetTextWidth () + 2;
 Height = GetTextHeight ();

 CPMenu *PMenu = dynamic_cast<CPMenu *> (Owner);
 CMenu *Menu = dynamic_cast<CMenu *> (Owner);

 if (Menu != NULL)
  {

   Y = 2;
   X = Menu->NextItemX;
   Menu->NextItemX += Width + 20;
   Height = Menu->GetHeight () - 4;
  }

 if (PMenu != NULL)
  {
   X = 4+PMenu->NextItemX;
   Y = PMenu->NextItemY + 4;
   PMenu->NextItemY += Height + 4;

      if((PMenu->NextItemY / (Height + 4)) == 30)
       {
          PMenu->NextItemY=0;
          PMenu->NextItemX+= PMenu->GetWidth ()/((PMenu->GetChildCount ()/30)+1);
       }
  }
 CLabel::Draw ();
}

int
CItemMenu::Create (CControl * control)
{
 return CLabel::Create (control);
}

void
CItemMenu::SetSubMenu (CPMenu * submenu)
{
 SubMenu = submenu;
};

CPMenu *
CItemMenu::GetSubMenu (void)
{
 return SubMenu;
}

lxStringList
CItemMenu::GetContext (void)
{
 CObject::GetContext ();

 Context.AddLine ("Text=" + GetText () + ";lxString");

 if (SubMenu)
  Context.AddLine ("SubMenu=" + SubMenu->GetName () + ";SubMenu");
 else
  Context.AddLine ("SubMenu=NULL;SubMenu");

 Context.AddLine ("MouseButtonPress=" + btoa (GetEv (true)) + ";event");

 /*
 for (uint i = 0; i < Context.GetLinesCount(); i++)
 {
 if(Context.GetLine(i).find("PopupMenu") == 0)
   Context.DelLine(i);
 };
  */
 return Context;
};

void
CItemMenu::SetContext (lxStringList context)
{
 Erase ();
 CObject::SetContext (context);
 for (uint i = 0; i < context.GetLinesCount (); i++)
  {
   lxString line = Context.GetLine (i);
   lxString arg;
   eqparse (line, arg);
   if (line.compare ("Text") == 0)
    SetText (arg);
   if (line.compare ("SubMenu") == 0)
    if (arg.compare ("NULL") != 0)
     SetSubMenu (dynamic_cast<CPMenu *> (Win->GetChildByName (arg)));
   if (line.compare ("MouseButtonPress") == 0)
    SetEv (atob (arg), true);
  };
 Draw ();
};


//eventos

void
CItemMenu::button_press (SDL_Event event)
{
 CPMenu *PMenu = dynamic_cast<CPMenu *> (Owner);
 if (PMenu != NULL)
  {
   PMenu->HideExclusive ();
   //XSync(GetWin()->GetADisplay(),false);
   //      XFlush(GetWin()->GetADisplay());
   CControl::button_press (event);

   if ((FOwner) && (EvMenuActive))
    {
     (FOwner->*EvMenuActive) (this);
    }
   return;
  };

 if ((SubMenu) && ((SubMenu->GetChildCount ()) != -1))
  {
   /* 
      //Window child;
      if ((!SubMenu->GetWWindow ()) != 0)
    {
      //Application.ACreateWindow (SubMenu,Win);
      Application->ACreateWindow (SubMenu);
    };
    */


   SubMenu->SetX (Win->GetX () + GetX ());
   
#ifdef _ONEWIN
   SubMenu->SetY (Win->GetY () + GetY () + Height+20);
#else
   SubMenu->SetY (Win->GetY () + GetY () + Height);   
#endif
   
   if(!SubMenu->GetWWindow ())     
     SubMenu->WCreate (Win);
   //SubMenu->Show ();
   SubMenu->Draw ();
   SubMenu->ShowExclusive ();
  }
 //Owner->GetWin ()->Update ();
 //CControl::button_press (event);
};

void
CItemMenu::button_release (SDL_Event event)
{
 if (SubMenu)
  {
    //SubMenu->WDestroy ();
    SubMenu->HideExclusive ();
  }
 //CControl::button_release (event);
};

void
CItemMenu::focus_out (void)
{
 if (SubMenu != NULL)
  {
    //SubMenu->WDestroy ();
    SubMenu->HideExclusive ();
  }
  //CControl::focus_out ();
};

