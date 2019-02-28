#include "LedControlMS.h"
LedControl lc = LedControl(12, 11, 10, 1);
int had[8][8] = {0};
byte xHad = 4;
byte yHad = 5;
byte xaxis = 0;
byte yaxis = 0;
byte directi = 0;
int step1 = 1;
long time1 = 0;
int speed1 = 500;
byte score1 = 0;
boolean snooze1 = false;
int num[11][7] = {
{B00000000, B00000000, B00000000, B00000000, B00000001, B01111111,
B00100001},
{B00000000, B00000000, B00110001, B01001001, B01000101, B00100011},
{B00000000, B00000000, B01000110, B01101001, B01010001, B01000001,
B01000010},
{B00000000, B00001000, B11111111, B01001000, B00101000, B00011000,
B00001000},
{B00000000, B00000000, B00111110, B01000101, B01001001, B01010001,
B00111110},
{B00000000, B00000000, B00000110, B01001001, B01001001, B00101001,
B00011110},
{B00000000, B00000000, B01110000, B01001000, B01000111, B01000000,
B01100000},
{B00000000, B00000000, B00110110, B01001001, B01001001, B01001001,
B00110110},
{B00000000, B00000000, B00111100, B01001010, B01001001, B01001001,
B00110000},
{B00000000, B00000000, B00111110, B01010001, B01001001, B01000101,
B00111110},
{B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
B00000000},

};
void setup() {
  Serial.begin(9600);
  Serial.println("Your game starts");
  delay(1000);
  randomSeed(analogRead(A0));
  genseed();
  lc.shutdown(0, false);
  lc.setIntensity(0, 1);
  byte h[7]={B10000000,B10000000,B10110000,B11001000,B10001000,B10001000,B10001000};
  lc.setRow(0,0,h[0]);
  lc.setRow(0,1,h[1]);
  lc.setRow(0,2,h[2]);
  lc.setRow(0,3,h[3]);
  lc.setRow(0,4,h[4]);
  lc.setRow(0,5,h[5]);
  lc.setRow(0,6,h[6]);
  delay(500);
  byte e[7]={B00000000,B00000000,B01110000,B10001000,B11111000,B10000000,B01110000};
  lc.setRow(0,0,e[0]);
  lc.setRow(0,1,e[1]);
  lc.setRow(0,2,e[2]);
  lc.setRow(0,3,e[3]);
  lc.setRow(0,4,e[4]);
  lc.setRow(0,5,e[5]);
  lc.setRow(0,6,e[6]);
  delay(500);
  byte y[7]={B00000000,B00000000,B10001000,B10001000,B01111000,B00001000,B01110000};
  lc.setRow(0,0,e[0]);
  lc.setRow(0,1,y[1]);
  lc.setRow(0,2,y[2]);
  lc.setRow(0,3,y[3]);
  lc.setRow(0,4,y[4]);
  lc.setRow(0,5,y[5]);
  lc.setRow(0,6,y[6]);
  delay(500);
  byte hf[8]={B00111100,B01000010,B10100101,B10000001,B10100101,B10011001,B01000010,B00111100};
  lc.setRow(0,0,hf[0]);
  lc.setRow(0,1,hf[1]);
  lc.setRow(0,2,hf[2]);
  lc.setRow(0,3,hf[3]);
  lc.setRow(0,4,hf[4]);
  lc.setRow(0,5,hf[5]);
  lc.setRow(0,6,hf[6]);
  lc.setRow(0,7,hf[7]);
  delay(500);
  lc.clearDisplay(0);
}
void loop() {
  if ((analogRead(A0) < 200) && (directi != 0) && (directi != 1)) directi = 1;
  if ((analogRead(A0) > 800) && (directi != 1) && (directi != 0)) directi = 0;
  if ((analogRead(A1) < 200) && (directi != 3) && (directi != 2)) directi = 3;
  if ((analogRead(A1) > 800) && (directi != 2) && (directi != 3)) directi = 2;
  if ((millis() - time1) > speed1) {
    time1 = millis();
    delfood(had);
    score();
    mov1();
  if (xHad == xaxis && yHad == yaxis) snooze1 = true;
  if (had[xHad][yHad] != 0) GameOver();
  step1++;
  had[xHad][yHad] = step1;
  }
  draw(had, xaxis, yaxis);
}

void score() {
  if (snooze1 == true) {
    snooze1 = false;
    genseed();
    score1++;
    speed1 -= 20;
    Serial.print ("Your score is ");
    Serial.println (score1);
  }
}
void draw(int matrix1[8][8], byte x, byte y) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if ((matrix1[i][j] >= 1) || ((i == x) && (j == y) )) lc.setLed(0, i, j, true);
      else lc.setLed(0, i, j, false);
    }
  }
}

void delfood(int matrix1[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (matrix1[i][j] == (step1 - score1)) matrix1[i][j] = 0;
    }
  }
}


void mov1() {
  switch (directi) {
    case 0:
      xHad++;
      break;
    case 1:
      xHad--;
      break;
    case 2:
      yHad++;
      break;
    case 3:
      yHad--;
      break;
  }
  if (xHad == 8) xHad = 0;
  if (yHad == 8) yHad = 0;
  if (xHad == 255) xHad = 7;
  if (yHad == 255) yHad = 7;
}

void genseed() {
  lc.setLed(0, xaxis, yaxis, false);
  do {
    xaxis = random(0, 8);
    yaxis = random(0, 8);
  } while (had[xaxis][yaxis] != 0 );
}

void draw1(byte num1) {
  if (num1 == 0) num1 = 10;
  for (int col = 0; col < 7; col++) {
    lc.setRow(0, col, num[num1 - 1][col]);
  }
}


void GameOver() {
  Serial.println ("Game over");
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, col, row, true);
      delay(25);
    }
  }
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, col, row, false);
      delay(25);
    }
  }
  do {
    draw1((score1 / 10) % 10);
    delay(200);
    draw1(score1 % 10);
    delay(200);
    draw1(11);
    delay(1000);
  } while (true);
}
