Autor: Alison Joselyn Fernández Martínez
Practica: Semaforo Durmiente
Software: Se utilizo software libre para programar y diagramar: Arduino y Fritzing.

En el siguiente programa se muestra un ejemplo de semaforo durmiente con Leds.

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

Materiales:
* Arduino 1
* Cable USB tipo AB
* 2 leds de 5mm rojos
* 2 leds de 5mm verdes
* 1 led de 5mm amarillo
* 1 led cuadrado rojo
* 1 led cuadraro azul
* 7 resistencias de 330 ohms
* 2 push button
* 2 resistencias de 1k ohm
* 1 potenciometro de 10 k ohms
* Conectores MM
* 1 protoboard

DIAGRAMA:
![Imagen Diagrama](DIAGRAMA/SemaforoDurmiente.jpg "Diagrama")

CIRCUITO:
![Imagen Circuito](IMAGENES/sd1.jpg "Circuito")

SOFTWARE:
![Imagen Fritzing](SOFTWARELIBRE/Fritzing.png "Fritzing")
![Imagen Arduino](SOFTWARELIBRE/Arduino.png "Arduino")