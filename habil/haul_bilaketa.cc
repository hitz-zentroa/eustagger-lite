#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <locale.h>
#include "ald_orok.h"
#include "getenvvar.h"


extern int hat_kargaparse(void);
extern FILE *hat_kargain;

/*** Aldagai orokorrak */
FILE *irteera_fitx;
char *testu_buffer;
int buffer_size;

// Hautazko aldagai bat -H HATak bakarrik ateratzeko. Defektuz testuan
// tartekaturik aterako dira.

main(int argc, char *argv[])
{
  FILE *jat_fitx;
  std::string tmp,tmp1;

  setlocale(LC_ALL,"es");
  if (argc <= 1)
    {
      printf("Parametro-kopuru okerra, gutxienez fitxategi baten izena!\n");
      exit(1);
    }
  
  tmp = getEnvVar("IXA_PREFIX");
  if (tmp.length() == 0) {
    printf("IXA_PREFIX ingurune-aldagaia ez dago definitua\n");
    exit(EXIT_FAILURE);
  }

  // tmp += "/var/habil/";
  tmp = "/sc01a4/users/jipecran/svn_lana/Eustagger/var/habil/";
  tmp += SEG_FITX;

  if ((jat_fitx = fopen(tmp.c_str(),"r")) == NULL)
    {
      fprintf(stderr,"Errorea %s fitxategia irekitzean\n",tmp.c_str());
      exit(EXIT_FAILURE);
    }

  int length;
  std::ifstream t(argv[1]);

  if (!t) { // Horrela begiratzen da errorerik egon den ifstream-etan?
    fprintf(stderr,"Errorea %s fitxategia irekitzean\n",argv[1]);
    exit(EXIT_FAILURE);
  }

  t.seekg(0, std::ios::end);
  length = t.tellg();
  t.seekg(0, std::ios::beg);
  testu_buffer = (char *) malloc(length+2);
  t.read(testu_buffer, length);
  t.close();
  testu_buffer[length+1] = '\0';
  buffer_size = length +2;
  
  argv[1][strlen(argv[1])-4] = '\0';
  tmp = argv[1];
  tmp += PHAT;

  if ((irteera_fitx = fopen(tmp.c_str(),"w")) == NULL)
    {
      fprintf(stderr,"Errorea %s fitxategia irekitzean\n",tmp.c_str());
      exit(EXIT_FAILURE);
    }

  hat_kargain = jat_fitx;
  hat_kargaparse();

}
