
/*
 * Clap_Detecter Code
 * 
 */
#define SINGLE_CLAP_SILENT_USEC 6000
#define ALL_CLAP_SILENT_USEC 450000

//MY: RGB_PIN
const byte RGB_BLUE_PIN =11;
const byte RGB_GREEN_PIN =12;
const byte RGB_RED_PIN =13;

//const byte ledPin = 5;
const byte interruptPin = 2;

unsigned long first_rise_ts = 0;
unsigned long last_fall_ts = 0;

// TY: I am dis-like these two needed to be declared as global variable
unsigned long last_clap_fall_ts = 0;
unsigned int clap_cnt = 0;

//MY: clap to verfify the clap count
unsigned int clap_to_confirm=0; //flag for count the confirm clap
unsigned int clap_cnt_LED=0; //clap count to drive RGB LED 
unsigned long RGB_startMillis =0; //RGB LED Delay Start
//unsigned int clap_confirm_cnt=0;
int LED_delay=0;

/*
 * ClapNDrive
 * 
 */
 // connect motor controller pins to Arduino digital pins
// motor one
int enA = 6;
int in1 = 8;
int in2 = 7;
// motor two
int enB = 3;
int in3 = 4;
int in4 = 5;
//Motor Drive Mode
unsigned int motor_drive_mode = 0;
unsigned int motor_mode_change = 0;
//unsigned long run_time_start =0; //Motor Run Time

/*
 * SR-04 Ultrasound Sensor
 */
#include <NewPing.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
  unsigned long dist_check_start = millis();

  


void setup() {
  Serial.begin(9600);
  Serial.println("setup() - begin");
  /*
   * Clap Detector
   */
  pinMode(RGB_BLUE_PIN,OUTPUT);
  pinMode(RGB_GREEN_PIN,OUTPUT);
  pinMode(RGB_RED_PIN,OUTPUT);

  // using CHANGE to detect both RISING & FALLING edge
  attachInterrupt(digitalPinToInterrupt(interruptPin), log_chg, CHANGE);

  // Reset RGB LED, time  
  digitalWrite(RGB_RED_PIN,HIGH);
  digitalWrite(RGB_GREEN_PIN,HIGH);
  digitalWrite(RGB_BLUE_PIN,HIGH);
  reset_ts();

  /*
   * clapNdrive
   */
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  /*
   * SR-04 Ultrasound Sensor
   */
//  NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
  //unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int dist_to_crash= 20;


  
  Serial.println("setup() - nearly end");
  delay(2000);
  Serial.println("LED_OFF");
  Serial.println("setup() - end");
}

void loop() {
  unsigned long curr_us = 0;
  unsigned long quiet_us = 0;
    NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
  unsigned int uS = sonar.ping();// Send ping, get ping time in microseconds (uS).
 
  if (dist_check_start + 1000 <millis())
  {
    Serial.print("ping:");
    Serial.println(uS/US_ROUNDTRIP_CM);
    if (uS/US_ROUNDTRIP_CM < 15)
    {
      motor_drive(0,0,0,0,0,0);
      reset_all_flag();  
    }
  dist_check_start = millis();
  }
  
 
  if (first_rise_ts)
  {
    noInterrupts();
    curr_us = micros();
    if (last_fall_ts)
    {
       quiet_us = curr_us - last_fall_ts;
    }    
    if (quiet_us > SINGLE_CLAP_SILENT_USEC)
    {
      if (first_rise_ts)
      {
        clap_cnt++;
        last_clap_fall_ts = last_fall_ts;
      }
      reset_ts();
    }
    interrupts();
  }

  if (clap_cnt)
  {
    delay(50);
    curr_us = micros();
    quiet_us = curr_us - last_clap_fall_ts;
    
    if (quiet_us > ALL_CLAP_SILENT_USEC)
    {
      if (clap_to_confirm ==0)
      {
      // print ONLY if first_rise_ts exist, ie not just a last_fall_ts detected
      Serial.print("clap count = ");
      Serial.println(clap_cnt);
      Serial.println();
      //digitalWrite(ledPin, LOW);
      clap_cnt_LED= motor_drive_mode =clap_cnt;//count to drive RGB LED

      LED_delay=2000; //RGB LED ON time for confirmation 
      RGB_startMillis=millis(); //RGB LED delay
      clap_cnt = 0;
      last_clap_fall_ts = 0;
      clap_to_confirm=1; //flag for to clap confirmation count 
      }
      else
      {
        if (clap_cnt==1)
        {
        Serial.print("confirm clap count = ");
        Serial.println(clap_cnt);
        Serial.println();
        motor_mode_change = 1; //flag for motor change confirmed
        clap_cnt_LED = 4; //show mode confirmed with white Color
        LED_delay = 200;
        RGB_startMillis = millis();
        clap_to_confirm = 0;
        clap_cnt = 0;
        }
      }
    }
  }
  
  //MY: RGB LED OUTPUT,case can be added for future dev
  switch(clap_cnt_LED)
    {
	  case 0:
	  RGB_LED(HIGH,HIGH,HIGH,LED_delay);
	  break;
	  case 1:
	  RGB_LED(HIGH,HIGH,LOW,LED_delay);
	  break;
	  case 2:
	  RGB_LED(HIGH,LOW,HIGH,LED_delay);
	  break;
	  case 3:
	  RGB_LED(LOW,HIGH,LOW,LED_delay);
	  break;
    case 4:
    RGB_LED (LOW,LOW,LOW,LED_delay);
    break; 
    }
  if (motor_mode_change==1)
  {

    switch (motor_drive_mode)
    {
      case 0:
      motor_drive(0,0,0,0,0,0);
      break;
      case 1: //FWD
      motor_drive( 1,0,122,1,0,100);
      motor_mode_change=0;
      break;
      case 2: //STOP
      motor_drive(0,0,0,0,0,0);
      motor_mode_change=0;
      break;
      
    }
  }
}

void log_chg() {
  unsigned long curr_us;
  int curr_val;

  curr_us = micros();
  curr_val = digitalRead(interruptPin);
  //Serial.print(curr_val);

//  if (first_rise_ts == 0)  <<-- this doesn't work
  if ((first_rise_ts == 0) && (curr_val == HIGH))
  {
     last_fall_ts = first_rise_ts = curr_us;
  }
  if (first_rise_ts && (curr_us - last_fall_ts) && (curr_val == LOW))
  {
     last_fall_ts = curr_us;
  }
}

void reset_ts() 
{
  first_rise_ts = 0;
  last_fall_ts = 0;
}

void reset_all_flag()
{
  clap_cnt = clap_to_confirm = motor_mode_change = 0; 
}

void RGB_LED(int R, int G, int B,int LED_delay) 
{
  for (int i=0;i<2;i++) //loop to turn LED off after delay
    {
    digitalWrite(RGB_RED_PIN,R);
    digitalWrite(RGB_GREEN_PIN,G);
    digitalWrite(RGB_BLUE_PIN,B);
    //MY: Delay with millis() and turn off LED
    if (RGB_startMillis + LED_delay < millis())
      {
      R=G=B=HIGH;
      RGB_startMillis = millis();
      clap_cnt_LED = 0;
      clap_to_confirm = 0;
      }
    }      
}

void motor_drive( int L1, int L2,int enA_L,int R1, int R2,  int enB_R)
{
 Serial.print("Motor Drive = ");
 Serial.print( L1);Serial.print(L2);Serial.print(enA_L);
 Serial.print(R1);Serial.print(R2);Serial.print(enB_R);
 Serial.println("");
 // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, L1);
  digitalWrite(in2, L2);
  // set speed to enA_L out of possible range 0~255
  analogWrite(enA, enA_L);
  // turn on motor B
  digitalWrite(in3, R1);
  digitalWrite(in4, R2);
  // set speed to enB_R out of possible range 0~255
  analogWrite(enB, enB_R); 
}


