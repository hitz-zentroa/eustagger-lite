/* ***************************************************
 
 * **************************************************** */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lema_aldaera.h"
#include <stdlib.h>


void bihur_asteris_maiuskula(char *st1,char *st2) {
 int i,j;
 for (i=j=0;st1[i]!='\0';j++)
  if (st1[i]=='*')
    {
      i++;
      st2[j]=(st1[i]=='\261')?'\221':toupper(st1[i]);
      i++;
    }
  else 
    if (st1[i]=='_') {  /*** 93/11/13 */
      st2[j]=' ';
      i++;
    } /*** 93/11/13 */
    else st2[j]=st1[i++];
 st2[j] = '\0'; /***93-9-20  */
}

/* ************************** */
/* Marka berezien tratamendua */
/* ************************** */


extern int kendu_marka_lex(char lex[], char azal[], int maj_ken_al);

void ken_marka_hitzetik(char *hitza,char *markatua)
{
 int l;

 hitza[0] = '\0';
 strcpy(hitza,markatua);
 l = strlen(markatua);
 
 kendu_marka_lex(hitza,markatua,0);
 bihur_asteris_maiuskula(markatua,hitza);

}

