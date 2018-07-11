CWindow1::CWindow1(void)
{
  SetFOwner(this);
  SetName("window1");
  SetTag(0);
  SetX(5);
  SetY(22);
  SetWidth(210);
  SetHeight(51);
  SetHint("(null)");
  SetEnable(1);
  SetVisible(1);
  SetPoupMenu(NULL);
  SetTitle("multthread");
  OnCreate=ONCREATE & CWindow1::_OnCreate;
  //timer1
  timer1.SetFOwner(this);
  timer1.SetName("timer1");
  timer1.SetTag(0);
  timer1.SetX(104);
  timer1.SetY(55);
  timer1.SetWidth(10);
  timer1.SetHeight(10);
  timer1.SetHint("");
  timer1.SetEnable(1);
  timer1.SetVisible(1);
  timer1.SetPoupMenu(NULL);
  timer1.SetTime(1);
  timer1.SetRunState(1);
  timer1.OnTime=ONTIME & CWindow1::timer1_OnTime;
  CreateChild(& timer1);
  //string1
  string1.SetFOwner(this);
  string1.SetName("string1");
  string1.SetTag(0);
  string1.SetX(13);
  string1.SetY(14);
  string1.SetWidth(183);
  string1.SetHeight(20);
  string1.SetHint("");
  string1.SetEnable(1);
  string1.SetVisible(1);
  string1.SetPoupMenu(NULL);
  string1.SetText("String");
  CreateChild(& string1);
};
