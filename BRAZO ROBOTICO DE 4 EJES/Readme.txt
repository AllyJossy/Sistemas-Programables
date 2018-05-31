Autores: Arvizu Ramirez Luis Alberto
		 Fernández Martínez Alison Joselyn 
Practica: Brazo Robótico de 4 Ejes
Software: Se utilizo software libre para programar y diagramar: Java, Arduino y Fritzing.

El propósito de esta práctica es desarrollar paso a paso un proyecto para controlar y programar un Brazo Robot, simulando las funciones básicas de un robot industrial.

El robot debe tener dos funciones básicas: 
    Programar: Registrar las posiciones de los brazos en tres dimensiones (cada registro 
    es un "paso", un programa consiste en una serie de pasos).     
    Ejecutar: Realice en secuencia las posiciones registradas en el "Programa". El robot ejecutará el programa hasta que se use el comando "ABORTAR". 

Características principales: 
    El proyecto se usa para controlar robots con  4 DOF ("Grados de libertad").     
    El robot se debe controlar en modo "REMOTO" (a través de una programa en java por medio del puerto serial).     
    La información para el usuario se podrá proporcionar a través de LEDS de colores, una pantalla LCD de 2 líneas y/ó sonido (un zumbador).
    Debe de contener un botón de paro de emergencia (Físico).
    Si existe un fallo y/o corte de energía, después de restablecerse la corriente el robot debe de continuar el programa (aunque este no se encuentre conectado a la aplicación).     
    Los brazos robóticos se pueden clasificar de acuerdo con el número de "articulaciones" o "Grados de libertad" (DOF) que tienen.             
    	-La "Base", o "Cintura", por lo general puede girar el brazo 180o o 360o, dependiendo del   tipo de Servo utilizado (aquí en este proyecto, se debe utilizar un motor a pasos para girar 360o)             
    	-El "Hombro" es el responsable de "levantar o bajar" el brazo verticalmente             
    	-El "Codo" hará que el brazo "avance o retroceda".             
    	-La "Garra" o "Pinza" funciona abriéndose o cerrándose para "agarrar cosas".

Aplicación de Java:
    Cuenta con un campo de texto y 4 botones diferentes:
	- Iniciar: Inicia el programa predeterminado del brazo
	- Abortar: Aborta en programa en ejecución. 
	- Campo de Texto: Recibe una cadena de texto con los pasos para crear un nuevo programa.
	- Enviar: EnEnvía los datos que se encuentran en el campo de texto para la ejecución del programa.
	- Instrucciones: Muestra las instrucciones del brazo.

Pasos:
	- a: Subir
	- b: Poner la base en la posición inicial
	- c: Bajar brazo
	- d: Abrir pinza
	- e: Adelante
	- f: Cerrar pinza
	- g: Girar base a la derecha
	- h: Acercar brazo a la base
	- i: Girar base a la izquierda
	- y: Mandar mensaje de que el brazo está cargado
	- z: Mandar mensaje de que el brazo no tiene carga

Materiales:
	* 2 Arduino Uno
	* 2 Cable USB tipo AB
	* 1 Protoboard
	* Conectores MM
	* 1 potenciometro de 10 k ohms
	* 1 Pantalla LiquidCrystal
	* 1 Resistencia de 220 ohms
	* LEDS de Colores
	* Zumbador
	* 1 Push Button
	* 1 Resistencia de 1 k ohm
	* 1 Brazo Robotico
	* 3 Servomotores
	* 1 Motor a Pasos
	* Modulo Micro SD
	* Pequeñas cajas que son transportadas por el brazo.

Materiales Carrito:
	* 2 Motores DC
	* 2 Leds
	* 1 Arduino Uno
	* 1 Cable USB tipo AB
	* 1 Protoboard
	* 1 Modulo Bluetooth HC-06
	* 1 Controlador L298 N Motor Surucu
	* 1 Bateria de 9v
	* 1 Power Bank

CONTENIDO:
	Readme.txt: Contiene la informacion del programa
	arm.jpg: Imagen de un Brazo Robótico
	brazo.png: Imagen que muestra el Brazo Robótico y sus articulaciones
	Brazo.png: Imagen muestra del Brazo Robotico Armado.
	DIAGRAMA: Contiene el diagrama del circuito
	IMAGENES: Contiene imagenes de evidencia del funcionamiento del programa.
	PROGRAMA: Contiene los programas en Java y Arduino para el funcionamiento del brazo.
		ARDUINO: Programas de Arduino para manejar el brazo y un Carrito como complemento.
			MasterWriter_Brazo_Java: Programa que se comunica con el programa en java y recibe las instrucciones, asi mismo envia a el MasterReader las instrucciones a ejecutar.
			MasterReader_Brazo_Java: Programa que recibe las instrucciones a ejecutar en el brazo.
			Carrito_Brazo: Programa para manejar el carrito como complemento al brazo robotico.
		JAVA: Contiene el programa en Java con la interfaz para manejar el brazo.
	SOFTWARE LIBRE: Contiene capturas que muestran el uso  de Software Libre.
