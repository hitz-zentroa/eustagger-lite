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


#ifndef LEMA_H
#define LEMA_H

#include "IM.h"
#include "IM_info.h"
//#include "list_rev.h"
#include <string>
#include <stdio.h>

typedef std::list<IM_info> IM_list;

class LEMA
{
// Aldagaiak

  std::string    Hitza;        // Lema gordetzeko.
  IM_list   im_zerrenda;  // Lemari dogozkion IMak gordetzeko.
                          // Lema agertzen den HATen indizeak eta 
                          // hitzaren posizioak ere gordetzen ditu.
//  std::string    sarrera;      // Lemari dagokion sarrera. Kasu honetan ez da
                          // beharrezkoa baina sinplifikazioa egiteko
                          // behar dugu.
public:

  indize_l     indizeak;  // im_zerrendan agertzen diren indizeak gordetzeko

// Eragiketak

            LEMA();
    // Hasieraketa-funtzioa.

            LEMA(const LEMA &l);
    // Kopia-hasieraketa funtzioa.

  void      Hasieraketa(std::string H, int i, int p, IM im);
    // Hitza eta lehen informazio morfologikoa gordetzen ditu.
    // (i,j) bikotea indizeak zerrendan erantsi.

  std::string    eman_Hitza();

//  void      sartu_sarrera(std::string s);

  void      erantsi_im(int i, int j, IM im);
    // i. HATaren j. osagai gisa sartu dagokion im-arekin.
    // (i,j) bikotea indizeak zerrendan erantsi.

  IM        eman_IM(int h, int p);
    // h HATaren p. osagaiari dagokion IM-a eman.

  int        konparatu(std::string H);
    // H Hitza-rekin konparatzen du.
    // Emaitza : <0 --> H < Hitza
    //            0 --> H == Hitza
    //           >0 --> H > Hitza

  int   operator <(LEMA &l);

  int   operator <=(LEMA &l);

  int   operator >(LEMA &l);

  int   operator >=(LEMA &l);

  int   operator ==(LEMA &l);

  int   operator !=(LEMA &l);

  int       IM_bateragarria(int h, int p, IM i, IM *emaitza);
    // i informazioa h HATean p posizioan dagoen lemarenarekin bateragarria den.
    // Emaitza : 0 --> ez da bateragarria.
    //           1 --> bateragarria da.
    // emaitza aldagaian LEMAren IMa itzuliko da.

            ~LEMA();
    // funtzio suntsitzailea.

  LEMA      operator =(const LEMA &l);

  void      inprimatu(FILE *Lemak);
};

#endif

