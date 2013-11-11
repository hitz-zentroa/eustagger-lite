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


/*TAIPAK.H*/
#include "filtro.h"

/*typedef int estaduak;*/ /*** ALEX */
#ifndef __EXEKU__
typedef struct {int alt;
                int zab;
                int estaduak[ESTADU_MAX][MULTZO_MAX];
                bool final[ESTADU_MAX];
                int klase[ESTADU_MAX];
                }automata_lag;
#else
typedef struct {int alt;
                int zab;
                int estaduak[ESTADU_MAX][MULTZO_MAX];
                bool final[ESTADU_MAX];
                int klase[ESTADU_MAX];
                }automata;
#endif /*__EXEKU__*/
typedef char *mul1;                
                
typedef struct {
                mul1 elementuak;
               }mul2;
               

