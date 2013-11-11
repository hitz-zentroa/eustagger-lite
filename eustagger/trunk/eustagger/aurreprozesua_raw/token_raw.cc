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


#include "token_raw.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

tokenRaw::tokenRaw() { tratamendua = 0; analizatu = true;}

tokenRaw::tokenRaw(const tokenRaw & t) {
 hitza = t.hitza;
 etiketa = t.etiketa;
 egiaztatzeko = t.egiaztatzeko;
 tratamendua = t.tratamendua;
 hasPos = t.hasPos;
 bukPos = t.bukPos;
 orig = t.orig;
 analizatu = t.analizatu;
}


void tokenRaw::init(string h, string e, string eg, int t, int has, int buk) {
 hitza = h;
 etiketa = e;
 egiaztatzeko = eg;
 tratamendua = t;
 hasPos = has;
 bukPos = buk;
 analizatu = true;
}


void tokenRaw::s_hitza(const string &h) { hitza = h; }

void tokenRaw::s_etiketa(const string &e) { etiketa = e; }

void tokenRaw::s_egiaztatzeko(const string &eg) { egiaztatzeko = eg; }

void tokenRaw::s_tratamendua(int t) { tratamendua = t; }

void tokenRaw::s_hasieraPos(int hp) { hasPos = hp; }

void tokenRaw::s_bukaeraPos(int bp) { bukPos = bp; }

void tokenRaw::s_orig(string ori) { orig = ori;  } 

void tokenRaw::s_analizatu(bool ana) { analizatu = ana; }

void tokenRaw::reset_h() { hitza = ""; }

void tokenRaw::reset_e() { egiaztatzeko = "" ;}

void tokenRaw::reset_etq() { etiketa = "" ; }



string tokenRaw::e_hitza() { return hitza;}

string tokenRaw::e_etiketa() { return etiketa; }

string tokenRaw::e_egiaztatzeko() { return egiaztatzeko; }

int tokenRaw::e_tratamendua() { return tratamendua; }

int tokenRaw::e_hasieraPos() { return hasPos; }

int tokenRaw::e_bukaeraPos() { return bukPos; }

string tokenRaw::e_orig() { return orig; } 

bool tokenRaw::e_analizatu() { return analizatu; }

tokenRaw tokenRaw::operator =(const tokenRaw & t) {
 hitza        = t.hitza;
 etiketa      = t.etiketa;
 egiaztatzeko = t.egiaztatzeko;
 tratamendua  = t.tratamendua;
 hasPos       = t.hasPos;
 bukPos       = t.bukPos;
 orig         = t.orig;
 analizatu    = t.analizatu;
 return *this;
}


void     tokenRaw::print_token(vector<string> *emaitza){
// token-a taulan inprimatu lerro bakoitza posizio batean
 string lag;

 lag = "/<";
 lag = lag + hitza;
 lag = lag + ">/";
 if (etiketa.c_str()[0] != '\0')
   {
    lag = lag + "<";
    lag = lag + etiketa;
    lag = lag + ">";
   }
 lag = lag + "/";
 emaitza->push_back(lag);

 if (egiaztatzeko.length()) /*** string-ak karaktereren bat duenean */
   {
    lag = "((forma \"";
    lag = lag + egiaztatzeko;
    lag = lag + "\")";
    emaitza->push_back(lag);
    lag = ")";
    emaitza->push_back(lag);
   }
}

string   tokenRaw::print_token()                      // token-a inprimatu
{
 static string lag;
 
 lag.erase(0,string::npos);
 lag = "/<";
 lag = lag + hitza;
 lag = lag + ">/";
 if (etiketa.c_str()[0] != '\0')
   {
    lag = lag + "<";
    lag = lag + etiketa;
    lag = lag + ">";
   }
 lag = lag + "/\n";
 if (egiaztatzeko.length()) /*** string-ak karaktereren bat duenean */
   {
    lag = lag + "((forma \"";
    lag = lag + egiaztatzeko;
    lag = lag + "\")\n)\n";
   }
 return lag;

}

void     tokenRaw::print_token_hutsa(vector<string> *emaitza) {
  // sarrera hutsa taulan inprimatu lerro bakoitza posizio batean

 emaitza->push_back(hitza);
}

string   tokenRaw::print_token_hutsa() {
 static string lag;

 lag.erase(0,string::npos);
 lag = hitza;
 lag = lag + "\n";
 return lag;
}

