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

#ifndef CFILEDIALOG
#define CFILEDIALOG

#include<sys/stat.h>
#include<errno.h>
#include"cbutton.h"
#include"cedit.h"
#include"cfilelist.h"
#include"capplication.h"
#include"cwindow.h"

class CFileDialog:public CWindow
{
private:
  bool CanDestroyChilds;
  bool Result;
  lxString Filter;
  int Type;
  lxString FileName;
  CButton button1, button2, button3, button4;
  CEdit edit1;
  CFileList filelist1;
public:
    CFileDialog (void);
   ~CFileDialog (void);
  int Create(CControl* control);
  void Run (void);
  //propriedades
  lxString GetFileName (void);
  void SetFileName (lxString filename);
  lxString GetDir (void);
  void SetDir (lxString dir);
  void DestroyChilds (void);
  lxStringList GetContext (void);
  void SetContext (lxStringList context);
  void SetFilter(lxString filter);
  void SetType(int type);
  int GetType(void);
  //events
  void (CControl::*EvOnClose) (const int retId);
  void ButtonRelease1 (CControl * control, const uint button, const uint x, const uint y, const uint state);
  void ButtonRelease2 (CControl * control, const uint button, const uint x, const uint y, const uint state);
  void ButtonRelease3 (CControl * control, const uint button, const uint x, const uint y, const uint state);
  void ButtonRelease4 (CControl * control, const uint button, const uint x, const uint y, const uint state);
  void ListOnFileSelected (CControl * flist);
};

#endif
