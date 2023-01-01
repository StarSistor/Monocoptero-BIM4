/////////////////////////////magnetometro//////////////////////////
#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"


// display pov https://www.instructables.com/Persistence-of-Vision-PoV-Display-Using-Arduino/
#include <SoftwareSerial.h>
#include <Servo.h>

// Declaramos la variable para controlar el servo
Servo ESC;
Servo servoMotor;


SoftwareSerial BT1(2, 4); // RX | TX de arduino
HMC5883L compass;

int16_t mx, my, mz;

//declinacion en grados en tu posición
const float declinacion = 0.12; 

////////////////////////design a pattern of display the number and alphabates//////////////////////////////// 

int NUMBER9[]={1,1,1,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,1,1,1,1,1,1,1};
 int NUMBER8[]={0,1,1,0,1,1,1,0, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 0,1,1,0,1,1,1,0};
 int NUMBER7[]={1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0, 1,0,0,1,1,1,1,1, 1,1,1,0,1,0,0,0};
 int NUMBER6[]={1,1,1,1,1,1,1,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,1,1,1};
 int NUMBER5[]={1,1,1,1,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,1,1,1};
 int NUMBER2[]= {1,0,0,0,0,0,1,1, 1,0,0,0,0,1,0,1, 1,0,0,0,1,0,0,1, 1,0,0,1,0,0,0,1, 0,1,1,0,0,0,0,1};
 int NUMBER1[]= {0,0,1,0,0,0,0,0, 0,1,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
 int NUMBER0[]= {1,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,1,1,1,1,1,1,1};

 int _[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
 int A[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,1,1,1,1,1,1,1};
 int B[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 0,1,1,0,1,1,1,0};
 int C[] = {0,0,1,1,1,1,0,0, 0,1,0,0,0,0,1,0, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1};
 int D[] = {1,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 0,1,0,0,0,0,1,0, 0,0,1,1,1,1,0,0};
 int E[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1};
 int F[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0};
 int G[] = {0,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,1,1,0};
 int H[] = {1,1,1,1,1,1,1,1, 0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0, 1,1,1,1,1,1,1,1};
 int I[] = {1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1};
 int J[] = {0,0,0,0,0,1,1,0, 0,0,0,0,1,0,0,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 1,1,1,1,1,1,1,0};
 int K[] = {1,1,1,1,1,1,1,1, 0,0,0,1,1,0,0,0, 0,0,1,0,0,1,0,0, 0,1,0,0,0,0,1,0, 1,0,0,0,0,0,0,1};
 int L[] = {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1};
 int M[] = {1,1,1,1,1,1,1,1, 0,1,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,1,0,0,0,0,0,0, 1,1,1,1,1,1,1,1};
 int N[] = {1,1,1,1,1,1,1,1, 0,0,1,0,0,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,0,0,1,0,0, 1,1,1,1,1,1,1,1};
 int O[] = {0,1,1,1,1,1,1,0, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 0,1,1,1,1,1,1,0};
 int P[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 0,1,1,0,0,0,0,0};
 int Q[] = {0,1,1,1,1,1,1,0, 1,0,0,0,0,0,0,1, 1,0,0,0,0,1,0,1, 0,1,1,1,1,1,1,0, 0,0,0,0,0,0,0,1};
 int R[] = {1,1,1,1,1,1,1,1, 1,0,0,1,1,0,0,0, 1,0,0,1,0,1,0,0, 1,0,0,1,0,0,1,0, 0,1,1,0,0,0,0,1};
 int S[] = {0,1,1,1,0,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,1,1,0};
 int T[] = {1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0};
 int U[] = {1,1,1,1,1,1,1,0, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 1,1,1,1,1,1,1,0};
 int V[] = {1,1,1,1,1,1,0,0, 0,0,0,0,0,0,1,0, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,1,0, 1,1,1,1,1,1,0,0};
 int W[] = {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,1,0, 0,0,0,0,0,1,0,0, 0,0,0,0,0,0,1,0, 1,1,1,1,1,1,1,1};
 int X[] = {1,1,0,0,0,0,1,1, 0,0,1,0,0,1,0,0, 0,0,0,1,1,0,0,0, 0,0,1,0,0,1,0,0, 1,1,0,0,0,0,1,1};
 int Y[] = {1,1,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,1,1,1,1,1, 0,0,1,0,0,0,0,0, 1,1,0,0,0,0,0,0};
 int Z[] = {1,0,0,0,0,1,1,1, 1,0,0,0,1,0,0,1, 1,0,0,1,0,0,0,1, 1,0,1,0,0,0,0,1, 1,1,0,0,0,0,0,1};
 
 int* alpha[]= {A,B,C,D,E,F,G,H,I,J,K,L,M,N};//,T,U,V,W,X,Y,Z};
 int letterSpace;
 int delayTime;

 #define IR_pin 10
 ////////////////////////////////////////////////////////////
   boolean flag = true; //when true allow for checking 
 ////////////////////////////////////////////////////////// 
 void setup()
 { 

  Serial.begin(9600);
  BT1.begin(9600);

  servoMotor.attach(5);
  servoMotor.write(0); // velociddad minima
  ESC.attach(3, 1000 , 2000);
  ESC.write(0); // velociddad minima
  delay(3000);
    /////////////////////////magnetometro//////////////////
    Wire.begin();
    compass .initialize();
  
    /////////////////////////////////////////////////  
      
         Serial.begin(9600);   

         for( int i = 6; i<13 ;i++ ) // setting the ports of the leds to OUTPUT
           {
            pinMode(i, OUTPUT);
           }
                
         letterSpace =4;// defining the space between the letters (ms)         
         delayTime =1;// defining the time dots appear (ms)
}


 void printLetter(int letter[])
 {
           int y;
          // printing the first y row of the letter
           for (y=0; y<8; y++)
           {
           digitalWrite(y+6, letter[y]); // EL PIN DE INCIO LO COLOCAS EN Y +6, Para el proyecto empieza en 6
           }
           delay(delayTime);
          // printing the second y row of the letter
           for (y=0; y<8; y++)
           {
           digitalWrite(y+6, letter[y+8]);
           }
           delay(delayTime);
          // printing the third y row of the letter
           for (y=0; y<8; y++)
           {
           digitalWrite(y+6, letter[y+16]);
           }
           delay(delayTime);
           for(y = 0; y<8; y++) {
           digitalWrite(y+6, letter[y+24]);
           }
           delay(delayTime);
          for(y = 0; y<8; y++) {
           digitalWrite(y+6, letter[y+32]);
           }
           delay(delayTime);
           // printing the space between the letters
           for (y=0; y<8; y++)
           {
           digitalWrite(y+6, 0);
           }
           delay(letterSpace);
 }

 
 void loop()
 {
    if (BT1.available() >= 2) {

    unsigned int ESCvelocidad = BT1.read();
    unsigned int Servoposicion = BT1.read();
    unsigned int recibido = (Servoposicion * 256) + ESCvelocidad;
      Serial.println(BT1.read());

    if (recibido >= 1000 && recibido < 1180) {
      int servo1 = recibido;
      servo1 = map(servo1, 1000, 1180, 0, 180);
      ESC.write (servo1);
      Serial.print(servo1);
      delay (10);
    }
    if (recibido >= 2000 && recibido < 2180) {
      int servo2 = recibido ;
      servo2 = map(servo2, 2000, 2180, 45, 90);
      servoMotor.write (servo2);
      Serial.println(servo2);
      delay (10);

    }
  }
      //Obtener componentes del campo magnético
    compass .getHeading(&mx, &my, &mz);

    //Calcular ángulo el ángulo del eje X respecto al norte
    float angulo = atan2(my, mx);
    angulo = angulo * RAD_TO_DEG;
    angulo = angulo - declinacion;
    
    if(angulo < 0) angulo = angulo + 360;
    {
    //Serial.print("N:");
    //Serial.println(angulo,0);  

///////////////////////////////////////////////////////////////

 if (flag == true && angulo > 359)
  {
    Serial.println(angulo,0);
     printLetter (P);
     printLetter (O);
     printLetter (V);
     printLetter (_);
     printLetter (_);
     printLetter (D);
     printLetter (I);
     printLetter (S);
     printLetter (P);
     printLetter (L);
     printLetter (A);
     printLetter (Y);
     printLetter (_);
    flag = false;
  }

  if(angulo <= 359)
  {
    
    flag = true; 
  }

  }
  }
