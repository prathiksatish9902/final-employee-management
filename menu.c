#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "fileHandling.h"
#include "addEmployee.h"
#include "deleteEmployee.h"
#include "display.h"
#include "updateEmployee.h"
#include "searchEmployee.h"
#include "sortEmployee.h"
#include "menu.h"
#define FILE_NAME "employees.txt"
FILE extern *global_file;

Employee *head = NULL;

typedef enum {
    ADDADMIN=1,
    ADDEMPLOYEE,
    DELETEEMPLOYEE,
    DISPLAYDELETEDEMPLOYEES,
    DISPLAYEMPLOYEES,
    UPDATEEMPLOYEE,
    SEARCHEMPLOYEE,
    SORTBYId,
    SORTBYDEPARTMENT,
    SORTBYDESIGNATION,
    EXIT
}menuOption;
const char* filename = "admin.txt";
int menu()
{
    char ad_username[20]; char ad_password[20]; // Check if admin.txt exists
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No admin found. Creating a new admin.\n");
        create_admin();
    }
    else
    {
        fclose(file);
    }
    printf("Enter admin username: ");
    scanf("%s", ad_username);
    printf("Enter admin password: ");
    scanf("%s", ad_password);
    if (check_admin(ad_username, ad_password))
    {
        printf("Access granted. Welcome, admin!\n");
        initialize_file();
        loadEmployeesFromFile();
        int choice, id;
        while (1) {
            printf("--- Employee Management System ---\n");
            printf("1. Add admin\n");
            printf("2. Add Employee\n");
            printf("3. Delete Employee\n");
            printf("4. Display Deleted Employees\n");
            printf("5. Display Employees\n");
            printf("6. Update Employee\n");
            printf("7. Search Employee\n");
            printf("8. Sort by Id\n");
            printf("9. Sort by Department\n");
            printf("10. Sort by Designation\n");
            printf("11. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
            case ADDADMIN:
                add_admin();
                break;
            case ADDEMPLOYEE:
                addEmployee();
                saveEmployeesToFile();
                break;
            case DELETEEMPLOYEE:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &id);
                deleteEmployee(id);
                saveEmployeesToFile();
                break;
            case DISPLAYDELETEDEMPLOYEES:
                displayDeletedEmployees();
                break;
            case DISPLAYEMPLOYEES:
                displayEmployees();
                break;
            case UPDATEEMPLOYEE:
                printf("Enter Employee ID to update: ");
                scanf("%d", &id);
                updateEmployee(id);
                saveEmployeesToFile();
                break;
            case SEARCHEMPLOYEE:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                Employee *emp = searchEmployee(id);
                if (emp != NULL) {
                    printf("Employee Found: %s (ID: %d)\n", emp->name, emp->id);
                } else {
                    printf("Employee not found.\n");
                }
                break;
            case SORTBYId:
                sortById();
                break;
            case SORTBYDEPARTMENT:
                sortByDepartment();
                break;
            case SORTBYDESIGNATION:
                sortByDesignation();
                break;
            case EXIT:
                close_file();
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
            }
        }
    }
    else
    {
        printf("Invalid credentials.\n");
        return menu();
    }

    return 0;
}
void create_admin()
{
    char new_username[20];
    char new_password[20];
    printf("Enter new admin username: ");
    scanf("%s", new_username);
    printf("Enter new admin password: ");
    scanf("%s", new_password);
    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s %s\n", new_username, new_password);
        fclose(file); printf("New admin created.\n");
    }
    else {
        printf("Error creating admin.\n");
    }
}
void add_admin() {
    char new_username[20];
    char new_password[20];
    printf("Enter new admin username: ");
    scanf("%s", new_username);
    printf("Enter new admin password: ");
    scanf("%s", new_password);
    FILE* file = fopen(filename, "a");
    if (file) {
        fprintf(file, "%s %s\n", new_username, new_password);
        fclose(file); printf("New admin added.\n");
    }
    else {
        printf("Error adding new admin.\n");
    }
}
int check_admin(const char* username, const char* password) {
    char stored_username[20];
    char stored_password[20];
    FILE* file = fopen(filename, "r");
    if (!file) {
        return 0;
    }
    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF)
    {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
