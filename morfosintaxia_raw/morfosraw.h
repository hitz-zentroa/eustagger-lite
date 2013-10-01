#ifndef _MORFOSRAW_H
#define _MORFOSRAW_H

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "ana2morfsar.h"

class MorfosRaw {
  std::string execpr;
  std::string amaraunIzen;
  int tamaina;
  bool debug;
  bool cg3form;
  Ana2Morfsar ana2Morfsar;
  std::stringstream morfDocStream;

  //DEBUG ALDAGAIAK
  time_t beginT, currentT;
  double morfsarT, fsT, lnkT,wrT;

  std::map<int, std::string> kont2tmpAmaraun;
  time_t fsTmpT, addTmpT, waitTmpT;
  std::map<int,double> kont2fsT;
  std::map<int,double> kont2addT;
  std::map<int,double> kont2waitT;

  void debugControl(int type, int kont, std::string tmpFitx);
  void printErr(std::string type, std::string cmd, int exit);
  std::string sortuTmpFitx(int kont);
  void txertatuMorfDoc(std::string & tmpAmaraun, int kont);
  std::string waitMorfsar2Raw(std::string & currentFitx, std::string & prCmd, int kont);
  
 public:
  MorfosRaw(const std::string & argv0, std::string & amaraunIzen, int tam, bool debug, bool cg3form=false);
  void sortuAnalisiak(std::string segpIzena);
  void writeResult();

  void setTamaina(int tamaina);
  int getTamaina();

  void setDebug(bool debug);
  bool getDebug();

  std::string getResult();
};

#endif // _MORFOSRAW_H	
