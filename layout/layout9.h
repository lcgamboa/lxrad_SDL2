#ifndef CWINDOW9 
#define CWINDOW9

#include"../include/lxrad.h"

class CWindow9:public CWindow
{
  public:
  /*#Controls*/
  CList list1;
  CButton button1;
  CButton button2;
  /*#Events*/
  void button1_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void button2_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  /*#Others*/
  void SubMenuMouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  CWindow9(void);
};
 extern CWindow9 Window9 ;

#endif /*#CWINDOW9*/

