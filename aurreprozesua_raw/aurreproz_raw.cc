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


#include "aurreproz_raw.h"
#include <string.h>
#include <vector>
#include <strings.h>
#include <sstream>
#include "bereiz_etq.h"
#include "filtro.h"
#include "dat_orok.h"

aurreprozRaw::aurreprozRaw() {}

void aurreprozRaw::init(char *auto_izena, char *sarrera_izena)
{

  sarrera_f.init(string(sarrera_izena));
  analizatu.init(auto_izena,&sarrera_f);
  fitxategiIzena = sarrera_izena;
}

extern void aztertu_zenbakia(char *,char *);
extern int berdinak(char *, char *); 
extern void Maiuskulak(char *, char *, char *);
extern int erromatarra_da(char *);

void aurreprozRaw::ken_gidoia()
{
 char hitz[MAX_STRING];
 int i = 0;

 hitz[0] = '\0';
 strcpy(hitz, hitza.e_hitza().c_str());

 while ((hitz[i] != '-') && (hitz[i] != '\0'))
   i++;
 if (hitz[i] == '-')
   {
	if ((hitz[i+1] == ' ') || (hitz[i+1] == '\t'))
	  // gidoia + (zuria | TAB)* + CR denerako
	  while ((hitz[++i] == ' ') || (hitz[i] == '\t'));
    if (hitz[i] == '\n')
      {
       string h;
       strcpy(&hitz[i],&hitz[i+2]);
       h = hitz;
       hitza.reset_h();
       hitza.s_hitza(h);
       hitza.reset_e();
       hitza.s_egiaztatzeko(h);
      }
   }
}

void  aurreprozRaw::tratatu_hitza()  // tratamendua egin hitzaren gainean
{
 char egiaz[MAX_STRING], hitz[MAX_STRING], aurreko[MAX_STRING], atzeko[MAX_STRING];
 int zen_errom;
 char tmp[MAX_STRING],atzizkia[MAX_STRING],tmp2[MAX_STRING];
 unsigned int l,a;

 egiaz[0] = '\0';
 aurreko[0] = '\0';
 atzeko[0] = '\0';
 atzizkia[0] = '\0';

 ken_gidoia(); /*** 95/1/10 gidoi + CR dagoenean kentzeko */

 switch (hitza.e_tratamendua()) {
 case -1:{
   hitza.reset_e();
   hitza.s_etiketa(BEREZIAK);
   return;
 }
 case 9: { // ID denean ezer ez egin eta egiaztatzekoa ezabatu
   hitza.reset_e();
   return;
 }
 case 7 : {
   hitz[0] = '\0';
   strcpy(hitz,hitza.e_egiaztatzeko().c_str());
   tmp[0] = '\0';
   strcpy(tmp,hitz);
   strcpy(aurreko,strtok(hitz,"'’´")); // t
   strcpy(atzeko,strtok(NULL,"'’´"));  // erdi?
   if (!strcmp(aurreko,"t") && !strcmp(atzeko,"erdi"))
     {
       // banatu
       long offseta;
       int kom = strlen(aurreko);
       char k[2];
       k[0]=tmp[kom];
       k[1]='\0';
       strcat(aurreko,k);
       hitza.reset_h();
       hitza.s_hitza(aurreko);
       offseta = (long) strlen(aurreko);
       analizatu.back_token(offseta);
       hitza.reset_e();
       strcpy(aurreko,"eta");
       hitza.s_egiaztatzeko(aurreko);
       return;
     }
   else
     {
       // Utzi dagoen bezala. min'...
       tmp[0] = '\0';
       strcpy(tmp,atzeko);
       hitza.reset_e();
       string bidali = string(tmp);
       string jaso = this->kenduMaj(bidali);
       
       hitza.s_egiaztatzeko(jaso);
       hitza.s_etiketa(BEREZIAK);
       return;
     }
 }
 case 1 : {
   hitza.reset_e();
   switch (hitza.e_hitza().c_str()[0])
     {
     case '.' : if (hitza.e_hitza().length() == 1)
       hitza.s_etiketa(PUNTUA);
       break;
     case ',' : hitza.s_etiketa(KOMA);
       break;
     case ':' : hitza.s_etiketa(BI_PUNTU);
       break;
     case ';' : hitza.s_etiketa(PUNTU_KOMA);
       break;
     case '?' : hitza.s_etiketa(GALDERA);
       break;
     case '!' : hitza.s_etiketa(ESKLAM);
       break;
     case '<' : hitza.s_etiketa(BESTELAKOAK);
       break;
     case '>' : hitza.s_etiketa(BESTELAKOAK);
       break;
     case '/' : hitza.s_etiketa(BESTELAKOAK);
       break;
     case ' ' :
     case '\t':
     case '\n': hitza.s_etiketa(TXURI);
       hitza.s_hitza("_"); // truko bat. gero kendu.
       break;
     default  : hitza.s_etiketa(BESTELAKOAK);
       break;
     }
   return;
 }
 case 2 : {
   strcpy(tmp2,hitza.e_egiaztatzeko().c_str());
   aztertu_zenbakia(tmp2, egiaz);
   hitza.s_egiaztatzeko(egiaz);
   return;
 }
 case 5 : { /*** erromatarren tratamendua */
   strcpy(tmp2,hitza.e_egiaztatzeko().c_str());
   Maiuskulak(tmp2,atzizkia,hitz);
   if (strlen(hitz) && (zen_errom = erromatarra_da(hitz)) != 0)
     {
       hitza.reset_e();
       hitza.reset_etq();
       hitza.s_etiketa(ERROMATARRAK);
       if (strlen(atzizkia) == 0) {
	 // Begiratu ea hurrengo tokena puntua den
	 tokenRaw hitza2;
	 analizatu.next_token();
	 hitza2 = analizatu.e_azkena();
	 if (hitza2.e_hitza().c_str()[0] == '.') {
	   strcpy(atzizkia,hitza2.e_hitza().c_str());
	   analizatu.next_token();
	   hitza2 = analizatu.e_azkena();
	   if (hitza2.e_hitza().c_str()[0] != ' ' && 
	       hitza2.e_hitza().c_str()[0] != '\t' &&
	       hitza2.e_hitza().c_str()[0] != '\n')
	     strcat(atzizkia,hitza2.e_hitza().c_str());
	   else analizatu.back();
	 }
	 else analizatu.back();
	 if (strlen(atzizkia) != 0) {
	   egiaz[0] = '\0';
	   strcpy(egiaz,hitza.e_hitza().c_str());
	   strcat(egiaz,atzizkia);
	   hitza.s_hitza(egiaz);
	 }
       }
       egiaz[0] = '\0';
       sprintf(egiaz,"%d%s",zen_errom,atzizkia);
       hitza.s_egiaztatzeko(egiaz);
       strcpy(tmp2,hitza.e_egiaztatzeko().c_str());
       aztertu_zenbakia(tmp2, egiaz);
       hitza.reset_e();
       hitza.s_egiaztatzeko(egiaz);
       return;
     }
   else if (hitza.e_etiketa() == BAK) {
     tmp2[strlen(tmp2)-1]='\0';
     string bidali = string(tmp2);
     string jaso = this->kenduMaj(bidali);


     hitza.s_egiaztatzeko(jaso);
     return;
   }
 }
 case 3 : {
   egiaz[0] = '\0';
   strcpy(tmp2,hitza.e_egiaztatzeko().c_str());
   string bidali = string(tmp2);
   string jaso = this->kenduMaj(bidali);
   
   hitza.s_egiaztatzeko(jaso);
   if (strchr(MAJ,hitza.e_hitza().c_str()[0]) == NULL && hitza.e_etiketa() != "IDENT") 
     hitza.reset_etq();
 }
 case 4 : {/*** hitz elkarketen tratamendua */
   if (strchr(hitza.e_egiaztatzeko().c_str(),'-') == NULL)
     break;
   if (strchr(hitza.e_egiaztatzeko().c_str(),'\n') != NULL)
     {
       hitz[0] = '\0';
       strcpy(hitz,hitza.e_egiaztatzeko().c_str());
       l=0;
       while (hitz[l] != '-') l++;
       a=l+1;
       while ((hitz[a] != '-') && (a < strlen(hitz))) a++;
       if (a == strlen(hitz)){
	 a=l+1;
	 while ((hitz[a] == ' ') || (hitz[a] == '\t') ||
		(hitz[a] == '\n')) a++;
	 tmp[0] = '\0';
	 strcpy(tmp,&(hitz[a]));
	 hitz[l] = '\0';
	 strcat(hitz,tmp);
	 hitza.reset_h();
	 hitza.s_hitza(hitz);
	 break;
       }
       if (l != a)
	 {
	   tmp[0] = '\0';
	   strcpy(tmp,&(hitz[a]));
	   hitz[l] = '\0';
	   strcat(hitz,tmp);
	   hitza.reset_h();
	   hitza.s_hitza(hitz);
	 }
     }
   hitz[0] = '\0';
   strcpy(hitz,hitza.e_hitza().c_str());
   strcpy(aurreko,strtok(hitz,"-"));
   strcpy(atzeko,strtok(NULL,"-"));
   if (!strcmp(atzeko,"edo")  || !strcmp(atzeko,"eta"))
     {
       // banatu
       long offseta = (long) strlen(aurreko);
       analizatu.back_token(offseta);
       hitza.reset_h();
       hitza.s_hitza(aurreko);
       hitza.reset_e();
       string bidali = string(aurreko);
       string jaso = this->kenduMaj(bidali);


       hitza.s_egiaztatzeko(jaso);
       break;
     }
   else {
     break;
   }
 }
 case 6 : {
   strcpy(tmp,hitza.e_egiaztatzeko().c_str());
   //   bihur_maj_asteris(tmp,egiaz);
   string bidali = string(tmp);
   string jaso = this->kenduMaj(bidali);

   hitza.s_egiaztatzeko(jaso);
   return;
 }
 case 8: {
   // Aukera hau IDENT motakoentzat jarrita dago.
   // Zenbakizkoak agertzen badira, saiatu dadila
   // morfologikorako prestatzen. Bestela dagoenean utzi.
   char hitzkopia[MAX_STRING], hitzkopia2[MAX_STRING],hurrengoak[MAX_STRING];
   char *hktmp;
   hitzkopia[0] = '\0';
   strcpy(hitzkopia,hitza.e_egiaztatzeko().c_str());
   strcpy(hitzkopia2,hitza.e_egiaztatzeko().c_str());
   if ((strstr(hitzkopia,"/") != NULL)||(strstr(hitzkopia,"@") != NULL))  {
     hitza.s_egiaztatzeko("cc");
     return;
   }
   if ((hktmp=strtok(hitzkopia,ZIFRA)) != NULL) {
     if (strcmp(hktmp,hitza.e_egiaztatzeko().c_str()) != 0) {
       hurrengoak[0] = '\0';
       strcpy(hurrengoak,&hitzkopia2[strlen(hktmp)]);
       char *atzizkirik;
       if ((atzizkirik=strpbrk(hurrengoak,ALF)) != NULL) {
	 egiaz[0] = '\0';
	 if ( strspn(atzizkirik,ALF) == strlen(atzizkirik) ) {
	   // atzizkia bakarrik ALFeko ikurrez osatuta
	   if (strchr(BOKALE,atzizkirik[0]) != NULL)
	     strcpy(egiaz,"cc");
	   else
	     strcpy(egiaz,"co");
	   strcat(egiaz,atzizkirik);
	   hitza.s_egiaztatzeko(egiaz);
	   return;
	 }
	 
	 else {
	   strcpy(egiaz,"cc");
	   hitza.s_egiaztatzeko(egiaz);
	   return;
	 }
       }
       if (strspn(hurrengoak,ZIFRA) == strlen(hurrengoak)) {
	 hitza.s_egiaztatzeko("cc");
	 return;
       }
       hitza.s_egiaztatzeko("cc");
       return;
     }
     else {  
       if (strchr(MAJ,hitzkopia[0]) != NULL) {
 	 egiaz[0] = '\0';
 	 strcpy(tmp2,"Cc");
	 string bidali = string(tmp2);
	 string jaso = this->kenduMaj(bidali);

 	 hitza.s_egiaztatzeko(jaso);
       }
       else {
	 hitza.s_egiaztatzeko("cc");
       }
       return;
     }
   }
   else {
     if (strchr(MAJ,hitzkopia[0]) != NULL) {
       egiaz[0] = '\0';
       strcpy(tmp2,"Cc");
       string bidali = string(tmp2);
       string jaso = this->kenduMaj(bidali);

       hitza.s_egiaztatzeko(jaso);
     }
     else {
       hitza.s_egiaztatzeko("cc");
     }
     return;
   }
 }
 default : {break;}
 }
 if (hitza.e_tratamendua() == 3 || hitza.e_tratamendua() == 5) return;
 egiaz[0] = '\0';
 strcpy(tmp2,hitza.e_hitza().c_str());
 string bidali = string(tmp2);
 string jaso = this->kenduMaj(bidali);

 hitza.s_egiaztatzeko(jaso); 
}

void  aurreprozRaw::aurreprozesua(int irteera,vector<string> *emaitza)  // aurreprozesuaren ziklo osoa betetzen duena
{
 // extern int INTERAK;
 // extern int INTERAMORFO;
 int amaitu_interamorfo=0;
 
 while (!amaitu_interamorfo && analizatu.next_token() > 0) {
   hitza = analizatu.e_azkena();
   tratatu_hitza();

   if (irteera == TOKENAK) {
     if (hitza.e_tratamendua() != 1)
       if (hitza.e_hitza().length()) {
	 printf("%s",hitza.print_token_hutsa().c_str());
       }
   }
   else {
     if (hitza.e_etiketa() != TXURI) {
       if (irteera == TOKEN_PUNT)
	 if (irteera == ANALIRA) {
	   hitza.print_token_hutsa(emaitza);
	 }
	 else {
	   printf("%s",hitza.print_token_hutsa().c_str());
	 }
       else {
	 // hau aldatu inprimatu beharrean tokena analizatzera bidaltzeko
	 if (irteera == ANALIRA) {
	   hitza.print_token(emaitza);
	 }
	 else {
	   printf("%s",hitza.print_token().c_str());
	 }
       }
       // if (INTERAK) printf("#\n");
       // if (INTERAMORFO) {
       // 	 const string amaitzeko = "@@##";
       // 	 if (hitza.e_hitza() == amaitzeko) {
       // 	   amaitu_interamorfo = 1;
       // 	 }
       // }
       fflush(stdout);
     }
   }
 }
}

string aurreprozRaw::kenduMaj(const string & str) {
  string lag = str; 
  string ema;
  
  for (unsigned int i = 0; i <  str.size(); i++) {

    if (isupper(lag[i]) && (lag[i]!='\321') && (lag[i]!='\361')) {
      
      ema.append(1,ASTERIS);
      char c = tolower(lag[i]);
      ema.append(1,c);
      
    }
    else if (lag[i]=='\321') {

      ema.append(1,ASTERIS);
      ema.append(1,NI_GUZTIENTZAT);

    }
    else if (lag[i]=='\361') {

      ema.append(1,NI_GUZTIENTZAT);

    }
    else if (lag[i]==' ') {

      ema.append(1,'_');

    }
    else if (lag[i]!='\222' && lag[i] != '\'' && lag[i] != '\"') ema.append(1,lag[i]);
    
  }
  
  return ema;
  
}

string aurreprozRaw::jarriMaj(const string & str) {
  
  string lag = str; 
  string ema;
  
  for (unsigned int i = 0; i <  str.size(); i++) {

    if (lag[i] == ASTERIS) {

      if (lag[i+1] == NI_GUZTIENTZAT) ema.append(1,NI_H);
      else {
	
	char c = toupper(lag[i+1]);
	ema.append(1,c); 

      }
      
      i++;

    }
    else if (lag[i] == NI_GUZTIENTZAT) ema.append(1,NI_T);
    else if (lag[i]=='_') ema.append(1,' ');
    else ema.append(1,lag[i]);
    
  }
  
  return ema;

}


