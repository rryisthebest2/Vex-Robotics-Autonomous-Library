#include "main.h"
bool EnablePositionTrack = true;
long double CurrentGlobal_X=52.375;
long double CurrentGlobal_Y=11.72917;
double CurrentAngle=0;
double deta_x;
double deta_y;
double deta_Angle=0;
bool EnablePositionTrack1st = true;
bool EnablePositionTrack2nd = true;
bool EnablePositionTrack3rd = true;
double Odometry(){
  righttracking.reset();
  horizontaltracking.reset();
  lefttracking.reset();
  double lastAngle= 0;
  double LAST_EncoderX=0;
  double Wheel_BackDisBetwwen = 14.45;
  double Wheel_Middle= 5.9;//5.9375// 5.75!!!/6
  double wheeldiameter=2.75;
  double LAST_EncoderR=0;
  double LAST_EncoderL=0;
  while(EnablePositionTrack){
    //update the current angle the robot is facing and caculate the change in angle

    //Caculate change in encoder value and convert them to inches.

    double EncoderR=((righttracking.get_value()/360.00000000000000)*(wheeldiameter*M_PI));
    double EncoderL=((lefttracking.get_value()/360.00000000000000)*(wheeldiameter*M_PI));
    double deta_EncoderR=(EncoderR-LAST_EncoderR);
    double deta_EncoderL =( (EncoderL - LAST_EncoderL));
    double EncoderY= (deta_EncoderL+deta_EncoderR)/2;
    double EncoderX=((horizontaltracking.get_value()/360.000000000000000)*(wheeldiameter*M_PI));
    double deta_Encoderx= (EncoderX-LAST_EncoderX);
    CurrentAngle=(imu.get_heading()*(M_PI/180));
    //pros::lcd::print(7, "deta_EncoderX: %f", deta_Encoderx);
    double deta_Angle = ((deta_EncoderR-deta_EncoderL)/Wheel_BackDisBetwwen);//DIVIDE by distance between the two backwheel.
    //pros::lcd::print(3, "horizontaltracking: %d", horizontaltracking.get_value());
    //pros::lcd::print(4, "righttracking: %d", righttracking.get_value());
    printf("CurrentAngle: %f", CurrentAngle);
    printf("X: %Le \n", CurrentGlobal_X);
    printf("Y: %Le \n", CurrentGlobal_Y);
    /*if (deta_Angle!=0){
       deta_x= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)+deta_Encoderx*sin(M_PI/2-lastAngle+deta_Angle/2));
       deta_y= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)-deta_Encoderx*cos(M_PI/2-lastAngle+deta_Angle/2));
    } else{
        deta_x=EncoderY*sin(CurrentAngle)+deta_Encoderx*cos(CurrentAngle);
        deta_y=EncoderY*cos(CurrentAngle)-deta_Encoderx*sin(CurrentAngle);
    }*/

    if (fabs(deta_Angle) <=0.00003){
      deta_x=EncoderY*sin(CurrentAngle)+deta_Encoderx*cos(CurrentAngle);
      deta_y=EncoderY*cos(CurrentAngle)-deta_Encoderx*sin(CurrentAngle);

    } else{
      deta_x= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)+(2*((deta_Encoderx/deta_Angle)-Wheel_Middle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)));
      deta_y= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)-(2*((deta_Encoderx/deta_Angle)-Wheel_Middle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)));
    }

    CurrentGlobal_X=CurrentGlobal_X+deta_x;
    CurrentGlobal_Y=CurrentGlobal_Y+deta_y;
    pros::lcd::print(0, "X: %f", CurrentGlobal_X);
    pros::lcd::print(6, "Y: %f", CurrentGlobal_Y);
    //pros::lcd::print(2, "horizontaltracking: %d", horizontaltracking.get_value());
    //pros::lcd::print(5, "lefttracking: %d", lefttracking.get_value());
    //pros::lcd::print(7, "righttracking: %d", righttracking.get_value());
    //pros::lcd::print(4, "A: %f", CurrentAngle);
    lastAngle=CurrentAngle;
    LAST_EncoderR=EncoderR;
    LAST_EncoderL=EncoderL;
    LAST_EncoderX=EncoderX;
    delay(10);
    //caculating the change in X and Y position of the robot

  }

  return 1;
}





double Odometry1st(){
  CurrentGlobal_X = 128;
  CurrentGlobal_Y = 17;
  //imu.set_heading(140);
  righttracking.reset();
  horizontaltracking.reset();
  lefttracking.reset();
  double lastAngle= 0;
  double LAST_EncoderX=0;
  double Wheel_BackDisBetwwen = 14.45;
  double Wheel_Middle= 5.9;//5.9375// 5.75!!!/6
  double wheeldiameter=2.75;
  double LAST_EncoderR=0;
  double LAST_EncoderL=0;
  while(EnablePositionTrack1st){
    //update the current angle the robot is facing and caculate the change in angle

    //Caculate change in encoder value and convert them to inches.

    double EncoderR=((righttracking.get_value()/360.00000000000000)*(wheeldiameter*M_PI));
    double EncoderL=((lefttracking.get_value()/360.00000000000000)*(wheeldiameter*M_PI));
    double deta_EncoderR=(EncoderR-LAST_EncoderR);
    double deta_EncoderL =( (EncoderL - LAST_EncoderL));
    double EncoderY= (deta_EncoderL+deta_EncoderR)/2;
    double EncoderX=((horizontaltracking.get_value()/360.000000000000000)*(wheeldiameter*M_PI));
    double deta_Encoderx= (EncoderX-LAST_EncoderX);
    CurrentAngle=(imu.get_heading()*(M_PI/180));
    //pros::lcd::print(7, "deta_EncoderX: %f", deta_Encoderx);
    double deta_Angle = ((deta_EncoderR-deta_EncoderL)/Wheel_BackDisBetwwen);//DIVIDE by distance between the two backwheel.
    //pros::lcd::print(3, "horizontaltracking: %d", horizontaltracking.get_value());
    //pros::lcd::print(4, "righttracking: %d", righttracking.get_value());
    printf("CurrentAngle: %f", CurrentAngle);
    printf("X: %Le \n", CurrentGlobal_X);
    printf("Y: %Le \n", CurrentGlobal_Y);
    /*if (deta_Angle!=0){
       deta_x= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)+deta_Encoderx*sin(M_PI/2-lastAngle+deta_Angle/2));
       deta_y= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)-deta_Encoderx*cos(M_PI/2-lastAngle+deta_Angle/2));
    } else{
        deta_x=EncoderY*sin(CurrentAngle)+deta_Encoderx*cos(CurrentAngle);
        deta_y=EncoderY*cos(CurrentAngle)-deta_Encoderx*sin(CurrentAngle);
    }*/

    if (fabs(deta_Angle) <=0.00003){
      deta_x=EncoderY*sin(CurrentAngle)+deta_Encoderx*cos(CurrentAngle);
      deta_y=EncoderY*cos(CurrentAngle)-deta_Encoderx*sin(CurrentAngle);

    } else{
      deta_x= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)+(2*((deta_Encoderx/deta_Angle)-Wheel_Middle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)));
      deta_y= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)-(2*((deta_Encoderx/deta_Angle)-Wheel_Middle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)));
    }

    CurrentGlobal_X=CurrentGlobal_X+deta_x;
    CurrentGlobal_Y=CurrentGlobal_Y+deta_y;
    pros::lcd::print(0, "X: %f", CurrentGlobal_X);
    pros::lcd::print(6, "Y: %f", CurrentGlobal_Y);
    //pros::lcd::print(2, "horizontaltracking: %d", horizontaltracking.get_value());
    //pros::lcd::print(5, "lefttracking: %d", lefttracking.get_value());
    //pros::lcd::print(7, "righttracking: %d", righttracking.get_value());
    //pros::lcd::print(4, "A: %f", CurrentAngle);
    lastAngle=CurrentAngle;
    LAST_EncoderR=EncoderR;
    LAST_EncoderL=EncoderL;
    LAST_EncoderX=EncoderX;
    delay(10);
    //caculating the change in X and Y position of the robot

  }

  return 1;
}






double Odometry2nd(){
  CurrentGlobal_X = 128;
  CurrentGlobal_Y = 128;
  //imu.set_heading(140);
  righttracking.reset();
  horizontaltracking.reset();
  lefttracking.reset();
  double lastAngle= 0;
  double LAST_EncoderX=0;
  double Wheel_BackDisBetwwen = 14.45;
  double Wheel_Middle= 5.9;//5.9375// 5.75!!!/6
  double wheeldiameter=2.75;
  double LAST_EncoderR=0;
  double LAST_EncoderL=0;
  while(EnablePositionTrack2nd){
    //update the current angle the robot is facing and caculate the change in angle

    //Caculate change in encoder value and convert them to inches.

    double EncoderR=((righttracking.get_value()/360.00000000000000)*(wheeldiameter*M_PI));
    double EncoderL=((lefttracking.get_value()/360.00000000000000)*(wheeldiameter*M_PI));
    double deta_EncoderR=(EncoderR-LAST_EncoderR);
    double deta_EncoderL =( (EncoderL - LAST_EncoderL));
    double EncoderY= (deta_EncoderL+deta_EncoderR)/2;
    double EncoderX=((horizontaltracking.get_value()/360.000000000000000)*(wheeldiameter*M_PI));
    double deta_Encoderx= (EncoderX-LAST_EncoderX);
    CurrentAngle=(imu.get_heading()*(M_PI/180));
    //pros::lcd::print(7, "deta_EncoderX: %f", deta_Encoderx);
    double deta_Angle = ((deta_EncoderR-deta_EncoderL)/Wheel_BackDisBetwwen);//DIVIDE by distance between the two backwheel.
    //pros::lcd::print(3, "horizontaltracking: %d", horizontaltracking.get_value());
    //pros::lcd::print(4, "righttracking: %d", righttracking.get_value());
    printf("CurrentAngle: %f", CurrentAngle);
    printf("X: %Le \n", CurrentGlobal_X);
    printf("Y: %Le \n", CurrentGlobal_Y);
    /*if (deta_Angle!=0){
       deta_x= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)+deta_Encoderx*sin(M_PI/2-lastAngle+deta_Angle/2));
       deta_y= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)-deta_Encoderx*cos(M_PI/2-lastAngle+deta_Angle/2));
    } else{
        deta_x=EncoderY*sin(CurrentAngle)+deta_Encoderx*cos(CurrentAngle);
        deta_y=EncoderY*cos(CurrentAngle)-deta_Encoderx*sin(CurrentAngle);
    }*/

    if (fabs(deta_Angle) <=0.00003){
      deta_x=EncoderY*sin(CurrentAngle)+deta_Encoderx*cos(CurrentAngle);
      deta_y=EncoderY*cos(CurrentAngle)-deta_Encoderx*sin(CurrentAngle);

    } else{
      deta_x= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)+(2*((deta_Encoderx/deta_Angle)-Wheel_Middle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)));
      deta_y= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)-(2*((deta_Encoderx/deta_Angle)-Wheel_Middle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)));
    }

    CurrentGlobal_X=CurrentGlobal_X+deta_x;
    CurrentGlobal_Y=CurrentGlobal_Y+deta_y;
    pros::lcd::print(0, "X: %f", CurrentGlobal_X);
    pros::lcd::print(6, "Y: %f", CurrentGlobal_Y);
    //pros::lcd::print(2, "horizontaltracking: %d", horizontaltracking.get_value());
    //pros::lcd::print(5, "lefttracking: %d", lefttracking.get_value());
    //pros::lcd::print(7, "righttracking: %d", righttracking.get_value());
    //pros::lcd::print(4, "A: %f", CurrentAngle);
    lastAngle=CurrentAngle;
    LAST_EncoderR=EncoderR;
    LAST_EncoderL=EncoderL;
    LAST_EncoderX=EncoderX;
    delay(10);
    //caculating the change in X and Y position of the robot

  }

  return 1;
}





double Odometry3rd(){
  CurrentGlobal_X = 17;
  CurrentGlobal_Y = 128;
  //imu.set_heading(140);
  righttracking.reset();
  horizontaltracking.reset();
  lefttracking.reset();
  double lastAngle= 0;
  double LAST_EncoderX=0;
  double Wheel_BackDisBetwwen = 14.45;
  double Wheel_Middle= 5.9;//5.9375// 5.75!!!/6
  double wheeldiameter=2.75;
  double LAST_EncoderR=0;
  double LAST_EncoderL=0;
  while(EnablePositionTrack3rd){
    //update the current angle the robot is facing and caculate the change in angle

    //Caculate change in encoder value and convert them to inches.

    double EncoderR=((righttracking.get_value()/360.00000000000000)*(wheeldiameter*M_PI));
    double EncoderL=((lefttracking.get_value()/360.00000000000000)*(wheeldiameter*M_PI));
    double deta_EncoderR=(EncoderR-LAST_EncoderR);
    double deta_EncoderL =( (EncoderL - LAST_EncoderL));
    double EncoderY= (deta_EncoderL+deta_EncoderR)/2;
    double EncoderX=((horizontaltracking.get_value()/360.000000000000000)*(wheeldiameter*M_PI));
    double deta_Encoderx= (EncoderX-LAST_EncoderX);
    CurrentAngle=(imu.get_heading()*(M_PI/180));
    //pros::lcd::print(7, "deta_EncoderX: %f", deta_Encoderx);
    double deta_Angle = ((deta_EncoderR-deta_EncoderL)/Wheel_BackDisBetwwen);//DIVIDE by distance between the two backwheel.
    //pros::lcd::print(3, "horizontaltracking: %d", horizontaltracking.get_value());
    //pros::lcd::print(4, "righttracking: %d", righttracking.get_value());
    printf("CurrentAngle: %f", CurrentAngle);
    printf("X: %Le \n", CurrentGlobal_X);
    printf("Y: %Le \n", CurrentGlobal_Y);
    /*if (deta_Angle!=0){
       deta_x= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)+deta_Encoderx*sin(M_PI/2-lastAngle+deta_Angle/2));
       deta_y= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)-deta_Encoderx*cos(M_PI/2-lastAngle+deta_Angle/2));
    } else{
        deta_x=EncoderY*sin(CurrentAngle)+deta_Encoderx*cos(CurrentAngle);
        deta_y=EncoderY*cos(CurrentAngle)-deta_Encoderx*sin(CurrentAngle);
    }*/

    if (fabs(deta_Angle) <=0.00003){
      deta_x=EncoderY*sin(CurrentAngle)+deta_Encoderx*cos(CurrentAngle);
      deta_y=EncoderY*cos(CurrentAngle)-deta_Encoderx*sin(CurrentAngle);

    } else{
      deta_x= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)+(2*((deta_Encoderx/deta_Angle)-Wheel_Middle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)));
      deta_y= (((2*EncoderY)/deta_Angle)*sin(deta_Angle/2)*sin(M_PI/2-lastAngle+deta_Angle/2)-(2*((deta_Encoderx/deta_Angle)-Wheel_Middle)*sin(deta_Angle/2)*cos(M_PI/2-lastAngle+deta_Angle/2)));
    }

    CurrentGlobal_X=CurrentGlobal_X+deta_x;
    CurrentGlobal_Y=CurrentGlobal_Y+deta_y;
    pros::lcd::print(0, "X: %f", CurrentGlobal_X);
    pros::lcd::print(6, "Y: %f", CurrentGlobal_Y);
    //pros::lcd::print(2, "horizontaltracking: %d", horizontaltracking.get_value());
    //pros::lcd::print(5, "lefttracking: %d", lefttracking.get_value());
    //pros::lcd::print(7, "righttracking: %d", righttracking.get_value());
    //pros::lcd::print(4, "A: %f", CurrentAngle);
    lastAngle=CurrentAngle;
    LAST_EncoderR=EncoderR;
    LAST_EncoderL=EncoderL;
    LAST_EncoderX=EncoderX;
    delay(10);
    //caculating the change in X and Y position of the robot

  }

  return 1;
}
