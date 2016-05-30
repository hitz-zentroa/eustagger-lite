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

#include "filtro.h"
#include "zuriune_token.h"
#include "token_raw.h"
#include <pcre++.h>
#include <iostream>

using namespace pcrepp;

iconvpp::converter zuriune_token::latin2utf = iconvpp::converter("UTF-8","ISO-8859-15");

string zuriune_token::l2u(const string & str) {
  string str_utf8;
  latin2utf.convert(str,str_utf8);
  return str_utf8;
}

zuriune_token::zuriune_token()              // hasieraketa funtzioa
{
  pos = 0;
}

void zuriune_token::init(fileMngRaw *fitx)        // hasieraketa funtzioa
{
  sarrera = fitx; 
  sarrera->reset();
  pos=0;
}

void zuriune_token::reset()    // sarrera reseteatu
{
  sarrera->reset();
  pos=0;
}

void  zuriune_token::reset(fileMngRaw *fitx)
                         // sarrera berria fitx-en eta hasieratu
{
  sarrera->close();
  sarrera->~fileMngRaw();
  sarrera = fitx;
  sarrera->reset();
  pos=0;
}

void  zuriune_token::back()     // aurreko statusera itzuli
{
  pos--;
}

void  zuriune_token::back_token(long offsetaa)  // tokenaren barruko aurreneko tokenera itzuli
{
  //Ez da onartzen. Tokenizazioa mantendua behar da derrigorrez.
  //pos--;
}

int zuriune_token::next_token()  
                         // hurrengo tokena lortzen duena
{
  string line;

  if (pos+1 < tokenak.size()) {
    // Bektoreko posizioa aurreratu
    pos++;
    return 1; 
  }
  
  if (!sarrera->eof()) {
    line = sarrera->get_line();

    boost::split(tokenak, line, boost::is_any_of("\t \n"));
    pos=0;
    return 1;
  }

  return -1;
}

tokenRaw zuriune_token::e_azkena()                // azken tokena ematen duena
{
  tokenRaw tmp;
  Pcre PUNT("\\.");
  Pcre karakBerezi("[\\.\\\"\'\\(\\)·]", "g");

  string token=tokenak.at(pos);
  string token_eg=tokenak.at(pos);
  string etik="";
  int tratamendua=0;

  /* hau borratu
  string eine_t(1,'\361');
  Pcre eine_T("ñ", "g");
  token_eg=eine_T.replace(token_eg, eine_t);

  string eine_h(1, '\321');
  Pcre eine_H("Ñ", "g");
  token_eg=eine_T.replace(token_eg, eine_h);
  */

  if (pos+1 >= tokenak.size()) {
    tmp.init("@@SENT_END", "ID", "@@SENT_END", 9, pos, 1);
    return(tmp);
  }

  if (tokenak.at(pos) == "...") {
    tmp.init("...", "PUNT_HIRU", "...", 1, pos, 1);    
    return(tmp);
  }

  if (tokenak.at(pos).substr(0,2) == "@@") {
    token = karakBerezi.replace(token, "?");
    tmp.init(l2u(token), "ID", l2u(token_eg), 9, pos, 1);
    return(tmp);
  }

  if (tokenak.at(pos) == "@") {
    tmp.init(l2u(token), "BEREIZ", token_eg, 0, pos, 1);    
    return(tmp);
  }

  Pcre BEREIZ("^[\\.\\-',\\\"\\/:;!\\?º%\\^~#&\\*\\+=\\|\\{\\}<>¿¡\\\\(\\)\\[\\]_]+$");
  if (BEREIZ.search(token)) {
    tmp.init(l2u(token), "BEREIZ", l2u(token_eg), 1, pos, 1);
    return(tmp);
  }

  Pcre karakBerezi2("[^a-záéíóúñA-ZÁÉÍÓÚÑ0-9\\.,:;\\-]", "g");
  Pcre gidoi("-$");
  token=karakBerezi2.replace(token, "");
  token=gidoi.replace(token, "");  
  token_eg=karakBerezi2.replace(token_eg, "");
  token_eg=gidoi.replace(token_eg, "");

  if (token == "") {
    tmp.init("#", "BEREIZ", "#", 1, pos, 1);
    return(tmp);    
  }

  Pcre BAK_punt("^[A-ZÁÉÍÓÚÑa-záéíóúñ]\\.$");
  if (BAK_punt.search(token)) {
    tmp.init(l2u(token), "BAK", l2u(token_eg), 5, pos, 1);
    return(tmp);
  }

  Pcre BAK("^[A-ZÁÉÍÓÚÑa-záéíóúñ]$");
  if (BAK.search(token)) {
    tmp.init(l2u(token), "BAK", l2u(token_eg), 6, pos, 1);
    return(tmp);
  }

  Pcre ZENB("^[0-9\\.\\,\\-\\:\\'\\\"]+$");
  if (ZENB.search(token)) {
    tmp.init(l2u(token), "ZENB", l2u(token_eg), 2, pos, 1);
    return(tmp);
  }

  Pcre ZENB_DEK("^[0-9\\.\\,\\-\\:\\'\\\"]+[a-záéíóúñ]+$");
  Pcre Digi("[0-9]");
  if (ZENB_DEK.search(token) && Digi.search(token)) {
    tmp.init(l2u(token), "ZENB_DEK", l2u(token_eg), 2, pos, 1);
    return(tmp);
  }

  Pcre LABDEK("^[A-ZÁÉÍÓÚÑa-záéíóúñ]+\\.(-?)[a-záéíóúñ]*$");
  if (LABDEK.search(token)) {
    tmp.init(l2u(token), "LAB_DEK", l2u(token_eg), 0, pos, 1);
    return(tmp);
  }

  Pcre HASMAI("^[A-ZÁÉÍÓÚÑ][a-záéíóúñ\\-]+$");
  if (HASMAI.search(token)) {
    tmp.init(l2u(token), "HAS_MAI", l2u(token_eg), 3, pos, 1);
    return(tmp);
  }

  Pcre DENMAI("^[A-ZÁÉÍÓÚÑ\\-]+$");
  if (DENMAI.search(token)) {
    tmp.init(l2u(token), "DEN_MAI", l2u(token_eg), 5, pos, 1);
    return(tmp);
  }

  Pcre DENMAI_DEK("^[A-ZÁÉÍÓÚÑ][A-ZÁÉÍÓÚÑ\\-]+(\\.)?[a-záéíóúñ\\-]+$");
  if (DENMAI_DEK.search(token)) {

    tratamendua = 4;
    if (PUNT.search(token)) tratamendua = 5;

    tmp.init(l2u(token), "DEN_MAI_DEK", l2u(token_eg), tratamendua, pos, 1);
    return(tmp);
  }

  Pcre SIG_MIN("^([a-záéíóúñ]\\.)+$");
  if (SIG_MIN.search(token)) {
    tmp.init(l2u(token), "SIG_MIN", l2u(token_eg), 0, pos, 1);
    return(tmp);
  }

  Pcre SIG_MAI("^([A-ZÁÉÍÓÚÑ]\\.)+$");
  if (SIG_MAI.search(token)) {
    tmp.init(l2u(token), "SIG_MAI", l2u(token_eg), 0, pos, 1);
    return(tmp);
  }

  Pcre SIG_MIN_DEK("^([a-záéíóúñ]\\.)+[a-záéíóúñ\\-]+$");
  if (SIG_MIN_DEK.search(token)) {
    tmp.init(l2u(token), "SIG_MIN_DEK", l2u(token_eg), 0, pos, 1);
    return(tmp);
  }

  Pcre SIG_MAI_DEK("^([A-ZÁÉÍÓÚÑ]\\.)+[a-záéíóúñ\\-]+$");
  if (SIG_MAI_DEK.search(token)) {
    tmp.init(l2u(token), "SIG_MAI_DEK", l2u(token_eg), 0, pos, 1);
    return(tmp);
  }

  Pcre IDENT("[^a-záéíóúñA-ZÁÉÍÓÚÑ\\'\\-]");
  if (IDENT.search(token)) {
    token = karakBerezi.replace(token, "?");

    tmp.init(l2u(token), "IDENT", l2u(token_eg), 8, pos, 1);
    return(tmp);
  }

  Pcre quote("\\'");
  if (quote.search(token)) tratamendua=7;

  tmp.init(l2u(token), etik, l2u(token_eg), tratamendua, pos, 1);
  return(tmp);
}
