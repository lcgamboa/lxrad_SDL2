#ifndef CWINDOW1 
#define CWINDOW1

#include<lxrad/lxrad.h>

class CWindow1:public CWindow
{
  public:
  /*#Controls*/
  CTimer timer1;
  CString string1;
  /*#Events*/
  void _OnCreate(CControl * control);
  void timer1_OnTime(CControl * control);
  /*#Others*/
  CWindow1(void);
};
 extern CWindow1 Window1 ;

#endif /*#CWINDOW1*/

