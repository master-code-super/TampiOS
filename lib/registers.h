#ifndef REGISTERS_H
#define REGISTERS_H

typedef struct {
    unsigned int ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
} registers_t;

#endif
