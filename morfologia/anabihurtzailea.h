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
