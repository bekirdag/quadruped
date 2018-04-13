#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define SLAVE_ADDRESS 0x04 // raspberry pi connection

char number[50];
int state = 0;

int raspi_val;
int mode = 0;

int servoDelay = 0;

String inString = "";

int photocellPin = 0;
int photocellValue = 0;

int micPin = A1;
int micVal = 0;

const int analogIn = A2;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;

float tempC;
int reading;
int tempPin = 3;

const int trigPin = 12;
const int echoPin = 13;
long duration;
int distance;


int fourty_five = 112;
int ninety = fourty_five*2;

int servoCurrentPositions[] = {315,495,335,535,282,430,410,460,335};

int startPositionX[] = {
// 0,  1,  2,  3,  4,  5,  6,  7,  8
  315,495,335,535,400,430,410,460,335
}; 


int startPositionY[] = {
// 0,  1,  2,  3,  4,  5,  6,  7,  8
  startPositionX[0]-ninety,startPositionX[1]-ninety,startPositionX[2]-ninety,startPositionX[3]-ninety,startPositionX[4]-ninety,startPositionX[5]-ninety,startPositionX[6]-ninety,startPositionX[7]-ninety,startPositionX[8]-ninety
}; 

volatile float site_now[4][2];    //real-time coordinates of the end of each leg
volatile float site_expect[4][2]; //expected coordinates of the end of each leg


void moveAbit(int direction) {
  turnAround(-1);
  walk(direction);
}

void wait_reach(int leg)
{
  while (1)
    if (site_now[leg][0] == site_expect[leg][0])
      if (site_now[leg][1] == site_expect[leg][1])
        break;
}

void wait_all_reach(void)
{
  for (int i = 0; i < 4; i++)
    wait_reach(i);
}

void walk(int direction) {
  if(distance<20 && direction<0)
  {
    // moveAbit(direction);
    return;
  }
  newServoValue(1,-100);
  newServoValue(5,-100);
  delay(servoDelay);

  // up
  newServoValue(0,fourty_five*direction);
  newServoValue(2,fourty_five*direction*(-1));
  newServoValue(4,fourty_five*direction*(-1));
  newServoValue(6,fourty_five*direction);
  delay(servoDelay);

  newServoValue(1,0);
  newServoValue(5,0);
  delay(servoDelay);

  newServoValue(8,-100);
  newServoValue(7,-100);
  delay(servoDelay);

  // down
  newServoValue(0,fourty_five*direction*(-1));
  newServoValue(2,fourty_five*direction);
  newServoValue(4,fourty_five*direction);
  newServoValue(6,fourty_five*direction*(-1));
  delay(servoDelay);

  newServoValue(8,0);
  newServoValue(7,0);
  delay(servoDelay);
  
}

void goLay() {
  newServoValue(1,fourty_five*(-2));
  newServoValue(8,fourty_five*(-2));
  newServoValue(5,fourty_five*(-2));
  newServoValue(7,fourty_five*(-2));
}

void goUp() {
  newServoValue(1,0);
  newServoValue(8,0);
  newServoValue(5,0);
  newServoValue(7,0);
}

void setup() { 

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  analogReference(INTERNAL);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);

  delay(100);
  
} 

void standStill() {
  changePos(startPositionX);
}

void swim(int direction) {
  newServoValue(1,-100);
  newServoValue(5,-100);
  delay(servoDelay);

  // up
  newServoValue(0,fourty_five*direction);
  newServoValue(2,fourty_five*direction);
  newServoValue(4,fourty_five*direction*(-1));
  newServoValue(6,fourty_five*direction*(-1));

  delay(servoDelay);

  newServoValue(1,0);
  newServoValue(5,0);

  delay(servoDelay);

  newServoValue(8,-100);
  newServoValue(7,-100);
  delay(servoDelay);

  // down
  newServoValue(0,fourty_five*direction*(-1));
  newServoValue(2,fourty_five*direction*(-1));
  newServoValue(4,fourty_five*direction);
  newServoValue(6,fourty_five*direction);

  delay(servoDelay);


  newServoValue(8,0);
  newServoValue(7,0);
  delay(servoDelay);
}

void turnAround(int direction) {
  newServoValue(1,-100);
  newServoValue(5,-100);
  delay(servoDelay);

  // up
  newServoValue(0,fourty_five*direction);
  newServoValue(2,fourty_five*direction*(-1));
  newServoValue(4,fourty_five*direction);
  newServoValue(6,fourty_five*direction*(-1));
  
  delay(servoDelay);

  newServoValue(1,0);
  newServoValue(5,0);
  delay(servoDelay);

  newServoValue(8,-100);
  newServoValue(7,-100);
  delay(servoDelay);

  // down
  newServoValue(0,fourty_five*direction*(-1));
  newServoValue(2,fourty_five*direction);
  newServoValue(4,fourty_five*direction*(-1));
  newServoValue(6,fourty_five*direction);
  delay(servoDelay);

  newServoValue(8,0);
  newServoValue(7,0);
  delay(servoDelay);
  
}

void changePos(int positions[]) {
  for (int servoNum = 0; servoNum < 8; servoNum++) {
    int servoControl = servoNum;
    servoControl = (servoNum==3) ? 8 : servoNum;
    delay(servoDelay);
    pwm.setPWM(servoControl, 0, positions[servoNum]);
    newServoValue(servoControl,0);
  }
}

void setDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  //delay(1000);
}

void loop() { 
  setDistance();
  //

  /*
  Serial.print("mode: ");
  Serial.print(mode);
  
  photocellValue = analogRead(photocellPin);
  Serial.println("Light value: ");
  Serial.println(photocellValue);

  reading = analogRead(tempPin);
  float voltage = reading * 5.19;
  voltage /= 1024.0;

   // print out the voltage
   Serial.print(voltage); Serial.println(" volts");
  
  float temperatureC = (voltage - 0.5) * 100 ;
  Serial.print(temperatureC); Serial.println(" degrees C");
  delay(1000);
/*
  micVal = analogRead(micPin);
  Serial.println("Volume: ");
  Serial.println (micVal);

 RawValue = analogRead(analogIn);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);
 
 
 Serial.print("Raw Value = " ); // shows pre-scaled value 
 Serial.print(RawValue); 
 Serial.print("\t mV = "); // shows the voltage measured 
 Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t Amps = "); // shows the voltage measured 
 Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
 */
/*


delay(1000);



Serial.println("Raspi val:");
Serial.println(mode);
*/
switch (mode) {
  case 0:
    standStill();
    break;
  case 1:
    walk(-1);
    break;
  case 2:
    walk(1);
    break;
  case 3:
    turnAround(1);
    break;
  case 4:
    turnAround(-1);
    break;
  case 5:
    swim(1);
    break;
  case 6:
    swim(-1);
    break;
  case 8:
    goUp();
    break;
  case 9:
    goLay();
    break;

}

} 

// callback for received data
void receiveData(int byteCount) {
  
  while (Wire.available()) {
    raspi_val = Wire.read();
  }

  inString = (char)raspi_val;

  Serial.print(inString);


  //raspi_val = (char)number.toInt();
  if(inString=="1"){
    mode = 1;
  }

  if(inString=="2"){
    mode = 2;
  }

  if(inString=="0"){
    mode = 0;
  }

  if(inString=="3"){
    mode = 3;
  }

    if(inString=="4"){
    mode = 4;
  }

  if(inString=="5"){
    mode = 5;
  }

  if(inString=="6"){
    mode = 6;
  }

  if(inString=="7"){
    mode = 7;
  }
  
  if(inString=="8"){
    mode = 8;
  }

  if(inString=="9"){
    mode = 9;
  }

  if(inString=="10"){
    mode = 10;
  }

  if(inString=="11"){
    mode = 11;
  }
}  // end while

// callback for sending data
void sendData() {
  Wire.write(number);
}

void newServoValue(int servoNum,int newVal) {
  if(servoCurrentPositions[servoNum]<startPositionX[servoNum]+newVal) {
    for (uint16_t pulselen = servoCurrentPositions[servoNum]; pulselen < startPositionX[servoNum]+newVal; pulselen++) {
      if(startPositionX[servoNum]+newVal<SERVOMAX) {
        servoCurrentPositions[servoNum] = startPositionX[servoNum]+newVal;
        pwm.setPWM(servoNum, 0, pulselen);
          Serial.print(servoNum);
      }
      else{
        Serial.print("bigger!");
        return;  
      }
      
    }  
  }
  else{
    for (uint16_t pulselen = servoCurrentPositions[servoNum]; pulselen > startPositionX[servoNum]-newVal; pulselen--) {
      if(startPositionX[servoNum]-newVal>SERVOMIN) {
        servoCurrentPositions[servoNum] = startPositionX[servoNum]-newVal;
        pwm.setPWM(servoNum, 0, pulselen);
      }
      else{
        Serial.print("smaller!");
        return;  
      }
      
    } 
  }
}











