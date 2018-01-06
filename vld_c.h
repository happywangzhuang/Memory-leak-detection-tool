#pragma once

#include<stdio.h>

void* __malloc(size_t sz, const char* file, size_t line);
void __free(void *ptr);
void check_leak();

#define malloc(sz) __malloc(sz,__FILE__,__LINE__)
#define free(p) __free(p)
