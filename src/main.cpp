#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();


	//pros::Task Odom (odom);



	  lbm.tare_position();
		rbm.tare_position();


	/*  righttracking.reset();
		lefttracking.reset();
		horizontaltracking.reset();




	imu.reset();
	opticalStoper1.set_led_pwm(25);
	opticalStoper2.set_led_pwm(0);
	optical3.set_led_pwm(10);
	while(imu.is_calibrating()){
		delay(100);
	}

	imu.set_heading(293.5);
	delay(100);
*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {


	/*pros::Task Position_Trakcing(Odometry);
	pros::Task IntakeBall(Ball);
	pros::Task Pace(BallPace);*/
	lfm.set_brake_mode(MOTOR_BRAKE_HOLD);
	rfm.set_brake_mode(MOTOR_BRAKE_HOLD);
	lbm.set_brake_mode(MOTOR_BRAKE_HOLD);
	rbm.set_brake_mode(MOTOR_BRAKE_HOLD);
	elevator1.set_brake_mode(MOTOR_BRAKE_HOLD);
	elevator2.set_brake_mode(MOTOR_BRAKE_HOLD);
	leftintake.set_brake_mode(MOTOR_BRAKE_HOLD);
	rightintake.set_brake_mode(MOTOR_BRAKE_HOLD);
	//elevator2.move_velocity(-600);
	//rightintake.move_velocity(-600);
	//delay(500);
	auton();
}


/**
- start on right side
- turn right and intake ball
- put ball into chamber
- go back to start position
- go to middle line
- turn right
- go forward to middle chamber
- elevator2 balls
- move back a bit
- turn towards top right corner
- go to corner and put ball in
- move back a bit
- turn towards top left corner
- go straight and intake ball at top left chamber
- elevator2 ball
- move back until in line with middle line ball of left side
- turn towards balls
- go forward and intake ball
- turn towards middle chamber
- elevator2 ball
- move back a bit
- turn towards bottom right corner
- move forward and intake ball
- elevator2 ball into bottom left chamber
**/


void opcontrol() {
EnablePositionTrack=false;
EnableIntakeBall=false;
EnablePace=false;
lfm.set_brake_mode(MOTOR_BRAKE_COAST);
rfm.set_brake_mode(MOTOR_BRAKE_COAST);
lbm.set_brake_mode(MOTOR_BRAKE_COAST);
rbm.set_brake_mode(MOTOR_BRAKE_COAST);
pidMove(-20,0,800,80,"Flip");
//int y = 0;
		while (true) {
			int power = master.get_analog(ANALOG_LEFT_Y);
			int turn = master.get_analog(ANALOG_RIGHT_X);
			//int strafe = master.get_analog(ANALOG_LEFT_X);
			int strafe = master.get_analog(ANALOG_LEFT_X);
			//int left = (power + turn) ;
			//int right =(power - turn) ;
			int velocityleftf= power + strafe + turn;
			int velocityrightf = - power + strafe + turn;
			int velocityleftb = - power + strafe - turn;
			int velocityrightb= power + strafe - turn;


					lfm.move(velocityleftf);
				  rfm.move(velocityrightf);
				  lbm.move(velocityleftb);
				  rbm.move(velocityrightb);


///////////////////////////////////////////////////////////////
		if(master.get_digital(DIGITAL_L2)==true){
			//intake elevator1
			elevator1.move_velocity(600);
			elevator2.move_velocity(600);
			y = 1;
		}

		else if(master.get_digital(DIGITAL_R2)==true){
			//extake elevator1
			elevator1.move_velocity(-600);
			elevator2.move_velocity(-600);
			y = 1;
		}
		else{
			if(y==0){
			elevator1.move_velocity(0);
			elevator1.set_brake_mode(MOTOR_BRAKE_HOLD);
			elevator2.move_velocity(0);
			elevator2.set_brake_mode(MOTOR_BRAKE_HOLD);
		}
			y = 0;
		}
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
		if(master.get_digital(DIGITAL_A)==true){
			//intake slow
			leftintake.move_velocity(100);
			rightintake.move_velocity(100);
		}

		else if(master.get_digital(DIGITAL_Y)==true){
			//extake slow
			leftintake.move_velocity(-100);
			rightintake.move_velocity(-100);
		}

		else if(master.get_digital(DIGITAL_L1)==true){
			//intake fast
			leftintake.move(127);
			rightintake.move(127);
			if(master.get_digital(DIGITAL_L2)){
				elevator1.move_velocity(600);
				elevator2.move_velocity(600);
			}
			else{
			elevator1.move_velocity(600);

		}
			y = 1;
		}
		else if(master.get_digital(DIGITAL_R1)==true){
		//outtake fast
		leftintake.move_velocity(-600);
		rightintake.move_velocity(-600);

		y = 1;
		if(master.get_digital(DIGITAL_R2)){
			elevator1.move_velocity(-600);
			elevator2.move_velocity(-600);
		}
		else{
		elevator1.move_velocity(-500);

	}
		}
		else{
			leftintake.move_velocity(0);
      rightintake.move_velocity(0);

			leftintake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			rightintake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

			if(y == 0){
			elevator1.move_velocity(0);
			elevator1.set_brake_mode(MOTOR_BRAKE_HOLD);
				elevator2.move_velocity(0);
				elevator2.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
			y=0;
		}

/////////////////////////////////////////////////////////////////////



		if(master.get_digital(DIGITAL_UP)==true){
			straight(50);
		}

		if(master.get_digital(DIGITAL_DOWN)==true){
			straight(-50);
		}

		if(master.get_digital(DIGITAL_RIGHT)==true){

		}

		if(master.get_digital(DIGITAL_LEFT)==true){

		}


	}
}
