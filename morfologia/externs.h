#include <stdio.h>
#include "taipak.h"
extern void aztertu_zenbakia( char *filtratua, char *hitza);
extern void bufferra_bete(FILE *fitx,int *zen);
extern int jarraitu_begiratzen (char k);
extern int filtratu(char);
extern int pasa_oker_dagoenean(int hitfigabeluz,int hitfiluz,char *xlin,
                         char *fil,char *bufferra,int *zen,
			 int indize,char klasea,char filmarka[3]);
extern int hitza_tratatu(char *xlin,char *fil,int *zen,int indize,
                  char klasea,char filmarka[3]);
extern int aurkitu_zutabea(char k);
extern int zenbakia(char ka);
extern int maius(char ka);
extern void kendu_maj_asteris(char *st1, char *st2);
extern void bihur_maj_asteris(char *st1, char *st2);
extern void bihur_asteris_maj(char *st1,char *st2);
extern int lor_hitza(char *bufferra, int *zen,char * xlin, char *fil, char filmarka[3]);
#ifndef __EXEKU__
extern int irakur_automata(char *fp,automata_lag *aut,int erre,int zut);
#else
extern int irakur_automata(char *fp,automata *aut,int erre,int zut);
#endif /*__EXEKU__*/

#ifdef __EXEKU__
extern int lor_hitza_markatua(char *bufferra,int *zen,char *fil,char filmarka[3]);
extern void zerhitz(int mota,char *hitza,char *fil,char *filmarka,int *zenbat_aurrera);
#endif /*__EXEKU__*/
/* extern char *Maiuskulak(char *hitz,char *atzizki); */
extern void Maiuskulak(char *hitz,char *atzizki, char *hitz_ald);
extern int erromatarra_da (char *hitza);
extern int berdinak (char *lehena, char *bigarrena);
extern int lehena_pasa(char *dena);
