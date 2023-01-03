#include "main.h"
void straight(double velocity){
  lfm.move(velocity);
  rfm.move(velocity);
  lbm.move(velocity);
  rbm.move(velocity);
}
void strafe(double velocity, int direction){
  //right is 1, left is -1
  velocity = velocity * direction;
  lfm.move(velocity);
  rfm.move(-velocity);
  lbm.move(-velocity);
  rbm.move(velocity);
}
void stopbrake(){
  lfm.move_velocity(0);
  rfm.move_velocity(0);
  lbm.move_velocity(0);
  rbm.move_velocity(0);
  lfm.set_brake_mode(MOTOR_BRAKE_BRAKE);
  rfm.set_brake_mode(MOTOR_BRAKE_BRAKE);
  rbm.set_brake_mode(MOTOR_BRAKE_BRAKE);
  lbm.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void drive(double velocityL, double velocityR){
  lfm.move_velocity(velocityL);
  rfm.move_velocity(velocityR);
  lbm.move_velocity(velocityL);
  rbm.move_velocity(velocityR);
}


void stophold(){
  lfm.move_velocity(0);
  rfm.move_velocity(0);
  lbm.move_velocity(0);
  rbm.move_velocity(0);
  lfm.set_brake_mode(MOTOR_BRAKE_HOLD);
  rfm.set_brake_mode(MOTOR_BRAKE_HOLD);
  rbm.set_brake_mode(MOTOR_BRAKE_HOLD);
  lbm.set_brake_mode(MOTOR_BRAKE_HOLD);
}



void stopcoast(){
  lfm.move_velocity(0);
  rfm.move_velocity(0);
  lbm.move_velocity(0);
  rbm.move_velocity(0);
  lfm.set_brake_mode(MOTOR_BRAKE_COAST);
  rfm.set_brake_mode(MOTOR_BRAKE_COAST);
  rbm.set_brake_mode(MOTOR_BRAKE_COAST);
  lbm.set_brake_mode(MOTOR_BRAKE_COAST);
}


void right(double velocityR){
  lfm.move(velocityR);
  rfm.move(-velocityR);
  lbm.move(velocityR);
  rbm.move(-velocityR);
}
void left(double velocityL){
  lfm.move(-velocityL);
  rfm.move(velocityL);
  lbm.move(-velocityL);
  rbm.move(velocityL);
}
