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


#ifndef STATUS_RAW_H
#define STATUS_RAW_H

#include "token_raw.h"

class statusRaw
{
 long  offset;
 tokenRaw azkena;
public:

         statusRaw();                 // hasieraketa funtzioa
         statusRaw(statusRaw & s);       // kopia-hasieraketa
void     init(long o, tokenRaw t); // balioak hasieratzeko

void     s_offset(long o);         // offset-a asignatu
void     s_token(tokenRaw t);      // tokena asignatu
long     e_offset();               // offset-a itzultzen du
tokenRaw e_token();                // tokena itzuli


     ~statusRaw();                 // funtzio suntsitzailea

statusRaw operator =(const statusRaw & s);  // asignazioa

};
#endif // STATUS_RAW_H

