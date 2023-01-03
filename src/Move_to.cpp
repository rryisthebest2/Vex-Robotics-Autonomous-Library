#include "main.h"
#include <math.h>
#include <iostream>
#include <cmath>

using namespace std;
string Intake;
double kpO = 10.5; //18 !!!!!!!!!!!!
double ki = 0.00;
double kdO = 2;//25 !!!!!!!!!!!!!!
double kap = 180; //180
double kad =25; //25
double ksp = 11; //10.5
double ksd = 70; //60
int Min=18;//18
//int MinT=10;
//int MinS=10;
// rpm/count
int IntakeCount=0;
int VelCap=0;
double Acceleration=3.175;
double AdjustPower;
double preAdjustPower;
double derA;
double KapA=5;
double KadA=5;
double velocityA=0;
double SideL = 0;
double SideR = 0;
double TotalerrorTurn;
double erroraverageY;
double erroraverageX;
double erroraverageX1;
double erroraverageY1;
double preverroraverageX;
double preverroraverageY;
double preverroraverageX1;
double preverroraverageY1;
double derAVX;
double derAVY;
double derAVX1;
double derAVY1;
double Power;
double Strafe;
double Power1;
double Strafe1;
double turn;
double turnerror;
double prevturnerror;
double derT;
double velocityT;
double velocityrightF;
double velocityleftF;
double velocityrightB;
double velocityleftB;
int currenttime;
bool EnableMotion =true;
int counter=0;
bool EnableTurnFilter = false;
void pidStrafe(double X,double Y,double turn, double time, double maxvel,string Intake){
//Caculate Current time.

currenttime = pros::millis();

/*if(fabs(X - CurrentGlobal_X) < 0.5 && fabs(Y- CurrentGlobal_Y) <0.5){
  EnableTurnFilter = true;
}*/

lfm.tare_position();
rfm.tare_position();
lbm.tare_position();
rbm.tare_position();

VelCap = CurrentV;
while((pros::millis()-currenttime) <= time && EnableMotion){


  SideL = lefttracking.get_value();
  SideR = righttracking.get_value(); // Get Adjust R and L;


  turnerror = turn - CurrentAngle;
  pros::lcd::print(1, "A: %f", CurrentAngle);
  if (fabs(turnerror) > M_PI){
      if (turnerror > 0){
        turnerror = turnerror - (2*M_PI);
      }
      else {
        turnerror = ((2*M_PI) + turnerror);
      }
    }
  /*if(fabs(turnerror<=M_PI)){
    turnerror = turnerror;
  }
  else if (turnerror > M_PI){
    turnerror = turnerror - (2*M_PI);}
  else {
        turnerror = ((2*M_PI) + turnerror);
      }*/




  /////////X Coordinate PID.
  erroraverageX = (1*(X-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(1*(Y-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)) + 1 * (8.5431 * turnerror); // for motor lfm 8.5431.
  derAVX = erroraverageX - preverroraverageX;
  preverroraverageX = erroraverageX;
  Strafe = (erroraverageX * kpO) + (derAVX * kdO); // for motor lfm and rbm


  ////////////////////////////////////////////
  //Y Coordinate PID.
  ////////////////////////////////////////////
  erroraverageY = (1*(X-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(1*(Y-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle)) + 1 *(8.5431 * turnerror ); // for motor rfm.
  derAVY = erroraverageY - preverroraverageY;
  preverroraverageY = erroraverageY;
  Power = (erroraverageY * kpO) + (derAVY * kdO); // for motor lbm and rfm.
/////////Angle PID.


erroraverageX1 = (1*(X-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(1 *(Y-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)) - 1 *(8.5431 * turnerror); // for motor rbm.
derAVX1 = erroraverageX1 - preverroraverageX1;
preverroraverageX1 = erroraverageX1;
Strafe1 = (erroraverageX1 * kpO) + (derAVX1 * kdO); // for motor lfm and rbm


////////////////////////////////////////////
//Y Coordinate PID.
////////////////////////////////////////////
erroraverageY1 = (1*(X-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(1*(Y-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle)) - 1 *(8.5431 * turnerror); // for motor lbm.
derAVY1 = erroraverageY1 - preverroraverageY1;
preverroraverageY1 = erroraverageY1;
Power1 = (erroraverageY1 * kpO) + (derAVY1 * kdO); // for motor lbm and rfm.

  /*turnerror = turn - CurrentAngle;
  pros::lcd::print(1, "A: %f", CurrentAngle);
  if (fabs(turnerror) > M_PI){
      if (turnerror > 0){
        turnerror = turnerror - (2*M_PI);
      }
      else {
        turnerror = ((2*M_PI) + turnerror);
      }
    }
    if (fabs(turnerror) < 0.016){
      turnerror = 0;
    }


  derT = turnerror - prevturnerror;
  prevturnerror = turnerror;
  velocityT = (turnerror*kap)+(derT * kad);
*/

  if(Intake=="true"){
    rightintake.move(IntakeP);
    leftintake.move(IntakeP);
    elevator1.move(Roller1);
    elevator2.move(Roller2);
  }
  if(Intake=="false"){
    Collect(0,0,0);
  }
  if(Intake=="outtakeC"){
    if(fabs(X-CurrentGlobal_X) < 20 || fabs(Y - CurrentGlobal_Y) < 20){
    Collect(-127,-127,-127);
  }else{
    Collect(-30,0,0);}
  }
  if(Intake=="Descore"){
    Collect(-127,0,0);
  }
  if(Intake=="outtake"){
     IntakeCount = IntakeCount+1;
     if(IntakeCount>15){
    Collect(-127,-127,-127);
  }else{
    Collect(0,0,0);
  }

  }

  if(Intake=="First"){
    Collect(450,150,0);
  }
  if(Intake=="outtake5"){
    if(fabs(X-CurrentGlobal_X) < 6 || fabs(Y - CurrentGlobal_Y) < 6){
    Collect(-127,-127,-127);
  }else{
    Collect(-30,0,0);}
  }
  if(Intake=="outtake2"){
    if(fabs(X-CurrentGlobal_X) < 12){
    Collect(-127,-127,-127);
  }else{
    Collect(-30,0,0);}
  }
///////// Velocity Cut.
VelCap = VelCap + Acceleration;
if(VelCap > maxvel){
  VelCap = maxvel;
}
  if (fabs(Power) > VelCap){
    if (Power> 0){
      Power = VelCap;
    }
    else {
      Power = - VelCap;
    }
  }

  if (fabs(Power1) > VelCap){
    if (Power1> 0){
      Power1 = VelCap;
    }
    else {
      Power1 = - VelCap;
    }
  }

  if (fabs(Strafe) > VelCap){
    if (Strafe > 0){
      Strafe = VelCap;
    }
    else {
      Strafe = - VelCap;
    }
  }

  if (fabs(Strafe1) > VelCap){
    if (Strafe1 > 0){
      Strafe1 = VelCap;
    }
    else {
      Strafe1 = - VelCap;
    }
  }

  if(fabs(Power)<Min){
    if(Power>0){
      Power= Min;
    }
    else{
      Power= -Min;
    }
  }

  if(fabs(Power1)<Min){
    if(Power1>0){
      Power1= Min;
    }
    else{
      Power1= -Min;
    }
  }

  if(fabs(Strafe)<Min){
    if(Strafe>0){
      Strafe= Min;
    }
    else{
      Strafe= -Min;
    }
  }

  if(fabs(Strafe1)<Min){
    if(Strafe1>0){
      Strafe1= Min;
    }
    else{
      Strafe1= -Min;
    }
  }

/*if(EnableTurnFilter==true){
  Strafe = 0;
  Power = 0;
}*/

  if (fabs(X-CurrentGlobal_X) < 0.5 && fabs(Y-CurrentGlobal_Y) < 0.5 && fabs(turnerror) < 0.017){
  counter=counter+1;
}

  if(counter>=5){
  drive(0,0);
  EnableMotion=false;
}
  //Move function

  /*velocityleftF= Strafe + velocityT;
  velocityrightF = Power + velocityT;
  velocityleftB = Power - velocityT;
  velocityrightB= Strafe - velocityT;*/


  lfm.move(Strafe);
  rfm.move(Power);
  lbm.move(Power1);
  rbm.move(Strafe1);
  delay(10);
  }
drive(0,0);
VelCap=0;
counter=0;
EnableMotion = true;
IntakeCount = 0;
pros::lcd::print(2, "lfm: %f", lfm.get_position());
pros::lcd::print(3, "rfm: %f", rfm.get_position());
pros::lcd::print(4, "lbm: %f", lbm.get_position());
pros::lcd::print(5, "rbm: %f", rbm.get_position());
// Call function here.
//Vision();
}








int Ballinplace;

void VisionTrack(double X,double Y,double turn, double time, double maxvel,std::string Intake){
//Caculate Current time.

currenttime = pros::millis();

/*if(fabs(X - CurrentGlobal_X) < 0.5 && fabs(Y- CurrentGlobal_Y) <0.5){
  EnableTurnFilter = true;
}*/

VelCap = CurrentV;
lfm.tare_position();
rfm.tare_position();
lbm.tare_position();
rbm.tare_position();


while((pros::millis()-currenttime) <= time && EnableMotion){


  SideL = lefttracking.get_value();
  SideR = righttracking.get_value(); // Get Adjust R and L;


  turnerror = turn - CurrentAngle;
  //pros::lcd::print(1, "A: %f", CurrentAngle);
  if (fabs(turnerror) > M_PI){
      if (turnerror > 0){
        turnerror = turnerror - (2*M_PI);
      }
      else {
        turnerror = ((2*M_PI) + turnerror);
      }
    }
  /*if(fabs(turnerror<=M_PI)){
    turnerror = turnerror;
  }
  else if (turnerror > M_PI){
    turnerror = turnerror - (2*M_PI);}
  else {
        turnerror = ((2*M_PI) + turnerror);
      }*/




  /////////X Coordinate PID.
  erroraverageX = (1*(X-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(0.6*(Y-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)) +(8.5431 * turnerror); // for motor lfm./0.5
  derAVX = erroraverageX - preverroraverageX;
  preverroraverageX = erroraverageX;
  Strafe = (erroraverageX * kpO) + (derAVX * kdO); // for motor lfm and rbm


  ////////////////////////////////////////////
  //Y Coordinate PID.
  ////////////////////////////////////////////
  erroraverageY = (1*(X-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(0.6*(Y-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle)) + (8.5431 * turnerror ); // for motor rfm.
  derAVY = erroraverageY - preverroraverageY;
  preverroraverageY = erroraverageY;
  Power = (erroraverageY * kpO) + (derAVY * kdO); // for motor lbm and rfm.
/////////Angle PID.


erroraverageX1 = (1*(X-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(0.6*(Y-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)) - (8.5431 * turnerror); // for motor rbm.
derAVX1 = erroraverageX1 - preverroraverageX1;
preverroraverageX1 = erroraverageX1;
Strafe1 = (erroraverageX1 * kpO) + (derAVX1 * kdO); // for motor lfm and rbm


////////////////////////////////////////////
//Y Coordinate PID.
////////////////////////////////////////////
erroraverageY1 = (1*(X-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(0.6*(Y-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle)) - (8.5431 * turnerror); // for motor lbm.
derAVY1 = erroraverageY1 - preverroraverageY1;
preverroraverageY1 = erroraverageY1;
Power1 = (erroraverageY1 * kpO) + (derAVY1 * kdO); // for motor lbm and rfm.

  /*turnerror = turn - CurrentAngle;
  pros::lcd::print(1, "A: %f", CurrentAngle);
  if (fabs(turnerror) > M_PI){
      if (turnerror > 0){
        turnerror = turnerror - (2*M_PI);
      }
      else {
        turnerror = ((2*M_PI) + turnerror);
      }
    }
    if (fabs(turnerror) < 0.016){
      turnerror = 0;
    }


  derT = turnerror - prevturnerror;
  prevturnerror = turnerror;
  velocityT = (turnerror*kap)+(derT * kad);
*/

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
    if(fabs(X-CurrentGlobal_X) < 20 || fabs(Y - CurrentGlobal_Y) < 20){
    Collect(-127,-600,-600);
  }else{
    Collect(-30,0,0);}
  }
  if(Intake=="Descore"){
    Collect(-127,0,0);
  }
  /*if(Intake=="outtake"){

    Collect(-127,-600,-600);
  }*/

  if(Intake=="outtake"){
     IntakeCount = IntakeCount+1;
     if(IntakeCount>15){
    Collect(-127,-127,-127);
  }else{
    Collect(0,0,0);
  }

  }

  if(Intake=="First"){
    Collect(450,150,0);
  }
  if(Intake=="outtake5"){
    if(fabs(X-CurrentGlobal_X) < 6 || fabs(Y - CurrentGlobal_Y) < 6){
    Collect(-127,-600,-600);
  }else{
    Collect(-30,0,0);}
  }
  if(Intake=="outtake2"){
    if(fabs(X-CurrentGlobal_X) < 12){
    Collect(-127,-600,-600);
  }else{
    Collect(-30,0,0);}
  }
///////// Velocity Cut.
VelCap = VelCap + Acceleration;
if(VelCap > maxvel){
  VelCap = maxvel;
}
  if (fabs(Power) > VelCap){
    if (Power> 0){
      Power = VelCap;
    }
    else {
      Power = - VelCap;
    }
  }

  if (fabs(Power1) > VelCap){
    if (Power1> 0){
      Power1 = VelCap;
    }
    else {
      Power1 = - VelCap;
    }
  }

  if (fabs(Strafe) > VelCap){
    if (Strafe > 0){
      Strafe = VelCap;
    }
    else {
      Strafe = - VelCap;
    }
  }

  if (fabs(Strafe1) > VelCap){
    if (Strafe1 > 0){
      Strafe1 = VelCap;
    }
    else {
      Strafe1 = - VelCap;
    }
  }

  if(fabs(Power)<Min){
    if(Power>0){
      Power= Min;
    }
    else{
      Power= -Min;
    }
  }

  if(fabs(Power1)<Min){
    if(Power1>0){
      Power1= Min;
    }
    else{
      Power1= -Min;
    }
  }

  if(fabs(Strafe)<Min){
    if(Strafe>0){
      Strafe= Min;
    }
    else{
      Strafe= -Min;
    }
  }

  if(fabs(Strafe1)<Min){
    if(Strafe1>0){
      Strafe1= Min;
    }
    else{
      Strafe1= -Min;
    }
  }

/*if(EnableTurnFilter==true){
  Strafe = 0;
  Power = 0;
}*/
//Ballinplace = BallControldown.get();

if (fabs(X-CurrentGlobal_X) < 12 && fabs(Y-CurrentGlobal_Y) < 12 && fabs(turnerror) < 0.17){
  pros::vision_object_s_t CheckBall = Camera.get_by_sig(0, 1);
  if(CheckBall.signature != 255){
    EnableMotion = false;
    //pros::lcd::print(7, "Vision Now");
  }
}else{
  //pros::lcd::print(7, "No Vision Open");
}

if(fabs(X-CurrentGlobal_X) < 0.5 && fabs(Y-CurrentGlobal_Y) < 0.5 && fabs(turnerror) < 0.017){
  counter = counter +1;
}

if(counter >=5){
  EnableMotion=false;
}
  //Move function

  /*velocityleftF= Strafe + velocityT;
  velocityrightF = Power + velocityT;
  velocityleftB = Power - velocityT;
  velocityrightB= Strafe - velocityT;*/

  lfm.move(Strafe);
  rfm.move(Power);
  lbm.move(Power1);
  rbm.move(Strafe1);
  delay(10);
  }
//drive(0,0);
VelCap=0;
counter=0;
EnableMotion = true;
IntakeCount =0;
// Call function here.
Vision("true");
}





void PidTowerMatch(double X,double Y,double turn, double time, double maxvel, std::string Intake, int rightvalue, int leftvalue){
//Caculate Current time.

currenttime = pros::millis();

/*if(fabs(X - CurrentGlobal_X) < 0.5 && fabs(Y- CurrentGlobal_Y) <0.5){
  EnableTurnFilter = true;
}*/

lfm.tare_position();
rfm.tare_position();
lbm.tare_position();
rbm.tare_position();

VelCap = CurrentV;
while((pros::millis()-currenttime) <= time && EnableMotion){


  SideL = lefttracking.get_value();
  SideR = righttracking.get_value(); // Get Adjust R and L;


  turnerror = turn - CurrentAngle;
  pros::lcd::print(1, "A: %f", CurrentAngle);
  if (fabs(turnerror) > M_PI){
      if (turnerror > 0){
        turnerror = turnerror - (2*M_PI);
      }
      else {
        turnerror = ((2*M_PI) + turnerror);
      }
    }
  /*if(fabs(turnerror<=M_PI)){
    turnerror = turnerror;
  }
  else if (turnerror > M_PI){
    turnerror = turnerror - (2*M_PI);}
  else {
        turnerror = ((2*M_PI) + turnerror);
      }*/




  /////////X Coordinate PID.
  erroraverageX = (1*(X-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(0.6*(Y-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)) +(8.5431 * turnerror); // for motor lfm.
  derAVX = erroraverageX - preverroraverageX;
  preverroraverageX = erroraverageX;
  Strafe = (erroraverageX * kpO) + (derAVX * kdO); // for motor lfm and rbm


  ////////////////////////////////////////////
  //Y Coordinate PID.
  ////////////////////////////////////////////
  erroraverageY = (1*(X-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(0.6*(Y-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle)) + (8.5431 * turnerror ); // for motor rfm.
  derAVY = erroraverageY - preverroraverageY;
  preverroraverageY = erroraverageY;
  Power = (erroraverageY * kpO) + (derAVY * kdO); // for motor lbm and rfm.
/////////Angle PID.


erroraverageX1 = (1*(X-CurrentGlobal_X) * cos((M_PI/4) - CurrentAngle))+(0.6*(Y-CurrentGlobal_Y) * sin((M_PI/4) - CurrentAngle)) - (8.5431 * turnerror); // for motor rbm.
derAVX1 = erroraverageX1 - preverroraverageX1;
preverroraverageX1 = erroraverageX1;
Strafe1 = (erroraverageX1 * kpO) + (derAVX1 * kdO); // for motor lfm and rbm


////////////////////////////////////////////
//Y Coordinate PID.
////////////////////////////////////////////
erroraverageY1 = (1*(X-CurrentGlobal_X) * sin((M_PI/4) - CurrentAngle))-(0.6*(Y-CurrentGlobal_Y) * cos((M_PI/4) - CurrentAngle)) - (8.5431 * turnerror); // for motor lbm.
derAVY1 = erroraverageY1 - preverroraverageY1;
preverroraverageY1 = erroraverageY1;
Power1 = (erroraverageY1 * kpO) + (derAVY1 * kdO); // for motor lbm and rfm.

  /*turnerror = turn - CurrentAngle;
  pros::lcd::print(1, "A: %f", CurrentAngle);
  if (fabs(turnerror) > M_PI){
      if (turnerror > 0){
        turnerror = turnerror - (2*M_PI);
      }
      else {
        turnerror = ((2*M_PI) + turnerror);
      }
    }
    if (fabs(turnerror) < 0.016){
      turnerror = 0;
    }


  derT = turnerror - prevturnerror;
  prevturnerror = turnerror;
  velocityT = (turnerror*kap)+(derT * kad);
*/

  if(Intake=="true"){
    rightintake.move(IntakeP);
    leftintake.move(IntakeP);
    elevator1.move(Roller1);
    elevator2.move(Roller2);
  }
  if(Intake=="false"){
    Collect(0,0,0);
  }
  if(Intake=="outtakeC"){
    if(fabs(X-CurrentGlobal_X) < 20 || fabs(Y - CurrentGlobal_Y) < 20){
    Collect(-127,-127,-127);
  }else{
    Collect(-30,0,0);}
  }
  if(Intake=="Descore"){
    Collect(-127,0,0);
  }
  if(Intake=="outtake"){

    Collect(-127,-127,-127);
  }
  if(Intake=="First"){
    Collect(450,150,0);
  }
  if(Intake=="outtake5"){
    if(fabs(X-CurrentGlobal_X) < 6 || fabs(Y - CurrentGlobal_Y) < 6){
    Collect(-127,-127,-127);
  }else{
    Collect(-30,0,0);}
  }
  if(Intake=="outtake2"){
    if(fabs(X-CurrentGlobal_X) < 12){
    Collect(-127,-127,-127);
  }else{
    Collect(-30,0,0);}
  }
///////// Velocity Cut.
VelCap = VelCap + Acceleration;
if(VelCap > maxvel){
  VelCap = maxvel;
}
  if (fabs(Power) > VelCap){
    if (Power> 0){
      Power = VelCap;
    }
    else {
      Power = - VelCap;
    }
  }

  if (fabs(Power1) > VelCap){
    if (Power1> 0){
      Power1 = VelCap;
    }
    else {
      Power1 = - VelCap;
    }
  }

  if (fabs(Strafe) > VelCap){
    if (Strafe > 0){
      Strafe = VelCap;
    }
    else {
      Strafe = - VelCap;
    }
  }

  if (fabs(Strafe1) > VelCap){
    if (Strafe1 > 0){
      Strafe1 = VelCap;
    }
    else {
      Strafe1 = - VelCap;
    }
  }

  if(fabs(Power)<Min){
    if(Power>0){
      Power= Min;
    }
    else{
      Power= -Min;
    }
  }

  if(fabs(Power1)<Min){
    if(Power1>0){
      Power1= Min;
    }
    else{
      Power1= -Min;
    }
  }

  if(fabs(Strafe)<Min){
    if(Strafe>0){
      Strafe= Min;
    }
    else{
      Strafe= -Min;
    }
  }

  if(fabs(Strafe1)<Min){
    if(Strafe1>0){
      Strafe1= Min;
    }
    else{
      Strafe1= -Min;
    }
  }

/*if(EnableTurnFilter==true){
  Strafe = 0;
  Power = 0;
}*/

  if (fabs(X-CurrentGlobal_X) < 3 && fabs(Y-CurrentGlobal_Y) < 3 && fabs(turnerror) < 0.08){
    EnableMotion = false;
  //counter=counter+1;
}

  /*if(counter>=5){
  drive(0,0);
  EnableMotion=false;
}*/
  //Move function

  /*velocityleftF= Strafe + velocityT;
  velocityrightF = Power + velocityT;
  velocityleftB = Power - velocityT;
  velocityrightB= Strafe - velocityT;*/


  lfm.move(Strafe);
  rfm.move(Power);
  lbm.move(Power1);
  rbm.move(Strafe1);
  delay(10);
  }
//drive(0,0);
VelCap=0;
counter=0;
EnableMotion = true;
TowerMatch(rightvalue,leftvalue,2000,"true");
// Call function here.
//Vision();
}
