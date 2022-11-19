/* Control de encendido y apagado de lampara vía Bluetooth
 Se envía vía bluetooth a la tarjeta Arduino la letra a para activar el led del pin13 y la letra b para apaga
 */
#include <SoftwareSerial.h>
int dato;                   //Se crea la variable dato tipo entero
 
void setup() {                
  pinMode(13, OUTPUT);     //Definimos el pin 13 como salida
  Serial.begin(9600);      //Inicializamos el puerto serial
}
void loop() {
 if (Serial.available()>0) {       //Confirmamos si existe un valor en el puerto serie
    dato = Serial.read();          //leemos el valor y lo asignamos a la variable dato
     switch(dato)                    //comparamos el valor guardado en la variable dato
     {
       case 'a':                        //si el dato leido es a
              digitalWrite(13,1);               //Setiamos a 5V el pin 13
              break;
      case 'b':                        //si el dato leido es b
             digitalWrite(13,0);              //setiamos a 0V el pin 13
             break;
     }
  }
}
