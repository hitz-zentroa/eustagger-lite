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


/* ***************************************************
 * File name     : lema_aldaera.h
 * Version       : 1.0
 * Date          : 1999/05/19
 * Last Revision : 1999/05/19
 * Author        : Aitor Maritxalar (jibmagoa@si.ehu.es)
 * Purpose       : 
 * Use           : 
 *               : 
 * **************************************************** */

# ifndef LEMA_ALDAERA
# define LEMA_ALDAERA

#include <ctype.h>

/*# define KENTZEKOAK "E$:/!^%~"
# define R_MARKAK "RQ"
# define A_ORGANIKOA_MARKAK "A#@&"
# define N_MARKA 'N' */
/* Hauek $MORFOLOGIA_HOME/xfl/kendu_marka_lex.c fitxategian eguneratuko dira */

# define NI_T    'ñ'     /* enie txiki */
# define NI_H    'Ñ'     /* enie handi */


void bihur_asteris_maiuskula( char* sarrerakoa, char* irteerakoa );
void ken_marka_hitzetik( char* hitza , char* markatua );

# endif 
