#include <Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define IN1  7
#define IN2  8
#define IN3  9
#define IN4  10

LiquidCrystal lcd(5, 4, 3, 2, 1, 0);

Servo altura, pinza, frente;
int inter = 400;
int gradosBase = 0;
int caso = 0;
boolean cargada = false;
String txt_lcd_1 = "", txt_lcd_2 = "";

//String secuencia_default = "abcdefzaghdyaf";
String secuencia = "";
//String secuencia = "";
int i=0;

void setup() {  
  
  altura.attach(11);
  pinza.attach(12);
  frente.attach(13);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  lcd.begin(16, 2);
  
  pinMode(A0, OUTPUT);
  
  analogWrite(A0, 70);

  recuperaEstado();
   
}

void loop() {

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
  
  
  i = i >= secuencia.length() ? 0 : i+1; 
  guardarEstado(i,secuencia);
  
  
  switch( secuencia[i] ){
    case 'a'  : defaultt();       break;
    case 'b'  : defaultBase();    break;
    case 'c'  : topeAbajo();      break;
    case 'd'  : abrir();          break;
    case 'e'  : preparaPinza();   break;
    case 'f'  : cerrar();         break;
    case 'g'  : girarDerecha();   break;
    case 'h'  : preparaDescarga();break;
    case 'z'  : cargada = true;   break;
    case 'y'  : cargada = false;  break;
  }

  //recuperaEstado();
  
  //txt_lcd_2 = cargada ? "Pinza cargada" : ""; 
  
  actualizaLCD();
  
  delay(inter);
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
}


void defaultt() {

  txt_lcd_1 = "Posicion base ..";
  altura.write(60);
  frente.write(30);
}

void abrir() {
  
  txt_lcd_1 = "Abriendo ..";
  pinza.write(80);
}


void cerrar() {
  
  txt_lcd_1 = "Cerrando ..";
  pinza.write(105);

}

void preparaDescarga() {

  txt_lcd_1 = "Prepara descarga ..";
  frente.write(62);
  altura.write(45);
}


void defaultBase() {
  txt_lcd_1 = "Girando base..";
  actualizaLCD();
  girarBase( gradosBase * (-1), 3 );
}


void girarDerecha(){
  txt_lcd_1 = "Gira derecha";
  actualizaLCD();
  girarBase(130, 3);
}


void preparaPinza(){
  txt_lcd_1 = "Recoge carga";
  altura.write(80);
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

void guardarEstado(int estado, String secuencia){
  Wire.begin();
  Wire.beginTransmission(1);
  Wire.write(estado);
  Wire.write(secuencia.length());
  for(int i=0, l=secuencia.length(); i<l; i++){
    Wire.write(secuencia[i]);
  }
  Wire.endTransmission();
}

void recuperaEstado(){
  Wire.begin(2);
  Wire.onReceive(actualizaEstado);
}

void actualizaEstado(int howMany){

   
  int secuencia_l;
  String sec = "";
  char c;

  i = Wire.read();
  secuencia_l = Wire.read();
  for(int j=0; j<secuencia_l; j++){
    c = Wire.read();
    sec = sec + c;
  }

  secuencia = sec;
}

