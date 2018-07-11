#ifndef CWINDOW1 
#define CWINDOW1

#include<lxrad/lxrad.h>

class CWindow1:public CWindow
{
  public:
  /*#Controls*/
  CDraw draw1;
  /*#Events*/
  void draw1_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  /*#Others*/
  CWindow1(void);
};
 extern CWindow1 Window1 ;

#endif /*#CWINDOW1*/

