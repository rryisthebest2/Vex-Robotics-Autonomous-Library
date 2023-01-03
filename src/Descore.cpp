#include "main.h"
int Currenttime2;
bool EnableDescore = true;
void Descore(int timeallowed){
  Currenttime2=pros::millis();

  int Stoper1=opticalStoper1.get_hue();
  while((pros::millis()-Currenttime2) <= timeallowed && EnableDescore == true){// && Stoper1<45
    Stoper1=opticalStoper1.get_hue();
    Collect(Arm,Shoot1,Shoot2);
    if(Stoper1 > 150 && Stoper1 < 270){
      EnableDescore = false;
    }
    delay(10);
  }
Collect(0,0,127);
delay(200);//300
Collect(0,0,0);
EnableDescore = true;
}



void DescoreThree(int timeallowed){

  Currenttime2=pros::millis();
  Collect(0,0,127);
  delay(480);
  int Stoper1=optical3.get_hue();
  while((pros::millis()-Currenttime2) <= timeallowed && EnableDescore == true){// && Stoper1<45
    Stoper1=optical3.get_hue();
    if(Stoper1 > 150 && Stoper1 < 270){
      EnableDescore = false;
    }else{
    Collect(Arm,Shoot1,Shoot2);
    }
    delay(10);
  }
Collect(127,0,0);
delay(550);//300
Collect(0,0,0);
EnableDescore = true;
}





void DescoreThreeS(int timeallowed){

  Currenttime2=pros::millis();
  Collect(0,0,127);
  delay(480);
  int Stoper1=optical3.get_hue();
  while((pros::millis()-Currenttime2) <= timeallowed && EnableDescore == true){// && Stoper1<45
    Stoper1=optical3.get_hue();
    if(Stoper1 > 150 && Stoper1 < 270){
      EnableDescore = false;
    }else{
    Collect(Arm,Shoot1,Shoot2);
    }
    delay(10);
  }
Collect(127,0,0);
delay(750);//300
Collect(0,0,0);
EnableDescore = true;
}



void Descore3(int timeallowed){
  Collect(0,0,127);
  delay(500);
  Collect(0,127,127);
  delay(500);
  Collect(127,0,0);
  delay(100);
  Collect(0,0,0);
  delay(100);


  /*Currenttime2=pros::millis();

  int Stoper1=VisionDetect.get();
  while((pros::millis()-Currenttime2) <= timeallowed && Stoper1 > 100){// && Stoper1<45
    Stoper1=VisionDetect.get();
    Collect(127,0,127);
    delay(10);
  }
Collect(0,127,127);
delay(800);//300
Collect(0,0,0);
delay(200)*/;
}


void DescoreMid(int timeallowed){
Collect(127,0,127);
delay(500);
Collect(127,127,0);
delay(800);
Collect(0,0,0);
  /*Currenttime2=pros::millis();
  //Collect(127,0,127);
  //delay(350);
  int Stoper1=BallControldown.get();
  int Stoper2=BallControlUp.get();
  while((pros::millis()-Currenttime2) <= timeallowed && EnableDescore == true){// && Stoper1<45
    Stoper1=BallControldown.get();
    Stoper2=BallControlUp.get();
    if(Stoper2 < 70){
      Collect(Arm,Shoot1,Shoot2);
    }
    else if (Stoper2 > 70){
      EnableDescore = false;
    }
    delay(10);
  }
  Collect(127,127,0);
  delay(900);//300
  Collect(0,0,0);*/
}



void Descore5(int timeallowed){

  Currenttime2=pros::millis();

  int Stoper1=VisionDetect.get();
  while((pros::millis()-Currenttime2) <= timeallowed && Stoper1 > 100){// && Stoper1<45
    Stoper1=VisionDetect.get();
    Collect(127,0,127);
    delay(10);
  }
Collect(0,0,127);
delay(200);//300
Collect(0,0,0);
}



void Descore8(int timeallowed){
Collect(127,0,0);
delay(300);
Collect(0,0,127);
delay(800);
}





void ThreeBall(int timeallowed1){
  Currenttime2=pros::millis();
  int StoperFirstTower=opticalStoper2.get_hue();
  while((pros::millis()-Currenttime2) <= timeallowed1){
    StoperFirstTower=opticalStoper2.get_hue();
    if(StoperFirstTower<60){
      Collect(350,600,600);
      StoperFirstTower=opticalStoper2.get_hue();
    }else{
      Collect(350,0,600);
      StoperFirstTower=opticalStoper2.get_hue();
    }
    delay(10);
  }
  Collect(0,0,0);
}
