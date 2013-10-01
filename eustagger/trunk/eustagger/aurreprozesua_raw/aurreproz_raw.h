#ifndef AURREPROZ_RAW_H
#define AURREPROZ_RAW_H

#include "an_lex_raw.h"
#include "file_mng_raw.h"
#include "token_raw.h"
#include "automata.h"
#include <vector>
#include <string>

using namespace std;
class aurreprozRaw
{
/*   automata aurrep_auto; */
  fileMngRaw sarrera_f;
  tokenRaw hitza;
  anLexRaw analizatu;
  string fitxategiIzena;	// tratatzen ari den fitxategiaren izena
  void tratatu_hitza();		// tratamendua egin tokenaren gainean
  void ken_gidoia();		// gidoia + CR agertzean kentzeko

public:
  
  aurreprozRaw();
  void  init(char *auto_izena, char *sarrera_izena);
  
  void  aurreprozesua(int irteera, vector<string> *emaitza); // aurreprozesuaren ziklo osoa betetzen duena
  // irteera ANALIRA baldin bada, orduan emaitza taulan itzuliko da, bestela zuzenean idatziko da
  
  //       ~aurreproz();

  string jarriMaj(const string &);
  string kenduMaj(const string &);

};

#endif // AURREPROZ_RAW_H

