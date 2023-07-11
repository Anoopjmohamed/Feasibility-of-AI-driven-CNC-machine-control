int x;
int potPin = A0; // the input pin where the potentiometer is connected

void setup() {
  pinMode(9,OUTPUT);    //Set Pin 7 as PUL
  pinMode (8,OUTPUT);   //Set Pin 6 as DIR  
  pinMode (11,OUTPUT); 
  
  pinMode(potPin, INPUT); // set the potentiometer pin as input
}

void loop() {
  int potValue = analogRead(potPin); // read the value from the potentiometer
  int delayTime = map(potValue, 0, 1023, 110, 1000); // map the potentiometer value to a suitable range for delay time

  digitalWrite(11,LOW);
  
  digitalWrite(8,HIGH);
  
  int steps = 3400;
  for (x=0; x<steps;x++)        
  {
    digitalWrite(9,HIGH);
      
    delayMicroseconds(delayTime);   
    digitalWrite(9,LOW);
         
    delayMicroseconds(delayTime);    
  }
  delay(50);
  digitalWrite(8,LOW);
   
  for(x=0;x<steps;x++)
  {
    digitalWrite(9,HIGH);
       
    delayMicroseconds(delayTime);   
    digitalWrite(9,LOW);
          
    delayMicroseconds(delayTime);    
  }
  delay(10);
}
