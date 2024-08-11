/*
  Web client

  This sketch connects to a website (http://www.google.com)
  using an Arduino Wiznet Ethernet shield.

  Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13

  created 18 Dec 2009
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe, based on work by Adrian McEwen
*/

// w5100 eth module

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xA0 };


// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 180);
IPAddress myDns(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
//EthernetClient client;



void Eth_setup() {
  Serial.println("Setup Ethernet ...");
  Ethernet.begin(mac, ip, myDns);
  Serial.print("Fixed IP: ");
  Serial.println(Ethernet.localIP());
  //give the Ethernet shield a second to initialize:
  delay(1000);
}
