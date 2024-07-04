//a sketch that keeps time and writes it to the display every second
#include <font5x7.h>
#include <LedDisplay.h>
#include <TimeLib.h>

time_t set_time = (12,0,0,4,7,2024);

LedDisplay disp = LedDisplay(11,12,13,14,15,8);
char disp_buf[9];
uint32_t disp_count;

void setup() {
  // put your setup code here, to run once:
  disp.begin();
  disp.setBrightness(5);
  disp.clear();
  Serial.ignoreFlowControl(true);
  Serial.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  disp_count++;
  if(disp_count == 10000){
    sprintf(disp_buf, "%02d:%02d:%02d",hour(),minute(),second());
    disp.clear();
    disp.home();
    disp.print(disp_buf);
    disp_count = 0;
  }
}
