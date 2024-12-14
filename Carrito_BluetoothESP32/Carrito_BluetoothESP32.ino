#include <Arduino.h>
#include "BluetoothSerial.h"


// Inicialización del bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Creamos el objeto Bluetooth
BluetoothSerial SerialBT;

// Creamos una variable para probar el carrito desde la computadora 

String comando = "";

// Seteamos velocidad maxima
int velocidad_max = 200;

// ----- Motor Derecho ----//

const int in1 = 25;
const int in2 = 26;

// ---- Definimos los canales derecho----//

int canal1MotorD = 0;
int canal2MotorD = 1;


// ---- ciclo de trabajo o velocidad en bits del motor derecho----//

int velocidad_derecho = velocidad_max; // Esta en bits, va de 0 a 255

// ----- Motor Izquierdo ----//

const int in3 = 33;
const int in4 = 32;

// ---- Definimos los canales izquierdo----//

int canal1MotorI = 2;
int canal2MotorI = 3;

// ---- ciclo de trabajo o velocidad en bits del motor derecho----//

int velocidad_izquierdo = velocidad_max; // Esta en bits, va de 0 a 255

// --- Parámetros para los motores ---- //

int frecuencia = 10000; // Esta frecuencia funciona para que no suene el encoder en caso de que tengamos encoder
int resolucion = 8; // Se refiere a 8 bits


// ---- Luces del Carrito --- //

const int LEDs = 27;

void setup() {
  Serial.begin(115200);
  // Para relacionar los pines de entrada con los canales

  // Seteamos el objeto instanciado anteriormente con la libreria Serial Bluetooth
  SerialBT.begin("Robot_Diferencial"); // Cuando abramos el Bluetooth, este va a ser el nombre que nos va a salir como nombre del carrito

  // ------ Motor Derecho -------- //
  // Configuración 1 motor derecho
  ledcSetup(canal1MotorD, frecuencia, resolucion); // Esta es una función propia del ESP32
  ledcAttachPin(in1, canal1MotorD); // Unimos el pin con el canal correcto

  // Configuración 2 motor derecho
  ledcSetup(canal2MotorD, frecuencia, resolucion);
  ledcAttachPin(in2, canal2MotorD); // Unimos el pin con el canal correcto


  // ------ Motor Izquierdo -------- //

  ledcSetup(canal1MotorI, frecuencia, resolucion); // Esta es una función propia del ESP32
  ledcAttachPin(in3, canal1MotorI); // Unimos el pin con el canal correcto

  // Configuración 2 motor derecho
  ledcSetup(canal2MotorI, frecuencia, resolucion);
  ledcAttachPin(in4, canal2MotorI); // Unimos el pin con el canal correcto

  // Bien importante, siempre comenzar con los motores apagados. 
  // --- Luces del Carrito --- //
  pinMode(LEDs, OUTPUT);

}

void loop() {
  // Llamamos a la funcion eventoSerial
  if(SerialBT.available()) eventoSerial(); // Con esto llamamos a nuestra funcion eventoSerial y la condicionamos a que el objeto BT este disponible.
  
  if(comando.length > 0){
    
    SerialBT.println(comando); // Con este comando imprimimos en pantalla el caracter que se envio desde el puerto serial 
    
    // Instruccion de que si le llega el caracter F vaya hacia adelante. 
    if(comando == "F"){
      adelante();
    }
    
    // Instruccion de que si le llega el caracter B vaya hacia atras. 
    if(comando == "B"){
      atras();
    }

    // Instruccion de que si le llega el caracter R vaya hacia la derecha. 
    if(comando == "R"){
      derecha();
    }

    // Instruccion de que si le llega el caracter L vaya hacia la izquierda. 
    if(comando == "L"){
      izquierda();
    }
  }
}

// ---- Creamos las funciones ---- //

void adelante(){

  giroHorario(canal1MotorD, canal2MotorD, velocidad_derecho); 
  giroHorario(canal1MotorI, canal2MotorI, velocidad_izquierdo); 

}

void atras(){

  giroAntihorario(canal1MotorD, canal2MotorD, velocidad_derecho); 
  giroAntihorario(canal1MotorI, canal2MotorI, velocidad_izquierdo);  
}

void izquierda(){

  giroHorario(canal1MotorD, canal2MotorD, velocidad_derecho); 
  giroAntihorario(canal1MotorI, canal2MotorI, velocidad_izquierdo);  
  
}

void derecha(){

  giroAntihorario(canal1MotorD, canal2MotorD, velocidad_derecho); 
  giroHorario(canal1MotorI, canal2MotorI, velocidad_izquierdo); 
}

void detenerse(){

  pararMotor(canal1MotorD, canal2MotorD);
  pararMotor(canal1MotorI, canal2MotorI); 
}
void giroHorario(int canal1, int canal2, int cv) {
  ledcWrite(canal1, cv); // Activar el motor derecho
  ledcWrite(canal2, 0);  // Apagar el motor izquierdo
  Serial.println("Esta Girando hacia la derecha");
}

void giroAntihorario(int canal1, int canal2, int cv) {
  ledcWrite(canal1, 0);  // Apagar el motor derecho
  ledcWrite(canal2, cv); // Activar el motor izquierdo
  Serial.println("Esta Girando hacia la izquierda");
}

void pararMotor(int canal1, int canal2) {
  ledcWrite(canal1, 0);  // Apagar el motor derecho
  ledcWrite(canal2, 0);  // Apagar el motor izquierdo
  Serial.println("Los motores están detenidos");
}


// Creamos una funcion para la recepcion de los datos
void eventoSerial() {
  while (SerialBT.available()){ // Con esta fucion verificamos que haya datos en el protocolo BT UART
      char inChar = (char)SerialBT.read(); // Con esta linea creamos una variable que va a recibir directo de la lectura del protocolo BT UART
      comando += inChar; // Con esta funcion concatenamos todos los datos que lleguen de comando
  }
 }


