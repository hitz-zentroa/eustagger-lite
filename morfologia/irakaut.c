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


/*irakaut.c*/
/*automata.dat fitxategitik irakurri eta taula batetan jasotzen du*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filtro.h"
#include "tamaino.h"
#include "klaseak.h"
#include "externs.h"
#include "externs_e.h"
#include "externs_k.h"

#ifndef __EXEKU__
int irakur_automata(char *fp,automata_lag *aut,int erre,int zut)
#else
int irakur_automata(char *fp,automata *aut,int erre,int zut)
#endif /*__EXEKU__*/
 {
   char *l;
   int i,j;                                
   FILE *fitx;
   char *tmp,izen_luze[200];
   if((tmp= (char *) getenv("IXA_PREFIX"))!=NULL) {
     strcpy(izen_luze,tmp);
     strcat(izen_luze,"/var/eustagger_lite/morfologia/");
   }
   else strcpy(izen_luze,"");
   strcat(izen_luze,fp);

   if ((fitx=fopen(izen_luze,"r"))==NULL)  {
     return(0);
   }
   while ((l = hur_lerro(fitx)) != NULL) {
     l=pasa_komen(l);
     l=pasa_txuri(l);
     sscanf(l,"%d %d",&(*aut).alt,&(*aut).zab);   
     l=hur_lerro(fitx);
     
     l=pasa_komen(l);
     
     for (i=0;i<erre;i++) {
       l=hur_lerro(fitx);
       l=pasa_zen(l);
       (*aut).final[i]=(*l==':'); /*bi puntu badira estadua finala da*/
       l++;
       l=pasa_txuri(l);
       for (j=0;j<zut;j++) {
         sscanf(l,"%d",&(*aut).estaduak[i][j]);
         l=pasa_zen(l);
         l=pasa_txuri(l);
       }
       sscanf(l,"%d",&(*aut).klase[i]);
       l=pasa_zen(l);
       l=pasa_txuri(l);
       
     }
     
   }
   fclose(fitx); 
   return(1);                        
}
            
               

