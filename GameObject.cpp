#include "GameObject.h"


GameObject::GameObject(char in_code, int in_id)
{
    display_code=in_code;
    id_num=in_id;
    location=CartPoint(0,0);
    cout<<"GameObject default constructed"<<endl;
    
}

GameObject::GameObject(char in_code, int in_id, CartPoint in_loc)
{
    display_code=in_code;
    id_num=in_id;
    this->location=in_loc; 
    cout<<"GameObject constructed"<<endl;
}

CartPoint GameObject::get_location()
{
    return this->location;
}

int GameObject::get_id()
{
    return this-> id_num;
}

void GameObject::show_status()
{
    cout<<this->display_code<<" with ID "<<get_id()<<" at location "<<get_location()<<endl;
}

GameObject::~GameObject()
{
    cout<<"GameObject Destructed"<<endl;
}

void GameObject::drawself(char* grid)
{
    *grid=this->display_code;
    *(grid+1)= '0'+this->get_id();
}

char GameObject::get_state()
{
    return this->state;
}

