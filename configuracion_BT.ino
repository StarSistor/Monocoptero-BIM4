  #include <SoftwareSerial.h>   // libreria comunicación serie
  SoftwareSerial BT(10,11);   // pin 10 como RX, pin 11 cómo TX
  
  void setup(){
    Serial.begin(9600);        // comunicación de monitor serial a 9600 bps
    Serial.println("Listo");  // escribe Listo en el monitor
    BT.begin(38400);         // comunicación serie entre Arduino y el módulo a 38400 bps
  }
  
  void loop(){
  if (BT.available())                // si hay información disponible desde módulo
     Serial.write(BT.read());   // lee Bluetooth y envía a monitor serial de Arduino
  
  if (Serial.available())              // si hay información disponible desde el monitor serial
     BT.write(Serial.read());   // lee monitor serial y envía a Bluetooth
  }
