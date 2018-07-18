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

#ifndef CDRAW
#define CDRAW

#include"ccontrol.h"
#include"cwindow.h"

class CDraw:public CControl
{
private:
  String FileName;
  char ** Data;
  bool Transparent;
  Pixmap CPixmap;
  Pixmap CMask;
  XColor BColor;
public:
  CPaint Canvas;
    CDraw (void);
   ~CDraw (void);
  void Draw (void);
  bool SetPixmapFileName (String filename);
  bool SetPixmapData (char** data);
  String GetPixmapFileName (void);
  void WritePixmapToFile (String filename);
  void WriteImgToFile (String filename);
  void Create (CControl * control);
  void Destroy (void);
  void SetWidth (uint Width);
  void SetHeight (uint height);
  bool GetTransparent (void);
  void SetTransparent (bool);
  CStringList GetContext (void);
  void SetContext (CStringList context);
  bool SetImgFileName(String iname);
  bool SetImgFileName(String iname, float sx, float sy);
};

#endif
