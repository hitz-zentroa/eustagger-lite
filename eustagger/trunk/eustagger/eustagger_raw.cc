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


extern void segHasieraketak(int sar_lem, int lex_uzei, int bigarren, int ez_est, int erab_lex, string &lexiko_izena, int parentizatua, int deslokala);
extern void segAmaierakoak();

extern void segmentazioaSortuRaw(string &fitxategiIzena, string &segIrteera);
extern void morfosintaxiaSortuRaw(string &fitxategiIzena, string &segIrteera, bool haul_seguruak, bool cg3form);
extern int prozesatuCG3Raw(int maila, int cg3form, string &oinIzen);

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

  cerr << "Erabilera:" <<endl;
  cerr << "eustagger_raw [-hs] [-m maila]" << endl;
  cerr << "-h laguntza hau" << endl;
  cerr << "-s HAUL seguruak prozesatu (defektuz ez)" << endl;
  cerr << "-m [1|2|3] (defektuz 2)" << endl;
  cerr << eustaggerVersion.str() ;
  exit(1);
}


std::string getEnvVar(std::string const& key);


int main(int argc, char *argv[])
{
 int Sarrera_berezia = 1 ; /*** 99/9/2 -L aukerarako */
 int lexiko_uzei = 0;
 int bigarren_aukera = 0; /*** 2000/11/20 -2 aukerarako */
 int lex_ald = 0; /*** 2000/12/20 erabiltzailearen lexikorako -L eta -2 ez dira onartzen*/
 int ez_estandarrak = 0;
 int maila = 2;
 int deslokala = 1;
 int parentizatua = 1;
 bool haul_seguruak = false;
 int cg3form = OUT_MG; // Defektuz hau beharko luke: OUT_LEM;
 char c;
 string lex_izena; 
 int IRT = IN_MORF;

 while ((c = getopt(argc, argv, "sShHM:m:")) != EOF) {
   switch (c) {
   case 'S':
   case 's': haul_seguruak = 1; break;
   case 'M':
   case 'm': maila =atoi(optarg); break;
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

 if (optind < argc) {
   for (int i=optind;i<argc;i++) {
     string fitxategiIzena = argv[i];
     string segIrteera;
     segmentazioaSortuRaw(fitxategiIzena,segIrteera);
     morfosintaxiaSortuRaw(fitxategiIzena,segIrteera,haul_seguruak,cg3form == OUT_MG); // Honek sortzen du .morf/.hat?
     // Hemen faltako litzateke CG3 formatua sortzea beharrezkoa balitz
     prozesatuCG3Raw(maila, cg3form, fitxategiIzena) ;

   }
 }
 else {
   help();
 }
 segAmaierakoak();
 return(0);
}

