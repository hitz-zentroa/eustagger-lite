#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "formatua.h"
#include "ald_orok.h"


#include "cgmanager.h"

using namespace std;

string getEnvVar(string const& key);


int prozesatuCG3Raw(int maila, int cg3form, string &oinIzen) {
  string tmpVar = getEnvVar("IXA_PREFIX");
  string tmpName;
  string gramatika;
  if (tmpVar.length()>0) {
    tmpVar += "/var/mg/";
    gramatika = tmpVar + "gramatika4.4.1.cg3.dat";
  }
  else {
    cerr << "prozesatuCG3Raw => ERRORE LARRIA: 'IXA_PREFIX' ingurune aldagaia ezin daiteke atzitu" << endl;
    exit(EXIT_FAILURE);
  }
  
  string desSarrera = oinIzen + PHAT;
  string desIrteera = oinIzen ;

  //  if (cg3forma == OUT_CG3)
  stringstream irt;
  irt << desIrteera << ".etiketatua" << maila;
  desIrteera = irt.str() ; // HAU ALDATU CG3 formatua beharrean gurea sortu behar bada
//   else desIrteera += ".irteera";
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
  cgApp.close();
  
  // Hemen lematizazioa sortu
  
      
  unlink(desSarrera.c_str());
  // if (cg3forma == OUT_LEM) ...
  //  unlink(desIrteera.c_str()); // HAU BAKARRIK .irteera-tik .lem SORTZEN DENEAN

  return EXIT_SUCCESS;
}

