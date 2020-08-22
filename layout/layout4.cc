

#include"layout4.h"
#include"layout4_d.cc"

CWindow4 Window4;
//implemetation

#include"layout2.h"

void
CWindow4::checkboxclick (CControl * control, uint button, uint x, uint y,
			 uint state)
{
  lxStringList List;
  CCheckBox *cb;
  if (Window2.GetControlOnFocus () == NULL)
    return;
  for (int c = 0; c <= Window4.GetChildCount (); c++)
    {
      cb = (CCheckBox *) (Window4.GetChild (c));
      List.AddLine (cb->GetText () + "=" + btoa (cb->GetCheck ()));
    };
  dynamic_cast<CObject *>(Window2.GetControlOnFocus ())->SetContext (List);
};

