
int clapCounter =0;
int timebase = 0;
int flagConfirm =0;
unsigned long startMillis;
int led=0;
int ledPin=13;
int REDpin=12;
int BLUEpin=10;
int GREENpin=11;


void setup() {
  // put your setup code here, to run once:
  attachInterrupt(0,IntHandler,RISING);
  pinMode(ledPin, OUTPUT);
  pinMode(REDpin,OUTPUT);
  pinMode(GREENpin,OUTPUT);
  pinMode(BLUEpin,OUTPUT);
  
  digitalWrite(REDpin,HIGH);
  digitalWrite(GREENpin,HIGH);
  digitalWrite(BLUEpin,HIGH);
  Serial.begin(9600); 
}


void loop() {
    
/* timebase is the time period allowed to detect the all the hand Clap input
 * 
 */
if (timebase>0){ timebase--;}
else{
  if(clapCounter>0){   
    if(clapCounter==1){
      Serial.println("    One Clap");
      digitalWrite(BLUEpin,LOW);
      //delay(1000);
      }
    if(clapCounter==2){
            Serial.println("    Two Claps");
            digitalWrite(GREENpin,LOW);
            //delay(1000);
            }
    if(clapCounter==3){
            Serial.println("    Three Claps");
            digitalWrite(REDpin,LOW);
            //delay(1000);
            } 
        //clapConfirm();  
      }

     clapCounter=0;
       led=0;
  } 


  digitalWrite(ledPin,led);
  digitalWrite(BLUEpin,HIGH);
  digitalWrite(GREENpin,HIGH);
  digitalWrite(REDpin,HIGH);
  delay(9);
  
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
  if((millis()-startMillis)>100 && flagConfirm==0){
    clapCounter++;
    startMillis=millis();
  }
  if(clapCounter>0){
    timebase= 150;
  }

  Serial.print("ClapCounter= ");
  Serial.println(clapCounter);

}


