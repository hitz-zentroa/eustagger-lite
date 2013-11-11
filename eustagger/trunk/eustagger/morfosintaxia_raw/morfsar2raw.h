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

#ifndef _MORFSAR2RAW_H
#define _MORFSAR2RAW_H

#ifdef _USE_SICSTUS_
#include <sicstus/sicstus.h>
#endif
#ifdef _USE_SWI_
#include "SWI-cpp.h"
#endif

#include <string>

#define PRED_NAGUSIA "analizatu_morf_morfeus"   // predikatu nagusiaren izena
#define PRED_NAGUSIA_AR 2                       // predikatu nagusiaren aritatea

class Morfsar2Raw {
  std::string prologHasieraQL;
  bool cg3form;

  void kargatuDatuak();
#ifdef _USE_SICSTUS_
  SP_term_ref prologExecute(std::string & morfSarFitx) throw (std::string);
#endif
#ifdef _USE_SWI_
  PlTerm prologExecute(std::string & morfSarFitx) throw (std::string);
#endif

  public:
  Morfsar2Raw(bool cg3form=false);
  void execute(std::string & morfsarFitx, std::string & morfFitx);
};

#endif // _MORFSAR2RAW_H
