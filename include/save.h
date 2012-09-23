 /*****************************************************************************
 **  This is part of the SpaceZero program
 **  Copyright (C) 2006-2012  MRevenga
 **
 **  This program is free software; you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License (version 3), or
 **  (at your option) any later version, as published by the Free Software 
 **  Foundation.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with this program; if not, write to the Free Software
 **  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ******************************************************************************/

/*************  SpaceZero  M.R.H. 2006-2012 ******************
		Author: MRevenga
		E-mail: mrevenga at users.sourceforge.net
		version 0.82 Jan 2012
****/

#ifndef _SAVE_
#define _SAVE_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <math.h>

#include "ai.h"
#include "objects.h"
#include "ai.h"
#include "general.h"
#include "data.h"
#include "spacecomm.h"
#include "functions.h"


char *CreateOptionsFile(void);
char *CreateSaveFile(int server,int client);
char *CreateRecordFile(void);
char *CreateKeyboardFile(void);

void SaveParamOptions(char *file,struct Parametres *par);
void SaveUserKeys(char *file,struct Keys *keys);
int LoadUserKeys(char *keyfile,struct Keys *keys);

int LoadParamOptions(char *file,struct Parametres *par);
void PrintParamOptions(struct Parametres *par);

int ExecSave(struct HeadObjList ,char *);
int ExecLoad(char *);


#endif
