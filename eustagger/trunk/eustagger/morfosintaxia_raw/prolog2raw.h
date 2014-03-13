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

#ifndef _PROLOG2RAW_H
#define _PROLOG2RAW_H

#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#ifdef _USE_SICSTUS_
#include <sicstus/sicstus.h>
#endif
#ifdef _USE_SWI_
#include "SWI-cpp.h"
#endif
#define ITZULPEN_TAULA_FITX "itzulpenTpro2xml"
#define ZER_MOTA_FITX "zerMotaTaula"
#define ORG_TAULA_FITX "orgTaula"

#define DEBUG_MODE

/* typedef */ enum ZerMotaType {
  ERRORE_ZM = 0,
  STR_ZM = 1,
  PLUSMINUS_ZM = 2,
  SYM_ZM = 3,
  NBR_ZM = 4,
  ID_ZM = 5
};

/* typedef */ enum ReturnType {
  FS_RETURN = 0,
  F_RETURN  = 1
};

class Prolog2Raw {
  static std::map<std::string, std::vector <std::string> > itzulpenT;
  static std::map<std::string, ZerMotaType> zerMotaT;

  static std::map<std::string, std::vector <std::string> > kargatuItzulpenT();
  static std::map<std::string, ZerMotaType> kargatuZerMota();

  std::stringstream morfDoc;
  std::string hasierakoLerroa;
  std::string lemaOsatua;
  std::string aldaeraOsatua;
  std::string fsLista;
  std::string forma;
  bool cg3form;

#ifdef _USE_SWI_
  std::string sortuFS        (PlTerm plstruct, std::string & ezaugIzen) throw (char*, int);
  std::string sortuFS        (std::vector <std::string> xmlEgituraV, PlTerm plBalio) throw(char*, int);
  std::string sortuF         (PlTerm plstruct, std::string & ezaugIzen) throw (char*, int);
  std::string sortuF         (std::vector <std::string> xmlEgituraV, PlTerm plBalio) throw(char*);
  std::string sortuF_BalAtom (std::string ezaugIzen, PlTerm plBalio) throw(char*);
  std::string sortuForFS(PlTerm plterm, std::string & fs, std::string & f, ReturnType ForFS) throw(char*, int);
#endif


 public:
  Prolog2Raw (bool cg3form=false);
#ifdef _USE_SICSTUS_
  void sortuAnalisiak(SP_term_ref anaRefList);
#endif
#ifdef _USE_SWI_
  void sortuAnalisiak(PlTerm plstruct);
#endif
  void writeMorf(std::string & morfFitx);
 };

#endif // _PROLOG2RAW_H
