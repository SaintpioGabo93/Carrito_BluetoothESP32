// ----- Motor Derecho ----//

const int in1 = 26;
const int in2 = 25;

// ---- Definimos los canales ----//

int canal1MotorD = 0;
int canal2MotorD = 1;

// ---- ciclo de trabajo o velocidad en bits ----//

int velocidad = 200; // Esta en bits, va de 0 a 255


// --- Parametros para los motores ---- //

int frecuencia = 10000; // Esta frecuencia funciona para que no suene el encoder en caso de que tengamos encoder
int resolucion = 8; // Se refiere a 8 bits

void setup() {
  // Para realacionar los pines de entrada con los canales
  // Configuracion motor 1
  ledcSetup(canal1MotorD, frecuencia, resolucion); // Esta es una funcion propia del ESP32
  ledAttachPin(in1, cana1MotorD); // Unimos el motor con el canal

  // Configuracion motor 2
  ledcSetup(canal2MotorD, frecuencia, resolucion);
  ledAttachPin(in2, canal2MotorD); // 
}

void loop() {
  giroDerecha(canal1MotorD, canal2MotorD, velocidad);
  delay(1000);
  giroIzquierda(canal1MotorD, canal2MotorD, velocidad);
  delay(1000);
  pararMotor(canal1MotorD, canal2MotorD, velocidad);
  delay(1000);

}

// ---- Creamos las funciones ---- //

void giroDerecha(int canal1, int canal2, int cv){
  ledcWrite(canal1, cv); // Deberia activar el motor derecho
  ledcWrite(canal2, 0); // Deberia apagar el motor izquierdo
}

void giroIzquierda(int canal1, int canal2, int cv){
  ledcWrite(canal1, 0); // Deberia activar el motor derecho
  ledcWrite(canal2, cv); // Deberia apagar el motor izquierdo  
}

void pararMotor(int canal1, int canal2, int cv){
  ledcWrite(canal1, 0); // Deberia activar el motor derecho
  ledcWrite(canal2, 0); // Deberia apagar el motor izquierdo  
}




