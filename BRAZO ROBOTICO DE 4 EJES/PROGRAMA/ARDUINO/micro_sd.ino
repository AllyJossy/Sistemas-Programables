 #include <SD.h>
#include <Wire.h>
File myFile;

void setup()
{
  Serial.begin(9600);
  
  SD.begin(9);
  
  guardarEstado();
}

void loop()
{
  recuperarEstado();
  Serial.println(getSecuencia());
  Serial.println(getUltimoEstado());
}

void setUltimoEstado(int estado){
  myFile = SD.open("estado.txt", FILE_WRITE);
  myFile.println(estado);
  myFile.close();  
}

void setSecuencia(String secuencia){
  myFile = SD.open("secu.txt", FILE_WRITE);
  myFile.println(secuencia);
  myFile.close();
}


int getUltimoEstado(){
  int estado=0;
  String cad;
  char c;
  
  myFile = SD.open("estado.txt", FILE_READ);
  while (myFile.available()) {
    c = myFile.read();
    if( c == 10 ){
      estado = cad.toInt();
      cad = "";
    }else{
      cad = cad + c;
    }
  }
  myFile.close();
  return estado;
}


String getSecuencia(){
  String cad_a = "", cad_b = "";
  char c;
  
  myFile = SD.open("secu.txt", FILE_READ);
  while (myFile.available()) {
    c = myFile.read();
    if( c == 10 ){
      cad_a = cad_b;
      cad_b = "";
    }else{
      cad_b = cad_b + c;
    }
  }
  myFile.close();
  return cad_a;
}


void guardarEstado(){
  Wire.begin(1);
  Wire.onReceive(recibeEstado);  
}

void recibeEstado(int howMany){
  int estado;
  int secuencia_l;
  String secuencia = "";
  char c;

  estado = Wire.read();
  secuencia_l = Wire.read();
  for(int i=0; i<secuencia_l; i++){
    c = Wire.read();
    secuencia = secuencia + c;
  }

  setUltimoEstado(estado);
  setSecuencia(secuencia);

}


void recuperarEstado(){
  int estado = getUltimoEstado();
  String secuencia = getSecuencia();
  
  Wire.begin();
  Wire.beginTransmission(2);
  Wire.write(estado);
  Wire.write(secuencia.length());
  for(int i=0, l=secuencia.length(); i<l; i++){
    Wire.write(secuencia[i]);
  }
  Wire.endTransmission();
}

