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


#include <pcre++.h>
#include <string>

using namespace std;
using namespace pcrepp;

string sortu_cg3rako_lema_info(string lema, string info, bool ezezag) {
  string infoTmp = info;
  Pcre adj("ADJ");
  Pcre te_tze("\\+t(z)?e$");
  Pcre ar_tar("ar$");
  Pcre al("al$");
  Pcre zale("zale$");
  Pcre ezin("ezin$");
  
  if (lema[lema.length()-1] == 'a') {
    infoTmp += " AORG";
  }
  else if (te_tze.search(lema)) {
    infoTmp += " TE_TZE";
  }
  if (ezezag && lema.length() >= 2 && ar_tar.search(lema) && adj.search(info)) {
    infoTmp += " AR_TAR";
  }
  else if (ezezag && lema.length() >= 2 && al.search(lema) && adj.search(info)) {
    infoTmp += " AL";
  }
  else if (ezezag && lema.length() >= 4 && zale.search(lema) && adj.search(info)) {
    infoTmp += " ZALE";
  }
  else if (ezezag && lema.length() >= 4 && ezin.search(lema) && adj.search(info)) {
    infoTmp += " EZIN";
  }
  return infoTmp;
}
string sortu_cg3rako_lema(string lema) {
  Pcre kt("k\\+\\!?t");
  Pcre tk("t\\+\\!?k");
  Pcre plus("\\+\\!?","g");
  Pcre garren("\\+garren\\!");
  string lemaTmp = lema;

  if (kt.search(lemaTmp))
    lemaTmp = kt.replace(lemaTmp,"t");
  if (tk.search(lemaTmp))
    lemaTmp = tk.replace(lemaTmp,"k");
  if (garren.search(lema))
    lemaTmp = garren.replace(lemaTmp,".");
  if (plus.search(lema))
    lemaTmp = plus.replace(lemaTmp,"");
  return lemaTmp;
}

string sortu_cg3rako_etiketak(string info) {
  string infoTmp = info;
  string infoOut = info;
  const string tnotPart = "(\\s+ADI\\sSIN)\\s*$";
  const string tkenPlusMinus = "\\s+(PLU|BIZ|IZAUR|ZENB|NEUR|HBN|LHB)[\\+-]";
  const string tkenRare = "\\s+(ANB|ABT|LEX)";
  const string tkenErrorKode = "\\s+(ATZKI|A_FAK|DE_DI|DE_ER|DE_LE|DIAL|ERAT|FO_OK|KONPOS|LD_FO|LD_MA|NEOL)";
  const string tkenMtkat = "\\s+(SIG|SNB|LAB)";
  const string tkenKonpa = "\\s+(KONP|GEHI|SUP)(\\s|$)";
  const string tkenKonpos = "\\s+IZE\\+IZE";
  const string tzero = "(IZE\\s+(ARR|ZKI|IZB|LIB)|ADJ\\s+(ARR|GAL)|ADI\\sSIN\\s(PART|ADIZE)|DET\\s(BAN|ORD)|DET\\sDZ[GH](\\s(NUMG[SP]|MG))?|DET\\sNOL(GAL|ARR)\\sMG|IOR\\sIZGMGB|ADB\\s(ARR|GAL)|GE[LN](\\s(NUM[SP]\\sMUGM|MG))?|BNK\\sMG|DESK)\\s*$";
  const string tadiizeeli = "\\s(ADI(ZE)|ADI_IZEELI)\\s";
  const string tkas = "\\s(ABL|ABS|ABU|ABZ|ALA|BNK|DAT|DES|DESK|ERG|GEL|GEN|INE|INS|MOT|PAR|PRO|SOZ)\\s*$";
  const string tnoterlt = "\\s+MEN\\s*$";
  const string tnor = "\\sNR_";
  const string tnori = "\\sNI_";
  const string tnork = "\\sNK_";
  Pcre notPart(tnotPart);
  Pcre kenPlusMinus(tkenPlusMinus,"g");
  Pcre kenRare(tkenRare,"g");
  Pcre kenErrorKode(tkenErrorKode,"g");
  Pcre kenMtkat(tkenMtkat,"g");
  Pcre kenKonpa(tkenKonpa,"g");
  Pcre kenKonpos(tkenKonpos,"g");
  Pcre kenZuri("\\s+$");
  Pcre zero(tzero);
  Pcre adiizeeli(tadiizeeli);
  Pcre kas(tkas);
  Pcre noterlt(tnoterlt);
  Pcre nor(tnor);
  Pcre nori(tnori);
  Pcre nork(tnork);

  if (notPart.search(infoTmp)) {
    infoOut += " NOTPART";
  }
  if (kenPlusMinus.search(infoTmp)) {
    infoTmp = kenPlusMinus.replace(infoTmp,"");
  }
  if (kenRare.search(infoTmp)) {
    infoTmp = kenRare.replace(infoTmp,"");
  }
  if (kenErrorKode.search(infoTmp)) {
    infoTmp = kenErrorKode.replace(infoTmp,"");
  }
  if (kenMtkat.search(infoTmp)) {
    infoTmp = kenMtkat.replace(infoTmp,"");
  }
  if (kenKonpa.search(infoTmp)) {
    infoTmp = kenKonpa.replace(infoTmp," ");
  }
  if (kenKonpos.search(infoTmp)) {
    infoTmp = kenKonpos.replace(infoTmp," ");
  }
  if (kenZuri.search(infoTmp)) {
    infoTmp = kenZuri.replace(infoTmp,"");
  }
   if (zero.search(infoTmp)) {
    infoOut += " ZERO";
  }
  if (adiizeeli.search(infoTmp) && kas.search(infoTmp)) {
    infoOut += " NOTDEK";
  }
  if (noterlt.search(infoTmp)) {
    infoOut += " NOTERLT";
  }
  if (nor.search(infoOut) && !nori.search(infoOut) && !nork.search(infoOut))
    infoOut = nor.replace(infoOut," NOR NR_");
  if (nor.search(infoOut) && nori.search(infoOut) && !nork.search(infoOut))
    infoOut = nor.replace(infoOut," NOR_NORI NR_");
  if (nor.search(infoOut) && !nori.search(infoOut) && nork.search(infoOut))
    infoOut = nor.replace(infoOut," NOR_NORK NR_");
  if (nor.search(infoOut) && nori.search(infoOut) && nork.search(infoOut))
    infoOut = nor.replace(infoOut," NOR_NORI_NORK NR_");

  return infoOut;
}

string kendu_cg3rako_etiketak(string info) {
  string infotmp = info;
  Pcre kendu("\\s+(ZERO|NOTDEK|NOTPART|NOTERLT|AORG|TE_TZE|AR_TAR|AL|ZALE|EZIN)(\\s|$)","g");
  Pcre kenduNNN("\\s+(NOR|NOR_NORI|NOR_NORK|NOR_NORI_NORK)\\s");
  Pcre aurrepr("\\s+(BEREIZ|ZEN|ZEN_DEK|BAK|HAS_MAI|LAB_DEK|DEN_MAI|DEN_MAI_DEK|SIG_MIN_DEK|SIG_MIN|SIG_MAI|SIG_MAI_DEK_|ID|PUNT_HIRU|IDENT|KAR_BER|ERROM|PUNT_ESKL|PUNT_GALD|PUNT_PUNT_KOMA|PUNT_BI_PUNT|PUNT_KOMA|PUNT_PUNT)(\\s|$)");
  if (kendu.search(infotmp)) {
    infotmp = kendu.replace(infotmp," ");
  }
  if (kenduNNN.search(infotmp)) {
    infotmp = kenduNNN.replace(infotmp," ");
  }
  if (aurrepr.search(infotmp)) {
    infotmp = aurrepr.replace(infotmp," ");
  }
  
  return infotmp;
}
