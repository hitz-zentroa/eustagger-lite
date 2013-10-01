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
  this->codepage_default = ucnv_getDefaultName();
  ucnv_setDefaultName("UTF-8");
  this->locale_default = "eu_ES.UTF-8"; //uloc_getDefault();

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
  fread(&CG3::cbuffers[0][0], 1, 4, in);
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
  try {
    this->applicator->runGrammarOnText(this->ux_stdin, this->ux_stdout);
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
