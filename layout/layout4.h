#ifndef CWINDOW4
#define CWINDOW4

#include"../include/lxrad.h"

class CWindow4:public CWindow
{
public:
  CWindow4 (void);
  void checkboxclick (CControl * control, uint button, uint x, uint y,
		      uint state);
};

extern CWindow4 Window4;

#endif
