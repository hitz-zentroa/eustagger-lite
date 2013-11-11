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


#include "hizkia.h"
#define FUNDEF
#include "filtro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int aurkitu_zutabea(char k)
 {int i;
  unsigned char kar; /*** 94/5/24 */

  i = 0;
  kar = (unsigned) k; /*** 94/5/24 */

/***  94/3/21 : 8 biteko ASCII karaktereak onar ditzan */
   if (((int)kar >= 128) && ((int)kar <= 255) &&  /*** 94/5/24 */
       (k != NI_T) && (k != NI_H)) 
      return(MULTZO_MAX); 
/**************************************************************/
 
  while ((strchr(multzoak[i],k) == NULL) && (i < MULTZO_MAX))
   {  i++;}
   
  return(i);
       
   } 
           
int zenbakia(char ka)
 /*char ka;*/
 {if(strchr(ZIFRA,ka) != NULL) return(1);
                           else return(0);
 }

        
int ken_majusk(char str[])
{
int i,j,l;
l=strlen(str);
for(i=0,j=0;i<l;i++)
  if(str[i]!=ASTERIS) { 
    str[j]=str[i];
    j++;
  }
str[j]='\0';
return(0);
}
int ken_majusk_marratxo(char str[]) 
/* aurreko bera baina marratxo ondoren maiuskula utziz */
{
int i,j,l;
l=strlen(str);
for(i=0,j=0;i<l;i++)
  if(str[i]!=ASTERIS) { 
    str[j]=str[i];
    j++;
  }
  else if (j>0 && str[j-1] == '-') {
    str[j]=str[i];
    j++;
  }
str[j]='\0';
return(0);
}

int maius(char ka)
 {if (strchr(MAJ,ka) != NULL) return(1);
                          else return(0);
 }                          
 
int filtratu(char k)
 {
  unsigned char kar ; /*** 94/5/24 */

	kar = (unsigned) k ; /*** 94/5/24 */
	if (((int)kar >= 128) && 
	    /* ((int)kar <= 255) &&  */
	    (k != NI_T) && (k != NI_H)) /*** 94/5/24 */ 
	   return (1);
	if ((strchr(ALF,k)!=NULL)||(strchr(MAJ,k)!=NULL)||(strchr(ZIFRA,k)!=NULL))
	   /*** 94/5/24 */
       return(0);
    else   return(1);
 }                           
         


#include <ctype.h>

void kendu_maj_asteris(char *st1, char *st2)
{
int i,j;
for (i=j=0;st1[i]!='\0';i++)
	if(st1[i]!=ASTERIS) st2[j++]=st1[i];
st2[j]='\0';
return;
}

void bihur_maj_asteris(char *st1, char *emai)
/* eineak ere bihurtzen dira */
{
  int i,j;
  char st2[200];
  st2[0] = '\0';

  for (i=j=0;st1[i]!='\0';i++)
    if (isupper(st1[i])&&(st1[i]!=NI_T)&&(st1[i]!=NI_H))
      {
	st2[j++]=ASTERIS;
	st2[j++]=tolower(st1[i]);
      }
    else if(st1[i]==NI_H)
      {
	st2[j++]=ASTERIS;
	st2[j++]=NI_GUZTIENTZAT;
      }
    else if(st1[i]==NI_T)
      {
	st2[j++]=NI_GUZTIENTZAT;
      }
    else if (st1[i]==' ') 
      {
	st2[j]='_';
	i++;
      } 
    else if (st1[i] != '\222' && st1[i] != '\'' && st1[i] != '\"') st2[j++]=st1[i];
  st2[j] = '\0'; 

  strcpy(emai,st2);
}

void bihur_asteris_maj(char *st1,char *emai)
{
  int i,j;
  char st2[200];
  st2[0] = '\0';
  for (i=j=0;st1[i]!='\0';j++)
    if (st1[i]==ASTERIS)
      {
	i++;
	st2[j]=(st1[i]==NI_GUZTIENTZAT)?NI_H:toupper(st1[i]);
	i++;
      }
    else if(st1[i]==NI_GUZTIENTZAT) {
      st2[j]=NI_T;
      i++;
    }
    else 
      if (st1[i]=='_') {
	st2[j]=' ';
	i++;
      } 
      else st2[j]=st1[i++];
  st2[j] = '\0';
  strcpy(emai,st2);
}

