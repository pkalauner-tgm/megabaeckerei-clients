//
// Created by Paul on 24.11.2015.
//

#ifndef SIMULATION_WATERTANK_H
#define SIMULATION_WATERTANK_H


#include <atomic>
#include "SocketHandler.h"

class SocketHandler;
class MixTank {
private:
    const int MAX_FUELLSTAND = 2000;
    SocketHandler * socketHandler;
    int fuellstand;
    volatile bool mischer_ventil;
    volatile bool lager_ventil;
    void mischer_ventil_open_loop();
    void lager_ventil_open_loop();
public:
    MixTank();
    void toggle_mischer_ventil();
    void toggle_lager_ventil();
    void setSocketHandler(SocketHandler* sh);
    int getFuellstand() const;
    void setFuellstand(int fuellstand);
};


#endif //SIMULATION_WATERTANK_H
