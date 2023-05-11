#include<iostream>

#ifndef datatypes_h
#define datatypes_h

#define N_OF_WORDS_IN_RANDOM_NAME 3     //Best from 2 to 4
#define VIETNAMESE_NAME true            //Random Vietnamese names (maybe)

using namespace std;

class DOB{
    public:
    int DD,MM,YYYY;

    public:
    DOB(int d=0, int m=0, int y=0);
    void setDOB(int d, int m, int y);
    static bool check(int d, int m, int y);
    string getDDMMYYYY();
};

class Name{

    template<class Student_Type>
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
    static string _beforeBar(string s);
    static string _afterBar(string s);
    static string _nextWord(string s);
    static string _theRest(string s);

    static string iC();         
    static string vV();         
    static string fC();         
    static string rand_name();  
};

#endif