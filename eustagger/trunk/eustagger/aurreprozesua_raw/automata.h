#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <string>
//#include "clstring.h"
using namespace std;

class automata
{
 int    **transizioak;
 string *multzoak;
 int    *finalak;
 string *etiketak;
 int    *tratamenduak;
 int    estadua;
 int    LERROAK;
 int    ZUTABEAK;

 public:

         automata();              // hasieraketa funtzioak
  int    init(char *fitxategi);

  void   reset();                 // automata hasierako estaduan jartzen du

  int    mugitu(char kar); 
                                  // hurrengo trantsizioa bilatzen du emandako
                                  // karakterearen arabera. Trantsizio posiblea
                                  // den ala ez itzultzen du emaitza gisa.

  int    bukaerakoa();            // estadua bukaerakoa den esaten digu

  string etiketa();               // estaduari dagokion etiketa itzultzen du

  int    tratamendua();           // estaduari dagokion tratamendua itzuli

        ~automata();              // funtzio suntsitzailea
};

#endif // AUTOMATA_H

