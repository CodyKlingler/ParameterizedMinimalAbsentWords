#include <iostream>
#include <string>
#include <vector>
#include <set>


//#define debug_print

using namespace std;

struct ptriple {
    int d;
    int i;
    int j;
}typedef ptriple;

struct p_tupl {
    int l;
    int r;
}typedef p_tupl;

ptriple* trip(int d, int i, int j) {
    ptriple* ret = (ptriple*)malloc(sizeof(ptriple));
    ret->d = d;
    ret->i = i;
    ret->j = j;
    return ret;
}

p_tupl* tup(int l, int r) {
    p_tupl* ret = (p_tupl*)malloc(sizeof(p_tupl));
    ret->r = r;
    ret->l = l;
    return ret;
}
void p_algo3(ptriple* tri, const char* str, int* prev, int* next, int str_len, const int* psa, set<string>& pmaws);

void p_algo2(ptriple* tri, const char* str, int* prev, int* next, int str_len, const int* sa);

void p_pinho(char* str, int* prev, int* next, int str_len, int* sa, int* lcp) {
    int len = strlen(str);

    vector<ptriple*> stck;
    set<string> pmaws;
    stck.push_back(trip(0, 0, 0));
    for (int k = 1; k <= len; k++) {
        int i = k - 1;
        while (stck.size() > 0 && lcp[k] < stck.back()->d) {
            ptriple* lcpin = stck.back();
            stck.pop_back();
            lcpin->j = k - 1;
            p_algo3(lcpin, str, prev, next, str_len, sa, pmaws);
            i = lcpin->i;
            free(lcpin);
        }
        //cout << "i:" << i << "   lcp[k]:" << lcp[k] << "   stck.d:" << (stck.size()? stck.back()->d : -99) << endl;
        if (i > 0 && lcp[k] > stck.back()->d) {
            stck.push_back(trip(lcp[k], i, 0));
        }
    }

    set<string>::iterator cur_pmaw;
    for (cur_pmaw = pmaws.begin(); cur_pmaw != pmaws.end(); cur_pmaw++) {
        cout << *cur_pmaw << endl;
    }
}

void p_algo2(ptriple* tri, const char* str, int* prev, int* next, int str_len, const int* psa) {
    int d = tri->d;
    int i = tri->i;
    int j = tri->j;

    if (d == 0)
        return;

    set<char> La;
    set<char> Ra;
    vector<p_tupl*> a;

    if (j == 9) {
        cout << "";
    }
    // used for cases where sAAAs is a MAW
    bool l_zero = false;
    bool r_zero = false;
    bool l_next_is_r = false;
    bool r_prev_is_l = false;
    for (int k = i; k <= j; k++) {
        //cout << "plcp[k]: " << plcp[k] << "  d - 1: " << d - 1 << endl;
        char l = str[psa[k] - 1];
        char r = str[psa[k] + d];

            //valid range
        if (psa[k] > 0 && psa[k] + d < str_len) {
            //print whole word
    #ifdef debug_print
            cout << '\t' << l;
            for (int f = psa[k]; f <= psa[k] + d - 1; f++) {
                cout << str[f];
            }
            cout << r <<  "    ";
    #endif

            if (psa[k] == 0)
                l = '#';
            if (l >= 'a' && l <= 'z') {
                int p = next[psa[k] - 1];
                l = -128 + p;

                if (p == d + 1)
                    l_next_is_r = true;

                // next is out of bounds of word
                if (p > d) {
                    l = -128;
                }

                if(l == -128)
                    l_zero = true;
            }

            La.insert(l);
        
            if (r >= 'a' && r <= 'z') {
                int p = prev[psa[k] + d];

                if (p == d + 1)
                    r_prev_is_l = true;

                if (p > d)              // was d+1
                    r = -128;
                else
                    r = -128 + p;

                if (r == -128)
                    r_zero = true;
            }

            Ra.insert(r);

    #ifdef debug_print
            cout << "\tla: " << (int)l << "   ra: " << (int)r << endl;
    #endif
            a.push_back(tup(l, r));
        }
    }
    /*for (int f = sa[i]; f <= sa[i] + d - 1; f++) {
        std::cout << str[f];
    }
    cout << "    l_0: " << l_zero << "   r0: " << r_zero << "  l_next_is_r: " << l_next_is_r << "r_prev_is_l: " << r_prev_is_l << endl;
    */
    if (l_zero && r_zero && !l_next_is_r && !r_prev_is_l) {
        cout << "MAW:  ";
        cout << "!";
        for (int f = psa[i]; f <= psa[i] + d - 1; f++) {
            std::cout << str[f];
        }
        cout << "!";
        cout << endl;
    }
        


    if (La.size() > 1) {
        //iterate left chars
        set<char>::iterator cur_la;
        for (cur_la = La.begin(); cur_la != La.end(); cur_la++) {
            char l = *cur_la;

            //iterate right chars
            set<char>::iterator cur_ra;
            for (cur_ra = Ra.begin(); cur_ra != Ra.end(); cur_ra++) {
                char r = *cur_ra;

#ifdef debug_print
                cout << "\tsearching for  l: " << (int)l << "   r: " << (int)r << endl;
#endif
                //check for matches in a
                char contains = 0;
                for (int n = 0; n < a.size(); n++) {
                    if (a[n]->l == l && a[n]->r == r) {
                        contains = 1;
                        break;
                    }
                }
                //MAW was found
                if (!contains) {

#ifdef debug_print
                    cout << "\tdid not have   l: " << (int)l << "   r: " << (int)r << endl;
#endif
                    char l_ch = l;
                    char r_ch = r;

                    if (l_ch != '#' && r_ch != '$' && r_ch != '\0' && l_ch != '$') {
                        cout << "MAW:  ";

                        if (l_ch < 0) {
                            l_ch += 128;
                            if (l_ch > 0)
                                l_ch = str[psa[i] + l_ch - 1];
                            else
                                l_ch = '!';
                        }
                        if (r_ch < 0) {
                            r_ch += 128;
                            if (r_ch > 0)
                                r_ch = str[psa[i] + d - r_ch];
                            else
                                r_ch = '@';
                        }

                        //whole word
                        cout << l_ch << "";
                        int sa_i = psa[i];
                        for (int f = psa[i]; f <= psa[i] + d - 1; f++) {
                            cout << str[f];
                        }
                        cout << r_ch;
                        cout << endl;
                        /*
                        cout << " \t";

                        
                        //left
                        cout << l_ch << "";
                        sa_i = sa[i];
                        for (int f = sa[i]; f <= sa[i] + d - 1; f++) {
                            cout << str[f];
                        }

                        //right
                        cout << "  \t";
                        for (int f = sa[i]; f <= sa[i] + d - 1; f++) {
                            cout << str[f];
                        }
                        cout << "" << r_ch << endl;
                        */
                    }
                }
            }
        }
    }
}


void p_pinho_slow(char* str, int* prev, int* next, int str_len, int* psa, int* plcp){
    // d is strlen
    // i is sa start index
    // j is sa end index
    int len = strlen(str);

    vector<ptriple*> stck;
    stck.push_back(trip(0, 0, 0));
    set<string> pmaws;

    for (int j = len - 1; j >= 0; j--) {
        if (plcp[j] == plcp[j - 1])
            continue;
        int d;
        for (int d = plcp[j]; d > 0; d--) {
            int i;
            for (i = j; plcp[i] >= d && i > 0; i--) {
                //cout << i << " plcp " << plcp[i] << endl;
            }
           // cout << d << " " << i << " " << j << endl;
            stck.push_back(trip(d, i, j));
        }
    }
    while (stck.size()) {
        p_algo3(stck.back(), str, prev, next, str_len, psa, pmaws);
        stck.pop_back();
    }
    set<string>::iterator cur_pmaw;
    for (cur_pmaw = pmaws.begin(); cur_pmaw != pmaws.end(); cur_pmaw++) {
        cout << *cur_pmaw << endl;
    }

}

void p_algo3(ptriple* tri, const char* str, int* prev, int* next, int str_len, const int* psa, set<string> &pmaws){
    int d = tri->d;
    int i = tri->i;
    int j = tri->j;

    if (d == 0)
        return;

    set<char> La;
    set<char> Ra;
    vector<p_tupl*> a;


    // used for cases where sAAAs is a MAW
    bool l_zero = false;
    bool r_zero = false;
    bool l_next_is_r = false;
    bool r_prev_is_l = false;
    for (int k = i; k <= j; k++) {
        char l = str[psa[k] - 1];
        char r = str[psa[k] + d];

        //valid range
        if (psa[k] > 0 && psa[k] + d < str_len) {
            //print whole word

            if (psa[k] == 0)
                l = '#';
            if (l >= 'a' && l <= 'z') {
                int p = next[psa[k] - 1];
                l = -128 + p;

                if (p == d + 1)
                    l_next_is_r = true;

                // next is out of bounds of word
                if (p > d) {
                    l = -128;
                }

                if (l == -128)
                    l_zero = true;
            }

            La.insert(l);

            if (r >= 'a' && r <= 'z') {
                int p = prev[psa[k] + d];

                if (p == d + 1)
                    r_prev_is_l = true;

                if (p > d)              // was d+1
                    r = -128;
                else
                    r = -128 + p;

                if (r == -128)
                    r_zero = true;
            }

            Ra.insert(r);
            a.push_back(tup(l, r));
        }
    }

    if (l_zero && r_zero && !l_next_is_r && !r_prev_is_l) {
        char r_ch = '!';
        char l_ch = '!';


        char* st = new char[d + 3];
        st[d + 2] = '\0';
        st[0] = l_ch;
        st[d + 1] = r_ch;
        int k = 1;
        for (int f = psa[i]; f < psa[i] + d; f++) {
            st[k] = str[f];
            k++;
        }
        
        string ss(st);
        pmaws.insert(ss);
        //cout << ss << endl;
    }

    if (La.size() > 1) {
        //iterate left chars
        set<char>::iterator cur_la;
        for (cur_la = La.begin(); cur_la != La.end(); cur_la++) {
            char l = *cur_la;

            //iterate right chars
            set<char>::iterator cur_ra;
            for (cur_ra = Ra.begin(); cur_ra != Ra.end(); cur_ra++) {
                char r = *cur_ra;

                //check for matches in a
                char contains = 0;
                for (int n = 0; n < a.size(); n++) {
                    if (a[n]->l == l && a[n]->r == r) {
                        contains = 1;
                        break;
                    }
                }
                //MAW was found
                if (!contains) {

                    char l_ch = l;
                    char r_ch = r;

                    if (l_ch != '#' && r_ch != '$' && r_ch != '\0' && l_ch != '$') {

                        if (l_ch < 0) {
                            l_ch += 128;
                            if (l_ch > 0)
                                l_ch = str[psa[i] + l_ch - 1];
                            else
                                l_ch = '!';
                        }
                        if (r_ch < 0) {
                            r_ch += 128;
                            if (r_ch > 0)
                                r_ch = str[psa[i] + d - r_ch];
                            else
                                r_ch = '@';
                        }

                        char* st = new char[d+3];
                        st[d + 2] = '\0';
                        st[0] = l_ch;
                        st[d + 1] = r_ch;
                        int k = 1;
                        for (int f = psa[i]; f < psa[i] + d; f++) {
                            st[k] = str[f];
                            k++;
                        }
                        std::string ss = std::string(st);
                        pmaws.insert(ss);
                    }
                }
            }
        }
    }
}
