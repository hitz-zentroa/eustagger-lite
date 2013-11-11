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
 * File name     : morfsarFormatu.h
 * Version       : 2006-02-22
 * Last Revision : 
 * Author        : Aitor Sologaistoa (jibsofra@si.ehu.es) 
 * Purpose       : prologen sarrera sortzeko klase lagungarria
 * Use           : 
 *               : 
 * **************************************************** */

#ifndef _MORFSAR_FORMATU_H
#define _MORFSAR_FORMATU_H
#include <string>
#include <vector>

struct Indizeak {
  int anaInd;
  int interInd;
  int morfInd;

  Indizeak();
  Indizeak(int ana, int inter, int morf);
};


struct MorfsarSar {
  Indizeak hasInd;
  Indizeak bukInd;
  std::vector<std::string> gorputzaV;

  int bodyKont;

  MorfsarSar();
  MorfsarSar(Indizeak hasInd, Indizeak bukInd, std::vector<std::string> gorputzV);
  MorfsarSar(Indizeak buruInd, bool idDauka);
  std::string toStr();
  std::string toStr(int hasAnaInd);
};

class MorfsarFormatu {
 std::vector <std::vector <MorfsarSar> > emaitzaV;

  int multzoTam;            //emaitza jasotzerakoan itzuli beharreko analisi kopurua
  int anaPos;               //emaitza jasotzeko analisi listaren posizioa

  int analisiKont;          //mementuan tratatzen den analisiaren hasiera
  int interprKont;          //mementuan tratatzen den analisiaren interprstazio hasiera
  int morfKont;             //mementuan tratatzen den analisiaren morfema hasiera
  std::string aurrekoForma;

  MorfsarSar mSar;            //mementuan tratatzen den analisiaren informazioa

 public:
  MorfsarFormatu();

  void addMorfsarSar(std::string & mSarStr);  //osatuta dagoen  prolog sarrera txertatzen du

  void add2Gorputza(std::string type, std::string value, bool symBal=false);
  void setForma(std::string forma,const std::string bereiz);
  void morfemaBerria();
  void analisiaBukatu();

  void begin(int tam);
  bool end();
  void next();
  std::string current(std::string & fitx);
};
#endif // _MORFSAR_FORMATU_H
