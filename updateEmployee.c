#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "updateEmployee.h"
#include "searchEmployee.h"
#include "fileHandling.h"
#include "menu.h"
#define FILE_NAME "employees.txt"
FILE extern *global_file;

typedef enum {
    NAME=1,
    AGE,
    PHONE,
    EMAIL,
    ADDRESS,
    DESIGNATION,
    BASICSALARY,
    HRA,
    DA,
    DEPARTMENTNAME,
    DEPARTMENTID,
    TEAMNAME,
    TEAMID,
    PROJECTNAME,
    PROJECTID,
    EXITUPDATE
}updateMenu;

void updateEmployeeField(int id, int field_choice, void* new_value) {
    long start_pos;
    Employee temp_emp;
    int found = 0;
    char line[1024];

    fseek(global_file, 0, SEEK_SET);

    while (1) {
        start_pos = ftell(global_file);
        if (fscanf(global_file, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%f|%f|%f|%[^|]|%d|%[^|]|%d|%[^|]|%d\n",
                   temp_emp.name, &temp_emp.age, temp_emp.phone, temp_emp.email,
                   temp_emp.address, &temp_emp.id, temp_emp.join_date,
                   temp_emp.designation.name, &temp_emp.salary.basic_salary,
                   &temp_emp.salary.hra, &temp_emp.salary.da, temp_emp.department.name,
                   &temp_emp.department.id, temp_emp.team.name, &temp_emp.team.id,
                   temp_emp.project.name, &temp_emp.project.id) != 17) {
            break;
        }

        if (temp_emp.id == id) {
            found = 1;
            break;
        }
    }

    if (!found) return;

    // Calculate field offsets based on actual positions in the file
    long field_offset = 0;
    long current_pos = start_pos;

    switch(field_choice) {
    case NAME:
        field_offset = 0;
        break;
    case AGE:
        field_offset = strlen(temp_emp.name) + 1;
        break;
    case PHONE:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1;
        break;
    case EMAIL:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1;
        break;
    case ADDRESS:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1;
        break;
    case DESIGNATION:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1;
        break;
    case BASICSALARY:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1 +
                       strlen(temp_emp.designation.name) + 1;
        break;
    case HRA:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1 +
                       strlen(temp_emp.designation.name) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.basic_salary) + 1;
        break;
    case DA:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1 +
                       strlen(temp_emp.designation.name) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.basic_salary) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.hra) + 1;
        break;
    case DEPARTMENTNAME:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1 +
                       strlen(temp_emp.designation.name) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.basic_salary) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.hra) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.da) + 1;
        break;
    case DEPARTMENTID:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1 +
                       strlen(temp_emp.designation.name) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.basic_salary) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.hra) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.da) + 1 +
                       strlen(temp_emp.department.name) + 1;
        break;
    case TEAMNAME:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1 +
                       strlen(temp_emp.designation.name) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.basic_salary) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.hra) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.da) + 1 +
                       strlen(temp_emp.department.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.department.id) + 1;
        break;
    case TEAMID:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1 +
                       strlen(temp_emp.designation.name) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.basic_salary) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.hra) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.da) + 1 +
                       strlen(temp_emp.department.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.department.id) + 1 +
                       strlen(temp_emp.team.name) + 1;
        break;
    case PROJECTNAME:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1 +
                       strlen(temp_emp.designation.name) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.basic_salary) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.hra) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.da) + 1 +
                       strlen(temp_emp.department.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.department.id) + 1 +
                       strlen(temp_emp.team.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.team.id) + 1;
        break;
    case PROJECTID:
        field_offset = strlen(temp_emp.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.age) + 1 +
                       strlen(temp_emp.phone) + 1 +
                       strlen(temp_emp.email) + 1 +
                       strlen(temp_emp.address) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.id) + 1 +
                       strlen(temp_emp.join_date) + 1 +
                       strlen(temp_emp.designation.name) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.basic_salary) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.hra) + 1 +
                       snprintf(NULL, 0, "%.2f", temp_emp.salary.da) + 1 +
                       strlen(temp_emp.department.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.department.id) + 1 +
                       strlen(temp_emp.team.name) + 1 +
                       snprintf(NULL, 0, "%d", temp_emp.team.id) + 1 +
                       strlen(temp_emp.project.name) + 1;
        break;
    }

    fseek(global_file, start_pos + field_offset, SEEK_SET);

    switch(field_choice) {
    case NAME:
    case PHONE:
    case EMAIL:
    case ADDRESS:
    case DESIGNATION:
    case DEPARTMENTNAME:
    case TEAMNAME:
    case PROJECTNAME:
        fprintf(global_file, "%s", (char*)new_value);
        break;

    case AGE:
    case DEPARTMENTID:
    case TEAMID:
    case PROJECTID:
        fprintf(global_file, "%d", *(int*)new_value);
        break;

    case BASICSALARY:
    case HRA:
    case DA:
        fprintf(global_file, "%.2f", *(float*)new_value);
        break;
    }

    fflush(global_file);
}

void updateEmployee(int id) {
    int field_choice;
    void* new_value;

    Employee *emp = searchEmployee(id);
    if (emp == NULL) {
        printf("Employee not found.\n");
        return;
    }

    int choice;
    do {
        printf("\n--- Updating Details for %s (ID: %d) ---\n", emp->name, emp->id);
        printf("1. Name\n");
        printf("2. Age\n");
        printf("3. Phone\n");
        printf("4. Email\n");
        printf("5. Address\n");
        printf("6. Designation\n");
        printf("7. Basic Salary\n");
        printf("8. HRA\n");
        printf("9. DA\n");
        printf("10. Department Name\n");
        printf("11. Department ID\n");
        printf("12. Team Name\n");
        printf("13. Team ID\n");
        printf("14. Project Name\n");
        printf("15. Project ID\n");
        printf("16. Exit Update\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case NAME:
            printf("Enter New Name: ");
            scanf(" %[^\n]", emp->name);
            break;
        case AGE:
            printf("Enter New Age: ");
            scanf("%d", &emp->age);
            break;
        case PHONE:
            printf("Enter New Phone: ");
            scanf(" %[^\n]", emp->phone);
            break;
        case EMAIL:
            printf("Enter New Email: ");
            scanf(" %[^\n]", emp->email);
            break;
        case ADDRESS:
            printf("Enter New Address: ");
            scanf(" %[^\n]", emp->address);
            break;
        case DESIGNATION:
            printf("Enter New Designation: ");
            scanf(" %[^\n]", emp->designation.name);
            break;
        case BASICSALARY:
            printf("Enter New Basic Salary: ");
            scanf("%f", &emp->salary.basic_salary);
            calculateNetSalary(&emp->salary); // Recalculate net salary
            break;
        case HRA:
            printf("Enter New HRA: ");
            scanf("%f", &emp->salary.hra);
            calculateNetSalary(&emp->salary); // Recalculate net salary
            break;
        case DA:
            printf("Enter New DA: ");
            scanf("%f", &emp->salary.da);
            calculateNetSalary(&emp->salary); // Recalculate net salary
            break;
        case DEPARTMENTNAME:
            printf("Enter New Department Name: ");
            scanf(" %[^\n]", emp->department.name);
            break;
        case DEPARTMENTID:
            printf("Enter New Department ID: ");
            scanf("%d", &emp->department.id);
            break;
        case TEAMNAME:
            printf("Enter New Team Name: ");
            scanf(" %[^\n]", emp->team.name);
            break;
        case TEAMID:
            printf("Enter New Team ID: ");
            scanf("%d", &emp->team.id);
            break;
        case PROJECTNAME:
            printf("Enter New Project Name: ");
            scanf(" %[^\n]", emp->project.name);
            break;
        case PROJECTID:
            printf("Enter New Project ID: ");
            scanf("%d", &emp->project.id);
            break;
        case EXITUPDATE:
            printf("Exiting update menu.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 16);

    printf("Employee details updated successfully!\n");
    updateEmployeeField( id,  field_choice,  new_value);

}
