/* ***************************************************
 * File name     : morfsarFormatu.h
 * Version       : 2006-02-22
 * Last Revision : 
 * Author        : Aitor Sologaistoa (jibsofra@si.ehu.es) 
 * Purpose       : prologen sarrera sortzeko klase lagungarria
 * Use           : 
 *               : 
 * **************************************************** */

#ifndef _MORFSAR_FORMATU_H
#define _MORFSAR_FORMATU_H
#include <string>
#include <vector>

struct Indizeak {
  int anaInd;
  int interInd;
  int morfInd;

  Indizeak();
  Indizeak(int ana, int inter, int morf);
};


struct MorfsarSar {
  Indizeak hasInd;
  Indizeak bukInd;
  std::vector<std::string> gorputzaV;

  int bodyKont;

  MorfsarSar();
  MorfsarSar(Indizeak hasInd, Indizeak bukInd, std::vector<std::string> gorputzV);
  MorfsarSar(Indizeak buruInd, bool idDauka);
  std::string toStr();
  std::string toStr(int hasAnaInd);
};

class MorfsarFormatu {
 std::vector <std::vector <MorfsarSar> > emaitzaV;

  int multzoTam;            //emaitza jasotzerakoan itzuli beharreko analisi kopurua
  int anaPos;               //emaitza jasotzeko analisi listaren posizioa

  int analisiKont;          //mementuan tratatzen den analisiaren hasiera
  int interprKont;          //mementuan tratatzen den analisiaren interprstazio hasiera
  int morfKont;             //mementuan tratatzen den analisiaren morfema hasiera
  std::string aurrekoForma;

  MorfsarSar mSar;            //mementuan tratatzen den analisiaren informazioa

 public:
  MorfsarFormatu();

  void addMorfsarSar(std::string & mSarStr);  //osatuta dagoen  prolog sarrera txertatzen du

  void add2Gorputza(std::string type, std::string value, bool symBal=false);
  void setForma(std::string forma);
  void morfemaBerria();
  void analisiaBukatu();

  void begin(int tam);
  bool end();
  void next();
  std::string current(std::string & fitx);
};
#endif // _MORFSAR_FORMATU_H
