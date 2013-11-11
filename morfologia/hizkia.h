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


/*** NEREA : 94/2/7 Alexandre */
#if (defined(MACINTOSH))
#define strdup(_str_)  ((char *) strcpy ((char *) malloc(strlen(_str_) * sizeof(char)), _str_))
#endif
/******************************/

#define ONDO 0
#define ERR_LEX 1
#define ERR_FIL 2
#define TESTU_ZATI_BUK 3
#define E_O_F 4

#define TAM_TESTU_ZATI 512

#define ELKAR 1
#define BATCH 2
#define ELKAR_MARK 3

#define FILONDO_MARKA '\4' 
#define FILJARRA_MARKA '\5'

/* TESTU MARKATUAREN FITXATEGIAN AGERTUKO DIREN MARKAK HONAKOAK DIRA: */

#define OKERMARK '\1' 
#define FILOKER_MARKA '\2' 
#define MARKA_BLOKE_BUK '\7'	
#define HITZ_AMAIERA_MARKA '\10' /* \0x8 */


#define KAR_DESEGOKI	1    /* filtroak espero ez den karakterea topatu du*/
/*** NEREA : 94/3/23 */
#define HITZ_LUZEEGIA   2    /* hitz-bufferrak onar dezakeena baino luzeago */
#define ZEN_DEKL	3    /* gaizki deklinatutako zenbakia */
#define DEKL_SIGLAK	4    /* gaizki deklinatutako siglak */
#define SIGLA		5    /* siglak ez daude hiztegian */
#define LAB_DEK     6    /* laburdura desegokia, edota gaizki deklinatua */


#define KODERIK_EZ	-1   /* bestelakoetan ez da mezurik ematen */

#define SBUK '\3'		/* Fitxategia bukatzen denean bufferrean sartu behar
						   den karakterea. Filtrorako behar beharrezkoa */
#define SBUKA "\3"		/* SBUK aldatzekotan hau ere */


/* MARKAK ALDATU BEHAR IZANGO BALIRA KONTUTAN IZAN BEHAR DENA:
	- MARKA_BLOKE_BUK eta HITZ_AMAIERA_MARKA filtroak behar dituen 
	  marken desberdinak izan behar dute.
	  Filtroak erabili behar dituen markak:
	  * \0x1 			\0x2 			\0x4 		\0x5 		\0x6
		OKERMARK		FILOKER_MARK    
		KAR_DESEGOKI    HITZ_LUZEEGIA	ZEN_DEKL	DEKL_SIGLAK	SIGLA

      * \0x3
		SBUK
*/



#define LEKU_IZENA 1
#define PERTSONA_IZENA 2
#define IZENA 3
#define ADJETIBOA 4
#define ADITZA 5
#define SIGLAKK 6		/*ALDAKETA*/
#define BESTEA 7


#define KMAXHITZ 80 /*** NEREA : 94/6/9 */

#define KMAXIZEN 200 /*** NEREA : 94/5/26 erabiltzailearen hiztegiaren izenaren
										  luzera maximoa */

#define PROPMAX 10

/*
extern int hasieraketa(); 
extern int hasiera_zuzen(); 
extern int ireki_erab_morfemategia(char *izena, int sortu, int info_morfo); 
extern void reset_erab();
extern void switch_filtro(int balioa);
extern int egiaz_zuzen_hitza(char *buffer,int ind_buf,int modua,char *hitza,char *hitza_fil,int mezu_kodea);
extern int proposamenak_sortu(char *hitza, char *proposamenak[]);
extern int swap_erab(int lexiko_berria);   
extern int erantsi_erab(char *lema, int mota, int r_gogorra);  
extern int ezabatu_erab(char *lema, int mota, int r_gogorra);
*/

/* MAIUSKULEN ARAZOA KONPONTZEKO */
#define ASTERIS '9' /* XEROXEKO TRESNETAN * GAZIKI DABIL */
#define ASTERIS_R "9r" /* XEROXEKO TRESNETAN * GAZIKI DABIL */
#define ASTERIS_A "9a" /* XEROXEKO TRESNETAN * GAZIKI DABIL */
#define ASTERIS_X '*' /* XEROXEKO TRESNETAN * GAZIKI DABIL */
 
