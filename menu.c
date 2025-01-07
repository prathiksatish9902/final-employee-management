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
    ADDEMPLOYEE=1,
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
int menu()
{
    const char* admin_username = "admin123";
    const char* admin_password = "123admin";
    char ad_username[20];
    char ad_password[20];
    printf("enter admin user name :");
    scanf("%s",ad_username);
    printf("enter admin password :");
    scanf("%s",ad_password);
    if (strcmp(ad_username, admin_username) == 0 && strcmp(ad_password, admin_password) == 0)
    {
        printf("Access granted. Welcome, admin!\n");
        initialize_file();
        loadEmployeesFromFile();
        int choice, id;
        while (1) {
            printf("--- Employee Management System ---\n");
            printf("1. Add Employee\n");
            printf("2. Delete Employee\n");
            printf("3. Display Deleted Employees\n");
            printf("4. Display Employees\n");
            printf("5. Update Employee\n");
            printf("6. Search Employee\n");
            printf("7. Sort by Id\n");
            printf("8. Sort by Department\n");
            printf("9. Sort by Designation\n");
            printf("10. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
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
        printf("Invalid username or password. Try again!\n");
        return menu();
    }
    return 0;
}
