#ifndef AN_H
#define AN_H

#include "IM.h"
#include <string>

class AN
{
 int     correct;   /*** NEREA : 97/11/28  eskuz landutakoetan C marka */
 std::string  lema;
 std::string  aldaera;
 IM      info;

 public:

// Eragiketak.

        AN();
        AN(const AN &a);
        AN(const int ona,const std::string &l,const std::string &a,const IM &im);
 std::string eman_lema();
 IM     eman_IM();
 int    operator ==(AN &a);
 int    operator >(AN &a);
 int    operator <(AN &a);
 int    operator !=(AN &a);
 AN     operator =(const AN &a);
 void   inprimatu();
        ~AN();
};

#endif
