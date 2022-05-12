#include <SoftwareSerial.h>
SoftwareSerial myGsm(7, 8);

void setup()
{
  myGsm.begin(9600);
  Serial.begin(9600);
  delay(500);

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

  myGsm.println("AT+HTTPPARA=\"URL\",\"tollcollection.herokuapp.com/checkPayment/1095/6565\""); // setting the httppara,
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
