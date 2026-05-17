#include <Wire.h>

#define NucleoSegmentos 0x35
#define NucleoLCD 0x20

#define I2C_SDA 21
#define I2C_SCL 22
uint8_t error=0;
uint8_t comando=1;

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  i2cScanner();
}

void loop() {
  delay(1000);
  //Escribir a las nucleos...
  
  Wire.beginTransmission(NucleoSegmentos);
  Wire.write(comando);
  Serial.println("se envio: "+String(comando));
  error= Wire.endTransmission(true);
  Serial.println(error);

  //Leerlas...
  uint8_t sensoresDisplay= 0;
  if(Wire.requestFrom(NucleoSegmentos, 1)){
    sensoresDisplay = Wire.read();
    Serial.print("Respuesta segmentos: ");
    Serial.println(sensoresDisplay);
  }else{
    Serial.println("No se recibio nada.");
  }


  //Escribir a Jorchhh el estado de cada sensor...
  Wire.beginTransmission(NucleoLCD);
  Wire.write(sensoresDisplay);
  error = Wire.endTransmission(true);
  Serial.print("Estado reenviado a LCD: 0b");
  Serial.println(sensoresDisplay, BIN);
  
  //leer la de Jorge.
  uint8_t sensoresjorge=0;
  if(Wire.requestFrom(NucleoLCD, 1)){
    sensoresjorge= Wire.read();
    Serial.print("Sensores: ");
    Serial.println(sensoresjorge, BIN);
  }else {
    Serial.println("No se recibio nada de jorch");
  }
  // CONTAR OCUPADOS
  comando = 0;
  for(int i = 0; i < 4; i++){
    if(sensoresjorge & (1 << i)){
      comando++;
    }
  }
  Serial.print("Ocupados: ");
  Serial.println(comando);

//************************************
  //Variable para el servidor o la RED
  //**********************************
  uint8_t sensoresTotales = 0;

  sensoresTotales = ((sensoresjorge & 0x0F) << 4) | (sensoresDisplay & 0x0F);

  Serial.print("Sensores Totales: 0b");
  Serial.println(sensoresTotales, BIN);
}


void i2cScanner()
{
  byte error, address;
  int nDevices;
  Serial.println("Scaneando...");
  nDevices =0;
  for (address=1; address<127; address++)
  {
    Wire.beginTransmission(address);
    error= Wire.endTransmission();
    if (error ==0 ){
      Serial.print("Dispositivo I2C encontrado en la direccion 0x");
      if(address<16){
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }else if(error==4){
      Serial.print("Error desconocido en la direccion 0x");
      if(address<16)
      { 
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }
  }
  if(nDevices == 0)
  {
    Serial.println("No se encontro el dispositivo I2C\n");
  }else{} 
  
}

