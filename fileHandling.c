#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "fileHandling.h"
#define FILE_NAME "employees.txt"
FILE *global_file = NULL;
Employee extern *head;
void saveEmployeesToFile() {
    Employee *current = head;

    // Clear file contents
    fseek(global_file, 0, SEEK_SET);
    ftruncate(fileno(global_file), 0);

    // Write each employee to file
    while (current != NULL) {
        fprintf(global_file, "%s|%d|%s|%s|%s|%d|%s|%s|%.2f|%.2f|%.2f|%s|%d|%s|%d|%s|%d\n",
                current->name, current->age, current->phone, current->email,
                current->address, current->id, current->join_date,
                current->designation.name, current->salary.basic_salary,
                current->salary.hra, current->salary.da, current->department.name,
                current->department.id, current->team.name, current->team.id,
                current->project.name, current->project.id);
        current = current->next;
    }

    fflush(global_file);
}
void initialize_file() {
    global_file = fopen(FILE_NAME, "r+");
    if (global_file == NULL) {
        global_file = fopen(FILE_NAME, "w+");
    }
}
void close_file() {
    if (global_file != NULL) {
        fclose(global_file);
    }
}
void loadEmployeesFromFile() {
    // Reset the head of the list
    head = NULL;

    // Reset file position to beginning
    fseek(global_file, 0, SEEK_SET);

    Employee temp_emp;

    // Read each line from the file
    while (fscanf(global_file, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%f|%f|%f|%[^|]|%d|%[^|]|%d|%[^|]|%d\n",
                  temp_emp.name, &temp_emp.age, temp_emp.phone, temp_emp.email,
                  temp_emp.address, &temp_emp.id, temp_emp.join_date,
                  temp_emp.designation.name, &temp_emp.salary.basic_salary,
                  &temp_emp.salary.hra, &temp_emp.salary.da, temp_emp.department.name,
                  &temp_emp.department.id, temp_emp.team.name, &temp_emp.team.id,
                  temp_emp.project.name, &temp_emp.project.id) == 17) {

        // Allocate memory for new employee
        Employee* new_employee = (Employee*)malloc(sizeof(Employee));
        if (new_employee == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

        // Copy data from temporary structure to new employee
        strcpy(new_employee->name, temp_emp.name);
        new_employee->age = temp_emp.age;
        strcpy(new_employee->phone, temp_emp.phone);
        strcpy(new_employee->email, temp_emp.email);
        strcpy(new_employee->address, temp_emp.address);
        new_employee->id = temp_emp.id;
        strcpy(new_employee->join_date, temp_emp.join_date);
        strcpy(new_employee->designation.name, temp_emp.designation.name);
        new_employee->salary.basic_salary = temp_emp.salary.basic_salary;
        new_employee->salary.hra = temp_emp.salary.hra;
        new_employee->salary.da = temp_emp.salary.da;
        calculateNetSalary(&new_employee->salary);
        strcpy(new_employee->department.name, temp_emp.department.name);
        new_employee->department.id = temp_emp.department.id;
        strcpy(new_employee->team.name, temp_emp.team.name);
        new_employee->team.id = temp_emp.team.id;
        strcpy(new_employee->project.name, temp_emp.project.name);
        new_employee->project.id = temp_emp.project.id;
        new_employee->next = NULL;

        // Insert into linked list (maintaining sorted order by name)
        if (head == NULL || strcmp(new_employee->name, head->name) < 0) {
            new_employee->next = head;
            head = new_employee;
        } else {
            Employee* current = head;
            while (current->next != NULL &&
                   strcmp(new_employee->name, current->next->name) > 0) {
                current = current->next;
            }
            new_employee->next = current->next;
            current->next = new_employee;
        }
    }

    // Check if any employees were loaded
    if (head == NULL) {
        printf("No employees found in file.\n");
    } else {
        printf("Employees loaded successfully from file!\n");
    }
}
