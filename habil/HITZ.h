#ifndef HITZ_H
#define HITZ_H

#include <list>
#include <string>
#include "AN.h"

typedef std::list<AN> AN_list;
typedef std::list<int> int_lista;
typedef std::list<std::string> string_lista;

class HITZ
{
 std::string   forma;           // Sarrera
 std::string   etiketa;         // Etiketa (duenean)
 int           begiratu;        // Aldez aurretik HAT baten parte izango ez dela
                                // jakinik, ez dugu begiratuko, bestela bai.
                                // Ez begiratzeko kasuak: puntuazio-ikurrak,
                                // siglak eta zifrak (oraingoz).

 int           Id;
 int           terminoa;        // HAT baten terminoa den.
 int           osagaiak;        // HATak duen osagai kopurua.
 int           segurua;         // HAT hori segurua den.
 string_lista  analisia;        // HATari dagokion analisia.

 int  begiratu_hitza(std::string etq);

 public:
 AN_list   anali;
 int_lista hat_lista;       // Zein HATen osagai den.

// Eragiketak.

              HITZ();
              HITZ(const HITZ &H);
 void         Sartu_forma(std::string f, std::string e);
 void         Sartu_etiketa(std::string e);
 int          eman_Id();
 std::string  eman_forma();
 std::string  eman_etiketa();
 void         eman_im(std::string nag_im,string_lista &emaitza);
 int          eman_osagai_kopurua();
 int          begiratu_behar_da();
 void         Sartu_analisi_hat(std::string an, int seg);
 void         Sartu_osagai_kopurua(int kop);
 void         markatu(int zein_hat);
 int          terminoa_da();
 void         ken_hat(int h);
 void         destroy_hat_analisi();
 void         inprimatu();
 void         inprimatu_forma(int azpimarra);
 void         inprimatu_hitza();
              ~HITZ();
};

#endif
