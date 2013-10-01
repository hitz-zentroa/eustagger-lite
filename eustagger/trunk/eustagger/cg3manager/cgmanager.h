#ifndef CGMANAGER_H_
#define CGMANAGER_H_
#include "stdafx.h"
#include "Grammar.h"
#include "BinaryGrammar.h"
#include "GrammarApplicator.h"


class cgManager {
  int trace;
  int wordform_case ;
  int print_word_forms;
  int only_first;
  int sections;
  const char *codepage_default;
  const char *locale_default;
  UErrorCode status ;
  UFILE *ux_stdin ;
  UFILE *ux_stdout ;
  UFILE *ux_stderr ;

  CG3::Grammar grammar;
  CG3::GrammarApplicator *applicator;

 public:
  cgManager();
  int initIO(const std::string inFileName, const std::string outFileName);
  int initGrammar(const std::string grammarFileName, int sections, char prefix, int trace);
  int applyGrammar(); //int sections ez dakit nola egin guztiak kargatu eta batzuk aplikatu
  bool loadedGrammar();
  void clean();
  void close();
};

#endif //CGMANAGER_H_
