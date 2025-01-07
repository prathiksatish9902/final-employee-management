#ifndef SORTEMPLOYEE_H
#define SORTEMPLOYEE_H
Employee* merge(Employee* left, Employee* right);
Employee* split(Employee* head);
Employee* mergeSort(Employee* head);
void sortById();
Employee* mergeByDepartment(Employee* left, Employee* right);
Employee* splitByDepartment(Employee* head);
Employee* mergeSortByDepartment(Employee* head) ;
void sortByDepartment();
void sortByDesignation();
#endif // SORTEMPLOYEE_H
