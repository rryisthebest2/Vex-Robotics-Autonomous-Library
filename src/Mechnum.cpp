#include "main.h"


void Mechnum(double power,double strafe, double turnN){
  lfm= power + Strafe + turnN;
	rfm = power - strafe - turnN;
	lbm = power - strafe + turnN;
	rbm= power + strafe- turnN;
}
