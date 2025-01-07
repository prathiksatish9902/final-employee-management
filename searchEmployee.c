#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "searchEmployee.h"
Employee extern *head;

//#define FILE_NAME "employees.txt"
//FILE *global_file = NULL;

Employee* searchEmployee(int id) {

    Employee *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
