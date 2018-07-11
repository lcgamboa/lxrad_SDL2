CWindow1::CWindow1(void)
{
  SetFOwner(this);
  SetName("window1");
  SetTag(0);
  SetX(5);
  SetY(51);
  SetWidth(798);
  SetHeight(553);
  SetHint("(null)");
  SetEnable(1);
  SetVisible(1);
  SetPoupMenu(NULL);
  SetTitle("imageview");
  OnCreate=ONCREATE & CWindow1::_OnCreate;
  //pmenu1
  pmenu1.SetFOwner(this);
  pmenu1.SetName("pmenu1");
  pmenu1.SetTag(0);
  pmenu1.SetX(171);
  pmenu1.SetY(74);
  pmenu1.SetWidth(10);
  pmenu1.SetHeight(1);
  pmenu1.SetHint("");
  pmenu1.SetEnable(1);
  pmenu1.SetVisible(1);
  pmenu1.SetMenuItens("Exit,");
  CreateChild(& pmenu1);
  //draw1
  draw1.SetFOwner(this);
  draw1.SetName("draw1");
  draw1.SetTag(0);
  draw1.SetX(175);
  draw1.SetY(33);
  draw1.SetWidth(615);
  draw1.SetHeight(511);
  draw1.SetHint("");
  draw1.SetEnable(1);
  draw1.SetVisible(1);
  draw1.SetPoupMenu(NULL);
  draw1.SetPixmapFileName("");
  CreateChild(& draw1);
  //menu1
  menu1.SetFOwner(this);
  menu1.SetName("menu1");
  menu1.SetTag(0);
  menu1.SetX(0);
  menu1.SetY(0);
  menu1.SetWidth(798);
  menu1.SetHeight(25);
  menu1.SetHint("");
  menu1.SetEnable(1);
  menu1.SetVisible(1);
  menu1.SetMenuItens("File,About,");
  CreateChild(& menu1);
  //menu1_File
  menu1_File.SetFOwner(this);
  menu1_File.SetName("menu1_File");
  menu1_File.SetTag(0);
  menu1_File.SetText("File");
  menu1_File.SetSubMenu(&pmenu1);
  menu1.CreateChild(& menu1_File);
  //menu1_About
  menu1_About.SetFOwner(this);
  menu1_About.SetName("menu1_About");
  menu1_About.SetTag(0);
  menu1_About.SetText("About");
  menu1_About.SetSubMenu(NULL);
  menu1_About.MouseButtonPress=MOUSEBUTTONPRESS & CWindow1::menu1_About_MouseButtonPress;
  menu1.CreateChild(& menu1_About);
  //filelist1
  filelist1.SetFOwner(this);
  filelist1.SetName("filelist1");
  filelist1.SetTag(0);
  filelist1.SetX(6);
  filelist1.SetY(33);
  filelist1.SetWidth(160);
  filelist1.SetHeight(508);
  filelist1.SetHint("");
  filelist1.SetEnable(1);
  filelist1.SetVisible(1);
  filelist1.SetPoupMenu(NULL);
  filelist1.OnFileSelected=ONFILESELECTED & CWindow1::filelist1_OnFileSelected;
  CreateChild(& filelist1);
  //pmenu1_Exit
  pmenu1_Exit.SetFOwner(this);
  pmenu1_Exit.SetName("pmenu1_Exit");
  pmenu1_Exit.SetTag(0);
  pmenu1_Exit.SetText("Exit");
  pmenu1_Exit.SetSubMenu(NULL);
  pmenu1_Exit.MouseButtonPress=MOUSEBUTTONPRESS & CWindow1::pmenu1_Exit_MouseButtonPress;
  pmenu1.CreateChild(& pmenu1_Exit);
};
