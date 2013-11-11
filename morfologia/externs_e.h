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


#ifndef _BOOL_H_
#include "bool.h"
#endif
#include <stdio.h>
#include "hizkia.h"

extern bool dago ( char *hitza );
extern void erantsi_dok(char *hitza);
extern int maiz_init (int init);
extern FILE *ireki_datu(char *,char *);
extern int strcmp2(const void *a, const void *b);
extern int strcmp3(const void *a, const void *b);
extern int dago_abisu ( char *hitza );
extern int propo_maiz_abisu(char *hitza,char hitz_zuzen[][KMAXHITZ],int *j);
extern void erantsi_dok_abisu(char *hitza,char hitz_zuzen[][KMAXHITZ],int *j);
extern int maiz_init_abisu (int init,FILE *hizt_fitx);
extern void reset_dok();
extern void markatu_hitza(char *hitza,char *markatua,int r_gogorra,int mota);
extern void ken_marka_hitzetik(char *hitza,char *markatua,int *r_gogorra,int mota);
extern char *zati1(char *hitza_fil_gabe);
extern char *zati2(char *hitza_fil_gabe);
extern char *zati3(char *hitza_mozteko);
extern int fil_oker_marka(char fil_marka);
extern int fil_ondo_marka(char fil_marka);
extern void marka_ipini(char *hitza, char *h_markatua, char *marka);
extern void ken_marka(char *thitzmar,char *thitz,char *marka);
extern void eranhitz(FILE *fitxategi,char *hitza);
extern int egiaztatu_zuzenketa(char *hitza);
extern int hasiera_filtro();
#ifdef FILTRO
extern int egiaz_zuzen_hitza(char *buffer, int *ind_buf, int modua, char *h_fil_gabe, 
                      char *hitz, int *mezu_kodea);
extern int kodea_eman(char marka,int *err_mota);
extern int egiaztatu_testua(char *sarrera_testua,char *testu_markatua,int *zenbat_huts);
#endif
extern int reset_mem_din();
extern int errore_tip(char *hitza,int *zenbat_tip,char hitz_zuz[][KMAXHITZ]);
