#include<iostream>
#include"datatypes.h"

#ifndef CLI_h
#define CLI_h

using namespace std;

class Command{
    public:
    string name;
    string description;
    
    Command();

    template<class T>
    static void help(T* obj);
    static void load_command(Command*& commands, string* name=NULL, string* description=NULL);
};

#endif