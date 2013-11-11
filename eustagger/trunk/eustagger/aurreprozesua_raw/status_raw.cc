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


#include "status_raw.h"
#include "token_raw.h"

// long offset;
// tokenRaw azkena;

     statusRaw::statusRaw()                    // hasieraketa funtzioa
{
 offset = 0;
}

void statusRaw::init(long o, tokenRaw t)     // balioak hasieratzeko
{
 offset = o;
 azkena = t;
}

     statusRaw::statusRaw(statusRaw & s)          // kopia-hasieraketa
{
 offset = s.offset;
 azkena = s.azkena;
}

void statusRaw::s_offset(long o)
{
 offset = o;
}

void statusRaw::s_token(tokenRaw t)
{
 azkena = t;
}

long statusRaw::e_offset()
{
 return(offset);
}

tokenRaw statusRaw::e_token()
{
 return(azkena);
}

    statusRaw::~statusRaw()                  // funtzio suntsitzailea
{
  // azkena.~token();
}


statusRaw statusRaw::operator =(const statusRaw & s)  // asignazioa
{
 offset = s.offset;
 azkena = s.azkena;

 return *this;
}


