// Autor: Alison Joselyn Fernández Martínez
// Practica: Semaforo Durmiente
/* En el siguiente programa se muestra un ejemplo de semaforo durmiente con Leds.
Se tienen 2 semaforos, el de automoviles que cuenta con 3 leds (verde, amarillo y rojo) y
  el semaforo de peatones que cuenta con 2 leds (verde y rojo).
Se inicia con el led verde de los automoviles encendido y el led rojo de los peatones apagado.
Se muestran 2 casos: 
  1.- Al presionar el boton blanco se enciende un led azul indicando que ya se presiono el boton.
      A continuacion el led verde de los automoviles empieza a parpadear y se apaga, 
      el led rojo de los peatones se apaga al igual que el led azul del boton,
      el led amarillo de los automoviles se enciende al igual que el led verde de los peatones,  
      el led amarillo de los automoviles se apaga y se enciende el led rojo de los automoviles,
      posteriormente parpadea el led verde de los peatones y se apaga al igual que 
      el led rojo de los automoviles, 
      y se vuelven a encender el led verde de los automoviles y el led rojo de los peatones,
      hasta que se vuelva a presionar un boton.
  2.- Al perionar el boton negro se enciende un led rojo indicando que ya se presiono el boton.
      Tiene un funcionamiento parecido al primer caso, dado que funciona igual hasta 
      el momento en que se apaga el led verde de los automoviles y el led rojo de los peatones,
      posterior a eso los tiempos se incrimentan al doble que en el caso anterior dado que es un 
      semaforo pensado en personas con capacidades diferentes que tardan mayor tiempo en 
      cruzar la calle, otra diferencia es que el led rojo del boton permanece prendido hasta que 
      el led verde de los automoviles y el led rojo de los peatones vuelven a estar encendidos.

Asi mismo se agrego un potenciometro para regular la velocidad del funcionamiento de los semaforos,
  depemdiendo de donde se encuentre situado funcionará más rápido o lento.
      */
//Variables      
int crojo = 5;      //led rojo de los automoviles
int camarillo = 4;  //led amarillo de los automoviles
int cverde = 3;     //led verde de los automoviles
int projo = 6;      //led rojo de los peatones
int pverde = 7;     //led verde de los peatones
int pushrojo = 10;  //led rojo del boton
int pushazul = 13;  //led azul del boton
int pushn = 9;      //boton negro
int pushb = 12;     //boton blanco
int frec = 1000;    //variable de frecuencia de la duracion de los leds

void setup() {      //codigo de inicio
  pinMode(crojo, OUTPUT);       //pin de salida
  pinMode(camarillo, OUTPUT);   //pin de salida
  pinMode(cverde, OUTPUT);      //pin de salida
  pinMode(projo, OUTPUT);       //pin de salida
  pinMode(pverde, OUTPUT);      //pin de salida
  pinMode(pushrojo, OUTPUT);    //pin de salida
  pinMode(pushazul, OUTPUT);    //pin de salida
  pinMode(pushb, INPUT);        //pin de entrada
  pinMode(pushn, INPUT);        //pin de entrada
}

void loop() {     //codigo principal
  frec = analogRead(A0); //se asigna el valor del potenciometro como frecuencia
  digitalWrite(projo, HIGH);              //led encendido
  digitalWrite(cverde, HIGH);             //led encendido
  if (digitalRead(pushb) == LOW) {        //si el boton blanco es presionado 
      digitalWrite(pushazul, HIGH);       //encender led azul del boton
      activaCambio();                     //inicia la funcion activaCambio()
      cambioSemaforo();                   //inicia la funcion cambioSemaforo()
  } else if (digitalRead(pushn) == LOW) { // ...si no, si el boton negro es presionado
      digitalWrite(pushrojo, HIGH);       //encender el led rojo
      activaCambio();                     //inicia la funcion activaCambio()
      frec = frec * 2;                    //duplicar la frecuencia
      cambioSemaforo();                   //inicia la funcion cambioSemaforo()
  } 
}

void activaCambio() {
  delay(frec * 2);                //Esperar el periodo de frecuencia * 2
  for (int i = 0; i < 3; i++) {
    digitalWrite(cverde, LOW);    //Apagar led
    delay(frec / 2);
    digitalWrite(cverde, HIGH);   //Encender led
    delay(frec / 2);
  }
}
void cambioSemaforo(){
  digitalWrite(pushazul, LOW);    //Apagar led
  digitalWrite(cverde, LOW);      //Apagar led
  digitalWrite(camarillo, HIGH);  //Encender led
  delay(frec * 2);
  digitalWrite(camarillo, LOW);   //Apagar led  
  digitalWrite(projo, LOW);       //Apagar led
  digitalWrite(pverde, HIGH);     //Encender led
  digitalWrite(crojo, HIGH);      //Encender led
  delay(frec * 4);
  for (int i = 0; i < 6; i++) {
    digitalWrite(pverde, LOW);    //Apagar led
    delay(frec / 2);
    digitalWrite(pverde, HIGH);   //Encender led
    delay(frec / 2);
  }
  digitalWrite(pverde, LOW);      //Apagar led
  digitalWrite(crojo, LOW);       //Apagar led
  digitalWrite(pushrojo, LOW);    //Apagar led
}

