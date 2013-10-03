%{
extern "C"
{
int yylex(void);
}

#include <stdio.h>
#include <string.h>
#include <string>
#include <malloc.h>

/* void yyerror(const char *s) */
/* { */
/*   printf("%s\n",s); */
/* } */
void yyerror(const char *msg)
{
  extern int line;
  (void) fprintf(stderr, "%d: %s\n", line, msg);
}

#include "HAT_class.h"
#include "ordena.h"

/*** Aldagai orokorrak */

 HAT_class       denak;
 int             line = 1;
 int             zein_h;
 int             posizioa;
 int             forma_da;
 int             gorde = 1;
 char            erroaren_im[500];

%}

%union {
        char str[500];
        char kar;
        int zif;
       }

%token <str> INFORMAZIOA LEMAA HAT_INFO HITZA OHARRA HAT_LEMA
%token <str> HITZ_FORMA ETIK ETIK_PUNT ALDAERA ETIK_HAUL
%token <zif> ZIFRA
%token PAR_IREKI PAR_ITXI ERROA ETENA EZORD BUK_MARKA BAI EZ PIPE
%token OSAGAI_KOP FORMA_DA LEMA_DA CORRECT AMAITU

%type <zif> zer erlazioa erroa segurua
%type <zif> osagai_kop terminoa
%type <str> hat_lema informazioa
%type <str> etiketa
%%
sarrera     : ereduak testua
              {
                denak.Hasieraketa();
                denak.Esaldi_reset_hitza();
              }
            ;

osagai_kop  : OSAGAI_KOP ZIFRA { $$ = $2;}
            ;

ereduak     : ereduak eredua
            | eredua
            ;

hasiera     : hat_lema HAT_INFO segurua osagai_kop
              {
                std::string lem = $1;
                std::string im = $2;
		gorde = 0;
                if ($3) {
		  zein_h = denak.zein_HAT();
		  denak.erantsi_HAT(lem,im,$4,$3);
		  gorde = 1;
		}
              }
            ;

eredua      : hasiera terminoak
            ;

hat_lema    : HAT_LEMA
              {
                int i,j;
                $$[0] = '\0';
                strcpy($$,$1);
                i = strlen($$);
                j = 0;
                while (j < i) {
                  if ($$[j] == ' ') 
                    $$[j] = '_';
                  j++;
                }
                posizioa = 0;
              }

terminoak   : terminoak erlazioa terminoa
              {
                if (gorde)
                  {
                    if ($3 == 1) {    // osagai nagusia bada, gorde posizioa .nagusia-n
                      denak.sartu_nagusia(zein_h,posizioa);
                    }
                    denak.sartu_murriztapena(zein_h,$2,posizioa-1);
                    posizioa++;
		  }
              }
            | terminoa
              {
                if (gorde)
                  if ($1 == 1) {    // osagai nagusia bada, gorde posizioa .nagusia-n
                    denak.sartu_nagusia(zein_h,posizioa);
                  }
		posizioa++;
              }
            ;

terminoa    : zer hitzak erroa term
              {
                $$ = $3;
              }
            ;

term        : PAR_IREKI LEMAA informazioa PAR_ITXI
              {
               erroaren_im[0] = '\0';
               strcpy(erroaren_im,$3);                
               if (gorde)
                 {
                   std::string im = $3;
                   std::string lem = $2;
                   if (!forma_da) {
		     denak.erantsi_LEMA(lem,zein_h,posizioa,im);
		   }
	         }
              }
            | {

              }
            ;

informazioa : INFORMAZIOA
              {
               $$[0] = '\0';
               strcpy($$,$1);
              }
            | { 
               $$[0] = '\0';
              }
            ;

hitzak      : hitzak PIPE HITZA ETIK_HAUL
              {
                if (gorde)
                  {
                   std::string hitz = $3;
                   if (forma_da) {
		     denak.erantsi_FORMA(hitz,zein_h,posizioa);
		   }
		  }
              }
            | HITZA ETIK_HAUL
              {
                if (gorde)
                  {
                   std::string hitz = $1;
                   if (forma_da) {
		     denak.erantsi_FORMA(hitz,zein_h,posizioa);
		   }
		  }
              }
            | hitzak PIPE HITZA
              {
                if (gorde)
                  {
                   std::string hitz = $3;
                   if (forma_da) {
		     denak.erantsi_FORMA(hitz,zein_h,posizioa);
		   }
		  }
              }
            | HITZA
              {
                if (gorde)
                  {
                   std::string hitz = $1;
                   if (forma_da) {
		     denak.erantsi_FORMA(hitz,zein_h,posizioa);
		   }
		  }
              }
            ;
zer         : FORMA_DA
              {
                forma_da = 1;
              }
            | LEMA_DA
              {
                forma_da = 0;
              }
            ;
 
segurua     : BAI
              {
                $$ = 1;
              }
            | EZ
              {
                $$ = 0;
              }
            ;

erroa       : ERROA
              {
                $$ = 1;
              }
            | { 
                $$ = 0; 
              }
            ;

erlazioa    : ETENA
              {
                $$ = ETEN;
              }
            | EZORD
              {
                $$ = EZOR;
              }
            | { $$ = JARR; }
            ;

testua      : esaldiak 
            ;

esaldiak    : esaldiak esaldia {
                                denak.bilatu_HAT_Esaldi();
				denak.inprimatu_Esaldi();
                                denak.Esaldi_reset_hitza();
                               }
            | esaldia          {
                                denak.bilatu_HAT_Esaldi();
				denak.inprimatu_Esaldi();
                                denak.Esaldi_reset_hitza();
                               }
            ;

esaldia     : hitza esaldia
            | puntuazioa
            ;

hitza       : HITZ_FORMA etiketa analisiak
             {
               std::string f = $1;
               std::string e = $2;

              denak.Esaldi_Sartu_forma(f,e);
              denak.Esaldi_next_hitza();
             }
            | HITZ_FORMA etiketa
             {
               std::string f = $1;
               std::string e = $2;

              denak.Esaldi_Sartu_forma(f,e);
              denak.Esaldi_next_hitza();
             }
            ;

etiketa     : ETIK
             { $$[0] = '\0'; strcpy($$,$1); }
            |{ $$[0] = '\0'; }
            ;

puntuazioa  : HITZ_FORMA ETIK_PUNT
             {
               std::string f = $1;
               std::string e = $2;

              denak.Esaldi_Sartu_forma(f,e);
              denak.Esaldi_next_hitza();
             }
            | AMAITU
            ;

analisiak   : analisiak analisia
            | analisia
            ;

analisia    : PAR_IREKI LEMAA ALDAERA INFORMAZIOA PAR_ITXI 
             {
              AN an(0,$2,$3,$4);

              denak.Esaldi_anali_insert(an);
             }
            | PAR_IREKI LEMAA INFORMAZIOA PAR_ITXI
             {
              std::string hutsa = "*******";
              AN an(0,$2,hutsa,$3);

              denak.Esaldi_anali_insert(an);
             }
            | CORRECT PAR_IREKI LEMAA ALDAERA INFORMAZIOA PAR_ITXI
             {
              std::string hutsa = "*******";
              AN an(1,$3,$4,$5);

              denak.Esaldi_anali_insert(an);
             }
            | CORRECT PAR_IREKI LEMAA INFORMAZIOA PAR_ITXI
             {
              std::string hutsa ="*******";
              AN an(1,$3,hutsa,$4);

              denak.Esaldi_anali_insert(an);
             }
            ;
