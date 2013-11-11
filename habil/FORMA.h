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


#ifndef FORMA_H
#define FORMA_H

#include <list>
#include <string>
#include "int_bikote.h"

/* typedef lista<int_bikote> indize_l; */

class FORMA
{
// Aldagaiak

  std::string    Hitza;       // Forma gordetzeko.

public:

  indize_l  indizeak;    // Forma agertzen den HATen indizeak eta hitzaren posizioak.

// Eragiketak

           FORMA();
    // Hasieraketa-funtzioa.

           FORMA(const FORMA &f);
    // Kopia-hasieraketa funtzioa.

  void  Hasieraketa(std::string &H, int i, int p);
    // Hitza eta lehen indizea eta posizioa gordetzen ditu.

  int   konparatu(std::string &H);
    // H Hitza-rekin konparatzen du.
    // Emaitza : <0 --> H < Hitza
    //            0 --> H == Hitza
    //           >0 --> H > Hitza

  std::string eman_Hitza();
    // forma ematen digu

  int   operator <(FORMA &f);

  int   operator <=(FORMA &f);

  int   operator >(FORMA &f);

  int   operator >=(FORMA &f);

  int   operator ==(FORMA &f);

  int   operator !=(FORMA &f);

        ~FORMA();
    // funtzio suntsitzailea.

  FORMA operator =(const FORMA &f);
    // Asignazioa.
};

#endif
