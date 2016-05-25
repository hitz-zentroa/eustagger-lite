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


#include "file_mng_raw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

iconvpp::converter fileMngRaw::utf2latin = iconvpp::converter("ISO-8859-15//TRANSLIT","UTF-8");


fileMngRaw::fileMngRaw()                           // hasieraketa funtzioa
{
  this->sarreraEstandarra = false;
  this->sarreraAmaitua = false;
  this->buffer = "";
  this->bufferLuzera = 0;
  this->posizioa = 0;
  this->stdLerroa = 0;
  this->sarreraIzena = "";
  this->paragrafoa = 0;
  this->offsetMetatuta = 0;
  this->utf8input = false;
}

fileMngRaw::fileMngRaw(const fileMngRaw & fm) {
  this->sarreraEstandarra = fm.sarreraEstandarra;
  this->sarreraAmaitua = fm.sarreraAmaitua;
  this->buffer = fm.buffer;
  this->bufferLuzera = fm.bufferLuzera;
  this->posizioa = fm.posizioa;
  this->stdLerroa = fm.stdLerroa;
  this->sarreraIzena = fm.sarreraIzena;
  this->paragrafoa = fm.paragrafoa;
  this->offsetMetatuta = fm.offsetMetatuta;
  this->utf8input = fm.utf8input;
}

void  fileMngRaw::init( const string & fitxIzen, bool utf8in ) // hasieraketa funtzioa
{

  this->sarreraIzena = fitxIzen;
  this->utf8input = utf8in;
  
  if (fitxIzen != "stdin") {
    
    this->fitxategia.open(fitxIzen.c_str());
    
    if (!this->fitxategia.is_open()){
      
      cerr <<"Errorea sarrera fitxategia irekitzerakoan: " << fitxIzen << endl;
      exit( EXIT_FAILURE );
      
    }
    
  }
    
  if (fitxIzen == "stdin") {    
    this->sarreraEstandarra = 1;
  }
  else {
    this->sarreraEstandarra = 0;
  }
  
  // sarrera estandarra bada
  this->kargatuStdBufferra();

}

void  fileMngRaw::reset()                   // fitxategia lehen posizioan kokatu
{

  this->posizioa=0;

}

int   fileMngRaw::back(long offset)         // fitxategia birkokatu
{
  
  if (offset <= this->posizioa) {    
    this->posizioa = (int)offset;
    return (1);
  }
  else return (0);
  
}

int   fileMngRaw::back_token(long offset_pre, long offset)
{

  this->back((int)(offset_pre + offset));
  return 1;

}


long  fileMngRaw::non()                     // offset-a ematen du
{
  return (this->posizioa);
}

char  fileMngRaw::get() {                    // hurrengo karakterea lortu

  char uneko_c;

  if (this->posizioa == this->bufferLuzera) this->kargatuStdBufferra();
  if (!this->sarreraAmaitua) { 
    uneko_c = this->buffer[this->posizioa];
    this->posizioa++;
    return uneko_c;
  }
  else return (0);
   
}

string fileMngRaw::get_line() {                    // hurrengo lerroa lortu

  if (this->posizioa == this->bufferLuzera) this->kargatuStdBufferra();
  if (!this->sarreraAmaitua) { 
    this->posizioa = this->posizioa+buffer.size();
    return this->buffer;
  }
  else return (0);
   
}


void fileMngRaw::close() {                   // fitxategia itxi
  if (!this->sarreraEstandarra) {    
    this->fitxategia.close();
  }
}

int fileMngRaw::eof() {                      // fitxategia bukatu den

  if (this->posizioa == this->bufferLuzera) this->kargatuStdBufferra();
  return this->sarreraAmaitua;
}

int fileMngRaw::get_paragrafoa() {

  return this->paragrafoa;

}

int fileMngRaw::get_offset_metatuta() {

  return this->offsetMetatuta;

}

fileMngRaw::~fileMngRaw()                // funtzio suntsitzailea
{
 if (!this->sarreraEstandarra && this->fitxategia.is_open())
   this->fitxategia.close();
}

void fileMngRaw::kargatuStdBufferra() {
  string buf,buf2;
  // char buf[MAX_BUFFER];

  this->offsetMetatuta = this->offsetMetatuta + this->bufferLuzera;

  if (this->sarreraEstandarra) {
    if (!getline(cin,buf,'\n')) this->sarreraAmaitua = true;
    // cin.getline(buf,MAX_BUFFER);
  }
  else {
    if (!getline(this->fitxategia,buf,'\n')) this->sarreraAmaitua = true;
    // this->fitxategia.getline(buf,MAX_BUFFER);
  }

  if (this->utf8input) {
	fileMngRaw::utf2latin.convert(buf,buf2);
	this->buffer = buf2;
  } else this->buffer = buf;

  this->buffer = this->buffer + "\n";
  this->bufferLuzera = this->buffer.size();
  this->posizioa = 0;
  this->stdLerroa++;
  this->paragrafoa++;

}

