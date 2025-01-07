cmake_minimum_required(VERSION 3.16)

project(Employee_Mgmt_Final LANGUAGES C)

add_executable(Employee_Mgmt_Final main.c
    structures.h
    addEmployee.h
    deleteEmployee.h
    display.h
    updateEmployee.h
    searchEmployee.h
    sortEmployee.h
    fileHandling.h
    addEmployee.c
    deleteEmployee.c
    display.c
    fileHandling.c
    searchEmployee.c
    sortEmployee.c
    updateEmployee.c
    menu.h
    menu.c)

include(GNUInstallDirs)
install(TARGETS Employee_Mgmt_Final
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
