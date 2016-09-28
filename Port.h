#ifndef PORT_H
#define PORT_H
#include <iostream>
using namespace std;

#include "CartPoint.h"
#include "GameObject.h"

class Port: public GameObject
{
public:
    Port();
    Port(int, CartPoint);
    bool is_empty();
    double provide_supplies(double = 50);
    bool update();
    void show_status();
    ~Port();
private:
    double inventory;
};

#endif