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

int servoDelay = 120;

String inString = "";

int photocellPin = 0;
int photocellValue = 0;

int micPin = A1;
int micVal = 0;

float tempC;
int reading;
int tempPin = 3;

const int trigPin = 9;
const int echoPin = 8;
long duration;
int distance;


int fourty_five = 112;
int ninety = fourty_five*2;
                             // 0,  1,  2,  3,  4,  5,  6,  7,  8
int servoCurrentPositions[] = {SERVOMIN,SERVOMAX,SERVOMIN,SERVOMAX,SERVOMIN,SERVOMAX,SERVOMIN,SERVOMAX};

int startPositionX[] = {
// 0,  1,  2,  3,  4,  5,  6,  7,  8
  SERVOMIN+ninety,
  SERVOMAX-ninety,
  SERVOMIN+ninety,
  SERVOMAX-ninety,
  SERVOMIN,
  SERVOMAX,
  SERVOMIN,
  SERVOMAX
}; 


int startPositionY[] = {
// 0,  1,  2,  3,  4,  5,  6,  7,  8
  SERVOMIN+ninety,
  SERVOMAX-ninety,
  SERVOMIN+ninety,
  SERVOMAX-ninety,
  SERVOMAX,
  SERVOMIN,
  SERVOMAX,
  SERVOMIN
}; 

int servoDir[4] = {1,-1,1,-1};
int move_dir = 0;

void move_body_backwards() {

  if(distance<10) {
    return 0;
  }

  pwm.setPWM(4, 0, SERVOMAX);
  pwm.setPWM(6, 0, SERVOMAX);
  
  delay(servoDelay);
  
  pwm.setPWM(0, 0, SERVOMIN);
  pwm.setPWM(1, 0, SERVOMAX-ninety);
  pwm.setPWM(2, 0, SERVOMIN+ninety);
  pwm.setPWM(3, 0, SERVOMAX);
  
  delay(servoDelay);
  
  pwm.setPWM(4, 0, SERVOMIN);
  pwm.setPWM(6, 0, SERVOMIN);
  pwm.setPWM(5, 0, SERVOMIN);
  pwm.setPWM(7, 0, SERVOMIN);
  
  delay(servoDelay);
  
  pwm.setPWM(0, 0, SERVOMIN+ninety);
  pwm.setPWM(1, 0, SERVOMAX);
  pwm.setPWM(2, 0, SERVOMIN);
  pwm.setPWM(3, 0, SERVOMAX-ninety);
  
  delay(servoDelay);
  
  pwm.setPWM(5, 0, SERVOMAX);
  pwm.setPWM(7, 0, SERVOMAX);


}

void move_body_forwards() {
  
  pwm.setPWM(4, 0, SERVOMAX);
  pwm.setPWM(6, 0, SERVOMAX);
  
  delay(servoDelay);
  
  pwm.setPWM(0, 0, SERVOMIN+ninety);
  pwm.setPWM(1, 0, SERVOMAX);
  pwm.setPWM(2, 0, SERVOMIN);
  pwm.setPWM(3, 0, SERVOMAX-ninety);
  
  delay(servoDelay);
  
  pwm.setPWM(4, 0, SERVOMIN);
  pwm.setPWM(6, 0, SERVOMIN);
  pwm.setPWM(5, 0, SERVOMIN);
  pwm.setPWM(7, 0, SERVOMIN);
  
  delay(servoDelay);
  
  pwm.setPWM(0, 0, SERVOMIN);
  pwm.setPWM(1, 0, SERVOMAX-ninety);
  pwm.setPWM(2, 0, SERVOMIN+ninety);
  pwm.setPWM(3, 0, SERVOMAX);
  
  delay(servoDelay);
  
  pwm.setPWM(5, 0, SERVOMAX);
  pwm.setPWM(7, 0, SERVOMAX);
}

void side_walk_backwards() {
  
  pwm.setPWM(4, 0, SERVOMAX);
  pwm.setPWM(6, 0, SERVOMAX);
  
  delay(servoDelay);
  pwm.setPWM(0, 0, SERVOMIN+ninety);
  pwm.setPWM(1, 0, SERVOMAX-ninety);
  pwm.setPWM(2, 0, SERVOMAX);
  pwm.setPWM(3, 0, SERVOMIN);  
  
  delay(servoDelay);
  
  pwm.setPWM(4, 0, SERVOMIN);
  pwm.setPWM(6, 0, SERVOMIN);
  pwm.setPWM(5, 0, SERVOMIN);
  pwm.setPWM(7, 0, SERVOMIN);
  
  delay(servoDelay);
  
  pwm.setPWM(0, 0, SERVOMAX);
  pwm.setPWM(1, 0, SERVOMIN);
  pwm.setPWM(2, 0, SERVOMIN+ninety);
  pwm.setPWM(3, 0, SERVOMAX-ninety);
  
  delay(servoDelay);
  
  pwm.setPWM(5, 0, SERVOMAX);
  pwm.setPWM(7, 0, SERVOMAX);
}

void side_walk_forwards() {
  
  pwm.setPWM(4, 0, SERVOMAX);
  pwm.setPWM(6, 0, SERVOMAX);
  
  delay(servoDelay);
  
  pwm.setPWM(0, 0, SERVOMAX);
  pwm.setPWM(1, 0, SERVOMIN);
  pwm.setPWM(2, 0, SERVOMIN+ninety);
  pwm.setPWM(3, 0, SERVOMAX-ninety);
  
  delay(servoDelay);
  
  pwm.setPWM(4, 0, SERVOMIN);
  pwm.setPWM(6, 0, SERVOMIN);
  pwm.setPWM(5, 0, SERVOMIN);
  pwm.setPWM(7, 0, SERVOMIN);
  
  delay(servoDelay);
  
  pwm.setPWM(0, 0, SERVOMIN+ninety);
  pwm.setPWM(1, 0, SERVOMAX-ninety);
  pwm.setPWM(2, 0, SERVOMAX);
  pwm.setPWM(3, 0, SERVOMIN);
  
  delay(servoDelay);
  
  pwm.setPWM(5, 0, SERVOMAX);
  pwm.setPWM(7, 0, SERVOMAX);
}

void turn_left(int degree=ninety) {
  
  pwm.setPWM(4, 0, SERVOMAX);
  pwm.setPWM(6, 0, SERVOMAX);
  
  delay(servoDelay);
  
  pwm.setPWM(0, 0, SERVOMAX);
  pwm.setPWM(1, 0, SERVOMAX-ninety);
  pwm.setPWM(2, 0, SERVOMAX);
  pwm.setPWM(3, 0, SERVOMAX-ninety);
  
  delay(servoDelay);
  
  pwm.setPWM(4, 0, SERVOMIN);
  pwm.setPWM(6, 0, SERVOMIN);
  pwm.setPWM(5, 0, SERVOMIN);
  pwm.setPWM(7, 0, SERVOMIN);
  
  delay(servoDelay);

  pwm.setPWM(0, 0, SERVOMIN+ninety);
  pwm.setPWM(1, 0, SERVOMAX);
  pwm.setPWM(2, 0, SERVOMIN+ninety);
  pwm.setPWM(3, 0, SERVOMAX);
  
  
  delay(servoDelay);
  
  pwm.setPWM(5, 0, SERVOMAX);
  pwm.setPWM(7, 0, SERVOMAX);
}

void turn_right(int degree=ninety) {
  
  pwm.setPWM(4, 0, SERVOMAX);
  pwm.setPWM(6, 0, SERVOMAX);
  
  delay(servoDelay);
  
  pwm.setPWM(0, 0, SERVOMIN+ninety);
  pwm.setPWM(1, 0, SERVOMAX);
  pwm.setPWM(2, 0, SERVOMIN+ninety);
  pwm.setPWM(3, 0, SERVOMAX);
  
  delay(servoDelay);
  
  pwm.setPWM(4, 0, SERVOMIN);
  pwm.setPWM(6, 0, SERVOMIN);
  pwm.setPWM(5, 0, SERVOMIN);
  pwm.setPWM(7, 0, SERVOMIN);
  
  delay(servoDelay);

  pwm.setPWM(0, 0, SERVOMAX);
  pwm.setPWM(1, 0, SERVOMAX-ninety);
  pwm.setPWM(2, 0, SERVOMAX);
  pwm.setPWM(3, 0, SERVOMAX-ninety);
  
  delay(servoDelay);
  
  pwm.setPWM(5, 0, SERVOMAX);
  pwm.setPWM(7, 0, SERVOMAX);
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
    //newServoValue(servoControl,0);
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
  //sendData();
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
      move_body_forwards();
      break;
    case 2:
      move_body_backwards();
      break;
    case 3:
      side_walk_forwards();
      break;
    case 4:
      side_walk_backwards();
      break;
    case 5:
      turn_left();
      break;
    case 6:
      turn_right();
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
    case 10:
      turn_left(1);
      move_dir = 0;
      break;
    case 11:
      turn_right(1);
      move_dir = 0;
      break;
    case 12:
      look_at(150);
      break;
    case 13:
      look_at(600);
      break;
    case 14:
      look_at(375);
      break;
    case 15:
      look_at(400);
      break;
      
  }
  
} 

void look_at(int where) {
  pwm.setPWM(8, 0, where);
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

  if(inString=="a"){
    mode = 10;
  }

  if(inString=="b"){
    mode = 11;
  }

  if(inString=="c"){
    mode = 12;
  }

  if(inString=="d"){
    mode = 13;
  }

  if(inString=="e"){
    mode = 14;
  }

  if(inString=="f"){
    mode = 15;
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











