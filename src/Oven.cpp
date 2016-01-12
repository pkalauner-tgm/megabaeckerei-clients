//
// Created by Paul on 24.11.2015.
//

#include "Oven.h"
#include <iostream>

Oven::Oven() {
    this->lager_ventil = false;
    this->mischer_ventil = false;
    srand((unsigned int) time(NULL));
    setFuellstand(0);
}

void Oven::toggle_mischer_ventil() {
    mischer_ventil = !mischer_ventil;
    if (mischer_ventil) {
        std::thread t_mischer(&Oven::mischer_ventil_open_loop, this);
        t_mischer.detach();
    }
}

void Oven::toggle_lager_ventil() {
    lager_ventil = !lager_ventil;
    if (lager_ventil) {
        std::thread t_lager(&Oven::lager_ventil_open_loop, this);
        t_lager.detach();
    }
}

void Oven::mischer_ventil_open_loop() {
    while (mischer_ventil && (fuellstand > 0)) {
        int amount;
        if (fuellstand >= 10)
            amount = 10;
        else
            amount = fuellstand;

        setFuellstand(fuellstand - amount);
        socketHandler->sendMessage("mixtank_to_mixer " + std::to_string(amount));
        socketHandler->sendMessage("level_oven " + std::to_string(fuellstand));
        Sleep(100);
    }
}

void Oven::lager_ventil_open_loop() {
    while (lager_ventil && (fuellstand < MAX_FUELLSTAND)) {
        int amount;
        if (fuellstand <= MAX_FUELLSTAND - 10)
            amount = 10;
        else
            amount = MAX_FUELLSTAND - fuellstand;

        setFuellstand(fuellstand + amount);
        socketHandler->sendMessage("level_oven " + std::to_string(fuellstand));
        Sleep(100);
    }
}

void Oven::setSocketHandler(SocketHandler *sh) {
    this->socketHandler = sh;
}

int Oven::getFuellstand() const {
    return this->fuellstand;
}

void Oven::setFuellstand(int fuellstand) {
    this->fuellstand = fuellstand;
    std::cout << "Aktueller Fuellstand: " << std::to_string(this->fuellstand) << "/" << std::to_string(MAX_FUELLSTAND) << std::endl;
}