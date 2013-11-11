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


#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <string>
//#include "clstring.h"
using namespace std;

class automata
{
 int    **transizioak;
 string *multzoak;
 int    *finalak;
 string *etiketak;
 int    *tratamenduak;
 int    estadua;
 int    LERROAK;
 int    ZUTABEAK;

 public:

         automata();              // hasieraketa funtzioak
  int    init(char *fitxategi);

  void   reset();                 // automata hasierako estaduan jartzen du

  int    mugitu(char kar); 
                                  // hurrengo trantsizioa bilatzen du emandako
                                  // karakterearen arabera. Trantsizio posiblea
                                  // den ala ez itzultzen du emaitza gisa.

  int    bukaerakoa();            // estadua bukaerakoa den esaten digu

  string etiketa();               // estaduari dagokion etiketa itzultzen du

  int    tratamendua();           // estaduari dagokion tratamendua itzuli

        ~automata();              // funtzio suntsitzailea
};

#endif // AUTOMATA_H

