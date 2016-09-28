#ifndef VIEW_H
#define VIEW_H

#include <iostream>
using namespace std;

#include "Port.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "GameObject.h"
#include "math.h"
#include "Dock.h"
#include "Sailor.h"
#include "model.h"
#include "GameCommand.h"


static int view_maxsize=20;

class View
{
public:
    View();
    void clear();
    void plot(GameObject* otr);
    void draw();
    ~View();
    
private:
    int size;
    double scale;
    CartPoint origin;
    char grid[20][20][2];
    bool get_subscripts(int &ix, int &iy, CartPoint location);
};

#endif