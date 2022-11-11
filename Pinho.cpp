#include <iostream>
#include <string>
#include <vector>
#include <set>




using namespace std;

struct triple {
    int d;
    int i;
    int j;
}typedef triple;

struct tupl {
    int l;
    int r;
}typedef tupl;

triple* trip(int d, int i, int j) {
    triple* ret = (triple*)malloc(sizeof(triple));
    ret->d = d;
    ret->i = i;
    ret->j = j;
    return ret;
}

tupl* tup(int l, int r) {
    tupl* ret = (tupl*)malloc(sizeof(tupl));
    ret->r = r;
    ret->l = l;
    return ret;
}




void algo2(triple* tri, const char* str, int str_len, const int* sa);

void pinho(char* str, int str_len, int* sa, int* lcp) {
    int len = strlen(str);

    vector<triple*> stck;
    stck.push_back(trip(0, 0, 0));
    for (int k = 1; k <= len; k++) {
        int i = k - 1;
        while (stck.size() > 0 && lcp[k] < stck.back()->d) {
            triple* lcpin = stck.back();
            stck.pop_back();
            lcpin->j = k - 1;
            algo2(lcpin, str, str_len, sa);
            i = lcpin->i;
            free(lcpin);
        }
        if (i > 0 && lcp[k] > stck.back()->d) {
            stck.push_back(trip(lcp[k], i, 0));
        }
    }

}

void algo2(triple* tri, const char* str, int str_len, const int* sa) {
    int d = tri->d;
    int i = tri->i;
    int j = tri->j;

    if (d == 0)
        return;

    set<char> La;
    set<char> Ra;
    vector<tupl*> a;

    for (int k = i; k <= j; k++) {
        if (sa[k] == 0)
            La.insert('#');
        else
            La.insert(str[sa[k] - 1]);
        Ra.insert(str[sa[k] + d]);
        if (sa[k] > 0 && sa[k] + d < str_len) {
            if (!str[sa[k] + d])
                std::cout << "r was null";
            a.push_back(tup(str[sa[k] - 1], str[sa[k] + d]));
        }
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
                    if (l != '#' && r != '$' && r!='\0' && l != '$') {
                        cout << "MAW:  ";

                        //whole word
                        cout << l << "";
                        int sa_i = sa[i];
                        for (int f = sa[i]; f <= sa[i] + d - 1; f++) {
                            cout << str[f];
                        }
                        cout << r;

                        cout << " \t";

                        //left
                        cout << l << "";
                        sa_i = sa[i];
                        for (int f = sa[i]; f <= sa[i] + d - 1; f++) {
                            cout << str[f];
                        }

                        //right
                        cout << "  \t";
                        for (int f = sa[i]; f <= sa[i] + d - 1; f++) {
                            cout << str[f];
                        }
                        cout << "" << r << endl;
                    }
                }
            }
        }
    }
}