#ifndef CWINDOW3
#define CWINDOW3

#include"../include/lxrad.h"

class CWindow3:public CWindow
{
public:
  CFileDialog dialog1;		
  CWindow3 (void);
  void editfocusout (CControl * control);
  void FileMouseButtonRelease (CControl * control, uint button, uint x, uint y,uint state);
};

extern CWindow3 Window3;
#endif
