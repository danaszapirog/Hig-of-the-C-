#include "Merchant.h"
#include "Model.h"

Merchant::Merchant(Model* model):Sailor('M', model)
{
    this->size=10;
    this->insideTime=0;
    
}

Merchant::Merchant(int id, Dock* home, Model* world):Sailor('M', id, home, world)
{
    this->size=10;
    this->state='h';
    this->insideTime=0;
}

double Merchant::get_speed()
{
    double speed=(1/size)*(this->health)*4;
    return speed;
}

bool Merchant::start_recruiting(Merchant* sailor_mate)
{
    if((sailor_mate->hideout)==this->hideout && this->is_hidden() && sailor_mate->is_hidden() && hideout->get_berths()>(this->size+sailor_mate->size) && ((this->health + sailor_mate->health)>80 || (this->health + sailor_mate->health)<120) )
    {
        this->mate= sailor_mate;
        this->state='r';
        sailor_mate->state='r';
        sailor_mate->mate=this;
        return true;
    }
    else
        return false; 
        
}

bool Merchant::update()
{
    switch (this->state)
    {
        case 'r':
            { 
                this->insideTime++;
                if(this->mate->state!='r')
                {
                    this->state='a';
                    this->insideTime=0;
                    return true;
                }
                if(this->insideTime==2 && this->mate->state=='r' && this->mate->insideTime==2 && world->canrecruit(this))
                { 
                    int newid = world->lowestmID();
                    Sailor* newMerchant = new Merchant(newid, this->hideout, this->world);
                    world->add_merchant(newMerchant);
                    this->state='a';
                    this->mate->state='a';
                    this->insideTime=0;
                    return true;
                }
                
                else
                    return false;
                  
            }
        case 'a':
            {
                if(is_hidden())
                {
                    this->health-=5;
                    for(int i=1; i<=world->num_sailors; i++)
                    {
                        if (world->get_Sailor_ptr(i)!=(Sailor*)NULL && world->canrecruit(this))
                        {
                        Sailor* sailor_mate = world->get_Sailor_ptr(i);
                            if ((sailor_mate->hideout)==this->hideout && this->is_hidden() && sailor_mate->is_hidden() && hideout->get_berths()>(this->size+sailor_mate->size) && ((this->health + sailor_mate->health)>80 || (this->health + sailor_mate->health)<120) )
                            {
                                bool check = start_recruiting((Merchant*)sailor_mate);
                                return check;
                            }
                            return false;
                        }
                        return false;
                    }
                }
                return false;
            }
        case 's':
            {
                bool v= update_location();
                this->insideTime=0;
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
                this->insideTime=0;
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
                this->insideTime=0;
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
                this->insideTime=0;
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
                this->insideTime=0;
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
                this->update_location();
                this->insideTime=0;
                bool hidden=false;
                   hidden=  this->is_hidden();
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

void Merchant::show_status()
{
    char merchantState=this->state;
    cout<<"Merchant status: "<<this->display_code<<" with ID "<<get_id()<<" at location "<<this->get_location()<<" ";
    switch(merchantState)
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
        case 'h':cout<<"is going to hide at Dock "<<hideout->get_id()<<endl;
            break;
        case 'r':
            {
                cout<<"is recruiting a merchant with M"<<this->mate->id_num<<"."<<endl;
                break;
            }
    }
    
}

