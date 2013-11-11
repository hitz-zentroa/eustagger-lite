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

