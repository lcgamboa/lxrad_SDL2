#include"../include/lxrad.h"
#include"layout1.h"
#include"layout2.h"
#include"layout3.h"
#include"layout4.h"
#include"layout5.h"
#include"layout6.h"
#include"layout7.h"
#include"layout8.h"
#include"layout9.h"
#include"layout10.h"


//inclui janela
//Programa________________________________________________________________


Initialize
{
  Application->Start ();
  if (!Application->GetExit ())
    {
      Splash.WCreate ();
      Splash.Draw ();
    };
  
  Application->ACreateWindow (&Window1);
  Application->ACreateWindow (&Window2);
  Application->ACreateWindow (&Window4);
  Application->ACreateWindow (&Window3);
  Application->ACreateWindow (&Window5);
  Application->ACreateWindow (&Window6);
  Application->ACreateWindow (&Window7);
  Application->ACreateWindow (&Window8);
  Application->ACreateWindow (&Window9);

  if (!Application->GetExit ())
    {
      sleep (1);
      Splash.WDestroy ();
    };
  
  Window5.ShowExclusive();
  Application->Load ();

  return 0;
}
