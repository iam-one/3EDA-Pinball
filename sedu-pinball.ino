#include <Servo.h>

// declare default pin value
const int l_servo_out = 3; // D3
const int r_servo_out = 5; // D5
const int cds_in = A0; // A0
const int l_tact = 4; // D4
const int r_tact = 6; // D6

// define seg pin value
const byte pin_segs[8] = {11, 12, A1, A2, A3, A4, A5, A6};
const byte pin_segDigit[4] = {7, 8, 9, 10};

// define seg value
const byte segNum[10][7] = {
   {1,1,1,1,1,1,0}, // 0
   {0,1,1,0,0,0,0}, // 1
   {1,1,0,1,1,0,1}, // 2
   {1,1,1,1,0,0,1}, // 3
   {0,1,1,0,0,1,1}, // 4
   {1,0,1,1,0,1,1}, // 5
   {1,0,1,1,1,1,1}, // 6
   {1,1,1,0,0,0,0}, // 7
   {1,1,1,1,1,1,1}, // 8
   {1,1,1,1,0,1,1}  // 9
};

Servo l_servo;
Servo r_servo;

boolean is_ready = false;

unsigned long segTime = 0;
unsigned long l_Time = 0;
unsigned long r_Time = 0;

int l_angle = 0;
int r_angle = 0;

int d1 = 0;
int d2 = 0;
int d3 = 0;
int d4 = 0;

int cds = 0;

// setup
void setup() {
  pinMode(l_tact, INPUT_PULLUP);
  pinMode(r_tact, INPUT_PULLUP);
  pinMode(cds_in, INPUT_PULLUP);

  l_servo.attach(l_servo_out);
  r_servo.attach(r_servo_out);

  for(int i=0; i<8; i++){
    pinMode(pin_segs[i], OUTPUT);
  }
  for(int j=0; j<4; j++){
    pinMode(pin_segDigit[j], OUTPUT);
    digitalWrite(pin_segDigit[j], HIGH);
  }

  Serial.begin(9600);
  Serial.println("Serial Init");
}

void loop() {
  // game start with clicking right switch
  if (digitalRead(r_tact) == LOW) is_ready = true;

  while(is_ready) {
    // when ball in hole, time out
    cds = analogRead(cds_in);
    if (cds < 100) is_ready = false;

    // init left servo
    if (digitalRead(l_tact) == LOW){
      l_Time = millis();
      l_angle = 90;
    }
    // init right servo
    if (digitalRead(r_tact) == LOW){
      r_Time = millis();
      r_angle = 90;
    }

    // set left servo
    if (millis() - l_Time < 500){
      l_angle -= 7;
    }

    // set right servo
    if (millis() - r_Time < 500){
      r_angle += 7;
    }

    // move servo
    l_servo.write(l_angle);
    r_servo.write(r_angle);

    // set Game Time
    segTime = millis()/10;
    d1 = segTime%10;
    d2 = (segTime/10)%10;
    d3 = (segTime/100)%10;
    d4 = (segTime/1000)%10;

    // show Game Time in Segment
    segOut(3,d1,0);
    if(segTime>=10) segOut(2,d2,0);
    if(segTime>=100) segOut(1,d3,0);
    if(segTime>=1000) segOut(0,d4,0);

    delay(100); // delay to move servo
  }
  // init segment
  segOut(3,0,0);
  if(segTime>=10) segOut(2,0,0);
  if(segTime>=100) segOut(1,0,0);
  if(segTime>=1000) segOut(0,0,0);
}

// segment clear
void segClear(){
  for(int i=0;i<8;i++){
    digitalWrite(pin_segs[i], LOW);
  }
}

// segment output
void segOut(int d, int value, int dp){
  segClear();
  digitalWrite(pin_segDigit[d], LOW);
  for(int i=0;i<7;i++){
     digitalWrite(pin_segs[i], segNum[value][i]);
  }
  digitalWrite(pin_segs[7], dp);
  delayMicroseconds(1000);
  digitalWrite(pin_segDigit[d], HIGH);
}