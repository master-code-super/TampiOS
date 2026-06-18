#ifndef KEYBOARD_H
#define KEYBOARD_H

void keyboard_init();
char keyboard_getchar(); // Pega 1 tecla, bloqueia até digitar
int keyboard_available(); // Retorna 1 se tem tecla na fila

#endif
