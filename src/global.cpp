#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor lfm(19, pros::E_MOTOR_GEARSET_06,true,MOTOR_ENCODER_DEGREES);
pros::Motor lbm(20, pros::E_MOTOR_GEARSET_06,MOTOR_ENCODER_DEGREES);
pros::Motor rfm(4, pros::E_MOTOR_GEARSET_06,true,MOTOR_ENCODER_DEGREES);
pros::Motor rbm(3, pros::E_MOTOR_GEARSET_06,MOTOR_ENCODER_DEGREES);


pros::Motor rightintake(2, pros::E_MOTOR_GEARSET_06,1);
//input port
pros::Motor leftintake(17, pros::E_MOTOR_GEARSET_06,0);
//input port
pros::Motor elevator1(18, pros::E_MOTOR_GEARSET_06,true);//bottom
//input port
pros::Motor elevator2(1, pros::E_MOTOR_GEARSET_06);//Top
//input port
pros::ADIEncoder lefttracking('e','f');
//pin ports

pros::ADIEncoder righttracking('a','b');
pros::ADIEncoder horizontaltracking('g','h');
// pin ports
pros::Imu imu(5);
pros::Optical opticalStoper1(8);
pros::Optical opticalStoper2(14);
pros::Optical optical3(9);
pros::Distance BallControldown(11);
pros::Distance BallControlUp(12);
pros::Distance TowerMatchLeft(16);
pros::Distance TowerMatchRight(10);
pros::Distance VisionDetect(15);
pros::Vision Camera(13,pros::E_VISION_ZERO_TOPLEFT);
int y = 0;
