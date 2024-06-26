/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2021  Luis Claudio Gamboa Lopes

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
#include"../include/newcontrolbycname.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#ifdef _ONEWIN
extern "C"
{

 void
 lxrad_scale_update(void)
 {
#ifdef __EMSCRIPTEN__
  double width, height;
  emscripten_get_element_css_size ("#canvas", &width, &height);
  emscripten_set_canvas_element_size ("#canvas", int(width), int(height));
  /*
  SDL_RenderSetLogicalSize (Application->GetARootWindow ()->GetRenderer (),
                            (int) (width * gscale), (int) (height * gscale));
   */
#else
  /*
  SDL_RenderSetLogicalSize (Application->GetARootWindow ()->GetRenderer (),
                            Application->GetARootWindow ()->GetWidth () * gscale, Application->GetARootWindow ()->GetHeight () * gscale);

   */
#endif
  Application->GetARootWindow ()->Show ();
 }

 void
 lxrad_scale_up(void)
 {
  double gscale = Application->GetGlobalScale ();

  gscale += 0.1;


  if (gscale > 4.0)
   {
    gscale = 4.0;
   }
  else
   {
    Application->SetGlobalScale (gscale);
    lxrad_scale_update ();
   }

 
 }

 void
 lxrad_scale_down(void)
 {
  double gscale = Application->GetGlobalScale ();

  gscale -= 0.1;

  if (gscale < 0.2)
   {
    gscale = 0.2;
   }
  else
   {
    Application->SetGlobalScale (gscale);
    lxrad_scale_update ();
   }

 }
}

#endif

//CWindow _______________________________________________________________

CWindow::CWindow(void)
{
 WWindow = NULL;
 Renderer = NULL;
 SetClass ("CWindow");
 Win = NULL;
 //PixmapBuffer = true;
 PixmapBuffer = false;
 HasMenu = false;
 XMouse = 0;
 YMouse = 0;
 SetX (0);
 SetY (0);
 SetWidth (300);
 SetHeight (200);
 PWidth = 0;
 PHeight = 0;
 SetBorder (1);
 Visible = 1;
 Title = "LXRAD Window";
 WParent = NULL;
 WPixmap = NULL;
 ControlOnFocus = NULL;
 LastControl = NULL;
 ORedirect = false;
 OverWin = false;
 move_on = 0;
 onewin_cursor = 0;
 Redraw = 1;
 statusbar = NULL;
 //events
 EvOnCreate = NULL;
 EvOnDestroy = NULL;
 EvOnShow = NULL;
 EvOnHide = NULL;
 EvOnEnter = NULL;
 EvOnLeave = NULL;
}

CWindow::~CWindow(void) { }

void
CWindow::WCreate(CWindow* window)
{

 if (window != NULL)
  {
   WParent = window;
  }
 else if (OverWin)
  {
   WParent = Application->GetARootWindow ();
  }
 else
  {
   WParent = NULL;
  }

 Win = this;

 if (!OverWin)
  {
   if (ORedirect)
    WWindow = SDL_CreateWindow (Title.c_str (), X, Y, Width, Height, SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS);
   else
    WWindow = SDL_CreateWindow (Title.c_str (), X, Y, Width, Height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

   if (WWindow == NULL)
    {
     printf ("Window could not be created! SDL Error: %s\n", SDL_GetError ());
     exit (-1);
    }
 
    Renderer = SDL_CreateRenderer (WWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);

   if (Renderer == NULL)
    {
     //    printf( "Hardware renderer could not be created! SDL Error: %s\n", SDL_GetError() );
     printf ("Switching to software renderer...\n");
     Renderer = SDL_CreateRenderer (WWindow, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
    }
   if (Renderer == NULL)
    {
     printf ("Renderer could not be created! SDL Error: %s\n", SDL_GetError ());
     exit (-1);
    }
#ifdef _ONEWIN   
   //ZOOM
   lxrad_scale_update ();
#endif

   //Initialize renderer color 
   SDL_SetRenderDrawColor (Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  }
 else
  {
   WWindow = WParent->GetWWindow ();
   Renderer = WParent->GetRenderer ();
  }

 WPaint.Create (this);
 Paint = &WPaint;

 Create (this);


 on_create ();

 if (Visible) Show ();

 Draw ();

 if (!OverWin)
  SDL_SetWindowPosition (WWindow, X, Y);

}

void
CWindow::Destroy(void)
{
 CControl::Destroy ();
 DestroyPixmap ();

 if ((Renderer)&&(!OverWin))
  SDL_DestroyRenderer (Renderer);
 if ((WWindow)&&(!OverWin))
  SDL_DestroyWindow (WWindow);
 WWindow = NULL;
 Renderer = NULL;
}

void
CWindow::Draw(void)
{
 if ((Paint == NULL) || (Visible == false))return;

 //SDL_SetRenderTarget (Win->GetRenderer (), NULL);

 if (OverWin)
  {
   Paint->InitDraw (this);
   Paint->Pen.SetColor (Color);
#ifdef _ONEWIN   
   if (!ORedirect)
    {
     //background
     Paint->Rectangle (0, 0, Width, Height + 20);
     Paint->RaiserFrame (0, 0, Width, Height + 20, 1);
     //bar
     Paint->Pen.SetColor (ColorByRGB (50, 50, 80));
     Paint->Rectangle (0, 0, Width, 20);
     Paint->RaiserFrame (0, 0, Width, 20, 1);
     //close button
     Paint->Pen.SetColor (ColorByRGB (80, 30, 30));
     Paint->Rectangle (Width - 16, 4, 12, 12);
     Paint->Pen.SetColor (ColorByRGB (120, 120, 120));
     Paint->Rectangle (0, Width - 16, 4, 12, 12);
     //resize button
     Paint->Pen.SetColor (ColorByRGB (170, 170, 170));
     Paint->Rectangle (1, Width - 10, Height + 10, 8, 8);
     //bar text
     int tw;
     TTF_SizeText (CFont.GetTTFFont (), Title.c_str (), &tw, NULL);
     Paint->Pen.SetColor (ColorByRGB (255, 255, 255));
     Paint->Text (Title, (Width - tw) / 2, 2);
    }
   else
    {
     Paint->Rectangle (0, 0, Width, Height);
     Paint->RaiserFrame (0, 0, Width, Height, 1);
    }
   Application->GetARootWindow ()->SetRedraw ();
#else
   Paint->Rectangle (0, 0, Width, Height);
   Paint->RaiserFrame (0, 0, Width, Height, 1);
#endif   
  }
 else
  {
   if (Redraw == 0)return;
   Paint->Pen.SetColor (Color);
   SDL_RenderClear (Renderer);
   Paint->InitDraw (this);
   //Paint->Rectangle (0, 0, Width, Height);
  }
 Paint->End ();
 //CControl::Draw ();

 Update ();
 Redraw = 0;
}

void
CWindow::SetPixmapBuffer(bool pbuffer)
{
 PixmapBuffer = pbuffer;
}

bool
CWindow::GetPixmapBuffer(void)
{
 return PixmapBuffer;
}

SDL_Texture*
CWindow::GetPixmap(void)
{
 return WPixmap;
}

void
CWindow::DestroyPixmap(void) {
 /*
 if ((WPixmap != 0)&&(WPixmap != WWindow))
 {
   XFreePixmap (ADisplay , WPixmap);
   WPixmap=0;
 }
  */ }

void
CWindow::CreatePixmap(bool draw) {
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
 }
 }
 else
WPixmap=WWindow;
  */ }

void
CWindow::DestroyChild(CControl * control)
{
 if (control == ControlOnFocus)
  ControlOnFocus = NULL;
 CControl::DestroyChild (control);
}

void
CWindow::DestroyChilds(void)
{
 ControlOnFocus = NULL;
 CControl::DestroyChilds ();
}

void
CWindow::WDestroy(void)
{
 if (CanExitExclusive)
  {
   CanExitExclusive = false;
   Application->SetModalWindow (NULL);
  }

 //if (OverWin)
 //  SetVisible (false);
 // else
 Hide ();

 on_destroy ();
 if (((!OverWin)&&(CanDestroy)) || (this == Application->GetAWindow (0)))
  {
   Destroy ();
   WPaint.Destroy ();
   if (WParent != NULL)
    {
     //        XDestroyWindow (ADisplay, GetWWindow ());
    }
   Win = NULL;
   Application->ADestroyWindow (this);
   WWindow = 0;
  }
}

void
CWindow::Show(void)
{
 SetVisible (true, false);
 if (Win != NULL)
  {
   if (!OverWin)
    {
     SDL_ShowWindow (WWindow);
     SDL_RaiseWindow (WWindow);
     //SDL_RenderPresent (Renderer);
#ifdef _ONEWIN    
     if (Application->GetARootWindow () == this)
      {
       for (int i = ChildCount; i >= 0; i--)
        {
         if (Child[i]->GetVisible () && (Child[i] != statusbar))
          {
           //simulate window resize
           Child[i]->SetWidth (Child[i]->GetWidth () + 1);
           Child[i]->SetHeight (Child[i]->GetHeight () + 1);

           ((CWindow *) Child[i])->Show ();
          }
        }
      }
#endif     
    }
   else
    {
     on_show ();
    }
   //Draw ();
   Update ();
  }
}

void
CWindow::ShowExclusive(void)
{
 Show ();
 CanExitExclusive = true;
 Application->SetModalWindow (this);
}

void
CWindow::Hide(void)
{
 if (!Visible) return;

 SetVisible (false);
 if (Win != NULL)
  {
   if (OverWin)
    {
     if (WParent)
      WParent->Draw ();
    }
   else
    {
     SDL_HideWindow (WWindow);
    }
  }
 on_hide ();
}

void
CWindow::HideExclusive(void)
{
 CanExitExclusive = false;
 Application->SetModalWindow (NULL);
 Hide ();
}

void
CWindow::Update(void)
{
 if ((Paint == NULL) || (Visible == false))return;
#ifdef _ONEWIN  
 if (Application->GetARootWindow () == this)
  {
   for (int i = ChildCount; i >= 0; i--)
    {
     if (Child[i]->GetVisible () && (Child[i] != statusbar))
      {
       if (PixmapBuffer)
        Child[i]->Update ();
       else
        Child[i]->Draw ();
      }
    }
  }
 else
  {
   for (int i = 0; i <= ChildCount; i++)
    {
     if (Child[i]->GetVisible () && (Child[i] != statusbar))
      {
       if (PixmapBuffer)
        Child[i]->Update ();
       else
        Child[i]->Draw ();
      }
    }
  }
#else 
 for (int i = 0; i <= ChildCount; i++)
  {
   if (Child[i]->GetVisible () && (Child[i] != statusbar))
    {
     if (PixmapBuffer)
      Child[i]->Update ();
     else
      Child[i]->Draw ();
    }
  }
#endif

 if (statusbar)
  {
   if (PixmapBuffer)
    statusbar->Update ();
   else
    statusbar->Draw ();
  }


 CControl::Update ();

 if (!OverWin)
  {
#ifdef _ONEWIN   
   CWindow * mw = Application->GetModalWindow ();
   if (mw)
    {
     mw->Draw ();
    }
#endif  
   SDL_RenderPresent (Renderer);
  }
}

void
CWindow::Update(SDL_Rect Reg)
{
 if (ChildCount == -1)
  return;
 else
  Update ();
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
       }
       }
   }

     XSetClipMask (GetADisplay (), WPaint.Agc, None);
     XDestroyRegion (Reg);
   }
  */
}

void
CWindow::SetOverrideRedirect(bool oredirect)
{
 ORedirect = oredirect;
 if (WWindow)
  {
   if (ORedirect)
    SDL_SetWindowBordered (WWindow, SDL_FALSE);
   else
    SDL_SetWindowBordered (WWindow, SDL_TRUE);
  }
}

bool
CWindow::GetOverrideRedirect(void)
{
 return ORedirect;
}

void
CWindow::SetSaveUnder(bool saveunder) { }

/*
bool predicate (Display *display,XEvent *event,XPointer arg)
{
  if((event->type == Expose)&&(event->xexpose.window == *((uint*)arg)))
    return 1;
  else
    return 0;
}
 */

bool
CWindow::WEvents(SDL_Event WEvent)
{
 int ret = 0;
#ifdef __EMSCRIPTEN__
 double width, height;
#endif
 switch (WEvent.type)
  {
  case SDL_WINDOWEVENT:
   switch (WEvent.window.event)
    {
    case SDL_WINDOWEVENT_SHOWN:
#ifdef _DEBUG
     SDL_Log ("Window %d shown", WEvent.window.windowID);
#endif
     on_show ();
     SetRedraw ();
     Draw ();
     ret = 1;
     break;
    case SDL_WINDOWEVENT_HIDDEN:
#ifdef _DEBUG
     SDL_Log ("Window %d hidden", WEvent.window.windowID);
#endif
     ret = 1;
     break;
    case SDL_WINDOWEVENT_EXPOSED:
#ifdef _DEBUG
     SDL_Log ("Window %d exposed", WEvent.window.windowID);
#endif
     SetRedraw ();
     Draw ();
     ret = 1;
     break;
    case SDL_WINDOWEVENT_MOVED:
#ifdef _DEBUG
     SDL_Log ("Window %d moved to %d,%d", WEvent.window.windowID, WEvent.window.data1, WEvent.window.data2);
#endif
#ifndef _ONEWIN
     X = WEvent.window.data1;
     Y = WEvent.window.data2;
#endif     
     ret = 1;
     break;
    case SDL_WINDOWEVENT_RESIZED:
#ifdef _DEBUG
     SDL_Log ("Window %d resized to %dx%d", WEvent.window.windowID, WEvent.window.data1, WEvent.window.data2);
#endif     
#ifndef _ONEWIN
     Width = WEvent.window.data1;
     Height = WEvent.window.data2;
     Draw ();
#else 
#ifdef __EMSCRIPTEN__
     emscripten_get_element_css_size ("#canvas", &width, &height);
     emscripten_set_canvas_element_size ("#canvas", int(width), int(height));
     /*
     SDL_RenderSetLogicalSize (Application->GetARootWindow ()->GetRenderer (),
                               (int) (width * gscale), (int) (height * gscale));
      */
#else
     /*
     SDL_RenderSetLogicalSize (Renderer, WEvent.window.data1*gscale, WEvent.window.data2 * gscale);
      */
#endif
#endif     
     on_show ();
     SetRedraw ();
     Draw ();
     ret = 1;
     break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
#ifdef _DEBUG
     SDL_Log ("Window %d size changed to %dx%d", WEvent.window.windowID, WEvent.window.data1, WEvent.window.data2);
#endif     
#ifndef _ONEWIN
     Width = WEvent.window.data1;
     Height = WEvent.window.data2;
     Draw ();
#else
#ifdef __EMSCRIPTEN__
     emscripten_get_element_css_size ("#canvas", &width, &height);
     emscripten_set_canvas_element_size ("#canvas", int(width), int(height));
     /*
     SDL_RenderSetLogicalSize (Application->GetARootWindow ()->GetRenderer (),
                               (int) (width * gscale), (int) (height * gscale));
      */
#else
     //SDL_RenderSetLogicalSize (Renderer, WEvent.window.data1*gscale, WEvent.window.data2 * gscale);
#endif
#endif    
     ret = 1;
     break;
    case SDL_WINDOWEVENT_MINIMIZED:
#ifdef _DEBUG
     SDL_Log ("Window %d minimized", WEvent.window.windowID);
#endif     
     ret = 1;
     break;
    case SDL_WINDOWEVENT_MAXIMIZED:
#ifdef _DEBUG
     SDL_Log ("Window %d maximized", WEvent.window.windowID);
#endif     
     SetRedraw ();
     Draw ();
     ret = 1;
     break;
    case SDL_WINDOWEVENT_RESTORED:
#ifdef _DEBUG
     SDL_Log ("Window %d restored", WEvent.window.windowID);
#endif    
     SetRedraw ();
     Draw ();
     ret = 1;
     break;
    case SDL_WINDOWEVENT_ENTER:
#ifdef _DEBUG
     SDL_Log ("Mouse entered window %d", WEvent.window.windowID);
#endif    
     on_enter ();
     ret = 1;
     break;
    case SDL_WINDOWEVENT_LEAVE:
#ifdef _DEBUG
     SDL_Log ("Mouse left window %d", WEvent.window.windowID);
#endif    
     on_leave ();
     ret = 1;
     break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
#ifdef _DEBUG
     SDL_Log ("Window %d gained keyboard focus", WEvent.window.windowID);
#endif    
     break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
#ifdef _DEBUG
     SDL_Log ("Window %d lost keyboard focus", WEvent.window.windowID);
#endif    
     break;
    case SDL_WINDOWEVENT_CLOSE:
#ifdef _DEBUG
     SDL_Log ("Window %d closed", WEvent.window.windowID);
#endif    
     WDestroy ();
     ret = 1;
     break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
    case SDL_WINDOWEVENT_TAKE_FOCUS:
#ifdef _DEBUG
     SDL_Log ("Window %d is offered a focus", WEvent.window.windowID);
#endif    
     break;
    case SDL_WINDOWEVENT_HIT_TEST:
#ifdef _DEBUG
     SDL_Log ("Window %d has a special hit test", WEvent.window.windowID);
#endif    
     break;
#endif
    default:
#ifdef _DEBUG
     SDL_Log ("Window %d got unknown event %d", WEvent.window.windowID, WEvent.window.event);
#endif
     break;
    }

   break;
#ifdef _ONEWIN   
  case SDL_MOUSEBUTTONDOWN:
  case SDL_MOUSEBUTTONUP:
   WEvent.button.x /= Application->GetGlobalScale ();
   WEvent.button.y /= Application->GetGlobalScale ();

   if (!ORedirect)
    {
     CalcRXY ();
     //bar click
     if (onewin_cursor == 1)
      {
       if (WEvent.type == SDL_MOUSEBUTTONDOWN)
        {
         if (WEvent.button.x < (int) (Width + RX - 20))
          {
           move_on = 1;
          }
         else
          {
           WDestroy ();
           Application->GetARootWindow ()->Draw ();
          }
        }
       else
        {
         move_on = 0;
        }
       break;
      }
      //resize click
     else if (onewin_cursor == 2)
      {
       if ((WEvent.button.y > (int) (RY + Height + 10)) && (WEvent.button.y < (int) (RY + Height + 20)))
        {
         if (WEvent.type == SDL_MOUSEBUTTONDOWN)
          {
           move_on = 2;
          }
         else
          {
           move_on = 0;
          }
         break;
        }
      }

    }
   CControl::Event (WEvent);
   ret = 1;
   break;
  case SDL_MOUSEMOTION:
   WEvent.motion.x /= Application->GetGlobalScale ();
   WEvent.motion.y /= Application->GetGlobalScale ();

   if (move_on == 1)
    {
     SetX (WEvent.motion.x - Application->GetOffsetX () - 10);
     SetY (WEvent.motion.y - Application->GetOffsetY () - 10);
     Application->GetARootWindow ()->Draw ();
     Draw ();
    }
   else if (move_on == 2)
    {
     int w = WEvent.motion.x - Application->GetOffsetX () - X + 5;
     int h = WEvent.motion.y - Application->GetOffsetY () - Y - 15;
     if (w > 64)
      {
       SetWidth (w);
      }
     if (h > 64)
      {
       SetHeight (h);
      }

     on_show ();
     Application->GetARootWindow ()->Draw ();
     Draw ();
    }
   else
    {
     if ((WEvent.motion.x > RX) && (WEvent.motion.x < (int) (Width + RX)))
      {
       if ((WEvent.motion.y > RY) && (WEvent.motion.y < (int) (20 + RY)))
        {
         SDL_Cursor* cursor;
         cursor = SDL_CreateSystemCursor (SDL_SYSTEM_CURSOR_HAND);
         SDL_SetCursor (cursor);
         onewin_cursor = 1;
        }
       else if ((WEvent.motion.x > (int) (Width + RX - 10)) && (WEvent.motion.x < (int) (Width + RX)))
        {
         if ((WEvent.motion.y > (int) (RY + Height + 10)) && (WEvent.motion.y < (int) (RY + Height + 20)))
          {
           SDL_Cursor* cursor;
           cursor = SDL_CreateSystemCursor (SDL_SYSTEM_CURSOR_SIZEALL);
           SDL_SetCursor (cursor);
           onewin_cursor = 2;
          }
         else
          {
           if (onewin_cursor)
            {
             onewin_cursor = 0;
             SDL_Cursor* cursor;
             cursor = SDL_CreateSystemCursor (SDL_SYSTEM_CURSOR_ARROW);
             SDL_SetCursor (cursor);
            }
          }
        }
       else
        {
         if (onewin_cursor)
          {
           onewin_cursor = 0;
           SDL_Cursor* cursor;
           cursor = SDL_CreateSystemCursor (SDL_SYSTEM_CURSOR_ARROW);
           SDL_SetCursor (cursor);
          }
        }
      }
     else
      {
       if (onewin_cursor)
        {
         onewin_cursor = 0;
         SDL_Cursor* cursor;
         cursor = SDL_CreateSystemCursor (SDL_SYSTEM_CURSOR_ARROW);
         SDL_SetCursor (cursor);
        }
      }
     CControl::Event (WEvent);
    }
   ret = 1;
   break;
#endif   
  case SDL_KEYDOWN:
#ifdef _ONEWIN
   if (this == Application->GetAWindow (0))
    {
     if (WEvent.key.keysym.sym == SDLK_x)
      {
       lxrad_scale_up ();
      }
     else if (WEvent.key.keysym.sym == SDLK_z)
      {
       lxrad_scale_down ();
      }
    }
#endif     
   CControl::Event (WEvent);
   ret = 1;
   break;
  case SDL_MULTIGESTURE:
#ifdef _ONEWIN
   if (fabs (WEvent.mgesture.dDist) > 0.002)
    {
     //Pinch open
     if (WEvent.mgesture.dDist > 0)
      {
       lxrad_scale_up ();
      }
      //Pinch close
     else
      {
       lxrad_scale_down ();
      }
    }
#endif   
   break;
  default:
   CControl::Event (WEvent);
   ret = 1;
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
     }
     Update (Reg);
     ret= 1;
     break;
    */
  }

 /*
   if ((LEvent.type != WEvent.type)&&(LEvent.type == ConfigureNotify))
   {
       Display *disp=Application->GetADisplay();

       if(disp)
       {
         int se=0;
     if(Width != (uint)LEvent.xconfigure.width)se=1;
         if(Height != (uint)LEvent.xconfigure.height)se=1;
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
       }
   }

 LEvent = WEvent;
 */

 return ret;
}

lxStringList
CWindow::GetContext(void)
{
 CControl::GetContext ();
 Context.AddLine (xml_out (lxT ("Title"), lxT ("lxString"), GetTitle ()));
 Context.AddLine (xml_out (lxT ("OverrideRedirect"), lxT ("bool"), itoa (GetOverrideRedirect ())));
 //events 
 Context.AddLine (xml_out (lxT ("EvOnCreate"), lxT ("Event"), btoa (GetEv ())));
 Context.AddLine (xml_out (lxT ("EvOnDestroy"), lxT ("Event"), btoa (GetEv ())));
 Context.AddLine (xml_out (lxT ("EvOnShow"), lxT ("Event"), btoa (GetEv ())));
 Context.AddLine (xml_out (lxT ("EvOnHide"), lxT ("Event"), btoa (GetEv ())));
 Context.AddLine (xml_out (lxT ("EvOnEnter"), lxT ("Event"), btoa (GetEv ())));
 Context.AddLine (xml_out (lxT ("EvOnLeave"), lxT ("Event"), btoa (GetEv ())));
 return Context;
}

void
CWindow::SetContext(lxStringList context)
{
 lxString name, type, value;
 CControl::SetContext (context);
 for (uint i = 0; i < context.GetLinesCount (); i++)
  {
   xml_in (Context.GetLine (i), name, type, value);
   if (name.compare (lxT ("Title")) == 0)
    SetTitle (value);
   if (name.compare (lxT ("OverrideRedirect")) == 0)
    SetOverrideRedirect (atoi (value));
   if (name.compare (lxT ("EvOnCreate")) == 0)
    SetEv (atob (value));
   if (name.compare (lxT ("EvOnDestroy")) == 0)
    SetEv (atob (value));
   if (name.compare (lxT ("EvOnShow")) == 0)
    SetEv (atob (value));
   if (name.compare (lxT ("EvOnHide")) == 0)
    SetEv (atob (value));
   if (name.compare (lxT ("EvOnEnter")) == 0)
    SetEv (atob (value));
   if (name.compare (lxT ("EvOnLeave")) == 0)
    SetEv (atob (value));
  }
 Draw ();
}

void
CWindow::CirculateFocus(bool asc)
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
        }
      }
    }
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
    }
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
     }
  }
}

void
CWindow::SetFocus(void)
{
 SDL_RaiseWindow (WWindow);
}



//propiedades

SDL_Window*
CWindow::GetWWindow(void)
{
 return WWindow;
}

void
CWindow::SetCanDestroy(bool candestroy)
{
 CanDestroy = candestroy;
}

bool
CWindow::GetCanDestroy(void)
{
 return CanDestroy;
}

void
CWindow::SetXMouse(uint x)
{
 XMouse = x;
}

uint
CWindow::GetXMouse(void)
{
 return XMouse;
}

void
CWindow::SetYMouse(uint y)
{
 YMouse = y;
}

uint
CWindow::GetYMouse(void)
{
 return YMouse;
}

void
CWindow::SetTitle(const lxString & title)
{
 Title = title;

 if ((WWindow)&&(!OverWin))
  {
   SDL_SetWindowTitle (WWindow, Title.c_str ());
  }

}

lxString
CWindow::GetTitle(void)
{
 return Title;
}

CControl *
CWindow::GetControlOnFocus(void)
{
 if (ControlOnFocus)
  return ControlOnFocus;
 else
  return NULL;
}

void
CWindow::SetControlOnFocus(CControl * controlonfocus)
{
 if ((ControlOnFocus != NULL) && (ControlOnFocus->GetCanFocus ()))
  {
   CControl *last = ControlOnFocus;
   ControlOnFocus = NULL;
   last->focus_out ();
  }
 ControlOnFocus = controlonfocus;
}

CControl *
CWindow::GetLastControl(void)
{
 if (LastControl)
  return LastControl;
 else
  return NULL;
}

void
CWindow::SetLastControl(CControl * lastcontrol)
{
 LastControl = lastcontrol;
}

void
CWindow::SetX(int x)
{
 CControl::SetX (x);
 if ((WWindow)&&(!OverWin))
  {
   SDL_SetWindowPosition (WWindow, X, Y);
  }
}

void
CWindow::SetY(int y)
{
 CControl::SetY (y);
 if ((WWindow)&&(!OverWin))
  {
   SDL_SetWindowPosition (WWindow, X, Y);
  }
}

void
CWindow::SetWidth(uint width)
{
 CControl::SetWidth (width);
 if ((WWindow)&&(!OverWin))
  {
   SDL_SetWindowSize (WWindow, Width, Height);
  }
}

void
CWindow::SetHeight(uint height)
{
 CControl::SetHeight (height);
 if ((WWindow)&&(!OverWin))
  {
   SDL_SetWindowSize (WWindow, Width, Height);
  }
}

int
CWindow::GetClientWidth(void)
{
 return Width;
}


int
CWindow::GetClientHeight(void)
{
 return Height;
}

//operators

void *
CWindow::operator
new (size_t sz){
 CWindow *m = (CWindow *) calloc (sz, 1);
 if (!m)
  puts ("out of memory");
 m->Dynamic = true;
 m->CanDestroy = true;
 return (void *) m;
}

void CWindow::operator delete(void* p)
{
  free(p);
}

//eventos

void
CWindow::on_create(void)
{
 if ((FOwner) && (EvOnCreate))
  (FOwner->*EvOnCreate) (this);
}

void
CWindow::on_destroy(void)
{
 if ((FOwner) && (EvOnDestroy))
  (FOwner->*EvOnDestroy) (this);
}

void
CWindow::on_show(void)
{
 if ((FOwner) && (EvOnShow))
  (FOwner->*EvOnShow) (this);
}

void
CWindow::on_hide(void)
{
 if ((FOwner) && (EvOnHide))
  (FOwner->*EvOnHide) (this);
}

void
CWindow::on_enter(void)
{
 if ((FOwner) && (EvOnEnter))
  (FOwner->*EvOnEnter) (this);
}

void
CWindow::on_leave(void)
{
 if ((FOwner) && (EvOnLeave))
  (FOwner->*EvOnLeave) (this);
}

int
CWindow::LoadXMLContextAndCreateChilds(lxString filename, CControl* ctrl)
{
 FILE* file2;
 lxStringList list;
 lxString line;

 file2 = fopen (filename.c_str (), "r");

 if (file2)
  {
   rewind (file2);
   
   if (ctrl == NULL)//for owner window
    {
     if (fgetline (file2, line))
      {
       ctrl = this;
       ctrl->SetName (line.substr (1, line.size () - 2)); //Get Window name
       ctrl->SetFOwner (this);
       rewind (file2);
      }
    }

   list.Clear ();
   while (fgetline (file2, line))
    {
     if (line.compare (lxT ("<") + ctrl->GetName () + lxT (">")) == 0)
      {
       fgetline (file2, line);
       do
        {
         list.AddLine (line);
         fgetline (file2, line);
        }
       while (line.c_str ()[0] == ' ');
       ctrl->SetContext (list);

       while (line.compare (lxT ("</") + ctrl->GetName () + lxT (">")) != 0)
        {
         lxString controlclass, ctype, name, cname;

         cname = line.substr (1, line.size () - 2);
         fgetline (file2, line);
         xml_in (line, name, ctype, controlclass);

         CControl *ch = newcontrolbycname (controlclass);
         ch->SetName (cname);
         ch->SetFOwner (ctrl);

         /* 
         if (ch->GetClass ().compare (lxT ("CItemMenu")) == 0)
                   {
                     ch->SetVisible (false, false);
                   }
          */
         ctrl->CreateChild (ch);

         if (ch != NULL)
          LoadXMLContextAndCreateChilds (filename, ch);
         else
          printf ("Child Not Found! %s \n", (char*) name.char_str ());

         do
          {
           fgetline (file2, line);
          }
         while ((line.compare (lxT ("</") + cname + lxT (">")) != 0));
         fgetline (file2, line);
        }

      }

    }

   fclose (file2);
   return 1;
  }
 else
  printf ("File (%s) not found!\n", (char *) filename.char_str ());

 return 0;
}

bool
CWindow::GetCanExitExclusive(void)
{
 return CanExitExclusive;
}

CWindow*
CWindow::GetWWidget(void)
{
 return this;
}

SDL_Renderer *
CWindow::GetRenderer(void)
{
 return Renderer;
}

bool
CWindow::GetOverWin(void)
{
 return OverWin;
}

void
CWindow::SetOverWin(bool ow)
{
 OverWin = ow;
}

int
CWindow::GetRedraw(void)
{
 return Redraw;
}

void
CWindow::SetRedraw(void)
{
 Redraw++;
#ifdef _ONEWIN   
 if (Application->GetARootWindow () != this)
  {
   Application->GetARootWindow ()->SetRedraw ();
  }
#endif
}

bool
CWindow::OwnerEvent(int x, int y)
{
 CalcRXY ();

 if ((x > RX) && (x < (int) (Width + RX)))
  {
#ifdef _ONEWIN   
   if ((y > RY) && (y < (int) (Height + RY + 20)))
#else   
   if ((y > RY) && (y < (int) (Height + RY)))
#endif
    return true;
   else
    return false;
  }
 else
  return false;
}

void
CWindow::CreateChild(CControl * control)
{
 CControl::CreateChild (control);
 if (!control->GetClass ().Cmp ("CStatusbar"))
  {
   statusbar = control;
  }
}
