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


#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>

#include "dat_orok.h"
#include "constants_decl.h"

#include "formatua.h"

#ifdef _USE_SWI_
#include "SWI-cpp.h"
#endif

using namespace std;


int edbl_bertsioa = 4;

const int NAF_OUTPUT    = 3;

extern void segHasieraketak(int sar_lem, int lex_uzei, int bigarren, int ez_est, int erab_lex, string &lexiko_izena, int parentizatua, int deslokala);
extern void segAmaierakoak();

extern void segmentazioaSortuRaw(string &fitxategiIzena, string &segIrteera, int zuriuneetan);
extern void morfosintaxiaSortuRaw(string &fitxategiIzena, string &segIrteera, bool haul_seguruak, bool cg3form);
extern int prozesatuCG3Raw(int maila, string &oinIzen, int zuriuneetan, int format);

void help() {
  stringstream eustaggerVersion;
  eustaggerVersion << "eustagger honako aukerekin konpilatu da:" << endl;
#ifdef _USE_FOMA_
  eustaggerVersion << "\tFOMAko transduktoreak erabilita" << endl;
#else
  eustaggerVersion << "\tXEROXeko transduktoreak erabilita" << endl;
#endif // _USE_FOMA_
#ifdef _USE_SWI_
  eustaggerVersion << "\tSWI-prolog erabilita morfosintaxian" << endl;
#else
  eustaggerVersion << "\tsicstus-prolog erabilita morfosintaxian" << endl;
#endif // _USE_SWI_
#ifdef __BRIDGE_VARIANTS__
  eustaggerVersion << "\taldaeren analisirik ez da egingo" << endl;
#else
  eustaggerVersion << "\taldaeren analisia egingo da" << endl;
#endif //__BRIDGE_VARIANTS__

  cerr << "Erabilera (BAKARRIK SARRERA ESTANDARRA BERBIDERATUZ):" <<endl;
  cerr << "ixa-pipe-pos-eu [-hs] [-m maila]" << endl;
  cerr << "-h laguntza hau" << endl;
  cerr << "-s HAUL seguruak prozesatu (defektuz ez)" << endl;
  cerr << "-m [0|1|2|3|4] (defektuz 2)" << endl;
  cerr << "-m 0 denean ez du desanbiguatuko" << endl;  
  cerr << "-m 4 denean bakarrik aplikatuko du CG3 desanbiguatzeko" << endl;
  cerr << eustaggerVersion.str() ;
  exit(EXIT_FAILURE);
}


std::string getEnvVar(std::string const& key);


int main(int argc, char *argv[])
{
 int Sarrera_berezia = 1 ; /*** 99/9/2 -L aukerarako */
 int lexiko_uzei = 0;
 int bigarren_aukera = 0; /*** 2000/11/20 -2 aukerarako */
 int lex_ald = 0; /*** 2000/12/20 erabiltzailearen lexikorako -L eta -2 ez dira onartzen*/
 int ez_estandarrak = 0;
 int zuriune_token = 0;
 int maila = 2;
 int deslokala = 1;
 int parentizatua = 1;
 int out_format = NAF_OUTPUT;
 bool haul_seguruak = false;
 char c;
 string lex_izena; 
 string format;

 while ((c = getopt(argc, argv, "sShHzZm:M:f:F:")) != EOF) {
   switch (c) {
   case 'S':
   case 's': haul_seguruak = 1; break;
   case 'Z':
   case 'z': zuriune_token = 1; break;
   case 'M':
   case 'm': maila =atoi(optarg); break;
   case 'F':
   case 'H':
   case 'h':
   default: help();
   }
 }


#ifdef _USE_SWI_
 PlEngine e(argv[0]);
#endif

 if (Sarrera_berezia) parentizatua = 1;

 edbl_bertsioa = 4;

 segHasieraketak(Sarrera_berezia,lexiko_uzei,bigarren_aukera,ez_estandarrak,lex_ald,lex_izena,parentizatua,deslokala);

 if (optind == argc) {

   char pid[10];
   sprintf(pid, "%d", getpid());
   string fitxategiIzena = "-"; // ixa-pipeek sarrera estandarretik elikatzen dira
   string segIrteera;
   segmentazioaSortuRaw(fitxategiIzena,segIrteera, zuriune_token);
   fitxategiIzena += pid;
   morfosintaxiaSortuRaw(fitxategiIzena,segIrteera,haul_seguruak,OUT_MG); 
   prozesatuCG3Raw(maila,fitxategiIzena, zuriune_token, out_format) ;

 }
 else {
   help();
 }
 segAmaierakoak();
 return(0);
}

