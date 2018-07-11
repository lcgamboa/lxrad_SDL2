#ifndef CWINDOW7
#define CWINDOW7

#include"../include/lxrad.h"

class CWindow7:public CWindow
{
  public:
  /*#Controls*/
  CButton button1;
  CButton button2;
  CList list1;
  CButton button3;
  CButton button4;
  /*#Events*/
  void button1_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void button2_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void button3_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void button4_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  /*#Others*/
  CList *cl;
  CCombo *cc;
  CWindow7(void);
  void  StringListMouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
};

extern CWindow7 Window7;

#endif /*#CWINDOW7*/
