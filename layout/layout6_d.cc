CWindow6::CWindow6 (void)
{
  SetName ("window6");
  SetTitle ("Object");
  SetX (10);
  SetY (90);
  SetWidth (210);
  SetHeight (40);
  SetVisible(true);

  //combo1
  combo1.SetName("combo1");
  combo1.SetX(5);
  combo1.SetY(5);
  combo1.SetWidth(200);
  combo1.AddItem("window1");
  combo1.SetSelectedItem("window1");
  combo1.SetFOwner(this);
  combo1.OnComboChange= ONCOMBOCHANGE &CWindow6::oncombochange6;
  CreateChild(&combo1);
};
