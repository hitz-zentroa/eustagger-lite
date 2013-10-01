#ifndef STATUS_RAW_H
#define STATUS_RAW_H

#include "token_raw.h"

class statusRaw
{
 long  offset;
 tokenRaw azkena;
public:

         statusRaw();                 // hasieraketa funtzioa
         statusRaw(statusRaw & s);       // kopia-hasieraketa
void     init(long o, tokenRaw t); // balioak hasieratzeko

void     s_offset(long o);         // offset-a asignatu
void     s_token(tokenRaw t);      // tokena asignatu
long     e_offset();               // offset-a itzultzen du
tokenRaw e_token();                // tokena itzuli


     ~statusRaw();                 // funtzio suntsitzailea

statusRaw operator =(const statusRaw & s);  // asignazioa

};
#endif // STATUS_RAW_H

