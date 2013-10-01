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
