//////////////////////////////////////////////////////////////////
//
//  EUSTAGGER LITE
//
//  Copyright (C) 1996-2013  IXA Taldea
//                           EHU-UPV
//
//  This file is part of EUSTAGGER LITE.
//
//  EUSTAGGER LITE is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  EUSTAGGER LITE is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
//  Contact: Ixa Taldea (ixa@ehu.es)
//           649 Posta kutxa
//           20080 Donostia (Basque Country)
//
//////////////////////////////////////////////////////////////////


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
