/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001  Luis Claudio Gambôa Lopes

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

// CPaint________________________________________________________________


CPaint::CPaint (void)
{
  SetClass ("CPaint");
  RX=0;
  RY=0;
  DrawIn=0;
  DrawOut=0;
  DoCalcRXY=true;
};
  
void 
CPaint::SetDoCalcRXY(bool docalcrxy)
{
  DoCalcRXY=docalcrxy;
};

void 
CPaint::SetDrawIn(Drawable drawin)
{
  DrawIn=drawin;
};

void 
CPaint::SetDrawOut(Drawable drawout)
{
  DrawOut=drawout;
};

CPaint::~CPaint (void)
{
};

void
CPaint::Create (CControl * control)
{
  Win = control->GetWin ();
  Owner = control;
  DrawIn = Win->GetPixmap();
  DrawOut = Win->GetWWindow();
  Agc = XCreateGC (Win->GetADisplay (), Win->GetWWindow (), 0, NULL);
  XSetGraphicsExposures(Win->GetADisplay (), Agc, false);
  Pen.Create (control, &Agc);
};

void
CPaint::Destroy (void)
{
  if (Win)
    XFreeGC (Win->GetADisplay (), Agc);
};

void
CPaint::SetFont (CControl * control)
{
  XGCValues *Gcv;
  Gcv = new XGCValues;
  XFontStruct *PFont = control->GetFont ();
  Gcv->font = PFont->fid;
  XChangeGC (Win->GetADisplay (), Agc, GCFont, Gcv);
  delete Gcv;
};

void
CPaint::InitDraw (CControl * control)
{
  if(DoCalcRXY)
  {	
    control->CalcRXY();
    RX=control->GetRX();
    RY=control->GetRY();
  }
  else
  {
  RX=0;
  RY=0;
  };
  SetFont(control);
};

void
CPaint::DrawControl (CControl * control)
{
  if ((control->GetVisible ())&&
      (DrawIn !=0 )&& 
      (DrawIn != DrawOut))
    {
      if(Owner != Win)
      {
      RX=control->GetRX();
      RY=control->GetRY();
      Pen.SetPen (control->GetPen ());
      XCopyArea (Win->GetADisplay (), DrawIn, DrawOut,
		 Agc, RX, RY, control->GetWidth (), control->GetHeight (),RX, RY);
      Pen.SetPen (GXcopy);
      }
      else
      {
      RX=control->GetRX()-1;
      RY=control->GetRY()-1;
      Pen.SetPen (control->GetPen ());
      XCopyArea (Win->GetADisplay (), DrawIn, DrawOut,
		 Agc, RX, RY, control->GetWidth ()+2, control->GetHeight ()+2,RX, RY);
      Pen.SetPen (GXcopy);
      }
    };
};




void
CPaint::Point (int x, int y)
{
  XDrawPoint (Win->GetADisplay (), DrawIn, Agc, RX+x, RY+y);
};

void
CPaint::FillPolygon (XPoint * points, int npoints)
{
  for(int c=0;c<npoints;c++)
  {
    points[c].x+=RX;	  
    points[c].y+=RY;	  
  }	
  XFillPolygon (Win->GetADisplay (), DrawIn, Agc, points,
		npoints, Nonconvex, CoordModeOrigin);
};

void
CPaint::Line (int x1, int y1, int x2, int y2)
{
  XDrawLine (Win->GetADisplay (), DrawIn, Agc, RX+x1, RY+y1, RX+x2, RY+y2);
};

void
CPaint::Lines (XPoint * points, int npoints)
{
  for(int c=0;c<npoints;c++)
  {
    points[c].x+=RX;	  
    points[c].y+=RY;	  
  }	
  XDrawLines (Win->GetADisplay (), DrawIn, Agc, points,
	      npoints, CoordModeOrigin);
};


void
CPaint::Rectangle (int x, int y, int w, int h)
{
  XFillRectangle (Win->GetADisplay (), DrawIn, Agc, RX+x, RY+y, w, h);
};

void
CPaint::Frame (int x, int y, int w, int h, uint wb)
{
  for (uint c = 0; c < wb; c++)
    XDrawRectangle (Win->GetADisplay (), DrawIn, Agc, RX+x + c,
		    RY+y + c, w - (c * 2), h - (c * 2));
};

void
CPaint::LowerFrame (int x, int y, int w, int h, uint wb)
{
  XColor OldPen;
  for (uint c = 0; c < wb; c++)
    {
      OldPen = Pen.GetColor ();
      Pen.SetColor (ColorByName ("gray35"));
      Line ( x + c, y + c, x + c, h - 2 - c);
      Line ( x + c, y + c, w - c - 1, y + c);
      Pen.SetColor (ColorByName ("gray59"));
      Line ( x + 1 + c, y + 1 + c, x + 1 + c, h - 2 - c);
      Line ( x + 1 + c, y + 1 + c, w - 2 - c, y + 1 + c);
      Pen.SetColor (ColorByName ("gray96"));
      Line ( x + c, h - c - 1, w - c - 1, h - 1 - c);
      Line ( w - 1 - c, y + 1 + c, w - 1 - c, h - c - 1);
      Pen.SetColor (ColorByName ("gray82"));
      Line ( x + 1 + c, h - 2 - c, w - 2 - c, h - 2 - c);
      Line ( w - 2 - c, y + 2 + c, w - 2 - c, h - 2 - c);
      Pen.SetColor (OldPen);
    };
};


void
CPaint::RaiserFrame (int x, int y, int w, int h, uint wb)
{
  XColor OldPen;
  for (uint c = 0; c < wb; c++)
    {
      OldPen = Pen.GetColor ();
      Pen.SetColor (ColorByName ("gray96"));
      Line ( x + c, y + c, x + c, h - 2 - c);
      Line ( x + c, y + c, w - c - 1, y + c);
      Pen.SetColor (ColorByName ("gray86"));
      Line ( x + 1 + c, y + 1 + c, x + 1 + c, h - 3 - c);
      Line ( x + 1 + c, y + 1 + c, w - 2 - c, y + 1 + c);
      Pen.SetColor (ColorByName ("gray35"));
      Line ( x + c, h - 1 - c, w - c - 1, h - 1 - c);
      Line ( w - 1 - c, y + 1 + c, w - 1 - c, h - c - 1);
      Pen.SetColor (ColorByName ("gray59"));
      Line ( x + 1 + c, h - 2 - c, w - 2 - c, h - 2 - c);
      Line ( w - 2 - c, y + 2 + c, w - 2 - c, h - 2 - c);
      Pen.SetColor (OldPen);
    };
};

void
CPaint::Text ( int x1, int y1, String text)
{
  XDrawString (Win->GetADisplay (), DrawIn, Agc, RX+x1, RY+y1,
	       text.c_str (), text.size ());
};


void
CPaint::ImgText ( int x1, int y1, String text)
{
  XDrawImageString (Win->GetADisplay (), DrawIn, Agc, RX+x1, RY+y1,
	       text.c_str (), text.size ());
};
  
void 
CPaint::PutPixmap (int x,int y, int w, int h,Pixmap pixmap)
{
   XCopyArea (Win->GetADisplay (), pixmap, DrawIn ,Agc, 0, 0, w, h, RX+x, RY+y);
};
  
void 
CPaint::SetLineWidth(int w)
{
  Pen.SetWidth (w);
}

void 
CPaint::Init(void)
{
}

void 
CPaint::End(void)
{
  Owner->Draw();	
}

void 
CPaint::SetFgColor(unsigned char r,unsigned char g, unsigned char b)
{
   Pen.SetColor (ColorByRGB(r,g,b));
}

void 
CPaint::SetBgColor(unsigned char r,unsigned char g, unsigned char b)
{
   Pen.SetColor (ColorByRGB(r,g,b));
}

void 
CPaint::Rectangle (bool filled, int x, int y, int w, int h)
{
  if(filled)
    Rectangle ( x, y,  w, h);
  else
    Frame ( x, y, w, h,1);

}

