CWindow1::CWindow1 (void)
{
  SetName ("window1");
  SetX (10);
  SetY (10);
  SetWidth (390);
  SetHeight (52);
  SetTitle ("LXRAD Layout");
  SetFOwner(this);
  SetVisible(true);
  EvOnCreate=EVONCREATE & CWindow1::_OnCreate;

//pmenu1
  pmenu1.SetName ("pmenu1");
  pmenuitem1_1.SetText ("New Session");
  pmenuitem1_1.SetName ("New_Session");
  pmenuitem1_1.SetFOwner (this);
  pmenuitem1_1.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::NewMouseButtonPress;
  pmenu1.CreateChild (&pmenuitem1_1);
  pmenuitem1_2.SetText ("New Window");
  pmenuitem1_2.SetName ("New_Window");
  pmenuitem1_2.SetFOwner (this);
  pmenuitem1_2.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::NewWindowMouseButtonPress;
  pmenu1.CreateChild (&pmenuitem1_2);
  pmenuitem1_3.SetText ("Save");
  pmenuitem1_3.SetName ("Save");
  pmenuitem1_3.SetFOwner (this);
  pmenuitem1_3.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::SaveMouseButtonPress;
  pmenu1.CreateChild (&pmenuitem1_3);
  pmenuitem1_5.SetText ("Preferences");
  pmenuitem1_5.SetName ("Preferences");
  pmenuitem1_5.SetFOwner (this);
  pmenuitem1_5.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::PreferencesMouseButtonPress;
  pmenu1.CreateChild (&pmenuitem1_5);
  pmenuitem1_4.SetText ("Exit");
  pmenuitem1_4.SetName ("Exit");
  pmenuitem1_4.SetFOwner (this);
  pmenuitem1_4.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::ExitMouseButtonPress;
  pmenu1.CreateChild (&pmenuitem1_4);
  

//pmenu2
  pmenu2.SetName ("pmenu2");
  pmenuitem2_1.SetText ("Options");
  pmenuitem2_1.SetName ("Options");
  pmenuitem2_1.SetFOwner (this);
  pmenuitem2_1.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::OptionsMouseButtonPress;
  pmenu2.CreateChild (&pmenuitem2_1);
  pmenuitem2_2.SetText ("Clear");
  pmenuitem2_2.SetName ("Clear");
  pmenuitem2_2.SetFOwner (this);
  pmenuitem2_2.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::ClearMouseButtonPress;
  pmenu2.CreateChild (&pmenuitem2_2);
  pmenuitem2_3.SetText ("Delete");
  pmenuitem2_3.SetName ("Delete");
  pmenuitem2_3.SetFOwner (this);
  pmenuitem2_3.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::DeleteMouseButtonPress;
  pmenu2.CreateChild (&pmenuitem2_3);

//pmenu3
  pmenu3.SetName ("pmenu3");

//pmenu4
  pmenu4.SetName ("pmenu4");
  pmenuitem4_1.SetText ("Contents");
  pmenuitem4_1.SetName ("Contents");
  pmenuitem4_1.SetFOwner (this);
  pmenuitem4_1.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::ContentsMouseButtonPress;
  pmenu4.CreateChild (&pmenuitem4_1);
  pmenuitem4_2.SetText ("Reference");
  pmenuitem4_2.SetName ("Reference");
  pmenuitem4_2.SetFOwner (this);
  pmenuitem4_2.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::ReferenceMouseButtonPress;
  pmenu4.CreateChild (&pmenuitem4_2);

//pmenu5
  pmenu5.SetName ("pmenu5");
  pmenuitem5_1.SetText ("Run");
  pmenuitem5_1.SetName ("Run");
  pmenuitem5_1.SetFOwner (this);
  pmenuitem5_1.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::RunMouseButtonPress;
  pmenu5.CreateChild (&pmenuitem5_1);
  pmenuitem5_2.SetText ("Build");
  pmenuitem5_2.SetName ("Build");
  pmenuitem5_2.SetFOwner (this);
  pmenuitem5_2.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::BuildMouseButtonPress;
  pmenu5.CreateChild (&pmenuitem5_2);
  pmenuitem5_3.SetText ("Edit Source");
  pmenuitem5_3.SetName ("Edit_Source");
  pmenuitem5_3.SetFOwner (this);
  pmenuitem5_3.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::SourceMouseButtonPress;
  pmenu5.CreateChild (&pmenuitem5_3);
  pmenuitem5_4.SetText ("Debug");
  pmenuitem5_4.SetName ("Debug");
  pmenuitem5_4.SetFOwner (this);
  pmenuitem5_4.EvMouseButtonPress =
    EVMOUSEBUTTONPRESS & CWindow1::DebugMouseButtonPress;
  pmenu5.CreateChild (&pmenuitem5_4);

//menu1
  menu1.SetName ("menu1");
  CreateChild (&menu1);
  
  menuitem1.SetText ("File");
  menuitem1.SetName ("File");
  menuitem1.SetSubMenu (&pmenu1);
  menu1.CreateChild (&menuitem1);
  
  menuitem2.SetText ("Edit");
  menuitem2.SetName ("Edit");
  menuitem2.SetSubMenu (&pmenu2);
  menu1.CreateChild (&menuitem2);
  
  menuitem5.SetText ("Project");
  menuitem5.SetName ("Project");
  menuitem5.SetSubMenu (&pmenu5);
  menu1.CreateChild (&menuitem5);
  
  menuitem3.SetText ("Windows");
  menuitem3.SetName ("Windows");
  menuitem3.SetSubMenu (&pmenu3);
  menu1.CreateChild (&menuitem3);
  
  menuitem4.SetText ("Help");
  menuitem4.SetName ("Help");
  menuitem4.SetSubMenu (&pmenu4);
  menu1.CreateChild (&menuitem4);

  getbuttons (this);
};
