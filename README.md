# DSPD2-A2-BT20CSE075
Implementation of Phonebook using AVL trees
Roll No.-BT20CSE075
Subject- DSPD2
Assignment2: Phonebook with AVL trees
v1.0


To keep the code easy to read and manage, there are following seperate files in this assignment.
personal_tree.h,personal_tree.c : Code for the tree of personal contacts and its functionalities
professional_tree.h,professional_tree.c : Code for the tree of professional contacts and its functionalities
phonebook_trees.h,phonebook_trees.c : serves as the interface between the main file and the trees
                                      hides the implementation details of the trees
phonebook_main.c : UI and main function that generates executable
Functionalities provided by Phonebook:
    Trees use phone number of the contact as key.
    1.Insert Contact-option to insert in personal or professional trees
    2.Edit Contact-option to edit details of the contact but not the key
    3.Delete Contact-option to delete a contact, using their key value
    4.Search Contact-search in tree for given key value, prints contact associated with the key
    5.Display Sorted-Display personal/professional contacts in ascending/descending order of keys
    6.Print all- Prints all personal/professional contacts
    7.Range search- Prints all personal/professional contacts in given key search range
    8.Name sort- Prints all personal/professional contacts in ascending order of their names
