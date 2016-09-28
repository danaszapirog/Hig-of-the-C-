#include <iostream>
using namespace std;

#include "Port.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "GameObject.h"
#include "math.h"
#include "Dock.h"
#include "Sailor.h"
#include "Model.h"
#include "GameCommand.h"
#include "InvalidInput.h"
#include "View.h"

int main()
{
    cout<<"EC327: Introduction to Software Engineering"<<endl;
    cout<<"Fall 2015"<<endl;
    cout<<"Programming Assignment 3"<<endl;
    Model* model = new Model();
	model->show_status();
    char command;
    View view =View();
    do
    {
        model->display(view);
        cout<<"Enter command: ";
            cin>>command;
            try{
                switch (command)
                {
                    case 's':
                        {
                            do_sail_command(model);
                            break;
                        }
                    case 'p': 
                        {
                            do_port_command(model);
                            break;
                        }
                    case 'a': 
                        {
                            do_anchor_command(model);
                            break;
                        }
                    case 'd': 
                        {
                            do_dock_command(model);
                            break;
                        }
                    case 'h': 
                        {
                            do_hide_command(model);
                            break;
                        }
                    case 'g': 
                        {
                            do_go_command(model);
                            model->show_status();
                            break;
                        }
                    case 'r': 
                        {
                            do_run_command(model);
                            model->show_status();
                            break;
                        }
                    case 'n':
                        {
                            handle_new_command(model);
                           // model->show_status();
                            break;
                        }
                    case 'u':
                        {
                            plUnder(model);
                            break;
                        }
                    case 'S':
                        {
                            savecommand(model);
                            break;
                        }
                    case 'R':
                        {
                            restorecommand(model);
                            break;
                        }
                }
            }
            catch(InvalidInput& except){
                cout<<"Invalid input - "<< except.msg_ptr<<endl;
            }
    }while(command!='q');
    cout<<"terminating Program"<<endl;
    model->display(view);
    cout<<"View destructed"<<endl;
    model->~Model();

return 0;
    
};