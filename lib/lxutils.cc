/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2018  Luis Claudio Gamboa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */


#include"../include/lxutils.h"
#include"../include/cwindow.h"
#include"../include/capplication.h"
#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>


//-------------------------------------------------------------------------
lxTextFile::lxTextFile()
{
  f=NULL;
}

int 
lxTextFile::Open(String fname)
{
  f=fopen(fname.c_str(),"rw");
  if(f)
   return 1;
  else
   return 0;		  
}
  
bool 
lxTextFile::IsOpened(void)
{
  if(f)
   return 1;
  else
   return 0;		  
}

void 
lxTextFile::Close(void)
{
  fclose(f);
  f=NULL;  
}

void 
lxTextFile::GoToLine(int l)
{
  //FIXME	
  fseek ( f, l, SEEK_SET);
}
  
FILE * 
lxTextFile::GetFd(void)
{
  return f;
}
  
lxTextFile::operator FILE*() const 
{ 
	return f; 
}

//-------------------------------------------------------------------------

	
lxImage::lxImage()
{
  Image=NULL;
}

lxImage::~lxImage()
{
//FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}


bool
lxImage::LoadFile(String fname)
{
//FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  return 0;
}

void
lxImage::Destroy(void)
{
//FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

lxImage::operator Imlib_Image() const
{
  return Image;
}
//-------------------------------------------------------------------------
lxBitmap::lxBitmap()
{
 
    CPixmap =0;
}

lxBitmap::~lxBitmap()
{
//  if (CPixmap != 0)
//    XFreePixmap (Application->GetADisplay (), CPixmap);
}

lxBitmap::lxBitmap(lxImage img)
{
//FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);

}

lxBitmap::operator Pixmap() const 
{ 
  return CPixmap; 
}

Pixmap  
lxBitmap::GetPixmap(void)
{
  return CPixmap;
}


//-------------------------------------------------------------------------

bool
lxSound::Create(String fname)
{
//FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
return false;
}

void
lxSound::Stop(void)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

void 
lxSound::Play(int flags)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}
//-------------------------------------------------------------------------
void 
lxFileName::Assign(String fname)
{
  FName=fname;
}

void
lxFileName::MakeAbsolute(void)
{
    char resolved_path[PATH_MAX]; 
    realpath(FName, resolved_path); 
    FName=resolved_path;
}

String
lxFileName::GetFullPath(void)
{
return FName;
}

//-------------------------------------------------------------------------
lxColor::lxColor()
{
}

lxColor::lxColor(SDL_Color color)
{
  Color=color;
}

lxColor::lxColor(const char * name)
{
    Color=ColorByName(name);
}

String
lxColor::GetAsString(int flags)
{
    //FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  /*
   char cname[20];
   XQueryColor(Application->GetADisplay (), Application->GetAScreen ()->cmap, &Color);

   if(flags ==  lxC2S_HTML_SYNTAX )
   {
     sprintf(cname,"#%02X%02X%02X",Color.red>>8,Color.green>>8,Color.blue>>8);
   }
   else
   {
     cname[0]=0;
   }

   return cname;	

   */
  return "";
}

lxColor::operator SDL_Color() const 
{ 
  return Color; 
}
//-------------------------------------------------------------------------

lxCursor::lxCursor()
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

lxCursor::lxCursor(int type)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

//-------------------------------------------------------------------------

lxFont::lxFont()
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

lxFont::lxFont(int size,int family,int style,int weight)
{
#ifdef _DEBUG	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
#endif
}
//-------------------------------------------------------------------------
void lxMilliSleep(unsigned int time)
{
  usleep(time *1000);
}

void lxSetCursor(lxCursor cursor)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

bool lxFileExists(String fname)
{
  struct stat sb;
  
  sb.st_mode=0; 

  stat(fname.c_str(), &sb);
          
  if(S_ISREG(sb.st_mode))
    return true;
  else
    return false;
}

void lxExecute(String cmd,unsigned int flags)
{
  cmd+=lxT(" &");	
  system(cmd.c_str());
}

String lxGetCwd(void)
{
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL)
     return cwd;
   else
    return "";
}


//-------------------------------------------------------------------------
bool lxUnzipDir(const String &in_filename, const String &out_dirname)
{
  char cmd[1024];	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  //FIXME use library
  
  sprintf(cmd,"unzip %s -d%s\n",in_filename.c_str(),out_dirname.c_str()); 
  
  system(cmd);
 /*	
    bool ret = true;

        wxFileSystem::AddHandler(new wxZipFSHandler);
        wxFileSystem fs;
           
        xauto_ptr<wxZipEntry> entry(new wxZipEntry);
        do {    
            wxFileInputStream in(in_filename);
            if (!in)
            {
                wxLogError(_T("Can not open file '")+in_filename+_T("'."));
                ret = false;
                break;
            }
            wxZipInputStream zip(in);

            //create dirs
            while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
            {
                // access meta-data
                wxString name = entry->GetName();
                
                if(dirname(name).Length() > 0)
                {
                    lxCreateDir(out_dirname+dirname(name));
                }
                
                name = out_dirname + name;

                    
                // read 'zip' to access the entry's data
                if (entry->IsDir())
                {
                    int perm = entry->GetMode();
                    wxFileName::Mkdir(name, perm, wxPATH_MKDIR_FULL);
                }
                else
                {
                    zip.OpenEntry(*entry.get());
                    if (!zip.CanRead())
                    {
                        wxLogError(_T("Can not read zip entry '")+entry->GetName()+_T("'."));
                        ret = false;
                        break;
                    }
                    wxFileOutputStream file(name);
                    if (!file)
                    {
                         wxLogError(_T("Can not create file '")+name+_T("'."));
                         ret = false;
                         break;
                    }
                    zip.Read(file);
                }
                       
            }
        } while(false);
    return ret;
    */
	return 0;
}


bool 
lxZipDir(const String &in_dirname, const String &out_filename)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
/*	
   wxString sep(wxFileName::GetPathSeparator());

   wxArrayString files;

   wxDir::GetAllFiles(in_dirname,&files);//the dir contented all the files need to compress.

   wxFFileOutputStream  fileout(out_filename);

   wxZipOutputStream zipout (fileout);

   wxFFileInputStream *in = NULL;   
   wxZipEntry *entry=NULL;
   wxFileName *zipname = NULL;

   for (size_t i = 0;i != files.GetCount(); ++i)
   {
      if (in!=NULL)
      {
         delete in;
         in = NULL;
      }
      if (zipname!=NULL)
      {
         delete zipname;
         zipname = NULL;
      }

      in = new wxFFileInputStream(files[i]);
      zipname = new wxFileName (files[i]);
      if(zipname->MakeRelativeTo(in_dirname))
      {
         entry =  new wxZipEntry(wxT("picsimlab_workspace/")+zipname->GetFullPath());
         zipout.PutNextEntry(entry);
         zipout.Write(*(in));
      }
      else
      {
         return false;
      }
   }
   zipout.CloseEntry();
   zipout.Close();
   fileout.Close();
   if (in!=NULL)
   {
      delete in;
      in = NULL;
   }
   if (zipname!=NULL)
   {
      delete zipname;
      zipname = NULL;
   }
   */
   return true;
}

bool lxRemoveFile(const char * fname)
{
    return remove(fname);
}

bool lxRemoveDir(const char* dirname)
{	
     DIR  *dp;
     struct dirent *dent;
     struct stat sb;
     char fname[1024];
     
     dp = opendir (dirname);

     if(dp)
     {
       while((dent=readdir(dp))!=NULL)
       {
          snprintf(fname,1024,"%s/%s",dirname,dent->d_name);  
          stat(fname, &sb);
          
          if(S_ISREG(sb.st_mode))
          {
            lxRemoveFile(fname);
          }
          else if(S_ISDIR(sb.st_mode))
          {
            if(!(!strcmp(dent->d_name,".") || !strcmp(dent->d_name,"..")))
            {    
              lxRemoveDir(fname);
            }
          }
       }
       closedir(dp);
       return rmdir(dirname);
     }
   return 0;
}    

bool 
lxCreateDir(const char * dirname)
{
   DIR  *dp; 
   dp = opendir (dirname);

   if(dp)
   {
     return closedir(dp);
   }
   else
   {
#ifndef _WIN_
     return mkdir(dirname, S_IWUSR| S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH ); 
#else     
     return mkdir(dirname);
#endif
   }
   return 0;
}


String 
lxGetUserDataDir(String appname)
{
  return String("/home/")+getlogin()+"/."+appname;
}

String 
lxGetTempDir(String appname)
{
  return "/tmp/";
}

String 
lxGetExecutablePath(String appname)
{
  return "/usr/bin/";
}



// Useful functions_______________________________________________________

void mprint(String message)
{
  fprintf(stdout,"%s",message.c_str());
};

void eprint(String error)
{
  fprintf(stderr,"%s",error.c_str());
};

SDL_Color
ColorByRGB (unsigned short r, unsigned short g, unsigned short b)
{

  SDL_Color colorA;

  colorA.r=r;
  colorA.g=g;
  colorA.b=b;
  
  return colorA;
};

SDL_Color
ColorByName (String name)
{        
  SDL_Color  colorA;
  if(name[0] == '#' )
  {
    char tmp[3];
    tmp[2]=0;
    tmp[0]=name[1];
    tmp[1]=name[2];
    sscanf(tmp,"%02hhX",&colorA.r);
    tmp[0]=name[3];
    tmp[1]=name[4];
    sscanf(tmp,"%02hhX",&colorA.g);
    tmp[0]=name[5];
    tmp[1]=name[6];
    sscanf(tmp,"%02hhX",&colorA.b);
  }	  
  else
  { 
     if(!name.Cmp("gray35"))
     {
         colorA.r=0x59;
         colorA.g=0x59;
         colorA.b=0x59;
         return colorA;
     }
     if(!name.Cmp("gray59"))
     {
         colorA.r=0x96;
         colorA.g=0x96;
         colorA.b=0x96;
         return colorA;
     }
     if(!name.Cmp("gray96"))
     {
         colorA.r=0x60;
         colorA.g=0x60;
         colorA.b=0x60;
         return colorA;
     }
     if(!name.Cmp("gray86"))
     {
         colorA.r=0xdb;
         colorA.g=0xdb;
         colorA.b=0xdb;
         return colorA;
     }
     if(!name.Cmp("gray82"))
     {
         colorA.r=0xd1;
         colorA.g=0xd1;
         colorA.b=0xd1;
         return colorA;
     }
     if(!name.Cmp("gray"))
     {
         colorA.r=0xbe;
         colorA.g=0xbe;
         colorA.b=0xbe;
         return colorA;
     }
     if(!name.Cmp("dark gray"))
     {
         colorA.r=0xa9;
         colorA.g=0xa9;
         colorA.b=0xa9;
         return colorA;
     }
     if(!name.Cmp("light gray"))
     {
         colorA.r=0xd3;
         colorA.g=0xd3;
         colorA.b=0xd3;
         return colorA;
     }     
     if(!name.Cmp("black"))
     {
         colorA.r=0x00;
         colorA.g=0x00;
         colorA.b=0x00;
         return colorA;
     } 
     if(!name.Cmp("white"))
     {
         colorA.r=0xff;
         colorA.g=0xff;
         colorA.b=0xff;
         return colorA;
     } 
     if(!name.Cmp("blue"))
     {
         colorA.r=0x00;
         colorA.g=0x00;
         colorA.b=0xff;
         return colorA;
     } 
     if(!name.Cmp("red"))
     {
         colorA.r=0xff;
         colorA.g=0x00;
         colorA.b=0x00;
         return colorA;
     } 
     if(!name.Cmp("green"))
     {
         colorA.r=0x00;
         colorA.g=0xff;
         colorA.b=0x00;
         return colorA;
     } 
    printf("Color %s not found\n",name.c_str());  
  }
  return colorA;    
};

/*
int
XXLookupString (XIC ic, XKeyPressedEvent * event, char *buffer_return,
		int bytes_buffer, KeySym * keysym_return,
		Status * status_return)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  return 0;
}
*/