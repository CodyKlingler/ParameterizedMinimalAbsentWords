#pragma once

int* prev_arr(char* str, int str_len);
int* next_arr(char* str, int str_len);
int* param_suffixarray(char* str, int* prev_arr, int str_len);
int* PLCP(int* psa, char* str, int* prev_arr, int str_len);
