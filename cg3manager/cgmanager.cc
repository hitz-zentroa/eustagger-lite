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


#include "cgmanager.h"

using namespace std;
using CG3::CG3Quit;

cgManager::cgManager () {
  this->trace = 0;
  this->wordform_case = 0;
  this->print_word_forms = 1;
  this->only_first = 0;
  this->sections = 1;
  
  this->status = U_ZERO_ERROR;
  this->ux_stdin = 0;
  this->ux_stdout = 0;
  this->ux_stderr = 0;
  this->applicator = 0;

  /* Initialize ICU */
  u_init(&status);
  if (U_FAILURE(status) && status != U_FILE_ACCESS_ERROR) {
    std::cerr << "Error: Cannot initialize ICU. Status = " << u_errorName(status) << std::endl;
    CG3Quit(1);
  }
  ucnv_setDefaultName("UTF-8");
  this->codepage_default = ucnv_getDefaultName();
  uloc_setDefault("eu_ES", &status);
  this->locale_default = uloc_getDefault();

  this->ux_stdin = u_finit(stdin, locale_default, codepage_default);
  this->ux_stdout = u_finit(stdout, locale_default, codepage_default);
  this->ux_stderr = u_finit(stderr, locale_default, codepage_default);

}

bool cgManager::loadedGrammar() {
  return (this->applicator==0?false:true);
}

int cgManager::initIO(string inFileName, string outFileName) {

  u_fclose(this->ux_stdin);
  this->ux_stdin = u_fopen(inFileName.c_str(), "rb", this->locale_default, this->codepage_default);
  if (this->ux_stdin == NULL) {
    return 0; 
  }
    
  u_fclose(this->ux_stdout);
  this->ux_stdout = u_fopen(outFileName.c_str(), "wb", this->locale_default, this->codepage_default);
  if (ux_stdout == NULL) {
    return 0; 
  }
 
  return 1;
}

int cgManager::initGrammar(string grammarFileName, int sections, char prefix, int trace) {
  CG3::IGrammarParser *parser = 0;
  if (this->loadedGrammar())
      this->clean();

  FILE *in = fopen(grammarFileName.c_str(), "rb");
  if (in == NULL || ferror(in)) {
    return 0;
  }
  size_t hm;
  if ((hm=fread(&CG3::cbuffers[0][0], 1, 4, in)) != 4) {
    std::cerr << "Error in grammar detected " << std::endl;
    CG3Quit(1);
  }
  fclose(in);
  this->trace = trace;
  if (CG3::cbuffers[0][0] == 'C' && CG3::cbuffers[0][1] == 'G' && 
      CG3::cbuffers[0][2] == '3' && CG3::cbuffers[0][3] == 'B') {
    parser = new CG3::BinaryGrammar(this->grammar, this->ux_stderr);
  }
  else {
    std::cerr << "Info: Text grammar detected -- to process textual " << std::endl;
    std::cerr << "grammars, use `vislcg3', to compile this grammar, use `cg-comp'" << std::endl;

    CG3Quit(1);
  }

  this->grammar.ux_stderr = this->ux_stderr;

  if (parser->parse_grammar_from_file(grammarFileName.c_str(), 
				      this->locale_default, this->codepage_default)) {
    std::cerr << "Error: Grammar could not be parsed - exiting!" << std::endl;
    CG3Quit(1);
  }

  this->grammar.mapping_prefix = prefix;
  this->grammar.reindex();

  delete parser;
  parser = 0;
  applicator = new CG3::GrammarApplicator(ux_stderr);

  if (this->trace) this->applicator->trace = true;
  this->applicator->setGrammar(&(this->grammar));
  for (int32_t i=1 ; i<=sections ; i++) {
    this->applicator->sections.push_back(i);
  }
  this->sections = sections;

  return 1;
}

int cgManager::applyGrammar() { // Momentuz kargatutako sekzio guztiak
  CG3::istream instream(this->ux_stdin);
  try {
    this->applicator->runGrammarOnText(instream, this->ux_stdout); //this->ux_stdin
  }
  catch (exception& e) {
    cerr << e.what();
    exit(EXIT_FAILURE);
  }
  return 1;
}

void cgManager::clean() {

  delete this->applicator;
  this->applicator = 0;
  
}

void cgManager::close() {

  u_fclose(this->ux_stdin);
  u_fclose(this->ux_stdout);
  u_fclose(this->ux_stderr);

  u_cleanup();
}
