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

#ifndef ZURI_TOKEN_H
#define ZURI_TOKEN_H

#include "file_mng_raw.h"
#include "token_raw.h"
#include "tokenizatzaile.h"
#include "iconv.hpp"
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

class zuriune_token : public tokenizatzaile
{

  fileMngRaw *sarrera; // sarrera (fitxategia)
  bool sarreraStandar;
  vector<string> tokenak;
  vector<unsigned int> vposhas;
  vector<unsigned int> vposbuk;
  int pos;
  static iconvpp::converter latin2utf;

  int linenum;
  int poffset;  

  string l2u(const string & str);

public:

 zuriune_token();               // hasieraketa funtzioa
 void init(fileMngRaw *fitx);   // hasieraketa funtzioa

 void  reset();       // sarrera reseteatu
 void  reset(fileMngRaw *fitx);
                      // sarrera berria fitx-en eta hasieratu
 void back();
 void back_token(long offsetaa);// tokenaren barruko aurreneko tokenera itzuli

 int next_token();              // hurrengo tokena lortzen duena
 tokenRaw e_azkena();           // azken tokena ematen duena

//       ~zuri_token();     // suntsitzailea

};

#endif // ZURI_TOKEN_H

