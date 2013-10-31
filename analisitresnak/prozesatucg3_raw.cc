#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "formatua.h"
#include "ald_orok.h"
#include "freeling.h"
#include "freeling/morfo/util.h"
#include <pcre++.h>

#include "cgmanager.h"
#include "euparole.h"

using namespace std;
using namespace pcrepp;
//using namespace freeling;


string getEnvVar(string const& key);
string kendu_cg3rako_etiketak(string info);
void PrintResults (list < sentence > &ls, int level, string &oinIzen);
void desHMM(int maila, string &desIrteera, string &oinIzen);


int prozesatuCG3Raw(int maila, string &oinIzen) {
  string tmpVar = getEnvVar("IXA_PREFIX");
  string tmpName;
  string gramatika;
  string desSarrera = oinIzen + PHAT;
  string desIrteera = oinIzen ;

  if (maila != 0) {

    if (tmpVar.length()>0) {
      tmpVar += "/var/mg/";
      gramatika = tmpVar + "gramatika4.4.1.cg3.dat";
    }
    else {
      cerr << "prozesatuCG3Raw => ERRORE LARRIA: 'IXA_PREFIX' ingurune aldagaia ezin daiteke atzitu" << endl;
      exit(EXIT_FAILURE);
    }
    
    
    desIrteera += ".irteera";
    // LEM formatua bada, .irteera ipini hemen eta bukaeran bihurketa egin
    
    
    cgManager cgApp;
    int sekzioak = 11;
    if (maila == 1) sekzioak = 3;
    else if (maila == 2) sekzioak = 4;
    else if (maila == 3) sekzioak = 5;
    
    
    if (cgApp.initGrammar(gramatika,sekzioak,'@',0) == 0) {// gramatika, zenbat sekzio, @ aurrizkia eta trace=0
      cerr << "Error in initGrammar: "<<gramatika << endl;
      return EXIT_FAILURE;
    }
    
    if (cgApp.initIO(desSarrera,desIrteera) == 0) {
      cerr << "Error in initIO " << desSarrera << " or " << desIrteera<< endl;
      return EXIT_FAILURE;
    }
    
    cgApp.applyGrammar();// aplikatu sekzio eta mapaketa guztiak
    
    
    cgApp.clean();
    
    unlink(desSarrera.c_str());
    desHMM(maila,desIrteera,oinIzen);
    unlink(desIrteera.c_str());
  }
  else {
    desHMM(maila,desSarrera,oinIzen);
    unlink(desSarrera.c_str());
  }

  return EXIT_SUCCESS;
}

void desHMM(int maila, string &desIrteera,string &oinIzen) {
  euParole parolera(maila);
    list<sentence> ls;
    sentence lws;
    ifstream in(desIrteera.c_str());
    string sars;
    string tmpVar = getEnvVar("IXA_PREFIX");
    string tmpName;

    if (tmpVar.length()>0) {
      tmpVar += "/var/mg/";
      tmpName = tmpVar + "eustaggerhmmf.dat";
    }
    else {
      cerr << "prozesatuCG3Raw => ERRORE LARRIA: 'IXA_PREFIX' ingurune aldagaia ezin daiteke atzitu" << endl;
      exit(EXIT_FAILURE);
    }
    wstring tagDat = util::string2wstring(tmpName);
    hmm_tagger taggerEu(L"eu",tagDat, false, FORCE_TAGGER,1);

    if (!in) {
      exit(EXIT_FAILURE);
    }
    getline(in,sars);
    while (sars.length()>0) {
      string formL;
      wstring form,lemma,tag;
      Pcre firstL("\\\"<\\$?(.[^>]*)>\\\"");
      if (firstL.search(sars)) {
	string formTmp = firstL.get_match(0);
	form = util::string2wstring(formTmp);
      }
      word w(form);
      // wstring wForm = util::string2wstring(form);
      // w.set_form(wForm);
      sars.clear();
      getline(in,sars);
      while (sars.length()>0 && sars[0] != '"') {
	//	sars = kendu_cg3rako_etiketak(sars);
	parolera.getLemmaTag(sars,lemma,tag);
	// analysis an(util::string2wstring(lemma),util::string2wstring(tag));
	if (lemma.length()>0) {
	  analysis an(lemma,tag);
	  w.add_analysis(an);
	}
	else if (tag.length()>0) {
	  lemma = form;
	  analysis an(lemma,tag);
	  w.add_analysis(an);
	}
	sars.clear();
	getline(in,sars);
      }
      //set prob
      int anNum = w.get_n_analysis();
      for (word::iterator an = w.analysis_begin();an != w.analysis_end();an++) {
	an->set_prob(1/anNum);
      }
      
      lws.push_back(w);
      if (form == L"." || form == L"!" || form == L"?") {
	ls.push_back(lws);
	lws.clear();
      }
      if (sars[0] != '"') {
	sars.clear();
	getline(in,sars);
      }
    }
    
    if (lws.size() > 0) {
      ls.push_back(lws);
      lws.clear();
    }
    if (ls.size() > 0) {
      taggerEu.analyze(ls);
      PrintResults(ls,maila,oinIzen);
      ls.clear();
    }  
}
void PrintResults (list < sentence > &ls, int level, string &oinIzen) {
  sentence::const_iterator w;
  list < sentence >::iterator si;
  stringstream irt;
 
  if (level != 0) 
    irt << oinIzen << ".etiketatua" << level;
  else
    irt << oinIzen << ".morfeus";
  string irtIzen = irt.str();
  wofstream taggedOut(irtIzen.c_str());

  for (si = ls.begin (); si != ls.end (); si++) {

      for (w = si->begin (); w != si->end (); w++) {
	taggedOut << w->get_form ();
	if (level > 0) {
	  for (word::const_iterator an = w->selected_begin (); an != w->selected_end (); an++) {
	    taggedOut << L" " << an->get_lemma () << L" " << an->get_tag () ;
	  }
	  taggedOut << endl;
	}
	else {
	  for (word::const_iterator an = w->analysis_begin();an != w->analysis_end();an++) {
	    taggedOut << L" " << an->get_lemma () << L" " << an->get_tag () ;
	  }
	  taggedOut << endl;
	}
      }
    // sentence separator: blank line.
    taggedOut << endl;
  }
}
