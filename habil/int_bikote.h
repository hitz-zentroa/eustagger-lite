#ifndef INT_BIKOTE_H
#define INT_BIKOTE_H

#include "bikote.h"

class int_bikote
{
  struct dat_bik datua;

public:

  int_bikote();

  int_bikote(int i, int j);

  int_bikote(const int_bikote &i);

  int operator >(const int_bikote &i);

  int operator >=(const int_bikote &i);

  int operator <(const int_bikote &i);

  int operator <=(const int_bikote &i);

  int operator ==(const int_bikote &i);

  int operator !=(const int_bikote &i);

  int_bikote operator =(const int_bikote &i);

  int_bikote operator =(struct dat_bik &i);

  void print_bikote();

  int  HAT_ind();

  int  F_L();

  int  posizioa();

};

#include <list>
typedef std::list<int_bikote> indize_l;

#endif
