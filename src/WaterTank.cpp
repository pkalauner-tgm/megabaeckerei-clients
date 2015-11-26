//
// Created by Paul on 24.11.2015.
//

#include "WaterTank.h"
#include <iostream>

WaterTank::WaterTank() {
    this->lager_ventil = false;
    this->mischer_ventil = false;
    this->fuellstand = (rand() % (MAX_FUELLSTAND + 1));
}

void WaterTank::toggle_mischer_ventil() {
    mischer_ventil = !mischer_ventil;
    if (mischer_ventil) {
        std::thread t_mischer(&WaterTank::mischer_ventil_open_loop, this);
        t_mischer.detach();
    }
}

void WaterTank::toggle_lager_ventil() {
    lager_ventil = !lager_ventil;
    if (lager_ventil) {
        std::thread t_lager(&WaterTank::lager_ventil_open_loop, this);
        t_lager.detach();
    }
}

void WaterTank::mischer_ventil_open_loop() {
    while (mischer_ventil) {
        if (fuellstand >= 10) {
            setFuellstand(fuellstand - 10);
            std::string msg = "water_to_mischer 10";
            socketHandler->sendMessage(msg);
            Sleep(100);
        }
    }
}

void WaterTank::lager_ventil_open_loop() {
    while (lager_ventil) {
        setFuellstand(fuellstand + 10);
        std::string msg = "water_to_tank 10";
        socketHandler->sendMessage(msg);
        Sleep(100);
    }
}

void WaterTank::setSocketHandler(SocketHandler *sh) {
    this->socketHandler = sh;
}

int WaterTank::getFuellstand() const {
    return this->fuellstand;
}

void WaterTank::setFuellstand(int fuellstand) {
    this->fuellstand = fuellstand;
    std::cout << "Aktueller Fuellstand: " << std::to_string(this->fuellstand) << "/" << std::to_string(MAX_FUELLSTAND) << std::endl;
}