#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
using namespace std;

map<string,int> mhmap;
int INIT = 0;

int ireki_maiztasun_handikoak() {
  char* tmp = 0;
  char fitxIzena[200];
  FILE* MHINPUT;
  INIT = 0;
  int kopurua;
  char hitza[100];
  if ( (tmp = getenv("IXA_PREFIX")) != 0 ){
    strcpy( fitxIzena , tmp);
  } 
  else return(0);
  strcat( fitxIzena, "/var/morfologia/maiztasun_handikoak.dat" );
  if((MHINPUT=fopen(fitxIzena,"r"))==NULL)
    fprintf(stderr,"ezin izan dugu %s ireki", fitxIzena);
  while(!feof(MHINPUT)){
    fscanf(MHINPUT,"%d %s",&kopurua,hitza);
    mhmap[hitza]=kopurua;
  }
  INIT = 1;
  return(1);
}

int badago_hitza_maiztasun_handikoak(char *gakoa) {
  if (INIT) {
    return(mhmap[gakoa]);
  } 
  else {
    return(0);
  }
  return(1);
}
