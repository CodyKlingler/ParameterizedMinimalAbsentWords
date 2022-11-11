#include <iostream>
#include <string>


int* prev_arr(char* str, int str_len) {

    //reset
    int* p_arr = (int*)malloc(sizeof(int) * str_len);
    memset(p_arr, -1, sizeof(int) * str_len);

    //reset previous array
    int* prev_occ = (int*)malloc(sizeof(int) * (255));
    memset(prev_occ, -1, sizeof(int) * (255));

    for (int i = 0; i < str_len; i++) {
        char c = str[i];
        if (c >= 'a' && c <= 'z') { // if is lower case
            if (prev_occ[c] < 0) {
                p_arr[i] = 0;
            }
            else {
                p_arr[i] = 0 + i - prev_occ[c];
            }
            prev_occ[c] = i;
        }
    }
    free(prev_occ);
    return p_arr;
}


int* next_arr(char* str, int str_len) {
    //reset
    int* n_arr = (int*)malloc(sizeof(int) * str_len);
    memset(n_arr, -1, sizeof(int) * str_len);

    //reset previous array
    int* next_occ = (int*)malloc(sizeof(int) * (255));
    memset(next_occ, -1, sizeof(int) * (255));

    for (int i = str_len-1; i >= 0; i--) {
        char c = str[i];
        if (c >= 'a' && c <= 'z') { // if is lower case
            if (next_occ[c] < 0) {
                n_arr[i] = 0;
            }
            else {
                n_arr[i] = next_occ[c] - i;
            }
            next_occ[c] = i;
        }
    }
    free(next_occ);
    return n_arr;
}



char* cur_str = NULL;
int* p_values = NULL;

int param_compare(const void* a, const void* b) {
    int ac = *(int*)a;
    int bc = *(int*)b;
    if (ac == bc || !cur_str || !p_values) return 0;

    //std::cout << "index a:" << ac << "    index b:" << bc << std::endl;

    for (int i = 0; ; i++) {
        int i_a = p_values[ac + i];
        int i_b = p_values[bc + i];

        char ch_a = cur_str[ac + i];
        char ch_b = cur_str[bc + i];

        if (!ch_a || !ch_b)
            return ch_a ? 1 : -1;

        //std::cout << ch_a << "    " << ch_b << std::endl;
        //std::cout << i_a << "    " << i_b << std::endl;
        
        // do comparison
        if (i_a >= 0 && i_b >= 0) {

            //if the p_char is the first occurence, set to 0
            if (i - i_a < 0) 
                i_a = 0;
            if (i - i_b < 0) 
                i_b = 0;
            if(i_a != i_b)
                return (i_a > i_b) ? 1 : -1;
        }
        else if (i_a < 0 && i_b < 0) {
            if (ch_a != ch_b)
                return (ch_a > ch_b) ? 1 : -1;
        }
        else {
            return i_a >= 0 ? -1 : 1;
        }

    }
    return 0;
}

int* param_suffixarray(char* str, int* prev_arr, int str_len) {

    int* psa = (int*)malloc(sizeof(int) * str_len);

    for (int i = 0; i < str_len; i++) {
        psa[i] = i;
    }

    cur_str = str;
    p_values = prev_arr;

    qsort(psa, str_len, sizeof(int), param_compare);
    return psa;
}


int* PLCP(int* psa, char* str, int* prev_arr, int str_len) {
    int* plcp = (int*)malloc(sizeof(int) * str_len);
    plcp[0] = 0;

    for (int i = 1; i < str_len; i++) {
        plcp[i] = 0;
        int sa_cur = psa[i];
        int sa_prev = psa[i - 1];
        for (int j = 0; ; j++) {
            int i_a = prev_arr[sa_cur + j];
            int i_b = prev_arr[sa_prev + j];
            char ch_a = str[sa_cur + j];
            char ch_b = str[sa_prev + j];

            if (!ch_a || !ch_b)
                break;

            //if either is parameterized
            if (i_a >= 0 && i_b >= 0) {

                //if the p_char is the first occurence, set to 0
                if (j - i_a < 0)
                    i_a = 0;
                if (j - i_b < 0)
                    i_b = 0;

                if (i_a != i_b)
                    break;
            }
            else {
                if (ch_a != ch_b)
                    break;
            }
            plcp[i]++;
        }
    }
    return plcp;
}

