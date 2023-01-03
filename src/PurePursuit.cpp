#include "main.h"
#include <math.h>
#include <iostream>
#include <cmath>

bool CheckY1=true;
bool CheckY2=true;
bool CheckX1=true;
bool CheckX2=true;
double average1;
double average2;
double averageY1;
double averageY2;
double averageT1;
double averageT2;
double lfmV;
double rfmV;
double rbmV;
double lbmV;
double Minp = 25;
//int MinpT=10;
//int MinpS=10;
// rpm/count
double turnerrorp1;
double turnerrorp2;
double VelCapp=0;
int Accelerationp=5;
double erroraverageYp;
double erroraverageXp;
double erroraverageX1p;
double erroraverageY1p;
double preverroraverageXp;
double preverroraverageYp;
double preverroraverageX1p;
double preverroraverageY1p;
double derAVXp;
double derAVYp;
double derAVX1p;
double derAVY1p;
double Powerp;
double Strafep;
double Power1p;
double Strafe1p;
double turnp;
double turnerrorp;
int currenttimeP;
bool EnableMotionp =true;
int counterp=0;
bool EnableFilter1 = true;
bool EnableFilter2 = true;
double XF;
double YF;
bool EnableTurnCalc = true;
double DistancePure;
double AverageDistanceX;
double AverageDistanceY;
void PureSuit(double X1, double Y1, double X2, double Y2, double X3, double Y3, double Angle1, double Angle2, double FinalAngle, double time, double maxvel, std::string Intake){

average1 = (X2 - X1)/50;
/*if(average1 >0){
  average1 = 0.5;
}else{
  average1 = -0.5;
}*/
average2 = (X3-X2)/50;
/*if(average2 >0){
  average2 = 0.5;
}else{
  average2 = -0.5;
}*/
averageY1 = (Y2-Y1)/50;
/*if(averageY1 >0){
  averageY1= 0.5;
}else{
  averageY1 = -0.5;
}*/
averageY2= (Y3-Y2)/50;
/*if(averageY2 >0){
  averageY2 = 0.5;
}else{
  averageY2 = -0.5;
}*/
/*turnerrorp1 = Angle2 - Angle1;
turnerrorp2 = FinalAngle - Angle2;
pros::lcd::print(1, "A: %f", CurrentAngle);
if (fabs(turnerrorp1) > M_PI){
    if (turnerrorp1 > 0){
      turnerrorp1 = turnerrorp1 - (2*M_PI);
    }
    else {
      turnerrorp1 = ((2*M_PI) + turnerrorp1);
    }
  }

  if (fabs(turnerrorp2) > M_PI){
      if (turnerrorp2 > 0){
        turnerrorp2 = turnerrorp2 - (2*M_PI);
      }
      else {
        turnerrorp2 = ((2*M_PI) + turnerrorp2);
      }
    }
averageT1 =(turnerrorp1)/20;
averageT2 =(turnerrorp2)/20;
*/


currenttimeP = pros::millis();

/*if(fabs(X - CurrentGlobal_X) < 0.5 && fabs(Y- CurrentGlobal_Y) <0.5){
  EnableTurnFilter = true;
}*/

lfm.tare_position();
rfm.tare_position();
lbm.tare_position();
rbm.tare_position();

XF = X1;
YF = Y1;
turnp = Angle1;

while((pros::millis()-currenttimeP) <= time && EnableMotionp){

  DistancePure = sqrt(pow((XF - CurrentGlobal_X),2.0)+ pow((YF - CurrentGlobal_Y),2.0));

  /*if(EnableTurnCalc == true){
    turnp = ((2 * (XF - CurrentGlobal_X)) / (pow((XF - CurrentGlobal_X),2.0)+ pow((YF - CurrentGlobal_Y),2.0)));
  }*/

  turnerrorp = turnp - CurrentAngle;
  pros::lcd::print(1, "A: %f", CurrentAngle);
  if (fabs(turnerrorp) > M_PI){
      if (turnerrorp > 0){
        turnerrorp = turnerrorp - (2*M_PI);
      }
      else {
        turnerrorp = ((2*M_PI) + turnerrorp);
      }
    }

  /*  derT = turnerrorp - prevturnerror;
    prevturnerror = turnerrorp;
    velocityT = (turnerrorp*kap)+(derT * kad);*/



  /////////X Coordinate PID.
  erroraverageXp = (1*(XF-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(1*(YF-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)) +(8.5431 * turnerrorp);
  //erroraverageXp = (0.5*(XF-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(0.5*(YF-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)); // for motor lfm.
  derAVXp = erroraverageXp - preverroraverageXp;
  preverroraverageXp = erroraverageXp;
  Strafep = (erroraverageXp * kpO) + (derAVXp * kdO); // for motor lfm and rbm
  /*if(XF == X3 && YF == Y3){
    Strafep = Strafep;
  }else if(Strafep >0){
    Strafep = 127;
  }else if(Strafep<0){
    Strafep =-127;
  }*/

  ////////////////////////////////////////////
  //Y Coordinate PID.
  ////////////////////////////////////////////
  erroraverageYp = (1*(XF-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(1*(YF-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle)) + (8.5431 * turnerrorp);
  //erroraverageYp = (0.5*(XF-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(0.5*(YF-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle));// for motor rfm.
  derAVYp = erroraverageYp - preverroraverageYp;
  preverroraverageYp = erroraverageYp;
  Powerp = (erroraverageYp * kpO) + (derAVYp * kdO);
  /*if(XF == X3 && YF == Y3){
    Powerp = Powerp;
  }else if(Powerp >0){
    Powerp = 127;
  }else if(Powerp<0){
    Powerp =-127;
  } // for motor lbm and rfm.*/
/////////Angle PID.


  erroraverageX1p = (1*(XF-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(1*(YF-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)) - (8.5431 * turnerrorp);
  //erroraverageX1p = (0.5*(XF-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(0.5*(YF-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)); // for motor rbm.
  derAVX1p = erroraverageX1p - preverroraverageX1p;
  preverroraverageX1p = erroraverageX1p;
  Strafe1p = (erroraverageX1p * kpO) + (derAVX1p * kdO);
  /*if(XF == X3 && YF == Y3){
    Strafe1p = Strafe1p;
  }else if(Strafe1p >0){
    Strafe1p = 127;
  }else if(Strafe1p<0){
    Strafe1p =-127;
  }*/
   // for motor lfm and rbm


  ////////////////////////////////////////////
  //Y Coordinate PID.
  ////////////////////////////////////////////
  erroraverageY1p = (1*(XF-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(1*(YF-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle)) - (8.5431 * turnerrorp);
  //erroraverageY1p = (0.5*(XF-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(0.5*(YF-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle)); // for motor lbm.
  derAVY1p = erroraverageY1p - preverroraverageY1p;
  preverroraverageY1p = erroraverageY1p;
  Power1p = (erroraverageY1p * kpO) + (derAVY1p * kdO); // for motor lbm and rfm.
  /*if(XF == X3 && YF == Y3){
    Power1p = Power1p;
  }else if(Power1p >0){
    Power1p = 127;
  }else if(Power1p<0){
    Power1p =-127;
  }*/

    if(Intake=="true"){
      rightintake.move(IntakeP);
      leftintake.move(IntakeP);
      elevator1.move_velocity(Roller1);
      elevator2.move_velocity(Roller2);
    }
    if(Intake=="false"){
      Collect(0,0,0);
    }
    if(Intake=="outtakeC"){
      if(fabs(XF-CurrentGlobal_X) < 20 || fabs(YF - CurrentGlobal_Y) < 20){
      Collect(-127,-600,-600);
    }else{
      Collect(-30,0,0);}
    }
    if(Intake=="Descore"){
      Collect(-127,0,0);
    }
    if(Intake=="outtake"){

      Collect(-127,-600,-600);
    }
    if(Intake=="First"){
      Collect(450,150,0);
    }
    if(Intake=="outtake5"){
      if(fabs(XF-CurrentGlobal_X) < 6 || fabs(YF - CurrentGlobal_Y) < 6){
      Collect(-127,-600,-600);
    }else{
      Collect(-30,0,0);}
    }
    if(Intake=="outtake2"){
      if(fabs(XF-CurrentGlobal_X) < 12){
      Collect(-127,-600,-600);
    }else{
      Collect(-30,0,0);}
    }
  ///////// Velocity Cut.
  VelCapp = VelCapp + Accelerationp;
  if(VelCapp > maxvel){
    VelCapp = maxvel;
  }
  if (fabs(Powerp) > VelCapp){
    if (Powerp> 0){
      Powerp = VelCapp;
    }
    else {
      Powerp = - VelCapp;
    }
  }

  if (fabs(Power1p) > VelCapp){
    if (Power1p> 0){
      Power1p = VelCapp;
    }
    else {
      Power1p = - VelCapp;
    }
  }

  if (fabs(Strafep) > VelCapp){
    if (Strafep > 0){
      Strafep = VelCapp;
    }
    else {
      Strafep = - VelCapp;
    }
  }

  if (fabs(Strafe1p) > VelCapp){
    if (Strafe1p > 0){
      Strafe1p = VelCapp;
    }
    else {
      Strafe1p = - VelCapp;
    }
  }


  if(fabs(Powerp)<Minp){
    if(Powerp>0){
      Powerp= Minp;
    }
    else{
      Powerp= -Minp;
    }
  }

  if(fabs(Power1p)<Minp){
    if(Power1p>0){
      Power1p= Minp;
    }
    else{
      Power1p= -Minp;
    }
  }

  if(fabs(Strafep)<Minp){
    if(Strafep>0){
      Strafep= Minp;
    }
    else{
      Strafep= -Minp;
    }
  }

  if(fabs(Strafe1p)<Minp){
    if(Strafe1p>0){
      Strafe1p= Minp;
    }
    else{
      Strafe1p= -Minp;
    }
  }

  if(fabs(velocityT)<Minp){
    if(velocityT>0){
      velocityT= Minp;
    }
    else{
      velocityT= -Minp;
    }
  }

  if(fabs(X1 - CurrentGlobal_X) < 3 && fabs(X2 - CurrentGlobal_X) >= 3){
    XF = XF + average1;

  }else if(fabs(X2 - CurrentGlobal_X) >=3){
    XF = XF + average1;
  }else if(fabs(X2 - CurrentGlobal_X) < 3 && fabs(X3 - CurrentGlobal_X) > 11){
    XF = XF + average2;
  }

  if(fabs(XF - X3) <= 11){
    XF = X3;
  }

  if(fabs(Y1 - CurrentGlobal_Y) < 3 && fabs(Y2 - CurrentGlobal_Y) >= 3){
    YF = YF + averageY1;

  }else if(fabs(Y2 - CurrentGlobal_Y) >=3){
    YF = YF + averageY1;

  }else if(fabs(Y2 - CurrentGlobal_Y) < 3 && fabs(Y3 - CurrentGlobal_Y) > 11){
    YF = YF + averageY2;
  }

  if(fabs(YF - Y3) <= 11){
    YF = Y3;
  }

  if(fabs(turnerrorp) < 0.3 && fabs( X1 - CurrentGlobal_X) < 6 && fabs(Y1- CurrentGlobal_Y) < 6 && EnableFilter1 == true){
    turnp = Angle2;
    EnableFilter1 =false;
  }

  if(fabs(turnerrorp) < 0.3 && fabs( X2 - CurrentGlobal_X) < 6 && fabs(Y2- CurrentGlobal_Y) < 6 && EnableFilter2 == true){
    turnp = FinalAngle;
    EnableFilter2=false;
  }


  /*if(fabs(Angle1 - CurrentAngle) < 0.175 && fabs(Angle1 - CurrentAngle) > averageT1){
    turnp = turnp + averageT1;

  } else if(fabs(FinalAngle - CurrentAngle) < 0.175 && fabs(FinalAngle - CurrentAngle) > averageT2){
    turnp = turnp + averageT2;
  }

*/
  if (fabs(X3-CurrentGlobal_X) < 0.5 && fabs(Y3-CurrentGlobal_Y) < 0.5 && fabs(turnerrorp) < 0.017){
    counterp=counterp+1;
    /*pros::vision_object_s_t CheckBallP = Camera.get_by_sig(0, 1);
    if(CheckBallP.signature != 255){
      EnableMotionp = false;
      pros::lcd::print(7, "Vision Now");
    }*/
}

if(counterp>=5){
  drive(0,0);
  EnableMotionp=false;
}

  //Move function

/*lfmV = Strafep + velocityT;
rfmV = Powerp + velocityT;
rbmV = Strafe1p - velocityT;
lbmV = Power1p - velocityT; */

  lfm.move(Strafep);
  rfm.move(Powerp);
  lbm.move(Power1p);
  rbm.move(Strafe1p);

/*  lfm.move(lfmV);
  rfm.move(rfmV);
  lbm.move(lbmV);
  rbm.move(rbmV); */

  delay(10);
  }
drive(0,0);
VelCapp=0;
counterp=0;
EnableMotionp = true;
EnableFilter1 = true;
EnableFilter2 = true;
EnableTurnCalc = true;
// Call function here.
//Vision("true");
}
