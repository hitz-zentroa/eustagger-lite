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


#ifndef HITZ_H
#define HITZ_H

#include <list>
#include <string>
#include "AN.h"

typedef std::list<AN> AN_list;
typedef std::list<int> int_lista;
typedef std::list<std::string> string_lista;

class HITZ
{
 std::string   forma;           // Sarrera
 std::string   etiketa;         // Etiketa (duenean)
 int           begiratu;        // Aldez aurretik HAT baten parte izango ez dela
                                // jakinik, ez dugu begiratuko, bestela bai.
                                // Ez begiratzeko kasuak: puntuazio-ikurrak,
                                // siglak eta zifrak (oraingoz).

 int           Id;
 int           terminoa;        // HAT baten terminoa den.
 int           osagaiak;        // HATak duen osagai kopurua.
 int           segurua;         // HAT hori segurua den.
 string_lista  analisia;        // HATari dagokion analisia.

 int  begiratu_hitza(std::string etq);

 public:
 AN_list   anali;
 int_lista hat_lista;       // Zein HATen osagai den.

// Eragiketak.

              HITZ();
              HITZ(const HITZ &H);
 void         Sartu_forma(std::string f, std::string e);
 void         Sartu_etiketa(std::string e);
 int          eman_Id();
 std::string  eman_forma();
 std::string  eman_etiketa();
 void         eman_im(std::string nag_im,string_lista &emaitza);
 int          eman_osagai_kopurua();
 int          begiratu_behar_da();
 void         Sartu_analisi_hat(std::string an, int seg);
 void         Sartu_osagai_kopurua(int kop);
 void         markatu(int zein_hat);
 int          terminoa_da();
 void         ken_hat(int h);
 void         destroy_hat_analisi();
 void         inprimatu();
 void         inprimatu_forma(int azpimarra);
 void         inprimatu_hitza();
              ~HITZ();
};

#endif
