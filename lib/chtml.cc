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

#include"../include/chtml.h"

  
CHtml::CHtml (void)
{
  SetClass ("CHtml");
  SetReadOnly (true);
  EvOnLinkClicked=NULL;
}

CHtml::~CHtml (void)
{
}


void 
CHtml::Create (CControl * control)
{
  CText::Create(control);
}

CStringList 
CHtml::GetContext (void)
{
  return CControl::GetContext();
}

void 
CHtml::SetContext (CStringList context)
{
  CControl::SetContext(context);
}

//void Event (wxEvent & event);
  
void 
CHtml::SetLoadText (String t)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

String 
CHtml::GetLoadText (void)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  return "";
}

void 
CHtml::SetLoadUrl (String url)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

String 
CHtml::GetLoadUrl (void)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  return "";
}

void 
CHtml::SetLoadFile (String url)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

String 
CHtml::GetLoadFile (void)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
  return "";
}

void 
CHtml::HistoryBack(void)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

void 
CHtml::HistoryForward(void)
{
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

