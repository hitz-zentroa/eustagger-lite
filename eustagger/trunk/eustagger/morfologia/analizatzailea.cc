#include <stdio.h>
#include <string>
#include <map>
#include <valarray>
#include <strings.h>
#include <stdlib.h>
#define MIN2(a,b) (a<b)?a:b
#include "analizatzailea.h"
#ifndef _USE_FOMA_
#include "erab_lex.h"
//#else
//#include "erab_lex.h"
#endif
#include "filtro.h"
#include "getenvvar.h"

extern int kendu_marka_lex(char *,char *,int);
extern int gehitu_marka_lex(char *,char *);
extern int ken_maiuskulak (char *str);
extern int ken_majusk_marratxo(char *st);
#ifndef _USE_FOMA_
extern int analizatu_hitza(int non, char *hitza,char lemak[][LUZMAXAN]);
extern int ireki_erab_morfemategia(char *,int,int);
#endif
extern int bilatu_erab_guztiak(char *);
extern void bihur_asteris_maj(char *,char *);
extern void bihur_maj_asteris(char *,char *);
extern void Maiuskulak(char *, char *, char *);
extern char *eman_azken_zifra(char *);
//extern void aztertu_zenbakia(char *,char *);
//extern "C" {
#ifndef _USE_FOMA_
#include "xfl_fun.h"
#include "anali_xerox.h"
#endif // _USE_FOMA
#include "maiztasun_handikoak.h"
//}
#ifdef DMALLOC
#include "dmalloc.h"
#endif

void analizatzailea::amaierakoak() {
#ifdef _USE_FOMA_
  //  transFoma.amaitu_transd_guztiak(); // Ez dabil ondo
#else
  xfl_amaitu_transd_guztiak();
#endif
}
void analizatzailea::hasieraketak(int sar_lem, int lex_uzei, int bigarren, int ez_est, int erab_lex, string &lexiko_izena, int parentizatua, int deslokala){
  char izena[7][200];
  int n,ondo;
  char ber[200];

  lexiko_uzei = lex_uzei;
  Sarrera_berezia = sar_lem;
  bigarren_aukera = bigarren;
  ez_estandarrak = ez_est;
  lex_ald = erab_lex;
  irteera_parentizatua= parentizatua;
  deslok = deslokala;
  
/*  lex_ald=1;
  lexiko_izena = "lex_erab_4.4.lex"; //GOGORATU HAU KENTZEAZ!!!*/

#ifndef _USE_FOMA_
  tmp = (char *)malloc(200*sizeof(char));
  tmp[0] = '\0';
  if (lex_ald) {
    strcpy(tmp,lexiko_izena.c_str());
    ondo = ireki_erab_morfemategia(tmp,0,IMREKIN);
    if (!ondo) lex_ald=0;
  }
#else
	#define IMREKIN 0
  if (lex_ald) {
    ondo = transFoma.ireki_erab_lex(lexiko_izena,0,IMREKIN);
    if (!ondo) {
      lex_ald=0;
      fprintf(stderr,"Arazoa %s lexikoa kargatzen\n", lexiko_izena.c_str());
    }
    else {
      fprintf(stderr,"Ondo kargatu dut erabiltzailearen lexikoa\n");
    }
  }
#endif // not _USE_FOMA_
  if (lexiko_uzei) {
#ifdef _USE_FOMA_
    // HAUEK EZ DAUDE ETA EZ DUTE EGON BEHAR
    strcpy(izena[0],"xuxen-IM_uzei.fst");
    strcpy(izena[1],"xuxen-IM_ald_uzei.fst");
    strcpy(izena[2],"xuxen-IM_berez_uzei.fst.");
#else
    strcpy(izena[0],"xuxenII_IM_uzei.fst");
    strcpy(izena[1],"xuxenII_IM_ald_uzei.fst");
    strcpy(izena[2],"xuxenII_IM_berez_uzei.fst.");
#endif
  }
  else {
#ifdef _USE_FOMA_
    strcpy(izena[0],"xuxen-IM_foma.fst.");
#else
    strcpy(izena[0],"xuxenII_IM.fst.");
#endif
#ifndef _USE_FOMA_ // MOMENTUZ ALDAERAK EZ
#ifndef __BRIDGE_VARIANTS__
    strcpy(izena[1],"xuxenII_IM_ald.fst.");
    strcpy(izena[3],"xuxenII_IM_ald_std.fst.");
    strcpy(izena[4],"xuxenII_ald_banatz.fst.");
    strcpy(izena[5],"xuxenII_IM_ald_banatz.fst.");
#endif // __BRIDGE_VARIANTS__
#endif // _USE_FOMA_

#ifdef _USE_FOMA_
    strcpy(izena[2],"xuxen-IM_foma_berez.fst.");
#else
    strcpy(izena[2],"xuxenII_IM_berez.fst.");
#endif
  }
  string tmpV = "4.4.9";
  
  char *tmp = strdup(tmpV.c_str());
  if (!lexiko_uzei) {
    strcat(izena[0],tmp);
#ifndef __BRIDGE_VARIANTS__
    strcat(izena[1],tmp);
    strcat(izena[3],tmp);
    strcat(izena[4],tmp);
    strcat(izena[5],tmp);
#endif // __BRIDGE_VARIANTS__

    /*** UZEIkoen lexikoarekin batera, lexikorik gabekoen automata orokorra */
    strcat(izena[2],tmp);
    strcpy(ber,tmp);
    ber[1] = '\0';
    edbl_bertsioa = atoi(tmp);
    free(tmp);
  }
  else {
    fprintf(stderr,"Aukeratu erabili nahi dituzun datuak\n");
    exit(1);
  }
  
  if (!Sarrera_berezia) {
    fprintf(stderr,"Hasieraketa...\n");
  }
#ifdef _USE_FOMA_
  n=transFoma.hasieratu_transd(izena[0],ESTANDARRA);
#else
  n=xfl_hasieratu_transd(izena[0],ESTANDARRA);
#endif //_USE_FOMA_
  if(n==0) fprintf(stderr,"***********ERROREA %s LEXIKOAN*************\n",izena[0]);
  if (!Sarrera_berezia) {
    fprintf(stderr,"estandarra bukatuta\n");
  }
#ifndef _USE_FOMA_
#ifndef __BRIDGE_VARIANTS__
  n=xfl_hasieratu_transd(izena[1],ALDAERAK);
  if(n==0) fprintf(stderr,"***********ERROREA %s LEXIKOAN*************\n",izena[1]);
  if (!Sarrera_berezia) {
    fprintf(stderr,"aldaerena bukatuta\n");
  }
#endif // __BRIDGE_VARIANTS__
#endif //_USE_FOMA_

#ifdef _USE_FOMA_
  n=transFoma.hasieratu_transd(izena[2],LEX_GABE);
#else
  n=xfl_hasieratu_transd(izena[2],LEX_GABE);
#endif //_USE_FOMA_
  if(n==0) fprintf(stderr,"***********ERROREA %s LEXIKOAN*************\n",izena[2]);
  if (!Sarrera_berezia) {
    fprintf(stderr,"berezia bukatuta\n");
  }
#ifndef _USE_FOMA_
#ifndef __BRIDGE_VARIANTS__
  if (!lexiko_uzei) {
    n=xfl_hasieratu_transd(izena[3],ALD_STD);
    if(n==0) fprintf(stderr,"***********ERROREA %s LEXIKOAN*************\n",izena[3]);
    if (!Sarrera_berezia) {
      fprintf(stderr,"aldaera+estandarra bukatuta\n");
    }
    n=xfl_hasieratu_transd(izena[4],ALD_BANA);
    if(n==0) fprintf(stderr,"***********ERROREA %s LEXIKOAN*************\n",izena[4]);
    if (!Sarrera_berezia) {
      fprintf(stderr,"aldaera banatzailea bukatuta\n");
    }
    n=xfl_hasieratu_transd(izena[5],ALD_BANA_ANA);
    if(n==0) fprintf(stderr,"***********ERROREA %s LEXIKOAN*************\n",izena[5]);
    if (!Sarrera_berezia) {
      fprintf(stderr,"aldaera banaketaren analizatzailea bukatuta\n");
    }
  }
#endif // __BRIDGE_VARIANTS__
#endif //_USE_FOMA_

  if (!Sarrera_berezia) {
    fprintf(stderr,"Hasieraketa bukatuta\n");
  }
  
  //  if (bigarren_aukera) {
    maiztasun_handikoak = 1;
    ondo = ireki_maiztasun_handikoak();
    if (!ondo) {
      fprintf(stderr,"Errorea Maiztasun handikoak irekitzean\n");
      maiztasun_handikoak = 0;
    }
    //  }
}


void analizatzailea::lortu_aurrizki_kar_ber(char *hitza,char *lema_ident) {
  char hitzkopia[LUZMAXAN];

  lema_ident[0] = '\0';
  strcpy(lema_ident,forma_ident);
  hitzkopia[0] = '\0';
  strcpy(hitzkopia,hitza);
  bihur_asteris_maj(hitzkopia,hitzkopia);
  lema_ident[strlen(forma_ident)-strlen(hitzkopia)] = '\0';

}


// void analizatzailea::gehitu_aldaera(char analisia[], char aldaera[]) {
//   char lerroa[LUZMAXAN], *phasi;
//   strcpy(lerroa,analisia);
//   phasi=strstr(analisia,"[[");
//   lerroa[strlen(analisia)-strlen(phasi)] = '\0';
//   if (lerroa[0] != '+' && (strstr(lerroa,"[ald_") == NULL) ) { 
//     strcat(lerroa,"[ald_");
//     strcat(lerroa,aldaera);
//     strcat(lerroa,"]");
//     strcat(lerroa,phasi);
//     strcpy(analisia,lerroa);
//   }
// }

void analizatzailea::lortu_lema_ident(char *hitza,char *lema_ident) {
  char hitzkopia[LUZMAXAN], hitzkopia2[LUZMAXAN],hurrengoak[LUZMAXAN];
  char *hktmp;
  
  hitzkopia[0] = '\0';
  strcpy(hitzkopia,forma_ident);
  strcpy(hitzkopia2,forma_ident);
  if ((hktmp=strtok(hitzkopia,ZIFRA)) != NULL) {
    if (strcmp(hktmp,forma_ident) != 0) {
      hurrengoak[0] = '\0';
      strcpy(hurrengoak,&hitzkopia2[strlen(hktmp)]);
      char *atzizkirik;
      if ((atzizkirik=strpbrk(hurrengoak,ALF)) != NULL) {
	strcpy(lema_ident,forma_ident);
	// hitza = c[co]+atzizkia LEMA GENERIKOA
	lema_ident[strlen(forma_ident)-strlen(hitza)+strlen("cc")] = '\0';
      }
      else
	if (strspn(hurrengoak,ZIFRA) == strlen(hurrengoak)) {
	  lema_ident[0] = '\0';
	  strcpy(lema_ident,forma_ident);
	  lema_ident[strlen(forma_ident)-strlen(hitza)+strlen("cc")] = '\0';
	}
	else {
	  lema_ident[0] = '\0';
	  strcpy(lema_ident,forma_ident);
	  lema_ident[strlen(forma_ident)-strlen(hitza)+strlen("cc")] = '\0';
	}
    }
    else {
      lema_ident[0] = '\0';
      strcpy(lema_ident,forma_ident);
      lema_ident[strlen(forma_ident)-strlen(hitza)+strlen("cc")] = '\0';
    }
  }
  else {
    lema_ident[0] = '\0';
    strcpy(lema_ident,forma_ident);
    lema_ident[strlen(forma_ident)-strlen(hitza)+strlen("cc")] = '\0';
  }
}

void analizatzailea::lortu_lema_zen_dek(char *lema_ident) {
  char hitzkopia[LUZMAXAN],hitzkopia2[LUZMAXAN],aurrizkia[LUZMAXAN],atzizkia[LUZMAXAN];
  char *hktmp;
  
  aurrizkia[0] = '\0';
  lema_ident[0] = '\0';
  hitzkopia[0] = '\0';
  strcpy(hitzkopia,forma_ident);
  hitzkopia2[0] = '\0';
  strcpy(hitzkopia2,forma_ident);
  if (!errom_da) {
    strcpy(hitzkopia,eman_azken_zifra(forma_ident));
    if (strlen(hitzkopia) != strlen(forma_ident)) {
      strcpy(aurrizkia,forma_ident);
      aurrizkia[strlen(forma_ident)-strlen(hitzkopia)] = '\0';
      strcpy(hitzkopia2,&forma_ident[strlen(aurrizkia)]);
    }
    if ((hktmp=strtok(hitzkopia,ZIFRA)) != NULL) {
      if (strcmp(hktmp,hitzkopia2) != 0) {
	strcpy(lema_ident,hitzkopia2);
	lema_ident[strlen(hitzkopia2)-strlen(hktmp)] = '\0';
      }
      else {
	strcpy(lema_ident,hitzkopia2);
      }
    }
    else {
        strcpy(lema_ident,hitzkopia2);
    }
    if (strlen(aurrizkia) != 0) {
      strcpy(hitzkopia,lema_ident);
      strcpy(lema_ident,aurrizkia);
      strcat(lema_ident,hitzkopia);
    }
  }
  else {
    Maiuskulak(forma_ident,atzizkia,lema_ident);
    if (strlen(lema_ident) == 0) strcpy(lema_ident,forma_ident);
  }
}

void analizatzailea::inprimatu_ident_analisia(char *analisiaorig, int *ident_analisia, char *lema_ident, vector<string>* emaitza) {
  //  char *phasi,*padoin;
  int SARda = 0;
  char analisia[LUZMAXAN];
  analisia[0] = '\0';
  strcpy(analisia,analisiaorig);

  // Filtratu soilik IZE direnak eta lema generikoa dutenak lema generikoak: cc ala co
  if ((strstr(analisia,"KAT_IZE") != NULL ) && analisia[strlen("cc")] == '[') {
    char lerroa_ident[LUZMAXAN];
    if (strstr(analisia,"[[SAR_aaaaa") != NULL) {
      SARda = 1;
    }

    string analisi_ident = bihur.aldatuBim(analisia,lema_ident);
    analisi_ident = bihur.aldatuSarInfo(analisi_ident,lema_ident,SARda);


//     if (strstr(phasi+strlen("][KAT_IZE][AZP_ARR]]"),"KAT_IZE") == NULL &&
// 	strstr(phasi+strlen("][KAT_IZE][AZP_ARR]]"),"KAT_ADI") == NULL &&
// 	strstr(phasi+strlen("][KAT_IZE][AZP_ARR]]"),"KAT_ADJ") == NULL) { 
//       // IZE + MAR + IZE/ADI/ADJ ez onartzeko

    strcpy(lerroa_ident,analisi_ident.c_str());
    
    if(irteera_nola == ESTANDAR_AN || irteera_nola == ESTANDAR_PIPE)
      if (Sarrera_berezia) {

	if (irteera_parentizatua) {
	  string lispler;
	  lispler=bihur.lispifikatu(lerroa_ident,ident_da,zen_da,zen_dek_da,errom_da);
	  printf("\n%cG\n  ((anal %d)\n   (%s))",'%',*ident_analisia,lispler.c_str());
	}
	else
	  printf("\n%cG\n  ((anal %d)\n   (%s))",'%',*ident_analisia,lerroa_ident);
      }
      else
	printf("G %d\t%s\n",*ident_analisia,lerroa_ident);
    else {
      char lerr[LUZMAXAN];
      if (Sarrera_berezia){
	if (irteera_parentizatua) {
	  string lispler;
	  lispler=bihur.lispifikatu(lerroa_ident,ident_da,zen_da,zen_dek_da,errom_da);
	  sprintf(lerr,"\n%cG\n  ((anal %d)\n   (%s))",'%',*ident_analisia,lispler.c_str());
	}
	else
	  sprintf(lerr,"\n%cG\n  ((anal %d)\n   (%s))",'%',*ident_analisia,lerroa_ident);
      }
      else
	sprintf(lerr,"G %d\t%s\n",*ident_analisia,lerroa_ident);
      emaitza->push_back(lerr);
    }
    *ident_analisia = *ident_analisia+1;
  }
}

void analizatzailea::inprimatu_lexgabeko_analisia(char *analisiaorig, int *i,char *lema_ident, vector<string>* emaitza) {
  char lerroa_gabekoa[LUZMAXAN];

  strcpy(lerroa_gabekoa,analisiaorig);

  if(irteera_nola == ESTANDAR_AN || irteera_nola == ESTANDAR_PIPE)
    if (Sarrera_berezia){
      if (irteera_parentizatua) {
	string lispler;
	lispler=bihur.lispifikatu(lerroa_gabekoa,ident_da,zen_da,zen_dek_da,errom_da);
	printf("\n%cG\n  ((anal %d)\n   (%s))",'%',*i,lispler.c_str());
      }
      else
	printf("\n%cG\n  ((anal %d)\n   (%s))",'%',*i,lerroa_gabekoa);
    }
    else
      printf("G %d\t%s\n",*i,lerroa_gabekoa);
  else {
    char lerr[LUZMAXAN];
    lerr[0] = '\0';
    if (Sarrera_berezia){
      if (irteera_parentizatua) {
	string lispler;
	lispler=bihur.lispifikatu(lerroa_gabekoa,ident_da,zen_da,zen_dek_da,errom_da);
	sprintf(lerr,"\n%cG\n  ((anal %d)\n   (%s))",'%',*i,lispler.c_str());
      }
      else
	sprintf(lerr,"\n%cG\n  ((anal %d)\n   (%s))",'%',*i,lerroa_gabekoa);
    }
    else
      sprintf(lerr,"G %d\t%s\n",*i,lerroa_gabekoa);
    emaitza->push_back(lerr);
  }
  *i = *i + 1;

}

void analizatzailea::inprimatu_aldaera_analisia( char *analisiaorig, int *i, int dist, char *lema_ident, vector<string>* emaitza ){
  char *phasi,*pbuk;
  char analisia[LUZMAXAN];

  analisia[0] = '\0';
  strcpy(analisia,analisiaorig);

  if (zen_dek_da || zen_da || errom_da) {
    if ( lema_ident[0] == 'I' && 
	 ( lema_ident[1] == '.' || lema_ident[1] == '\0') &&
	 !strstr(analisia,"DET") && ( !strstr(analisia,"IZE") || !strstr(analisia,"bat[") )
	 ) return;
    if ( lema_ident[0] == '1' && 
	 ( lema_ident[1] == '.' || lema_ident[1] == '\0') &&
	 !strstr(analisia,"DET") && ( !strstr(analisia,"IZE") || !strstr(analisia,"bat[") )
	 ) return;
    char lerroa_ident[LUZMAXAN];
    lerroa_ident[0] = '\0';
    strcpy(lerroa_ident,lema_ident);
    phasi=strstr(analisia,"[[");
    if (strstr(phasi,"[[SAR_") != NULL) {
      if ( (pbuk = strstr(phasi+strlen("[[SAR_"),"]")) != NULL) {
	if (strstr(analisia,"[ald_") == NULL) {
	  strcat(lerroa_ident,"[ald_");
	  strcat(lerroa_ident,lema_ident);
	  strcat(lerroa_ident,"]");
	}
	strcat(lerroa_ident,"[[SAR_");
	strcat(lerroa_ident,lema_ident);
	phasi = pbuk;
      }
    }
    if (strstr(phasi,"[[Sarrera_") != NULL) {
      if ( (pbuk = strstr(phasi+strlen("[[Sarrera_"),"]")) != NULL) {
	if (strstr(analisia,"[ald_") == NULL) {
	  strcat(lerroa_ident,"[ald_");
	  strcat(lerroa_ident,lema_ident);
	  strcat(lerroa_ident,"]");
	}
	strcat(lerroa_ident,"[[Sarrera_");
	strcat(lerroa_ident,lema_ident);
	strcat(lerroa_ident,"--0");
 	if (edbl_bertsioa>4)
 	  strcat(lerroa_ident,"---"); // HBn arautu gabe
	phasi = pbuk;
      }
    }
    strcat(lerroa_ident,phasi);
    // prozesatu analisia lema aldatzeko
    strcpy(analisia,lerroa_ident);
  }

  if(irteera_nola == ESTANDAR_AN || irteera_nola == ESTANDAR_PIPE)
    if (Sarrera_berezia) {
      if (irteera_parentizatua) {
	string lispler;
	lispler=bihur.lispifikatu(analisia,ident_da,zen_da,zen_dek_da,errom_da);
	printf("\n%cT:err0:%d\n  ((anal $ %d)\n   (%s))",'%',dist,*i,lispler.c_str());
      }
      else
	printf("\n%cT:err0:%d\n  ((anal $ %d)\n   (%s))",'%',dist,*i,analisia);
    }
    else
      printf("T:%d %d\t%s\n",dist,*i,analisia);
  else{
    char lerr[LUZMAXAN];
    lerr[0] = '\0';
    if (Sarrera_berezia){
      if (irteera_parentizatua) {
	string lispler;
	lispler=bihur.lispifikatu(analisia,ident_da,zen_da,zen_dek_da,errom_da);
	sprintf(lerr,"\n%cT:err0:%d\n  ((anal $ %d)\n   (%s))",'%',dist,*i,lispler.c_str());
      }
      else
	sprintf(lerr,"\n%cT:err0:%d\n  ((anal $ %d)\n   (%s))",'%',dist,*i,analisia);
    }
    else
      sprintf(lerr,"T:%d %d\t%s\n",dist,*i,analisia);
    emaitza->push_back(lerr);
  }
  *i = *i + 1;
}

void analizatzailea::inprimatu_estandar_analisia( char *analisiaorig, int *i, char *lema_ident, vector<string>* emaitza ){
  char *phasi,*pbuk;
  char analisia[LUZMAXAN];

  analisia[0] = '\0';
  strcpy(analisia,analisiaorig);

  if (zen_dek_da || zen_da || errom_da) {
    if ( lema_ident[0] == 'I' && 
	 ( lema_ident[1] == '.' || lema_ident[1] == '\0') &&
	 !strstr(analisia,"DET") && ( !strstr(analisia,"IZE") || !strstr(analisia,"bat[") )
	 ) return;
    if ( lema_ident[0] == '1' && 
	 ( lema_ident[1] == '.' || lema_ident[1] == '\0') &&
	 !strstr(analisia,"DET") && ( !strstr(analisia,"IZE") || !strstr(analisia,"bat[") ) 
	 ) return;
    char lerroa_ident[LUZMAXAN];
    lerroa_ident[0] = '\0';
    strcpy(lerroa_ident,lema_ident);
    phasi=strstr(analisia,"[[");
    if (strstr(phasi,"[[SAR_") != NULL) {
      if ( (pbuk = strstr(phasi+strlen("[[SAR_"),"]")) != NULL) {
	strcat(lerroa_ident,"[[SAR_");
	strcat(lerroa_ident,lema_ident);
	phasi = pbuk;
      }
    }
    if (strstr(phasi,"[[Sarrera_") != NULL) {
      if ( (pbuk = strstr(phasi+strlen("[[Sarrera_"),"]")) != NULL) {
	strcat(lerroa_ident,"[[Sarrera_");
	strcat(lerroa_ident,lema_ident);
	strcat(lerroa_ident,"--0");
 	if (edbl_bertsioa>4)
 	  strcat(lerroa_ident,"---"); // HBn arautu gabe
	phasi = pbuk;
      }
    }
    strcat(lerroa_ident,phasi);
    // prozesatu analisia lema aldatzeko
    strcpy(analisia,lerroa_ident);
  }

  if(irteera_nola == ESTANDAR_AN || irteera_nola == ESTANDAR_PIPE)
    if (Sarrera_berezia){
      if (irteera_parentizatua) {
	string lispler;
	lispler=bihur.lispifikatu(analisia,ident_da,zen_da,zen_dek_da,errom_da);
	printf("\n%cA\n  ((anal %d)\n   (%s))",'%',*i,lispler.c_str());
      }
      else
	printf("\n%cA\n  ((anal %d)\n   (%s))",'%',*i,analisia);
    }
    else 
      printf("A %d\t%s\n",*i,analisia);
  else{
    char lerr[LUZMAXAN];
    lerr[0] = '\0';
    if (Sarrera_berezia) {
      if (irteera_parentizatua) {
	string lispler;
	lispler=bihur.lispifikatu(analisia,ident_da,zen_da,zen_dek_da,errom_da);
	sprintf(lerr,"\n%cA\n  ((anal %d)\n   (%s))",'%',*i,lispler.c_str());
      }
      else
	sprintf(lerr,"\n%cA\n  ((anal %d)\n   (%s))",'%',*i,analisia);
    }
    else 
      sprintf(lerr,"A %d\t%s\n",*i,analisia);
    emaitza->push_back(lerr);
  }
  *i = *i + 1;
}

void analizatzailea::inprimatu_goiburukoa( char *hitza, char mota, vector<string>* emaitza ) {
  if (Sarrera_berezia) {
    if (irteera_nola == ESTANDAR_AN || irteera_nola == ESTANDAR_PIPE)
      printf("((forma \"%s\")",hitza);
    else {
      char lerr[LUZMAXAN];
      lerr[0] = '\0';
      sprintf(lerr,"((forma \"%s\")",hitza);
      emaitza->push_back(lerr);
    }
  }
  else {
    if(irteera_nola == ESTANDAR_AN || irteera_nola == ESTANDAR_PIPE)
      printf("%c\n%s\n",mota,hitza);
    else {
      char lerr[LUZMAXAN];
      lerr[0] = '\0';
      sprintf(lerr,"%c\n%s\n",mota,hitza);
      emaitza->push_back(lerr);
    }
  }
}

vector<string> analizatzailea::analizatu(int modua, vector<string> *sarrerako_taula) {
  char hitza[LUZMAXAN];
  vector<string> emaitza;
  int indizea=0;
  int hm=-1;
  irteera_nola = modua;

  if (Sarrera_berezia)
    lortu_hitza(hitza,sarrerako_taula,&emaitza,&indizea);
  else 
    hm=scanf("%s",hitza) ;

  while ((Sarrera_berezia && strlen(hitza)) || (!Sarrera_berezia && !feof(stdin) && hm != -1))
    {
      analizatu_hitza_trans(hitza,modua,sarrerako_taula,&emaitza,&indizea);

      if (Sarrera_berezia)
	lortu_hitza(hitza,sarrerako_taula,&emaitza,&indizea);
      else 
	hm=scanf("%s",hitza) ;
    }

  if (Sarrera_berezia) {
    lortu_hitza(hitza,sarrerako_taula,&emaitza,&indizea);
    if (strlen(hitza) > 0)
      analizatu_hitza_trans(hitza,modua,sarrerako_taula,&emaitza,&indizea);
  }
  /* fomaMorf klaseak destruktoran egiten du */
  /*  xfl_amaitu_transd_guztiak(); */
  return(emaitza);
}


void analizatzailea::analizatu_hitza_trans(char hitza[], int modua, vector<string> *sarrerako_taula,vector<string> *emaitza,int *indizea) {
  char hitza2[LUZMAXAN];
  char anal[ANMAX][LUZMAXAN];
  int i,m,m_aur=0;
  char motak[ANMAX];
  char lema_ident[LUZMAXAN];
  int ident_analisia = 1, beste_analisia = 1;
  int distan[ANMAX];

  irteera_nola = modua;

  if (ident_da)  // lortu lema_ident
    lortu_lema_ident(hitza,lema_ident);
  if ( zen_dek_da || zen_da || errom_da)
    lortu_lema_zen_dek(lema_ident);
  if (kar_ber)
    lortu_aurrizki_kar_ber(hitza,lema_ident);
  ident_analisia = 1;
  beste_analisia = 1;
  for (int d=0; d<ANMAX; d++) distan[d] = 0;
  if (ident_da)
    m=analizatu_aukerak_hitza(bigarren_aukera,LEX_GABE,hitza,anal,motak,distan);
  else
    m=analizatu_aukerak_hitza(bigarren_aukera,ESTANDARRA,hitza,anal,motak,distan);
  if (m) {
    if (ident_da || zen_dek_da || zen_da || errom_da) {
      inprimatu_goiburukoa(forma_ident, 'A', emaitza);
      ident_analisia = 1;
    }
    else {
      if (irteera_parentizatua) {
	string shitza = bihur.bihurtu_xerox_lemati(hitza);
	strcpy(hitza,shitza.c_str());
      }
      inprimatu_goiburukoa(hitza, 'A', emaitza);
      beste_analisia = 1;
      if (m>2 && deslok) { // non == ESTANDARRA baina ez da ident edo horrelako bat
	m = bihur.desanbEratorpena(m,anal,motak,distan);
	// 	    m = bihur.desanbEstandar(m,anal,motak,distan,hitza);
      }
    } 
    
    // hemen analisiaren emaitzak idazten hasten da hasten da
    for (i=0;i<m; i++) {
      if (ident_da)
	inprimatu_ident_analisia(&anal[i][0],&ident_analisia/*,distan[i]*/,lema_ident,emaitza);
      else
	if (motak[i] == 'T') {
	  inprimatu_aldaera_analisia(&anal[i][0],&beste_analisia,distan[i],lema_ident,emaitza);
	}
	else 
	  if (motak[i] == 'G')
	    inprimatu_lexgabeko_analisia(&anal[i][0],&beste_analisia,lema_ident,emaitza);
	  else  // estandarra
	    inprimatu_estandar_analisia(&anal[i][0],&beste_analisia,lema_ident,emaitza);
    } 
    if (errom_da) {
      int m_lag;
      char hitza2[LUZMAXAN];
      strcpy(hitza2,lema_ident);
      bihur_maj_asteris(hitza2,hitza2);
#ifdef _USE_FOMA_
      m_lag=transFoma.analizatu_hitza(ESTANDARRA,hitza2,anal);
#else
      m_lag=analizatu_hitza(ESTANDARRA,hitza2,anal);
#endif
      if (m_lag>2 && deslok) { // non == ESTANDARRA
	m_lag = bihur.desanbEratorpena(m_lag,anal,motak,distan);
	// 	    m_lag = bihur.desanbEstandar(m_lag,anal,motak,distan,hitza);
      }
      if (m_lag) {
	errom_da = 0;
	for (i=0;i<m_lag; i++) {
	  if (strlen(lema_ident) == 1 && strstr(&anal[i][0],"[KAT_IZE]") != NULL)
	    inprimatu_estandar_analisia(&anal[i][0],&beste_analisia,lema_ident,emaitza);
	  else
	    inprimatu_estandar_analisia(&anal[i][0],&beste_analisia,lema_ident,emaitza);
	}
	errom_da = 1;
      }
    }
  }
  // Erabiltzailearen lexikoan begiratu eta inprimatzen ditu analisiak estandarrak balira bezala
#ifndef _USE_FOMA_
  if (lex_ald) {
    m = analizatuErabLex(hitza,m,anal,&beste_analisia,lema_ident,emaitza);
  }
#else
  if (lex_ald) {
    m = analizatuErabLex(hitza,m,anal,&beste_analisia,lema_ident,emaitza);
  }
#endif

  if (m == 0) {
    // kendu 9-ak luzera kalkulatzeko
    strcpy(hitza2,hitza);
    ken_maiuskulak(&hitza2[0]);
    //   	if (strlen(hitza2) < 4) m=0; // 4 baino laburragoak ez egin aldaera gisa
    // 	else 

#ifndef __BRIDGE_VARIANTS__

    m=analizatu_aukerak_hitza(bigarren_aukera,ALDAERAK,hitza,anal,motak,distan);
    if (m>2 && deslok) { // non == ALDAERA
      m = bihur.desanbEratorpena(m,anal,motak,distan);
    }
    if (m) { 
      if (ident_da) {
	inprimatu_goiburukoa(forma_ident, 'T', emaitza);
	ident_analisia = 1;
      }
      else {
	if (irteera_parentizatua) {
	  string shitza = bihur.bihurtu_xerox_lemati(hitza);
	  strcpy(hitza,shitza.c_str());
	}
	inprimatu_goiburukoa(hitza, 'T', emaitza);
	beste_analisia = 1;
      }
      for(i=0;i<m; i++) {
	if (ident_da)
	  inprimatu_ident_analisia(&anal[i][0],&ident_analisia/* ,distan[i]*/,lema_ident,emaitza);
	else
	  if (motak[i] == 'T')
	    inprimatu_aldaera_analisia(&anal[i][0],&beste_analisia,distan[i],lema_ident,emaitza);
	  else // lexikorik gabekoa 2. aukera gisa
	    inprimatu_lexgabeko_analisia(&anal[i][0],&beste_analisia,lema_ident,emaitza);
      }
    }
    else {
#endif // __BRIDGE_VARIANTS__
      if (zen_dek_da) {
	// bihurtu IDENT atzizkirik gabe. Adib: 5ha -> cc IDENT moduan
	//	    zen_dek_da = 0;
	zen_dek_da = 1;
	ident_da = 1;
	strcpy(hitza,"cc");
	lortu_lema_ident(hitza,lema_ident);
      }
      m=analizatu_aukerak_hitza(0,LEX_GABE,hitza,anal,motak,distan);
      if (m>2 && deslok) {
	m = bihur.desanbEratorpena(m,anal,motak,distan);
	if (m>2)  // oraindik bi analisi baino gehiago dago
	  m = bihur.desanbLexGabe(m,anal,motak,distan,hitza);
	//	      m = bihur.desanbEratorpena(m,anal,motak,distan);
      }
      if (m) {
	if (ident_da) {
	  inprimatu_goiburukoa(forma_ident, 'G', emaitza);
	  ident_analisia = 1;
	}
	else {
	  if (irteera_parentizatua) {
	    string shitza = bihur.bihurtu_xerox_lemati(hitza);
	    strcpy(hitza,shitza.c_str());
	  }
	  inprimatu_goiburukoa(hitza, 'G', emaitza);
	  beste_analisia = 1;
	}
	// 	    if (m>2 && deslok) { // non == LEX_GABE ez aplikatu oraingoz
	// 	      m = bihur.desanbEratorpena(m,anal,motak,distan);
	// 	    }
	for(i=0;i<m; i++) {
	  if (ident_da)
	    inprimatu_ident_analisia(&anal[i][0],&ident_analisia,lema_ident,emaitza);
	  else
	    inprimatu_lexgabeko_analisia(&anal[i][0],&beste_analisia,lema_ident,emaitza);
	}
      }
#ifndef __BRIDGE_VARIANTS__
    }
#endif // __BRIDGE_VARIANTS__
  }
  if ((m || m_aur) && Sarrera_berezia) {
    if (irteera_nola == ESTANDAR_AN || irteera_nola == ESTANDAR_PIPE)
      printf("\n)\n");
    else {
      char lerr[LUZMAXAN];
      lerr[0] = '\0';
      sprintf(lerr,"\n)\n");
      emaitza->push_back(lerr);	  
    }
  }
  if (irteera_nola == ESTANDAR_PIPE)
    printf("#\n");
  fflush(stdout);
}

int analizatzailea::analizatu_aukerak_hitza(int bigarren_aukera, int non, char *hitzasar, char anal[][LUZMAXAN],char motak[],int distantziak[]) {
  unsigned int m = 0;
  char hitza[LUZMAXAN],hitza2[LUZMAXAN],hitzasig[LUZMAXAN],aurrekoa[LUZMAXAN],atzekoa[LUZMAXAN];
  char anal2[ANMAX][LUZMAXAN],an_lag[LUZMAXAN],an_lag2[LUZMAXAN],lema_ize[LUZMAXAN],lema_adi[LUZMAXAN];
  char k;
  unsigned int minuskuletara,i,m_aur,m2,anali_majus = 0, dena_majusk_al = 0,denak_rare = 0,denak_rare_mai = 0,anali_distan = 0;
#ifndef __BRIDGE_VARIANTS__
  char anal_bana[ANMAX][LUZMAXAN],anal_bana2[ANMAX][LUZMAXAN];
  map<string,string> an_ban_map;
#endif //__BRIDGE_VARIANTS

  hitza[0] = '\0';
  strcpy(hitza,hitzasar);
  lema_ize[0] = '\0';
  aurrekoa[0] = '\0';
  atzekoa[0] = '\0';
  if ((kar_ber && non == LEX_GABE) || !kar_ber) {

#ifdef _USE_FOMA_
    m=transFoma.analizatu_hitza(non,hitza,anal);
#else
    m=analizatu_hitza(non,hitza,anal);
#endif
#ifndef _USE_FOMA_
#ifndef __BRIDGE_VARIANTS__
 if (non == ALDAERAK) {
      an_ban_map.clear();
      mm = analizatu_hitza(ALD_BANA,hitza,anal_bana);
      sortu_banaketak(mm,&anal_bana[0],an_ban_map);
    }
    if (m) {
      if (!zen_dek) {
	/* Analisi guztiek RARE+ badute orduan tipiko bezala analizatu */
	denak_rare = 1;
	int j = 0;
	for(i=0;i<m; i++) {
	  if (!strstr(&anal[i][0],"RARE") &&
	      !strstr(&anal[i][0],"LEX") &&
	      !strstr(&anal[i][0],"ANB") &&
	      !strstr(&anal[i][0],"ABT")){ denak_rare=0; }
	  if (non == ALDAERAK) {
	    unsigned int dist = 0;
	    char aldaera[LUZMAXAN];
	    char banaketa[LUZMAXAN];
	    an_lag[0] = '\0';
	    banaketa[0] = '\0';
	    strcpy(an_lag,&anal[i][0]);
	    // 	    eman_banaketa(an_lag,mm,anal_bana,banaketa);
	    eman_banaketa(an_lag,an_ban_map,banaketa);
// 	    if (i>=mm) 
// 	      strcpy(banaketa,&anal_bana[mm-1][0]);
// 	    else
// 	      strcpy(banaketa,&anal_bana[i][0]);
	    dist = lortu_distantzia(an_lag,hitza,banaketa,aldaera);
	    /***********************************************************************/
	    //dist_min = MIN2(dist_min, dist);
	    if ( strlen(aldaera) ) {
	      // Lema bada eta EDBLtik ez badator aldaera-n analisi eguneratua, aldatu
	      strcpy(&anal[i][0],aldaera);
	    }
	    hitzamin[0] = '\0';
	    strcpy(hitzamin,hitza);
	    ken_maiuskulak(&hitzamin[0]);
	    // DISTANTZIA PARAMETRIZATU
	    if (dist < 2 && (strlen(hitzamin)>=4 || dist==0)) { // 4 baino laburragoetan EDBLtik bakarrik
	      strcpy(&anal[j][0],anal[i]);
	      motak[j] = 'T';
	      distantziak[j] = dist;
	      j++;
	    }
	  }
	}
	if (non == ALDAERAK && j != m) m = j;
      }
      else denak_rare = 0;
      if (non == ESTANDARRA) k = 'A';
      else if (non == ALDAERAK)  k = 'T';
      else k = 'G';
      for (i=0;i<m;i++) motak[i] = k;
    }
#endif //__BRIDGE_VARIANTS__
#endif // _USE_FOMA_    
    m_aur=m;
    
    if (strstr(&hitza[1],"9"))
      dena_majusk_al=1;
    else
      dena_majusk_al=0;
    
    /************************ HAU analizatu_hitza funtzioan egin beharko litzateke, errepikapenak ekiditeko **/
    if ((non == ESTANDARRA
#ifndef __BRIDGE_VARIANTS__
	 || non == ALDAERAK
#endif //__BRIDGE_VARIANTS__
	 ) && dena_majusk_al && m_aur==0
	) {
      //    if (non<LEX_GABE && dena_majusk_al && m_aur==0) {
      /* dena majuskulak */
      m = 0;
      minuskuletara = strlen(hitza)-1;
      strcpy(hitza2,hitza);
      while (m == 0 && minuskuletara > 0) {
	ken_maiuskulak(&hitza2[minuskuletara]);
#ifdef _USE_FOMA_
	m=transFoma.analizatu_hitza(non,hitza2,&anal[m_aur]);
#else
	m=analizatu_hitza(non,hitza2,&anal[m_aur]);
#endif

#ifndef __BRIDGE_VARIANTS__
	// Hau ez da gertatuko puenteatzen denean
	if (non == ALDAERAK) {
	  mm = analizatu_hitza(ALD_BANA,hitza2,&anal_bana[m_aur]);
	  sortu_banaketak(mm,&anal_bana[m_aur],an_ban_map);
	}
#endif //__BRIDGE_VARIANTS
	minuskuletara--;
      }
      if (m) {
	if (non == ESTANDARRA) k = 'A';
#ifndef __BRIDGE_VARIANTS__
	else if (non == ALDAERAK)  k = 'T';
#endif //__BRIDGE_VARIANTS__
	else k = 'G';
	
#ifndef __BRIDGE_VARIANTS__
	if (non == ALDAERAK) {
	  int j = m_aur;
	  for(i=m_aur;i<m+m_aur;i++) {
	    unsigned int dist = 0;
	    char aldaera[LUZMAXAN];
	    char banaketa[LUZMAXAN];
	    an_lag[0] = '\0';
	    banaketa[0] = '\0';
	    strcpy(an_lag,&anal[i][0]);
	    // 	    eman_banaketa(an_lag,mm,anal_bana,banaketa);
	    eman_banaketa(an_lag,an_ban_map,banaketa);
// 	    if (i>=mm) 
// 	      strcpy(banaketa,&anal_bana[mm-1][0]);
// 	    else
// 	      strcpy(banaketa,&anal_bana[i][0]);
	    dist = lortu_distantzia(an_lag,hitza,banaketa,aldaera);
	    /***********************************************************************/
	    //dist_min = MIN2(dist_min, dist);
	    if ( strlen(aldaera) ) {
	      // Lema bada eta EDBLtik ez badator aldaera-n analisi eguneratua, aldatu
	      strcpy(&anal[i][0],aldaera);
	    }
	    /***********************************************************************/
	    //dist_min = MIN2(dist_min, dist);
	    hitzamin[0] = '\0';
	    strcpy(hitzamin,hitza);
	    ken_maiuskulak(&hitzamin[0]);
	    // DISTANTZIA PARAMETRIZATU
	    if (dist < 2 && dist<strlen(hitzamin)/2) {
	      strcpy(&anal[j][0],anal[i]);
	      motak[j] = 'T';
	      distantziak[j] = dist;
	      j++;
	    }
	  }
	  m = j-m_aur;
	}
	else
#endif //__BRIDGE_VARIANTS__
	  for(i=m_aur;i<m+m_aur;i++)
	    motak[i] = k;
      }
    }
    else
      if ((non == ESTANDARRA
#ifndef __BRIDGE_VARIANTS__
	   || non == ALDAERAK
#endif //__BRIDGE_VARIANTS__
	   )  && dena_majusk_al && m_aur!=0 ){
	//     if (non<LEX_GABE && dena_majusk_al && m_aur!=0) {
	strcpy(hitza2,hitza);
	ken_maiuskulak(&hitza2[1]);
#ifdef _USE_FOMA_
	m=transFoma.analizatu_hitza(non,hitza2,&anal[m_aur]);
#else
	m=analizatu_hitza(non,hitza2,&anal[m_aur]);
#endif
#ifndef __BRIDGE_VARIANTS__
	// Hau ez da gertatuko puenteatzen denean
	if (non == ALDAERAK) {
	  mm = analizatu_hitza(ALD_BANA,hitza2,&anal_bana[m_aur]);
	  sortu_banaketak(mm,&anal_bana[m_aur],an_ban_map);
	}
#endif //__BRIDGE_VARIANTS__
	if (m) {
	  if (non == ESTANDARRA) k = 'A';
#ifndef __BRIDGE_VARIANTS__
	  else if (non == ALDAERAK)  k = 'T';
#endif //__BRIDGE_VARIANTS__
	  else k = 'G';
	  /****** ZATI HAU ERREPASATZEKO ********/
#ifndef __BRIDGE_VARIANTS__
	  if (non == ALDAERAK) {
	    int j = m_aur;
	    for(i=m_aur;i<m+m_aur;i++) {
	      unsigned int dist = 0;
	      char aldaera[LUZMAXAN];
	      char banaketa[LUZMAXAN];
	      an_lag[0] = '\0';
	      banaketa[0] = '\0';
	      strcpy(an_lag,&anal[i][0]);
	      //	      eman_banaketa(an_lag,mm,anal_bana,banaketa);
	      eman_banaketa(an_lag,an_ban_map,banaketa);
// 	      if (i>=mm) 
// 		strcpy(banaketa,&anal_bana[mm-1][0]);
// 	      else
// 		strcpy(banaketa,&anal_bana[i][0]);
	      dist = lortu_distantzia(an_lag,hitza,banaketa,aldaera);
	      /***********************************************************************/
	      //dist_min = MIN2(dist_min, dist);
	      if ( strlen(aldaera) ) {
	      // Lema bada eta EDBLtik ez badator aldaera-n analisi eguneratua, aldatu
		strcpy(&anal[i][0],aldaera);
	      }	
	      //dist_min = MIN2(dist_min, dist);
	      hitzamin[0] = '\0';
	      strcpy(hitzamin,hitza);
	      ken_maiuskulak(&hitzamin[0]);
	      // DISTANTZIA PARAMETRIZATU
	      if (dist < 2 && dist<strlen(hitzamin)/2) {
		strcpy(&anal[j][0],anal[i]);
		motak[j] = 'T';
		distantziak[j] = dist;
		j++;
	      }
	      m = j-m_aur;
	    }
	  }
	  else
#endif //__BRIDGE_VARIANTS__
	    for(i=m_aur;i<m+m_aur;i++)
	      motak[i] = k;
	}
      }
      else {
	/*** ZATI HAU ERREPASATZEKO *****/


// 	if (non == ESTANDARRA && m_aur) {
// 	  int k;
// 	  int itxia_badu = 0;
// 	  for(i=0;i<m_aur; i++)  
// 	    if (!strstr(&anal[i][0],"IZE") &&
// 		!strstr(&anal[i][0],"ADJ") &&
// 		!strstr(&anal[i][0],"ADI") ) { itxia_badu = 1; break;}
// 	  // Ez badu kategoria itxietako analisirik,
// 	  // Begiratu ea ALDAERETAN kategoria itxiko analisirik duen
// 	  if (!itxia_badu) {
// 	    m2=analizatu_hitza(non+1,hitza,anal2);
// 	    if(m2) {
// 	      m = 0;
// 	      for(i=0;i<m2; i++)  
// 		if (!strstr(&anal2[i][0],"RARE")  &&
// 		    !strstr(&anal2[i][0],"LEX") &&
// 		    !strstr(&anal2[i][0],"ANB") &&
// 		    !strstr(&anal2[i][0],"ABT") &&
// 		    !strstr(&anal2[i][0],"IZE") &&
// 		    !strstr(&anal2[i][0],"ADJ") &&
// 		    !strstr(&anal2[i][0],"ADI") ) {
// 		  int dago = 0;
// 		  for (k=0;k<m_aur;k++)
// 		    if (!strcmp(anal2[i],anal[k])) {dago=1;break;}
// 		  if (!dago) {
// 		    strcpy(&anal[m_aur+m][0],anal2[i]);
// 		    motak[m_aur+m] = 'T';
// 		    m++;
// 		  }
// 		}
// 	      m_aur = m + m_aur;
// 	    }
// 	  }
// 	  m = 0;
// 	}
// 	else
// 	  m = 0;
	// ARAZOA: gizon -> dizun aurrean-> haurrean
	m = 0; // Aurrekoa deskomentatzen bada hau kendu.
      }

    // Bigarren aukera: ESTANDARRA + denak_majusk_al = denak_rare_mai?
    //                  ESTANDARRA + denak_rare

    if ((non == ESTANDARRA
#ifndef __BRIDGE_VARIANTS__
	 || non == ALDAERAK
#endif //__BRIDGE_VARIANTS__
	 )  && bigarren_aukera && denak_rare && ((m && denak_rare_mai) || !m)) {
      //    if (non < LEX_GABE && bigarren_aukera && denak_rare && ((m && denak_rare_mai) || !m)) {

#ifndef __BRIDGE_VARIANTS__
      m2=analizatu_hitza(non+1,hitza,anal2);
      if (non+1 == ALDAERAK) {
	mm2=analizatu_hitza(ALD_BANA,hitza,anal_bana2);
	sortu_banaketak(mm2,&anal_bana2[0],an_ban_map);
      }
#else
#ifdef _USE_FOMA_
      m2=transFoma.analizatu_hitza(non+2,hitza,anal2);
#else
      m2=analizatu_hitza(non+2,hitza,anal2);
#endif
#endif //__BRIDGE_VARIANTS__
      if(m2) {
#ifndef __BRIDGE_VARIANTS__
	if (non+1 == ALDAERAK)  k = 'T';
	else 
#endif //__BRIDGE_VARIANTS__
	  k = 'G';
	m = 0;
	for(i=0;i<m2; i++)  
	  if (!strstr(&anal2[i][0],"RARE")  &&
	      !strstr(&anal2[i][0],"LEX") &&
	      !strstr(&anal2[i][0],"ANB") &&
	      !strstr(&anal2[i][0],"ABT")) {

	    // Agian hemen distantzia egiaztatu beharko litzateke!!!!
	    // Bigarren aukeran analisiak gehitzeko distantzia == 0? Hau da, lexikotik!!

#ifndef __BRIDGE_VARIANTS__
	    if (non+1 == ALDAERAK) {
	      unsigned int dist = 0;
	      char aldaera[LUZMAXAN];
	      char banaketa[LUZMAXAN];
	      strcpy(an_lag,&anal2[i][0]);
	      //eman_banaketa(an_lag,mm2,anal_bana2,banaketa);
	      eman_banaketa(an_lag,an_ban_map,banaketa);
// 	      if (i>=mm2) 
// 		strcpy(banaketa,&anal_bana2[mm2-1][0]);
// 	      else
// 		strcpy(banaketa,&anal_bana2[i][0]);
	      dist = lortu_distantzia(an_lag,hitza,banaketa,aldaera);
	      /***********************************************************************/
	      if ( strlen(aldaera) ) {
		// Lema bada eta EDBLtik ez badator aldaera-n analisi eguneratua, aldatu
		strcpy(&anal[i][0],aldaera);
	      }
	      /*dist_min = MIN2(dist_min, dist);*/
	      hitzamin[0] = '\0';
	      strcpy(hitzamin,hitza);
	      ken_maiuskulak(&hitzamin[0]);
	      // DISTANTZIA PARAMETRIZATU
	      if (dist == 0) {
		strcpy(&anal[m][0],anal2[i]);
		motak[m] = 'T';
		distantziak[m] = dist;
		m++;
	      }
	    }
	    else {
#endif //__BRIDGE_VARIANTS
	      strcpy(&anal[m][0],anal2[i]);
	      motak[m] = k;
	      m++;
#ifndef __BRIDGE_VARIANTS__
	    }
#endif //__BRIDGE_VARIANTS__
	  }
	if (!m) m = m_aur;
      }
      else {
	m = m + m_aur;
      }
    }
    else m = m + m_aur;
    
    if (hitza[0]=='9' && bigarren_aukera ) { 
      anali_majus=1;
      lema_adi[0] = '\0';
      for(i=0;i<m; i++) {
	char *tmp;
	char *tmp2 = '\0';
	char lema[LUZMAXAN];
	char lema2[LUZMAXAN];
	lema[0] = '\0';
	strcpy(lema,&anal[i][0]);
	tmp = strstr(lema,"[[");
	*tmp = '\0';
	if (!strlen(lema_ize) && strstr(&anal[i][0],"KAT_IZE")){
	  strcpy(lema_ize,lema);
	}
	if (!strlen(lema_adi) && strstr(&anal[i][0],"KAT_ADI")){
	  lema2[0] = '\0';
	  strcpy(lema2,&anal[i][0]);
	  if (strstr(lema2,"[SAR_") != NULL) {
	    tmp2 = strstr(lema2,"[SAR_");
	    tmp2 += strlen("[SAR_");
	  }
	  if (strstr(lema2,"[Sarrera_") != NULL) {
	    tmp2 = strstr(lema2,"[Sarrera_");
	    tmp2 += strlen("[Sarrera_");
	  }
	  strcpy(lema2,tmp2);
	  tmp2 = strstr(lema2,"]");
	  *tmp2 = '\0';
	  strcpy(lema_adi,lema2);
	}
	kendu_marka_lex(lema,lema,0);
	if (badago_hitza_maiztasun_handikoak(lema)) {
	  anali_majus = 0;
	}
	if (strstr(&anal[i][0],"AZP_LIB")||
	    strstr(&anal[i][0],"AZP_IZB")||
	    strstr(&anal[i][0],"KAT_SIG")||
	    (anal[i][0] == '9')) {
	  anali_majus=0;
	}
      }
    }

    /************************* HAU OSORIK ERREPASATZEKO ***************************************/
#ifndef __BRIDGE_VARIANTS__
    if (bigarren_aukera && non == ALDAERAK) {
      if (m) {
	unsigned int dist;
	int anali_majus_ald = 0;
	int kategoria_itxiak = 0;
	dist_min = strlen(hitza);
	for(i=0;i<m; i++) {
        /* azalekoa lortu eta distantzia *******************************************/
	  char aldaera[LUZMAXAN];
	  char banaketa[LUZMAXAN];
	  strcpy(an_lag,&anal[i][0]);
	  //eman_banaketa(an_lag,mm,anal_bana,banaketa);
	  eman_banaketa(an_lag,an_ban_map,banaketa);
// 	  if (i>=mm) 
// 	    strcpy(banaketa,&anal_bana[mm-1][0]);
// 	  else
// 	    strcpy(banaketa,&anal_bana[i][0]);
	  dist = lortu_distantzia(an_lag,hitza,banaketa,aldaera);
	  /***********************************************************************/
	  if ( strlen(aldaera) ) {
	    // Lema bada eta EDBLtik ez badator aldaera-n analisi eguneratua, aldatu
	    strcpy(&anal[i][0],aldaera);
	  }	
	  //dist_min = MIN2(dist_min, dist);
	  motak[i] = 'T';
	  distantziak[i] = dist;
	  //	  dist_min = MIN2(dist_min, dist);
	  if (!anali_majus_ald &&
	      (strstr(&anal[i][0],"AZP_LIB")||
	       strstr(&anal[i][0],"AZP_IZB")||
	       strstr(&anal[i][0],"SIG") ||
	       (anal[i][0] == '9')))
	    anali_majus_ald=1;
	  if (!kategoria_itxiak &&
	      !strstr(&anal[i][0],"KAT_IZE") &&
	      !strstr(&anal[i][0],"KAT_ADJ") &&
	      !strstr(&anal[i][0],"KAT_ADI") &&
	      !strstr(&anal[i][0],"KAT_SIG"))
	    kategoria_itxiak = 1;
	}
	anali_distan=1;  /* 1eko distantzia: 2000/11/20 */
	// DISTANTZIA PARAMETRIZATU
	if (dist < 3) {
	  if (kategoria_itxiak)
	    return(m);
	  if (anali_majus_ald && dist && hitza[0] == '9') 
	    /*** bakarrik onartu lexikoan dauden IZB/LIBen aldaerak */
	    /*** edota hasierako  letra maiuskulaz ez egotea */
	    anali_distan = 1;
	  else {
	    if (strstr(hitza,"c") || strstr(hitza,"v") || (strstr(hitza,"ge") && !strstr(hitza,"je") && strstr(lema_ize,"je")) ) {
	      return(m);
	    }
	    i = 0;
	    while (i<strlen(hitza)) {
	      if (hitza[i] == '9') {
		hitzasig[i] = hitza[i];
		hitzasig[i+1] = hitza[i+1];
		i+=2;
	      }
	      else if (hitza[i] == '-') {
		hitzasig[i] = hitza[i];
		i++;
	      }
	      else {
		hitzasig[i] = '\0';
		break;
	      }
	    }
	    if (hitzasig[strlen(hitzasig)-1] == '-') hitzasig[strlen(hitzasig)-1] = '\0';
	    if (strlen(hitzasig) <= 2) den_mai_dek = 0;
	    if (den_mai_dek) {
#ifdef _USE_FOMA_
	      m2=transFoma.analizatu_hitza(LEX_GABE,hitza,anal2);
#else
	      m2=analizatu_hitza(LEX_GABE,hitza,anal2);
#endif
	      m_aur = m;
	      m = 0;
	      if(m2) {
		strcpy(hitza2,hitzasig);
		ken_maiuskulak(&hitza2[1]);
		for(i=0;i<m2; i++) {
		  if (strstr(&anal2[i][0],"SIG") || strstr(&anal2[i][0],"IZB") || strstr(&anal2[i][0],"LIB")) {
		    char *tmp;
		    strcpy(an_lag,&anal2[i][0]);
		    tmp = strstr(an_lag,"[[");
		    *tmp = '\0';
		    kendu_marka_lex(an_lag,an_lag,0);
		    strcpy(an_lag2,&an_lag[0]);
		    if (strstr(&anal2[i][0],"SIG")) {
		      if (strcmp(hitzasig,an_lag) == 0) {
			strcpy(an_lag,&anal2[i][0]);
			if (strstr(an_lag,"[SAR_") != NULL)
			  tmp = strstr(an_lag,"[SAR_")+strlen("[SAR_");
			if (strstr(an_lag,"[Sarrera_") != NULL)
			  tmp = strstr(an_lag,"[Sarrera_")+strlen("[Sarrera_");
			bihur_asteris_maj(an_lag2,an_lag2);
			strcat(an_lag2,"--0");
			if (edbl_bertsioa>4)
			  strcat(an_lag2,"---"); // HBn arautu gabe
			// 
			strcpy(tmp,an_lag2);
			tmp=strstr(&anal2[i][0],"]");
			strcat(an_lag,tmp);
			strcpy(&anal[m][0],an_lag); 
			motak[m] = 'G';
			m++;
		      }
		    }
		    else {
		      if (strcmp(hitza2,an_lag) == 0) {
			strcpy(an_lag,&anal2[i][0]);
			if (strstr(an_lag,"[SAR_") != NULL)
			  tmp=strstr(an_lag,"[SAR_")+strlen("[SAR_");
			if (strstr(an_lag,"[Sarrera_") != NULL)
			  tmp=strstr(an_lag,"[Sarrera_")+strlen("[Sarrera_");
			bihur_asteris_maj(an_lag2,an_lag2);
			strcat(an_lag2,"--0");
			if (edbl_bertsioa>4)
			  strcat(an_lag2,"---"); // HBn arautu gabe
			// 
			strcpy(tmp,an_lag2);
			tmp=strstr(&anal2[i][0],"]");
			strcat(an_lag,tmp);
			strcpy(&anal[m][0],an_lag); 
			motak[m] = 'G';
			m++;
		      }
		    }
		  }
		}
	      }
	      if (!m) m = m_aur;
	      return(m);
	    }
	    else
	      anali_distan = 0;
	  }
	}
	else
	  anali_distan = 0;
      }
    }
#endif //__BRIDGE_VARIANTS__
    if (bigarren_aukera && anali_distan) {
      /*** baztertu aldaerak eta lexikorik gabe analizatu behar da, beraz, m = 0 */
      return(0);
    }
    
    /**** Agian etorkizunean. Estandarra, maiuskulaz eta berezia ez */
    if ((!ez_estandarrak || (ez_estandarrak && non != ESTANDARRA)) && bigarren_aukera && anali_majus // && !aurrekoa_puntua
	) {
      if (!den_mai // || (den_mai && !aurrekoa_den_mai)
	   && m) {
	hitza2[0] = '\0';
	i = 0;
	while (i<strlen(hitza)) {
	  if (hitza[i] == '9') {
	    hitzasig[i] = hitza[i];
	    hitzasig[i+1] = hitza[i+1];
	    i+=2;
	  }
	  else
	    if (hitza[i] == '-') {
	      hitzasig[i] = hitza[i];
	      i++;
	    }
	    else {
	      hitzasig[i] = '\0';
	      break;
	    }
	}
	if (hitzasig[strlen(hitzasig)-1] == '-') {
	  hitzasig[strlen(hitzasig)-1] = '\0';
	}
	if (strlen(hitzasig) > 2 && !den_mai_dek) den_mai_dek = 1;
	else hitzasig[0] = '\0';
	if (strlen(aurrekoa))
	  strcpy(hitza,atzekoa);
	strcpy(hitza2,hitza);
	ken_maiuskulak(&hitza2[0]);
#ifdef _USE_FOMA_
	m2=transFoma.analizatu_hitza(LEX_GABE,hitza,anal2);
#else
	m2=analizatu_hitza(LEX_GABE,hitza,anal2);
#endif
	if(m2) {
	  m_aur = m;
	  for(i=0;i<m2; i++)
	    if (((strstr(&anal2[i][0],"AZP_LIB")||strstr(&anal2[i][0],"AZP_IZB")) && (!den_mai || den_mai_dek)) ||
		(strstr(&anal2[i][0],"SIG") && (den_mai || den_mai_dek))) {
	      char *tmp;
	      strcpy(an_lag,&anal2[i][0]);
	      tmp = strstr(an_lag,"[[");
	      *tmp = '\0';
	      strcpy(an_lag2,&an_lag[0]);
	      if (strstr(&anal2[i][0],"SIG") == NULL) {
		ken_maiuskulak(&an_lag[0]);
		ken_maiuskulak(&an_lag2[2]);
	      }
	      kendu_marka_lex(an_lag,an_lag,0);
	      if ((!strlen(lema_adi) && strcmp(lema_ize,an_lag) == 0) || 
		  (strlen(hitzasig) && strcmp(hitzasig,an_lag) == 0) ||
		  (!strlen(lema_adi) && strlen(lema_ize) == (strlen(an_lag) - 1) && an_lag[strlen(an_lag)-1] == 'a') ||
		  /* hau Ibaia-Ibai onartzeko */
		  (strlen(lema_adi) && strcmp(lema_adi,an_lag) == 0) ||
		  (!strlen(hitzasig) && (strlen(hitza2) <= strlen(an_lag)) && strncmp(hitza2,an_lag,strlen(hitza2)) == 0)
		  /* hau Gabiri-Gabiria onartzeko */
		  ) {
		kendu_marka_lex(an_lag2,an_lag2,0);
		strcpy(an_lag,&anal2[i][0]);
		if (strstr(an_lag,"[SAR_") != NULL)
		  tmp=strstr(an_lag,"[SAR_")+strlen("[SAR_");
		if (strstr(an_lag,"[Sarrera_") != NULL)
		  tmp=strstr(an_lag,"[Sarrera_")+strlen("[Sarrera_");
		bihur_asteris_maj(an_lag2,an_lag2);
		strcat(an_lag2,"--0");
		if (edbl_bertsioa>4)
		  strcat(an_lag2,"---"); // HBn arautu gabe
		//	
		strcpy(tmp,an_lag2);
		tmp=strstr(&anal2[i][0],"]");
		strcat(an_lag,tmp);
		strcpy(&anal[m][0],an_lag);
		motak[m] = 'A';
		m++;
	      }
	    }
	}
      }
    }

    /*** hemen garbitu analisiak aldaeretan bakarrik ??? **/
#ifndef __BRIDGE_VARIANTS__
    if (non == ALDAERAK && m>1 && deslok) 
      m = bihur.desanbAldaerak(m,anal,motak,distantziak,distantzia_minimoa);
#endif //__BRIDGE_VARIANTS__
    return (m);
  }
  return (0);
}


/// hau egin beharko litzateke analisi fasean eta emaitza vector<string> batean zuzenean
/// ez ibiltzeko bihurketa absurdoetan
/// gainera, garbitu funtzio bat beharko da, gero eratorpenaren desanbiguazioa ere egin ahal izateko

#ifndef __BRIDGE_VARIANTS__

int analizatzailea::desanb_aldaerak_cstr(int m, char anal[][LUZMAXAN],char motak[],int distantziak[]){
  valarray<int> dist(distantziak,m); 
  map<string,int> an_garbia_map; // analisi garbiak 
  int ema_indizeak[ANMAX];
  vector<string> ema_ana;
  char an_lag[LUZMAXAN],*pp,*pp2, mot[ANMAX];
  int j = 0;
  int zerokoak_daude = 0;

  if (m > 1 && dist.max() > 0) {
    // lehenengo aztertu bakarrik distantzia == 0 dutenak eta gero distantzia > 1 dutenak
    for (int k=0;k<m;k++) {
      ema_indizeak[k] = -1; // defektuz ez gorde emaitza
      if (distantziak[k] == 0) {
	// garbitu, MAPean sartu eta k gorde emaitzan
	map<string,int>::iterator dago;

	zerokoak_daude = 1;
	an_lag[0] = '\0';
	strcpy(an_lag,&anal[k][0]);
	while ( ( (pp=strstr(an_lag,"[ald_")) != NULL )
		|| ( (pp=strstr(an_lag,"[ERROR-KODE_")) != NULL )
		|| ( (pp=strstr(an_lag,"[BIZ_")) != NULL )
		|| ( (pp=strstr(an_lag,"[IZAUR_")) != NULL )
		|| ( (pp=strstr(an_lag,"[ZENB_")) != NULL )
		|| ( (pp=strstr(an_lag,"[NEUR_")) != NULL )
		){   
	  // estandarraren azalekoa lortzeko kendu ald eta ERROR-KODE
	  pp2=strstr(pp, "]")+1;
	  strcpy(pp, pp2);
	}
	dago = an_garbia_map.find(an_lag);
	if (dago == an_garbia_map.end()) { // ez dago, sartu
	  ema_indizeak[k] = j;
	  ema_ana.push_back(&anal[k][0]);
	  dist[j] = distantziak[k];
	  mot[j] = motak[k];
	  an_garbia_map[an_lag] = k;
	  j++;
	}
      }
    }
    // bigarren bueltan dist>0 dutenetan ikusteko ea badagoen analisi baliokiderik EDBLko informazioan oinarrituta
    for (int k=0;k<m;k++) {
      if (!distantzia_minimoa || distantzia_minimoa && !zerokoak_daude && distantziak[k] > 0) {
	// garbitu, MAPean begiratu eta k gorde emaitzan ez badago baliokiderik
	map<string,int>::iterator dago;
	an_lag[0] = '\0';
	strcpy(an_lag,&anal[k][0]);
	while ( ( (pp=strstr(an_lag,"[ald_")) != NULL ) 
		|| ( (pp=strstr(an_lag,"[ERROR-KODE_")) != NULL )
		|| ( (pp=strstr(an_lag,"[BIZ_")) != NULL )
		|| ( (pp=strstr(an_lag,"[IZAUR_")) != NULL )
		|| ( (pp=strstr(an_lag,"[ZENB_")) != NULL )
		|| ( (pp=strstr(an_lag,"[NEUR_")) != NULL )
		){   
	  // estandarraren azalekoa lortzeko kendu ald eta ERROR-KODE
	  pp2=strstr(pp, "]")+1;
	  strcpy(pp, pp2);
	}
	dago = an_garbia_map.find(an_lag);
	if (dago == an_garbia_map.end()) { // ez dago, sartu
	  ema_indizeak[k] = j;
	  ema_ana.push_back(&anal[k][0]);
	  dist[j] = distantziak[k];
	  mot[j] = motak[k];
	  an_garbia_map[an_lag] = k;
	  j++;
	}
	else {
	  // Hobetsi bakarrik erregela, EDBL+erregela aurretik
	  int non = an_garbia_map[an_lag];
	  if (distantziak[non] == distantziak[k] 
	      && strstr(&anal[k][0],"[ERROR-KODE_") == 0
	      &&strstr(&anal[non][0],"[ERROR-KODE_") != 0 
	      || distantziak[non] > distantziak[k]
	      ) {
	    // ordezkatu
	    int posizioa = ema_indizeak[non];
	    ema_indizeak[k] = posizioa;
	    ema_indizeak[non] = -1;
	    ema_ana[posizioa] = &anal[k][0];
	    dist[posizioa] = distantziak[k];
	    mot[posizioa] = motak[k];
	    an_garbia_map[an_lag] = k;
	  }
	}
      }
    }
    // Orain utzi bakarrik beharrezkoak direnak emaitzan. Lehenengo 0 erregela, gero besteak
    //    j = 0;
    for (int k=0;k<j;k++) {
      strcpy(anal[k],ema_ana[k].c_str());
      distantziak[k] = dist[k];
      motak[k] = mot[k];
    }
  }
  else
    j = m;

  return j;
}

#endif //__BRIDGE_VARIANTS

int analizatzailea::desanb_eratorpena_cstr(int m, char anal[][LUZMAXAN],char motak[],int distantziak[]){
  valarray<int> dist(distantziak,m); 
  map<string,int> an_garbia_map; // analisi garbiak 
  int ema_indizeak[ANMAX];
  vector<string> ema_ana;
  char an_lag[LUZMAXAN],*pp,*pp2, mot[ANMAX];
  int j = 0;
  int eratorririk = 0;

  // lehenengo begiratu eratorririk dagoen (sartu aurretik egin)
  for (int k=0;k<m;k++) {
    if (strstr(&anal[k][0],"[ERAKAT_") != NULL) {
      eratorririk = 1;
      break;
    }
  }
  // ondoren gorde lexikalizatuen analisiak baina bim, ald, Sarrera kenduta??

  if (eratorririk) {
    an_lag[0] = '\0';
    for (int k=0;k<m;k++) {
      ema_indizeak[k] = -1; // defektuz ez gorde emaitza
      if (strstr(&anal[k][0],"[ERAKAT_") == NULL) {
	// garbitu, MAPean sartu eta k gorde emaitzan
	map<string,int>::iterator dago;
	strcpy(an_lag,&anal[k][0]);
	pp = strstr(an_lag,"["); // iritsi analisi hasieraraino bim saltatzeko
	if (pp != NULL) strcpy(an_lag,pp);
	// hurrengo morfemaren bim saltatu behar da dagoenean, bestela ez du hartuko while-an
	pp = strstr(an_lag,"]]")+2;
	while (pp[0] == ']') { // saltatu ]] sekuentziak
	  pp = pp+1;
	}
	if (pp[0] != '[' && pp[0] != '\0') {
	  pp2 = strstr(pp,"["); // iritsi IMraino bim saltatzeko
	  if (pp2 != NULL) strcpy(pp,pp2);
	}
	while ( ( (pp=strstr(an_lag,"[ald_")) != NULL )
		|| ( (pp=strstr(an_lag,"[ERROR-KODE_")) != NULL )
		|| ( (pp=strstr(an_lag,"[Sarrera_")) != NULL )
		|| ( (pp=strstr(an_lag,"[BIZ_")) != NULL )
		|| ( (pp=strstr(an_lag,"[IZAUR_")) != NULL )
		|| ( (pp=strstr(an_lag,"[ZENB_")) != NULL )
		|| ( (pp=strstr(an_lag,"[NEUR_")) != NULL )
		){   
	  // estandarraren azalekoa lortzeko kendu ald eta ERROR-KODE
	  pp2=strstr(pp, "]")+1;
	  strcpy(pp, pp2);
	  while (pp[0] == ']') { // saltatu ]] sekuentziak
	    pp = pp+1;
	  }
	  if (pp[0] != '[' && pp[0] != '\0') {
	    pp2 = strstr(pp,"["); // iritsi IMraino bim saltatzeko
	    if (pp2 != NULL) strcpy(pp,pp2);
	  }
	}
	dago = an_garbia_map.find(an_lag);
	if (dago == an_garbia_map.end()) { // ez dago, sartu
	  ema_indizeak[k] = j;
	  ema_ana.push_back(&anal[k][0]);
	  dist[j] = distantziak[k];
	  mot[j] = motak[k];
	  an_garbia_map[an_lag] = k;
	  j++;
	}
      }
    }
    
    
    // bigarren bueltan eratorriak konparatu lexikalizatuekin bim, ald, Sarrera kenduta
    // Gainera, [KAT eta [AZP eta [KAT_ATZ] kendu eta [ERAKAT_IZE][ERAAZP_ARR]] KAT eta AZP bihurtu
    // errazena agian lehenengo [KAT_ATZ]rainoko guztia kentzea da, eta ondoren ERA kendu
    for (int k=0;k<m;k++) {
      // garbitu, MAPean begiratu eta k gorde emaitzan ez badago baliokiderik
      map<string,int>::iterator dago;
      
      if (ema_indizeak[k] == -1) { // ERAKAT dauka
	an_lag[0] = '\0';
	strcpy(an_lag,&anal[k][0]);
	pp = strstr(an_lag,"[ERAKAT_"); // iritsi analisi ERAKAT-eraino bim saltatzeko
	if (pp != NULL) {
	  strcpy(an_lag,"[[KAT_");
	  strcat(an_lag,pp+strlen("[ERAKAT_"));
	}
	pp2 = strstr(an_lag,"[ERAAZP_"); // iritsi analisi ERAAZP-eraino bim saltatzeko
	if (pp2 != NULL) {
	  strcpy(pp2+1,pp2+strlen("[ERA"));
	}
	// hurrengo morfemaren bim saltatu behar da dagoenean, bestela ez du hartuko while-an
	pp = strstr(an_lag,"[AZP_");
	pp2=strstr(pp, "]")+1;
	pp = pp2;
	while (pp[0] == ']') { // saltatu ]] sekuentziak
	  pp = pp+1;
	}
	if (pp[0] != '[' && pp[0] != '\0') {
	  pp2 = strstr(pp,"["); // iritsi IMraino bim saltatzeko
	  if (pp2 != NULL) strcpy(pp,pp2);
	}
	
	while ( ( (pp=strstr(an_lag,"[ald_")) != NULL ) 
		|| ( (pp=strstr(an_lag,"[ERROR-KODE_")) != NULL )
		|| ( (pp=strstr(an_lag,"[Sarrera_")) != NULL )
		|| ( (pp=strstr(an_lag,"[BIZ_")) != NULL )
		|| ( (pp=strstr(an_lag,"[IZAUR_")) != NULL )
		|| ( (pp=strstr(an_lag,"[ZENB_")) != NULL )
		|| ( (pp=strstr(an_lag,"[NEUR_")) != NULL )
		){   
	  // estandarraren azalekoa lortzeko kendu ald eta ERROR-KODE
	  pp2=strstr(pp, "]")+1;
	  strcpy(pp, pp2);
	  while (pp[0] == ']') { // saltatu ]] sekuentziak
	    pp = pp+1;
	  }
	  if (pp[0] != '[' && pp[0] != '\0') {
	    pp2 = strstr(pp,"["); // iritsi IMraino bim saltatzeko
	    if (pp2 != NULL) strcpy(pp,pp2);
	  }
	}
	dago = an_garbia_map.find(an_lag);
	if (dago == an_garbia_map.end()) { // ez dago, sartu
	  ema_indizeak[k] = j;
	  ema_ana.push_back(&anal[k][0]);
	  dist[j] = distantziak[k];
	  mot[j] = motak[k];
	  an_garbia_map[an_lag] = k;
	  j++;
	}
	else {
	  // Hobetsi lexikalizatua
	}
      }
    }
    // Orain utzi bakarrik beharrezkoak direnak emaitzan.
    //    j = 0;
    for (int k=0;k<j;k++) {
      strcpy(anal[k],ema_ana[k].c_str());
      distantziak[k] = dist[k];
      motak[k] = mot[k];
    }
  }
  else 
    j = m;

  return j;
}


#ifndef _USE_FOMA_
#ifndef __BRIDGE_VARIANTS__
// Beharbada analizatutako hitzaren banaketa guztiak edukitzean analisi desberdin
// bakoitzari dagokion banaketa MAP batean gehitu eta hemen bakarrik kontsultatu.
// Hau ez da eraginkorra!!
void analizatzailea::sortu_banaketak(int mm,char anal_bana[][LUZMAXAN],map<string,string> &an_ban_map) {
  char anal_bana_ana[ANMAX][LUZMAXAN];

  for (int i=0;i<mm;i++) {
    int j = analizatu_hitza(ALD_BANA_ANA,anal_bana[i],anal_bana_ana);
    if (j>0) {
      for (int k=0;k<j;k++) {
	map<string,string>::iterator dago = an_ban_map.find(anal_bana_ana[k]);
	if (dago == an_ban_map.end()) { // ez badago lehendik sartu
	  string an_gako = anal_bana_ana[k];
	  string banaketa = anal_bana[i];
	  an_ban_map[an_gako] = banaketa;
	}
      }
    }
  }
}

void analizatzailea::eman_banaketa(char an_lag[], map<string,string> &an_ban_map,char banaketa[]) {
  string an_gako = an_lag;
  string banstr=an_ban_map[an_gako];
  strcpy(banaketa,banstr.c_str());
  return;
}




#define MIN(a,b,c) (a<b?((a<c)?a:c):((b<c)?b:c))

/***************************************************************************/
/*********** BI HITZEN ARTEKO EDIZIO-DISTANTZIA KALKULATU ******************/
/***************************************************************************/

/**** BERTSIO ITERATIBOA ****/

int analizatzailea::distantz(char *forma, char *lema, char *aldaera) {
  int i,j,plus=0,distantzia;
  int luzforma = 0;
  int luzlema = 0;
  int taula[100][100];
  char aldaeratmp[100];

  luzforma = strlen(forma);
  luzlema = strlen(lema);
  
  for (i=0;i<=luzforma;i++) {
    taula[i][0] = i;
  }

  for (j=0;j<= luzlema ;j++) {
    taula[0][j] = j;
  }

/* forma[i+1] == lema[j+1]     ed(forma[i+1],lema[j+1]) = ed(forma[i],lema[j])

   forma[i] == lema[j+1] &&
   forma[i+1] == lema[j]       ed(forma[i+1],lema[j+1]) = 1 + min { ed(forma[i-1],lema[j-1],
                                                                    ed(forma[i+1],lema[j],
                                                                    ed(forma[i],lema[j+1] }

   forma[i+1] != lema[j+1]     ed(forma[i+1],lema[j+1]) = 1 + min { ed(forma[i],lema[j],
                                                                    ed(forma[i+1],lema[j],
                                                                    ed(forma[i],lema[j+1] }
*/

  for (i=0;i<luzforma;i++) {
    for (j=0;j<luzlema;j++) {
      if ( forma[i] == lema[j] ) {
        taula[i+1][j+1] = taula[i][j];
      }
      else
        if (i && j && (forma[i-1] == lema[j]) && (forma[i] == lema[j-1]) )
          taula[i+1][j+1] = 1 + MIN(taula[i-1][j-1],taula[i+1][j],taula[i][j+1]);
        else
	  if (lema[j] == '+') {
	    taula[i+1][j+1] = taula[i+1][j];
	    plus = j;
	  }
	  else
	    taula[i+1][j+1] = 1 + MIN(taula[i][j],taula[i+1][j],taula[i][j+1]);
    }
  }

  j = luzlema;
  i = luzforma;
  distantzia = taula[i][j];

  while (taula[i-1][j] < taula[i][j]) i--;

  aldaera[0] = '\0';
  strcpy(aldaera,forma);
  aldaera[i] ='\0';
/*   distantzia = taula[i][j]; */
  if (lema[j-1] == 'a' && forma[i-1] == 'e' && i != luzforma) {
    distantzia--;
    aldaera[strlen(aldaera)-1] = '\0';
    strcat(aldaera, "a");
  }

  if (plus > 0) {
    while (taula[i-1][plus] < taula[i][plus]) {
      i--;
    }
    aldaeratmp[0] = '\0';
    strcpy(aldaeratmp,aldaera);
    aldaeratmp[i] = '\0';
    strcat(aldaeratmp, "+");
    strcat(aldaeratmp, &aldaera[i]);
    strcpy(aldaera,aldaeratmp);
  }

  if ((lema[0] == 't' || lema[0] == 'k') && forma[0] == 'e')
      // atzizkietan e-ren galera egon daiteke
    distantzia--;

  return(distantzia);
}




int analizatzailea::lortu_distantzia(char an_lag[],char hitza[],char banaketa[],char aldaera[]) {
  char *pp,*pp2,azalekoa[LUZMAXAN],azalekoald_std[LUZMAXAN],hitza2[LUZMAXAN],an_lag2[LUZMAXAN],lagald[LUZMAXAN],lagald2[LUZMAXAN];
  char stdbim[LUZMAXAN],stdsar[LUZMAXAN],sarrera[LUZMAXAN],aldbim[LUZMAXAN],aldsar[LUZMAXAN],*phasi,lerrohasiera[LUZMAXAN],*bhasi,banhasiera[LUZMAXAN];
  unsigned int nn,nnald_std,dist = 0,distald = 0, dist_ez_ald=0, distbim = 0, distmp = 0, dist1 = 0, dist2 = 0, disterror=0;
  int err_morfeman = 0;
  int err_leman = 0;
  char aldaera1[LUZMAXAN],aldaera2[LUZMAXAN],aldaera3[LUZMAXAN];

//   if (strstr(an_lag,"Estandarrak")) {
//     dist = 0;
//     aldaera[0] = '\0';
//     return(dist);
//   }
  aldaera[0] = '\0';
  aldaera1[0] = '\0';
  aldaera2[0] = '\0';
  aldaera3[0] = '\0';

  if (strstr(an_lag,"[ald_") != NULL || strstr(an_lag,"[ERROR-KODE_") != NULL) {
    nn = xfl_sortu(ALD_STD,an_lag,azalekoa);
  }
  else {
    nn=xfl_sortu(ESTANDARRA,an_lag, azalekoa);
  }
  if(nn) {
    char *tmp;
    distmp = strlen(hitza);
    tmp = strstr(azalekoa,",9");
    if (hitza[0] == '9') {
      strcpy(hitza2,hitza);
      ken_maiuskulak(&hitza2[1]);
      if (tmp != NULL) {
	strcpy(azalekoa,++tmp);
      }
    }
    else {
      if (tmp != NULL)
	*(tmp)='\0';  /* maiuskulak kentzeko */
    }
    while (distmp && strlen(azalekoa)) {
      char azaltmp[LUZMAXAN];
      azaltmp[0] = '\0';
      if ( (tmp = strstr(azalekoa,",")) != NULL ) {
	strncpy(azaltmp,azalekoa,tmp-azalekoa);
	azaltmp[tmp-azalekoa] = '\0';
	strcpy(azalekoa,++tmp);
      }
      else {
	strcpy(azaltmp,azalekoa);
	azalekoa[0] = '\0';
      }
      if (hitza[0] == '9')
	dist = distantz(hitza2,azaltmp,aldaera2);
      else
	dist = distantz(hitza,azaltmp,aldaera);
      if (dist < strlen(hitza)) azalekoa[0] = '\0';
    }

    // DISTANTZIA PARAMETRIZATU
    if (dist == 0 || dist >= 2) {
      aldaera[0] = '\0';
      return dist;
    }
   /// orain sortu aldaera banaketan oinarrituta


    an_lag2[0] = '\0';
    lerrohasiera[0] = '\0';
    strcpy(lerrohasiera,an_lag);
    banhasiera[0] = '\0';
    strcpy(banhasiera,banaketa);
    while ( (phasi=strstr(lerrohasiera,"[[")) != NULL ) {
      char morfema[LUZMAXAN],formazatia[LUZMAXAN];
      char aldedbl[LUZMAXAN], *hasaldedbl;
      int beROker = 0;
      strncpy(morfema,lerrohasiera,strlen(lerrohasiera)-strlen(phasi));
      morfema[strlen(lerrohasiera)-strlen(phasi)] = '\0';
      if (morfema[0] == '-' && banhasiera[0] == '-' && banhasiera[1] != '+') {
	formazatia[0] = '-';
	formazatia[1] = '\0';
	strcpy(banhasiera,&banhasiera[1]);
      }
      else {
	bhasi=strstr(banhasiera,"+");
	if (bhasi != NULL) {
	  strncpy(formazatia,banhasiera,strlen(banhasiera)-strlen(bhasi));
	  formazatia[strlen(banhasiera)-strlen(bhasi)] = '\0';
	  strcpy(banhasiera,bhasi+1);
	}
	else {
	  strcpy(formazatia,banhasiera);
	}
      }
      if ((strcmp(formazatia,"ber") == 0) && (strchr(BOKALE,banhasiera[0]) == NULL)) {
	// ber ordez bir beharko luke
	beROker = 1;
      }
      if (dist == 1 && (strcmp(formazatia,"bai") == 0) && (strcmp(morfema,"bait")==0) &&
	  (strstr(lerrohasiera,"[ald_") != NULL) ) {
	strcat(formazatia,"t"); // errorea mugan dago eta ondorengoari jarri zaio aldaera
	dist = 0;
      }
      else if (dist == 1 && (strcmp(formazatia,"bai") == 0) && (strcmp(morfema,"bait")==0)){
	strcat(formazatia,"t"); // errorea mugan dago eta ondorengoari ere ez dio jarri
      }

      if ((formazatia[0] == '9' || formazatia[0] == '*')&& 
	  !strstr(an_lag,"IZB") && !strstr(an_lag,"LIB"))
	ken_maiuskulak(&formazatia[0]);
      aldedbl[0] = '\0';
      if ( (hasaldedbl=strstr(morfema,"[ald_")) != NULL) {
	strcpy(aldedbl,hasaldedbl+strlen("[ald_"));
	// amaierako "]" kendu
	aldedbl[strlen(aldedbl)-1] = '\0';
	*hasaldedbl = '\0';
      }
      strcat(an_lag2,morfema); // aurrez, [ald_ kendu beharko litzateke morfema eta forma desberdinak badira
      if (morfema[0] == '+') {
	strcpy(morfema,&morfema[1]);
      }
      if (formazatia[0] != '\0') { //&& strstr(morfema,"[ald_") == NULL) {
	// 0 morfemaren ez bada edo EDBLtik ez badator, gehitu
	//konparatu diakritikorik gabe
	char morfema_garbia[LUZMAXAN],formazatia_garbia[LUZMAXAN];
	morfema_garbia[0] = '\0';
	formazatia_garbia[0] = '\0';
	strcpy(morfema_garbia,morfema);
	strcpy(formazatia_garbia,formazatia);
	kendu_marka_lex(morfema_garbia,morfema_garbia,0);
	// salbuespena: morfema_garbia-n hasierako E kendu denean, konparazioa egiteko formazatiari kendu hasierako e
	
	if (morfema[0] == 'E' && formazatia[0] == 'e') {
	  strcpy(formazatia_garbia,&formazatia_garbia[1]);
	}

	// DISTANTZIA PARAMETRIZATU
	// MOMENTUZ morfema eta aldaeraren arteko distantzia ez dadila izan distantzia baino handiagoa
	// banatzailea konponduz gero baldintza ken daiteke //&& abs((int)(strlen(morfema_garbia)-strlen(formazatia)))<2) {
 	if (strcmp(morfema_garbia,"tu") == 0 && strcmp(formazatia_garbia,"du") == 0) {
 	  // l+tu -> ldu baina ez da errorea. Ez jarri ald
 	}
 	else
	  if (strcmp(morfema_garbia,formazatia_garbia) != 0 || beROker != 0) { 
	    strcat(an_lag2,"[ald_");
	    // diakritikoak gehitu beharrezkoa denean
	    if (strlen(formazatia)>1)
	      gehitu_marka_lex(morfema,formazatia);
	    if (morfema[strlen(morfema)-1] == 'A' && formazatia[strlen(formazatia)-1] != 'A' && 
		(strstr(an_lag,"]]+a") != NULL || strstr(an_lag,"]]+e") != NULL))
	      strcat(formazatia,"A");
	    // A+a A+e egitean banatzaileak ez du a horren berririk ematen
	    // biskA[ald_pisk][[Sarrera_biska--0][KAT_IZE][AZP_ARR][BIZ_-]]+a
	    
	    // diakritikoak lispifikatzean bihurtzen dira
	    // 	  string formalem = bihur.bihurtu_xerox_lemati(formazatia);
	    // 	  strcat(an_lag2,formalem.c_str());
	    strcat(an_lag2,formazatia);
	    strcat(an_lag2,"]");
	    // edblko aldaera aldatu bada, kendu Aldaera eta LHB ezaugarriak
	    if (strlen(aldedbl) > 0) {
	      lagald[0] = '\0';
	      strcpy(lagald,phasi);
	      if ( (pp = strstr(lagald,"[Aldaera_")) != NULL) {
		strncpy(lagald2,lagald,strlen(lagald)-strlen(pp));
		lagald2[strlen(lagald)-strlen(pp)] = '\0';
		strcat(an_lag2,lagald2);
		char *aldbuk = strstr(pp,"]");
		strcpy(lagald,aldbuk+1);
	      }
	      if ( (pp = strstr(lagald,"[LHB_")) != NULL) {
		strncpy(lagald2,lagald,strlen(lagald)-strlen(pp));
		lagald2[strlen(lagald)-strlen(pp)] = '\0';
		strcat(an_lag2,lagald2);
		char *aldbuk = strstr(pp,"]");
		strcpy(lagald,aldbuk+1); // saltatu LHB+/-
	      }
	      strcpy(lagald2,lagald); // bestela matxakatzen du ondoren
	      phasi = lagald2;
	    }
	  }
	  else if (strlen(aldedbl) > 0){
	    strcat(an_lag2,"[ald_");
	    strcat(an_lag2,aldedbl);
	    strcat(an_lag2,"]");
	  }
      }
      // gehitu morfemaren IMa
      lagald[0] = '\0';
      strcpy(lagald,phasi);
      pp = strstr(lagald,"]]");
      while (pp != NULL && pp[2] == '[') {
	strncpy(lagald2,lagald,strlen(lagald)-strlen(pp)+2); // bukaerako ']]' ere kopiatu
	lagald2[strlen(lagald)-strlen(pp)+2] = '\0';
	strcat(an_lag2,lagald2);
	strcpy(lagald,pp+2);
	pp = strstr(lagald,"]]");
      }
      strncpy(lagald2,lagald,strlen(lagald)-strlen(pp)+2); // bukaerako ']]' ere kopiatu
      lagald2[strlen(lagald)-strlen(pp)+2] = '\0';
      strcat(an_lag2,lagald2);      
      if (pp == NULL || pp[2] == '\0') 
	lerrohasiera[0] = '\0';
      else
	strcpy(lerrohasiera,pp+2);
      while (lerrohasiera[0] == ']') { // uste dut bakarra egongo dela egotekotan
	strcat(an_lag2,"]");
	strcpy(lerrohasiera,&lerrohasiera[1]);
      }
    }
    if (strlen(lerrohasiera)) // amaierako ']'-ak gehitu
      strcat(an_lag2,lerrohasiera);
    strcpy(aldaera,an_lag2);
  }
  else // Honek ez luke gertatu beharko!! Baina gertatzen da
    // analisia egiten da baina aldaeren informazioa kenduta ez du sorkuntza egiten ALD_STD transduktoreak
    // horiek ez ditut sartuko
    // hion[[Sarrera_hion--1][KAT_ADL][ERR_[Sarrera_*edun--0]][MDN_B1][NOR_HURA][NORI_HARI][NORK_HIK]]+En[[Sarrera_n--2][KAT_ERL][ERL_ERLT][FSL_[FS1_@+JADLAG__IZLG>][FS2_@+JADNAG__IZLG>]]]+ek[[Sarrera_ek--2][KAT_DEK][KAS_ERG][NUM_P][MUG_M][FSL_[FS1_@SUBJ]]
    //  **************** sortu ESTANDARRA erabilita ere:
    //bait[[Sarrera_bait--1][KAT_ERL][ERL_KAUS][FSL_[FS1_@+JADLAG__MP][FS2_@+JADNAG__MP]]]+dugu[[Sarrera_dugu--1][KAT_ADL][ERR_[Sarrera_*edun--0]][MDN_A1][NOR_HURA][NORK_GUK]]
    // 
    // dist=10; /// MAXIMO BAT IPINI BEHARKO LITZATEKE HEMEN
    // Aldaera EDBLtik badator, dist=0 jarri, mugan badago (bait-en kasuan) dist=1, bestela dist=10, baina honek ez luke gertatu beharko
    
    if (strstr(an_lag,"[ald_") != NULL) dist = 0; 
    else if (strstr(an_lag,"bait[[") != NULL) dist = 1; else dist=10;
  return dist;
}

#endif //__BRIDGE_VARIANTS__
#endif //_USE_FOMA_

void analizatzailea::lortu_hitza(char *hitza,vector<string> *sarrerako_taula,vector<string> *emaitza,int *indizea)
{
  // char forma[LUZMAXAN];
 int jarraitu = 1;
 int sar_luz, luzera=0;
 static char lerroa[LUZMAXAN];
 string llag;
 // static int lehena = 1;
 hitza[0] = '\0';
 // forma[0] = '\0';
 kar_ber = 0;
 if (irteera_nola == TAULAN)
   luzera = sarrerako_taula->size();
 sar_luz = luzera;

 /*
 if (lerroa[0] == '\0')
   gets(forma);
 else
   {
     strcpy(forma, lerroa);
     lerroa[0] = '\0';
   }
 printf("%s\n",forma);
 forma[0] = '\0';
 */

 ident_da = 0;
 zen_da = 0;
 zen_dek_da = 0;
 errom_da = 0;
 char *getRet;

 if(irteera_nola == ESTANDAR_AN) {
   getRet = fgets(lerroa,LUZMAXAN-1,stdin); 
 //   gets(lerroa);
   if (getRet != NULL && strlen(lerroa)>0 && lerroa[0] != '/') {
     strcpy(hitza,lerroa);
     if (hitza[strlen(hitza)-1] == '\n')
       hitza[strlen(hitza)-1] = '\0';
     if (strlen(hitza)) {
       lerroa[0] = ')';
       lerroa[1] = '\0';
     }
   }
 }
 else {
   if (*indizea < sar_luz) {
     llag = (*sarrerako_taula)[*indizea];
     strcpy(lerroa,llag.c_str());
     *indizea = *indizea + 1;
     hitza[0] = '\0';
   }
   else jarraitu=0;
 }
//  if (!lehena && (strstr(lerroa,"<ID>") == NULL)) aurrekoa_puntua = 0;

 while (jarraitu && ((irteera_nola == ESTANDAR_AN && !feof(stdin)) || (irteera_nola == TAULAN && *indizea <= sar_luz)) ) {
   if (strstr(lerroa,">/<IDENT>/") != NULL ) {
     // forma eta lema aldatu behar dira
     ident_da = 1;
     forma_ident[0] = '\0';
     strcpy(forma_ident,&lerroa[2]);
     if (irteera_nola == TAULAN) // kasu honetan \n ez dauka amaieran
       forma_ident[strlen(lerroa)-strlen(">/<IDENT>/")-strlen("/<")] = '\0';
     else
       forma_ident[strlen(lerroa)-strlen(">/<IDENT>/")-strlen("/<\n")] = '\0';
   }
   if (strstr(lerroa,">/<ZEN>/") != NULL ) {
     // forma eta lema aldatu behar dira
     zen_da = 1;
     forma_ident[0] = '\0';
     strcpy(forma_ident,&lerroa[2]);
     if (irteera_nola == TAULAN) // kasu honetan \n ez dauka amaieran
       forma_ident[strlen(lerroa)-strlen(">/<ZEN>/")-strlen("/<")] = '\0';
     else
       forma_ident[strlen(lerroa)-strlen(">/<ZEN>/")-strlen("/<\n")] = '\0';
   }
   if (strstr(lerroa,">/<ZEN_DEK>/") != NULL ) {
     // forma eta lema aldatu behar dira
     zen_dek_da = 1;
     forma_ident[0] = '\0';
     strcpy(forma_ident,&lerroa[2]);
     if (irteera_nola == TAULAN) // kasu honetan \n ez dauka amaieran
       forma_ident[strlen(lerroa)-strlen(">/<ZEN_DEK>/")-strlen("/<")] = '\0';
     else
       forma_ident[strlen(lerroa)-strlen(">/<ZEN_DEK>/")-strlen("/<\n")] = '\0';
   }
   if (strstr(lerroa,">/<ERROM>/") != NULL ) {
     // forma eta lema aldatu behar dira
     errom_da = 1;
     forma_ident[0] = '\0';
     strcpy(forma_ident,&lerroa[2]);
     if (irteera_nola == TAULAN) // kasu honetan \n ez dauka amaieran
       forma_ident[strlen(lerroa)-strlen(">/<ERROM>/")-strlen("/<")] = '\0';
     else
       forma_ident[strlen(lerroa)-strlen(">/<ERROM>/")-strlen("/<\n")] = '\0';
   }
   if ( strstr(lerroa,">/<KAR_BER>/") ) {
     kar_ber = 1;
     forma_ident[0] = '\0';
     strcpy(forma_ident,&lerroa[2]);
     if (irteera_nola == TAULAN) // kasu honetan \n ez dauka amaieran
       forma_ident[strlen(lerroa)-strlen(">/<KAR_BER>/")-strlen("/<")] = '\0';
     else
       forma_ident[strlen(lerroa)-strlen(">/<KAR_BER>/")-strlen("/<\n")] = '\0';
   }
   if (strstr(lerroa,"((forma") != 0) { /*** forma bada, hitza jaso */
     if (irteera_nola == TAULAN) {
       strncpy (hitza, &lerroa[9],strlen(lerroa)-11);
       hitza[strlen(lerroa)-11] = '\0';
     }
     else {
       strncpy (hitza, &lerroa[9],strlen(lerroa)-12);
       hitza[strlen(lerroa)-12] = '\0';
     }
     if (ident_da || zen_da || zen_dek_da || errom_da) {
       // ordezkatu analizatu den hitz generikoa edo zenbakia formarekin
       strcpy(lerroa,"((forma \"");
       strcat(lerroa,forma_ident);
       strcat(lerroa,"\")");
     }
   }
   if (lerroa[0] == ')') {
     if (strlen(hitza)) {
       lerroa[0] = '\0';
     }
     /*       else {
	      lerroa[0] = '\0';
	      gets(lerroa);
	      }*/
     jarraitu = 0;
   }
   else {
     if (lerroa[0] == '/') {
       if (strstr(lerroa,">/<IDENT>/") == NULL ) ident_da = 0;
       if (strstr(lerroa,">/<ZEN>/") == NULL ) zen_da = 0;
       if (strstr(lerroa,">/<ZEN_DEK>/") == NULL ) zen_dek_da = 0;
       if (strstr(lerroa,">/<ERROM>/") == NULL ) errom_da = 0;
 //       if ( strstr(lerroa,"<.>") ||
// 	    strstr(lerroa,"<!>") ||
// 	    strstr(lerroa,"<?>") ||
// 	    strstr(lerroa,"<...>") ||
// 	    strstr(lerroa,"<:>") ||
// 	    strstr(lerroa,"<\">") ||
// 	    strstr(lerroa,"<«>")
// 	    )
// 	 aurrekoa_puntua = 1;
//        else
       if (!strstr(lerroa,"<PUNT") && !strstr(lerroa,"BEREIZ")) {
// 	 aurrekoa_den_mai = den_mai;
// 	 aurrekoa_has_mai = has_mai;
	 if ( strstr(lerroa,"<HAS_MAI>") ) has_mai = 1;
	 else has_mai = 0;
	 if ( strstr(lerroa,"<DEN_MAI") ) den_mai = 1;
	 else den_mai = 0;
	 if ( strstr(lerroa,"<DEN_MAI_") ) den_mai_dek = 1;
	 else den_mai_dek = 0;
	 if ( strstr(lerroa,"<ZEN_DEK") ) zen_dek = 1;
	 else zen_dek = 0;
       }
       if(irteera_nola == ESTANDAR_AN){
	 printf("%s",lerroa);
       }
       else {
	 char lerr[LUZMAXAN];
	 lerr[0] = '\0';
	 sprintf(lerr,"%s\n",lerroa);
	 emaitza->push_back(lerr);
       }
     }
     if (irteera_nola == ESTANDAR_AN){
       lerroa[0] = '\0';
        getRet = fgets(lerroa,LUZMAXAN-1,stdin);
       //	   gets(lerroa);
     }
     else {
       lerroa[0] = '\0';
       if(*indizea!=sar_luz) {
	 llag = (*sarrerako_taula)[*indizea];
	 strcpy(lerroa,llag.c_str());
       }
       *indizea = *indizea+1;
     }
   }
   //   lehena = 0;
 }
}


using namespace pcrepp;
int analizatzailea::analizatuErabLex(char *hitza,int m, char anal[][LUZMAXAN], int *beste_analisia, char *lema_ident,  vector<string> *emaitza) {
  int m_lag,m_lag2;//,dena_majusk_al=0;
  char analErabLex[LUZMAXAN];
  int SARda=0;
  string analisia;
  Pcre SAR("\\[SAR_");
	  
  if (errom_da) {
    char hitza2[LUZMAXAN];
    strcpy(hitza2,lema_ident);
    bihur_maj_asteris(hitza2,hitza2);
    #ifdef _USE_FOMA_
    m_lag=transFoma.analizatu_hitza(LEX_GABE,hitza2,anal); // SEGURU HORRELA?? m_lag+mlag2 zertarako? eta m/=0 bada??
  }
  else
    m_lag=transFoma.analizatu_hitza(LEX_GABE,hitza,anal);
    #else
    m_lag=analizatu_hitza(LEX_GABE,hitza2,anal); // SEGURU HORRELA?? m_lag+mlag2 zertarako? eta m/=0 bada??
  }
  else
    m_lag=analizatu_hitza(LEX_GABE,hitza,anal);
    #endif
  m_lag2=0;
  // if ((!errom_da && strstr(&hitza[1],"9")) ||
  //     (errom_da && strstr(&hitza2[1],"9")))
  //   dena_majusk_al=1;
  // else
  //   dena_majusk_al=0;

  if (m_lag > 0) {
    analisia =  &anal[0][0]; 
  // Nahikoa da lehenengo analisia begiratzea jakiteko zein bertsiotakoa den IMa
    if (SAR.search(analisia)) {
      SARda = 1;
    }
  }
  analErabLex[0] = '\0';

  for(int i=0;i<m_lag+m_lag2; i++) {
    // prestatu erabiltzaileren hiztegian bilatzeko
    string analisia = &anal[i][0];
    string bimStr = bihur.lortuBim(analisia);
    string bilatzekoa = bihur.lortuErabLexInfo(bimStr,analisia);

    strcpy(analErabLex,bilatzekoa.c_str());
    #ifdef _USE_FOMA_
    if (transFoma.bilatu_erab_guztiak(analErabLex) != transFoma.azkena()) {
		#else
    if (bilatu_erab_guztiak(analErabLex)) {
    #endif
      /* prestatu emaitza anal gehi lema SAR eremuan */
      /* anal-etik dena SAR_ ondorengoa kenduta */
      /* zati hori da tmp_on-eko lehen zatia */
      /* emaitza tmp_lag-en */		
      string analisi_erab;
      char bim_erab[LUZMAXAN];
      bim_erab[0] = '\0';
      
      strcpy(bim_erab,bimStr.c_str());
      kendu_marka_lex(bim_erab,bim_erab,0);
      bihur_asteris_maj(bim_erab,bim_erab);

      analisi_erab = bihur.aldatuSarInfo(analisia,bim_erab,SARda);


      if(m==0) {/* idatzi burukoa */
	if (irteera_parentizatua) {
	  string shitza = bihur.bihurtu_xerox_lemati(hitza);
	  strcpy(hitza,shitza.c_str());
	}
	inprimatu_goiburukoa(hitza, 'A', emaitza);
	*beste_analisia = 1;
      }
      m++;
//       if (m>1 && deslok) {
// 	m = bihur.desanbEratorpena(m,anal,motak,distan);
//       }
      // ez du zentzurik, erabiltzailearen lexikoan topatutakoa baino ez da gehituko
      strcpy(analErabLex,analisi_erab.c_str());

      if (errom_da) {
	errom_da = 0;
	inprimatu_estandar_analisia(analErabLex,beste_analisia,lema_ident,emaitza);
	errom_da = 1;
      }
      else
	inprimatu_estandar_analisia(analErabLex,beste_analisia,lema_ident,emaitza);
    }	    
  }
  return m;
}


