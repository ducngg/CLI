#include"university.h"

Student::Student(string first, string remain, int DOB_day, int DOB_month, int DOB_year, string schoolName, string courseName, int nSem){
    __name=new Name(first,remain);
    __dob.setDOB(DOB_day,DOB_month,DOB_year);
    __schoolName=schoolName;
    __courseName=courseName;
    __nSem=nSem;
}

Student::~Student(){
    delete __name;
    for(int i=0;i<__nSem;i++)
    {
        if(__sem[i]) delete __sem[i];
    }
    delete[] __sem;
}

string Student::fullname(){
    return __name->full();
}

float Student::gpa(){
    float sum=0;
    for(int i=0;i<__nSem;i++)
    {
        sum+=__sem[i]->score;
    }
    return sum/__nSem;
}

template<class Student_Type> List<Student_Type>::List(string name){
    count=0;
    capacity=100;
    __multiplier=2;
    __name=name;

    commands=new Command[100];
    string _command_name[100]={
        "help",
        "demo",
        "find",
        "forget",
        "insert",
        "info",
        "quit",
        "remove",
        "random",
        "show",
        "top",
        //More commands here
        " ",
    };
    string _command_description[100]={
        "Show this helper",
        "Demo the some of the commands below, try it!\n\t\tdemo",
        "Find and show all students contains that name from the list\n\t\tfind duc",
        "Forget portion of the list\n\t\tforgot 4 15",
        "Insert to the list, seperate the parameters by | or , or /\n\t\tinsert duc nguyen phan tri, 13 11 2003, HCMUT, computer science\n\t\t(This will insert name \'Duc\', remainings name \'Nguyen Phan Tri\', d.o.b. \'13/11/2003\', school name \'HCMUT\', course name \'Computer Science\',  automatically capitalized)",
        "Show inner information of this list",
        "Exit the program",
        "Remove from the list\n\t\tremove duc nguyen phan tri\n\t\t(This will remove first one on the list that has name \'Duc\' and remainings name \'Nguyen Phan Tri\', automatically capitalize)",
        "Insert some random names\n\t\trandom 88\n\t\t(This will insert 88 names)",
        "Show the list",
        "Show the top students on the list\n\t\ttop",
        //More commands here
        " ",
    };

    Command::load_command(commands,_command_name,_command_description);

    student_arr=new Student_Type*[capacity];
}

template<class Student_Type> 
List<Student_Type>::~List(){
    for(int i=0;i<count;i++) if(student_arr[i]) delete student_arr[i];
    delete[] student_arr;
}

/*
If message=true then print message of sucessfully inserted
*/
template<class Student_Type> void List<Student_Type>::insert(string first, string remains, int DOB_day, int DOB_month, int DOB_year, string schoolName, string courseName, bool message){

    //If current size reach max size
    if(count==capacity)
    {
        Student_Type** new_student_arr=new Student_Type*[capacity*__multiplier];

        for(int i=0;i<capacity;i++)
        {
            new_student_arr[i]=student_arr[i];
        }

        delete student_arr;
        student_arr=new_student_arr;

        //Update max size
        capacity*=__multiplier;
    }

    student_arr[count]=new Student_Type(
        Name::capitalize(first),
        Name::capitalize(remains),
        DOB_day,DOB_month,DOB_year,
        Name::capitalize(schoolName),
        Name::capitalize(courseName)
    );

    if(message) cout<<"\tSuccesfully inserted \""<<student_arr[count]->fullname()<<"\"\n";

    count++;
}  

//Show all names and corresponding score
template<class Student_Type> void List<Student_Type>::show(bool top){
    int numberslots=ceil(log10(count))+1;

    cout<<"\t• nSems: Number of semesters\n";
    cout<<"\t• nAsgm: Number of assignments per semester\n";
    cout<<"\t• nExam: Number of exams per semester\n";
    cout<<"\t• nTest: Number of tests per semester\n";

    float best=0;
    if(top)
    {
        for(int i=0;i<count;i++)
        {
            if(student_arr[i] && student_arr[i]->gpa()>=best)
            {
                best=student_arr[i]->gpa();
            }
        }
    }

    for(int i=1;i<numberslots;i++) cout<<"-";
    cout<<"---------- NAME -------------------------- DOB ---------- SCHOOL ------------------------------------- COURSE ---------------------- nSems - nAsgm - nExam - nTest - GPA --\n";    
    for(int i=0;i<count;i++)
    {
        //If 'top' is on then compare before show, if off then always show
        if(student_arr[i] && (!top || student_arr[i]->gpa()==best)){
            cout<<setw(numberslots)<<left<<i+1<<"| ";
            cout<<setw(40)<<left<<student_arr[i]->fullname();
            cout<<setw(15)<<left<<student_arr[i]->__dob.getDDMMYYYY();
            cout<<setw(45)<<left<<student_arr[i]->__schoolName;
            cout<<setw(30)<<left<<student_arr[i]->__courseName;
            cout<<setw(8) <<left<<student_arr[i]->__nSem;
            cout<<setw(8)<<left<<student_arr[i]->__sem[0]->__nAssignment;
            cout<<setw(8)<<left<<student_arr[i]->__sem[0]->__nExam;
            cout<<setw(8)<<left<<student_arr[i]->__sem[0]->__nTest;
            cout<<setw(8)<<left<<student_arr[i]->gpa();
            cout<<"\n";
        }
        //Display ... for the portions of the list that have been deleted, if 'top' is on then don't need to care
        else if((!student_arr[i] && student_arr[i+1]) && !top)
        {
            cout<<setw(numberslots)<<left<<""<<"| ";
            cout<<"...\n";
        }
    }
    for(int i=0;i<numberslots;i++) cout<<"-";
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

/*
Remove the first one with that name
*/
template<class Student_Type> string List<Student_Type>::remove(string full){
    for(int i=0;i<count;i++)
    {
        if(!student_arr[i]) continue;
        else if(Name::lower(full)==Name::lower(student_arr[i]->fullname()))
        {
            string res=student_arr[i]->fullname();

            delete student_arr[i];
            student_arr[i]=NULL;

            cout<<"\tSuccessfully removed \""<<res<<"\" (located at "<<i+1<<")\n";
            return res;
        }
    }
    return "";
}

//Insert n names
template<class Student_Type> void List<Student_Type>::random(int n, int n_words_in_name){
    if(n<0 || n>1000000) n=1000000;
    if(n_words_in_name<1 || n_words_in_name>7) n_words_in_name=N_OF_WORDS_IN_RANDOM_NAME;

    //Display at most 15 succesful announcements
    bool message=true;

    for(int i=0;i<n;i++)
    {
        if(i==15){
            message=false;
            cout<<"\t...\n";
        }

        string rand_remains="";
        for(int j=0;j<n_words_in_name-1;j++)
        {
            if(j) rand_remains+=" ";
            rand_remains+=(Name::rand_name());
        }

        int rday=0;
        int rmonth=0;
        int ryear=0;
        while(!DOB::check(rday,rmonth,ryear))
        {
            rday=rand()%29+1;
            rmonth=rand()%12+1;
            ryear=rand()%100+1900;
        }

        insert( Name::rand_name(),
                rand_remains,
                rday,
                rmonth,
                ryear,
                "Ho Chi Minh City University of Technology",
                "Computer Science",
                message
        );
    }
    if(!message) cout<<"\t...and "<<n-15<<" more.\n";
}

//Forget elements from a to b 
template<class Student_Type> bool List<Student_Type>::forget(int a, int b){

    if(a<0 || b>=count || a>b)
    {
        return false;
    }

    for(int i=a;i<=b && i<count;i++)
    {
        if(student_arr[i])
        {
            delete student_arr[i];
            student_arr[i]=NULL;
        }
    }

    return true;
}

//Show students include given name
template<class Student_Type> void List<Student_Type>::find(string s){
    int numberslots=ceil(log10(count))+1;
    cout<<"\t• nSems: Number of semesters\n";
    cout<<"\t• nAsgm: Number of assignments per semester\n";
    cout<<"\t• nExam: Number of exams per semester\n";
    cout<<"\t• nTest: Number of tests per semester\n";

    for(int i=1;i<numberslots;i++) cout<<"-";
    cout<<"---------- NAME -------------------------- DOB ---------- SCHOOL ------------------------------------- COURSE ---------------------- nSems - nAsgm - nExam - nTest - GPA --\n";    

    for(int i=0;i<count;i++)
    {
        if(student_arr[i] && student_arr[i]->__name->has(s)){
            cout<<setw(numberslots)<<left<<i+1<<"| ";
            cout<<setw(40)<<left<<student_arr[i]->fullname();
            cout<<setw(15)<<left<<student_arr[i]->__dob.getDDMMYYYY();
            cout<<setw(45)<<left<<student_arr[i]->__schoolName;
            cout<<setw(30)<<left<<student_arr[i]->__courseName;
            cout<<setw(8) <<left<<student_arr[i]->__nSem;
            cout<<setw(8)<<left<<student_arr[i]->__sem[0]->__nAssignment;
            cout<<setw(8)<<left<<student_arr[i]->__sem[0]->__nExam;
            cout<<setw(8)<<left<<student_arr[i]->__sem[0]->__nTest;
            cout<<setw(8)<<left<<student_arr[i]->gpa();

            cout<<"\n";
        }
    }
    for(int i=0;i<numberslots;i++) cout<<"-";
    cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

//Inner information
template<class Student_Type> void List<Student_Type>::info(){
    cout<<"\t• Array located at: "<<student_arr<<"\n";
    cout<<"\t• Name: "<<__name<<"\n";
    cout<<"\t• Multiplier: "<<__multiplier<<"\n";
    cout<<"\t• Capacity:   "<<capacity<<"\n";
    cout<<"\t• Count   :   "<<count<<"\n";
}

//Command line interface for using list functions
template<class Student_Type> void List<Student_Type>::CLI(string pre){
    string INPUT="";
    Command::help(this);
    pre+="/"+__name;
    while(exec(INPUT) != -1)
    {   
        cout<<"["<<pre<<"]> ";
        getline(cin,INPUT);
    }
}

/*
Return 1+:  Success
Return 0:   Unsuccess
Return -1:  Quit
*/
template<class Student_Type> int List<Student_Type>::exec(string statement){
    
    statement=Name::remove_extra_space(statement);

    //Check command name
    string input_cmd=Name::_nextWord(statement);
    string params=Name::_theRest(statement);

    int i=0;
    string cmd="_none_";

    while(commands[i].name != " ")
    {
        if(commands[i].name == input_cmd)
        {
            cmd=input_cmd;
            break;
        }
        i++;
    }
    if(cmd=="_none_") return 0;

    //Execute command based on parameters
    
    if(cmd=="quit")
        return -1;
    else if(cmd=="demo")
    {
        demo();
    }
    else if(cmd=="help")
        Command::help(this);
    else if(cmd=="show")
        show();
    else if(cmd=="top")
        show(true);
    else if(cmd=="remove")
    {
        string name_removed=remove(Name::remove_extra_space(params));
        if(name_removed=="")
        {
            cout<<"\tList doesn't have that name\n";
            return 0;
        }
        else cout<<"\tSuccessfully removed \""<<name_removed<<"\"\n";
    }
    else if(cmd=="insert")
    {
        string param1=Name::_beforeBar(params);
        string firstName=Name::_nextWord(param1);
        string remainName=Name::_theRest(param1);

        params=Name::_afterBar(params);

        string param2=Name::remove_extra_space(Name::_beforeBar(params));              
        int day=  stoi(Name::_nextWord(param2));
        param2=Name::_theRest(param2);                                         
        int month=stoi(Name::_nextWord(param2));
        param2=Name::_theRest(param2);                                          
        int year= stoi(Name::_nextWord(param2));    

        if(!DOB::check(day,month,year))
        {
            cout<<"\t!! Invalid date !!\n";
            return 0;
        }

        params= Name::_afterBar(params);

        string schoolName=Name::_beforeBar(params);

        params= Name::_afterBar(params);

        string courseName=params;

        insert( Name::capitalize(firstName),
                Name::capitalize(remainName),
                day, month, year,
                Name::capitalize(schoolName),
                Name::capitalize(courseName)
        );
    }
    else if(cmd=="info")
    {
        info();
    }
    else if(cmd=="random")
    {
        random(stoi(params));
    }
    else if(cmd=="forget")
    {
        int start=stoi(Name::_nextWord(params));
        int end=  stoi(Name::_theRest(params));

        if(! forget(start-1,end-1))
        {
            cout<<"\tInvalid range input, expected ["<<(count==0?"/":"1")<<","<<(count==0?"/":to_string(count))<<"]\n";
            return 0;
        }
        else cout<<"\tSuccessfully forgot ["<<start<<","<<end<<"]\n";
    }
    else if(cmd=="find")
    {
        find(Name::capitalize(params));
    }
    else
    {
        cout<<"\t!! No command, type \'help\' to show commands !!\n";
        return 0;
    }

    return 1;
}

//Demo some of the functionalities
template<class Student_Type> void List<Student_Type>::demo(){
    string statements[100]={
        "insert Duc Nguyen Phan Tri, 13 11 2003, Ho Chi Minh City University of Technology, Computer Science",
        "insert   duc ng  phan   tri |  13    11 2002      |    ho   chi   minh  City    university of  technology,    computer  Science",
        "show",
        "random 5",
        "random  20",
        "show",
        "forget 5 20",
        "show",
        "info",
        "find nguyen",
        "remove duc nguyen phan tri",
        "find   nguyen",
        "show",
        "top",
        //More statements here
        " "
    };
    int i=0;
    while(statements[i] != " ")
    {
        cout<<"["<<__name<<"]> "<<statements[i]<<"\n";
        exec(statements[i]);
        i++;
    }

}

UniversityStudent::UniversityStudent(string first, string remain, int DOB_day, int DOB_month, int DOB_year, string schoolName, string courseName)
        :Student(first,remain,DOB_day,DOB_month,DOB_year,schoolName,courseName,N_UNI_SEM){
    __sem=new Semester*[N_UNI_SEM];

    for(int i=0;i<N_UNI_SEM;i++)
    {
        float rand_point=float(rand()%500+501)/100;
        __sem[i]=new Semester(
            UNI_SEM_ASSIGNMENT,
            UNI_SEM_EXAM,
            UNI_SEM_TEST,
            rand_point
        );
    }
}

CollegeStudent::CollegeStudent(string first, string remain, int DOB_day, int DOB_month, int DOB_year, string schoolName, string courseName)
        :Student(first,remain,DOB_day,DOB_month,DOB_year,schoolName,courseName,N_COL_SEM){
    __sem=new Semester*[N_COL_SEM];

    for(int i=0;i<N_COL_SEM;i++)
    {
        float rand_point=float(rand()%500+501)/100;
        __sem[i]=new Semester(
            COL_SEM_ASSIGNMENT,
            COL_SEM_EXAM,
            COL_SEM_TEST,
            rand_point
        );
    }
}

Semester::Semester(int __A, int __T, int __E, float __S){
    __nAssignment=__A;
    __nTest=__T;
    __nExam=__E;

    score=__S;
}

University::University(string name, int n_uni_class, int n_col_class){
    this->n_uni_class=n_uni_class;
    this->n_col_class=n_col_class;
    this->__name=name;

    CS21_UNI=new List<UniversityStudent>*[n_uni_class];
    CS21_COL=new List<CollegeStudent>*[n_col_class];

    for(int i=0;i<n_uni_class;i++)
    {
        CS21_UNI[i]=new List<UniversityStudent>("UNI21KHM"+to_string(i+1));
    }
    for(int i=0;i<n_col_class;i++)
    {
        CS21_COL[i]=new List<CollegeStudent>("COL21KHM"+to_string(i+1));
    }

    commands=new Command[100];
    string _command_name[100]={
        "help",
        "quit",
        "goto",
        "info",
        //More commands here
        " ",
    };
    string _command_description[100]={
        "Show this helper",
        "Exit the program",
        "Go to desired class\n\t\tgoto uni 1\n\t\t(This will go to CLI of class UNI21KHM1)\n\t\tgoto col 3\n\t\t(This will go to CLI of class COL21KHM3)",
        "Show inner information of this university",
        //More commands here
        " ",
    };

    Command::load_command(commands,_command_name,_command_description);
}

University::~University(){
    
    for(int i=0;i<n_uni_class;i++)
    {
        if(CS21_UNI[i]) delete CS21_UNI[i];
    }
    for(int i=0;i<n_col_class;i++)
    {
        if(CS21_COL[i]) delete CS21_COL[i];
    }
    delete[] CS21_UNI;
    delete[] CS21_COL;
}

//Inner information
void University::info(){
    cout<<"\t• Name: "<<__name<<"\n";
    cout<<"\t• Number of university classes: "<<n_uni_class<<"\n";
    cout<<"\t• Number of college classes:    "<<n_col_class<<"\n";
}

//Command line interface for using university functions
void University::CLI(string pre){
    string INPUT="";
    int res=0;
    Command::help(this);
    pre+="/"+__name;

    while(true)
    {   
        cout<<"["<<pre<<"]> ";
        getline(cin,INPUT);
        res=exec(INPUT);

        //Quit
        if(res==-1) break;

        if(res>UNI_THRESHOLD && res<COL_THRESHOLD)
        {
            res-=UNI_THRESHOLD;
            if(res>=1 && res<=n_uni_class)
            {
                CS21_UNI[res-1]->CLI(pre);
            }
            else cout<<"\t!! Invalid input university class number, expected ["<<1<<","<<n_uni_class<<"] !!\n";
        }
        if(res>COL_THRESHOLD)
        {
            res-=COL_THRESHOLD;
            if(res>=1 && res<=n_col_class)
            {
                CS21_COL[res-1]->CLI(pre);
            }
            else cout<<"\t!! Invalid input college class number, expected ["<<1<<","<<n_col_class<<"] !!\n";
        }
    }
}

/*
Return 1+:  Success, the return value will be the chosen class + relative threshold
Return 0:   Unsuccess
Return -1:  Quit
*/
int University::exec(string statement){
    
    statement=Name::remove_extra_space(statement);

    //Check command name
    string input_cmd=Name::_nextWord(statement);
    string params=Name::_theRest(statement);

    int i=0;
    string cmd="_none_";

    while(commands[i].name != " ")
    {
        if(commands[i].name == input_cmd)
        {
            cmd=input_cmd;
            break;
        }
        i++;
    }
    if(cmd=="_none_") return 0;

    //Execute command based on parameters    
    if(cmd=="quit")
        return -1;
    else if(cmd=="help")
        Command::help(this);
    else if(cmd=="info")
    {
        info();
    }
    else if(cmd=="goto")
    {
        string param1=Name::_nextWord(params);
        string param2=Name::_theRest(params);

        if(param1=="uni" || param1=="university")
            return stoi(param2)+UNI_THRESHOLD;
        else if(param1=="col" || param1=="college")
            return stoi(param2)+COL_THRESHOLD;
        else return 0;
    }
    else
    {
        cout<<"\t!! No command, type \'help\' to show commands !!\n";
        return 0;
    }

    return 1;
}