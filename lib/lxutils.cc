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
#include <minizip/zip.h>
#include <minizip/unzip.h>


#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

//-------------------------------------------------------------------------

lxTextFile::lxTextFile ()
{
 f = NULL;
}

int
lxTextFile::Open (String fname)
{
 f = fopen (fname.c_str (), "rw");
 if (f)
  return 1;
 else
  return 0;
}

bool
lxTextFile::IsOpened (void)
{
 if (f)
  return 1;
 else
  return 0;
}

void
lxTextFile::Close (void)
{
 fclose (f);
 f = NULL;
}

void
lxTextFile::GoToLine (int l)
{
 //FIXME	
 fseek (f, l, SEEK_SET);
}

FILE *
lxTextFile::GetFd (void)
{
 return f;
}

lxTextFile::operator FILE*() const
{
 return f;
}

//-------------------------------------------------------------------------

lxImage::lxImage ()
{
 Surface = NULL;
}

lxImage::~lxImage ()
{
 if (Surface)
  SDL_FreeSurface (Surface);
 Surface = NULL;
}

bool
lxImage::LoadFile (String fname)
{
 Surface = IMG_Load (fname.c_str ());
 if (Surface)
  return 1;
 else
  return 0;
}

void
lxImage::Destroy (void)
{
 if (Surface)
  SDL_FreeSurface (Surface);
 Surface = NULL;
}

SDL_Surface*
lxImage::GetImage (void)
{
 return Surface;
}

lxImage::operator SDL_Surface*() const
{
 return Surface;
}

//-------------------------------------------------------------------------

lxBitmap::~lxBitmap ()
{
 if (Texture)
  SDL_DestroyTexture (Texture);
 Texture = NULL;
}

lxBitmap::lxBitmap (SDL_Surface* surf, CPWindow * win)
{
 if (!win->GetVisible () && !win->GetOverWin ())SDL_ShowWindow (win->GetWWindow ());

 SDL_Texture *tim = SDL_CreateTextureFromSurface (win->GetRenderer (), surf);

 Texture = SDL_CreateTexture (win->GetRenderer (), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surf->w, surf->h);

 SDL_SetRenderTarget (win->GetRenderer (), Texture);

 SDL_SetRenderDrawColor (win->GetRenderer (), 0xFF, 0xFF, 0x00, 0xFF);
 SDL_RenderClear (win->GetRenderer ());

 SDL_RenderCopy (win->GetRenderer (), tim, NULL, NULL);
 SDL_DestroyTexture (tim);
 SDL_RenderPresent (win->GetRenderer ());

 SDL_SetRenderTarget (win->GetRenderer (), NULL);

 if (!win->GetVisible () && !win->GetOverWin ())SDL_HideWindow (win->GetWWindow ());

}

SDL_Texture *
lxBitmap::GetPixmap (void)
{
 return Texture;
}


//-------------------------------------------------------------------------

bool
lxSound::Create (String fname)
{
 //FIXME	
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
 return false;
}

void
lxSound::Stop (void)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

void
lxSound::Play (int flags)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}
//-------------------------------------------------------------------------

void
lxFileName::Assign (String fname)
{
 FName = fname;
}

void
lxFileName::MakeAbsolute (void)
{
 char resolved_path[PATH_MAX];
 realpath (FName, resolved_path);
 FName = resolved_path;
}

String
lxFileName::GetFullPath (void)
{
 return FName;
}

//-------------------------------------------------------------------------

lxColor::lxColor () { }

lxColor::lxColor (SDL_Color color)
{
 Color = color;
}

lxColor::lxColor (const char * name)
{
 Color = ColorByName (name);
}

String
lxColor::GetAsString (int flags)
{
  char cname[10];
 
  if(flags ==  lxC2S_HTML_SYNTAX )
  {
    sprintf(cname,"#%02X%02X%02X",Color.r,Color.g,Color.b);
  }
  else
  {
    cname[0]=0;
  }

  return cname;	
}

lxColor::operator
SDL_Color () const
{
 return Color;
}
//-------------------------------------------------------------------------

lxCursor::lxCursor ()
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

lxCursor::lxCursor (int type)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

//-------------------------------------------------------------------------

lxFont::lxFont ()
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

lxFont::lxFont (int size, int family, int style, int weight)
{
#ifdef _DEBUG 
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
#endif
}
//-------------------------------------------------------------------------

void
lxMilliSleep (unsigned int time)
{
 usleep (time * 1000);
}

void
lxSetCursor (lxCursor cursor)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

bool
lxFileExists (String fname)
{
 struct stat sb;

 sb.st_mode = 0;

 stat (fname.c_str (), &sb);

 if (S_ISREG (sb.st_mode))
  return true;
 else
  return false;
}

void
lxExecute (String cmd, unsigned int flags)
{
 cmd += lxT (" &");
 system (cmd.c_str ());
}

String
lxGetCwd (void)
{
 char cwd[1024];
 if (getcwd (cwd, sizeof (cwd)) != NULL)
  return cwd;
 else
  return "";
}


//-------------------------------------------------------------------------

bool
lxUnzipDir (const String &in_filename, const String &out_dirname) {
 
 char fname[1024];
 unzFile uzf =unzOpen (in_filename.c_str ());
 
 if(uzf != NULL)
 {
   if(unzGoToFirstFile(uzf) == UNZ_OK)
    {
     do
      {
      unz_file_info finfo; 
      unzGetCurrentFileInfo(uzf,&finfo,fname,1024,NULL,0,NULL,0);
      
      char *buff= (char *)malloc(finfo.uncompressed_size);
      unzOpenCurrentFile(uzf);
      unzReadCurrentFile(uzf,buff,finfo.uncompressed_size);
      unzCloseCurrentFile(uzf);
      
      String dname=out_dirname;
      dname+=dirname(fname);
      
      if(dname.length () > 0)
       {
        lxCreateDir(dname);
       }
      
      String name=out_dirname;
      name+=fname;
      
      FILE * fout=fopen(name.c_str(),"w");
      if(fout)
       {
        fwrite(buff,finfo.uncompressed_size,1, fout);
        fclose(fout);
       }
      free(buff);
      }
      while(unzGoToNextFile(uzf) == UNZ_OK);
    }
   
   unzClose(uzf);
 }
 
 return 0;
 }

bool
lxZipDir (const String &in_dirname, const String &out_filename)
{
CStringList paths =lxListDirRec(in_dirname);
   
String dname= basename(in_dirname.substr(0,in_dirname.length ()-1));

 if (paths.GetLinesCount () == 0)
  {
   return 1;
  }


 zipFile zf = zipOpen (out_filename.c_str (), APPEND_STATUS_CREATE);
 if (zf == NULL)
  {
   return 1;
  }

 bool _return = true;


 for (size_t i = 0; i < paths.GetLinesCount (); i++)
  {
   FILE * file =fopen(paths.GetLine (i).c_str (), "r");
   if (file)
    {
     fseek (file,0,SEEK_END);
     long size = ftell (file);
     fseek (file, 0, SEEK_SET);

     char * buffer= (char*)malloc(size);
     if (size == 0 || fread (buffer, size,1,file))
      {
       zip_fileinfo zfi = {0};
       String fileName = dname+paths.GetLine (i).substr(in_dirname.length (),paths.GetLine (i).length ()-in_dirname.length ());

       if (0 == zipOpenNewFileInZip (zf, fileName.c_str (), &zfi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION))
        {
         if (zipWriteInFileInZip (zf, size == 0 ? "" : buffer, size))
          _return = false;

         if (zipCloseFileInZip (zf))
          _return = false;

         fclose (file);
         free(buffer);
         continue;
        }
      }
     fclose (file);
    }
   _return = false;
  }

 if (zipClose (zf, NULL))
  return 3;

 if (!_return)
  return 4;
 return 0;
 
}

bool
lxRemoveFile (const char * fname)
{
 return remove (fname);
}

bool
lxRemoveDir (const char* dirname)
{
 DIR *dp;
 struct dirent *dent;
 struct stat sb;
 char fname[1024];

 dp = opendir (dirname);

 if (dp)
  {
   while ((dent = readdir (dp)) != NULL)
    {
     snprintf (fname, 1024, "%s/%s", dirname, dent->d_name);
     stat (fname, &sb);

     if (S_ISREG (sb.st_mode))
      {
       lxRemoveFile (fname);
      }
     else if (S_ISDIR (sb.st_mode))
      {
       if (!(!strcmp (dent->d_name, ".") || !strcmp (dent->d_name, "..")))
        {
         lxRemoveDir (fname);
        }
      }
    }
   closedir (dp);
   return rmdir (dirname);
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

CStringList
lxListDirRec (const String & dirname)
{
 DIR *dp;
 struct dirent *dent;
 struct stat sb;
 char fname[1024];

 CStringList list;

 list.Clear ();

 dp = opendir (dirname);

 if (dp)
  {
   while ((dent = readdir (dp)) != NULL)
    {
     snprintf (fname, 1024, "%s/%s", dirname.c_str(), dent->d_name);
     stat (fname, &sb);

     if (S_ISREG (sb.st_mode))
      {
       list.AddLine (fname);
      }
     else if (S_ISDIR (sb.st_mode))
      {
       if (!(!strcmp (dent->d_name, ".") || !strcmp (dent->d_name, "..")))
        {
          CStringList list2=lxListDirRec (fname);
          for(unsigned int i=0;i<list2.GetLinesCount ();i++)
           {
            list.AddLine (list2.GetLine (i));
           }
        }
      }
    }
   closedir (dp);
  }
 return list;

}

String
lxGetUserDataDir (String appname)
{
 return String ("/home/") + getlogin () + "/." + appname;
}

String
lxGetTempDir (String appname)
{
 return "/tmp/";
}

String
lxGetExecutablePath (String appname)
{
 return "/usr/bin/";
}



// Useful functions_______________________________________________________

void
mprint (String message)
{
 fprintf (stdout, "%s", message.c_str ());
};

void
eprint (String error)
{
 fprintf (stderr, "%s", error.c_str ());
};

SDL_Color
ColorByRGB (unsigned short r, unsigned short g, unsigned short b)
{

 SDL_Color colorA;

 colorA.r = r;
 colorA.g = g;
 colorA.b = b;

 return colorA;
};

SDL_Color
ColorByName (String name)
{
 char cname[10];
 strncpy (cname, name.c_str (), 9);
 SDL_Color colorA;
 if (cname[0] == '#')
  {
   char tmp[3];
   tmp[2] = 0;
   tmp[0] = cname[1];
   tmp[1] = cname[2];
   sscanf (tmp, "%02hhX", &colorA.r);
   tmp[0] = cname[3];
   tmp[1] = cname[4];
   sscanf (tmp, "%02hhX", &colorA.g);
   tmp[0] = cname[5];
   tmp[1] = cname[6];
   sscanf (tmp, "%02hhX", &colorA.b);
  }
 else
  {
   if (!name.Cmp ("gray35"))
    {
     colorA.r = 0x59;
     colorA.g = 0x59;
     colorA.b = 0x59;
     return colorA;
    }
   if (!name.Cmp ("gray59"))
    {
     colorA.r = 0x96;
     colorA.g = 0x96;
     colorA.b = 0x96;
     return colorA;
    }
   if (!name.Cmp ("gray96"))
    {
     colorA.r = 0x60;
     colorA.g = 0x60;
     colorA.b = 0x60;
     return colorA;
    }
   if (!name.Cmp ("gray86"))
    {
     colorA.r = 0xdb;
     colorA.g = 0xdb;
     colorA.b = 0xdb;
     return colorA;
    }
   if (!name.Cmp ("gray82"))
    {
     colorA.r = 0xd1;
     colorA.g = 0xd1;
     colorA.b = 0xd1;
     return colorA;
    }
   if (!name.Cmp ("gray"))
    {
     colorA.r = 0xbe;
     colorA.g = 0xbe;
     colorA.b = 0xbe;
     return colorA;
    }
   if (!name.Cmp ("dark gray"))
    {
     colorA.r = 0xa9;
     colorA.g = 0xa9;
     colorA.b = 0xa9;
     return colorA;
    }
   if (!name.Cmp ("light gray"))
    {
     colorA.r = 0xd3;
     colorA.g = 0xd3;
     colorA.b = 0xd3;
     return colorA;
    }
   if (!name.Cmp ("black"))
    {
     colorA.r = 0x00;
     colorA.g = 0x00;
     colorA.b = 0x00;
     return colorA;
    }
   if (!name.Cmp ("white"))
    {
     colorA.r = 0xff;
     colorA.g = 0xff;
     colorA.b = 0xff;
     return colorA;
    }
   if (!name.Cmp ("blue"))
    {
     colorA.r = 0x00;
     colorA.g = 0x00;
     colorA.b = 0xff;
     return colorA;
    }
   if (!name.Cmp ("red"))
    {
     colorA.r = 0xff;
     colorA.g = 0x00;
     colorA.b = 0x00;
     return colorA;
    }
   if (!name.Cmp ("green"))
    {
     colorA.r = 0x00;
     colorA.g = 0xff;
     colorA.b = 0x00;
     return colorA;
    }
   if (!name.Cmp ("light yellow"))
    {
     colorA.r = 0xfe;
     colorA.g = 0xfe;
     colorA.b = 0xe0;
     return colorA;
    }
   if (!name.Cmp ("dark blue"))
    {
     colorA.r = 0x00;
     colorA.g = 0x00;
     colorA.b = 0x8b;
     return colorA;
    }

   printf ("Color %s not found\n", name.c_str ());
  }
 return colorA;
};


