Roll No.-BT20CSE075
Subject- DSPD2
Assignment1: Phonebook with linked list

To keep the code easy to read and manage, there are 4 seperate files in this assignment.
File 1: Phonebook.h- contains all the declarations for the structures of Phonebook and it contains declarations for functions from Q1-Q8.
File 2: Phonebook.c- contains all the definitions for the functions declared in Phonebook.h.
File 3: BT20CSE075-A1-Q1toQ8.c- contains the main() function and the UI to demonstrate Q1-Q8 of the assignment.
File 4: BT20CSE075-A1-Q9- contains all the extra functions, structures and the main() function to demonstrate Q9(linked list of Phonebooks)

!!!NOTE:Ensure that all these files are in one folder as they depend on the header and .c file of Phonebook!!!
!!!As make command does not come by default on all OS,makefiles are not used,instead compilation instructions for both executables are provided!!!

Compilation instructions:
    To generate executable of Q1-Q8:
        gcc -o BT20CSE075-A1-Q1toQ8 BT20CSE075-A1-Q1toQ8.c Phonebook.c
    To generate executable of Q9:
        gcc -o BT20CSE075-A1-Q9 BT20CSE075-A1-Q9.c Phonebook.c 
 