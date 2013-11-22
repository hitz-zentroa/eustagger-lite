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
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#include "morfosraw.h"

using namespace std;

string getEnvVar(string const& key);

extern int hat_kargaparse(void);
extern FILE *hat_kargain;
FILE *irteera_fitx;
extern const char* PHAT;
extern const char* SEG_FITX;

char *testu_buffer;
int buffer_size;


void morfosintaxiaSortuRaw(string &oinIzen, string &segIrteera, bool haul_seguruak, bool cg3form) {
 // Definitu morfosintaxi exekutagarriaren izena ingurune aldagaien arabera
  string execPath;

  string tmpPath = getEnvVar("IXA_PREFIX");
  if (tmpPath.length()>0) {
    execPath = tmpPath + "/bin/";
  }

//   string tmpOs ;// = getEnvVar("OSTYPE"); INSTALATUTAKOAN EZ DAUKA ATZIZKIA

  execPath = execPath + "morfosintaxia_raw";
  #ifdef _USE_SWI_
  execPath = execPath + "_swi";
  #endif

  string segpIzen = oinIzen + ".segp";
  bool cg3zuz = cg3form;
  if (haul_seguruak) cg3zuz = false; // habil-ek ez du CG3 formatua jaten
  MorfosRaw morfosintaxia(execPath, oinIzen, 100, false,cg3zuz); // 1 beharrean 100 beharko luke
  morfosintaxia.sortuAnalisiak(segIrteera);


  if (haul_seguruak) {
    //HEMEN HABIL ERABILI ETA EMAITZA IDATZI
    FILE *jat_fitx;
    std::string tmp;
    
    setlocale(LC_ALL,"es");

    tmp = tmpPath + "/var/eustagger_lite/habil/";
    tmp += SEG_FITX;

    if ((jat_fitx = fopen(tmp.c_str(),"r")) == NULL) {
      fprintf(stderr,"Errorea %s fitxategia irekitzean\n",tmp.c_str());
      exit(EXIT_FAILURE);
    }

    string irtMorfos = morfosintaxia.getResult(); // Hemen emaitza string batean jaso

    int length = irtMorfos.length();
    testu_buffer = (char *) malloc(length+2);
    testu_buffer[0] = '\0';
    strcpy(testu_buffer,irtMorfos.c_str());
    testu_buffer[length+1] = '\0';
    buffer_size = length +2;

    string irteeraIzen = oinIzen + PHAT; 
    if ((irteera_fitx = fopen(irteeraIzen.c_str(),"w")) == NULL) {
      fprintf(stderr,"Errorea %s fitxategia irekitzean\n",irteeraIzen.c_str());
      exit(EXIT_FAILURE);
    }
    hat_kargain = jat_fitx;
    hat_kargaparse();
  }
  else {
    morfosintaxia.writeResult(); 
  }

}

