#ifndef DOCK_H
#define DOCK_H


#include "CartPoint.h"
#include "GameObject.h"


class Sailor;

class Dock: public GameObject
{
public:
    Dock();
    Dock(int, CartPoint);
    bool dock_boat(Sailor* sailor_to_dock);
    bool set_sail(Sailor* sailor_to_dock);
    bool update();
    void show_status();
    ~Dock();
    double get_berths();
private:
    double berths;
};

#endif