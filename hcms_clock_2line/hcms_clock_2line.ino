//a sketch that keeps time and writes it to the display every second
#include <font5x7.h>
#include <LedDisplay.h>
#include <TimeLib.h>

uint32_t time_adj = 0;

LedDisplay disp = LedDisplay(11,12,13,14,15,16);
char disp_buf[17];
uint32_t disp_count;

void setup() {
  // put your setup code here, to run once:
  setTime(12,0,0,4,7,2024);
  adjustTime(time_adj);
  disp.begin();
  disp.setBrightness(15);
  disp.clear();
  Serial.ignoreFlowControl(true);
  Serial.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  disp_count++;
  if(disp_count == 100000){
    sprintf(disp_buf, "%02d:%02d:%02d%02d/%02d/%02d",hour(),minute(),second(),month(),day(),(year() % 100));
    disp.home();
    disp.print(disp_buf);
    disp_count = 0;
  }
}
