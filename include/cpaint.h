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

#ifndef CPAINT
#define CPAINT

#include"cobject.h"
#include"cpen.h"

class CControl;
class CWindow;

class CPaint:public CObject
{
private:
  CWindow * Win;
  SDL_Texture* DrawIn;
  SDL_Texture* DrawOut;
  CControl *Owner;
  int RX,RY;
  bool DoCalcRXY;
  float Scalex;
  float Scaley;
  int LineWidth;
  int orientation;
  void Rotate(int *x, int *y);
  int Width;
  int Height;
public:
    CPen Pen;
    CPaint (void);
   ~CPaint (void);
  void SetDoCalcRXY(bool docalcrxy); 
  void SetDrawIn(SDL_Texture* drawin);
  void SetDrawOut(SDL_Texture* drawout);
  void InitDraw (CControl * control);
  void DrawControl (CControl * control);
  void Create (CControl * control);
  void Create (CControl * control, lxBitmap* bitmap);
  void Destroy (void);
  void SetFont (CControl * control);
  void SetPen (int function);
  void Point (int x, int y);
  void FillPolygon (SDL_Point * points, int npoints);
  void Line (int x1, int y1, int x2, int y2);
  void Lines (SDL_Point * points, int npoints);
  void Rectangle (int x, int y, int w, int h);
  void Frame (int x, int y, int w, int h, uint wb = 1);
  void LowerFrame (int x, int y, int w, int h, uint wb = 1);
  void RaiserFrame (int x, int y, int w, int h, uint wb = 1);
  void Text (lxString text, int x, int y);
  void RotatedText (lxString str, int x, int y, int angle);
  void ImgText (int x, int y, lxString text);
  void PutPixmap (int x,int y, int w, int h,SDL_Texture* pixmap);
  void PutBitmap (lxBitmap* bitmap,int x,int y);
  void SetBitmap(lxBitmap* bitmap,double xs, double ys);
  void SetFont (lxFont font);
  void TextOnRect (lxString text,lxRect rect,CAlign align);
  void SetLineWidth(int w);
  void Init(void);
  void Init(float sx, float sy, int angle=0);
  void ChangeScale(float sx, float sy);
  void End(void);
  void SetColor(unsigned char r,unsigned char g, unsigned char b); 
  void SetColor(lxColor c); 
  void SetFgColor(unsigned char r,unsigned char g, unsigned char b); 
  void SetBgColor(unsigned char r,unsigned char g, unsigned char b); 
  void SetFgColor(lxString cname); 
  void SetBgColor(lxString cname); 
  void SetFgColor(lxColor c); 
  void SetBgColor(lxColor c); 
  void Rectangle (bool filled, int x, int y, int w, int h);
  void Circle (bool filled, int x, int y, int radius);
  void Polygon(bool filed, lxPoint * points, int npoints);
};

#endif
