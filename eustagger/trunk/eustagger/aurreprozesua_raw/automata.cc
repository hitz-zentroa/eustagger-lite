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


#include "automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>


automata::automata()                      // hasieraketa funtzioa
{
 LERROAK = 0;
 ZUTABEAK = 0;
 estadua = 1;
}

int automata::init(char *fitxategi)       // hasieraketa funtzioa
{
 FILE *aut;
 // char c;

// Ireki fitxategia.

char *tmp;
string izen_luze, eslaxvar;

 eslaxvar = "/var/eustagger_lite/aurreprozesua/"; 
 if((tmp = (char *) getenv("IXA_PREFIX"))!=NULL)  {
   izen_luze = tmp;
   izen_luze = izen_luze + eslaxvar;
   izen_luze = izen_luze + fitxategi;
 }
 else {
    printf("\Errorea: ez dago IXA_PREFIX aldagaia definituta\n");
    exit(1);
 }

 if ((aut = fopen(izen_luze.c_str(),"r")) == NULL)  {
   printf("\nErrorea %s irekitzean\n",fitxategi);
   exit(1);
 }

// Hasierako komentarioa pasa (komila artean)

 while (fgetc(aut) != '\"');
 // c = (char) fgetc(aut);
 // while ( c != '\"')
 //   c = (char) fgetc(aut);
 while (fgetc(aut) != '\"');


// Irakurri Lerro eta zutabe kopurua
 int kop;
 if ((kop = fscanf(aut," %d ",&LERROAK)) != 1) {
   printf("\nErrorea automataren lerroak irakurtzean\n");
   exit(1);
 }
 if ((kop = fscanf(aut," %d \n",&ZUTABEAK)) != 1) {
   printf("\nErrorea automataren zutabeak irakurtzean\n");
   exit(1);
 }
// Sortu memoria transizioak, finalak, etiketak eta tratamenduak gordetzeko

 transizioak = new (int *[LERROAK] ); 
 for (int k=0;k<LERROAK;k++)
   transizioak[k] = new int[ZUTABEAK-1];
 finalak = new int[LERROAK];
 multzoak = new string[ZUTABEAK-2];
 etiketak = new string[LERROAK]; 
 tratamenduak = new int[LERROAK];

// Irakurri transizioak, finalak, etiketak eta tratamenduak estadu bakoitzeko
 for (int i=0;i<LERROAK;i++)
   {
    int est,fin;
    char str_lag[20];
    int k = 0;

    if ((kop = fscanf(aut," %d",&est)) != 1) {
      printf("\nErrorea automatan egoera irakurtzean\n");
      exit(1);
    }

    if (est != (i+1))
      {
       printf("\n Errorea. %s fitxategia gaizki eratua\n",fitxategi);
       return 0;
      }
    fin=fgetc(aut);                              // irakurri finala den
    finalak[i] = (fin == ':') ? 1 : 0;
    for (int j=0;j<ZUTABEAK-2;j++) {
      if (( kop = fscanf(aut," %d ",&transizioak[i][j])) != 1) { // irakurri transizioak
	printf("\nErrorea automatan trantsizioak irakurtzean\n");
	exit(1);
      }
    }

    while (fgetc(aut) != '\"');                  // irakurri etiketa
    while ((str_lag[k]=fgetc(aut)) != '\"') k++;
    str_lag[k] = '\0';
    etiketak[i] = str_lag;
    if ((kop = fscanf(aut," %d",&tratamenduak[i])) != 1) {  // irakurri tratamendua
      printf("\nErrorea automatan tratamenduak irakurtzean\n");
      exit(1);
    }
   } 


// Irakurri multzoak

 while (fgetc(aut) != '\"');                    // pasa komentarioa
 while (fgetc(aut) != '\"');
 fgetc(aut);                                    // irakurri lerro bukaera

 char mul_lag[ZUTABEAK];

 for (int j=0;j<ZUTABEAK-2;j++)                 // multzoak irakurri 
   {
    int k = 0,azkena = 0;
    char k_lag;

    while (fgetc(aut) != '\"');                 // multzoaren hasierako " 
    mul_lag[k] = fgetc(aut);
    while (!azkena)
      {
       while (mul_lag[k] != '\"')
         {
          k++; 
          mul_lag[k] = fgetc(aut);
         }
       if ((k_lag = fgetc(aut)) == '\n') 
         azkena = 1;
       else
         {
          k++;
          mul_lag[k] = k_lag; 
         }
      }
    mul_lag[k] = '\0';
    multzoak[j] = mul_lag;
   }

// Itxi fitxategia

 fclose(aut);
 return 1;

}

void automata::reset()     // automataren estadua hasieratzen du
{
 estadua = 1;
}

int automata::mugitu(char kar) 
       // hurrengo trantsizioa bilatzen du emandako
       // karakterearen arabera. Estadua finala den
       // ala ez itzultzen du emaitza gisa.
{
 int i = 0;
 char *multzoan,*multzotmp;

 multzotmp = strdup(multzoak[i++].c_str());
 multzoan = strchr(multzotmp,kar);
 while ((multzoan == NULL) && (i<ZUTABEAK-2)){ 
   free(multzotmp);
   multzotmp = strdup(multzoak[i++].c_str());
   multzoan = strchr(multzotmp,kar);
   //   multzoan = strchr(multzoak[i++].c_str(),kar);
 }

 if (multzoan == NULL)       // ez badago multzoen artean, transizio ez-posiblea
 {                    // estadua dagoen moduan utzi
//  estadua = 0;
  return -1;
 }
 estadua = transizioak[estadua - 1][--i];
 if (estadua == 0) return 0;
 else return 1;

}

string automata::etiketa()
{
 return(etiketak[estadua - 1]);
}

int automata::tratamendua()
{
 return(tratamenduak[estadua - 1]);
}

int automata::bukaerakoa()
{
 return (finalak[estadua - 1]);
}

automata::~automata()        // funtzio suntsitzailea
{
  // for (int k=0;k<LERROAK;k++)
  //   delete (transizioak[k]);
 delete []transizioak; 
 delete []finalak;
 // for (int i=0;i<ZUTABEAK-2;i++)
 //   multzoak[i].~string();
 delete []multzoak;
 // for (int j=1;j<LERROAK;j++)
 //   etiketak[j].~string();
 delete []etiketak;
}



