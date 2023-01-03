#include "main.h"
void auton(){
//pidStrafe(72,48, 0, 50000,127,"false");
//delay(500000);
//pidStrafe(52.375,11.72917,M_PI,5000, 127, "false");
//delay(50000);
//PureSuit(24, 20, 48, 28, 72, 48, (120*M_PI/180), (90*M_PI/180), 0, 50000, 127, "outtake");
//路线1
//VisionTrack(36,72,0,2000,127,"true");//73
pidMove(-10,0,600,127,"Flip");
Vision("true");
VisionTrack(19,32,CurrentAngle, 5000,127,"true");
//pidStrafe(24,24,((228*M_PI)/180),5000,127,"true");//1600
//TowerMatch(61,45,1000,"true");
PidTowerMatch(24,24,((226*M_PI)/180),5000,127,"true",47,58);
Descore(1500); //900
//First Tower Finish
VisionTrack(48,48,(M_PI/2),5000,127,"outtake");//800
VisionTrack(96,36,(140*M_PI/180),5000,140,"true");
VisionTrack(116,27,((75*M_PI)/180),5000,127,"true");
PidTowerMatch(117,26,((138*M_PI)/180),1500,140,"false",41,53);//36.5 before //1000//900
Descore(2000);
Reset(128,17, 140);
pidMove(-5,0,500,127,"outakeAlot");
//second tower finish

VisionTrack(108,51,(310*M_PI/180),5000,127,"outtake");
VisionTrack(100,74.3,(M_PI/2),5000,140,"true"); //110//74
pidStrafe(125.8,74.3,((90*M_PI)/180),1000,127,"true"); //64.7/74
Descore3(900); //650
pidMove(-10,0,500,127,"false");
//third tower finish
pidStrafe(108,95,((350*M_PI)/180),2000,140,"true");//36.5 before //1000//900
VisionTrack(106,110,((350*M_PI)/180),5000,140,"true");
VisionTrack(116,97,((80*M_PI)/180),5000,127,"true"); //123
PidTowerMatch(120,118,((45*M_PI)/180),1500,127,"false",53,46);
//TowerMatch(61,45,1000,"true");//71,40
DescoreThreeS(5000);//1600
pidMove(-10,0,500,127,"false");
Reset2();
//fourth tower finish
//pidStrafe(105,88,((275*M_PI)/180),5000,127,"outtake");
VisionTrack(88,99,((220*M_PI)/180),5000,127,"outtake");//88/82
//PureSuit(72, 96, 72, 122, 72, 122, 0, 0, 0, 5000, 127, "false");
pidStrafe(73, 117,0,5000,127,"true");//((3*M_PI)/180)
pidStrafe(73, 129,0,800,127, "false"); //126
Descore5(1000);//500
pidMove(-10,0,400,127,"false"); //-10
//fifth tower finish
//pidStrafe(75,113,0,5000,140,"true");//36.5 before //1000//900
VisionTrack(55,120,((270*M_PI)/180),5000,127,"true");//800
VisionTrack(25,109,((235*M_PI)/180),5000,140,"true");
PidTowerMatch(24,120,((317*M_PI)/180),1500,127,"true",52,40);//311/39/63//317,//R:52,L:40;
Reset3();
DescoreThree(5000);//1600
pidMove(-10,0,500,127,"false");
pidStrafe(22,120,((110*M_PI)/180),500,127,"outtake");
//pidMove(-13,0,500,127,"false");
//sixth tower finish

// PureSuit(24, 96, 24, 96, 24, 96,CurrentAngle, ((270*M_PI)/180), ((180*M_PI)/180), 5000, 127, "outtake");
VisionTrack(27,90,(M_PI),5000,127,"outtake");//800
pidStrafe(27,72,((270*M_PI)/180),1500,127,"true");
pidMove(8,0,300,127,"false");
//PureSuit(28, 73, 28, 73, 20, 73, M_PI, ((270*M_PI)/180), ((275*M_PI)/180), 2500, 127, "false");
Descore8(1500);//600//1000
//seventh tower finish
//PureSuit(28, 73, 28, 73, 28, 73, ((270*M_PI)/180), ((170*M_PI)/180), ((93*M_PI)/180), 5000, 127, "outtake");
pidMove(-10,0,500,127,"false");
pidStrafe(CurrentGlobal_X,CurrentGlobal_Y, ((85*M_PI)/180), 1000,100,"outtake");
pidStrafe(60,78.8, ((85*M_PI)/180),2000,127,"true");
pidMove(20,0,2000,100,"true");
//pidMove(45,0,3000,127,"true");
//Vision("true");
//pidMove(30,0,2000,127,"true");
//pidStrafe(67,72,((90*M_PI)/180),2000,80,"true");//73
/*VisionBlue("false",((87*M_PI)/180),2500);
pidMove(25,0,2500,127,"true");*/
//pidStrafe(CurrentGlobal_X+12,CurrentGlobal_Y,((90*M_PI)/180),1000,127,"true");
DescoreMid(5000);//1300
pidMove(-15,0,5000,127,"outtake");
//All Finish, good luck, 神之一手



















/*
//路线1
pidMove(-10,0,600,127,"Flip");
Vision("true");
VisionTrack(19,32,CurrentAngle, 5000,127,"true");
//pidStrafe(24,24,((228*M_PI)/180),5000,127,"true");//1600
//TowerMatch(61,45,1000,"true");
PidTowerMatch(24,24,((226*M_PI)/180),5000,127,"true",47,58);
Descore(1200); //900
//First Tower Finish
VisionTrack(48,48,(M_PI/2),5000,127,"outtake");//800
VisionTrack(96,36,(140*M_PI/180),5000,140,"true");
VisionTrack(118,27,((75*M_PI)/180),5000,127,"true");
PidTowerMatch(120,26,((140*M_PI)/180),1500,140,"false",41,53);//36.5 before //1000//900
Descore(2000);
Reset(60,17, 140);
//second tower finish
//PureSuit(118, 24, 106, 40, 96, 48, (120*M_PI/180), (90*M_PI/180), 0, 5000, 127, "outtake");
//delay(50000);
//PureSuit(96, 72, 115, 72, 126, 72, 0, (90*M_PI/180), (90*M_PI/180), 5000, 127, "true");
//VisionTrack(100,50,(345*M_PI/180),5000,127,"outtake");//800
VisionTrack(105,50,(310*M_PI/180),5000,127,"outtake");
VisionTrack(105,70,(M_PI/2),5000,140,"true"); //110
pidStrafe(120,69.5,((90*M_PI)/180),800,127,"true"); //64.7
pidStrafe(130,69.5,((90*M_PI)/180),600,127,"false"); //64.7
Descore3(900); //650
pidMove(-10,0,500,127,"false");
//third tower finish
pidStrafe(106,95,0,5000,140,"true");//36.5 before //1000//900
VisionTrack(106,110,0,5000,140,"true");
VisionTrack(122,95,((85*M_PI)/180),5000,127,"true"); //123
PidTowerMatch(121,115,((45*M_PI)/180),1500,127,"false",53,46);
//TowerMatch(61,45,1000,"true");//71,40
DescoreThree(5000);//1600
pidMove(-10,0,500,127,"false");
//fourth tower finish
//pidStrafe(105,88,((275*M_PI)/180),5000,127,"outtake");
VisionTrack(92,99,((220*M_PI)/180),5000,127,"outtake");//88/82
//PureSuit(72, 96, 72, 122, 72, 122, 0, 0, 0, 5000, 127, "false");
pidStrafe(64.5, 110,0,5000,127,"true");//((3*M_PI)/180)
pidStrafe(64.5, 125,0,800,127, "false"); //126
Descore5(1000);//500
pidMove(-13,0,400,127,"false"); //-10
//fifth tower finish
//pidStrafe(75,113,0,5000,140,"true");//36.5 before //1000//900
VisionTrack(50,110,((270*M_PI)/180),5000,127,"true");//800
VisionTrack(25,109,((235*M_PI)/180),5000,140,"true");
PidTowerMatch(20,115,((311*M_PI)/180),1500,127,"true",39,63);
DescoreThree(5000);//1600
pidMove(-10,0,500,127,"false");
//sixth tower finish
// PureSuit(24, 96, 24, 96, 24, 96,CurrentAngle, ((270*M_PI)/180), ((180*M_PI)/180), 5000, 127, "outtake");
VisionTrack(24,85,(M_PI),5000,127,"outtake");//800
pidStrafe(19,59,((268*M_PI)/180),1500,127,"true");
pidMove(5,0,300,127,"false");
//PureSuit(28, 73, 28, 73, 20, 73, M_PI, ((270*M_PI)/180), ((275*M_PI)/180), 2500, 127, "false");
Descore5(1000);//600
//seventh tower finish

//PureSuit(28, 73, 28, 73, 28, 73, ((270*M_PI)/180), ((170*M_PI)/180), ((93*M_PI)/180), 5000, 127, "outtake");
pidMove(-10,0,500,127,"false");
pidStrafe(CurrentGlobal_X,CurrentGlobal_Y, ((90*M_PI)/180), 1000,100,"outtake");
VisionTrack(38,60,((90*M_PI)/180),5000,127,"true");//73
pidStrafe(60,60,((90*M_PI)/180),800,80,"true");//73
VisionBlue("false",M_PI/2,1000);
pidStrafe(CurrentGlobal_X+8,CurrentGlobal_Y,((90*M_PI)/180),1000,127,"true");
DescoreMid(5000);//1300
pidMove(-15,0,5000,127,"outtake");
//All Finish, good luck, 神之一手
*/

















}
