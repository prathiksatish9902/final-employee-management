#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "addEmployee.h"
#include "fileHandling.h"
#include "menu.h"
#define FILE_NAME "employees.txt"
FILE extern *global_file;
Employee extern *head;
const char *designations[] = {
    "Intern",
    "Junior Developer",
    "Developer",
    "Senior Developer",
    "Team Lead",
    "Manager",
    "Director",
    "Vice President",
    "CEO"
};
const int designation_count = 9;


int get_designation_level(const char *designation) {
    for (int i = 0; i < designation_count; i++) {
        if (strcmp(designations[i], designation) == 0) {
            return i;
        }
    }
    return -1; // Return -1 if the designation is not found
}
void addEmployeeToFile(Employee *emp) {
    long file_size;
    Employee temp_emp;

    fseek(global_file, 0, SEEK_END);
    file_size = ftell(global_file);

    if (file_size == 0) {
        fprintf(global_file, "%s|%d|%s|%s|%s|%d|%s|%s|%.2f|%.2f|%.2f|%s|%d|%s|%d|%s|%d\n",
                emp->name, emp->age, emp->phone, emp->email, emp->address, emp->id,
                emp->join_date, emp->designation.name, emp->salary.basic_salary,
                emp->salary.hra, emp->salary.da, emp->department.name,
                emp->department.id, emp->team.name, emp->team.id,
                emp->project.name, emp->project.id);
        return;
    }

    // Find correct position for sorted insertion by name
    fseek(global_file, 0, SEEK_SET);
    long insert_pos = 0;

    while (fscanf(global_file, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%f|%f|%f|%[^|]|%d|%[^|]|%d|%[^|]|%d\n",
                  temp_emp.name, &temp_emp.age, temp_emp.phone, temp_emp.email,
                  temp_emp.address, &temp_emp.id, temp_emp.join_date,
                  temp_emp.designation.name, &temp_emp.salary.basic_salary,
                  &temp_emp.salary.hra, &temp_emp.salary.da, temp_emp.department.name,
                  &temp_emp.department.id, temp_emp.team.name, &temp_emp.team.id,
                  temp_emp.project.name, &temp_emp.project.id) == 17) {

        if (strcmp(emp->name, temp_emp.name) < 0) {
            break;
        }
        insert_pos = ftell(global_file);
    }

    // Shift existing records
    long current_pos = file_size;
    char ch;
    while (current_pos > insert_pos) {
        fseek(global_file, current_pos - 1, SEEK_SET);
        fread(&ch, 1, 1, global_file);
        fseek(global_file, current_pos, SEEK_SET);
        fwrite(&ch, 1, 1, global_file);
        current_pos--;
    }

    // Insert new record
    fseek(global_file, insert_pos, SEEK_SET);
    fprintf(global_file, "%s|%d|%s|%s|%s|%d|%s|%s|%.2f|%.2f|%.2f|%s|%d|%s|%d|%s|%d\n",
            emp->name, emp->age, emp->phone, emp->email, emp->address, emp->id,
            emp->join_date, emp->designation.name, emp->salary.basic_salary,
            emp->salary.hra, emp->salary.da, emp->department.name,
            emp->department.id, emp->team.name, emp->team.id,
            emp->project.name, emp->project.id);
    fflush(global_file);
}

void addEmployee() {

    Employee *new_employee = (Employee *)malloc(sizeof(Employee));

    // Input employee details
    printf("Enter Name: ");
    scanf(" %[^\n]", new_employee->name);
    printf("Enter Age: ");
    scanf("%d", &new_employee->age);
    printf("Enter Phone: ");
    scanf(" %[^\n]", new_employee->phone);
    printf("Enter Email: ");
    scanf(" %[^\n]", new_employee->email);
    printf("Enter Address: ");
    scanf(" %[^\n]", new_employee->address);
    printf("Enter ID: ");
    scanf("%d", &new_employee->id);
    printf("Enter Join Date: ");
    scanf(" %[^\n]", new_employee->join_date);

    int valid_designation = 0;
    do {
        printf("Enter Designation: ");
        scanf(" %[^\n]", new_employee->designation.name);

        if (get_designation_level(new_employee->designation.name) != -1) {
            valid_designation = 1;
        } else {
            printf("Invalid designation. Please enter one of the following:\n");
            for (int i = 0; i < designation_count; i++) {
                printf("- %s\n", designations[i]);
            }
        }
    } while (!valid_designation);

    printf("Enter Basic Salary: ");
    scanf("%f", &new_employee->salary.basic_salary);
    printf("Enter HRA: ");
    scanf("%f", &new_employee->salary.hra);
    printf("Enter DA: ");
    scanf("%f", &new_employee->salary.da);
    calculateNetSalary(&new_employee->salary);

    printf("Enter Department Name: ");
    scanf(" %[^\n]", new_employee->department.name);
    printf("Enter Department ID: ");
    scanf("%d", &new_employee->department.id);
    printf("Enter Team Name: ");
    scanf(" %[^\n]", new_employee->team.name);
    printf("Enter Team ID: ");
    scanf("%d", &new_employee->team.id);
    printf("Enter Project Name: ");
    scanf(" %[^\n]", new_employee->project.name);
    printf("Enter Project ID: ");
    scanf("%d", &new_employee->project.id);

    // Insert the employee in sorted order by name
    if (head == NULL || strcmp(new_employee->name, head->name) < 0) {
        // If the list is empty or new employee's name is smaller than head's name
        new_employee->next = head;
        head = new_employee;
    } else {
        // Traverse the list to find the correct position
        Employee *current = head;
        while (current->next != NULL && strcmp(new_employee->name, current->next->name) > 0) {
            current = current->next;
        }

        // Insert the new employee after the found position
        new_employee->next = current->next;
        current->next = new_employee;

    }



    printf("Employee added successfully!\n");
    // Write to file
    addEmployeeToFile(new_employee);

}

void calculateNetSalary(Salary *salary) {
    salary->net_salary = salary->basic_salary + salary->hra + salary->da;
}
