// declare default pin value
const int l_servo = 6; // D3
const int r_servo = 8; // D5
const int cds_in = 19; // A0
const int l_tact = 7; // D4
const int r_tact = 9; // D6

// define seg pin value
const byte pin_segs[8] = {14, 15, 20, 21, 22, 23, 24, 25}; // D11 (a), D12 (b), A1 (c), A2 (d), A3 (e), A4 (f), A5 (g), A6 (dp)
const byte pin_segDigit[4] = {10, 11, 12, 13}; // D7 (d1), D8 (d2), D9 (d3), D10 (d4)

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

unsigned long currentTime=0;
int d1 = 0;
int d2 = 0;
int d3 = 0;
int d4 = 0;

void setup() { // setup
  pinMode(l_tact, INPUT_PULLUP);
  pinMode(r_tact, INPUT_PULLUP);
  pinMode(cds_in, INPUT_PULLUP);
  pinMode(l_servo, OUTPUT);
  pinMode(r_servo, OUTPUT);

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
  currentTime = millis()/10;

  d1 = currentTime%10;
  d2 = (currentTime/10)%10;
  d3 = (currentTime/100)%10;
  d4 = (currentTime/1000)%10;

  segOut(3,d1,0);
  if(currentTime>=10) segOut(2,d2,0);
  if(currentTime>=100) segOut(1,d3,0);
  if(currentTime>=1000) segOut(0,d4,0);
}

void segClear(){ // segment clear
  for(int i=0;i<8;i++){
    digitalWrite(pin_segs[i], LOW);
  }
}

void segOut(int d, int value, int dp){ // segment output
  segClear();
  digitalWrite(pin_segDigit[d], LOW);
  for(int i=0;i<7;i++){
     digitalWrite(pin_segs[i], segNum[value][i]);
  }
  digitalWrite(pin_segs[7], dp);
  delayMicroseconds(1000);
  digitalWrite(pin_segDigit[d], HIGH);
}