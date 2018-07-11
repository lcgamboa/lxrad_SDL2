CWindow5::CWindow5(void)
{
  SetFOwner(this);
  SetName("Project");
  SetX(226);
  SetY(182);
  SetWidth(457);
  SetHeight(222);
  SetTitle("LXRAD Layout");
  SetVisible(false);
  OnCreate= ONCREATE & CWindow5::_OnCreate;
  //checkbox1
  checkbox1.SetFOwner(this);
  checkbox1.SetName("checkbox1");
  checkbox1.SetX(40);
  checkbox1.SetY(21);
  checkbox1.SetWidth(200);
  checkbox1.SetHeight(20);
  checkbox1.EvMouseButtonPress=EVMOUSEBUTTONPRESS & CWindow5::checkbox1_MouseButtonPress;
  checkbox1.SetText("Open an existing Project");
  checkbox1.SetCheck(1);
  CreateChild(&checkbox1);
  //checkbox2
  checkbox2.SetFOwner(this);
  checkbox2.SetName("checkbox2");
  checkbox2.SetX(41);
  checkbox2.SetY(86);
  checkbox2.SetWidth(200);
  checkbox2.SetHeight(20);
  checkbox2.EvMouseButtonPress=EVMOUSEBUTTONPRESS & CWindow5::checkbox2_MouseButtonPress;
  checkbox2.SetText("New Project");
  checkbox2.SetCheck(0);
  CreateChild(&checkbox2);
  //button1
  button1.SetFOwner(this);
  button1.SetName("button1");
  button1.SetX(153);
  button1.SetY(171);
  button1.SetWidth(60);
  button1.SetHeight(20);
  button1.EvMouseButtonClick=EVMOUSEBUTTONCLICK & CWindow5::button1_MouseButtonClick;
  button1.SetText("Ok");
  CreateChild(&button1);
  //button2
  button2.SetFOwner(this);
  button2.SetName("button2");
  button2.SetX(238);
  button2.SetY(171);
  button2.SetWidth(60);
  button2.SetHeight(20);
  button2.EvMouseButtonClick=EVMOUSEBUTTONCLICK & CWindow5::button2_MouseButtonClick;
  button2.SetText("Cancel");
  CreateChild(&button2);
  //edit1
  edit1.SetFOwner(this);
  edit1.SetName("edit1");
  edit1.SetX(155);
  edit1.SetY(44);
  edit1.SetWidth(209);
  edit1.SetHeight(20);
  edit1.SetText("");
  CreateChild(&edit1);
  //button3
  button3.SetFOwner(this);
  button3.SetName("button3");
  button3.SetX(370);
  button3.SetY(44);
  button3.SetWidth(60);
  button3.SetHeight(20);
  button3.EvMouseButtonClick=EVMOUSEBUTTONCLICK & CWindow5::button3_MouseButtonClick;
  button3.SetText("Choose");
  CreateChild(&button3);
  //button4
  button4.SetFOwner(this);
  button4.SetName("button4");
  button4.SetX(370);
  button4.SetY(108);
  button4.SetWidth(60);
  button4.SetHeight(20);
  button4.EvMouseButtonClick=EVMOUSEBUTTONCLICK & CWindow5::button4_MouseButtonClick;
  button4.SetText("Choose");
  button4.SetEnable(false);
  CreateChild(&button4);
  //edit2
  edit2.SetFOwner(this);
  edit2.SetName("edit2");
  edit2.SetX(155);
  edit2.SetY(108);
  edit2.SetWidth(209);
  edit2.SetHeight(20);
  edit2.SetText("");
  edit2.SetEnable(false);
  CreateChild(&edit2);
  //string1
  string1.SetFOwner(this);
  string1.SetName("string1");
  string1.SetX(50);
  string1.SetY(45);
  string1.SetWidth(100);
  string1.SetHeight(20);
  string1.SetText("Project file");
  CreateChild(&string1);
  //string2
  string2.SetFOwner(this);
  string2.SetName("string2");
  string2.SetX(50);
  string2.SetY(108);
  string2.SetWidth(100);
  string2.SetHeight(20);
  string2.SetText("Project Dir");
  CreateChild(&string2);
  //string3
  string3.SetFOwner(this);
  string3.SetName("string3");
  string3.SetX(52);
  string3.SetY(131);
  string3.SetWidth(100);
  string3.SetHeight(20);
  string3.SetText("Project Name");
  CreateChild(&string3);
  //edit3
  edit3.SetFOwner(this);
  edit3.SetName("edit3");
  edit3.SetX(155);
  edit3.SetY(131);
  edit3.SetWidth(209);
  edit3.SetHeight(20);
  edit3.SetText("");
  edit3.SetEnable(false);
  CreateChild(&edit3);
};
