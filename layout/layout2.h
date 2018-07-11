#ifndef CWINDOW2
#define CWINDOW2

#include"../include/lxrad.h"

class CWindow2:public CWindow
{
public:
  virtual bool WEvents (XEvent WEvent);
  String getalign (CAlign align);
  CControl *NewControl (String cclass, uint x, uint y);
  String WriteEvents (String name, String event);
  String WriteControlEvents (String name, String event);
  CStringList linesbak;
  void Draw(void);
  void Reset (void);
  void MakeList (bool prompt);
  bool testline(String line);
  void MakeProject (String basename);
  bool LoadProject (String dirname, String filename);
  void ListPropierties (CControl * control);
  void SCreateChild(CControl * control);
  void GKeyboardPress (CControl * control, uint key, uint x, uint y,
		       uint mask);
  void Window2MouseButtonClick (CControl * control, uint button, uint x,
				uint y, uint state);
  void GMouseButtonPress (CControl * control, uint button, uint x, uint y,
			  uint state);
  void GMouseButtonRelease (CControl * control, uint button, uint x, uint y,
			    uint state);
  void GMouseMove (CControl * control, uint x, uint y);
  
    CWindow2 (void);
   ~CWindow2 (void);
};

extern CWindow2 Window2;

String space2underline(String str);

#endif
