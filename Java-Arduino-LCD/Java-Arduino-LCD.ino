//Autor: Alison Joselyn Fernández Martínez
//Practica: Semaforo Durmiente
//Software: Se utilizo software libre para programar y diagramar: Arduino y Fritzing.

/*
Programa de Arduino-Java con LCD
   El programa empieza con un mensaje, al presionar los botones despliega:
      Temperatura
      La hora
      Mensajes:
          1. CustomCaracter (Muñeco bailando)
          2. Display (Parpadeo de mensaje: Sistemas Programables)
          3. Serial Display (Entrada de mensaje por Serial o Java)

En el siguiente programa se muestra un ejemplo de un programa de Arduino con Java que mide la temperatura, 
lee la hora y muestra mensajes.

Inicia con el mensaje: Alison Fernández

Se presentan 10 casos:
  En Arduino:
    1.- Al presionar el boton azul del circuito se muestra la temperatura que se lee desde un sensor de temperatura que se encuentra en el circuito.

    2.- Al presionar el boton plateado del circuito se muestra la hora que se lee desde un modulo rtc Reloj de tiempo Real de alta precision.

    3.- Al presionar el boton rojo del circuito se muestra un mensaje que dice: I Love Arduino y muestra un muñeco bailando.

    4.- Al presionar el boton dorado del circuito se muestra un mensaje intermitente que dice: Sistemas Programables.

    5.- Al presionar el boton negro del circuito lee un mensaje desde el Serial, al presionar nuevamente el boton se muestra el mensaje en la pantalla LCD.

  En Java: 
    1.- Al presionar el boton de Temperatura  de la interfaz se muestra la temperatura que se lee desde un sensor de temperatura que se encuentra en el circuito.

    2.- Al presionar el boton de Hora de la interfaz se muestra la hora que se lee desde un modulo rtc Reloj de tiempo Real de alta precision.

    3.- Al presionar el boton de Mensaje 1 de la interfaz se muestra un mensaje que dice: I Love Arduino y muestra un muñeco bailando.

    4.- Al presionar el boton de Mensaje 2 de la interfaz se muestra un mensaje intermitente que dice: Sistemas Programables.

    5.- Al llenar el Input Text y presionar el boton Mensaje 3 de la interfaz lee el mensaje de Java y se muestra el mensaje en la pantalla LCD.
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
#define sensorT 2       // Variable para el sensor de Temperatura en el pin 2
float voltaje = 0;      // Variable para guardar el voltaje
float temperatura = 0;  // Variable para guardar la temperatura

/*--------------------------------------------------------------
  Funciones de fecha y hora utilizando un RTC DS3231
  conectado vía I2C y libreria Wire
  --------------------------------------------------------------*/
#include <Wire.h>
#include "RTClib.h"   // Libreria de RTC

RTC_DS3231 rtc;

// Arreglo para establecer los dias de la semana 
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
int Byte_entrada = 0;   // Variable para leer el valor del boton presionado en java

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

  Serial.begin(9600); // Abre el puerto serial

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
  if (digitalRead(pb_temperatura) == LOW) {         // Si el boton de la temperatura es presionado
    lcd.clear();          // Limpia la pantalla LCD
    leertemperatura();    // Ejecuta la funcion leertemperatura()
  } else if (digitalRead(pb_hora) == LOW) {  // Si el boton de la hora es presionado
    lcd.clear();          // Limpia la pantalla LCD
    leerhora();           // Ejecuta la funcion leerhora()
  } else if (digitalRead(pb_mensaje1) == LOW) { // Si el boton del mensaje 1 es presionado
    lcd.clear();          // Limpia la pantalla LCD
    mensaje1();           // Ejecuta la funcion mensaje1()
  } else if (digitalRead(pb_mensaje2) == LOW) { // Si el boton del mensaje 2 es presionado
    lcd.clear();          // Limpia la pantalla LCD
    mensaje2();           // Ejecuta la funcion mensaje2()
  } else if (digitalRead(pb_mensaje3) == LOW) { // Si el boton del mensaje 3 es presionado
    lcd.clear();          // Limpia la pantalla LCD
    mensaje3();           // Ejecuta la funcion mensaje3()
  } else if (Serial.available() > 0) {       // Si el puerto serial está disponible
    Byte_entrada = Serial.read();     // Se leen los datos transmitidos desde java
    if (Byte_entrada == '0') {        // Si el boton de la temperatura es presionado en java
      lcd.clear();        // Limpia la pantalla LCD
      leertemperatura();  // Ejecuta la funcion leertemperatura()
    } else if (Byte_entrada == '1') { // Si el boton de la hora es presionado en java
      lcd.clear();        // Limpia la pantalla LCD
      leerhora();         // Ejecuta la funcion leerhora()
    } else if (Byte_entrada == '2') { // Si el boton del mensaje 1 es presionado en java
      lcd.clear();        // Limpia la pantalla LCD
      mensaje1();         // Ejecuta la funcion mensaje1()
    } else if (Byte_entrada == '3') { // Si el boton del mensaje 2 es presionado en java
      lcd.clear();        // Limpia la pantalla LCD
      mensaje2();         // Ejecuta la funcion mensaje2()
    } else if (Byte_entrada == '4') { // Si el boton del mensaje 3 es presionado en java
      lcd.clear();        // Limpia la pantalla LCD
      mensaje3();         // Ejecuta la funcion mensaje3()
    } 
  } else {
      lcd.clear();            // Limpia la pantalla LCD
      lcd.setCursor(0, 0);    // Establece el cursor de la pantalla LCD en la columna 0, renglon 0
      lcd.print("Alison");    // Imprime el mensaje 
      lcd.setCursor(7, 1);    // Establece el cursor de la pantalla LCD en la columna 7, renglon 1
      lcd.print("Fernandez"); // Imprime el mensaje 
    }
}

void leertemperatura() {  // Funcion que lee la temperatura del sensor LM35
  voltaje = analogRead(sensorT) * 3.3 / 1023;   //Lee el valor del sensor
  temperatura = voltaje * 100;  // Realiza la operacion para sacar el valor de la remperatura
  Serial.println(temperatura);  // Imprime el valor de la temperatura en el serial
  lcd.setCursor(0, 0);          // Establece el cursor de la pantalla LCD en la columna 0, renglon 0
  lcd.print("Temperatura: ");   // Imprime el mensaje
  lcd.setCursor(9, 1);          // Establece el cursor de la pantalla LCD en la columna 9, renglon 1
  lcd.print(temperatura);       // Imprime la temperatura
  lcd.print(" C");              // Imprime el mensaje
  delay(500);                   // Espera medio segundo
}

void leerhora() {   // Funcion que lee la temperatura del modulo rTC
  DateTime now = rtc.now();

// Imprime en el serial
  Serial.print(now.year(), DEC);  // Imprime el año
  Serial.print('/');              // Imprime el mensaje
  Serial.print(now.month(), DEC); // Imprime el mes
  Serial.print('/');              // Imprime el mensaje
  Serial.print(now.day(), DEC);   // Imprime el dia
  Serial.print(" ");              // Imprime un espacio  
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);  // Imprime el dia de la semana
  Serial.print(" ");                // Imprime un espacio
  Serial.print(now.hour(), DEC);    // Imprime la hora
  Serial.print(':');                // Imprime el mensaje
  Serial.print(now.minute(), DEC);  // Imprime los minutos
  Serial.print(':');                // Imprime el mensaje
  Serial.print(now.second(), DEC);  // Imprime los segundos
  Serial.println();                 // Imprime un salto de linea

// Imprime en la pantalla LCD
  lcd.setCursor(0, 0);    // Establece el cursor de la pantalla LCD en la columna 0, renglon 0
  lcd.print(now.year(), DEC);  // Imprime el año
  lcd.print('/');              // Imprime el mensaje
  lcd.print(now.month(), DEC); // Imprime el mes
  lcd.print('/');              // Imprime el mensaje
  lcd.print(now.day(), DEC);   // Imprime el dia
  lcd.setCursor(0, 1);    // Establece el cursor de la pantalla LCD en la columna 0, renglon 1
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);  // Imprime el dia de la semana
  lcd.print(" ");                // Imprime un espacio
  lcd.print(now.hour(), DEC);    // Imprime la hora
  lcd.print(':');                // Imprime el mensaje
  lcd.print(now.minute(), DEC);  // Imprime los minutos
  lcd.print(':');                // Imprime el mensaje
  lcd.print(now.second(), DEC);  // Imprime los segundos

  delay(1000);    // Espera 1 segundo
}

void mensaje1() { // Funcion que ejecuta el mensaje 1 que muestra un mensaje y un muñeco bailando
  lcd.setCursor(0, 0);  // Establece el cursor de la pantalla LCD en la columna 0, renglon 0

  // Imprime el mensaje en el lcd
  lcd.print("I ");
  lcd.write(byte(0));   // Cuando se llama a lcd.write() '0' se deve convertir como byte
  lcd.print(" Arduino! ");
  lcd.write((byte)1);
  int sensorReading = analogRead(A0);   // Lee el potenciometro en A0
  // Asignar el resultado a  200 - 1000:
  int delayTime = map(sensorReading, 0, 1023, 200, 1000);
  lcd.setCursor(4, 1);  // Posiciona el cursor en la columna 4, renglon 1
  lcd.write(3);         // Dibujar el muñeco, brazos abajo:
  delay(delayTime);     // Espera dependiendo del valor del potenciometro
  lcd.setCursor(4, 1);  // Posiciona el cursor en la columna 4, renglon 1
  lcd.write(4);         // Dibujar sus brazos arriba:
  delay(delayTime);     // Espera dependiendo del valor del potenciometro
}

void mensaje2 () {  // Funcion que ejecuta el mensaje 2 que muestra el mensaje intermitente
  lcd.setCursor(0, 0);        // Posiciona el cursor arriba a la izquierda, en la columna 0, renglon 0
  lcd.print("Sistemas");      // Imprime el mensaje
  lcd.setCursor(4, 1);        // Posiciona el cursor en la columna 4, renglon 1
  lcd.print("Programables");  // Imprime el mensaje
  lcd.noDisplay();            // Apaga el display
  delay(500);                 // Espera medio segundo
  lcd.display();              // Enciende el display
  delay(500);                 // Espera medio segundo
}

void mensaje3() { // Funcion que ejecuta el mensaje 3 que se lee desde Serial o Java
  if (Serial.available()) {   // Cuando los caracteres son recibidos desde el puerto serial
    delay(100);   // Espera a que llegue el mensaje
    lcd.clear();  // Limpia la pantalla LCD

    while (Serial.available() > 0) {     // Lee todos los caracteres
      lcd.write(Serial.read());   // Despliega los caracteres en la pantalla
    }
  }
}

