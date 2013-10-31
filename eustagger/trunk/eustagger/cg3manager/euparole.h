#ifndef EUPAROLE_H_
#define EUPAROLE_H_
#include <string>
#include <map>

class euParole {
  std::map<std::string,char> euPar[8];
  int level;
  int maxColumns[4]; 
  bool loaded;
  std::string toParole(const std::string analysis);
  void loadMap();
public:
  euParole();
  euParole(int tagLevel);
  // set multitag system level
  void setLevel(int level);
  // extract lemma and tag from analysis according to level
  void getLemmaTag(const std::string analysis,std::wstring &lemma,std::wstring &tag);
};

#endif //EUPAROLE_H_
