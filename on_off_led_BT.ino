#include <SoftwareSerial.h> // libreria que permite establecer pines digitales

SoftwareSerial BT(10, 11);  // pin 10 como RX, pin 11 como TX

char valor = 0;      // variable para almacenar caracter recibido

void setup(){
  BT.begin(9600);    // comunicacion serie entre Arduino y el modulo
  Serial.begin(115200);
pinMode(13, OUTPUT);

}

void loop(){
if (BT.available()){     // si hay informacion disponible desde modulo
  valor = BT.read();   // almacena en valor el caracter recibido desde modulo

  if( valor == 'a' )   
  {
      digitalWrite(13,HIGH); 

      Serial.println("encendido");
  }
      
  if( valor == 'b' )   
   {
      digitalWrite(13,LOW); 

      Serial.println("apagado");
   }
      
}
}
