#include "main.h"
bool EnablePace=true;
int Shoot1=0;
int Shoot2=0;
int Arm=0;
int BallPace(){
  int Position1= BallControlUp.get();
  int Position2= BallControldown.get();
  while(EnablePace){
      Position1= BallControlUp.get();
      Position2= BallControldown.get();
      if(Position1<100 && Position2<100){
        Shoot1=0;
        Arm=127;
        Shoot2=127;
      }
      if(Position1>100 && Position2<100){
        Shoot1=127;
        Arm=127;
        Shoot2=127;
      }
      if(Position1<100 && Position2>100){
        Shoot1=127;
        Arm=127;
        Shoot2=127;
      }
      if(Position1>100 && Position2>100){
        Shoot1=127;
        Arm=127;
        Shoot2=127;
      }

      delay(10);
  }
  return 1;
}
