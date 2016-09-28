#include "Model.h"
#include "Kraken.h"

Kraken* kraken;
//create all objects
Model::Model()
{
    this->time=0;
    srand(this->time);
    object_ptrs = new list<GameObject*>();
    dock_ptrs = new list<Dock*>();
    sailor_ptrs = new list<Sailor*>();
    port_ptrs = new list<Port*>();
    active_ptrs = new list<GameObject*>();
    
    Dock* dock1 = new Dock(1, CartPoint(5,1));
    dock_ptrs->push_back(dock1);
    object_ptrs->push_back(dock1);
    active_ptrs->push_back(dock1);
    Dock* dock2 = new Dock(2, CartPoint(6,2));
    dock_ptrs->push_back(dock2);
    object_ptrs->push_back(dock2);
    active_ptrs->push_back(dock2);
    Dock* dock3 = new Dock(3, CartPoint(1,8));
    dock_ptrs->push_back(dock3);
    object_ptrs->push_back(dock3);
    active_ptrs->push_back(dock3);
    Port* port1 = new Port(1, CartPoint(1,20));
    port_ptrs->push_back(port1);
    object_ptrs->push_back(port1);
    active_ptrs->push_back(port1);
    Port* port2 = new Port(2, CartPoint(20,1));
    port_ptrs->push_back(port2);
    object_ptrs->push_back(port2);
    active_ptrs->push_back(port2);
    Port* port3 = new Port(3, CartPoint(20,20));
    port_ptrs->push_back(port3);
    object_ptrs->push_back(port3);
    active_ptrs->push_back(port3);
    Port* port4 = new Port(4, CartPoint(7,2));
    port_ptrs->push_back(port4);
    object_ptrs->push_back(port4);
    active_ptrs->push_back(port4);
    Merchant* merchant1 = new Merchant(1, dock1, this);
    sailor_ptrs->push_back(merchant1);
    object_ptrs->push_back(merchant1);
    active_ptrs->push_back(merchant1);
    Merchant* merchant2 = new Merchant(2, dock1, this);
    sailor_ptrs->push_back(merchant2);
    object_ptrs->push_back(merchant2);
    active_ptrs->push_back(merchant2);
    Merchant* merchant3 = new Merchant(3, dock2, this);
    sailor_ptrs->push_back(merchant3);
    object_ptrs->push_back(merchant3);
    active_ptrs->push_back(merchant3);
    Pirate* pirate1 = new Pirate(4, this);
    sailor_ptrs->push_back(pirate1);
    object_ptrs->push_back(pirate1);
    active_ptrs->push_back(pirate1);
    Pirate* pirate2 = new Pirate(5, this);
    sailor_ptrs->push_back(pirate2);
    object_ptrs->push_back(pirate2);
    active_ptrs->push_back(pirate2);

    
    num_objects = 12;
    num_sailors = 5;
    num_ports = 4;
    num_docks = 3;
    cout<<"GameObject constructed"<<endl;
    cout<<"Model default constructed"<<endl;
}

//destructor

Model::~Model()
{
    kraken->printsailors();
   for (list<GameObject*>::iterator it = object_ptrs->begin(); it != object_ptrs->end(); it++)
   {
    cout<<"Model destruced"<<endl;
    delete *it;
  }

}

bool Model::is_alive(GameObject* it)
{
    if(it->state=='x')
        return false;
    else
        return true;
}
//get poiner to object functions. itinerates through arrays and look for specific object with corresponding ID.
Sailor* Model::get_Sailor_ptr(int id_num)
{
    for (list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++)
    {
        if((*it)->get_id()==id_num){
            return *it;}
    }
    return NULL;
}

Port* Model::get_Port_ptr(int id_num)
{
    for (list<Port*>::iterator it = port_ptrs->begin(); it != port_ptrs->end(); it++)
    {
        if((*it)->get_id()==id_num){
            return *it;}
    }
    return NULL;
}

Dock* Model::get_Dock_ptr(int id_num)
{
    for (list<Dock*>::iterator it = dock_ptrs->begin(); it != dock_ptrs->end(); it++)
    {
        if((*it)->get_id()==id_num){
            return *it;}
    }
    return NULL;
}

//update function. calls a pure virtual update function in GameObject to update all objects. Increments time.
bool Model::update()
    
{
    bool ifChanged=false;
    this->time++;
    srand(this->time);
    if(kraken == (Kraken*)NULL)
    {
        kraken = new Kraken(this);
    }
    for (list<GameObject*>::iterator it = object_ptrs->begin(); it != object_ptrs->end(); it++)
    {
        if(!is_alive(*it))
        {
            active_ptrs->remove(*it);
        }
    }
    for (list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++)
    {
      bool check=(*it)->update();
        if (check == true)
        {
            ifChanged=true;  
        }
    }
    bool krakencheck = kraken->start_krakening();
    
    return ( ifChanged || krakencheck);
}

void Model::display(View& view)
{
    cout<<"Time: "<<this->time<<endl;
    view =View();
    view.clear();
    for (list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++)
    {
      view.plot(*it); 
    }
    view.draw();
}

void Model::show_status()
{
    for (list<GameObject*>::iterator it = active_ptrs->begin(); it != active_ptrs->end(); it++)
    {
      (*it)->show_status();  
    }
    
}

void Model::add_merchant(Sailor* newMerchant)
{
    sailor_ptrs->push_back(newMerchant);
    object_ptrs->push_back(newMerchant);
    active_ptrs->push_back(newMerchant); 
    this->num_sailors++;
}
    
void Model::add_port(Port* newport)
{
    port_ptrs->push_back(newport);
    object_ptrs->push_back(newport);
    active_ptrs->push_back(newport);
    this->num_ports++;
}

void Model::add_dock(Dock* dock)
{
    Dock* newdock= dock;
    dock_ptrs->push_back(newdock);
    object_ptrs->push_back(newdock);
    active_ptrs->push_back(newdock);
    this->num_docks++;
}

void Model::add_pirate(Sailor* newpirate)
{
    sailor_ptrs->push_back(newpirate);
    object_ptrs->push_back(newpirate);
    active_ptrs->push_back(newpirate); 
    this->num_sailors++;
}

int Model::lowestmID()
{
    for(int i=1; i<=num_sailors ; i++)
    {
        Sailor* sailorid = get_Sailor_ptr(i);
        if (sailorid == (Sailor*)NULL)
        {
            return i;
        }
    }
    return num_sailors+1;
}

bool Model::canrecruit(Sailor* sailor)
{
    CartPoint hideloc= sailor->hideout->get_location();
    int nummerch = 0;
    for (list<Sailor*>::iterator it = sailor_ptrs->begin(); it != sailor_ptrs->end(); it++)
    {
        Sailor* ob = (*it);
        if(cart_compare(ob->location,hideloc) && ob->is_hidden()){
            nummerch++;
        }
    }
    if(nummerch==2){
        return true;
    }
    return false;
}


