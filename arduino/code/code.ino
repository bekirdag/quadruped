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



void setup() { 

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  analogReference(INTERNAL);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  delay(10);
  
} 


void loop() { 
  switch (mode) {
    case 0:
      pwm.setPWM(0, 0, 0);
      pwm.setPWM(1, 0, 0);
      pwm.setPWM(2, 0, 0);
      pwm.setPWM(3, 0, 0);

      pwm.setPWM(4, 0, 0);
      pwm.setPWM(5, 0, 0);
      pwm.setPWM(6, 0, 0);
      pwm.setPWM(7, 0, 0);
      break;
    case 1:
      pwm.setPWM(0, 0, 180);
      pwm.setPWM(1, 0, 180);
      pwm.setPWM(2, 0, 180);
      pwm.setPWM(3, 0, 180);

      pwm.setPWM(4, 0, 180);
      pwm.setPWM(5, 0, 180);
      pwm.setPWM(6, 0, 180);
      pwm.setPWM(7, 0, 180);
      
      break;
    case 2:
      pwm.setPWM(0, 0, 90);
      pwm.setPWM(1, 0, 90);
      pwm.setPWM(2, 0, 90);
      pwm.setPWM(3, 0, 90);

      pwm.setPWM(4, 0, 90);
      pwm.setPWM(5, 0, 90);
      pwm.setPWM(6, 0, 90);
      pwm.setPWM(7, 0, 90);
      
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













