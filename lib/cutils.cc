/* ########################################################################

   LXRAD -  GUI for X programing

   ########################################################################

   Copyright (c) : 2001  Luis Claudio Gambôa Lopes

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

#include"../include/cutils.h"
#include"../include/cwindow.h"
#include"../include/capplication.h"

#include<stdio.h>

// Useful functions_______________________________________________________

void mprint(String message)
{
  fprintf(stdout,"%s",message.c_str());
};

void eprint(String error)
{
  fprintf(stderr,"%s",error.c_str());
};

XColor
ColorByRGB (unsigned short r, unsigned short g, unsigned short b)
{
  XColor
    colorA,
    colorB;
  colorA.red = r * 256;
  colorA.green = g * 256;
  colorA.blue = b * 256;
  colorA.flags = DoRed | DoGreen | DoBlue;
  colorA.pad = '@';
  colorB = colorA;
  if (Application->XSearchInColorTable (&colorA))
    return colorA;
  XAllocColor (Application->GetADisplay (), Application->GetAScreen ()->cmap,
	       &colorB);
  Application->AddToColorTable ("RGB", colorA, colorB);
  return colorB;
};

XColor
ColorByName (String name)
{
  XColor
    colorA,
    colorB;
  if (Application->XSearchInColorTable (name, &colorA))
    return colorA;
  XAllocNamedColor (Application->GetADisplay (),
		    Application->GetAScreen ()->cmap, name.c_str (), &colorA,
		    &colorB);
  Application->AddToColorTable (name, colorA, colorB);
  return colorB;
};

int
XXLookupString (XIC ic, XKeyPressedEvent * event, char *buffer_return,
		int bytes_buffer, KeySym * keysym_return,
		Status * status_return)
{
#ifdef _DEBUG
  *status_return = XLookupBoth;
  switch ((event->state & ShiftMask) + (event->state & LockMask))
    {
    case ShiftMask:
      *keysym_return = XLookupKeysym (event, 1);
      break;
    case LockMask:
      *keysym_return = XLookupKeysym (event, 1);
      break;
    default:
      *keysym_return = XLookupKeysym (event, 0);
    };

  strcpy (buffer_return, XKeysymToString (*keysym_return));
  return 1;

#else
  if (ic)
    {
      return XmbLookupString (ic, event, buffer_return, bytes_buffer,
			      keysym_return, status_return);
    }
  else
    {
      return XLookupString (event, buffer_return, bytes_buffer, keysym_return,
			    NULL);
    };

#endif
};
