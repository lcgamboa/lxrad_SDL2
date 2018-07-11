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

#ifndef CWINDOW
#define CWINDOW

#include"ccontrol.h"
#include"cpaint.h"

#define ONCREATE        (void(CControl::*)(CWindow*))
#define ONDESTROY       (void(CControl::*)(CWindow*))
#define ONSHOW          (void(CControl::*)(CWindow*))
#define ONHIDE          (void(CControl::*)(CWindow*))
#define ONENTER         (void(CControl::*)(CWindow*))
#define ONLEAVE         (void(CControl::*)(CWindow*))

class CWindow:public CControl
{
protected:
  Window * ADefaultRootWindow;
  Screen *AScreen;
  uint *AWhiteColor;
  uint *ABlackColor;
  Pixmap WPixmap;
  uint PWidth,PHeight;
  String Title;
  Atom *AWMProtocols;
  Atom *AWMDeleteWindow;
  Atom *AWMTakeFocus;
  unsigned int XMouse, YMouse;
  CControl *ControlOnFocus;
  CControl *LastControl;
  Window WWindow;
  int *ADepth;
  Display *ADisplay;
  XEvent WEvent;
  unsigned long BorderColor;
  XTextProperty WTextProperty;
  XSizeHints WSizeHints;
  XWMHints WWMHints;
  XClassHint WClassHints;
  XSetWindowAttributes WAttributes;
  CPaint WPaint;
  bool CanDestroy;
  CWindow* WParent;
  XIC IC;
  bool CanExitExclusive;
  void CreatePixmap(bool draw=false);
  void DestroyPixmap(void);
  bool PixmapBuffer;
public:
    CWindow (void);
   ~CWindow (void);
  void Draw (void);
  void Destroy (void);
  void DestroyChild (CControl * control);
  void DestroyChilds (void);
  virtual void WCreate (CWindow* window = NULL);
  virtual void WDestroy (void);
  void Show (void);
  void ShowExclusive (void);
  void Hide (void);
  void HideExclusive (void);
  void Update (void);
  void Update (Region Reg);
  virtual bool WEvents (XEvent WEvent);
  CStringList GetContext (void);
  void SetContext (CStringList context);
  void SetFocus (void);
  XIC GetIC (void);
  void SetPixmapBuffer(bool pbuffer);
  bool GetPixmapBuffer(void);
//propiedades
  Window GetWWindow (void);
  Display *GetADisplay (void);
  int *GetADepth (void);
  void SetCanDestroy (bool candestroy);
  bool GetCanDestroy (void);
  void SetOverrideRedirect (bool redirect);
  void SetSaveUnder (bool saveunder);
  void SetX (int x);
  void SetY (int y);
  void SetWidth (uint width);
  void SetHeight (uint height);
  void SetXMouse (uint x);
  uint GetXMouse (void);
  void SetYMouse (uint y);
  uint GetYMouse (void);
  void SetTitle (const String & title);
  String GetTitle (void);
  CControl *GetControlOnFocus (void);
  void SetControlOnFocus (CControl * controlonfocus);
  CControl *GetLastControl (void);
  Pixmap GetPixmap(void);
  void SetLastControl (CControl * lastcontrol);
  void CirculateFocus (bool asc);
  //operator
  void *operator new (size_t sz);
  //eventos
  virtual void on_create (void);
  virtual void on_destroy (void);
  virtual void on_show (void);
  virtual void on_hide (void);
  virtual void on_enter (void);
  virtual void on_leave (void);

  void (CControl::*OnCreate) (CWindow * win);
  void (CControl::*OnDestroy) (CWindow * win);
  void (CControl::*OnShow) (CWindow * win);
  void (CControl::*OnHide) (CWindow * win);
  void (CControl::*OnEnter) (CWindow * win);
  void (CControl::*OnLeave) (CWindow * win);
};

void XFreeTextProperty (XTextProperty & textp);

#endif
