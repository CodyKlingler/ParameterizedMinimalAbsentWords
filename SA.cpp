
#include <iostream>
#include <string>

char* cur_str2 = NULL;

int compare(const void* a, const void* b) {
    int ac = *(int*)a;
    int bc = *(int*)b;
    if (ac == bc || !cur_str2) return 0;

    for (int i = 0; ; i++) {
        char ch_a = cur_str2[ac + i];
        char ch_b = cur_str2[bc + i];
        if (ch_a != ch_b)
            return (ch_a > ch_b) ? 1 : -1;
    }
    return 0;
}


int* suffixarray(char* str, int str_len) {
    if (!str)
        return NULL;

    cur_str2 = str;
    str_len = strlen(str);

    int* sa = (int*)malloc(sizeof(int) * str_len);

    for (int i = 0; i < str_len; i++) {
        sa[i] = i;
    }

    cur_str2 = str;

    qsort(sa, str_len, sizeof(int), compare);
    return sa;
}


int* LCP(int* sa, char* str, int str_len) {
    int* lcp = (int*)malloc(sizeof(int) * str_len);
    lcp[0] = 0;

    for (int i = 1; i < str_len; i++) {
        lcp[i] = 0;
        int sa_cur = sa[i];
        int sa_prev = sa[i - 1];
        for (int j = 0; ; j++) {
            char a = str[sa_cur + j];
            char b = str[sa_prev + j];
            if (a != b)
                break;
            lcp[i]++;
        }
    }
    return lcp;
}