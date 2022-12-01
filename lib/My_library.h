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

    #define tunnel1 "PIPE2"
    #define tunnel2 "PIPE1"
    #define tunnel3 "PIPE3"
    #define tunnel4 "PIPE4"
    #define tunnel5 "PIPE5"
    #define tunnel6 "PIPE6"

    const byte adresses[][6] = {tunnel1, tunnel2, tunnel3, tunnel4, tunnel5, tunnel6};

    // class Radio : My_library {
    //     public:
    //         Radio() { _communicate = RF24(pinCE, pinCSN, 4000000); };
    //         ~Radio() = default;


    //         RF24 _communicate;
    // };

    class My_library {
        public:
            My_library() {};
            My_library(int pinCE, int pinCSN) {
                _radio = RF24(pinCE, pinCSN, 4000000);
                _remoteData = {{0, 0}, {0, 0}, 0, 0, 0, 0};
                !_radio.begin() ? Serial.println("Radio initialisation failed") : Serial.println("Radio initialisation success");
                // if (!_radio.begin())
                //     Serial.println("Radio initialisation failed");
                // else
                //     Serial.println("Radio initialisation success");
                _radio.setPALevel(RF24_PA_HIGH);
                _radio.setDataRate(RF24_250KBPS);
                _radio.openWritingPipe(adresses[0]);
                _radio.openReadingPipe(1, adresses[1]);
                _radio.openReadingPipe(2, adresses[2]);
                _radio.openReadingPipe(3, adresses[3]);
                _radio.openReadingPipe(4, adresses[4]);
                _radio.openReadingPipe(5, adresses[5]);
                _radio.startListening();
            };
            ~My_library() = default;

            struct joystick {
                int x;
                int y;
            };

            struct remoteData {
                struct joystick ljoystick;
                struct joystick rjoystick;
                byte button1;
                byte button2;
                byte button3;
                byte button4;
            };

            void listener(void) {
                unsigned long time = millis();
                if (time - _stopMillis >= 1) {
                    _radio.startListening();
                    _startMillis = millis();
                        if (_radio.available()) {
                            while (_radio.available())
                                _radio.read(&_remoteData, sizeof(struct remoteData));
                        }
                }
            };
            bool send(char const *message) {
                unsigned long time = millis();
                if (time - _startMillis >= 1) {
                    _radio.stopListening();
                    _stopMillis = millis();
                    return _radio.write(message, sizeof(char) * 32);
                }
                return false;
            };

            RF24 getLegacyRadio(void) { return _radio; };

            unsigned long _startMillis;
            unsigned long _stopMillis;
            struct remoteData _remoteData;
            RF24 _radio;
    };

#endif /* !MY_LIBRARY_HPP */