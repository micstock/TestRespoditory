#include <Arduino_FreeRTOS.h>

void hello_world_task(void *pvParameters);
void repeat_task(void *pvParameters);

void setup() {
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(
    hello_world_task
    ,  (const portCHAR *)"Blink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

//  xTaskCreate(
//    repeat_task
//    ,  (const portCHAR *) "AnalogRead"
//    ,  128  // Stack size
//    ,  NULL
//    ,  1  // Priority
//    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void hello_world_task(void *pvParameters)
{
  (void) pvParameters;
    pinMode(13,OUTPUT);
    int i=0;
    int led=0;
    while(1) {
//        Serial.print("Hello World! "); Serial.println(i);
        digitalWrite(13,led);
        i++;
        led=!led;
        vTaskDelay(10);
        //digitalWrite(3,1);
    }
    
}
//void repeat_task(void *pvParameters)
//{
//   (void) pvParameters;
//    pinMode(9,OUTPUT);
//    int i=0;
//    int led=0;
//    while(1) {
//        Serial.print("Repeat Hello World! "); Serial.println(i);
//        digitalWrite(9,led);
//        i++;
//        led=!led;
//        vTaskDelay(10);
//        //digitalWrite(3,1);
//    }    
//}
String in_string;
int in_num;
int index;
void loop()
{
  Serial.println("input now..");
  if (Serial.available()) {};
  in_string = Serial.readString();
  in_num = in_string.toInt();

  Serial.print(index);Serial.print(" in_num =.");Serial.print(in_num);
  Serial.print(" in_string = "); Serial.println(in_string);
  delay(200);
}

