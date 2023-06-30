
int x;

void setup() {
  pinMode(9,OUTPUT);    //Set Pin 7 as PUL
  pinMode (8,OUTPUT);   //Set Pin 6 as DIR  
  pinMode (11,OUTPUT); 
}

void loop() {
  digitalWrite(11,LOW);
    
  digitalWrite(8,HIGH); 
      //Set high level direction
  int steps = 2000;
  int delaytime = 200;
  for (x=0; x<steps;x++)        //Repeat 400 times a revolution when setting is 400 on driver
  {
    digitalWrite(9,HIGH);    //Output high
    delayMicroseconds(delaytime);   //Set rotate speed
    digitalWrite(9,LOW);      //Output low
    delayMicroseconds(delaytime);    //Set rotate speed
  }
  delay(50);
  digitalWrite(8,LOW);   
      // Set high level direction
  for(x=0;x<steps;x++)
  {
    digitalWrite(9,HIGH);
    delayMicroseconds(delaytime);
    digitalWrite(9,LOW);
    delayMicroseconds(delaytime);
  }
  delay(50);

}