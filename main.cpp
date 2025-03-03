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

void move_forward(int percent, int inches) //using encoders
{
    int counts = inches*40.49;
    resetcounts();
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts){
        LCD.Clear(BLACK);
        LCD.WriteLine(left_encoder.Counts());
        LCD.WriteLine(right_encoder.Counts());
        Sleep(.01);
    }
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
//40.49 counts per inch

void turnright(int speed){
    resetcounts();
    int counts = 260;  //260 DEFAULT
    right_motor.SetPercent(-speed);  //both negative
    left_motor.SetPercent(-speed);
    while((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts){}
    right_motor.Stop();
    left_motor.Stop();
}

void turnleft(int speed){
    resetcounts();
    int counts = 260;   //260 DEFAULT
    right_motor.SetPercent(speed);   // both positive
    left_motor.SetPercent(speed);
    while((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts){}
    right_motor.Stop();
    left_motor.Stop();
}

void mile1a(){
    move_forward(35, 1186); //see function
}

void encoderResults(){
    Sleep(2.0);
    LCD.Clear(BLACK);
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
}

void mile1b(){
    move_forward(55, 950);
    Sleep(1.0);
    turnright(23);
    turnright(23);
    Sleep(1.0);
    move_forward(25, 1100);
}

void touchstart( const char* blah ){
    float x, y; 
    LCD.Clear(BLACK);
    LCD.WriteLine( blah );
    LCD.ClearBuffer();
    while(!LCD.Touch(&x,&y)) {};
    while(LCD.Touch(&x,&y)) {};
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
    lever = RPS.GetLever();
    */
  // RCS.InitializeTouchMenu("0800A1KDN");
DigitalInputPin distanceSensor(FEHIO::P2_1);


int main(void)
{
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

