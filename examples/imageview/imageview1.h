#ifndef CWINDOW1 
#define CWINDOW1

#include<lxrad/lxrad.h>

class CWindow1:public CWindow
{
  public:
  /*#Controls*/
  CPMenu pmenu1;
  CDraw draw1;
  CMenu menu1;
  CItemMenu menu1_File;
  CItemMenu menu1_About;
  CFileList filelist1;
  CItemMenu pmenu1_Exit;
  /*#Events*/
  void _OnCreate(CControl * control);
  void menu1_About_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void filelist1_OnFileSelected(CControl * control);
  void pmenu1_Exit_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  /*#Others*/
  CWindow1(void);
};
 extern CWindow1 Window1 ;

#endif /*#CWINDOW1*/

