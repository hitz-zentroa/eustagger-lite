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


//#include "morfsarFormatu.h"
#include "constants_decl.h"
#include "morfosraw.h"
#include "morfsar2raw.h"
#ifdef _USE_SWI_
#include "SWI-cpp.h"
#endif
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "getenvvar.h"

using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::stringstream;

#define TO_MORFSAR   "TO_MORFSAR"               // soilik morfsar-eraino egin
#define FROM_MORFSAR "FROM_MORFSAR"             // morfsar sarreratik eta aurrera
#define DEBUG        "DEBUG"                    // osoa baina tarteko fitxategiak gordez
#define UPDATE       "UPDATE"                   // morfosintaxi bertsio aldatzean fitxategiak eguneratzeko

#define ALL          "ALL"                      // osoa (defektuzkoa)


int edbl_bertsioa = 4;
// MorfsarFormatu morfSar;

int main(int argc, char **argv){

#ifdef _USE_SWI_
  PlEngine e(argv[0]);
#endif

  int errflg =0, aflg=0,hflg=0;
  bool cg3form = false;
  string execpr = string(argv[0]);
  if (execpr.find('/') == string::npos) {
    string tmpX = getEnvVar("IXA_PREFIX");
    tmpX = tmpX + "/bin/" + execpr;
    execpr = tmpX;
  }
  string oinIzen;
  string prozesuMota = ALL;
  int tamaina = 0;
  int c;
  while ((c= getopt(argc, argv, "a:m:k:hc")) != EOF) {
    switch (c) {    
    case 'a': {
      oinIzen = optarg;
      aflg++;
      break;
    }
    case 'm': {
      string strLag = optarg;
      if (strLag==TO_MORFSAR || strLag==FROM_MORFSAR || strLag==DEBUG || strLag==UPDATE||strLag==ALL) prozesuMota = strLag; 
      else errflg++;
      break;
    }
    case 'k': 
      tamaina = atoi(optarg);
      break;
    case 'h':
      hflg++;
      break;
    case 'c':
      cg3form=true;
      break;
    case '?':
      errflg++;
      break;
    }    
  }  
  if ((!errflg && !aflg) || hflg) {
     stringstream morfosintaxiaVersion;
     morfosintaxiaVersion << "morfosintaxia_raw honako aukerekin konpilatu da:" << endl;
#ifdef _USE_FOMA_
    morfosintaxiaVersion << "\tFOMAko transduktoreak erabilita" << endl;
#else
    morfosintaxiaVersion << "\tXEROXeko transduktoreak erabilita" << endl;
#endif // _USE_FOMA_
#ifdef _USE_SWI_
    morfosintaxiaVersion << "\tSWI-prolog erabilita morfosintaxian" << endl;
#else
    morfosintaxiaVersion << "\tsicstus-prolog erabilita morfosintaxian" << endl;
#endif // _USE_SWI_

    cerr << endl;
    cerr << "erabilera: morfosintaxia_raw [-c] -a <oinIzen>  [-m TO_MORFSAR|FROM_MORFSAR|DEBUG|ALL|UPDATE] [-k 0|1|2|... ]" << endl;
    cerr << "\t-c => irteera CG3 formatuan" << endl;
    cerr << "\t-a => morfosintaxia burutzeko oinarri izena (.segp luzapenik gabe)" << endl;
    cerr << "\t-m => morfosintaxi prozesuaren faseak:" << endl;
    cerr << "\t\t TO_MORFSAR=> soilik morfsar fitxategia lortu harte" << endl;
    cerr << "\t\t FROM_MORFSAR=> morfsar fitxategitik abiatu" << endl;
    cerr << "\t\t DEBUG=> prozesu osoa baina tarteko fitxategiak berreskuratuz (debug katalogoa)" << endl;
    cerr << "\t\t ALL=> prozesu osoa (defektuzkoa)" << endl;
    cerr << "\t\t UPDATE=> Morfosintaxi bertsio aldaketak amaraunean eguneratzeko" << endl;
    cerr << "\t-k => prologen sarrerarentzako aldiko forma kopurua. Soilik ALL eta DEBUG aukerarekin" << endl;
    cerr << "\t\t - Defektuz => 0 "<< endl;
    cerr << "\t\t - Forma guztiak pasatzeko => 0" << endl;
    cerr << "\t\t - OHARRA => K txikitzen den neurrian morfosintaxia moteldu egiten da" << endl << endl;
    cerr << morfosintaxiaVersion.str() ;

    exit(EXIT_FAILURE);
  }
  extern int   ana2morfsarparse();	        // LEX-YACC modulua
  extern FILE* ana2morfsarin;       	        // LEX-YACC moduluaren sarrerako FILE*;

  if (prozesuMota==TO_MORFSAR) {
    Ana2Morfsar morfsarItzul;
    string segpIzen = oinIzen+ ".segp";
    string morfsarFitx=oinIzen+".morfsar";
    morfsarItzul.setAnaFitx(segpIzen);
    morfsarItzul.current(morfsarFitx);
  }
  if (prozesuMota==FROM_MORFSAR) {
    Morfsar2Raw morfsar2raw(cg3form);
    string morfsarFitx=oinIzen+".morfsar";
    string morfFitx=oinIzen+".morf";
    morfsar2raw.execute(morfsarFitx, morfFitx);
  }
  if (prozesuMota==DEBUG || prozesuMota==ALL) {
    bool debug=(prozesuMota==DEBUG)?true:false;
    string segpIzen = oinIzen + ".segp";
    MorfosRaw morfosintaxia(execpr, oinIzen, tamaina, debug, cg3form);
    morfosintaxia.sortuAnalisiak(segpIzen);
    morfosintaxia.writeResult();
  }
  return(EXIT_SUCCESS);
}
