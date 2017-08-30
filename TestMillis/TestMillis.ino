
int ClapCounter =0;
int timebase = 0;
unsigned long startMillis;
int led=0;
int ledPin=13;


void setup() {
  // put your setup code here, to run once:
  attachInterrupt(0,IntHandler,RISING);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
}


void loop() {
    
/* timebase is the time period allowed to detect the all the hand Clap input
 * 
 */
if (timebase>0){ timebase--;}
else{
  if(ClapCounter>0){
    if(ClapCounter==1){
      Serial.println("Clap one");   
      }
    if(ClapCounter==2){
            Serial.println("Clap two");
      }
    if(ClapCounter==3){
            Serial.println("Clap three");
      }   
    }
  ClapCounter=0;
  led=0;
  digitalWrite(ledPin,led);
  }
  delay(9);
}

void IntHandler(){
  /*ClapCounter started from 1 as first Clap interrupt occur. 
   *
   */

  //Serial.print("Int==");
  //int Time=millis();
  //Serial.println(Time);
  if (ClapCounter==0){
    //Serial.print("startMillis==");
    startMillis=millis();
    //Serial.println(startMillis);
    ClapCounter=1;
    digitalWrite(ledPin,!led);
    led=!led;
    }
/*To stop the sound boundce causing more interrupt & flase ClapCount to occur
 * Millis() timer added
 */
  if((millis()-startMillis) >100){
  ClapCounter++;
  led=!led;
       digitalWrite(ledPin,led);
       //Time=millis();
    //Serial.print("startMillis+5 millis()==");    
    //Serial.println(Time);
    startMillis=millis();
}
  if(ClapCounter>0){
    timebase= 150;
  }

  //ClapCounter++;

  //delay (100);
  Serial.println("ClapCounter");
  Serial.println(ClapCounter);

}


