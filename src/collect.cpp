#include "main.h"
#include <math.h>
#include <iostream>
#include <cmath>
void Collect(int velocity1, int ElevatorVel,int Elevatorvel2) {
  rightintake.move(velocity1);
  leftintake.move(velocity1);
  elevator1.move(ElevatorVel);
  elevator2.move(Elevatorvel2);

}

void Reset (double XReset , double YReset,double Angle){

  EnablePositionTrack = false;
  delay(100);
  pros::Task Position_Trakcing1st(Odometry1st);
  delay(20);
}

void Reset2(){

  EnablePositionTrack1st = false;
  delay(100);
  pros::Task Position_Trakcing2nd(Odometry2nd);
  delay(20);
}


void Reset3(){

  EnablePositionTrack2nd = false;
  delay(100);
  pros::Task Position_Trakcing3rd(Odometry3rd);
  delay(20);
}

int Time;
bool EnableTowerMatch = true;
double XMatch;
double derXMatch;
double PreXMatch;
double XPower;
double YPower;
double YMatch;
double derYMatch;
double PreYMatch;
int MinX = 18;
int MinY =18;
int counterTower = 0;
double LeftFrontMotor;
double RightFrontMotor;
double LeftBackMotor;
double RightBackMotor;

void TowerMatch(int RightValue, int LeftValue,double timeAllow,std::string Sort){

  Time = pros::millis();

  while((pros::millis()-Time) <= timeAllow && EnableTowerMatch){

    int CurrentL = TowerMatchLeft.get();
    int CurrentR = TowerMatchRight.get();


      XMatch = (CurrentR - RightValue)/25.4 ;// 50.8;
      derXMatch = XMatch - PreXMatch;
      PreXMatch = XMatch;
      XPower = (XMatch * kpO) + (derXMatch * kdO); // for lfm and rbm

      YMatch = (LeftValue - CurrentL)/ 25.4 ;// 50.8;
      derYMatch = YMatch - PreYMatch;
      PreYMatch = YMatch;
      YPower = (YMatch * kpO) + (derYMatch * kdO);  // for lbm and rfm



    /*if(TowerName == 3){
      XMatch = (((LeftValue-CurrentL)* cos(M_PI/4 + CurrentAngle)) * cos(CurrentAngle))-(((RightValue-CurrentR) * cos(M_PI/4 + CurrentAngle)) * sin(CurrentAngle));
      derXMatch = XMatch - PreXMatch;
      PreXMatch = XMatch;
      XPower = (XMatch * kp) + (derXMatch * kd);
    }

    else if(TowerName == 5){
      XMatch = (((RightValue-CurrentR)* cos(M_PI/4 - CurrentAngle)) * cos(CurrentAngle))-(((LeftValue-CurrentL) * cos(M_PI/4 - CurrentAngle)) * sin(CurrentAngle));
      derXMatch = XMatch - PreXMatch;
      PreXMatch = XMatch;
      XPower = (XMatch * kp) + (derXMatch * kd);
    }

    else if(TowerName == 7){
      XMatch = (((LeftValue-CurrentL)* cos(CurrentAngle-((135*M_PI)/180))) * cos(CurrentAngle))-(((RightValue-CurrentR) * cos(CurrentAngle-((135*M_PI)/180))) * sin(CurrentAngle));
      derXMatch = XMatch - PreXMatch;
      PreXMatch = XMatch;
      XPower = (XMatch * kp) + (derXMatch * kd);
    }

    else if(TowerName ==1){
      XMatch = (((RightValue-CurrentR)* cos(((225*M_PI)/180) - CurrentAngle)) * cos(CurrentAngle))-(((LeftValue-CurrentL) * cos(((225*M_PI)/180) - CurrentAngle)) * sin(CurrentAngle));
      derXMatch = XMatch - PreXMatch;
      PreXMatch = XMatch;
      XPower = (XMatch * kp) + (derXMatch * kd);
    }

/////// Y Value Loop;

    if(TowerName == 3){
      YMatch = (((LeftValue-CurrentL)* cos(M_PI/4 + CurrentAngle)) * sin(CurrentAngle))+(((RightValue-CurrentR) * cos(M_PI/4 + CurrentAngle)) * cos(CurrentAngle));
      derYMatch = YMatch - PreYMatch;
      PreYMatch = YMatch;
      YPower = (YMatch * kp) + (derYMatch * kd);
    }

    else if(TowerName == 5){
      XMatch = (((RightValue-CurrentR)* cos(M_PI/4 - CurrentAngle)) * sin(CurrentAngle))+(((LeftValue-CurrentL) * cos(M_PI/4 - CurrentAngle)) * cos(CurrentAngle));
      derYMatch = YMatch - PreYMatch;
      PreYMatch = YMatch;
      YPower = (YMatch * kp) + (derYMatch * kd);
    }

    else if(TowerName == 7){
      XMatch = (((LeftValue-CurrentL)* cos(CurrentAngle-((135*M_PI)/180))) * sin(CurrentAngle))+(((RightValue-CurrentR) * cos(CurrentAngle-((135*M_PI)/180))) * cos(CurrentAngle));
      derYMatch = YMatch - PreYMatch;
      PreYMatch = YMatch;
      YPower = (YMatch * kp) + (derYMatch * kd);
    }

    else if(TowerName ==1){
      XMatch = (((RightValue-CurrentR)* cos(((225*M_PI)/180) - CurrentAngle)) * sin(CurrentAngle))+(((LeftValue-CurrentL) * cos(((225*M_PI)/180) - CurrentAngle)) * cos(CurrentAngle));
      derYMatch = YMatch - PreYMatch;
      PreYMatch = YMatch;
      YPower = (YMatch * kp) + (derYMatch * kd);
    } */

    if(fabs(YPower)<MinY){
      if(YPower>0){
        YPower= MinY;
      }
      else{
        YPower= -MinY;
      }
    }

    if(fabs(XPower)<MinX){
      if(XPower>0){
        XPower= MinX;
      }
      else{
        XPower= -MinX;
      }
    }

    if(Sort=="true"){
      rightintake.move(IntakeP);
      leftintake.move(IntakeP);
      elevator1.move(Roller1);
      elevator2.move(Roller2);
    }
    if(Sort=="false"){
      Collect(0,0,0);
    }

    //pros::lcd::print(2, "Right: %f", XMatch);
    //pros::lcd::print(5, "Left: %f", YMatch);

    if (fabs(XMatch) < 0.8 && fabs(YMatch) < 0.8){

    counterTower=counterTower+1;
  }

  if(counterTower>=3){
    EnableTowerMatch=false;
  }

  /*LeftFrontMotor= YPower + XPower;
  RightFrontMotor = - YPower + XPower;
  LeftBackMotor = - YPower + XPower;
  RightBackMotor= YPower + XPower; */


  lfm.move(XPower);
  rfm.move(YPower);
  lbm.move(YPower);
  rbm.move(XPower);
  delay(10);
}
drive(0,0);
counterTower=0;
EnableTowerMatch = true;
}
