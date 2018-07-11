CWindow2::CWindow2 (void)
{	
  SetName ("window1");
  SetX (340);
  SetY (100);
  SetWidth (400);
  SetHeight (400);
  SetTitle ("LXRAD Layout");
  SetVisible(true);
//  SetPixmapBuffer(false);
  SetFOwner (this);
  EvMouseButtonClick = EVMOUSEBUTTONCLICK & CWindow2::Window2MouseButtonClick;
  EvMouseButtonPress = EVMOUSEBUTTONPRESS & CWindow2::GMouseButtonPress;
  EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CWindow2::GMouseButtonRelease;
  EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CWindow2::GMouseButtonRelease;
  EvKeyboardPress = EVKEYBOARDPRESS & CWindow2::GKeyboardPress;
};
