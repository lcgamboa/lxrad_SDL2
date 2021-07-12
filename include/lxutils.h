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


#ifndef LXUTILS_H
#define	LXUTILS_H

#include"clxrad.h"
#include"mstring.h"
#include<math.h>

class CWindow;

//Compatibillity 
#define CPWindow CWindow
#define CImage CDraw
#define lxT
#define _T
#define CCanvas CPaint

struct TXColor
{
  lxString name;
  SDL_Color color;
  SDL_Color displaycolor;
};

void mprint(lxString message);

void eprint(lxString error);

SDL_Color ColorByRGB (unsigned short r, unsigned short g, unsigned short b);

SDL_Color ColorByName (lxString name);


class lxTextFile
{
  private:	
  FILE * f;
  lxString fn;
  public:
  lxTextFile();
  int Open(lxString fname);
  int Create(lxString fname);
  bool IsOpened(void);
  void Close(void);
  void GoToLine(int l);
  FILE * GetFd(void);
  operator FILE*() const;
  void Clear(void);
  void Write(void){};
  void AddLine(lxString line);
};


class lxImage
{
private:
CPWindow * Win;
SDL_Texture* Texture;
public:
lxImage(CPWindow * win);
~lxImage();
bool LoadFile(const lxString fname, int orientation = 0, float scalex = 1.0, float scaley = 1.0, int useAlpha = 0, double * ret_sx=NULL, double * ret_sy=NULL);
void Destroy();
SDL_Texture * GetImage(void);
operator SDL_Texture*() const;
unsigned int GetWidth(void);
unsigned int GetHeight(void);
};

class lxSize
{
private:
  unsigned int w,h;
public:
  unsigned int GetWidth(void){return w;};
  unsigned int GetHeight(void){return h;};
  void SetWidth(unsigned int w_){w=w_;}
  void SetHeight(unsigned int h_){h=h_;};
};

class lxBitmap
{
private:
SDL_Texture* Texture;
public:
~lxBitmap();
lxBitmap (SDL_Texture* Texture); 
lxBitmap(lxImage * surf, CPWindow * win);
lxBitmap (int width, int height); 
SDL_Texture* GetPixmap(void);
lxSize GetSize(void);
unsigned int GetWidth(void);
unsigned int GetHeight(void);
};

class lxSound
{
private:
public:
  bool Create(lxString fname);	
  void Stop(void);
  void Play(int flags);
};

class lxFileName
{
private:
lxString FName;
public:
  void Assign(lxString fname);
  void MakeAbsolute(void);
  lxString GetFullPath(void);
};

#define lxPoint SDL_Point

typedef struct
{
int x,y,width,height;	
}lxRect;


class lxColor
{
private:	
  SDL_Color Color;
public:
  lxColor();
  lxColor(SDL_Color color);
  lxColor(const char * name);
  lxColor(unsigned char r, unsigned char g, unsigned char b);
  lxString GetAsString(int flags =0);
  unsigned char Red(void){return Color.r;};
  unsigned char Green(void){return Color.g;};
  unsigned char Blue(void){return Color.b;};
  operator SDL_Color() const;
  void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 0xFF);
};

class lxCursor
{
private:    
  SDL_Cursor* cursor;
public:
  ~lxCursor();
  lxCursor(int type);
  SDL_Cursor* GetSDLCursor(void);
};

class lxFont
{
private:
  TTF_Font * font;
  int Size;
  int Family;
  int Style; 
  int Weight;
public:
  lxFont();
  lxFont(int size,int family,int style,int weight);
  void SetPointSize(int size); 
  TTF_Font * GetTTFFont(void);
  int GetPointSize(void);
};

class lxMutex
{
private:
  void * Mutex;  
public:
  void * GetMutex(void);     
  lxMutex();
  ~lxMutex();  
  void Lock(void);
  void Unlock(void);  
};

class lxCondition
{
private:
  void * Cond;  
  void * Mutex;  
public:       
  lxCondition(lxMutex & mutex);  
  ~lxCondition();
  void Signal(void);   
  void Wait(void);   
};

#define lxFONTFAMILY_DEFAULT  0x00
#define lxFONTFAMILY_TELETYPE 0x01
#define lxFONTSTYLE_NORMAL 0x01
#define lxFONTWEIGHT_BOLD 0x01
#define lxFONTWEIGHT_NORMAL 0x00


#define lxCURSOR_CROSS SDL_SYSTEM_CURSOR_CROSSHAIR
#define lxCURSOR_ARROW SDL_SYSTEM_CURSOR_ARROW
#define lxCURSOR_SIZENWSE SDL_SYSTEM_CURSOR_SIZENWSE
#define lxCURSOR_SIZING  SDL_SYSTEM_CURSOR_SIZEALL
#define lxCURSOR_SIZENS  SDL_SYSTEM_CURSOR_SIZENS
#define lxCURSOR_SIZEWE  SDL_SYSTEM_CURSOR_SIZEWE

#define lxALIGN_LEFT   0x00
#define lxALIGN_RIGHT  0x01
#define lxALIGN_CENTER 0x02
#define lxALIGN_CENTER_VERTICAL 0x04


#define lxFD_OPEN 	0x1
#define lxFD_SAVE 	0x2
#define lxFD_CHANGE_DIR 0x4

#define lxSOUND_ASYNC  0x01
#define lxSOUND_LOOP   0x02

#define lxEXEC_MAKE_GROUP_LEADER 0x01

#define lxConvUTF8 2048

#define lxC2S_HTML_SYNTAX 0x01

#define lxEXEC_ASYNC 0x01
#define lxEXEC_SYNC  0x02      

#define lxMOUSE_BTN_RIGHT 0x01
#define lxMOUSE_BTN_LEFT  0x02      

#define LXK_SHIFT SDLK_LSHIFT  
#define LXK_RIGHT SDLK_RIGHT
#define LXK_LEFT  SDLK_LEFT
#define LXK_DOWN  SDLK_DOWN
#define LXK_UP    SDLK_UP
#define LXK_CONTROL  SDLK_LCTRL

lxBitmap * lxGetBitmapRotated(lxImage *image, CWindow * win, int orientation); 

void lxMilliSleep(unsigned int time);
void lxSetCursor(lxCursor cursor); 
bool lxFileExists(lxString fname);
void lxExecute(lxString cmd,unsigned int flags=0, void * arg = NULL);
lxString lxGetCwd(void);
int lxSetWorkingDirectory(lxString dir);
bool lxLaunchDefaultBrowser(lxString url);
bool lxLaunchDefaultApplication(lxString cmd);

lxString lxGetUserDataDir(lxString appname="");
lxString lxGetTempDir(lxString appname="");
lxString lxGetExecutablePath(lxString appname="");

lxStringList lxListDirRec(const lxString &dirname);
bool lxZipDir(const lxString &in_dirname, const lxString &out_filename);
bool lxUnzipDir(const lxString &in_filename, const lxString &out_dirname);

bool lxRemoveFile(const char* fname);
bool lxRemoveDir(const char* dirname);
bool lxCreateDir(const char * dirname);
bool lxRenameFile(lxString oldfname, lxString newfname);

unsigned int lxGetDisplayWidth(int disp);
unsigned int lxGetDisplayHeight(int disp);

lxString lxGetLocalFile(lxString file);

#endif	/* LXUTILS_H */
