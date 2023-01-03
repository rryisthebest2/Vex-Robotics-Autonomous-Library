#include "main.h"
#include <math.h>
#include <iostream>
#include <cmath>

using namespace std;
/*double ki = 0.00;
double kd = 60;//36//200//180
double kap = 180;
double kad = 25;
double ksp = 45;
double ksd = 10;*/
// rpm/count
/*double Offset = 18;
double turn2;
double turnerror2;
double prevturnerror2;
double derT2;
double velocityT2;
double Average = 0;
//double erroraverageD;
//double preverroraverageD;
//double derAVY1;
double turn3;
double turn4;
double turn5;

void BackTo(double X1,double Y1, double time2){
//Caculate Current time.

double ChangeOfX = X1 - CurrentGlobal_X;
double ChangeOfY = Y1 - CurrentGlobal_Y;
double Distance =  Offset-sqrt((pow(ChangeOfX,2.0))+(pow(ChangeOfY,2.0)));

  currentDL = (lefttracking.get_value() - CancelL);
  currentDR = (righttracking.get_value() - CancelR);
  Average = (currentDL + currentDR) / 2;
  CurrentDistance = ((Average/360)*(M_PI*2.739));
  erroraverageD = Distance - CurrentDistance;
  derAVY = erroraverageD - preverroraverageD;
  preverroraverageD = erroraverageD;
  VelocityRN = (erroraverageD * kp) + (derAVYD * kd);
/////////Angle PID.

  if(fabs(ChangeOfY) < 0.5){

      if (ChangeOfX > 0){
      turn2 = (3*M_PI)/2;
      //pros::lcd::print(2, "My bad");
      }else{
      turn2 = M_PI/2;
      //pros::lcd::print(7, "Here");
      }
  }else if (ChangeOfY > 0){
        turn2 = (M_PI+atan(ChangeOfX / ChangeOfY));
        } else {
        turn2 = atan(ChangeOfX / ChangeOfY);
        }
  turn2 = (turn2 * 180) / M_PI;

  pidMove(0,turn2,time2,200,"false");
  pidMove(Distance,0,time2,200,"outtake");
  pidMove(0,(180+turn2),1000,200,"false");
  pidMove(18,0,600,200,"true");
  Vision();
  delay(10);
  }



  void HeadTo(double X2,double Y2, double time3){
  //Caculate Current time.

  double ChangeOfX = X2 - CurrentGlobal_X;
  double ChangeOfY = Y2 - CurrentGlobal_Y;
  double Distance = (sqrt((pow(ChangeOfX,2.0))+(pow(ChangeOfY,2.0))) - Offset);

    currentDL = (lefttracking.get_value() - CancelL);
    currentDR = (righttracking.get_value() - CancelR);
    Average = (currentDL + currentDR) / 2;
    CurrentDistance = ((Average/360)*(M_PI*2.739));
    erroraverageD = Distance - CurrentDistance;
    derAVY = erroraverageD - preverroraverageD;
    preverroraverageD = erroraverageD;
    VelocityRN = (erroraverageD * kp) + (derAVYD * kd);
  /////////Angle PID.

    if(fabs(ChangeOfY) < 0.5){

      if (X2 > CurrentGlobal_X){
        turn3 = M_PI/2;
      }else{
        turn3 = (3*M_PI)/2;
      }
    }
    else if (fabs(ChangeOfY) > 0.5){
            turn3 = atan(ChangeOfX / ChangeOfY);
          }
    else {
            turn3 =(M_PI + atan(ChangeOfX / ChangeOfY));
          }
    turn3 = (turn3 * 180) / M_PI;
    //pros::lcd::print(5, "Angle: %f", turn3);
    pidMove(0,turn3,time3,600,"false");
    pidMove(Distance+18,0,time3,200,"true");
    if (fabs(Distance) < 4){
      Vision();
    }else{
    pidMove(Distance,0,time3,200,"true");
    Vision();
    delay(10);
  }
}




    void Back(double X4, double Y4, double time4,std::string Intake3){
    //Caculate Current time.

    double ChangeOfX = X4 - CurrentGlobal_X;
    double ChangeOfY = Y4 - CurrentGlobal_Y;
    double Distance = -sqrt((pow(ChangeOfX,2.0))+(pow(ChangeOfY,2.0)));

      currentDL = (lefttracking.get_value() - CancelL);
      currentDR = (righttracking.get_value() - CancelR);
      Average = (currentDL + currentDR) / 2;
      CurrentDistance = ((Average/360)*(M_PI*2.739));
      erroraverageD = Distance - CurrentDistance;
      derAVY = erroraverageD - preverroraverageD;
      preverroraverageD = erroraverageD;
      VelocityRN = (erroraverageD * kp) + (derAVYD * kd);
    /////////Angle PID.

      if(fabs(ChangeOfY) < 0.5){

          if (ChangeOfX > 0){
          turn4 = (3*M_PI)/2;
          //pros::lcd::print(2, "My bad");
          }else{
          turn4 = M_PI/2;
          //pros::lcd::print(7, "Here");
          }
      }else if (ChangeOfY > 0){
            turn4 = (M_PI+atan(ChangeOfX / ChangeOfY));
            } else {
            turn4 = atan(ChangeOfX / ChangeOfY);
            }
      turn4 = (turn4 * 180) / M_PI;
      pidMove(0,turn4,time4,200,Intake3);
      pidMove(Distance,0,time4,200,Intake3);
      delay(10);
      }

      void Head(double X5,double Y5, double time5, std::string Intake4){
      //Caculate Current time.

      double ChangeOfX = X5 - CurrentGlobal_X;
      double ChangeOfY = Y5 - CurrentGlobal_Y;
      double Distance = sqrt((pow(ChangeOfX,2.0))+(pow(ChangeOfY,2.0)));

        currentDL = (lefttracking.get_value() - CancelL);
        currentDR = (righttracking.get_value() - CancelR);
        Average = (currentDL + currentDR) / 2;
        CurrentDistance = ((Average/360)*(M_PI*2.739));
        erroraverageD = Distance - CurrentDistance;
        derAVY = erroraverageD - preverroraverageD;
        preverroraverageD = erroraverageD;
        VelocityRN = (erroraverageD * kp) + (derAVYD * kd);
      /////////Angle PID.

        if(fabs(ChangeOfY) < 0.5){

          if (X5 > CurrentGlobal_X){
            turn5 = M_PI/2;
          }else{
            turn5 = (3*M_PI)/2;
          }
        }else if (ChangeOfY > 0){
                turn5 = atan(ChangeOfX / ChangeOfY);
              }else {
                turn5 =(M_PI + atan(ChangeOfX / ChangeOfY));
              }
        turn3 = (turn5 * 180) / M_PI;
        pidMove(0,turn5,time5,600,Intake4);
        pidMove(Distance,0,time5,200,Intake4);
        delay(10);
        }
*/
