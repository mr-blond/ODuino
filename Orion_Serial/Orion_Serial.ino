#include <Servo.h> 
 
Servo myservo,myservo2;
int pos = 0;

char charInput = 0;
int i = 1;
char aInput[8];

int led = 13;

void setup() {
      Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
      pinMode(led, OUTPUT); 
}

void loop() {
        //!11-010:
        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                charInput = (char)Serial.read();

                // say what you got:
                /*Serial.print("I received: ");
                Serial.print((char)charInput);
                Serial.print('\n');*/
                
                if((char)charInput == ':'){


                  
                  Serial.print("Port : ");
                  Serial.print(getPort());
                  Serial.print(" -- Value : ");
                  Serial.print(getValue());
                  Serial.print('\n');
                  
                  servoDirect(getValue(), getPort());

                  reset();

                }else{
                  aInput[i] = charInput; 
                }
                
                i++;
        }
        
     
}

void reset(){
  i = 0;
  Serial.flush();
  lB();
}

int getPort(){
  String val = (String)(char)aInput[2] + (char)aInput[3];
  lB();
  return val.toInt();
}

int getValue(){
  String val = (String)(char)aInput[5] + (char)aInput[6] + (char)aInput[7];
  lB();
  return val.toInt(); 
}

void servo(int x){
  for(pos = 0; pos < x; pos += 1)   
  {                                   
    myservo.write(pos);              
    delay(15);                  
  } 
}

void servoDirect(int x, int p){
  if(x >= 0 || x <= 180){ 
     myservo.attach(p);
     myservo.write(x);
     lB();
  }
}

void lB(){
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
}

