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

#include"../include/cfilelist.h"

// CFileList_____________________________________________________________

CFileList::CFileList (void)
{
  SetClass ("CFileList");
  char *temp = get_current_dir_name ();
  Dir = temp;
  delete[]temp;
  OnDirSelected = NULL;
  OnFileSelected = NULL;
  ItensType = NULL;
};


CFileList::~CFileList (void)
{
  if (ItensType)
    {
      delete[]ItensType;
      ItensType = NULL;
    };
};

void
CFileList::Create (CControl * control)
{
  CList::Create (control);
  char *temp = get_current_dir_name ();
  SetVisible (false, false);
  SetDir (temp);
  SetVisible (true, false);
  delete[]temp;
};

int
file_filter (const struct dirent *de)
{
  if ((de->d_type == DT_REG) && (de->d_name[0] != '.'))
    return 1;
  else
    return 0;
};

int
dir_filter (const struct dirent *de)
{
  if ((de->d_type == DT_DIR)
      && ((de->d_name[0] != '.') || (de->d_name[1] == '.')))
    return 1;
  else
    return 0;
};

void
CFileList::SetDir (String dir)
{
  struct dirent **dirs = NULL;
  struct dirent **files = NULL;
  int n;

  Dir = dir;
  
  Scroll->SetPosition (0);
  ItensList.Clear ();
  SelectedItem = -1;

  n = scandir (Dir.c_str (), &dirs, dir_filter, alphasort);
  if (n >= 0)
    {
      for (int cnt = 0; cnt < n; ++cnt)
	AddItem (dirs[cnt]->d_name, dirs[cnt]->d_type);
    }
  else
    eprint( "Couldn't open the directory " + Dir +"\n");
  for (int cnt = 0; cnt < n; ++cnt)
    {
      if (dirs[cnt])
	delete dirs[cnt];
    };
    delete[]dirs;
  
  dirs = NULL;

  n = scandir (Dir.c_str (), &files, file_filter, alphasort);
  if (n >= 0)
    {
      for (int cnt = 0; cnt < n; ++cnt)
	AddItem (files[cnt]->d_name, files[cnt]->d_type);
    }
  else
    eprint("Couldn't open the directory " + Dir + "\n");
  for (int cnt = 0; cnt < n; ++cnt)
    {
      if (files[cnt])
	delete files[cnt];
    };
   delete[]files;
  
  files = NULL;
  
  Draw ();
};

void
CFileList::Draw ()
{
  if((!Visible)||(Paint == NULL))
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
      for (int c = 1;(h * c + h) < (int) Height; c++)
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
      {
         Itens[c]->SetText (ItensList.GetLine (c + Scroll->GetPosition ()));
      if (ItensType[c + Scroll->GetPosition ()] == DT_REG)
	{
	  Itens[c]->EvMouseButtonRelease =
	    EVMOUSEBUTTONRELEASE & CFileList::FileButtonRelease;
	  Itens[c]->EvMouseButtonClick = NULL;
	  Itens[c]->SetColor ("black");
	};
      if (ItensType[c + Scroll->GetPosition ()] == DT_DIR)
	{
	  Itens[c]->EvMouseButtonRelease = NULL;
	  Itens[c]->EvMouseButtonClick =
	    EVMOUSEBUTTONCLICK & CFileList::DirButtonClick;
	  Itens[c]->SetColor ("blue");
	  Itens[c]->SetText ("/" + Itens[c]->GetText ());
	};
       }
      else
      {
        Itens[c]->SetText(""); 
	Itens[c]->EvMouseButtonRelease = NULL;
	Itens[c]->EvMouseButtonClick = NULL;
	Itens[c]->SetColor ("black");
      };
      Itens[c]->SetVisible (true, false);
    };
  CControl::Draw ();

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

CStringList 
CFileList::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine ("OnChangeItem=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("OnFileSelected=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("OnDirSelected=" + btoa (GetEv ()) + ";event");
  return Context;
};

void
CFileList::SetContext (CStringList context)
{
  Eraser ();
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      String line = Context.GetLine (i);
      String arg;
      eqparse (line, arg);
      if (line.compare ("OnChangeItem") == 0)
	SetEv (atob (arg));
      if (line.compare ("OnFileSelected") == 0)
	SetEv (atob (arg));
      if (line.compare ("OnDirSelected") == 0)
	SetEv (atob (arg));
    };
  Draw ();
};


//propriedades

void
CFileList::AddStringItem (String text)
{
  CLabel *item;
  item = new CLabel;
  item->SetText (text);
  item->SetAlign (ca_left);
  item->SetCanExecuteEvent (true);
  item->SetX (5);
  item->SetY (5);
  item->SetWidth (Width - Scroll->GetWidth () - 10);
  item->SetTag (ItensCount + 1);
  item->SetVisible (false, false);
  item->SetFOwner (this);
  item->EvMouseButtonPress = EVMOUSEBUTTONPRESS & CFileList::ItemButtonPress;
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
CFileList::AddItem (char *name, unsigned char dtype)
{
  int ICount = ItensList.GetLinesCount ();
  unsigned char *AItensType = new unsigned char[ICount + 1];
  for (int c = 0; c < ICount; c++)
    AItensType[c] = ItensType[c];
  AItensType[ICount] = dtype;
  if (ItensType)
    delete[]ItensType;
  ItensType = AItensType;
  
  ItensList.AddLine (name);
};

void
CFileList::DeleteItens (bool clean)
{
  CList::DeleteItens (clean);
  if ((ItensType) && (clean))
    {
      delete[]ItensType;
      ItensType = NULL;
    };
};


String
CFileList::GetSelectedDir (void)
{
  return Dir;
};

String
CFileList::GetSelectedFile (void)
{
  return (Dir +"/"+ ItensList.GetLine(SelectedItem));
};

void
CFileList::DirButtonClick (CControl * control, uint button, uint x,
			   uint y, uint state)
{
  CLabel *item;
  String dir = GetSelectedDir ();

  item = dynamic_cast < CLabel * >(control);

  SetVisible (false, false);
  if (item->GetText ().compare ("/..") != 0)
    {
      if (dir.size () != 1)
	SetDir (dir + item->GetText ());
      else
	SetDir (item->GetText ());
    }
  else
    {
      int pos = dir.rfind ("/");
      if (pos > 0)
	SetDir (dir.substr (0, pos));
      else
	SetDir ("/");
    };
  SetVisible (true, false);
  Draw ();
  dir_selected ();
  change_item();
};

void
CFileList::dir_selected (void)
{
  if ((FOwner) && (OnDirSelected))
    (FOwner->*OnDirSelected) (this);
};

void
CFileList::FileButtonRelease (CControl * control, uint button, uint x, uint y,
			      uint state)
{
  file_selected ();
  change_item();
};

void
CFileList::file_selected (void)
{
  if ((FOwner) && (OnFileSelected))
    (FOwner->*OnFileSelected) (this);
};
