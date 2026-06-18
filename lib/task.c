#include "task.h"

task_t main_task;
task_t task2_struct;
task_t* current_task = &main_task;

uint8_t task2_stack[4096]; // Stack real pra task2

void task_init() {
    main_task.next = &task2_struct;
    task2_struct.next = &main_task;
}

void task_create(void (*entry)()) {
    uint32_t* stack = (uint32_t*)(task2_stack + 4096);
    *(--stack) = (uint32_t)entry; // eip
    *(--stack) = 0; // ebp
    *(--stack) = 0; // ebx
    *(--stack) = 0; // esi
    *(--stack) = 0; // edi

    task2_struct.esp = (uint32_t)stack;
    task2_struct.ebp = (uint32_t)stack;
}

void task_switch() {
    current_task = current_task->next;
}
