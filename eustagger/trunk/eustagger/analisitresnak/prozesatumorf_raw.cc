#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#include "morfosraw.h"

using namespace std;

string getEnvVar(string const& key);

extern int hat_kargaparse(void);
extern FILE *hat_kargain;
FILE *irteera_fitx;
extern const char* PHAT;
extern const char* SEG_FITX;

char *testu_buffer;
int buffer_size;


void morfosintaxiaSortuRaw(string &oinIzen, string &segIrteera, bool haul_seguruak, bool cg3form) {
 // Definitu morfosintaxi exekutagarriaren izena ingurune aldagaien arabera
  string execPath;

  string tmpPath = getEnvVar("IXA_PREFIX");
  if (tmpPath.length()>0) {
    execPath = tmpPath + "/bin/";
  }

//   string tmpOs ;// = getEnvVar("OSTYPE"); INSTALATUTAKOAN EZ DAUKA ATZIZKIA

  execPath = execPath + "morfosintaxia_raw";
  #ifdef _USE_SWI_
  execPath = execPath + "_swi";
  #endif

  string segpIzen = oinIzen + ".segp";
  bool cg3zuz = cg3form;
  if (haul_seguruak) cg3zuz = false; // habil-ek ez du CG3 formatua jaten
  MorfosRaw morfosintaxia(execPath, oinIzen, 100, false,cg3zuz); // 1 beharrean 100 beharko luke
  morfosintaxia.sortuAnalisiak(segIrteera);


  if (haul_seguruak) {
    //HEMEN HABIL ERABILI ETA EMAITZA IDATZI
    FILE *jat_fitx;
    std::string tmp;
    
    setlocale(LC_ALL,"es");

    tmp = tmpPath + "/var/habil/";
    //tmp = "/sc01a4/users/jipecran/svn_lana/Eustagger/var/habil/";
    tmp += SEG_FITX;

    if ((jat_fitx = fopen(tmp.c_str(),"r")) == NULL) {
      fprintf(stderr,"Errorea %s fitxategia irekitzean\n",tmp.c_str());
      exit(EXIT_FAILURE);
    }

    string irtMorfos = morfosintaxia.getResult(); // Hemen emaitza string batean jaso

    int length = irtMorfos.length();
    testu_buffer = (char *) malloc(length+2);
    testu_buffer[0] = '\0';
    strcpy(testu_buffer,irtMorfos.c_str());
    testu_buffer[length+1] = '\0';
    buffer_size = length +2;

    string irteeraIzen = oinIzen + PHAT; 
    if ((irteera_fitx = fopen(irteeraIzen.c_str(),"w")) == NULL) {
      fprintf(stderr,"Errorea %s fitxategia irekitzean\n",irteeraIzen.c_str());
      exit(EXIT_FAILURE);
    }
    hat_kargain = jat_fitx;
    hat_kargaparse();
  }
  else {
    morfosintaxia.writeResult(); 
  }

}

