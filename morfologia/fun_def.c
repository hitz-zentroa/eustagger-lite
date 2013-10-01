#include "hizkia.h"
#define FUNDEF
#include "filtro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef __EXEKU__

#include "tamaino.h"
#include "klaseak.h"
#include "externs.h"

char bufferra[BUFFERTAM+2];      


void bufferra_bete(FILE *fitx,int *zen)
      { int n; 

	   if (*zen == BUFFERTAM)
	   {
        *zen = 0;
        n=fread(bufferra,sizeof(char),BUFFERTAM,fitx);
        if(feof(fitx)) bufferra[n]=SBUK;
        else bufferra[n] = MARKA_BLOKE_BUK; 
		bufferra[n+1] = '\0';
       }
       else
	   {
		char aux[KMAXHITZ_FIL_GABE];
		int l;

        aux[0] = '\0';
		l = strlen(&bufferra[*zen]) - 1;
		strncpy(aux,&bufferra[*zen],l);
		aux[l] = '\0';
		bufferra[0] = '\0';
		strcpy(bufferra,aux);
        n=fread(&bufferra[l],sizeof(char),BUFFERTAM-l,fitx);
        if(feof(fitx)) bufferra[l+n]=SBUK;
        else bufferra[l+n] = MARKA_BLOKE_BUK; 
		bufferra[l+n+1] = '\0';
		*zen = 0;
		}
      }

/*** NEREA : 93/12/15 : filtroak onartzen ez dituen karaktereak filtratzeko */
int jarraitu_begiratzen (char k)
 /*char k;*/ /*** NEREA : 94/3/21 */
 {
   int i=0,j=0;
   unsigned char kar; /*** NEREA : 94/5/24 */

   kar = (unsigned) k; /*** NEREA : 94/5/24 */
/*** NEREA : 94/3/21 : 8 biteko ASCII karaktereak onar ditzan */
   if (((int)kar >= 128) && ((int)kar <= 255)) /*** NEREA : 94/5/24 */
      return(1);
/**************************************************************/

   while (i<MULTZO_MAX)
   {
	 while (multzoak[i][j]!= '\0')
	 {
	   if (multzoak[i][j] == k)
		  return(1);  
		  /*** filtroak onartzen dituen karaktereen artean dago */
       j++;
     }
	 i++;j=0;
   }
   return(0);
   /*** filtroak ez du onartzen, beraz, ez da automata mugitu behar */
 }
/*****************************************************************************/

/*** NEREA : 94/3/22 */
int pasa_oker_dagoenean(int hitfigabeluz,int hitfiluz,char *xlin,
                         char *fil,char *bufferra,int *zen,
			 int indize,char klasea,char filmarka[3])
   {
	int k;
	
    *zen = *zen - 1;
	k = bufferra[*zen];
	*zen = *zen + 1;
    hitfigabeluz--;
	if (!filtratu(k)) /*** NEREA : 94/5/3 */
      hitfiluz--;
    while ((strchr(BEREIZGARRI_GIDOI_GABE,k)==NULL)&&(k!=SBUK)
		   &&(hitfigabeluz < KMAXHITZ_FIL_GABE-2))
      { 
       xlin[hitfigabeluz] = k;
       if (!filtratu(k))
         if (hitfiluz < KMAXHITZ-1)
           {
            fil[hitfiluz] = k;
            hitfiluz++;
           }
       hitfigabeluz++;
       k= bufferra[*zen];
       if (k == MARKA_BLOKE_BUK) 
         {
          *zen = indize;
          return(TESTU_ZATI_BUK);
         }
       *zen = *zen + 1;
      }
    while ((strchr(BEREIZGARRIAK,k)!=NULL)&&(k!=SBUK)&&
		   (hitfigabeluz < KMAXHITZ_FIL_GABE-2))
      { 
       xlin[hitfigabeluz] = k;
	   if (hitfiluz < KMAXHITZ-1)
		 {
		  if (!filtratu(k)) /*** NEREA : 94/5/3 */
			{
             fil[hitfiluz] = k;
             hitfiluz++;
            }
         }   
       hitfigabeluz++;
       k= bufferra[*zen];
       if (k == MARKA_BLOKE_BUK) 
         {
          *zen = indize;
          return(TESTU_ZATI_BUK);
         }
       *zen = *zen + 1;
      }
    if ((hitfiluz >= KMAXHITZ-1) || (hitfigabeluz >= KMAXHITZ_FIL_GABE-2))
	  klasea = (char) HITZ_LUZE_KLASE;
    *zen = *zen - 1;
    xlin[hitfigabeluz]='\0';
    fil[hitfiluz]='\0';  
    filmarka[0] = FILOKER_MARKA;
    filmarka[1] = klasea;
    filmarka[2] = '\0';
    return(ERR_FIL);
   }

int hitza_tratatu(char *xlin,char *fil,int *zen,int indize,
                  char klasea,char filmarka[3]) /*** NEREA : 94/3/23 */
{
 int zenbat_aurrera,errepikakor=0;

 zerhitz((int)klasea,xlin,fil,filmarka,&zenbat_aurrera); 
 if (*zen != indize + zenbat_aurrera) 
   errepikakor = 1;
 *zen = indize + zenbat_aurrera;
 if (*filmarka==FILJARRA_MARKA) 
   {
    if (errepikakor) 
      filmarka[1] = HITZ_NORMALA;
    else 
      filmarka[1] = klasea;
    filmarka[2] = '\0';
    *zen = *zen - 1;
    return(ERR_LEX);
   }
 else 
   filmarka[1] = '\0';
 if (filmarka[0] == FILONDO_MARKA)
   {
     if (klasea == IDENTIFIKATZAILEA) {
       filmarka[1] = klasea;
       filmarka[2] = '\0';
     }
    *zen = *zen - 1;
    return (ONDO);
   }
 return (ONDO);
 }


int aurkitu_zutabea(char k)
 /*char k;*/ /*** NEREA : 94/3/21 */
 {int i;
  unsigned char kar; /*** NEREA : 94/5/24 */

  i = 0;
  kar = (unsigned) k; /*** NEREA : 94/5/24 */

/*** NEREA : 94/3/21 : 8 biteko ASCII karaktereak onar ditzan */
   if (((int)kar >= 128) && ((int)kar <= 255) &&  /*** NEREA : 94/5/24 */
       (k != NI_T) && (k != NI_H)) 
      return(MULTZO_MAX); 
/**************************************************************/
 
  while ((strchr(multzoak[i],k) == NULL) && (i < MULTZO_MAX))
   {  i++;}
   
  return(i);
       
   } 
           
int zenbakia(char ka)
 /*char ka;*/
 {if(strchr(ZIFRA,ka) != NULL) return(1);
                           else return(0);
 }


#endif /*__EXEKU__*/
        
int ken_majusk(char str[])
{
int i,j,l;
l=strlen(str);
for(i=0,j=0;i<l;i++)
  if(str[i]!=ASTERIS) { 
    str[j]=str[i];
    j++;
  }
str[j]='\0';
return(0);
}
int ken_majusk_marratxo(char str[]) 
/* aurreko bera baina marratxo ondoren maiuskula utziz */
{
int i,j,l;
l=strlen(str);
for(i=0,j=0;i<l;i++)
  if(str[i]!=ASTERIS) { 
    str[j]=str[i];
    j++;
  }
  else if (j>0 && str[j-1] == '-') {
    str[j]=str[i];
    j++;
  }
str[j]='\0';
return(0);
}

int maius(char ka)
 {if (strchr(MAJ,ka) != NULL) return(1);
                          else return(0);
 }                          
 
int filtratu(char k)
 {
  unsigned char kar ; /*** 94/5/24 */

	kar = (unsigned) k ; /*** 94/5/24 */
	if (((int)kar >= 128) && 
	    /* ((int)kar <= 255) &&  */
	    (k != NI_T) && (k != NI_H)) /*** 94/5/24 */ 
	   return (1);
	if ((strchr(ALF,k)!=NULL)||(strchr(MAJ,k)!=NULL)||(strchr(ZIFRA,k)!=NULL))
	   /*** 94/5/24 */
       return(0);
    else   return(1);
 }                           
         


#include <ctype.h>

void kendu_maj_asteris(char *st1, char *st2)
{
int i,j;
for (i=j=0;st1[i]!='\0';i++)
	if(st1[i]!=ASTERIS) st2[j++]=st1[i];
st2[j]='\0';
return;
}

void bihur_maj_asteris(char *st1, char *emai)
/* eineak ere bihurtzen dira */
{
  int i,j;
  char st2[200];
  st2[0] = '\0';
  /*  strcpy(st2,st1);*/
  for (i=j=0;st1[i]!='\0';i++)
    if (isupper(st1[i])&&(st1[i]!=NI_T)&&(st1[i]!=NI_H))
      {
	st2[j++]=ASTERIS;
	st2[j++]=tolower(st1[i]);
      }
    else if(st1[i]==NI_H)
      {
	st2[j++]=ASTERIS;
	st2[j++]=NI_GUZTIENTZAT;
      }
    else if(st1[i]==NI_T)
      {
	st2[j++]=NI_GUZTIENTZAT;
      }
    else if (st1[i]==' ') /*** NEREA : 93/11/13 */
      {
	st2[j]='_';
	i++;
      } /*** NEREA : 93/11/13 */
    else if (st1[i] != '\222' && st1[i] != '\'' && st1[i] != '\"') st2[j++]=st1[i];
  st2[j] = '\0'; /*** NEREA : 93-9-20 !!!!!!!!!!!!!!! */

  strcpy(emai,st2);
  /*  free(st2);*/
/*** NEREA : 93-9-20 erabiltzailearen lexikoa dela eta */
/* if((!strcmp(&st2[j-2],ASTERIS_R))&& st2[0]!=ASTERIS)  */
/* 	{ */
/* 	st2[j-2]='R'; */
/* 	st2[j-1]='\0'; */
/* 	} */
/* if((!strcmp(&st2[j-2],ASTERIS_A))&& st2[0]!=ASTERIS) ALDAKETA*/
/* 	{ */
/* 	st2[j-2]='A'; */
/* 	st2[j-1]='\0'; */
/* 	} */
}

void bihur_asteris_maj(char *st1,char *emai)
{
  int i,j;
  char st2[200];
  st2[0] = '\0';
  /*  strcpy(st2,st1);*/
  for (i=j=0;st1[i]!='\0';j++)
    if (st1[i]==ASTERIS)
      {
	i++;
	st2[j]=(st1[i]==NI_GUZTIENTZAT)?NI_H:toupper(st1[i]);
	i++;
      }
    else if(st1[i]==NI_GUZTIENTZAT) {
      st2[j]=NI_T;
      i++;
    }
    else 
      if (st1[i]=='_') {  /*** NEREA : 93/11/13 */
	st2[j]=' ';
	i++;
      } /*** NEREA : 93/11/13 */
      else st2[j]=st1[i++];
  st2[j] = '\0'; /*** NEREA : 93-9-20 !!!!!!!!!!!!!!! */
  strcpy(emai,st2);
  /*free(st2);*/
}

