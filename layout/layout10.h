#ifndef CSPLASH
#define CSPLASH

#include"../include/lxrad.h"

class CSplash:public CWindow
{
public:
  CDraw draw1;
  CSplash (void);
};

extern CSplash Splash;
#endif
