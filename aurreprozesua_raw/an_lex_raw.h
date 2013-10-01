#ifndef AN_LEX_RAW_H
#define AN_LEX_RAW_H

#include "automata.h"
#include "status_raw.h"
#include "file_mng_raw.h"
#include "token_raw.h"
#define MAX_STRING 1500+1
using namespace std;

class anLexRaw
{
 statusRaw aurrekoa;      // badaezpada aurreko token-a eta sarreraren estadua gorde
 statusRaw azkena;        // azken token-a eta sarreraren estadua gorde
 automata aurre_auto;  // transizio posibleak eta bestelako informazioa
 fileMngRaw *sarrera;    // sarrera (fitxategia edo buffer bat)
 string paragrafoa;
 int hasierapar;
 int trans_berria(char *kar);  
                      // hurrengo karakterea lortu eta transizioa egin
public:

       anLexRaw();      // hasieraketa funtzioa
void   init(char *auto_izena, fileMngRaw *fitx);
                      // hasieraketa funtzioa

 void  reset();       // sarrera reseteatu
 void  reset(fileMngRaw *fitx);
                      // sarrera berria fitx-en eta hasieratu
 void  back();        // aurreko statusera itzuli

 int   next_token();  
                      // hurrengo tokena lortzen duena

 void  back_token(long offsetaa);// tokenaren barruko aurreneko tokenera itzuli
 // hau -edo -eta agertzen direnerako

 tokenRaw e_azkena();    // azken tokena ematen duena

//       ~anLexRaw();     // suntsitzailea

};

#endif // AN_LEX_RAW_H

