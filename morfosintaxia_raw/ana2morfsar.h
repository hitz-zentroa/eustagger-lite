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
  void setForma(std::string forma,const std::string bereiz);
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
