#include <Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define IN1  7
#define IN2  8
#define IN3  9
#define IN4  10

const int rs = 1, en = 2, d4 = 3, d5 = 4, d6 = 5, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo altura, pinza, frente;
int gradosBase, caso;
boolean cargada, pause=false;
String txt_lcd_1, txt_lcd_2;

int ledAzul = 14;
int ledRojo = 15;
int boton = 16;


void setup() {  
  gradosBase = 0;
  caso = 0;
  cargada = false;
  txt_lcd_1 = "";
  txt_lcd_2 = "";

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  lcd.begin(16, 2);
  
  recuperaEstado();

  pinMode(ledAzul, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(boton, INPUT);
}

void loop() {
  if( digitalRead(boton) == LOW){
    delay(1000);
    pause=!pause;
  }
}

void recuperaEstado(){
  Wire.begin(1);
  Wire.onReceive(ejecutaFuncion);
}

void ejecutaFuncion(int howMany){
  
  
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);

  altura.attach(11);
  pinza.attach(12);
  frente.attach(13);
  /*
  a: defaultt();
  b: defaultBase();
  c: topeAbajo();
  d: abrir();
  e: prepararPinza();
  f: cerrar();
  g: girarDerecha();
  h: preparaDescarga();
  */
  char ejecutar = Wire.read();
  if(pause) ejecutar='t';
  
   switch( ejecutar ){
    case 'a'  : 
      defaultt();       
      break;
    case 'b'  : 
      girarIzquierda(); 
      break;
    case 'c'  : 
      topeAbajo();      
      break;
    case 'd'  : 
      abrir();          
      break;
    case 'e'  : 
      preparaPinza();   
      break;
    case 'f'  : 
      cerrar();         
      break;
    case 'g'  : 
      girarDerecha();   
      break;
    case 'h'  : 
      preparaDescarga();
      break;
    case 'i'  : 
      cargada = true;   
      break;
    case 'j'  : 
      cargada = false;  
      break;
  }

  
  txt_lcd_2 = cargada ? "Pinza cargada" : ""; 
  actualizaLCD();
}


void actualizaLCD(){
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print(txt_lcd_1);
  lcd.setCursor(0,1);
  lcd.print(txt_lcd_2);
}

void topeAbajo() {

  txt_lcd_1 = "Bajando ..";
  frente.write(110);
  altura.write(20);
  digitalWrite(ledAzul, HIGH);
}


void defaultt() {

  txt_lcd_1 = "Posicion base ..";
  altura.write(60);
  frente.write(30);
  digitalWrite(ledAzul, HIGH);
  
}

void abrir() {
  
  txt_lcd_1 = "Abriendo ..";
  pinza.write(80);
  digitalWrite(ledAzul, HIGH);
}


void cerrar() {
  
  txt_lcd_1 = "Cerrando ..";
  pinza.write(105);
  digitalWrite(ledAzul, HIGH);

}

void preparaDescarga() {

  txt_lcd_1 = "Prepara descarga ..";
  frente.write(62);
  altura.write(45);
  digitalWrite(ledAzul, HIGH);
}


void defaultBase() {
  txt_lcd_1 = "Girando base..";
  actualizaLCD();
  girarBase( gradosBase * (-1), 3 );
  digitalWrite(ledAzul, HIGH);
}


void girarDerecha(){
  txt_lcd_1 = "Gira derecha";
  actualizaLCD();
  girarBase(130, 3);
  digitalWrite(ledAzul, HIGH);
}

void girarIzquierda(){
  txt_lcd_1 = "Gira izquierda";
  actualizaLCD();
  girarBase(-130, 3);
  digitalWrite(ledAzul, HIGH);
}


void preparaPinza(){
  txt_lcd_1 = "Recoge carga";
  altura.write(80);
  digitalWrite(ledAzul, HIGH);
}

void motorBase(int a, int b, int c, int d) {
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
  delay(3);
}

void girarBase(int grados, int intervalo) {
  gradosBase += grados;

  if (grados > 0)
    while (grados > 0) {
      motorBase(1, 0, 0, 0);
      motorBase(1, 1, 0, 0);
      motorBase(0, 1, 0, 0);
      motorBase(0, 1, 1, 0);
      motorBase(0, 0, 1, 0);
      motorBase(0, 0, 1, 1);
      motorBase(0, 0, 0, 1);
      motorBase(1, 0, 0, 1);
      grados--;
      delay(intervalo);
    }
  else
    while (grados < 0) {
      motorBase(1, 0, 0, 1);
      motorBase(0, 0, 0, 1);
      motorBase(0, 0, 1, 1);
      motorBase(0, 0, 1, 0);
      motorBase(0, 1, 1, 0);
      motorBase(0, 1, 0, 0);
      motorBase(1, 1, 0, 0);
      motorBase(1, 0, 0, 0);
      grados++;
      delay(intervalo);
    }
}
