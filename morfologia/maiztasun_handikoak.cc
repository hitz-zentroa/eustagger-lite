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
#include <string>
#include <map>
using namespace std;

map<string,int> mhmap;
int INIT = 0;

int ireki_maiztasun_handikoak() {
  char* tmp = 0;
  char fitxIzena[200];
  FILE* MHINPUT;
  INIT = 0;
  int kopurua,hm=2;
  char hitza[100];
  if ( (tmp = getenv("IXA_PREFIX")) != 0 ){
    strcpy( fitxIzena , tmp);
  } 
  else return(0);
  strcat( fitxIzena, "/var/eustagger_lite/morfologia/maiztasun_handikoak.dat" );
  if((MHINPUT=fopen(fitxIzena,"r"))==NULL)
    fprintf(stderr,"ezin izan dugu %s ireki", fitxIzena);
  while(!feof(MHINPUT) && hm==2){
    hm=fscanf(MHINPUT,"%d %s",&kopurua,hitza);
    mhmap[hitza]=kopurua;
  }
  INIT = 1;
  return(1);
}

int badago_hitza_maiztasun_handikoak(char *gakoa) {
  if (INIT) {
    return(mhmap[gakoa]);
  } 
  else {
    return(0);
  }
  return(1);
}
