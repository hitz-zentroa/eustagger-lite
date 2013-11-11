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
 * File name     : morfsarFormatu.cc
 * Version       : 2006-02-22
 * Last Revision : 
 * Author        : Aitor Sologaistoa (jibsofra@si.ehu.es) 
 * Purpose       : prologen sarrera sortzeko klase lagungarria
 * Use           : 
 *               : 
 * **************************************************** */

#include "morfsarFormatu.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

/* **************************************************** */
/* **** Indizeak egitura ****************************** */
/* **************************************************** */

Indizeak::Indizeak() {
  anaInd   = 0;
  interInd = 0;
  morfInd  = 0;
}

Indizeak::Indizeak(int ana, int inter, int morf) {
  anaInd = ana;
  interInd = inter;
  morfInd = morf;
}

/* **************************************************** */
/* **** MorfsarSar Egitura ***************************** */
/* **************************************************** */

MorfsarSar::MorfsarSar() {
  hasInd = Indizeak(0,0,0);
  bukInd = Indizeak(0,0,0);

  bodyKont = 0;
}

MorfsarSar::MorfsarSar(Indizeak hasInd, Indizeak bukInd, vector<string> gorputzV) {
  this->hasInd = hasInd;
  this->bukInd = bukInd;
  this->gorputzaV = gorputzV;
}

MorfsarSar::MorfsarSar(Indizeak buruInd, bool idDauka){
  hasInd = buruInd;
  bukInd = Indizeak(0,0,0);
  
  bodyKont = (idDauka)?0:1;
}

string MorfsarSar::toStr() { return this->toStr(this->hasInd.anaInd); }

string MorfsarSar::toStr(int hasAnaInd) {
  if (hasAnaInd == 0 && this->hasInd.anaInd != 0) return this->toStr(this->hasInd.anaInd);

  int bukAnaInd = hasAnaInd + (bukInd.anaInd - hasInd.anaInd);

  ostringstream hasOss;
  hasOss << setw(3) << setfill('0') << hasAnaInd << setw(3) << hasInd.interInd << setw(3) << hasInd.morfInd;

  ostringstream bukOss;
  bukOss << setw(3) << setfill('0') << bukAnaInd << setw(3) << bukInd.interInd << setw(3) << bukInd.morfInd;

  string emaitza = "dict(" + hasOss.str() + ", " + bukOss.str() + ", X@[" + "\n";
  for (vector<string>::iterator it = gorputzaV.begin(); it != gorputzaV.end(); it++) {
    emaitza +=  (*it);
    if ((it+1) != gorputzaV.end()) emaitza += ",\n";
  }
  emaitza += "]).";
  return emaitza;
}


/* **************************************************** */
/* **** MorfsarFormatu Klasea ************************** */
/* **************************************************** */

MorfsarFormatu::MorfsarFormatu() {
  this->multzoTam=0;
  this->anaPos=0;

  this->analisiKont=0;
  this->interprKont=1;
  this->morfKont=-1;

  this->aurrekoForma="-";

  Indizeak hasInd(1,0,0);
  mSar = MorfsarSar(hasInd, true);
}

/* **************************************************** */

void MorfsarFormatu::addMorfsarSar(string & mSarStr) {
  vector <string> gorputzV;
  string indLerro;
  string lag = mSarStr;
  while (lag != "") {
    int ind = lag.find("\n");
    if (ind != -1) {
      string lerro = lag.substr(0, ind);
      lag = lag.substr(ind+1);
      if (lerro != "") {
	if (lerro.find("dict(") != string::npos) indLerro = lerro; // lehen != -1
	else gorputzV.push_back(lerro);
      }
    } else {
      cout << "ERROREA: morfsar fitxategia formatu desekogia dauka" << endl;
      exit(0);
    }
  }

  int ind1Has = indLerro.find_first_of("(")+1;
  int ind1Buk = indLerro.find_first_of(",");
  int ind2Has = ind1Buk+1;
  int ind2Buk = indLerro.find_last_of(",");
  string his = indLerro.substr(ind1Has, ind1Buk-ind1Has);
  string bis = indLerro.substr(ind2Has, ind2Buk-ind2Has);
  remove(his.begin(),his.end(),' ');
  remove(bis.begin(),bis.end(),' ');
  Indizeak hasInd(atoi(his.substr(0,3).c_str()),atoi(his.substr(3,3).c_str()),atoi(his.substr(6,3).c_str()));
  Indizeak bukInd(atoi(bis.substr(0,3).c_str()),atoi(bis.substr(3,3).c_str()),atoi(bis.substr(6,3).c_str()));

  for (int i=0;(unsigned) i<gorputzV.size(); i++) {
    string line = gorputzV[i];
    int ebakInd = line.find("]).");
    if (ebakInd == -1) ebakInd = line.rfind(",");
    if (ebakInd!=-1) line = line.substr(0,ebakInd);
    gorputzV[i]=line;
  }

  MorfsarSar morfsarSar(hasInd,bukInd,gorputzV);
  vector<MorfsarSar> v;
  if  (!emaitzaV.empty()) v = emaitzaV.back();
  if (!v.empty() && v.back().hasInd.anaInd == morfsarSar.hasInd.anaInd) {
    v.push_back(morfsarSar);
    emaitzaV[emaitzaV.size()-1]= v;
  }
  else {
    v.clear();
    v.push_back(morfsarSar);
    emaitzaV.push_back(v);
  }
   
}

/* **************************************************** */

void MorfsarFormatu::add2Gorputza(string type, string value, bool symBal) {
  string valueLag = value;
  string typeLag;

  char* str=strdup(type.c_str());
  char* zati=strtok(str,"/");
  while(zati!=NULL) {
    string s(zati);
    if (typeLag.length()!=0)typeLag+="/";
    if (s.find('-')<s.length()) typeLag+="'" + s +"'";    
    else typeLag+=s;
    zati=strtok(NULL,"/");
  }
  transform(typeLag.begin(), typeLag.end(), typeLag.begin(), static_cast<int (*)(int)> (std::tolower));
  

  ostringstream gorputza;
  if (symBal) {
    transform(valueLag.begin(), valueLag.end(), valueLag.begin(),  static_cast<int (*)(int)> (std::tolower));
    if (valueLag.find('/')<valueLag.length() || valueLag.find('-')<valueLag.length()) valueLag ="'" + valueLag + "'";
  } else {
    int strBanatuInd=valueLag.find('"');
    if ((unsigned)strBanatuInd<valueLag.length()) {
      valueLag = valueLag.substr(0,strBanatuInd) + "\"\"" + valueLag.substr(strBanatuInd+1);
    }
    if ( valueLag[valueLag.size()-1] == '\\') valueLag[valueLag.size()-1]='#';
    valueLag = "\"" + valueLag + "\"";
  }
  gorputza << "  m("<< mSar.bodyKont << ", X/" << typeLag << " <=> " << valueLag << " )";      

  mSar.gorputzaV.push_back(gorputza.str());
  mSar.bodyKont++;
}

/* **************************************************** */

void MorfsarFormatu::setForma(string forma,const std::string bereiz) {
  // forma mantentzen bada analisi beraren intertretazio berria bestela Analisi guztiz berri bat.
  this->morfKont=0;
  if (aurrekoForma == forma && bereiz != "NULL") {
     interprKont++;
  }
  else {
    analisiKont++;
    interprKont = 1;
    aurrekoForma = forma;
    vector<MorfsarSar> anaBerri;
    emaitzaV.push_back(anaBerri);
  }
  
  Indizeak hasInd(analisiKont,0,0);
  mSar.hasInd = hasInd;
  
    
}

/* **************************************************** */

void MorfsarFormatu::morfemaBerria() {
  this->morfKont++;

  Indizeak  bukInd(analisiKont, interprKont, morfKont);
  mSar.bukInd = bukInd;
  vector <MorfsarSar> lag = this->emaitzaV[analisiKont-1];
  lag.push_back(mSar);
  this->emaitzaV[analisiKont-1] = lag;

  // morfema berriarentzako sarrera
  this->mSar = MorfsarSar(bukInd, false); ////Analisi ID-a azaldu behar badu, true
}

/* **************************************************** */

void MorfsarFormatu::analisiaBukatu() {
  Indizeak bukInd(analisiKont+1,0,0);
  mSar.bukInd = bukInd;
  vector <MorfsarSar> lag = this->emaitzaV[analisiKont-1];
  lag.push_back(mSar);
  this->emaitzaV[analisiKont-1] = lag;

  Indizeak hasInd(0,0,0);
  this->mSar = MorfsarSar(hasInd,true);
}

/* **************************************************** */

void MorfsarFormatu::begin(int tam) {
  this->multzoTam = tam;
  this->anaPos = 0;
}

/* **************************************************** */

bool MorfsarFormatu::end() {return (unsigned)anaPos >= emaitzaV.size();}

/* **************************************************** */

void MorfsarFormatu::next() { this->anaPos += (multzoTam)?this->multzoTam:emaitzaV.size(); }

/* **************************************************** */

string MorfsarFormatu::current(string & fitx) {
  ofstream out (fitx.c_str());
  if (!out) {
    cerr << "Ezin daiteke " << fitx << " fitxategia sortu" << endl;
    return "";
  }
  for (int i = 0; (i<multzoTam || !multzoTam) && (unsigned)(anaPos+i) < emaitzaV.size(); i++) {
    vector<MorfsarSar> emaPart = emaitzaV[anaPos+i];
    for (int j=0; (unsigned)j<emaPart.size(); j++) 
	out <<  emaPart[j].toStr(i+1) << endl << endl;
  } 
  
  out.close();

  return fitx; 
}
/* **************************************************** */
