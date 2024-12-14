#include <ESP32Servo.h>


// Creamos un Objeto Servo

Servo miServo; 

// Determinamos donde conectaremos el servo
const int servoPin = 18; // GPIO 18

// Variable para almacenar el angulo 
int angulo = 90; // angulo inicial

void setup() {
  Serial.begin(115200);
  miServo.attach(servoPin); // Unimos el servo con el pin que declaramos
  Serial.println("Escrib un angulo entre 0 y 180 grados");
}

void loop() {
  // Verificador de datos en el puerto serial
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Asi dejamos que entren datos al serial
    int anguloNuevo = input.toInt(); // convertimos la variable input que hicimos a entero

  // Validador del rango del angulo
  if (anguloNuevo >= 0 && anguloNuevo <= 180){ // Eso es para asegurar que no nos vamos a pasar del rango del servomotor
    angulo = anguloNuevo; // Actualizamos el angulo 
    miServo.write(angulo); // Movemos el servo
    Serial.print("El Servomotor se movio al angulo: ");
    Serial.print(angulo);
  } else {
    Serial.println("Por favor, introduce un angulo válido");
  }
 } 
}