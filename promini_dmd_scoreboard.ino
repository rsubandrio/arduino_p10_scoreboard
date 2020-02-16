/*
 * Pin tombol 3, 4, 5
*/

#include <SPI.h>
#include <EasyButton.h>
#include <DMD2.h>
#include <fonts/BigNumber.h>

SoftDMD dmd(1,1);  // DMD controls the entire display

#define btn1_pin 5
#define btn2_pin 3
#define btn3_pin 4

EasyButton btn1(btn1_pin);
EasyButton btn2(btn2_pin);
EasyButton btn3(btn3_pin);

byte score1 = 0;
byte score2 = 0;
byte scored_before = 0;

void onBtn1Pressed(){
  score1++;
  if(score1 > 30 || score1 < 0)
  {
    score1 = 0;
  }
  
  if (score1 < 10){
    dmd.drawString(19, -1, "0" + String(score1));
  }
  else {
    dmd.drawString(19, -1, String(score1));
  }

  dmd.drawBox(0, 14, 12, 15, GRAPHICS_OFF);
  dmd.drawBox(19, 14, 31, 15);

  dmd.drawBox(15, 5, 16, 7, scored_before == 1 ? GRAPHICS_ON : GRAPHICS_OFF);

  scored_before = 1;
}

void onBtn2Pressed(){
  score2++;
  if(score2 > 30 || score2 < 0)
  {
    score2 = 0;
  }
  
  if (score2 < 10){
    dmd.drawString(0, -1, "0" + String(score2));
  }
  else {
    dmd.drawString(0, -1, String(score2));
  }

  dmd.drawBox(0, 14, 12, 15);
  dmd.drawBox(19, 14, 31, 15, GRAPHICS_OFF);

  dmd.drawBox(15, 5, 16, 7, scored_before == 2 ? GRAPHICS_ON : GRAPHICS_OFF);

  scored_before = 2;
}

void onBtn3Pressed(){
  scored_before = 0;
  score1 = 0;
  score2 = 0;
  dmd.drawString(0,-1,F("00"));
  dmd.drawString(19, -1, F("00"));
  dmd.drawBox(14,4,17,8);
  dmd.drawBox(15, 5, 16, 7, GRAPHICS_OFF);
  dmd.drawBox(0, 14, 12, 15, GRAPHICS_OFF);
  dmd.drawBox(19, 14, 31, 15, GRAPHICS_OFF);
}

void setup() {
  dmd.setBrightness(20);
  dmd.selectFont(BigNumber);
  dmd.begin();
  dmd.drawString(0,-1,F("00"));
  dmd.drawString(19, -1, F("00"));
  dmd.drawBox(14,4,17,8);
  dmd.drawBox(0, 14, 12, 15, GRAPHICS_OFF);
  dmd.drawBox(19, 14, 31, 15, GRAPHICS_OFF);
  // inisiasi button
  btn1.begin();
  btn2.begin();
  btn3.begin();
  // button event
  btn1.onPressed(onBtn1Pressed);
  btn2.onPressed(onBtn2Pressed);

  // khusus tombol tengah, menghindari kepencet tanpa sengaja
  // jika dipencet selama 2 detik baru reset
  btn3.onPressedFor(2000, onBtn3Pressed);
}

void loop() {
  btn1.read();
  btn2.read();
  btn3.read();
}
