#include "LowPower.h"

const int contacto = 2; //Pin asignado al reed switch
const int led = 13; //Pin asignado al LED
int value = LOW;
int ledRojo = 9; //Declara Pin LED Rojo
int ledVerde = 10; //Declara Pin LED Verde
int ledAzul = 11; //Declara Pin LED Azul

//------------------------------------
//Funcion principal
//------------------------------------
void setup() { // Se ejecuta cada vez que el Arduino se inicia
  pinMode(contacto, INPUT_PULLUP); //El reed switch como una entrada
  pinMode(led, OUTPUT); //El LED como una salida
  pinMode(ledRojo, OUTPUT); //El LED Rojo como una salida
  pinMode(ledVerde, OUTPUT); //El LED Verde como una salida
  pinMode(ledAzul, OUTPUT); //El LED Azul como una salida
}

//------------------------------------
//Funcion ciclica
//------------------------------------
void loop() { // Esta función se mantiene ejecutando
  value = digitalRead(contacto);
  color(0, 0, 0);
  if (value == LOW) {
    parpadeo();
  } else{
    colores();
  }
  apagado();
}

void apagado(){
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
}

//------------------------------------
//Funcion led
//------------------------------------
void parpadeo() { // Esta funcion se mantiene ejecutando
  if (value == LOW) {
    digitalWrite(led, HIGH); //Prende el LED
    delay(20); //Tiempo
    digitalWrite(led, LOW); //Apaga el LED
    // Si el iman esta lejos del reed switch
  } else {
    digitalWrite(led, LOW); //Mantiene apagado el LED
  } //Fin del if
}

//------------------------------------
//Funcion color
//------------------------------------
void color(int rojo, int verde, int azul) { //Escritura de PWM del color Rojo
  analogWrite(ledRojo, 255 - rojo); //Escritura de PWM del color Verde
  analogWrite(ledVerde, 255 - verde);
  //Escritura de PWM del color Azul
  analogWrite(ledAzul, 255 - azul);
}

void colores(){
    // Llamado a la función Color que recibe
    // 1er posicion: Intensidad Rojo
    // 2da posición: Intensidad Verde
    // 3ra posición: Intensidad Azul
    color(255, 0, 0);     //Rojo
    delay(500);
    color(0, 255, 0);     //Verde
    delay(500);
    color(0, 0, 255);     //Azul
    delay(500);
    color(255, 255, 255); //Blanco
    delay(500);
    color(255, 0, 255);   //Magenta
    delay(500);
    color(255, 128, 0); //Naranja
    delay(500);
}
//Fin del programa
