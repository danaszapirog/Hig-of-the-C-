
#include "Sailor.h"
#include "Dock.h"
#include <fstream>
using namespace std;


//default Dock constructor
Dock::Dock():GameObject('d', 0)
{
    this->state = 'e';
    this->berths=30;
    cout<<"Dock default constructed"<<endl;
}
//Dock constructor in id and location arguements. 
Dock::Dock(int in_id, CartPoint in_loc):GameObject('d', in_id, in_loc)
{
    this->state = 'e';
    this->berths=30; 
    cout<<"Dock constructed"<<endl;
}

//Check if there is enought space in the dock for the boat's size and docks it. then updates the available space in the dock
bool Dock::dock_boat(Sailor* sailor_to_dock)
{
    if(this->berths>=sailor_to_dock->get_size())
    {
        this->berths-=(sailor_to_dock->get_size());
        return true;
    }
    else
        return false;
}

//set_sail function. Lets sailor sail if their boat is empty (cargo=0). Updates the new available space in the dock after the sailor leaves. 

bool Dock::set_sail(Sailor* sailor_to_sail)
{
    double cargo=sailor_to_sail->get_cargo();
    double size=sailor_to_sail->get_size();
    if(cargo==0)
    {
        this->berths+=sailor_to_sail->originalsize;
        return true;
    }
    else
        return false;
}

//update function. updates state and code. 

bool Dock::update()
{
    if(berths==0 && state!='p')
    {
        this->state='p';
        this->display_code='D';
        cout<<"Dock "<<get_id()<<" is packed"<<endl;
            return true;
    }
    else if(berths!=0 && state=='p')
    {
        this->display_code='d';
        this->state='u';
        return true;
    }
    else 
        return false;
    
}

//Print out status of dock
void Dock::show_status()
{
    cout<<"Dock Status: "<<this->display_code<<" with ID "<<get_id()<<" at location "<<get_location()<<" has "<<this->berths<<" berths"<<endl;
}

Dock::~Dock()
{
    cout<<"Dock desctruced."<<endl;
}

double Dock::get_berths()
{
    return this->berths;
}

