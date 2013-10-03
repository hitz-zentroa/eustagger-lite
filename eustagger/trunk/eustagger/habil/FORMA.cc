#include "FORMA.h"
#include <string.h>
#include <string>

using namespace std;

//class FORMA
//{
// Aldagaiak

//  string     Hitza;      // Forma gordetzeko.
//public:

//  indize_l  indizeak;    // Forma agertzen den HATen indizeak eta hitzaren posizioak.

// Eragiketak


// *********************************************************************//
FORMA::FORMA()
{
  
}

// *********************************************************************//
FORMA::FORMA(const FORMA &f)
{
  
  Hitza = f.Hitza;
  if (!indizeak.empty())
    indizeak.clear();
  indizeak.assign(f.indizeak.begin(),f.indizeak.end());
}

// *********************************************************************//
void  FORMA::Hasieraketa(string &H, int i, int p)
  // Hitza eta lehen indizea eta posizioa gordetzen ditu.
{
  int_bikote bi(i,p);
  
  Hitza = H;
  indizeak.push_back(bi);
}

// *********************************************************************//
int   FORMA::konparatu(string &H)
  // H Hitza-rekin konparatzen du.
  // Emaitza : <0 --> H < Hitza
  //            0 --> H == Hitza
  //           >0 --> H > Hitza
{
  string H2 = H;
//   if (H == Hitza)
//     return 0;
//   if (H < Hitza)
//     return -1;
//   return 1;
  if (islower(Hitza[0]) && isupper(H2[0]))
     H2[0] = tolower(H2[0]);

  return strcmp(Hitza.c_str(),H2.c_str());
  //  return (Hitza == H);
}

// *********************************************************************//
string FORMA::eman_Hitza()
  // forma ematen digu.
{
  return Hitza;
}

// *********************************************************************//
int   FORMA::operator <(FORMA &f)
{
  return (Hitza < f.Hitza);
}

// *********************************************************************//
int   FORMA::operator <=(FORMA &f)
{
  return (Hitza <= f.Hitza);
}

// *********************************************************************//
int   FORMA::operator >(FORMA &f)
{
  return (Hitza > f.Hitza);
}

// *********************************************************************//
int   FORMA::operator >=(FORMA &f)
{
  return (Hitza >= f.Hitza);
}

// *********************************************************************//
int   FORMA::operator ==(FORMA &f)
{
  return (Hitza == f.Hitza);
}

// *********************************************************************//
int   FORMA::operator !=(FORMA &f)
{
  return (Hitza != f.Hitza);
}

// *********************************************************************//
FORMA::~FORMA()
  // funtzio suntsitzailea.
{
}

// *********************************************************************//
FORMA FORMA::operator =(const FORMA &f)
{
  Hitza = f.Hitza;

  if (!indizeak.empty())
    indizeak.clear();
  indizeak.assign(f.indizeak.begin(),f.indizeak.end());

  return *this;
}

// *********************************************************************//

//};


