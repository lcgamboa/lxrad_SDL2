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
#include"../include/ctimer.h"
#include <sys/time.h>

#ifdef HAVE_LIBPTHREAD	
#include<pthread.h>
#include<unistd.h>
#endif

// CTimer___________________________________________________________

CTimer::CTimer (void)
{
  CanFocus = false;
  SetX (10);
  SetY (10);
  SetWidth (10);
  SetHeight (10);
  SetClass ("CTimer");
  Time = 1;
  Run = false;
  EvOnTime = NULL;
  SetVisible (false);
};

CTimer::~CTimer (void)
{
};

void
CTimer::Create (CControl * control)
{
  CControl::Create (control);
};

void
CTimer::Destroy (void)
{
  SetRunState (false);
  CControl::Destroy ();
};

void
CTimer::Draw (void)
{
  /*	
  if ((!Visible)||(Paint == NULL))
    return;
  Paint->InitDraw (this);
  Paint->Pen.SetColor (Color);
  Paint->Rectangle ( 2, 2, Width - 4, Height - 4);
  Paint->Pen.SetColor (ColorByName ("black"));
  Paint->LowerFrame ( 0, 0, Width, Height);
  Paint->Text ( 10, 10, "Timer");
  CControl::Draw ();
  */
};

CStringList CTimer::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine ("Time=" + itoa (GetTime ()) + ";int");
  Context.AddLine ("RunState=" + itoa (GetRunState ()) + ";int");
  Context.AddLine ("OnTime=" + btoa (GetEv ()) + ";event");
  return Context;
};

void
CTimer::SetContext (CStringList context)
{
  Eraser ();
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      String line = Context.GetLine (i);
      String arg;
      eqparse (line, arg);
      if (line.compare ("Time") == 0)
	SetTime (atoi (arg));
      if (line.compare ("RunState") == 0)
	SetRunState (atoi (arg));
      if (line.compare ("OnTime") == 0)
	SetEv (atob (arg));
    };
  Draw ();
};

#ifdef HAVE_LIBPTHREAD	
extern pthread_mutex_t Display_Lock;

void *
thread1 (void *arg)
{
  struct timeval  tv1, tv2;
  pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS,NULL);  
  CTimer *timer = (CTimer *) arg;
  usleep (timer->GetTime ()*1000);
  for (;;)
    {
      pthread_mutex_lock (&Display_Lock);                   
      gettimeofday(&tv1, NULL);
      timer->on_time ();
      gettimeofday(&tv2, NULL);	
      pthread_mutex_unlock (&Display_Lock);                   
      usleep ((timer->GetTime ()*1000) -((tv2.tv_usec - tv1.tv_usec) + 1000000L*(tv2.tv_sec - tv1.tv_sec)));
    };
};
#endif

/*
void *
CTimer::thread (void *arg)
{
  CTimer *timer = static_cast < CTimer * >(arg);
  for (;;)
    {
      sleep (timer->GetTime ());
      timer->on_time ();
    };
};
*/

//propiedades

void
CTimer::SetTime (uint time)
{
  Time = time;
};

uint
CTimer::GetTime (void)
{
  return Time;
};

void
CTimer::SetRunState (bool run)
{
#ifdef HAVE_LIBPTHREAD	
  if (Run != run)
    {
      if (run)
      {
	  pthread_create (&Th, NULL, thread1, (void *) this);
      }
      else
	{
	  pthread_cancel (Th);
	  pthread_join (Th, NULL);
	};
      Run = run;
    };
#endif  
};

bool
CTimer::GetRunState (void)
{
  return Run;
};

void
CTimer::on_time (void)
{
  if ((FOwner) && (EvOnTime))
    (FOwner->*EvOnTime) (this);
};
