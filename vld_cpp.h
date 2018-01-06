#pragma once

#include<iostream>
#include<new>
using namespace std;

void* operator new(size_t sz, const char *file, size_t line);
void operator delete(void *ptr);
void* operator new[](size_t sz, const char *file, size_t line);
void operator delete[](void *ptr);
//void* malloc(size_t sz, const char *file, size_t line);
//void free(void *ptr);
void* __malloc(size_t sz, const char *file, size_t line);
void __free(void *ptr);

#define new new(__FILE__,__LINE__)
#define malloc(sz) __malloc(sz, __FILE__, __LINE__)
#define free(p)  __free(p)

