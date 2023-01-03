#include "main.h"
bool EnableIntakeBall=true;
int IntakeP=0;
int Roller1=0;
int Roller2=0;
int Ball(){
  int Slot1= BallControlUp.get();
  int Slot2= BallControldown.get();
  int Slot3= VisionDetect.get();
  while(EnableIntakeBall){
    if(Slot1>70 || Slot2>70 || Slot3>70){
      Slot1= BallControlUp.get();
      Slot2= BallControldown.get();
      Slot3= VisionDetect.get();
      if(Slot1>70){
        if(Slot2<100){
          IntakeP=127;
          Roller1=127;
          Roller2=127;
        }else{
          IntakeP=127;
          Roller1=127;
          Roller2=0;

      }
    }
      if(Slot1<70){
        if(Slot2>70){
          IntakeP=127;
          Roller1=127;
          Roller2=0;
        }
      }
      if(Slot1<70 && Slot2<70){
        if(Slot3>70){
          IntakeP=127;
          Roller1=0;
          Roller2=0;
        }
      }

      if(Slot1>70 && Slot2>70){
        if(Slot3<70){
          IntakeP=127;
          Roller1=127;
          Roller2=127;
        }
      }

      if(Slot2<70 && Slot3<70){
        if(Slot1>70){
          IntakeP=127;
          Roller1=127;
          Roller2=127;
        }
      }

      if(Slot1<70){
        if(Slot2>70 && Slot3 >70){
          IntakeP=127;
          Roller1=127;
          Roller2=0;
        }
      }
    }
  Slot1= BallControlUp.get();
  Slot2= BallControldown.get();
  Slot3= VisionDetect.get();
  delay(10);
  IntakeP=10;
  Roller1=0;
  Roller2=0;
  }
  return 1;
}
