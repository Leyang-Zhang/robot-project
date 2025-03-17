#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRCS.h>

//left motor is negative!!!!!!
#define CPI 40.49

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P2_0);
DigitalEncoder left_encoder(FEHIO::P0_0);
FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHMotor left_motor(FEHMotor::Motor3,9.0);

void resetcounts(){
right_encoder.ResetCounts();
left_encoder.ResetCounts();
}

void move_forward(int percent, int counts) //using encoders
void move_forward(int percent, int inches) //using encoders
{
    int counts = inches*40.49;
resetcounts();
//Reset encoder counts
right_encoder.ResetCounts();
@@ -45,8 +46,8 @@

void turnright(int speed){
resetcounts();
    int counts = 255;  //26- DEFAULT
    right_motor.SetPercent(-speed);
    int counts = 260;  //260 DEFAULT
    right_motor.SetPercent(-speed);  //both negative
left_motor.SetPercent(-speed);
while((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts){}
right_motor.Stop();
@@ -56,7 +57,7 @@
void turnleft(int speed){
resetcounts();
int counts = 260;   //260 DEFAULT
    right_motor.SetPercent(speed);
    right_motor.SetPercent(speed);   // both positive
left_motor.SetPercent(speed);
while((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts){}
right_motor.Stop();
@@ -93,7 +94,14 @@
Sleep(0.5);
}


void moveindef(int power){
    right_motor.SetPercent(power);
    left_motor.SetPercent(-power);
}
void stop(){
    right_motor.Stop();
    left_motor.Stop();
}
/*
   int lever;
   RPS.InitializeTouchMenu("0800A1KDN");
@@ -105,7 +113,22 @@*/

int main(void)
{
    int ds = distanceSensor.Value();
    moveindef(25);
    while(distanceSensor.Value()){}
    stop();
    Sleep(0.5);
    turnright(25);
    Sleep(0.5);
    moveindef(25);
    while(distanceSensor.Value()){}
    stop();
    Sleep(0.5);
    turnleft(25);
    Sleep(0.5);
    moveindef(25);
    while(distanceSensor.Value()){}
    stop();


}

//STUFF
AnalogInputPin cds(FEHIO::P3_0);

void cdstest() //prints value of cds cell to screen
{
    while()
    {
    LCD.Clear(BLACK);
    LCD.WriteLine(cds.Value());
    Sleep(1.0);
    }
}


