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


#include "an_lex_raw.h"
#include "token_raw.h"
#include "dat_orok.h"
#include "filtro.h"

#define LEMA_GENERIKOA_BOK "cc"
#define LEMA_GENERIKOA_KON "co"

// statusRaw aurrekoa;      // aurreko token-a eta sarreraren estadua gorde
// statusRaw azkena;        // azken token-a eta sarreraren estadua gorde
// automata aurre_auto;  // transizio posibleak eta bestelako informazioa
// fileMngRaw sarrera;     // sarrera (fitxategia edo buffer bat)

anLexRaw::anLexRaw()         // hasieraketa funtzioa
{
 tokenRaw lag;
 string s1,s2,s3;

 s1 = ".";
 s2 = "BEREIZ";
 s3 = "";
 hasierapar = 0;
 lag.init(s1,s2,s3,0,hasierapar,hasierapar+1);

 aurrekoa.s_token(lag);
 aurrekoa.s_offset(0L);
 azkena.s_token(lag);
 azkena.s_offset(0L);
//  aurre_auto.init(AURREAN_LEX);
}

void anLexRaw::init(char *auto_izena, fileMngRaw *fitx) 
                         // hasieraketa funtzioa
{

 tokenRaw lag;
 string s1,s2,s3;

 s1 = ".";
 s2 = "BEREIZ";
 s3 = "";
 hasierapar = 0;
 lag.init(s1,s2,s3,0,hasierapar,hasierapar+1);

 aurrekoa.s_token(lag);
 aurrekoa.s_offset(0L);
 azkena.s_token(lag);
 azkena.s_offset(0L);
//  aurre_auto = *aurre;
 aurre_auto.init(auto_izena);
 sarrera = fitx; 
 sarrera->reset();

}

void  anLexRaw::reset()    // sarrera reseteatu
{
 sarrera->reset();
}

void  anLexRaw::reset(fileMngRaw *fitx)
                         // sarrera berria fitx-en eta hasieratu
{

 sarrera->close();
 sarrera->~fileMngRaw();
 sarrera = fitx;
 sarrera->reset();

}

void  anLexRaw::back()     // aurreko statusera itzuli
{
 sarrera->back(aurrekoa.e_offset());
}

int anLexRaw::trans_berria(char *kar)
                         // hurrengo karakterea irakurri eta automata mugitu.
                         // transizioa posible den ala ez itzultzen du.
{
 int trans;

 if (sarrera->eof())
   return 0;
 *kar = sarrera->get();
 // if (*kar == '\303')  *kar = sarrera->get();

 if (*kar == '\221') 
   *kar=NI_H;
 if (*kar == '\261') 
   *kar=NI_T;
 trans = aurre_auto.mugitu(*kar);
 if (trans == 0)
   {
//    printf("\n%c trantsizioa ez da posible\n",*kar);
    return 0;           // trantsizio ezina
   }
 if (trans == -1)
   return -1;           // karaktere berezia
 return 1;
}

int   anLexRaw::next_token()  
                         // hurrengo tokena lortzen duena
{
 statusRaw aurreko;                 // aurreko-n tartean topatutako tokena
                                 // lortutako token-a
 char kar;                       // irakurritako karakterea
 char irakurritakoa[MAX_STRING]; // orain arte irakurritakoa
 char irakurritakoaeg[MAX_STRING]; // orain arte irakurritakoa egiaztatzeko
 int luz_i,luz_ie;                      // irakurritakoaren indizea
 int aurreko_betea = 0;
 extern int filtratu(char k);
 string h,e;
 tokenRaw t;
 int berezia = 0;                // karaktere bereziak detektatu diren
 int trans_bai;                  // transizio berria egin daitekeen jakiteko
 int hasiera;
 string origattr = "";
 string etikstr = "";

// hasieraketak

 aurre_auto.reset();                  // automata hasierako estaduan
 luz_i = 0;// indizeak hasieratu
 luz_ie = 0;
 trans_bai = trans_berria(&kar);
 if (trans_bai == 0)
   {
    if (sarrera->eof())
      return -1;
    sarrera->back(azkena.e_offset());
    return 0;
   }
 else
   if (trans_bai == -1)
     berezia = 1;

 hasiera = (int)sarrera->non()-hasierapar;
 while (!sarrera->eof())               // karaktererik geratzen den bitartean
   {
    while ((!aurre_auto.bukaerakoa()) && (!sarrera->eof()) &&
	   (luz_i < MAX_STRING - 1))
      // automataren estadua bukaerakoa ez den
      // bitartean karaktereak irakurri eta
      // gorde.
      {
        if (!berezia) {
          irakurritakoaeg[luz_ie++] = kar;
        }
	irakurritakoa[luz_i++] = kar;
        berezia = 0;
//       kar = sarrera.get();
        if ((trans_bai = trans_berria(&kar)) == 0)
          if (!aurreko_betea)
            {
              sarrera->back(azkena.e_offset());
              return 0;
            }
          else                         // aurkitu dugu lehenago token bat
            {
              aurrekoa = azkena;
              azkena = aurreko;
              sarrera->back(aurreko.e_offset());
              return 1;
            }
        else
          if (trans_bai == -1)
            berezia = 1;
      }

    if (!berezia) {
      irakurritakoaeg[luz_ie++] = kar;
    }
    if (kar == NI_H ) { 
      if (luz_i>0 && irakurritakoa[luz_i-1] == '\303')
	irakurritakoa[luz_i++] = '\221';
      else {
	if (luz_i==0 || irakurritakoa[luz_i-1] != '\303')
	  irakurritakoa[luz_i++] = '\303';
	irakurritakoa[luz_i++] = '\221';
      }
    }
    else if (kar == NI_T) {
      if (luz_i>0 && irakurritakoa[luz_i-1] == '\303')
	irakurritakoa[luz_i++] = '\261';
      else {
	if (luz_i==0 || irakurritakoa[luz_i-1] != '\303')
	  irakurritakoa[luz_i++] = '\303';
	irakurritakoa[luz_i++] = '\261';
      }
    }
    else {
      irakurritakoa[luz_i++] = kar;
    }
    berezia = 0;
    irakurritakoa[luz_i] = '\0';
    irakurritakoaeg[luz_ie] = '\0';

    // oraingo estadua gorde, tokena eta offseta
    h = irakurritakoa;
    e = irakurritakoaeg;
    etikstr = aurre_auto.etiketa();

    if (berezia) t.init(h,etikstr,e,-1,hasiera,(int)sarrera->non()-hasierapar);    
    else t.init(h,etikstr,e,aurre_auto.tratamendua(),hasiera,(int)sarrera->non()-hasierapar);
    
    aurreko.s_token(t);
    // gorde offseta eta aurreko bete dela adierazi
    aurreko.s_offset(sarrera->non());
    aurreko_betea = 1;
    if (luz_i < MAX_STRING)
      trans_bai = trans_berria(&kar);
    if ((trans_bai == 0) || (luz_i >= MAX_STRING))
      // ezin da tokena gehiago luzatu
      {
       aurrekoa = azkena;
       azkena = aurreko;
       if (luz_i < MAX_STRING)
         sarrera->back(aurreko.e_offset());
//       printf("%s",azkena.e_token().print_token().cstr());
       return 1;
      }
    else
      if (trans_bai == -1)
	berezia = 1;               // karaktere berezia 
   }
 return -1;                        // EOF markatzeko
}

void anLexRaw::back_token(long offsetaa) {

  // funtzio berria erabiliko dugu hemen,
  // parametroak: aurrekoaren offseta + oraingoaren luzera
  sarrera->back_token(aurrekoa.e_offset(), offsetaa);

}

tokenRaw anLexRaw::e_azkena()                // azken tokena ematen duena
{
  tokenRaw tmp;
  tmp = azkena.e_token();
  return(tmp);
}

