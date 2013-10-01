/*TAIPAK.H*/
#include "filtro.h"

/*typedef int estaduak;*/ /*** ALEX */
#ifndef __EXEKU__
typedef struct {int alt;
                int zab;
                int estaduak[ESTADU_MAX][MULTZO_MAX];
                bool final[ESTADU_MAX];
                int klase[ESTADU_MAX];
                }automata_lag;
#else
typedef struct {int alt;
                int zab;
                int estaduak[ESTADU_MAX][MULTZO_MAX];
                bool final[ESTADU_MAX];
                int klase[ESTADU_MAX];
                }automata;
#endif /*__EXEKU__*/
typedef char *mul1;                
                
typedef struct {
                mul1 elementuak;
               }mul2;
               

