#include "Header.h"
#include "sysCommands.h"

void jobs_sort(){

    struct bg_prc *temp;
    temp = initial;
    int count = 0;
    struct bg_prc *prev, *curr, *next;
    while (temp != NULL){
        temp = temp->next;
        count++;
    }
    // printf("%d\n", count);
    int i;
    for (i = 0; i < count; i++){

        curr = initial;
        prev = initial;
        while (curr->next != NULL){
            next = curr->next;
            if (curr == initial){

                if (strcmp(curr->name, next->name) > 0){
                    curr->next = next->next;
                    next->next = curr;
                    initial = next;
                    prev = next;
                }
                else{
                    curr = curr->next;
                    prev = initial;
                }
            }
            else{
                // break;
                if (strcmp(curr->name, next->name) > 0){
                    curr->next = next->next;
                    next->next = curr;
                    prev->next = next;
                    prev = next;
                }
                else{
                    curr = curr->next;
                    prev = prev->next;
                }
            }
        }
    }
}