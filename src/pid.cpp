#include "main.h"
#include <math.h>
#include <iostream>
#include <cmath>



long double changeX = 0;
long double changeY = 0;

using namespace std;
double kp1 = 20; //13 before
double ki1 = 0.0000;
double kd1 = 10; // 40 before
double kap1 = 5;
double kad1 = 20;
double ksp1 = 0;
double ksd1 = 0;
double minvel=5;
// rpm/count

double distanceD;
double currentleft1;
double currentright1;
double Offset1;
double Offset2;
double Sum;
double currentaverage;
double errorwanted;
double erroraverage;
double erroraverage1;
double erroraverage2;
double erroraverage3;
double preverroraverage;
double derAV;
double velocityaverage;
double preverroraverage1;
double derAV1;
double velocityaverage1;
double preverroraverage2;
double derAV2;
double velocityaverage2;
double preverroraverage3;
double derAV3;
double velocityaverage3;
double Distance;
double turn1;
double turnerror1;
double prevturnerror1;
double derT1;
double velocityT1;
double turncurrent1;
double NaDistance;
double velocityrightf;
double velocityleftf;
double velocityleftb;
double velocityrightb;
int PidCounter=0;
bool EnablePid = true;
int currenttime1;
int VelCapPid =0;

void pidMove(double dist, double turn1, double time1, double maxvel1, std::string Intake1) {

  lfm.tare_position();
  rfm.tare_position();
  lbm.tare_position();
  rbm.tare_position();

  if(turn1 == 0){
    turn1 = imu.get_heading();
  }

Offset1=lefttracking.get_value();
Offset2= righttracking.get_value();

errorwanted = dist;

currenttime1 = pros::millis();

while((pros::millis()-currenttime1) <= time1 && EnablePid){

  currentleft1 = (lefttracking.get_value() - Offset1);
  currentright1 = (righttracking.get_value() - Offset2);


  Sum = ((currentleft1 + currentright1)/2);
  currentaverage = ((Sum/360)*(M_PI*2.75));

  if(turn1<0){
    turn1 = turn1 + 360;
  }
  if(turn1>360){
    turn1=turn1 -360;
  }

  turnerror1 = turn1 - imu.get_heading();

  if (fabs(turnerror1) > 180){
      if (turnerror1 > 0){
        turnerror1 = turnerror1 - 360;
      }
      else {
        turnerror1 = (360 + turnerror1);
      }
    }

  turnerror1 = (turnerror1 * M_PI) /180;
  Distance = errorwanted - currentaverage;
  NaDistance = - Distance;
  erroraverage = ((Distance * sqrt(2)*0.25) + (8.5431 * turnerror1)); //lfm
  derAV = erroraverage - preverroraverage;
  preverroraverage = erroraverage;
  velocityaverage = (erroraverage * kp1) + (derAV * kd1);


  erroraverage1 = ((NaDistance * sqrt(2)*0.25) + (8.5431 * turnerror1)); //rfm
  derAV1 = erroraverage1 - preverroraverage1;
  preverroraverage1 = erroraverage1;
  velocityaverage1 = (erroraverage1 * kp1) - (1 * (derAV1 * kd1));



  erroraverage2 = ((NaDistance * sqrt(2)*0.25) - (8.5431 * turnerror1)); //lbm
  derAV2 = erroraverage2 - preverroraverage2;
  preverroraverage2 = erroraverage2;
  velocityaverage2 = (erroraverage2 * kp1) - (1 * (derAV2 * kd1));

  erroraverage3 = ((Distance * sqrt(2)*0.25) - (8.5431 * turnerror1)); //rbm
  derAV3 = erroraverage3 - preverroraverage3;
  preverroraverage3 = erroraverage3;
  velocityaverage3 = (erroraverage3 * kp1) + (derAV3 * kd1);


  ////////////////////////////////////////////
  //Angle PID
  ////////////////////////////////////////////

  VelCapPid = VelCapPid + 15;
    if(VelCapPid > maxvel1){
      VelCapPid = maxvel1;
    }

    if (fabs(velocityaverage) > VelCapPid){
        if (velocityaverage > 0){
          velocityaverage = VelCapPid;
        }
        else {
          velocityaverage = -VelCapPid;
        }
      }


    if (fabs(velocityaverage1) > VelCapPid){
        if (velocityaverage1 > 0){
            velocityaverage1 = VelCapPid;
          }
        else {
            velocityaverage1 = -VelCapPid;
          }
        }

    if (fabs(velocityaverage2) > VelCapPid){
        if (velocityaverage2 > 0){
              velocityaverage2 = VelCapPid;
            }
        else {
              velocityaverage2 = -VelCapPid;
            }
          }

    if (fabs(velocityaverage3) > VelCapPid){
        if (velocityaverage3 > 0){
                velocityaverage3 = VelCapPid;
              }
        else {
                velocityaverage3 = -VelCapPid;
              }
            }

    if(fabs(velocityaverage)< 12){
      if(velocityaverage>0){
        velocityaverage=12;
      }
      else{
        velocityaverage=-12;
      }
    }

    if(fabs(velocityaverage1)< 12){
      if(velocityaverage1>0){
        velocityaverage1=12;
      }
      else{
        velocityaverage1=-12;
      }
    }

    if(fabs(velocityaverage2)< 12){
      if(velocityaverage2>0){
        velocityaverage2=12;
      }
      else{
        velocityaverage2=-12;
      }
    }

    if(fabs(velocityaverage3)< 12){
      if(velocityaverage3>0){
        velocityaverage3=12;
      }
      else{
        velocityaverage3=-12;
      }
    }

    if(Intake1=="true"){
      rightintake.move(IntakeP);
      leftintake.move(IntakeP);
      elevator1.move(Roller1);
      elevator2.move(Roller2);
    }
    if(Intake1=="false"){
      Collect(0,0,0);
    }
    if(Intake1=="outtake"){

      Collect(-20,0,0);
    }
    if(Intake1 == "outakeAlot"){
      Collect(-80,0,0);
    }

    if(Intake1=="Descore"){
      Collect(-127,0,0);
    }
    if(Intake1=="First"){
      Collect(450,150,0);
    }
    if(Intake1=="Flip"){
    rightintake.move_velocity(600);
    }
    //DeadZone
    //if (fabs(erroraverage) < 0.5 && fabs(erroraverage1) < 0.5 && fabs(erroraverage2) < 0.5 && fabs(erroraverage3) < 0.5){
    if(fabs(errorwanted-currentaverage) < 0.5){
    PidCounter = PidCounter +1;
    }

    if(PidCounter >= 5){
      EnablePid = false;
    }


    lfm.move(velocityaverage); //move before
    rfm.move(velocityaverage1);
    lbm.move(velocityaverage2);
    rbm.move(velocityaverage3);

  delay(10);
  }
  drive(0,0);
  //pros::lcd::print(2, "lfm: %f", lfm.get_position());
  //pros::lcd::print(5, "lbm: %f", lbm.get_position());
  //pros::lcd::print(7, "rfm: %f", rfm.get_position());
  //pros::lcd::print(4, "rbm: %f", rbm.get_position());
  EnablePid = true;
  VelCapPid =0;
  PidCounter=0;
}

/**
void pidXY(double X, double Y, double maxvel, double time) {
  double dist = (sqrt((pow((X - changeX),2.0))+(pow((Y - changeY),2.0))));

  turn = atan((X - changeX)/(Y - changeY));
  lbm.tare_position();
  rbm.tare_position();
  errorwanted = ((dist) / (4* 3.141592))*(1800/7);

  currenttime = pros::millis();

  while((pros::millis()-currenttime) <= time){

  currentleft = lbm.get_position();
  currentright = rbm.get_position();

  currentaverage = (currentleft + currentright)/2;

  erroraverage = errorwanted - currentaverage;

  derAV = erroraverage - preverroraverage;
  preverroraverage = erroraverage;

  velocityaverage = (erroraverage * kp) + (derAV * kd);

  ////////////////////////////////////////////
  //Angle PID
  ////////////////////////////////////////////


  turnerror = turn - imu.get_heading();
  if (fabs(turnerror) > 180){
    if (turnerror > 0){
      turnerror = turnerror - 360;
    }
    else {
      turnerror = (360 + turnerror);
    }
  }
  if (fabs(turnerror) < 1){
    turnerror = 0;
  }


  derT = turnerror - prevturnerror;
  prevturnerror = turnerror;

  velocityT = (turnerror*kap)+(derT * kad);






  if (fabs(velocityaverage) > maxvel){
    if (velocityaverage > 0){
      velocityaverage = maxvel;
    }
    else {
      velocityaverage = -maxvel;
    }
  }

  //DeadZone
  if (fabs(erroraverage) < 40 && fabs(turnerror) < 1){
  drive(0,0);

  break;
  }

  velocityright = velocityaverage - velocityT;
  velocityleft = velocityaverage + velocityT;



  lfm.move(velocityleft);
  lbm.move(velocityleft);
  rfm.move(velocityright);
  rbm.move(velocityright);






  delay(10);
  }
  drive(0,0);
  }



 void odom(){

     long double theta = 0;
     long double prevtheta = 0;
     long double phi;
     long double dx = 0;
     long double dy = 0;
     long double sint = 0;
     long double cost = 0;
     double h;
     double radius=0;
     double c=0;

     double leftencoder = 0;
     double rightencoder = 0;
     double encoder = 0;


     while(true){

       theta = imu.get_heading()*(3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534/180);
       phi = theta - prevtheta;
       prevtheta = theta;
       if(phi<0){
         phi = 360 + phi;
       }


       leftencoder = lbm.get_position()- ((2*phi*radius)/c);
       rightencoder = rbm.get_position()+ ((2*phi*radius)/c);
       encoder = (leftencoder+rightencoder)/2;
       h = 2*(encoder/theta)*sin(theta/2);


       sint = sin(theta);
       cost = cos(theta);
       dx = h*sint;
       dy = h* cost;

       changeX = dx;
       changeY = dy;
       std::cout<<changeX<<"  "<<changeY<<std::endl;
       delay(1000);
       theta = theta*(180/3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534);
     }
  }
*/
/**

  void rotateto(double degrees,double speed){
    double rightDeg = 0;
    double leftDeg = 0;
    double difference = 0;
    double within10ofdiffernce = 0;
    bool leftturn = false;


    if(imu.get_heading() < degrees){
      rightDeg = degrees-imu.get_heading();
      leftDeg = 360 + (imu.get_heading()-degrees) ;
    }
    else{
      rightDeg = 360 - imu.get_heading() + degrees ;
      leftDeg = imu.get_heading() - degrees;
    }

    if(rightDeg> leftDeg){//left is shorter
      speed = -speed;
      difference  = leftDeg;
      leftturn = true;
    }
    else{
      difference = rightDeg;
    }

    if(difference > 20){
      drive(speed,-speed);
      delay(200);
      while(difference>20){
        if(imu.get_heading()<degrees){
          if(leftturn){
            difference = degrees-imu.get_heading();
            leftturn = false;
            speed = -speed;

           }
          else{
                difference = degrees - imu.get_heading();

          }
        }
        else{
          if(leftturn){
            difference = imu.get_heading()-degrees;

          }
          else {
            leftturn = true;
            speed = -speed;
            difference = imu.get_heading() - degrees;
          }


          }
          delay(200);


          }
  stophold();
  delay(100);

        }


        drive(0.25*speed,-0.25*speed);
    if(difference < 20) {
      drive(0.25*speed,-0.25*speed);
      delay(200);

      while(fabs(difference) > 5 ){
        drive(0.25*speed,-0.25*speed);
        if(imu.get_heading()<degrees){
          if(leftturn){
            difference = degrees-imu.get_heading();
            leftturn = false;
            speed = -speed;

           }
          else{
                difference = degrees - imu.get_heading();

          }
        }
        else{
          if(leftturn){
            difference = imu.get_heading()-degrees;

          }
          else {
            leftturn = true;
            speed = -speed;
            difference = imu.get_heading() - degrees;
          }


          }

    }
    delay(200);
    stophold();
    }


  }*/
