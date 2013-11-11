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


#ifndef IM_INFO_H
#define IM_INFO_H

#include <list>
#include "int_bikote.h"
#include "IM.h"

class IM_info
{
// Aldagaiak

  IM morfo;

public:

  indize_l indizeak;

// Eragiketak

  IM_info();

  IM_info(const IM_info &i);

  IM_info(int i, int j, IM im);

  IM eman_IM();

  int bateragarria(IM im);
    // im morfologikoarekin bateragarria den.
    // Emaitza : 0 --> ez da bateragarria.
    //           1 --> bateragarria.

  IM_info operator =(const IM_info &im);

  int     operator ==(const IM_info &im);

  int     operator !=(const IM_info &im);

  int     operator <=(const IM_info &im);

  int     operator >=(const IM_info &im);

  int     operator <(const IM_info &im);

  int     operator >(const IM_info &im);

  int     indizea_dago(int_bikote b);
    // indizeen zerrendan b indizea dagoen.
    // Emaitza : 0 --> ez dago     1 --> badago.
  void    sartu_indizea(int_bikote b);

};

#endif
