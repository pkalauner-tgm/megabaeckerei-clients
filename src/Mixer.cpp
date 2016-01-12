//
// Created by Paul on 24.11.2015.
//

#include "Mixer.h"
#include <iostream>

MixTank::MixTank() {
    this->lager_ventil = false;
    this->mischer_ventil = false;
    srand((unsigned int) time(NULL));
    setFuellstand(0);
}

void MixTank::toggle_oven_ventil() {
    mischer_ventil = !mischer_ventil;
    if (mischer_ventil) {
        std::thread t_mischer(&MixTank::oven_ventil_open_loop, this);
        t_mischer.detach();
    }
}

void MixTank::oven_ventil_open_loop() {
    while (mischer_ventil && (fuellstand > 0)) {
        int amount;
        if (fuellstand >= 10)
            amount = 10;
        else
            amount = fuellstand;

        setFuellstand(fuellstand - amount);
        socketHandler->sendMessage("mixer_to_oven " + std::to_string(amount));
        socketHandler->sendMessage("level_mixer " + std::to_string(fuellstand));
        Sleep(100);
    }
}

void MixTank::setSocketHandler(SocketHandler *sh) {
    this->socketHandler = sh;
}

int MixTank::getFuellstand() const {
    return this->fuellstand;
}

void MixTank::setFuellstand(int fuellstand) {
    this->fuellstand = fuellstand;
    std::cout << "Aktueller Fuellstand: " << std::to_string(this->fuellstand) << "/" << std::to_string(MAX_FUELLSTAND) << std::endl;
}