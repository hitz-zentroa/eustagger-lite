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


/*azterzen.c*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filtro.h"
#include "tamaino.h"
#include "hizkia.h"
#include "externs.h"

char *eman_azken_zifra(char zenb[]) {
 int l=strlen(zenb)-1;
 
 while (strchr(ZIFRA,zenb[l]) == NULL) /*** 97/10/23 %90 eta antzekoetarako */
   {
    l--;
   }
 while ((l>=0) && (strchr(ZIFRA,zenb[l]) != NULL))
   {
     l--;
   }
 return(&zenb[l+1]);

}

void aztertu_zenbakia( char *filtratua, char *hitza)
{ 
  char bitar[2];
  int y,z,k,estadua,kont,zenb,p;
#ifndef __EXEKU__
  extern  automata_lag autofil2;
#else
  extern  automata autofil2;
#endif /*__EXEKU__*/

  char atzizkia[KMAXHITZ];
  char tmp2[KMAXHITZ_FIL_GABE];
       /***  95/5/25 zenbakietan marratxoa dagoenerako */
  int zenbaki[10];
  int l;

   atzizkia[0]='\0';
   zenbaki[0]='\0';
   kont = 0;
   zenb = 0;
   z = 0;
   k = 0;
   bitar[1] = '\0';

/*** 95/5/25 zenbakietan bereizgarriak daudenerako */
  strcpy(tmp2,eman_azken_zifra(filtratua));
/*******************************************************/

   l = strlen (tmp2); /*** 94/3/23 */

 while ((strchr(ZIFRA,tmp2[kont]) != NULL) && (kont < l))
     {
      bitar[0] = tmp2[kont];
      zenbaki[k] = atoi(bitar);
      k++;
      kont++;
     }   
   zenbaki[k] ='\0';
   zenb = kont-1;
   if (tmp2[kont] == '.') 
     {
      strcpy(atzizkia,"garren");
      z = 6;
      kont++;
     }

   while (kont != l) 
     {
       if (!filtratu(tmp2[kont])) {   /*** 99/8/3 zuriguneak eta bereizgarriak ez sartzeko*/
	 atzizkia[z] = tmp2[kont];
	 z++;
       }
      kont++;
     }
   atzizkia[z] = '\0';
   estadua = 1;
   p = estadua-1;

   if (zenbaki[k-1] == 3)
     strcpy(hitza,"hamahiru");
   else
     if (zenbaki[k-1] ==4)
       strcpy(hitza,"hamalau");
     else     
       if ( (k==1) && (zenbaki[k-1] == 1) )
	 strcpy(hitza,"bat");
       else {
	 while ((autofil2.final[p] == 0) && (estadua != 0))
	   {
	     if (zenb < 0)
	       y = 10;
	     else y =zenbaki[zenb];
	     estadua = autofil2.estaduak[p][y];
	     p = estadua-1;
	     zenb--;
	   }     
	 
	 if (autofil2.final[p] == 1)
	   {
	     if (estadua == 4)
	       strcpy(hitza,"hamazazpi");
	     if (estadua == 6) {
	       if ((atzizkia[0] == 'g') || (atzizkia[0] == 'G')) 
		 strcpy(hitza,"hamabos"); 
	       else {
		 strcpy(hitza,"hamabost");
		 if (strchr(BOKALE,atzizkia[0]) == NULL) {
		   strcat(hitza,"e");
		 }
	       }
	     }
	     if (estadua == 7) {
	       if (atzizkia[0] == 'e' || atzizkia[0] == 'E' || atzizkia[0] == 'a' || atzizkia[0] == 'A')
		 strcpy(hitza,"hamaik");
	       else
		 strcpy(hitza, "hamaika");
	     }
	   }
       }

   strcat(hitza,atzizkia);
 
 
}
 
 

