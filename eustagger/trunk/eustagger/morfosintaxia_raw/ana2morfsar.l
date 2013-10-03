/* ***************************************************
 * **************************************************** */

%{

#include <stdlib.h>
#include <stdio.h>
#include <string>


int ana2morfsar_lerro_kop = 1;
std::string analisi_mota = "A";
/*AnaType analisi_mota(ESTANDAR_ANATYPE,0);*/
YY_BUFFER_STATE bStateAna2Morfsar;

%}

delim	 [ \t]
huts	 {delim}+
letra	 [A-Za-z\321\361]
markak	 [*-_@+<>]
kombik   ["]
digito	 [0-9]
literal  \"[^ \)\-"]+\"[^ \)]+\"|\"[^"]*\"
sinbolo	 [^ \n\t\)\(\"]+|[^ \n\t\)\(\"]+\"[^ \n\t\)\(\"]+
/*sinbolo	 ({letra}|{digito}|{markak})+*/
komen    ^[\/].*

%%

{komen}         {ana2morfsarlval.str = new string; *ana2morfsarlval.str = ana2morfsartext; return( t_forma_lerro ); }
{huts}		{}
anal            { return( t_anal ); }
"(forma"        { return( t_forma ); }
ald             { return( t_ald ); }
"(lema"		{ return( t_lema ); }
morf		{ return( t_morfema ); }
STwol		{ return( t_stwol ); }
ATwol		{ return( t_atwol ); }
"Sarrera"       { ana2morfsarlval.str = new string; *ana2morfsarlval.str = ana2morfsartext; return( t_sarrera ); }
"Aldaera"       { ana2morfsarlval.str = new string; *ana2morfsarlval.str = ana2morfsartext; return( t_aldaera ); }
"SAR"           { ana2morfsarlval.str = new string; *ana2morfsarlval.str = ana2morfsartext; return( t_sarrera ); }
"ERR"           { ana2morfsarlval.str = new string; *ana2morfsarlval.str = ana2morfsartext; return( t_erroa ); }
FS1	        { return( t_funtzioak ); }
FS2	        { return( t_funtzioak ); }
FS3	        { return( t_funtzioak ); }
FS4	        { return( t_funtzioak ); }
FS5	        { return( t_funtzioak ); }
FS6	        { return( t_funtzioak ); }
FS7	        { return( t_funtzioak ); }
FS8	        { return( t_funtzioak ); }
FS9	        { return( t_funtzioak ); }
FS10	        { return( t_funtzioak ); }
"("		{ return( t_paren_ireki ); }
")"		{ return( t_paren_itxi ); }
"$"             { return( t_dolar ) ; }
","             { return( t_koma ); }
"%A"           { 
                  ana2morfsarlval.str = new string; *ana2morfsarlval.str = "A" ;
                  analisi_mota = *ana2morfsarlval.str;
		  return( t_erregela );
                }
"%G"           { 
                  ana2morfsarlval.str = new string; *ana2morfsarlval.str = "G" ;
                  analisi_mota = *ana2morfsarlval.str;
                  return( t_erregela );
                }
"%T".*         {  ana2morfsarlval.str = new string;
                  string cpKopia, cpKopiaDig;
                  string::size_type dig;
                  cpKopia = ana2morfsartext;
                  if ((dig = cpKopia.find_last_of(":")) == string::npos) dig = 0; 
                  else dig++;
                  stringstream atrib;
                  cpKopiaDig = cpKopia.substr(dig,string::npos);
                  atrib << "T" << cpKopiaDig;
                  *ana2morfsarlval.str = atrib.str();

                  analisi_mota = *ana2morfsarlval.str;
		  return( t_erregela );
                }

LHB             { ana2morfsarlval.str = new string;
                  *ana2morfsarlval.str = "lotura-HBn";
                  return(t_lhb);
                }
{sinbolo}	{
                  ana2morfsarlval.str = new string;
                  if (!strcmp(ana2morfsartext,"NRI")) 
                    *ana2morfsarlval.str = "NORI";
                  else if (!strcmp(ana2morfsartext,"NRK")) 
                    *ana2morfsarlval.str = "NORK";
                  else *ana2morfsarlval.str = ana2morfsartext;
                  if (!strcmp(ana2morfsartext,"Elkarketa")) return( t_sinbolo_list );
                  if (!strcmp(ana2morfsartext,"FSL")) return( t_sinbolo_list_sym );
                  if (!strcmp(ana2morfsartext,"Hobetsiak") || 
		      !strcmp(ana2morfsartext,"Estandarrak") )
                    return( t_sinbolo_set );
                  return( t_sinbolo ); 
                }
{literal}       { /* Kendu hasiera eta amaierako komatxoak */
                  string tmp = ana2morfsartext;
                  ana2morfsarlval.str = new string;
                  *ana2morfsarlval.str = tmp.substr(1,tmp.length()-2);
                  return(t_literal);
                }
.               { fprintf(stderr,"ana2morfsar.l: Errore lexikoa %d. lerroan ==> %s\n",ana2morfsar_lerro_kop, ana2morfsartext); exit(-1); }
"\n"            { ana2morfsar_lerro_kop++; }

%%

int ana2morfsarwrap(){
   return (1);
}

void bufferParse(char *buffer, int size) {
  bStateAna2Morfsar = yy_scan_buffer(buffer,size);
  yy_switch_to_buffer(bStateAna2Morfsar);
  yyparse();
  yy_delete_buffer(bStateAna2Morfsar);
}
