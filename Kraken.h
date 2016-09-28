#ifndef KRAKEN_H
#define KRAKEN_H
#include <iostream>
using namespace std;

#include "Model.h"
#include "Sailor.h"

class Kraken
{
public:
    Kraken(Model* model);
    Model* world;
    bool start_krakening();
    list<Sailor*>* sailor_killed;
    void printsailors();
    Kraken* getKraken(Model*);
};

#endif