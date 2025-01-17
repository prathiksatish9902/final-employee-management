#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "deleteEmployee.h"
#include "fileHandling.h"
#include "menu.h"
#define FILE_NAME "employees.txt"
FILE extern *global_file;
Employee extern *head;

void deleteEmployee(int id) {
    Employee *temp = head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Employee not found.\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);

    // Mark as deleted in file and create backup
    markEmployeeAsDeleted(id);
    printf("Employee marked as deleted and backed up successfully!\n");
}

void copyToBackupFile(Employee emp) {
    FILE *backup_file = fopen("deleted_employees.txt", "a");
    if (backup_file == NULL) {
        printf("Error opening backup file!\n");
        return;
    }

    fprintf(backup_file, "%s|%d|%s|%s|%s|%d|%s|%s|%.2f|%.2f|%.2f|%s|%d|%s|%d|%s|%d\n",
            emp.name, emp.age, emp.phone, emp.email, emp.address, emp.id,
            emp.join_date, emp.designation.name, emp.salary.basic_salary,
            emp.salary.hra, emp.salary.da, emp.department.name,
            emp.department.id, emp.team.name, emp.team.id,
            emp.project.name, emp.project.id);

    fclose(backup_file);
}

void markEmployeeAsDeleted(int id) {
    long current_pos;
    Employee temp_emp;
    char line[1024];
    FILE *temp_file = tmpfile();

    if (temp_file == NULL) {
        printf("Error creating temporary file!\n");
        return;
    }

    // Reset file pointer to start
    fseek(global_file, 0, SEEK_SET);

    // Read and process each line
    while (fgets(line, sizeof(line), global_file)) {
        current_pos = ftell(global_file);

        if (sscanf(line, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%f|%f|%f|%[^|]|%d|%[^|]|%d|%[^|]|%d\n",
                   temp_emp.name, &temp_emp.age, temp_emp.phone, temp_emp.email,
                   temp_emp.address, &temp_emp.id, temp_emp.join_date,
                   temp_emp.designation.name, &temp_emp.salary.basic_salary,
                   &temp_emp.salary.hra, &temp_emp.salary.da, temp_emp.department.name,
                   &temp_emp.department.id, temp_emp.team.name, &temp_emp.team.id,
                   temp_emp.project.name, &temp_emp.project.id) == 17) {

            if (temp_emp.id == id) {
                // Copy to backup file
                copyToBackupFile(temp_emp);

                // Write modified line with [DELETED] mark
                fprintf(temp_file, "[DELETED] %s", line);
            } else {
                fprintf(temp_file, "%s", line);
            }
        }
    }

    // Reset both files to beginning
    fseek(global_file, 0, SEEK_SET);
    fseek(temp_file, 0, SEEK_SET);

    // Clear original file
    if (ftruncate(fileno(global_file), 0) != 0) {
        printf("Error truncating file!\n");
        return;
    }

    // Copy temp file contents back to original file
    char ch;
    while ((ch = fgetc(temp_file)) != EOF) {
        fputc(ch, global_file);
    }

    fflush(global_file);
    fclose(temp_file);
}

void displayEmployeeRecord(Employee emp, int isDeleted) {
    printf("\n%s=== Employee ID: %d %s===\n",
           isDeleted ? "[DELETED] " : "",
           emp.id,
           isDeleted ? "[DELETED] " : "");
    printf("Name: %s\n", emp.name);
    printf("Age: %d\n", emp.age);
    printf("Phone: %s\n", emp.phone);
    printf("Email: %s\n", emp.email);
    printf("Address: %s\n", emp.address);
    printf("Join Date: %s\n", emp.join_date);
    printf("Designation: %s\n", emp.designation.name);
    printf("Salary Details:\n");
    printf("  Basic Salary: %.2f\n", emp.salary.basic_salary);
    printf("  HRA: %.2f\n", emp.salary.hra);
    printf("  DA: %.2f\n", emp.salary.da);
    printf("Department: %s (ID: %d)\n", emp.department.name, emp.department.id);
    printf("Team: %s (ID: %d)\n", emp.team.name, emp.team.id);
    printf("Project: %s (ID: %d)\n", emp.project.name, emp.project.id);
    printf("=========================================\n");
}

// Function to display all deleted employees from both main and backup files
void displayDeletedEmployees() {
    Employee temp_emp;
    char line[1024];
    int found = 0;

    printf("\n=== Displaying Deleted Employees ===\n");

    // First, check the main file for records marked as [DELETED]
    printf("\nDeleted Records in Main File:\n");
    fseek(global_file, 0, SEEK_SET);

    while (fgets(line, sizeof(line), global_file)) {
        // Check if line starts with [DELETED]
        if (strstr(line, "[DELETED]") == line) {
            // Skip the [DELETED] prefix for scanning
            char *actual_data = line + 9;  // Length of "[DELETED] "

            if (sscanf(actual_data, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%f|%f|%f|%[^|]|%d|%[^|]|%d|%[^|]|%d\n",
                       temp_emp.name, &temp_emp.age, temp_emp.phone, temp_emp.email,
                       temp_emp.address, &temp_emp.id, temp_emp.join_date,
                       temp_emp.designation.name, &temp_emp.salary.basic_salary,
                       &temp_emp.salary.hra, &temp_emp.salary.da, temp_emp.department.name,
                       &temp_emp.department.id, temp_emp.team.name, &temp_emp.team.id,
                       temp_emp.project.name, &temp_emp.project.id) == 17) {

                displayEmployeeRecord(temp_emp, 1);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No deleted records found in main file.\n");
    }

    // Then, check the backup file
    printf("\nDeleted Records in Backup File:\n");
    FILE *backup_file = fopen("deleted_employees.txt", "r");
    found = 0;

    if (backup_file == NULL) {
        printf("No backup file found or unable to open backup file.\n");
        return;
    }

    while (fgets(line, sizeof(line), backup_file)) {
        if (sscanf(line, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%f|%f|%f|%[^|]|%d|%[^|]|%d|%[^|]|%d\n",
                   temp_emp.name, &temp_emp.age, temp_emp.phone, temp_emp.email,
                   temp_emp.address, &temp_emp.id, temp_emp.join_date,
                   temp_emp.designation.name, &temp_emp.salary.basic_salary,
                   &temp_emp.salary.hra, &temp_emp.salary.da, temp_emp.department.name,
                   &temp_emp.department.id, temp_emp.team.name, &temp_emp.team.id,
                   temp_emp.project.name, &temp_emp.project.id) == 17) {

            displayEmployeeRecord(temp_emp, 1);
            found = 1;
        }
    }

    if (!found) {
        printf("No records found in backup file.\n");
    }

    fclose(backup_file);
}
