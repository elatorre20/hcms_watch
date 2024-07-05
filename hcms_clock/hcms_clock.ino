#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0
#include <RPi_Pico_TimerInterrupt.h>
#include <font5x7.h>
#include <LedDisplay.h>
#include <TimeLib.h>

uint8_t button_flag = 0;
#define BUTTON_A_PIN 16
#define BUTTON_B_PIN 17
uint8_t button_b_count = 0;
#define BUTTON_C_PIN 18
uint8_t button_c_count = 0;
#define BUTTON_D_PIN 19
uint8_t disp_flag = 0;
bool TimerHandler0(struct repeating_timer *t){
  (void) t;
  button_flag = 1;
  disp_flag++;
  return true;
}

#define TIMER0_INTERVAL_MS        100
RPI_PICO_Timer ITimer0(0);

uint32_t time_adj = 60; //adjust one minute


LedDisplay disp = LedDisplay(11,12,13,14,15,8);
char disp_buf[8]; //buffer for formatted printing
uint8_t disp_mode = 0; //modes for displaying time vs date

void setup() {
  // put your setup code here, to run once:
  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0); //button poll timer
  setTime(12,0,0,4,7,2024); //set clock time
  disp.begin(); //initialize display
  disp.setBrightness(5);
  disp.clear();
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_C_PIN, INPUT_PULLUP);
  pinMode(BUTTON_D_PIN, INPUT_PULLUP);
  Serial.begin(); //initialize serial
}

void loop() {
  // put your main code here, to run repeatedly:
  if(disp_flag == 5){ //only update display infrequently
    if(disp_mode == 0){
      sprintf(disp_buf, "%02d:%02d:%02d",hour(),minute(),second());
    }
    if(disp_mode == 1){
      sprintf(disp_buf, "%02d/%02d/%02d",month(),day(),(year() % 100));
    }
    disp.home();
    disp.print(disp_buf);
    disp_flag = 0;
  }
  if(button_flag){ //poll buttons on interrupt
    if(!(digitalRead(BUTTON_A_PIN))){ //change time/date mode
      disp_mode = 1;
    }
    else{
      disp_mode = 0;
    }
    if(!(digitalRead(BUTTON_B_PIN))){ //adjust time forward  
      if(button_b_count > 20){ //go fast if the user holds for more than 2 seconds
        if(disp_mode == 1){ //if in date mode, add a month (technically 31 days)
          adjustTime((long)2678400);
        }
        else{
          adjustTime((long)600); //add 10 minutes
        }
      }
      else{ //for the first few clicks add slowly
        if(disp_mode == 1){ //if in date mode add, add a day
          adjustTime((long)86400);
        }
        else{
          adjustTime((long)60); //add a minute
        }
        button_b_count++;
      }
    }
    else{
      button_b_count = 0;
    }
    if(!(digitalRead(BUTTON_C_PIN))){ //adjust time backwards  
      if(button_c_count > 20){ //go fast if the user holds for more than 2 seconds
        if(disp_mode == 1){ //if in date mode, add a month (technically 31 days)
          adjustTime((long)-2678400);
        }
        else{
          adjustTime((long)-600); //add 10 minutes
        }
      }
      else{ //for the first few clicks add slowly
        if(disp_mode == 1){ //if in date mode add, add a day
          adjustTime((long)-86400);
        }
        else{
          adjustTime((long)-60); //add a minute
        }
        button_c_count++;
      }
    }
    else{
      button_c_count = 0;
    }
    button_flag = 0;
  }
}
