
#include"layout9.h"
#include"layout9_d.cc"

CWindow9 Window9;

#include"layout2.h"

//Implementation


void  
CWindow9::SubMenuMouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state)
{	
  CControl *ctrl;	
  if(Window2.GetControlOnFocus () != NULL)
  {	
    Window9.list1.DeleteItens();
    Window9.list1.AddItem("NULL");
    for(int c=0;c <= Window2.GetChildCount();c++)
    {
	ctrl=Window2.GetChild(c);
	if(ctrl->GetClass().compare("CPMenu") == 0)
           Window9.list1.AddItem(ctrl->GetName());
    };
    Window9.ShowExclusive(); 
  };
};


void
CWindow9::button1_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state)
{
  CItemMenu *ctrl=dynamic_cast<CItemMenu*>(Window2.GetControlOnFocus());	
  if(ctrl)
  {
  ctrl->SetSubMenu(dynamic_cast<CPMenu*>(Window2.GetChildByName( Window9.list1.GetSelectedItem()))); 
  }
  else
  {
  Window2.GetControlOnFocus()->SetPopupMenu(dynamic_cast<CPMenu*>(Window2.GetChildByName( Window9.list1.GetSelectedItem()))); 
  }
  
  Window9.HideExclusive(); 
  
  Window2.ListPropierties(Window2.GetControlOnFocus ());
};

void
CWindow9::button2_MouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state)
{
  Window9.HideExclusive(); 
};

