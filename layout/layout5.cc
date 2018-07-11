
#include"layout1.h"
#include"layout2.h"

#include"layout5.h"
#include"layout5_d.cc"

CWindow5 Window5;


//implemetation
void
CWindow5::_OnCreate(CControl * control)
{
    edit1.SetText(fdialog1.GetDir()+"/untitled.prj_lxrad");
    edit2.SetText(fdialog1.GetDir());
    edit3.SetText("untitled");
};


void
CWindow5::button1_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state)
{
  operation = "editar";
  
  if(checkbox1.GetCheck())
  {
  if (edit1.GetText().size()>0)
    {
      WN = 1;
      Window2.ListPropierties (&Window2);
      Window2.DestroyChilds ();
      Window2.Reset ();
      PDir = fdialog1.GetDir();
      if(! Window2.LoadProject (fdialog1.GetDir (),fdialog1.GetFileName ()))
	  {
	    return;
	  };
      Window1.pmenu3.DestroyChilds ();
      for (int n = 1; n <= PNW; n++)
	{
	  CItemMenu *im;
	  im = new CItemMenu;
	  im->SetText ("Window" + itoa (n));
	  im->SetName ("Window" + itoa (n));
	  im->SetTag (n);
	  im->SetFOwner (this);
	  im->EvMouseButtonPress =
	    EVMOUSEBUTTONPRESS & CWindow1::WindowsMouseButtonPress;
	  Window1.pmenu3.CreateChild (im);
	};
      Save = false;
    }
    else
	{
	Message("Choose one file!");
	return;
	};
  }
  else
  {
    if (edit3.GetText().size()>0)
    {
       if (edit2.GetText().size()>0)
	   {
          WN = 1;
          PNW = 1;
          PName = edit3.GetText();
          PDir = edit2.GetText()+"/"+PName;
          POptions = "-Wall -O5";
          Window1.pmenu3.DestroyChilds ();
          Window2.ListPropierties (&Window2);
          Window2.DestroyChilds ();
          Window2.Reset ();
          Window2.SetName ("window1");
          Window2.SetX (340);
          Window2.SetY (40);
          Window2.SetWidth (400);
          Window2.SetHeight (400);
          Window2.SetTitle (PName);
          if (mkdir (PDir.c_str (), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) !=0)
	      {
	         Message (strerror (errno));
			 return;
	      };
		  Window2.MakeList(false);
		  Save = true;
	   }
	   else
	   {
	      Message("Write Project Name!");
	      return;
	   };
	}
    else
	{
	   Message("Choose one dir!");
	   return;
	};
  }; 
  HideExclusive();
};

void
CWindow5::button2_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state)
{
  HideExclusive();		
  Window1.WDestroy ();
};

void
CWindow5::button3_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state)
{
  if(fdialog1.Run())
  {
    edit1.SetText(fdialog1.GetDir()+"/"+fdialog1.GetFileName());
  };
};

void
CWindow5::button4_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state)
{
  if(fdialog1.Run())
  {
    edit2.SetText(fdialog1.GetDir());
  };
};


void
CWindow5::checkbox1_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  checkbox2.SetCheck(!checkbox1.GetCheck());
  
  if(checkbox1.GetCheck())
  {
  button3.SetEnable(true);
  button4.SetEnable(false);
  edit1.SetEnable(true);
  edit2.SetEnable(false);
  edit3.SetEnable(false);
  }
  else
  {
  button3.SetEnable(false);
  button4.SetEnable(true);
  edit1.SetEnable(false);
  edit2.SetEnable(true);
  edit3.SetEnable(true);
  }
};

void
CWindow5::checkbox2_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  checkbox1.SetCheck(!checkbox2.GetCheck());
  
  if(checkbox2.GetCheck())
  {
  button3.SetEnable(false);
  button4.SetEnable(true);
  edit1.SetEnable(false);
  edit2.SetEnable(true);
  edit3.SetEnable(true);
  }
  else
  {
  button3.SetEnable(true);
  button4.SetEnable(false);
  edit1.SetEnable(true);
  edit2.SetEnable(false);
  edit3.SetEnable(false);
  }
};
