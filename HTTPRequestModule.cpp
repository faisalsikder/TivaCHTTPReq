/*
 * TestModulePrintData.h
 *
 *  Created on: Feb 21, 2015
 *      Author: Faisal Sikder
 */

//#include "SPI.h"
#include <Ethernet.h>

#include "HTTPRequestModule.h"
//
#include "driverlib/sysctl.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

#include "inc/hw_flash.h"
#include "driverlib/flash.h"
//



// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = { 0x00, 0x1A, 0xB6, 0x03, 0x03, 0xEC};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(172, 19, 4, 240);

// fill in your Domain Name Server address here:
IPAddress myDns(192, 31, 89, 16);

// initialize the library instance:
EthernetClient client;

//char server[] = "ioe01";
IPAddress server(192, 31, 89, 21);
int dhcp_refresh = 600;
unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers

//get the mac accress from hearware
int32_t user0,user1;

char pram_buffer[100];

MAKE_MODULE(TestModulePrintData)
MAKE_MODULE(ISL29023Module)
MAKE_MODULE(BMP180Module)
MAKE_MODULE(SHT21Module)

void TestModulePrintData::execute()
{
  tivaWare.UART.printf("Humidity:");
  TestModulePrintData::print_value_in_fraction(theSHT21Representation->fHumidity);
  tivaWare.UART.printf("\tTemparature:");
  TestModulePrintData::print_value_in_fraction(theSHT21Representation->fTemperature);
  tivaWare.UART.printf("\tVisible Lux:");
  TestModulePrintData::print_value_in_fraction(theISL29023Representation->fAmbient);
  tivaWare.UART.printf("\tPressure:");
  TestModulePrintData::print_value_in_fraction(theBMP180Representation->fPressure);
  tivaWare.UART.printf("\tTemparature:");
  TestModulePrintData::print_value_in_fraction(theBMP180Representation->fTemperature);
  tivaWare.UART.printf("\tAltitude:");
  TestModulePrintData::print_value_in_fraction(theBMP180Representation->fAltitude);
  tivaWare.UART.printf("\tMAC:%02X%02X%02X%02X%02X%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
  tivaWare.UART.printf("\n");
  sprintf(pram_buffer,"%02X%02X%02X%02X%02X%02X;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5],
            theSHT21Representation->fHumidity, theSHT21Representation->fTemperature,theISL29023Representation->fAmbient,
            theBMP180Representation->fPressure,theBMP180Representation->fTemperature,theBMP180Representation->fAltitude);
  TestModulePrintData::localLoop();
}


void TestModulePrintData::readmac(byte mac[],int32_t user0,int32_t user1){
    mac[0] = user0 & 0xFF;
    mac[1] = (user0 >> 8) & 0xFF;
    mac[2] = (user0 >> 16) & 0xFF;
    mac[3] = user1 & 0xFF;
    mac[4] = (user1 >> 8) & 0xFF;
    mac[5] = (user1 >> 16) & 0xFF;
}

void TestModulePrintData::init(){
  user0 = HWREG(FLASH_USERREG0);
  user1 = HWREG(FLASH_USERREG1);
   //tivaWare.UART.printf("got it here...");
  // start the Ethernet connection using a fixed IP address and DNS server:
  TestModulePrintData::readmac(mac,user0,user1);
  tivaWare.UART.printf("\tMAC:%06X%06X %02X%02X%02X%02X%02X%02X\n",user0,user1,mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  //Ethernet.begin(mac);
  //dhcp internet address
  //Ethernet.maintain();
  //client.connect(server, 80);
  //tivaWare.UART.printf("ethernet passed it here...");
}


void TestModulePrintData::print_value_in_fraction(float data)
{
	int32_t i32IntegerPart = (int32_t) data;
	int32_t i32FractionPart = (int32_t) (data* 1000.0f);
	i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
	tivaWare.UART.printf("%d.%3d",i32IntegerPart, i32FractionPart);
}

void TestModulePrintData::localLoop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  //if (client.available()) {
    //char c = client.read();
    //Serial.write(c);
	//tivaWare.UART.printf(c);
  //}

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  //if (millis() - lastConnectionTime > postingInterval) {
    TestModulePrintData::httpRequest();
  //}

}

// this method makes a HTTP connection to the server:
void TestModulePrintData::httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  if(--dhcp_refresh <= 0){
    Ethernet.begin(mac);
    dhcp_refresh = 600;
  }
  delay(100);
  client.stop();
  delay(1000);
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    //Serial.println("connecting...");
	tivaWare.UART.printf("connecting....");
    // send the HTTP PUT request:
    client.print("GET /academic/sensordata/getdata.php?reading=");
	client.print(pram_buffer);
	client.println(" HTTP/1.1");
    client.println("Host: xxxxx.xx.xxxxx.xxx");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
	delay(1000);
    // note the time that the connection was made:
    //lastConnectionTime = millis();
	tivaWare.UART.printf("connection ended");
  } else {
	tivaWare.UART.printf("connection failed");
	HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;
 }
}
