#include "Port.h"
#include "Sailor.h"
#include "Model.h"
#include "Dock.h"
#include "GameCommand.h"
#include "InvalidInput.h"
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

void do_sail_command(Model* model)
{
    int ID;
    if (!(cin>>ID))
       throw InvalidInput("Was expecting an integer");
    Sailor* sailor=model->get_Sailor_ptr(ID);
    if(sailor==(Sailor*)NULL){
        throw InvalidInput("Invalid Sailor ID");}
    else
    {
        double x, y;
        cin>>x>>y;
        CartPoint dest= CartPoint(x,y);
        sailor->start_sailing(dest);
    }

}

void do_go_command(Model* model)
{
    cout<<"Advancing time one tick"<<endl;
    model->update();
}

void do_run_command(Model* model)
{   
    cout<<"Advancing to next event or 5 ticks"<<endl;
    int i=1;
    bool updatecheck = false;
    while(updatecheck!= true && i<=5)
    {
        updatecheck=model->update();
        i++;
    }
}

void do_port_command(Model* model)
{
    int ID1, ID2;
    if (!(cin>>ID1>>ID2))
        throw InvalidInput("Was expecting an integer");
    Sailor* sailor=model->get_Sailor_ptr(ID1);
    Port* port=model->get_Port_ptr(ID2);
    if(sailor!=(Sailor*)NULL && port!=(Port*)NULL)
    {
        sailor->start_supplying(port);
    }
    else if (sailor==(Sailor*)NULL)
        throw InvalidInput("Invalid Sailor ID");
    else if (port==(Port*)NULL)
        throw InvalidInput("Invalid Port ID");
}
void do_hide_command(Model* model)
{
    int ID;
    if (!(cin>>ID))
        throw InvalidInput("Was expecting an integer");
    Sailor* sailor=model->get_Sailor_ptr(ID);
    if(sailor!=(Sailor*)NULL)
    {
        sailor->start_hiding();
    }
    else if (sailor==(Sailor*)NULL)
        throw InvalidInput("Invalid Sailor ID");
}

void do_anchor_command(Model* model)
{
    int ID;
    if (!(cin>>ID))
        throw InvalidInput("Was expecting an integer");
    Sailor* sailor=model->get_Sailor_ptr(ID);
    if(sailor!=(Sailor*)NULL)
    {
        sailor->anchor();
    }
    else if (sailor==(Sailor*)NULL)
        throw InvalidInput("Invalid Sailor ID");
}
void do_list_command(Model* model)
{
    model->show_status();
}
    
void do_dock_command(Model* model)
    {
    int ID1, ID2;
    if (!(cin>>ID1>>ID2))
        throw InvalidInput("Was expecting an integer");
    Sailor* sailor=model->get_Sailor_ptr(ID1);
    Dock* dock=model->get_Dock_ptr(ID2);
    if(sailor!=(Sailor*)NULL && dock!=(Dock*)NULL)
    {
        sailor->start_docking(dock);
    }
    else if (sailor==(Sailor*)NULL)
        throw InvalidInput("Invalid Sailor ID");
    else if (dock==(Dock*)NULL)
        throw InvalidInput("Invalid Dock ID");
    
}


//??
void plUnder(Model* model)
{
    int ID1, ID2;
    if (!(cin>>ID1>>ID2))
        throw InvalidInput("Was expecting an integer");
    Sailor* sailor1=model->get_Sailor_ptr(ID1);
    Sailor* sailor2=model->get_Sailor_ptr(ID2);
    if(sailor1!=(Sailor*)NULL && sailor2!=(Sailor*)NULL)
    {
        sailor1->start_plunder(sailor2);
    }
    
}

void handle_new_command(Model* model)
{
    int ID;
    char type;
    int xin, yin;
    cin>>type>>ID;
    if(!cin>>type>>ID)
    {
        throw InvalidInput("invalid type");
    }
    if(!cin>>ID)
    {
        throw InvalidInput("Was expecting integer foe ID");
    }
    if(type=='P')
    {
        cin>>xin>>yin;
        if(!cin>>xin>>yin){
            throw InvalidInput("Was expecting doubles for Location");}
        if (model->get_Port_ptr(ID)!=(Port*)NULL){
            throw InvalidInput("Duplicate ID"); } 
        Port* port= new Port(ID, CartPoint(xin,yin));
        model->add_port(port);
    }
    else if(type=='D')
    {
        cin>>xin>>yin;
        if(!cin>>xin>>yin){
            throw InvalidInput("Was expecting doubles for Location");}
        if (model->get_Dock_ptr(ID)!=(Dock*)NULL){
            throw InvalidInput("Duplicate ID");}
        Dock* dock=new Dock(ID, CartPoint(xin,yin));
        model->add_dock(dock);
    }
    else if(type=='M')
    {
        int idHome;
        cin>>idHome;
        if (!cin>>idHome){
            throw InvalidInput("Was expecting an integer for ID");
        }
        if (model->get_Dock_ptr(idHome)==(Dock*)NULL){
            throw InvalidInput("no dock ID");}
        if (model->get_Sailor_ptr(ID)!=(Sailor*)NULL){
            throw InvalidInput("Duplicate ID");}
        Dock* home =model->get_Dock_ptr(idHome);
        Sailor* merchant=new Merchant(ID, home, model);
        model->add_merchant(merchant);
    }
    else if(type=='R')
    {
        if (model->get_Sailor_ptr(ID)!=(Sailor*)NULL)
            throw InvalidInput("Duplicate ID");
        Pirate* pirate=new Pirate(ID,model);
        model->add_pirate(pirate);
    }
}


void savecommand(Model* model)
{
    string filename;
    cin>>filename;
    ofstream output;
    output.open(filename);
    int timer= model->time;
    output<<timer<<endl;
    for (list<GameObject*>::iterator it = model->active_ptrs->begin(); it !=   model->active_ptrs->end(); it++)
    {
        GameObject* object = (*it);
        char obstate = object->display_code;
        output<<obstate;
        switch (obstate)
        {
            case 'd':
                {
                    output<<object->get_id()<<" "<<object->location.x<<" "<<object->location.y<<" "<<endl;
                    break;
                }
            case 'P':
                {
                    output<<object->get_id()<<" "<<object->location.x<<" "<<object->location.y<<endl;
                    break;
                }
            case 'M':
                {
                    Merchant* objectm = (Merchant*)object;
                    output<<objectm->state<<" "<<objectm->get_id()<<" "<<objectm->location.x<<" "<<objectm->location.y<<" "<<objectm->hideout->get_id()<<endl;
                    break;
                }
            case 'R':
                {
                     output<<object->state<<" "<<object->get_id()<<" "<<object->location.x<<" "<<object->location.y<<endl;
                    break;
                }

        }
    } 
        output.close();
}



void restorecommand(Model* model)
{
    
    model->dock_ptrs->clear();
    model->object_ptrs->clear();
    model->active_ptrs->clear();
    model->port_ptrs->clear();
    model->sailor_ptrs->clear();
    string line;
    string filename;
    cin>>filename;
  ifstream myfile (filename);
    char code;
  if (myfile.is_open())
  {
    myfile >> model->time;
      srand(model->time);
    while (!myfile.eof()) {
        while ( getline (myfile,line) ){


    myfile >> code;
        if(code=='d'){
            int id;
            double inx, iny;
            myfile>>id>>inx>>iny;
            Dock* dock = new Dock(id, CartPoint(inx,iny));
            model->dock_ptrs->push_back(dock);
            model->object_ptrs->push_back(dock);
            model->active_ptrs->push_back(dock);
            continue;
        }
        else if (code=='P'){
            int id;
            double inx, iny;
            myfile>>id>>inx>>iny;
            Port* port = new Port(id, CartPoint(inx, iny));
            model->port_ptrs->push_back(port);
            model->object_ptrs->push_back(port);
            model->active_ptrs->push_back(port);
            continue;
        }
        else if (code=='M'){
            int id, idhideout;
            double inx, iny;
            char nstate;
            myfile>>nstate>>id>>inx>>iny>>idhideout;
            Dock* home= model->get_Dock_ptr(idhideout);
            Sailor* merchant = new Merchant(id, home, model);
            merchant->location.x=inx;
            merchant->location.y=iny;
            merchant->state=nstate;
            model->sailor_ptrs->push_back(merchant);
            model->object_ptrs->push_back(merchant);
            model->active_ptrs->push_back(merchant);
            continue;
        }
        else if (code=='R'){
            int id;
            double inx, iny;
            char nstate;
            myfile>>nstate>>id>>inx>>iny;
            Sailor* pirate = new Pirate(id, model);
            pirate->location.x=inx;
            pirate->location.y=iny;
            pirate->state=nstate;
            model->sailor_ptrs->push_back(pirate);
            model->object_ptrs->push_back(pirate);
            model->active_ptrs->push_back(pirate);
            continue;
        }
            model->update();
    }
    }
    }
    myfile.close();
 }


