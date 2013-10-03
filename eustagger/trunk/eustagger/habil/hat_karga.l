%{
extern "C"
{
int yylex(void);
}

#include "hat_karga.tab.hh"
#include <stdio.h>
#include <string.h>
#include "bereiz_etq.h"

int puntuazioa_da(char *etq)
{
 if ((strcmp(etq,PUNTUA) == 0) ||
     (strcmp(etq,GALDERA) == 0) ||
     (strcmp(etq,PUNTU_KOMA) == 0) ||
     (strcmp(etq,ESKLAM) == 0) ||
     (strcmp(etq,BI_PUNTU) == 0))
   return 1;
 return 0;
}


int amaitu_bidalia=0;

YY_BUFFER_STATE bStateHat;
extern char *testu_buffer;
extern int buffer_size;

extern FILE *irteera_fitx;
extern int TARTEKATU;
extern int line;

%}
hitza           [a-z\361A-Z\321\.][a-z\361A-Z\321\-\+\*]*
forma           ^[a-z\361A-Z\321\.][^\n]*
zifrak          [0-9]+
lema            \"([^ ])*\"[ ]
osagaikop       \(OSAGAIAK\)
formada         \(FORMA\)
lemada          \(LEMA\)
seguruabai      \(BAI\)
seguruaez       \(EZ\)
komentarioa     ^[ \t]*OHAR:[^\n]+
informazioa     [A-Z\[\^][A-Z\_\+\\\(\)0-9\| \$\[\]\*\^s\-\@\<\>\?]+\)$
hat_informazioa \#[ \t]*[^\n]*

forma2          \/\<.[^\>]*\>\/
aldaera         \/([^ ])*\/[ ]
etiketa         \<[A-Z_\(\)]+\>\/
etiketa_haul    HAS_MAI
informazioa2    [A-Z\.][^\)]+
correct         ^[C|X]
%option noyywrap
%x testua
%%
{hitza}            {
                    hat_kargalval.str[0] = '\0';
                    strcpy(hat_kargalval.str,yytext);
                    return HITZA;
                   }
{etiketa_haul}     {
                    hat_kargalval.str[0] = '\0';
                    strcpy(hat_kargalval.str,yytext);
                    return ETIK_HAUL;
                   }
{forma}            {
                    int i=0;

                    while ((yytext[i]==' ') || (yytext[i] == '\t'))
                      /*** hasierako zuriguneak kendu */
                      i++;
                    hat_kargalval.str[0] = '\0';
                    strcpy(hat_kargalval.str,&yytext[i]);
                    i = strlen(hat_kargalval.str)-1;
                    while ((hat_kargalval.str[i] == ' ') || (hat_kargalval.str[i] == '\t'))
                      /*** bukaerako zuriguneak kendu */
                       i--;
                    hat_kargalval.str[i+1] = '\0';
                    return HAT_LEMA;
                   }
{zifrak}           {
                    sscanf(yytext,"%d",&hat_kargalval.zif);
                    return ZIFRA;
                   }
<INITIAL,testua>{lema}             {
                    hat_kargalval.str[0] = '\0';
                    strcpy(hat_kargalval.str,&yytext[1]); /*** hasierako " kenduta */
                    /* hasierako \" kenduta */
                    hat_kargalval.str[strlen(hat_kargalval.str)-2] = '\0';
                    /* bukaerako \" eta zuriunea kenduta */
                    return LEMAA;
                   }
{komentarioa}      {
                    int i=0;

                    while ((yytext[i]==' ') || (yytext[i] == '\t'))
                      /*** hasierako zuriguneak kendu */
                      i++;
                    hat_kargalval.str[0] = '\0';
                    strcpy(hat_kargalval.str,&yytext[i]);
                    i = strlen(hat_kargalval.str)-1;
                    while ((hat_kargalval.str[i] == ' ') || (hat_kargalval.str[i] == '\t'))
                      /*** bukaerako zuriguneak kendu */
                       i--;
                    hat_kargalval.str[i+1] = '\0';
                    return OHARRA;
                   }
<INITIAL,testua>"("                {
                    return PAR_IREKI;
                   }
<INITIAL,testua>")"                {
                    return PAR_ITXI;
                   }
"+"                {
                    return ERROA;
                   }
"*"                {
                    return ETENA;
                   }
"/"                {
                    return EZORD;
                   }
"|"                {
                    return PIPE;
                   }
{osagaikop}        {
                    return OSAGAI_KOP;
                   }
{formada}          {
                    return FORMA_DA;
                   }
{lemada}           {
                    return LEMA_DA;
                   }
{seguruabai}       {
                    return BAI;
                   }
{seguruaez}        {
                    return EZ;
                   }
{hat_informazioa}  {
                    int i=1; /*** lehen posizio # */

                    while ((yytext[i]==' ') || (yytext[i] == '\t'))
                      /*** hasierako zuriguneak kendu */
                      i++;
                    hat_kargalval.str[0] = '\0';
                    if (yytext[i] != '\0')
                      strcpy(hat_kargalval.str,&yytext[i]);
                    i = strlen(hat_kargalval.str)-1;
                    while ((hat_kargalval.str[i] == ' ') || (hat_kargalval.str[i] == '\t'))
                      /*** bukaerako zuriguneak kendu */
                       i--;
                    hat_kargalval.str[i+1] = '\0';
                    return HAT_INFO;
                   }
{informazioa}      {
                    int i=0;
                    yyless(yyleng-1);
                    while ((yytext[i]==' ') || (yytext[i] == '\t'))
                      /*** hasierako zuriguneak kendu */
                      i++;
                    hat_kargalval.str[0] = '\0';
                    strcpy(hat_kargalval.str,&yytext[i]);
                    i = strlen(hat_kargalval.str)-1;
                    while ((hat_kargalval.str[i] == ' ') || (hat_kargalval.str[i] == '\t'))
                      /*** bukaerako zuriguneak kendu */
                       i--;
                    hat_kargalval.str[i+1] = '\0';
                    return INFORMAZIOA;
                   }
<INITIAL><<EOF>> {
                   yyout = irteera_fitx;
                   fclose(yyin);

                   bStateHat = yy_scan_buffer(testu_buffer,buffer_size);
                   yy_switch_to_buffer(bStateHat); 

                   BEGIN(testua);
                   line = 1;
                 }
<testua><<EOF>>  {
                    if (amaitu_bidalia) { 
                      yy_delete_buffer(bStateHat); 
                      fclose(yyout);
                      return yytext[0];
                    }
                    else {
                      amaitu_bidalia = 1;
                      return AMAITU;
                    }
                 }

<INITIAL,testua>[ \t]   { 
                        }
<INITIAL,testua>[\n]    { 
                          line++;
                        }
<testua>{correct}       {
                         return CORRECT;
                        }
<INITIAL,testua>.       {
                        return yytext[0];
                        }
<testua>{forma2}        {
               hat_kargalval.str[0] = '\0';
               strcpy(hat_kargalval.str,&yytext[2]);
               /* hasierako /< kenduta */
               hat_kargalval.str[strlen(hat_kargalval.str)-2] = '\0';
               /* bukaerako >/ kenduta */
               return HITZ_FORMA;
              }
<testua>{aldaera}     {
               hat_kargalval.str[0] = '\0';
               strcpy(hat_kargalval.str,&yytext[1]); /*** / */
               /* hasierako / kenduta */
               hat_kargalval.str[strlen(hat_kargalval.str)-2] = '\0';
               /* bukaerako / eta txuria kenduta */
               return ALDAERA;
              }
<testua>{etiketa}     {
               hat_kargalval.str[0] = '\0';
               strcpy(hat_kargalval.str,&yytext[1]);
               /* hasierako < kenduta */
               hat_kargalval.str[strlen(hat_kargalval.str)-2] = '\0';
               /* bukaerako >/ kenduta */
               if (puntuazioa_da(hat_kargalval.str))
                 return ETIK_PUNT;
               return ETIK;
              }
<testua>{informazioa2} {
               hat_kargalval.str[0] = '\0';
               strcpy(hat_kargalval.str,yytext);
               return INFORMAZIOA;
              }
%%
