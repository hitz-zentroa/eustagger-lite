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

  string zerMotaFitx = strVarOrokorra + "/var/morfosintaxia/" + ZER_MOTA_FITX + strVersion;

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
  
  string itzulpenTaulaFitx = strVarOrokorra + "/var/morfosintaxia/" + ITZULPEN_TAULA_FITX + strVersion;
     

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
string sortuLema(string sarrera) {return sarrera;}

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
    else balio = "\"" + balio + "\"";
    if (ezaugIzen != SARRERA && ezaugIzen != EDBL_SARRERA && ezaugIzen != FORMA && ezaugIzen != ADOIN)
      return balio;
    else
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

void Prolog2Raw::sortuAnalisiak(PlTerm plstruct) {

  PlTail tail(plstruct);
  PlTerm e;
  string ezaugIzen;

  while(tail.next(e)) {
    bool lehena = true;
    PlTail tail2(e);
    PlTerm e2;
    string etiketa, forma;
    char anMota = hasierakoLerroa[0];
    
    while(tail2.next(e2)) {
      
      try {
	string fs = sortuFS(e2,ezaugIzen);
	hasierakoLerroa = hasierakoLerroa.substr(hasierakoLerroa.find("/"),string::npos);
	if (lehena) {
	  if (cg3form) {
	    string hasierakoaCG3 = hasierakoLerroa;
	    while (hasierakoaCG3.find("/") != string::npos) {
	      hasierakoaCG3.replace(hasierakoaCG3.find("/"),1,"\"");
	    }
	    
	    if (hasierakoaCG3.find(">\"")) {
	      string tmpZ = hasierakoaCG3.substr(hasierakoaCG3.find(">\""),string::npos);
	      forma = hasierakoaCG3.substr(2,hasierakoaCG3.length()-tmpZ.length()-2);
	      if (forma == "." || forma == ";" || forma == ":" || forma == "!" || forma == "?") {
		string formaDolar = "$" + forma;
		hasierakoaCG3.replace(hasierakoaCG3.find(forma),1,formaDolar);
	      }
	    }
	    if (hasierakoaCG3.find(">\"<")) {	    
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
	if (this->lemaOsatua != "\"NULL\"") { // ANALISIRIK GABEKO TOKENETAN, puntuazio-ikurrak, etab.
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
	      cg3formatua = sortu_cg3rako_lema_info(this->lemaOsatua,cg3formatua,anMota=='G');
	      this->lemaOsatua = sortu_cg3rako_lema(this->lemaOsatua);
	      morfDoc << "\t" << this->lemaOsatua << " ";
	    }
	    if (this->aldaeraOsatua.length()> 0) {
	      cg3formatua = sortu_cg3rako_lema_info(aldaeraOsatua,cg3formatua,anMota=='G');
	      this->aldaeraOsatua = sortu_cg3rako_lema(this->aldaeraOsatua);
	      morfDoc << this->aldaeraOsatua << " ";
	    }
	    if (anMota == 'G')
	      morfDoc << "EZEZAG ";
	    morfDoc << cg3formatua;
	    //	    morfDoc << fs ;


	    // Inprimatu aurreprozesuaren etiketa
	    if (etiketa.length() > 0)
	      morfDoc << " " << etiketa;
	    if (fsLista.length()>0)
	      morfDoc << " " << fsLista << endl;
	    else
	      morfDoc << endl;
	  }
	  else {
	    if (anMota == 'G') {
	      this->aldaeraOsatua = this->lemaOsatua;
	      this->lemaOsatua = "";
	      morfDoc << "\t(\"\" ";
	    }
	    if (lemaOsatua.length() > 0)
	      morfDoc << "\t(" << this->lemaOsatua << " "; 
	    if (this->aldaeraOsatua.length()> 0)
	      if (anMota == 'G')
		morfDoc << "/" << this->aldaeraOsatua.substr(1,this->aldaeraOsatua.length()-2) << "/ " ;
	      else
	         morfDoc << this->aldaeraOsatua << " ";
	    morfDoc << " " << fs ;
	    if (fsLista.length()>0)
	      morfDoc << " " << fsLista << ")" << endl; 
	    else
	      morfDoc << ")" << endl; 
	  }
	  this->fsLista = "";
	}
	else if (cg3form) { 
	  morfDoc << "\t" << " " << etiketa << endl;
	}
      } catch (char* msg) {
	cerr << msg << endl;
      } catch (...) {}
      
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
