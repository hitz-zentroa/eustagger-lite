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


#include "HAT_class.h"
#include <math.h>
#include <algorithm>

using namespace std;
// *********************************************************************//
void HAT_class::bilatu_HAT_Esaldi()
{
 int i;
 HAT_mark HAT_lista;
 AN_list::iterator anhasi, anamaitu, ant;
// Aurreko esaldiko HAT markatuak ezabatu.
 hustu_HAT_markatua();

// Lehenik, esaldiko hitzak terminoak izan badaitezke, markatu.

 for (i=0;i<hitz_indizea;i++)
   {
    int k;

    if (Esaldi[i].begiratu_behar_da())
      {
        int_lista findizeak;
        int_lista::iterator fhasi, famaitu, fin;
        findizeak = bilatu_FORMA(Esaldi[i].eman_forma());
        if (findizeak.size()) {
          fhasi = findizeak.begin();
          famaitu = findizeak.end();
          for ( fin = fhasi; fin != famaitu; ++fin)
            markatu_FORMA(*fin,i);
        }
        anhasi = Esaldi[i].anali.begin();
        anamaitu = Esaldi[i].anali.end();
        for ( ant = anhasi; ant != anamaitu; ++ant )
          if ((k=bilatu_LEMA(ant->eman_lema()))>0)
            markatu_LEMA(k,i);
      }
   }

// Ondoren, osagai guztiak markatuak dituzten HATak HAT markatuen zerrendan
// sartu baldin eta esaldian detektatutako hitzek ordenari buruzko
// murriztapenak betetzen badituzte. Bestela HATaren markak ezabatu.

 for (i=0;i<zein_HAT();i++)
   if (markatua_HAT(i))
     if (konprobatu_murriztapenak_HAT(i))
       erantsi_HAT_markatua(i);
     else
       ken_markak_HAT(i);
   else
     ken_markak_HAT(i);

// Markatutako HATetarako konprobatu informazio morfologikoa bateragarria
// den. Hala bada, esaldian gorde HATari dagokion analisia.

 // ordenatu HAT__mark

 HAT__mark.sort();

 HAT_mark::iterator hasi, amaitu, t;
 hasi = HAT__mark.begin();
 amaitu = HAT__mark.end();
 for ( t = hasi; t != amaitu; ++t)
   {
     int h = *t;
     int kop = HAT_taula[h].eman_osagai_kopurua();
     int onak[MAX_ERREP];
     string nagusiak[MAX_ERREP];
     string lema_im;
     int zenb;
     int bateragarria=0;
     int nagusia_da = -1;
     int zenbat=0;
     vector< vector<int> > det;
     
     det = vector< vector<int> >(MAX_ERREP);
     for (i=0;i<MAX_ERREP;i++) {
       det[i] = vector<int>(kop);
       nagusiak[i] = "";
     }

     zenb = HAT_taula[h].eman_detektatuak(det);
     nagusia_da = HAT_taula[h].eman_nagusia();
     
     for (i=0;i<zenb;i++)
       {
      for (int j=0;j<kop;j++)
        {
          if (HAT_taula[h].forma_da(j))
            bateragarria = 1;
          else
            {
             int k = det[i][j];

             anhasi = Esaldi[k].anali.begin();
             anamaitu = Esaldi[k].anali.end();

             for ( ant = anhasi; ant != anamaitu; ++ant )
               {
                IM info(ant->eman_IM());
                string lem(ant->eman_lema());
                int l=bilatu_LEMA(lem);

                if (l != 0)
                  {
                   bateragarria = LEMA_taula[l-1].IM_bateragarria(h,j,info,&lema_im);
                   if (bateragarria) {
                     if (j == nagusia_da) {
                       nagusiak[i] = lema_im;
                     }
                     break;
                   }
	          }
	       }
             if (!bateragarria) 
               continue;
	   }
        }
// Denak bateragarriak badira, esaldian erantsi analisia.
       if (bateragarria)
         onak[i] = 1;
       else
         onak[i] = 0;
       bateragarria = 0;
      }

// HAT bakoitzeko detektatu direnen artean interferentziarik badago,
// distantzia txikiena duena hobestuko dugu.

    for (int z=0;z<zenb;z++)
      if (onak[z])
        zenbat++;
      else
        det[z][0] = -1;
    if (zenbat > 1)
      {
       int zein = 0;
       while (!onak[zein]) zein++;
       while (zein < zenb-1)
         {
          for (int x=zein+1;x<zenb;x++)
            if (onak[x])
              {
               int berdinik=0;
               for (int y=0;y<kop;y++)
                 if (det[zein][y] == det[x][y])
                   berdinik = 1;
               if (berdinik)
                 {
                  int osag = 0;

                  while (onak[zein] && onak[x] && (osag < kop-1))
                    {
                     int dif_zein, dif_x,ord_zein = 0,ord_x=0;
                     if (det[zein][osag] > det[zein][osag+1])
                       {
                        dif_zein = det[zein][osag] - det[zein][osag+1];
                        ord_zein = 0;
		       }
                     else
                       {
                        dif_zein = det[zein][osag+1] - det[zein][osag];
                        ord_zein = 1;
		       }
                     if (det[x][osag] > det[x][osag+1])
                       {
                        dif_x = det[x][osag] - det[x][osag+1];
                        ord_x = 0;
		       }
                     else
                       {
                        dif_x = det[x][osag+1] - det[x][osag];
                        ord_x = 1;
		       }
		     // diferentzia txikiena duena aukeratuko dugu.
                     if (dif_zein < dif_x)
                       onak[x] = 0;
                     if (dif_zein > dif_x)
                       {
                        onak[zein] = 0;
                        zein = x;
                        break;
                       }
		     // Diferentzia bera badute, ordenaturik dagoena.
                     if (dif_zein == dif_x)
                       {
                        if (ord_zein < ord_x)
                          {
                           onak[zein] = 0;
                           zein = x;
                           break;
			  }
                        else
                          onak[x] = 0;
		       }
                     osag++;
		    }
		 }
              }
          zein++;
          while (!onak[zein] && (zein < zenb-1)) zein++;
	 }
       // HATaren detektatuetan gorde onak.
       for (int o=0;o<zenb;o++)
         if (!onak[o])
           det[o][0] = -1;      // lehenengo posizioan -1 ipini
       HAT_taula[h].sartu_detektatuak(det,nagusiak);
      }
    else
      HAT_taula[h].sartu_detektatuak(det,nagusiak);

    zenb = HAT_taula[h].eman_detektatuak(det);
    for (int p=0;p<zenb;p++)
      if (det[p][0] != -1)
        for (int o=0;o<kop;o++)
          Esaldi[det[p][o]].markatu(h);
    ken_markak_HAT(h);
//     for (i=0;i<MAX_ERREP;i++)
//       delete det[i];
//     delete det;  
    if (zenb) {
      HAT_mark::iterator amaitu = HAT_lista.end();
      if (find(HAT_lista.begin(),amaitu,h) == amaitu)
        HAT_lista.push_back(h);
    }
   }

// Eguneratu HAT markatuen zerrenda (HAT_lista-n daudenekin)
 hustu_HAT_markatua();

 hasi = HAT_lista.begin();
 amaitu = HAT_lista.end();
 for ( t = hasi; t != amaitu; ++t)
   {
     int h = *t;
     erantsi_HAT_markatua(h);
   }

// Detektatutako HATen arteko ebakidura ez hutsa bada, sinplifikatu.

 sinplifikatu_HAT_markatuak();

// Onak diren HATen osagaietan analisia gehitu.

 hasi = HAT__mark.begin();
 amaitu = HAT__mark.end();
 for ( t = hasi; t != amaitu; ++t)
   {
     string hat_analisi, hat_kat_azp;
     int h = *t;
     int kop = HAT_taula[h].eman_osagai_kopurua();
     int nag = HAT_taula[h].eman_nagusia();
     int zenb;
     vector< vector<int> > det;
     
     det = vector< vector<int> >(MAX_ERREP);
     for (i=0;i<MAX_ERREP;i++)
       det[i] = vector<int>(kop);
     
     zenb = HAT_taula[h].eman_detektatuak(det);
     hat_analisi = "\"";
     hat_analisi += HAT_taula[h].eman_LEMA();
     hat_analisi += "\"  ";
     hat_kat_azp = HAT_taula[h].eman_KAT_AZP();
     hat_analisi += hat_kat_azp;
     
     if (Esaldi[det[0][0]].eman_etiketa() != "HAUL_EDBL")
       for (int p=0;p<zenb;p++) {
	 if (det[p][0] != -1) {
	   int os;
	   string hat_forma,et,nag_ima,hat_an;
	   string_lista hat_im;
	   if (Esaldi[det[p][0]].eman_etiketa() == "HAUL_EDBL")
	     hat_forma = Esaldi[det[p][0]].eman_forma();
	   else {
	     int_lista osagaiak;
	     int_lista::iterator ohasi, oamaitu,ot;
	     for (os=0;os<kop;os++) {
	       osagaiak.push_back(det[p][os]);
	     }
	     osagaiak.sort();
	     ohasi = osagaiak.begin();
	     oamaitu = osagaiak.end();
	     for (ot = ohasi; ot != oamaitu; ++ot) {
	       int os = *ot;
	       string f = Esaldi[os].eman_forma();
	       if (ot != ohasi) 
		 hat_forma += "_";
	       if (os == det[p][nag]) {
		 nag_ima = HAT_taula[h].eman_nagusiaren_im(p);
		 Esaldi[os].eman_im(nag_ima,hat_im);
	       }
	       hat_forma += f;
	     }
	   }
	   et = Esaldi[det[p][0]].eman_etiketa();
	   
	   if (nag != -1) {
	     string_lista::iterator hanhasi, hanamaitu,hant;
	     
	     hanhasi = hat_im.begin();
	     hanamaitu = hat_im.end();
	     for ( hant = hanhasi; hant != hanamaitu; ++hant) {
	       string hantmp = *hant;
	       hat_an = hat_analisi;
	       hat_an += hantmp;
	       for (os=0;os<kop;os++) {
		 Esaldi[det[p][os]].Sartu_forma(hat_forma,"HAUL_EDBL");
		 Esaldi[det[p][os]].Sartu_osagai_kopurua(kop);
		 Esaldi[det[p][os]].Sartu_analisi_hat(hat_an,HAT_taula[h].segurua());
	       }
	     }
	   }
	   else {
	     hat_an = hat_analisi;
	     for (os=0;os<kop;os++) {
	       Esaldi[det[p][os]].Sartu_forma(hat_forma,"HAUL_EDBL");
	       Esaldi[det[p][os]].Sartu_osagai_kopurua(kop);
	       Esaldi[det[p][os]].Sartu_analisi_hat(hat_an,HAT_taula[h].segurua());
	     }
	   }
	 }
       }
     else
       for (int p=0;p<zenb;p++) 
	 for (int os=0;os<kop;os++) 
	   Esaldi[det[p][os]].ken_hat(h);
     
     HAT_taula[h].ken_markak_detektatuak();

   }
}

// *********************************************************************//
void  HAT_class::sinplifikatu_HAT_markatuak()
  // Elementu amankomunak dituzten HATak detektatzen badira,
  // HATik luzeena, segurua dena, distantzia txikiena duena edota
  // HATaren lemaren ordena mantentzen duena aukeratuko dugu.
{
  int i,i1,j,k;
  string nagusiak[MAX_ERREP];

// Hitzez hitz konprobatuko dugu hat bat baino gehiagotan dagoen.

  for (i=0;i<hitz_indizea;i++)
    {
      int zenbat = Esaldi[i].terminoa_da();
      int_lista hitzaren_hat;
      // HAT bat baino gehiagotan badago aukeratu:
      // - Segururik badago, segurua aukeratu.
      // - Ez badago, ez-seguru guztiak eman.
      if (zenbat > 1)
	{
	  int_lista seguruak;
	  int_lista ez_seguruak;
	  int_lista aukeratua;
          int_lista::iterator hasi, amaitu, t;

	  // Seguruak eta ez-seguruak bananduko ditugu bi zerrendatan.
          hasi = Esaldi[i].hat_lista.begin();
          amaitu = Esaldi[i].hat_lista.end();
          for ( t = hasi; t != amaitu; ++t )
	    {
	      int h = *t;
	      if (HAT_taula[h].segurua())
		seguruak.push_back(h);
	      else
		ez_seguruak.push_back(h);
	    }
	  // Segururik badago, haien artean aukeratu.
	  // Emaitza aukeratua aldagaian gordeko dugu.
	  if (!seguruak.empty())
	    {
	      aukeratu_hat_seguruak(&seguruak,&aukeratua);
	    }
	  
	  // Orain aukeratutakoaz beste guztietan begiratu zein beste hitz diren
	  // osagai eta hitz horietatik kendu hataren indizea. Aukeratuak ez-seguruak
	  // edo aukeratutakoa.
	  hitzaren_hat.assign(hasi,amaitu);
          hasi = hitzaren_hat.begin();
          amaitu = hitzaren_hat.end();
          for ( t = hasi; t != amaitu; ++t )
	    {
	      int ezab = *t;
	      int kop = HAT_taula[ezab].eman_osagai_kopurua();
	      int zenb;
              vector< vector<int> > det;
              
	      
	      // segurua aukeratu bada, edo segururik ez badago, ez-segurua denean
	      // ez dugu ezer egin behar. Hurrengora pasa.
	      if (((!aukeratua.empty()) && 
                   (find(aukeratua.begin(),
                         aukeratua.end(),
                         ezab) != aukeratua.end())) || 
		  ((aukeratua.empty()) && 
                   (find(ez_seguruak.begin(),
                         ez_seguruak.end(),
                         ezab) != ez_seguruak.end())))
		{
		  continue;
		}
	      // Bestela, bilatu hat horretan zein hitzekin agertzen den,
	      // markak ezabatu eta hitzei hat hori ezabatu listatik.
              det = vector< vector<int> >(MAX_ERREP);
              for (i1=0;i1<MAX_ERREP;i1++)
                det[i1] = vector<int>(kop);

	      zenb = HAT_taula[ezab].eman_detektatuak(det);
	      
	      for (j=0;j<zenb;j++)
		for (k=0;k<kop;k++)
		  if (det[j][k] == i)
		    {
		      int t;
		      for (t=0;t<kop;t++)
			// hat listatik ezabatu hat horren indizea
			//                  if (t != k)
			Esaldi[det[j][t]].ken_hat(ezab);
		      det[j][0] = -1;
		      break;
		    }
	      HAT_taula[ezab].sartu_detektatuak(det,nagusiak);
// 	      for (i1=0;i1<MAX_ERREP;i1++)
// 		delete det[i1];
// 	      delete det;  
	    }      
	  // Ezabatu seguruak eta ez-seguruak banatzeko erabilitako listak.
	  seguruak.clear();
	  ez_seguruak.clear();
	}
    }
  
// Eguneratu HAT__mark. Esaldian agertutako HATak bakarrik utziko ditugu.

  hustu_HAT_markatua();

  int_lista::iterator hasi, amaitu, t;
  
  for (i=0;i<hitz_indizea;i++)
    {
      if (Esaldi[i].terminoa_da())
	{
          hasi = Esaldi[i].hat_lista.begin();
          amaitu = Esaldi[i].hat_lista.end();
          for ( t = hasi; t != amaitu; ++t )
	    {
	      int hata = *t;
	      erantsi_HAT_markatua(hata);
	    }
	}
    }
  
}

// *********************************************************************//
void  HAT_class::aukeratu_hat_seguruak(int_lista *zeintzuk, int_lista *ona)
    // listako HATen artekoan aukeratu ondokoaren arabera:
    // - Elementu gehien dituena.
    // Elementu kopuru bera badute, oraingoz lehena utzi.
    // Pendiente dago errore fitxategian esaldia eta dudazko HATak idaztea.
{
  int kont=0;

  // kontatu zenbat diren
  kont = zeintzuk->size();
  if (kont == 1)
    {
      // bakarra bada, horixe itzuli.
      ona->push_back(zeintzuk->front());
    }
  else
    {
      int h=-1,max=0,bakarra=1;
      int_lista::iterator hasi, amaitu, t;

      // bat baino gehiago badira, luzeena itzuli.
      // max-en osagai kopuru handiena gordeko dugu.
      // h-n osagai gehien duen HATaren indizea.
      // bakarra-n gordeko dugu osagai kopuru bera duena bakarra den ala ez.

      hasi = zeintzuk->begin();
      amaitu = zeintzuk->end();
      for ( t = hasi; t != amaitu; ++t )
	{
	  int dat = *t;
	  int osa = HAT_taula[dat].eman_osagai_kopurua();
	  if (osa > max)
	    {
	      max = osa;
	      bakarra = 1;
	      h = dat;
	    }
	  else
	    if (osa == max)
	      bakarra = 0;
	}
      if (bakarra)
	// osagai kopuru maximoa duen HATa bakarra bada, horixe itzuli.
	ona->push_back(h);
      else
	{
	  // osagai kopuru bereko HAT bat baino gehiago badago, lehena???
	  // oraingoz lehena. Bestela erabiliko ditugu irizpideak erabakitzeko.
          // 2001/XII/7 aldatua. Osagai kopuru bereko seguru guztiak eman.
          hasi = zeintzuk->begin();
          amaitu = zeintzuk->end();
          for ( t = hasi; t != amaitu; ++t )
            {
              int dat = *t;
              int osa = HAT_taula[dat].eman_osagai_kopurua();
              if (osa == max)
                ona->push_back(dat);
            }
	}
    }
}

// *********************************************************************//


