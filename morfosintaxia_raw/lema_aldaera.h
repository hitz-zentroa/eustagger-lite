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
