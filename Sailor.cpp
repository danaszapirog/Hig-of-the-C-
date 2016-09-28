#include "Model.h"
#include "Sailor.h"
#include <cmath>

//default Sailor constructor.
Sailor::Sailor(char dc, Model* model):GameObject(dc,0)
{
    this->world = model;
    this->state='a';
    this->health=60;
    this->size=15;
    this->hold=100;
    this->cargo=0;
    this->destination=CartPoint();
    this->port=NULL;
    this->display_code=dc;
    this->dock=NULL;
    this->hideout=NULL;
    this->originalsize=size;
    cout<<"Sailor default constructed"<<endl;
}

Sailor::Sailor(char dc, int id, CartPoint plocation, Model* model):GameObject(dc ,id, plocation)
{
    this->world = model;
    this->state='a';
    this->health=60;
    this->size=15;
    this->hold=100;
    this->cargo=0;
    this->hideout=NULL;
    this->port=NULL;
    this->dock=NULL;
    this->location=plocation;
    this->display_code=dc;
    this->originalsize=size;
    cout<<"Sailor constructed"<<endl;
}

//sailor constructor with id and hideout arguements
Sailor::Sailor(char dc, int in_id, Dock* in_hideout, Model* model):GameObject(dc ,in_id, in_hideout->get_location())
{
    this->world = model;
    this->state='h';
    this->health=60;
    this->size=15;
    this->hold=100;
    this->cargo=0;
    this->location = in_hideout->get_location();
    this->destination = in_hideout->get_location();
    this->port=NULL;
    this->dock=NULL;
    this->hideout=in_hideout;
    this->display_code=dc;
    this->originalsize=size;
    cout<<"Sailor constructed"<<endl;
}
//function to get size of Sailor.
double Sailor::get_size()
{
    return this->size;
}
//function to get cargo of sailor
double Sailor::get_cargo()
{
    return this->cargo;
}

//start sailing function ??
void Sailor::start_sailing(CartPoint dest)
{
    setup_destination(dest);
    cout<<"Sailing "<<get_id()<<" to "<<dest<<endl;
    cout<<this->display_code<<get_id()<<": On my way"<<endl;
    if (this->state=='d')
    {
        dock->set_sail(this);
    }
    this->state='s';
    
}

//start supplying function. Setup new port destination, updates state to outbound and prints supplying message. 
void Sailor::start_supplying(Port* destPort)
{
    this->port=destPort;
    CartPoint dest=port->get_location();
    setup_destination(dest);
    if (this->state=='d')
    {
        dock->set_sail(this);
    }
    this->state='o';
    cout<<"Sailor "<<get_id()<<" supplying at Port "<<port->get_id()<<" and going to Port "<<port->get_id()<<endl;
    cout<<this->display_code<<get_id()<<": Supplies here I come!"<<endl;
    
}

//start hiding function. setup hiding destination, updates state and prints out hiding message (to be checked??)
void Sailor::start_hiding()
{
    if (this->state=='d')
    {
        dock->set_sail(this);
    }
    this->state='h';
    CartPoint dest=hideout->get_location();
    setup_destination(dest);
    cout<<"Sailor "<<get_id()<<" hiding "<<hideout->get_id()<<endl;
    cout<<this->display_code<<get_id()<<": Off to hide"<<endl;
}

//checks if sailor is hidden (if arrived to hideout location)
bool Sailor::is_hidden()
{
    if(this->hideout != (Dock*)NULL)
    {
        bool hidden=cart_compare(this->location, hideout->get_location());
        if (hidden)
        {
            return true;
        }
        else
            return false;
    }
    return false;
}

//start docking function. Setup destination to dock location, updates state to inbound and prints out docking message (to be checked??)
void Sailor::start_docking(Dock* destDock)
{
    if (this->state=='d')
    {
        dock->set_sail(this);
    }
    this->dock = destDock;
    setup_destination(dock->get_location());
    this->state='i';
    cout<<"Sailor "<<get_id()<<" sailing to Dock "<<dock->get_id()<<endl;
    cout<<this->display_code<<get_id()<<": Off to Dock"<<endl;
}

//stops sailor and updates state to anchored
void Sailor::anchor()
{
    setup_destination(location);
   this->state='a'; 
    cout<<"Stopping "<<get_id()<<endl;
    cout<<this->display_code<<get_id()<<": Dropping anchor"<<endl;
}

void Sailor::show_status()
{
    char sailorState=this->state;
    cout<<"Sailor status: "<<this->display_code<<" with ID "<<get_id()<<" at location "<<get_location()<<" ";
    switch(sailorState)
    {
        case 'a': 
            {
                bool hidden=is_hidden();
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
        case 's': cout<<"Has a speed of: "<<get_speed()<<" and is heading to: "<<this->destination<<endl;
            break;
        case 'o': cout<<"is outbound to Port: "<<port->get_id()<<" With a speed of "<<get_speed()<<endl;
            break;
        case 'i': cout<<"is inbound to Dock: "<<dock->get_id()<<" With a speed of "<<get_speed()<<endl;
            break;
        case 'l': cout<<"is supplying at Port "<<port->get_id()<<endl;
            break;
        case 'u': cout<<"is unloading at Dock "<<dock->get_id()<<endl;
            break;
        case 'd': cout<<"is docked at Dock "<<dock->get_id()<<endl;
            break;
        case 't': cout<<"is in trouble "<<get_id()<<endl;
            break;
        case 'h':cout<<" is going to hide at Dock "<<hideout->get_id()<<endl;
            break;
    }
    
}

//calculates speed of sailor
double Sailor::get_speed()
{
    double speed=(size-((cargo)*0.1));
    return speed;
}
                  
//update speed function. if sailor have not arrived to destination adds delta to location
bool Sailor::update_location()
{
    if(fabs(this->destination.x-this->location.x)<=fabs(this->delta.x) && fabs(this->destination.y-this->location.y)<=fabs(this->delta.y) || ((this->destination.x == this->location.x) && (this->destination.y == this->location.y)) )
    {
        this->location=this->destination;
        cout<<this->display_code<<get_id()<<": I'm there!"<<endl;
        return true;
    }
    else
    {
        this->location=this->location+delta;
        cout<<this->display_code<<get_id()<<": Just keep sailing... " <<endl;
        return false;
    }
    
}

//setup destination function. updates destination and calculates delta value. 
void Sailor::setup_destination(CartPoint dest)
{
    this->destination=dest;
    double speed=get_speed();
    this->delta=(this->destination-this->location) * speed / cart_distance(this->location, this->destination);
    if( cart_distance(this->location, this->destination) == 0)
    {
        this->delta=CartVector(0,0);
        this->state='a';
    }
}

bool Sailor::update()
{
    switch (this->state)
    {
        case 'a':
            {
                return false;
            }
        case 's':
            {
                bool v= update_location();
            if (v)
            {
                this->state='a';
                return true;
            }

            else
                return false;
            }
        case 'o':
            {
            bool v=update_location();
            if (v)
            {
                this->state='l';
                cout<<this->display_code<<get_id()<<": Starting to supply at a port"<<endl;
                return true;
            }  
            else
                return false;
            }
        case 'i':
            {
             bool v=update_location();
            if (v)
            {
                this->state='u';
                cout<<this->display_code<<get_id()<<": Starting to unload at a dock"<<endl;
                return true;
            }  
            else
                return false;
            }
        case 'l':
            {
            if(this->cargo==this->hold)
            {
                this->state='a';
                cout<<this->display_code<<get_id()<<": My boat is filled up. Send me to a Dock to unload. Dropping anchor"<<endl;
                return true;
            }
            else 
            {   
                double supplies= port->provide_supplies();
                if (supplies!=0)
                {
                    if((this->cargo+supplies)<this->hold)
                    {
                        this->cargo+=supplies;
                        cout<<this->display_code<<get_id()<<": My new cargo is "<<this->cargo<<endl;
                        return false;
                    }
                    else if (this->cargo+supplies>=hold)
                    {
                        this->cargo=this->hold;
                        cout<<this->display_code<<get_id()<<": My new cargo is "<<this->cargo<<endl; 
                            return false;
                    }   
                }
                else if (supplies==0)
                {
                    this->state='a';
                    cout<<this->display_code<<get_id()<<": this Port has no more supplies for me. Dropping anchor"<<endl;
                    return true;
                }
                    
            }
            return false;
            }
        case 'u':
            {
                this->originalsize=this->size;
                bool d=dock->dock_boat(this);
                if(d==true)
                {
                    this->state='d';
                    cout<<this->display_code<<get_id()<<": I am unloading at the dock"<<endl;
                    if(this->cargo>0)
                    {
                        this->size+=5;
                        this->hold+=20;
                        this->cargo=0;
                    }
                    return true;
                }
                else if (d!=true)
                {
                    this->state='t';
                    cout<<this->display_code<<get_id()<<": Help! My home dock is full"<<endl;
                    return true;
                }
                else
                    return false;
            }
        case 'h':
            {
                update_location();
                bool hidden=is_hidden();
                this->health-=1/4;
                if (this->health<5)
                {
                    this->state='x';
                    return true;
                }
                if (hidden)
                {
                    this->state='a';
                    return true;
                }
                else
                {
                    return false;
                }  
            }
        case 't':
            {
                return false;
            }
        default: return false;
    }
    
}

void Sailor::start_plunder(Sailor* s)
{
    cout<<"I cannot plunder."<<endl;
}

bool Sailor::start_recruiting(Sailor* s)
{
    cout<<"I cannot recruit."<<endl;
}

void Sailor::get_plundered(int attack_stength)
{
    this->health-=attack_stength;
    if (this->health<=0)
    {
        cout<<"Oh no, now I'm in Davy Jones' Locker!"<<endl;
        this->state='x';
    }
    else
    {
        cout<<"Ouch!"<<endl;
    }
}

Sailor::~Sailor()
{
    cout<<"Sailor destructed."<<endl;
}

char Sailor::get_display()
{
    char code=this->display_code;
    return code;
}
CartPoint Sailor::get_location()
{
    return this->location;
}

    
