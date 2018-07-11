

#include"layout7.h"
#include"layout7_d.cc"


CWindow7 Window7;

//implemetation

#include"layout2.h"

void  
CWindow7::StringListMouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state)
{
  Window7.cl = dynamic_cast<CList*>(Window2.GetControlOnFocus ());
  Window7.cc = dynamic_cast<CCombo*>(Window2.GetControlOnFocus ());
  
  if(Window7.cl != NULL)
  {	  
    Window7.list1.SetItens(Window7.cl->GetItens());
    Window7.ShowExclusive(); 
  };
  
  if(Window7.cc != NULL)
  {	  
    Window7.list1.SetItens(Window7.cc->GetItens());
    Window7.ShowExclusive(); 
  };
};

void
CWindow7::button1_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state)
{
  String item;
  if(Input("Add String: ",item))
  {
  list1.AddItem(item);
  };
};

void
CWindow7::button2_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state)
{
  list1.DeleteItem(list1.GetSelectedItemN());
};

void
CWindow7::button3_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state)
{
  list1.DeleteItens();
};

void
CWindow7::button4_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state)
{
  HideExclusive(); 
  if(cl)cl->SetItens(list1.GetItens());
  if(cc)cc->SetItens(list1.GetItens());
};


