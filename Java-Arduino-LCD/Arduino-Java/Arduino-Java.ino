/*Programa de Arduino-Java con LCD
   El programa despliega:
      Temperatura
      La hora
      Mensajes:
          1. CustomCaracter (Monito bailando)
          2. Display (Parpadeo de mensaje
          3. Serial Display (Entrada de mensjae por Serial)
*/

/*--------------------------------------------------------------
  LiquidCrystal
  --------------------------------------------------------------*/
#include <LiquidCrystal.h> // Incluye la libreria LiquidCrystal

//Inincializa la libreria asociando cada pin de interfaz LCD necesaria
//con el numero de pin de arduino que esta conectado
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD

/*--------------------------------------------------------------
  Variables para leer la temperatura
  --------------------------------------------------------------*/
#define sensorT 2
float voltaje = 0;      // Variable para guardar el voltaje
float temperatura = 0;  // Variable para guardar la temperatura

/*--------------------------------------------------------------
  Funciones de fecha y hora utilizando un RTC DS3231
  conectado vía I2C y libreria Wire
  --------------------------------------------------------------*/
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = { "Domingo", "Lunes", "Martes",
                              "Miercoles", "Jueves", "Viernes", "Sabado"
                            };

/*--------------------------------------------------------------
  Variables para los botones que despliegan la información
  --------------------------------------------------------------*/
int pb_temperatura = 6;   // Botón para mostrar la temperatura
int pb_hora = 7;   // Botón para mostrar la hora
int pb_mensaje1 = 8;  // Botón para mostrar el mensaje 1
int pb_mensaje2 = 9;  // Botón para mostrar el mensaje 2
int pb_mensaje3 = 10; // Botón para mostrar el mensaje 3

/*--------------------------------------------------------------
  Variables para la conexion con java
  --------------------------------------------------------------*/
int Byte_entrada = 0;

/*--------------------------------------------------------------
  Caracteres personalizados para el mensaje 1
  --------------------------------------------------------------*/
byte heart[8] = { //Caracter de corazon
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] = { //Caracter de Sonrisa
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] = { // Carater brazos abajo
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = { // Caracter brazos arriba

  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

void setup() {
#ifndef ESP8266
  while (!Serial);
#endif

  Serial.begin(9600); // Abre el puerto serie

  if (! rtc.begin()) {
    Serial.println("RTC no encontrado");
    lcd.print("RTC no encontrado");
    while (1);
  }

  // Inicializar el lcd y configurar el numero de columnas y renglones
  lcd.begin(COLS, ROWS);
  // Crear un nuevo caracter de corazon
  lcd.createChar(0, heart);
  // Crear un nuevo caracter de sonrisa
  lcd.createChar(1, smiley);
  // Crear un nuevo caracter
  lcd.createChar(2, frownie);
  // Crear un nuevo caracter de brazos abajo
  lcd.createChar(3, armsDown);
  // Crear un nuevo caracter de brazos arriba
  lcd.createChar(4, armsUp);


  pinMode(pb_temperatura, INPUT);   // Configurar el boton de la temperatura como entrada
  pinMode(pb_hora, INPUT);   // Configurar el boton de la hora como entrada
  pinMode(pb_mensaje1, INPUT);  // Configurar el boton del mensaje 1 como entrada
  pinMode(pb_mensaje2, INPUT);  // Configurar el boton del mensaje 2 como entrada
  pinMode(pb_mensaje3, INPUT);  // Configurar el boton del mensaje 3 como entrada
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alison");
  lcd.setCursor(7, 1);
  lcd.print("Fernandez");

  if (digitalRead(pb_temperatura) == LOW) {         // Si el boton de la temperatura es presionado
    Serial.println("TEMPERATURA!!!!");
    lcd.clear();
    leertemperatura();
  } else if (digitalRead(pb_hora) == LOW) {  // Si el boton de la hora es presionado
    Serial.println("HORA!!!!");
    lcd.clear();
    leerhora();
  } else if (digitalRead(pb_mensaje1) == LOW) { // Si el boton del mensaje 1 es presionado
    Serial.println("MENSAJE 1!!!!");
    lcd.clear();
    mensaje1();
  } else if (digitalRead(pb_mensaje2) == LOW) { // Si el boton del mensaje 2 es presionado
    Serial.println("MENSAJE 2!!!!");
    lcd.clear();
    mensaje2();
  } else if (digitalRead(pb_mensaje3) == LOW) { // Si el boton del mensaje 3 es presionado
    lcd.clear();
    mensaje3();
  } else if (Serial.available() > 0) {       // Si el puerto serial está disponible
    Byte_entrada = Serial.read();     // Se leen los datos transmitidos desde java
    if (Byte_entrada == '0') {        // Si el boton de la temperatura es presionado en java
      lcd.clear();
      leertemperatura();
    } else if (Byte_entrada == '1') { // Si el boton de la hora es presionado en java
      lcd.clear();
      leerhora();
    } else if (Byte_entrada == '2') { // Si el boton del mensaje 1 es presionado en java
      lcd.clear();
      mensaje1();
    } else if (Byte_entrada == '3') { // Si el boton del mensaje 2 es presionado en java
      lcd.clear();
      mensaje2();
    } else if (Byte_entrada == '4') { // Si el boton del mensaje 3 es presionado en java
      lcd.clear();
      mensaje3();
    } 
  } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alison");
      lcd.setCursor(7, 1);
      lcd.print("Fernandez");
    }
}

void leertemperatura() {
  voltaje = analogRead(sensorT) * 3.3 / 1023;
  temperatura = voltaje * 100;
  Serial.println(temperatura);
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.setCursor(9, 1);
  lcd.print(temperatura);
  lcd.print(" C");
  delay(500);
}

void leerhora() {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  lcd.setCursor(0, 0);
  lcd.print(now.year(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.day(), DEC);
  lcd.setCursor(0, 1);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(" ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);

  delay(1000);
}

void mensaje1() {
  // Posiciona el cursor arriba a la izquierda
  lcd.setCursor(0, 0);

  // Imprime el mensaje en el lcd
  lcd.print("I ");
  lcd.write(byte(0)); // Cuando se llama a lcd.write() '0' se deve convertir como byte
  lcd.print(" Arduino! ");
  lcd.write((byte)1);
  // Lee el potenciometro en A0
  int sensorReading = analogRead(A0);
  // Asignar el resultado a  200 - 1000:
  int delayTime = map(sensorReading, 0, 1023, 200, 1000);
  // Posicionar el cursor en la fila inferior, 5a posicion:
  lcd.setCursor(4, 1);
  // Dibujar el muñeco, brazos abajo:
  lcd.write(3);
  delay(delayTime);
  lcd.setCursor(4, 1);
  // Dibujar sus brazos arriba:
  lcd.write(4);
  delay(delayTime);
}

void mensaje2 () {
  // Posiciona el cursor arriba a la izquierda
  lcd.setCursor(0, 0);
  lcd.print("Sistemas");
  // Posiciona el cursor abajo en la posicion 5
  lcd.setCursor(4, 1);
  lcd.print("Programables");
  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
}

void mensaje3() {
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}

