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

    const byte adresses[][6] = {tunnel1, tunnel2, tunnel3, tunnel4, tunnel5, tunnel6};

    class Radio : My_library {
        public:
            Radio() { _communicate = RF24(pinCE, pinCSN, 4000000); };
            ~Radio() = default;

            void listener(void) {
                delay(5);
                _communicate.startListening();
                    if (_communicate.available()) {
                        while (_communicate.available())
                            _communicate.read(&_remoteData, sizeof(remoteData_t));
                        delay(20);
                    }
                delay(5);
            };
            bool send(char const *message) { _communicate.stopListening(); return _communicate.write(message, sizeof(char) * 32); };

            RF24 _communicate;
    };

    class My_library {
        public:
            My_library();
            ~My_library() = default;

            remoteData_t _remoteData;
            Radio _radio;
    };

#endif /* !MY_LIBRARY_HPP */