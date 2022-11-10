#include <Servo.h>
Servo ESC;     // create servo object to control the ESC


String inString = "";
void setup() {

  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC.write(0);    // Send the signal to the ESC

  delay(3000);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps 
     
}

void loop() {
  if(Serial.available() > 0){

    int inChar = Serial.read();

    if(inChar != '\n'){

      inString += (char)inChar; 

    }else{

      float data =inString.toFloat();
ESC.write(data);    // Send the signal to the ESC
Serial.println(data);
      
      inString = "";

    }

  }


}
