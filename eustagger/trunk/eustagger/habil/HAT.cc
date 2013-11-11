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


#include "HAT.h"
#include "ordena.h"
#include <string.h>
#include <algorithm>

using namespace std;
//class HAT
//{
// Aldagaiak
//  string      lema;
//  IM          im;
//  int         osagai_kopurua;
//  int         nagusia;
//  int         segurtasuna;
//  erref_lista *hitz_erref;
//  int_l       *markatuak;
//  int         *murriztapenak;

//  int_l_e  detektatuak[MAX_ERREP];
//  int      detek;

// Eragiketak

// *********************************************************************//
int     HAT::murriz(int dat, int m, int emaitza[])
{
  int dat2;
  int_l::iterator hasi, amaitu, t;

  hasi = markatuak[m+1].begin();
  amaitu = markatuak[m+1].end();

  for ( t = hasi; t != amaitu; ++t )
    {
      dat2 = *t;
      if (murriztapenak_bete(dat,dat2,murriztapenak[m]))
	{
	  emaitza[m] = dat;
	  if (osagai_kopurua > (m+2))
	    if (murriz(dat2,m+1,emaitza))
	      return 1;
	    else
	      return 0;
	  else // osagai guztiak tratatuak
	    {
	      emaitza[m+1] = dat2;
	      return 1;
	    }
	}
    }
  return 0;
}

// *********************************************************************//
int      HAT::murriztapenak_bete(int e1, int e2, int m)
  // e1 eta e2 indizeen artean m murriztapena betetzen den esaten du.
  // m murriztapenak hiru balio hauek har ditzake:
  // 1.- JARR --> jarraian joan behar dute.
  // 2.- ETEN --> erdian elementuren bat egon daiteke.
  // 3.- EZOR --> jarraian edo alderantzizko ordenean joan daitezke.
  // Emaitza : 0 --> ez da m murriztapena betetzen.
  //           1 --> m murriztapena betetzen da.
{
  if (m == JARR)          // JARRAIA == bata bestearen ondoan.
    if (e2 == (e1 + 1))
      return 1;
  if (m == ETEN)          // ETENA == bigarrena lehenaren atzetik.
    // Oraingoz limiterik ez (esaldia amaiera).
    if (e2 > e1)
      return 1;
  if (m == EZOR)          // EZ ORDENATUA == atzetik ala aurretik.
    if ((e2 == (e1 + 1)) || (e2 == (e1 - 1)))
      return 1;
  return 0;
}

// *********************************************************************//

//public:

// *********************************************************************//
HAT::HAT()
{
  lema = "";
  osagai_kopurua = 0;
  nagusia = 0;
}

// *********************************************************************//
HAT::HAT(const HAT &h)
  // kopia-hasieraketa.
{
  int i;
  
  lema = h.lema;
  im = h.im;
  osagai_kopurua = h.osagai_kopurua;
  nagusia = h.nagusia;
  segurtasuna = h.segurtasuna;
  if (osagai_kopurua) {
    hitz_erref = vector<erref_list>(osagai_kopurua);
    markatuak = vector<int_l>(osagai_kopurua);
    murriztapenak = vector<int>(osagai_kopurua-1);
    nagusiaren_im = vector<string>(MAX_ERREP);
    detektatuak = vector< vector<int> >(MAX_ERREP);
    for (i=0;i<MAX_ERREP;i++)
      detektatuak[i] = vector<int>(osagai_kopurua);
    for (i=0;i<osagai_kopurua;i++)
      if (!h.hitz_erref[i].empty())
        hitz_erref[i].assign(h.hitz_erref[i].begin(),h.hitz_erref[i].end()); // lista kopiatu
    for (i=0;i<osagai_kopurua;i++)
      if (!h.markatuak[i].empty())
        markatuak[i].assign(h.markatuak[i].begin(),h.markatuak[i].end());     // lista kopiatu
    for (i=0;i<osagai_kopurua-1;i++)
      murriztapenak[i] = h.murriztapenak[i];
    for (i=0;i<MAX_ERREP;i++) {
      nagusiaren_im[i] = h.nagusiaren_im[i];
      for (int j=0;j<osagai_kopurua;j++)
        detektatuak[i][j] = h.detektatuak[i][j];
    }
  }
}  
     
// *********************************************************************//
void  HAT::Hasieraketa(string lem, IM him, int kop, int seg)
  // HATaren lema eta IMa gorde eta gainontzekoentzako memoria alokatu.
{
  int i;
  
  lema = lem;
  im = him;
  osagai_kopurua = kop;
  hitz_erref = vector<erref_list>(osagai_kopurua);
  markatuak = vector<int_l>(osagai_kopurua);
  murriztapenak = vector<int>(osagai_kopurua-1);
  nagusiaren_im = vector<string>(MAX_ERREP);
  detektatuak = vector< vector<int> >(MAX_ERREP);
  for (i=0;i<MAX_ERREP;i++)
    detektatuak[i] = vector<int>(osagai_kopurua);
  for (i=0;i<MAX_ERREP;i++) {
    nagusiaren_im[i] = "";
    for (int j=0;j<osagai_kopurua;j++)
      detektatuak[i][j] = -1;
  }
  detek = 0;
  nagusia = -1;
  segurtasuna = seg;
  //      oharra = oh;
}

// *********************************************************************//
void HAT::sartu_hitz_erref(int p, erref erreferentzia)
  // HATaren osagaiak forma edo lema diren eta dagokien taulan zein
  // posiziotan dauden gorde.
{
  hitz_erref[p].push_back(erreferentzia);
}

// *********************************************************************//
void  HAT::sartu_murriztapena(int m, int i)
  // i. eta i+1. osagaien arteko ordenari dagokion murriztapena.
{
  murriztapenak[i] = m;
}
// *********************************************************************//
void  HAT::sartu_nagusia(int i)
  // i. osagaiak emango dio IMa HATari
  // -1 balioa izango du IMrik jasotzen ez duenean.
{
  nagusia = i;
}
// *********************************************************************//
void  HAT::markatu_osagaia(int i, int j)
  // i. osagaia esaldiaren j. posizioan agertu dela markatu.
  // HAT markatuen zerrendan ez badago, sartzen du.
{
  if ( find(markatuak[i].begin(),markatuak[i].end(),j) == markatuak[i].end() )
    markatuak[i].push_back(j);
}
// *********************************************************************//
void  HAT::ken_marka_osagaia(int i, int j)
  // i. osagaitik j. posizioa ezabatu. 
{
  int_l::iterator t;
  if ( ( t = find(markatuak[i].begin(),markatuak[i].end(),j) ) != markatuak[i].end() )
    markatuak[i].erase(t);
}
// *********************************************************************//
void  HAT::ken_markak()
  // HATean dauden marka guztiak ezabatu.
{
  int i;
  
  for (i=0;i<osagai_kopurua;i++)
    markatuak[i].clear();
}
// *********************************************************************//
void HAT::ken_markak_detektatuak()
  // detektatutakoak ezabatzen ditu.
{
  int i;
  
  for (i=0;i<MAX_ERREP;i++)
    for (int j=0;j<osagai_kopurua;j++)
      detektatuak[i][j] = -1;
}
// *********************************************************************//
int  HAT::markatua()
  // HATaren osagai guztiak markatuak dauden.
  // Emaitza : 0 --> ez daude denak markatuak.
  //           1 --> denak markatuak.
{
  int i;
  
  for (i=0;i<osagai_kopurua;i++)
    if (markatuak[i].empty()) return 0;
  return 1;
}
// *********************************************************************//
int    HAT::konprobatu_murriztapenak()
  // Hitzen agerpenetan ordenari dagozkion murriztapenak betetzen diren
  // konprobatu.
  // Emaitza : 0 --> ez dira murriztapen guztiak betetzen.
  //           1 --> murriztapen guztiak betetzen dira.
  
{
  vector< vector<int> > detektatu = vector< vector<int> >(MAX_ERREP);  // tarteko emaitzetarako
  int i,j,k;
  int detmp;
  int_l::iterator amaitu0, t0, amaitu1, t1, amaitui, ti;

  for (i=0;i<MAX_ERREP;i++)
    {
      detektatu[i] = vector<int>(osagai_kopurua);
      for (j=0;j<osagai_kopurua;j++)
	detektatu[i][j] = -1;
    }
  
  // Lehenengo bien arteko konbinazio posible guztiak sortu.
  detek = 0;
  t0 = markatuak[0].begin();
  amaitu0 = markatuak[0].end();
  while ( (detek < MAX_ERREP) && ( t0 != amaitu0 ) )
    {
      int dat0 = *t0;
      
      t1 = markatuak[1].begin();
      amaitu1 = markatuak[1].end();
      while ( (detek < MAX_ERREP) && ( t1 != amaitu1 ) )
	{
	  int dat1 = *t1;
	  
	  if (murriztapenak_bete(dat0,dat1,murriztapenak[0]))
	    {
              detektatu[detek][0] = dat0;
              detektatu[detek++][1] = dat1;
	    }
          t1++;
	}
      t0++;
    }
  
  // Lehenengo bietatik aurrerako elementuen murriztapenak
  // orain arte betetzen dituztenekin konprobatu soilik.
  
  detmp = detek;
  for (i=2;i<osagai_kopurua;i++)
    {
      for (j=0;j<detmp;j++)
	{
          ti = markatuak[i].begin();
          amaitui = markatuak[i].end();
	  while ((detek < MAX_ERREP) && ((ti != amaitui)))
	    {
	      int dati = *ti;

              if (detektatu[j][i-1] == -1)
                break; // aurrekoak ez badu baliorik posibilitatea utzi.
              if (murriztapenak_bete(detektatu[j][i-1],dati,murriztapenak[i-1]))
                {
		  if (detektatu[j][i] == -1)  // lehendik ez da bete.
		    detektatu[j][i] = dati;
		  else                        // lehendik betea.
		    {
		      // gehitu beste posibilitate bat
		      detektatu[detek][i] = dati;
		      // kopiatu aurreko osagaien balioak
		      for (k=0; k<i;k++)
			detektatu[detek][k] = detektatu[j][k];
		      detek++;
		    }
                }
              ti++;
	    }
	}
      detmp = detek;
    }
  
  // Posizio guztietako murriztapenak betetzen dituztenak 'detektatuak'
  // taulan gorde.
  detmp=0;
  for (i=0;i<detek;i++)
    {
      int oso=1;
      
      for (j=0;j<osagai_kopurua;j++)
	if (detektatu[i][j] == -1)
	  oso=0;
	else
	  detektatuak[detmp][j] = detektatu[i][j];
      if (oso)
	detmp++;
    }
  detek = detmp;
  
  // alokatutako memoria askatu.
//   for (i=0;i<MAX_ERREP;i++)
//     delete detektatu[i];
  
  return detek;
}


// *********************************************************************//
int  HAT::eman_osagai_kopurua()
  // HATari IMa emango dion osagaia emango du.
{
  return osagai_kopurua;
}

// *********************************************************************//
int  HAT::eman_nagusia()
  // HATaren osagai-kopurua emango du.
{
  return nagusia;
}

// *********************************************************************//
string HAT::eman_nagusiaren_im(int p)
  // HATaren osagai-kopurua emango du.
{
  return nagusiaren_im[p];
}

// *********************************************************************//
int  HAT::eman_detektatuak(vector< vector<int> >& emaitza)
  // HATean murriztapenak betetzen dituzten hitzak itzultzen ditu.
  // Emaitza : HAT hau zenbatetan detektatu den momentuko esaldian.
{
  for (int i=0;i<detek;i++)
    for (int j=0;j<osagai_kopurua;j++)
      emaitza[i][j] = detektatuak[i][j];
  return detek;
}

// *********************************************************************//
void HAT::sartu_detektatuak(vector< vector<int> > sar, string nagusiak[MAX_ERREP])
  // HATean murriztapenak betetzen dituzten hitzak gordetzen ditu.
{
  int zenbat_on=0;
  
  for (int i=0;i<detek;i++)
    if (sar[i][0] != -1)
      {
	for (int j=0;j<osagai_kopurua;j++)
	  detektatuak[zenbat_on][j] = sar[i][j];
        nagusiaren_im[zenbat_on] = nagusiak[i];
	zenbat_on++;
      }
  detek = zenbat_on;
}
int HAT::zenbat_detektatuak()
{
  return detek;
}

// *********************************************************************//
int    HAT::forma_da(int i)
  // i. posizioko osagaia forma den ala ez.
{
  erref_list::iterator t = hitz_erref[i].begin();
  if (t->F_L() == FORM)
    return 1;
  return 0;
}

// *********************************************************************//
string HAT::eman_LEMA()
  // HATaren lema ematen du.
{
  return lema;
}

// *********************************************************************//
IM     HAT::eman_KAT_AZP()
  // HATaren informazioa ematen du.
{
  return im;
}

// *********************************************************************//
int    HAT::segurua()
  // HATa segurua den esaten du.
  // Emaitza : 0 --> ez da segurua.
  //           1 --> segurua da.
{
  return segurtasuna;
}

// *********************************************************************//
int  HAT::konparatu(string H)
  // H lema-rekin konparatzen du.
  // Emaitza : <0 --> H < lema
  //            0 --> H == lema
  //           >0 --> H > lema
{
  return lema.compare(H);
}

// *********************************************************************//
HAT::~HAT()
  // funtzio suntsitzailea
{
//   int i;
  
//   for (i=0;i<MAX_ERREP;i++)
//     delete detektatuak[i];
//   if (osagai_kopurua != 0)
//     {
//       delete hitz_erref;
//       delete markatuak;
//       delete murriztapenak;
//       delete detektatuak;
//     }
}
// *********************************************************************//
HAT   HAT::operator =(const HAT &h)
  // asignazioa
{
  int i;
  
  for (i=0;i<osagai_kopurua;i++)
    markatuak[i].clear();
  for (i=0;i<osagai_kopurua;i++)
    hitz_erref[i].clear();
  lema = h.lema;
  im = h.im;
  osagai_kopurua = h.osagai_kopurua;
  nagusia = h.nagusia;
  segurtasuna = h.segurtasuna;
  for (i=0;i<osagai_kopurua;i++)
    if (!h.hitz_erref[i].empty())
      hitz_erref[i].assign(h.hitz_erref[i].begin(),h.hitz_erref[i].end());   // lista kopiatu
  for (i=0;i<osagai_kopurua;i++)
    if (!h.markatuak[i].empty())
      markatuak[i].assign(h.markatuak[i].begin(),h.markatuak[i].end());     // lista kopiatu
  for (i=0;i<osagai_kopurua-1;i++)
    murriztapenak[i] = h.murriztapenak[i];
  for (int j=0;j<MAX_ERREP;j++)
    for (i=0;i<osagai_kopurua;i++)
      detektatuak[i][j] = h.detektatuak[i][j];
  return *this;
}
// *********************************************************************//
//};

