#include <SoftwareSerial.h>
SoftwareSerial myGsm(7, 8);
#include<Servo.h>
Servo myservo; 
void setup()
{
   myservo.attach(9);
  myGsm.begin(9600);
  Serial.begin(9600);
  delay(500);
myservo.write(0);
  Serial.println("here");
  myGsm.println("AT+CGATT=1");
  delay(200);
  printSerialData();

  myGsm.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""); // setting the SAPBR,connection type is GPRS
  delay(1000);
  printSerialData();

  myGsm.println("AT+SAPBR=3,1,\"APN\",\"internet\""); // setting the APN,2nd parameter empty works for all networks
  delay(5000);
  printSerialData();

  myGsm.println();
  myGsm.println("AT+SAPBR=1,1");
  delay(10000);
  printSerialData();

  myGsm.println("AT+HTTPINIT"); // init the HTTP request
  delay(2000);
  printSerialData();

  myGsm.println("AT+HTTPPARA=\"URL\",\"tollcollection.herokuapp.com/checkPayment/16095/6565\""); // setting the httppara,
  // the second parameter is the website from where you want to access data
  delay(1000);
  printSerialData();

  myGsm.println();
  myGsm.println("AT+HTTPACTION=0"); // submit the GET request
  delay(8000);                      // the delay is important if the return datas are very large, the time required longer.
  printSerialData();
  myGsm.println("AT+HTTPREAD=0,20"); // read the data from the website you access
  delay(3000);
  printResult();

  myGsm.println("");
  delay(1000);
  myGsm.println("AT+HTTPTERM"); // terminate HTTP service
  printSerialData();
}

void loop()
{
}
void printResult()
{
  int chars = 0;
  int ones = 0;
  int zeroes = 0;
  char prevchar = "";
  while (myGsm.available() != 0)
  {
    char data = char(myGsm.read());
    if (data == '1')
      ones++;
    else if (data == '0')
      zeroes++;
    Serial.write(data);
    // if(found<2)
    chars++;
    prevchar = data;
  }
  Serial.println(zeroes);
  Serial.println(ones);
  if(ones==2){
    int pos=0;
    Serial.println("good to go");
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
   
  delay(3000); 
   }
}
void printSerialData()
{
  int chars = 0;
  while (myGsm.available() != 0)
  {
    Serial.write(myGsm.read());
    chars++;
  }
  // Serial.println(chars);
}
