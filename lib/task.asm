bits 32
global switch_to_task

; void switch_to_task(uint32_t* old_esp, uint32_t new_esp);
switch_to_task:
    mov eax, [esp + 4] ; old_esp ponteiro
    mov edx, [esp + 8] ; new_esp valor

    push ebp
    push ebx
    push esi
    push edi
    pushfd

    mov [eax], esp ; Salva ESP atual em *old_esp
    mov esp, edx ; Carrega novo ESP

    popfd
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret ; Pula pra nova task
