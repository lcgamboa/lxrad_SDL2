#ifndef CWINDOW8 
#define CWINDOW8

#include"../include/lxrad.h"

class CWindow8:public CWindow
{
  public:
  /*#Controls*/
  CList list1;
  CButton button1;
  CButton button2;
  CButton button3;
  CButton button4;
  CButton button5;
  CButton button6;
  /*#Events*/
  void button1_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void button2_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void button3_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void button4_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void button5_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void button6_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  /*#Others*/
  CMenu *menu;
  CPMenu *pmenu;
  void MenuItensMouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  CWindow8(void);
};
 extern CWindow8 Window8 ;

#endif /*#CWINDOW8*/

