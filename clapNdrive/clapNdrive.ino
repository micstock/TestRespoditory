//Sound Sensor & LED Pin
int clapCounter =0;
int timebase = 0;
int flagConfirm =0;
unsigned long startMillis;
//int led=0;
//int ledPin=13;
int REDpin=12;
int BLUEpin=10;
int GREENpin=11;

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 6;
int in1 = 4;
int in2 = 5;
// motor two
int enB = 9;
int in3 = 7;
int in4 = 8;


void setup() {
  // set sounder sensor and LED pins
  attachInterrupt(0,IntHandler,RISING); //sound sensor interrupt
  //pinMode(ledPin, OUTPUT);
  pinMode(REDpin,OUTPUT);
  pinMode(GREENpin,OUTPUT);
  pinMode(BLUEpin,OUTPUT);
  
  digitalWrite(REDpin,HIGH);
  digitalWrite(GREENpin,HIGH);
  digitalWrite(BLUEpin,HIGH);
  Serial.begin(9600); 
 
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}


void loop() {
    
/* timebase is the time period allowed to detect the all the hand Clap input
 * 
 */

  

 Serial.println(timebase);
if (timebase>0){ timebase--;}
else{
  if(clapCounter>0){   
    if(clapCounter==1){
      Serial.println("    One Clap");
      digitalWrite(BLUEpin,LOW);
      demoOne();
      delay(1000);
      }
    if(clapCounter==2){
            Serial.println("    Two Claps");
            digitalWrite(GREENpin,LOW);
            demoTwo();
            delay(1000);
            }
    if(clapCounter==3){
            Serial.println("    Three Claps");
            digitalWrite(REDpin,LOW);
            delay(1000);
            } 
            
        //clapConfirm();  
      }

     clapCounter=0;
       //led=0;
  } 


  //digitalWrite(ledPin,led);
  digitalWrite(BLUEpin,HIGH);
  digitalWrite(GREENpin,HIGH);
  digitalWrite(REDpin,HIGH);
  //delay(9);
  
}

void IntHandler(){
  /*ClapCounter started from 1 as first Clap interrupt occur. 
   *
   */
  if (clapCounter==0){
    startMillis=millis();
    clapCounter=1;
    }
/*To stop the sound boundce causing more interrupt & flase ClapCount to occur
 * Millis() timer added
 */
  if((millis()-startMillis)>50 && flagConfirm==0){
    clapCounter++;
    startMillis=millis();
  }
  if(clapCounter>0){
    timebase= 250;
  }

  Serial.print("ClapCounter= ");
  Serial.println(clapCounter);

}


