

const unsigned long decisionTimeInterval = 0;
const unsigned long testPininterval = 100;
unsigned long decisionTimer;
unsigned long testPintimer;
#define NoMasterNoButton 0
#define ButtonNoMaster 1
#define ButtonIAmMaster 2
#define ButtonOtherMaster 3
#define ButtonCollision 4 
#define NoButtonOtherMaster 5
#define TryToBeMaster 6
#define testPin 8


#define LED 13 
#define Button 2
#define OUT 3
#define OtherMASTER 4
#define Alive 8

char state;


void setup () 
  {
  
  pinMode (testPin, OUTPUT);
  decisionTimer = millis ();
  testPintimer = millis ();
  Serial.begin(9600);
pinMode(LED, OUTPUT);
pinMode(OUT, OUTPUT);
pinMode(OtherMASTER,INPUT_PULLUP);
pinMode(Button,INPUT_PULLUP);
pinMode(Alive, OUTPUT);
digitalWrite (Alive, HIGH );
state = NoMasterNoButton;
 }

 bool readBtn(){
 return(digitalRead(Button) != HIGH);
}

bool OtherMaster(){
  return(digitalRead(OtherMASTER) != HIGH);
}


void decisionTask ()
  {
    Serial.println("state");
    Serial.println(state,DEC);
//    Serial.println("OtherMaster");
//    Serial.println(OtherMaster(),DEC);
//    Serial.println("readBTN");
//    Serial.println(readBtn(),DEC);
//    delay (200);
switch (state) {
  
  case NoMasterNoButton:
  {
  digitalWrite(OUT ,HIGH);
  digitalWrite(LED ,LOW);
  //delay (20);
  if(!readBtn() && !OtherMaster())
  {
    state = NoMasterNoButton;
    break;
  }
  if(!readBtn && OtherMaster()){
  state= NoButtonOtherMaster;
  break;
  }
  if(readBtn){
    state=ButtonNoMaster;
    break;
  }
  break;

}

  case ButtonNoMaster:
  {
  digitalWrite(OUT,HIGH);
  digitalWrite(LED,LOW);
  //delay (200);
  if(!readBtn()){
    state = NoMasterNoButton;
    break;
  }
  if(readBtn() && OtherMaster()){
    state=ButtonOtherMaster;
    break;
  }
  if(readBtn() && !OtherMaster()){
    state=TryToBeMaster;
    break;
  }
  
  

}

case TryToBeMaster:
  digitalWrite(LED,LOW);
  digitalWrite(OUT,LOW);
  delay(random(100));
  if(!readBtn()){
    state=NoMasterNoButton;
    break;
  }
   if(readBtn() && OtherMaster()){
    state=ButtonCollision;
    break;
  
  }
   if(readBtn() && !OtherMaster()){
    state=ButtonIAmMaster;
    break;
  
}
break;

case ButtonIAmMaster:
  digitalWrite(LED,HIGH);
  digitalWrite(OUT,LOW);
  //delay (200);
  if(!readBtn()){
    state=NoMasterNoButton;
    break;
  }
   if(readBtn() && OtherMaster()){
    state=ButtonCollision;
    break;
  
  }
   if(readBtn() && !OtherMaster()){
    state=ButtonIAmMaster;
    break;
   }
   break;

 case ButtonOtherMaster:
 digitalWrite(LED,LOW);
  digitalWrite(OUT,HIGH);
  //delay (200);
  if(!readBtn()){
    state=NoMasterNoButton;
    break;
  }
   if(readBtn() && OtherMaster()){
    state=ButtonOtherMaster;
    break;
  
  }
   if(readBtn() && !OtherMaster()){
    state=ButtonIAmMaster;
    break;
   }
   break;

case ButtonCollision:
digitalWrite(LED,LOW);
  digitalWrite(OUT,HIGH);
  delay(random(100));
  if(!readBtn()){
    state=NoMasterNoButton;
    break;
  }
   else{
    state=ButtonNoMaster;
    break;
   }
   break;
   
 case NoButtonOtherMaster:
 while (1) {
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
 }

 default:
 {
 state=NoMasterNoButton;
  break;
 }
 decisionTimer=millis();
}
}

void signalBuilder ()
  {
   if (digitalRead (testPin) == LOW)
   {
      digitalWrite (testPin, HIGH);
     // Serial.println("high");
   }
   else
      {
        digitalWrite (testPin, LOW);
       // Serial.println("low");
      }

  // remember when we toggled it
  testPintimer = millis ();  
  }  // end of signalBuilder

void loop ()
  {


  if ( (millis () - decisionTimer) >= decisionTimeInterval)
     decisionTask ();

  
  if ( (millis () - testPintimer) >= testPininterval) 
    signalBuilder ();


   

}  // end of loop
