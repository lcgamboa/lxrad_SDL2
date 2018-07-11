
#include"imageview1.h"
#include"imageview1_d.cc"

CWindow1 Window1;

//Implementation



void
CWindow1::menu1_About_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  Message("Create By LCGambôa");
};

void
CWindow1::filelist1_OnFileSelected(CControl * control)
{ 
  String file=filelist1.GetSelectedFile();

  if((file.find(".gif") >0)||
     (file.find(".jpg") >0)||
     (file.find(".png") >0)||
     (file.find(".tiff")>0)||
     (file.find(".ps")  >0)||
     (file.find(".bmp") >0)||
     (file.find(".xpm") >0)||
     (file.find(".ppm") >0)||
     (file.find(".GIF") >0)||
     (file.find(".JPG") >0)||
     (file.find(".PNG") >0)||
     (file.find(".TIFF")>0)||
     (file.find(".PS")  >0)||
     (file.find(".BMP") >0)||
     (file.find(".XPM") >0)||
     (file.find(".PPM") >0))
     {
        draw1.Eraser();
        draw1.SetPixmapFileName(filelist1.GetSelectedFile());
     };
};

void
CWindow1::pmenu1_Exit_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  WDestroy();
};

void
CWindow1::_OnCreate(CControl * control)
{
  draw1.SetTransparent(true);
};

