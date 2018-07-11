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

#ifndef COBJECT
#define COBJECT

#include"clxrad.h"

class CObject
{
protected:
  bool Ev[EVMAX];
  uint Evcount;
  String Name;
  String Class;
  CStringList Context;
  uint Tag;
public:
    CObject (void);
    virtual ~ CObject (void);
//proprierties
  void SetName (const String name);
  String GetName (void);
  String GetClass (void);
  void SetClass (const String classn);
  virtual CStringList GetContext (void);
  virtual void SetContext (CStringList context);
  bool GetEv (bool reset = false);
  void SetEv (bool value, bool reset = false);
  void SetTag (uint tag);
  uint GetTag (void);
};

#endif
