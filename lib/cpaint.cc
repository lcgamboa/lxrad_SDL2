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

#include"../include/cpaint.h"
#include"../include/cwindow.h"
#include"../include/capplication.h"

// CPaint________________________________________________________________

CPaint::CPaint (void)
{
 SetClass ("CPaint");
 RX = 0;
 RY = 0;
 DrawIn = NULL;
 DrawOut = NULL;
 DoCalcRXY = true;
 Scalex = 1.0;
 Scaley = 1.0;
 LineWidth=1.0;
};

void
CPaint::SetDoCalcRXY (bool docalcrxy)
{
 DoCalcRXY = docalcrxy;
};

void
CPaint::SetDrawIn (SDL_Texture* drawin)
{
 DrawIn = drawin;
};

void
CPaint::SetDrawOut (SDL_Texture* drawout)
{
 DrawOut = drawout;
};

CPaint::~CPaint (void) { };

void
CPaint::Create (CControl * control)
{
 Win = control->GetWin ();
 Owner = control;
 DrawIn = NULL;
 //DrawOut = NULL;
 Pen.Create (control);
};

void
CPaint::Create (CControl * control, lxBitmap *bitmap)
{
 Win = control->GetWin ();
 if (Win == NULL)Win = (CWindow *) control;
 Owner = NULL; //control;
 DrawIn = bitmap->GetPixmap ();
 //DrawOut = bitmap->GetPixmap();
 Pen.Create (control);
}

void
CPaint::Destroy (void) {
 //if (Agc != 0)
 //   XFreeGC (Disp, Agc);
};

void
CPaint::SetFont (CControl * control) {
 /*    
   XGCValues *Gcv;
   Gcv = new XGCValues;
   XFontStruct *PFont = control->GetFont ();
   Gcv->font = PFont->fid;
   XChangeGC (Disp, Agc, GCFont, Gcv);
   delete Gcv;

  */ };

void
CPaint::InitDraw (CControl * control)
{
 if (DoCalcRXY)
  {
   control->CalcRXY ();
   RX = control->GetRX ();
   RY = control->GetRY ();
  }
 else
  {
   RX = 0;
   RY = 0;
  };
 SetFont (control);
};

void
CPaint::DrawControl (CControl * control)
{

 SDL_SetRenderTarget (Win->GetRenderer (), NULL);
 SDL_RenderPresent (Win->GetRenderer ());

};

void
CPaint::Point (int x, int y)
{
 SDL_RenderDrawPoint (Win->GetRenderer (), RX + x, RY + y);
};

void
CPaint::FillPolygon (SDL_Point * points, int npoints)
{
 for (int c = 0; c < npoints; c++)
  {
   points[c].x += RX;
   points[c].y += RY;
  }
 //  XFillPolygon (Disp, DrawIn, Agc, points,
 //		npoints, Nonconvex, CoordModeOrigin);
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
};

void
CPaint::Line (int x1, int y1, int x2, int y2)
{  
  //TODO fix line draw
  float xi,yi,m;
  int xo,yo;
   
  m=sqrt(((x2-x1)*(x2-x1)+((y2-y1)*(y2-y1))));
  xi= fabs(y2-y1)/m;
  yi= (x2-x1)/m;  
     
  for(int i=0;i<LineWidth;i++) 
   {
     xo=xi*(i-(LineWidth/2.0));
     yo=yi*(i-(LineWidth/2.0));
     SDL_RenderDrawLine (Win->GetRenderer (), RX + x1+ xo, RY + y1+yo, RX + x2+xo, RY + y2+yo);
   }
};

void
CPaint::Lines (SDL_Point * points, int npoints)
{
 for (int c = 0; c < npoints; c++)
  {
   points[c].x += RX;
   points[c].y += RY;
  }
 SDL_RenderDrawLines (Win->GetRenderer (), points, npoints);
};

void
CPaint::Rectangle (int x, int y, int w, int h)
{
 SDL_Rect fillRect = {(RX + x) * Scalex, (RY + y) * Scaley, w*Scalex, h * Scaley};
 SDL_RenderFillRect (Win->GetRenderer (), &fillRect);
}

void
CPaint::Frame (int x, int y, int w, int h, uint wb)
{
 for (uint c = 0; c < wb; c++)
  {
   SDL_Rect fillRect = {(RX + x + c) * Scalex, (RY + y + c) * Scaley, (w - (c * 2)) * Scalex, (h - (c * 2)) * Scaley};
   SDL_RenderDrawRect (Win->GetRenderer (), &fillRect);
  }
};

void
CPaint::LowerFrame (int x, int y, int w, int h, uint wb)
{
 SDL_Color OldPen;
 for (uint c = 0; c < wb; c++)
  {
   OldPen = Pen.GetColor ();
   Pen.SetColor (ColorByName ("gray35"));
   Line (x + c, y + c, x + c, h - 2 - c);
   Line (x + c, y + c, w - c - 1, y + c);
   Pen.SetColor (ColorByName ("gray59"));
   Line (x + 1 + c, y + 1 + c, x + 1 + c, h - 2 - c);
   Line (x + 1 + c, y + 1 + c, w - 2 - c, y + 1 + c);
   Pen.SetColor (ColorByName ("gray96"));
   Line (x + c, h - c - 1, w - c - 1, h - 1 - c);
   Line (w - 1 - c, y + 1 + c, w - 1 - c, h - c - 1);
   Pen.SetColor (ColorByName ("gray82"));
   Line (x + 1 + c, h - 2 - c, w - 2 - c, h - 2 - c);
   Line (w - 2 - c, y + 2 + c, w - 2 - c, h - 2 - c);
   Pen.SetColor (OldPen);
  };
};

void
CPaint::RaiserFrame (int x, int y, int w, int h, uint wb)
{
 SDL_Color OldPen;
 for (uint c = 0; c < wb; c++)
  {
   OldPen = Pen.GetColor ();
   Pen.SetColor (ColorByName ("gray96"));
   Line (x + c, y + c, x + c, h - 2 - c);
   Line (x + c, y + c, w - c - 1, y + c);
   Pen.SetColor (ColorByName ("gray86"));
   Line (x + 1 + c, y + 1 + c, x + 1 + c, h - 3 - c);
   Line (x + 1 + c, y + 1 + c, w - 2 - c, y + 1 + c);
   Pen.SetColor (ColorByName ("gray35"));
   Line (x + c, h - 1 - c, w - c - 1, h - 1 - c);
   Line (w - 1 - c, y + 1 + c, w - 1 - c, h - c - 1);
   Pen.SetColor (ColorByName ("gray59"));
   Line (x + 1 + c, h - 2 - c, w - 2 - c, h - 2 - c);
   Line (w - 2 - c, y + 2 + c, w - 2 - c, h - 2 - c);
   Pen.SetColor (OldPen);
  };
};

void
CPaint::Text (String text, int x1, int y1)
{
 if (text.size () == 0)return;
 //Render text surface
 //SDL_Color textColor = { 0, 0, 0 };
 SDL_Surface* textSurface = TTF_RenderText_Blended(Win->GetFont (), text.c_str (), Pen.GetColor ()/*, Pen.GetBGColor ()*/);
 if (textSurface == NULL)
  {
   printf ("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError ());
  }
 else
  {
   //Create texture from surface pixels
   SDL_Texture* mTexture = SDL_CreateTextureFromSurface (Win->GetRenderer (), textSurface);
   if (mTexture == NULL)
    {
     printf ("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError ());
    }
   else
    {
     SDL_Rect DestR;

     SDL_QueryTexture (mTexture, NULL, NULL, &DestR.w, &DestR.h);
     DestR.x = RX + x1;
     DestR.y = RY + y1 ;
     SDL_RenderCopy (Win->GetRenderer (), mTexture, NULL, &DestR);
     SDL_DestroyTexture (mTexture);
    }

   //Get rid of old surface
   SDL_FreeSurface (textSurface);
  }
}

void
CPaint::ImgText (int x1, int y1, String text)
{
 Text (text, x1, y1);
 //  XDrawImageString (Disp, DrawIn, Agc, RX+x1, RY+y1,
 //	       text.c_str (), text.size ());
};

void
CPaint::PutPixmap (int x, int y, int w, int h, SDL_Texture * pixmap)
{
 SDL_Rect DestR;

 DestR.x = RX + x;
 DestR.y = RY + y;
 DestR.w = w;
 DestR.h = h;
 SDL_RenderCopy (Win->GetRenderer (), pixmap, NULL, &DestR);
 SDL_RenderPresent (Win->GetRenderer ());
};

void
CPaint::SetLineWidth (int w) {
 //  Pen.SetWidth (w);
 LineWidth=w;
}

void
CPaint::Init (void)
{
 Scalex = 1.0;
 Scaley = 1.0;
 DrawOut = SDL_GetRenderTarget (Win->GetRenderer ());
 SDL_SetRenderTarget (Win->GetRenderer (), DrawIn);
}

void
CPaint::Init (float sx, float sy)
{
 Scalex = sx;
 Scaley = sy;
 DrawOut = SDL_GetRenderTarget (Win->GetRenderer ());
 SDL_SetRenderTarget (Win->GetRenderer (), DrawIn);
}

void
CPaint::End (void)
{
 SDL_RenderPresent (Win->GetRenderer ());
 SDL_SetRenderTarget (Win->GetRenderer (), NULL);
 if (Owner)
  Owner->Draw ();
 SDL_SetRenderTarget (Win->GetRenderer (), DrawOut);
}

void
CPaint::SetFgColor (unsigned char r, unsigned char g, unsigned char b)
{
 Pen.SetColor (ColorByRGB (r, g, b));
}

void
CPaint::SetFgColor (String cname)
{
 Pen.SetColor (ColorByName (cname));
}

void
CPaint::SetBgColor (unsigned char r, unsigned char g, unsigned char b)
{
 Pen.SetBGColor (ColorByRGB (r, g, b));
}

void
CPaint::SetBgColor (String cname)
{
 Pen.SetBGColor (ColorByName (cname));
}

void
CPaint::Rectangle (bool filled, int x, int y, int w, int h)
{
 if (filled)
  Rectangle (x, y, w, h);
 else
  Frame (x, y, w, h, 1);

}

//FIXME

void
CPaint::RotatedText (String text, int x, int y, int angle)
{
 if (text.size () == 0)return;
 //Render text surface
 //SDL_Color textColor = { 0, 0, 0 };
 SDL_Surface* textSurface = TTF_RenderText_Blended (Win->GetFont (), text.c_str (), Pen.GetColor ());
 if (textSurface == NULL)
  {
   printf ("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError ());
  }
 else
  {
   //Create texture from surface pixels
   SDL_Texture* mTexture = SDL_CreateTextureFromSurface (Win->GetRenderer (), textSurface);
   if (mTexture == NULL)
    {
     printf ("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError ());
    }
   else
    {
     SDL_Rect DestR;
     SDL_Point center;
     
     SDL_QueryTexture (mTexture, NULL, NULL, &DestR.w, &DestR.h);
     DestR.x = RX + x;
     DestR.y = RY + y ;
     
     center.x=0;
     center.y=0;
         
     SDL_RenderCopyEx (Win->GetRenderer (), mTexture, NULL, &DestR,-angle,&center ,SDL_FLIP_NONE);
     SDL_DestroyTexture (mTexture);
    }

   //Get rid of old surface
   SDL_FreeSurface (textSurface);
  }
}

void
CPaint::PutBitmap (lxBitmap* bitmap, int x, int y)
{
 SDL_Rect DestR;

 DestR.x = RX + x;
 DestR.y = RY + y;
 SDL_QueryTexture (bitmap->GetPixmap (), NULL, NULL, &DestR.w, &DestR.h);
 SDL_RenderCopy (Win->GetRenderer (), bitmap->GetPixmap (), NULL, &DestR);
 SDL_RenderPresent (Win->GetRenderer ());
}

void
CPaint::SetBitmap (lxBitmap* bitmap, double xs, double ys)
{
 SDL_Rect DestR;

 SDL_Texture* back = SDL_GetRenderTarget (Win->GetRenderer ());
 SDL_SetRenderTarget (Win->GetRenderer (), DrawIn);
 
 DestR.x = 0;
 DestR.y = 0;
 SDL_QueryTexture (bitmap->GetPixmap (), NULL, NULL, &DestR.w, &DestR.h);
 DestR.w *= xs;
 DestR.h *= ys;
 SDL_RenderCopy (Win->GetRenderer (), bitmap->GetPixmap (), NULL, &DestR);
 SDL_RenderPresent (Win->GetRenderer ());
 
  SDL_SetRenderTarget (Win->GetRenderer (), back);
}

void
CPaint::SetFont (lxFont font)
{
#ifdef _DEBUG 
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
#endif
}

void
CPaint::ChangeScale (float sx, float sy)
{
 Scalex = sx;
 Scaley = sy;
}

void
CPaint::Circle (bool filled, int cx, int cy, int radius)
{
//This function is based in the code of: 
//https://gist.github.com/derofim/912cfc9161269336f722
 if (filled)
  {
   for (double dy = 1; dy <= radius; dy += 1.0)
    {
     double dx = floor (sqrt ((2.0 * radius * dy) - (dy * dy)));
     SDL_RenderDrawLine (Win->GetRenderer (), cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
     SDL_RenderDrawLine (Win->GetRenderer (), cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
    }
  }
 else
  {
   double error = (double) -radius;
   double x = (double) radius - 0.5;
   double y = (double) 0.5;
   cx -= 0.5;
   cy -= 0.5;

   while (x >= y)
    {
     SDL_RenderDrawPoint(Win->GetRenderer (), (int) (cx + x), (int) (cy + y));
     SDL_RenderDrawPoint(Win->GetRenderer (), (int) (cx + y), (int) (cy + x));

     if (x != 0)
      {
       SDL_RenderDrawPoint(Win->GetRenderer (), (int) (cx - x), (int) (cy + y));
       SDL_RenderDrawPoint(Win->GetRenderer (), (int) (cx + y), (int) (cy - x));
      }

     if (y != 0)
      {
       SDL_RenderDrawPoint(Win->GetRenderer (), (int) (cx + x), (int) (cy - y));
       SDL_RenderDrawPoint(Win->GetRenderer (), (int) (cx - y), (int) (cy + x));
      }

     if (x != 0 && y != 0)
      {
       SDL_RenderDrawPoint(Win->GetRenderer (), (int) (cx - x), (int) (cy - y));
       SDL_RenderDrawPoint(Win->GetRenderer (), (int) (cx - y), (int) (cy - x));
      }

     error += y;
     ++y;
     error += y;

     if (error >= 0)
      {
       --x;
       error -= x;
       error -= x;
      }

    }
  }

}

void
CPaint::Polygon (bool filed, lxPoint * points, int npoints)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
 
 for (int c = 0; c < npoints; c++)
  {
   points[c].x += RX;
   points[c].y += RY;
  }
 
 SDL_RenderDrawLines (Win->GetRenderer (), points, npoints);
 
}

void
CPaint::SetColor (unsigned char r, unsigned char g, unsigned char b)
{
 SDL_SetRenderDrawColor (Win->GetRenderer (), r, g, b, 0xFF);
}

void
CPaint::SetFgColor (lxColor c)
{
 SDL_SetRenderDrawColor (Win->GetRenderer (), c.GetR (), c.GetG (), c.GetB (), 0xFF);
}

void
CPaint::SetBgColor (lxColor c)
{
 SDL_SetRenderDrawColor (Win->GetRenderer (), c.GetR (), c.GetG (), c.GetB (), 0xFF);
}

