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
#include <iostream>
#include <fstream>
#include <string>
#include "freeling.h"
#include "freeling/morfo/util.h"
#include <pcre++.h>

#include "euparole.h"

using namespace std;
using namespace pcrepp;
using namespace freeling;

string getEnvVar(string const& key);

euParole::euParole() {
  euParole::level = 4;
  euParole::loaded = false;
}

euParole::euParole(int tagLevel) {
  if (tagLevel == 0) 
    euParole::level = 4;
  else
    euParole::level = tagLevel;
  try {
    euParole::loadMap();
    euParole::loaded = true;
  } catch (exception &e){
    cerr << e.what();
    exit(EXIT_FAILURE);
  }

}

void euParole::loadMap() {
  string tmpVar = getEnvVar("IXA_PREFIX");
  string tmpName;
  if (tmpVar.length()>0) {
    tmpVar += "/var/eustagger_lite/mg/";
    tmpName = tmpVar + "tagmap.dat";
  }
  else {
    cerr << "euParole => ERRORE LARRIA: 'IXA_PREFIX' ingurune aldagaia ezin daiteke atzitu" << endl;
    exit(EXIT_FAILURE);
  }

  ifstream in(tmpName.c_str());
  int lev;
  string euTag;
  char pe;
  if (!in) {
    throw (char *) "euParole => Error: cannot load tagmap.dat file\n";
  }
  in>>maxColumns[0]>>maxColumns[1]>>maxColumns[2]>>maxColumns[3];
  while (in>>lev>>euTag>>pe) {
    if (lev < maxColumns[3]) 
      euPar[lev][euTag] = pe;
    else throw (char *) "euParole => Error: malformed tagmap.dat\n";
  }
}

string euParole::toParole(const string analysis) {
  string tmp = "00000000";
  char k;
  int tmpLev = 1;
  Pcre delim("\\s+","g");
  if (!euParole::loaded) {
    try {
      euParole::loadMap();
      euParole::loaded = true;
    } catch (exception &e){
      cerr << e.what();
      exit(EXIT_FAILURE);
    }
  }

  vector<string> anSplit = delim.split(analysis);
  int prevl = 0;
  for(vector<string>::iterator t = anSplit.begin(); t != anSplit.end() && prevl < 8; ++t) {
    bool match = false;
    int i = prevl;
    while (!match && i < euParole::maxColumns[euParole::level-1]) {
      if (euPar[i][*t]) {
	if (tmp[0] == 'V' && euPar[6][*t]) tmp[6] = euPar[i][*t]; // exception: case of noun-verbs at 6th position
	else if  (tmp[0] == 'V' && euPar[7][*t]) tmp[7] = euPar[i][*t]; // exception: relation of verbs, if any, at 7th position
	else tmp[i] = euPar[i][*t];
	i++;
	match = true;
      }
      else if (i == 0) {
	Pcre izeeli("([^_]+)(_IZEELI)+");
	if (izeeli.search(*t)) {
	  string kat = izeeli.get_match(0);
	  tmp[0] = euPar[0][kat];
	  if (euParole::level > 1) {
	    if (kat == "ADL") tmp[1] = 'A';
	    if (kat == "ADT") tmp[1] = 'M';
	    tmp[2] = 'N';
	  }
	  i=3;
	  match = true;
	}
      }
      if (*t == "PUNT_PUNT") { tmp = "Fp"; return tmp; }
      else if (t->find("PUNT_") != string::npos) { tmp = "Fo"; return tmp; }
      if (*t == "BEREIZ") { tmp = "Fo"; return tmp; }
      if (euParole::level > 1) {
	if (*t == "ADL") tmp[1] = 'A';
	if (*t == "ADT") tmp[1] = 'M';
      }
      if (!match) i++; 
      else prevl = i;
    }
  }
  if (tmp[1] == 'Q' && tmp[0] == 'N') tmp[1] = 'C';
  return tmp;
}

void euParole::setLevel(int tagLevel) {
  euParole::level = tagLevel;
}

void euParole::getLemmaTag(const string analysis,wstring &lemma,wstring &tag) {
  Pcre anTmp("\\s+\\\"(.[^\\\"]+)\\\"\\s+(.+)\\s*$");
  Pcre anTmp2("\\s+(.+)\\s*$");
  if (anTmp.search(analysis)) {
    string lemmaT = anTmp.get_match(0);
    string anT = anTmp.get_match(1);
    string tagT = toParole(anT);
    lemma = util::string2wstring(lemmaT);
    tag = util::string2wstring(tagT);
  }
  else if (anTmp2.search(analysis)) {
    string anT = anTmp2.get_match(0);
    string tagT = toParole(anT);
    lemma = L"";
    tag = util::string2wstring(tagT);
  }
}
