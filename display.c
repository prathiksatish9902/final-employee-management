#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "display.h"
#define FILE_NAME "employees.txt"
//FILE *global_file = NULL;
Employee extern *head;
void displayEmployees() {

    if (head == NULL) {
        printf("No employees to display.\n");
        return;
    }
    Employee *temp = head;
    while (temp != NULL) {
        printf("\n--- Employee Details ---\n");
        printf("Name: %s\n", temp->name);
        printf("Age: %d\n", temp->age);
        printf("Phone: %s\n", temp->phone);
        printf("Email: %s\n", temp->email);
        printf("Address: %s\n", temp->address);
        printf("ID: %d\n", temp->id);
        printf("Join Date: %s\n", temp->join_date);
        printf("Designation: %s\n", temp->designation.name);
        printf("Basic Salary: %.2f\n", temp->salary.basic_salary);
        printf("HRA: %.2f\n", temp->salary.hra);
        printf("DA: %.2f\n", temp->salary.da);
        printf("Net Salary: %.2f\n", temp->salary.net_salary);
        printf("Department: %s (ID: %d)\n", temp->department.name, temp->department.id);
        printf("Team: %s (ID: %d)\n", temp->team.name, temp->team.id);
        printf("Project: %s (ID: %d)\n", temp->project.name, temp->project.id);
        temp = temp->next;
    }
}
