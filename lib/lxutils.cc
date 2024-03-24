/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001-2021  Luis Claudio Gamboa Lopes

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

#include <iostream>
#include <cstring>
#include"../../lunasvg/include/lunasvg.h"

using namespace lunasvg;

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

//-------------------------------------------------------------------------

lxTextFile::lxTextFile()
{
 f = NULL;
}

int
lxTextFile::Create(lxString fname)
{
 fn = fname;
 f = fopen (fname.c_str (), "rw");
 if (f)
  return 1;
 else
  return 0;
}

int
lxTextFile::Open(lxString fname)
{
 fn = fname;
 f = fopen (fname.c_str (), "rw");
 if (f)
  return 1;
 else
  return 0;
}

bool
lxTextFile::IsOpened(void)
{
 if (f)
  return 1;
 else
  return 0;
}

void
lxTextFile::Close(void)
{
 fclose (f);
 f = NULL;
}

void
lxTextFile::GoToLine(int l)
{
 //FIXME	
 fseek (f, l, SEEK_SET);
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

void
lxTextFile::Clear(void)
{
 if (f) fclose (f);
 f = fopen (fn.c_str (), "w");
 if (f) fclose (f);
 f = fopen (fn.c_str (), "rw");
}

void
lxTextFile::AddLine(lxString line)
{
 fprintf (f, "%s\n", line.c_str ());
}

//-------------------------------------------------------------------------

lxImage::lxImage(CPWindow * win)
{
 Win = win;
 Texture = NULL;
}

lxImage::~lxImage()
{
 if (Texture)
  SDL_DestroyTexture (Texture);
 Texture = NULL;
}

unsigned int
lxImage::GetWidth(void)
{
 int w, h;
 SDL_QueryTexture (Texture, NULL, NULL, &w, &h);

 return w;
}

unsigned int
lxImage::GetHeight(void)
{
 int w, h;
 SDL_QueryTexture (Texture, NULL, NULL, &w, &h);

 return h;
}

bool
lxImage::LoadFile(const lxString fname, int orientation, float scalex, float scaley, int useAlpha, double * ret_sx, double * ret_sy)
{
 Destroy ();
 
 scalex*=Application->GetGlobalScale ();
 scaley*=Application->GetGlobalScale ();

 if (fname.Contains (".svg"))
  {
   int width;
   int height;
   unsigned int bgrcolor;

   auto document = Document::loadFromFile (std::string (fname.c_str ()));

   if (document)
    {
     width = document->width () * scalex;
     height = document->height () * scaley;


     if (ret_sx)
      *ret_sx = ((double) width/Application->GetGlobalScale ()) / document->width ();

     if (ret_sy)
      *ret_sy = ((double) height/Application->GetGlobalScale ()) / document->height ();

     if(useAlpha){
    	bgrcolor = 0;
     }
     else{
	    lxColor backgrd =  SystemColor(lxCOLOR_BTNFACE);
        bgrcolor = (backgrd.Red()<<24) | (backgrd.Blue()<<16) | (backgrd.Green()<<8)| backgrd.Alpha();  
	 }
	 
	 auto bitmap = document->renderToBitmap (width, height, bgrcolor);
     bitmap.convertToRGBA();

     SDL_Surface * Surface = SDL_CreateRGBSurfaceFrom ((void *) bitmap.data (),
                                                       bitmap.width (),
                                                       bitmap.height (),
                                                       32,
                                                       4 * bitmap.width (),
                                                       0x000000FF,
                                                       0x0000FF00,
                                                       0x00FF0000,
                                                       0xFF000000);

     SDL_Texture * mTexture = SDL_CreateTextureFromSurface (Win->GetRenderer (), Surface);

     SDL_Rect DestR;
     int sw=0, sh=0;
     SDL_QueryTexture (mTexture, NULL, NULL, &DestR.w, &DestR.h);

     switch (orientation)
      {
      case 0:
      case 2:
       sw = DestR.w;
       sh = DestR.h;
       DestR.x = 0;
       DestR.y = 0;
       break;
      case 1:
      case 3:
       sw = DestR.h;
       sh = DestR.w;
       DestR.y = (DestR.w - DestR.h) / 2;
       DestR.x = (DestR.h - DestR.w) / 2;
       break;
      }

     Texture = SDL_CreateTexture (Win->GetRenderer (), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sw, sh);

     SDL_Texture* last = SDL_GetRenderTarget (Win->GetRenderer ());
     SDL_SetRenderTarget (Win->GetRenderer (), Texture);

     //SDL_SetRenderDrawColor (Win->GetRenderer (), 0xFF, 0xFF, 0xFF, 0x00);
     //SDL_RenderClear (Win->GetRenderer ());

     SDL_RenderCopyEx (Win->GetRenderer (), mTexture, NULL, &DestR, orientation * 90, NULL, SDL_FLIP_NONE);

     SDL_DestroyTexture (mTexture);

     SDL_RenderPresent (Win->GetRenderer ());

     SDL_SetRenderTarget (Win->GetRenderer (), last);

     SDL_FreeSurface (Surface);

     return 1;
    }

  }
 else //png
  {
   SDL_Surface * Surface = IMG_Load (fname.c_str ());

   if (Surface)
    {
     SDL_Texture * mTexture = SDL_CreateTextureFromSurface (Win->GetRenderer (), Surface);


     SDL_Rect DestR;
     int sw=0, sh=0;
     SDL_QueryTexture (mTexture, NULL, NULL, &DestR.w, &DestR.h);

     DestR.w *= scalex;
     DestR.h *= scaley;

     switch (orientation)
      {
      case 0:
      case 2:
       sw = DestR.w;
       sh = DestR.h;
       DestR.x = 0;
       DestR.y = 0;
       break;
      case 1:
      case 3:
       sw = DestR.h;
       sh = DestR.w;
       DestR.y = (DestR.w - DestR.h) / 2;
       DestR.x = (DestR.h - DestR.w) / 2;
       break;
      }

     Texture = SDL_CreateTexture (Win->GetRenderer (), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sw, sh);

     SDL_Texture* last = SDL_GetRenderTarget (Win->GetRenderer ());
     SDL_SetRenderTarget (Win->GetRenderer (), Texture);


     //SDL_SetRenderDrawColor (Win->GetRenderer (), 0xFF, 0xFF, 0xFF, 0x00);
     //SDL_RenderClear (Win->GetRenderer ());

     SDL_RenderCopyEx (Win->GetRenderer (), mTexture, NULL, &DestR, orientation * 90, NULL, SDL_FLIP_NONE);

     SDL_DestroyTexture (mTexture);

     SDL_RenderPresent (Win->GetRenderer ());

     SDL_SetRenderTarget (Win->GetRenderer (), last);

     SDL_FreeSurface (Surface);

     return 1;
    }
  }

 return 0;

}

bool 
lxImage::CreateBlank(const unsigned int width, const unsigned int height, int orientation, double scalex, double  scaley ){
     SDL_Surface * Surface = SDL_CreateRGBSurface (    0,
                                                       width * scalex,
                                                       height * scaley,
                                                       32,
                                                       0x000000FF,
                                                       0x0000FF00,
                                                       0x00FF0000,
                                                       0xFF000000);

     SDL_Texture * mTexture = SDL_CreateTextureFromSurface (Win->GetRenderer (), Surface);

     SDL_Rect DestR;
     int sw=0, sh=0;
     SDL_QueryTexture (mTexture, NULL, NULL, &DestR.w, &DestR.h);

     switch (orientation)
      {
      case 0:
      case 2:
       sw = DestR.w;
       sh = DestR.h;
       DestR.x = 0;
       DestR.y = 0;
       break;
      case 1:
      case 3:
       sw = DestR.h;
       sh = DestR.w;
       DestR.y = (DestR.w - DestR.h) / 2;
       DestR.x = (DestR.h - DestR.w) / 2;
       break;
      }

     Texture = SDL_CreateTexture (Win->GetRenderer (), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sw, sh);

     SDL_Texture* last = SDL_GetRenderTarget (Win->GetRenderer ());
     SDL_SetRenderTarget (Win->GetRenderer (), Texture);

     //SDL_SetRenderDrawColor (Win->GetRenderer (), 0xFF, 0xFF, 0xFF, 0x00);
     //SDL_RenderClear (Win->GetRenderer ());

     SDL_RenderCopyEx (Win->GetRenderer (), mTexture, NULL, &DestR, orientation * 90, NULL, SDL_FLIP_NONE);

     SDL_DestroyTexture (mTexture);

     SDL_RenderPresent (Win->GetRenderer ());

     SDL_SetRenderTarget (Win->GetRenderer (), last);

     SDL_FreeSurface (Surface);

     return 1;	
}

void
lxImage::Destroy(void)
{
 if (Texture)
  SDL_DestroyTexture (Texture);
 Texture = NULL;
}

SDL_Texture*
lxImage::GetImage(void)
{
 return Texture;
}

lxImage::operator SDL_Texture*() const
{
 return Texture;
}

//-------------------------------------------------------------------------

lxBitmap::~lxBitmap()
{
 if (Texture)
  SDL_DestroyTexture (Texture);
 Texture = NULL;
}

lxBitmap::lxBitmap(lxImage * surf, CPWindow * win)
{
 if (!win->GetVisible () && !win->GetOverWin ())SDL_ShowWindow (win->GetWWindow ());

 SDL_Texture *tim = *surf;

 Texture = SDL_CreateTexture (win->GetRenderer (), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surf->GetWidth (), surf->GetHeight ());

 SDL_Texture* last = SDL_GetRenderTarget (win->GetRenderer ());
 SDL_SetRenderTarget (win->GetRenderer (), Texture);

 //SDL_SetRenderDrawColor (win->GetRenderer (), 0xFF, 0xFF, 0xFF, 0x00);
 //SDL_RenderClear (win->GetRenderer ());

 SDL_RenderCopy (win->GetRenderer (), tim, NULL, NULL);
 SDL_DestroyTexture (tim);
 //SDL_RenderPresent (win->GetRenderer ());

 SDL_SetRenderTarget (win->GetRenderer (), last);

 if (!win->GetVisible () && !win->GetOverWin ())SDL_HideWindow (win->GetWWindow ());

}

lxBitmap::lxBitmap(SDL_Texture* _Texture)
{
 Texture = _Texture;
}

lxBitmap::lxBitmap(int width, int height)
{
 //Texture = SDL_CreateTexture (win->GetRenderer (), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

SDL_Texture *
lxBitmap::GetPixmap(void)
{
 return Texture;
}

lxSize
lxBitmap::GetSize(void)
{
 lxSize t;
 int w, h;
 SDL_QueryTexture (Texture, NULL, NULL, &w, &h);

 t.SetWidth (w);
 t.SetHeight (h);
 return t;
}

unsigned int
lxBitmap::GetWidth(void)
{
 int w, h;
 SDL_QueryTexture (Texture, NULL, NULL, &w, &h);

 return w;
}

unsigned int
lxBitmap::GetHeight(void)
{
 int w, h;
 SDL_QueryTexture (Texture, NULL, NULL, &w, &h);

 return h;
}
//-------------------------------------------------------------------------

bool
lxSound::Create(lxString fname)
{
 //FIXME	
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
 return false;
}

void
lxSound::Stop(void) {
 //FIXME: sound stop incomplete
 //printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}

void
lxSound::Play(int flags)
{
 printf ("Incomplete: %s -> %s :%i\n", __func__, __FILE__, __LINE__);
}
//-------------------------------------------------------------------------

void
lxFileName::Assign(lxString fname)
{
 FName = fname;
}

void
lxFileName::MakeAbsolute(void)
{
 char resolved_path[PATH_MAX];
 realpath (FName, resolved_path);
 FName = resolved_path;
}

lxString
lxFileName::GetFullPath(void)
{
 return FName;
}

//-------------------------------------------------------------------------

lxColor::lxColor() { }

lxColor::lxColor(SDL_Color color)
{
 Color = color;
}

lxColor::lxColor(const char * name)
{
 Color = ColorByName (name);
}

lxColor::lxColor(unsigned char r, unsigned char g, unsigned char b)
{
 Color = ColorByRGB (r, g, b);
}

lxString
lxColor::GetAsString(int flags)
{
 char cname[10];

 if (flags == lxC2S_HTML_SYNTAX)
  {
   sprintf (cname, "#%02X%02X%02X", Color.r, Color.g, Color.b);
  }
 else
  {
   cname[0] = 0;
  }

 return cname;
}

lxColor::operator
SDL_Color() const
{
 return Color;
}

void
lxColor::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
{
 Color = ColorByRGB (r, g, b);
}

lxColor SystemColor(int id)
{
   switch(id){
     case lxCOLOR_WINDOWTEXT:
        return lxColor(0, 0, 0);
        break;
     case lxCOLOR_BTNFACE:
        return ColorByName ("light gray");
        break; 
   }
   return lxColor(0, 0, 0);
}

//-------------------------------------------------------------------------

lxCursor::lxCursor(int type)
{
 cursor = SDL_CreateSystemCursor ((SDL_SystemCursor) type);
}

lxCursor::~lxCursor()
{
 free (cursor);
}

SDL_Cursor*
lxCursor::GetSDLCursor(void)
{
 return cursor;
}

//-------------------------------------------------------------------------

lxFont::lxFont()
{

 Size = 12;
 Family = lxFONTFAMILY_DEFAULT;
 Style = lxFONTSTYLE_NORMAL;
 Weight = lxFONTWEIGHT_NORMAL;

 font = Application->GetFont (Size, Family, Style, Weight);

}

lxFont::lxFont(int size, int family, int style, int weight)
{
 Size = size;
 Family = family;
 Style = style;
 Weight = weight;

 font = Application->GetFont (Size, Family, Style, Weight);
}

TTF_Font *
lxFont::GetTTFFont(void)
{
 return font;
}

int
lxFont::GetPointSize(void)
{
 return Size;
}

void
lxFont::SetPointSize(int size)
{
 Size = size;
 font = Application->GetFont (Size, Family, Style, Weight);
}

int
lxFont::GetFamily(void)
{
 return Family;
}

void
lxFont::SetFamily(int family)
{
 Family = family;
 font = Application->GetFont (Size, Family, Style, Weight);
}

int
lxFont::GetStyle(void)
{
 return Style;
}

void
lxFont::SetStyle(int style)
{
 Style = style;
 font = Application->GetFont (Size, Family, Style, Weight);
}

int
lxFont::GetWeight(void)
{
 return Weight;
}

void
lxFont::SetWeight(int weight)
{
 Weight = weight;
 font = Application->GetFont (Size, Family, Style, Weight);
}


//-------------------------------------------------------------------------

void
lxMilliSleep(unsigned int time)
{
 usleep (time * 1000);
}

void
lxSetCursor(lxCursor cursor)
{
 SDL_SetCursor (cursor.GetSDLCursor ());
}

bool
lxFileExists(lxString fname)
{
 struct stat sb;

 sb.st_mode = 0;

 stat (fname.c_str (), &sb);

 if (S_ISREG (sb.st_mode))
  return true;
 else
  return false;
}

int 
lxExecute(lxString cmd, unsigned int flags, void * arg)
{
 if (flags != lxEXEC_SYNC)
  cmd += lxT (" &");
 return system (cmd.c_str ());
}

lxString
lxGetCwd(void)
{
 char cwd[1024];
 if (getcwd (cwd, sizeof (cwd)) != NULL)
  return cwd;
 else
  return "";
}

int
lxSetWorkingDirectory(lxString dir)
{
 return chdir (dir.c_str ());
}

bool
lxLaunchDefaultBrowser(lxString url)
{
#ifdef __EMSCRIPTEN__

 const char * isf = strstr (url.c_str (), "file://");

 printf ("Opening url: %s \n", url.c_str ());

 if (isf)
  {
   printf ("Opening file: %s \n", url.c_str () + 7);
   EM_ASM_ ({
            var url = UTF8ToString ($0);
            var contents = FS.readFile (url,
    { encoding : 'utf8'});
            var winex = window.open ("example.html", "examples");
            winex.document.write (contents);
            winex.document.close ();
   }, url.c_str () + 7);
  }
 else
  {
   EM_ASM_ ({
            var link = UTF8ToString ($0);
            window.open (link);
   }, url.c_str ());
  }
 return true;
#else 
 lxString cmd = lxT ("xdg-open ") + url + lxT ("  &");
 return system (cmd.c_str ());
#endif
}

bool
lxLaunchDefaultApplication(lxString cmd)
{
 lxString cmd_ = lxT ("xdg-open ") + cmd + lxT ("  &");
 return system (cmd_.c_str ());
}

//-------------------------------------------------------------------------

bool
lxUnzipDir(const lxString &in_filename, const lxString &out_dirname)
{

 char fname[1024];
 unzFile uzf = unzOpen (in_filename.c_str ());

 if (uzf != NULL)
  {
   if (unzGoToFirstFile (uzf) == UNZ_OK)
    {
     do
      {
       unz_file_info finfo;
       unzGetCurrentFileInfo (uzf, &finfo, fname, 1024, NULL, 0, NULL, 0);

       char *buff = (char *) malloc (finfo.uncompressed_size);
       unzOpenCurrentFile (uzf);
       unzReadCurrentFile (uzf, buff, finfo.uncompressed_size);
       unzCloseCurrentFile (uzf);

       lxString dname = out_dirname;
       dname += dirname (fname);

       if (dname.length () > 0)
        {
         lxCreateDir (dname);
        }

       lxString name = out_dirname;
       name += fname;

       FILE * fout = fopen (name.c_str (), "w");
       if (fout)
        {
         fwrite (buff, finfo.uncompressed_size, 1, fout);
         fclose (fout);
        }
       free (buff);
      }
     while (unzGoToNextFile (uzf) == UNZ_OK);
    }

   unzClose (uzf);
  }

 return 0;
}

bool
lxZipDir(const lxString &in_dirname, const lxString &out_filename)
{
 lxStringList paths = lxListDirRec (in_dirname);

 lxString dname = basename (in_dirname.substr (0, in_dirname.length () - 1));

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
   FILE * file = fopen (paths.GetLine (i).c_str (), "r");
   if (file)
    {
     fseek (file, 0, SEEK_END);
     long size = ftell (file);
     fseek (file, 0, SEEK_SET);

     char * buffer = (char*) malloc (size);
     if (size == 0 || fread (buffer, size, 1, file))
      {
       zip_fileinfo zfi = {0};
       lxString fileName = dname + paths.GetLine (i).substr (in_dirname.length (), paths.GetLine (i).length () - in_dirname.length ());

       if (0 == zipOpenNewFileInZip (zf, fileName.c_str (), &zfi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION))
        {
         if (zipWriteInFileInZip (zf, size == 0 ? "" : buffer, size))
          _return = false;

         if (zipCloseFileInZip (zf))
          _return = false;

         fclose (file);
         free (buffer);
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
lxRemoveFile(const char * fname)
{
 return remove (fname);
}

bool
lxRenameFile(lxString oldfname, lxString newfname)
{
 return rename (oldfname.c_str (), newfname.c_str ());
}

bool
lxRemoveDir(const char* dirname)
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
 DIR *dp;
 dp = opendir (dirname);

 if (dp)
  {
   return closedir (dp);
  }
 else
  {
#ifndef _WIN_
   return mkdir (dirname, S_IWUSR | S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH);
#else     
   return mkdir (dirname);
#endif
  }
 return 0;
}

lxStringList
lxListDirRec(const lxString & dirname)
{
 DIR *dp;
 struct dirent *dent;
 struct stat sb;
 char fname[1024];

 lxStringList list;

 list.Clear ();

 dp = opendir (dirname);

 if (dp)
  {
   while ((dent = readdir (dp)) != NULL)
    {
     snprintf (fname, 1024, "%s/%s", dirname.c_str (), dent->d_name);
     stat (fname, &sb);

     if (S_ISREG (sb.st_mode))
      {
       list.AddLine (fname);
      }
     else if (S_ISDIR (sb.st_mode))
      {
       if (!(!strcmp (dent->d_name, ".") || !strcmp (dent->d_name, "..")))
        {
         lxStringList list2 = lxListDirRec (fname);
         for (unsigned int i = 0; i < list2.GetLinesCount (); i++)
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

lxString
lxGetUserDataDir(lxString appname)
{
 return lxString ("/home/") + getlogin () + "/." + appname;
}

lxString
lxGetTempDir(lxString appname)
{
 return "/tmp/";
}

lxString
lxGetExecutablePath(lxString appname)
{
 char buff[1024];
 int size = readlink ("/proc/self/exe", buff, 1023);
 if (size == -1)
  {
   return "";
  }
 buff[size] = 0;
 return buff;
}



// Useful functions_______________________________________________________

void
mprint(lxString message)
{
 fprintf (stdout, "%s", message.c_str ());
};

void
eprint(lxString error)
{
 fprintf (stderr, "%s", error.c_str ());
};

SDL_Color
ColorByRGB(unsigned short r, unsigned short g, unsigned short b)
{

 SDL_Color colorA;

 colorA.r = r;
 colorA.g = g;
 colorA.b = b;

 return colorA;
};

SDL_Color
ColorByName(lxString name)
{
 char cname[10];
 strncpy (cname, name.c_str (), 9);
 SDL_Color colorA;
 colorA.a = 0xFF;
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
}

lxBitmap *
lxGetBitmapRotated(lxImage *image, CWindow * win, int _orientation)
{
 SDL_Texture* Texture;
 SDL_Texture* mTexture = *image;

 if (mTexture == NULL)
  {
   printf ("Unable to get rotated bitmap! SDL Error: %s\n", SDL_GetError ());
  }
 else
  {
   SDL_Rect DestR;
   int sw=0, sh=0;
   SDL_QueryTexture (mTexture, NULL, NULL, &DestR.w, &DestR.h);


   switch (_orientation)
    {
    case 0:
    case 2:
     sw = DestR.w;
     sh = DestR.h;
     DestR.x = 0;
     DestR.y = 0;
     break;
    case 1:
    case 3:
     sw = DestR.h;
     sh = DestR.w;
     DestR.y = (DestR.w - DestR.h) / 2;
     DestR.x = (DestR.h - DestR.w) / 2;
     break;
    }


   Texture = SDL_CreateTexture (win->GetRenderer (), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sw, sh);

   SDL_Texture* last = SDL_GetRenderTarget (win->GetRenderer ());
   SDL_SetRenderTarget (win->GetRenderer (), Texture);


   //SDL_SetRenderDrawColor (win->GetRenderer (), 0xFF, 0xFF, 0xFF, 0x00);
   //SDL_RenderClear (win->GetRenderer ());

   SDL_RenderCopyEx (win->GetRenderer (), mTexture, NULL, &DestR, _orientation * 90, NULL, SDL_FLIP_NONE);

   SDL_DestroyTexture (mTexture);

   SDL_RenderPresent (win->GetRenderer ());

   SDL_SetRenderTarget (win->GetRenderer (), last);

   return new lxBitmap (Texture);

  }


 return NULL;

}

unsigned int
lxGetDisplayWidth(int disp)
{
 return Application->GetARootWindow ()->GetWidth ();
}

unsigned int
lxGetDisplayHeight(int disp)
{
 return Application->GetARootWindow ()->GetHeight ();
}

lxMutex::lxMutex()
{
 Mutex = (void *) new pthread_mutex_t;
 pthread_mutex_init ((pthread_mutex_t*) Mutex, NULL);
}

lxMutex::~lxMutex()
{
 delete (pthread_mutex_t*) Mutex;
}

void *
lxMutex::GetMutex(void)
{
 return Mutex;
}

int
lxMutex::Lock(void)
{
 return pthread_mutex_lock ((pthread_mutex_t*) Mutex);
}

int
lxMutex::Unlock(void)
{
 return pthread_mutex_unlock ((pthread_mutex_t*) Mutex);
}

lxCondition::lxCondition(lxMutex & mutex)
{
 Mutex = mutex.GetMutex ();
 Cond = (void *) new pthread_cond_t;
 pthread_cond_init ((pthread_cond_t *) Cond, NULL);
}

lxCondition::~lxCondition()
{
 delete (pthread_cond_t*) Cond;
}

void
lxCondition::Signal(void)
{
 pthread_cond_signal ((pthread_cond_t *) Cond);
}

void
lxCondition::Wait(void)
{
 pthread_cond_wait ((pthread_cond_t *) Cond, (pthread_mutex_t*) Mutex);
}

lxString
lxGetLocalFile(lxString file)
{

#ifndef __WXMSW__
 if (file.Contains ("http"))
  {
   lxString appname = lowercase (basename (Application->Aargv[0]));

   lxString name = file.substr (file.find (".com/") + 4, file.length ());

   lxString local;

   local.Printf ("%s/%s_local/%s", (const char *) lxGetTempDir (appname).c_str (),
                 (const char *) appname.c_str (),
                 (const char *) name.c_str ());

   if (lxFileExists (local))
    {
     return local;
    }

   lxCreateDir (dirname (local));

   lxString cmd = "cd \"" + dirname (local) + "\"; wget --inet4-only \"" + file + "\"";

   system ((const char *) cmd.c_str ());

   return local;
  }
#endif

 //local file
 return file;
}

