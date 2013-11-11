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


#ifndef __ANABIHURTZAILEA_H__
#define __ANABIHURTZAILEA_H__

#include <stdio.h>
#include <string>
#include <valarray>
#include <strings.h>
#include <stdlib.h>
#include <vector>
//#include <pcre.h>
#include <pcre++.h>
#ifdef _USE_FOMA_
#define ANMAX 600
#define LUZMAXAN 1000
#else
#include "anali_xerox.h"
#endif

using namespace std;
using namespace pcrepp;

class anaBihurtzailea {
 const string kenduInfoEzKonparagarria(const string analisiOsoa);
 const string bihurtuEratorria(const string analisiOsoa);
 Pcre ez_zenb, diak, diak_98, bat, bi, hiru, lau, zortzi, bederatzi;
 Pcre kenAld, kenSar, kenSarrera, kenAldaera, kenTwol, kenPlusMinus, kenErrorKode, kenAoi, kenAdoin, kenBim, kenBimG;
 Pcre lorBim,bst;
 Pcre bilatuHasiera, aldatuEraazp, aldatuAdoin, aldatuAoi, aldatuSar, aldatuSarrera, aldatuAdoinPar, aldatuAoiPar, aldatuSarPar, aldatuSarreraPar;
 Pcre kat, azp, mtkat;
 typedef pair<string,string> tag_trig;
 map<tag_trig,int> trigramak;
 map<string,int> zenbat_etiketako;
 int edbl_bertsioa;
 string kenduMaj(const string & str);
 string jarriMaj(const string & str);

 public:
 anaBihurtzailea();
 const string lispifikatu(char *analisia,int ident_da,int zen_da, int zen_dek_da, int errom_da);
 int desanbAldaerak(int m, char anal[][LUZMAXAN],char motak[],int distantziak[],int distantzia_minimoa);
 int desanbEratorpena(int m, char anal[][LUZMAXAN],char motak[],int distantziak[]);
 int desanbLexGabe(int m, char anal[][LUZMAXAN],char motak[],int distantziak[], string forma);
 int desanbKatTrig(int m, vector<string> &ema_ana,char mot[], valarray<int> dist) ;
 int desanbEstandar(int m, char anal[][LUZMAXAN],char motak[],int distantziak[], string forma);
 const string kenduBim(const string analisiOsoa);
 const string lortuBim(const string analisiOsoa);
 const string aldatuBim(string analisiOsoa, string bimStr);
 string aldatuSarInfo(const string analisia, char bim_erab[], int SARda);
 string aldatuSarInfoPar(const string analisia, const char bim_erab[], int SARda);
 const string bihurtu_xerox_lemati (string aldatzeko);
 const string lortuErabLexInfo(string bimStr, string analisia);
};

#endif // __ANABIHURTZAILEA_H__
