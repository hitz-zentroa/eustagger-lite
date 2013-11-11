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


#include "AN.h"
#include <stdio.h>

extern FILE *hat_kargaout;
using namespace std;

//class AN
//{
// int     correct;
// string  lema;
// string  aldaera;
// IM      info;

// public:

// Eragiketak.

// *********************************************************************//
AN::AN() {}

// *********************************************************************//
AN::AN(const AN &a)
{
 correct = a.correct;
 lema = a.lema;
 aldaera = a.aldaera;
 info = a.info;
}

// *********************************************************************//
AN::AN(const int ona,const string &l,const string &a,const IM &im)
{
 correct = ona;
 lema = l;
 aldaera = a;
 info = im;
}

// *********************************************************************//
string AN::eman_lema()
{
 return lema;
}

// *********************************************************************//
IM     AN::eman_IM()
{
 return info;
}

// *********************************************************************//
string sortu_cg3rako_etiketak(string info);
string sortu_cg3rako_lema_info(string lema, string info, bool ezezag);
string sortu_cg3rako_lema(string lema);

void   AN::inprimatu()
{
 string hutsa("*******");
 if (correct)
   fprintf(hat_kargaout,"C");
 // fprintf(hat_kargaout,"\t(\"%s\"  ",lema.c_str());

 // Hemen bihurtu info CG3ra (kalkulatu etiketak eta inprimatu)
 string cg3formatua = sortu_cg3rako_etiketak(info);

 if (lema.length() > 0) {
   cg3formatua = sortu_cg3rako_lema_info(lema,cg3formatua,lema.length()==0);
   lema = sortu_cg3rako_lema(lema);

   fprintf(hat_kargaout,"\t\"%s\"  ",lema.c_str());
 }
 else
   fprintf(hat_kargaout,"\t");
 if (aldaera != hutsa) {
   cg3formatua = sortu_cg3rako_lema_info(aldaera,cg3formatua,lema.length()==0);
   aldaera = sortu_cg3rako_lema(aldaera);
   fprintf(hat_kargaout,"\"%s\" ",aldaera.c_str());
 }
 if (lema.length() == 0)
   fprintf(hat_kargaout,"EZEZAG ");
 // fprintf(hat_kargaout,"%s)\n",info.c_str());

 fprintf(hat_kargaout," %s", cg3formatua.c_str());
 // fprintf(hat_kargaout,"%s",info.c_str());

}

// *********************************************************************//
int    AN::operator ==(AN &a)
{
 return ((lema == a.lema) && (aldaera == a.aldaera) && (info == a.info));
}

// *********************************************************************//
int    AN::operator <(AN &a)
{
 return ((lema < a.lema) && (info < a.info));
}

// *********************************************************************//
int    AN::operator >(AN &a)
{
 return ((lema > a.lema) && (info > a.info));
}

// *********************************************************************//
int    AN::operator !=(AN &a)
{
 return ((lema != a.lema) || (aldaera != a.aldaera) || (info != a.info));
}

// *********************************************************************//
AN::~AN() {}

// *********************************************************************//
AN    AN::operator =(const AN &a)
{
 correct = a.correct;
 lema = a.lema;
 aldaera = a.aldaera;
 info = a.info;
 return *this;
}

// *********************************************************************//
//};
