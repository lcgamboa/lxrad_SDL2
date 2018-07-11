#ifndef CWINDOW1 
#define CWINDOW1

#include<lxrad/lxrad.h>

class CWindow1:public CWindow
{
  public:
  /*#Controls*/
  CPMenu pmenu1;
  CButton button2;
  CButton button3;
  CButton button4;
  CEdit edit1;
  CEdit edit2;
  CEdit edit3;
  CLabel string1;
  CLabel string2;
  CButton button5;
  CMenu menu1;
  CButton button1;
  CItemMenu pmenu1_Exit;
  CItemMenu menu1_File;
  CItemMenu menu1_About;
  /*#Events*/
  void _MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void button2_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void button3_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void button4_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void button5_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void button1_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void pmenu1_Exit_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void menu1_About_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  /*#Others*/
  CWindow1(void);
};
 extern CWindow1 Window1 ;

#endif /*#CWINDOW1*/

