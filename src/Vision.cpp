#include "main.h"
double CurrentV;
double CurrenttimeV;
double turnerrorV;
bool BallCollect = false;
long double AddX=50.75;
long double AddY=15.75;
long double AddAngle=0;
double AddVelocityX =0;
double AddVelocityY =0;
double StartWidth=250;
double Xdistance =11;
double YDistance =11;
double velocityLF;
double velocityRF;
double velocityLB;
double velocityRB;
double kap2=2.5;
double kp2=2;
double kadV=10;
double kdV =15;
int VMinS=0;
int VMinY=0;
double VisionDX;
double VisionDY;
double PreX;
double PreY;
int BallInfo = 120;
int BallInfoup = 120;
int counterVision=0;
void Vision(std::string Intake){
  /*if(BallNum ==1){
    BallInfo = 40;
  }*/
  pros::lcd::print(4, "BallNumOption: %d", BallInfo);
  while(counterVision<1 || BallCollect == false){
    /*if(BallNum==2){
    BallInfo= VisionDetect.get();
  }*/
    //BallInfoup =BallControlUp.get();
    pros::lcd::print(5, "Down: %d", BallInfo);
    pros::lcd::print(2, "Up: %d", BallInfoup);
    pros::vision_object_s_t RedDetect = Camera.get_by_sig(0, 1);
    double XPosition = RedDetect.x_middle_coord;
    Xdistance = XPosition - VISION_FOV_WIDTH/2;
    if(RedDetect.signature ==255){
      AddVelocityX =0;
      Xdistance=0;
    }else{
      VisionDX = Xdistance - PreX;
      PreX = Xdistance;
      AddVelocityX = (Xdistance * kp2) + (VisionDX * kdV);
    }

    int ObjectHigh = RedDetect.width;
    if(ObjectHigh > 150){
      counterVision = counterVision +1;
    }
    int Detect = VisionDetect.get();
    if(Detect<70){
      BallCollect = true;
    }
    YDistance = StartWidth - ObjectHigh;
    if(RedDetect.signature ==255){
      AddVelocityY =0;
      YDistance=0;
    }else{
      VisionDY = YDistance - PreY;
      PreY = YDistance;
      AddVelocityY = (YDistance * kap2) + (PreY * kadV);
    }
    if (fabs(AddVelocityY) > 127){
      if (AddVelocityY> 0){
        AddVelocityY = 127;
      }
      else {
        AddVelocityY = -127;
      }
    }

    if (fabs(AddVelocityX) > 127){
      if (AddVelocityX> 0){
        AddVelocityX = 127;
      }
      else {
        AddVelocityX = -127;
      }
    }

    if(fabs(AddVelocityX)<VMinS){
      if(AddVelocityX>0){
        AddVelocityX= VMinS;
      }
      else{
        AddVelocityX= - VMinS;
      }
    }

    if(fabs(AddVelocityY)<VMinY){
      if(AddVelocityY>0){
        AddVelocityY= VMinY;
      }
      else{
        AddVelocityY= - VMinY;
      }
    }

    if(Intake=="true"){
      rightintake.move(IntakeP);
      leftintake.move(IntakeP);
      elevator1.move(Roller1);
      elevator2.move(Roller2);
    }

    if(sin(CurrentAngle) == 0){
      if(CurrentGlobal_X < 10 || CurrentGlobal_X > 134){
        break;
      }

    }

    if(sin(CurrentAngle) > 0){
      if(CurrentGlobal_X > (144 - (12 * sin(CurrentAngle)))) {
        break;
      }

    }

    if(sin(CurrentAngle) <0 ){
        if(CurrentGlobal_X < (-12 * sin(CurrentAngle))){
          break;
        }
    }

/*   /* if(TowerSpot == 1){
      if(CurrentGlobal_X > 54 || CurrentGlobal_Y > 54){
        break;
      }
    }

    if(TowerSpot == 2){
      if(CurrentGlobal_Y > 60){
        break;
      }
    }

    if(TowerSpot == 3){
      if(CurrentGlobal_Y > 96 || CurrentGlobal_X < 88){
        break;
      }
    }

    if(TowerSpot == 4){
      if(CurrentGlobal_X < 88){
        break;
      }
    }

    if(TowerSpot == 5){
      if(CurrentGlobal_X < 48 || CurrentGlobal_Y < 72){
        break;
      }

    }

    if(TowerSpot == 6){
      if(CurrentGlobal_Y < 88){
        break;
      }

    }
*/


    velocityLF = AddVelocityY + AddVelocityX;
    velocityRF = - AddVelocityY + AddVelocityX;
    velocityLB = - AddVelocityY - AddVelocityX;
    velocityRB = AddVelocityY - AddVelocityX;

CurrentV = (fabs(velocityLF) + fabs(velocityRF)) / 2;

    lfm.move(velocityLF);
    rfm.move(velocityRF);
    lbm.move(velocityLB);
    rbm.move(velocityRB);
    delay(20);
  }
  Collect(IntakeP,Roller1,Roller2);
  counterVision = 0;
  BallCollect = false;
  //BallInfo = 120;
  //BallInfoup=120;
//drive(0,0);
//Xdistance =11;
//YDistance =11;
}






void VisionBlue(std::string Intake,double turn, double TimeLimit){
leftintake.set_brake_mode(MOTOR_BRAKE_COAST);
rightintake.set_brake_mode(MOTOR_BRAKE_COAST);
CurrenttimeV = pros::millis();

  while(counterVision < 1 && (pros::millis()- CurrenttimeV) <= TimeLimit){

    pros::vision_object_s_t BlueDetect = Camera.get_by_sig(0, 2);
    double XPosition = BlueDetect.x_middle_coord;
    Xdistance = XPosition - VISION_FOV_WIDTH/2;
    if(BlueDetect.signature ==255){
      AddVelocityX =0;
      Xdistance=0;
    }else{
      VisionDX = Xdistance - PreX;
      PreX = Xdistance;
      AddVelocityX = (Xdistance * kp2) + (VisionDX * kdV);
    }

    int ObjectHigh = BlueDetect.width;
    if(Xdistance < 0){
      counterVision = counterVision +1;
    }
    YDistance = StartWidth- ObjectHigh;
    if(BlueDetect.signature ==255){
      AddVelocityY =0;
      YDistance=0;
    }else{
      VisionDY = YDistance - PreY;
      PreY = YDistance;
      AddVelocityY = (YDistance * kap2) + (PreY * kadV);
    }

    turnerrorV = turn - CurrentAngle;
    if (fabs(turnerrorV) > M_PI){
        if (turnerrorV > 0){
          turnerrorV = turnerrorV - (2*M_PI);
        }
        else {
          turnerrorV = ((2*M_PI) + turnerrorV);
        }
      }

    derT = turnerrorV - prevturnerror;
    prevturnerror = turnerrorV;
    velocityT = (turnerrorV*kap)+(derT * kad);


    if (fabs(AddVelocityY) > 127){
      if (AddVelocityY> 0){
        AddVelocityY = 127;
      }
      else {
        AddVelocityY = -127;
      }
    }

    if (fabs(AddVelocityX) > 127){
      if (AddVelocityX> 0){
        AddVelocityX = 127;
      }
      else {
        AddVelocityX = -127;
      }
    }

    if(fabs(AddVelocityX)<VMinS){
      if(AddVelocityX>0){
        AddVelocityX= VMinS;
      }
      else{
        AddVelocityX= - VMinS;
      }
    }

    if(fabs(AddVelocityY)<VMinY){
      if(AddVelocityY>0){
        AddVelocityY= VMinY;
      }
      else{
        AddVelocityY= - VMinY;
      }
    }


    if(fabs(velocityT)<VMinY){
      if(velocityT>0){
        velocityT= VMinY;
      }
      else{
        velocityT= - VMinY;
      }
    }

    if(Intake=="true"){
      rightintake.move(IntakeP);
      leftintake.move(IntakeP);
      elevator1.move(Roller1);
      elevator2.move(Roller2);
    }

    if(Intake=="false"){
      Collect(0,0,0);
    }

    /*if(sin(CurrentAngle) == 0){
      if(CurrentGlobal_X < 12 || CurrentGlobal_X > 132){
        break;
      }

    }

    if(sin(CurrentAngle) > 0){
      if(CurrentGlobal_X > (144 - (21 * sin(CurrentAngle)))) {
        break;
      }

    }

    if(sin(CurrentAngle) <0 ){
        if(CurrentGlobal_X < (-21 * sin(CurrentAngle))){
          break;
        }
    }*/

/*    if(TowerSpot == 1){
      if(CurrentGlobal_X > 54 || CurrentGlobal_Y > 54){
        break;
      }
    }

    if(TowerSpot == 2){
      if(CurrentGlobal_Y > 60){
        break;
      }
    }

    if(TowerSpot == 3){
      if(CurrentGlobal_Y > 96 || CurrentGlobal_X < 88){
        break;
      }
    }

    if(TowerSpot == 4){
      if(CurrentGlobal_X < 88){
        break;
      }
    }

    if(TowerSpot == 5){
      if(CurrentGlobal_X < 48 || CurrentGlobal_Y < 72){
        break;
      }

    }

    if(TowerSpot == 6){
      if(CurrentGlobal_Y < 88){
        break;
      }

    }
*/


    velocityLF = AddVelocityY + AddVelocityX + velocityT;
    velocityRF = - AddVelocityY + AddVelocityX + velocityT;
    velocityLB = - AddVelocityY + AddVelocityX - velocityT;
    velocityRB = AddVelocityY + AddVelocityX - velocityT;

CurrentV = (fabs(velocityLF) + fabs(velocityRF)) / 2;

    lfm.move(velocityLF);
    rfm.move(velocityRF);
    lbm.move(velocityLB);
    rbm.move(velocityRB);
    delay(20);
  }
  Collect(IntakeP,Roller1,Roller2);
  counterVision = 0;

  //BallInfo = 120;
  //BallInfoup=120;
//drive(0,0);
//Xdistance =11;
//YDistance =11;
}
