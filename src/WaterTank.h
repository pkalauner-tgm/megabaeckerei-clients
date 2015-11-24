//
// Created by Paul on 24.11.2015.
//

#ifndef SIMULATION_WATERTANK_H
#define SIMULATION_WATERTANK_H


class WaterTank {
private:
    int fuellstand;
public:
    WaterTank();
    void addWater(int amount);

    int getFuellstand() const {
        return fuellstand;
    }

    void setFuellstand(int fuellstand) {
        WaterTank::fuellstand = fuellstand;
    }
};


#endif //SIMULATION_WATERTANK_H
