#ifndef STRING_H
#define STRING_H
 
 int strlen(const char* str);
 void strcpy(char* dest, const char* src);
 int strcmp(const char* s1, const char* s2);
 void* memcpy(void* dest, const void* src, int n);
 void* memset(void* ptr, int value, int num);
 int strncmp(const char* s1, const char* s2, int n);
  #endif
