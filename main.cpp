#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "SA.h"
#include "PSA.h"
//#include "Pinho.h"
#include "p_pinho.h"


using namespace std;


//SA.h
int* suffixarray(char* str, int str_len);
int* LCP(int* sa, char* str, int str_len);

//PSA.h
int* prev_arr(char* str, int str_len);
int* param_suffixarray(char* str, int* prev_arr, int str_len);
int* PLCP(int* psa, char* str, int* prev_arr, int str_len);

//Pinho.h
void pinho(char* str, int str_len, int* sa, int* lcp);



int main()
{
    //"ACTAACTG$CGTACTA"
        //MAWS: AAA  ACG  GTG  TGT  CTAC  GTAA  AACTA  TACTG  TACTAA

        // TEST STRINGS
    // "stssAtssAs"
    // "QQQsAAAtQQQ" 
    // "QQQsAAAtQQQmAAAnQQQ"
    // "rtArrAnnA"
    // "oAeBefOOeOsBsrC"
    

    bool param = true;

    char str[] = "QQQsAAAtQQQmAAAnQQQ";      ///////////CHANGE THIS TO TEST OUTPUT
    int str_len = strlen(str);

    int* sa = suffixarray(str, str_len);
    int* lcp = LCP(sa, str, str_len);

    int* prev = prev_arr(str, str_len);
    int* psa = param_suffixarray(str, prev, str_len);
    int* plcp = PLCP(psa, str, prev, str_len);
    int* next = next_arr(str, str_len);
    
    //cout << str << endl;
    cout << "      ";
    for (int i = 0; i < str_len; i++) {
        cout << str[i];
        cout << " ";
    } cout << endl;


    cout << "prev: ";
    for (int i = 0; i < str_len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            cout << prev[i];
        else
            cout << str[i];
        cout << " ";
    } cout << endl;

    cout << "next: ";
    for (int i = 0; i < str_len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            cout << next[i];
        else
            cout << str[i];
        cout << " ";
    } cout << endl << endl;

    cout << "SA:   ";
    for (int i = 0; i < str_len; i++) {
        cout << sa[i] << " ";
    } cout << endl;

    cout << "LCP:  ";
    for (int i = 0; i < str_len; i++) {
        cout << lcp[i] << " ";
    } cout << endl << endl;

    cout << "PSA:  ";
    for (int i = 0; i < str_len; i++) {
        cout << psa[i] << " ";
    } cout << endl;

    cout << "PLCP: ";
    for (int i = 0; i < str_len; i++) {
        cout << plcp[i] << " ";
    } cout << endl << endl;


    if (param) {
        cout << "broken linear time PMAWs:\n\n";
        p_pinho(str, prev, next, str_len, psa, plcp);
        cout << "\n\n";
        cout << "slow but correct PMAWs:\n\n";
        p_pinho_slow(str, prev, next, str_len, psa, plcp);
    }
    else
        //pinho(str, str_len, sa, lcp);
        4;



}


