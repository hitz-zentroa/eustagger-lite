/* ***************************************************
 * **************************************************** */
#include "morfsar2raw.h"
#include "ana2morfsar.h"
#include "prolog2raw.h"
#include <iostream>

using namespace std;

/* ***************************************************** */
/* *** Metodo pribatuak ******************************** */
/* ***************************************************** */

void Morfsar2Raw::kargatuDatuak() {
  char* cpVarOrokorra = getenv("IXA_PREFIX");
  if (cpVarOrokorra == NULL) {
    cerr << "morfosintaxia => ERRORE LARRIA: 'IXA_PREFIX' ingurune aldagaia ezin daiteke atzitu" << endl;
    exit(EXIT_FAILURE);
  } 

  string strVarOrokorra(cpVarOrokorra);
  string strVersion= "4.4.1";

  this->prologHasieraQL = strVarOrokorra + "/var/morfosintaxia/prolog/hasiera.ql" + strVersion;
}

/* *************************************************************************************** */

#ifdef _USE_SWI_

PlTerm Morfsar2Raw::prologExecute(string & morfSarFitx) throw (string) {

  PlTerm res;
  PlTermv av0(0);
  PlCall("erregelak_hasieratu",av0);
  PlTermv av1(2);

  av1[0] = morfSarFitx.c_str();
  PlQuery q("analizatu_morf_morfeus", av1);
  if ( q.next_solution() ) {
	return av1[1];
  } else return av1[1];

}

#endif

/* ***************************************************** */
/* *** Metodo publikoak ******************************** */
/* ***************************************************** */

Morfsar2Raw::Morfsar2Raw(bool cg3form) {
  this->cg3form = cg3form;
  this->kargatuDatuak();
}

/* *************************************************************************************** */

void Morfsar2Raw::execute(string & morfsarFitx, string & morfFitx) {
//   try {
//     this->prologExecute(morfsarFitx);
//   } catch (string exMsg){
//     cerr << exMsg << endl;
//     exit(EXIT_FAILURE);
//   }

  Prolog2Raw plItzul(this->cg3form);

  try {
    plItzul.sortuAnalisiak(this->prologExecute(morfsarFitx));
    plItzul.writeMorf(morfFitx);
  } catch (string exMsg){
    cerr << exMsg << endl;
    exit(EXIT_FAILURE);
  }
}

