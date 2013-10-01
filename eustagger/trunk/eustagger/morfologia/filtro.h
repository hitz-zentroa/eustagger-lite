#ifndef FILTRO_H
#define FILTRO_H
#include "hizkia.h"
 
# define MAIZ_EN 0
# define OROK_EN 1
# define ERAB_EN 2
 
# define HUTSA   0
# define CONCR   1
# define SET     2
# define ANY     3
 
#ifndef _BOOL_H_
#include "bool.h"  /*** 94/2/9 */
#endif /* _BOOL_H_ */

# define ESTADU_MAX 68 /*** 98/12/11 */
# define MULTZO_MAX 14
# define ESTADU2_MAX 7
# define MULTZO2_MAX 11
#define KAK '\"'
#define GID "'-''_'"
#define GIDOIA '-'
 
#define ZIFRA "0123456789"
#define BOK "236789"
#define KON "45"
#define PAR "2468"
#define IMPAR "13579"
#define ZEN "123456789"
#define BOKALE "aeiou" /*** 94/4/25 */
#define ERROMATAR "IVXLCDM" /*** 94/5/27 */
#define LEN_ERROM 7 /*** 96/11/24  aurrekoaren luzera */
 
# define NI_T    ((char)241)     /* enie txiki */
# define NI_H    ((char)209)     /* enie handi */
 
#define NI_GUZTIENTZAT '8' 

#define ALF "abcdefghijklmn\361opqrstuvwxyz"
#define MAJ "ABCDEFGHIJKLMN\321OPQRSTUVWXYZ"
 
#ifdef FUNDEF
 char *multzoak[MULTZO_MAX]=
     {
       ":@",
       " \t",
       "\n\x0D",
       "1234567890",
       "abcdefghijklmn\361opqrstuvwxyz\x1F",
       "ABCDEFGHIJKLMN\321OPQRSTUVWXYZ\x1F",
       "-",
       "_",
       ",",
       "\"",
"\x0E\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E^~#@$&`|'[];*+:=()<>\\/{}%\x96\x98\x99\x9C\x9D",
       "?!",
       ".",
       SBUKA,
       } ;
#endif


#define BEREIZGARRIAK "\x0E\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E^~#@$&*+=`|'.'','' ''\t''\n'{};:><?/()%![]-_\x96\x98\x99\x9C\x9D'\"''\''"



#define BEREIZGARRI_GIDOI_GABE "\x0E\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E^~#@$&*+=`|'.'','' ''\t''\n'{};:><?/()%![]_\x96\x98\x99\x9C\x9D'\"''\''"


#endif /*FILTRO_H*/
