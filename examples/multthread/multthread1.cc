
#include"multthread1.h"
#include"multthread1_d.cc"


CWindow1 Window1;

//Implementation

#include<time.h>


void
CWindow1::timer1_OnTime(CControl * control)
{
  time_t t;
  t=time(NULL);
  string1.SetText(ctime(&t));
};

void
CWindow1::_OnCreate(CControl * control)
{
  time_t t;
  t=time(NULL);
  string1.SetText(ctime(&t));
};

