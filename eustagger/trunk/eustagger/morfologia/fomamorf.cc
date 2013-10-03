#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "fomamorf.h"


using namespace std;

fomaMorf::fomaMorf() {

}

int fomaMorf::hasieratu_transd(const string fitx_iz, int n_lex) {
  if (n_lex >= MAX_LEXIK) {
//     cerr << "Errorea lexikoi kopuruan. Max = " << MAX_LEXIK << " emandakoa " << n_lex <<endl;
//     exit(EXIT_FAILURE);
    return(0);
  }

  string tmpPath = getEnvVar("IXA_PREFIX");
  if (tmpPath.length()>0) {
    tmpPath = tmpPath + "/var/morfologia/" +fitx_iz;
  }
  else
    tmpPath = fitx_iz;

  char *izena=strdup(tmpPath.c_str());
  if ((lexikoiak[n_lex-1] = fsm_read_binary_file(izena)) == NULL) {
    //  cerr << "Errorea lexikoia irekitzean " << tmpPath <<endl;
    //exit(EXIT_FAILURE);
    return(0);
  }
  lexHandle[n_lex-1] = apply_init(lexikoiak[n_lex-1]);
  free(izena);
  return(1);
}


int fomaMorf::amaitu_transd(int n_lex) {
  if (lexikoiak[n_lex-1] != NULL && lexHandle[n_lex-1] != NULL) {
    apply_clear(lexHandle[n_lex-1]);
    fsm_destroy(lexikoiak[n_lex-1]);
  }
  return(1);
}


int fomaMorf::amaitu_transd_guztiak() {
  for(int i=1; i<=MAX_LEXIK; i++)
    this->amaitu_transd(i);
  return(1);
}

int fomaMorf::analizatu(int n_lex, string hitza, vector<string> &emaitza) {
  string result;
  char *hitzaCstr =  strdup(hitza.c_str());
  char *tmp;
  tmp = apply_up(lexHandle[n_lex-1], hitzaCstr);

  while (tmp != NULL) {
    result = tmp;
    emaitza.push_back(result);
    tmp = apply_up(lexHandle[n_lex-1], NULL);
  }
  free(hitzaCstr);
  return emaitza.size();
}

int fomaMorf::analizatu_hitza (int n_lex, char * hitza, char anal[][LUZMAXAN]) {
	vector<string> ema;
	int res = this->analizatu (n_lex, std::string(hitza), ema);
	for(size_t i = 0; i < ema.size(); ++i) strcpy(anal[i], ema[i].c_str());
	return res;
}


int fomaMorf::sortu(int n_lex, string hitza,  vector<string> &emaitza) {
  string result;
  char *hitzaCstr =  strdup(hitza.c_str());
  char *tmp;
  tmp = apply_down(lexHandle[n_lex-1], hitzaCstr);

  while (tmp != NULL) {
    result = tmp;
    emaitza.push_back(result);
    tmp = apply_down(lexHandle[n_lex-1], NULL);
  }
  free(hitzaCstr);
  return emaitza.size();
}

int fomaMorf::sortu_dena(int n_lex, string hitza,  vector<string> &emaitza) {
  string result;
  char *hitzaCstr =  strdup(hitza.c_str());
  char *tmp;
  tmp = apply_down(lexHandle[n_lex-1], hitzaCstr);

  while (tmp != NULL) {
    result = tmp;
    emaitza.push_back(result);
    tmp = apply_down(lexHandle[n_lex-1], NULL);
  }
  free(hitzaCstr);
  return emaitza.size();
}

int fomaMorf::ireki_erab_lex (const std::string izena, int sortu, int info_morfo) {
/*
1.- LEKU_IZENA
2.- PERTSONA_IZENA
3.- IZENA
4.- ADJETIBOA
5.- ADITZA
6.- SIGLAKK 
7.- BESTEA
*/
  string tmpPath = getEnvVar("MORFOLOGIA_HOME");
  if (tmpPath.length()>0) {
    tmpPath = tmpPath + "anali/" + izena;
  }
  else
    tmpPath = izena;
    
  	FILE * pFile;
		pFile = fopen (tmpPath.c_str(),"r");
		char mystring [1024];
		string strOsoa;
		if (pFile == NULL) {
			return 0;
		}
		while (fgets (mystring , 1024 , pFile) != NULL) {
//		strOsoa = (char *)malloc(sizeof(char)*1024);
			strOsoa = strOsoa + mystring;
		}
		fclose (pFile);
		istringstream iss(strOsoa);
		string token;
		
		int hitzKop=0;
		while(getline(iss, token, '\n'))
{
//			printf ("%s string-a sartuta!\n", token.c_str());
			lexGabe.insert(sStrStrPair(token, token));
			hitzKop++;
}

/*
		sStrIntMap::iterator iter;
		for (iter = lexGabe.begin(); iter != lexGabe.end(); iter++) {
			printf ("Hitza: %s\n", iter->first.c_str());
		}
*/

    
	return hitzKop;
}

sStrStrMap::iterator fomaMorf::bilatu_erab_guztiak (char *sar) {
	return lexGabe.find(string(sar));
}


sStrStrMap::iterator fomaMorf::azkena () {
	return lexGabe.end();
}

fomaMorf::~fomaMorf() {
  // kaskatzen du amaitzean 
  //*** glibc detected *** ./anali_linux_bridge: munmap_chunk(): invalid pointer: 0x0064ca15 ***

  //  this->amaitu_transd_guztiak();
}
