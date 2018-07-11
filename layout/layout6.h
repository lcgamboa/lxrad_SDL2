#ifndef CWINDOW6
#define CWINDOW6

#include"../include/lxrad.h"

class CWindow6:public CWindow
{
public:
  CCombo combo1;
  CWindow6 (void);
  void oncombochange6(CCombo* combo);
};

extern CWindow6 Window6;

#endif
