// declare pin value
int l_servo = 6; // D3
int r_servo = 8; // D5
int ir_in = 5; // D2
int ir_out = 19; // A0
int l_tact = 7; // D4
int r_tact = 9; // D6

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


// define seg pin value
byte pin_segs[8] = {}; // a, b, c, d, e, f, g, dp
byte pin_segDigit[4] = {}; // d1, d2, d3, d4

void setup() { // setup
  for(int i=0; i<8; i++){
    pinMode(segPin[i], OUTPUT);
  }
  for(int j=0; j<4; j++){
    pinMode(digitPin[j], OUTPUT);
    digitalWrite(digitPin[j], HIGH);
  }
}

void loop() {
}

void segClear(){ // segment clear
  for(int i=0;i<8;i++){
    digitalWrite(segPin[i], LOW);        
  }
}

void segOut(int d, int value, int dp){ // segment output
  segClear();
  digitalWrite(pin_segDigit[d], LOW); 
  for(int i=0;i<7;i++){
     digitalWrite(segPin[i], segValue[value][i]);        
  }
  digitalWrite(segPin[7], dp);
  delayMicroseconds(1000);
  digitalWrite(pin_segDigit[d], HIGH); 
}
