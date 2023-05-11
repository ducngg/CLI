#include<iostream>
#include<iomanip>
#include<math.h>
#include"datatypes.cpp"
#include"CLI.cpp"

#ifndef university_h
#define university_h

#define N_UNI_SEM 8
#define N_COL_SEM 4

#define UNI_SEM_ASSIGNMENT 3
#define UNI_SEM_TEST 2
#define UNI_SEM_EXAM 1
#define COL_SEM_ASSIGNMENT 1
#define COL_SEM_TEST 1
#define COL_SEM_EXAM 1

#define UNI_THRESHOLD 10000 //See University::exec() for more info
#define COL_THRESHOLD 20000 //See University::exec() for more info

template<class Student_Type> class List;
class Semester;

using namespace std;

class Student{
    template<class Student_Type>
    friend class List;

    protected:
    Name* __name;
    DOB   __dob;

    string __schoolName;
    string __courseName;

    Semester** __sem;
    int __nSem;

    public:
    Student(string first="", string remain="", int DOB_day=0, int DOB_month=0, int DOB_year=0, string schoolName="", string courseName="", int nSem=0);
    ~Student();

    string fullname();
    float gpa();
};

class UniversityStudent : public Student{
    public:
    UniversityStudent(string first="", string remain="", int DOB_day=0, int DOB_month=0, int DOB_year=0, string schoolName="", string courseName="");
};
class CollegeStudent : public Student{
    public:
    CollegeStudent(string first="", string remain="", int DOB_day=0, int DOB_month=0, int DOB_year=0, string schoolName="", string courseName="");
};

class Semester{
    friend class Student;
    template<class Student_Type>
    friend class List;

    protected:
    int __nAssignment;
    int __nTest;
    int __nExam;

    float score;

    public:
    Semester(int __A=0, int __T=0, int __E=0, float score=0.0F);
};

template<class Student_Type>
class List{
    friend class Command;
    private:
    string __name;
    Student_Type** student_arr;   //Student array

    int count;              //Current size
    int capacity;           //Max size (can be automatically updated if current size reach this)
    int __multiplier;       //For updating max size

    Command* commands;

    public:
    List(string name);
    ~List();
    
    void insert(string first="", string remains="", int DOB_day=0, int DOB_month=0, int DOB_year=0, string schoolName="", string courseName="", bool message=true);
    void show(bool top=false);
    string remove(string full="");
    void random(int n=10, int n_words_in_name=N_OF_WORDS_IN_RANDOM_NAME);        
    bool forget(int a, int b);   
    void demo();
    void find(string s="_none_");                   
    void info();    
                                 
    void CLI(string pre=".");      
    int exec(string statement);                                   
};

class University{
    friend class Command;

    private:

    protected:
    string __name;
    List<UniversityStudent>** CS21_UNI;
    List<CollegeStudent>** CS21_COL;

    int n_uni_class;
    int n_col_class;

    Command* commands;

    public:
    University(string name="", int n_uni_class=1, int n_col_class=1);
    ~University();

    void info();

    void CLI(string pre=".");
    int exec(string statement);
};

#endif