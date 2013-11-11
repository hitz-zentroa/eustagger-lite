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


/*zerhitz.c*/


/*************************************************************************/
/*automataren bukaerako estaduen zenbakiak erabili beharrean hitza zer mota-
takoa den jakiteko,automataren estadu bakoitzari klase izeneko balio bat 
ematen diogu,eta klase horren arabera hitza zer motatakoa den jakin dezakegu*/
/*adibidez 16. estaduan bukatzen direnak zenbakiak dira, eta programa honetan
bukaerako estaduaren zenbakia zein den aztertu beharrean, estadu horren klasea
aztertuko dugu eta klasea ZENBAKIA da, honela automaten estaduei zenbakiak
aldatzen badizkiogu ere ez dugu zertan programa hau aldatu behar*/
/***********************************************************************/

/*irakurri duen hitza zer eratakoa den esaten digu*/
#include <stdio.h>
#include <string.h>
#include "filtro.h"
/*#include "taipak.h"*/ /*** externs.h fitxategian */
#include "tamaino.h"
#include "hizkia.h"
#include "klaseak.h"
#include "externs.h"
#include <ctype.h>

#ifdef __EXEKU__
char hitz[KMAXHITZ];
char hitzaze[KMAXHITZ_FIL_GABE];


void zerhitz(int mota,char *hitza,char *fil,char *filmarka,int *zenbat_aurrera)
/*int mota;
int *zenbat_aurrera; 
char hitza[],fil[],*filmarka;*/


{
 char aurreko[KMAXHITZ],atzeko[KMAXHITZ],atzizkia[KMAXHITZ];
 extern int HITZ_ELK;
 int lmota,total;
extern char *zati3(char *hitza_mozteko);

 *zenbat_aurrera = strlen(hitza) + 1; /*#5*/
 if (HITZ_ELK) lmota = HITZ_ELKARTUA;
 else lmota = mota;

 switch(lmota)
 
  { 
    case HITZ_NORMALA: 
      *filmarka = FILJARRA_MARKA;     
      break;
    case MAIUSKUL_DEKLINATUA: 
      /*strcpy(hitz,Maiuskulak(fil,atzizkia));*/ /*** NEREA : 94/5/27 */
	  Maiuskulak(fil,atzizkia,hitz); /*** JPB : 00/11/22 funktio-aldaketa */
      total = erromatarra_da(hitz);
      if (total) {
	sprintf(hitzaze,"%d%s",total,atzizkia);
	aztertu_zenbakia(hitzaze,hitz);
	strcpy(fil,hitz);
	*filmarka = FILJARRA_MARKA;
      }
      else
	*filmarka = FILJARRA_MARKA;
      break;
    case MAIUSKULA: 
      total = erromatarra_da(fil);
      if (total) {
	sprintf(hitzaze,"%d",total);
	aztertu_zenbakia(hitzaze,hitz);
	strcpy(fil,hitz);
	*filmarka = FILJARRA_MARKA;
      }
      else
	*filmarka = FILJARRA_MARKA;
        break;
    case SIGLAK: 
	    *filmarka = FILJARRA_MARKA;
        break;
    case DEKLINATUTAKO_SIGLAK: 
	    *filmarka = FILJARRA_MARKA;
        break;
    case IZEN_HASIERA: 
	    *filmarka = FILONDO_MARKA;
        break;
    case ZENBAKIA: 
	    *filmarka = FILONDO_MARKA;
        break;
    case ZENBAKI_DEKLINATUA:    
        strcpy(hitzaze,hitza); /*** NEREA : 94/3/23 zati3 */
        aztertu_zenbakia(hitzaze,hitz);
        strcpy(fil,hitz);
        *filmarka = FILJARRA_MARKA;
        break;                  
    case LETRA_BAKARRA: 
	    *filmarka = FILONDO_MARKA;
	    break;
/*    case MAIUSKULA_BEHARRA:
	    *filmarka = FILJARRA_MARKA;
        break;
    case PUNTU_ONDORENA:
	    *filmarka = FILJARRA_MARKA;
        break; */ /*** NEREA : 93/11/30 : ez konprobatu */         
    case MINUSKULA_PUNTUZ_BUKATUA:
        *filmarka = FILONDO_MARKA;
        break;
    case SIGLAK_MINUSKULAZ:
	    *filmarka = FILJARRA_MARKA;
        break;
    case HITZ_ELKARTUA:
/*** NEREA : 93-7-18 hitz-elkarketa errepikakorretan bi zatiak egiaztatzeko */
      strcpy(hitz,fil); /*#5*/
      strcpy(aurreko,strtok(hitz,"-")); /*#5*/
      strcpy(atzeko,strtok(NULL,"-")); /*#5*/
      if (!strcmp(atzeko,"edo")  || !strcmp(atzeko,"eta"))
	{
	  fil[strlen(aurreko)] = '\0';
	  *zenbat_aurrera=lehena_pasa(hitza);
	}
      else {
	/*	if (strlen(aurreko) > 2) 
	  {
	    if (berdinak(aurreko,atzeko))
	      {
		strcpy(fil,atzeko);
		*zenbat_aurrera = strlen(hitza) + 1;
	      }
	    else *zenbat_aurrera = strlen(hitza) + 1;
	  }
	  else */
	*zenbat_aurrera = strlen(hitza) + 1; /*** NEREA : 94/6/23 */
      }
/****************************************************************************/
      *filmarka = FILJARRA_MARKA;
      break;
    case LABURDURA_DEK: /*** NEREA : 93/11/18 laburdurak egiaztatzeko */
        *filmarka = FILJARRA_MARKA;
        break;
    case BEREIZGARRIAK_SOILIK: /*** NEREA : 94/3/23 : ez da beharrezkoa, baina
								bada ezpada */
        *filmarka = FILONDO_MARKA;
	    break;
    case ERROMATARRA_IZAN_DAITEKE: /*** NEREA : 94/5/12 */
      /*strcpy(hitz,Maiuskulak(hitza,atzizkia));*/ /*** NEREA : 94/5/27 */
		Maiuskulak(hitza,atzizkia,hitz); /*** JPB : 00/11/22 funktio-aldaketa */
      total = erromatarra_da(hitz);
      if (total) {
	sprintf(hitzaze,"%d%s",total,atzizkia);
	aztertu_zenbakia(hitzaze,hitz);
	strcpy(fil,hitz);
	*filmarka = FILJARRA_MARKA;
      }
      else
	*filmarka = FILJARRA_MARKA;
      break;
  case IDENTIFIKATZAILEA:
    *filmarka = FILONDO_MARKA;
    fil[0] = '\0';
    strcpy(fil,zati3(hitza));
    break;
    }
   
  }              

#endif  /*__EXEKU__*/
  
/*** NEREA : 94/5/27 hitzaren hasierako maiuskulak bakarrik tratatzeko */
/*char *Maiuskulak(char *hitz,char *atzizki)*/
void Maiuskulak(char *hitz,char *atzizki, char *hitz_ald)	/* JPB 00/11/22  errore konpotzeko */
/*char *hitz;*/
{
 unsigned int i=0,j=0;
 char hitza[KMAXHITZ];

 while (!maius(hitz[j])) j++;
 hitza[0] = '\0';
 atzizki[0] = '\0';
 strcpy(hitza,&hitz[j]);
 for (i=0;i<strlen(hitza);i++)
   if (!maius(hitza[i])) 
     {
       strcpy(atzizki,&hitza[i]);
       hitza[i]='\0';
	   strcpy(hitz_ald, hitza);/* JPB 00/11/22  */
	   return ;/* JPB 00/11/22  */
	   /*return (hitza);*//* JPB 00/11/22  */
     }
	strcpy(hitz_ald, hitza);/* JPB 00/11/22  */
	return ;/* JPB 00/11/22  */
	/*return (hitza);*//* JPB 00/11/22  */
}

/*** NEREA : 94/5/27 zenbaki erromatarrak direnean ez egiaztatzeko 


beharrezkoak diren konprobazioak */
#include <stdlib.h>
int erromatarra_da (char *hitza)
/*char *hitza;*/
{
 unsigned int i=0,total=0;
 int itzul[KMAXHITZ];
 int errom_zifrak[LEN_ERROM] = {1,5,10,50,100,500,1000};
 int posizioak[KMAXHITZ];
 int zenbat_jarraian = 1;
 int azkena_kendu = 1000;
 if (strspn(hitza,ERROMATAR)==strlen(hitza))
   {
     for (i=0;i<strlen(hitza);i++) {
       posizioak[i] = LEN_ERROM - strlen(strchr(ERROMATAR,hitza[i]));
       itzul[i] = errom_zifrak[posizioak[i]];
       if (i>0){
	 if (itzul[i] == itzul[i-1]) {
	   zenbat_jarraian++;
	   if ( (zenbat_jarraian > 3 && itzul[i] != 1000) ||  /*** IIII */
		(zenbat_jarraian > 1 && div(posizioak[i],2).rem != 0) ) return(0); /*** LL, DD ez onartzeko*/
	 }
	 else if (zenbat_jarraian > 1 && itzul[i] > itzul[i-1]) return(0); /*** IIIV ez onartzeko */
	 else {
	   if ( itzul[i] > itzul[i-1] )
	     if ( azkena_kendu > itzul[i-1] ) azkena_kendu = itzul[i-1];
	     else return(0);
	   else /*** itzul[i] < itzul[i-1] */
	     if ( azkena_kendu == itzul[i] ) return(0);
	   zenbat_jarraian = 1;
	 }
       }
     }
     total = itzul[strlen(hitza)-1];
     if (strlen(hitza)>1) {
       for (i=strlen(hitza)-2;i>=0;i--) {
	 if (itzul[i] < itzul[i+1]){
	   if ( div(posizioak[i+1],2).rem == 0 )  /*** 10,100,1000 */
	     if ( (posizioak[i+1]-posizioak[i]) != 2 )  /*** VX, LC, DM ez onartzeko */
	       return(0);
	     else {
	       total -= itzul[i];
	     }
	   else
	     if ( (posizioak[i+1]-posizioak[i]) != 1 )
	       return(0);
	     else {
	       total -= itzul[i];
	     }
	 }
	 else {
	   total += itzul[i];
	 }
	 if (i==0) return(total);
       }
     }
     else return(total);
   }
 return(total);
}

/****************************************************************************/

/*** NEREA : 93-7-18 hitz-elkarketa errepikakorretan bi zatiak egiaztatzeko */
int berdinak (char *lehena, char *bigarrena) /*#5*/
/*char lehena[],bigarrena[]; */
{
  unsigned int i,j,k=0;
  char lehen[KMAXHITZ],bigarren[KMAXHITZ];

  if (strlen(lehena) > strlen(bigarrena)) {
    return(0);
  }
  if (strlen(lehena) == strlen(bigarrena)) {
    j=strlen(lehena);
  }
  else {
    j=strlen(lehena) - 1;
  }
  for (i=0;i<strlen(lehena);i++) 
    if (isupper(lehena[i])) lehen[i]=tolower(lehena[i]);
    else lehen[i]=lehena[i];
  lehen[i]='\0';
  
  for (i=0;i<strlen(bigarrena);i++) 
    if (isupper(bigarrena[i])) bigarren[i]=tolower(bigarrena[i]);
    else bigarren[i]=bigarrena[i];
  bigarren[i]='\0';
  
#ifndef EZ_ETA_EDO  /*** NEREA : 94/9/12 : -eta -edo aparte egiaztatzeko */
  /*** EZ_ETA_EDO definitu -eta -edo aparte egiaztatzea nahi ez denean */
  
  if ((!strcmp(bigarren,"eta")) || (!strcmp(bigarren,"edo")))
    return(2);
  
#endif /*EZ_ETA_EDO*/
  
  i = 0;
  /*** lehen eta bigarren ia berdinak diren ikusi */
  while (i<j)
    if (lehen[i++] != bigarren[k++]) return(0);
  /*** lehen eta bigarren ia berdinak dira */
  return(1);

} /*#5*/


int lehena_pasa(char *dena) /*#5*/
/*char dena[];*/
{
   int zenbat=0;

	 /*** aurretik dauden bereizgarriak pasa */
     while (strchr(BEREIZGARRIAK,dena[zenbat++]) != NULL) ; 

	 zenbat--;

	 /*** hitz-elkartuaren lehen partea pasa */
     while (strchr(BEREIZGARRIAK,dena[zenbat++]) == NULL) ; 

	 zenbat--;

	 /*** lehen partearen bukaeran dauden bereizgarriak pasa */
     while (strchr(BEREIZGARRIAK,dena[zenbat++]) != NULL) ; 

     dena[zenbat] = '\0';
	 return (zenbat);
} /*#5*/
/****************************************************************************/
