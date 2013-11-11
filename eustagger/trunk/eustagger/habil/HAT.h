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


#ifndef HAT_H
#define HAT_H

#include "IM.h"
#include "int_bikote.h"
#include <list>
#include <vector>

#include "HAT_kom.h"

typedef int_bikote erref;
typedef std::list<erref> erref_list;
typedef std::list<int> int_l;
typedef std::list<int> int_l_e;

#define MAX_ERREP 10
#define MARGEN 0

class HAT
{
// Aldagaiak
  std::string     lema;             // HATaren lema.
  IM         im;               // HATaren kategoria eta azpikategoria.
  int        osagai_kopurua;   // Zenbat osagai dituen.
  int        nagusia;          // Osagai nagusia zein den.
  std::vector<std::string>     nagusiaren_im;    // Osagai naguasiak behar duen IM minimoa.
  int        segurtasuna;      // HAT segurua den.
  std::vector<erref_list> hitz_erref;      // Osagaiak non gorde diren.
  std::vector<int_l>      markatuak;       // Momentuko esaldian agertu diren.
  std::vector<int>        murriztapenak;   // Osagaien artean dauden ordenari buruzko murriztapenak.

  std::vector< std::vector<int> >        detektatuak;
                               // HATaren osagaiak non detektatu diren
                               // murriztapenak betetzen dituztenean.
  int      detek;              // Zenbat aldiz detektatu den.
//  std::string   oharra;             // sarrera fitxategiko oharra.

// Eragiketak
  int      murriz(int dat, int m, int emaitza[]);

  int      murriztapenak_bete(int e1, int e2, int m);
    // e1 eta e2 indizeen artean m murriztapena betetzen den esaten du.
    // m murriztapenak hiru balio hauek har ditzake:
    // 1.- JARRA --> jarraian joan behar dute.
    // 2.- ETENA --> erdian elementuren bat egon daiteke.
    // 3.- EZORD --> jarraian edo alderantzizko ordenean joan daitezke.
    // Emaitza : 0 --> ez da m murriztapena betetzen.
    //           1 --> m murriztapena betetzen da.

public:
       HAT();
    // hasieraketa-funtzioa.

       HAT(const HAT &h);
    // Kopia-hasieraketa funtzioa.

  void Hasieraketa(std::string lem, IM him, int kop, int seg);
    // HATaren lema eta IMa gorde eta gainontzekoentzako memoria alokatu.

  void sartu_hitz_erref(int p, erref erreferentzia);
    // HATaren osagaiak forma edo lema diren eta dagokien taulan zein
    // posiziotan dauden gorde.

  void sartu_murriztapena(int m, int i);
    // i. eta i+1. osagaien arteko ordenari dagokion murriztapena.

  void sartu_nagusia(int i);
    // i. osagaiak emango dio IMa HATari
    // -1 balioa izango du IMrik jasotzen ez duenean.

  void markatu_osagaia(int i, int j);
    // i. osagaia esaldiaren j. posizioan agertu dela markatu.
    // HAT markatuen zerrendan ez badago, sartzen du.

  void ken_marka_osagaia(int i, int j);
    // i. osagaitik j. posizioa ezabatu. 

  void ken_markak();
    // HATean dauden marka guztiak ezabatu.

  void ken_markak_detektatuak();
    // detektatutakoak ezabatzen ditu.

  int  markatua();
    // HATaren osagai guztiak markatuak dauden.
    // Emaitza : 0 --> ez daude denak markatuak.
    //           1 --> denak markatuak.

  int  konprobatu_murriztapenak();
    // Hitzen agerpenetan ordenari dagozkion murriztapenak betetzen diren
    // konprobatu.
    // Emaitza : 0 --> ez dira murriztapen guztiak betetzen.
    //           1 --> murriztapen guztiak betetzen dira.

  int  eman_osagai_kopurua();
    // HATaren osagai-kopurua emango du.

  int  eman_nagusia();
    // HATari IMa emango dion osagaia emango du.

  std::string eman_nagusiaren_im(int p);
    // HATari IMa emango dion osagaiaren IM minimoa.

  int  eman_detektatuak(std::vector< std::vector<int> >& emaitza);
    // HATean murriztapenak betetzen dituzten hitzak itzultzen ditu.
    // Emaitza : HAT hau zenbatetan detektatu den momentuko esaldian.

  void sartu_detektatuak(std::vector< std::vector<int> > sar,std::string nagusiak[MAX_ERREP]);
    // HATean murriztapenak betetzen dituzten hitzak gordetzen ditu.

  int zenbat_detektatuak();
 

  int  forma_da(int i);
    // i. posizioko osagaia forma den ala ez.

  std::string eman_LEMA();
    // HATaren lema ematen du.

  IM   eman_KAT_AZP();
    // HATaren informazioa ematen du.

  int  segurua();
    // HATa segurua den esaten du.
    // Emaitza : 0 --> ez da segurua.
    //           1 --> segurua.

  int  konparatu(std::string H);
    // H lema-rekin konparatzen du.
    // Emaitza : <0 --> H < lema
    //            0 --> H == lema
    //           >0 --> H > lema

       ~HAT();
    // funtzio suntsitzailea.

  HAT  operator =(const HAT &h);
    // asignazioa;

};

#endif
