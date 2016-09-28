#ifndef PIRATE_H
#define PIRATE_H

#include "Sailor.h"
//#include "Model.h"

class Model;

class Pirate: public Sailor
{
public:
    Pirate(Model*);
    Pirate(int, Model*);
    double get_speed();
    void start_plunder(Sailor*);
    bool update();
    void show_status();

private:
    int attack_strength;
    double range;
    Sailor* target;
};

#endif