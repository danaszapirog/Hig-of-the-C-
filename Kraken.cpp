#include "Kraken.h"

Kraken::Kraken(Model* model)
{
    this->world=model;
    sailor_killed = new list<Sailor*>();
}

Kraken* Kraken::getKraken(Model* model)
{
    static Kraken* kraken = new Kraken(model); 
}
bool Kraken::start_krakening()
{   
    int time= world->time;
    if (time%15 == 10)
    {
        cout<<"Early Kraken Warning!"<<endl;
        return true;
    }
    else if(time%15==0 && time!=0)
    {

      for (list<Sailor*>::iterator it = world->sailor_ptrs->begin(); it !=   world->sailor_ptrs->end(); it++)
        {
          GameObject* ob = (*it);
          if( ob->state!='d' || ob->state!='r')
          {
            sailor_killed->push_back(*it);
            world->active_ptrs->remove(*it);
          }
        }
        cout<<"The Kraken is upon us!"<<endl;
        cout<<"----------The Kraken Claimed----------"<<endl;
        int i=1;
       for (list<Sailor*>::iterator it = sailor_killed->begin(); it !=         sailor_killed->end(); it++)
       {
           cout<<"("<<i<<")"<<(*it)->display_code<<(*it)->id_num<<endl;
           i++;
       }
        cout<<"-----------------------------------------"<<endl;
        return true;
        
    }
    return false;
}

void Kraken::printsailors()
{
        cout<<"----------The History of Kraken's Wrath----------"<<endl;
        int i=1;
       for (list<Sailor*>::iterator it = sailor_killed->begin(); it !=         sailor_killed->end(); it++)
       {
           cout<<"("<<i<<")"<<(*it)->display_code<<(*it)->id_num<<endl;
           i++;
       }
        cout<<"----------------------------------------------------"<<endl;
}

