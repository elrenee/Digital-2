#include "BluetoothSerial.h"

// Variable para el Bluetooth
BluetoothSerial SerialBT;

// Buffer para comandos Bluetooth
String comandoBuffer = "";
unsigned long ultimaRecepcion = 0;
const unsigned long TIMEOUT_COMANDO = 100;


void setup() {
  // Inicializar comunicación serial para debugging
  Serial.begin(115200);
  
  // Inicializar Bluetooth
  SerialBT.begin("control1");
}

void loop() {
  // Leer datos Bluetooth carácter por carácter
  while (SerialBT.available()) {
    char c = SerialBT.read();
    comandoBuffer += c;
    ultimaRecepcion = millis();
    
    // Procesar inmediatamente si tenemos un comando completo
    procesarComando();
    
    // Limitar el tamaño del buffer para evitar desbordamiento
    if (comandoBuffer.length() > 10) {
      comandoBuffer = comandoBuffer.substring(comandoBuffer.length() - 10);
    }
  }
  
  // Limpiar buffer si ha pasado mucho tiempo sin datos
  if (millis() - ultimaRecepcion > TIMEOUT_COMANDO && comandoBuffer.length() > 0) {
    comandoBuffer = "";
  }
  
}
void procesarComando() {
  // El comando completo debería tener unos 6 caracteres (ej: F01R00)
  if (comandoBuffer.length() >= 6) {
    
    // 1. Extraer dirección adelante/atrás
    int adelanteatras = 0; // 0: stop, 1: adelante, 2: atrás
    char ejeY = ' ';
    
    if (comandoBuffer.indexOf("F01") >= 0) adelanteatras = 1;
    else if (comandoBuffer.indexOf("B01") >= 0) adelanteatras = 2;

    // 2. Extraer dirección giro
    int giro = 0; // 0: stop, 1: derecha, 2: izquierda
    if (comandoBuffer.indexOf("R01") >= 0) giro = 1;
    else if (comandoBuffer.indexOf("L01") >= 0) giro = 2;

  // 3. Lógica Combinada
   // if (adelanteatras == 1 && giro == 1) {
  // Serial.println("DIAGONAL: Adelante + Derecha");
   // } 
    //else if (adelanteatras == 1 && giro == 2) {
    //  Serial.println("DIAGONAL: Adelante + Izquierda");
   // }
    //else if (adelanteatras == 2 && giro == 1) {
   //   Serial.println("DIAGONAL: Atrás + Derecha");
    //}
    //else if (adelanteatras == 2 && giro == 2) {
      //Serial.println("DIAGONAL: Atrás + Izquierda");
   // }
    if (adelanteatras == 1) {
      Serial.println("u");
    }
    else if (adelanteatras == 2) {
      Serial.println("d");
    }
    else if (giro == 1) {
      Serial.println("r");
    }
    else if (giro == 2) {
      Serial.write("l");
    }
    else {
      Serial.println("s");
    }

    // Limpiamos el buffer tras procesar el comando completo
    comandoBuffer = ""; 
  }
}