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
#include"../include/cdraw.h"
#include"../include/cmessage.h"
#include"../include/capplication.h"

#include"xevents.cc"

#include<pthread.h>
//extern pthread_mutex_t Display_Lock;

#ifdef HAVE_LIBIMLIB2
#include<Imlib2.h>
//extern ImlibData* AID;
#endif

#ifdef HAVE_LIBXPM    
#include<X11/xpm.h>
#endif

// CDraw_____________________________________________________________

CDraw::CDraw (void)
{
  FileName = "";
  Data = NULL;
  SetX (10);
  SetY (10);
  SetWidth (100);
  SetHeight (100);
  SetClass ("CDraw");
  SetTransparent (false);
  CPixmap = NULL;
};

CDraw::~CDraw (void)
{
   if (CPixmap != NULL) SDL_FreeSurface( CPixmap);
   CPixmap=NULL;
};

void
CDraw::Create (CControl * control)
{
  if (!ColorSet)
    SetColor ("white");
  CControl::Create (control);
  Canvas.Create(this);
  Canvas.SetDoCalcRXY(false);
  Visible=false;	    
  SetPixmapFileName (FileName);
  SetPixmapData (Data);
  Visible=true;	    
  if(!CPixmap)
  {
    CPixmap = SDL_CreateRGBSurfaceWithFormat(0, Width, Height, 32, SDL_PIXELFORMAT_RGBA32);
    Canvas.SetDrawIn(CPixmap);
    Canvas.Pen.SetColor (Color);
    Canvas.Rectangle ( 0, 0, Width, Height);
  };
 };

void
CDraw::Destroy (void)
{
  if (CPixmap != 0)
  {
    SDL_FreeSurface( CPixmap);
    CPixmap=NULL;
  }
  Canvas.Destroy();
  CControl::Destroy ();
};

void 
CDraw::SetWidth (uint width)
{
  if(Paint != NULL)
  {
      if (CPixmap != NULL) SDL_FreeSurface( CPixmap);
      CPixmap = SDL_CreateRGBSurfaceWithFormat(0, width, Height, 32, SDL_PIXELFORMAT_RGBA32);
      if (CPixmap == NULL) {
        SDL_Log("SDL_CreateRGBSurfaceWithFormat() failed: %s", SDL_GetError());
        exit(1);
      }

      Canvas.SetDrawIn(CPixmap);
      //pthread_mutex_unlock (&Display_Lock);
  };
  CControl::SetWidth(width);
};

void 
CDraw::SetHeight (uint height)
{
  if(Paint != NULL)
  {
      if (CPixmap != NULL) SDL_FreeSurface( CPixmap);
      CPixmap = SDL_CreateRGBSurfaceWithFormat(0, Width, height, 32, SDL_PIXELFORMAT_RGBA32);
      if (CPixmap == NULL) {
        SDL_Log("SDL_CreateRGBSurfaceWithFormat() failed: %s", SDL_GetError());
        exit(1);
      }
      Canvas.SetDrawIn(CPixmap);
      //pthread_mutex_unlock (&Display_Lock);
  };
  CControl::SetHeight(height);
};
      
void
CDraw::Draw ()
{
	
  if ((!Visible)||(Paint == NULL))return;
  Paint->InitDraw (this);
 
  if(Color.r != BColor.r)
  {
    if(CPixmap != 0)
    {	  
      SDL_FreeSurface(CPixmap);
      CPixmap=NULL;
    };
    BColor=Color;
  };
  
  if (CPixmap == 0)
    {
      Visible=false;	    
      SetPixmapFileName (FileName);
      SetPixmapData (Data);
      Visible=true;	    
      Canvas.SetDrawIn(CPixmap);
      if(!CPixmap)
      {
        CPixmap=SDL_CreateRGBSurfaceWithFormat(0, Width, Height, 32, SDL_PIXELFORMAT_RGBA32);
        Canvas.SetDrawIn(CPixmap);
        Canvas.Pen.SetColor (Color);
	Canvas.Rectangle ( 0, 0, Width, Height);
      };
    };
  
  if (CPixmap != NULL)
    {
     /* 
      if ((Transparent) && (CMask != 0))
      {
        XGCValues gcvalues;
        gcvalues.clip_x_origin = GetRX ();
        gcvalues.clip_y_origin = GetRY ();
        gcvalues.clip_mask = CMask;
        XChangeGC (Win->GetADisplay (), Paint->Agc, GCClipXOrigin | GCClipYOrigin | GCClipMask, &gcvalues);
      };
      * */
      Paint->Rectangle(0, 0, Width, Height);
      Paint->PutPixmap(0,0,Width,Height,CPixmap);
      //XSetClipMask (Win->GetADisplay (), Paint->Agc, None);
    };
 
  Paint->LowerFrame ( 0, 0, Width, Height, Border);
  CControl::Draw ();

};

bool
CDraw::GetTransparent (void)
{
  return Transparent;
};

void
CDraw::SetTransparent (bool transparent)
{
  Transparent = transparent;
};

CStringList CDraw::GetContext (void)
{
  CControl::GetContext ();
  Context.AddLine ("PixmapFileName=" + GetPixmapFileName () + ";File");
  return Context;
};

void
CDraw::SetContext (CStringList context)
{
  Eraser ();
  CControl::SetContext (context);
  for (uint i = 0; i < context.GetLinesCount (); i++)
    {
      String line = Context.GetLine (i);
      String arg;
      eqparse (line, arg);
      if (line.compare ("PixmapFileName") == 0)
      {
	if(arg.size() >  0)
	  SetPixmapFileName (arg);
	else
	  SetPixmapFileName ("");
      };
    };
  Draw ();
};

String
CDraw::GetPixmapFileName (void)
{
  return FileName;
};


bool
CDraw::SetPixmapFileName (String filename)
{
  FileName = filename;
  if (CPixmap != NULL)
    SDL_FreeSurface(CPixmap);
  CPixmap=NULL;
 
  if ((Win) && (FileName.size () > 0))
    {
      int rc = -1;
      
      SDL_Surface* simg=IMG_Load(FileName.c_str());
      CPixmap=SDL_ConvertSurface( simg, SDL_GetWindowSurface(Win->GetWWindow())->format, 0);
      SDL_FreeSurface(simg);
      Canvas.SetDrawIn(CPixmap);
      
      if (rc == 0)
	{
	  Draw ();
	  return true;
	}
      else
	{
	  Message ("Warning: Load pixmap " + FileName + " failed");
	  FileName = "";
          Canvas.SetDrawIn(0);

	  return false;
	};
    };
  return false;
}


bool
CDraw::SetPixmapData (char **data)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  return false;
};

void
CDraw::WritePixmapToFile (String filename)
{
#ifdef HAVE_LIBXPM    
  XpmWriteFileFromPixmap (Win->GetADisplay (), (char *) filename.c_str (),
			  CPixmap, CMask, 0);
#endif

#ifdef HAVE_LIBIMLIB    
  ImlibImage *im;
  ImlibSaveInfo info;
  im = Imlib_create_image_from_drawable(AID,CPixmap , CMask, 0, 0, Width, Height);
  
  if(filename.find(".xpm") > 0)
    Imlib_save_image_to_ppm(AID,im,(char *) filename.c_str () );
  else
    Imlib_save_image(AID, im, (char *) filename.c_str (), &info);
#endif
};


bool 
CDraw::SetImgFileName(String iname)
{
  return SetPixmapFileName (iname);
}
  
bool 
CDraw::SetImgFileName(String filename, float sx, float sy)
{
  FileName = filename;
  if (CPixmap != NULL)
    SDL_FreeSurface(CPixmap);
  CPixmap=NULL;
 
  if ((Win) && (FileName.size () > 0))
    {
      int rc = -1;
      
      CPixmap=IMG_Load(FileName.c_str());
      SDL_Surface* simg=SDL_ConvertSurface( simg, SDL_GetWindowSurface(Win->GetWWindow())->format, 0);
      SDL_FreeSurface(CPixmap);
      
      CPixmap=SDL_CreateRGBSurfaceWithFormat(0, Width, Height, 32, SDL_PIXELFORMAT_RGBA32);
      
              
      SDL_Rect stretchRect; 
      stretchRect.x = 0; 
      stretchRect.y = 0; 
      stretchRect.w = simg->w*sx;
      stretchRect.h = simg->h*sy;
      SDL_BlitScaled( simg, NULL, CPixmap, &stretchRect );
      
      SDL_FreeSurface(simg);
        
      Canvas.SetDrawIn(CPixmap);
      
      if (rc == 0)
	{
	  Draw ();
	  return true;
	}
      else
	{
	  Message ("Warning: Load pixmap " + FileName + " failed");
	  FileName = "";
          Canvas.SetDrawIn(0);

	  return false;
	};
    };
  return false;
}

void 
CDraw::WriteImgToFile (String filename)
{
//FIXME
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}
