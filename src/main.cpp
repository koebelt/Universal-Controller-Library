// #include <Arduino.h>
// #include <SPI.h>
// #include <RF24.h>
#include "../lib/My_library.hpp"

// /************************** Radio Declarations ********************************/

// #define pinCE 7
// #define pinCSN 8
// #define tunnel1 "PIPE2"
// #define tunnel2 "PIPE1"
// #define tunnel3 "PIPE3"
// #define tunnel4 "PIPE4"
// #define tunnel5 "PIPE5"
// #define tunnel6 "PIPE6"
// RF24 radio(pinCE, pinCSN, 4000000);
// const byte adresses[][6] = {tunnel1, tunnel2, tunnel3, tunnel4, tunnel5, tunnel6};
// bool connected = false;
// int currentChannel = 0;

// typedef struct joystick {
//   int x;
//   int y;
// } joystick_t;

// typedef struct remoteData {
//   joystick_t ljoystick;
//   joystick_t rjoystick;
//   byte button1;
//   byte button2;
//   byte button3;
//   byte button4;
// } remoteData_t;

// remoteData_t remoteData = {{0, 0}, {0, 0}, 0, 0, 0, 0};

/********************* End of Radio Declarations ******************************/


// void listener(void) {
//   radio.startListening();
//   if (radio.available()) {
//     while (radio.available()) {
//       radio.read(&remoteData, sizeof(remoteData_t));
//       // Serial.println(" Received data");
//     }
//     // remoteData = (remoteData_t)malloc(sizeof(remoteData_t));
//     delay(20);
//   }
// }

// bool send(char const *message)
// {
//   return radio.write(message, sizeof(char) * 32);
// }
My_library receiver;

void setup() {
    Serial.begin(9600);
  /* Radio initialisation */
//   if (!radio.begin())
//     Serial.println("Radio initialisation failed");
//   else
//     Serial.println("Radio initialisation success");
//   // radio.setChannel(0);
//   radio.setPALevel(RF24_PA_MIN);
//   // radio.setDataRate(RF24_250KBPS);
//   radio.openWritingPipe(adresses[0]);
//   // radio.openReadingPipe(0, adresses[0]);
//   radio.openReadingPipe(1, adresses[1]);
//   radio.openReadingPipe(2, adresses[2]);
//   radio.openReadingPipe(3, adresses[3]);
//   radio.openReadingPipe(4, adresses[4]);
//   radio.openReadingPipe(5, adresses[5]);
//   radio.startListening();
//   /* End of Radio Initialisation */
  // put your setup code here, to run once:
}

char message[32] = "Hello World";

void loop() {
  // uint8_t pipe;
  // if (radio.available(&pipe))
  // {
  //   // remoteData = (remoteData_t)malloc(sizeof(remoteData_t));
  //   uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
  //   radio.read(&message, sizeof(message));
  //   Serial.print(F("Received "));
  //   Serial.print(bytes);
  //   Serial.print(F(" bytes on pipe ")); //   Serial.print(pipe);
  //   Serial.print("Received data: ");
  //   Serial.println(message);  
  // }
  receiver._radio.listener();
  Serial.print("lX: ");
  Serial.print(receiver._remoteData.ljoystick.x);
  Serial.print(" lY: ");
  Serial.print(receiver._remoteData.ljoystick.y);
  Serial.print(" rX: ");
  Serial.print(receiver._remoteData.rjoystick.x);
  Serial.print(" rY: ");
  Serial.print(receiver._remoteData.rjoystick.y);
  Serial.print(" b1: ");
  Serial.print(receiver._remoteData.button1);
  Serial.print(" b2: ");
  Serial.print(receiver._remoteData.button2);
  Serial.print(" b3: ");
  Serial.print(receiver._remoteData.button3);
  Serial.print(" b4: ");
  Serial.println(receiver._remoteData.button4);
  receiver._radio.send("message");
  // Serial.write(12);
  // put your main code here, to run repeatedly:
}

// /**
//  * See documentation at https://nRF24.github.io/RF24
//  * See License information at root directory of this library
//  * Author: Brendan Doherty (2bndy5)
//  */

// /**
//  * A simple example of sending data from 1 nRF24L01 transceiver to another.
//  *
//  * This example was written to be used on 2 devices acting as "nodes".
//  * Use the Serial Monitor to change each node's behavior.
//  */
// #include <SPI.h>
// #include "printf.h"
// #include "RF24.h"

// // instantiate an object for the nRF24L01 transceiver
// RF24 radio(7, 8, 4000000); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// // Let these addresses be used for the pair
// uint8_t address[][6] = {"1Node", "2Node"};
// // It is very helpful to think of an address as a path instead of as
// // an identifying device destination

// // to use different addresses on a pair of radios, we need a variable to
// // uniquely identify which address this radio will use to transmit
// bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// // Used to control whether this node is sending or receiving
// bool role = false; // true = TX role, false = RX role

// // For this example, we'll be using a payload containing
// // a single float number that will be incremented
// // on every successful transmission
// float payload = 0;

// void setup()
// {

//   Serial.begin(9600);
//   while (!Serial)
//   {
//     // some boards need to wait to ensure access to serial over USB
//   }
//   delay(10);
//   // initialize the transceiver on the SPI bus
//   if (!radio.begin())
//   {
//     Serial.println(F("radio hardware is not responding!!"));
//     while (1)
//     {
//     } // hold in infinite loop
//   }

//   // print example's introductory prompt
//   Serial.println(F("RF24/examples/GettingStarted"));

//   radioNumber = 1;
//   Serial.print(F("radioNumber = "));
//   Serial.println((int)radioNumber);

//   // Set the PA Level low to try preventing power supply related problems
//   // because these examples are likely run with nodes in close proximity to
//   // each other.
//   radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.

//   // save on transmission time by setting the radio to only transmit the
//   // number of bytes we need to transmit a float
//   radio.setPayloadSize(sizeof(float)); // float datatype occupies 4 bytes

//   // set the TX address of the RX node into the TX pipe
//   radio.openWritingPipe(address[radioNumber]); // always uses pipe 0

//   // set the RX address of the TX node into a RX pipe
//   radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

//   // additional setup specific to the node's role
//   if (role)
//   {
//     radio.stopListening(); // put radio in TX mode
//   }
//   else
//   {
//     radio.startListening(); // put radio in RX mode
//   }

//   // For debugging info
//   // printf_begin();             // needed only once for printing details
//   // radio.printDetails();       // (smaller) function that prints raw register values
//   radio.printPrettyDetails(); // (larger) function that prints human readable data

// } // setup

// void loop()
// {

//   // This device is a RX node

//   uint8_t pipe;
//   if (radio.available(&pipe))
//   {                                         // is there a payload? get the pipe number that recieved it
//     uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
//     radio.read(&payload, bytes);            // fetch payload from FIFO
//     Serial.print(F("Received "));
//     Serial.print(bytes); // print the size of the payload
//     Serial.print(F(" bytes on pipe "));
//     Serial.print(pipe); // print the pipe number
//     Serial.print(F(": "));
//     Serial.println(payload); // print the payload's value
//   }

// } // loop