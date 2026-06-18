#ifndef TASK_H
#define TASK_H
#include "isr.h"

typedef struct task {
    uint32_t esp, ebp, eip;
    struct task* next;
} task_t;

void task_init();
void task_create(void (*entry)());
void task_switch();

#endif
