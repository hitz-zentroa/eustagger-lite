#ifndef TOKEN_RAW_H
#define TOKEN_RAW_H

#include <string>
#include <list>
#include <vector>

using namespace std;


class tokenRaw
{
 string hitza;
 string etiketa;
 string egiaztatzeko;
 int    tratamendua;
 int    hasPos;
 int    bukPos;

 string orig;                   // 
 bool analizatu;                // hitza analizatzera bidali behar al dugu?

public:

 tokenRaw();                    // hasieraketa funtzioa
 tokenRaw(const tokenRaw & t);           // kopia-hasieraketa

 // hasieraketa funtzioa
 void init(string h, string e, string eg, int trat, int has, int buk);
 void s_hitza(const string &h);         // hitza asignatu
 void s_etiketa(const string &e);       // etiketa asignatu
 void s_egiaztatzeko(const string &eg); // egiaztatzeko hitza asignatu
 void s_tratamendua(int t);             // tratamendua asignatu
 void s_hasieraPos(int hp);             // tokenaren hasiera posizioa
 void s_bukaeraPos(int bp);             // tokenaren bukaera posizioa
 void s_orig(string ori);               // hitz originala
 void s_analizatu(bool ana);            // hitza analizatu?

 void reset_h();                  // hitza "" bihurtu
 void reset_e();                  // egiaztatzeko forma "" bihurtu
 void reset_etq();                // etiketa "" bihurtu
 
 string e_hitza();                // hitza lortu
 string e_etiketa();              // etiketa lortu
 string e_egiaztatzeko();         // egiaztatzeko hitza lortu
 int    e_tratamendua();          // tratamendua lortu
 int    e_hasieraPos();           // hasiera posizioa lortu
 int    e_bukaeraPos();           // bukaera posizioa lortu
 string e_orig();                 // hitz originala lortu
 bool e_analizatu();              // hitza analizatu?

tokenRaw operator =(const tokenRaw & t);// asignazioa
string   print_token();           // token-a inprimatu
string   print_token_hutsa();     // sarrera hutsa  inprimatu
void     print_token(vector<string> *emaitza);
                                  // token-a taulan inprimatu lerro bakoitza posizio batean
void     print_token_hutsa(vector<string> *emaitza);
                                  // sarrera hutsa taulan inprimatu lerro bakoitza posizio batean

};
#endif //TOKEN_RAW_H
 
