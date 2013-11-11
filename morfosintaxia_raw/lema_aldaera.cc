//////////////////////////////////////////////////////////////////
//
//  EUSTAGGER LITE
//
//  Copyright (C) 1996-2013  IXA Taldea
//                           EHU-UPV
//
//  This file is part of EUSTAGGER LITE.
//
//  EUSTAGGER LITE is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  EUSTAGGER LITE is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
//  Contact: Ixa Taldea (ixa@ehu.es)
//           649 Posta kutxa
//           20080 Donostia (Basque Country)
//
//////////////////////////////////////////////////////////////////


/* ***************************************************
 
 * **************************************************** */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lema_aldaera.h"
#include <stdlib.h>


void bihur_asteris_maiuskula(char *st1,char *st2) {
 int i,j;
 for (i=j=0;st1[i]!='\0';j++)
  if (st1[i]=='*')
    {
      i++;
      st2[j]=(st1[i]=='\261')?'\221':toupper(st1[i]);
      i++;
    }
  else 
    if (st1[i]=='_') {  /*** 93/11/13 */
      st2[j]=' ';
      i++;
    } /*** 93/11/13 */
    else st2[j]=st1[i++];
 st2[j] = '\0'; /***93-9-20  */
}

/* ************************** */
/* Marka berezien tratamendua */
/* ************************** */


extern int kendu_marka_lex(char lex[], char azal[], int maj_ken_al);

void ken_marka_hitzetik(char *hitza,char *markatua)
{
 int l;

 hitza[0] = '\0';
 strcpy(hitza,markatua);
 l = strlen(markatua);
 
 kendu_marka_lex(hitza,markatua,0);
 bihur_asteris_maiuskula(markatua,hitza);

}

