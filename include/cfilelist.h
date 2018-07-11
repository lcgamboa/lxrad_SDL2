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

#ifndef CFILELIST
#define CFILELIST

#include"clist.h"
#include"cwindow.h"
#include<unistd.h>
#include<dirent.h>

#define ONFILESELECTED   (void(CControl::*)(CFileList*))
#define ONDIRSELECTED   (void(CControl::*)(CFileList*))

class CFileList:public CList
{
protected:
  String Dir;
  void dir_selected (void);
  void file_selected (void);
  unsigned char *ItensType;
public:
    CFileList (void);
   ~CFileList (void);
  void Draw (void);
  void Create (CControl * control);
  CStringList GetContext (void);
  void SetContext (CStringList context);
  //propiedades
  void AddItem (char *name, unsigned char dtype);
  void AddStringItem (String text);
  void DeleteItens (bool clean=true);
  void SetDir (String dir);
  String GetSelectedDir (void);
  String GetSelectedFile (void);
//events
  void DirButtonClick (CControl * control, uint button, uint x, uint y,
			     uint state);
  void FileButtonRelease (CControl * control, uint button, uint x, uint y,
			  uint state);
  void (CControl::*OnFileSelected) (CFileList * flist);
  void (CControl::*OnDirSelected) (CFileList * flist);
};

#endif
