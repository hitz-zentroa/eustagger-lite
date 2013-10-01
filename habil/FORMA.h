#ifndef FORMA_H
#define FORMA_H

#include <list>
#include <string>
#include "int_bikote.h"

/* typedef lista<int_bikote> indize_l; */

class FORMA
{
// Aldagaiak

  std::string    Hitza;       // Forma gordetzeko.

public:

  indize_l  indizeak;    // Forma agertzen den HATen indizeak eta hitzaren posizioak.

// Eragiketak

           FORMA();
    // Hasieraketa-funtzioa.

           FORMA(const FORMA &f);
    // Kopia-hasieraketa funtzioa.

  void  Hasieraketa(std::string &H, int i, int p);
    // Hitza eta lehen indizea eta posizioa gordetzen ditu.

  int   konparatu(std::string &H);
    // H Hitza-rekin konparatzen du.
    // Emaitza : <0 --> H < Hitza
    //            0 --> H == Hitza
    //           >0 --> H > Hitza

  std::string eman_Hitza();
    // forma ematen digu

  int   operator <(FORMA &f);

  int   operator <=(FORMA &f);

  int   operator >(FORMA &f);

  int   operator >=(FORMA &f);

  int   operator ==(FORMA &f);

  int   operator !=(FORMA &f);

        ~FORMA();
    // funtzio suntsitzailea.

  FORMA operator =(const FORMA &f);
    // Asignazioa.
};

#endif
