#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX
 char c;
 
 
void setup()
{ Serial.begin(9600);
  delay(1000);
  BT1.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  BT1.println("AT+RST\r\n"); //Envia comando AT para reiniciar el modulo 
  delay(2000); // Tiempo de espera para realizar el reset del modulo 
  BT1.println("AT+CIFSR\r\n"); //Envia comando AT para consultar la dirección ip estatica asignada
  delay(1000);// Tiempo de espera para la consulta de la ip estatica del modulo 
  BT1.println("AT+CIPMUX=1\r\n");//Envia comando AT para configurar el modulo con multiples peticiones 
  delay(1000);// Tiempo de espera para la configuración 
  BT1.println("AT+CIPSERVER=1,80\r\n");//Envia comando AT para configurar el modulo como servidor y su puerto de conexión para este caso es el 1234
  delay(1000);
  BT1.println("AT+CIFSR\r\n");
  
}
 
void loop()
{ 
   String cc="";
   cc= readBT1();
   int var = 0;
   var= decideTurnLed(cc);
   switch (var) {
    case 1:
    turnOn();
    break;

    case 2:
    turnOff();
    break;

    default:
    turnOffOn();
    //Serial.println("a request does not exist");
    break;
   }

}

String readBT1(){
   char cal;
   String cadena = "";
  while (BT1.available() == 0) {
    //nada
  }
  do {
    if (BT1.available() > 0) {
      cadena = "";
      cal = BT1.read(); ;
      while (cal != '\n'){
      cadena += cal ;
      delay(25) ;
      cal = BT1.read();
    }
      Serial.println("---> " + cadena);
      return cadena; 
      
    }
  }  while ((BT1.available() == 0));  
  
 }

  int decideTurnLed(String state){
    if(state.length() > 0){
      if (state.startsWith("/on",15)){
        //turnOn();
        return 1;
        }
      if (state.startsWith("/off",15)){
        //turnOff();
        return 2;
        }
       return -1;
      }
    }
  
  void turnOn(){
     digitalWrite(LED_BUILTIN, HIGH);
     Serial.println("led on -> ok");
  }
  
  void turnOff(){
    digitalWrite(LED_BUILTIN, LOW); 
    Serial.println("led off -> ok");
  }

  void turnOffOn(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300); 
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300); 
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300); 
    digitalWrite(LED_BUILTIN, LOW); 
    Serial.println("a request does not exist");
  }



  
