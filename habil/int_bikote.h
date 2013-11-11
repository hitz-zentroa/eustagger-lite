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


#ifndef INT_BIKOTE_H
#define INT_BIKOTE_H

#include "bikote.h"

class int_bikote
{
  struct dat_bik datua;

public:

  int_bikote();

  int_bikote(int i, int j);

  int_bikote(const int_bikote &i);

  int operator >(const int_bikote &i);

  int operator >=(const int_bikote &i);

  int operator <(const int_bikote &i);

  int operator <=(const int_bikote &i);

  int operator ==(const int_bikote &i);

  int operator !=(const int_bikote &i);

  int_bikote operator =(const int_bikote &i);

  int_bikote operator =(struct dat_bik &i);

  void print_bikote();

  int  HAT_ind();

  int  F_L();

  int  posizioa();

};

#include <list>
typedef std::list<int_bikote> indize_l;

#endif
