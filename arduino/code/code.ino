#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define SLAVE_ADDRESS 0x04 // raspberry pi connection

char coming_number[50];
int state = 0;

int raspi_val;
int mode = 0;

int servoDelay = 100;

String inString = "";

int photocellPin = 0;
int photocellValue = 0;

int micPin = A1;
int micVal = 0;

float tempC;
int reading;
int tempPin = 3;

const int trigPin = 6;
const int echoPin = 5;
long duration;
int distance;


int fourty_five = 112;
int ninety = fourty_five*2;
                             // 0,  1,  2,  3,  4,  5,  6,  7,  8
int servoCurrentPositions[] = {SERVOMIN,SERVOMAX,SERVOMIN,SERVOMAX,SERVOMAX,SERVOMIN,SERVOMAX,SERVOMIN};

int startPositionX[] = {
// 0,  1,  2,  3,  4,  5,  6,  7,  8
  SERVOMIN,SERVOMAX,SERVOMIN,SERVOMAX,SERVOMAX,SERVOMIN,SERVOMAX,SERVOMIN
}; 


int startPositionY[] = {
// 0,  1,  2,  3,  4,  5,  6,  7,  8
    SERVOMAX,SERVOMIN,SERVOMAX,SERVOMIN,SERVOMIN,SERVOMAX,SERVOMIN,SERVOMAX
}; 

int servoDir[4] = {1,1,-1,-1};
int move_dir = 0;

void move_body(int servoData[]) {

  if(mode==1 && distance<40){
    return;  
  }
  int legOrder[4] = {1,5,8,7};

  newServoValue(legOrder[0],-100);
  newServoValue(legOrder[1],-100);
  delay(servoDelay);

  // up
  newServoValue(0,fourty_five*servoData[0]);
  newServoValue(2,fourty_five*servoData[1]);
  newServoValue(4,fourty_five*servoData[2]);
  newServoValue(6,fourty_five*servoData[3]);
  delay(servoDelay);

  newServoValue(legOrder[0],0);
  newServoValue(legOrder[1],0);
  delay(servoDelay);

  newServoValue(legOrder[2],-100);
  newServoValue(legOrder[3],-100);
  delay(servoDelay);

  // down
  newServoValue(0,fourty_five*servoData[0]*(-1));
  newServoValue(2,fourty_five*servoData[1]*(-1));
  newServoValue(4,fourty_five*servoData[2]*(-1));
  newServoValue(6,fourty_five*servoData[3]*(-1));
  delay(servoDelay);

  newServoValue(legOrder[2],0);
  newServoValue(legOrder[3],0);
  delay(servoDelay);
  
}

void goLay() {
  newServoValue(1,ninety*(-1));
  newServoValue(8,ninety*(-1));
  newServoValue(5,ninety*(-1));
  newServoValue(7,ninety*(-1));
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

  delay(10);
  
} 

void standStill(int axis) {
  if(axis>0){
    changePos(startPositionX);  
  }
  else
  {
    changePos(startPositionY);  
  }
  
}

void changePos(int positions[]) {
  for (int servoNum = 0; servoNum < 8; servoNum++) {
    int servoControl = servoNum;
    //servoControl = (servoNum==3) ? 8 : servoNum;
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
  sendData();
/*
  photocellValue = analogRead(photocellPin);
  Serial.println("Light value: ");
  Serial.println(photocellValue);

  reading = analogRead(tempPin);
  float voltage = reading * 5.19;
  voltage /= 1024.0;
  
  float temperatureC = (voltage - 0.5) * 100 ;
  Serial.print(temperatureC); Serial.println(" degrees C");
  delay(1000);

  micVal = analogRead(micPin);
  Serial.println("Volume: ");
  Serial.println (micVal);

 RawValue = analogRead(analogIn);
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);
*/
  
  switch (mode) {
    case 0:
    move_dir = 0;
      standStill(1);
    return;
      break;
    case 1:
      servoDir[0] = 1;
      servoDir[1] = 1;
      servoDir[2] = -1;
      servoDir[3] = -1;
      move_dir = 1;
      break;
    case 2:
      servoDir[0] = 1;
      servoDir[1] = -1;
      servoDir[2] = 1;
      servoDir[3] = -1;
      move_dir = 1;
      break;
    case 3:
      servoDir[0] = 1;
      servoDir[1] = -1;
      servoDir[2] = -1;
      servoDir[3] = 1;
      move_dir = 1;
      break;
    case 4:
      servoDir[0] = -1;
      servoDir[1] = -1;
      servoDir[2] = 1;
      servoDir[3] = -1;
      move_dir = 1;
      break;
    case 5:
      servoDir[0] = -1;
      servoDir[1] = 1;
      servoDir[2] = -1;
      servoDir[3] = 1;
      move_dir = 1;
      break;
    case 6:
      servoDir[0] = -1;
      servoDir[1] = 1;
      servoDir[2] = 1;
      servoDir[3] = -1;
      move_dir = 1;
      break;
    case 7:
      standStill(0);
      move_dir = 0;
      break;
    case 8:
      goUp();
      move_dir = 0;
      break;
    case 9:
      goLay();
    move_dir = 0;
      break;
  }
  if(move_dir > 0) {
    move_body(servoDir);
  }
  
} 

// callback for received data
void receiveData(int byteCount) {
  while (Wire.available()) {
    raspi_val = Wire.read();
  }
  
  inString = (char)raspi_val;
  Serial.print(inString);
  if(inString=="0"){
    mode = 0;
  }
  
  if(inString=="1"){
    mode = 1;
  }

  if(inString=="2"){
    mode = 2;
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
  Wire.write(distance);
  //delay(1000);
}

void newServoValue(int servoNum,int newVal) {
    if((startPositionX[servoNum]+newVal<SERVOMAX) && startPositionX[servoNum]-newVal>SERVOMIN) {
      servoCurrentPositions[servoNum] = startPositionX[servoNum]+newVal;
      pwm.setPWM(servoNum, 0, servoCurrentPositions[servoNum]);
    }
    else{
      Serial.print("bigger or smaller!");
      return;  
    }
}











