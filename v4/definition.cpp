#include"declaration.h"

Name::Name(string f, string r){
    first=f;
    remain=r;
}
string Name::full(){
    return first+" "+remain;
}
//Find by capitalized both sides full name and capitalized input
bool Name::has(string s){
    //     string.find(substring) != npos
    return capitalize(full(),true).find(capitalize(s,true))!=string::npos;
}

//////// Static functions ////////

//Remove extra spaces, also cut the score value at the end
string Name::remove_extra_space(string s){
    string res="";
    for(int i=0;i<s.size();){
        //If the string has got to the score value part, stop and return
        if(s[i]=='.' || (s[i]>='0' && s[i]<='9')) return res;

        if(s[i]==' '){
            if(i==0 || i==s.size()-1){
                i++;
                continue;
            }
            while(s[i+1]==' ') i++;
        }
        res+=s[i++];
    }
    return res;
}

//Simplify the name to just lowercase
string Name::lower(string s){
    string low=remove_extra_space(s);
    for(int i=0;i<low.size();i++)
        if(low[i]>='A' && low[i]<='Z')
            low[i]+=32;
    
    return low;
}

//Capitalize first character of each word, use both_sides=true for capitalize both first and last characters
string Name::capitalize(string s, bool both_sides){
    string cap=remove_extra_space(s);
    bool next_cap=true;

    for(int i=0;i<cap.size();i++)
    {
        if(next_cap)
        {
            if(cap[i]>='a' && cap[i]<='z') cap[i]-=32;
            next_cap=false;
        }
        if(cap[i]==' ')
        {
            next_cap=true;
        }
    }
    if(both_sides)
    {   
        next_cap=true;
        for(int i=cap.size()-1;i>=0;i--)
        {
            if(next_cap)
            {
                if(cap[i]>='a' && cap[i]<='z') cap[i]-=32;
                next_cap=false;
            }
            if(cap[i]==' ')
            {
                next_cap=true;
            }
        }
    }
    
    return cap;
}

//Take the score value at the end of the input value string
float Name::value(string s){
    int size=s.size();
    for(int i=0;i<s.size();i++){
        if(s[i]=='.' || s[i]=='-' || (s[i]>='0' && s[i]<='9')) s=s.substr(i);
    }

    //No value
    if(s.size()==size) return -1;
    return stof(s);
}

//random initial consonant
string Name::iC(){
    string s[42]={"b","bv","c","ch","d","dm","f","g","gh","h","","j","jh","k","kh","l","lr","m","mg","n","ng","nz","p","ph","q","r","rh","s","sh","sq","t","th","tz","tch","tg","v","vh","wtr","x","xh","z","zh"};
    string v[22]={"b","ch","d","g","gi","h","","kh","l","m","n","ng","nh","ph","qu","r","s","t","th","tr","v","x",}; //đ is not included

    if(VIETNAMESE_NAME) return v[rand()%22];
    return s[rand()%42];
}
//random vowel consonant
string Name::vV(){
    string s[17]={"a","ya","wa","wya","e","ye","we","eo","yeo","weo","i","wi","o","yo","wo","u","yu"};
    string v[12]={"a","oa","ua","e","ie","oe","ue","uye","i","uy","o","u"};

    if(VIETNAMESE_NAME) return v[rand()%12];
    return s[rand()%17];
}
//random final consonant
string Name::fC(){
    string s[15]={"c","ch","g","","k","l","m","n","ng","p","ph","r","s","t","th"};
    string v[12]={"n","t","ng","c","nh","ch","m","p","","o","i","u"};

    if(VIETNAMESE_NAME) return v[rand()%12];
    return s[rand()%15];
}
//iC+vV+fC
string Name::rand_name(){
    return iC()+vV()+fC();
}

Student::Student(string first, string remain, float score){
    __name=new Name(first,remain);
    __score=score;
}
Student::~Student(){
    delete __name;
}
string Student::fullname(){
    return __name->full();
}
float Student::score(){
    return __score;
}



List::List(){
    count=0;
    capacity=100;
    __multiplier=2;

    student_arr=new Student*[capacity];
} 
List::~List(){
    for(int i=0;i<count;i++) if(student_arr[i]) delete student_arr[i];
    delete[] student_arr;
}

/*
Example: 
>> insert Duc Nguyen Phan Tri 9.0

first="Duc", remains="Nguyen Phan Tri", score=9.0F
If message=true then print message of sucessfully inserted
*/
void List::insert(string first, string remains, float score, bool message){

    //If current size reach max size
    if(count==capacity)
    {
        Student** new_student_arr=new Student*[capacity*__multiplier];

        for(int i=0;i<capacity;i++)
        {
            new_student_arr[i]=student_arr[i];
        }

        delete student_arr;
        student_arr=new_student_arr;

        //Update max size
        capacity*=__multiplier;
    }

    student_arr[count]=new Student(Name::capitalize(first),Name::capitalize(remains),score);

    if(message) cout<<"\tSuccesfully inserted \""<<student_arr[count]->fullname()<<"\", score: "<<student_arr[count]->score()<<"\n";

    count++;
}  

//Show all names and corresponding score
void List::show(){
    int numberslots=ceil(log10(count))+1;
    cout<<"---------- LIST --------------------------------------[SCORE]----------\n";    
    for(int i=0;i<count;i++)
    {
        if(student_arr[i]){
            cout<<setw(numberslots)<<left<<i+1<<"| ";
            cout<<setw(50)<<left<<student_arr[i]->fullname();
            cout<<student_arr[i]->score()<<"\n";
        }
        //Display ... for the portions of the list that have been deleted
        else if(!student_arr[i] && student_arr[i+1])
        {
            cout<<setw(numberslots)<<left<<""<<"| ";
            cout<<"...\n";
        }
    }
    cout<<"-----------------------------------------------------------------------\n";
}

//Show all names with highest score
void List::show_top(){
    int numberslots=ceil(log10(count))+1;
    float top=0;
    for(int i=0;i<=count;i++)
    {
        if(student_arr[i]){
            if(student_arr[i]->score()>=top)
            {
                top=student_arr[i]->score();
            }
        }
    }
    cout<<"------ TOP LIST --------------------------------------[SCORE]----------\n";    
    for(int i=0;i<=count;i++)
    {
        if(student_arr[i] && student_arr[i]->score()==top){
            cout<<setw(numberslots)<<left<<i+1<<"| ";
            cout<<setw(50)<<left<<student_arr[i]->fullname();
            cout<<student_arr[i]->score()<<"\n";
        }
    }
    cout<<"-----------------------------------------------------------------------\n";
}

/*
Remove the first one with that name
*/
string List::remove(string full){
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

    cout<<"\tList doesn't have that name\n";
    return "";
}

//Insert n names with random score
void List::demo(int n, int n_words_in_name){
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
        for(int i=0;i<n_words_in_name-1;i++)
        {
            if(i) rand_remains+=" ";
            rand_remains+=(Name::rand_name());
        }
        insert( Name::rand_name(),
                rand_remains,
                rand()%10+float(rand()%10)/10+float(rand()%11)/100,
                message
        );
    }
    if(!message) cout<<"\t...and "<<n-15<<" more.\n";
}

void List::forgot(int a, int b){

    if(a<0 || b>=count || a>b)
    {
        cout<<"\tInvalid range input, expected ["<<(count==0?"/":"1")<<","<<(count==0?"/":to_string(count))<<"]\n";
        return;
    }

    for(int i=a;i<=b && i<count;i++)
    {
        if(student_arr[i])
        {
            delete student_arr[i];
            student_arr[i]=NULL;
        }
    }

    cout<<"\tSuccessfully forgot ["<<a+1<<","<<b+1<<"]\n";
}

void List::show_average(){
    float sum=0;
    int count_current=0;
    for (int i=0;i<=count;i++)
    {
        if(student_arr[i]){
                count_current++;
                sum+=student_arr[i]->score();
        }
    }
    cout<<"------ AVERAGE ---------------------------------------[SCORE]----------\n";    
            cout<<setw(5)<<left<<"Avg.";
            cout<<setw(50)<<left<<" ";
            cout<<sum/count_current<<"\n";
    cout<<"-----------------------------------------------------------------------\n";
}

//Show students include given name
void List::find(string s){
    int numberslots=ceil(log10(count))+1;
    cout<<"---------- LIST --------------------------------------[SCORE]----------\n";    
    for(int i=0;i<count;i++)
    {
        if(student_arr[i] && student_arr[i]->__name->has(s)){
            cout<<setw(numberslots)<<left<<i+1<<"| ";
            cout<<setw(50)<<left<<student_arr[i]->fullname();
            cout<<student_arr[i]->score()<<"\n";
        }
    }
    cout<<"-----------------------------------------------------------------------\n";
}

void List::info(){
    cout<<"\t. Array located at: "<<student_arr<<"\n";
    cout<<"\t. Multiplier: "<<__multiplier<<"\n";
    cout<<"\t. Capacity:   "<<capacity<<"\n";
    cout<<"\t. Count   :   "<<count<<"\n";
}

void List::CLI_help(){
    string s1="\tCommands:\n";
    string sh="\t-- \'help\': Show this helper\n";
    string sf="\t-- \'find\': Find and show all students contains that name from the list\n\t\tExample: find duc\n";
    string si="\t-- \'insert\': Insert to the list\n\t\tExample: insert duc nguyen phan tri 8.77\n\t\t(This will insert name \'Duc\' and insert remainings name \'Nguyen Phan Tri\' and corresponding score \'8.77\', automatically capitalize)\n";
    string si2="\t-- \'info\': Show inner information of this list\n";
    string sq="\t-- \'quit\': Exit the program\n";
    string sr="\t-- \'remove\': Remove from the list\n\t\tExample: remove duc nguyen phan tri \n\t\t(This will remove first one on the list that has name \'Duc\' and remainings name \'Nguyen Phan Tri\', automatically capitalize)\n";
    string sr2="\t-- \'random\': Insert some names with random scores\n\t\tExample: random 88 \n\t\t(This will insert 88 names with random values of score in [0,10])\n";
    string ss="\t-- \'show\': Show the list\n";
    string st="\t-- \'top\': Show the list of top score students\n";
    cout<<s1<<sh<<sf<<si<<si2<<sq<<sr<<sr2<<ss<<st;
}

//Command line interface for using list functions
bool List::CLI(){

    string INPUT;

    //Command name
    cout<<">> "; cin>>INPUT;
    
    if(INPUT=="quit" || INPUT=="exit")
        return false;
    else if(INPUT=="help")
        CLI_help();
    else if(INPUT=="show" || INPUT=="display")
        show();
    else if(INPUT=="remove" || INPUT=="delete")
    {
        //Parameter of remove
        string INPUT2;
            //cout<<"Input name to remove\n";
            //cout<<">>> "; 
        cin.ignore(); getline(cin,INPUT2); 
        remove(Name::remove_extra_space(INPUT2));
    }
    else if(INPUT=="insert")
    {
        //Parameters of insert
        string INPUT_F, INPUT_R;
            //cout<<"Input first name to insert\n";
            //cout<<">>> "; 
        cin>>INPUT_F;
            //cout<<"Input remainings of the name\n";
            //cout<<">>> "; 
        cin.ignore(); getline(cin,INPUT_R);

        if(Name::value(INPUT_R)<0 || Name::value(INPUT_R)>10)
        {
            cout<<"\tInvalid or missing score input, must be in [0,10]\n";
            return true;
        }

        insert(   INPUT_F,
                    Name::remove_extra_space(INPUT_R),
                    Name::value(INPUT_R)
                );
    }
    else if(INPUT=="info")
    {
        info();
    }
    else if(INPUT=="top" || INPUT=="best")
        show_top();
    else if(INPUT=="random" || INPUT=="demo")
    {
        //Parameter of random
        string INPUT2;
        cin>>INPUT2;
        demo(stoi(INPUT2));
    }
    else if(INPUT=="average" || INPUT=="avg")
        show_average();
    else if(INPUT=="forgot" || INPUT=="forget")
    {
        //Parameters of forgot
        string INPUT2, INPUT3;
        cin>>INPUT2>>INPUT3;

        forgot(stoi(INPUT2)-1,stoi(INPUT3)-1);
    }
    else if(INPUT=="find")
    {
        //Parameter of find
        string INPUT2;
        cin>>INPUT2;
        find(Name::capitalize(INPUT2));
    }
    else
        cout<<"!! No command, type \'help\' to show commands !!\n";

    //True means not quit
    return true;
}



University::University(string name){
    __name=name;
}
//Command line interface
void University::CLI(){
    List::CLI_help();
    while(true)
    {
        if(!class_CC21KHM1.CLI()) break;
    }
}
