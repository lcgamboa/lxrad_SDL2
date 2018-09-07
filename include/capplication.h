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

#ifndef CAPPLICATION
#define CAPPLICATION

#include"clxrad.h"
#include"cwindow.h"
#include"ctimer.h"
#include"cthread.h"
#include"chint.h"
#include<locale.h>

class CWindow;

class CApplication
{
private:
  SDL_Event AEvent, LAEvent;
  CWindow **AWindowList;
  CWindow * ARootWindow;
  int AWindowCount;
  CTimer **TimerList;
  int TimerCount;
  CThread **ThreadList;
  int ThreadCount;
  timeval LastDrawTime;
  bool Exit;
  unsigned int FWindow;
  CControl* HintControl;
  long int HintTime;
  int HintX,HintY;
  int Tag;
  String Title;
  CWindow * MWindow; //Modal Window
public:
    CApplication (void);
   ~CApplication (void);
  void Start (void);
  void ACreateWindow (CWindow * AWindow,CWindow* window=NULL);
  void ADestroyWindow (CWindow * AWindow);
  bool ProcessEvents (void);
  void AddTimer(CTimer *tm);	
  void RemoveTimer(CTimer *tm);	
  void AddThread(CThread *td);	
  void RemoveThread(CThread *td);	
  void Draw (void);
  void Update (void);
  void Load (void);
  int Aargc;
  char **Aargv;
  bool GetExit (void);
  //propiedades
  int GetAWindowCount (void);
  CWindow *GetAWindow (uint window);
  CWindow *GetARootWindow (void);
  void SetModalWindow (CWindow * mwindow);
  CWindow * GetModalWindow (void);
  void SetTag (int x);
  int GetTag ();
  String GetTitle ();
  void SetHintControl(CControl* hcontrol,int x,int y);
};


#endif
