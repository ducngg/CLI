#include"university.cpp"

#define NUMBER_OF_UNI_CLASSES 10
#define NUMBER_OF_COL_CLASSES 5

int main(){

    University MyUni(
        "HCMUT",
        NUMBER_OF_UNI_CLASSES,
        NUMBER_OF_COL_CLASSES
    );

    MyUni.CLI();

    return 0;
}