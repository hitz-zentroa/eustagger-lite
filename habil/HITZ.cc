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


#include <stdio.h>
#include "HITZ.h"
#include "bereiz_etq.h"
#include <string.h>
#include <string>
#include <algorithm>
#include <pcre++.h>

using namespace std;
using namespace pcrepp;

//class HITZ
//{
// string   forma;
// string   etiketa;
// int      begiratu;
// int      terminoa;
// int      segurua;

// public:
// AN_list  anali;

extern FILE *hat_kargaout;

// Eragiketak.

// *********************************************************************//
HITZ::HITZ() 
{
 terminoa = 0;
 begiratu = 1;
 segurua = 0;
 hat_lista.clear();
 anali.clear();
}

// *********************************************************************//
HITZ::HITZ(const HITZ &H)
{
 forma = H.forma;
 etiketa = H.etiketa;
 begiratu = H.begiratu;
 terminoa = H.terminoa;
 segurua = H.segurua;
 if (!analisia.empty())
   analisia.clear();
 analisia = H.analisia;
 if (!anali.empty())
   anali.clear();
 anali.assign(H.anali.begin(),H.anali.end());
 if (!hat_lista.empty())
   hat_lista.clear();
 hat_lista.assign(H.hat_lista.begin(),H.hat_lista.end());
}

// *********************************************************************//
int    HITZ::begiratu_hitza(string etq)
{
  AN_list::iterator t;
  char etqc[20];

  etqc[0]= '\0';
  strcpy(etqc,etq.c_str());
 if (strstr(etqc,"BAK") != NULL)
   return 1;
 if (anali.empty())
   return 0;
//  t = anali.begin();
//  if (!t->eman_lema().length())
//    return 0;
 if (strcmp(etqc,ERROMATARRAK) == 0)
   return 0;
 if (strcmp(etqc,BEREZIAK) == 0)
   return 0;
 if (strstr(etqc,"SIG") != NULL)
   return 0;
 if (strstr(etqc,"ZEN") != NULL)
   return 0;
 if (strcmp(etqc,"LAB_DEK") == 0)
   return 0;
 return 1;
}

// *********************************************************************//
void   HITZ::Sartu_forma(string f, string e)
{
 forma = f;
 etiketa = e;
 begiratu = begiratu_hitza(e);
 terminoa = 0;
 segurua = 0;
}
// *********************************************************************//
void   HITZ::Sartu_etiketa(string e) { etiketa = e; }
// *********************************************************************//
void   HITZ::Sartu_osagai_kopurua(int kop){ osagaiak = kop; }
// *********************************************************************//
int    HITZ::eman_osagai_kopurua(){ return osagaiak; }
// *********************************************************************//
void   HITZ::Sartu_analisi_hat(string an, int seg)
{
 analisia.push_front(an);
 segurua = seg;
 if (!terminoa) terminoa = hat_lista.size();
 if (!terminoa) terminoa = 1; // hau data eta zenbakietarako
}

// *********************************************************************//
int HITZ::eman_Id()
{
 return Id;
}

// *********************************************************************//
string HITZ::eman_forma()
{
 return forma;
}

// *********************************************************************//
string HITZ::eman_etiketa()
{
 return etiketa;
}

// *********************************************************************//
void HITZ::eman_im(string nag_im,string_lista &emaitza)
{
  AN_list::iterator hasi,amaitu,t;
  //  char sarrera[200],patroia[200];
  string im_orig = nag_im;
  string nag_im_tmp;
  string rare = " (ANB|ABT|LEX)(\\s|\\))";
  string lema_ezaugarri = "( [A-Z]+(\\+|\\-))+(\\s|$)";

  Pcre im_regex(nag_im);
  Pcre rare_regex(rare);
  Pcre lema_regex(lema_ezaugarri);

  hasi = anali.begin();
  amaitu = anali.end();
  for ( t = hasi; t != amaitu; ++t) {
    string tan = t->eman_IM();

    string tmp;
    if (im_regex.search(tan)) {
      tmp = tan;

      tmp = im_regex.replace(tmp, "");
      if (rare_regex.search(tmp)) {
	tmp = rare_regex.replace(tmp, rare_regex.get_match(1));
      }
      if (lema_regex.search(tmp)) {
	tmp = lema_regex.replace(tmp, lema_regex.get_match(lema_regex.matches()-1));
      }

      emaitza.push_back(tmp);
    }     
  }
}

// *********************************************************************//
int    HITZ::begiratu_behar_da()
{
 return begiratu;
}

// *********************************************************************//
int    HITZ::terminoa_da()
{
 return terminoa;
}


void   HITZ::inprimatu_forma(int azpimarra)
{
  if (azpimarra)
    fprintf(hat_kargaout,"_%s",forma.c_str());
  else
    fprintf(hat_kargaout,"%s",forma.c_str());
}

// *********************************************************************//
void   HITZ::inprimatu()
{
 string hat_anali;
 string_lista::iterator hasi, amaitu, t;
 AN_list::iterator ahasi, aamaitu, at;
 bool analisirik = false;

 // fprintf(hat_kargaout,"/<%s>/",forma.c_str());
 // if (etiketa.length())
 //   fprintf(hat_kargaout,"<%s>/",etiketa.c_str());
 if (forma == "." || forma == ";" || forma == ":" || forma == "!" || forma == "?") {
   string formaDolar = "$" + forma;
   fprintf(hat_kargaout,"\"<%s>\"",formaDolar.c_str());
 }
 else
   fprintf(hat_kargaout,"\"<%s>\"",forma.c_str());
 if (etiketa.length()>0)
   fprintf(hat_kargaout,"<%s>\"",etiketa.c_str());
 fprintf(hat_kargaout,"\n");
// markatu HAT batean badago
 if (terminoa) {
   hasi = analisia.begin();
   amaitu = analisia.end();
   for ( t = hasi; t != amaitu; ++t) {
     hat_anali = *t;
     analisirik = true;
     //     fprintf(hat_kargaout,"\t%s)\n",hat_anali.c_str());
     if (etiketa.length()>0)
       fprintf(hat_kargaout,"\t%s %s\n",hat_anali.c_str(),etiketa.c_str());
     else
       fprintf(hat_kargaout,"\t%s\n",hat_anali.c_str());
   }
 }
 if (!segurua) {
   ahasi = anali.begin();
   aamaitu = anali.end();
   for ( at = ahasi; at != aamaitu; ++at) {
     at->inprimatu();
     if (etiketa.length()>0) {
       fprintf(hat_kargaout," %s",etiketa.c_str());
     }
     fprintf(hat_kargaout,"\n");
     analisirik = true;
   }
 }
 if (!analisirik && etiketa.length()>0)
   fprintf(hat_kargaout,"\t%s\n",etiketa.c_str());
}

// *********************************************************************//
void HITZ::markatu(int zein_hat)
{
  int_lista::iterator amaitu;
  amaitu = hat_lista.end();
  if ( find(hat_lista.begin(),amaitu,zein_hat) == amaitu )
   {
    hat_lista.push_back(zein_hat);
    terminoa = hat_lista.size();
   }
}

// *********************************************************************//
void HITZ::ken_hat(int h)
{
  int_lista::iterator amaitu,t;
  amaitu = hat_lista.end();

  if ( ( t = find(hat_lista.begin(),amaitu,h) ) != amaitu )
   {
    hat_lista.erase(t);
    terminoa = hat_lista.size();
   }
}

// *********************************************************************//
void HITZ::destroy_hat_analisi()
{
  analisia.clear();
}

// *********************************************************************//
HITZ::~HITZ() {}

// *********************************************************************//

//};
