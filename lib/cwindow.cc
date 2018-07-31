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

#include<stdio.h>

#include"../config.h"
#include"../include/cwindow.h"
#include"../include/capplication.h"

#ifdef LIBPTHREAD
#include<pthread.h>
//extern pthread_mutex_t Display_Lock;
#endif

//CWindow _______________________________________________________________

CWindow::CWindow (void)
{
  WWindow = NULL;
  Renderer=NULL;
  SetClass ("CWindow");
  Win = NULL;
  PixmapBuffer=true;
  HasMenu=false;
  //  PixmapBuffer=false;
  XMouse = 0;
  YMouse = 0;
  SetX (0);
  SetY (0);
  SetWidth (300);
  SetHeight (200);
  PWidth=0;
  PHeight=0;
  SetBorder (1);
  Visible = 1;
  Title = "LXRAD Window";
  WParent=NULL;
  WPixmap = NULL;
  ControlOnFocus = NULL;
  LastControl = NULL;
  ORedirect=false;
//events
  EvOnCreate = NULL;
  EvOnDestroy = NULL;
  EvOnShow = NULL;
  EvOnHide = NULL;
  EvOnEnter = NULL;
  EvOnLeave = NULL;
};

CWindow::~CWindow (void)
{

};

void
CWindow::WCreate (CWindow* window)
{
 
  //SDL_Window *parent; 
  if(window != NULL)
  {
    //parent=window->GetWWindow();
    WParent=window;
  }
  //else
    //parent=NULL;
  
  if(ORedirect)
     WWindow= SDL_CreateWindow(Title.c_str(), X, Y, Width, Height, SDL_WINDOW_HIDDEN |SDL_WINDOW_BORDERLESS); 
  else
     WWindow= SDL_CreateWindow(Title.c_str(), X, Y, Width, Height, SDL_WINDOW_HIDDEN |SDL_WINDOW_RESIZABLE); 
      
if( WWindow == NULL ) 
{ 
    printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() ); 
    exit(-1);
}

//Renderer = SDL_CreateRenderer( WWindow, -1, SDL_RENDERER_ACCELERATED ); 
if( Renderer == NULL ) 
{
//    printf( "Hardware renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    printf( "Switching to software renderer...\n");
    Renderer = SDL_CreateRenderer( WWindow, -1, SDL_RENDERER_SOFTWARE ); 
} 
if( Renderer == NULL ) 
{
    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    exit(-1);
} 
//Initialize renderer color 
SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 


  //uint FEvent = 0;
  
  Win = this;
  WPaint.Create (this);
  Paint = &WPaint;
  
  Create (this);
  Draw();
  
  if(Visible) Show ();
  
  SDL_SetWindowPosition(WWindow,X,Y);

  on_create ();
};

void
CWindow::Destroy (void)
{
  CControl::Destroy ();
  DestroyPixmap();
  if(Renderer)
    SDL_DestroyRenderer( Renderer );
  if(WWindow )
    SDL_DestroyWindow( WWindow );
  WWindow = NULL;
  Renderer = NULL;
};


void
CWindow::Draw(void)
{
  if(Paint == NULL)return;
  SDL_RenderClear( Renderer );
  Paint->InitDraw(this);
  Paint->Pen.SetColor(Color);
  Paint->Rectangle ( 0, 0, Width, Height);
  CControl::Draw ();
  
  SDL_RenderPresent( Renderer );
};

void
CWindow::SetPixmapBuffer(bool pbuffer)
{
  PixmapBuffer=pbuffer;
};

bool
CWindow::GetPixmapBuffer(void)
{
  return PixmapBuffer;
};

SDL_Texture* 
CWindow::GetPixmap(void)
{
  return WPixmap;
};

void
CWindow::DestroyPixmap (void)
{
    /*
  if ((WPixmap != 0)&&(WPixmap != WWindow))
    {
      XFreePixmap (ADisplay , WPixmap);
      WPixmap=0;
    };
    */
};

void
CWindow::CreatePixmap(bool draw)
{
    /*
  if(PixmapBuffer)
  {
  if((Width > PWidth) || ( Height > PHeight))
  {
  DestroyPixmap();	
  WPixmap=XCreatePixmap(ADisplay , WWindow ,Width , Height ,*ADepth);
  WPaint.SetDrawIn(WPixmap);
  if(Width > PWidth)PWidth=Width;
  if(Height > PHeight)PHeight=Height;
  if(draw) Draw();
  };
  }
  else
   WPixmap=WWindow;
     */
};



void
CWindow::DestroyChild (CControl * control)
{
  if (control == ControlOnFocus)
    ControlOnFocus = NULL;
  CControl::DestroyChild (control);
};

void
CWindow::DestroyChilds (void)
{
  ControlOnFocus = NULL;
  CControl::DestroyChilds ();
};


void
CWindow::WDestroy (void)
{
  Hide ();
  on_destroy ();
  if ((CanDestroy) || (this == Application->GetAWindow ((uint) 0)))
    {
      Destroy ();
      WPaint.Destroy ();
      if(WParent != NULL)
      {
//        XDestroyWindow (ADisplay, GetWWindow ());
      };
      Win = NULL;
      Application->ADestroyWindow (this);
      WWindow = 0;
    };
};

void
CWindow::Show (void)
{
  if(Win != NULL)
    {
      SetVisible (true);
      Draw();
      SDL_ShowWindow(WWindow);
      SDL_RaiseWindow(WWindow); 
      Update ();
    };
};

void
CWindow::ShowExclusive (void)
{
  Show ();
  CanExitExclusive = true;
  while (CanExitExclusive)
    Application->ProcessEvents (this);
};

void
CWindow::Hide (void)
{
  if (Win != NULL)
    {
      SDL_HideWindow(WWindow);
      SetVisible (false);
    };
};

void
CWindow::HideExclusive (void)
{
  CanExitExclusive = false;
  Hide ();
};

void
CWindow::Update (void)
{
  for (int i = 0; i <= ChildCount; i++)
    {
      if (Child[i]->GetVisible ())
	{
	  if(PixmapBuffer)	
	    Child[i]->Update ();
	  else
	    Child[i]->Draw ();
	};
    };
  CControl::Update();
};

void
CWindow::Update (SDL_Rect Reg)
{
  if (ChildCount == -1)
    return;
  else
    Update();   
  /*
  else
    {
      
      XSetRegion (GetADisplay (), WPaint.Agc, Reg);
      
      for (int i = 0; i <= ChildCount; i++)
	{
	  if (Child[i]->GetVisible ())
	    {
	      XRectangle rec=Child[i]->GetRectangle();	    
	      if (XRectInRegion (Reg,rec.x,rec.y,rec.width,rec.height) != RectangleOut)
		{
		  if(PixmapBuffer)	
		    Child[i]->Update ();
		  else
		    Child[i]->Draw ();
		};
	    };
	};

      XSetClipMask (GetADisplay (), WPaint.Agc, None);
      XDestroyRegion (Reg);
    };
   */ 
};

void
CWindow::SetOverrideRedirect (bool oredirect)
{
    ORedirect=oredirect;
    if(WWindow)
    {
        if(ORedirect)
           SDL_SetWindowBordered(WWindow, SDL_TRUE);
        else
           SDL_SetWindowBordered(WWindow, SDL_FALSE);
    }  
};

void
CWindow::SetSaveUnder (bool saveunder)
{

};

/*
bool predicate (Display *display,XEvent *event,XPointer arg)
{
  if((event->type == Expose)&&(event->xexpose.window == *((uint*)arg)))
    return 1;
  else
    return 0;
};
*/

bool
CWindow::WEvents (SDL_Event WEvent)
{
  int ret=0;

  switch (WEvent.type)
    {
    case SDL_WINDOWEVENT:
        switch (WEvent.window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            //SDL_Log("Window %d shown", WEvent.window.windowID);
            on_show ();
            Draw();
            ret=1;
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            //SDL_Log("Window %d hidden", WEvent.window.windowID);
            on_hide ();
            ret=1;
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            //SDL_Log("Window %d exposed", WEvent.window.windowID);
            Draw();
            ret=1;
            break;
        case SDL_WINDOWEVENT_MOVED:
            //SDL_Log("Window %d moved to %d,%d", WEvent.window.windowID, WEvent.window.data1, WEvent.window.data2);
            X=WEvent.window.data1;
            Y=WEvent.window.data2; 
            ret= 1;
            break;
        case SDL_WINDOWEVENT_RESIZED:
            //SDL_Log("Window %d resized to %dx%d", WEvent.window.windowID, WEvent.window.data1,WEvent.window.data2);    
            Width=WEvent.window.data1;
            Height=WEvent.window.data2; 
            Draw();
            ret= 1;
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            //SDL_Log("Window %d size changed to %dx%d", WEvent.window.windowID, WEvent.window.data1,WEvent.window.data2);
            Width=WEvent.window.data1;
            Height=WEvent.window.data2; 
            Draw();
            ret= 1;
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            //SDL_Log("Window %d minimized", WEvent.window.windowID);
            ret= 1;
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            //SDL_Log("Window %d maximized", WEvent.window.windowID);
            Draw();
            ret= 1;
            break;
        case SDL_WINDOWEVENT_RESTORED:
            //SDL_Log("Window %d restored", WEvent.window.windowID);
            Draw();
            ret= 1;
            break;
        case SDL_WINDOWEVENT_ENTER:
            //SDL_Log("Mouse entered window %d", WEvent.window.windowID);
            on_enter ();
            ret= 1;
            break;
        case SDL_WINDOWEVENT_LEAVE:
            //SDL_Log("Mouse left window %d", WEvent.window.windowID);
            on_leave ();
            ret=1;
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            //SDL_Log("Window %d gained keyboard focus", WEvent.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            //SDL_Log("Window %d lost keyboard focus", WEvent.window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            //SDL_Log("Window %d closed", WEvent.window.windowID);
            on_destroy ();
            WDestroy ();
            ret=1;
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            //SDL_Log("Window %d is offered a focus", WEvent.window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            //SDL_Log("Window %d has a special hit test", WEvent.window.windowID);
            break;
#endif
        default:
            //SDL_Log("Window %d got unknown event %d", WEvent.window.windowID, WEvent.window.event);
            break;
        }

      break;    
      default:
       CControl::Event (WEvent);
       ret= 1;
       break;
    /*  
    case Expose:
      XRectangle rec;
      Region Reg=XCreateRegion();
      
      rec.x =WEvent.xexpose.x;
      rec.y =WEvent.xexpose.y;
      rec.width =WEvent.xexpose.width;
      rec.height =WEvent.xexpose.height;
      XUnionRectWithRegion(&rec,Reg,Reg);

      while(XCheckIfEvent(ADisplay, &WEvent, predicate,(char*)&WWindow))
      {
      rec.x =WEvent.xexpose.x;
      rec.y =WEvent.xexpose.y;
      rec.width =WEvent.xexpose.width;
      rec.height =WEvent.xexpose.height;
      XUnionRectWithRegion(&rec,Reg,Reg);
      };
      Update (Reg);
      ret= 1;
      break;
     */ 
    };

/*
  if ((LEvent.type != WEvent.type)&&(LEvent.type == ConfigureNotify))
  {
      Display *disp=Application->GetADisplay();

      if(disp)
      {
        int se=0;
	if(Width != (uint)LEvent.xconfigure.width)se=1;
        if(Height != (uint)LEvent.xconfigure.height)se=1;
	//pthread_mutex_lock (&Display_Lock);
        XLockDisplay(disp);
        X = LEvent.xconfigure.x;
        Y = LEvent.xconfigure.y;
        Width=LEvent.xconfigure.width;
        Height=LEvent.xconfigure.height;
        Border = LEvent.xconfigure.border_width;
	if(se)
	{
          CreatePixmap(true);
          on_show ();
	  Draw();
	}
        XUnlockDisplay(disp);
        //pthread_mutex_unlock (&Display_Lock);
      }
  }
*/

  LEvent=WEvent;

  return ret;
};


CStringList CWindow::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine ("Title=" + GetTitle () + ";String");
  //events 
  Context.AddLine ("OnCreate=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnDestroy=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnShow=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnHide=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnEnter=" + btoa (GetEv (false)) + ";event");
  Context.AddLine ("OnLeave=" + btoa (GetEv (false)) + ";event");
  return Context;
};

void
CWindow::SetContext (CStringList context)
{
  Eraser ();
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      String line = Context.GetLine (i);
      String arg;
      eqparse (line, arg);
      if (line.compare ("Title") == 0)
	SetTitle (arg);
      if (line.compare ("OnCreate") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnDestroy") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnShow") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnHide") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnEnter") == 0)
	SetEv (atob (arg), false);
      if (line.compare ("OnLeave") == 0)
	SetEv (atob (arg), false);
    };
  Draw ();
};

void
CWindow::CirculateFocus (bool asc)
{
  if (asc)
    {
      for (int c = 0; c < ChildCount; c++)
	{
	  if (Child[c] == ControlOnFocus)
	    {
	      if (Child[c + 1]->GetCanFocus ())
		{
		  Child[c + 1]->SetFocus (true);
		  return;
		}
	      else
		{
		  SetControlOnFocus (NULL);
		  ControlOnFocus = Child[c + 1];
		  CirculateFocus (asc);
		  return;
		};
	    };
	};
      if (Child[0]->GetCanFocus ())
	{
	  Child[0]->SetFocus (true);
	  return;
	}
      else
	{
	  SetControlOnFocus (NULL);
	  ControlOnFocus = Child[0];
	  CirculateFocus (asc);
	  return;
	};
    }
  else
    {
      for (int c = ChildCount - 1; c >= 0; c++)
	if (Child[c] == ControlOnFocus)
	  {
	    if (Child[c - 1]->GetCanExecuteEvent ())
	      {
		Child[c - 1]->SetFocus (true);
		return;
	      }
	    else
	      ControlOnFocus = Child[c - 1];
	  };
    };
};

void
CWindow::SetFocus (void)
{
    SDL_RaiseWindow(WWindow); 
};



//propiedades
SDL_Window* 
CWindow::GetWWindow (void)
{
  return WWindow;
};




void
CWindow::SetCanDestroy (bool candestroy)
{
  CanDestroy = candestroy;
};

bool
CWindow::GetCanDestroy (void)
{
  return CanDestroy;
};

void
CWindow::SetXMouse (uint x)
{
  XMouse = x;
};

uint
CWindow::GetXMouse (void)
{
  return XMouse;
};

void
CWindow::SetYMouse (uint y)
{
  YMouse = y;
};

uint
CWindow::GetYMouse (void)
{
  return YMouse;
};

void
CWindow::SetTitle (const String & title)
{   
  Title = title;

  if (WWindow)
    {
      SDL_SetWindowTitle(WWindow, Title.c_str ());
    };

};

String CWindow::GetTitle (void)
{
  return Title;
};

CControl *
CWindow::GetControlOnFocus (void)
{
  if (ControlOnFocus)
    return ControlOnFocus;
  else
    return NULL;
};


void
CWindow::SetControlOnFocus (CControl * controlonfocus)
{
  if ((ControlOnFocus != NULL) && (ControlOnFocus->GetCanFocus ()))
    {
      CControl *last = ControlOnFocus;
      ControlOnFocus = NULL;
      last->focus_out ();
    };
  ControlOnFocus = controlonfocus;
};

CControl *
CWindow::GetLastControl (void)
{
  if (LastControl)
    return LastControl;
  else
    return NULL;
};

void
CWindow::SetLastControl (CControl * lastcontrol)
{
  LastControl = lastcontrol;
};

void
CWindow::SetX (int x)
{
  CControl::SetX (x);
  if (WWindow)
    SDL_SetWindowPosition(WWindow,X,Y);
};

void
CWindow::SetY (int y)
{
  CControl::SetY (y);
  if (WWindow)
    SDL_SetWindowPosition(WWindow,X,Y);
};

void
CWindow::SetWidth (uint width)
{
  CControl::SetWidth (width);
  if (WWindow)
    SDL_SetWindowSize( WWindow, Width, Height);
};

void
CWindow::SetHeight (uint height)
{
  CControl::SetHeight (height);
  if (WWindow)
    SDL_SetWindowSize( WWindow, Width, Height);
};

//operators

void *
  CWindow::operator
new (size_t sz)
{
  CWindow *m = (CWindow *) calloc (sz, 1);
  if (!m)
    puts ("out of memory");
  m->Dynamic = true;
  m->CanDestroy = true;
  return (void *) m;
};

//eventos

void
CWindow::on_create (void)
{
  if ((FOwner) && (EvOnCreate))
    (FOwner->*EvOnCreate) (this);
};

void
CWindow::on_destroy (void)
{
  if ((FOwner) && (EvOnDestroy))
    (FOwner->*EvOnDestroy) (this);
};

void
CWindow::on_show (void)
{
  if ((FOwner) && (EvOnShow))
    (FOwner->*EvOnShow) (this);
};

void
CWindow::on_hide (void)
{
  if ((FOwner) && (EvOnHide))
    (FOwner->*EvOnHide) (this);
};

void
CWindow::on_enter (void)
{
  if ((FOwner) && (EvOnEnter))
    (FOwner->*EvOnEnter) (this);
};

void
CWindow::on_leave (void)
{
  if ((FOwner) && (EvOnLeave))
    (FOwner->*EvOnLeave) (this);
};


bool 
CWindow::LoadXMLContextAndCreateChilds(String fname)
{
//FIXME
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
return 0;
}

bool 
CWindow::GetCanExitExclusive(void)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  return 0;
}
  
CWindow* 
CWindow::GetWWidget (void)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  return this; 
}

SDL_Renderer * 
CWindow::GetRenderer (void)
{
    return Renderer;
}
