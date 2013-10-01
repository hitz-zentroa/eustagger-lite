#ifndef FILE_MNG_RAW_H
#define FILE_MNG_RAW_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "token_raw.h"

#define MAX_BUFFER 100000       // irakurriko dugun lerroaren luzera maximoa
using namespace std;

class fileMngRaw
{
  
  ifstream fitxategia;           // sarrera fitxategia
  bool sarreraAmaitua;           // fitxategiaren bukaerara iritsi garen
  bool sarreraEstandarra;        // sarrera estandarra irakurtzen ari al gara?
  string buffer;                 // uneko testu zatia gordetzeko
  int bufferLuzera;              // uneko testu zatiaren luzera
  int posizioa;                  // testu zatian mugitzeko indizea
  int stdLerroa;                 // sarrera estandarra irakurtzen ari bagara zenbat lerro irakurri ditugun
  string sarreraIzena;           // tokenizatutako fitxategiaren izena gordetzeko

 public:
  
  // Eraikitzaileak

  fileMngRaw();                               
  fileMngRaw(bool, bool, bool, const string &, int, int, int);
  fileMngRaw(const fileMngRaw &);
  
  void init(const string &);                // hasieraketa funtzioa
  void reset();                             // fitxategia lehen posizioan kokatu
  int back(long offset);                    // fitxategia birkokatu
  int back_token(long offset_pre,long offset);                    // fitxategia birkokatu
  char get();                               // hurrengo karakterea lortu fitxategitik
  long non();                               // offset-a ematen du
  void close();                             // fitxategia itxi
  int eof();                                // fitxategia bukatu den

  ~fileMngRaw();                              // funtzio suntsitzailea
  
 private:
  
  void kargatuStdBufferra();                // bufferra berritu sarrera estandarrarekin

};

#endif // FILE_MNG_RAW_H

