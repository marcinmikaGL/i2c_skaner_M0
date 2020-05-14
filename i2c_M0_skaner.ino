#include <Wire.h>
#include "wiring_private.h"

TwoWire myWire(&sercom2, 2, 3);  
//x= 0;
String i2c_adress = "";
String i2c_body = "";
bool is_body = false;
String inputString = "";
String i2c_body_buffor = "";
boolean stringComplete = false;
int i2c_loop = 0;
int led1 = 12;
int led2 = 13;
int input = 4;
int turbo = 0;
int demo_loop = 0;
int adress,i,i2c_adress_buffor,z,adr;

byte crcCalc(byte arr[8]) {
  byte crc = 0xFF;
  int i = 0;
  for(i=0; i<sizeof(arr); i++) crc = crc ^ arr[i];
  return crc;
}

void setup() {
  Wire.begin();
 SerialUSB.begin(115200);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(input, INPUT);
  myWire.begin(8);                    // join i2c bus with address #8

  pinPeripheral(2, PIO_SERCOM_ALT);   // assign SDA function to pin 2
  pinPeripheral(3, PIO_SERCOM_ALT);   // assign SCL function to pin 3
 SerialUSB.println("[SATERUNS I2C]"); 
 SerialUSB.println("[VER 0,02B]"); 
 SerialUSB.println("[Autor: Marcin Mika]"); 

 myWire.onRequest(requestEvent);     // register event
}

void loop() {
  SerialUSB.println("[SATERUNS I2C]"); 
//i2c_scaner();
delay(1000);
  Wire.requestFrom(6, 5);     // request 1 bytes from slave device #5

  while (Wire.available()) {  // slave may send less than requested
   char c = Wire.read();     // receive a byte as character
    SerialUSB.print(c);       // print the character
  }

  delay(500);
}

    void i2c_read(int i2c_adress){
 
   
  }


  void i2c_send(int adress,int data) {
    Wire.beginTransmission(adress);
    Wire.write(data);              
    Wire.endTransmission();
    }


void i2c_scaner() {
byte error, address;
int nDevices;

nDevices = 0;
for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      SerialUSB.print(i++);
      SerialUSB.print(";");
      SerialUSB.print("0x");
      if (address<16)
      SerialUSB.print("0");
      SerialUSB.print(address);
      SerialUSB.print(";");
      adr = (int)address;
      i2c_read(adr);
      SerialUSB.println(";");
      nDevices++;
    } else if (error==4) {
      SerialUSB.print("Unknow error at address 0x");
      if (address<16)
      SerialUSB.print("0");
      SerialUSB.println(address);
    }
  }
    if (nDevices == 0) {
      digitalWrite(led1, HIGH);
      SerialUSB.print("[");
      SerialUSB.print(i++);
      SerialUSB.print("]");
      SerialUSB.println("Brak urzadzeni na magistrali I2C \n");  
}

}

void i2c_scaner_byte() {
byte error, address;
int nDevices;

nDevices = 0;
for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      SerialUSB.print(i++);
      SerialUSB.print(";");
      SerialUSB.print("0x");
      if (address<16)
      SerialUSB.print("0");
      SerialUSB.print(address);
      SerialUSB.print(";");
      adr = (int)address;
      i2c_read(adr);
      SerialUSB.println(";");
      nDevices++;
    } else if (error==4) {
      SerialUSB.print("Unknow error at address 0x");
      if (address<16)
      SerialUSB.print("0");
      SerialUSB.println(address);
    }
  }
    if (nDevices == 0) {
      digitalWrite(led1, HIGH);
      SerialUSB.print("[");
      SerialUSB.print(i++);
      SerialUSB.print("]");
      SerialUSB.println("Brak urzadzeni na magistrali I2C \n");
}
}


extern "C" {
  void SERCOM2_Handler(void);

  void SERCOM2_Handler(void) {
    myWire.onService();
  }
}

 void requestEvent() {
  myWire.write("hello "); // respond with message of 6 bytes as expected by master
}

// void software_Reset() { asm volatile ("  jmp 0");  } 
