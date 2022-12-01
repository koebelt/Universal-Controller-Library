/*
** EPITECH PROJECT, 2022
** Receiver
** File description:
** My_library
*/

#ifndef MY_LIBRARY_HPP
    #define MY_LIBRARY_HPP_

    #include <Arduino.h>
    #include <SPI.h>
    #include <RF24.h>

    #define pinCE 7
    #define pinCSN 8
    #define tunnel1 "PIPE2"
    #define tunnel2 "PIPE1"
    #define tunnel3 "PIPE3"
    #define tunnel4 "PIPE4"
    #define tunnel5 "PIPE5"
    #define tunnel6 "PIPE6"

    // void listener(void) {
    //     radio.startListening();
    //     if (radio.available()) {
    //         while (radio.available()) {
    //         radio.read(&remoteData, sizeof(remoteData_t));
    //         // Serial.println(" Received data");
    //         }
    //         // remoteData = (remoteData_t)malloc(sizeof(remoteData_t));
    //         delay(20);
    //     }
    // }

    // bool send(char const *message) {
    //     return radio.write(message, sizeof(char) * 32);
    // }


    class My_library {
        public:
            class Radio {
                public:
                    Radio() { _communicate = RF24(pinCE, pinCSN, 4000000); };
                    ~Radio();
                    void listener(void) {
                        _communicate.startListening();
                            if (_communicate.available()) {
                                while (_communicate.available()) {
                                    _communicate.read(&remoteData, sizeof(remoteData_t));
                                    // Serial.println(" Received data");
                                }
                                // remoteData = (remoteData_t)malloc(sizeof(remoteData_t));
                                delay(20);
                            }
                    };
                    bool send(char const *message);

                    RF24 _communicate;
            };

            My_library() { _remoteData = {{0, 0}, {0, 0}, 0, 0, 0, 0}; };
            ~My_library();

            typedef struct joystick {
                int x;
                int y;
            } joystick_t;

            typedef struct remoteData {
                joystick_t ljoystick;
                joystick_t rjoystick;
                byte button1;
                byte button2;
                byte button3;
                byte button4;
            } remoteData_t;

            remoteData_t _remoteData;
            Radio _radio;
    };

#endif /* !MY_LIBRARY_HPP */