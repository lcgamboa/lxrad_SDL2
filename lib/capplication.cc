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

#include"../config.h"
#include"../include/capplication.h"

#include<time.h>
#include<unistd.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
// CApplication__________________________________________________________

CApplication::CApplication(void)
{
 Title = "Program";
 AWindowCount = -1;
 AWindowList = NULL;
 TimerCount = -1;
 TimerList = NULL;
 ThreadCount = -1;
 ThreadList = NULL;
 Tag = 0;
 Exit = false;
 ARootWindow = NULL;
 HintControl = NULL;
 HintTime = time (NULL);
 HintX = 0;
 HintY = 0;
 MWindow = NULL;
 Gscale = 1.0;
 OffsetX = 0;
 OffsetY = 0;
 mdx = 0;
 mdy = 0;
 mouse_scroll = 0;

 if(!TTF_WasInit())
 {
   for (int i = 0; i < (FONT_MAX * 2); i++)
   {
     fontlist[i] = NULL;
    }

   //Initialize SDL_ttf
   if (TTF_Init () == -1)
   {
     printf ("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError ());
     Exit = true;
     return;
   }
 } 

}

CApplication::~CApplication(void)
{
 for (int i = 0; i < (FONT_MAX * 2); i++)
  {
   if (fontlist[i])
    {
     TTF_CloseFont (fontlist[i]);
     fontlist[i] = NULL;
    }
  }
 TTF_Quit ();
 IMG_Quit ();
 SDL_Quit ();
}

TTF_Font *
CApplication::GetFont(int size, int family, int style, int weight)
{

 if (size < 1)size = 1;
 if (size >= FONT_MAX) size = FONT_MAX - 1;

 const int fontaddr = size + family * FONT_MAX;

  if(!TTF_WasInit())
  {
   for (int i = 0; i < (FONT_MAX * 2); i++)
   {
     fontlist[i] = NULL;
    }

   //Initialize SDL_ttf
   if (TTF_Init () == -1)
   {
     printf ("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError ());
     exit(-1);
   }
  } 

 //TODO only size font and size are used 
 if (fontlist[fontaddr] == NULL)
  {
   if (!family)
    {
     fontlist[fontaddr] = TTF_OpenFontIndex ((lxString (_SHARE) + "fonts/FreeSans.ttf").c_str (), size + 2, 0);
    }
   else
    {
     fontlist[fontaddr] = TTF_OpenFontIndex ((lxString (_SHARE) + "fonts/FreeMonoBold.ttf").c_str (), size + 3, 0);
    }

   if (fontlist[fontaddr] == NULL)
    {
     printf ("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError ());
     exit (-1);
    }
   //printf ("Font Loaded %i %i %i %i\n", size, family, style, weight);
  }

 return fontlist[fontaddr];
}

void
CApplication::Start(void)
{

 eprint ("Application init ...\n");
 if (SDL_Init (SDL_INIT_VIDEO) < 0)
  {
   printf ("SDL could not initialize! SDL_Error: %s\n", SDL_GetError ());
   eprint ("Error!: Can't open  Display \n");
   eprint ("...Application Finished\n");
   Exit = true;
   return;
  }
  
  //SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "0");
  //SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");

 //Initialize PNG loading 
 int imgFlags = IMG_INIT_PNG;
 if (!(IMG_Init (imgFlags) & imgFlags))
  {
   printf ("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError ());
   eprint ("...Application Finished\n");
   Exit = true;
   return;
  }

 if (setlocale (LC_CTYPE, "") == NULL)
  {
   eprint ("Error : setlocale() !\n");
   Exit = true;
   return;
  };

};

void
CApplication::ACreateWindow(CWindow * AWindow, CWindow *window)
{
#ifdef _ONEWIN
 if (AWindowCount == -1)
  {
   SDL_Rect rect;
   SDL_GetDisplayUsableBounds (0, &rect);

   ARootWindow = new CWindow;
   ARootWindow->SetWidth (rect.w);
   ARootWindow->SetHeight (rect.h);
   ARootWindow->SetColor("dark gray");
   ARootWindow->WCreate ();
  }
 AWindow->SetOverWin (true);
 ARootWindow->CreateChild (AWindow);
#else
 if (AWindowCount == -1)
  {
   ARootWindow = AWindow;
  }
#endif
 if (Exit)
  {
   AWindow->CControl::Destroy ();
   return;
  }
 if (AWindowCount == -1)
  AWindow->SetVisible (true, false);
 AWindowCount++;
 CWindow **WindowList;
 WindowList = new CWindow *[AWindowCount + 1];
 for (int c = 0; c < AWindowCount; c++)
  WindowList[c] = AWindowList[c];
 WindowList[AWindowCount] = AWindow;
 if (AWindowList)
  delete[]AWindowList;
 AWindowList = WindowList;
 AWindow->WCreate (window);
 AWindow->Draw ();
}

void
CApplication::Draw(void)
{
 if (AWindowCount < 0)
  return;
 else
  for (int i = 0; i <= AWindowCount; i++)
   AWindowList[i]->Draw ();
}

void
CApplication::Update(void)
{
 if (AWindowCount < 0)
  return;
 else
  for (int i = 0; i <= AWindowCount; i++)
   AWindowList[i]->Update ();
}

void
CApplication::ADestroyWindow(CWindow * AWindow)
{
 if (AWindowCount >= 0)
  {
#ifdef _ONEWIN   
   ARootWindow->DestroyChild (AWindow);
#endif   
   int wn = 0;
   if (AWindowList[0] == AWindow)
    {
     if (AWindowList[0]->GetDynamic ())
      delete AWindowList[0];
     for (int r = AWindowCount; r > 0; r--)
      {
       AWindowList[r]->SetCanDestroy (true);
       AWindowList[r]->WDestroy ();
      };
     delete[]AWindowList;
     AWindowList = NULL;
     AWindowCount = -1;
     eprint ("...Application Finished\n");
#ifdef __EMSCRIPTEN__
     emscripten_cancel_main_loop ();
#endif  

     Exit = true;
     return;
    }
   else
    {
     for (int f = 0; f <= AWindowCount; f++)
      if (AWindowList[f] == AWindow)
       wn = f;
     if (wn != 0)
      {
       if (AWindowList[wn]->GetDynamic ())
        delete AWindowList[wn];
       for (int c = wn; c < AWindowCount; c++)
        AWindowList[c] = AWindowList[c + 1];
       AWindowList[AWindowCount] = NULL;
       AWindowCount--;
      }
    }
  }
}


#ifdef __EMSCRIPTEN__

void
loop_handler(void)
{  
 Application->GetARootWindow ()->SetRedraw (); //FIXME force redraw every cicle to avoid flicker. Use software double buffer?
 Application->ProcessEvents ();
}
#endif

void
CApplication::Load(void)
{
 if (Exit)
  return;

 if (AWindowCount == -1)
  {
   eprint ("No Windows!\n");
   eprint ("...Application Finished\n");
   return;
  }

 int wn = 0;
 FWindow = SDL_GetWindowID (AWindowList[wn]->GetWWindow ());
#ifdef __EMSCRIPTEN__
 emscripten_set_main_loop (loop_handler, -1, 1);
#else 
 for (; AWindowList != NULL;)
  {
   ProcessEvents ();
  }
#endif

#ifdef _ONEWIN
 if (ARootWindow)
  {
   delete ARootWindow;
   ARootWindow = NULL;
  }
#endif
}

bool
CApplication::ProcessEvents(void)
{
 CWindow * wn = NULL;
 int ec; //events in queue
 struct timeval tv;
 long int elapsed;
 static int trun = 0;

#ifdef _ONEWIN
 ARootWindow->Draw ();
#else
 //Redraw windows
 Draw ();
#endif


 if (!MWindow)//Not modal window
  {
   //timer an thread process
   if ((!trun)&&(!Exit))
    {
     trun = 1;
     //printf("---------------------\n");
     for (int t = 0; t <= TimerCount; t++)
      {
       gettimeofday (&tv, NULL);
       elapsed = (((tv.tv_usec - TimerList[t]->tv.tv_usec) / 1000L) + 1000L * (tv.tv_sec - TimerList[t]->tv.tv_sec));

       //printf("Elapsed %i = %lu de %lu\n",t,elapsed,TimerList[t]->GetTime());
       if (elapsed >= TimerList[t]->GetTime ())
        {
         //printf("===>>Timer %i reseted\n",t);	       
         TimerList[t]->tv = tv;
         TimerList[t]->SetOverTime (elapsed - TimerList[t]->GetTime ());
         TimerList[t]->on_time ();
        }
      }

#ifndef HAVE_LIBPTHREAD
     for (int t = 0; t <= ThreadCount; t++)
      {
       ThreadList[t]->on_run ();
      }
#endif
     trun = 0;
    }
  }


 while (1)
  {
   //wait hint loop	    
   ec = SDL_PollEvent (&AEvent);
   if (ec == 0)
    {
     usleep (1000); //idle
     if ((HintControl)&&(time (NULL) - HintTime > 1))
      {
       if (HintControl->GetHint ().size () > 0)
        {
         WHint (HintControl->GetHint (),
                HintX + HintControl->GetWin ()->GetX (),
                HintY + HintControl->GetWin ()->GetY ());
        }
       HintControl = NULL;
      }

     return false;
    }


   //compress mouse move events
   if (AEvent.type == SDL_MOUSEMOTION)
    {
     SDL_Event LEvent;
     do
      {
       LEvent = AEvent;
       ec = SDL_PollEvent (&AEvent);
      }
     while (ec && (AEvent.type == SDL_MOUSEMOTION));

     if (ec)//event != SDL_MOUSEMOTION
      {
       SDL_PushEvent (&AEvent);
      }
     AEvent = LEvent;
    }

   //discard repeated keydown event
   if ((AEvent.type == SDL_KEYDOWN)&&(AEvent.key.repeat > 0))
    {
     return false;
    }

   HintControl = NULL;



   FWindow = AEvent.window.windowID;



#ifdef _ONEWIN   
   for (int e = 0; e <= AWindowCount; e++)
    {
     wn = NULL;

     if (AWindowList[e]->GetVisible ())
      {
       switch (AEvent.type)
        {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
         if (AWindowList[e]->OwnerEvent (AEvent.button.x / Gscale, AEvent.button.y / Gscale))
          {
           wn = AWindowList[e];
          }
         break;
        default:
         wn = AWindowList[e];
        }
      }

#else
   wn = NULL;
   for (int e = 0; e <= AWindowCount; e++)
    {
     if (FWindow == SDL_GetWindowID (AWindowList[e]->GetWWindow ()))
      {
       wn = AWindowList[e];
       break;
      }
    }
#endif

     if (AEvent.type == SDL_MOUSEBUTTONUP)
      {
       mouse_scroll = 0;
       mdx = 0;
       mdy = 0;
      }

     if (!MWindow)//Not modal window
      {
       if (wn)
        {
         wn->WEvents (AEvent);
         if ((AEvent.type == SDL_MOUSEBUTTONDOWN) || (AEvent.type == SDL_MOUSEBUTTONUP))
          {
           mouse_scroll = 0;
           mdx = 0;
           mdy = 0;
           return 1;
          }
        }

       if (AEvent.type == SDL_MOUSEBUTTONDOWN)
        {
         mouse_scroll = 1;
         mdx = AEvent.button.x;
         mdy = AEvent.button.y;
        }

       if (AEvent.type == SDL_MOUSEMOTION)
        {
         if (mouse_scroll)
          {
           OffsetX -= mdx - AEvent.button.x;
           OffsetY -= mdy - AEvent.button.y;
           mdx = AEvent.button.x;
           mdy = AEvent.button.y;
           //update_all = 1;
          }
        }

       if (AEvent.window.type == SDL_WINDOWEVENT_CLOSE)
        for (int p = 0; p <= AWindowCount; p++)
         {
          if (AEvent.window.windowID == SDL_GetWindowID (AWindowList[p]->GetWWindow ()))
           {
            ADestroyWindow (AWindowList[p]);
            wn = NULL;
            //Update ();
            if (Exit)
             return true;
            break;
           }
         }
      }
     else // modal window
      {
#ifndef _ONEWIN   
       MWindow->Draw ();
#endif   
       if ((/*(AEvent.type == SDL_WINDOWEVENT) &&*/ ((AEvent.window.type == SDL_WINDOWEVENT_ENTER) || (AEvent.window.type == SDL_WINDOWEVENT_EXPOSED)))
           && (AWindowCount >= 0) && (wn != NULL))
        {
         wn->WEvents (AEvent);
        }
       else
        {
         if (AEvent.window.windowID == SDL_GetWindowID (MWindow->GetWWindow ()))
          {
           if (AEvent.window.type == SDL_WINDOWEVENT_CLOSE)
            {
             return false;
            }
           else if ((AEvent.type == SDL_MOUSEBUTTONDOWN) || (AEvent.type == SDL_MOUSEBUTTONUP))
            {
             if (MWindow->OwnerEvent (AEvent.button.x / Gscale, AEvent.button.y / Gscale))
              {
               MWindow->WEvents (AEvent);
               return true;
              }
            }
           else
            {
             MWindow->WEvents (AEvent);
             return true;
            }
          }
         else
          {
           if (AEvent.type == SDL_MOUSEMOTION)
            {
             MWindow->WEvents (AEvent);
             return true;
            }
          }

        }
      }
#ifdef _ONEWIN
    }
#endif
  }
 return false;
}

bool
CApplication::GetExit(void)
{
 return Exit;
};

//properties

int
CApplication::GetAWindowCount(void)
{
 return AWindowCount;
};

CWindow *
CApplication::GetAWindow(uint window)
{
 if (((int) window <= AWindowCount)&&(AWindowCount >= 0))
  return AWindowList[window];
 else
  return NULL;
}

CWindow *
CApplication::GetARootWindow(void)
{
 return ARootWindow;
}

int
CApplication::GetTag()
{
 return Tag;
}

void
CApplication::SetTag(int x)
{
 Tag = x;
}

lxString
CApplication::GetTitle(void)
{
 return Title;
}

/*
void
CApplication::OnHintTime(CControl* control)
{
  if((HTimer.GetTag()==2)&&(HintControl)&&(HintControl->GetHint().size()>0))
  {
    	  
    //WHint(HintControl->GetHint(),
    //	  HTimer.GetX()+HintControl->GetWin()->GetX(),
    // 	  HTimer.GetY()+HintControl->GetWin()->GetY());
   
    XClientMessageEvent xev;
    memset(&xev, 0, sizeof(xev));
    xev.type = ClientMessage;
    xev.send_event=1;
    xev.display=ADisplay;
    xev.window=FWindow;
    xev.message_type = AShowHint;
    xev.format=32;
    xev.data.s[0] = CurrentTime; 
    
    //XSendEvent(ADisplay, FWindow, false,0l, (XEvent *) &xev);
    printf("%s\n",HintControl->GetHint().c_str());	  
    HTimer.SetTag(0);   
    HintControl=NULL;
  }

  if( HTimer.GetTag() == 1 )
    HTimer.SetTag(2);   
  else  
    HTimer.SetTag(0);   
  
}
 */


void
CApplication::SetHintControl(CControl* hcontrol, int x, int y)
{
 HintControl = hcontrol;
 HintTime = time (NULL);
 HintX = x;
 HintY = y;
}

void
CApplication::SetModalWindow(CWindow * mwindow)
{
 if (mwindow)
  {
   LMWindow = MWindow;
   MWindow = mwindow;
  }
 else
  {
   MWindow = LMWindow;
   LMWindow = NULL;
  }
}

CWindow *
CApplication::GetModalWindow(void)
{
 return MWindow;
}

void
CApplication::AddTimer(CTimer * tm)
{
 TimerCount++;
 CTimer **TList;
 TList = new CTimer *[TimerCount + 1];
 for (int c = 0; c < TimerCount; c++)
  TList[c] = TimerList[c];
 TList[TimerCount] = tm;
 if (TimerList)
  delete[]TimerList;
 TimerList = TList;
 gettimeofday (&tm->tv, NULL);
 //printf("Timer %i added: %s\n",TimerCount,tm->GetName().c_str()); 
}

void
CApplication::RemoveTimer(CTimer *tm)
{
 if (TimerCount >= 0)
  {
   int n = -1;
   for (int f = 0; f <= TimerCount; f++)
    if (TimerList[f] == tm)
     n = f;
   if (n != -1)
    {
     for (int c = n; c < TimerCount; c++)
      TimerList[c] = TimerList[c + 1];
     TimerList[TimerCount] = NULL;
     TimerCount--;
     if (TimerCount == -1)
      {
       if (TimerList)
        {
         delete[]TimerList;
         TimerList = NULL;
        }
      }
    }
   //printf("Timer %i Removed: %s\n",TimerCount,tm->GetName().c_str()); 
  }
}

double
CApplication::GetGlobalScale(void)
{
 return Gscale;
}

void
CApplication::SetGlobalScale(double gscale)
{
 Gscale = gscale;
}

void
CApplication::SetOffsetX(int xo)
{
 OffsetX = xo;
}

void
CApplication::SetOffsetY(int yo)
{
 OffsetY = yo;
}

int
CApplication::GetOffsetX(void)
{
 return OffsetX;
}

int
CApplication::GetOffsetY(void)
{
 return OffsetY;
}

#ifndef HAVE_LIBPTHREAD

void
CApplication::AddThread(CThread * td)
{
 ThreadCount++;
 CThread **TList;
 TList = new CThread *[ThreadCount + 1];
 for (int c = 0; c < ThreadCount; c++)
  TList[c] = ThreadList[c];
 TList[ThreadCount] = td;
 if (ThreadList)
  delete[]ThreadList;
 ThreadList = TList;
}

void
CApplication::RemoveThread(CThread *td)
{
 if (ThreadCount >= 0)
  {
   int n = -1;
   for (int f = 0; f <= ThreadCount; f++)
    if (ThreadList[f] == td)
     n = f;
   if (n != -1)
    {
     for (int c = n; c < ThreadCount; c++)
      ThreadList[c] = ThreadList[c + 1];
     ThreadList[ThreadCount] = NULL;
     ThreadCount--;
     if (ThreadCount == -1)
      {
       if (ThreadList)
        {
         delete[]ThreadList;
         ThreadList = NULL;
        }
      }
    }
  }
}
#endif
