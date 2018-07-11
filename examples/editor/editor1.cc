
#include"editor1.h"
#include"editor1_d.cc"

CWindow1 Window1;

//Implementation

bool fig[100];


void
CWindow1::toolbuttonMouseButtonPress(CControl* control,uint button,uint x,uint y,uint mask)
{
  if(button == 1)
  {
    CToolButton* tbutton;
    tbutton=dynamic_cast<CToolButton*>(control);
    if(fig[tbutton->GetTag()])
    {	  
      tbutton->SetColor("red");
      fig[tbutton->GetTag()]=false;
    }  
    else 
    {	    
      tbutton->SetColor("blue");
      fig[tbutton->GetTag()]=true;
    };
  };
};


void
CWindow1::_OnCreate(CControl * control)
{
  CToolButton* tbutton;
  for(int i=1;i<=100;i++)
  {
    tbutton=dynamic_cast<CToolButton*>(Window1.GetChild(i));
    tbutton->SetColor("red");
    tbutton->SetBorder(0);
    fig[tbutton->GetTag()]=false;
    tbutton->Draw();
  };
};

void
CWindow1::menu1_Limpar_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  CToolButton* tbutton;
  for(int i=1;i<=100;i++)
  {
    tbutton=dynamic_cast<CToolButton*>(Window1.GetChild(i));
    tbutton->SetColor("red");
    fig[tbutton->GetTag()]=false;
    tbutton->Draw();
  };
};

void
CWindow1::menu1_Sobre_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  Message("Desenvolvido por LCGambôa");	
};

void
CWindow1::pmenu1_Abrir_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  char ch;
  FILE* file;
  int c,d,g;
  CToolButton* tbutton;
  if(Window1.abrirdialog.Run())
    {	
    Window1.salvardialog.SetFileName(Window1.abrirdialog.GetFileName());	    
    file=fopen(Window1.abrirdialog.GetFileName().c_str(),"r");
      for(c=0;c<=9;c++)
        {      
        for(d=0;d<=9;d++)
	  {	
          g=(c*10)+d;
          ch=fgetc(file);
          tbutton=dynamic_cast<CToolButton*>(Window1.GetChild(g+1));
          if(ch == '-')
	    {	  
            tbutton->SetColor("blue");
            tbutton->Draw();
            fig[g]=true;
	    }
          else 
	    {	  
            tbutton->SetColor("red");
            tbutton->Draw();
            fig[g]=false;
	    };
          ch=fgetc(file);
	  };
       ch=fgetc(file);
       ch=fgetc(file);
       };
    fclose(file);
  };
};

void
CWindow1::pmenu1_Salvar_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  int c,d,g;
  FILE* file;
  if(Window1.salvardialog.Run())
    {	  
    file = fopen(Window1.salvardialog.GetFileName().c_str(),"w");
      for(c=0;c<= 9;c++)
        {
        for(d=0;d<=9;d++)
	  {	
          g=(c*10)+d;
          if(fig[g])
            fprintf(file,"-1");
          else
            fprintf(file," 1");
	  };
          fprintf(file," \n");
        };
    fclose(file);
  };
};

void
CWindow1::pmenu1_Sair_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  Window1.WDestroy();
};

void
CWindow1::toolbutton1_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton2_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton3_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton4_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton5_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton6_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton7_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton8_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton9_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton10_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton11_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton12_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton13_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton14_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton15_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton16_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton17_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton18_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton19_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton20_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton21_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton22_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton23_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton24_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton25_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton26_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton27_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton28_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton29_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton30_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton31_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton32_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton33_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton34_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton35_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton36_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton37_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton38_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton39_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton40_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton41_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton42_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton43_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton44_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton45_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton46_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton47_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton48_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton49_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton50_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton51_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton52_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton53_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton54_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton55_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton56_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton57_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton58_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton59_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton60_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton61_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton62_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton63_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton64_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton65_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton66_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton67_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton68_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton69_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton70_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton71_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton72_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton73_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton74_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton75_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton76_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton77_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton78_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton79_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton80_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton81_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton82_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton83_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton84_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton85_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton86_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton87_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton88_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton89_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton90_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton91_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton92_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton93_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton94_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton95_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton96_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton97_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton98_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton99_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

void
CWindow1::toolbutton100_MouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  toolbuttonMouseButtonPress(control,button,x,y,state);
};

