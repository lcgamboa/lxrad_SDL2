#ifndef CONTROLSDEF
#define CONTROLSDEF
CControl *newcontrol (String controltype, CControl * owner);
void resetcontrolscount (void);
void getbuttons (CControl * owner);
#endif
