#include "string.h"
int strlen(const char* str) {
	int len = 0;
    while(str[len]) {
	len++;
    }
	return len;
}
 
 void strcpy(char* dest, const char* src) {
	 int i = 0;
	 while(src[i]) {
		 dest[i] = src[i];
		 i++;
	 }
	 dest[i] = 0;
 }
 int strcmp(const char* s1, const char* s2) {
	 int i = 0;
	 while(s1[i] && s2[i]) {
		 if(s1[i]!= s2[i]) return s1[i] -s2[i];
		 i++;
	 }
	 return s1[i] - s2[i];
 }
 void* memcpy(void* dest, const void* src, int n) {
	 char* d = (char*)dest;
	 const char* s = (const char*)src;
	 for(int i = 0; i < n; i++) {
		 d[i] = s[i];
	 }
	 return dest;
 }
 void* memset(void* ptr, int value, int num) {
	 unsigned char* p = (unsigned char*)ptr;
	 for(int i = 0; i < num; i++) {
		 p[i] = (unsigned char)value;
	 }
	 return ptr;
 }
 int strncmp(const char* s1, const char* s2, int n) {
    while(n && *s1 && (*s1 == *s2)) { s1++; s2++; n--; }
    if(n == 0) return 0;
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}
