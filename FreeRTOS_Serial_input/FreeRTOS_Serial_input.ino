#include <Arduino_FreeRTOS.h>

void setup() {
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
}
String in_string;
int in_num;
int index;
void loop()
{
  Serial.println("input now..");
  while (!Serial.available()) {}; //waiting for input..
  in_string = Serial.readString();
  in_num = in_string.toInt();

  Serial.print(index);Serial.print(" in_num =.");Serial.print(in_num);
  Serial.print(" in_string = "); Serial.println(in_string);
  index++;
  delay(200);
}

