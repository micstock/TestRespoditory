<<<<<<< HEAD
//see your comment
=======
/*
    clapConfirm() will confirm a clap is identified
*/
>>>>>>> 2f5355514ef98b425676f9697585ed59c7a390d4

void clapConfirm(){
  
  flagConfirm =1;
  if (timebase>0){ timebase--;}
else{
  if(clapCounter>0){   
    if(clapCounter==1){
      Serial.println("    Confirmed Clap");
      digitalWrite(BLUEpin,LOW);
      digitalWrite(REDpin,LOW);
      digitalWrite(GREENpin,LOW);
      flagConfirm=0;
      //delay(1000);
      }
    
     }

     clapCounter=0;
  } 
  Serial.print("clapConfirm clapCounter==");
  Serial.println(clapCounter);
 Serial.println(timebase);
delay(1000);
}

