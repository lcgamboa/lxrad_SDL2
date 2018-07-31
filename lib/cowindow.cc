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
#include"../include/cowindow.h"
#include"../include/capplication.h"


//CWindow _______________________________________________________________

COWindow::COWindow (void)
{
  WWindow = NULL;
  SetClass ("COWindow");
  Win = NULL;
}

COWindow::~COWindow (void)
{

}


void
COWindow::WCreate (CWindow* window)
{
 

  if(window != NULL)
  {
    WParent=window;
  }
  
  Win = this;
  WWindow=Application->GetAWindow (0)->GetWWindow ();
  Renderer=Application->GetAWindow (0)->GetRenderer ();
  
 // if(ORedirect)
     
  WPixmap=  SDL_CreateTexture(Win->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width, Height );

  
 
  WPaint.Create (this);
  Paint = &WPaint;
  
  Create (this);
  Draw();
  
  if(Visible) Show ();

  on_create ();
}

void
COWindow::Destroy (void)
{
  CControl::Destroy ();
  DestroyPixmap();
  if(Renderer)
    SDL_DestroyRenderer( Renderer );
  if(WWindow )
    SDL_DestroyWindow( WWindow );
  WWindow = NULL;
  Renderer = NULL;
}


void
COWindow::Draw(void)
{
  if(Paint == NULL)return;
  SDL_SetRenderTarget(Renderer,WPixmap);
  Paint->InitDraw(this);
  Paint->Pen.SetColor(Color);
  Paint->Rectangle ( 0, 0, Width, Height);
  CControl::Draw ();
  
  SDL_SetRenderTarget(Renderer,NULL);
  SDL_Rect DestR;

  DestR.x = (Win->GetWidth ()-Width)/2;
  DestR.y = (Win->GetHeight ()- Height)/2;
  DestR.w = Width;
  DestR.h = Height;
  SDL_RenderCopy( Renderer, WPixmap, NULL, &DestR); 
  SDL_RenderPresent( Renderer );
}

void
COWindow::WDestroy (void)
{
  SetVisible (false);
  on_destroy ();
};

void
COWindow::Show (void)
{
  if(Win != NULL)
    {
      SetVisible (true);
      Draw();
      Update ();
    };
};

void
COWindow::ShowExclusive (void)
{
  Show ();
  CanExitExclusive = true;
  while (CanExitExclusive)
    Application->ProcessEvents (this);
};

void
COWindow::Hide (void)
{
  if (Win != NULL)
    {
      SetVisible (false);
    };
};

void
COWindow::HideExclusive (void)
{
  CanExitExclusive = false;
  Hide ();
};
