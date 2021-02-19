/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2020  Luis Claudio Gamboa Lopes

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

#include<SDL2_gfxPrimitives.h>
#include"third/SDL2_gfx_extra.h"

// CPaint________________________________________________________________

CPaint::CPaint(void)
{
 SetClass ("CPaint");
 RX = 0;
 RY = 0;
 DrawIn = NULL;
 DrawOut = NULL;
 DoCalcRXY = true;
 Scalex = 1.0;
 Scaley = 1.0;
 LineWidth = 1.0;
 orientation = 0;
}

void
CPaint::SetDoCalcRXY(bool docalcrxy)
{
 DoCalcRXY = docalcrxy;
}

void
CPaint::SetDrawIn(SDL_Texture* drawin)
{
 DrawIn = drawin;
}

void
CPaint::SetDrawOut(SDL_Texture* drawout)
{
 DrawOut = drawout;
}

CPaint::~CPaint(void) { }

void
CPaint::Create(CControl * control)
{
 Win = control->GetWin ();
 Owner = control;
 DrawIn = NULL;
 //DrawOut = NULL;
 Pen.Create (control);
}

void
CPaint::Create(CControl * control, lxBitmap *bitmap)
{
 Win = control->GetWin ();
 if (Win == NULL)Win = (CWindow *) control;
 Owner = NULL; //control;
 DrawIn = bitmap->GetPixmap ();
 //DrawOut = bitmap->GetPixmap();
 Pen.Create (control);
 Width = bitmap->GetWidth ();
 Height = bitmap->GetHeight ();
}

void
CPaint::Destroy(void) {
 //if (Agc != 0)
 //   XFreeGC (Disp, Agc);
}

void
CPaint::SetFont(CControl * control) {
 /*    
   XGCValues *Gcv;
   Gcv = new XGCValues;
   XFontStruct *PFont = control->GetFont ();
   Gcv->font = PFont->fid;
   XChangeGC (Disp, Agc, GCFont, Gcv);
   delete Gcv;

  */ }

void
CPaint::InitDraw(CControl * control)
{
 Init ();
#ifdef _ONEWIN   
 SDL_Rect wrec;
 wrec.x = Win->GetX ();
 wrec.y = Win->GetY ();
 wrec.w = Win->GetWidth ();
 wrec.h = Win->GetHeight () + 20;
 SDL_RenderSetClipRect (Win->GetRenderer (), &wrec);
#endif  
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
  }
 SetFont (control);
}

void
CPaint::DrawControl(CControl * control)
{
 SDL_Texture* last = SDL_GetRenderTarget (Win->GetRenderer ());
 SDL_SetRenderTarget (Win->GetRenderer (), NULL);
 Win->SetRedraw ();
 SDL_SetRenderTarget (Win->GetRenderer (), last);
}

void
CPaint::Point(int x, int y)
{
 Rotate (&x, &y);
 SDL_RenderDrawPoint (Win->GetRenderer (), RX + x, RY + y);
}

void
CPaint::FillPolygon(SDL_Point * points, int npoints)
{
 for (int c = 0; c < npoints; c++)
  {
   points[c].x += RX;
   points[c].y += RY;
  }
 //  XFillPolygon (Disp, DrawIn, Agc, points,
 //		npoints, Nonconvex, CoordModeOrigin);
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

void
CPaint::Line(int x1, int y1, int x2, int y2)
{
 Rotate (&x1, &y1);
 Rotate (&x2, &y2);
 if (LineWidth == 1)
  {
   SDL_RenderDrawLine (Win->GetRenderer (), RX + x1, RY + y1, RX + x2, RY + y2);
  }
 else
  {
     SDL_Color color = Pen.GetFgColor ();
     
     thickLineRGBA (Win->GetRenderer (),RX+x1, RY+y1, RX+x2, RY+y2, Pen.GetWidth (), color.r, color.g, color.b, 0xFF);
     filledCircleRGBA (Win->GetRenderer (), RX+x1, RY+y1, Pen.GetWidth()/2.0, color.r, color.g, color.b, 0xFF);
     filledCircleRGBA (Win->GetRenderer (), RX+x2, RY+y2, Pen.GetWidth()/2.0, color.r, color.g, color.b, 0xFF);
   /*
   SDL_Rect DestR;
   SDL_Point center;
   float a, m;

   m = sqrt (((x2 - x1)*(x2 - x1)+((y2 - y1)*(y2 - y1))));
   a = 180 / M_PI * atan2 ((y2 - y1), (x2 - x1));


   SDL_Texture* line = SDL_CreateTexture (Win->GetRenderer (), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m, LineWidth);
   SDL_SetRenderTarget (Win->GetRenderer (), line);
   SDL_RenderClear (Win->GetRenderer ());
   SDL_SetRenderTarget (Win->GetRenderer (), DrawIn);

   DestR.w = m + LineWidth / 2;
   DestR.h = LineWidth;
   DestR.x = RX + x1 - LineWidth / 2;
   DestR.y = RY + y1 - LineWidth / 2;

   center.x = LineWidth / 2;
   center.y = LineWidth / 2;

   SDL_RenderCopyEx (Win->GetRenderer (), line, NULL, &DestR, a, &center, SDL_FLIP_NONE);
   SDL_DestroyTexture (line);
   */
  }
}

void
CPaint::Lines(SDL_Point * points, int npoints)
{
 for (int c = 0; c < npoints; c++)
  {
   points[c].x += RX;
   points[c].y += RY;
  }
 if (Pen.GetWidth() == 1)
  {
   SDL_RenderDrawLines (Win->GetRenderer (), points, npoints);
  }
 else
  {
   SDL_Color color = Pen.GetFgColor ();

   for (int i = 0; i < npoints - 1; i++)
    {
     thickLineRGBA (Win->GetRenderer (),points[i].x, points[i].y, points[i+1].x, points[i+1].y, Pen.GetWidth (), color.r, color.g, color.b, 0xFF);
     filledCircleRGBA (Win->GetRenderer (), points[i].x, points[i].y, Pen.GetWidth()/2.0, color.r, color.g, color.b, 0xFF);
     filledCircleRGBA (Win->GetRenderer (), points[i+1].x, points[i+1].y, Pen.GetWidth()/2.0, color.r, color.g, color.b, 0xFF);
    }
  }
}

void
CPaint::Rectangle(int x, int y, int w, int h)
{
 int x2, y2;
 x2 = x + w;
 y2 = y + h;
 Rotate (&x, &y);
 Rotate (&x2, &y2);
 SDL_Rect fillRect = {(int) ((RX + x) * Scalex), (int) ((RY + y) * Scaley), (int) ((x2 - x) * Scalex), (int) ((y2 - y) * Scaley)};
 SDL_RenderFillRect (Win->GetRenderer (), &fillRect);
}

void
CPaint::Frame(int x, int y, int w, int h, uint wb)
{
 for (uint c = 0; c < wb; c++)
  {
   SDL_Rect fillRect = {(int) ((RX + x + c) * Scalex), (int) ((RY + y + c) * Scaley), (int) ((w - (c * 2)) * Scalex), (int) ((h - (c * 2)) * Scaley)};
   SDL_RenderDrawRect (Win->GetRenderer (), &fillRect);
  }
}

void
CPaint::LowerFrame(int x, int y, int w, int h, uint wb)
{
 SDL_Color OldPen;
 for (uint c = 0; c < wb; c++)
  {
   OldPen = Pen.GetFgColor ();
   Pen.SetFgColor (ColorByName ("gray35"));
   Line (x + c, y + c, x + c, h - 2 - c);
   Line (x + c, y + c, w - c - 1, y + c);
   Pen.SetFgColor (ColorByName ("gray59"));
   Line (x + 1 + c, y + 1 + c, x + 1 + c, h - 2 - c);
   Line (x + 1 + c, y + 1 + c, w - 2 - c, y + 1 + c);
   Pen.SetFgColor (ColorByName ("gray96"));
   Line (x + c, h - c - 1, w - c - 1, h - 1 - c);
   Line (w - 1 - c, y + 1 + c, w - 1 - c, h - c - 1);
   Pen.SetFgColor (ColorByName ("gray82"));
   Line (x + 1 + c, h - 2 - c, w - 2 - c, h - 2 - c);
   Line (w - 2 - c, y + 2 + c, w - 2 - c, h - 2 - c);
   Pen.SetFgColor (OldPen);
  }
}

void
CPaint::RaiserFrame(int x, int y, int w, int h, uint wb)
{
 SDL_Color OldPen;
 for (uint c = 0; c < wb; c++)
  {
   OldPen = Pen.GetFgColor ();
   Pen.SetFgColor (ColorByName ("gray96"));
   Line (x + c, y + c, x + c, h - 2 - c);
   Line (x + c, y + c, w - c - 1, y + c);
   Pen.SetFgColor (ColorByName ("gray86"));
   Line (x + 1 + c, y + 1 + c, x + 1 + c, h - 3 - c);
   Line (x + 1 + c, y + 1 + c, w - 2 - c, y + 1 + c);
   Pen.SetFgColor (ColorByName ("gray35"));
   Line (x + c, h - 1 - c, w - c - 1, h - 1 - c);
   Line (w - 1 - c, y + 1 + c, w - 1 - c, h - c - 1);
   Pen.SetFgColor (ColorByName ("gray59"));
   Line (x + 1 + c, h - 2 - c, w - 2 - c, h - 2 - c);
   Line (w - 2 - c, y + 2 + c, w - 2 - c, h - 2 - c);
   Pen.SetFgColor (OldPen);
  }
}

void
CPaint::Text(lxString text, int x1, int y1)
{
 if (text.size () == 0)return;
 //Render text surface
 //SDL_Color textColor = { 0, 0, 0 }
 SDL_Surface* textSurface = TTF_RenderText_Blended (Win->GetFont (), text.c_str (), Pen.GetFgColor ()/*, Pen.GetBGColor ()*/);
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
     DestR.y = RY + y1;
     SDL_RenderCopy (Win->GetRenderer (), mTexture, NULL, &DestR);
     SDL_DestroyTexture (mTexture);
    }

   //Get rid of old surface
   SDL_FreeSurface (textSurface);
  }
}

void
CPaint::TextOnRect(lxString text, lxRect rect, CAlign align)
{
 Text (text, rect.x, rect.y);
}

void
CPaint::ImgText(int x1, int y1, lxString text)
{
 Text (text, x1, y1);
 //  XDrawImagelxString (Disp, DrawIn, Agc, RX+x1, RY+y1,
 //	       text.c_str (), text.size ());
}

void
CPaint::PutPixmap(int x, int y, int w, int h, SDL_Texture * pixmap)
{
 SDL_Rect DestR;

 DestR.x = RX + x;
 DestR.y = RY + y;
 DestR.w = w;
 DestR.h = h;
 SDL_RenderCopy (Win->GetRenderer (), pixmap, NULL, &DestR);
 //if (SDL_GetRenderTarget (Win->GetRenderer ()))
 //SDL_RenderPresent (Win->GetRenderer ());
}

void
CPaint::SetLineWidth(int w)
{
 Pen.SetWidth (w);
 LineWidth = w;
}

void
CPaint::Init(void)
{
 Scalex = 1.0;
 Scaley = 1.0;
 DrawOut = SDL_GetRenderTarget (Win->GetRenderer ());
 SDL_SetRenderTarget (Win->GetRenderer (), DrawIn);

 orientation = 0;
 //printf("%s Init render=%p last=%p\n", Win->GetName ().c_str (), DrawIn, DrawOut);
}

void
CPaint::Init(float sx, float sy, int _orientation)
{
 Scalex = sx;
 Scaley = sy;
 DrawOut = SDL_GetRenderTarget (Win->GetRenderer ());
 SDL_SetRenderTarget (Win->GetRenderer (), DrawIn);

 orientation = _orientation;
 //printf("%s Init render=%p last=%p\n",Win->GetName ().c_str () ,  DrawIn, DrawOut);
}

void
CPaint::End(void)
{
 // if (SDL_GetRenderTarget (Win->GetRenderer ()))
 //  SDL_RenderPresent (Win->GetRenderer ());
 /*
  SDL_SetRenderTarget (Win->GetRenderer (), NULL);
  if (Owner)
   Owner->Draw ();
  */
 //SDL_Texture* last = SDL_GetRenderTarget (Win->GetRenderer ());
 SDL_SetRenderTarget (Win->GetRenderer (), DrawOut);

 //printf("%s End  render=%p last=%p\n", Win->GetName ().c_str (), DrawIn, last);

 Win->SetRedraw ();
}

void
CPaint::SetFgColor(unsigned char r, unsigned char g, unsigned char b)
{
 Pen.SetFgColor (ColorByRGB (r, g, b));
}

void
CPaint::SetFgColor(lxString cname)
{
 Pen.SetFgColor (ColorByName (cname));
}

void
CPaint::SetBgColor(unsigned char r, unsigned char g, unsigned char b)
{
 Pen.SetBgColor (ColorByRGB (r, g, b));
}

void
CPaint::SetBgColor(lxString cname)
{
 Pen.SetBgColor (ColorByName (cname));
}

void
CPaint::Rectangle(bool filled, int x, int y, int w, int h)
{
 if (filled)
  {
   lxColor old = Pen.GetFgColor ();
   Pen.SetFgColor (Pen.GetBgColor ());
   Rectangle (x, y, w, h);
   Pen.SetFgColor (old);
  }

 Frame (x, y, w, h, Pen.GetWidth ());

}

//FIXME

void
CPaint::RotatedText(lxString text, int x, int y, int _angle)
{
 Rotate (&x, &y);
 switch (orientation)
  {
  case 1:
   _angle += -90;
   break;
  case 2:
   _angle += 180;
   break;
  case 3:
   _angle += 90;
   break;
  default:
   break;
  }
 if (text.size () == 0)return;
 //Render text surface
 //SDL_Color textColor = { 0, 0, 0 }
 SDL_Surface* textSurface = TTF_RenderText_Blended (Win->GetFont (), text.c_str (), Pen.GetFgColor ());
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
     DestR.y = RY + y;

     center.x = 0;
     center.y = 0;

     SDL_RenderCopyEx (Win->GetRenderer (), mTexture, NULL, &DestR, -_angle, &center, SDL_FLIP_NONE);
     SDL_DestroyTexture (mTexture);
    }

   //Get rid of old surface
   SDL_FreeSurface (textSurface);
  }
}

void
CPaint::PutBitmap(lxBitmap* bitmap, int x, int y)
{
 SDL_Rect DestR;

 Rotate (&x, &y);
 switch (orientation)
  {
  case 1:
   x -= bitmap->GetWidth ();
   break;
  case 2:
   x -= bitmap->GetWidth ();
   y -= bitmap->GetHeight ();
   break;
  case 3:
   y -= bitmap->GetHeight ();
   break;
  }

 DestR.x = (RX + x) * Scalex;
 DestR.y = (RY + y) * Scaley;
 SDL_QueryTexture (bitmap->GetPixmap (), NULL, NULL, &DestR.w, &DestR.h);
 DestR.w *= Scalex;
 DestR.h *= Scaley;
 SDL_RenderCopy (Win->GetRenderer (), bitmap->GetPixmap (), NULL, &DestR);
 //if (SDL_GetRenderTarget (Win->GetRenderer ()))
 //SDL_RenderPresent (Win->GetRenderer ());
}

void
CPaint::SetBitmap(lxBitmap* bitmap, double xs, double ys)
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
 //SDL_RenderPresent (Win->GetRenderer ());

 SDL_SetRenderTarget (Win->GetRenderer (), back);
}

void
CPaint::SetFont(lxFont font) {
 //#ifdef _DEBUG 
 // printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
 //#endif
}

void
CPaint::ChangeScale(float sx, float sy)
{
 Scalex = sx;
 Scaley = sy;
}

void
CPaint::Circle(bool filled, int cx, int cy, int radius)
{
 Rotate (&cx, &cy);
 cx = (RX + cx) * Scalex;
 cy = (RY + cy) * Scaley;
 radius = radius * Scalex;


 if (filled)
  {
   SDL_Color color = Pen.GetBgColor ();
   filledCircleRGBA (Win->GetRenderer (), cx, cy, radius, color.r, color.g, color.b, 0xFF);
  }
 SDL_Color color = Pen.GetFgColor ();
 if (Pen.GetWidth () <= 1)
  {
   circleRGBA (Win->GetRenderer (), cx, cy, radius, color.r, color.g, color.b, 0xFF);
  }
 else
  {
   thickCircleRGBA(Win->GetRenderer (), cx, cy, radius , color.r, color.g, color.b, 0xFF, Pen.GetWidth ());
  }

 /*
 //This function is based in the code of: 
 //https://gist.github.com/derofim/912cfc9161269336f722
 if (filled)
 {
 lxColor old = Pen.GetFgColor();
 Pen.SetFgColor(Pen.GetBgColor());
 for (double dy = 1; dy <= radius; dy += 1.0)
 {
 double dx = floor (sqrt ((2.0 * radius * dy) - (dy * dy)));
 SDL_RenderDrawLine (Win->GetRenderer (), cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
 SDL_RenderDrawLine (Win->GetRenderer (), cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
 }
 Pen.SetFgColor(old);
 }
 double error = (double) -radius;
 double x = (double) radius - 0.5;
 double y = (double) 0.5;
 cx -= 0.5;
 cy -= 0.5;

 while (x >= y)
 {
 SDL_RenderDrawPoint (Win->GetRenderer (), (int) (cx + x), (int) (cy + y));
 SDL_RenderDrawPoint (Win->GetRenderer (), (int) (cx + y), (int) (cy + x));

 if (x != 0)
 {
 SDL_RenderDrawPoint (Win->GetRenderer (), (int) (cx - x), (int) (cy + y));
 SDL_RenderDrawPoint (Win->GetRenderer (), (int) (cx + y), (int) (cy - x));
 }

 if (y != 0)
 {
 SDL_RenderDrawPoint (Win->GetRenderer (), (int) (cx + x), (int) (cy - y));
 SDL_RenderDrawPoint (Win->GetRenderer (), (int) (cx - y), (int) (cy + x));
 }

 if (x != 0 && y != 0)
 {
 SDL_RenderDrawPoint (Win->GetRenderer (), (int) (cx - x), (int) (cy - y));
 SDL_RenderDrawPoint (Win->GetRenderer (), (int) (cx - y), (int) (cy - x));
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
  */
}

void
CPaint::Polygon(bool filled, lxPoint * points, int npoints)
{
 // printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);

 for (int c = 0; c < npoints; c++)
  {
   points[c].x += RX;
   points[c].y += RY;
  }

 short vx[2048];
 short vy[2048];

 if (npoints > 2048) npoints = 2048;

 for (int p = 0; p < npoints; p++)
  {
   vx[p] = points[p].x;
   vy[p] = points[p].y;
  }


 if (filled)
  {

   SDL_Color color = Pen.GetBgColor ();
   filledPolygonRGBA (Win->GetRenderer (), vx, vy, npoints, color.r, color.g, color.b, 0xFF);
   /*   
   // Sort the points so that y0 <= y1 <= y2
   if (points[1].y < points[0].y)
   {
   lxPoint temp = points[1];
   points[1] = points[0];
   points[0] = temp;
   }
   if (points[2].y < points[0].y)
   {
   lxPoint temp = points[2];
   points[2] = points[0];
   points[0] = temp;
   }
   if (points[2].y < points[1].y)
   {
   lxPoint temp = points[2];
   points[2] = points[1];
   points[1] = temp;
   }

   // Compute the x coordinates of the triangle edges
   //x01 = Interpolate(point[0].y, point[0].x, point[1].y, point[1].x);
   int yX01 = points[1].y - points[0].y;
   int xX01 = points[1].x - points[0].x;
   float dx = xX01 / ((float) yX01);
   int X01[100]; //fixme 
   for (int i = 0; i < yX01; i++)
   {
   X01[i] = points[0].x + (dx*i+0.5);
   }
   //x12 = Interpolate(point[1].y, point[1].x, point[2].y, point[2].x);
   int yX12 = points[2].y - points[1].y;
   int xX12 = points[2].x - points[1].x;
   dx = xX12 / ((float) yX12);
   int X12[100]; //fixme 
   for (int i = 0; i < yX12; i++)
   {
   X12[i] = points[1].x + (dx*i+0.5);
   }
   //x02 = Interpolate(point[0].y, point[0].x, point[2].y, point[2].x);
   int yX02 = points[2].y - points[0].y;
   int xX02 = points[2].x - points[0].x;
   dx = xX02 / ((float) yX02);
   int X02[2048]; //fixme 
   for (int i = 0; i < yX02; i++)
   {
   X02[i] = points[0].x + (dx*i+0.5);
   }

   // Concatenate the short sides
   //remove_last(x01)
   //yX01--;
   //x012 = x01 + x12
   int yX012 = yX01 + yX12;
   int X012[2048]; //fixme
   for (int i = 0; i < yX01; i++)
   X012[i] = X01[i];
   for (int i = 0; i < yX12; i++)
   X012[i + yX01] = X12[i];

   // Determine which is left and which is right
   //m = x012.length / 2
   int m = yX012 / 2;

   int * x_left;
   int * x_right;

   if (X02[m] < X012[m])
   {
   x_left = X02;
   x_right = X012;
   }
   else
   {
   x_left = X012;
   x_right = X02;
   }

   // Draw the horizontal segments
   for (int y = points[0].y; y < points[2].y; y++)
   {
   for (int x = x_left[y - points[0].y]; x < x_right[y - points[0].y]; x++)
   {
   SDL_RenderDrawPoint (Win->GetRenderer (), x, y);
   }
   }
    */
  }

 SDL_Color color = Pen.GetFgColor ();
 if (Pen.GetWidth () <= 1)
  {
   polygonRGBA (Win->GetRenderer (), vx, vy, npoints, color.r, color.g, color.b, 0xFF);
  }
 else
  {
   for (int i = 0; i < npoints - 1; i++)
    {
     thickLineRGBA (Win->GetRenderer (), vx[i], vy[i], vx[i + 1], vy[i + 1], Pen.GetWidth (), color.r, color.g, color.b, 0xFF);
     
     filledCircleRGBA (Win->GetRenderer (), vx[i+1], vy[i+1], Pen.GetWidth()/2.0, color.r, color.g, color.b, 0xFF);
    }
  }
 //SDL_RenderDrawLines (Win->GetRenderer (), points, npoints);
 //SDL_RenderDrawLine(Win->GetRenderer (),points[0].x,points[0].y,points[npoints-1].x,points[npoints-1].y);



}

void
CPaint::SetColor(unsigned char r, unsigned char g, unsigned char b)
{

 Pen.SetFgColor (ColorByRGB (r, g, b));
 Pen.SetBgColor (ColorByRGB (r, g, b));
}

void
CPaint::SetFgColor(lxColor c)
{

 Pen.SetFgColor (c);
}

void
CPaint::SetBgColor(lxColor c)
{

 Pen.SetBgColor (c);
}

void
CPaint::SetColor(lxColor c)
{

 Pen.SetFgColor (c);
 Pen.SetBgColor (c);
}

void
CPaint::Rotate(int *x, int *y)
{
 int ox = *x;
 int oy = *y;

 switch (orientation)
  {
  case 1:
   *x = Width - oy;
   *y = ox;
   break;
  case 2:
   *x = Width - ox;
   *y = Height - oy;
   break;
  case 3:
   *x = oy;
   *y = Height - ox;
   break;
  default:
   break;
  }

}

