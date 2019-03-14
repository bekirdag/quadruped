#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>
#include <string.h>
#include <ctype.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);



Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define SLAVE_ADDRESS 0x04 // raspberry pi connection

int state = 0;
int raspi_val;
int mode = 0;
int servoDelay = 150;
String inString = "";

const int trigPin = 8;
const int echoPin = 9;
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

void setup() { 
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);

  delay(10);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // display oled
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); // clearing the display
  display.setTextColor(WHITE); //setting the color
  display.setTextSize(1); //set the font size
  display.setCursor(5,0); //set the cursor coordinates
  display.print("initializing");
  display.display();
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
  distance = (duration/2) / 29.1;

      // print time
  display.clearDisplay();
  display.setTextColor(WHITE); //setting the color
  display.setTextSize(1); //set the font size
  display.setCursor(5,0); //set the cursor coordinates

  display.print("Distance: ");
  display.print(distance);
  display.print("cm");
  display.display();
}

void loop() { 
  setDistance();

  
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

      move_dir = 0;
      break;
    case 9:

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
      look_at(200);
      break;
    case 13:
      look_at(300);
      break;
    case 14:
      look_at(400);
      break;
    case 15:
      look_at(500);
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











