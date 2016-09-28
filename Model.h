#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <list>

#include "Port.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "GameObject.h"
#include "Dock.h"
#include "Sailor.h"
#include "Pirate.h"
#include "Merchant.h"
#include "View.h"
#include "Kraken.h"
using namespace std;

class View;
class Sailor;
class Dock;
class GameObject;
class Port;
class Pirate;
class Merchant;

class Model
{
public:
    Model();
    ~Model();
    Sailor* get_Sailor_ptr(int id_num);
    Port* get_Port_ptr(int id_num);
    Dock* get_Dock_ptr(int id_num);
    bool update();
    void display(View& view);
    void show_status();
    int time;
    int num_objects;
    int num_sailors;
    int num_docks;
    int num_ports;
    void add_merchant(Sailor*); 
    void add_port(Port* newport);
    void add_dock(Dock* newdock);
    void add_pirate(Sailor* newpirate);
    
//private:
    list<GameObject*>* object_ptrs;
    list<Dock*>* dock_ptrs;
    list<Sailor*>* sailor_ptrs;
    list<Port*>* port_ptrs;
    list<GameObject*>* active_ptrs;
    bool is_alive(GameObject*);
    int lowestmID();
    bool canrecruit(Sailor*);

};


#endif