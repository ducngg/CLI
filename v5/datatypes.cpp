#include"datatypes.h"

#define is ==
#define is_equal_to ==

#define jan 1   
#define feb 2
#define mar 3
#define apr 4
#define may 5
#define jun 6
#define jul 7
#define aug 8
#define sep 9
#define oct 10
#define nov 11
#define dec 12

DOB::DOB(int d, int m, int y){
    setDOB(d,m,y);
}

//check if valid date
bool DOB::check(int d, int m, int y){
    bool leap=(y%4 is_equal_to 0)?
    /*a multiple of 4*/     (y%100 is_equal_to 0)?
    /*a multiple of 100*/       (y%400 is_equal_to 0)?
    /*a multiple of 400*/                       true:false      /*a multiple of 100 but not a multiple of 400*/
                                                    :true       /*a multiple of 4 but not a multiple of 100*/
                                                        :false; /*not a multiple of 4*/

    if(!(m>=jan and m<=dec)) return false;
    if(!(d>=1 and d<=31)) return false;
    if(d is_equal_to 31 and (m is apr or m is jun or m is sep or m is nov)) return false;
    if(d is_equal_to 30 and m is feb) return false;
    if(d is_equal_to 29 and m is feb and not leap) return false;

    return true;
}


//set DOB
void DOB::setDOB(int d, int m, int y){
    if(!DOB::check(d,m,y))
    {
        DD=0;
        MM=0;
        YYYY=0;
        return;
    }

    DD=d;
    MM=m;
    YYYY=y;
}

//return "DD/MM/YYYY"
string DOB::getDDMMYYYY(){
    string d=DD?to_string(DD):"NA";
    string m=MM?to_string(MM):"NA";
    string y=to_string(YYYY);
    return d+"/"+m+"/"+y;
}

//////////////
//////////////

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

//Remove extra spaces
string Name::remove_extra_space(string s){
    string res="";
    for(int i=0;i<s.size();){
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

//Before | or , or /
string Name::_beforeBar(string s){
    int barindex=0;
    for(;barindex<s.size();barindex++)
    {
        if(s[barindex]=='|' || s[barindex]=='/' || s[barindex]==',')
        return s.substr(0,barindex);
    }
    return s;
}

//After | or , or /
string Name::_afterBar(string s){
    int barindex=0;
    for(;barindex<s.size();barindex++)
    {
        if(s[barindex]=='|' || s[barindex]=='/' || s[barindex]==',')
        return s.substr(barindex+1);
    }
    return s;
}

//Next word
string Name::_nextWord(string s){
    return s.substr(0,s.find(' '));
}
//The rest part except first word
string Name::_theRest(string s){
    return s.substr(s.find(' ')+1);
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
