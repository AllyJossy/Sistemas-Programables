#include <SD.h>
#include <Wire.h>
File myFile;

String secuencia="abcde";
int estado=0;
int inter = 500;

char Byte_entrada;   // Variable para leer el valor del boton presionado en java

bool pause=true;

void setup() {
#ifndef ESP8266
  while (!Serial);
#endif
  SD.begin(9);
  Serial.begin(9600);
  secuencia = getSecuencia();
  estado = getUltimoEstado();
  //actualizarSecuencia("abcdefzaghdyaf");
}

void loop() {
  Byte_entrada = Serial.read();   // Se leen los datos transmitidos desde java
  if (Byte_entrada == '0') {        // Si el boton de inicio es presionado en java
    pause = false;
    secuencia= "abcdefjaghdiaf";
    ejecutaFuncion(Byte_entrada);
  } else if (Byte_entrada == '1') { // Si el boton de abortar es presionado en java
    estado = 0;
    pause=true;
    ejecutaFuncion(Byte_entrada);
    //se();
  }

  if(!pause) se();
}

void se(){
  estado = estado >= secuencia.length() - 1 ? 0 : estado + 1;
  setUltimoEstado(estado);
  ejecutaFuncion( secuencia[estado] );
  delay(inter);
}

/*
  Se ingresa el string que programa el brazo
*/
void actualizarSecuencia(String secu) {
  setSecuencia(secu);
  secuencia = getSecuencia();
}


void ejecutaFuncion(char funcion) {
  Wire.begin();
  Wire.beginTransmission(1);
  Wire.write(funcion);
  Wire.endTransmission();
}

void setUltimoEstado(int estado) {
  myFile = SD.open("estado.txt", FILE_WRITE);
  myFile.println(estado);
  myFile.close();
}

void setSecuencia(String secuencia) {
  SD.remove("secu.txt");
  myFile = SD.open("secu.txt", FILE_WRITE);
  myFile.println(secuencia);
  myFile.close();
}


int getUltimoEstado() {
  int estado = 0;
  String cad;
  char c;

  myFile = SD.open("estado.txt", FILE_READ);
  while (myFile.available()) {
    c = myFile.read();
    if ( c == 10 ) {
      estado = cad.toInt();
      cad = "";
    } else {
      cad = cad + c;
    }
  }
  myFile.close();
  return estado;
}


String getSecuencia() {
  String cad_a = "", cad_b = "";
  char c;

  myFile = SD.open("secu.txt", FILE_READ);
  while (myFile.available()) {
    c = myFile.read();
    if ( c == 10 ) {
      cad_a = cad_b;
      cad_b = "";
    } else {
      cad_b = cad_b + c;
    }
  }
  myFile.close();
  return cad_a;
}
