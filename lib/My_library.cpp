/*
** EPITECH PROJECT, 2022
** Universal-Controller-Library
** File description:
** My_library
*/

#include "My_library.hpp"

My_library::My_library()
{
    _remoteData = {{0, 0}, {0, 0}, 0, 0, 0, 0};
    !_radio._communicate.begin() ? Serial.println("Radio initialisation failed") : Serial.println("Radio initialisation success");
    // if (!_radio._communicate.begin())
    //     Serial.println("Radio initialisation failed");
    // else
    //     Serial.println("Radio initialisation success");
    _radio._communicate.setPALevel(RF24_PA_MIN);
    _radio._communicate.openWritingPipe(adresses[0]);
    _radio._communicate.openReadingPipe(1, adresses[1]);
    _radio._communicate.openReadingPipe(2, adresses[2]);
    _radio._communicate.openReadingPipe(3, adresses[3]);
    _radio._communicate.openReadingPipe(4, adresses[4]);
    _radio._communicate.openReadingPipe(5, adresses[5]);
    _radio._communicate.startListening();
}
