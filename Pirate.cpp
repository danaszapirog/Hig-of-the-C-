#include "Pirate.h"
#include "Model.h"
#include <ctime>


Pirate::Pirate(Model* model): Sailor('R', model)
{
    this->size=15;
    this->attack_strength=2;
    this->range=1;
    this->health=25;
}

Pirate::Pirate(int id, Model* model): Sailor('R', id, CartPoint((rand()%20),(rand()%20)), model)
{   
    this->size=15;
    this->id_num=id;
    this->attack_strength=2;
    this->range=1;
    this->health=25;
}
                                                   
double Pirate::get_speed()
{
    double speed=0;
    return speed;
}

void Pirate::start_plunder(Sailor* target)
{
    if (cart_distance(this->get_location(),target->get_location())<=this->range)
    {
        cout<<"Arrrggghhhh!"<<endl;
        this->state='p';
        this->target=target;
        target->get_plundered(this->attack_strength);
    }
    else
    {
        cout<<this->display_code<<this->id_num<<": I will be back for you!"<<endl;
    }
}
   
bool Pirate::update()
{
    char s=this->state;
    switch(s)
    {
        case 'x':
            {
                
                
                return false;
            }
        case 's': 
            {
                return false;
            }
        case 'p':
            {
               if (cart_distance(get_location(), target->get_location())>this->range) 
               {
                   cout<<"Darn! it escaped."<<endl;
                   return true;
               }
                else
                {
                    if(target->get_state() == 'x')
                    {
                        cout<<"I triumph!"<<endl;
                        this->state='s';
                        this->attack_strength+=5;
                        return true;
                    }
                    else
                    {
                        cout<<"Arrghh matey!"<<endl;
                        target->get_plundered(this->attack_strength);
                        return false;
                    }
                }
            }
    }
    Sailor::update();
}

void Pirate::show_status()
{
    char pirateState=this->state;
    cout<<"Pirate status: "<<this->get_display()<<" with ID "<<get_id()<<" at location "<<get_location()<<" ";
    switch(pirateState)
    {
            case 'a': 
            {
                bool hidden=this->is_hidden();
                if (hidden)
               {
                   cout<<"is anchored (and hiding). Has a size of: "<<this->size<<", cargo of: "<<this->cargo<<", hold of: "<<this->hold<<", and health of: "<<this->health<<endl;
               }
                else
                {
                   cout<<"is anchored. Has a size of: "<<this->size<<", cargo of: "<<this->cargo<<", hold of: "<<this->hold<<", and health of: "<<this->health<<endl;
               }
                    
            break;
            }
        case 's': 
            {
                cout<<"Has a speed of: "<<get_speed()<<" and is heading to: "<<this->destination<<endl;
                break;
            }
        case 'o': 
            {
                cout<<"is outbound to Port: "<<port->get_id()<<" With a speed of "<<get_speed()<<endl;
                break;
            }
        case 'i': 
            {
                cout<<"is inbound to Dock: "<<dock->get_id()<<" With a speed of "<<get_speed()<<endl;
                break;
            }
        case 'l': 
            {
                cout<<"is supplying at Port "<<port->get_id()<<endl;
                break;
            }
        case 'u': 
            {
                cout<<"is unloading at Dock "<<dock->get_id()<<endl;
                break;
            }
        case 'd': 
            {   
                cout<<"is docked at Dock "<<dock->get_id()<<endl;
                break;
            }
        case 't': 
            {
                cout<<"is in trouble "<<get_id()<<endl;
                break;
            }
        case 'h':
            {
                cout<<"is going to hide at Dock "<<hideout->get_id()<<endl;
                break;
            }
    }
}