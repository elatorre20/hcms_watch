//a sketch that pulls characters from the serial port and scrolls them to the display
#include <font5x7.h>
#include <LedDisplay.h>

LedDisplay disp = LedDisplay(11,12,13,14,15,8);
char disp_buf[8];
uint32_t disp_count, serial_count;

void setup() {
  // put your setup code here, to run once:
  disp.begin();
  disp.setBrightness(15);
  disp.clear();
  Serial.ignoreFlowControl(true);
  Serial.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    for(uint8_t i = 0; i < 7; i++){
      disp_buf[i] = disp_buf[i+1];
    }
    disp_buf[7] = Serial.read();
  }
  disp.clear();
  disp.home();
  for(uint8_t i = 0; i < 8; i++){
    disp.print(disp_buf[i]);
  }
}
