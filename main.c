#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "ppm6.h"

/////////////////////////////////////////////////////////////

int main(){
 
   char pavadinimas[20] = "";
   for (int i=1;i<800;i++){ 
      sprintf(pavadinimas, "kadras-%d.ppm", i);
      struct PPM6* pav = kurkPaveiksleli(pavadinimas, 1280, 720, 255);
      staciakampis(pav, 0, 0, 1279, 719, 0,35,46); //nuspalviname dali fono tamsiai melynai
      staciakampis(pav, 0, 450, 1279, 269, 255,255,255);    //nuspalviname dali fono baltai
      menulis(pav, 740, 50, 100, 120, 233,233,193); //pastatome menuli fone

      if(i%5==0){
       	blight(pav, 60, 280, 20, 20, 255,255,255);
       	blight(pav, 320, 150, 20, 20, 255,255,255);
       	blight(pav, 590, 260, 20, 20, 255, 255, 255);  //blight, tai blyksincios zvaigzdes, is didesniu tampa mazesnes.
       	blight(pav, 750, 210, 20, 20, 255,255,255);
       	blight(pav, 920, 50, 20, 20, 255, 255, 255);
       			
       }
       	else {
       		blight(pav, 65, 285, 10, 10, 255,255,255);
       		blight(pav, 325, 155, 10, 10, 255,255,255);
                  blight(pav, 595, 265, 10, 10, 255, 255, 255);
       		blight(pav, 755, 215, 10, 10, 255,255,255);
       		blight(pav, 925, 55, 10, 10, 255, 255, 255);
       				
       	}

      if(i%5!=0){
       	blight(pav, 210, 70, 20, 20, 255,255,255);
       	if (i<770) blight(pav, 480, 30, 20, 20, 255,255,255); //viena zvaigzde kuri isnyksta.
       	blight(pav, 850, 350, 20, 20, 255,255,255);                    
       	blight(pav, 1130, 240, 20, 20, 255, 255, 255);        //blight, tai blyksincios zvaigzdes, is mazesniu tampa didesnes.
      }
       	else {
       		blight(pav, 215, 75, 10, 10, 255,255,255);
       		if (i<770) blight(pav, 485, 35, 10, 10, 255,255,255);
       		blight(pav, 855, 355, 10, 10, 255,255,255);
       		blight(pav, 1135, 245, 10, 10, 255, 255, 255);
       	}

	//pilki namukai
      hata5(pav, 1, 340, 100, 120, 30,30,30);
      hata6(pav, 100, 340, 100, 120, 30,30,30);
      hata7(pav, 200, 360, 80, 100, 30,30,30);
      hata8(pav, 280, 380, 60, 80, 30,30,30);
      //tarpas
      hata1(pav, 830, 360, 80, 100, 30,30,30);
      hata3(pav, 900, 400, 50, 60, 30,30,30);   //pastatome namus fone
      hata2(pav, 949, 340, 100, 120, 30,30,30);
      hata4(pav, 1045, 370, 70, 90, 30,30,30);
      //tarpas
      hata2(pav, 510, 360, 100, 120, 30,30,30);
      hata4(pav, 610, 390, 70, 90, 30,30,30);
      hata7(pav, 679, 360, 100, 120, 30,30,30);


      //juodi namukai
      hata1(pav, 1, 380, 80, 100, 0,0,0);
      hata3(pav, 70, 420, 50, 60, 0,0,0);
      hata2(pav, 119, 360, 100, 120, 0,0,0);
      hata4(pav, 215, 390, 70, 90, 0,0,0);
      //tarpas
      hata5(pav, 330, 360, 100, 120, 0,0,0);
      hata6(pav, 430, 360, 100, 120, 0,0,0);
      hata7(pav, 530, 380, 80, 100, 0,0,0);
      hata8(pav, 610, 400, 60, 80, 0,0,0);
      hata1(pav, 660, 380, 80, 100, 0,0,0);
      //tarpas
      hata5(pav, 760, 400, 60, 80, 0,0,0);
      hata3(pav, 800, 420, 50, 60, 0,0,0);
      hata8(pav, 846, 360, 100, 120, 0,0,0);
      //tarpas
      hata2(pav, 1010, 360, 100, 120, 0,0,0);
      hata4(pav, 1110, 390, 70, 90, 0,0,0);
      hata7(pav, 1179, 360, 100, 120, 0,0,0);


      if(i<200){
 	      santa(pav, i, 25+i/4, 40+i*3/5, 30+i*9/20, 0,0,0);
            elk(pav, i+(75+i/2), 25+i/4, 40+i*3/5, 30+i*9/20, 0,0,0);  //kaledu senis atskrenda ir dideja.
            elk(pav, i+(150+i*0.875), 25+i/4, 40+i*3/5, 30+i*9/20, 0,0,0);

      }
      if(i>=200&&i<600){
       	santa(pav, i, 75, 160, 120, 0,0,0);
       	elk(pav, i+175, 75, 160, 120, 0,0,0); //islieka tokio pat dydzio ir meto dovanas.
       	elk(pav, i+325, 75, 160, 120, 0,0,0);
       

      }
      if(i>=600){
       	santa(pav, i, -0.325*i+270, -3*i/5+520, -9*i/20+390, 0,0,0);
       	elk(pav, (-i/2+475)+i, -0.325*i+270, -3*i/5+520, -9*i/20+390, 0,0,0);  //SKRENDA į Ñahui, Peru(14°24′28″ p. pl. 71°18′0″ v. ilg.)
       	elk(pav, (-7*i/8+850)+i, -0.325*i+270, -3*i/5+520, -9*i/20+390, 0,0,0);
      }
       	

      if(i>=200&&i<400){
       	//1 dezes kritimas
       	box1(pav, 215, 2*i-275, i/5, i/5, 0, 0, 0);
	}

	if(i>=400){
		//1 dezes stovejimas
       	box1(pav, 215, 525, 80, 80, 0, 0, 0);
	}

	if(i>=400&&i<600){
       	//2 dezes kritimas
       	box2(pav, 415, 2*i-675, i/5-40, i/5-40, 0, 0, 0);
	}
		
      if(i>=600){
		//2 dezes stovejimas
       	box2(pav, 415, 525, 80, 80, 0, 0, 0);
      }

      if(i>=600&&i<800){
		//3 dezes kritimas
       	box3(pav, 615, i*2-1075, i/5-80, i/5-80, 0, 0, 0);
	}

	if(i>=800){
		//3 dezes stovejimas
       	box3(pav, 615, 525, 80, 80, 0, 0, 0);
	}

	egle(pav, 815, 250, 400, 400, 0, 0, 0); //pastatome eglute i vieta

      //momentaliai dideja ir mazeja viena zvaigzdute.
	if (i>=770&&i<785) blight(pav, (-2*i/3)+(2980/3), (-2*i/3)+(1630/3), (4*i/3)-(3020/3), (4*i/3)-(3020/3), 255,255,255);
      if (i>=785) blight(pav, (7*i/6)-(2675/6), (7*i/6)-(5375/6), (-7*i/3)+(5615/3), (-7*i/3)+(5615/3), 255,255,255);

	girlianda(pav, 920, 475, 30, 25, 255, 0, 0);
	girlianda(pav, 1110, 495, 30, 25, 255, 0, 0); 
      girlianda(pav, 1030, 435, 30, 25, 255, 0, 0);
	girlianda(pav, 955, 390, 30, 25, 255, 0, 0);
	girlianda(pav, 1055, 355, 30, 25, 255, 0, 0);  //raudonos spalvos kamuoliukai ant eglutes
	girlianda(pav, 975, 320, 30, 25, 255, 0, 0);
	girlianda(pav, 965, 535, 30, 25, 255, 0, 0);
	girlianda(pav, 1080, 555, 30, 25, 255, 0, 0);
	girlianda(pav, 890, 570, 30, 25, 255, 0, 0);


	if(i%13==0){
		girlianda(pav, 920, 475, 30, 25, 51, 255, 255);
		girlianda(pav, 1110, 495, 30, 25, 51, 255, 255); 
		girlianda(pav, 1030, 435, 30, 25, 51, 255, 255); //eglutes mirksejimas
		girlianda(pav, 955, 390, 30, 25, 51, 255, 255);
		girlianda(pav, 1055, 355, 30, 25, 51, 255, 255);
		girlianda(pav, 975, 320, 30, 25, 51, 255, 255);
		girlianda(pav, 965, 535, 30, 25, 51, 255, 255);
		girlianda(pav, 1080, 555, 30, 25, 51, 255, 255);
		girlianda(pav, 890, 570, 30, 25, 51, 255, 255);
	}

	if(i%23==0){
		girlianda(pav, 920, 475, 30, 25, 255, 255, 51);
		girlianda(pav, 1110, 495, 30, 25, 255, 255, 51); 
		girlianda(pav, 1030, 435, 30, 25, 255, 255, 51);    //eglutes mikrsejimas
		girlianda(pav, 955, 390, 30, 25, 255, 255, 51);
		girlianda(pav, 1055, 355, 30, 25, 255, 255, 51);
		girlianda(pav, 975, 320, 30, 25, 255, 255, 51);
		girlianda(pav, 965, 535, 30, 25, 255, 255, 51);
		girlianda(pav, 1080, 555, 30, 25, 255, 255, 51);
		girlianda(pav, 890, 570, 30, 25, 255, 255, 51);
	}

      rasykPaveiksleli(pav);
      trinkPaveiksleli(pav);
   }
	
   for (int i=800; i<1000; i++){ 
       
      sprintf(pavadinimas, "kadras-%d.ppm", i);
      struct PPM6* pav = kurkPaveiksleli(pavadinimas, 1280, 720, 255);
      staciakampis(pav, 0, 0, 1279, 719, 0,35,46); //nuspalviname dali fono tamsiai melynai
      staciakampis(pav, 0, 450, 1279, 269, 255,255,255);    //nuspalviname dali fono baltai
      menulis(pav, 740, 50, 100, 120, 233,233,193); //pastatome menuli fone

      if(i%5==0){
       	blight(pav, 60, 280, 20, 20, 255,255,255);
       	blight(pav, 320, 150, 20, 20, 255,255,255);
       	blight(pav, 590, 260, 20, 20, 255, 255, 255); //zvaigzdiu blyksejimas
       	blight(pav, 750, 210, 20, 20, 255,255,255);
       	blight(pav, 920, 50, 20, 20, 255, 255, 255);
       			
      }
       	else {
       		blight(pav, 65, 285, 10, 10, 255,255,255);
       		blight(pav, 325, 155, 10, 10, 255,255,255);
       		blight(pav, 595, 265, 10, 10, 255, 255, 255);
       		blight(pav, 755, 215, 10, 10, 255,255,255);
       		blight(pav, 925, 55, 10, 10, 255, 255, 255);
       				
       	}

      if(i%5!=0){
       	blight(pav, 210, 70, 20, 20, 255,255,255);
       	blight(pav, 850, 350, 20, 20, 255,255,255);
       	blight(pav, 1130, 240, 20, 20, 255, 255, 255);
      }
       	else {
       		blight(pav, 215, 75, 10, 10, 255,255,255);
       		blight(pav, 855, 355, 10, 10, 255,255,255);
       		blight(pav, 1135, 245, 10, 10, 255, 255, 255);
       	}

	//pilki
      hata5(pav, 1, 340, 100, 120, 30,30,30);
      hata6(pav, 100, 340, 100, 120, 30,30,30);
      hata7(pav, 200, 360, 80, 100, 30,30,30);
      hata8(pav, 280, 380, 60, 80, 30,30,30);
      //tarpas
      hata1(pav, 830, 360, 80, 100, 30,30,30);
      hata3(pav, 900, 400, 50, 60, 30,30,30);
      hata2(pav, 949, 340, 100, 120, 30,30,30);
      hata4(pav, 1045, 370, 70, 90, 30,30,30);
      //tarpas
      hata2(pav, 510, 360, 100, 120, 30,30,30);
      hata4(pav, 610, 390, 70, 90, 30,30,30);
      hata7(pav, 679, 360, 100, 120, 30,30,30);


      //juodi
      hata1(pav, 1, 380, 80, 100, 0,0,0);
      hata3(pav, 70, 420, 50, 60, 0,0,0);
      hata2(pav, 119, 360, 100, 120, 0,0,0);
      hata4(pav, 215, 390, 70, 90, 0,0,0);
      //tarpas
      hata5(pav, 330, 360, 100, 120, 0,0,0);
      hata6(pav, 430, 360, 100, 120, 0,0,0);
      hata7(pav, 530, 380, 80, 100, 0,0,0); //pastatome namus fone
      hata8(pav, 610, 400, 60, 80, 0,0,0);
      hata1(pav, 660, 380, 80, 100, 0,0,0);
      //tarpas
      hata5(pav, 760, 400, 60, 80, 0,0,0);
      hata3(pav, 800, 420, 50, 60, 0,0,0);
      hata8(pav, 846, 360, 100, 120, 0,0,0);
      //tarpas
      hata2(pav, 1010, 360, 100, 120, 0,0,0);
      hata4(pav, 1110, 390, 70, 90, 0,0,0);
      hata7(pav, 1179, 360, 100, 120, 0,0,0);

      box1(pav, 215, 525, 80, 80, 0, 0, 0);
      box2(pav, 415, 525, 80, 80, 0, 0, 0); //stacionariu deziu kordinates
      box3(pav, 615, 525, 80, 80, 0, 0, 0);

      egle(pav, 815, 250, 400, 400, 0, 0, 0); //stacionarios eglutes koordinates

      star(pav, 2.485*i-1508, 0.875*i-670, 0.275*i-200, 0.25*i-180, 241, 210, 55); //krentanti ir didejanti geltona zvaigzde

	girlianda(pav, 920, 475, 30, 25, 255, 0, 0);
	girlianda(pav, 1110, 495, 30, 25, 255, 0, 0); 
	girlianda(pav, 1030, 435, 30, 25, 255, 0, 0);
	girlianda(pav, 955, 390, 30, 25, 255, 0, 0);
	girlianda(pav, 1055, 355, 30, 25, 255, 0, 0); //raudoni kamuoliukai and eglute
	girlianda(pav, 975, 320, 30, 25, 255, 0, 0);
	girlianda(pav, 965, 535, 30, 25, 255, 0, 0);
	girlianda(pav, 1080, 555, 30, 25, 255, 0, 0);
	girlianda(pav, 890, 570, 30, 25, 255, 0, 0);


	if(i%11==0){
		girlianda(pav, 920, 475, 30, 25, 51, 255, 255);
		girlianda(pav, 1110, 495, 30, 25, 51, 255, 255); 
		girlianda(pav, 1030, 435, 30, 25, 51, 255, 255);
		girlianda(pav, 955, 390, 30, 25, 51, 255, 255);
		girlianda(pav, 1055, 355, 30, 25, 51, 255, 255);
		girlianda(pav, 975, 320, 30, 25, 51, 255, 255); //eglutes kamuoliu mirksejimas
		girlianda(pav, 965, 535, 30, 25, 51, 255, 255);
		girlianda(pav, 1080, 555, 30, 25, 51, 255, 255);
		girlianda(pav, 890, 570, 30, 25, 51, 255, 255);
	}

	if(i%17==0){
		girlianda(pav, 920, 475, 30, 25, 255, 255, 51);
		girlianda(pav, 1110, 495, 30, 25, 255, 255, 51); 
		girlianda(pav, 1030, 435, 30, 25, 255, 255, 51);
		girlianda(pav, 955, 390, 30, 25, 255, 255, 51);
		girlianda(pav, 1055, 355, 30, 25, 255, 255, 51);
		girlianda(pav, 975, 320, 30, 25, 255, 255, 51);
		girlianda(pav, 965, 535, 30, 25, 255, 255, 51);
		girlianda(pav, 1080, 555, 30, 25, 255, 255, 51);
		girlianda(pav, 890, 570, 30, 25, 255, 255, 51);
	}

      rasykPaveiksleli(pav);
      trinkPaveiksleli(pav);

   }

   for (int i=1000; i<1800; i++){ 
       
      sprintf(pavadinimas, "kadras-%d.ppm", i);
      struct PPM6* pav = kurkPaveiksleli(pavadinimas, 1280, 720, 255);
      staciakampis(pav, 0, 0, 1279, 719, 0,35,46);    //nuspalviname dali fono tamsiai melynai
      staciakampis(pav, 0, 450, 1279, 269, 255,255,255); //nuspalviname dali fono baltai 
      menulis(pav, 740, 50, 100, 120, 233,233,193); //pastatome menuli fone

      if(i%5==0){
       	blight(pav, 60, 280, 20, 20, 255,255,255);
       	blight(pav, 320, 150, 20, 20, 255,255,255);
       	blight(pav, 590, 260, 20, 20, 255, 255, 255);
       	blight(pav, 750, 210, 20, 20, 255,255,255);    //zvaigzdiu mirksejimas
       	blight(pav, 920, 50, 20, 20, 255, 255, 255);
       			
       }
       	else {
       		blight(pav, 65, 285, 10, 10, 255,255,255);
       		blight(pav, 325, 155, 10, 10, 255,255,255);
       		blight(pav, 595, 265, 10, 10, 255, 255, 255);
                  blight(pav, 755, 215, 10, 10, 255,255,255);
       		blight(pav, 925, 55, 10, 10, 255, 255, 255);
       				
       	}

      if(i%5!=0){
       	blight(pav, 210, 70, 20, 20, 255,255,255);
       	blight(pav, 850, 350, 20, 20, 255,255,255);
       	blight(pav, 1130, 240, 20, 20, 255, 255, 255);
      }
       	else {
       		blight(pav, 215, 75, 10, 10, 255,255,255);
       		blight(pav, 855, 355, 10, 10, 255,255,255);
       		blight(pav, 1135, 245, 10, 10, 255, 255, 255);
       	}

	//pilki
      hata5(pav, 1, 340, 100, 120, 30,30,30);
      hata6(pav, 100, 340, 100, 120, 30,30,30);
      hata7(pav, 200, 360, 80, 100, 30,30,30);
      hata8(pav, 280, 380, 60, 80, 30,30,30);
      //tarpas
      hata1(pav, 830, 360, 80, 100, 30,30,30);
      hata3(pav, 900, 400, 50, 60, 30,30,30);
      hata2(pav, 949, 340, 100, 120, 30,30,30);
      hata4(pav, 1045, 370, 70, 90, 30,30,30);
      //tarpas
      hata2(pav, 510, 360, 100, 120, 30,30,30);
      hata4(pav, 610, 390, 70, 90, 30,30,30);
      hata7(pav, 679, 360, 100, 120, 30,30,30);

      //juodi
      hata1(pav, 1, 380, 80, 100, 0,0,0);
      hata3(pav, 70, 420, 50, 60, 0,0,0);
      hata2(pav, 119, 360, 100, 120, 0,0,0);
      hata4(pav, 215, 390, 70, 90, 0,0,0);
      //tarpas
      hata5(pav, 330, 360, 100, 120, 0,0,0);
      hata6(pav, 430, 360, 100, 120, 0,0,0);
      hata7(pav, 530, 380, 80, 100, 0,0,0);
      hata8(pav, 610, 400, 60, 80, 0,0,0);        //pastatome namukus fone
      hata1(pav, 660, 380, 80, 100, 0,0,0);
      //tarpas
      hata5(pav, 760, 400, 60, 80, 0,0,0);
      hata3(pav, 800, 420, 50, 60, 0,0,0);
      hata8(pav, 846, 360, 100, 120, 0,0,0);
      //tarpas
      hata2(pav, 1010, 360, 100, 120, 0,0,0);
      hata4(pav, 1110, 390, 70, 90, 0,0,0);
      hata7(pav, 1179, 360, 100, 120, 0,0,0);


      if(i>=1050&&i<=1130) raideM(pav, 225, -1.125*i+1786.25, 60, 80, 255, 0, 0); //kyla staciai i virsu
      if(i>=1130&&i<=1220) raideM(pav, -29*i/18+(18410/9), -3*i/2+2210, 60, 80, 255, 0, 0); //juda i vieta istrizai  

      if(i>=1220&&i<=1300) raideR(pav, 220, -0.5*i+1135, 60, 80, 255, 0, 0);
      if(i>=1300&&i<=1390) raideR(pav, 2*i/9-620/9, -37*i/18+28415/9, 60, 80, 255, 0, 0);

      if(i>=1390&&i<=1470) raideE(pav, 230, -1.125*i+2088.75, 50, 80, 255, 0, 0);
      if(i>=1470&&i<=1560) raideE(pav, -7*i/9+(4120/3), -3*i/2+2640, 50, 80, 255, 0, 0);
      


      if(i>=1050&&i<=1130) raideY(pav, 430, -i+1575, 50, 80, 255, 0, 0);
      if(i>=1130&&i<=1220) raideY(pav, -i/3+2420/3, -29*i/18+20390/9, 50, 80, 255, 0, 0);                        //is dezes islendancios raides

      if(i>=1220&&i<=1300) raideR(pav, 420, -i+1745, 60, 80, 255, 0, 0);
      if(i>=1300&&i<=1390) raideR(pav, -10*i/9+(16780/9), -29*i/18+(22855/9), 60, 80, 255, 0, 0);

      if(i>=1390&&i<=1470) raideX(pav, 430, -i+1915, 50, 80, 255, 0, 0);
      if(i>=1470&&i<=1560) raideX(pav, i-1040, -29*i/18+8440/3, 50, 80, 255, 0, 0);



      if(i>=1050&&i<=1130) raideS(pav, 635, -i+1575, 100, 80, 255, 0, 0);
      if(i>=1130&&i<=1220) raideS(pav, 25*i/18-8410/9, -29*i/18+20390/9, 100, 80, 255, 0, 0);

      if(i>=1220&&i<=1300) raideM(pav, 620, -0.5*i+1215, 60, 80, 255, 0, 0);
      if(i>=1300&&i<=1390) raideM(pav, -2*i/9+8180/9, -37*i/18+29135/9, 60, 80, 255, 0, 0);

      if(i>=1390&&i<=1470) raideA(pav, 625, -i+1995, 70, 80, 255, 0, 0);
      if(i>=1470&&i<=1560) raideA(pav, 11*i/18-820/3, -29*i/18+8680/3, 70, 80, 255, 0, 0);



      box1(pav, 215, 525, 80, 80, 0, 0, 0);     //stacionariu deziu koordinates
      box2(pav, 415, 525, 80, 80, 0, 0, 0);
      box3(pav, 615, 525, 80, 80, 0, 0, 0);

      egle(pav, 815, 250, 400, 400, 0, 0, 0);   //pastatome eglute fone

      girlianda(pav, 920, 475, 30, 25, 255, 0, 0);         //raudoni kamuoliukai ant eglute
	girlianda(pav, 1110, 495, 30, 25, 255, 0, 0); 
	girlianda(pav, 1030, 435, 30, 25, 255, 0, 0);
	girlianda(pav, 955, 390, 30, 25, 255, 0, 0);
	girlianda(pav, 1055, 355, 30, 25, 255, 0, 0);
	girlianda(pav, 975, 320, 30, 25, 255, 0, 0);
	girlianda(pav, 965, 535, 30, 25, 255, 0, 0);
	girlianda(pav, 1080, 555, 30, 25, 255, 0, 0);
	girlianda(pav, 890, 570, 30, 25, 255, 0, 0);


	if(i%13==0){
		girlianda(pav, 920, 475, 30, 25, 51, 255, 255);
		girlianda(pav, 1110, 495, 30, 25, 51, 255, 255); 
		girlianda(pav, 1030, 435, 30, 25, 51, 255, 255);
		girlianda(pav, 955, 390, 30, 25, 51, 255, 255);
		girlianda(pav, 1055, 355, 30, 25, 51, 255, 255); //kamuoliuku mirksejimas
		girlianda(pav, 975, 320, 30, 25, 51, 255, 255);
		girlianda(pav, 965, 535, 30, 25, 51, 255, 255);
		girlianda(pav, 1080, 555, 30, 25, 51, 255, 255);
		girlianda(pav, 890, 570, 30, 25, 51, 255, 255);
	}

	if(i%17==0){
		girlianda(pav, 920, 475, 30, 25, 255, 255, 51);
		girlianda(pav, 1110, 495, 30, 25, 255, 255, 51); 
		girlianda(pav, 1030, 435, 30, 25, 255, 255, 51);
		girlianda(pav, 955, 390, 30, 25, 255, 255, 51);
		girlianda(pav, 1055, 355, 30, 25, 255, 255, 51); //kamuoliuku mirksejimas
		girlianda(pav, 975, 320, 30, 25, 255, 255, 51);
		girlianda(pav, 965, 535, 30, 25, 255, 255, 51);
		girlianda(pav, 1080, 555, 30, 25, 255, 255, 51);
		girlianda(pav, 890, 570, 30, 25, 255, 255, 51);
	}

      star(pav, 977, 205, 75, 70, 241, 210, 55); //stacionarios zvaigzdes koordinates

      if(i>=1220) raideM(pav, 80, 380, 60, 80, 255, 0, 0); //stacionarios raides koordinates

      if(i>=1390) raideR(pav, 240, 300, 60, 80, 255, 0, 0);
   
      if(i>=1560) raideE(pav, 160, 300, 50, 80, 255, 0, 0);
      
      
      if(i>=1220) raideY(pav, 400, 300, 50, 80, 255, 0, 0);

      if(i>=1390) raideR(pav, 320, 300, 60, 80, 255, 0, 0);

      if(i>=1560) raideX(pav, 520, 300, 50, 80, 255, 0, 0);


      
      if(i>=1220) raideS(pav, 760, 300, 100, 80, 255, 0, 0);

      if(i>=1390) raideM(pav, 600, 380, 60, 80, 255, 0, 0);

      if(i>=1560) raideA(pav, 680, 380, 70, 80, 255, 0, 0);

      rasykPaveiksleli(pav);
      trinkPaveiksleli(pav);

   }


   system("ffmpeg -framerate 30 -i kadras-%d.ppm  filmas.mp4");
   system("rm *.ppm");
   
   
   return 0;
}
