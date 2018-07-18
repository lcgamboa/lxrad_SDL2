CWindow9::CWindow9(void)
{
  SetFOwner(this);
  SetName("window9");
  SetX(329);
  SetY(178);
  SetWidth(192);
  SetHeight(186);
  SetTitle("layout9");
  SetVisible(false);
  //list1
  list1.SetFOwner(this);
  list1.SetName("list1");
  list1.SetX(16);
  list1.SetY(13);
  list1.SetWidth(160);
  list1.SetHeight(130);
  list1.SetItems("");
  CreateChild(& list1);
  //button1
  button1.SetFOwner(this);
  button1.SetName("button1");
  button1.SetX(24);
  button1.SetY(151);
  button1.SetWidth(60);
  button1.SetHeight(20);
  button1.EvMouseButtonRelease=EVMOUSEBUTTONRELEASE & CWindow9::button1_MouseButtonRelease;
  button1.SetText("Ok");
  CreateChild(& button1);
  //button2
  button2.SetFOwner(this);
  button2.SetName("button2");
  button2.SetX(100);
  button2.SetY(151);
  button2.SetWidth(60);
  button2.SetHeight(20);
  button2.EvMouseButtonRelease=EVMOUSEBUTTONRELEASE & CWindow9::button2_MouseButtonRelease;
  button2.SetText("Cancel");
  CreateChild(& button2);
};
