/* ***************************************************
 * **************************************************** */

%{
#include <locale.h>
#include <sstream>
#include <string.h>
#include <string>
#include <iostream>
#include "morfsarFormatu.h"
#include "ana2morfsar.h"
#include "constants.h"

#include "lema_aldaera.h"

#define LEMA_LUZERA_MAXIMOA 75

using namespace std;
  
 void ana2morfsarerror(const char *msg);
 string nextId();
 void  lortu_sarrera_homografo( char *cpLiteral, char *cpLema2, char *cpHomId, char *cpHBn );
 extern void   bihur_asteris_maiuskula(char *st1,char *st2);

 extern int    ana2morfsar_lerro_kop;
 extern char*  ana2morfsartext;
 extern int    ana2morfsarlex();

 extern Ana2Morfsar* yyparseAna2Morfsar;


 bool   lehenMorfema;  /* lehen morfema bada, irteerako hiztegi zenbakiak eguneratzen dira */
 string formaString;   /* hitz-forma */
 string formaLerro;    /* /<forma>/(<etiketa>/)? */
 int    ezaugOrd;      /* zenbatu beharreko ezaugarrien ordinala, morfemaz morfema resetatzen da */
 string analisiMota;   /* A, T[01], G */
 string etiketaString; /* Aurreprozesuko etiketa */ 
 bool   etiketaDago = false;
 int    trickCount = 1;

 extern int edbl_bertsioa;
 %}

%union {
  string *str;
  char  kar;
}

/* Terminalak zein motakoak diren */

%token <str>  t_forma_lerro t_anal t_forma t_ald t_aldaera t_lema t_morfema t_sarrera t_funtzioak t_sinbolo t_sinbolo_list t_sinbolo_list_sym t_sinbolo_set t_literal t_dolar t_erregela t_erroa 
%token <kar>  t_paren_ireki t_paren_itxi t_koma
%token t_stwol t_atwol t_lhb


/*  Ez terminalak zein motakoak diren */

%type  <str>  morfema_nor morfema_ald lema_nor lema_ald ezaugarriakfsn sarrera_twol
%type  <str>  hitzak sarrera fsezaugarriak 

%%

/* ***********************************************************
 * <TESTUA>	::= <KOHORTEAK>
 * *********************************************************** */

testua       : kohorteak
             ;
/* ***********************************************************
 * <KOHORTEAK>	::= <KOHORTEAK> <KOHORTEA>
 *		|   <KOHORTEA>
 * *********************************************************** */

kohorteak    : kohorteak kohortea
             | kohortea
             ;
/* ***********************************************************
 * <KOHORTEA>	::= ( <FORMA> <ANALISIAK> )
 *              |   ( <FORMA> )
 * *********************************************************** */

kohortea     : forma_lerro t_paren_ireki forma analisiak t_paren_itxi
               {
		stringstream formaStringC;
		formaStringC << formaString << trickCount;
		yyparseAna2Morfsar->setForma(formaStringC.str(),"NOTNULL");
		stringstream tmpIdLerro;
		tmpIdLerro << analisiMota[0] << formaLerro;
		yyparseAna2Morfsar->add2Gorputza(ID, tmpIdLerro.str());
		yyparseAna2Morfsar->add2Gorputza(FORMA, formaString);
		yyparseAna2Morfsar->add2Gorputza(EDBL_SARRERA, "NOTNULL");
		yyparseAna2Morfsar->add2Gorputza(HOMOGRAFOA,"0");
		yyparseAna2Morfsar->add2Gorputza(TWOL,"null");
		yyparseAna2Morfsar->add2Gorputza("kat","NULL");
		yyparseAna2Morfsar->analisiaBukatu();
               }
             | forma_lerro t_paren_ireki forma t_paren_itxi
               {
		stringstream formaStringC;
		formaStringC << formaString << trickCount;
		yyparseAna2Morfsar->setForma(formaStringC.str(),"NOTNULL");
		stringstream tmpIdLerro;
		tmpIdLerro << 'G' << formaLerro;
		yyparseAna2Morfsar->add2Gorputza(ID, tmpIdLerro.str());
		yyparseAna2Morfsar->add2Gorputza(FORMA, formaString);
		yyparseAna2Morfsar->add2Gorputza(EDBL_SARRERA, "NOTNULL");
		yyparseAna2Morfsar->add2Gorputza(HOMOGRAFOA,"0");
		yyparseAna2Morfsar->add2Gorputza(TWOL,"null");
		yyparseAna2Morfsar->add2Gorputza("kat","NULL");
		yyparseAna2Morfsar->analisiaBukatu();
               }
             | forma_lerro {
                stringstream formaStringC;
                formaStringC << formaString << trickCount;
                yyparseAna2Morfsar->setForma(formaStringC.str(),"NULL");
		yyparseAna2Morfsar->add2Gorputza(ID, formaLerro);
		yyparseAna2Morfsar->add2Gorputza(FORMA, "NULL");
		yyparseAna2Morfsar->add2Gorputza(EDBL_SARRERA, "NULL");
		yyparseAna2Morfsar->add2Gorputza(HOMOGRAFOA,"0");
		yyparseAna2Morfsar->add2Gorputza(TWOL,"null");
		yyparseAna2Morfsar->add2Gorputza("kat","NULL");
		yyparseAna2Morfsar->analisiaBukatu();
               }
             ;
forma_lerro : t_forma_lerro
{
  /* hemen jaso etiketa baldin badago??? */
  char *cpZat,*cpLer,formatmp[100];
  char *lerrOrig;

  formaLerro = *$<str>1;
  lerrOrig = strdup( $<str>1->c_str() );
  cpLer = lerrOrig; cpLer+=2; /* pasa /< forma jasotzeko */
  strcpy( formatmp, cpLer );

  if ( (cpZat = strstr(formatmp,">/") ) != NULL) {
    *cpZat = '\0';
    char *cpForma         = 0;	    /* Hitz-forma */ 

    cpForma = strdup( formatmp );
    formaString = cpForma;
    etiketaString = "";
    trickCount++;
    strcpy( formatmp, cpLer+strlen(cpForma)+2 ); /* pasatu >/ ere */
    if ( formatmp[0] == '<' ) {
      etiketaDago = true;
      cpLer = formatmp; cpLer++; /* pasa < etiketa jasotzeko */
      strcpy( formatmp, cpLer );
      formatmp[strlen(formatmp)-2] = '\0';
      etiketaString = formatmp;
    }
    else {
      etiketaDago = false;
      formaLerro = formaLerro.substr(0,formaLerro.length()-1); /* kendu amaierako '/' geroko */
    }
  }
  free(lerrOrig);
}
;

/* ***********************************************************
 * <FORMA>	 ::= ( t_forma t_literal )
 * *********************************************************** */

forma        : t_forma t_literal t_paren_itxi
             ;

/* ***********************************************************
 * <ANALISIAK>	::= <ANALISIAK> <ANALISIA>
 *		|   <ANALISIA>
 * *********************************************************** */

analisiak    : analisiak analisia
             | analisia
             ;

/* ***********************************************************
 * <ANALISIA>	::= t_erregela ( <ANAL> <LEM-MORF> )
 * *********************************************************** */

analisia     : t_erregela 
{
  analisiMota = *$<str>1 ;
}
t_paren_ireki anal lem_morf t_paren_itxi
{
  string stringErregela = *$<str>1 ;
  if (edbl_bertsioa > 4 && stringErregela[0] == 'T') {
    /* erregela-kopurua pasa */
    string errekop = stringErregela.substr(1,string::npos);
    if (errekop.length() == 0)
      errekop = "0";
    yyparseAna2Morfsar->add2Gorputza("ErregelaKopurua", errekop);

  }
}
;

/* ***********************************************************
 * <ANAL>	::= ( t_anal t_sinbolo )
 *		|   ( t_anal t_dolar t_sinbolo )
 * *********************************************************** */

anal         : t_paren_ireki t_anal t_sinbolo t_paren_itxi
             | t_paren_ireki t_anal t_dolar t_sinbolo t_paren_itxi
             ;

/* ***********************************************************
 * <LEM-MORF>     ::=   <LEM-MORFAK>
 * *********************************************************** */

lem_morf     : {
                lehenMorfema = true;
		ezaugOrd=0;
                stringstream formaStringC;
                formaStringC << formaString << trickCount;
		yyparseAna2Morfsar->setForma(formaStringC.str(),"NOTNULL");
		stringstream tmpIdLerro;
		tmpIdLerro << analisiMota[0] << formaLerro;
		yyparseAna2Morfsar->add2Gorputza(ID, tmpIdLerro.str());
		yyparseAna2Morfsar->add2Gorputza(FORMA, formaString);
               }
               lem_morfak
               {
 		yyparseAna2Morfsar->analisiaBukatu();
	       }
               ;


/* ***********************************************************
 * <LEM-MORFAK>	::= <LEM-MORFAK> <LEMA>
 *		|   <LEM-MORFAK> <MORFEMA>
 *		|   <LEMA>
 *		|   <MORFEMA>
 * *********************************************************** */

lem_morfak   : lem_morfak lema
             | lem_morfak morfema
             | lema
             | morfema
             ;

/* ***********************************************************
 * <LEMA>     ::  ( <LEMA-ALD> <RESTO-ALD> )
 *	      |   ( <LEMA-NOR> <EZAUGARRIAK> )
 * *********************************************************** */

lema         : t_paren_ireki lema_ald resto_ald t_paren_itxi

{
  if (edbl_bertsioa < 5) {
    yyparseAna2Morfsar->add2Gorputza(TWOL,*$<str>2);
  }
}

| t_paren_ireki lema_nor ezaugarriak t_paren_itxi

{
  if (edbl_bertsioa < 5) {
    yyparseAna2Morfsar->add2Gorputza(TWOL,*$<str>2);
  }
}
;

/* ***********************************************************
 * <RESTO-ALD>	::= <ALDAERA> <EZAUGARRIAK> <ERR-ZERRENDA>
 * *********************************************************** */

resto_ald    : aldaera ezaugarriak
             ;

/* ***********************************************************
 * <LEMA-ALD>	::= ( t_lema t_dolar t_literal )
 * *********************************************************** */

lema_ald     : t_lema t_dolar t_literal t_paren_itxi /* STwol */
{
  $<str>$ = new string;
  string twol = *$<str>3;
  
  if (edbl_bertsioa < 5) {
    if (!lehenMorfema){
      yyparseAna2Morfsar->morfemaBerria();
      yyparseAna2Morfsar->add2Gorputza(FORMA, formaString);
    }
    lehenMorfema = false;    
    
    if (twol.find(" ") != string::npos)
      twol.replace(twol.find(" "),1,"_");
    *$<str>$ = twol;
  }
}
;

/* ***********************************************************
 * <LEMA-NOR>	::= ( t_lema t_literal )
 * *********************************************************** */

lema_nor     : t_lema t_literal t_paren_itxi /* STwol */
{
  $<str>$ = new string;

  string twol = *$<str>2;
    
  if (edbl_bertsioa < 5) {
    if (!lehenMorfema){
      yyparseAna2Morfsar->morfemaBerria();
      yyparseAna2Morfsar->add2Gorputza(FORMA, formaString);
    }
    lehenMorfema = false;
        
    if (twol.find(" ") != string::npos)
      twol.replace(twol.find(" "),1,"_");
    *$<str>$ = twol;
  }
}
;

/* ***********************************************************
 * <ALDAERA>	::= ( t_ald t_literal )
 * *********************************************************** */

aldaera      : t_paren_ireki t_ald t_literal t_paren_itxi /* ATwol */
{
  if (edbl_bertsioa < 5) {
    char cpAux[LEMA_LUZERA_MAXIMOA];
    
    string aldTwol = *$<str>3;
    char *cpLema2=strdup( aldTwol.c_str() );
    
    if (!etiketaDago || etiketaDago && (etiketaString.find("ZEN") == string::npos)
	&& (etiketaString.find("IDENT") == string::npos) && (etiketaString.find("ERROM") == string::npos)
	)
      ken_marka_hitzetik( cpAux , cpLema2 ); 
    else
      strcpy(cpAux,cpLema2);
    
    aldTwol = cpAux ;
    
    yyparseAna2Morfsar->add2Gorputza(ALDAERA, aldTwol);
  }

}
;


/* ***********************************************************
 * <MORFEMA>	::  ( <MORFEMA-ALD> <RESTO-ALD> )
 *		|   ( <MORFEMA-NOR> <EZAUGARRIAK> )
 * *********************************************************** */

morfema      : t_paren_ireki morfema_ald resto_ald t_paren_itxi
{
  yyparseAna2Morfsar->add2Gorputza(TWOL,*$<str>2);
}

| t_paren_ireki morfema_nor ezaugarriak t_paren_itxi

{
  yyparseAna2Morfsar->add2Gorputza(TWOL,*$<str>2);
}
;

/* ***********************************************************
 * <MORFEMA-ALD>	::= ( t_morfema t_dolar t_literal )
 * *********************************************************** */

morfema_ald  : t_paren_ireki t_morfema t_dolar t_literal t_paren_itxi /* STwol */
{
  $<str>$ = new string;

  if (edbl_bertsioa < 5) {
    string twol = *$<str>4;
    
    if (!lehenMorfema){
      yyparseAna2Morfsar->morfemaBerria();
      yyparseAna2Morfsar->add2Gorputza(FORMA, formaString);
    }
    lehenMorfema = false;
    
    
    if (twol.find(" ") != string::npos)
      twol.replace(twol.find(" "),1,"_");
    *$<str>$ = twol;
  }
}
;

/* ***********************************************************
 * <MORFEMA-NOR>	::= ( t_morfema t_literal )
 * *********************************************************** */

morfema_nor  : t_paren_ireki t_morfema t_literal t_paren_itxi /* STwol */
{
  $<str>$ = new string;
  if (edbl_bertsioa < 5) {
    string twol = *$<str>3;

    if (!lehenMorfema){
      yyparseAna2Morfsar->morfemaBerria();
      yyparseAna2Morfsar->add2Gorputza(FORMA, formaString);
    }
    lehenMorfema = false;
    
    
    if (twol.find(" ") != string::npos)
      twol.replace(twol.find(" "),1,"_");
    *$<str>$ = twol;
  }
}
;

/* ***********************************************************
 * <EZAUGARRIAK>	::= ( <SARRERA> <BESTEAK> )
 * *********************************************************** */

ezaugarriak  : t_paren_ireki t_paren_ireki  t_aldaera 
{
  if (!lehenMorfema){
    yyparseAna2Morfsar->morfemaBerria();
    yyparseAna2Morfsar->add2Gorputza(FORMA, formaString);
  }
  lehenMorfema = false;
}  
aldaeraosoa t_paren_ireki t_sarrera sarrera sarrera_twol lotura 
{
  
  char cpLema2[LEMA_LUZERA_MAXIMOA];
  char cpHomId[LEMA_LUZERA_MAXIMOA];   /* Homografo-Id-a lortzeko*/
  string twol = *$<str>9;
  string sarreraHBn = *$<str>8;
  char *cpLiteral=strdup( sarreraHBn .c_str() );
  char cpHBn[2];
  lortu_sarrera_homografo( cpLiteral,cpLema2,cpHomId,cpHBn );
  free(cpLiteral);
  
  yyparseAna2Morfsar->add2Gorputza(EDBL_SARRERA, cpLema2);
  
  yyparseAna2Morfsar->add2Gorputza(HOMOGRAFOA,cpHomId);
  yyparseAna2Morfsar->add2Gorputza(HBN_ARAUTUA2,cpHBn);
  
  if (twol.find(" ") != string::npos)
    twol.replace(twol.find(" "),1,"_");
  yyparseAna2Morfsar->add2Gorputza(TWOL,twol);
  
}
besteak t_paren_itxi

| t_paren_ireki t_paren_ireki t_sarrera sarrera 
{

  char cpLema2[LEMA_LUZERA_MAXIMOA];
  char cpHomId[LEMA_LUZERA_MAXIMOA];   /* Homografo-Id-a lortzeko*/
  string sarreraHBn = *$<str>4;
  char *cpLiteral=strdup( sarreraHBn .c_str() );
  char cpHBn[2];
  lortu_sarrera_homografo( cpLiteral,cpLema2,cpHomId,cpHBn );
  free(cpLiteral);
  
  yyparseAna2Morfsar->add2Gorputza(EDBL_SARRERA, cpLema2);
  yyparseAna2Morfsar->add2Gorputza(HOMOGRAFOA,cpHomId);

  if (edbl_bertsioa > 4) {
    yyparseAna2Morfsar->add2Gorputza(HBN_ARAUTUA2,cpHBn);
  }

}
sarrera_twol besteak t_paren_itxi
{
  if (edbl_bertsioa > 4) {
    string twol = *$<str>6;
    
    if (twol.find(" ") != string::npos)
      twol.replace(twol.find(" "),1,"_");
    yyparseAna2Morfsar->add2Gorputza(TWOL,twol);
  }
}
;

lotura : t_paren_ireki t_lhb t_sinbolo t_paren_itxi
{
  $<str>$ = $<str>3;
}
| ezaugarria
{
  /*** edbl_bertsioa < 5 denean */
  $<str>$ = $<str>1;
}
;

aldaeraosoa      : hitzak t_paren_itxi t_paren_ireki t_atwol hitzak t_paren_itxi
{
  if (edbl_bertsioa > 4) {
    string twol = *$<str>5;
    string sarreraHBn = *$<str>1;
    char cpLema2[LEMA_LUZERA_MAXIMOA];
    char cpHomId[LEMA_LUZERA_MAXIMOA];   /* Homografo-Id-a lortzeko*/
    char *cpLiteral=strdup( sarreraHBn .c_str() );
    char cpHBn[2];
    lortu_sarrera_homografo( cpLiteral,cpLema2,cpHomId,cpHBn );
    free(cpLiteral);
        
    yyparseAna2Morfsar->add2Gorputza(EDBL_SARRERA, cpLema2);
    
    yyparseAna2Morfsar->add2Gorputza(HOMOGRAFOA,cpHomId);
    yyparseAna2Morfsar->add2Gorputza(HBN_ARAUTUA2,cpHBn);
    
    if (twol.find(" ") != string::npos)
      twol.replace(twol.find(" "),1,"_");
    yyparseAna2Morfsar->add2Gorputza(TWOL,twol);
  }

}
;

sarrera_twol:  t_paren_ireki t_stwol hitzak t_paren_itxi
{
  $<str>$ = $<str>3;
}
| ezaugarria
{
  $<str>$ = $<str>1;
}
;

/* ***********************************************************
 * <SARRERA>	::= ( t_sarrera hitzak )
 * *********************************************************** */

sarrera : hitzak t_paren_itxi
{
  $<str>$ = $<str>1;
}
;

/* ***********************************************************
 * <HITZAK>      ::= t_sinbolo <HITZAK>
 *               |   t_sinbolo
 * *********************************************************** */

hitzak     : hitzak t_sinbolo
{
  *$<str>$ = *$<str>1 + " " + *$<str>2;
}
| t_sinbolo
{
  *$<str>$ = *$<str>1;
}
| t_anal
{
  *$<str>$ = *$<str>1;
}
| t_sarrera 

{
  *$<str>$ = *$<str>1;
}
;

/* ***********************************************************
 * <BESTEAK>	::= <NORMALAK>
 *		|   <HUTSA> Aurretik kontsumitu bada sarrera_twol edota lotura ez-bukaerakoatan
 * *********************************************************** */

/* Sintaktikoak besteekin batera */
besteak      : normalak
{
  ezaugOrd = 0;
}
|
{
  ezaugOrd = 0;
}
;

/* ***********************************************************
 * <NORMALAK> ::= <NORMALAK> <EZAUGARRIA>
 *            |   <EZAUGARRIA>
 * *********************************************************** */

normalak : normalak ezaugarria
         | ezaugarria
         ;

/* ***********************************************************
 * <EZAUGARRIA>	::= ( t_sinbolo <HITZAK> )
 * *********************************************************** */

ezaugarria    : ezaugarrial
              | ezaugarrian
              ;

ezaugarrial   : t_paren_ireki t_sinbolo_set ezaugarriakfsn t_paren_itxi
              | t_paren_ireki t_sinbolo_list ezaugarriakn t_paren_itxi
              | t_paren_ireki t_sinbolo_list_sym sintaktikoak t_paren_itxi
              | t_paren_ireki t_sinbolo ezaugarriakfsn t_paren_itxi
              ;

ezaugarriakfsn  : ezaugarriakfsn ezaugarriafsn
{
  $<str>$ = $<str>0;
}
|  ezaugarriafsn
{
  $<str>$ = $<str>0;
}
;


ezaugarriakn  : ezaugarriakn ezaugarrian
              | ezaugarrian
              ;

fsezaugarriak : t_sinbolo { /*** mota jakiteko aurretik agertuko den Estandarrak/Hobetsiak */  }
              | t_sarrera { /*** mota jakiteko aurretik agertuko den Estandarrak/Hobetsiak */  }
              ;

/*** Kontuz!! ezaugarriafsn.hizena atributu heredatua $<str>0              */
/*** ezaugarriakfsn-k erabiliko du aurretik dagoen t_sinbolo-ren balioa    */
/*** Estandarrak/Hobetsiak balioa erabiliko du atzetik datozen guztientzat */
/*** Gero ezaugOrd aldagaiarekin zenbatu egingo dira                       */

ezaugarriafsn : t_paren_ireki fsezaugarriak hitzak t_paren_itxi
{
  string sarreraHBn = *$<str>3;
  char cpLema2[LEMA_LUZERA_MAXIMOA];
  char cpHomId[LEMA_LUZERA_MAXIMOA];   /* Homografo-Id-a lortzeko*/
  char *cpLiteral= strdup( sarreraHBn.c_str() );
  char cpHBn[2];
  lortu_sarrera_homografo( cpLiteral,cpLema2,cpHomId,cpHBn );
  free(cpLiteral);


  ezaugOrd++;

  /*** Erreferentzia motakoak (Gako+HBn) 5 bertsioan*/
  stringstream ezaugIzen;
  ezaugIzen << *$<str>0 << ezaugOrd << "/" << EDBL_SARRERA;
  yyparseAna2Morfsar->add2Gorputza(ezaugIzen.str(), cpLema2);
  ezaugIzen.str(std::string()) ;
  ezaugIzen << *$<str>0 << ezaugOrd << "/" << HOMOGRAFOA;
  yyparseAna2Morfsar->add2Gorputza(ezaugIzen.str(),cpHomId);

  if (edbl_bertsioa > 4) {
    ezaugIzen.str(std::string()) ;
    ezaugIzen << *$<str>0 << ezaugOrd << "/" << HBN_ARAUTUA2;
    yyparseAna2Morfsar->add2Gorputza(ezaugIzen.str(),cpHBn);
  }

}
;

ezaugarrian   : t_paren_ireki t_erroa hitzak t_paren_itxi
{
  string strNameOsa = *$<str>2;
  char cpLema2[LEMA_LUZERA_MAXIMOA];
  char cpHomId[LEMA_LUZERA_MAXIMOA];   /* Homografo-Id-a lortzeko*/
  char *cpLiteral=strdup( $<str>3->c_str() );
  char cpHBn[2];
  lortu_sarrera_homografo( cpLiteral,cpLema2,cpHomId,cpHBn );
  free(cpLiteral);
  string strValAux( cpLema2 );
  if (cpLema2[0] == '7') {
    cpLema2[0] = '*';
  }
  stringstream ezaugIzen;
  ezaugIzen << *$<str>2 << "/" << EDBL_SARRERA;
  yyparseAna2Morfsar->add2Gorputza(ezaugIzen.str(), cpLema2);
  ezaugIzen.str(std::string()) ;
  ezaugIzen << *$<str>2 << "/" << HOMOGRAFOA;
  yyparseAna2Morfsar->add2Gorputza(ezaugIzen.str(),cpHomId);

}
| t_paren_ireki t_sinbolo hitzak t_paren_itxi
{		  
  if ( (*$<str>3 == "-") || (*$<str>3 == "+") ){
    yyparseAna2Morfsar->add2Gorputza(*$<str>2,*$<str>3); /* komatxo bikoitzarekin */
  } 
  else {
    if ( $<str>2->find("OSA") != string::npos ) {
      char cpLema2[LEMA_LUZERA_MAXIMOA];
      char cpHomId[LEMA_LUZERA_MAXIMOA];   /* Homografo-Id-a lortzeko*/
      char *cpLiteral=strdup( $<str>3->c_str() );
      char cpHBn[2];
      lortu_sarrera_homografo( cpLiteral,cpLema2,cpHomId,cpHBn );
      free(cpLiteral);

      /*** Jarri aurretik OSA1 OSA2 */
      stringstream ezaugIzen;
      ezaugIzen << *$<str>2 << "/" << EDBL_SARRERA;
      yyparseAna2Morfsar->add2Gorputza(ezaugIzen.str(), cpLema2);
      ezaugIzen.str(std::string()) ;
      ezaugIzen << *$<str>2 << "/" << HOMOGRAFOA;
      yyparseAna2Morfsar->add2Gorputza(ezaugIzen.str(),cpHomId);
      
      if (edbl_bertsioa > 4) {
	ezaugIzen.str(std::string()) ;
	ezaugIzen << *$<str>2 << "/" << HBN_ARAUTUA2;
	yyparseAna2Morfsar->add2Gorputza(ezaugIzen.str(),cpHBn);
      }
    } 
    else {
      yyparseAna2Morfsar->add2Gorputza(*$<str>2,*$<str>3,true);
    }

  }
}
;

/* ***********************************************************
 * <SINTAKTIKOAK>	::= <SINTAKTIKOAK> <FUNTZIOA>
 *	        	|   NULL
 * *********************************************************** */

sintaktikoak : sintaktikoak funtzioa
             |
             ;

/* ***********************************************************
 * <FUNTZIOA>	::= ( t_funtzioak t_sinbolo )
 * *********************************************************** */

funtzioa    : t_paren_ireki t_funtzioak t_sinbolo t_paren_itxi
{
  ezaugOrd++;
  stringstream ezaugIzen;
  ezaugIzen << FSList << ezaugOrd;
  yyparseAna2Morfsar->add2Gorputza(ezaugIzen.str(),*$<str>3);
}
;


%%

/* ***************************  */


/*  **************************  */
#include "lex.ana2morfsar.cc"

void ana2morfsarerror(const char *msg) {  
  fprintf( stderr , "ana2morfsar.y: %s ==> lerro zenbakia: %d -%s-\n" , msg , ana2morfsar_lerro_kop , ana2morfsartext );
}

/*  **************************  */

void  lortu_sarrera_homografo( char *cpLiteral, char *cpLema2, char *cpHomId, char *cpHBn ) {
  /* cpLiteral = cpLema--cpHomId; */

  int luz = strlen(cpLiteral)-1;
  cpLema2[0] = '\0';
  cpHomId[0] = '\0';
  cpHBn[0] = '\0';
  if (cpLiteral[luz] == '+' || cpLiteral[luz] == '-') {
    /* HBn ezaugarri dagoenean, kopiatu emaitzan eta kendu --[-+] */
    cpHBn[0] =cpLiteral[luz];
    cpHBn[1] = '\0';
    cpLiteral[luz-2] = '\0';
    luz=luz-3;
  }
  strcpy(cpLema2,cpLiteral);
  while (luz > 0 && cpLiteral[luz] != '-') luz--;
  if (luz != 0 && cpLiteral[luz-1]=='-') {
    strcpy(cpHomId,&(cpLiteral[luz+1]));
    cpLema2[luz-1] = '\0';
  }
  else {  /* Homografo-Id ez badago, defektuz 0 eman */
    cpHomId[0] = '0';
    cpHomId[1] = '\0';
  }
}

