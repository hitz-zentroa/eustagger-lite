#ifndef IM_INFO_H
#define IM_INFO_H

#include <list>
#include "int_bikote.h"
#include "IM.h"

class IM_info
{
// Aldagaiak

  IM morfo;

public:

  indize_l indizeak;

// Eragiketak

  IM_info();

  IM_info(const IM_info &i);

  IM_info(int i, int j, IM im);

  IM eman_IM();

  int bateragarria(IM im);
    // im morfologikoarekin bateragarria den.
    // Emaitza : 0 --> ez da bateragarria.
    //           1 --> bateragarria.

  IM_info operator =(const IM_info &im);

  int     operator ==(const IM_info &im);

  int     operator !=(const IM_info &im);

  int     operator <=(const IM_info &im);

  int     operator >=(const IM_info &im);

  int     operator <(const IM_info &im);

  int     operator >(const IM_info &im);

  int     indizea_dago(int_bikote b);
    // indizeen zerrendan b indizea dagoen.
    // Emaitza : 0 --> ez dago     1 --> badago.
  void    sartu_indizea(int_bikote b);

};

#endif
