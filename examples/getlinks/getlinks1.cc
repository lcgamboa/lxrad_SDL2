
#include"getlinks1.h"
#include"getlinks1_d.cc"

CWindow1 Window1;

//Implementation

void
CWindow1::button1_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state)
{
  if(filedialog1.Run())
  {
  FILE* fin;
  String line1,line2,line3,line4;
  int i,f,s;
  fin=fopen((filedialog1.GetDir()+"/"+filedialog1.GetFileName()).c_str(),"r");
  if(fin)
  {
    i=-1; 	  
    list1.DeleteItens();
    while(fgetline(fin,line1))
    {
      list1.SetVisible(false,false);
      i=line1.find("href=\"");
      if(i <= 0)i=line1.find("HREF=\"");
      if(i <= 0)i=line1.find("Href=\"");
      if(i >= 0)
      {
      line2=line1.substr(i+6,line1.size());
      line3="";
      f=-1; 
      while(f<0)
      {
        f=line2.find("\"");
        if(f<0)
        {
          fgetline(fin,line3);
	  line2+=line3;
	}
      };
      //cout<<"-"<<line2.substr(0,f)<<endl;
      line4="\""+edit1.GetText()+line2.substr(0,f)+"\"";
      s=-1;      
      s=line4.find(" ");
      while(s>=0)
      {
        line4[s]='%';
        line4=line4.substr(0,s+1)+"20"+line4.substr(s+1,line4.size());
        s=line4.find(" ");
      };
      list1.AddItem(line4);
      };
    };
    list1.SetVisible(true);
    list1.Draw();
    fclose(fin);
  };
  };
};

void
CWindow1::button2_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state)
{
  if(filedialog1.Run())
  {
  list1.SaveItensToFile(filedialog1.GetDir()+"/"+filedialog1.GetFileName());
  };  
};

void
CWindow1::button3_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state)
{
    String cmd;	
    String file;
    struct stat statf;
    
    int g,d=0;
    for(int c=0;c < list1.GetItensCount() ;c++)
    {
      if(d >=50)
      {
         Message("More 50?");
	 d=0;
      };	     
      file=list1.GetItem(c);
      g=-1;
      g=file.rfind("/");
      if(g<0)g=0;
      file=file.substr(g+1,file.size()-1);
      
      if((stat(file.c_str(),&statf) == -1)&&(file.size() > 0))
      {
        cmd="xterm -e proz "+list1.GetItem(c)+" &";	    
        //cout<<cmd<<endl;
        system(cmd.c_str());
        d++;
      }
      else
      {
       if(file.size() > 2)printf("%s OK!\n",file.c_str());
      };
    };
};

void
CWindow1::button4_MouseButtonClick(CControl * control, uint button, uint x, uint y,uint state)
{
  list1.DeleteItem(list1.GetSelectedItemN());
};

