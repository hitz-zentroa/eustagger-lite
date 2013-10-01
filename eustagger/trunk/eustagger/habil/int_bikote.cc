#include "int_bikote.h"
#include <stdio.h>

//class int_bikote
//{
// struct dat_bik datua;

//public:

// *********************************************************************//
  int_bikote::int_bikote()
    {
      datua.datu1 = 0;
      datua.datu2 = 0;
    }

// *********************************************************************//
  int_bikote::int_bikote(int i, int j)
    {
      datua.datu1 = i;
      datua.datu2 = j;
    }

// *********************************************************************//
  int_bikote::int_bikote(const int_bikote &i)
    {
      datua.datu1 = i.datua.datu1;
      datua.datu2 = i.datua.datu2;
    }

// *********************************************************************//
  int int_bikote::operator >(const int_bikote &i)
    {
      return (datua.datu1 > i.datua.datu1) || 
             ((datua.datu1 == i.datua.datu1) && (datua.datu2 > i.datua.datu2));
    }

// *********************************************************************//
  int int_bikote::operator >=(const int_bikote &i)
    {
      return (datua.datu1 >= i.datua.datu1) || 
             ((datua.datu1 == i.datua.datu1) && (datua.datu2 >= i.datua.datu2));
    }

// *********************************************************************//
  int int_bikote::operator <(const int_bikote &i)
    {
      return (datua.datu1 < i.datua.datu1) || 
             ((datua.datu1 == i.datua.datu1) && (datua.datu2 < i.datua.datu2));
    }

// *********************************************************************//
  int int_bikote::operator <=(const int_bikote &i)
    {
      return (datua.datu1 <= i.datua.datu1) || 
             ((datua.datu1 == i.datua.datu1) && (datua.datu2 <= i.datua.datu2));
    }

// *********************************************************************//
  int int_bikote::operator ==(const int_bikote &i)
    {
      return ((datua.datu1 == i.datua.datu1) && (datua.datu2 == i.datua.datu2));
    }

// *********************************************************************//
  int int_bikote::operator !=(const int_bikote &i)
    {
      return ((datua.datu1 != i.datua.datu1) || (datua.datu2 != i.datua.datu2));
    }

// *********************************************************************//
  int_bikote int_bikote::operator =(const int_bikote &i)
    {
      datua.datu1 = i.datua.datu1;
      datua.datu2 = i.datua.datu2;
      return *this;
    }

// *********************************************************************//
  int_bikote int_bikote::operator =(struct dat_bik &i)
    {
      datua.datu1 = i.datu1;
      datua.datu2 = i.datu2;
      return *this;
    }

// *********************************************************************//
  void int_bikote::print_bikote()
    {
     printf("%d,%d\n",datua.datu1,datua.datu2);
    }

// *********************************************************************//
  int  int_bikote::HAT_ind()
    {
      return datua.datu1;
    }


// *********************************************************************//
  int  int_bikote::F_L()
    {
      return datua.datu1;
    }

// *********************************************************************//
  int  int_bikote::posizioa()
    {
      return datua.datu2;
    }

// *********************************************************************//
//};

//#endif INT_BIKOTE_H
