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


#include <string.h>
#include <stdlib.h>

static char MARKAK_KENDU[]="E/~^%+!:134";
static char MARKAK_ALDATU[] ="RQMN\\A@&#2";
static char MARKAK_ALDATU2[]="rrnnnaaaaa";
static char MARKAK_BIHURTU[] ="123489";
static char MARKAK_BIHURTU2[]="%#:!ñ*";

#define MARKA_MAJ "9*"

int ken_maiuskulak (char *str)
{
  int i,j,l;
  
  l = strlen(str);
  for (i=0,j=0;i<l;i++)
    if (str[i] != '9' && str[i] != '*')
      {
	str[j] = str[i];
	j++;
      }
  str[j] = '\0';
  return(1);
}


int bihurtu_marka_lex(char lex[], char azal[])
{
  int i,l;
  char *p,*lexbihur;

  lexbihur = strdup(lex);

  /* bihurtu gure marketara */
  l = strlen(lex);
  for(i=0;i<l;i++)
    {
      if((p=(char *)strchr(MARKAK_BIHURTU,lex[i]))!=NULL)
	lexbihur[i]=MARKAK_BIHURTU2[p-MARKAK_BIHURTU];
    }
  strcpy(azal,lexbihur);
  free(lexbihur);
  return 1;
}

int bihurtu_marka_lex_xeroxera(char lex[], char lexxerox[])
{
  int i,l;
  char *p,*lexbihur;

  lexbihur = strdup(lex);

  /* bihurtu gure marketatik Xerox-eko marketara */
  l = strlen(lex);
  for(i=0;i<l;i++)
    {
      if((p=(char *)strchr(MARKAK_BIHURTU2,lex[i]))!=NULL)
	lexbihur[i]=MARKAK_BIHURTU[p-MARKAK_BIHURTU2];
    }
  strcpy(lexxerox,lexbihur);
  free(lexbihur);
  return 1;
}

int kendu_marka_lex(char lex[], char azal[], int maj_ken_al)
{
  int i,j,l;
  char *p;

  l=strlen(lex);
  for(i=0,j=0;i<l;i++)
    {
      if(strchr(MARKAK_KENDU,lex[i])) continue;  /* karakterea galdu */
      else if((p=(char *)strchr(MARKAK_ALDATU,lex[i]))!=NULL)
	azal[j++]=MARKAK_ALDATU2[p-MARKAK_ALDATU];
      else if((strchr(MARKA_MAJ,lex[i]))&&maj_ken_al) continue;
      else azal[j++]=lex[i];
    }
  azal[j]='\0';
  return 1;
}

int gehitu_marka_lex(char bim[], char azal[])
{
  int j,l;
  char *p,k;

 l=strlen(bim);
 j=strlen(azal);

 /* MARKAK bakarrik lehenengo eta azkeneko posizioetan */ 

 if (l)
   if ((p=strchr(MARKAK_KENDU,bim[l-1])) != NULL) {
     if (strlen(bim) == strlen(azal)+1) {
       azal[j] = *p;
       azal[j+1] = '\0';
     }
   }
 if ((p=strchr(MARKAK_KENDU,bim[0])) != NULL) {
   char azal2[80];
   azal2[0] = *p;
   azal2[1] = '\0';
   if (azal[0] == 'e' && azal2[0] == 'E')
     strcat(azal2,&azal[1]);
   else
     strcat(azal2,azal);
   strcpy(azal,azal2);
 }

 if (l) {
   if ((p=(char *)strchr(MARKAK_ALDATU,bim[l-1]))!=NULL) {
     k=MARKAK_ALDATU2[p-MARKAK_ALDATU];
     if (k == 'r' && *p == 'R' && j>1 && azal[j-1] == k && azal[j-2] == k) {
       /* R gogorra jarri baina ordezkatu rr->R */
       azal[j-2] = *p;
       azal[j-1] = '\0';
     }
     else
       if (azal[j-1] == k) { azal[j-1] = *p; azal[j] = '\0'; }
   }
   if (azal[j-1] == 'e' && bim[l-1] != 'e') azal[j-1] = 'E';
 }
 if ((p=(char *)strchr(MARKAK_ALDATU,bim[0]))!=NULL) {
   k=MARKAK_ALDATU2[p-MARKAK_ALDATU];
   if (azal[0] == k) azal[0] = *p;
 }

 return 1;
}
		
