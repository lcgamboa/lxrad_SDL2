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

#include"../config.h"
#include"../include/capplication.h"

#include<time.h>
#include<unistd.h>

#include<pthread.h>
pthread_mutex_t Display_Lock;

#ifdef HAVE_LIBIMLIB2
#include<Imlib2.h>
#endif

// CApplication__________________________________________________________


CApplication::CApplication (void)
{
  Title = "Program";
  AWindowCount = -1;
  AWindowList = NULL;
  Tag = 0;
  Exit = false;

  HintControl=NULL;
  HintTime=time(NULL);
  HintX=0;
  HintY=0;
  pthread_mutex_init (&Display_Lock,NULL);
  pthread_mutex_lock (&Display_Lock);
};

CApplication::~CApplication (void)
{
  pthread_mutex_destroy (&Display_Lock);  
};

void
CApplication::Start (void)
{

   
  eprint("Application init ...\n");
 if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
   { 
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
      eprint("Error!: Can't open  Display \n");
      eprint("...Application Finished\n");
      Exit = true;
      return;
    };

     //Initialize PNG loading 
    int imgFlags = IMG_INIT_PNG; 
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
    { 
      printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
      eprint("...Application Finished\n");
      Exit = true;
      return; 
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
      printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
      Exit = true;
      return; 
    }    
    

#ifdef _DEBUG
  eprint("synchronize\n");
  XSynchronize (ADisplay, true);
#else
  if (setlocale (LC_CTYPE, "") == NULL)
    {
      eprint("Error : setlocale() !\n");
      Exit = true;
      return;
    };

#endif

};

void
CApplication::ACreateWindow (CWindow * AWindow,CWindow *window)
{
  if (Exit)
    {
      AWindow->CControl::Destroy ();
      return;
    };
  if (AWindowCount == -1)
    AWindow->SetVisible (true,false);
  AWindow->WCreate (window);
  AWindowCount++;
  CWindow **WindowList;
  WindowList = new CWindow *[AWindowCount + 1];
  for (int c = 0; c < AWindowCount; c++)
    WindowList[c] = AWindowList[c];
  WindowList[AWindowCount] = AWindow;
  if (AWindowList)
    delete[]AWindowList;
  AWindowList = WindowList;
  AWindow->Draw ();
};

void
CApplication::Draw (void)
{
  if (AWindowCount < 0)
    return;
  else
    for (int i = 0; i <= AWindowCount; i++)
      AWindowList[i]->Draw ();
};

void
CApplication::Update (void)
{
  if (AWindowCount < 0)
    return;
  else
    for (int i = 0; i <= AWindowCount; i++)
      AWindowList[i]->Update ();
};

void
CApplication::ADestroyWindow (CWindow * AWindow)
{
  if (AWindowCount >= 0)
    {
      int wn = 0;
      if (AWindowList[0]->GetWWindow () == AWindow->GetWWindow ())
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
	  eprint("...Application Finished\n");
#ifdef _DEBUG
	  eprint("synchronize\n");
	  XSynchronize (ADisplay, false);
#endif
          TTF_Quit();
	  IMG_Quit();
          SDL_Quit();
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
	    };
	};
    };
};


bool
CApplication::ProcessEvents (CWindow * AWindow)
{
  if (AWindow != NULL)
    {
      int wn = -1;
      int ec;
      
     //wait hint loop	    

     ec=SDL_PollEvent(&AEvent);
     while(ec ==  0 )
     {
	usleep(50000);
        ec=SDL_PollEvent(&AEvent);
	if((HintControl)&&(time(NULL)-HintTime > 1))
	{
          if(HintControl->GetHint().size() >0)
	  {
	  WHint(HintControl->GetHint(),
    	    HintX+HintControl->GetWin()->GetX(),
     	    HintY+HintControl->GetWin()->GetY());
	  };
	  HintControl=NULL;
        }
     };
      HintControl=NULL;
      
      
      FWindow = AEvent.window.windowID;
      for (int e = 0; e <= AWindowCount; e++)
	{
	  if (FWindow == SDL_GetWindowID(AWindowList[e]->GetWWindow ()) )
	    {
	      wn = e;
	      break;
	    };

	};


      if (((AEvent.type == SDL_WINDOWEVENT) && ((AEvent.window.type == SDL_WINDOWEVENT_ENTER)||(AEvent.window.type == SDL_WINDOWEVENT_EXPOSED)))
	  && (AWindowCount >= 0) && (wn >= 0))
	{
	  AWindowList[wn]->WEvents (AEvent);
	}
      else
       {
        if (AEvent.window.windowID == SDL_GetWindowID(AWindow->GetWWindow ()))
	{
           if ((AEvent.type == SDL_WINDOWEVENT)&&(AEvent.window.type == SDL_WINDOWEVENT_CLOSE))
            {
	      return false;
	    }
	  else
          {
            AWindow->WEvents (AEvent);   
	    return true;
          }
	}
        else
	{
           if (AEvent.type == SDL_MOUSEMOTION )
	    {
	      AWindow->WEvents (AEvent);
	      return true;
	    }
	};
		
       };
    };
  return false;
};




void
CApplication::Load (void)
{
  if (Exit)
    return;
  
  pthread_mutex_unlock (&Display_Lock);

  if (AWindowCount == -1)
    {
      eprint("No Windows!\n");
      eprint("...Application Finished\n");
#ifdef _DEBUG
      eprint("synchronize\n");
      XSynchronize (ADisplay, false);
#endif
      TTF_Quit();
      IMG_Quit();
      SDL_Quit();
      return;
    };

  int wn = 0;
  int ec;   //events in queue

  FWindow = SDL_GetWindowID(AWindowList[wn]->GetWWindow ());
  for (; AWindowList != NULL;)
    {

     //wait hint loop	    
     ec=SDL_PollEvent(&AEvent);
     while(ec ==  0 )
     {
	usleep(50000);
	ec=SDL_PollEvent(&AEvent);
	if((HintControl)&&(time(NULL)-HintTime > 1))
	{
          if(HintControl->GetHint().size() >0)
	  {
	  WHint(HintControl->GetHint(),
    	    HintX+HintControl->GetWin()->GetX(),
     	    HintY+HintControl->GetWin()->GetY());
	  };
	  HintControl=NULL;
        }
     };
      HintControl=NULL;
      

      
      FWindow = AEvent.window.windowID;

      wn = -1;
      for (int e = 0; e <= AWindowCount; e++)
	if (FWindow == SDL_GetWindowID(AWindowList[e]->GetWWindow ()) )
	  {
	    wn = e;
	    break;
	  };
      if (wn >= 0)
	AWindowList[wn]->WEvents (AEvent);

      if ((AEvent.type == SDL_WINDOWEVENT)&&(AEvent.window.type == SDL_WINDOWEVENT_CLOSE))
	for (int p = 0; p <= AWindowCount; p++)
	  if (AEvent.window.windowID == SDL_GetWindowID(AWindowList[p]->GetWWindow ()))
	    {
	      ADestroyWindow (AWindowList[p]);
	      wn = -1;
	      //Update ();
	      if (Exit)
		return;
	      break;
	    };
      
    };
};




bool
CApplication::GetExit (void)
{
  return Exit;
};

//propierties

int
CApplication::GetAWindowCount (void)
{
  return AWindowCount;
};

CWindow *
CApplication::GetAWindow (uint window)
{
  return AWindowList[window];
};

int
CApplication::GetTag ()
{
  return Tag;
};

void
CApplication::SetTag (int x)
{
  Tag = x;
};

String CApplication::GetTitle (void)
{
  return Title;
};




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
  };

  if( HTimer.GetTag() == 1 )
    HTimer.SetTag(2);   
  else  
    HTimer.SetTag(0);   
  
};
*/


void 
CApplication::SetHintControl(CControl* hcontrol,int x,int y)
{
  HintControl=hcontrol;
  HintTime=time(NULL);
  HintX=x;
  HintY=y;
};


bool
CApplication::ProcessEvents (void)
{
//FIXME
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
return 0;
}
