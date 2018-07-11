
#include<math.h>
#include"sin1.h"
#include"sin1_d.cc"

CWindow1 Window1;

//Implementation

void
CWindow1::draw1_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  int x1,y1,y2,y2a,c;
  float ic;
  c=0;
  ic=(0.314)*rand()/RAND_MAX;
  x1=0;
  y1=0;				
  y2=0;
  y2a=-200;
  draw1.Canvas.Init();
  draw1.Canvas.SetBgColor(0,0,0);
  draw1.Canvas.Rectangle(1,0,0,draw1.GetWidth(),draw1.GetHeight()); 
  for(int x=0;x<11000;x++)  
  {
    if(x1 >800)
    {
      x1=0;
      y2a+=10;
      draw1.Canvas.End();
  draw1.Canvas.Init();
      c++;
    };
    y1=(int)(100*sin(0.04*x1-c*ic)+105);		
    draw1.Canvas.SetFgColor(255-y2a,2*y2a,y2a);
    draw1.Canvas.SetLineWidth(2);
    draw1.Canvas.Line(x1-5,y2,x1,y1+y2a);
    x1+=5;
    y2=y1+y2a;
  };
  draw1.Canvas.End();
};

