#include 
SoftwareSerial BT(2,3); //rx-tx
int Car1= 5;
int Car2= 6;
int motorlc = 8; // left motor clockwise rotation
int motorla = 9; // left motor anticlockwise rotation
int motorrc = 10; // right motor clockwise rotation
int motorra = 11; // right motor anticlockwise rotatio
int Far = 13;
int hiz1;
int hiz2;
int hiz3;

String readString;

void setup() { // presenting pins as outputs
pinMode(Far, OUTPUT);
pinMode(motorlc, OUTPUT);
pinMode(motorla, OUTPUT);
pinMode(motorrc, OUTPUT);
pinMode(motorra, OUTPUT);
Serial.begin(9600);
BT.begin(9600);
}
void loop() {
while(BT.available()){ // the code here is for bluetooth
delay(3);
char c = BT.read();
readString += c;
}
if(readString.length() > 0){ // when a certain button is pressed the reaction will be...
Serial.println(readString);
if(readString == "Forward"){
analogWrite (Car1,hiz1);
analogWrite (Car2,hiz1);
digitalWrite(motorlc, HIGH);
digitalWrite(motorla, LOW);
digitalWrite(motorrc, HIGH);
digitalWrite(motorra, LOW);
}
if(readString == "Back"){
analogWrite (Car1,hiz1);
analogWrite (Car2,hiz1);
digitalWrite(motorlc, LOW);
digitalWrite(motorla, HIGH);
digitalWrite(motorrc, LOW);
digitalWrite(motorra, HIGH);
}
if(readString == "Left"){
analogWrite (Car1,hiz2);
analogWrite (Car2,hiz2);
digitalWrite(motorlc, HIGH);
digitalWrite(motorla, LOW);
digitalWrite(motorrc, LOW);
digitalWrite(motorra, HIGH); 
}
if(readString == "Right"){
analogWrite (Car1,hiz2);
analogWrite (Car2,hiz2);
digitalWrite(motorlc, LOW);
digitalWrite(motorla, HIGH);
digitalWrite(motorrc, HIGH);
digitalWrite(motorra, LOW); 
}
if(readString == "Stop"){

digitalWrite(motorlc, LOW);
digitalWrite(motorla, LOW);
digitalWrite(motorrc, LOW);
digitalWrite(motorra, LOW);
analogWrite (Car1,hiz3);
analogWrite (Car2,hiz3);
}
if(readString == "Car on"){

hiz1 =200;
hiz2 =140;
hiz3 =0;
digitalWrite(Far,HIGH);
delay(50);
digitalWrite(Far,LOW);
delay(50);
digitalWrite(Far,HIGH);
delay(50);
digitalWrite(Far,LOW);
delay(50);
digitalWrite(Far,HIGH);
delay(50);
digitalWrite(Far,LOW);
}
if(readString == "Car off"){

hiz1 =0;
hiz2 =0;
hiz3 =0;
}
if(readString == "Far on"){

digitalWrite(Far,HIGH);
}
if(readString == "Far off"){

digitalWrite(Far, LOW);
}
}
readString="";
}
