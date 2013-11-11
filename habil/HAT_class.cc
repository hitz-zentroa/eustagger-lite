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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "HAT_class.h"
#include <algorithm>

using namespace std;


// Sarrerako fitxategitik irakurtzean aldagaiak hasieratzeko
// erabiltzen diren metodoak.

// *********************************************************************//
void  HAT_class::Hasieraketa()
    // Sarrerako fitxategitik lortutako datuen arabera memoria alokatu
    // eta taulak hasieratzen ditu.
  {
    HAT_kopurua = 10;
    FORMA_kopurua = 10;
    LEMA_kopurua = 10;
    HITZ_kopurua = 10;

    HAT_taula = vector<HAT>(HAT_kopurua);
    FORMA_taula = vector<FORMA>(FORMA_kopurua);
    LEMA_taula = vector<LEMA>(LEMA_kopurua);
    Esaldi = vector<HITZ>(HITZ_kopurua);

    hat = 0;
    forma = 0;
    lema = 0;
    hitz_indizea = 0;
  }

// *********************************************************************//
void  HAT_class::erantsi_HAT(string lem, IM im, int kop, int seg)
  {
    if (hat >= HAT_kopurua)
      {
	HAT_kopurua = hat+10;
	HAT_taula.resize(HAT_kopurua);
	//fprintf(stderr,"HAT_taula handitu: %d\n", HAT_kopurua);
      }
    HAT_taula[hat].Hasieraketa(lem,im,kop,seg);
    hat++;
  }

// *********************************************************************//
int_lista  HAT_class::badago_FORMA(string H)
    // H hitza formen taula dagoen esaten digu.
    // Emaitza : posizioen lista bat: i --> i-1 posizioan dago
    // Hau beharrezkoa da Maiuskulaz zein minuskulaz ager daitekeenean
    // forma bera. Adibidez: Euskal Herria / euskal eskola.
  {
   int i;
   int_lista emaitza;
   //   char tmp[50];
   string Htmp = H;

//    tmp[0] = '\0';
//    strcpy(tmp,H.elem());
   
   for (i=1;(unsigned)i<Htmp.length();i++) {
     if (Htmp[i] == 'Ñ') Htmp[i] = 'ñ';
     else
       if (isupper(Htmp[i])) 
         Htmp[i] = tolower(Htmp[i]);
   }
   for (i=0;i<forma;i++)
     if (FORMA_taula[i].konparatu(Htmp) == 0)
       emaitza.push_back(i+1);
   return emaitza;
 }

// *********************************************************************//
int  HAT_class::badago_LEMA(string H)
    // H hitza lemen taula dagoen esaten digu.
    // Emaitza : 0 --> ez dago      i --> i-1 posizioan dago
  {
   int i;

   for (i=0;i<lema;i++)
     if (LEMA_taula[i].konparatu(H) == 0)
       return i+1;
   return 0;
  }
// *********************************************************************//
int HAT_class::badago_HAT(string H, string ima)
    // H lema HATen taulan dagoen esaten digu.
    // Emaitza : 0 --> ez dago      i --> i-1 posizioan dago.
  {
     int i;

     for (i=0; i<hat;i++)
       {
         int k = HAT_taula[i].konparatu(H);

         if (k == 0) {
           string kat_azp = HAT_taula[i].eman_KAT_AZP();
           if ( kat_azp == ima) 
             return i+1;
         }
       }
     return 0;
   }

// *********************************************************************//
int  HAT_class::zein_HAT()
    // Hutsik dagoen lehenengo HATaren indizea ematen du.
    // Emaitza : hat
  {
     return hat;
  }

// *********************************************************************//
void  HAT_class::erantsi_FORMA(string H, int i, int p)
    // H hitza formen taulan gordetzen du. Forma dagoeneko badago,
    // i HATean eta p posizio berriak erantsiko dizkio.
  {
    int t=0;
    int_bikote bi(i,p);
    int_lista findizeak;

    findizeak = badago_FORMA(H);
    if (findizeak.size())
      {
        int_lista::iterator hasi,amaitu,fin;
        hasi = findizeak.begin();
        amaitu = findizeak.end();
        for ( fin = hasi; fin != amaitu; ++fin) {
          t = *fin;
          int_bikote erreferentzia(FORM,t-1);
          indize_l::iterator hasi,amaitu;
          
          hasi = FORMA_taula[t-1].indizeak.begin();
          amaitu = FORMA_taula[t-1].indizeak.end();
          if ( find(hasi,amaitu,bi) == amaitu )
            FORMA_taula[t-1].indizeak.push_back(bi);
          HAT_taula[i].sartu_hitz_erref(p,erreferentzia);
        }
      }
    else
      {
       int_bikote erreferentzia(FORM,forma);

       if (forma >= FORMA_kopurua)
         {
	   FORMA_kopurua = forma+10;
	   FORMA_taula.resize(FORMA_kopurua);
	   //fprintf(stderr,"FORMA_taula handitu: %d\n", FORMA_kopurua);
         }
       FORMA_taula[forma].Hasieraketa(H,i,p);
       HAT_taula[i].sartu_hitz_erref(p,erreferentzia);
       forma++;
      }
  }

// *********************************************************************//
void  HAT_class::erantsi_LEMA(string H, int i, int p, IM im)
    // H hitza lemen taulan gordetzen du. Lema dagoeneko badago,
    // i HATean eta p posizio berriak erantsiko dizkio
    // dagokion informazio morfologiko eta guzti.
  {
    int t=0;
    int_bikote bi(i,p);

    if ((t = badago_LEMA(H))>0)
      {
        int_bikote erreferentzia(LEM,t-1);
//         indize_l::iterator hasi,amaitu;

        HAT_taula[i].sartu_hitz_erref(p,erreferentzia);

//         hasi = LEMA_taula[t-1].indizeak.begin();
//         amaitu = LEMA_taula[t-1].indizeak.end();
//         if ( find(hasi,amaitu,bi) == amaitu )
        LEMA_taula[t-1].erantsi_im(i,p,im);
      }
    else
      {
        int_bikote erreferentzia(LEM,lema);

        if (lema >= LEMA_kopurua)
          {
	    LEMA_kopurua=lema+10;
	    LEMA_taula.resize(LEMA_kopurua);
	    //fprintf(stderr,"LEMA_taula handitu: %d\n", LEMA_kopurua);
          }
        HAT_taula[i].sartu_hitz_erref(p,erreferentzia);
        LEMA_taula[lema].Hasieraketa(H,i,p,im);
        lema++;
      }
  }


// *********************************************************************//
void HAT_class::sartu_murriztapena(int h, int m, int p)
  {
    HAT_taula[h].sartu_murriztapena(m,p);
  }

// *********************************************************************//
void HAT_class::sartu_nagusia(int h, int i)
  // h. HATaren i posizioak emango dio HATari IMa.
  {
    HAT_taula[h].sartu_nagusia(i);
  }
  
// *********************************************************************//

// Bilaketa prozesuan erabiltzen diren metodoak.

// *********************************************************************//
int_lista  HAT_class::bilatu_FORMA(string H)
    // H hitza Formen taulan bilatzen du.
    // Emaitza : posizioen lista bat: i --> i-1 posizioan dago
    // Hau beharrezkoa da Maiuskulaz zein minuskulaz ager daitekeenean
    // forma bera. Adibidez: Euskal Herria / euskal eskola.
  {
     return badago_FORMA(H);
  }

// *********************************************************************//
int    HAT_class::bilatu_LEMA(string H)
    // H hitza Lemen taulan bilatzen du.
    // Emaitza : 0 --> ez dago      i --> i-1 posizioan dago
  {
     return badago_LEMA(H);
  }

// *********************************************************************//
void  HAT_class::markatu_FORMA(int i, int j)
    // i-1 posizioko forma agertzen den HATetan esaldiaren j. hitza
    // dela markatu
  {
    indize_l::iterator hasi,amaitu,t;
    
    hasi = FORMA_taula[i-1].indizeak.begin();
    amaitu = FORMA_taula[i-1].indizeak.end();

    for (t = hasi; t != amaitu; ++t)
      {
        int h, p;
        h = t->HAT_ind();
        p = t->posizioa();
        HAT_taula[h].markatu_osagaia(p,j);        
      }
  }

// *********************************************************************//
void  HAT_class::markatu_LEMA(int i, int j)
    // i-1 posizioko lema agertzen den HATetan esaldiaren j. hitzan
    // dagoela markatu
  {
    
    indize_l::iterator hasi,amaitu,t;
    
    hasi = LEMA_taula[i-1].indizeak.begin();
    amaitu = LEMA_taula[i-1].indizeak.end();

    for (t = hasi; t != amaitu; ++t)
      {
        int h,p;
        h = t->HAT_ind();
        p = t->posizioa();
        HAT_taula[h].markatu_osagaia(p,j);        
      }
  }

// *********************************************************************//
void  HAT_class::erantsi_HAT_markatua(int i)
    // i. HATa markatuen zerrendan sartzen du.
  {
    HAT_mark::iterator amaitu = HAT__mark.end();
    if ( find(HAT__mark.begin(),amaitu,i) == amaitu )
      HAT__mark.push_back(i);
  }

// *********************************************************************//
int    HAT_class::markatua_HAT(int i)
    // i. HATaren osagai guztiak markatuak dauden esango digu.
    // Emaitza : 0 --> ez daude denak  1 --> denak markatuak
  {
    return HAT_taula[i].markatua();
  }

// *********************************************************************//
int    HAT_class::konprobatu_murriztapenak_HAT(int i)
    // Esaldian egon daitekeen i. HATean ordenari buruzko 
    // murriztapenak betetzen diren konprobatu.
    // Emaitza : 0 --> ez dira betetzen  1 --> betetzen dira
  {
     return HAT_taula[i].konprobatu_murriztapenak();
  }

// *********************************************************************//
void  HAT_class::ken_markak_HAT(int i)
    // i. HATetik marka guztiak kenduko ditu.
  {
    HAT_taula[i].ken_markak();
  }

// *********************************************************************//
void  HAT_class::ken_HAT_markatua(int i)
    // i. HATa kentzen du zerrendatik.
  {
    HAT_mark::iterator t,amaitu;
    amaitu = HAT__mark.end();
    if ( ( t = find(HAT__mark.begin(),amaitu,i) ) != amaitu )
      HAT__mark.erase(t);
  }

// *********************************************************************//
void  HAT_class::hustu_HAT_markatua()
    // HAT markatuen zerrenda husten du.
  {
    HAT__mark.clear();
  }

// *********************************************************************//
HAT_class::~HAT_class()
    // funtzio suntsitzailea
  {
//     delete FORMA_taula;
//     delete LEMA_taula;
//     delete HAT_taula;
  }

// *********************************************************************//
void  HAT_class::inprimatu()
    // HAT guztiak inprimatu.
  {
    FILE *Formak,*Lemak,*Hatak;
    int i;

    if ((Formak = fopen("formak.out","w")) == NULL)
      {
        fprintf(stderr,"errorea formak.out irekitzean\n");
        exit(2);
      }
    if ((Lemak = fopen("lemak.out","w")) == NULL)
      {
        fprintf(stderr,"errorea lemak.out irekitzean\n");
        exit(2);
      }
    if ((Hatak = fopen("hatak.out","w")) == NULL)
      {
        fprintf(stderr,"errorea hatak.out irekitzean\n");
        exit(2);
      }
    i = 0;
    while (i<forma)
      {
       fprintf(Formak,"%s ",FORMA_taula[i].eman_Hitza().c_str());
       indize_l::iterator hasi,amaitu,t;
    
       hasi = FORMA_taula[i].indizeak.begin();
       amaitu = FORMA_taula[i].indizeak.end();

       for (t = hasi; t != amaitu; ++t)
         {
           fprintf(Formak,"(%d,%d) ",t->HAT_ind(),t->posizioa());
         }

       fprintf(Formak,"\n");
       i++;
      }
    fclose(Formak);

    i = 0;
    while (i < lema)
      {
       LEMA_taula[i].inprimatu(Lemak);
       i++;
      }
    fclose(Lemak);
  }



// *********************************************************************//
// Esaldiaren gaineko eragiketak

// *********************************************************************//
void  HAT_class::Esaldi_Sartu_forma(string f, string e)
    // Esaldiaren hitz_indizeari dagokion hitza hasieratu f forma,
    // e etiketa eta begiratu behar den ala ez sartuaz.
  {
    Esaldi[hitz_indizea].Sartu_forma(f,e);
  }

// *********************************************************************//
void  HAT_class::Esaldi_anali_insert(AN an)
    // Esaldiaren hitz_indizeari dagokion hitzari an analisia erantsi.
  {
    if (hitz_indizea == HITZ_kopurua)
      {
	HITZ_kopurua = HITZ_kopurua+10;
	Esaldi.resize(HITZ_kopurua);
	//fprintf(stderr,"Esaldi handitu: %d\n", HITZ_kopurua);

      }
    Esaldi[hitz_indizea].anali.push_back(an);
  }

// *********************************************************************//
void  HAT_class::Esaldi_reset_hitza()
    // Esaldian dauden hitzak ezabatu eta indizea hasieratu.
  {
    if (hitz_indizea)      // hitzik bazegoen analisi listak ezabatu.
      for (int i=0;i<hitz_indizea;i++)
        {
         Esaldi[i].anali.clear();
         Esaldi[i].hat_lista.clear();
         Esaldi[i].destroy_hat_analisi();
        }
    hitz_indizea = 0;
  }

// *********************************************************************//
void  HAT_class::Esaldi_next_hitza()
    // hitz_indizea eguneratu.
  {
   hitz_indizea++;
  }

// *********************************************************************//
void HAT_class::inprimatu_Esaldi()
  {
    int i = 0;
    while (i<hitz_indizea) {
      if ( Esaldi[i].terminoa_da() ) {
	Esaldi[i].inprimatu();
	i += Esaldi[i].eman_osagai_kopurua();            
      }
      else { 
	Esaldi[i].inprimatu();
	i++;
      }
    }
  }

// *********************************************************************//
//};
