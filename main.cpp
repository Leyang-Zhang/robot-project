#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRCS.h>

//cds values
//RED = Value = 0.200
//BLUE = Value = 0.500
//NONE = Value>2.1

//left motor is negative!!!!!!
#define CPI 40.49

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P2_0);
DigitalEncoder left_encoder(FEHIO::P0_0);
FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHMotor left_motor(FEHMotor::Motor3,9.0);
AnalogInputPin cds(FEHIO :: P1_0);



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
    }
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
//40.49 counts per inch

void turnright(int speed, int counts){
    resetcounts();
    int counts1 = 260 + counts;  //260 DEFAULT
    right_motor.SetPercent(-speed);  //both negative
    left_motor.SetPercent(-speed);
    while((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts1){}
    right_motor.Stop();
    left_motor.Stop();
}

void turnleft(int speed, int counts){
    resetcounts();
    int counts1 = 260 + counts;   //260 DEFAULT
    right_motor.SetPercent(speed);   // both positive
    left_motor.SetPercent(speed);
    while((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts1){}
    right_motor.Stop();
    left_motor.Stop();
}

void encoderResults(){
    Sleep(2.0);
    LCD.Clear(BLACK);
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
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

int checkcolor(){ // 2 if red,1 if blue, 0 if no light
    LCD.Clear();
    while(1){
        if (cds.Value()<0.8 && cds.Value()>0.38) //blue
        {
            LCD.SetFontColor(BLUE);
            LCD.FillRectangle(0,0,1000,1000);
            return 1;
            break;
        }
        if (cds.Value()<0.38) //red
        {
            LCD.SetFontColor(RED);
            LCD.FillRectangle(0,0,1000,1000);
            return 2;
            break;
        }
        if (cds.Value()>1.4) // no light
        { 
            LCD.Clear();
            return 0;
        }
        
    }
}

void start()
{
    LCD.Clear();
    //on start light
    //wait for light
    LCD.WriteLine("Waiting for light");
    checkcolor();
    while(checkcolor() == 0)
    {
        //nothing
    }
    LCD.Clear(BLACK);
}

void RedButton()
{

    turnright(20, 0);
    move_forward(20, 4);
    turnleft(20, 0);
    move_forward(20, 6);
    move_forward(-20, 10);
    
}

void BlueButton()
{

    turnleft(20, 0);
    move_forward(20, 4);
    turnright(20, 0);
    move_forward(20, 6);
    move_forward(-20, 10);
    
}

void mile2()
{
    start();
    //align with wall
    move_forward(40, 5); //5 in
    Sleep(0.3);
    turnright(20, 0);
    Sleep(0.3);

    // run into wall
    move_forward(20, 8);
    //back up from wall
    move_forward(-15, 4);
    Sleep(0.3);
    turnleft(25, -7);
    //go up ramp
    move_forward(40,33); //35 in
    Sleep(0.3);

    //back up into wall to align
    turnleft(25, -7);
    Sleep(0.3);
    moveindef(-33);
    Sleep(1.0);
    stop();
    //go to humidifier buttons light
    move_forward(25, 19);
    Sleep(0.3);
    while(checkcolor() == 0){}
    checkcolor();
    Sleep(0.5);
    if(checkcolor() == 2) //if red
    {
    Sleep(0.5);
    RedButton();
    }
    else if(checkcolor() == 1)//if blue
    {
        Sleep(0.5);
        BlueButton();
        turnleft(20, 0);
        turnleft(20, 0);
        moveindef(25);
        Sleep(5.0);
        move_forward(-20,5);
        turnright(20, 10);
        moveindef(40);
    }
    

}
void startUpRamp(){
    start();
    //align with wall
    move_forward(40, 5); //5 in
    Sleep(0.3);
    turnright(20, 0);
    Sleep(0.3);

    // run into wall
    move_forward(20, 8);
    //back up from wall
    move_forward(-15, 4);
    Sleep(0.3);
    turnleft(25, -7);
    //go up ramp
    move_forward(40,33); //35 in
    Sleep(0.3);
}
int main(void)
{
  mile2();  
    
    
}

