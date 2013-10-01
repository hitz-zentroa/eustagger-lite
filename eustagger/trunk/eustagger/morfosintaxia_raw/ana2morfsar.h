/* ***************************************************
 * **************************************************** */
#ifndef _ANA2MORFSAR_H
#define _ANA2MORFSAR_H

#include <string>
#include <vector>
#include "morfsarFormatu.h"

#define TMP_PATH "/tmp/"

class Ana2Morfsar {
  int tamaina;
  std::string dataversion;
  MorfsarFormatu morfsarForm;

  void read_data_version();
  FILE*        fpFitxAna;
  void toMorfsar();
  void toMorfsar(const std::string segString);

public:
  Ana2Morfsar();
  Ana2Morfsar(const std::string &segp, int tam);
  ~Ana2Morfsar(); 

  void setMorfsarFitx(const std::string & morfsar);
  void setAnaFitx(const std::string & segp);
  void setAnaString(const std::string & segIrteera);
  void setAnaTam(int tamaina);
  int  getAnaTam();
  
  void add2Gorputza(std::string type, std::string value, bool symBal=false);
  void setForma(std::string forma);
  void morfemaBerria();
  void analisiaBukatu();

  void begin();
  bool ready();
  void next();
  std::string current();
  std::string current(std::string & tmpFitx);

  std::vector<std::string> execute(std::string & amaraunIzen);
};

#endif // _ANA2MORFSAR_H
