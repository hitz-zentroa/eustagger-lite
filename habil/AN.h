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


#ifndef AN_H
#define AN_H

#include "IM.h"
#include <string>

class AN
{
 int     correct;   /*** NEREA : 97/11/28  eskuz landutakoetan C marka */
 std::string  lema;
 std::string  aldaera;
 IM      info;

 public:

// Eragiketak.

        AN();
        AN(const AN &a);
        AN(const int ona,const std::string &l,const std::string &a,const IM &im);
 std::string eman_lema();
 IM     eman_IM();
 int    operator ==(AN &a);
 int    operator >(AN &a);
 int    operator <(AN &a);
 int    operator !=(AN &a);
 AN     operator =(const AN &a);
 void   inprimatu();
        ~AN();
};

#endif
