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


#include "LEMA.h"
#include <string.h>
#include <algorithm>

using namespace std;

//class LEMA
//{
// Aldagaiak

//  string    Hitza;        // Lema gordetzeko.
//  IM_list   im_zerrenda;  // Lemari dogozkion IMak gordetzeko.
                          // Lema agertzen den HATen indizeak eta 
                          // hitzaren posizioak ere gordetzen ditu.
//  string    sarrera;
//public:

//  indize_l     indizeak;  // im_zerrendan agertzen diren indizeak gordetzeko

// Eragiketak


// *********************************************************************//
LEMA::LEMA()
    // Hasieraketa-funtzioa.
{
  Hitza = "";
  //      sarrera = "";
}

// *********************************************************************//
LEMA::LEMA(const LEMA &l)
  // Kopia-hasieraketa funtzioa.
{
  Hitza = l.Hitza;
  //      sarrera = l.sarrera;

  IM_list::const_iterator imhasi, imamaitu, imt;
  IM_info imbal;

  if (!indizeak.empty())
    indizeak.clear();
  indizeak.assign(l.indizeak.begin(),l.indizeak.end());

  if (!im_zerrenda.empty())
    im_zerrenda.clear();
  im_zerrenda.assign(l.im_zerrenda.begin(),l.im_zerrenda.end());

}

// *********************************************************************//
void      LEMA::Hasieraketa(string H, int i, int p, IM im)
  // Hitza eta lehen informazio morfologikoa gordetzen ditu.
  // (i,p) bikotea indizeak zerrendan erantsi.
{
  int_bikote bi(i,p);
  IM_info tmp(i,p,im);
  
  Hitza = H;
  indizeak.push_back(bi);
  im_zerrenda.push_front(tmp);
}

// *********************************************************************//
string    LEMA::eman_Hitza()
{
  return Hitza;
}

// *********************************************************************//
//  void      LEMA::sartu_sarrera(string s)
//    {
//       sarrera = s;
//    }

// *********************************************************************//
void      LEMA::erantsi_im(int i, int j, IM im)
  // i. HATaren j. osagai gisa sartu dagokion im-arekin.
  // (i,j) bikotea indizeak zerrendan erantsi.
{
  int_bikote bi(i,j);
  indize_l::iterator hasi, amaitu;
  IM_info tmp(i,j,im),imbal;
  IM_list::iterator badago, imamaitu;
  int topatua = 0;
  IM imb;

  hasi = indizeak.begin();
  amaitu = indizeak.end();
  if ( find(hasi,amaitu,bi) == amaitu)
    indizeak.push_back(bi);
  badago = im_zerrenda.begin();
  imamaitu = im_zerrenda.end();

  while (!topatua && badago != imamaitu) {
//     imbal = *badago;
    imb = badago->eman_IM();
    if (imb == im) {
      badago->sartu_indizea(bi);
      topatua = 1;
    }
    badago++;
  }
  if (!topatua) {
    im_zerrenda.push_front(tmp);
  }

//   if ( ( badago = find(imhasi,imamaitu,tmp)) == imamaitu)
//     im_zerrenda.push_front(tmp);
//   else
//     {
//       imbal = *badago;
//       if (imbal.eman_IM() == im) {
//         imbal.sartu_indizea(bi);
//       }
//     }
}

// *********************************************************************//
IM         LEMA::eman_IM(int h, int p)
{
  int_bikote bi(h,p);
  IM hutsa;
  IM_list::iterator amaitu, t;

  t = im_zerrenda.begin();
  amaitu = im_zerrenda.end();
  while (t != amaitu) {
    if ( t->indizea_dago(bi) ) 
      hutsa = t->eman_IM();
    t++;
  }

  return hutsa;
}
// *********************************************************************//
//extern int pattern_match( string, string );
int      LEMA::konparatu(string H)
  // H Hitza-rekin konparatzen du.
  // Emaitza : <0 --> H < Hitza
  //            0 --> H == Hitza
  //           >0 --> H > Hitza
{
//   if (H == Hitza)
//     return 0;
// //   if (pattern_match(H,Hitza) ||
// //       pattern_match(Hitza,H))
// //     return 0;
//   if (H < Hitza)
//     return -1;
//   return 1;
  return strcmp(Hitza.c_str(),H.c_str());
  //  return (Hitza == H);
}

// *********************************************************************//
int     LEMA::operator <(LEMA &f)
{
  return (Hitza < f.Hitza);
}

// *********************************************************************//
int   LEMA::operator <=(LEMA &f)
{
  return (Hitza <= f.Hitza);
}

// *********************************************************************//
int   LEMA::operator >(LEMA &f)
{
  return (Hitza > f.Hitza);
}

// *********************************************************************//
int   LEMA::operator >=(LEMA &f)
{
  return (Hitza >= f.Hitza);
}

// *********************************************************************//
int   LEMA::operator ==(LEMA &f)
{
  return (Hitza == f.Hitza);
}

// *********************************************************************//
int   LEMA::operator !=(LEMA &f)
{
  return (Hitza != f.Hitza);
}

// *********************************************************************//
int       LEMA::IM_bateragarria(int h, int p, IM i, IM *emaitza)
  // i informazioa h HATean p posizioan dagoen lemarenarekin bateragarria den.
  // Emaitza : 0 --> ez da bateragarria.
  //           1 --> bateragarria da.
{
  int_bikote bi(h,p);
  IM_list::iterator amaitu, t;
  IM_info tmp;

  t = im_zerrenda.begin();
  amaitu = im_zerrenda.end();

  while (t != amaitu)
    {
//       tmp = *t;
      int i_b = t->bateragarria(i);
      int ind_b = t->indizea_dago(bi);
      if ( i_b && ind_b )
	{
          *emaitza = t->eman_IM();
	  //                IM info = tmp.eman_IM();
	  return 1;
	}
      t++;
    }
  *emaitza = "";
  return 0;
}

// *********************************************************************//
LEMA::~LEMA()
  // funtzio suntsitzailea.
{
}

// *********************************************************************//
LEMA      LEMA::operator =(const LEMA &l) 
{
  Hitza = l.Hitza;
  //      sarrera = l.sarrera;

  if (!indizeak.empty())
    indizeak.clear();
  indizeak.assign(l.indizeak.begin(),l.indizeak.end());

  if (!im_zerrenda.empty())
    im_zerrenda.clear();
  im_zerrenda.assign(l.im_zerrenda.begin(),l.im_zerrenda.end());

  return *this;
}

// *********************************************************************//
void LEMA::inprimatu(FILE *Lemak)
{
  IM_list::iterator imamaitu, imt;

  imt = im_zerrenda.begin();
  imamaitu = im_zerrenda.end();

  fprintf(Lemak,"%s\n",Hitza.c_str());
  while (imt != imamaitu)
    {
      indize_l ind;
      indize_l::iterator amaitu, t;
      fprintf(Lemak,"\t(%s) ",imt->eman_IM().c_str());
      ind = imt->indizeak;
      t = ind.begin();
      amaitu = ind.end();

      while (t != amaitu)
        {
	  int h = t->HAT_ind();
	  int p = t->posizioa();
	  fprintf(Lemak,"(%d,%d) ",h,p);
          t++;
        }
      fprintf(Lemak,"\n");
      imt++;
    }
}

// *********************************************************************//
//};

//#endif LEMA_H

