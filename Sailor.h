#ifndef SAILOR_H
#define SAILOR_H
#include <iostream>


#include "Port.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "GameObject.h"
#include "Dock.h"
using namespace std;

class Dock;
class Model;

class Sailor : public GameObject
{
public:
    CartPoint get_location();
    CartPoint location;
    Sailor(char, Model*);
    Sailor(char, int, Dock*, Model*);
    virtual bool update();
    double originalsize;
    double get_size();
    double get_cargo();
    void start_sailing(CartPoint);
    void start_supplying(Port* destPort);
    void start_hiding();
    bool is_hidden();
    void start_docking(Dock*);
    void anchor();
    void show_status();
    virtual double get_speed()=0;
    virtual void start_plunder(Sailor*);
    virtual bool start_recruiting(Sailor*);
    void get_plundered(int);
    ~Sailor();
    char get_display();
    char display_code;
    
//protected:
    Model* world;
    Dock* hideout;
    double health, size, hold, cargo;
    Sailor(char display_code, int id, CartPoint location, Model*);
    CartPoint destination;
    CartVector delta;
    Port* port;
    Dock* dock;
    bool update_location();
    void setup_destination(CartPoint);    
};
#endif