#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef _PPM6_H
#define _PPM6_H
#define DID_EIL 20
#define DID_EIL1 (DID_EIL-1)

struct PPM6Antraste{
     char eilute1[DID_EIL];
     int stulpeliu;
     int eiluciu;
     int didSpalva;
};

struct PPM6Pikseliai{
     int stulpeliu;
     int eiluciu;
     int didSpalva;
     size_t kiekBaitu;
     uint8_t* pikseliai;  
};

struct PPM6{
     char* pavadinimas;
     struct PPM6Antraste* antraste;
     struct PPM6Pikseliai* pikseliai;  
};


struct PPM6Antraste* naujaAntraste();

void trinkAntraste(struct PPM6Antraste* pa);

void infoAntraste(struct PPM6Antraste* pa);

struct PPM6Pikseliai* naujiPikseliai(int stulpeliu, int eiluciu,int didSpalva);

void trinkPikselius(struct PPM6Pikseliai* px);

void infoPikseliai(struct PPM6Pikseliai* px);

void skaitykAntraste(const char* failas, struct PPM6Antraste* pa);

void skaitykPikselius(const char* failas, struct PPM6Pikseliai* px);

struct PPM6* naujasPaveikslelis();

void trinkPaveiksleli(struct PPM6* pav);

void skaitykPaveiksleli(struct PPM6* pav, const char* vardas);

void rasykPaveiksleli(struct PPM6* pav);

void rasykPaveiksleliKaip(struct PPM6* pav, const char* vardas);

void infoPaveikslelis(struct PPM6* pav);

struct PPM6* kurkPaveiksleli(const char* vardas, 
                             int stulpeliu, 
                             int eiluciu, 
                             int didSpalva);

void dekTaska(struct PPM6* pav, 
              int x, int y, 
              uint8_t r, uint8_t g, uint8_t b);

void atkarpa(struct PPM6* pav, 
             int x1, int y1, 
             int x2, int y2, 
             uint8_t r, uint8_t g, uint8_t b);

void trikampis(struct PPM6* pav, 
               int x1, int y1, 
               int x2, int y2, 
               int x3, int y3, 
               uint8_t r, uint8_t g, uint8_t b);

void staciakampis(struct PPM6* pav, 
                 int x, int y, 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideC(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);


void star(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void box1(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void box2(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void box3(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void santa(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void elk(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void blight(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void egle(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void menulis(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);


void hata1(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void hata2(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void hata3(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void hata4(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void hata5(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void hata6(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void hata7(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void hata8(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void girlianda(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideA(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideM(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideX(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideR(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideY(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideS(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideE(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideB(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideC1(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideD(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideF(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideG(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideH(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideI(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideJ(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideK(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideL(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideN(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);
void raideO(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);
void raideP(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideQ(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideT(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideU(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideV(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideW(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void raideZ(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius1(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius2(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius3(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius4(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius5(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius6(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius7(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius8(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius9(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

void skaicius0(struct PPM6* pav, 
                 int x, int y,                    // k.v. kampas 
                 int p, int a, 
                 uint8_t r, uint8_t g, uint8_t b);

#endif


