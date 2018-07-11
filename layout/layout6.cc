

#include"layout6.h"
#include"layout6_d.cc"

CWindow6 Window6;

//implemetation

#include"layout2.h"

void
CWindow6::oncombochange6(CCombo* combo)
{
  if(combo1.GetSelectedItem().compare(Window2.GetName()) == 0)
  {
    Window2.ListPropierties(&Window2);
    Window2.SetControlOnFocus(NULL);
  }
  else
  {
    CControl* ctrl;	  
    if(combo1.GetSelectedItem().size() > 0) 
      ctrl=Window2.GetChildByName(combo1.GetSelectedItem());	  
    else
      ctrl=&Window2;	  
    Window2.ListPropierties(ctrl);
    Window2.SetControlOnFocus(ctrl);
  };
};

