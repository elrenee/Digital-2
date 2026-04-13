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
  // Buscar comandos en el buffer
  if (comandoBuffer.indexOf("F") >= 0) {
    comandoBuffer = "";
    Serial.println("ADELANTE - FS detectado");
  }
  else if (comandoBuffer.indexOf("BS") >= 0) {
    comandoBuffer = "";
    Serial.println("ATRAS - BS detectado");
  }
  else if (comandoBuffer.indexOf("RS") >= 0) {
    comandoBuffer = "";
    Serial.println("DERECHA - RS detectado");
  }
  else if (comandoBuffer.indexOf("LS") >= 0) {
    comandoBuffer = "";
    Serial.println("IZQUIERDA - LS detectado");
  }
  else if (comandoBuffer.indexOf("ST") >= 0) {
    comandoBuffer = "";
    Serial.println("PARAR - ST detectado");
  }
}