#ifndef CWINDOW5
#define CWINDOW5

#include"../include/lxrad.h"

class CWindow5:public CWindow
{
  public:
  /*#Controls*/
  CCheckBox checkbox1;
  CCheckBox checkbox2;
  CButton button1;
  CButton button2;
  CEdit edit1;
  CButton button3;
  CButton button4;
  CEdit edit2;
  CLabel string1;
  CLabel string2;
  CLabel string3;
  CEdit edit3;
  CFileDialog fdialog1;
  /*#Events*/
  void _OnCreate(CControl * control);
  void checkbox1_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void checkbox2_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void button1_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state);
  void button2_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state);
  void button3_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state);
  void button4_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state);
  /*#Others*/
  CWindow5(void);
};

extern CWindow5 Window5;

#endif
