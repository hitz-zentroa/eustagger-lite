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


#include "prolog2raw.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "constants.h"

using namespace std;

/* ******************************************************************* */
/* *** MAKROAK ******************************************************* */
/* ******************************************************************* */

#define printDebugList(debugStr, valV)
//{ cout <<debugStr; for (int i=0; i<valV.size(); i++) cout << valV[i] << " "; cout<< endl; }

#define printDebug(debugStr)
//{ cout <<debugStr << endl; }

/* ******************************************************************* */
/* *** ESTATIKOAK **************************************************** */
/* ******************************************************************* */

map <string, vector<string> > Prolog2Raw::itzulpenT=kargatuItzulpenT();

map <string, ZerMotaType> Prolog2Raw::zerMotaT=kargatuZerMota();


/* ******************************************************************* */
map <string, ZerMotaType> Prolog2Raw::kargatuZerMota() {
  map <string, ZerMotaType> taula;
  string str;
  int zmt;

 char* cpVarOrokorra = getenv("IXA_PREFIX");
  if (cpVarOrokorra == NULL) {
    cerr << "morfosintaxia => ERRORE LARRIA: 'IXA_PREFIX' ingurune aldagaia ezin daiteke atzitu" << endl;
    exit(EXIT_FAILURE);
  } 

  string strVarOrokorra(cpVarOrokorra);
  string strVersion = ".4.4.1";

  string zerMotaFitx = strVarOrokorra + "/var/eustagger_lite/morfosintaxia/" + ZER_MOTA_FITX + strVersion;

  ifstream in(zerMotaFitx.c_str());
  if (!in) {
    cerr << "ERROREA" << endl;
    cerr << "\t prolog2raw::kargatuZerMota()" << endl;
    cerr << "\t Ezin daiteke " <<  zerMotaFitx << " fitxategia kargatu." << endl << endl;
    exit(EXIT_FAILURE);
  }

  while (!in.eof()) {
    in >> str;
    if (str.find("//")==0) in.ignore(1000,'\n');
    else {
      in >> zmt;
      taula[str]=(ZerMotaType)zmt;
    }
  }

  in.close();
  return taula;
}

/* ******************************************************************* */

map <string, vector<string> > Prolog2Raw::kargatuItzulpenT() {
  map <string, vector<string> > taula;
  string prStr;
  vector <string> xmlStrV;

 char* cpVarOrokorra = getenv("IXA_PREFIX");
  if (cpVarOrokorra == NULL) {
    cerr << "morfosintaxia => ERRORE LARRIA: 'IXA_PREFIX' ingurune aldagaia ezin daiteke atzitu" << endl;
    exit(EXIT_FAILURE);
  } 

  string strVarOrokorra(cpVarOrokorra);
  string strVersion = ".4.4.1";
  
  string itzulpenTaulaFitx = strVarOrokorra + "/var/eustagger_lite/morfosintaxia/" + ITZULPEN_TAULA_FITX + strVersion;
     

  ifstream in(itzulpenTaulaFitx.c_str());
  if (!in) {
    cerr << "ERROREA" << endl;
    cerr << "\t prolog2raw::kargatuItzulpenT()" << endl;
    cerr << "\t Ezin daiteke " << itzulpenTaulaFitx << " fitxategia kargatu." << endl << endl;
    exit(EXIT_FAILURE);
  }

  while (!in.eof()) {
    string strLine, lag;
    getline(in, strLine);
    istringstream iss(strLine);
    iss >> prStr;
    if (prStr.find("//")!=0 && prStr!="") {
      for (iss>>lag; lag!=""; lag="", iss>>lag) xmlStrV.push_back(lag);
      taula[prStr]=xmlStrV;
      xmlStrV.clear();
      prStr ="";
    }
  }

  in.close();
  return taula;
}

/* ******************************************************************* */
/* *** PRIBATUAK ***************************************************** */
/* ******************************************************************* */


#ifdef _USE_SWI_

string Prolog2Raw::sortuFS (PlTerm plstruct,string & ezaugIzen) throw (char*, int) {
  printDebug("sortuFS(terminoa)");
//   FS fs;
//   F f;
  string fs;
  string f;
  ezaugIzen = this->sortuForFS(plstruct, fs, f, FS_RETURN);
  return fs;
}

/* ******************************************************************* */

string Prolog2Raw::sortuFS (vector <string> xmlEgituraV, PlTerm plBalio) throw (char*, int) {
  printDebugList("sotuFS(lista) => ",xmlEgituraV);
  string ezaugIzen;

  if (string(plBalio.name()) == "."  && xmlEgituraV.size()==0) {

    PlTail tail(plBalio);
    PlTerm head;
    tail.next(head);
    
    if (head.type() != PL_ATOM) { cout << "AURRERA..." << endl; return sortuFS(head,ezaugIzen); }
    else throw (char*) "egitura ez onartua: ez da edukirik gabeko egiturarik onartzen";

  }
  else {
    string fs; // sortuko den emaitza
    string fsType (xmlEgituraV.front()); // egitura mota
    xmlEgituraV.erase(xmlEgituraV.begin());
      
    if (string(plBalio.name()) == "." && xmlEgituraV.size()==0) {
      
      PlTail tail(plBalio);
      PlTerm head;
      
      while (tail.next(head)) {
	
	if (head.type() != PL_ATOM) {
	  try {
	    string f = sortuF(head,ezaugIzen);
	    if (f.length() > 0)
	      if (fs.length() == 0)
		fs = f;
	      else
		fs = fs + " " + f;
	  } catch (int) {}
	  
	}
	else throw (char*)"egitura ez onartua: FS batean ez dira balio atomikoak onartzen";
      }
    }
    else {
      string f = sortuF(xmlEgituraV, plBalio);
      fs = f;
    }
    return fs;
  }
}

/* ******************************************************************* */

string Prolog2Raw::sortuF (PlTerm plstruct, string & ezaugIzen) throw (char*, int) {
  printDebug("sortuF(terminoa)");
  string fs;
  string f;
  ezaugIzen = this->sortuForFS(plstruct, fs, f, F_RETURN);
  return f;
}

/* ******************************************************************* */

string Prolog2Raw::sortuF (vector <string> xmlEgituraV, PlTerm plBalio) throw(char*){
  printDebugList("sortuF(lista) => ", xmlEgituraV);
  string f;
  string fs;
  string ezaugIzen;

  if (xmlEgituraV.size()==1) {
    
    if (string(plBalio.name()) == ".") {
      string fName(xmlEgituraV.front()); // ezaugarria: string
      
      PlTail tail(plBalio);
      PlTerm head;
      
      while (tail.next(head)) {
	  
	if (head.type() == PL_ATOM) {
	  
	  string balio = (char*)head; // balioa: string
	  string sym;
	  if (balio.length() == 1)
	    sym = fName + balio;
	  else
	    sym = balio;
	    if (f.length() > 0)
	      f = f + " " + sym;
	    else
	      f = sym;
	}
	else {
	  try {
	    string fs = sortuFS(head,ezaugIzen);
	    f = fs;
	  } catch (int) {}
	}
      }
	
      if (fName == "FSL") {
	this->fsLista = f;
	return "";
      }
      if (fName == GOIMAILAKO_EZAUG) 
	return f;
      else
	return "";
    }
    else return sortuF_BalAtom(xmlEgituraV.front(), plBalio);

  }
  else {

    string fName(xmlEgituraV.front());

    xmlEgituraV.erase(xmlEgituraV.begin());
    try {
      string fs = sortuFS(xmlEgituraV, plBalio);
      f = fs;
    } catch (int) {}
    return f;
  }
}

/* ******************************************************************* */
string sortuLema(string sarrera) {
  // Pcre tplus("\\+\\!?");
  // if (tplus.search(sarrera)) {
  //   sarrera = tplus.replace(sarrera,"");
  // }
  return sarrera;
}

string Prolog2Raw::sortuF_BalAtom (string ezaugIzen, PlTerm plBalio) throw(char*) {
  string balio;
  if (plBalio.type() == PL_ATOM) {
    balio = (char*)plBalio;
  }
  else if (plBalio.type() == PL_INTEGER) {
    long int intBalio = (long int)plBalio;
    ostringstream itoa;
    itoa << intBalio;
    balio = itoa.str();
  }
  printDebug("BalioAtomikoa => " + balio);

  switch (zerMotaT[ezaugIzen]) {
  case STR_ZM:
    if ((ezaugIzen == LEMA_OSATUA || ezaugIzen == ALDAERA_OSATUA)
	 && balio.find("+") != string::npos) {
      balio = sortuLema(balio) ;
    }
    if (ezaugIzen == LEMA_OSATUA) { 
      balio = "\"" + balio + "\""; 
      this->lemaOsatua = balio; 
      return "";
    }
    else if (ezaugIzen == ALDAERA_OSATUA) {
      if (this->cg3form) 
	balio = "\"" + balio + "\"";
      else
	balio = "/" + balio + "/"; 

      this->aldaeraOsatua = balio; 
      return "";
    }
    else if (ezaugIzen != FORMA)
      balio = "\"" + balio + "\"";
    if (ezaugIzen != SARRERA && ezaugIzen != TWOL && ezaugIzen != EDBL_SARRERA && ezaugIzen != FORMA && ezaugIzen != ADOIN)
      return balio;
    else
      if (ezaugIzen == FORMA) this->forma = balio;
      return "";
  case PLUSMINUS_ZM:
    transform(ezaugIzen.begin(), ezaugIzen.end(), ezaugIzen.begin(),  static_cast<int (*)(int)> (std::toupper));
    if (balio=="-" || balio=="minus") {
      string ezaugBal = ezaugIzen + "-";
      return ezaugBal;
    }
    else {
      string ezaugBal = ezaugIzen + "+";
      return ezaugBal;
    }
  case SYM_ZM:
    transform(balio.begin(), balio.end(), balio.begin(),  static_cast<int (*)(int)> (std::toupper));
    if (balio.length() == 1) {
      string sym;
      sym = ezaugIzen + balio;
      return sym;
    }
    else if (ezaugIzen == NOR || ezaugIzen == NORI || ezaugIzen == NORK) {
      string sym;
      char c[] = {*ezaugIzen.begin(), *(ezaugIzen.end()-1), '\0'};
      sym = c;
      sym = sym + "_" + balio;
      return sym;
    }
    else
      return balio;
  case NBR_ZM:
    return ""; // Homografoa ez da inprimatzen 
  case ID_ZM:
    this->hasierakoLerroa = balio;
    return ""; // Ikusi nola kudeatzen den...
  default:
    string msg = ezaugIzen + " ezaugarri izena ez da ezagutzen (ZerMotaT)";
    throw (char*) msg.c_str();
  }
}


/* ******************************************************************* */

string Prolog2Raw::sortuForFS(PlTerm plstruct,string & fs, string & f, ReturnType  ForFS) throw(char*, int) {
  printDebug("sortuForFS");

  string ezaugIzen;
  PlTerm plBalio;
  string strFunktore = plstruct.name();

  if (strFunktore == ":") {

    ezaugIzen = (char*)(plstruct[1]);
    plBalio = plstruct[2];

 }
  else {

    ezaugIzen = strFunktore;
    plBalio = plstruct[1];
	
  }

  if (itzulpenT.count(ezaugIzen)==1) {

    if (plBalio.type() != PL_VARIABLE) {  
      vector <string> v = itzulpenT[ezaugIzen];
      if (v.size()==0) throw (int) -1;
      if (ForFS==FS_RETURN) {
	fs = sortuFS (itzulpenT[ezaugIzen], plBalio);
      }
      else if (ForFS==F_RETURN) {
	f = sortuF( itzulpenT[ezaugIzen], plBalio);
      }
      else throw (char*) "sortuForFS->ReturnType ezezaguna FS_RETURN edo F_RETURN izan behar du\n";
    }
  }
  else {
    string msg = "itzulpen taulan ez da ezaugarri hau definitzen ->" + ezaugIzen + "\n";
    throw (char*)msg.c_str();
  }
  if (ezaugIzen == OINA) {
    f = "";
    fs = "";
  }
  return ezaugIzen;
}

#endif


/* ******************************************************************* */
/* *** PUBLIKOA ****************************************************** */
/* ******************************************************************* */

Prolog2Raw::Prolog2Raw(bool cg3form) {
  this->cg3form = cg3form;
}

/* ******************************************************************* */

#ifdef _USE_SWI_

string sortu_cg3rako_etiketak(string info);
string sortu_cg3rako_lema_info(string lema, string info, bool ezezag);
string sortu_cg3rako_lema(string lema);

#include <pcre++.h>
#include "filtro.h"
using namespace pcrepp;

void Prolog2Raw::sortuAnalisiak(PlTerm plstruct) {

  PlTail tail(plstruct);
  PlTerm e;
  string ezaugIzen;
  stringstream sni_t,sni_h;
  sni_t<< NI_T;
  Pcre ni_t(sni_t.str(),"g");
  sni_h<< NI_H;
  Pcre ni_h(sni_h.str(),"g");
  string hasierakoaCG3;

  while(tail.next(e)) {
    bool lehena = true;
    bool analisirik = false;
    PlTail tail2(e);
    PlTerm e2;
    string etiketa, formaTmp;
    char anMota = hasierakoLerroa[0];
    
    while(tail2.next(e2)) {
      
      try {
	string fs = sortuFS(e2,ezaugIzen);
	hasierakoLerroa = hasierakoLerroa.substr(hasierakoLerroa.find("/"),string::npos);
	if (ni_t.search(hasierakoLerroa)) {
	  hasierakoLerroa = ni_t.replace(hasierakoLerroa,"\303\261");
	}
	if (ni_h.search(hasierakoLerroa)) {
	  hasierakoLerroa = ni_h.replace(hasierakoLerroa,"\303\221");
	}
	if (lehena) {
	  if (cg3form) {
	    hasierakoaCG3 = hasierakoLerroa;
	    while (hasierakoaCG3.find("/<") != string::npos) {
	      hasierakoaCG3.replace(hasierakoaCG3.find("/<"),2,"\"<");
	    }
	    if (hasierakoaCG3.find(">/") != string::npos) {
	      hasierakoaCG3.replace(hasierakoaCG3.find(">/"),2,">\"");
	    }
	    
	    if (hasierakoaCG3.find(">\"") != string::npos) {
	      string tmpZ = hasierakoaCG3.substr(hasierakoaCG3.find(">\""),string::npos);
	      formaTmp = hasierakoaCG3.substr(2,hasierakoaCG3.length()-tmpZ.length()-2);
	      this->forma = formaTmp;
	      if (forma == "." || forma == ";" || forma == ":" || forma == "!" || forma == "?") {
		string formaDolar = "$" + forma;
		hasierakoaCG3.replace(hasierakoaCG3.find(forma),1,formaDolar);
	      }
	    }
	    if (hasierakoaCG3.find(">\"<") != string::npos) {	    
	      string tmpZ = hasierakoaCG3.substr(hasierakoaCG3.find(">\"<")+3,string::npos);
	      etiketa = tmpZ.substr(0,tmpZ.length()-2);
	    }
	    if (etiketa == forma) etiketa = "";
	    morfDoc << hasierakoaCG3 << endl;
	  }
	  else {
	    morfDoc << this->hasierakoLerroa << endl; 
	  }
	  hasierakoLerroa = "";
	  lehena = false;
	}
	if (this->lemaOsatua != "\"NULL\"" && this->lemaOsatua != "\"NOTNULL\"") { // ANALISIRIK GABEKO TOKENETAN, puntuazio-ikurrak, etab.
	  if (this->lemaOsatua.length() == 2) { // salbuespena, bait, ba
	    lemaOsatua = "\"" + forma + "\"";
	    if (cg3form) 
	      aldaeraOsatua = "\"" + forma + "\"";
	    else
	      aldaeraOsatua = "/" + forma + "/";
	  }
	  if (cg3form) {
	    if (anMota == 'G') {
	      this->aldaeraOsatua = this->lemaOsatua;
	      this->lemaOsatua = "";
	      morfDoc << "\t";
	    }
	    // Hemen bihurtu fs CG3ra (kalkulatu etiketak eta inprimatu)
	    string cg3formatua = sortu_cg3rako_etiketak(fs);
	    if (lemaOsatua.length() > 0) {
	      if (ni_t.search(lemaOsatua)) {
		lemaOsatua = ni_t.replace(lemaOsatua,"\303\261");
	      }
	      if (ni_h.search(lemaOsatua)) {
		lemaOsatua = ni_h.replace(lemaOsatua,"\303\221");
	      }
	      cg3formatua = sortu_cg3rako_lema_info(this->lemaOsatua,cg3formatua,anMota=='G');
	      this->lemaOsatua = sortu_cg3rako_lema(this->lemaOsatua);
	      morfDoc << "\t" << this->lemaOsatua << " ";
	    }
	    if (this->aldaeraOsatua.length()> 0) {
	      if (ni_t.search(aldaeraOsatua)) {
		aldaeraOsatua = ni_t.replace(aldaeraOsatua,"\303\261");
	      }
	      if (ni_h.search(aldaeraOsatua)) {
		aldaeraOsatua = ni_h.replace(aldaeraOsatua,"\303\221");
	      }

	      cg3formatua = sortu_cg3rako_lema_info(aldaeraOsatua,cg3formatua,anMota=='G');
	      this->aldaeraOsatua = sortu_cg3rako_lema(this->aldaeraOsatua);
	      morfDoc << this->aldaeraOsatua << " ";
	    }
	    if (anMota == 'G')
	      morfDoc << "EZEZAG ";
	    morfDoc << cg3formatua;
	    //	    morfDoc << fs ;


	    // Inprimatu aurreprozesuaren etiketa
	    if (etiketa.length() > 0) {
	      morfDoc << " " << etiketa;
	      lehena = false;
	    }
	    analisirik = true;
	    if (fsLista.length()>0) {
	      morfDoc << " " << fsLista << endl;
	    }
	    else
	      morfDoc << endl;
	  }
	  else {
	    if (anMota == 'G') {
	      this->aldaeraOsatua = this->lemaOsatua;
	      this->lemaOsatua = "";
	      morfDoc << "\t(\"\" ";
	    }
	    if (lemaOsatua.length() > 0) {

	      if (ni_t.search(lemaOsatua)) {
		lemaOsatua = ni_t.replace(lemaOsatua,"\303\261");
	      }
	      if (ni_h.search(lemaOsatua)) {
		lemaOsatua = ni_h.replace(lemaOsatua,"\303\221");
	      }

	      morfDoc << "\t(" << this->lemaOsatua << " "; 
	    }
	    if (this->aldaeraOsatua.length()> 0) {

	      if (ni_t.search(aldaeraOsatua)) {
		aldaeraOsatua = ni_t.replace(aldaeraOsatua,"\303\261");
	      }
	      if (ni_h.search(aldaeraOsatua)) {
		aldaeraOsatua = ni_h.replace(aldaeraOsatua,"\303\221");
	      }

	      if (anMota == 'G')
		morfDoc << "/" << this->aldaeraOsatua.substr(1,this->aldaeraOsatua.length()-2) << "/ " ;
	      else
	         morfDoc << this->aldaeraOsatua << " ";
	    }
	    morfDoc << " " << fs ;
	    analisirik = true;
	    if (fsLista.length()>0) {
	      morfDoc << " " << fsLista << ")" << endl; 
	    }
	    else
	      morfDoc << ")" << endl; 
	  }
	  this->fsLista = "";
	}
	else {
	  if (this->lemaOsatua == "\"NULL\"" && this->lemaOsatua != "\"NOTNULL\"") { 
	    if (cg3form)
	      morfDoc << "\t" << " " << etiketa << endl;
	    analisirik = true;
	  }
	}
      } catch (char* msg) {
	cerr << msg << endl;
      } catch (...) {}
      
    }
    if (this->lemaOsatua == "\"NOTNULL\"" && !analisirik) {
      // Hona dator morfosintaxiak analisi guztiak baztertu baditu ala ez badago hasieratik analisirik
      if (cg3form) 
	aldaeraOsatua = "\"" + forma + "\"";
      else
	aldaeraOsatua = "/" + forma + "/";
      this->lemaOsatua = "";
      if (cg3form) {
	morfDoc << "\t\"\"  " << aldaeraOsatua << " EZEZAG IZE ARR" ;
	if (etiketa.length()>0)
	  morfDoc << " " << etiketa;
	morfDoc << endl;
	morfDoc << "\t\"\"  " << aldaeraOsatua << " EZEZAG IZE ARR ABS MG" ;
	if (etiketa.length()>0)
	  morfDoc << " " << etiketa;
	morfDoc << " @OBJ @PRED @SUBJ" << endl;
      }
      else {
	morfDoc << "\t(\"\"  " << aldaeraOsatua << " IZE ARR" ;
	if (etiketa.length()>0)
	  morfDoc << " " << etiketa ;
	morfDoc << ")" << endl;
	morfDoc << "\t(\"\"  " << aldaeraOsatua << " IZE ARR ABS MG" ;
	if (etiketa.length()>0)
	  morfDoc << " " << etiketa ;
	morfDoc << " @OBJ @PRED @SUBJ)" << endl;
      }
    }
    this->lemaOsatua = "";
    this->aldaeraOsatua = "";
  }

}

#endif


/* ******************************************************************* */

void Prolog2Raw::writeMorf(string & morfFitx) {
  ofstream outFile(morfFitx.c_str());
  if (!outFile) cout << this->morfDoc.str() ;
  else outFile << this->morfDoc.str();
  outFile.close();
}
