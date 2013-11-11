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


#include <stdio.h>
#include "bool.h"

static char             lerro[90] ;

char *pasa_txuri(char *s)
{ while (*s == ' ') s++ ;
  return(s) ;
}

char *pasa_ez_komilla(char *s)
{  while ((*s != '\42') && (*s != '\n')) s++ ;
   return(s) ;
}

char *hur_lerro(FILE *fitx)
{  char *l,*l1 ;
   bool lerro_hutsa, buk ;

   lerro_hutsa = 1 ;
   buk = 0 ;
   while ( !buk && lerro_hutsa) {
       l = lerro ;
       buk = (fgets(lerro,90,fitx) == NULL) ;
       if (!buk) {
          l1 = pasa_txuri(l) ;
          lerro_hutsa = (*l1 == '\n') ;
       }
   }
   if (buk) return(NULL) ;
   else return(l) ;
}

char *hur_autom(FILE *fitx)
{
  char *l ;
   bool aut_bilatua, buk ;

   aut_bilatua = 0 ;
   buk = 0 ;
   while ( !buk && !aut_bilatua) {
       l = lerro ;
       buk = (fgets(lerro,90,fitx) == NULL) ;
       if (!buk) {
          l = pasa_ez_komilla(l) ;
          aut_bilatua = (*l == '\42') ;
       }
   }
   if (buk) return(NULL) ;
   else return(l) ;
}

char *pasa_zen(char *s)
{ while ((*s >= '0') && (*s <= '9')) s++ ;
  return(s) ;
}


char *pasa_komen(char *s)
{     do
        s++ ;
      while (*s != '\42') ;      /* --\42 = "-- komentarioa " tartean dator */
      s++ ;
   
   return(s) ;
}

int pare_konp (const void *a,const void *b)            /* bi kar pare konparatzen ditu :    */
 				        /*  '=' ->  emaitza 0                */
{ int var ;
  char *pare1, *pare2 ;                 /*  '<' ->  emaitza 0 baino txikiago */
  pare1=(char *)a;  
  pare2=(char *)b;                      /*  '>' ->  emaitza 0 baino handiago */
  var = (*pare1 - *pare2) ;

  if (!var)                              /* berdinak direnez ...          */
        return( *(pare1+1) - *(pare2+1));/* pareetako 2. letrak konparatu */
  else
        return( var ) ;

}
