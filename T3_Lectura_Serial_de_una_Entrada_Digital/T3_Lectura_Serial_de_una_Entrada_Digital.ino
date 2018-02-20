/*
--------------------------------------
Lectura serial de una entrada digital
--------------------------------------
Leer una entrada digital y mostrar por la pantalla del
computador (consola serial) el estado del pulsador
cuando es oprimido
Cosas de Mecatrónica y Tienda de Robótica
*/
//------------------------------------
//Declara puertos de entradas y salidas
//------------------------------------
int boton=2; //Pin donde se encuentra el pulsador, entrada
//------------------------------------
//Funcion principal
//------------------------------------
void setup() // Se ejecuta cada vez que el Arduino se inicia
{
//Configuración
pinMode(boton,INPUT); //Configurar el boton como una entrada
Serial.begin(9600); //Inicia comunicación serial
}
//------------------------------------
//Funcion ciclicla
//------------------------------------
void loop() // Esta funcion se mantiene ejecutando
{ // cuando este energizado el Arduino
//Guardar en una variable entera el valor del boton 0 ó 1
int estado = digitalRead(boton);
//Condicional para saber estado del pulsador
if (estado==1)
{
// Pulsado
Serial.println("Pulsado"); //Imprime en la consola serial
} // "Pulsado"
else
{
// No esta pulsado
Serial.println("NO Pulsado"); //Imprime en la consola serial
} // "NO Pulsado"
delay(100); //Retardo para la visualización de datos en la consola
}
//Fin programa
