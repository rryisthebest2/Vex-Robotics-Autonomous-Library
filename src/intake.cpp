#include"main.h"

void intake(int velocity,int elevatorvel){
  rightintake.move_velocity(velocity);
  leftintake.move_velocity(velocity);
  elevator1.move_velocity(elevatorvel);
  elevator2.move_velocity(elevatorvel);

}
