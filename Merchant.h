#ifndef MERCHANT_H
#define MERCHANT_H

#include "Sailor.h"
//#include "Model.h"
//#include "Dock.h"

class Sailor;
class Model;
class Dock;

class Merchant : public Sailor
{
 public:
    Merchant(Model*);
    Merchant(int, Dock*, Model*);
    double get_speed();
    bool start_recruiting(Merchant*);
    bool update();
    void show_status();
    int insideTime;
    Merchant* mate;
    
};
#endif