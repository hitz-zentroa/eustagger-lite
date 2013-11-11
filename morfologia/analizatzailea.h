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


#include <string>
#include <vector>
#include "anabihurtzailea.h"
#ifdef _USE_FOMA_
#include "fomamorf.h"
#endif

#define ESTANDAR_AN 0
#define TAULAN      1
#define ESTANDAR_PIPE 2

using namespace std;
using namespace pcrepp;


class analizatzailea {
  /* aukerak: -L srrera berezia
     -2 bigarren aukera estandar eta aldaera batzuetan
     -E <erab_hizt> erabiltzailearen hiztegia
     formatua: tuntunA[KAT_IZE][AZP_ARR]
     konbinatu datezke: anali_xerox_erab -2E lex_erab.lex */
    
  /*extern int ireki_maiztasun_handikoak();
    extern int badago_hitza_maiztasun_handikoak(char *gakoa);*/

// int ken_majusk(char *st);
 void lortu_hitza(char *hitza,vector<string> *sarrera,vector<string> *irteera,int *indizea);
 int analizatu_aukerak_hitza(int bigarren_aukera, int non, char *hitzasar, char anal[][LUZMAXAN],char motak[],int distantziak[]);
//#ifndef _USE_FOMA_
 int analizatuErabLex(char *hitza,int m, char anal[][LUZMAXAN], int *beste_analisia, char *lema_ident,  vector<string> *emaitza);
//#endif
 void lortu_lema_ident(char *hitza,char *lema_ident);
 void lortu_lema_zen_dek(char *lema_ident);
 void inprimatu_ident_analisia(char *analisia, int *ident_analisia, char* lema_ident, vector<string>* emaitza);
 void inprimatu_lexgabeko_analisia(char *analisia, int *i, char* lema_ident,  vector<string>* emaitza);
 void inprimatu_aldaera_analisia(char *analisia, int *i, int dist, char* lema_ident, vector<string>* emaitza);
 void inprimatu_estandar_analisia(char *analisia, int *i, char* lema_ident, vector<string>* emaitza);
 void inprimatu_goiburukoa(char *hitza, char mota,  vector<string>* emaitza);
 void lortu_aurrizki_kar_ber(char *hitza,char *lema_ident);

#ifdef _USE_FOMA_
 fomaMorf transFoma;
#endif

#ifndef __BRIDGE_VARIANTS__
 void sortu_banaketak(int mm,char anal_bana[][LUZMAXAN],map<string,string> &an_ban_map);
 void eman_banaketa(char an_lag[], map<string,string> &an_ban_map,char banaketa[]);
 int desanb_aldaerak_cstr(int m, char anal[][LUZMAXAN],char motak[],int distantziak[]); //kentzeko
 int lortu_distantzia(char an_lag[],char hitza[],char banaketa[],char aldaera[]);
 int distantz(char *forma, char *lema, char *aldaera);
#endif //__BRIDGE_VARIANTS
 int desanb_eratorpena_cstr(int m, char anal[][LUZMAXAN],char motak[],int distantziak[]); //kentzeko
 anaBihurtzailea bihur;

 // int aurrekoa_puntua;
 int den_mai;
 int den_mai_dek;
 int zen_dek;
 int edbl_bertsioa;
/*  int aurrekoa_den_mai; */
/*  int aurrekoa_has_mai; */
 int has_mai;
 int kar_ber;
 int maiztasun_handikoak;
 int ez_estandarrak;

 int Sarrera_berezia; /*** 99/9/2 -L aukerarako */
 int lexiko_uzei;
 int bigarren_aukera; /*** 2000/11/20 -2 aukerarako */
 int lex_ald; /*** 2000/12/20 erabiltzailearen lexikorako -L eta -2 ez dira onartzen*/
 int irteera_parentizatua;
 int irteera_nola;
 char forma_ident[LUZMAXAN];
 int ident_da;
 int zen_da;
 int zen_dek_da;
 int errom_da;
 int distantzia_minimoa;
 int deslok; /*** desanbiguazio lokala aplikatu ala ez. Defektuz bai */

 public:
 analizatzailea() {
/*    aurrekoa_puntua = 1; */
   den_mai = 0;
   den_mai_dek = 0;
   zen_dek = 0;
/*    aurrekoa_den_mai = 0; */
/*    aurrekoa_has_mai = 0; */
   has_mai = 0;
   kar_ber = 0;
   maiztasun_handikoak = 0;
   ez_estandarrak = 0;
   irteera_parentizatua = 0;
   ident_da = 0;
   zen_da = 0;
   zen_dek_da = 0;
   errom_da = 0;
   forma_ident[0] = '\0';
   deslok = 1;
   edbl_bertsioa = 4;

   Sarrera_berezia = 0 ; /*** 99/9/2 -L aukerarako */
   lexiko_uzei = 0;
   bigarren_aukera = 0; /*** 2000/11/20 -2 aukerarako */
   lex_ald=0; /*** 2000/12/20 erabiltzailearen lexikorako -L eta -2 ez dira onartzen*/
   irteera_nola = ESTANDAR_AN;
   distantzia_minimoa = 1; /*** parametro bat definitu beharko litzateke */
 }
 void hasieraketak(int sar_lem, int lex_uzei, int bigarren, int ez_est, int erab_lex, string &lexiko_izena, int parentizatua, int deslokala);
 void amaierakoak();
 vector<string> analizatu(int modua,vector<string> *sarrerako_taula);
 // void analizatu();
 void analizatu_hitza_trans(char hitza[], int modua, vector<string> *sarrerako_taula,vector<string> *emaitza,int *indizea);
};
