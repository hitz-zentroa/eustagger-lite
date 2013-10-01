#include "file_mng_raw.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

fileMngRaw::fileMngRaw()                           // hasieraketa funtzioa
{

  this->sarreraEstandarra = false;
  this->sarreraAmaitua = false;
  this->buffer = "";
  this->bufferLuzera = 0;
  this->posizioa = 0;
  this->stdLerroa = 0;
  this->sarreraIzena = "";

}

fileMngRaw::fileMngRaw(const fileMngRaw & fm) {

  this->sarreraEstandarra = fm.sarreraEstandarra;
  this->sarreraAmaitua = fm.sarreraAmaitua;
  this->buffer = fm.buffer;
  this->bufferLuzera = fm.bufferLuzera;
  this->posizioa = fm.posizioa;
  this->stdLerroa = fm.stdLerroa;
  this->sarreraIzena = fm.sarreraIzena;

}

void  fileMngRaw::init( const string & fitxIzen ) // hasieraketa funtzioa
{

  this->sarreraIzena = fitxIzen;
  
  if (fitxIzen != "stdin") {
    
    this->fitxategia.open(fitxIzen.c_str());
    
    if (!this->fitxategia.is_open()){
      
      cerr <<"Errorea sarrera fitxategia irekitzerakoan: " << fitxIzen << endl;
      exit( EXIT_FAILURE );
      
    }
    
  }
    
  // sarrera estandarra bada

  if (fitxIzen == "stdin") {
      
    this->kargatuStdBufferra();
    this->sarreraEstandarra = 1;
      
  }
  
  else {

    this->sarreraEstandarra = 0;      

  }
  
}

void  fileMngRaw::reset()                   // fitxategia lehen posizioan kokatu
{

  if (this->sarreraEstandarra) this->posizioa=0;
  else this->fitxategia.seekg(0);

}

int   fileMngRaw::back(long offset)         // fitxategia birkokatu
{
  
  if (this->sarreraEstandarra) {
    
    if (offset <= this->posizioa) {
      
      this->posizioa = (int)offset;
      return (1);
      
    }
    else return (0);
  }
  else {
    
    int pos1 = this->fitxategia.tellg();
    this->fitxategia.seekg(offset);
    int pos2 = this->fitxategia.tellg();
    if (pos1 != pos2) return 1;
    else return 0;
    
  }
  
}

int   fileMngRaw::back_token(long offset_pre, long offset)
{

  this->back((int)(offset_pre + offset));
  return 1;

}


long  fileMngRaw::non()                     // offset-a ematen du
{

  if (this->sarreraEstandarra) return (this->posizioa);
  else return(this->fitxategia.tellg());

}

char  fileMngRaw::get() {                    // hurrengo karakterea lortu

  char uneko_c;

  if (!this->sarreraAmaitua) {
  
    if (this->sarreraEstandarra) {
		  
      if (this->posizioa == this->bufferLuzera) this->kargatuStdBufferra();
      uneko_c = this->buffer[this->posizioa];
      this->posizioa++;
      return uneko_c;
      
    }
    else  {
	
      char kar;
      this->fitxategia.get(kar);
      return kar;
      
    }
      
  } else return (0);
   
}


void fileMngRaw::close() {                   // fitxategia itxi
  
  this->fitxategia.close();
  
}

int fileMngRaw::eof() {                      // fitxategia bukatu den
    
  if (this->sarreraEstandarra) {     
    
    if (this->posizioa == this->bufferLuzera) {
      
      if (cin.eof()) {this->sarreraAmaitua = true; return 1;}
      this->kargatuStdBufferra();
      return 0;
      
    }
    else return 0;
    
  }
  else 
    
    if (this->fitxategia.eof()) {this->sarreraAmaitua = true; return 1;}
    else return 0;
  
}


fileMngRaw::~fileMngRaw()                // funtzio suntsitzailea
{
 if (this->fitxategia.is_open())
   this->fitxategia.close();
}

void fileMngRaw::kargatuStdBufferra() {

  char buf[MAX_BUFFER];
  cin.getline(buf,MAX_BUFFER);
  this->buffer = buf;
  this->buffer = this->buffer + "\n";
  this->bufferLuzera = this->buffer.size();
  this->posizioa = 0;
  this->stdLerroa++;
  
}

