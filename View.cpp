#include "View.h"

View::View()
{
    this->size=11;
    this->scale=2;
    this->origin=CartPoint(0,0);
}

bool View::get_subscripts(int &ix, int &iy, CartPoint location)
{
    ix=((location.x-this->origin.x)/scale);
    iy=((location.y-this->origin.y)/scale);
    if(ix > size || ix < 0 || iy > size || iy<0)
    {
        cout<<"An object is outside the display"<<endl;
        return false;
    }
    else return true;
    
}

void View::plot(GameObject* ptr)
{
    CartPoint loc = ptr->get_location();
    int ix, iy;
    if(get_subscripts(ix, iy, loc) && grid[ix][iy][0]=='.')
    {
        ptr->drawself(grid[ix][iy]);
    }
    else if(get_subscripts(ix, iy, loc))
    {
        grid[ix][iy][0]='*';
        grid[ix][iy][1]=' ';
    }
}

void View::clear()
{
    for(int i =0; i<view_maxsize; i++)
    {
        for (int j = 0; j<view_maxsize; j++)
        {
            grid[i][j][0]='.';
            grid[i][j][1]=' ';
        }
    }
}

void View::draw()
{
    int coord=size-1;
   for(int j =size-1; j>=0; j--)
    {
       if(coord%2==0)
       {
           cout<<coord*scale;
           if(coord*scale<10)
               cout<<" ";
       }
       else cout<<"  ";
        for (int i = 0; i<size; i++)
        {
            cout<<grid[i][j][0];
            cout<<grid[i][j][1];
        }
       cout<<endl;
       coord--;
    }
    int lowercoord=0;
    for(int i =size; i>0; i--)
    {
       if(lowercoord%2==0)
           cout<<" "<<lowercoord*scale;
       else cout<<"  ";
        lowercoord++;
    }
    cout<<endl;
}


View::~View()
{
    //cout<<"View destructed"<<endl;
}