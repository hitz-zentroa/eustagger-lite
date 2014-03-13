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


/* ***************************************************
 * **************************************************** */
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "ana2morfsar.h"
#include "morfsarFormatu.h"


Ana2Morfsar* yyparseAna2Morfsar;

using namespace std;
/* ******************************************************************* */
/* ***** METODO PRIBATUAK ******************************************** */
/* ******************************************************************* */

/* ******************************************************************* */

void Ana2Morfsar::toMorfsar(){
  extern int   ana2morfsarparse();	        // LEX-YACC modulua
  extern FILE* ana2morfsarin;       	        // LEX-YACC moduluaren sarrerako FILE*;
  if (fpFitxAna == NULL) {
    cerr << "Errorea Ana2Morfsar::toMorfsar()" << endl;
    exit( EXIT_FAILURE );
  }
  ana2morfsarin=fpFitxAna;
  yyparseAna2Morfsar = this;
  ana2morfsarparse();
  fclose( fpFitxAna );
}

void Ana2Morfsar::toMorfsar(const std::string segString){
  extern void bufferParse(char *buffer, int size);
  char *buffer;
  ofstream out ("tmp.segp");
  if (!out) {
    cerr << "Ezin daiteke tmp.segp fitxategia sortu" << endl;
  }
  out << segString << endl;
  if (fpFitxAna != NULL) {
    fpFitxAna = NULL;
  }
  buffer = (char *) malloc(segString.length()+2); /* bukeran \0\0 egotea eskatzen du */
  buffer[0] = '\0';
  strcpy(buffer,segString.c_str());
  buffer[segString.length()+1] = '\0'; // bukaeran \0\0 behar du
  yyparseAna2Morfsar = this;
  bufferParse(buffer,segString.length()+2);
 
}


void Ana2Morfsar::read_data_version() {
  this->dataversion = "4.4.9";
}

/* ******************************************************************* */
/* ***** METODO PUBLIKOAK  ******************************************* */
/* ******************************************************************* */

Ana2Morfsar::Ana2Morfsar(){
  this->tamaina=1;
  this->read_data_version();
  srand(time(0));
}
/* ******************************************************************* */

Ana2Morfsar::Ana2Morfsar(const string &segp, int tam) {
  this->tamaina=tam;
  this->read_data_version();
  srand(time(0));
  this->setAnaFitx(segp);
}

/* ******************************************************************* */

Ana2Morfsar::~Ana2Morfsar(){}

/* ******************************************************************* */

void Ana2Morfsar::setMorfsarFitx(const string & morfsar) {
  ifstream in (morfsar.c_str());
  if (!in) {
    cerr << "ERROREA" << endl;
    cerr << "\t ana2morfsar::setMorfsarFitx() => Ezin kargatu " << morfsar << " fitxategia." << endl << endl;
    exit(0);
  }
  string sar;
  while(!in.eof()) {
    string line;
    getline(in, line);
    
    sar += line + "\n";
    if (line.find("]).") != string::npos) { // lehen != -1
      morfsarForm.addMorfsarSar(sar);
      sar = "";
    }
  }
  in.close();    
}

/* ******************************************************************* */

void Ana2Morfsar::setAnaFitx(const string &segp) {
  if ( !( this->fpFitxAna = fopen(segp.c_str() , "r" )) ){
    cerr << "Errorea Ana2Morfsar::setAnaFitx --> fopen(" << segp <<")"<<endl;
    exit( EXIT_FAILURE );
  }
  this->toMorfsar();
}

void Ana2Morfsar::setAnaString(const string &segIrteera) {
  this->toMorfsar(segIrteera);
}

/* ******************************************************************* */

void Ana2Morfsar::setAnaTam(int tamaina) { this->tamaina = tamaina; }


/* ******************************************************************* */

int Ana2Morfsar::getAnaTam() {return this->tamaina; }

/* ******************************************************************* */

void Ana2Morfsar::add2Gorputza(string type, string value, bool symBal) {
  this->morfsarForm.add2Gorputza(type, value, symBal);
}

/* ******************************************************************* */

void Ana2Morfsar::setForma(string forma,const std::string bereiz) {
  this->morfsarForm.setForma(forma,bereiz);
}

/* ******************************************************************* */

void Ana2Morfsar::morfemaBerria() {
  this->morfsarForm.morfemaBerria();
}


/* ******************************************************************* */

void Ana2Morfsar::analisiaBukatu() {
  this->morfsarForm.analisiaBukatu();
}


/* ******************************************************************* */

void Ana2Morfsar::begin() {  this->morfsarForm.begin(tamaina);}

/* ******************************************************************* */

bool Ana2Morfsar::ready() { return !this->morfsarForm.end(); }

/* ******************************************************************* */

void Ana2Morfsar::next() { this->morfsarForm.next(); }

/* ******************************************************************* */

string Ana2Morfsar::current() {
  string morfsarFitx;
  bool fExist=false;
  do{
    ostringstream tmpFitx;
    tmpFitx << TMP_PATH << rand() << ".tmp.morfsar";
    morfsarFitx=tmpFitx.str();

    ifstream fIn;
    fIn.open(morfsarFitx.c_str());
    fExist=fIn.is_open();
    fIn.close();
  } while (fExist);
  return this->morfsarForm.current(morfsarFitx);
 }

/* ******************************************************************* */

string Ana2Morfsar::current(string & tmpFitx) {
  return this->morfsarForm.current(tmpFitx);
}

/* ******************************************************************* */

vector<string> Ana2Morfsar::execute(string & amaraunIzen) {
  vector<string> morfsarV;
  int kont=0;
  for (this->begin(); this->ready(); this->next()) {
    kont++;
    string morfsarFitx;
    if (tamaina>0) {
      ostringstream kontOSS;
      kontOSS.fill('0');
      kontOSS.width(6);
      kontOSS << kont;
      morfsarFitx = amaraunIzen + "." + kontOSS.str() + ".morfsar";
    }
    else morfsarFitx= amaraunIzen + ".morfsar";

    this->current(morfsarFitx);
    morfsarV.push_back(morfsarFitx);
  }
  return morfsarV;
}

/* ******************************************************************* */
