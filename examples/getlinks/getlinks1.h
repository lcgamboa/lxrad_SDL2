#ifndef CWINDOW1 
#define CWINDOW1

#include<lxrad/lxrad.h>

class CWindow1:public CWindow
{
  public:
  /*#Controls*/
  CFileDialog filedialog1;
  CList list1;
  CButton button1;
  CButton button2;
  CEdit edit1;
  CString string2;
  CButton button3;
  CButton button4;
  /*#Events*/
  void button1_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state);
  void button2_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state);
  void button3_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state);
  void button4_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state);
  /*#Others*/
  CWindow1(void);
};
 extern CWindow1 Window1 ;

#endif /*#CWINDOW1*/

