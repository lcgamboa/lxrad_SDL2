CWindow8::CWindow8(void)
{
  SetFOwner(this);
  SetName("window8");
  SetX(318);
  SetY(127);
  SetWidth(227);
  SetHeight(205);
  SetTitle("layout8");
  SetVisible(false);
  //list1
  list1.SetFOwner(this);
  list1.SetName("list1");
  list1.SetX(17);
  list1.SetY(12);
  list1.SetWidth(193);
  list1.SetHeight(130);
  list1.SetItems("");
  CreateChild(& list1);
  //button1
  button1.SetFOwner(this);
  button1.SetName("button1");
  button1.SetX(18);
  button1.SetY(146);
  button1.SetWidth(60);
  button1.SetHeight(20);
  button1.EvMouseButtonRelease=EVMOUSEBUTTONRELEASE & CWindow8::button1_MouseButtonRelease;
  button1.SetText("New");
  CreateChild(& button1);
  //button2
  button2.SetFOwner(this);
  button2.SetName("button2");
  button2.SetX(18);
  button2.SetY(170);
  button2.SetWidth(60);
  button2.SetHeight(20);
  button2.EvMouseButtonRelease=EVMOUSEBUTTONRELEASE & CWindow8::button2_MouseButtonRelease;
  button2.SetText("Delete");
  CreateChild(& button2);
  //button3
  button3.SetFOwner(this);
  button3.SetName("button3");
  button3.SetX(83);
  button3.SetY(146);
  button3.SetWidth(60);
  button3.SetHeight(20);
  button3.EvMouseButtonRelease=EVMOUSEBUTTONRELEASE & CWindow8::button3_MouseButtonRelease;
  button3.SetText("Up");
  CreateChild(& button3);
  //button4
  button4.SetFOwner(this);
  button4.SetName("button4");
  button4.SetX(83);
  button4.SetY(170);
  button4.SetWidth(60);
  button4.SetHeight(20);
  button4.EvMouseButtonRelease=EVMOUSEBUTTONRELEASE & CWindow8::button4_MouseButtonRelease;
  button4.SetText("Down");
  CreateChild(& button4);
  //ton5
  button5.SetFOwner(this);
  button5.SetName("button5");
  button5.SetX(147);
  button5.SetY(146);
  button5.SetWidth(60);
  button5.SetHeight(20);
  button5.EvMouseButtonRelease=EVMOUSEBUTTONRELEASE & CWindow8::button5_MouseButtonRelease;
  button5.SetText("Ok");
  CreateChild(& button5);
  //button6
  button6.SetFOwner(this);
  button6.SetName("button6");
  button6.SetX(148);
  button6.SetY(170);
  button6.SetWidth(60);
  button6.SetHeight(20);
  button6.EvMouseButtonRelease=EVMOUSEBUTTONRELEASE & CWindow8::button6_MouseButtonRelease;
  button6.SetText("Cancel");
  CreateChild(& button6);
};
