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
#include "formatua.h"
#include "ald_orok.h"
#include "freeling.h"
#include "freeling/morfo/util.h"
#include <pcre++.h>

#include "cgmanager.h"
#include "euparole.h"

using namespace std;
using namespace pcrepp;
using namespace freeling;

const int PAROLE_OUTPUT = 1;
const int MG_OUTPUT     = 2;
const int NAF_OUTPUT    = 3;

string getEnvVar(string const& key);
string kendu_cg3rako_etiketak(string info);
string getPoS(string tag);
void PrintParole (list < sentence > &ls, int level);
void PrintMG (list < sentence > &ls, int level);
void PrintNAF (list < sentence > &ls, int level);
void desHMM(int maila, string &desIrteera, string &oinIzen, int zuriuneetan, int format);

// trim from start
static inline string &ltrim(string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline string &rtrim(string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline string &trim(string &s) {
        return ltrim(rtrim(s));
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, sizeof(buf), "%Y-%m-%dT%T%z", &tstruct);

  return buf;
}

// XML entities
string XML_entities(string s) {
  Pcre amp("&", "g");
  Pcre gt(">", "g");
  Pcre lt("<", "g");
  //Pcre quot("\\\"|“|”", "g");
  Pcre quot("\\\"", "g");
  
  s= trim(s);

  //cerr << s;
  s=amp.replace(s, "&amp;");
  s=lt.replace(s, "&lt;");
  s=gt.replace(s, "&gt;");
  s=quot.replace(s, "&quot;");
  //cerr << "\t" << s << endl;
  
  return s;
}

int prozesatuCG3Raw(int maila, string &oinIzen, int zuriuneetan, int format) {
  string tmpVar = getEnvVar("IXA_PREFIX");
  string tmpName;
  string gramatika;
  string desSarrera = oinIzen + PHAT;
  string desIrteera = oinIzen ;

  if (maila != 0) {

    if (tmpVar.length()>0) {
      tmpVar += "/var/eustagger_lite/mg/";
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
    desHMM(maila,desIrteera,oinIzen, zuriuneetan, format);
    unlink(desIrteera.c_str());
  }
  else {
    desHMM(maila,desSarrera,oinIzen, zuriuneetan, format);
    unlink(desSarrera.c_str());
  }

  return EXIT_SUCCESS;
}

void desHMM(int maila, string &desIrteera,string &oinIzen, int zuriuneetan, int format) {
  euParole parolera(maila);
  list<sentence> ls;
  sentence lws;
  ifstream in(desIrteera.c_str());
  string sars;
  string tmpVar = getEnvVar("IXA_PREFIX");
  string tmpName;
  
  if (tmpVar.length()>0) {
    tmpVar += "/var/eustagger_lite/mg/";
    tmpName = tmpVar + "eustaggerhmmf.dat";
  }
  else {
    cerr << "prozesatuCG3Raw => ERRORE LARRIA: 'IXA_PREFIX' ingurune aldagaia ezin daiteke atzitu" << endl;
    exit(EXIT_FAILURE);
  }

  wstring tagDat = util::string2wstring(tmpName);
  hmm_tagger taggerEu(tagDat, false, FORCE_TAGGER,1);
  tmpName = tmpVar + "probabilitateak.dat";
  wstring probDat = util::string2wstring(tmpName);
  probabilities probs(probDat,0.001);
  stringstream irt;
  
  if (!in) {
    exit(EXIT_FAILURE);
  }

  getline(in,sars);
  while (sars.length()>0) {
    string formL;
    wstring form,lemma,tag,ambclass;
    Pcre firstL("\\\"<\\$?(.[^>]*)>\\\"");

    if (firstL.search(sars)) {
      string formTmp = firstL.get_match(0);
      form = util::string2wstring(formTmp);
    }
    word w(form);

    formL = sars;
    sars.clear();
    getline(in,sars);
    while (sars.length()>0 && sars[0] != '"') {
      parolera.getLemmaTag(sars,lemma,tag);

      string user = formL + "\n" + sars;
      if (lemma.length()>0) {
	analysis an(lemma,tag);
	an.user.push_back(util::string2wstring(user));
	w.add_analysis(an);
	if (ambclass.length()) ambclass += L"-";
	ambclass += tag;
      }
      else if (tag.length()>0) {
	lemma = form;
	analysis an(lemma,tag);
	an.user.push_back(util::string2wstring(user));
	w.add_analysis(an);
	if (ambclass.length()) ambclass += L"-";
	ambclass += tag;
      }
      sars.clear();
      getline(in,sars);
    }
    //set prob
    wstring fakeform = ambclass + L"&-&";
    fakeform = fakeform + form;
    w.set_form(fakeform);
    probs.annotate_word(w);
    w.set_form(form);

    if (zuriuneetan && form == L"@@SENT_END") {
      ls.push_back(lws);
      lws.clear();
    }
    else {
      lws.push_back(w);
    }

    if (!zuriuneetan && (form == L"." || form == L"!" || form == L"?")) {
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
    if (format == NAF_OUTPUT) {
      PrintNAF(ls,maila);
    }
    else if (format == MG_OUTPUT) {
      PrintMG(ls,maila);
    }
    else {
      PrintParole(ls,maila);
    }
    ls.clear();
  }  
}

string getPoS(string tag) {
  string PoS = "O";
  string tmp = tag.substr(0,1);
  if (tmp == "V" || tmp == "C" || tmp == "D") {
    PoS = tmp;
  }
  else if (tmp == "R") {
    PoS = "A";
  }
  else if (tmp == "A") {
    PoS = "G";
  }
  else if (tmp == "N") {
    if (tag.substr(1,1) == "P" || tag.substr(1,1) == "L") {
      PoS = "R";
    }
    else {
      PoS = tmp;
    }
  }
  return PoS;
}

void PrintParole (list < sentence > &ls, int level) {
  sentence::const_iterator w;
  list < sentence >::iterator si;
 
  for (si = ls.begin (); si != ls.end (); si++) {
    for (w = si->begin (); w != si->end (); w++) {
      wcout << w->get_form ();
      if (level > 0) {
	for (word::const_iterator an = w->selected_begin (); an != w->selected_end (); an++) {
	  wcout << L" " << an->get_lemma () << L" " << an->get_tag () ;
	}
	wcout << endl;
      }
      else {
	for (word::const_iterator an = w->analysis_begin();an != w->analysis_end();an++) {
	  wcout << L" " << an->get_lemma () << L" " << an->get_tag () ;
	}
	wcout << endl;
      }
    }
    // sentence separator: blank line.
    wcout << endl;
  }
  wcout.flush();
}

void PrintMG (list < sentence > &ls, int level) {
  sentence::const_iterator w;
  list < sentence >::iterator si;
 
  for (si = ls.begin (); si != ls.end (); si++) {
    for (w = si->begin (); w != si->end (); w++) {

      word::const_iterator an;
      word::const_iterator last;
      if (level > 0) {
	an = w->selected_begin();
	last = w->selected_end();
      }
      else {
	an = w->analysis_begin();
	last = w->analysis_end();
      }

      for (word::const_iterator an = w->selected_begin (); an != w->selected_end (); an++) {
	  if (an->user.begin() != an->user.end())
	    wcout << *(an->user.begin());
	  else 
	    wcout << w->get_form() << endl;
      }
      wcout << endl;
    }
    // sentence separator: blank line.
    wcout << endl;
  }
  wcout.flush();
}

string MG2XML(string input) {
  string output;
  string tmp = input;
  
  Pcre anTmp("\\s+\\\"(.[^\\\"]+)\\\"\\s+(.+)\\s*$");
  Pcre anTmp2("\\s+(.+)\\s*$");

  if (anTmp.search(tmp)) {
    output = XML_entities(anTmp.get_match(1));
  }
  else if (anTmp2.search(tmp)) {
    output = XML_entities(anTmp2.get_match(0));	
  }

  return output;
}

void PrintNAF (list < sentence > &ls, int level) {
  sentence::const_iterator w;
  list < sentence >::iterator si;
 
  std::locale::global(std::locale(""));
  ostringstream text;
  ostringstream terms;

  int sent = 1;
  int word = 1;
  int term = 1;
  for (si = ls.begin (); si != ls.end (); si++) {
    for (w = si->begin (); w != si->end (); w++) {
      string form = util::wstring2string(w->get_form());
      form = XML_entities(form);
	  //      text << "  <wf id=\"w" << word << "\" sent=\"" << sent << "\"";
      //text << " offset=\"" << w->get_span_start() << "\"";
	  //      text << ">" << form << "</wf>" << endl;

      word::const_iterator an;
      word::const_iterator last;
      
      if (level > 0) {
	an = w->selected_begin();
	last = w->selected_end();
      }
      else {
	an = w->analysis_begin();
	last = w->analysis_end();
      }

      if (an != last) { 

		string ana = util::wstring2string(*(an->user.begin()));
		string xoffset = "";
		string xoffset2 = "";
		int xlength = 0;
		string xpara = "";
		Pcre reg("#([0-9]+)\\-([0-9]+)#p([0-9]+)#");
		if(reg.search(ana) == true) {
		  if(reg.matches() >= 2) {
			xoffset = reg.get_match(0);
			xoffset2 = reg.get_match(1);
			xlength = (atoi(xoffset2.c_str()) - atoi(xoffset.c_str()))+1;
			xpara = reg.get_match(2);
		  }
		}

		
		text << "  <wf id=\"w" << word << "\" offset=\""<< xoffset << "\" lenght=\""<< xlength <<"\" sent=\"" << sent << "\" para=\""<< xpara <<"\"";
		text << ">" << form << "</wf>" << endl;



	string lemma = util::wstring2string(w->get_lemma());
	string form = util::wstring2string(w->get_form());
	string tag = util::wstring2string(an->get_tag());
	lemma = XML_entities(lemma);

	Pcre kendu("--", "g");
	form = kendu.replace(form, " - -");

	terms << "  <!-- " << form << " -->" << endl;
	terms << "  <term id=\"t" << term << "\" lemma=\"" << lemma << "\" morphofeat=\"" << tag;
	terms << "\" pos=\"" << getPoS(tag);
	if (an->user.begin() != an->user.end()) terms << "\" case=\"" << MG2XML(util::wstring2string(*(an->user.begin())));
	terms << "\">" << endl;
	terms << "   <span>" << endl << "    <target id=\"w" << word << "\"/>" << endl;
	terms << "   </span>" << endl << "  </term>" << endl;
	
	term++;
      }

      word++;
    }

    sent++;
  }

  cout << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
  cout << "<NAF xml:lang=\"eu\" version=\"2.0\">" << endl;

  //<lp name="ixa-pipe-dependencies-Basque" beginTimestamp="2015-04-13T18:38:37+0200" endTimestamp="2015-04-13T18:39:01+0200" version="1.0" hostname="basajaun"/>

  string endtime = currentDateTime();

  cout << "<nafHeader>" << endl;
  cout << " <linguisticProcessors layer=\"text\">\n  <lp name=\"EHU-eustagger\" version=\"1.0.0\" beginTimestamp=\"" << endtime << "\" endTimestamp=\"" << endtime << "\"/>\n </linguisticProcessors>" << endl;
  cout << " <linguisticProcessors layer=\"terms\">\n  <lp name=\"EHU-eustagger\" version=\"1.0.0\" beginTimestamp=\"" << endtime << "\" endTimestamp=\"" << endtime << "\"/>\n </linguisticProcessors>" << endl;
  cout << "</nafHeader>" << endl;

  cout << " <text>" << endl << text.str() << " </text>"<< endl;
  cout << " <terms>" << endl << terms.str() << " </terms>"<< endl;

  cout << "</NAF>" << endl;

  cerr << "Finished: " << sent << " sentences analyzed." << endl;

  cout.flush();
}
