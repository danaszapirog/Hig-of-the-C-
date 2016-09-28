#include "Port.h"


Port::Port():GameObject('P', 0)
{
    this->state='f'; 
    this->inventory=500;
    cout<<"Port default constructed"<<endl;
}

Port::Port(int in_id, CartPoint in_loc): GameObject('P', in_id, in_loc)
{
    this->state='f';  
    this->inventory=500;
    cout<<"Port constructed"<<endl;
}

bool Port::is_empty()
{
    if(this->inventory==0)
        return true;
    else
        return false;
}

double Port::provide_supplies(double amount_to_provide)
{
    if(this->inventory >= amount_to_provide)
    {
        this->inventory-=amount_to_provide;
        return amount_to_provide;
    }
    else if (this->inventory < amount_to_provide)
        this->inventory=0;
        return this->inventory;
    
}

bool Port::update()
{
    if (this->is_empty()==true && this->state!='e')
    {
        this->state='e';
        this-> display_code='p';
        cout<<"Port "<<get_id()<<" has been depleted of supplies"<<endl;
        return true;
    }
    else
        return false;
}

void Port::show_status()
{
    cout<<"Port Status: "<<this->display_code<<" with ID "<<get_id()<<" at location "<<get_location()<<" containing supplies "<<this->inventory<<endl;
}

Port::~Port()
{
    cout<<"Port destructed."<<endl;
}