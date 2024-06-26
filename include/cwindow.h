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

#ifndef CWINDOW
#define CWINDOW

#include"ccontrol.h"
#include"cpaint.h"

#define EVONCREATE        (void(CControl::*)(CControl*))
#define EVONDESTROY       (void(CControl::*)(CControl*))
#define EVONSHOW          (void(CControl::*)(CControl*))
#define EVONHIDE          (void(CControl::*)(CControl*))
#define EVONENTER         (void(CControl::*)(CControl*))
#define EVONLEAVE         (void(CControl::*)(CControl*))

class CWindow:public CControl
{
private:    
  int move_on;
  int onewin_cursor;
protected:
  bool ORedirect;  
  SDL_Texture* WPixmap;
  uint PWidth,PHeight;
  lxString Title;
  unsigned int XMouse, YMouse;
  CControl *ControlOnFocus;
  CControl *LastControl;
  SDL_Window* WWindow;
  SDL_Renderer* Renderer;
  //SDL_Event LEvent;//last event
  unsigned long BorderColor;
  CPaint WPaint;
  bool CanDestroy;
  CWindow* WParent;
  bool CanExitExclusive;
  void CreatePixmap(bool draw=false);
  void DestroyPixmap(void);
  bool PixmapBuffer;
  bool OverWin;
  int Redraw;
  CControl * statusbar;
public:
  bool HasMenu;//FIXME tornar privado
    CWindow (void);
   ~CWindow (void);
  virtual void Draw (void);
  virtual void Destroy (void);
  void DestroyChild (CControl * control);
  void DestroyChilds (void);
  virtual void WCreate (CWindow* window = NULL);
  virtual void WDestroy (void);
  void Show (void);
  void ShowExclusive (void);
  void Hide (void);
  void HideExclusive (void);
  void Update (void);
  void Update (SDL_Rect Reg);
  virtual bool WEvents (SDL_Event WEvent);
  lxStringList GetContext (void);
  void SetContext (lxStringList context);
  void SetFocus (void);
  void SetPixmapBuffer(bool pbuffer);
  bool GetPixmapBuffer(void);
  int LoadXMLContextAndCreateChilds (lxString filename, CControl* ctrl = NULL);
  bool GetCanExitExclusive(void);
  bool OwnerEvent (int x, int y);
  void CreateChild (CControl * control);
//propriedades
  SDL_Window * GetWWindow (void);
  SDL_Renderer * GetRenderer (void);
  CWindow* GetWWidget (void);
  void SetCanDestroy (bool candestroy);
  bool GetCanDestroy (void);
  void SetOverrideRedirect (bool redirect);
  bool GetOverrideRedirect (void);
  void SetSaveUnder (bool saveunder);
  virtual void SetX (int x);
  virtual void SetY (int y);
  virtual void SetWidth (uint width);
  virtual void SetHeight (uint height);
  void SetXMouse (uint x);
  uint GetXMouse (void);
  void SetYMouse (uint y);
  uint GetYMouse (void);
  void SetTitle (const lxString & title);
  lxString GetTitle (void);
  CControl *GetControlOnFocus (void);
  void SetControlOnFocus (CControl * controlonfocus);
  CControl *GetLastControl (void);
  SDL_Texture* GetPixmap(void);
  void SetLastControl (CControl * lastcontrol);
  void CirculateFocus (bool asc);
  bool GetOverWin(void);
  void SetOverWin(bool ow);
  void SetRedraw(void);
  int  GetRedraw(void);
  int GetClientHeight (void);
  int GetClientWidth (void);
  //operator
  void *operator new (size_t sz);
  void operator delete(void* p);
  //eventos
  virtual void on_create (void);
  virtual void on_destroy (void);
  virtual void on_show (void);
  virtual void on_hide (void);
  virtual void on_enter (void);
  virtual void on_leave (void);

  void (CControl::*EvOnCreate) (CControl * win);
  void (CControl::*EvOnDestroy) (CControl * win);
  void (CControl::*EvOnShow) (CControl * win);
  void (CControl::*EvOnHide) (CControl * win);
  void (CControl::*EvOnEnter) (CControl * win);
  void (CControl::*EvOnLeave) (CControl * win);
};


#endif
