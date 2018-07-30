/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001  Luis Claudio Gamboa Lopes

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

#include"../include/ccontrol.h"
#include"../include/cwindow.h"
#include"../include/cmenu.h"
#include"../include/cpmenu.h"
#include"../include/capplication.h"

extern CApplication *Application;

#include<stdio.h>

// CControl______________________________________________________________


CControl::CControl (void)
{
  //Dynamic = false;
  Owner = NULL;
  Win = NULL;
  Paint = NULL;
  ChildCount = -1;
  Child = NULL;
  SetX(0);
  SetY(0);
  Border = 1;
  Width = 10;
  Height = 10;
  Visible = true;
  GChanges=true;
  Tag = 0;
  //OnFocus=false;
  CanExecuteEvent = true;
  CanExecuteEventOld = true;
  CanFocus = true;
  Enable = true;
  Pen = 0;
  FOwner = NULL;
  PointerOn = false;
  FontName = "FreeSans.ttf";
  FontSize = 12;
  SetClass ("CControl");
  PopupMenu = NULL;
  SetHint(""); 
  
  EvMouseMove = NULL;
  EvMouseButtonPress = NULL;
  EvMouseButtonRelease = NULL;
  EvMouseButtonClick = NULL;
  EvMouseButtonDoubleClick = NULL;
  EvKeyboardPress = NULL;
  EvKeyboardRelease = NULL;
  EvKeyboardKey = NULL;
  PointerIn = NULL;
  PointerOut = NULL;
  EvOnDraw = NULL;
  CFocusIn = NULL;
  CFocusOut = NULL;

  CFont = NULL;
  ColorName = "";
  ColorSet = false;
};

CControl::~CControl ()
{
//  eprint("~"+GetClass()+"\n");
  if (Child)
    {
      for (int c = 0; c <= ChildCount; c++)
	{
	  if (Child[c]->GetDynamic ())
	    delete Child[c];
	  Child[c] = NULL;
	};
      ChildCount = -1;
      delete[]Child;
      Child = NULL;
    };
};


void
CControl::Create (CControl * control)
{
  //printf("Created :(%s)\t%s - %s\n",control->GetName().c_str(),Class.c_str(),Name.c_str());	
  SetOwner (control);
  Win = control->Win;
  Paint = control->Paint;
  if (!CFont)
    CFont = TTF_OpenFont((String(_SHARE)+"fonts/"+FontName).c_str (), FontSize );
   if( CFont == NULL )
   {
       printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
       exit(-1);
   }
  /*
  if (!CFont)
    {
      eprint( FontName +" font not found!, Try to use default font.\n");
      FontName = "*6x13";
      CFont = XLoadQueryFont (Win->GetADisplay (), FontName.c_str ());
    };

  if (!CFont)
    {
      eprint( "Default font not found!\n");
      eprint( "...Application Finished\n");
      exit (-1);
    };
   */
  if (ColorSet)
    {
      if (ColorName.size () > 0)
	Color = ColorByName (ColorName);
      else
	Color = ColorByRGB (Color.r, Color.g, Color.b);
    }
  else
    Color = ColorByName ("light gray");

  
  if (ChildCount > -1)
    for (int i = 0; i <= ChildCount; i++)
      {
	Child[i]->Create (this);
      };
    
    DisableColor = ColorByName ("dark gray");


    if(!Enable)
    {
      Enable=true;
      SetEnable(false);
    };
};


void
CControl::Destroy (void)
{
//  eprint("Destroy "+GetClass()+"\n");
  DestroyChilds ();
  Eraser ();
  if (Win != NULL)
    {
      if (CFont)
	{
	//  XFreeFont (Win->GetADisplay (), CFont);
	  CFont = NULL;
	};
      if (Win->GetLastControl () == this)
	Win->SetLastControl (NULL);
    };
};

CWindow *
CControl::GetWin (void)
{
  return Win;
};

void
CControl::SetWin (CWindow * win)
{
  Win = win;
};

void
CControl::Draw (void)
{
  if ((!Visible) || (Paint == NULL)) return;
  on_draw ();
  if (ChildCount != -1)
    for (int i = 0; i <= ChildCount; i++)
      {
	Child[i]->Draw ();
      };
    Update ();
};

void
CControl::Update (void)
{
  if ((!Visible) || (Paint == NULL) || (Win->GetWWindow () == 0))
    return;

  if ((Win == Owner) && (Win != this))
    {
      if (Win->GetControlOnFocus () == this)
	{
	   Paint->InitDraw (this);
	   Paint->Pen.SetColor (ColorByName ("black"));
	   Paint->Frame (  - 1,  - 1, Width + 1, Height + 1);
	}
      else
	{
	   Paint->InitDraw (this);
	   Paint->Pen.SetColor (Win->GetColor ());
	   Paint->Frame ( - 1, - 1, Width + 1, Height + 1);
	};
    };
  
    Paint->DrawControl (this);

};

void
CControl::Eraser (void)
{
  if ((Paint == NULL) || (!Visible)) return;

  if ((this != Win)&&(Owner == Win))
    {
	Paint->InitDraw (this);
        Paint->Pen.SetColor (Owner->GetColor ());
	Paint->Rectangle (0,0, Width, Height);
        if (Win->GetControlOnFocus () == this)
	{
	  Paint->Pen.SetColor (Win->GetColor ());
	  Paint->Frame (- 1, - 1, Width + 1, Height + 1);
	};
        Paint->DrawControl (this);
    };

};


void
CControl::Event (SDL_Event event)
{
  CControl *control = 0;

  if (Win == NULL)
    return;
  
  //mouse position
  if ((event.type == SDL_MOUSEMOTION) && (Win != NULL))
  {
      if(Owner==this)
      {
      Win->SetXMouse (event.motion.x);
      Win->SetYMouse (event.motion.y);
      control=NULL;
      for (int j = 0; j <= ChildCount; j++)
      {
        if (Child[j]->OwnerEvent (Win->GetXMouse (), Win->GetYMouse ())
	  && (Child[j]->GetVisible ()))
	 control = Child[j];
       };

      if(control)
         Application->SetHintControl(control,event.motion.x,event.motion.y);
      else
         Application->SetHintControl(NULL,0,0);
      };
  };
  
   if ((event.type == SDL_MOUSEBUTTONDOWN) && (Win != NULL))
    {
      Win->SetXMouse (event.button.x);
      Win->SetYMouse (event.button.y);
    };
  //verify Owner of event  
  for (int j = 0; j <= ChildCount; j++)
    {
      if (Child[j]->OwnerEvent (Win->GetXMouse (), Win->GetYMouse ())
	  && (Child[j]->GetVisible ()))
	control = Child[j];
    };

  if (control == NULL)
    {
      control = this;
    }
  else
    {
      if (control->GetCanExecuteEvent ())
	{
	  control->Event (event);
	  return;
	}
      else
	{
	  control = control->GetOwner ();
	};
    };
  //verify control focus 
  if (control != Win->GetLastControl ())
    {
      control->pointer_in ();
      if (Win->GetLastControl () != NULL)
	Win->GetLastControl ()->pointer_out ();
    };
  Win->SetLastControl (control);
  if (control->Win != NULL)
    {
      if ((event.type == SDL_MOUSEBUTTONDOWN)
	  && (control != control->Win->GetControlOnFocus ())
	  && (event.button.button == 1))
	{
	  control->SetFocus (true);
	}
    }


  if (control == NULL)
    return;
//activate event in control
  switch (event.type)
    {
    case SDL_MOUSEMOTION:
      control->mouse_move (event);
      return;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_TAB)
	{
//look status        
	  Win->CirculateFocus (true);
	  return;
	};

      if (Win->GetControlOnFocus ())
	Win->GetControlOnFocus ()->key_press (event);
      else
	control->key_press (event);
      return;
      break;
      case SDL_KEYUP:
      if (Win->GetControlOnFocus ())
	Win->GetControlOnFocus ()->key_release (event);
      else
	control->key_release (event);
      return;
      break;
    case SDL_MOUSEBUTTONDOWN:
      control->button_press (event);
      return;
      break;
    case SDL_MOUSEBUTTONUP:
      control->button_release (event);
      return;
      break;
//  case EnterNotify:           
//  return 1;break;
//  case LeaveNotify:           
//  return 1;break;
//  case ColormapNotify:                
//  return 1;break;
//  case GraphicsExpose:                
//  return 1;break;
//  case NoExpose:              
//  return 1;break;
//  case FocusIn:                       
//  return 1;break;
//  case FocusOut:              
//  return 1;break;
//  case KeymapNotify:          
//  return 1;break;
//  case PropertyNotify:                
//  return 1;break;
//  case ResizeRequest:         
//  return 1;break;
//  case MappingNotify:         
//  return 1;break;
//  case SelectionClear:                
//  return 1;break;
//  case SelectionNotify:               
//  return 1;break;
//  case SelectionRequest:      
//  return 1;break;
//  case VisibilityNotify:      
//  return 1;break;
//  case LASTEvent:             
//  return 1;break;
//  case Expose:  
//  return 1;break;
    default:
      //printf("default !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
      return;
    };

};

void
CControl::DestroyChilds (void)
{
  for (int c = 0; c <= ChildCount; c++)
    {
      Child[c]->SetVisible (false);
      Child[c]->Destroy ();
      if (Child[c]->GetDynamic ())
	delete Child[c];
      Child[c] = NULL;
    };
  ChildCount = -1;
  delete[]Child;
  Child = NULL;
  if (Win)
    if (Win->GetLastControl () == this)
      Win->SetLastControl (NULL);
};

void
CControl::CreateChild (CControl * control)
{
  ChildCount++;
  CControl **Child1;
  Child1 = new CControl *[ChildCount + 1];
  for (int c = 0; c < ChildCount; c++)
    Child1[c] = Child[c];
  Child1[ChildCount] = control;
  if (Child)
    delete[]Child;
  Child = Child1;

  if (Win != NULL)
    control->Create (this);
};

void
CControl::DestroyChild (CControl * control)
{
  int childn = -1;
  if (Win)
    if (Win->GetLastControl () == control)
      Win->SetLastControl (NULL);
  for (int f = 0; f <= ChildCount; f++)
    if (Child[f] == control)
      {
	childn = f;
	break;
      };
  if (childn != -1)
    {
      Child[childn]->Eraser ();
      Child[childn]->Destroy ();
      if (Child[childn]->GetDynamic ())
	delete Child[childn];
      for (int c = childn; c < ChildCount; c++)
	Child[c] = Child[c + 1];

      Child[ChildCount] = NULL;
      ChildCount--;
    };
};

bool
CControl::OwnerEvent (int x, int y)
{
  CalcRXY();

  if ((x > RX) && (x < (int) (Width + RX)))
    {
      if ((y > RY) && (y < (int) (Height + RY)))
	return true;
      else
	return false;
    }
  else
    return false;
};

CStringList CControl::GetContext (void)
{
  CObject::GetContext ();

//propierties
  Context.AddLine ("X=" + itoa (GetX ()) + ";int");
  Context.AddLine ("Y=" + itoa (GetY ()) + ";int");
  Context.AddLine ("Width=" + itoa (GetWidth ()) + ";uint");
  Context.AddLine ("Height=" + itoa (GetHeight ()) + ";uint");
  Context.AddLine ("Hint=" + GetHint () + ";String");
  Context.AddLine ("Enable=" + itoa (GetEnable ()) + ";bool");
  Context.AddLine ("Visible="+ itoa (GetVisible ()) + ";bool");
//  Context.AddLine("FontSize="+itoa(GetFontSize()));
  
  if (PopupMenu)
    Context.AddLine ("PopupMenu=" + PopupMenu->GetName () + ";PopupMenu");
  else
    Context.AddLine ("PopupMenu=NULL;PopupMenu");
//events  
  Context.AddLine ("MouseMove=" + btoa (GetEv (true)) + ";event");
  Context.AddLine ("MouseButtonPress=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("MouseButtonRelease=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("MouseButtonClick=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("MouseButtonDoubleClick=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("KeyboardPress=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("KeyboardRelease=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("KeyboardKey=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("PointerIn=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("PointerOut=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("OnDraw=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("CFocusIn=" + btoa (GetEv ()) + ";event");
  Context.AddLine ("CFocusOut=" + btoa (GetEv ()) + ";event");
  return Context;
};

void
CControl::SetContext (CStringList context)
{
  CObject::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      String line = Context.GetLine (i);
      String arg;
      eqparse (line, arg);
      if (line.compare ("X") == 0)
	SetX (atoi (arg));
      if (line.compare ("Y") == 0)
	SetY (atoi (arg));
      if (line.compare ("Width") == 0)
	SetWidth (atoi (arg));
      if (line.compare ("Height") == 0)
	SetHeight (atoi (arg));
      if (line.compare ("Hint") == 0)
	SetHint (arg);
      if (line.compare ("Enable") == 0)
	SetEnable (atoi(arg));
      if (line.compare ("Visible") == 0)
	SetVisible (atoi(arg));
      if (line.compare ("PopupMenu") == 0)
        if(arg.compare("NULL") != 0) 
	     SetPopupMenu(dynamic_cast < CPMenu * >(Win->GetChildByName(arg)));
      
      if (line.compare ("MouseMove") == 0)
	SetEv (atob (arg), true);
      if (line.compare ("MouseButtonPress") == 0)
	SetEv (atob (arg));
      if (line.compare ("MouseButtonRelease") == 0)
	SetEv (atob (arg));
      if (line.compare ("MouseButtonClick") == 0)
	SetEv (atob (arg));
      if (line.compare ("MouseButtonDoubleClick") == 0)
	SetEv (atob (arg));
      if (line.compare ("KeyboardPress") == 0)
	SetEv (atob (arg));
      if (line.compare ("KeyboardRelease") == 0)
	SetEv (atob (arg));
      if (line.compare ("KeyboardKey") == 0)
	SetEv (atob (arg));
      if (line.compare ("PointerIn") == 0)
	SetEv (atob (arg));
      if (line.compare ("PointerOut") == 0)
	SetEv (atob (arg));
      if (line.compare ("OnDraw") == 0)
	SetEv (atob (arg));
      if (line.compare ("CFocusIn") == 0)
	SetEv (atob (arg));
      if (line.compare ("CFocusOut") == 0)
	SetEv (atob (arg));
    };
};

SDL_Rect
CControl::GetRectangle (void)
{
  SDL_Rect rec;
  rec.x = X;
  rec.y = Y;
  rec.w = Width;
  rec.h = Height;
  return rec;
};


//properties


void
CControl::SetFont (const String font)
{
  FontName = font;
  if (Win)
    {
//      if (CFont != NULL)
//	XFreeFont (Win->GetADisplay (), CFont);
//      CFont = XLoadQueryFont (Win->GetADisplay (), FontName.c_str ());
    };
};

void
CControl::SetFont (TTF_Font * font)
{
  CFont = font;
};

TTF_Font *
CControl::GetFont (void)
{
  return CFont;
};

String CControl::GetFontName (void)
{
  return FontName;
};

void
CControl::SetFontSize (uint size)
{
  FontSize = size;
};

uint
CControl::GetFontSize (void)
{
  return FontSize;
};

void
CControl::SetHint(String hint)
{
  Hint=hint;
};

String
CControl::GetHint(void)
{
 return Hint;
};

void 
CControl::CalcRXY(void)
{
  CWindow *o,*t; 
  o = dynamic_cast < CWindow * >(Owner);
  t = dynamic_cast < CWindow * >(this);
  
  if(o) //owner == CWindow
  {
    if(t) //this == CWindow 
    {
      RX=0;	  
      RY=0;
    }
    else //this != CWindow
    {
      CMenu  *m = dynamic_cast < CMenu * >(this);
      if((o->HasMenu)&&(!m))
        RY=Y+25;
      else
        RY=Y;
      
      RX=X;	  
    };
  }
  else //owner != CWindow
  {
    if(Owner != NULL)
    {
      RX=Owner->GetRX()+X;  
      RY=Owner->GetRY()+Y;  
    };
  };
};

void
CControl::SetX (int x)
{
  Eraser ();
  X = x;
  Update ();
};

int
CControl::GetX (void)
{
  return X;
};

void
CControl::SetY (int y)
{
  Eraser ();
  Y = y;
  Update ();
};

int
CControl::GetY (void)
{
  return Y;
};

int
CControl::GetRX (void)
{
  return RX;
};

int
CControl::GetRY (void)
{
  return RY;
};

void
CControl::SetWidth (uint w)
{
  Eraser ();
  Width = w;
  GChanges=true;
  Draw ();
};

uint
CControl::GetWidth (void)
{
  return Width;
};

void
CControl::SetHeight (uint h)
{
  Eraser ();
  Height = h;
  GChanges=true;
  Draw ();
};

uint
CControl::GetHeight (void)
{
  return Height;
};

void
CControl::SetBorder (uint b)
{
  Border = b;
};

uint
CControl::GetBorder (void)
{
  return Border;
};

void
CControl::SetColor (SDL_Color c)
{
  Color = c;
};

void
CControl::SetColor (const String name)
{
  ColorName = name;

  if(name.compare("#000001") == 0)return;

  if (Win != NULL)
    Color = ColorByName (name);
  else
    ColorSet = true;
};

void
CControl::SetColor (uint r, uint g, uint b)
{
  if (Win != NULL)
    {
      Color = ColorByRGB (r, g, b);
    }
  else
    {
      Color.r= r;
      Color.g = g;
      Color.b = b;
      ColorSet = true;
      ColorName = "";
    };
};

lxColor CControl::GetColor (void)
{
  return Color;
};


bool
CControl::GetCanExecuteEvent (void)
{
  return CanExecuteEvent;
};

void
CControl::SetCanExecuteEvent (bool cee)
{
  CanExecuteEvent = cee;
  CanExecuteEventOld = cee;
};

void
CControl::SetEnable (bool enable)
{
  SDL_Color temp;
  
  if (Enable != enable)
    {
    temp=Color;  
    Color=DisableColor;
    DisableColor=temp;
    
    Enable = enable;
    SetCanExecuteEvent (Enable);
    SetCanFocus (Enable);
   
    Draw();
    };
  
};

bool CControl::GetEnable (void)
{
  return Enable;
};

void
CControl::SetPen (int pen)
{
  Pen = pen;
  Draw ();
};

int
CControl::GetPen (void)
{
  return Pen;
};

CControl *
CControl::GetOwner (void)
{
  return Owner;
};

void
CControl::SetOwner (CControl * control)
{
  Owner = control;

};

void
CControl::SetVisible (bool visible, bool update)
{
  if (update)
    if (visible)
      {
	CanExecuteEvent = CanExecuteEventOld;
	Visible = visible;
	Update ();
      }
    else
      {
	CanExecuteEventOld = CanExecuteEvent;
	Eraser ();
	Visible = visible;
      }
  else
    Visible = visible;
};

bool
CControl::GetVisible (void)
{
  return Visible;
};

void
CControl::SetPopupMenu (CPMenu * poupmenu)
{
  PopupMenu = poupmenu;
};

void
CControl::SetFocus (bool focus)
{
  if (CanFocus)
    {
      if (focus)
	{
	  Win->SetControlOnFocus (this);
	  focus_in ();
	}
      else
	{
	  Win->SetControlOnFocus (NULL);
	  focus_out ();
	};
    };
};

bool
CControl::GetFocus (void)
{
  if (Win->GetControlOnFocus () == this)
    return true;
  else
    return false;
};

void
CControl::SetCanFocus (bool canfocus)
{
  CanFocus = canfocus;
};

bool
CControl::GetCanFocus (void)
{
  return CanFocus;
};

bool
CControl::GetDynamic (void)
{
  return Dynamic;
};

int
CControl::GetChildCount (void)
{
  return ChildCount;
};


CControl *
CControl::GetChild (uint child)
{
  return Child[child];
};

CControl *
CControl::GetChildByName (const String child)
{
  for (int a = 0; a <= ChildCount; a++)
    if (Child[a]->GetName ().compare (child) == 0)
      return Child[a];
  return NULL;
};


void
CControl::SetFOwner (CControl * control)
{
  FOwner = control;
};

CControl *
CControl::GetFOwner (void)
{
  return FOwner;
};

//operators

void *
CControl::operator new (size_t sz)
{
/*The use of calloc instead malloc preserve Dynamic=false in controls owned */
  CControl *m = (CControl *) calloc (sz, 1);
  if (!m)
    puts ("out of memory");
  m->Dynamic = true;
  return (void *) m;
};

void *
CControl::operator new[] (size_t sz)
{
  printf ("operator new[]: %ld Bytes\n", sz);
  return::new char[sz];
};
  
void 
CControl::operator delete(void *p)
{
  free(p);
}

//events

void
CControl::mouse_move (SDL_Event event)
{
	//FIXME inverted coords
  if ((FOwner) && (EvMouseMove))
    (FOwner->*EvMouseMove) (this, event.motion.y, event.motion.x);
};

void
CControl::button_press (SDL_Event event)
{
  BTimePress = event.button.timestamp;

  if ((FOwner) && (EvMouseButtonPress))
    (FOwner->*EvMouseButtonPress) (this, event.button.button, event.button.x-RX,
				 event.button.y-RY, event.button.state);

  if ((event.button.button == 3) && (PopupMenu != NULL)&&((PopupMenu->GetChildCount ()) != -1))
    {
      int x, y;
      //Window child;
      x=event.button.x;
      y=event.button.y;
      if ((!PopupMenu->GetWWindow ()) != 0)
	{
	  //Application.ACreateWindow (SubMenu,Win);
	  Application->ACreateWindow (PopupMenu);
	};

      
      PopupMenu->SetX (Win->GetX()+x);
      PopupMenu->SetY (Win->GetY()+y);
     
      PopupMenu->Show ();
      PopupMenu->Draw ();
      while (PopupMenu->GetVisible ())
	{
	  Application->ProcessEvents (PopupMenu);
	};
    
    }
};

void
CControl::button_release (SDL_Event event)
{
  BTimeRelease = event.button.timestamp;

  if ((FOwner) && (EvMouseButtonRelease))
    (FOwner->*EvMouseButtonRelease) (this, event.button.button,
				   event.button.x-RX, event.button.y-RY,
				   event.button.state);


  if ((BTimeRelease - BTimeClick) < DOUBLECLICKTIME)
    {
      if ((FOwner) && (EvMouseButtonDoubleClick))
	{
	  (FOwner->*EvMouseButtonDoubleClick) (this, event.button.button,
					     event.button.x, event.button.y,
					     event.button.state);
	};
    }
  else
    {
      if ((FOwner) && (EvMouseButtonClick))
	{
	  (FOwner->*EvMouseButtonClick) (this, event.button.button,
				       event.button.x, event.button.y,
				       event.button.state);
	}
      BTimeClick = BTimePress;
    };

  if ((event.button.button == 3) && (PopupMenu != NULL))
    {
      PopupMenu->SetVisible (false);
      Win->Draw ();
    };
};

void
CControl::key_press (SDL_Event event)
{
  if ((FOwner) && (EvKeyboardPress))
    (FOwner->*EvKeyboardPress) (this, event.key.keysym.sym, 0,
			      0, event.key.state);
};

void
CControl::key_release (SDL_Event event)
{
  if ((FOwner) && (EvKeyboardRelease))
    (FOwner->*EvKeyboardRelease) (this, event.key.keysym.sym, 0,
				0, event.key.state);
};


void
CControl::focus_in (void)
{
  Update ();
  if ((FOwner) && (CFocusIn))
    (FOwner->*CFocusIn) (this);
};

void
CControl::focus_out (void)
{
  Update ();
  if ((FOwner) && (CFocusOut))
    (FOwner->*CFocusOut) (this);
};

void
CControl::pointer_in (void)
{
  PointerOn = true;
  if ((FOwner) && (PointerIn))
    (FOwner->*PointerIn) (this);
};

void
CControl::pointer_out (void)
{
  PointerOn = false;
  if ((FOwner) && (PointerOut))
    (FOwner->*PointerOut) (this);
};

void
CControl::on_draw (void)
{
  if ((FOwner) && (EvOnDraw))
    (FOwner->*EvOnDraw) (this);
};

