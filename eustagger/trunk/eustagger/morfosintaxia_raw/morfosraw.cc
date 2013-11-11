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


#include "morfosraw.h"
#include "ana2morfsar.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

#define RESET        0
#define MORFSAR      1
#define ANALISIAK    2
#define LINK         3
#define WRITE        4
#define ANALISI_TMP  5
#define ADD          6
#define WAIT         7
#define PRINT        8

/* *************************************************************************************** */
/* **** Metodo pribatuak ***************************************************************** */
/* *************************************************************************************** */

void MorfosRaw::debugControl(int type, int kont, string tmpFitx) {
  if (this->debug) {;
    switch (type) {
    case RESET:{
      int k =  system ("mkdir ./debug");
      if (k == -1) {
	printErr(string("EXEKUTATZEAN"),string("mkdir ./debug"),0 );  
      }
      this->kont2tmpAmaraun.clear();
      this->kont2fsT.clear();
      this->kont2addT.clear();
      this->kont2waitT.clear();
      this->beginT=time(&beginT);
      this->currentT=time(&currentT);
      break;
    }
    case MORFSAR: {
      time_t t=time(&t);
      this->morfsarT=difftime(t,currentT);
      this->currentT=t;
      break;
    }
    case ANALISIAK: {
      time_t t=time(&t);
      this->fsT=difftime(t,currentT);
      this->currentT=t;
      break;
    }
    case LINK: {
      time_t t=time(&t);
      this->lnkT=difftime(t,currentT);
      this->currentT=t;
      break;
    }
    case WRITE:{
      time_t t=time(&t);
      this->wrT=difftime(t,currentT);
      this->currentT=t;
      break;
    }
    case ANALISI_TMP:{
      if (this->kont2tmpAmaraun.count(kont)==0 && this->kont2fsT.count(kont)==0) {
	this->kont2tmpAmaraun[kont]=this->sortuTmpFitx(kont);
	this->fsTmpT=time(&fsTmpT);
	this->kont2fsT[kont]=0;
      } else {
	time_t t=time(&t);
	this->kont2fsT[kont]=difftime(t,fsTmpT);
	string tmpMorfsar=tmpFitx +".morfsar";
	string cmd= "cp " + tmpMorfsar + " ./" + kont2tmpAmaraun[kont];
	int k = system(cmd.c_str());
	if (k == -1) {
	  printErr(string("EXEKUTATZEAN"),cmd,0 );  
	}
	unlink(tmpMorfsar.c_str());
      }
      break;
    }
    case ADD: {
      if (this->kont2addT.count(kont)==0) {
	this->addTmpT=time(&addTmpT);
	this->kont2addT[kont]=0;
      }
      else {
	time_t t=time(&t);
	this->kont2addT[kont]=difftime(t,addTmpT);
      }
      break;
    }
    case WAIT: {
      if (this->kont2waitT.count(kont)==0) {
	waitTmpT=time(&waitTmpT);
	this->kont2waitT[kont]=0;
      }
      else {
	time_t t=time(&t);
	this->kont2waitT[kont]=difftime(t,this->waitTmpT);
      }
      break;
    }
    case PRINT: {
      string timeFitx = "debug/" + this->amaraunIzen + ".time";
//       WXMLDoc wDoc;
//       wDoc.read(amaraunIzen +".w.xml");

      ofstream fTime;
      fTime.open(timeFitx.c_str());
      fTime << " " << wrT << endl;
      fTime << "MorfsarTime  => " << morfsarT << endl;
      fTime << "AnalisiaTime => " << fsT << endl;
      fTime << "LinkTime =>     " << lnkT << endl;
      fTime << "WriteTime =>    " << wrT << endl;
      fTime << "TotalTime =>    " << difftime(currentT,beginT) << endl;      
      fTime <<  endl << "############################################################" << endl << endl;
//       fTime << "wKop      => " << wDoc.getWList().size() << endl;
//       fTime << "mwKop     => " << mwDoc.size() << endl;
//       fTime << "FsKop     => " << morfDoc.size() << endl;
//       fTime << "LnkKop    => " << morfLnkDoc.size() << endl;
      fTime <<  endl << "############################################################" << endl << endl;
      fTime.precision(4);
      fTime << "                                fs     txer   wait" << endl;
      fTime << "--------------------------------------------------" << endl;
      for (int i=1;(unsigned) i<kont2tmpAmaraun.size(); i++) {
	fTime.width(20);
	fTime << kont2tmpAmaraun[i] << " ";
	fTime.width(7);
	fTime << (kont2fsT[i]) << " ";
	fTime.width(7);
	fTime << (kont2addT[i]) << " ";
	fTime.width(7);
	fTime << (kont2waitT[i]) << '\n' ;
      }
      fTime.close();
      break;
    }
    default:
      break;
    }
  }

  if (!debug && type==ANALISI_TMP) {
    string tmpMorfsar=tmpFitx +".morfsar";
    unlink(tmpMorfsar.c_str());
  }
}
/* *************************************************************************************** */

void MorfosRaw::printErr(string type, string cmd, int exit) {
  cerr << "ERROREA PROZESUA " << type << ":" << endl;
  cerr << "\t " << cmd << endl;
  cerr << "\t WIFEXITED=" << WIFEXITED(exit) << ",  WEXITSTATUS=" <<  WEXITSTATUS(exit) << endl;
}

/* *************************************************************************************** */

string MorfosRaw::sortuTmpFitx(int kont) {
  ostringstream kontOSS;
  kontOSS.fill('0');
  kontOSS.width(6);
  kontOSS << kont;
  return "debug/" + kontOSS.str() + ".debug.morfsar";
}

/* *************************************************************************************** */

void MorfosRaw::sortuAnalisiak(std::string segString) {
  string prevFitx="";
  string currentFitx="";
  int fitxKont=1;

  signal(SIGTTOU, SIG_IGN); // badirudi zerbait idatzi nahi duela eta geldirik geratzen da wait-en
  // ignore egiten dut ez dakidalako zer den esaten duena...

  
  ana2Morfsar.setAnaTam(this->tamaina);
  ana2Morfsar.setAnaString(segString);
  this->debugControl(MORFSAR,0, "");
  for (ana2Morfsar.begin(); ana2Morfsar.ready(); ana2Morfsar.next(), fitxKont++) {
    this->debugControl(ANALISI_TMP, fitxKont, "");
    currentFitx = ana2Morfsar.current();
    if (currentFitx.find(".morfsar")!= string::npos)
      currentFitx = currentFitx.substr(0, currentFitx.find(".morfsar"));

    pid_t morfsar2RawId=fork();
//     tcsetpgrp(STDERR_FILENO,morfsar2RawId);
    switch (morfsar2RawId) {
    case -1: { //Ezin prozesua sortu
      if (this->cg3form)
	printErr(string("SORTZEAN"), this->execpr + "-c  -a " + currentFitx + " -m FROM_MORFSAR ", 0);
      else
	printErr(string("SORTZEAN"), this->execpr + " -a " + currentFitx + " -m FROM_MORFSAR ", 0);
      break;
    }
    case 0: { //Semea exekutatzen
      if (this->cg3form)
	execl(this->execpr.c_str(),this->execpr.c_str(),"-c","-a", currentFitx.c_str(), "-m", "FROM_MORFSAR",(char *) 0);
      else
	execl(this->execpr.c_str(),this->execpr.c_str(),"-a", currentFitx.c_str(), "-m", "FROM_MORFSAR",(char *) 0);
      break;
    }
    default: { //Aita exekutatzen
      //Saiatu aurrekoa prozesuko datuak eraldatzen
      this->txertatuMorfDoc(prevFitx, fitxKont-1);
      prevFitx=this->waitMorfsar2Raw(currentFitx, this->execpr, fitxKont);
      this->debugControl(ANALISI_TMP, fitxKont, currentFitx);
      break;
    }
    }
  }
  this->txertatuMorfDoc(prevFitx, fitxKont);
  this->debugControl(ANALISIAK, 0, "");
}

/* *************************************************************************************** */

void MorfosRaw::txertatuMorfDoc(string & tmpAmaraun, int kont) {
  string tmpIzen = tmpAmaraun + ".morf";
  ifstream tmpMorf(tmpIzen.c_str());

  this->debugControl(ADD, kont, "");
  if (tmpMorf) {
    string lerro;
    while (!tmpMorf.eof()) {
      getline(tmpMorf,lerro);
      this->morfDocStream << lerro << endl;
    }
  }
  tmpMorf.close();
  this->debugControl(ADD, kont, "");
  unlink(tmpIzen.c_str());  
}
/* *************************************************************************************** */

string MorfosRaw::waitMorfsar2Raw(string & currentFitx, string & prCmd, int kont) {
  int morfsar2RawExit;
  this->debugControl(WAIT, kont, "");
  wait(&morfsar2RawExit);
  this->debugControl(WAIT, kont, "");

  if (WIFEXITED(morfsar2RawExit)!=0 && WEXITSTATUS(morfsar2RawExit)==0) {
    return currentFitx;
  }
  else {
    this->printErr(string("EXEKUTATZEAN"), prCmd, morfsar2RawExit);
    return "";
  }
}


/* ************************************************************************************** */
void MorfosRaw::writeResult() {
  string resIzen = this->amaraunIzen + ".morf";
  ofstream res(resIzen.c_str());
  if (!res) {
    cerr << "Errorea " << resIzen << " irekitzean" << endl;
    exit(EXIT_FAILURE);
  }
  res << morfDocStream.str();
  res.close();
}

/* *************************************************************************************** */
/* **** Metodo publikoak ***************************************************************** */
/* *************************************************************************************** */

MorfosRaw::MorfosRaw(const std::string & argv0, string & amaraunIzen, int tam, bool debug, bool cg3form) {
  this->execpr = argv0;
  this->amaraunIzen=amaraunIzen;
  this->tamaina=tam;
  this->debug=debug;
  this->cg3form=cg3form;
  this->debugControl(RESET,0, "");
}

/* *************************************************************************************** */

void MorfosRaw::setTamaina(int tamaina) { this->tamaina=tamaina; }

/* *************************************************************************************** */

int MorfosRaw::getTamaina() {return this->tamaina; }

/* *************************************************************************************** */

void MorfosRaw::setDebug(bool debug) { this->debug=debug; }

/* *************************************************************************************** */

bool MorfosRaw::getDebug() {return this->debug; }

/* *************************************************************************************** */

string MorfosRaw::getResult() { return morfDocStream.str(); }


