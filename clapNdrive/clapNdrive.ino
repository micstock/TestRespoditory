//Sound Sensor & LED Pin
int clapCounter =0;
int timebase = 0;
int flagConfirm =0;
unsigned long startMillis;
//int led=0;
int ledPin=13;
int REDpin=10;
int BLUEpin=12;
int GREENpin=11;

//Motor Run Mode
int runMode=0; // 0=Motor Stop,1=FWD ,2= Left Turn with turnTime 3=RES
int turnTime=2000; //2sec

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
  pinMode(ledPin,OUTPUT);
  
  digitalWrite(REDpin,HIGH);
  digitalWrite(GREENpin,HIGH);
  digitalWrite(BLUEpin,HIGH);
  digitalWrite(ledPin,LOW);
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

  

 //Serial.println(timebase);
if (timebase>0)
    { timebase--;
      //Serial.print(timebase);
      }
else{
  if(clapCounter>0)
  { 
    //noInterrupts();
    flagConfirm=1;  
    if(clapCounter==1)
    {
      Serial.println("    One Clap");
      digitalWrite(BLUEpin,LOW);
      //demoOne();
      //flagConfirm=1;
      delay(1000);
      }
    if(clapCounter==2)
    {
      Serial.println("    Two Claps");
      digitalWrite(GREENpin,LOW);
            //demoTwo();
      delay(1000);
            }
    if(clapCounter==3)
    {
      Serial.println("    Three Claps");
      digitalWrite(REDpin,LOW);
      delay(1000);
            } 
            
  
   }

     clapCounter=0;
     flagConfirm=0;
     //interrupts();
       //led=0;
  } 


  //digitalWrite(ledPin,led);
  digitalWrite(BLUEpin,HIGH);
  digitalWrite(GREENpin,HIGH);
  digitalWrite(REDpin,HIGH);
  digitalWrite(ledPin,LOW);
  delay(7); //This delay is for timebase effectively count
  
}

void IntHandler()
{
  /*ClapCounter started from 1 as first Clap interrupt occur. 
   */
  if (flagConfirm==1){
    digitalWrite(ledPin,HIGH);
    if (clapCounter==1){runMode=1;}
    if (clapCounter==2){runMode=2;}
    if (clapCounter==3){runMode=3;}
  }
  else{
 /*    
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
}


