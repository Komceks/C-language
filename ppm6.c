#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "ppm6.h"


struct PPM6Antraste* naujaAntraste(){

     struct PPM6Antraste* pa = 
          (struct PPM6Antraste*) calloc(sizeof(struct PPM6Antraste), 1);
     strcpy(pa->eilute1, "P6");
     pa->stulpeliu = 0;
     pa->eiluciu = 0;
     pa->didSpalva = 0;
     return pa;

}

void trinkAntraste(struct PPM6Antraste* pa){

     free(pa);

}

void infoAntraste(struct PPM6Antraste* pa){

     printf("%s\n%d %d\n%d\n",
            pa->eilute1, pa->stulpeliu, pa->eiluciu, pa->didSpalva);
            
}

struct PPM6Pikseliai* naujiPikseliai(int stulpeliu, int eiluciu,int didSpalva){

    struct PPM6Pikseliai* px = (struct PPM6Pikseliai*) calloc(sizeof(struct PPM6Pikseliai), 1);
    px->stulpeliu = stulpeliu;
    px->eiluciu = eiluciu;
    px->didSpalva = didSpalva;
    px->kiekBaitu = stulpeliu * eiluciu * 3;
    px->pikseliai = (uint8_t*) calloc(px->kiekBaitu, sizeof(uint8_t));
    return px;
}

void trinkPikselius(struct PPM6Pikseliai* px){

    free(px->pikseliai);
    free(px);

}

void infoPikseliai(struct PPM6Pikseliai* px){

     printf("%d x %d\n%d\n\%ld : ",
             px->stulpeliu, px->eiluciu, 
             px->didSpalva, px->kiekBaitu);
     int sp = 20;
     if (sp > px->kiekBaitu) sp = px->kiekBaitu;
     for(int i=0;i<sp;i++)        
        printf("%3x", px->pikseliai[i]);
     printf("\n");   
            
}

/////////////////////////////////////
void skaitykAntraste(const char* failas, struct PPM6Antraste* pa){
   FILE* fin = fopen(failas, "r");
   
   char s[DID_EIL] = "";
   fscanf(fin,"%s", s);
   if(strcmp(s,"P6") != 0){
      perror("Blogas failo formatas\n");
      fclose(fin);
      exit(1);
   }
   fscanf(fin,"%d%d%d", &pa->stulpeliu, 
                        &pa->eiluciu,
                        &pa->didSpalva);
   
   fclose(fin);    

}


/////////////////////////////////////////////////////////////////


void skaitykPikselius(const char* failas, struct PPM6Pikseliai* px){
   FILE* fin = fopen(failas, "r");
   char ch;
   int kiekA = 0;
   while(kiekA<3){
     fread(&ch, 1, 1, fin);       
     if(ch == '\n') kiekA++;
   }

   fread(px->pikseliai, sizeof(uint8_t), px->kiekBaitu, fin);
   
   fclose(fin);    
}


/////////////////////////////////////////////////////////////////
struct PPM6* naujasPaveikslelis(){
   struct PPM6* p6 = (struct PPM6*) calloc(sizeof(struct PPM6), 1);  
   
   p6->pavadinimas = NULL;
   p6->antraste = NULL;
   p6->pikseliai = NULL;   
   
   return p6;
} 

void trinkPaveiksleli(struct PPM6* pav){

   if(pav->pavadinimas != NULL) 
       free(pav->pavadinimas);
   if(pav->antraste != NULL)
       trinkAntraste(pav->antraste);
        
   if(pav->pikseliai != NULL)
       trinkPikselius(pav->pikseliai);
   free(pav);   

}

void skaitykPaveiksleli(struct PPM6* pav, const char* vardas){

   pav->pavadinimas = (char*) calloc(sizeof(char), strlen(vardas)+1); 
   strcpy(pav->pavadinimas, vardas);
   
   pav->antraste = naujaAntraste();
   skaitykAntraste(pav->pavadinimas, pav->antraste);

    
   pav->pikseliai = naujiPikseliai(pav->antraste->stulpeliu, pav->antraste->eiluciu, 
                  pav->antraste->didSpalva);
        
   skaitykPikselius(pav->pavadinimas, pav->pikseliai);
}


void rasykPaveiksleli(struct PPM6* pav){

   FILE* fout = fopen(pav->pavadinimas, "w");
   fprintf(fout,"P6\n");
   fprintf(fout,"%d %d\n%d\n", pav->antraste->stulpeliu, pav->antraste->eiluciu, 
                  pav->antraste->didSpalva);
   
   fwrite(pav->pikseliai->pikseliai, pav->pikseliai->kiekBaitu, 1, fout);
   fclose(fout);
   
}

void rasykPaveiksleliKaip(struct PPM6* pav, const char* vardas){

   free(pav->pavadinimas);
   pav->pavadinimas = (char*) calloc(sizeof(char), strlen(vardas)+1); 
   strcpy(pav->pavadinimas, vardas);
   rasykPaveiksleli(pav);

}   

void infoPaveikslelis(struct PPM6* pav){

   printf("%s\n", pav->pavadinimas);
   infoAntraste(pav->antraste); 
   infoPikseliai(pav->pikseliai);

}
/////////////////////////////////////////////////////////////////
// Piešimas
/////////////////////////////////////////////////////////////////
struct PPM6* kurkPaveiksleli(const char* vardas, int stulpeliu, int eiluciu, int 
                             didSpalva){


   struct PPM6* pav = naujasPaveikslelis();

   pav->pavadinimas = (char*) calloc(sizeof(char), strlen(vardas)+1); 
   strcpy(pav->pavadinimas, vardas);
   
   pav->antraste = naujaAntraste();
   pav->antraste->stulpeliu = stulpeliu;
   pav->antraste->eiluciu = eiluciu;
   pav->antraste->didSpalva = didSpalva;
   
   pav->pikseliai = naujiPikseliai(pav->antraste->stulpeliu, pav->antraste->eiluciu, 
                  pav->antraste->didSpalva);
   
   for(int i=0;i<pav->pikseliai->kiekBaitu;i++){
      pav->pikseliai->pikseliai[i] = (uint8_t) didSpalva;
   }
    
   return pav;   
}
/////////////////////////////////////////////////////////////
// dekTaska(x,y,c);
/////////////////////////////////////////////////////////////
void dekTaska(struct PPM6* pav, int x, int y, 
              uint8_t r, uint8_t g, uint8_t b){
   if( x >= 0 && x < pav->antraste->stulpeliu &&
       y >= 0 && y < pav->antraste->eiluciu){           
       int adresas = (y * pav->antraste->stulpeliu + x)  * 3;
       pav->pikseliai->pikseliai[adresas] = r;
       pav->pikseliai->pikseliai[adresas+1] = g;
       pav->pikseliai->pikseliai[adresas+2] = b;
   } else{
   
      printf("Blogos koordinatės: (%d, %d)\n", x,y);
   
   }

}

/////////////////////////////////////////////////////////////
void atkarpa(struct PPM6* pav, int x1, int y1, int x2, int y2, 
              uint8_t r, uint8_t g, uint8_t b){

   int tasku = abs(x2-x1) + abs(y2-y1);
   double dt =  0.5 / tasku;
   for(double t=0; t <= 1.0 + dt; t+=dt){
      int x = (int) (x1 * (1 - t) + x2 * t);
      int y = (int) (y1 * (1 - t) + y2 * t); 
      dekTaska(pav, x, y, r, g, b);
   }
   
}
///////////////////////////////////////////////////////////////
void trikampis(struct PPM6* pav, int x1, int y1,int x2, int y2, 
               int x3, int y3,uint8_t r, uint8_t g, uint8_t b){
               
   int tasku = abs(x2-x1) + abs(y2-y1);
   double dt =  0.5 / tasku;
   for(double t=0; t <= 1.0 + dt; t+=dt){
      int x = (int) (x1 * (1 - t) + x2 * t);
      int y = (int) (y1 * (1 - t) + y2 * t); 
      atkarpa(pav, x3, y3, x, y, r, g, b);
   }           
               
 }

void staciakampis(struct PPM6* pav, int x, int y, 
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){
   for(int xx=x; xx<=x+p; xx++)
      for(int yy=y; yy<=y+a; yy++) {
      
      dekTaska(pav, xx, yy, r, g, b);
      
  }                    
                 
}

void raideC(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p, x+p/4, x, x+p/4, x+p};
  int ys[] = {y, y, y+a/4, y+a, y+3*a/4, y+a};

  trikampis(pav, xs[0], ys[0], xs[1], ys[1], xs[2], ys[2], r, g, b);
  trikampis(pav, xs[0], ys[0], xs[2], ys[2], xs[3], ys[3], r, g, b);
  trikampis(pav, xs[2], ys[2], xs[3], ys[3], xs[4], ys[4], r, g, b);
  trikampis(pav, xs[3], ys[3], xs[4], ys[4], xs[5], ys[5], r, g, b);
}

//////////
void star(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/8, x+2*p/8, x+3*p/8, x+p*4/8, x+5*p/8, x+6*p/8, x+7*p/8, x+p};
      int ys[] = {y, y+a/4, y+2*a/4, y+3*a/4, y+a};

      trikampis(pav, xs[0],ys[1], xs[2],ys[2], xs[3],ys[1], r,g,b);
      trikampis(pav, xs[3],ys[1], xs[4],ys[0], xs[5],ys[1], r,g,b);
      trikampis(pav, xs[8],ys[1], xs[6],ys[2], xs[5],ys[1], r,g,b);
      trikampis(pav, xs[7],ys[4], xs[6],ys[2], xs[4],ys[3], r,g,b);
      trikampis(pav, xs[1],ys[4], xs[2],ys[2], xs[4],ys[3], r,g,b);
      trikampis(pav, xs[3],ys[1], xs[2],ys[2], xs[4],ys[3], r,g,b);
      trikampis(pav, xs[3],ys[1], xs[5],ys[1], xs[4],ys[3], r,g,b);
      trikampis(pav, xs[6],ys[2], xs[5],ys[1], xs[4],ys[3], r,g,b);
}
////////////
void box1(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){

      int xs[] = {x, x+p/3, x+2*p/3, x+p};
      int ys[] = {y, y+a/3, y+2*a/3, y+a};
      
      //dezes spalva
      trikampis(pav, xs[0],ys[0], xs[0],ys[1], xs[1],ys[1], 255,0,0);
      trikampis(pav, xs[0],ys[0], xs[1],ys[0], xs[1],ys[1], 255,0,0);
      trikampis(pav, xs[2],ys[0], xs[3],ys[0], xs[3],ys[1], 255,0,0);
      trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[1], 255,0,0);
      trikampis(pav, xs[0],ys[2], xs[0],ys[3], xs[1],ys[3], 255,0,0);
      trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[1],ys[3], 255,0,0);
      trikampis(pav, xs[2],ys[2], xs[2],ys[3], xs[3],ys[2], 255,0,0);
      trikampis(pav, xs[2],ys[3], xs[3],ys[3], xs[3],ys[2], 255,0,0);

      //juosteliu spalva
      trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[0],ys[2], 0,255,255);
      trikampis(pav, xs[0],ys[2], xs[1],ys[1], xs[1],ys[2], 0,255,255);
      trikampis(pav, xs[1],ys[0], xs[1],ys[3], xs[2],ys[3], 0,255,255);
      trikampis(pav, xs[1],ys[0], xs[2],ys[0], xs[2],ys[3], 0,255,255);
      trikampis(pav, xs[2],ys[1], xs[2],ys[2], xs[3],ys[2], 0,255,255);
      trikampis(pav, xs[2],ys[1], xs[3],ys[1], xs[3],ys[2], 0,255,255);

}

void box2(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){

      int xs[] = {x, x+p/3, x+2*p/3, x+p};
      int ys[] = {y, y+a/3, y+2*a/3, y+a};
      
      //dezes spalva
      trikampis(pav, xs[0],ys[0], xs[0],ys[1], xs[1],ys[1], 234, 185, 55);
      trikampis(pav, xs[0],ys[0], xs[1],ys[0], xs[1],ys[1], 234, 185, 55);
      trikampis(pav, xs[2],ys[0], xs[3],ys[0], xs[3],ys[1], 234, 185, 55);
      trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[1], 234, 185, 55);
      trikampis(pav, xs[0],ys[2], xs[0],ys[3], xs[1],ys[3], 234, 185, 55);
      trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[1],ys[3], 234, 185, 55);
      trikampis(pav, xs[2],ys[2], xs[2],ys[3], xs[3],ys[2], 234, 185, 55);
      trikampis(pav, xs[2],ys[3], xs[3],ys[3], xs[3],ys[2], 234, 185, 55);

      //juosteliu spalva
      trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[0],ys[2], 105, 180, 44);
      trikampis(pav, xs[0],ys[2], xs[1],ys[1], xs[1],ys[2], 105, 180, 44);
      trikampis(pav, xs[1],ys[0], xs[1],ys[3], xs[2],ys[3], 105, 180, 44);
      trikampis(pav, xs[1],ys[0], xs[2],ys[0], xs[2],ys[3], 105, 180, 44);
      trikampis(pav, xs[2],ys[1], xs[2],ys[2], xs[3],ys[2], 105, 180, 44);
      trikampis(pav, xs[2],ys[1], xs[3],ys[1], xs[3],ys[2], 105, 180, 44);

}


void box3(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){

      int xs[] = {x, x+p/3, x+2*p/3, x+p};
      int ys[] = {y, y+a/3, y+2*a/3, y+a};
      
      //dezes spalva
      trikampis(pav, xs[0],ys[0], xs[0],ys[1], xs[1],ys[1], 8, 164, 44);
      trikampis(pav, xs[0],ys[0], xs[1],ys[0], xs[1],ys[1], 8, 164, 44);
      trikampis(pav, xs[2],ys[0], xs[3],ys[0], xs[3],ys[1], 8, 164, 44);
      trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[1], 8, 164, 44);
      trikampis(pav, xs[0],ys[2], xs[0],ys[3], xs[1],ys[3], 8, 164, 44);
      trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[1],ys[3], 8, 164, 44);
      trikampis(pav, xs[2],ys[2], xs[2],ys[3], xs[3],ys[2], 8, 164, 44);
      trikampis(pav, xs[2],ys[3], xs[3],ys[3], xs[3],ys[2], 8, 164, 44);

      //juosteliu spalva
      trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[0],ys[2], 208, 112, 137);
      trikampis(pav, xs[0],ys[2], xs[1],ys[1], xs[1],ys[2], 208, 112, 137);
      trikampis(pav, xs[1],ys[0], xs[1],ys[3], xs[2],ys[3], 208, 112, 137);
      trikampis(pav, xs[1],ys[0], xs[2],ys[0], xs[2],ys[3], 208, 112, 137);
      trikampis(pav, xs[2],ys[1], xs[2],ys[2], xs[3],ys[2], 208, 112, 137);
      trikampis(pav, xs[2],ys[1], xs[3],ys[1], xs[3],ys[2], 208, 112, 137);

}

///////
void santa(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){

      int xs[] = {x, x+2*p/22, x+4*p/22, x+7*p/22, x+9*p/22, x+p/2, x+13*p/22, x+17*p/22, x+19*p/22, x+p};
    int ys[] = {y, y+a/23, y+2*a/23, y+3*a/23, y+4*a/23, y+7*a/23, y+10*a/23, y+13*a/23, y+18*a/23, y+21*a/23, y+a};
      
      //burbulas
    trikampis(pav, xs[0],ys[1], xs[1],ys[0], xs[2],ys[1], r,g,b);
    trikampis(pav, xs[0],ys[1], xs[0],ys[3], xs[2],ys[1], r,g,b);
    trikampis(pav, xs[0],ys[3], xs[2],ys[3], xs[2],ys[1], r,g,b);
    trikampis(pav, xs[0],ys[3], xs[2],ys[3], xs[1],ys[4], r,g,b);

      //kepure
    trikampis(pav, xs[2],ys[2], xs[3],ys[0], xs[3],ys[4], r,g,b);
    trikampis(pav, xs[5],ys[0], xs[3],ys[0], xs[5],ys[4], r,g,b);
    trikampis(pav, xs[3],ys[4], xs[3],ys[0], xs[5],ys[4], r,g,b);

      //zmogus
    trikampis(pav, xs[3],ys[4], xs[4],ys[5], xs[5],ys[4], r,g,b);
    trikampis(pav, xs[3],ys[6], xs[4],ys[5], xs[6],ys[7], r,g,b);

      //karieta
    trikampis(pav, xs[3],ys[6], xs[3],ys[7], xs[6],ys[7], r,g,b);
    trikampis(pav, xs[1],ys[5], xs[3],ys[6], xs[3],ys[8], r,g,b);
    trikampis(pav, xs[3],ys[7], xs[3],ys[8], xs[8],ys[8], r,g,b);
    trikampis(pav, xs[3],ys[7], xs[8],ys[7], xs[8],ys[8], r,g,b);
    trikampis(pav, xs[9],ys[7], xs[8],ys[7], xs[8],ys[8], r,g,b);
    trikampis(pav, xs[9],ys[7], xs[8],ys[7], xs[9],ys[6], r,g,b);

     //sakes
    trikampis(pav, xs[3],ys[8], xs[3],ys[9], xs[4],ys[9], r,g,b);
    trikampis(pav, xs[3],ys[8], xs[4],ys[8], xs[4],ys[9], r,g,b);
    trikampis(pav, xs[7],ys[8], xs[7],ys[9], xs[8],ys[9], r,g,b);
    trikampis(pav, xs[7],ys[8], xs[8],ys[9], xs[8],ys[8], r,g,b);
    trikampis(pav, xs[1],ys[9], xs[9],ys[9], xs[9],ys[10], r,g,b);
    trikampis(pav, xs[1],ys[9], xs[9],ys[10], xs[1],ys[10], r,g,b);

}
//////
void elk(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){

      int xs[] = {x, x+2*p/18, x+3*p/18, x+4*p/18, x+5*p/18, x+6*p/18, x+7*p/18, x+8*p/18, x+9*p/18, x+10*p/18, x+11*p/18, x+12*p/18, x+13*p/18, x+14*p/18, x+16*p/18, x+p};
      int ys[] = {y, y+a/19, y+2*a/19, y+3*a/19, y+4*a/19, y+5*a/19, y+6*a/19, y+7*a/19, y+9*a/19, y+10*a/19, y+11*a/19, y+12*a/19, y+13*a/19, y+14*a/19, y+15*a/19, y+16*a/19, y+a};
      
      //ragai
      trikampis(pav, xs[6],ys[1], xs[7],ys[4], xs[8],ys[4], r,g,b);
      trikampis(pav, xs[10],ys[4], xs[7],ys[4], xs[11],ys[5], r,g,b);
      trikampis(pav, xs[8],ys[2], xs[10],ys[4], xs[11],ys[3], r,g,b);
      trikampis(pav, xs[10],ys[4], xs[11],ys[5], xs[11],ys[3], r,g,b);
      trikampis(pav, xs[12],ys[4], xs[11],ys[5], xs[11],ys[3], r,g,b);
      trikampis(pav, xs[12],ys[2], xs[12],ys[4], xs[13],ys[3], r,g,b);
      trikampis(pav, xs[12],ys[2], xs[13],ys[2], xs[13],ys[3], r,g,b);
      trikampis(pav, xs[10],ys[1], xs[12],ys[2], xs[13],ys[2], r,g,b);
      trikampis(pav, xs[14],ys[0], xs[13],ys[2], xs[13],ys[3], r,g,b);

      //galva
      trikampis(pav, xs[13],ys[3], xs[13],ys[7], xs[15],ys[5], r,g,b);
      trikampis(pav, xs[15],ys[6], xs[13],ys[7], xs[15],ys[5], r,g,b);
      trikampis(pav, xs[13],ys[3], xs[11],ys[5], xs[13],ys[7], r,g,b);

      //chest
      trikampis(pav, xs[11],ys[5], xs[9],ys[7], xs[13],ys[7], r,g,b);
      trikampis(pav, xs[11],ys[8], xs[9],ys[7], xs[13],ys[7], r,g,b);
      trikampis(pav, xs[11],ys[8], xs[9],ys[7], xs[9],ys[13], r,g,b);
      trikampis(pav, xs[11],ys[8], xs[11],ys[14], xs[9],ys[13], r,g,b);
      trikampis(pav, xs[11],ys[8], xs[11],ys[14], xs[13],ys[12], r,g,b);
      trikampis(pav, xs[11],ys[8], xs[13],ys[7], xs[13],ys[12], r,g,b);

      //body
      trikampis(pav, xs[9],ys[13], xs[9],ys[7], xs[1],ys[9], r,g,b);
      trikampis(pav, xs[3],ys[13], xs[9],ys[13], xs[1],ys[9], r,g,b);
      trikampis(pav, xs[0],ys[10], xs[2],ys[11], xs[1],ys[9], r,g,b);
      trikampis(pav, xs[3],ys[13], xs[2],ys[11], xs[1],ys[13], r,g,b);

      //legs
      trikampis(pav, xs[1],ys[16], xs[2],ys[15], xs[1],ys[13], r,g,b);
      trikampis(pav, xs[4],ys[16], xs[3],ys[13], xs[1],ys[13], r,g,b);
      trikampis(pav, xs[11],ys[16], xs[11],ys[14], xs[9],ys[13], r,g,b);
      trikampis(pav, xs[13],ys[16], xs[12],ys[13], xs[9],ys[13], r,g,b);

}
/////
void blight(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){

      int xs[] = {x, x+p*8/20, x+p/2, x+p*12/20, x+p};
      int ys[] = {y, y+a*8/20, y+a/2, y+a*12/20, y+a};

      trikampis(pav, xs[0], ys[2], xs[1], ys[1], xs[1], ys[3],r,g,b);
      trikampis(pav, xs[1], ys[1], xs[2], ys[0], xs[3], ys[1],r,g,b);
      trikampis(pav, xs[3], ys[1], xs[3], ys[3], xs[4], ys[2],r,g,b);
      trikampis(pav, xs[1], ys[3], xs[3], ys[3], xs[2], ys[4],r,g,b);
      trikampis(pav, xs[1], ys[1], xs[1], ys[3], xs[3], ys[1],r,g,b);
      trikampis(pav, xs[1], ys[3], xs[3], ys[3], xs[3], ys[1],r,g,b);


}
void egle(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
      
      int xs[] = {x,x+p/12, x+p*2/12,x+p*3/12, x+p*4/12,x+p*5/12,x+p*6/12,x+p*7/12, x+p*8/12,x+p*9/12, x+p*10/12,x+p*11/12, x+p};
      int ys[] = {y, y+a/14, y+a*2/14,y+a*3/14, y+a*4/14, y+a*5/14,y+a*6/14, y+a*7/14,y+a*8/14,y+a*9/14, y+a*10/14,y+a*11/14,y+a*12/14,y+a*13/14, y+a};

      trikampis(pav, xs[5],ys[12], xs[5],ys[14], xs[7],ys[12], 51,25,0);//kotas
      trikampis(pav, xs[5],ys[14], xs[7],ys[12], xs[7],ys[14], 51,25,0);

      trikampis(pav, xs[0],ys[12], xs[2],ys[10], xs[10],ys[10], r,102,b);
      trikampis(pav, xs[0],ys[12], xs[10],ys[10], xs[12],ys[12], r,102,b);

      trikampis(pav, xs[1],ys[10], xs[3],ys[7], xs[9],ys[7], r,51,b);
      trikampis(pav, xs[1],ys[10], xs[9],ys[7], xs[11],ys[10], r,51,b);

      trikampis(pav, xs[2],ys[7], xs[4],ys[5], xs[8],ys[5], r,102,b);
      trikampis(pav, xs[2],ys[7], xs[8],ys[5], xs[10],ys[7], r,102,b);
      
      trikampis(pav, xs[5],ys[3], xs[7],ys[3], xs[3],ys[5], r,51,b);
      trikampis(pav, xs[3],ys[5], xs[7],ys[3], xs[9],ys[5], r,51,b);

      trikampis(pav, xs[6],ys[0], xs[4],ys[3], xs[8],ys[3], r,102,b);

}
void menulis(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){

       int xs[] = {x,x+p/4, x+p*2/4,x+p*3/4, x+p};
       int ys[] = {y, y+a/5, y+a*2/5,y+a*3/5,y+a*4/5, y+a};

       trikampis(pav, xs[0],ys[1], xs[1],ys[0], xs[3],ys[0], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[3],ys[0], xs[4],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[3],ys[1], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[2],ys[2], xs[0],ys[4], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[2],ys[3], xs[0],ys[4], r,g,b);
       trikampis(pav, xs[0],ys[4], xs[2],ys[3], xs[1],ys[5], r,g,b);
       trikampis(pav, xs[1],ys[5], xs[2],ys[3], xs[3],ys[4], r,g,b);
       trikampis(pav, xs[1],ys[5], xs[3],ys[4], xs[3],ys[5], r,g,b);
       trikampis(pav, xs[3],ys[4], xs[3],ys[5], xs[4],ys[4], r,g,b);
   }

 void hata1(struct PPM6* pav,  int x, int y,                    // k.v. kampas 
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){
                 
       
       int xs[] = {x,x+p/2, x+p};
       int ys[] = {y, y+a/3, y+a*2/3, y+a};
       
       trikampis(pav, xs[0],ys[1], xs[1],ys[0], xs[2],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[0],ys[3], xs[2],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[3], xs[2],ys[1], xs[2],ys[3], r,g,b);
    }

    void hata2(struct PPM6* pav,  int x, int y,                    // k.v. kampas 
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){
                 
       
       int xs[] = {x,x+p/2, x+p};
       int ys[] = {y, y+a/3, y+a*2/3, y+a};
       

       trikampis(pav, xs[0],ys[1], xs[2],ys[0], xs[2],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[2],ys[1], xs[0],ys[3], r,g,b);
       trikampis(pav, xs[0],ys[3], xs[2],ys[1], xs[2],ys[3], r,g,b);
   }

    void hata3(struct PPM6* pav,  int x, int y,                    // k.v. kampas 
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){
                 
       
       int xs[] = {x,x+p/2, x+p};
       int ys[] = {y, y+a/3, y+a*2/3, y+a};
       

       trikampis(pav, xs[0],ys[0], xs[0],ys[1], xs[2],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[2],ys[1], xs[0],ys[3], r,g,b);
       trikampis(pav, xs[0],ys[3], xs[2],ys[1], xs[2],ys[3], r,g,b);
   }

   void hata4(struct PPM6* pav,  int x, int y,                    // k.v. kampas 
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){
                 
       
       int xs[] = {x,x+p/2, x+p};
       int ys[] = {y, y+a/5, y+a*2/5,y+a*3/5,y+a*4/5, y+a};
       

       trikampis(pav, xs[0],ys[1], xs[1],ys[0], xs[2],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[2],ys[1], xs[2],ys[5], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[0],ys[5], xs[2],ys[5], r,g,b);
   }

   void hata5(struct PPM6* pav,  int x, int y,                    // k.v. kampas 
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){
                 
       
       int xs[] = {x,x+p/2, x+p};
       int ys[] = {y, y+a/2, y+a};
       

       trikampis(pav, xs[0],ys[1], xs[1],ys[0], xs[2],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[0],ys[2], xs[2],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[1], xs[2],ys[2], xs[0],ys[2], r,g,b);
   }

   void hata6(struct PPM6* pav,  int x, int y,                    // k.v. kampas 
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){
                 
       
       int xs[] = {x,x+p/3, x+p*2/3, x+p};
       int ys[] = {y, y+a/3,y+a*2/3, y+a};
       

       trikampis(pav, xs[0],ys[1], xs[1],ys[0], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[1],ys[1], xs[1],ys[0], xs[2],ys[0], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[3],ys[1], xs[0],ys[3], r,g,b);
       trikampis(pav, xs[0],ys[3], xs[3],ys[1], xs[3],ys[3], r,g,b);
   }

   void hata7(struct PPM6* pav,  int x, int y,                    // k.v. kampas 
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){
                 
       
       int xs[] = {x,x+p/4, x+p*2/4, x+p*3/4, x+p};
       int ys[] = {y, y+a/4,y+a*2/4, y+a*3/4, y+a};
       

       trikampis(pav, xs[0],ys[1], xs[2],ys[0], xs[4],ys[1], r,g,b);
       trikampis(pav, xs[3],ys[0], xs[3],ys[1], xs[4],ys[1], r,g,b);
       trikampis(pav, xs[3],ys[0], xs[4],ys[0], xs[4],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[0],ys[2], xs[4],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[2], xs[4],ys[1], xs[4],ys[2], r,g,b);

       trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[0],ys[3], 255,200,0);//langas
       trikampis(pav, xs[1],ys[2], xs[1],ys[3], xs[0],ys[3], 255,200,0);

       trikampis(pav, xs[0],ys[3], xs[0],ys[4], xs[1],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[2], xs[2],ys[2], xs[1],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[2],ys[4], xs[0],ys[4], r,g,b);
       trikampis(pav, xs[3],ys[2], xs[4],ys[2], xs[3],ys[4], r,g,b);
       trikampis(pav, xs[3],ys[4], xs[4],ys[2], xs[4],ys[4], r,g,b);

         trikampis(pav, xs[2],ys[2], xs[3],ys[2], xs[2],ys[4], 10,10,10);
         trikampis(pav, xs[3],ys[2], xs[3],ys[4], xs[2],ys[4], 10,10,10);//durys
     }

     void hata8(struct PPM6* pav,  int x, int y,                    // k.v. kampas 
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){
                 
       
       int xs[] = {x,x+p/4, x+p*2/4, x+p*3/4, x+p};
       int ys[] = {y, y+a/6,y+a*2/6, y+a*3/6, y+a*4/6, y+a*5/6, y+a};
       

       trikampis(pav, xs[0],ys[2], xs[2],ys[0], xs[4],ys[2], r,g,b);
       trikampis(pav, xs[0],ys[2], xs[2],ys[2], xs[0],ys[6], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[2],ys[6], xs[0],ys[6], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[4],ys[2], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[3], xs[4],ys[2], xs[4],ys[3], r,g,b);

       trikampis(pav, xs[2],ys[3], xs[3],ys[3], xs[2],ys[4], 255,200,0);//langas
       trikampis(pav, xs[2],ys[4], xs[3],ys[4], xs[3],ys[3], 255,200,0);

       trikampis(pav, xs[3],ys[3], xs[4],ys[3], xs[3],ys[4], r,g,b);
       trikampis(pav, xs[3],ys[4], xs[4],ys[3], xs[4],ys[4], r,g,b);
       trikampis(pav, xs[2],ys[4], xs[4],ys[4], xs[2],ys[6], r,g,b);
       trikampis(pav, xs[2],ys[6], xs[4],ys[4], xs[4],ys[6], r,g,b);
   }

   void girlianda(struct PPM6* pav,  int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){

       int xs[] = {x,x+p/4, x+p*2/4,x+p*3/4, x+p};
       int ys[] = {y, y+a/4, y+a*2/4,y+a*3/4, y+a};


       trikampis(pav, xs[0],ys[1], xs[1],ys[0], xs[2],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[2],ys[1], xs[0],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[1], xs[2],ys[2], xs[0],ys[2], r,g,b);
       trikampis(pav, xs[0],ys[2], xs[2],ys[2], xs[1],ys[3], r,g,b);
   }

  void raideA(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+2*p/7, x+3*p/7, x+4*p/7, x+5*p/7, x+p, x+2*p/7, x+5*p/7, x+3*p/7, x+3*p/7, x+4*p/7, x+4*p/7, x+p/2, x+2*p/7, x+5*p/7, x+3*p/7, x+4*p/7};  
  int ys[] = {y, y, y, y, y, y, y-4*a/5, y-4*a/5, y-3*a/5, y-2*a/5, y-2*a/5, y-3*a/5, y-a, y-a/5, y-a/5, y-4*a/5, y-4*a/5};

  trikampis(pav, xs[0], ys[0], xs[1], ys[1], xs[13], ys[13], r, g, b);
  trikampis(pav, xs[1], ys[1], xs[6], ys[6], xs[15], ys[15], r, g, b);
  trikampis(pav, xs[1], ys[1], xs[2], ys[2], xs[15], ys[15], r, g, b);
  trikampis(pav, xs[6], ys[6], xs[7], ys[7], xs[12], ys[12], r, g, b);
  trikampis(pav, xs[8], ys[8], xs[9], ys[9], xs[11], ys[11], r, g, b);
  trikampis(pav, xs[9], ys[9], xs[10], ys[10], xs[11], ys[11], r, g, b);
  trikampis(pav, xs[3], ys[3], xs[4], ys[4], xs[16], ys[16], r, g, b);
  trikampis(pav, xs[4], ys[4], xs[7], ys[7], xs[16], ys[16], r, g, b);
  trikampis(pav, xs[4], ys[4], xs[5], ys[5], xs[14], ys[14], r, g, b);

}

void raideE(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
   int xs[] = {x,x+p/3, x+p*2/3, x+p};
    int ys[] = {y, y+a/5, y+2*a/5, y+3*a/5, y+4*a/5, y+a}; 

    trikampis(pav, xs[0], ys[0], xs[1], ys[0], xs[0], ys[5], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[0], ys[5], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[3], ys[0], xs[1], ys[1], r, g, b);
    trikampis(pav, xs[1], ys[1], xs[3], ys[0], xs[2], ys[1], r, g, b);
    trikampis(pav, xs[1], ys[2], xs[2], ys[3], xs[1], ys[3], r, g, b);
    trikampis(pav, xs[1], ys[4], xs[3], ys[5], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[1], ys[4], xs[2], ys[4], xs[3], ys[5], r, g, b); 
}

void raideY(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/4, x+p*2/4,x+p*3/4, x+p};
       int ys[] = {y, y+a/5, y+a*2/5, y+a*3/5, y+a};

       trikampis(pav, xs[0],ys[0], xs[1],ys[0], xs[0],ys[2], r,g,b);
       trikampis(pav, xs[1],ys[0], xs[0],ys[2], xs[1],ys[2], r,g,b);
       trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[1],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[1], xs[1],ys[4], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[1],ys[4], xs[3],ys[4], r,g,b);
       trikampis(pav, xs[3],ys[4], xs[2],ys[2], xs[3],ys[1], r,g,b);
       trikampis(pav, xs[3],ys[2], xs[4],ys[2], xs[3],ys[3], r,g,b);
       trikampis(pav, xs[3],ys[2], xs[4],ys[2], xs[4],ys[0], r,g,b);
       trikampis(pav, xs[4],ys[0], xs[3],ys[2], xs[3],ys[0], r,g,b);

}

void raideM(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
      int xs[] = {x, x+p/6, x+2*p/6, x+3*p/6, x+4*p/6, x+5*p/6, x+p};
      int ys[] = {y, y-a/4, y-a/2, y-3*a/4, y-a};
      
      trikampis(pav, xs[0],ys[0], xs[0],ys[2], xs[1],ys[0], r,g,b);
      trikampis(pav, xs[1],ys[0], xs[0],ys[2], xs[1],ys[2], r,g,b);           
      trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[2],ys[3], r,g,b);           
      trikampis(pav, xs[0],ys[2], xs[2],ys[3], xs[2],ys[4], r,g,b);        
      trikampis(pav, xs[2],ys[3], xs[2],ys[4], xs[3],ys[1], r,g,b);          
      trikampis(pav, xs[2],ys[4], xs[3],ys[1], xs[3],ys[2], r,g,b);
      trikampis(pav, xs[3],ys[1], xs[3],ys[2], xs[4],ys[4], r,g,b);
      trikampis(pav, xs[3],ys[1], xs[4],ys[3], xs[4],ys[4], r,g,b);
      trikampis(pav, xs[4],ys[3], xs[4],ys[4], xs[5],ys[2], r,g,b);
      trikampis(pav, xs[5],ys[2], xs[6],ys[2], xs[4],ys[4], r,g,b);
      trikampis(pav, xs[5],ys[2], xs[6],ys[2], xs[5],ys[0], r,g,b);
      trikampis(pav, xs[6],ys[0], xs[5],ys[0], xs[6],ys[2], r,g,b);
      trikampis(pav, xs[1],ys[0], xs[2],ys[0], xs[1],ys[1], r,g,b);
      trikampis(pav, xs[4],ys[0], xs[5],ys[0], xs[5],ys[1], r,g,b);

}

void raideX(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
    
    int xs[] = {x, x+p/8, x+p*2/8, x+p*3/8, x+p*4/8, x+p*5/8, x+p*6/8, x+p*7/8, x+p};
    int ys[] = {y, y+a/5, y+2*a/6, y+3*a/6, y+4*a/6, y+5*a/6, y+a};

    trikampis(pav, xs[0], ys[0], xs[2], ys[0], xs[3], ys[3], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[3], ys[3], xs[4], ys[2], r, g, b);
    trikampis(pav, xs[3], ys[3], xs[4], ys[2], xs[4], ys[4], r, g, b);
    trikampis(pav, xs[4], ys[2], xs[4], ys[4], xs[5], ys[3], r, g, b);
    trikampis(pav, xs[3], ys[3], xs[0], ys[6], xs[2], ys[6], r, g, b);
    trikampis(pav, xs[3], ys[3], xs[2], ys[6], xs[4], ys[4], r, g, b);
    trikampis(pav, xs[4], ys[2], xs[5], ys[3], xs[6], ys[0], r, g, b);
    trikampis(pav, xs[6], ys[0], xs[8], ys[0], xs[5], ys[3], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[5], ys[3], xs[8], ys[6], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[8], ys[6], xs[6], ys[6], r, g, b);

}

void raideS(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/8, x+p*2/8, x+p*3/8, x+p*4/8, x+p*5/8, x+p*6/8, x+p*7/8, x+p};
    int ys[] = {y, y+a/5, y+2*a/6, y+3*a/6, y+4*a/6, y+5*a/6, y+a};

    trikampis(pav, xs[1], ys[0], xs[2], ys[0], xs[0], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[2], ys[1], xs[0], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[2], ys[2], xs[3], ys[1], r, g, b);
    trikampis(pav, xs[0], ys[1], xs[1], ys[1], xs[1], ys[2], r, g, b);
    trikampis(pav, xs[0], ys[1], xs[0], ys[2], xs[1], ys[2], r, g, b);
    trikampis(pav, xs[0], ys[1], xs[0], ys[2], xs[1], ys[2], r, g, b);
    trikampis(pav, xs[0], ys[2], xs[1], ys[2], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[0], ys[2], xs[2], ys[4], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[2], ys[4], xs[3], ys[4], xs[2], ys[6], r, g, b);
    trikampis(pav, xs[3], ys[4], xs[2], ys[6], xs[3], ys[5], r, g, b);
    trikampis(pav, xs[1], ys[5], xs[2], ys[5], xs[2], ys[6], r, g, b);
    trikampis(pav, xs[1], ys[5], xs[1], ys[6], xs[2], ys[6], r, g, b);
    trikampis(pav, xs[0], ys[5], xs[1], ys[4], xs[1], ys[6], r, g, b);


}

void raideR(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/4, x+p*2/4, x+p*3/4, x+p};
    int ys[] = {y, y+a/5, y+2*a/5, y+3*a/5, y+4*a/5, y+a};

    trikampis(pav, xs[1], ys[0], xs[2], ys[0], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[0], ys[0], xs[1], ys[0], xs[1], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[2], ys[5], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[2], ys[1], xs[3], ys[0], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[3], ys[0], xs[4], ys[1], r, g, b);
    trikampis(pav, xs[3], ys[1], xs[4], ys[1], xs[4], ys[2], r, g, b);
    trikampis(pav, xs[3], ys[1], xs[4], ys[2], xs[3], ys[3], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[3], ys[2], xs[2], ys[3], r, g, b);
    trikampis(pav, xs[3], ys[2], xs[2], ys[3], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[3], ys[3], xs[3], ys[5], xs[4], ys[4], r, g, b);
    trikampis(pav, xs[3], ys[5], xs[4], ys[5], xs[4], ys[4], r, g, b);

}
////////////////////
void raideB(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/5, x+p*2/5, x+p*3/5, x+p*4/5, x+p};
    int ys[] = {y, y+a/6, y+2*a/6, y+3*a/6, y+4*a/6, y+5*a/6, y+a}; 

    trikampis(pav, xs[0], ys[1], xs[1], ys[1], xs[1], ys[0], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[2], ys[0], xs[1], ys[6], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[1], ys[6], xs[2], ys[6], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[3], ys[0], xs[2], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[3], ys[0], xs[4], ys[1], r, g, b);
    trikampis(pav, xs[3], ys[1], xs[4], ys[2], xs[4], ys[1], r, g, b);
    trikampis(pav, xs[3], ys[1], xs[4], ys[2], xs[3], ys[3], r, g, b);
    trikampis(pav, xs[3], ys[2], xs[2], ys[4], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[3], ys[2], xs[2], ys[4], r, g, b);
    trikampis(pav, xs[3], ys[3], xs[4], ys[3], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[3], ys[4], xs[4], ys[3], xs[5], ys[4], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[5], ys[4], xs[5], ys[5], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[5], ys[5], xs[4], ys[6], r, g, b);
    trikampis(pav, xs[2], ys[5], xs[4], ys[5], xs[2], ys[6], r, g, b);
    trikampis(pav, xs[2], ys[6], xs[4], ys[5], xs[4], ys[6], r, g, b);
    trikampis(pav, xs[3], ys[5], xs[4], ys[5], xs[4], ys[4], r, g, b);
}
/////////////////
void raideC1(struct PPM6* pav,  int x, int y,                    // k.v. kampas
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){



       int xs[] = {x, x+p/5, x+p*2/5, x+p*3/5, x+p*4/5, x+p};
    int ys[] = {y, y+a/7, y+2*a/7, y+3*a/7, y+4*a/7, y+5*a/7, y+6*a/7, y+a};

    trikampis(pav, xs[0], ys[2], xs[0], ys[5], xs[1], ys[6], r, g, b);
    trikampis(pav, xs[1], ys[6], xs[1], ys[1], xs[0], ys[2], r, g, b);
    trikampis(pav, xs[1], ys[1], xs[1], ys[2], xs[2], ys[0], r, g, b);
    trikampis(pav, xs[1], ys[2], xs[2], ys[1], xs[2], ys[0], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[2], ys[1], xs[4], ys[0], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[4], ys[0], xs[5], ys[1], r, g, b);
    trikampis(pav, xs[4], ys[1], xs[5], ys[1], xs[5], ys[2], r, g, b);
    trikampis(pav, xs[1], ys[5], xs[1], ys[6], xs[2], ys[7], r, g, b);
    trikampis(pav, xs[1], ys[5], xs[2], ys[7], xs[2], ys[6], r, g, b);
    trikampis(pav, xs[2], ys[6], xs[2], ys[7], xs[4], ys[7], r, g, b);
    trikampis(pav, xs[2], ys[6], xs[4], ys[7], xs[5], ys[6], r, g, b);
    trikampis(pav, xs[4], ys[6], xs[5], ys[6], xs[5], ys[5], r, g, b);



}
////////////////////
void raideD(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+2*p/3, x+p, x+2*p/3, x, x+p/6, x+3*p/6, x+p/6};  
  int ys[] = {y, y+a/6, y+a/2, y+5*a/6, y+a, y+2*a/6, y+a/2, y+4*a/6};

  trikampis(pav, xs[0], ys[0], xs[5], ys[5], xs[1], ys[1], r, g, b);
  trikampis(pav, xs[5], ys[5], xs[1], ys[1], xs[6], ys[6], r, g, b);
  trikampis(pav, xs[1], ys[1], xs[6], ys[6], xs[2], ys[2], r, g, b);
  trikampis(pav, xs[2], ys[2], xs[6], ys[6], xs[3], ys[3], r, g, b);
  trikampis(pav, xs[3], ys[3], xs[6], ys[6], xs[7], ys[7], r, g, b);
  trikampis(pav, xs[3], ys[3], xs[7], ys[7], xs[4], ys[4], r, g, b);
  trikampis(pav, xs[4], ys[4], xs[5], ys[5], xs[7], ys[7], r, g, b);
  trikampis(pav, xs[0], ys[0], xs[4], ys[4], xs[5], ys[5], r, g, b);


}
//////////////////
void raideF(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/4, x+2*p/4, x+3*p/4, x+p};
    int ys[] = {y, y+a/5, y+2*a/5, y+3*a/5, y+4*a/5, y+a};

    trikampis(pav, xs[0], ys[5], xs[1], ys[5], xs[1], ys[4], r, g, b);
    trikampis(pav, xs[1], ys[5], xs[2], ys[5], xs[1], ys[1], r, g, b);
    trikampis(pav, xs[1], ys[1], xs[2], ys[1], xs[2], ys[5], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[1], ys[1], xs[3], ys[0], r, g, b);
    trikampis(pav, xs[1], ys[1], xs[3], ys[0], xs[3], ys[1], r, g, b);
    trikampis(pav, xs[4], ys[0], xs[3], ys[0], xs[3], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[2], ys[3], xs[3], ys[2], r, g, b);
    trikampis(pav, xs[2], ys[3], xs[3], ys[2], xs[3], ys[3], r, g, b);
    trikampis(pav, xs[3], ys[2], xs[3], ys[3], xs[4], ys[2], r, g, b);
}
//////////////////////
void raideG(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+3*p/4, x+p, x+3*p/4, x+p/4, x+p/4, x+3*p/4, x+3*p/4, x+p/2, x+p/2, x+3*p/4, x+p, x+p, x+3*p/4, x+p/4, x, x};  
  int ys[] = {y, y, y+2*a/6, y+a/6, y+a/6, y+5*a/6, y+5*a/6, y+4*a/6, y+4*a/6, y+a/2, y+a/2, y+a/2, y+a, y+a, y+a, y+a, y+a/6};

  trikampis(pav, xs[0], ys[0], xs[1], ys[1], xs[16], ys[16], r, g, b);
  trikampis(pav, xs[16], ys[16], xs[1], ys[1], xs[3], ys[3], r, g, b);
  trikampis(pav, xs[1], ys[1], xs[2], ys[2], xs[3], ys[3], r, g, b);
  trikampis(pav, xs[15], ys[15], xs[16], ys[16], xs[14], ys[14], r, g, b);
  trikampis(pav, xs[4], ys[4], xs[16], ys[16], xs[14], ys[14], r, g, b);
  trikampis(pav, xs[5], ys[5], xs[6], ys[6], xs[14], ys[14], r, g, b);
  trikampis(pav, xs[13], ys[13], xs[6], ys[6], xs[14], ys[14], r, g, b);
  trikampis(pav, xs[13], ys[13], xs[12], ys[12], xs[10], ys[10], r, g, b);
  trikampis(pav, xs[12], ys[12], xs[11], ys[11], xs[10], ys[10], r, g, b);
  trikampis(pav, xs[9], ys[9], xs[7], ys[7], xs[10], ys[10], r, g, b);
  trikampis(pav, xs[8], ys[8], xs[9], ys[9], xs[7], ys[7], r, g, b);

}
///////////////////
void raideH(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/5, x+2*p/5, x+3*p/5, x+4*p/5, x+p};
    int ys[] = {y, y+a/3, y+2*a/3, y+a}; 

    trikampis(pav, xs[0], ys[0], xs[1], ys[0], xs[1], ys[1], r, g, b);
    trikampis(pav, xs[0], ys[3], xs[1], ys[3], xs[1], ys[2], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[2], ys[0], xs[1], ys[3], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[1], ys[3], xs[2], ys[3], r, g, b);
    trikampis(pav, xs[0], ys[0], xs[1], ys[0], xs[1], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[3], ys[1], xs[3], ys[2], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[2], ys[2], xs[3], ys[2], r, g, b);
    trikampis(pav, xs[3], ys[0], xs[4], ys[0], xs[3], ys[3], r, g, b);
    trikampis(pav, xs[4], ys[0], xs[3], ys[3], xs[4], ys[3], r, g, b);
    trikampis(pav, xs[4], ys[0], xs[5], ys[0], xs[4], ys[1], r, g, b);
    trikampis(pav, xs[4], ys[3], xs[5], ys[3], xs[4], ys[2], r, g, b);

}
/////////////////
void raideI(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x,x+p/3, x+p*2/3, x+p};
    int ys[] = {y, y+a/5, y+2*a/5, y+3*a/5, y+4*a/5, y+a}; 

    trikampis(pav, xs[0], ys[0], xs[3], ys[0], xs[0], ys[1], r, g, b);
    trikampis(pav, xs[0], ys[1], xs[3], ys[0], xs[3], ys[1], r, g, b);
    trikampis(pav, xs[1], ys[1], xs[2], ys[1], xs[1], ys[4], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[1], ys[4], xs[2], ys[4], r, g, b);
    trikampis(pav, xs[0], ys[4], xs[3], ys[4], xs[0], ys[5], r, g, b);
    trikampis(pav, xs[0], ys[5], xs[3], ys[4], xs[3], ys[5], r, g, b);

}
///////////////////
void raideJ(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/5, x+p*2/5, x+p*3/5, x+p*4/5, x+p};
    int ys[] = {y, y+a/6, y+a*2/6, y+a*3/6, y+a*4/6, y+a*5/6, y+a};

    trikampis(pav, xs[0], ys[0], xs[1], ys[0], xs[1], ys[1], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[1], ys[1], xs[5], ys[1], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[5], ys[0], xs[5], ys[1], r, g, b);
    trikampis(pav, xs[4], ys[1], xs[4], ys[2], xs[5], ys[1], r, g, b);
    trikampis(pav, xs[4], ys[2], xs[5], ys[2], xs[5], ys[1], r, g, b);
    trikampis(pav, xs[4], ys[2], xs[5], ys[2], xs[4], ys[4], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[5], ys[4], xs[5], ys[2], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[5], ys[4], xs[4], ys[6], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[3], ys[5], xs[4], ys[6], r, g, b);
    trikampis(pav, xs[3], ys[5], xs[1], ys[6], xs[4], ys[6], r, g, b);
    trikampis(pav, xs[1], ys[5], xs[5], ys[4], xs[1], ys[6], r, g, b);
    trikampis(pav, xs[1], ys[4], xs[1], ys[5], xs[2], ys[5], r, g, b);
    
}
//////////////////
void raideK(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/5, x+2*p/5, x+3*p/5, x+4*p/5, x+p};
    int ys[] = {y, y+a/6, y+2*a/6, y+3*a/6, y+4*a/6, y+5*a/6, y+a};

    trikampis(pav, xs[0], ys[0], xs[1], ys[0], xs[1], ys[1], r, g, b);
    trikampis(pav, xs[0], ys[6], xs[1], ys[6], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[1], ys[6], xs[2], ys[6], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[2], ys[0], xs[2], ys[6], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[3], ys[0], xs[4], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[2], ys[3], xs[4], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[3], xs[2], ys[4], xs[3], ys[6], r, g, b);
    trikampis(pav, xs[2], ys[3], xs[3], ys[6], xs[4], ys[5], r, g, b);
    trikampis(pav, xs[5], ys[6], xs[3], ys[6], xs[4], ys[5], r, g, b);
    trikampis(pav, xs[3], ys[0], xs[5], ys[0], xs[4], ys[1], r, g, b);
    
}
/////////////
void raideL(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/5, x+2*p/5, x+3*p/5, x+4*p/5, x+p};
    int ys[] = {y, y+a/5, y+2*a/5, y+3*a/5, y+4*a/5, y+a};

    trikampis(pav, xs[0], ys[2], xs[1], ys[1], xs[1], ys[3], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[1], ys[1], xs[2], ys[1], r, g, b);
    trikampis(pav, xs[1], ys[5], xs[1], ys[1], xs[2], ys[5], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[1], ys[1], xs[2], ys[5], r, g, b);
    trikampis(pav, xs[2], ys[4], xs[2], ys[5], xs[4], ys[4], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[2], ys[5], xs[4], ys[5], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[4], ys[5], xs[5], ys[5], r, g, b);
}
////////////////////
void raideN(struct PPM6* pav,  int x, int y,                    // k.v. kampas
                 int p, int a, uint8_t r, uint8_t g, uint8_t b){



      int xs[] = {x, x+p/5, x+p*2/5, x+p*3/5, x+p*4/5, x+p};
    int ys[] = {y, y+a/4, y+2*a/4, y+3*a/4, y+a};

    trikampis(pav, xs[0], ys[4], xs[1], ys[4], xs[1], ys[3], r, g, b);
    trikampis(pav, xs[1], ys[4], xs[1], ys[0], xs[2], ys[0], r, g, b);
    trikampis(pav, xs[1], ys[4], xs[2], ys[4], xs[2], ys[0], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[2], ys[1], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[3], ys[4], xs[3], ys[3], r, g, b);
    trikampis(pav, xs[3], ys[0], xs[4], ys[0], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[3], ys[4], xs[4], ys[4], xs[4], ys[0], r, g, b);
    trikampis(pav, xs[4], ys[0], xs[1], ys[4], xs[5], ys[0], r, g, b);

}
/////////////////
void raideO(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/3, x+p*2/3, x+p};
       int ys[] = {y, y+a/4, y+a*2/4, y+a*3/4, y+a};

       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[0], r,g,b);
       trikampis(pav, xs[1],ys[0], xs[1],ys[1], xs[2],ys[0], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[1], xs[3],ys[1], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[1], xs[3],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[2], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[3],ys[2], xs[3],ys[3], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[3], xs[3],ys[3], xs[2],ys[4], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[1],ys[3], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[2],ys[4], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[3], xs[1],ys[4], xs[0],ys[3], r,g,b);
       trikampis(pav, xs[0],ys[3], xs[1],ys[3], xs[0],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[3], r,g,b);
 
}
//////////////////
void raideP(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/4, x+p*2/4, x+p*3/4, x+p};
    int ys[] = {y, y+a/5, y+2*a/5, y+3*a/5, y+4*a/5, y+a};

    trikampis(pav, xs[1], ys[0], xs[2], ys[0], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[0], ys[0], xs[1], ys[0], xs[1], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[2], ys[5], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[2], ys[0], xs[2], ys[1], xs[3], ys[0], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[3], ys[0], xs[4], ys[1], r, g, b);
    trikampis(pav, xs[3], ys[1], xs[4], ys[1], xs[4], ys[2], r, g, b);
    trikampis(pav, xs[3], ys[1], xs[4], ys[2], xs[3], ys[3], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[3], ys[2], xs[2], ys[3], r, g, b);
    trikampis(pav, xs[3], ys[2], xs[2], ys[3], xs[3], ys[3], r, g, b);
}
////////////////////////
void raideQ(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/3, x+p*2/3, x+p, p*1.5+x/3};
       int ys[] = {y, y+a/4, y+a*2/4, y+a*3/4, y+a, 2.5*a+y/3};

       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[0], r,g,b);
       trikampis(pav, xs[1],ys[0], xs[1],ys[1], xs[2],ys[0], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[1], xs[3],ys[1], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[1], xs[3],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[2], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[3],ys[2], xs[3],ys[3], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[3], xs[3],ys[3], xs[2],ys[4], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[1],ys[3], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[2],ys[4], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[3], xs[1],ys[4], xs[0],ys[3], r,g,b);
       trikampis(pav, xs[0],ys[3], xs[1],ys[3], xs[0],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[3], r,g,b);
       atkarpa(pav, xs[4], ys[5], xs[3], ys[4], 0,0,0);

}
/////////////////
void raideT(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x,x+p/7, x+p*2/7, x+p*3/7, x+p*4/7,x+p*5/7, x+p*6/7, x+p};
    int ys[] = {y, y+a/5, y+2*a/5, y+3*a/5, y+4*a/5, y+a}; 

    trikampis(pav, xs[0], ys[0], xs[2], ys[1], xs[5], ys[0], r, g, b);
    trikampis(pav, xs[5], ys[0], xs[2], ys[1], xs[7], ys[1], r, g, b);
    trikampis(pav, xs[3], ys[1], xs[4], ys[1], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[4], ys[1], xs[3], ys[4], xs[4], ys[4], r, g, b);
    trikampis(pav, xs[2], ys[5], xs[3], ys[4], xs[4], ys[4], r, g, b);
    trikampis(pav, xs[4], ys[4], xs[2], ys[5], xs[5], ys[5], r, g, b);
}
//////////////////
void raideU(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/3, x+p*2/3, x+p};
       int ys[] = {y, y+a/4, y+a*2/4, y+a*3/4, y+a};

       trikampis(pav, xs[0],ys[0], xs[1],ys[1], xs[0],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[1], xs[0],ys[3], xs[1],ys[4], r,g,b);
       trikampis(pav, xs[1],ys[3], xs[1],ys[4], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[2],ys[4], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[1], xs[2],ys[4], xs[3],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[1], xs[3],ys[3], xs[3],ys[0], r,g,b);
 

}
//////////////////
void raideV(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/5, x+p*2/5, x+p*3/5, x+p*4/5, x+p};
       int ys[] = {y, y+a/6, y+2*a/6, y+3*a/6, y+4*a/6, y+5*a/6, y+a};

       trikampis(pav, xs[0],ys[0], xs[1],ys[1], xs[0],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[4], r,g,b);
       trikampis(pav, xs[1],ys[1], xs[1],ys[4], xs[2],ys[4], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[3],ys[4], xs[2],ys[6], r,g,b);
       trikampis(pav, xs[2],ys[6], xs[3],ys[6], xs[3],ys[4], r,g,b);
       trikampis(pav, xs[3],ys[4], xs[3],ys[6], xs[4],ys[4], r,g,b);
       trikampis(pav, xs[3],ys[4], xs[4],ys[4], xs[4],ys[1], r,g,b);
       trikampis(pav, xs[4],ys[4], xs[4],ys[1], xs[5],ys[1], r,g,b);
       trikampis(pav, xs[4],ys[1], xs[5],ys[1], xs[5],ys[0], r,g,b);
}
////////////////////////
void raideW(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/6, x+2*p/6, x+3*p/6, x+4*p/6, x+5*p/6, x+p};
    int ys[] = {y, y+a/4, y+a/2, y+3*a/4, y+a};
      
      trikampis(pav, xs[0],ys[0], xs[0],ys[2], xs[1],ys[0], r,g,b);
      trikampis(pav, xs[1],ys[0], xs[0],ys[2], xs[1],ys[2], r,g,b);           
      trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[2],ys[3], r,g,b);           
      trikampis(pav, xs[0],ys[2], xs[2],ys[3], xs[2],ys[4], r,g,b);        
      trikampis(pav, xs[2],ys[3], xs[2],ys[4], xs[3],ys[1], r,g,b);          
      trikampis(pav, xs[2],ys[4], xs[3],ys[1], xs[3],ys[2], r,g,b);
      trikampis(pav, xs[3],ys[1], xs[3],ys[2], xs[4],ys[4], r,g,b);
      trikampis(pav, xs[3],ys[1], xs[4],ys[3], xs[4],ys[4], r,g,b);
      trikampis(pav, xs[4],ys[3], xs[4],ys[4], xs[5],ys[2], r,g,b);
      trikampis(pav, xs[5],ys[2], xs[6],ys[2], xs[4],ys[4], r,g,b);
      trikampis(pav, xs[5],ys[2], xs[6],ys[2], xs[5],ys[0], r,g,b);
      trikampis(pav, xs[6],ys[0], xs[5],ys[0], xs[6],ys[2], r,g,b);
      trikampis(pav, xs[1],ys[0], xs[2],ys[0], xs[1],ys[1], r,g,b);
      trikampis(pav, xs[4],ys[0], xs[5],ys[0], xs[5],ys[1], r,g,b);

}
////////////////////
void raideZ(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p, x+p*3/4, x+p/4};
    int ys[] = {y, y+a/5, y+a*4/5, y+a, y+a*2/5, y+a*3/5};

    trikampis(pav, xs[0],ys[0], xs[1],ys[0], xs[0],ys[1], r,g,b);
    trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[0], r,g,b);
    trikampis(pav, xs[1],ys[1], xs[2],ys[1], xs[3],ys[2], r,g,b);
  trikampis(pav, xs[2],ys[1], xs[0],ys[2], xs[3],ys[2], r,g,b);
    trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[0],ys[3], r,g,b);
    trikampis(pav, xs[0],ys[3], xs[1],ys[2], xs[1],ys[3], r,g,b);
    trikampis(pav, xs[0],ys[1], xs[0],ys[4], xs[3],ys[1], r,g,b);
    trikampis(pav, xs[1],ys[2], xs[1],ys[5], xs[2],ys[2], r,g,b);
}
////////////////////
void skaicius0(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/3, x+p*2/3, x+p};
       int ys[] = {y, y+a/4, y+a*2/4, y+a*3/4, y+a};

       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[0], r,g,b);
       trikampis(pav, xs[1],ys[0], xs[1],ys[1], xs[2],ys[0], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[1], xs[3],ys[1], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[1], xs[3],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[2], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[3],ys[2], xs[3],ys[3], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[3], xs[3],ys[3], xs[2],ys[4], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[1],ys[3], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[2],ys[4], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[3], xs[1],ys[4], xs[0],ys[3], r,g,b);
       trikampis(pav, xs[0],ys[3], xs[1],ys[3], xs[0],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[3], r,g,b);
       atkarpa(pav, xs[1], ys[3], xs[2], ys[1], r,g,b);

}
/////////////////
void skaicius1(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/3, x+p*2/3, x+p};
       int ys[] = {y, y+a/5,y+a*4/5, y+a};

       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[0], r,g,b);
       trikampis(pav, xs[1],ys[0], xs[1],ys[2], xs[2],ys[0], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[1],ys[2], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[0],ys[2], xs[3],ys[2], xs[0],ys[3], r,g,b);
       trikampis(pav, xs[0],ys[3], xs[3],ys[3], xs[3],ys[2], r,g,b);
 
}
//////////////////////
void skaicius2(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/4, x+p*2/4, x+p*3/4, x+p};
    int ys[] = {y, y+a/4, y+2*a/4, y+3*a/4, y+a};

    trikampis(pav, xs[0], ys[1], xs[1], ys[0], xs[2], ys[0], r, g, b);
    trikampis(pav, xs[0], ys[1], xs[2], ys[0], xs[3], ys[1], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[3], ys[1], xs[3], ys[2], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[3], ys[2], xs[2], ys[3], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[1], ys[3], xs[2], ys[3], r, g, b);
    trikampis(pav, xs[0], ys[4], xs[1], ys[3], xs[4], ys[3], r, g, b);
    trikampis(pav, xs[0], ys[4], xs[4], ys[3], xs[3], ys[4], r, g, b);

}
////////////////////
void skaicius3(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/4, x+a/2, x+3*p/4, x+p};
    int ys[] = {y, y+a/6, y+2*a/6, y+3*a/6, y+4*a/6, y+5*a/6, y+a};
      
      trikampis(pav, xs[0],ys[0], xs[2],ys[0], xs[0],ys[1], r,g,b);
      trikampis(pav, xs[0],ys[1], xs[2],ys[0], xs[2],ys[1], r,g,b);           
      trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[2], r,g,b);           
      trikampis(pav, xs[2],ys[0], xs[3],ys[2], xs[4],ys[2], r,g,b);          
      trikampis(pav, xs[3],ys[2], xs[4],ys[2], xs[1],ys[3], r,g,b);          
      trikampis(pav, xs[4],ys[2], xs[1],ys[3], xs[2],ys[3], r,g,b);
      trikampis(pav, xs[1],ys[3], xs[2],ys[3], xs[4],ys[4], r,g,b);
      trikampis(pav, xs[1],ys[3], xs[3],ys[4], xs[4],ys[4], r,g,b);
      trikampis(pav, xs[3],ys[4], xs[4],ys[4], xs[2],ys[5], r,g,b);
      trikampis(pav, xs[2],ys[5], xs[2],ys[6], xs[4],ys[4], r,g,b);
      trikampis(pav, xs[2],ys[5], xs[2],ys[6], xs[0],ys[5], r,g,b);
      trikampis(pav, xs[0],ys[6], xs[0],ys[5], xs[2],ys[6], r,g,b);
 

}
////////////////
void skaicius4(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/3, x+p*2/3, x+p};
    int ys[] = {y, y+a/6, y+2*a/6, y+3*a/6, y+4*a/6, y+5*a/6, y+a};

    trikampis(pav, xs[0], ys[1], xs[1], ys[0], xs[1], ys[3], r, g, b);
    trikampis(pav, xs[0], ys[1], xs[0], ys[3], xs[1], ys[3], r, g, b);
    trikampis(pav, xs[0], ys[3], xs[1], ys[4], xs[3], ys[3], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[2], ys[3], xs[3], ys[3], r, g, b);
    trikampis(pav, xs[1], ys[4], xs[3], ys[3], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[2], ys[4], xs[3], ys[4], xs[2], ys[5], r, g, b);
    trikampis(pav, xs[2], ys[5], xs[3], ys[4], xs[3], ys[6], r, g, b);

}
////////////////////
void skaicius5(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/3, x+p*2/3, x+p};
    int ys[] = {y, y+a/5, y+2*a/5, y+3*a/5, y+4*a/5, y+a};

    trikampis(pav, xs[0], ys[0], xs[4], ys[0], xs[3], ys[1], r, g, b);
    trikampis(pav, xs[0], ys[0], xs[3], ys[1], xs[0], ys[1], r, g, b);
    trikampis(pav, xs[0], ys[1], xs[1], ys[1], xs[2], ys[3], r, g, b);
    trikampis(pav, xs[1], ys[1], xs[2], ys[2], xs[2], ys[3], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[3], ys[2], xs[2], ys[3], r, g, b);
    trikampis(pav, xs[2], ys[3], xs[3], ys[2], xs[4], ys[3], r, g, b);
    trikampis(pav, xs[3], ys[3], xs[4], ys[3], xs[4], ys[4], r, g, b);
    trikampis(pav, xs[3], ys[3], xs[3], ys[5], xs[4], ys[4], r, g, b);
    trikampis(pav, xs[3], ys[4], xs[3], ys[5], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[3], ys[4], xs[1], ys[5], xs[0], ys[4], r, g, b);
    trikampis(pav, xs[0], ys[4], xs[1], ys[3], xs[1], ys[4], r, g, b);

}
////////////////
void skaicius6(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/3, x+p*2/3, x+p};
    int ys[] = {y, y+a/5, y+2*a/5, y+3*a/5, y+4*a/5, y+a};

    trikampis(pav, xs[0], ys[1], xs[1], ys[0], xs[3], ys[1], r, g, b);
    trikampis(pav, xs[1], ys[0], xs[2], ys[0], xs[3], ys[1], r, g, b);
    trikampis(pav, xs[0], ys[1], xs[1], ys[1], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[0], ys[1], xs[0], ys[4], xs[1], ys[5], r, g, b);
    trikampis(pav, xs[1], ys[4], xs[1], ys[5], xs[2], ys[4], r, g, b);
    trikampis(pav, xs[1], ys[5], xs[2], ys[4], xs[2], ys[5], r, g, b);
    trikampis(pav, xs[2], ys[3], xs[2], ys[5], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[2], ys[3], xs[3], ys[3], xs[3], ys[4], r, g, b);
    trikampis(pav, xs[1], ys[3], xs[3], ys[3], xs[2], ys[2], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[1], ys[2], xs[1], ys[3], r, g, b);

}
////////////////////////
void skaicius7(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
    int xs[] = {x, x+p/3, x+p*2/3, x+p};
    int ys[] = {y, y+a/4, y+2*a/4, y+3*a/4, y+a};

    trikampis(pav, xs[0], ys[0], xs[3], ys[0], xs[1], ys[1], r, g, b);
    trikampis(pav, xs[1], ys[1], xs[3], ys[1], xs[3], ys[0], r, g, b);
    trikampis(pav, xs[2], ys[1], xs[3], ys[1], xs[1], ys[2], r, g, b);
    trikampis(pav, xs[3], ys[1], xs[2], ys[2], xs[1], ys[2], r, g, b);
    trikampis(pav, xs[1], ys[2], xs[2], ys[2], xs[1], ys[3], r, g, b);
    trikampis(pav, xs[2], ys[2], xs[1], ys[3], xs[2], ys[3], r, g, b);
    trikampis(pav, xs[1], ys[3], xs[2], ys[3], xs[1], ys[4], r, g, b);

}
/////////////////
void skaicius8(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/3, x+p*2/3, x+p};
       int ys[] = {y, y+a/6, y+a*2/6, y+a*3/6, y+a*4/6, y+a*5/6, y+a};

       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[0], r,g,b);
       trikampis(pav, xs[1],ys[0], xs[1],ys[1], xs[2],ys[0], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[1], xs[3],ys[1], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[1], xs[3],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[2], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[2],ys[3], xs[1],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[3], xs[1],ys[2], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[1],ys[2], xs[0],ys[2], xs[1],ys[3], r,g,b);
       trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[2], xs[0],ys[1], xs[1],ys[1], r,g,b);

       trikampis(pav, xs[0],ys[4], xs[1],ys[4], xs[1],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[1],ys[3], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[2],ys[4], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[3], xs[2],ys[4], xs[3],ys[4], r,g,b);
       trikampis(pav, xs[2],ys[4], xs[3],ys[4], xs[2],ys[5], r,g,b);
       trikampis(pav, xs[2],ys[5], xs[3],ys[5], xs[3],ys[4], r,g,b);
       trikampis(pav, xs[2],ys[5], xs[2],ys[6], xs[3],ys[5], r,g,b);
       trikampis(pav, xs[2],ys[5], xs[2],ys[6], xs[1],ys[6], r,g,b);
       trikampis(pav, xs[1],ys[5], xs[1],ys[6], xs[2],ys[5], r,g,b);
       trikampis(pav, xs[1],ys[5], xs[1],ys[6], xs[0],ys[5], r,g,b);
       trikampis(pav, xs[0],ys[5], xs[1],ys[5], xs[1],ys[4], r,g,b);
       trikampis(pav, xs[1],ys[4], xs[0],ys[4], xs[0],ys[5], r,g,b);

}
/////////////////
void skaicius9(struct PPM6* pav, int x, int y, int p, int a, uint8_t r, uint8_t g, uint8_t b){
  
  int xs[] = {x, x+p/3, x+p*2/3, x+p};
       int ys[] = {y, y+a/6, y+a*2/6, y+a*3/6, y+a*4/6, y+a*5/6, y+a};

       trikampis(pav, xs[0],ys[1], xs[1],ys[1], xs[1],ys[0], r,g,b);
       trikampis(pav, xs[1],ys[0], xs[1],ys[1], xs[2],ys[0], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[0], xs[2],ys[1], xs[3],ys[1], r,g,b);
       trikampis(pav, xs[2],ys[1], xs[3],ys[1], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[1], xs[3],ys[2], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[3],ys[2], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[2], xs[2],ys[3], xs[1],ys[3], r,g,b);
       trikampis(pav, xs[1],ys[3], xs[1],ys[2], xs[2],ys[2], r,g,b);
       trikampis(pav, xs[1],ys[2], xs[0],ys[2], xs[1],ys[3], r,g,b);
       trikampis(pav, xs[0],ys[2], xs[1],ys[2], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[0],ys[2], xs[0],ys[1], xs[1],ys[1], r,g,b);
       trikampis(pav, xs[3],ys[2], xs[3],ys[3], xs[2],ys[3], r,g,b);
       trikampis(pav, xs[2],ys[3], xs[3],ys[3], xs[2],ys[5], r,g,b);
       trikampis(pav, xs[3],ys[3], xs[2],ys[5], xs[3],ys[4], r,g,b);
       trikampis(pav, xs[0],ys[4], xs[2],ys[4], xs[2],ys[5], r,g,b);
       trikampis(pav, xs[2],ys[5], xs[1],ys[5], xs[0],ys[4], r,g,b);

}
/////////////////////