Autor: Alison Joselyn Fernández Martínez
Practica: Programa de Java-Arduino con LCD
Software: Se utilizo software libre para programar y diagramar: Arduino y Fritzing.

Programa de Arduino-Java con LCD
   El programa empieza con un mensaje, al presionar los botones despliega:
      Temperatura
      La hora
      Mensajes:
          1. CustomCaracter (Muñeco bailando)
          2. Display (Parpadeo de mensaje: Sistemas Programables)
          3. Serial Display (Entrada de mensaje por Serial o Java)

CONTENIDO:
	Java-Arduino-LCD
		Java-Arduino-LCD-ino: Programa de Arduino
		Readme.txt: Contiene la informacion del programa

		DIAGRAMA: Contiene el diagrama del circuito
		IMAGENES: Contiene imagenes de evidencia del funcionamiento del programa.
		Java_Arduino_LCD: Contiene el programa en Java con la interfaz
		SOFTWARELIBRE: Contiene capturas que muestran el uso  de Software Libre
		VIDEOS: Contiene videos de evidencia del funcionamiento del programa.

En el siguiente programa se muestra un ejemplo de un programa de Arduino con Java que mide la temperatura, lee la hora y muestra mensajes.

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

Materiales:
* 1 Arduino Uno
* Cable USB tipo AB
* Conectores MM
* 1 Protoboard
* 1 Pantalla LiquidCrystal
* 1 Sensor de Temperatura LM35
* 1 Modulo RTC DS3231
* 5 Push button
* 2 Potenciometro de 10 k ohms
* 5 Resistencias de 1k ohm
* 1 Resistencia de 220 ohms

