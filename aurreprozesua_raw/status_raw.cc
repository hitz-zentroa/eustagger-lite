#include "status_raw.h"
#include "token_raw.h"

// long offset;
// tokenRaw azkena;

     statusRaw::statusRaw()                    // hasieraketa funtzioa
{
 offset = 0;
}

void statusRaw::init(long o, tokenRaw t)     // balioak hasieratzeko
{
 offset = o;
 azkena = t;
}

     statusRaw::statusRaw(statusRaw & s)          // kopia-hasieraketa
{
 offset = s.offset;
 azkena = s.azkena;
}

void statusRaw::s_offset(long o)
{
 offset = o;
}

void statusRaw::s_token(tokenRaw t)
{
 azkena = t;
}

long statusRaw::e_offset()
{
 return(offset);
}

tokenRaw statusRaw::e_token()
{
 return(azkena);
}

    statusRaw::~statusRaw()                  // funtzio suntsitzailea
{
  // azkena.~token();
}


statusRaw statusRaw::operator =(const statusRaw & s)  // asignazioa
{
 offset = s.offset;
 azkena = s.azkena;

 return *this;
}


