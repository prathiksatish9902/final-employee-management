#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "addEmployee.h"
#include "sortEmployee.h"
#include "menu.h"
//#define FILE_NAME "employees.txt"
//FILE *global_file = NULL;
Employee extern *head;


Employee* merge(Employee* left, Employee* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->id < right->id) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

Employee* split(Employee* head) {
    if (!head || !head->next) return head;

    Employee* slow = head;
    Employee* fast = head->next;

    // Move `slow` by 1 step and `fast` by 2 steps
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Employee* middle = slow->next;
    slow->next = NULL;
    return middle;
}
Employee* mergeSort(Employee* head) {
    if (!head || !head->next) return head;  // Base case: if the list has 0 or 1 element

    Employee* middle = split(head);  // Split the list into two halves

    // Recursively sort both halves
    Employee* left = mergeSort(head);
    Employee* right = mergeSort(middle);

    // Merge the two sorted halves
    return merge(left, right);
}

void sortById() {

    if (head == NULL || head->next == NULL) return;

    head = mergeSort(head);  // Apply merge sort on the list

    printf("Employees sorted by ID successfully!\n");
}



Employee* mergeByDepartment(Employee* left, Employee* right) {
    if (!left) return right;
    if (!right) return left;

    if (strcmp(left->department.name, right->department.name) < 0) {
        left->next = mergeByDepartment(left->next, right);
        return left;
    } else {
        right->next = mergeByDepartment(left, right->next);
        return right;
    }
}

Employee* splitByDepartment(Employee* head) {
    if (!head || !head->next) return head;

    Employee* slow = head;
    Employee* fast = head->next;

    // Move `slow` by 1 step and `fast` by 2 steps
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Employee* middle = slow->next;
    slow->next = NULL;
    return middle;
}

Employee* mergeSortByDepartment(Employee* head) {
    if (!head || !head->next) return head;  // Base case: if the list has 0 or 1 element

    Employee* middle = splitByDepartment(head);  // Split the list into two halves

    // Recursively sort both halves
    Employee* left = mergeSortByDepartment(head);
    Employee* right = mergeSortByDepartment(middle);

    // Merge the two sorted halves
    return mergeByDepartment(left, right);
}

void sortByDepartment() {
    if (head == NULL || head->next == NULL) return;

    head = mergeSortByDepartment(head);  // Apply merge sort on the list

    printf("Employees sorted by department successfully!\n");
}

void sortByDesignation() {
    if (head == NULL || head->next == NULL) return; // Nothing to sort if 0 or 1 employee

    Employee *i, *j;
    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (get_designation_level(i->designation.name) > get_designation_level(j->designation.name)) {
                // Swap the data between employees i and j
                Employee temp = *i;
                *i = *j;
                *j = temp;

                Employee *temp_next = i->next;
                i->next = j->next;
                j->next = temp_next;
            }
        }
    }
    printf("Employees sorted by designation hierarchy successfully!\n");
}
