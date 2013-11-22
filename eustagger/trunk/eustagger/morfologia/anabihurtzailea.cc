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


#include "anabihurtzailea.h"
#include <string.h>
#include <fstream>
#include "filtro.h"

extern void bihur_asteris_maj(char *,char *);
extern void bihur_maj_asteris(char *,char *);
extern int kendu_marka_lex(char *,char *,int);

using namespace pcrepp;

anaBihurtzailea::anaBihurtzailea() {

  Pcre tez_zenb("[^0-9]");
  Pcre tdiak("[123489]");
  Pcre tdiak_98("[1234\\/%]");
  Pcre tbat("1$");
  Pcre tbi("2$");
  Pcre thiru("3$");
  Pcre tlau("4$|^4");
  Pcre tzortzi("8");
  Pcre tbederatzi("9","g");
  Pcre tkenAld("(\\[ald_[^\\[]+\\])","g");
  Pcre tkenSarrera("(\\[Sarrera_[^\\[]+\\])","g");
  //  Pcre tkenTwol("\\[[AS]Twol_[^\\]]+\\]","g");
  Pcre tkenAldaera("(\\[Aldaera_[^\\[]+\\])","g");
  Pcre tkenSar("(\\[SAR_[^\\[]+\\])","g");
  Pcre tkenAoi("(\\[AOI_)(a+)");
  Pcre tkenAdoin("(\\[ADOIN_)(a+)");
  Pcre tkenPlusMinus("(\\[(BIZ|IZAUR|ZENB|NEUR|RARE|HBN|LHB)_[^\\[\\]]+\\])","g"); /* Ez dira bakarrik+/+, RARE ere */
  Pcre tkenErrorKode("(\\[ERROR-KODE_[^\\[\\]]+\\])","g");
  Pcre tkenBim("^([^\\[]+)");
  Pcre tkenBimG("(\\][^\\]\\[]+\\[)","g");
  Pcre tlorBim("([^\\[]+)");
  Pcre tbilatuHasiera("(\\[ERAKAT_)");
  Pcre taldatuEraazp("(\\[ERAAZP_)");
  Pcre taldatuAoi("(\\[AOI_)(a+)");
  Pcre taldatuAoiPar("(\\(AOI )(a+)");
  Pcre taldatuSar("(\\[\\SAR_)([Aa]+)\\]");
  Pcre taldatuSarPar("(\\(\\SAR )([Aa]+)\\)");
  Pcre taldatuAdoin("(\\[ADOIN_)(a+)");
  Pcre taldatuAdoinPar("(\\(ADOIN )(a+)");
  Pcre taldatuSarrera("(\\[\\Sarrera_)([Aa]+)\\]");
  Pcre taldatuSarreraPar("(\\(\\Sarrera )([Aa]+)\\)");
  Pcre tkat("(\\[KAT_[^\\[\\]]+\\])");
  Pcre tazp("(\\[AZP_[^\\[\\]]+\\])");
  Pcre tmtkat("(\\[MTKAT_[^\\[\\]]+\\])");
  Pcre tbst("\\[KAT_BST\\]");


  bst = tbst;
  ez_zenb = tez_zenb;
  diak = tdiak;
  diak_98 = tdiak_98;
  bat = tbat;
  bi = tbi;
  hiru = thiru;
  lau = tlau;
  zortzi = tzortzi;
  bederatzi = tbederatzi;
  kenAld = tkenAld;
  kenSarrera = tkenSarrera;
  kenAldaera = tkenAldaera;
  kenSar = tkenSar;
  kenPlusMinus = tkenPlusMinus;
  kenErrorKode = tkenErrorKode;
  kenAdoin = tkenAdoin;
  kenAoi = tkenAoi;
  kenBim = tkenBim;
  kenBimG = tkenBimG;
  lorBim = tlorBim;
  bilatuHasiera = tbilatuHasiera;
  aldatuEraazp = taldatuEraazp;
  aldatuAdoin = taldatuAdoin;
  aldatuAoi = taldatuAoi;
  aldatuAdoinPar = taldatuAdoinPar;
  aldatuAoiPar = taldatuAoiPar;
  aldatuSar = taldatuSar;
  aldatuSarrera = taldatuSarrera;
  aldatuSarPar = taldatuSarPar;
  aldatuSarreraPar = taldatuSarreraPar;
  kat = tkat;
  azp = tazp;
  mtkat = tmtkat;
  char *tmp;
  string path;
  tmp = (char *)malloc(200*sizeof(char));
  tmp[0] = '\0';
  if ((tmp = getenv("IXA_PREFIX")) != NULL) { 
    path = tmp;
    path = path + "/var/eustagger_lite/morfologia";
  }
  else
    path = ".";
  path = path + "/kat_trig_maila_2_datuak";
  path = path + "4.4.1";
  path = path + ".txt";
  edbl_bertsioa = 4;
  std::ifstream trigram(path.c_str());
  string tag, trig;
  int count = 0;
  while (trigram >> tag >> trig >> count) {
    if (trig.length() == 2)
      trig = " " + trig;
    else if (trig.length() == 1)
      trig = "  " + trig;
    tag_trig p(tag,trig);
    trigramak[p] = count;
    if (zenbat_etiketako.count(tag) > 0)
      zenbat_etiketako[tag]++;
    else
      zenbat_etiketako[tag]=1;
  }

}


const string anaBihurtzailea::lispifikatu (char *analisia,int ident_da,int zen_da, int zen_dek_da, int errom_da)
{
  int morfema_da = 0;
  Pcre thmorf("^([^\\(]+)\\(\\(");
  Pcre thald("^([^\\(]+)\\(ald ([^)]+)");
  Pcre tbanz("\\[", "g");
  Pcre tbans("\\]","g");
  Pcre tzuriune("\\)_\\(","g");
  Pcre tazpi1("([^_])_([^_])","g");
  Pcre tazpi2("__","g");
  Pcre tmorf("\\)\\)([+]?)([^\\(\\)+\\s]+)\\(\\(");
  Pcre tald("\\)\\)([+]?)([^\\(\\)+\\s]+)\\(ald ([^)]+)");
  Pcre terr("\\(ERR (7)","g");
  Pcre tzuriune2("Sarrera__-","g");
  Pcre tamaierakoplus("[+]$");
  Pcre tlehenplus("\\)\\)([+])([^\\(\\)+\\s]+)");

  Pcre hmorf = thmorf;
  Pcre hald = thald;
  Pcre banz = tbanz;
  Pcre bans = tbans;
  Pcre zuriune = tzuriune;
  Pcre azpi1 = tazpi1;
  Pcre azpi2 = tazpi2;
  Pcre morf = tmorf;
  Pcre ald = tald;
  Pcre err = terr;
  Pcre zuriune2 = tzuriune2;
  Pcre amaierakoplus = tamaierakoplus;
  Pcre lehenplus = tlehenplus;

  string sar = analisia;
  if (banz.search(sar)) {
    sar=banz.replace(sar,"(");
  }
  if (bans.search(sar)) {
    sar=bans.replace(sar,")");
  }
  if (zuriune.search(sar)) {
    sar=zuriune.replace(sar,")__(");
  }
  if (azpi1.search(sar)) {
    //    sar=azpi1.replace(sar,"$1 $2");
    sar=azpi1.replace(sar,"$1 $2");
  }
  if (azpi2.search(sar)) {
    sar=azpi2.replace(sar,"_");
  }
  if (hmorf.search(sar)) {
    // lehenengo morfema estandarra prozesatu
    string morfema = hmorf.get_match(0);
//     if (morfema[morfema.length()-1] == '+') { // falta da + hori kentzea HAU EZ DA INOIZ GERTATUKO????
//       morfema_da = 1;
//     }
    if (morfema == "ba" || morfema == "bait") {
      if (lehenplus.search(sar)) {
	string plus = lehenplus.get_match(0);
	if (plus.length() == 1)
	  sar = lehenplus.replace(sar,"))$2");
      }
      morfema_da = 1;
    }
    if (morfema_da) {
      morfema=bihurtu_xerox_lemati(morfema);
      sar = hmorf.replace(sar,"(morf \""+morfema+"\")((");
    }
    else {
      if (!ident_da && !zen_dek_da && !zen_da && !errom_da)
	morfema=bihurtu_xerox_lemati(morfema);
      sar = hmorf.replace(sar,"(lema \""+morfema+"\")((");
      if (aldatuSarreraPar.search(sar) || aldatuSarPar.search(sar))
	sar = this->aldatuSarInfoPar(sar,morfema.c_str(), 0);
    }
  }
  else {
    if (hald.search(sar)) {
      // lehenengo morfemen aldaerak prozesatzerakoan $ ipini eta aldaera "" artean
      string morfema = hald.get_match(0);
      string aldaera = hald.get_match(1);
      morfema=bihurtu_xerox_lemati(morfema);
      aldaera=bihurtu_xerox_lemati(aldaera);
//       if (morfema[morfema.length()-1] == '+') { // HAU EZ DA GERTATZEN???
// 	morfema_da = 1;
//       }
      if (morfema == "ba" || morfema == "bait") {
	if (lehenplus.search(sar)) {
	  string plus = lehenplus.get_match(0);
	  if (plus.length() == 1)
	    sar = lehenplus.replace(sar,"))$2");
	}
	morfema_da = 1;
      }
      if (morfema_da) {
	sar = hald.replace(sar,"(morf $ \""+morfema+"\")(ald \""+aldaera+"\"");
      }
      else {
	sar = hald.replace(sar,"(lema $ \""+morfema+"\")(ald \""+aldaera+"\"");
	if (aldatuSarreraPar.search(sar) || aldatuSarPar.search(sar))
	  sar = this->aldatuSarInfoPar(sar,morfema.c_str(), 0);
      }
    }
  }
  while (morf.search(sar)) {
    // gainerako morfema estandarrak prozesatu
    string plus = morf.get_match(0);
    string morfema,morfemaAld;
    string sarTmp = sar;
    morfema_da = 0;
    if (plus.length() == 1)
      morfema_da = 1;
    if (plus.length() > 1) {
      plus = morf.get_match(1);
      if (plus.length() == 1)
	morfema_da = 1;
      morfema = morf.get_match(2);
    }
    else
      morfema = morf.get_match(1);
    morfemaAld=bihurtu_xerox_lemati(morfema);
    if ((morfema[morfema.length()-1] == '\\') && morfema[morfema.length()-2] != '\\') {
      morfema += "\\";
    }
    if (morfema[morfema.length()-1] == '^') {
      morfema[morfema.length()-1] = '\\';
      morfema += "^";
    }
    if (morfema_da) {
      string patt = "\\)\\)[+]"+morfema+"\\(\\(";
      Pcre morfAld=patt;
      sar = morfAld.replace(sarTmp,")))\n   ((morf \""+morfemaAld+"\")((");
    }
    else {
      string patt = "\\)\\)"+morfema+"\\(\\(";
      Pcre morfAld = patt;
      sar = morfAld.replace(sarTmp,")))\n   ((lema \""+morfemaAld+"\")((");
      if (aldatuSarreraPar.search(sar) || aldatuSarPar.search(sar))
	sar = this->aldatuSarInfoPar(sar,morfemaAld.c_str(), 0);
    }
  }

  while (ald.search(sar)) {
    // gainerako morfemen aldaerak prozesatzerakoan $ ipini eta aldaera "" artean
    string plus = ald.get_match(0);
    string morfema;
    string aldaera;
    morfema_da = 0;
    if (plus.length() == 1)
      morfema_da = 1;
    if (plus.length() > 1) {
      plus = ald.get_match(1);
      if (plus.length() == 1)
	morfema_da = 1;
      morfema = ald.get_match(2);
      aldaera = ald.get_match(3);
    }
    else{
      morfema = ald.get_match(1);
      aldaera = ald.get_match(2);
    }
    morfema=bihurtu_xerox_lemati(morfema);
    aldaera=bihurtu_xerox_lemati(aldaera);
    if (morfema[morfema.length()-1] == '+') { // falta da + hori kentzea
      morfema_da = 1;
    }
    if (morfema == "ba" || morfema == "bait") {
      morfema_da = 1;
    }
    if (morfema_da) {
      sar = ald.replace(sar,")))\n   ((morf $ \""+morfema+"\")(ald \""+aldaera+"\"");
    }
    else {
      sar = ald.replace(sar,")))\n   ((lema $ \""+morfema+"\")(ald \""+aldaera+"\"");
      if (aldatuSarreraPar.search(sar) || aldatuSarPar.search(sar))
	sar = this->aldatuSarInfoPar(sar,morfema.c_str(), 0);
    }
  }

  // (ERR *xxxx--3)) beharrean (ERR 7xxxx--3) 
  //  Pcre terr("\\(ERR 7","g");
  if (err.search(sar)) {
    sar = err.replace(sar,"(ERR *"); // guztiak aldiberean, baina ez da egongo bat baino gehiago
  }

  sar=zuriune2.replace(sar,"Sarrera _-");
  sar=amaierakoplus.replace(sar,"");
  return(sar);
}

const string anaBihurtzailea::bihurtu_xerox_lemati (string aldatzeko) {
  string hitza=aldatzeko;

  if ( ez_zenb.search(hitza) && diak.search(hitza) ) {
    if (bat.search(hitza)) {
      hitza=bat.replace(hitza,"%");
    }
    if (bi.search(hitza)) {
      hitza=bi.replace(hitza,"#");
    }
    if (hiru.search(hitza)) {
      hitza=hiru.replace(hitza,":");
    }
    if (lau.search(hitza)) {
      hitza=lau.replace(hitza,"!");
    }
    if (zortzi.search(hitza)) {
      hitza=zortzi.replace(hitza,"\303\261");
    }
    Pcre tbederatzi("9","g");
    if (tbederatzi.search(hitza)) {
      hitza=tbederatzi.replace(hitza,"*");
    }
  }
// 	  $morf =~ s/1/\%/g;
// 	  $morf =~ s/2/\#/g;
// 	  $morf =~ s/3/\:/g;
// 	  $morf =~ s/4/\!/g;
// 	  $morf =~ s/8/ñ/g;
// 	  $morf =~ s/9/\*/g;
  return(hitza);
}

const string anaBihurtzailea::kenduInfoEzKonparagarria(const string analisiOsoa) {
  string analisia = analisiOsoa;

  if (kenAld.search(analisia)) {
    analisia=kenAld.replace(analisia,"");
  }
  if (kenSarrera.search(analisia)) {
    analisia=kenSarrera.replace(analisia,"");
  }
  if (kenAldaera.search(analisia)) {
    analisia=kenAldaera.replace(analisia,"");
  }
//   if (kenTwol.search(analisia)) {
//     analisia=kenTwol.replace(analisia,"");
//   }
  if (kenSar.search(analisia)) {
    analisia=kenSar.replace(analisia,"");
  }
  if (kenAdoin.search(analisia)) {
    analisia=kenAdoin.replace(analisia,"");
  }
  if (kenAoi.search(analisia)) {
    analisia=kenAoi.replace(analisia,"");
  }
  if (kenPlusMinus.search(analisia)) {
    analisia=kenPlusMinus.replace(analisia,"");
  }
  if (kenErrorKode.search(analisia)) {
    analisia=kenErrorKode.replace(analisia,"");
  }
  return analisia;
}
const string anaBihurtzailea::kenduBim(const string analisiOsoa) {
  string analisia = analisiOsoa;

  if (kenBim.search(analisia)) {
    analisia=kenBim.replace(analisia,"");
  }
  if (kenBimG.search(analisia)) {
    analisia=kenBimG.replace(analisia,"][");
  }
  return analisia;
}

const string anaBihurtzailea::aldatuBim(string analisiOsoa, string bimStr) {
  string analisia = analisiOsoa;
  //  Pcre aldatuBim("^([^\\[]+)");

  if (kenBim.search(analisia)) {
    analisia = kenBim.replace(analisia,bimStr);
  }

  return analisia;
}


const string anaBihurtzailea::lortuBim(const string analisiOsoa) {
  string bimStr;
  string analisia= analisiOsoa;
  //  Pcre lorBim2("^([^\\[]+)");

  if (lorBim.search(analisia,0)) {
    bimStr=lorBim.get_match(0);
  }
  return bimStr;
}

const string anaBihurtzailea::bihurtuEratorria(const string analisiOsoa) {
  string analisia = analisiOsoa;

  if (bilatuHasiera.search(analisia)) {
    int pos = bilatuHasiera.get_match_end();
    string analisia2 = "[[KAT"; // aurrekoak azpimarraren posizioa emango du
    analisia2 = analisia2 + &analisia[pos];
    analisia = analisia2;
    // Kendu ERAKAT arteko guztia eta ERAKAT ordez KAT jarri
  }
  if (aldatuEraazp.search(analisia)) {
    analisia=aldatuEraazp.replace(analisia,"[AZP_");
    //ERAAZP ordez AZP jarri
  }
  return analisia;
}

// Hau egokitu behar da 3.3.? bertsioetarako baliagarria izan dadin.

int anaBihurtzailea::desanbEratorpena(int m, char anal[][LUZMAXAN],char motak[],int distantziak[]){
  valarray<int> dist(distantziak,m); 
  map<string,int> an_garbia_map; // analisi garbiak 
  int ema_indizeak[ANMAX];
  vector<string> ema_ana;
  char mot[ANMAX];
  int j = 0;
  int eratorririk = 0;
  string analisia,eralema;

  // Estandar eta aldaeretan kendu eratorpen bidezko analisia, lexikalizatuarena badago
  // Lexikorik gabekoetan kendu eratorpen bidezko lema baino luzeagoak (ez da oso probablea)

  // lehenengo begiratu eratorririk dagoen (sartu aurretik egin)
  for (int k=0;k<m;k++) {
    if (strstr(&anal[k][0],"[ERAKAT_") != NULL) {
      eratorririk++;
    }
  }
  // ondoren gorde lexikalizatuen analisiak baina bim, ald, Sarrera kenduta??

  if (eratorririk > 0 && eratorririk < m) {
    for (int k=0;k<m;k++) {
      ema_indizeak[k] = -1; // defektuz ez gorde emaitza
      if (strstr(&anal[k][0],"[ERAKAT_") == NULL) {
	// garbitu, MAPean sartu eta k gorde emaitzan
	map<string,int>::iterator dago;

	//	analisia =&anal[k][0];
	analisia = kenduBim(&anal[k][0]);
	analisia = kenduInfoEzKonparagarria(analisia);
	dago = an_garbia_map.find(analisia);
	if (dago == an_garbia_map.end()) { // ez dago, sartu
	  ema_indizeak[k] = j;
	  ema_ana.push_back(&anal[k][0]);
	  dist[j] = distantziak[k];
	  mot[j] = motak[k];
	  an_garbia_map[analisia] = k;
	  j++;
	}
	else {
	  // litekeena da BIM desberdinarekin IM berbera izatea (adib -A duenean)
	  // an_garbia_map-en ez sartu baina bere analisia gehitu
	  ema_indizeak[k] = j;
	  ema_ana.push_back(&anal[k][0]);
	  dist[j] = distantziak[k];
	  mot[j] = motak[k];
	  //	  an_garbia_map[analisia] = k;
	  j++;	  
	}
      }
    }
    
    // bigarren bueltan eratorriak konparatu lexikalizatuekin bim, ald, Sarrera kenduta
    // Gainera, [KAT eta [AZP eta [KAT_ATZ] kendu eta [ERAKAT_IZE][ERAAZP_ARR]] KAT eta AZP bihurtu
    // errazena agian lehenengo [KAT_ATZ]rainoko guztia kentzea da, eta ondoren ERA kendu
    for (int k=0;k<m;k++) {
      // garbitu, MAPean begiratu eta k gorde emaitzan ez badago baliokiderik
      if (ema_indizeak[k] == -1) { // ERAKAT dauka
	map<string,int>::iterator dago;
	
	analisia = bihurtuEratorria(&anal[k][0]);
	analisia = kenduBim(analisia); // gainerako morfemen Bim kendu konparatzeko
	analisia = kenduInfoEzKonparagarria(analisia);
	
	dago = an_garbia_map.find(analisia);
	if (dago == an_garbia_map.end()) { // ez dago, sartu
	  ema_indizeak[k] = j;
	  ema_ana.push_back(&anal[k][0]);
	  dist[j] = distantziak[k];
	  mot[j] = motak[k];
	  an_garbia_map[analisia] = k;
	  j++;
	}
	else {
	  // Hobetsi lexikalizatua
	  if (motak[k] == 'G' && eralema.length() == 0) {
	    int lexikal = an_garbia_map[analisia];
	    eralema = lortuBim(&anal[lexikal][0]);
// 	    if (eralema[eralema.length()-1] == 'A') 
// 	      eralema[eralema.length()-1] = '\0';
	  }
	}
      }
    }
    // Orain utzi bakarrik beharrezkoak direnak emaitzan.
    int i = 0;
    for (int k=0;k<j;k++) {
      string anlema;
      if (mot[k] == 'G' && eralema.length() > 0)
	// eratorpen bidezkoak baino lema luzeagoak ez emateko
	anlema = lortuBim(&anal[k][0]);
      if (mot[k] != 'G' || anlema.length() <= strlen(eralema.c_str())) {
	strcpy(anal[i],ema_ana[k].c_str());
	distantziak[i] = dist[k];
	motak[i] = mot[k];
	i++;
      }
    }
    if (i > 0)
      j = i;
    else if (j == 0)
      j = m;
  }
  else 
    j = m;

  return j;
}

/// hau egin beharko litzateke analisi fasean eta emaitza vector<string> batean zuzenean
/// ez ibiltzeko bihurketa absurdoetan
/// gainera, garbitu funtzio bat beharko da, gero eratorpenaren desanbiguazioa ere egin ahal izateko

int anaBihurtzailea::desanbAldaerak(int m, char anal[][LUZMAXAN],char motak[],int distantziak[],int distantzia_minimoa){
  valarray<int> dist(distantziak,m); 
  map<string,int> an_garbia_map; // analisi garbiak 
  int ema_indizeak[ANMAX];
  vector<string> ema_ana;
  char mot[ANMAX];
  int j = 0;
  int zerokoak_daude = 0;
  string analisia;
  Pcre aldMorf("(\\[ald_)");
  Pcre aldaeraEdbl("(\\]\\[ERROR-KODE_)");

  aldMorf.study();
  aldaeraEdbl.study();
  if (m > 1 && dist.max() > 0) {
    // lehenengo aztertu bakarrik distantzia == 0 dutenak eta gero distantzia > 1 dutenak
    if (dist.min() == 0)
      zerokoak_daude = 1;

    for (int k=0;k<m;k++) {
      ema_indizeak[k] = -1; // defektuz ez gorde emaitza
      int aldKop = 0;
      int edblKop = 0;
      analisia = &anal[k][0];
      while (aldMorf.search(analisia)){
	aldKop++;
	analisia = aldMorf.replace(analisia,"[ALD_"); 
	// ez errepikatzeko leku berean
      }
      while (aldaeraEdbl.search(analisia)){
	edblKop++;
	analisia = aldaeraEdbl.replace(analisia,"][error-kode_");
	// ez errepikatzeko leku berean
      }
      if (aldKop - edblKop != distantziak[k]) {
	if (aldKop+edblKop>0 && aldKop - edblKop >= 0) {
	 distantziak[k] = aldKop - edblKop;
	}
	else {
	  if (aldKop+edblKop>0) {
	    distantziak[k] = 0;
	  }
	}
      }
      if (distantziak[k] == 0) {
	// garbitu, MAPean sartu eta k gorde emaitzan
	map<string,int>::iterator dago;

	analisia = kenduInfoEzKonparagarria(&anal[k][0]);

	dago = an_garbia_map.find(analisia);
	if (dago == an_garbia_map.end()) { // ez dago, sartu
	  ema_indizeak[k] = j;
	  ema_ana.push_back(&anal[k][0]);
	  dist[j] = distantziak[k];
	  mot[j] = motak[k];
	  an_garbia_map[analisia] = k;
	  j++;
	}
      }
    }
    // bigarren bueltan dist>0 dutenetan ikusteko ea badagoen analisi baliokiderik EDBLko informazioan oinarrituta
    // DISTANTZIA PARAMETRIZATU
    for (int k=0;k<m;k++) {
      if (!distantzia_minimoa || (distantzia_minimoa && !zerokoak_daude && distantziak[k] > 0 && distantziak[k] < 2)) {
	// garbitu, MAPean begiratu eta k gorde emaitzan ez badago baliokiderik
	map<string,int>::iterator dago;

	analisia = kenduInfoEzKonparagarria(&anal[k][0]);

	dago = an_garbia_map.find(analisia);
	if (dago == an_garbia_map.end()) { // ez dago, sartu
	  ema_indizeak[k] = j;
	  ema_ana.push_back(&anal[k][0]);
	  dist[j] = distantziak[k];
	  mot[j] = motak[k];
	  an_garbia_map[analisia] = k;
	  j++;
	}
	else {
	  // Hobetsi bakarrik erregela, EDBL+erregela aurretik
	  // eta ErrorKode bakarra hobetsi ErrorKode gehiagoren aurretik
	  int non = an_garbia_map[analisia];
	  int matchk = 0;
	  int matchnon = 0;
	  if (kenErrorKode.search(anal[k]))
	    matchk = kenErrorKode.matches();
	  if (kenErrorKode.search(anal[non]))
	    matchnon =kenErrorKode.matches();
	  if ((distantziak[non] == distantziak[k] 
// 	      && strstr(&anal[k][0],"[ERROR-KODE_") == 0
// 	      &&strstr(&anal[non][0],"[ERROR-KODE_") != 0 
	       && matchk < matchnon)
	      || distantziak[non] > distantziak[k]
	      ) {
	    // ordezkatu
	    int posizioa = ema_indizeak[non];
	    ema_indizeak[k] = posizioa;
	    ema_indizeak[non] = -1;
	    ema_ana[posizioa] = &anal[k][0];
	    dist[posizioa] = distantziak[k];
	    mot[posizioa] = motak[k];
	    an_garbia_map[analisia] = k;
	  }
	}
      }
    }
    // Orain utzi bakarrik beharrezkoak direnak emaitzan. Lehenengo 0 erregela, gero besteak
    //    j = 0;
    for (int k=0;k<j;k++) {
      strcpy(anal[k],ema_ana[k].c_str());
      distantziak[k] = dist[k];
      motak[k] = mot[k];
    }
  }
  else
    j = m;

  return j;
}


int anaBihurtzailea::desanbLexGabe(int m, char anal[][LUZMAXAN],char motak[],int distantziak[], string forma){
 // int ema_indizeak[ANMAX];
 valarray<int> dist(distantziak,m); 
 vector<string> ema_ana;
 char mot[ANMAX];
 int j = 0, marraAurrekoa = 0, den_mai_da = 0;
 string analisia,lema,formaHas,formaHasmin;
 string partForma;
 Pcre tadmadoin("\\[ADM_ADOIN\\]");
 Pcre tizblib("\\[AZP_(IZB|LIB)\\]");
 Pcre tpar("\\[KAS_PAR\\]");
 Pcre tgendesk("\\[KAS_(GEN|DESK)\\]");
 Pcre tgel("\\[KAS_GEL\\]");
 Pcre tgen("\\[KAS_GEN\\]");
 Pcre tabsmg("\\[KAS_ABS\\]\\[MUG_MG\\]");
 Pcre tsoz("\\[KAS_SOZ\\]");
 Pcre tala("\\[KAS_ALA\\]");
 Pcre tpro("\\[KAS_PRO\\]");
 Pcre tsup("\\[MAI_SUP\\]");
 Pcre tadj("\\[KAT_ADJ\\]");
 Pcre tkas("\\[KAT_DEK\\]\\[KAS_");
 Pcre tmarratxoa("([^-]+)-[^-]+");
 Pcre tden_mai("^([A-Z\321]+)-?[a-z]+");
 Pcre tizar("\\*","g");
 Pcre trare("\\[RARE_");

 Pcre rare = trare;
 Pcre admadoin = tadmadoin;
 Pcre izblib = tizblib;
 Pcre par = tpar;
 Pcre gendesk = tgendesk;
 Pcre gel = tgel;
 Pcre gen = tgen;
 Pcre absmg = tabsmg;
 Pcre soz = tsoz;
 Pcre ala = tala;
 Pcre pro = tpro;
 Pcre sup = tsup;
 Pcre adj = tadj;
 Pcre kas = tkas;
 Pcre marratxoa = tmarratxoa;
 Pcre den_mai = tden_mai;
 Pcre izar = tizar;


 char sar[LUZMAXAN],irt[LUZMAXAN];
 string formaTmp;

 sar[0] = '\0';
 irt[0] = '\0';
 strcpy(sar,forma.c_str());
 bihur_asteris_maj(sar,irt);
 formaTmp = irt;
 formaHas = forma;

 if (marratxoa.search(forma))
   formaHas = marratxoa.get_match(0);
 else if (den_mai.search(formaTmp)){
   string zatia = den_mai.get_match(0); 
   unsigned int zatl = zatia.length();
   if (zatl>1 && zatl != formaTmp.length()) {
     strcpy(sar,zatia.c_str());
     bihur_maj_asteris(sar,irt);
     formaHas = irt;
     den_mai_da = 1;
   }
 }

 // 9-ak '*' bihurtu
 formaHas = bihurtu_xerox_lemati(formaHas);

 if (formaHas[0] == '*') {
   formaHasmin = formaHas.substr(1,string::npos); // kendu hasierako */9
   partForma = formaHasmin;
 }


 if (izar.search(formaHasmin)) {
   formaHasmin=izar.replace(formaHasmin,"");
 }

 if (izar.search(formaHas,1)) {
   if (formaHas[0] == '*')
     formaHas= "*" + izar.replace(partForma,"");
   else
     formaHas=izar.replace(formaHas,"");
 }
 else
   den_mai_da = 0;

 for (int k=0;k<m;k++) {
   // ema_indizeak[k] = -1; // defektuz ez gorde emaitza
   // filtratu
   analisia = &anal[k][0];
   lema = lortuBim(analisia);
   lema = bihurtu_xerox_lemati(lema);

//    analisia = kenduInfoEzKonparagarria(&anal[k][0]);
   if (lema[0] == '*' && !izblib.search(analisia)) {
       // Maiuskulaz baina ez IZB/LIB
     //     cerr << "deslok 2: Maiusk+ !izblib "<<analisia <<"\n";
     continue;
   }
   if (izar.search(lema.substr(1,string::npos))) {
     //kendu '*' luzerak kontuan hartzeko
     if (lema[0] == '*')
       lema = "*" + izar.replace(lema,"");
     else
       lema = izar.replace(lema,"");
   }
   if (den_mai_da && lema.compare(formaHasmin)!=0) {
     // Maiuskula zati bat badu eta lema ez badator bat, kendu
     continue;
   }
   if (lema.length() > 4 && bst.search(analisia)) {
     //     cerr << "deslok 1: BST+|lema|>4 "<<analisia <<"\n";
     // edo BST izanda ere, ez badator bat maiuskulaz agertzen den zatiarekin, kendu
     continue;
   }
   if (rare.search(analisia)) {
     continue;
   }
//    if (Aorg.search(lema) && izblib.search(analisia)==0) {
//      //     cerr << "deslok 3: 'A' + !izblib "<<analisia <<"\n";
//      continue; // Kendu A organikoa, ez bada IZB edo LIB
//    }
//    if (admadoin.search(analisia) || // ADOIN kendu
//        izblib.search(analisia) && par.search(analisia) || // IZB/LIB + PAR
//        gendesk.search(analisia) && absmg.search(analisia) || // GEN/DESK + ABS MG oso probabilitate txikia
//        gel.search(analisia) && absmg.search(analisia) && 
//        !ala.search(analisia) && !soz.search(analisia) || // GEL + ABS MG kendu, baina ez SOZ/ALA aurretik
//        gen.search(analisia) && pro.search(analisia) || // GEN+PRO kendu, DES probableago
//        adj.search(analisia) && sup.search(analisia) && (absmg.search(analisia) || !kas.search(analisia) 
// 							|| pro.search(analisia))
//        //ADJ + SUP + ZERO|ABS MG|PRO (en+tzat, DES probableago)?? baino probableago GEN
//        )
   if (admadoin.search(analisia)) {
     // ADOIN kendu
     //     cerr << "deslok 4: ADOIN "<<analisia <<"\n";
     continue;
   }
   if (izblib.search(analisia) && par.search(analisia)) {
       // IZB/LIB + PAR
     //     cerr << "deslok 5: izblib+par "<<analisia <<"\n";
     continue;
   }
   if (gendesk.search(analisia) && absmg.search(analisia)) {
     // GEN/DESK + ABS MG oso probabilitate txikia
     //    cerr << "deslok 6: gendesk+absmg "<<analisia <<"\n";
     continue;
   }
   if(gel.search(analisia) && absmg.search(analisia) && 
      !ala.search(analisia) && !soz.search(analisia)) {
     // GEL + ABS MG kendu, baina ez SOZ/ALA aurretik
     //     cerr << "deslok 7: gel+absmg + !soz/ala "<<analisia <<"\n";
     continue;
   }
   if (gen.search(analisia) && pro.search(analisia)) {
     // GEN+PRO kendu, DES probableago
     //     cerr << "deslok 8: gen+pro "<<analisia <<"\n";
     continue;
   }
   if (adj.search(analisia) && sup.search(analisia) && 
       (absmg.search(analisia) || !kas.search(analisia) || pro.search(analisia))){
       //ADJ + SUP + ZERO|ABS MG|PRO (en+tzat, DES probableago)?? baino probableago GEN
     //     cerr << "deslok 9: adj+sup+(zero/absmg/pro) gen hobesteko "<<analisia <<"\n";
     continue;
   }
   // hona iritsi direnak gorde
   // ema_indizeak[k] = j;
   ema_ana.push_back(&anal[k][0]);
   mot[j] = motak[k];
   dist[j] = distantziak[k];
   j++;
   if (!marraAurrekoa && (lema.compare(formaHas) == 0 || lema.compare(formaHasmin) == 0))
     marraAurrekoa = 1;
 }
 if (j > 0) {
   int i = 0;
   for (int k=0;k<j;k++) {
     analisia = ema_ana[k];
     lema = lortuBim(analisia);
     if (diak_98.search(lema.substr(1,string::npos))) // 9 eta 8 kenduta...
       lema = lema.substr(0,lema.length()-1);
 
    lema = bihurtu_xerox_lemati(lema);
    if (izar.search(lema.substr(1,string::npos))) {
      //kendu '*' formekin konparatzeko
      if (lema[0] == '*')
	lema = "*" + izar.replace(lema,"");
      else
	lema = izar.replace(lema,"");
    }
    if (lema[lema.length()-1] == 'R') lema[lema.length()-1] = 'r';
     if (!marraAurrekoa || 
	 (marraAurrekoa && (lema.compare(formaHas) == 0 || lema.compare(formaHasmin) == 0))) {
       // formak marratxoa (edo DEN_MAIdek) badu eta baldin badago analisirik marratxo aurreko lemarekin, horiek utzi
       //     strcpy(anal[i],ema_ana[k].c_str());
       ema_ana[i] = analisia;
       dist[i] = dist[k];
       mot[i] = mot[k];
       i++;
     }
   }
   // Pasa geratu diren i analisiak etiketa+trigramak erabiltzen dituenera
   if (i > 2) { 
     j = desanbKatTrig(i, ema_ana, mot,dist);
   }
   i = 0;
   for (int k=0;k<j;k++) {
     strcpy(anal[i],ema_ana[k].c_str());
     distantziak[i] = dist[k];
     motak[i] = mot[k];
     i++;
   }
   if (i > 0)
     j = i;
 }
 else {// hasierako m analisiak etiketa+trigramak aplikatu
   if (m>2) {
     for (int k=0;k<m;k++) {
       ema_ana.push_back(&anal[k][0]);
     }
     j = desanbKatTrig(m, ema_ana, mot,dist);
   }
 }
 
//  map<tag_trig,int>::const_iterator t;
//  for (t=trigramak.begin();t != trigramak.end();++t){
//    tag_trig p = t->first;
//    int c = t->second;
//    cerr << p.first << "\t" << p.second << "\t" << c << endl;
//  }
 if (j == 0) return m;
 return j;
}


int anaBihurtzailea::desanbEstandar(int m, char anal[][LUZMAXAN],char motak[],int distantziak[], string forma){
 // int ema_indizeak[ANMAX];
 valarray<int> dist(distantziak,m); 
 vector<string> ema_ana;
 char mot[ANMAX];
 int j = 0, marraAurrekoa = 0, den_mai_da = 0;
 string analisia,lema,formaHas,formaHasmin;
 string partForma;
 Pcre tadmadoin("\\[ADM_ADOIN\\]");
 Pcre tizblib("\\[AZP_(IZB|LIB)\\]");
 Pcre tpar("\\[KAS_PAR\\]");
 Pcre tgendesk("\\[KAS_(GEN|DESK)\\]");
 Pcre tgel("\\[KAS_GEL\\]");
 Pcre tgen("\\[KAS_GEN\\]");
 Pcre tabsmg("\\[KAS_ABS\\]\\[MUG_MG\\]");
 Pcre tsoz("\\[KAS_SOZ\\]");
 Pcre tala("\\[KAS_ALA\\]");
 Pcre tpro("\\[KAS_PRO\\]");
 Pcre tsup("\\[MAI_SUP\\]");
 Pcre tadj("\\[KAT_ADJ\\]");
 Pcre tbst("\\[KAT_BST\\]");
 Pcre tkas("\\[KAT_DEK\\]\\[KAS_");
 Pcre tmarratxoa("([^-]+)-[^-]+");
 Pcre tden_mai("^([A-Z\321]+)-?[a-z]+");
 Pcre tizar("\\*","g");

 Pcre admadoin = tadmadoin;
 Pcre izblib = tizblib;
 Pcre par = tpar;
 Pcre gendesk = tgendesk;
 Pcre gel = tgel;
 Pcre gen = tgen;
 Pcre absmg = tabsmg;
 Pcre soz = tsoz;
 Pcre ala = tala;
 Pcre pro = tpro;
 Pcre sup = tsup;
 Pcre adj = tadj;
 Pcre bst = tbst;
 Pcre kas = tkas;
 Pcre marratxoa = tmarratxoa;
 Pcre den_mai = tden_mai;
 Pcre izar = tizar;

 char sar[LUZMAXAN],irt[LUZMAXAN];
 string formaTmp;

 sar[0] = '\0';
 irt[0] = '\0';
 strcpy(sar,forma.c_str());
 bihur_asteris_maj(sar,irt);
 formaTmp = irt;

 if (marratxoa.search(forma))
   formaHas = marratxoa.get_match(0);
 else if (den_mai.search(formaTmp)){
   string zatia = den_mai.get_match(0); 
   unsigned int zatl = zatia.length();
   if (zatl>1 && zatl != formaTmp.length()) {
     strcpy(sar,zatia.c_str());
     bihur_maj_asteris(sar,irt);
     formaHas = irt;
     den_mai_da = 1;
   }
 }

 // 9-ak '*' bihurtu
 formaHas = bihurtu_xerox_lemati(formaHas);

 if (formaHas[0] == '*') {
   formaHasmin = formaHas.substr(1,string::npos); // kendu hasierako */9
   partForma = formaHasmin;
 }

 if (izar.search(formaHasmin)) {
   formaHasmin=izar.replace(formaHasmin,"");
 }

 if (izar.search(formaHas,1)) {
   if (formaHas[0] == '*')
     formaHas= "*" + izar.replace(partForma,"");
   else
     formaHas=izar.replace(formaHas,"");
 }
 else
   den_mai_da = 0;

 for (int k=0;k<m;k++) {
   // ema_indizeak[k] = -1; // defektuz ez gorde emaitza
   // filtratu
   analisia = &anal[k][0];
   lema = lortuBim(analisia);
   lema = bihurtu_xerox_lemati(lema);

   if (lema[0] == '*' && !izblib.search(analisia)) {
       // Maiuskulaz baina ez IZB/LIB
     //     cerr << "deslok 2: Maiusk+ !izblib "<<analisia <<"\n";
     continue;
   }
   if (izar.search(lema.substr(1,string::npos))) {
     //kendu '*' luzerak kontuan hartzeko
     if (lema[0] == '*')
       lema = "*" + izar.replace(lema,"");
     else
       lema = izar.replace(lema,"");
   }
   if (den_mai_da && bst.search(analisia) && lema.compare(formaHasmin)!=0) {
     //     cerr << "deslok 1: BST+|lema|>4 "<<analisia <<"\n";
     // edo BST izanda ere, ez badator bat maiuskulaz agertzen den zatiarekin, kendu
     continue;
   }

//    if (admadoin.search(analisia)) {
//      // ADOIN kendu
//      //     cerr << "deslok 4: ADOIN "<<analisia <<"\n";
//      continue;
//    }
   if (izblib.search(analisia) && par.search(analisia)) {
       // IZB/LIB + PAR
     //     cerr << "deslok 5: izblib+par "<<analisia <<"\n";
     continue;
   }
   if (gendesk.search(analisia) && absmg.search(analisia)) {
     // GEN/DESK + ABS MG oso probabilitate txikia
     //    cerr << "deslok 6: gendesk+absmg "<<analisia <<"\n";
     continue;
   }
   if(gel.search(analisia) && absmg.search(analisia) && 
      !ala.search(analisia) && !soz.search(analisia)) {
     // GEL + ABS MG kendu, baina ez SOZ/ALA aurretik
     //     cerr << "deslok 7: gel+absmg + !soz/ala "<<analisia <<"\n";
     continue;
   }
   if (gen.search(analisia) && pro.search(analisia)) {
     // GEN+PRO kendu, DES probableago
     //     cerr << "deslok 8: gen+pro "<<analisia <<"\n";
     continue;
   }
   if (adj.search(analisia) && sup.search(analisia) && 
       (absmg.search(analisia) || !kas.search(analisia) || pro.search(analisia))){
       //ADJ + SUP + ZERO|ABS MG|PRO (en+tzat, DES probableago)?? baino probableago GEN
     //     cerr << "deslok 9: adj+sup+(zero/absmg/pro) gen hobesteko "<<analisia <<"\n";
     continue;
   }
   // hona iritsi direnak gorde
   // ema_indizeak[k] = j;
   ema_ana.push_back(&anal[k][0]);
   mot[j] = motak[k];
   dist[j] = distantziak[k];
   j++;
   if (!marraAurrekoa && (lema.compare(formaHas) == 0 || lema.compare(formaHasmin) == 0))
     marraAurrekoa = 1;
 }
 if (j > 0) {
   int i = 0;
   for (int k=0;k<j;k++) {
     analisia = ema_ana[k];
     lema = lortuBim(analisia);
     if (diak_98.search(lema.substr(1,string::npos))) // 9 eta 8 kenduta...
       lema = lema.substr(0,lema.length()-1);
 
    lema = bihurtu_xerox_lemati(lema);
    if (izar.search(lema.substr(1,string::npos))) {
      //kendu '*' formekin konparatzeko
      if (lema[0] == '*')
	lema = "*" + izar.replace(lema,"");
      else
	lema = izar.replace(lema,"");
    }
    if (lema[lema.length()-1] == 'R') lema[lema.length()-1] = 'r';
     if (!marraAurrekoa || 
	 (marraAurrekoa && (lema.compare(formaHas) == 0 || lema.compare(formaHasmin) == 0))) {
       // formak marratxoa (edo DEN_MAIdek) badu eta baldin badago analisirik marratxo aurreko lemarekin, horiek utzi
       //     strcpy(anal[i],ema_ana[k].c_str());
       ema_ana[i] = analisia;
       dist[i] = dist[k];
       mot[i] = mot[k];
       i++;
     }
   }
   // Pasa geratu diren i analisiak etiketa+trigramak erabiltzen dituenera
//    if (i > 2) { 
//      j = desanbKatTrig(i, ema_ana, mot,dist);
//    }
   j = i;
   i = 0;
   for (int k=0;k<j;k++) {
     strcpy(anal[i],ema_ana[k].c_str());
     distantziak[i] = dist[k];
     motak[i] = mot[k];
     i++;
   }
   if (i > 0)
     j = i;
 }
 else {// hasierako m analisiak etiketa+trigramak aplikatu
   j = m;
//    j = desanbKatTrig(m, ema_ana, mot,dist);
 }
//  map<tag_trig,int>::const_iterator t;
//  for (t=trigramak.begin();t != trigramak.end();++t){
//    tag_trig p = t->first;
//    int c = t->second;
//    cerr << p.first << "\t" << p.second << "\t" << c << endl;
//  }
 if (j == 0) return m;
 return j;
}


int anaBihurtzailea::desanbKatTrig(int m, vector<string> &ema_ana,char mot[], valarray<int> dist) {
  map<string,int> tag_pisua;
  map<string,string> ana_tag;
  valarray<int> pisu_guztiak(0,m);
  vector<string> sar_ana = ema_ana;
  char sar[LUZMAXAN],irt[LUZMAXAN];
  Pcre tlortuKatAzpMTKat("(\\[KAT_[^\\]]+\\]\\[AZP_[^\\]]+\\]\\[MTKAT_SIG\\])"); // Siglak bereziak
  Pcre tlortuKatAzp("(\\[KAT_[^\\]]+\\]\\[AZP_[^\\]]+\\])");
  Pcre tlortuKat("(\\[KAT_[^\\]]+\\])");
  Pcre tplus("\\+","g");

  Pcre plus = tplus;
  Pcre lortuKat = tlortuKat;
  Pcre lortuKatAzpMTKat = tlortuKatAzpMTKat;
  Pcre lortuKatAzp = tlortuKatAzp;
 
  sar[0] = '\0';
  irt[0] = '\0';
  for (int k=0;k<m;k++) {
    string analisia = sar_ana[k];
    string sarrera,etik,trig,lema;
    int pisua = 0,pisua_luz;

    lema = lortuBim(analisia);
    strcpy(sar,lema.c_str());
    bihur_asteris_maj(sar,irt);
    kendu_marka_lex(irt,irt,0);
    lema = irt;
    if (plus.search(lema))
      lema = plus.replace(lema,"");
    sarrera = irt;
    if (sarrera.length() >= 3) {
      trig = sarrera.substr(sarrera.length()-3,string::npos);
    }
    else 
      if (sarrera.length() == 2) {
	trig = " " + sarrera.substr(sarrera.length()-2,string::npos);
      }
      else
	if (sarrera.length() == 1) {
	  trig = "  " + sarrera.substr(sarrera.length()-1,string::npos);
	}
	else trig = "   ";
    if (lortuKatAzpMTKat.search(analisia)) {
      etik = lortuKatAzpMTKat.get_match(0);
    }
    else if (lortuKatAzp.search(analisia)) {
      etik = lortuKatAzp.get_match(0);
    }
    else if (lortuKat.search(analisia)) {
      etik = lortuKat.get_match(0);
    }
    else etik = "";
    tag_trig p(etik,trig);

    if (lema.length() > 12)
      pisua_luz = 0;
    else
      pisua_luz = 12 - lema.length();

    pisua = trigramak[p]*5*100/(zenbat_etiketako[etik]+1)+pisua_luz;
    tag_pisua[etik] = max(pisua,tag_pisua[etik]);
    pisu_guztiak[k] = pisua;
    ana_tag[analisia] = etik;
//     cerr <<"tag_trig:" <<p.first << " |" << p.second<<"| "<< pisua << endl;
    

//	    $pisua_esta = ($trigramak2{"$etiketa\t$trig"}*5*100/($zenbat2{$etiketa} + 1)) + $pisua_luz;

  }

  // orain utzi bakarrik etiketa bakoitzeko pisu altuena duena
  int j = 0;
  for (int k=0;k<m;k++) {
    string analisia = sar_ana[k];
  
    if (pisu_guztiak[k] == tag_pisua[ana_tag[analisia]]) {
//       cerr << "pisua-k: " << pisu_guztiak[k] << " tag " << ana_tag[analisia] << endl;
//       cerr << analisia << endl;
      // kopiatu emaitzan
       ema_ana[j] = analisia;
       dist[j] = dist[k];
       mot[j] = mot[k];
       j++;
    }
  }
  if (j == 0) return m;
  return j;
}


string anaBihurtzailea::kenduMaj(const string & str) {
  string lag = str; 
  string ema;
  
  for (unsigned int i = 0; i <  str.size(); i++) {

    if (isupper(lag[i]) && (lag[i]!=NI_T) && (lag[i]!=NI_H)) {
      
      ema.append(1,ASTERIS);
      char c = tolower(lag[i]);
      ema.append(1,c);
      
    }
    else if (lag[i]==NI_H) {

      ema.append(1,ASTERIS);
      ema.append(1,NI_GUZTIENTZAT);

    }
    else if (lag[i]==NI_T) {

      ema.append(1,NI_GUZTIENTZAT);

    }
    else if (lag[i]==' ') {

      ema.append(1,'_');

    }
    else if (lag[i]!='\222' && lag[i] != '\'' && lag[i] != '\"') ema.append(1,lag[i]);
    
  }
  
  return ema;
  
}


string anaBihurtzailea::jarriMaj(const string & str) {
  
  string lag = str; 
  string ema;
  
  for (unsigned int i = 0; i <  str.size(); i++) {

    if (lag[i] == ASTERIS_X) {

      if (lag[i+1] == NI_GUZTIENTZAT) {
	ema.append(1,'\303');
	ema.append(1,'\221');
      }
      else {
	
	char c = toupper(lag[i+1]);
	ema.append(1,c); 

      }
      
      i++;

    }
    else if (lag[i] == NI_GUZTIENTZAT) {
	ema.append(1,'\303');
	ema.append(1,'\261');
    }
    else if (lag[i]=='_') ema.append(1,' ');
    else ema.append(1,lag[i]);
    
  }
  
  return ema;

}


string anaBihurtzailea::aldatuSarInfo(const string analisia, char bim_erab[], int SARda) {
  string analisiAldatua = analisia;
  char aldaketa[LUZMAXAN],irt[LUZMAXAN];
  string sar;
  aldaketa[0] = '\0'; 
  irt[0] = '\0';

  strcpy(irt,bim_erab);
  kendu_marka_lex(irt,irt,0);
  sar = irt;
  sar = this->jarriMaj(sar);
  strcpy(irt,sar.c_str());


  // ADI direnetan bi lekutan aldatu behar da aaaaa(tu): Sarrera eta ADOIN edo SAR eta AOI
  
  if (SARda) {
    if (aldatuAoi.search(analisiAldatua)) {
      strcpy(aldaketa,"[AOI_");
      strcat(aldaketa,irt);
      analisiAldatua = aldatuAoi.replace(analisiAldatua,aldaketa);
    }
    if (aldatuSar.search(analisiAldatua)) {
      strcpy(aldaketa,"[SAR_");
      strcat(aldaketa,irt);
      strcat(aldaketa,"]");
      analisiAldatua = aldatuSar.replace(analisiAldatua,aldaketa);
    }
  }
  else {
    if (aldatuAdoin.search(analisiAldatua)) {
      strcpy(aldaketa,"[ADOIN_");
      strcat(aldaketa,irt);
      analisiAldatua = aldatuAdoin.replace(analisiAldatua,aldaketa);
    }

    //    Pcre taldatuSarrera("\\[\\Sarrera_([Aa]+)\\]]");
    // gehitu homografo ID Momentuz 0 baina 1 beharko luke
    if (aldatuSarrera.search(analisiAldatua)) {
      strcpy(aldaketa,"[Sarrera_");
      strcat(aldaketa,irt);
      strcat(aldaketa,"--0]");
      analisiAldatua = aldatuSarrera.replace(analisiAldatua,aldaketa);
    }
  }
  return analisiAldatua;
}
string anaBihurtzailea::aldatuSarInfoPar(const string analisia, const char bim_erab[], int SARda) {
  string analisiAldatua = analisia,sarreraTmp;
  char aldaketa[LUZMAXAN],irt[LUZMAXAN];
  string sar;
  aldaketa[0] = '\0'; 
  irt[0] = '\0';

  strcpy(irt,bim_erab);
  kendu_marka_lex(irt,irt,0);
  sar = irt;
  sar = this->jarriMaj(sar);
  strcpy(irt,sar.c_str());

  // ADI direnetan bi lekutan aldatu behar da aaaaa(tu): Sarrera eta ADOIN edo SAR eta AOI
  
  if (SARda) {
    if (aldatuAoiPar.search(analisiAldatua)) {
      strcpy(aldaketa,"(AOI ");
      strcat(aldaketa,irt);
      analisiAldatua = aldatuAoiPar.replace(analisiAldatua,aldaketa);
    }
    if (aldatuSarPar.search(analisiAldatua)) {
      strcpy(aldaketa,"(SAR ");
      strcat(aldaketa,irt);
      strcat(aldaketa,")");
      analisiAldatua = aldatuSarPar.replace(analisiAldatua,aldaketa);
    }
  }
  else {
    if (aldatuAdoinPar.search(analisiAldatua)) {
      strcpy(aldaketa,"(ADOIN ");
      strcat(aldaketa,irt);
      analisiAldatua = aldatuAdoinPar.replace(analisiAldatua,aldaketa);
    }

    //    Pcre taldatuSarrera("\\(\\Sarrera [Aa]+\\)");
    // gehitu homografo ID Momentuz 0 baina 1 beharko luke
    if (aldatuSarreraPar.search(analisiAldatua)) {
      strcpy(aldaketa,"(Sarrera ");
      strcat(aldaketa,irt);
      strcat(aldaketa,"--0)");
      analisiAldatua = aldatuSarreraPar.replace(analisiAldatua,aldaketa);
    }
  }
  return analisiAldatua;
}


const string anaBihurtzailea::lortuErabLexInfo(string bimStr, string analisia) {

  // BIM+KAT+AZP eta siglen kasuan MTKAT
  string bilatzekoa;
  bilatzekoa = bimStr;

  if (kat.search(analisia)) {
    bilatzekoa += kat.get_match(0);
  }
  if (azp.search(analisia)) {
    bilatzekoa += azp.get_match(0);
  }
  if (mtkat.search(analisia)) {
    bilatzekoa += mtkat.get_match(0);
  }

  return bilatzekoa;
}
