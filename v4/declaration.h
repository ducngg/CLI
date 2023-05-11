#include<iostream>
#include<iomanip>
#include<math.h>

#ifndef declaration_h
#define declaration_h

#define N_OF_WORDS_IN_RANDOM_NAME 3     //Best from 2 to 4
#define VIETNAMESE_NAME true            //Random Vietnamese names (maybe)

using namespace std;

class Name{
    friend class List;
    friend class Student;

    string first;
    string remain;

    public:
    Name(string f="", string r="");
    string full();
    bool has(string s);                         //Find by capitalized both sides full name and capitalized input

    //////// Static functions ////////

    static string remove_extra_space(string s);                         //Remove extra spaces, also cut the score value at the end
    static string lower(string s);                                      //Simplify the name to just lowercase
    static string capitalize(string s, bool both_sides=false);          //Capitalize first character of each word, use both_sides for capitalize both first and last characters
    static float  value(string s);                                      //Take the score value at the end of the input value string

    static string iC();         
    static string vV();         
    static string fC();         
    static string rand_name();  
};

class Student{
    friend class List;

    Name* __name;
    float __score;

    public:
    Student(string first="", string remain="", float score=0.0F);
    ~Student();

    string fullname();
    float  score();
};

class List{

    Student** student_arr;   //Student array

    int count;              //Current size
    int capacity;           //Max size (can be automatically updated if current size reach this)
    int __multiplier;       //For updating max size

    public:
    List();
    ~List();

    
    void insert(string first="", string remains="", float score=0.0F, bool message=true);
    void show();                                        
    void show_top();                                    
    string remove(string full="");                      
    void demo(int n=10, int n_words_in_name=N_OF_WORDS_IN_RANDOM_NAME);        
    void forgot(int a, int b);                                                  
    void show_average();                             
    void find(string s="xxxxxxxx");                   
    void info();    
                                 
    static void CLI_help();
    bool CLI();                                         
};

class University{
    string __name;
    List class_CC21KHM1;

    public:
    University(string name="");
    void CLI();
};

#endif