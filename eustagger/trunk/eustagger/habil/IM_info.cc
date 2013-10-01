#include "IM_info.h"
#include <list>
#include <algorithm>
#include <pcre++.h>

using namespace pcrepp;
using namespace std;


//typedef lista<int_bikote> indize_l;

//class IM_info
//{
// Aldagaiak

//  IM morfo;

//public:

//  indize_l indizeak;

// Eragiketak


// *********************************************************************//
  IM_info::IM_info()
    {

    }

// *********************************************************************//
  IM_info::IM_info(const IM_info &i)
    {
      indizeak.clear();
      morfo = i.morfo;
      indizeak.assign(i.indizeak.begin(),i.indizeak.end());
    }

// *********************************************************************//
  IM_info::IM_info(int i, int j, IM im)
    {
     int_bikote bi(i,j);

     morfo = im;
     indizeak.push_back(bi);
    }

// *********************************************************************//
  IM      IM_info::eman_IM()
    {
     static IM tmp;

     tmp = morfo;
     return tmp;
    }
 
// *********************************************************************//
//extern int pattern_match( string, string );
int     IM_info::bateragarria(IM im)
    // im morfologikoarekin bateragarria den.
    // Emaitza : 0 --> ez da bateragarria.
    //           1 --> bateragarria.
{
  Pcre ema(morfo);
    
  if (ema.search(im))
    return 1;
  return 0;
}

// *********************************************************************//
IM_info IM_info::operator =(const IM_info &im)
{
  indizeak.clear();
  morfo = im.morfo;
  indizeak.assign(im.indizeak.begin(),im.indizeak.end());
  return *this;
}

// *********************************************************************//
int     IM_info::operator ==(const IM_info &im)
{
  return (morfo == im.morfo);
}

// *********************************************************************//
int     IM_info::operator !=(const IM_info &im)
{
  return (morfo != im.morfo);
}

// *********************************************************************//
int     IM_info::operator <=(const IM_info &im)
{
  return (morfo <= im.morfo);
}

// *********************************************************************//
int     IM_info::operator >=(const IM_info &im)
{
  return (morfo >= im.morfo);
}

// *********************************************************************//
int     IM_info::operator <(const IM_info &im)
{
  return (morfo < im.morfo);
}

// *********************************************************************//
int     IM_info::operator >(const IM_info &im)
{
  return (morfo > im.morfo);
}

// *********************************************************************//
int     IM_info::indizea_dago(int_bikote b)
  // indizeen zerrendan b indizea dagoen.
  // Emaitza : 0 --> ez dago     1 --> badago.
{
  indize_l::iterator hasi, amaitu,t;
  hasi = indizeak.begin();
  amaitu = indizeak.end();
  while (hasi != amaitu) {
    int_bikote a = *hasi;
    if (a == b) {
      return 1;
    }
    hasi++;
  }
  //       if ( find( hasi, amaitu, b ) != amaitu )
  //         return 1;
  //       else 
  return 0;
}

void     IM_info::sartu_indizea(int_bikote b)
  // indizeen zerrendan b indizea sartu.
{
  if (!indizea_dago(b))
    indizeak.push_back(b);
}
// *********************************************************************//
//};


