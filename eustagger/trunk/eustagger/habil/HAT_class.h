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


#ifndef HAT_CLASS_H
#define HAT_CLASS_H

#include "HAT.h"
#include "FORMA.h"
#include "LEMA.h"
#include "IM.h"
#include "IM_info.h"
#include "HITZ.h"
#include <vector>
#include <map>

#define MAX_HITZ 4000 // esaldiak izan dezakeen hitz-kopuru maximoa

typedef std::list<int> int_lista;
typedef int_lista HAT_mark;

class HAT_class
{
  // HATak kudeatzeko datu_mota
  
  // Aldagaiak
  
  std::vector<HAT>        HAT_taula;         // HATen informazioa gordetzeko taula
  std::vector<FORMA>      FORMA_taula;       // Formen taula
  std::vector<LEMA>       LEMA_taula;        // Lemen taula
  HAT_mark                HAT__mark;         // HAT markatuen zerrenda

  int                     HAT_kopurua;       // Zenbat HAT
  int                     FORMA_kopurua;     // Zenbat forma desberdin
  int                     LEMA_kopurua;      // Zenbat lema desberdin
  int                     HITZ_kopurua;      // Zenbat hitz desberdin esaldi batean
  
  int                     hat;               // HAT_taulan hutsik dagoen lehenengo indizea
  int                     forma;             // FORMA_taulan hutsik dagoen lehenengo indizea
  int                     lema;              // LEMA_taulan hutsik dagoen lehenengo indizea
  
  // Sarrerako testua gordetzen joateko aldagaiak:
  std::vector<HITZ>       Esaldi;
  int                     hitz_indizea;
  
  // Eragiketak
  int_lista  badago_FORMA(std::string H);
  // H hitza formen taula dagoen esaten digu.
  // Emaitza : posizioen lista bat: i --> i-1 posizioan dago
  // Hau beharrezkoa da Maiuskulaz zein minuskulaz ager daitekeenean
  // forma bera. Adibidez: Euskal Herria / euskal eskola.
  int  badago_LEMA(std::string H);
  // H hitza lemen taula dagoen esaten digu.
  // Emaitza : 0 --> ez dago      i --> i-1 posizioan dago
  void aukeratu_hat_seguruak(int_lista *zeintzuk, int_lista *ona);
  // listako HATen artekoan aukeratu ondokoaren arabera:
  // - Elementu gehien dituena
  // - Osagaien arteko distantzia txikiena
  // - Ordenatua
  // Seguruak badira, bakarra aukeratu. Bestela ordenatu.
  
public:
  
  // Sarrerako fitxategitik irakurtzean aldagaiak hasieratzeko
  // erabiltzen diren metodoak.
  
  HAT_class()
  {
    HAT_kopurua = 0;
    FORMA_kopurua = 0;
    LEMA_kopurua = 0;
    HITZ_kopurua = 0;
    hat = 0;
    forma = 0;
    lema = 0;
    hitz_indizea = 0;
  }
  void  Hasieraketa();
  // Sarrerako fitxategitik lortutako datuen arabera memoria alokatu
  // eta taulak hasieratzen ditu.
  void  erantsi_HAT(std::string lem, IM him, int kop, int seg);
  // HATen taulan hutsik dagoen lehenengo posizioan gordetzen du HATa.
  void  erantsi_FORMA(std::string H, int i, int p);
  // H hitza formen taulan gordetzen du. Forma dagoeneko badago,
  // i indizea eta p posizio berriak erantsiko dizkio.
  int  badago_HAT(std::string H, std::string ima);
  // H hitza HATen taula dagoen esaten digu.
  // Gainera, baldin badago, ima IMarekin dagoen konprobatuko du.
  // Emaitza : 0 --> ez dago      i --> i-1 posizioan dago
  int  zein_HAT();
  // Hutsik dagoen lehenengo HATaren indizea ematen du.
  // Emaitza : hat
  void  erantsi_LEMA(std::string H, int i, int p, IM im);
  // H hitza lemen taulan gordetzen du. Lema dagoeneko badago,
  // i indizea eta p posizio berriak erantsiko dizkio dagokion 
  // informazio morfologiko eta guzti.
  void  sartu_murriztapena(int h, int m, int p);
  // h. HATaren p posizioan m murriztapena gorde.
  void  sartu_nagusia(int h, int i);
  // h. HATaren i posizioak emango dio HATari IMa.
  
  // Bilaketa prozesuan erabiltzen diren metodoak.
  
  int_lista bilatu_FORMA(std::string H);
  // H hitza Formen taulan bilatzen du.
  // Emaitza : posizioen lista bat: i --> i-1 posizioan dago
  // Hau beharrezkoa da Maiuskulaz zein minuskulaz ager daitekeenean
  // forma bera. Adibidez: Euskal Herria / euskal eskola.
  int    bilatu_LEMA(std::string H);
  // H hitza Lemen taulan bilatzen du.
  // Emaitza : 0 --> ez dago      i --> i-1 posizioan dago
  void  markatu_FORMA(int i, int j);
  // i-1 posizioko forma agertzen den HATetan esaldiaren j. hitza
  // dela markatu
  void  markatu_LEMA(int i, int j);
  // i-1 posizioko lema agertzen den HATetan esaldiaren j. hitzan
  // dagoela markatu
  void  erantsi_HAT_markatua(int i);
  // i. HATa markatuen zerrendan sartzen du.
  int    markatua_HAT(int i);
  // i. HATaren osagai guztiak markatuak dauden esango digu.
  // Emaitza : 0 --> ez daude denak  1 --> denak markatuak
  int    konprobatu_murriztapenak_HAT(int i);
  // Esaldian egon daitekeen i. HATean ordenari buruzko 
  // murriztapenak betetzen diren konprobatu.
  // Emaitza : 0 --> ez dira betetzen  1 --> betetzen dira
  void  ken_markak_HAT(int i);
  // i. HATetik marka guztiak kenduko ditu.
  void  ken_HAT_markatua(int i);
  // i. HATa kentzen du zerrendatik.
  void  hustu_HAT_markatua();
  // HAT markatuen zerrenda husten du.
  ~HAT_class();
  // funtzio suntsitzailea
  void  inprimatu();
  

  // Esaldiaren gaineko eragiketak
  
  void  Esaldi_Sartu_forma(std::string f, std::string e);
  // Esaldiaren hitz_indizeari dagokion hitza hasieratu f forma,
  // e etiketa sartu eta begiratu behar den ala ez erabakiaz.
   
  void  Esaldi_anali_insert(AN an);
  // Esaldiaren hitz_indizeari dagokion hitzari an analisia erantsi.

  void  Esaldi_reset_hitza();
  // Esaldian dauden hitzak ezabatu eta indizea hasieratu.
  
  void  Esaldi_next_hitza();
  // hitz_indizea eguneratu.
  
  void  inprimatu_Esaldi();
  // Momentuan dugun esaldia inprimatu analisietan HATenak tartekatuz.
    
  void  bilatu_HAT_Esaldi();
  // Begiratu momentuko esaldian HATen bat dagoen.
  // Gainera, Esaldian informazioa gordetzen duen heinean,
  // HAT markatuetatik markak ezabatuz joango da.
  
  void  sinplifikatu_HAT_markatuak();
  // Elementu amankomunak dituzten HATak detektatzen badira,
  // HATik luzeena aukeratuko du, besteak ezabatuz.
};
#endif
