#ifndef __sysCommands_H
#define __sysCommands_H

void sysCommands(char* , int);

struct bg_prc{
    char name[30];
    int pid;
    struct bg_prc* next;
    int size;
};


#endif