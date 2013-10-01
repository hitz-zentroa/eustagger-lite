#include "automata.h"
#include <stdio.h>
#include <stdlib.h>
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

 eslaxvar = "/var/aurreprozesua/"; 
 if((tmp = (char *) getenv("IXA_PREFIX"))!=NULL)  {
   izen_luze = tmp;
   izen_luze = izen_luze + eslaxvar;
   izen_luze = izen_luze + fitxategi;
 }
 else {
    printf("\Errorea: ez dago IXA_PREFIX aldagaia definituta\n");
    exit(1);
 }

 if ((aut = fopen(izen_luze.c_str(),"r")) == NULL)
   {
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

 fscanf(aut," %d ",&LERROAK);
 fscanf(aut," %d \n",&ZUTABEAK);

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

    fscanf(aut," %d",&est);
    if (est != (i+1))
      {
       printf("\n Errorea. %s fitxategia gaizki eratua\n",fitxategi);
       return 0;
      }
    fin=fgetc(aut);                              // irakurri finala den
    finalak[i] = (fin == ':') ? 1 : 0;
    for (int j=0;j<ZUTABEAK-2;j++)
      fscanf(aut," %d ",&transizioak[i][j]); // irakurri transizioak

    while (fgetc(aut) != '\"');                  // irakurri etiketa
    while ((str_lag[k]=fgetc(aut)) != '\"') k++;
    str_lag[k] = '\0';
    etiketak[i] = str_lag;
    fscanf(aut," %d",&tratamenduak[i]);          // irakurri tratamendua
//    fgetc(aut);                                  // irakurri lerro bukaera 
   } 


// Irakurri multzoak

 while (fgetc(aut) != '\"');                    // pasa komentarioa
 while (fgetc(aut) != '\"');
 fgetc(aut);                                    // irakurri lerro bukaera

 char mul_lag[40];

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
 char *multzoan;

 multzoan = strchr(multzoak[i++].c_str(),kar);
 while ((multzoan == NULL) && (i<ZUTABEAK-2)) 
   multzoan = strchr(multzoak[i++].c_str(),kar);
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



