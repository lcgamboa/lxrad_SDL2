/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2020  Luis Claudio Gamboa Lopes

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

#ifndef CCONTROL
#define CCONTROL

#include"cobject.h"

class CPen;
class CPaint;
class CWindow;
class CPMenu;

class CControl:public CObject
{
protected:
  CControl * FOwner;		//function owner control
  bool Dynamic;
  bool CanExecuteEvent;
  bool CanExecuteEventOld;
  bool CanFocus;
  bool PointerOn;
  bool Enable;
  bool DragAcceptFiles;
  timeval LastDrawTime;
  long int BTimePress, BTimeRelease, BTimeClick;
  int X, Y;
  int RX, RY;
  uint Width, Height;
  uint Border;
  SDL_Color Color;
  SDL_Color DisableColor;
  lxString ColorName;
  bool ColorSet;
  CControl **Child;
  int ChildCount;
  int Pen;
  lxString FontName;
  TTF_Font *CFont;
  uint FontSize;
  CControl *Owner;
  bool GChanges;
  bool Visible;
  CPMenu *PopupMenu;
  CWindow *Win;
  CPaint  *Paint;
  lxString  Hint;
  bool CanVisible;		///<Can be Visible ?
public:
  bool GetCanVisible (void);
  CControl (void);
   ~CControl (void);
  virtual bool OwnerEvent (int x, int y);
  CWindow *GetWin (void);
  void SetWin (CWindow * win);
  virtual void Event (SDL_Event event);
  virtual int Create (CControl * control);
  virtual void Destroy (void);
  virtual void Erase (void);
  virtual void Draw (void);
  virtual void Update (void);
  lxStringList GetContext (void);
  void SetContext (lxStringList context);
  void SetDragAcceptFiles(bool accept);
  SDL_Rect GetRectangle (void);
//propiedades
  void SetFont (const lxString font);
  void SetFont (TTF_Font * font);
  TTF_Font *GetFont (void);
  lxString GetFontName (void);
  void SetFontSize (uint size);
  uint GetFontSize (void);
  virtual void SetX (int x);
  int GetX (void);
  virtual void SetY (int y);
  int GetY (void);
  void CalcRXY(void);
  int GetRX (void);
  int GetRY (void);
  virtual void SetBorder (uint border);
  unsigned int GetBorder (void);
  virtual void SetWidth (unsigned w);
  uint GetWidth (void);
  virtual void SetHeight (unsigned h);
  uint GetHeight (void);
  void SetColor (SDL_Color c);
  void SetColor (const lxString name);
  void SetColor (unsigned r, unsigned g, unsigned b);
  lxColor GetColor (void);
  bool GetCanExecuteEvent (void);
  void SetCanExecuteEvent (bool cee);
  virtual void SetEnable (bool enable);
  virtual bool GetEnable (void);
  virtual void SetPen (int penwidth);
  virtual int GetPen (void);
  void SetOwner (CControl * control);
  CControl *GetOwner (void);
  void SetVisible (bool visible, bool update = true);
  bool GetVisible (void);
  void SetPopupMenu (CPMenu * popupmenu);
  void SetFocus (bool focus);
  bool GetFocus (void);
  void SetCanFocus (bool canfocus);
  bool GetCanFocus (void);
  bool GetDynamic (void);
  int GetChildCount (void);
  void SetHint(lxString hint);
  lxString GetHint(void);
  CControl *GetChild (uint child);
  CControl *GetChildByName (const lxString child);
  virtual void CreateChild (CControl * control);
  virtual void DestroyChild (CControl * control);
  virtual void DestroyChilds (void);
  virtual void WriteXMLContext (lxString filename, bool first = true);
  virtual void LoadXMLContext (lxString filename);
  
//operators
  void *operator new (size_t sz);
  void *operator new[] (size_t sz);
  void operator delete(void *p);
//events
  void SetFOwner (CControl * control);
  CControl *GetFOwner (void);
  virtual void mouse_move (SDL_Event event);
  virtual void button_press (SDL_Event event);
  virtual void button_release (SDL_Event event);
  virtual void key_press (SDL_Event event);
  virtual void key_release (SDL_Event event);
  virtual void focus_in (void);
  virtual void focus_out (void);
  virtual void pointer_in (void);
  virtual void pointer_out (void);
  virtual void on_draw (void);
  virtual void mouse_wheel (SDL_Event event);
  virtual void on_drop_files(SDL_Event event);

  void (CControl::*EvMouseMove) (CControl * control, const uint button, const uint x, const uint y, const uint mask);
  void (CControl::*EvMouseButtonPress) (CControl * control, const uint button, const uint x, const uint y, const uint mask);
  void (CControl::*EvMouseButtonRelease) (CControl * control, const uint button, const uint x, const uint y, const uint mask);
  void (CControl::*EvMouseButtonClick) (CControl * control, const uint button, const uint x, const uint y, const uint mask);
  void (CControl::*EvMouseButtonDoubleClick) (CControl * control, const uint button, const uint x, const uint y, const uint mask);
  void (CControl::*EvKeyboardPress) (CControl * control,const uint keyval,const uint hardware_keycode,const  uint state);
  void (CControl::*EvKeyboardRelease) (CControl * control,const uint keyval,const uint hardware_keycode,const uint state);
  void (CControl::*PointerIn) (CControl * control);
  void (CControl::*PointerOut) (CControl * control);
  void (CControl::*EvOnDraw) (CControl * control);
  void (CControl::*EvOnFocusIn) (CControl * control);
  void (CControl::*EvOnFocusOut) (CControl * control);
  void (CControl::*EvMouseWheel) (CControl * control, const int rotation);
  void (CControl::*EvOnDropFile) (CControl * control, const lxString fname);

};
#endif
