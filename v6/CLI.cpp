#include"CLI.h"

Command::Command(){
    ;
}

//List the commands and their description of one class object
template<class T>
void Command::help(T* obj){
    int i=0;
    while(obj->commands[i].name != " ")
    {
        cout<<"\t• "<<obj->commands[i].name<<"\n";
        cout<<"\t"<<obj->commands[i].description<<"\n";
        i++;
    }
}

//Load the names and description for the commands list, the final element must have name " "
void Command::load_command(Command*& commands, string* name, string* description){
    int i=0;
    while(name[i] != " "){
        commands[i].name=name[i];
        commands[i].description=description[i];
        i++;
    }
    commands[i].name=" ";
    commands[i].description=" ";
}